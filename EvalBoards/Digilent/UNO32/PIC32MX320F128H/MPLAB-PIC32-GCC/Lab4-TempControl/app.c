/**************************************************************************
 * File:		app.c
 * Date:		October 4, 2013
 * Status:       in development - temperature control not implemented but the
 *                                code instantiated in the two tasks
 *                                does get the two tasks separate arguments
 *                                correctly and turn the fans on and off.
 * Processor:	PIC32MX320F128H
 * Toolchain:	MPLAB-X
 * Board:	UNO32 from Digilent
 * Programmer:	M.J. Batchelder
 * Organization:	CENG 448/548, SDSMT
 * RTOS:		uCOS-III from Micrium
 *
 * Description:	Lab4.  Temperature controller with a heater and a fan activated
 *               with the FET on the Basic Shield
 * Tasks:	Start task which also blinks the Basic Shield LEDs
 *              Temperature control task1:  turns on/off heater1 and on/off fan1
 *                                          temperature sensor 1 input to ADC
 *              Temperature control task2:  turns on/off heater2 and on/off fan2
 *                                          temperature sensor 2 input to ADC
 *
 *
 * Note: baud rate is set in UART1.h
 **************************************************************************/
#include <includes.h>

/*
 *********************************************************************************************************
 *                                                Task Stacks/TCB
 *********************************************************************************************************
 */

#define TASK_STK_SIZE 320

#define APP_CFG_TASK_ONE_STK_SIZE TASK_STK_SIZE
#define APP_CFG_TASK_TWO_STK_SIZE TASK_STK_SIZE

#define  APP_CFG_TASK_ONE_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_ONE_STK_SIZE_LIMIT (APP_CFG_TASK_ONE_STK_SIZE * (100u - APP_CFG_TASK_ONE_STK_SIZE_PCT_FULL))   / 100u

#define  APP_CFG_TASK_TWO_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_TWO_STK_SIZE_LIMIT (APP_CFG_TASK_TWO_STK_SIZE * (100u - APP_CFG_TASK_TWO_STK_SIZE_PCT_FULL))   / 100u


//#define APP_CFG_TASK_ONE_STK_SIZE_LIMIT TASK_STK_SIZE-32
//#define APP_CFG_TASK_TWO_STK_SIZE_LIMIT TASK_STK_SIZE-32

static OS_TCB App_TaskStartTCB;
static CPU_STK App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static OS_TCB App_TaskOneTCB;
static CPU_STK App_TaskOneStk[APP_CFG_TASK_ONE_STK_SIZE];

static OS_TCB App_TaskTwoTCB;
static CPU_STK App_TaskTwoStk[APP_CFG_TASK_TWO_STK_SIZE];


/*
 *********************************************************************************************************
 *                                            Task PROTOTYPES
 *********************************************************************************************************
 */

void App_TaskStart(void *p_arg);
void AppTaskCreate(void);

void App_TaskControl(void *data);


/*
 *********************************************************************************************************
 *                                            Task Priorities
 *********************************************************************************************************
 */

#define APP_CFG_TASK_ONE_PRIO 4
#define APP_CFG_TASK_TWO_PRIO 5


/*
 *********************************************************************************************************
 *                                                ADC Semaphore
 *********************************************************************************************************
 */
OS_SEM AdcSem;


// *********************************************************************
// GPIO defines     Digilent Basic Shield for UNO32
// *********************************************************************
// Open Drain FETs
#define HEATER1         0 //_RD0    // Connector J7-1
#define FAN1            1 //_RD1    //           J7-2
#define HEATER2         2 //_RD2    //           J8-1
#define FAN2            3 //_RD3    //           J8-2
// Pushbutton switches
#define TEST_HEATER1_SW	_RF1    // Port F bit 1 switch
#define TEST_FAN1_SW     _RD5   // Port D bit 5 switch
#define TEST_HEATER2_SW	_RD6    // Port D bit 6 switch
#define TEST_FAN2_SW	_RD7    // Port D bit 7 switch


