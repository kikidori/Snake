/**************************************************************************
 * File:		app.c
 * Date:		October 26, 2013
 * Status:       in development
 * Processor:	PIC32MX320F128H
 * Toolchain:	MPLAB-X
 * Board:	UNO32 from Digilent
 * Programmer:	M.J. Batchelder
 * Organization:	CENG 448/548, SDSMT
 * RTOS:		uCOS-III from Micrium
 *
 * Description:	Lab5.  Simple Robot Control
 *               PWM motors with the FET on the Basic Shield
 * Tasks:	Start task which also blinks the Basic Shield LEDs
 *              Left Motor task1:  PWM with FET driver 1
 *              Right Motor task2: PWM with FET driver 2
 *              Bump Task pending on bump switches on change notice input ints.
 *              Path task that sends speed and direction to the motor tasks
 *
 *
 * Note: baud rate is set in UART1.h
 **************************************************************************/
#include <includes.h>
//#include <plib.h>

#define FPB 72000000    // Frequency of the Peripheral Bus

/*
 *********************************************************************************************************
 *                                                Task Stacks/TCB
 *********************************************************************************************************
 */

#define TASK_STK_SIZE 220 // 256 //320

#define APP_CFG_TASK_ONE_STK_SIZE TASK_STK_SIZE
#define APP_CFG_TASK_TWO_STK_SIZE TASK_STK_SIZE
#define APP_CFG_TASK_BUMP_STK_SIZE TASK_STK_SIZE
#define APP_CFG_TASK_PATH_STK_SIZE TASK_STK_SIZE

#define  APP_CFG_TASK_ONE_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_ONE_STK_SIZE_LIMIT (APP_CFG_TASK_ONE_STK_SIZE * (100u - APP_CFG_TASK_ONE_STK_SIZE_PCT_FULL))   / 100u

#define  APP_CFG_TASK_TWO_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_TWO_STK_SIZE_LIMIT (APP_CFG_TASK_TWO_STK_SIZE * (100u - APP_CFG_TASK_TWO_STK_SIZE_PCT_FULL))   / 100u

#define  APP_CFG_TASK_BUMP_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_BUMP_STK_SIZE_LIMIT (APP_CFG_TASK_BUMP_STK_SIZE * (100u - APP_CFG_TASK_BUMP_STK_SIZE_PCT_FULL))   / 100u

#define  APP_CFG_TASK_PATH_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_PATH_STK_SIZE_LIMIT (APP_CFG_TASK_PATH_STK_SIZE * (100u - APP_CFG_TASK_PATH_STK_SIZE_PCT_FULL))   / 100u


static OS_TCB App_TaskStartTCB;
static CPU_STK App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static OS_TCB App_TaskOneTCB;
static CPU_STK App_TaskOneStk[APP_CFG_TASK_ONE_STK_SIZE];

static OS_TCB App_TaskTwoTCB;
static CPU_STK App_TaskTwoStk[APP_CFG_TASK_TWO_STK_SIZE];

static OS_TCB App_TaskBumpTCB;
static CPU_STK App_TaskBumpStk[APP_CFG_TASK_BUMP_STK_SIZE];

static OS_TCB App_TaskPathTCB;
static CPU_STK App_TaskPathStk[APP_CFG_TASK_PATH_STK_SIZE];

/*
 *********************************************************************************************************
 *                                            Task PROTOTYPES
 *********************************************************************************************************
 */

void App_TaskStart(void *p_arg);
void AppTaskCreate(void);

void App_TaskControl(void *data);
void App_TaskBump(void *pdata);
void App_TaskPath(void *pdata);


/*
 *********************************************************************************************************
 *                                            Task Priorities
 *********************************************************************************************************
 */

#define APP_CFG_TASK_ONE_PRIO 6
#define APP_CFG_TASK_TWO_PRIO 7
#define APP_CFG_TASK_BUMP_PRIO 5
#define APP_CFG_TASK_PATH_PRIO 4


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
//#define HEATER1         0 //_RD0    // Connector J7-1
#define LEFT_MOTOR      1 //_RD1    //           J7-2
#define RIGHT_MOTOR    2 //_RD2    //           J8-1


/*
 *********************************************************************************************************
 *                                                Structure for data passed to control tasks
 *********************************************************************************************************
 */
#define NO_CONTROL_TASKS 2

typedef struct {
    CPU_INT08U Speed;
    CPU_INT08U MotorControlNumber;
    CPU_INT08U Space1;
    CPU_INT08U Space2;
    CPU_INT08U Space3;
} CONTROLLER_DATA;

CONTROLLER_DATA SystemDataArray[NO_CONTROL_TASKS];