/*  Analog to Digital Converter
 * UNO32 PIC32
 *   A0	AN2	Connected to Pot
 *   A1	AN4	Thermistor1
 *   A2	AN8	Thermistor2
 *   A3	AN10
 *   A4	AN12
 *   A5	AN14
 */

#define ADC_CH_THERMISTOR_ONE   4   // AN4 is UNO32 Pin A1
#define ADC_CH_THERMISTOR_TWO   8   // AN8 is UNO32 Pin A2

/*
 *********************************************************************************************************
 *                                                Structure for data passed to control tasks
 *********************************************************************************************************
 */
#define NO_CONTROL_TASKS 2
typedef struct {
	CPU_INT08U	DesiredTemperature;
	CPU_INT08U	HeaterControlNumber;
	CPU_INT08U	FanControlNumber;
	CPU_INT08U	SensorChannelNumber;
	CPU_INT08U	UpdatePeriod;
} CONTROLLER_DATA;

CONTROLLER_DATA SystemDataArray[NO_CONTROL_TASKS];

void initSys(void) {
// Initialize parameters for temperature controller 1
        SystemDataArray[0].HeaterControlNumber = HEATER1;
        SystemDataArray[0].FanControlNumber = FAN1;
        SystemDataArray[0].SensorChannelNumber = ADC_CH_THERMISTOR_ONE;
        SystemDataArray[0].DesiredTemperature = 110;
        SystemDataArray[0].UpdatePeriod = 1;

// Initialize parameters for temperature controller 2
        SystemDataArray[1].HeaterControlNumber = HEATER2;
        SystemDataArray[1].FanControlNumber = FAN2;
        SystemDataArray[1].SensorChannelNumber = ADC_CH_THERMISTOR_TWO;
        SystemDataArray[1].DesiredTemperature = 90;
        SystemDataArray[1].UpdatePeriod = 3;
}

// *********************************************************************
// Screen defines and function prototypes
// *********************************************************************
#define SCREEN_X_START      1
#define SCREEN_X_END        80
#define SCREEN_Y_START      1
#define SCREEN_Y_END        25

void Screen_Init(void);
void Screen_Clear(void);
void Screen_MoveCursor(int Xpos, int Ypos);
int Screen_WriteChar(int x, int y, char c);
int Screen_WriteNumber(int x, int y, int number);
void Screen_OffCursor(void);
void Screen_OnCursor(void);

// ********************************************************************* */
// Global Variables
// *********************************************************************

// Temperature lookup table for 10K thermistor with 10K voltage divider.
// Index is 7-bit value from ADC, entry is deg C
const  CPU_INT08U AD2Temp[] = {
    164, 147, 131, 122, 115, 109, 105, 101, 98, 95, 93, 90, 88, 86, 84, 83,
    81, 79, 78, 76, 75, 74, 73, 71, 70, 69, 68, 67, 66, 65, 64, 63,
    63, 62, 61, 60, 59, 58, 58, 57, 56, 55, 55, 54, 53, 53, 52, 51,
    51, 50, 49, 49, 48, 48, 47, 46, 46, 45, 45, 44, 43, 43, 42, 42,
    41, 41, 40, 40, 39, 39, 38, 38, 37, 37, 36, 35, 35, 34, 34, 33,
    33, 32, 32, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27, 27, 26, 26,
    25, 25, 24, 24, 23, 23, 22, 22, 21, 21, 20, 20, 19, 19, 18, 18,
    17, 17, 16, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10
};
// ------------------------------------------------------------
// Device control:  heater, fan on/off
// ------------------------------------------------------------

void deviceOn(int i)	// FET on turns on heater or fan
{
  mPORTDSetBits(1<<i);
}

void deviceOff(int i) // FET off turns off heater or fan
{
  mPORTDClearBits(1<<i);
}