void initSys(void) {
    // Initialize parameters for motor controller 1
    SystemDataArray[0].Speed = 50u;
    SystemDataArray[0].MotorControlNumber = LEFT_MOTOR;
    SystemDataArray[0].Space1 = 0;
    SystemDataArray[0].Space2 = 0;
    SystemDataArray[0].Space3 = 0;

    // Initialize parameters for motor controller 2
    SystemDataArray[1].Speed = 25u;
    SystemDataArray[1].MotorControlNumber = RIGHT_MOTOR;
    SystemDataArray[1].Space1 = 0;
    SystemDataArray[1].Space2 = 0;
    SystemDataArray[1].Space3 = 0;
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


// ------------------------------------------------------------
// Device control:  Motor on/off for test - PWM in normal use
// ------------------------------------------------------------

//* Example from Programming 32-bit Microcontrollers in C by Lucio Di Jasio
/*
void initPWM(int samplerate)
{
    OpenOC1(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE,0,0);
    OpenTimer2(T2_ON | T2_PS_1_1, FPB/samplerate);
    PR2 = FPB/samplerate-1;
}
 */

/*********************************************************************************************************
 *                                        PB_Config_BS()
 *
 * Description: This function configures the port pins for the push button on the Basic Shield
 *********************************************************************************************************/
void PB_Config_BS(void) { /* Set the pin corresponding to Basic Shield push buttons as input    */
    TRISDbits.TRISD5 = 1; // BTN2 RD5, CN14
    TRISDbits.TRISD6 = 1; // BTN3 RD6, CN15
    TRISDbits.TRISD7 = 1; // BTN4 RD7, CN16
}

/*********************************************************************************************************
 *                                        PB_IntInit_BS()
 *
 * Description: This function performs the interrupt initialization for the push buttons.
 *
 *********************************************************************************************************/

void PB_IntInit_BS(void) {
    CPU_INT32U dummy_read;
    CPU_INT16U config;

    config = CHANGE_INT_ON
            | CHANGE_INT_PRI_3;

    CNCON = 0x8000; /* Enable the change notice module         */
    /* Enable change notice tied to Basic Shield push buttons     */
    EnableCN14(); // BTN2, RD5, CN14
    EnableCN15(); // BTN3, RD6, CN15
    EnableCN16(); // BTN4, RD7, CN16

    /* Enable a weak pull-up corresponding to the CN pin        */
    // Basic Shield push buttons have 10K pull down resistors so don't need pull up.
    //ConfigCNPullups(CN14_PULLUP_ENABLE | CN15_PULLUP_ENABLE | CN16_PULLUP_ENABLE);

    dummy_read = PORTD; /* Perform a dummy read to clear any mismatch conditions    */

    mCNClearIntFlag(); /* Clear the int flag just in case it was triggered         */

    ConfigIntCN(config); /* Enable CN interrupts at priority level 3                 */
}

/*********************************************************************************************************
 *                                        PB_Init_BS()
 *
 * Description: This function performs the initialization for the Basic Shield push buttons.
 *
 * Basic Shield BTN2 pin 34: RD5, CN14
 *              BTN3 pin 36: RD6, CN15
 *              BTN4 pin 37: RD7, CN16
 *********************************************************************************************************/
void PB_Init_BS(void) {
    PB_Config_BS(); /* Configure the port pins                                  */
    PB_IntInit_BS(); /* Configure interrupt settings                             */
}

void deviceOn(int i) // FET on
{
    mPORTDSetBits(1 << i);
}

void deviceOff(int i) // FET off 
{
    mPORTDClearBits(1 << i);
}

void initDevice(void) // Port bits connected to FETs set as outputs and turned off
{
    mPORTDOutputConfig((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3));
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
    } else {
        val = -1; // Error
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

    //OSSemCreate(&AdcSem, "ADC Semaphore", 1, &os_err); // Create and init to 1

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

    //initADC(AINPUTS); // Initialize the Analog to Digital Converter

    initSys(); // Initialize the temperature control system parameters passed to each control task

    initDevice(); // Initialize heater, fan control port

    PB_Init_BS(); // Initialize pushbuttons and CN interrupt

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
    putsU1("uC/OS-III ");
    putsU1("Version ");
    putsU1(uint2str(OSVersion(&err), 10));
    putsU1(" The Real-Time Kernel running on the PIC32 \n\r");
    putsU1(" Robot Control Application\r\n");

    OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_HMSM_STRICT, &err); /* Wait two seconds */
    if (err != OS_ERR_NONE) {
        putsU1("Error OSTimeDlyHMSM ");
    }
    Screen_Init();
    Screen_OffCursor();

    OSTaskCreate((OS_TCB *) & App_TaskOneTCB, /* Create control one task   */
            (CPU_CHAR *) "One",
            (OS_TASK_PTR) App_TaskControl,
            (void *) &SystemDataArray[0],
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
            (void *) &SystemDataArray[1],
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

    OSTaskCreate((OS_TCB *) & App_TaskBumpTCB, // Create control two task
            (CPU_CHAR *) "Bump",
            (OS_TASK_PTR) App_TaskBump,
            (void *) 0,
            (OS_PRIO) APP_CFG_TASK_BUMP_PRIO,
            (CPU_STK *) & App_TaskBumpStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_BUMP_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_BUMP_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    if (os_err != OS_ERR_NONE) {
        putsU1("Error starting task: Bump ");
    }

    OSTaskCreate((OS_TCB *) & App_TaskPathTCB, // Create control two task
            (CPU_CHAR *) "Path",
            (OS_TASK_PTR) App_TaskPath,
            (void *) 0,
            (OS_PRIO) APP_CFG_TASK_PATH_PRIO,
            (CPU_STK *) & App_TaskPathStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_PATH_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_PATH_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    if (os_err != OS_ERR_NONE) {
        putsU1("Error starting task: Path ");
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


/*********************************************************************************************************
 *                                     BSP_CNHandler_BS()
 *
 * Description: This function handles change notice interrupts.  It is in the ISR state and posts to
 *              the CNHandlerTask to process the change notice interrupt
 *
 * Notes: Each push of the user push button will actually generate 2 interrupts, as there will actually be
 *        two changes of state with the IO pin. Additionally, the switch will bounce.
 *********************************************************************************************************/
CPU_INT32U reg_val; // This communicates from the ISR to the task so must be global

void BSP_CNHandler_BS(void) // Set bsp_cnint: in bsp_a.S to call this int handler
{
    OS_ERR err;
    OS_TCB CNTaskHandlerTCB;

    reg_val = PORTD; /* Read register to clear change notice mismatch condition  */

    OSTaskSemPost(&App_TaskBumpTCB,
            OS_OPT_POST_NONE,
            &err);
    mCNClearIntFlag();
}


/*********************************************************************************************************
 *                                     App_taskBump()
 *
 * Description: The task that process the sensor input such as bump sensor
 * Task pends on the OSTaskSem from the change notice ISR.  Processes the CN int when activated by post.
 * reg_val is global variable holding the input causing the CN interrupt
 *********************************************************************************************************/

#define BTN4 (1<<7)
#define BTN3 (1<<6)
#define BTN2 (1<<5)

CPU_BOOLEAN Bump = 0;

void App_TaskBump(void *pdata) {

    OS_TICK timeout = 0; // 0 means wait forever, no timeout
    CPU_TS ts; // Time stamp
    OS_ERR err; // returned error code

    while (DEF_ON) {

        OSTaskSemPend(timeout,
                OS_OPT_PEND_BLOCKING,
                &ts,
                &err);

        // check for BTN2, BTN3, or BTN4 causing interrupt
        if (reg_val & BTN4) LED_Toggle(4);
        if (reg_val & BTN3) LED_Toggle(3);
        if (reg_val & BTN2) LED_Toggle(2);
        Bump = 1; // Tell Path Task that robot hit something
        OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_HMSM_STRICT, &err); // Delay while try to fix
        Bump = 0;

    }
}

void App_TaskPath(void *pdata) {
    OS_ERR err; // returned error code
    CPU_INT08U Lspeed = 0;
    CPU_INT08U Rspeed = 100;

    while (DEF_ON) {
        while (!Bump) {
            SystemDataArray[0].Speed = Lspeed;
            OSTaskSemPost(&App_TaskOneTCB,
                    OS_OPT_POST_NONE,
                    &err);

            OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);

            SystemDataArray[1].Speed = Rspeed;
            OSTaskSemPost(&App_TaskTwoTCB,
                    OS_OPT_POST_NONE,
                    &err);

            OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);


            Lspeed += 10;
            if (Lspeed > 100) Lspeed = 0;
            Rspeed -=10;
            if (Rspeed == 0) Rspeed = 100;
        }
        SystemDataArray[0].Speed = 0;
        SystemDataArray[1].Speed = 0;
    }
}

void App_TaskControl(void *pdata) {
    CONTROLLER_DATA *SystemPtr;
    SystemPtr = (CONTROLLER_DATA *) pdata;
    int percent;
    OS_ERR err;
    unsigned int motor, speed;

    motor = SystemPtr->MotorControlNumber;
    percent = SystemPtr->Speed;


    // PWM mode
    OC1CON = 0x8000 | 0x06; // ON, Timer 2 source, PWM fault disabled
    OC2CON = 0x8000 | 0x06; // ON, Timer 2 source, PWM fault disabled


    T2CON = 0x8000 | 0x50; //ON, 1:32 prescale @72 MHz FPB = 2.25 MHz, T=444.444ns
    PR2 = 2250; // Set PWM period: 225*444.444ns = 100 us, T = 10 KHz
    // PR2 = 2250 is 1000 Hz, T = 1 ms
    // PR2 = 22,500 is 100 Hz, T = 10 ms




    OS_TICK timeout = 0; // 0 means wait forever, no timeout
    CPU_TS ts; // Time stamp

    while (DEF_ON) {
        // Pend on path task to set new motor control data
        OSTaskSemPend(timeout,
                OS_OPT_PEND_BLOCKING,
                &ts,
                &err);

        // New control information received
        percent = SystemPtr->Speed;
        if (motor == LEFT_MOTOR) {
            OC1RS = (PR2 * percent) / 100; // set PWM on time out of PR2 period
        } else if (motor == RIGHT_MOTOR) {
            OC2RS = (PR2 * percent) / 100; // set PWM on time out of PR2 period
        }
    }
}