void initDevice(void) // Port bits connected to FETs set as outputs and turned off
{
mPORTDOutputConfig((IOPORT_BIT_0 | IOPORT_BIT_1 |   IOPORT_BIT_2 | IOPORT_BIT_3));
mPORTDClearBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3));
}


// ------------------------------------------------------------
// ADC Defines
// ------------------------------------------------------------
#define POT     2      // 10k potentiometer on AN0 input
#define CH (POT)
#define AINPUTS 0xfeeb  // Analog inputs for POT pin A0 (AN2), thermistor1 (AN4), thermistor2 (AN8)
#define SAMC 2	// Auto-sample time bits 1-31 Tad
#define ADCS 2	// ADC Conversion Clock select bits Tad = 2*(ADCS+1)*Tpb
//	Ex:  ADCS = 2, SAMC = 2,Tpb = 25 ns (Fpb = 40 MHz)
//	Tad = Tpb*2*(2+1) = 25*6 = 150 ns
//	Auto-sample time = 2*Tad = 300 ns
//	12 Tad required for conversion = 150 * 12 = 1.8 us
//	total ADC time = 12*150 + 300 = 2.1 us
#define AD1CON3_BITS ((SAMC<<8)|ADCS)


// ------------------------------------------------------------
// Initialize ADC
// ------------------------------------------------------------
// initialize the ADC for single conversion, select input pins

void initADC(int amask) {
    AD1PCFG = amask; // select analog input pins:
    AD1CON1 = 0x00E0; // auto convert after end of sampling
    AD1CSSL = 0; // no scanning required
    AD1CON2 = 0; // use MUXA, AVss/AVdd used as Vref+/-
    AD1CON3 = AD1CON3_BITS;
    AD1CON1SET = 0x8000; // turn on the ADC
    AD1CHSbits.CH0SA = CH; // select analog input channel
} //initADC

int readADC(int ch) {
    AD1CHSbits.CH0SA = ch; // select analog input channel
    AD1CON1bits.SAMP = 1; // start sampling
    while (!AD1CON1bits.DONE); // wait to complete conversion
    return ADC1BUF0; // read the conversion result
} // readADC

int readTemperature(int ch) {
    // Acquire ADC semaphore: OSSemPend()
    // start conversion
    // wait for response with timeout
    // if timedout release aemaphore, return error code
    // else release semaphore, return ADC value
    OS_ERR err;
    CPU_TS ts;
    int val;

    OSSemPend(&AdcSem, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    if (err == OS_ERR_NONE) {
        val = readADC(ch);
        OSSemPost(&AdcSem, OS_OPT_POST_1, &err);
    }
    else {
        val = -1;   // Error
    }
    return val;
}


/*
 *********************************************************************************************************
 *                                                main()
 *
 * Description : This is the standard entry point for C code.
 *
 * Arguments   : none
 *********************************************************************************************************
 */
// The pragma config is in bsp.c
//#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF

int main(void) {

    OS_ERR os_err;

    CPU_Init(); /* Initialize the uC/CPU services                           */

    BSP_IntDisAll();

    OSInit(&os_err); /* Init uC/OS-III.                                     */

    OSSemCreate(&AdcSem, "ADC Semaphore", 1, &os_err); // Create and init to 1

    OSTaskCreate((OS_TCB *) & App_TaskStartTCB, /* Create the start task    */
            (CPU_CHAR *) "Start",
            (OS_TASK_PTR) App_TaskStart,
            (void *) 0,
            (OS_PRIO) APP_CFG_TASK_START_PRIO,
            (CPU_STK *) & App_TaskStartStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    OSStart(&os_err); /* Start multitasking (i.e. give control to uC/OS-III).     */

    (void) &os_err;

    return (0);
}

/*$PAGE*/

/*
 *********************************************************************************************************
 *                                          STARTUP TASK
 *
 * Description : This is an example of a startup task.
 * Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
 *********************************************************************************************************
 */

void App_TaskStart(void *p_arg) {
//#if CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL // maybe not needed for uCOS-III
//    CPU_SR cpu_sr;
//#endif
    CPU_INT08U i;
    CPU_INT08U j;

    (void) p_arg;
    OS_ERR err;

    BSP_InitIO(); /* Initialize BSP functions                                 */

#if OS_CFG_STAT_TASK_EN > 0   // Set in os_cfg.h
    OSStatTaskCPUUsageInit(&err);
    if (err != OS_ERR_NONE) {
        putsU1("Error starting OSStatTaskCPUUsageInit ");
    }
#endif

    initU1(); // Initialize UART1

    initADC(AINPUTS); // Initialize the Analog to Digital Converter

    initSys();  // Initialize the temperature control system parameters passes to each control task

    initDevice();  // Initialize heater, fan control port

    AppTaskCreate(); /* Create application tasks                                 */

    while (DEF_TRUE) { /* Task body, always written as an infinite loop.            */

#if OS_CFG_STAT_TASK_EN > 0 // Set in os_cfg.h
        OSSchedLock(&err); // Don't let another task run as it might change cursor position
        Screen_MoveCursor(40, 2); // before  writting to the screen
        UART_PrintNum(OSStatTaskCPUUsage);
        Screen_MoveCursor(40, 3); // before  writting to the screen
        UART_PrintNum(OSTaskQty);
        Screen_MoveCursor(40, 4); // before  writting to the screen
        //UART_PrintNum3(App_TaskStartTCB.StkFree);
        UART_PrintNum3(App_TaskTwoTCB.StkFree);
        Screen_MoveCursor(40, 5); // before  writting to the screen
        //UART_PrintNum3(App_TaskStartTCB.StkUsed);
        UART_PrintNum3(App_TaskTwoTCB.StkUsed);
        OSSchedUnlock(&err); // Ok for other tasks to run
#endif

        for (j = 0; j < 2; j++) {
            for (i = 1; i < 9; i++) {
                LED_Toggle(i);
                OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
            }

            for (i = 0; i < 8; i++) {
                LED_Toggle(0);
                OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
            }
        }

        for (; j > 0; j--) {
            for (i = 9; i > 0; --i) {
                LED_Toggle(i);
                OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
            }

            for (i = 0; i < 8; i++) {
                LED_Toggle(0);
                OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
            }
        }
    }
}

/*$PAGE*/

/*
 *********************************************************************************************************
 *                                        CREATE APPLICATION TASKS
 *
 * Description: This function creates the application tasks.
 *
 * Arguments  : none.
 *
 * Note(s)    : none.
 *********************************************************************************************************
 */

void AppTaskCreate(void) {

    OS_ERR os_err, err;
    unsigned char i;
    char key;

    Screen_Init();

    Screen_MoveCursor(8, 8);
    putsU1("uC/OS-III ");  putsU1("Version " ); putsU1(uint2str(OSVersion(&err), 10));
    putsU1(" The Real-Time Kernel running on the PIC32 \n\r");
    putsU1(" Temperature Control Application\r\n");
    
    OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_HMSM_STRICT, &err); /* Wait two seconds */
    if (err != OS_ERR_NONE) {
        putsU1("Error OSTimeDlyHMSM ");
    }
    Screen_Init();
    Screen_OffCursor();

    OSTaskCreate((OS_TCB *) & App_TaskOneTCB, /* Create control one task   */
            (CPU_CHAR *) "One",
            (OS_TASK_PTR) App_TaskControl,
            (void *)&SystemDataArray[0],
            (OS_PRIO) APP_CFG_TASK_ONE_PRIO,
            (CPU_STK *) & App_TaskOneStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_ONE_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_ONE_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    if (os_err != OS_ERR_NONE) {
        putsU1("Error starting task: One ");
    }


    OSTaskCreate((OS_TCB *) & App_TaskTwoTCB, // Create control two task
            (CPU_CHAR *) "Two",
            (OS_TASK_PTR) App_TaskControl,
            (void *)&SystemDataArray[1],
            (OS_PRIO) APP_CFG_TASK_TWO_PRIO,
            (CPU_STK *) & App_TaskTwoStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_TWO_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_TWO_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    if (os_err != OS_ERR_NONE) {
        putsU1("Error starting task: Two ");
    }
}


/*$PAGE*/


/* ********************************************************************* */
/* Local functions */
// *********************************************************************

// Prints a 2 digit base 10 number

void UART_PrintNum(int i) {
    putU1(i / 10u + '0');
    putU1(i % 10u + '0');
}

// Prints a 3 digit base 10 number

void UART_PrintNum3(int i) {
    putU1(i / 100u + '0');
    putU1((i % 100) / 10u + '0');
    putU1(((i % 100) % 10) + '0');
}


void Screen_Clear(void) {
    putU1(0x1B);
    putU1('c');
}

void Screen_OffCursor(void) // Doesn't seem to work
{
    putU1(0x1B);
    putU1('[');
    putU1('?');
    putU1(25);
    putU1('l');
}

void Screen_OnCursor(void) {
    putU1(0x1B);
    putU1('[');
    putU1('?');
    putU1(25);
    putU1('h');
}

void Screen_MoveCursor(int Xpos, int Ypos) {
    putU1(0x1B);
    putU1('[');
    UART_PrintNum(Ypos);
    putU1(';');
    UART_PrintNum(Xpos);
    putU1('H');
}

int Screen_WriteChar(int x, int y, char c) {
    OS_ERR err;
    if ((x > SCREEN_X_END) || (x < SCREEN_X_START) ||
            (y > SCREEN_Y_END) || (y < SCREEN_Y_START)) {
        return 1; // Error
    }
    OSSchedLock(&err); // Don't let another task run as it might change cursor position
    Screen_MoveCursor(x, y); // before the character is written to the screen
    putU1(c);
    OSSchedUnlock(&err); // Ok for other tasks to run
}

int Screen_WriteNumber(int x, int y, int number) {
    OS_ERR err;
    if ((x > SCREEN_X_END) || (x < SCREEN_X_START) ||
            (y > SCREEN_Y_END) || (y < SCREEN_Y_START)) {
        return 1; // Error
    }
    OSSchedLock(&err); // Don't let another task run as it might change cursor position
    Screen_MoveCursor(x, y); // before writing the value to the screen
    UART_PrintNum(number);
    OSSchedUnlock(&err); // Ok for other tasks to run
}

void Screen_Init(void) {
    int i;
    Screen_Clear();
}

void App_TaskControl(void *pdata) {
    CONTROLLER_DATA *SystemPtr;
    SystemPtr = (CONTROLLER_DATA *)pdata;

    OS_ERR err;
    unsigned int val, htr, fan, ch, desiredTemp, updatePeriod, measuredTemp;

    htr = SystemPtr->HeaterControlNumber;
    fan = SystemPtr->FanControlNumber;
    ch  = SystemPtr->SensorChannelNumber;
    desiredTemp = SystemPtr->DesiredTemperature;
    updatePeriod  = SystemPtr->UpdatePeriod;
   
    while (1) {  // Not fully implemented
        OSTimeDlyHMSM(0, 0, updatePeriod, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        deviceOn(fan);
        OSTimeDlyHMSM(0, 0, updatePeriod, 0, OS_OPT_TIME_HMSM_STRICT, &err);
        deviceOff(fan);//
        val = readTemperature(ch);
        val = val >> 3; // ADC value is 10 bits but only 7 bits needed for lookup table
        measuredTemp = AD2Temp[val];

        putsU1("Ch "); putsU1(uint2str(ch,10)); putsU1(" ");
        putsU1("value = ");  putsU1(uint2str(val),10); putsU1(" ");
        putsU1("Temp deg C = "); putsU1(uint2str(measuredTemp),10); putsU1("\r\n");
	if (measuredTemp > desiredTemp)
            deviceOff(htr);			// Temperature too high, turn heater off
	else
            deviceOn(htr);			// Temperature too low, turn heater on

    }
}




