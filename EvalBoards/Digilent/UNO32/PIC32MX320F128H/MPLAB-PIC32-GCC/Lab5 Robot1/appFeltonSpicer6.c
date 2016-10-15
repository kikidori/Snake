/**************************************************************************
* Lab_5:        ROBOTv2_HBRIDGE
* Date:		November 18, 2013
* Status:       Some bugs remaining but generally functions.
* Processor:	PIC32MX320F128H
* Toolchain:	MPLAB-X
* Board:	UNO32 from Digilent
* Programmer:	Laton Felton and Cody Spicer
* Organization:	CENG 448/548, SDSMT
* RTOS:		uCOS-III from Micrium
*
*
*
* Note: baud rate is set in UART1.h
**************************************************************************/
#include <includes.h>
#include <stdio.h>
#include <stdlib.h>

//#include<plib.h>

/*
*********************************************************************************************************
*                                                Task Stacks/TCB
*********************************************************************************************************
*/

#define TASK_STK_SIZE 	320

#define APP_CFG_TASK_LEFT_MOTOR_STK_SIZE 	TASK_STK_SIZE
#define APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE 	TASK_STK_SIZE
#define APP_CFG_TASK_BUMP_STK_SIZE              TASK_STK_SIZE

#define  APP_CFG_TASK_LEFT_MOTOR_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_LEFT_MOTOR_STK_SIZE_LIMIT 	(APP_CFG_TASK_LEFT_MOTOR_STK_SIZE * (100u - APP_CFG_TASK_LEFT_MOTOR_STK_SIZE_PCT_FULL))   / 100u

#define  APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE_LIMIT 	(APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE * (100u - APP_CFG_TASK_LEFT_MOTOR_STK_SIZE_PCT_FULL))   / 100u

#define  APP_CFG_TASK_BUMP_STK_SIZE_PCT_FULL                    90u
#define  APP_CFG_TASK_BUMP_STK_SIZE_LIMIT               (APP_CFG_TASK_BUMP_STK_SIZE * (100u - APP_CFG_TASK_BUMP_STK_SIZE_PCT_FULL))   / 100u

static  OS_TCB    App_TaskStartTCB;
static  CPU_STK   App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB    App_Task_left_motorTCB;
static  CPU_STK   App_Task_left_motorStk[APP_CFG_TASK_LEFT_MOTOR_STK_SIZE];

static  OS_TCB    App_Task_right_motorTCB;
static  CPU_STK   App_Task_right_motorStk[APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE];

static OS_TCB     App_Task_BumpTCB;
static CPU_STK    App_Task_BumpStk[APP_CFG_TASK_BUMP_STK_SIZE];

        OS_SEM Bump_sem_left;
        OS_SEM Bump_sem_right;



//#define BTN4 (1<<7)
//#define BTN3 (1<<6)
//#define BTN2 (1<<5)



/*
*********************************************************************************************************
*                                            Task PROTOTYPES
*********************************************************************************************************
*/

static  void        App_TaskStart(void *p_arg);
static  void        AppTaskCreate(void);
//static  void        App_TaskControl(void *data);

static void         App_left_motor (void *data);
static void         App_right_motor (void *data);
static void         App_interrupt (void *data);
static void         App_Bump (void *data);

/*
*********************************************************************************************************
*                                            Task Priorities
*********************************************************************************************************
*/

#define APP_CFG_TASK_left_motor_PRIO 4
#define APP_CFG_TASK_right_motor_PRIO 3
#define APP_CFG_TASK_Bump_PRIO 5

// *********************************************************************
// GPIO defines     Switches on Digilent Basic Shield for UNO32
// *********************************************************************
//#define BTN1	_RF1    // Port F bit 1 switch
#define BTN2    _RD5    // Port D bit 5 switch
#define BTN3	_RD6    // Port D bit 6 switch
#define BTN4	_RD7    // Port D bit 7 switch
// ------------------------------------------------------------
// ADC Defines
// ------------------------------------------------------------
//#define POT     2      // 10k potentiometer on AN0 input
#define A1 4
#define A0 2
//#define AINPUT_A0 = 0xfffb
//#define AINPUT_A1 = 0xffef
#define CH (A0)
#define AINPUTS 0xfffb  // Analog inputs for POT pin A0 (AN2)
#define SAMC 2	// Auto-sample time bits 1-31 Tad
#define ADCS 2	// ADC Conversion Clock select bits Tad = 2*(ADCS+1)*Tpb
//	Ex:  ADCS = 2, SAMC = 2,Tpb = 25 ns (Fpb = 40 MHz)
//	Tad = Tpb*2*(2+1) = 25*6 = 150 ns
//	Auto-sample time = 2*Tad = 300 ns
//	12 Tad required for conversion = 150 * 12 = 1.8 us
//	total ADC time = 12*150 + 300 = 2.1 us
#define AD1CON3_BITS ((SAMC<<8)|ADCS)
CPU_INT32U reg_val;



// *********************************************************************
// Screen defines and function prototypes
// *********************************************************************

void Screen_Init(void);
void Screen_Clear (void);
void initADC(int amask);
int readADC(int ch);
void Device_On(int i);
void Device_Off(int i);
void Device_Init(void);
int lookup(int ch);
void Screen_MoveCursor (int Xpos, int Ypos);
int Screen_WriteChar(int x, int y, char c);
int Screen_WriteNumber(int x, int y, int number);
void UART_PrintNum( int i);
void PB_Config_BS(void);
void PB_IntInit_BS (void);
void  PB_Init_BS(void);
void BSP_CNHandler_BS(void);

void left_forward(void);
void left_backward(void);
void right_forward(void);
void right_backward(void);

void init_sensors(void);
int read_sensors(void);



// ********************************************************************* */
// Global Variables
// *********************************************************************

#define FPB 72000000


int left_bumper = 0;
int right_bumper = 0;

int left_room = 0;
int right_room = 0;

int percent1 = 80;
int percent2 = 80;
int check = 0;

//int HTR_1 = 1;
//int FAN_1 = 0;
//int TEMP_1 = A1;

//int HTR_2 = 3;
//int FAN_2 = 2;
//int TEMP_2 = A0;



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

int  main (void)
{



    mPORTDOutputConfig(( IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3));

    OS_ERR   os_err;
    CPU_Init();                                                           /* Initialize the uC/CPU services                           */

    BSP_IntDisAll();

    //OSSemCreate(&Bump_sem_left,"Control lSem",1,&os_err);
    //OSSemCreate(&Bump_sem_right,"Control rSem",1,&os_err);

    //OC1CON=0x8000 | 0x06;
    //OC2CON=0x8000 | 0x06;

    //T2CON = 0x8000 | 0x50;

    //PR2 = 2250;

    PB_Init_BS();
    //Device_Init();

    OSInit(&os_err);


   initADC(0);

    //init_sensors();

    OSTaskCreate((OS_TCB      *)&App_TaskStartTCB,                        /* Create the start task                                    */
                 (CPU_CHAR    *)"Start",
                 (OS_TASK_PTR  )App_TaskStart,
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_START_PRIO,
                 (CPU_STK     *)&App_TaskStartStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

    OSStart(&os_err);                                                     /* Start multitasking (i.e. give control to uC/OS-III).     */

    (void)&os_err;

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

static  void  App_TaskStart (void *p_arg)
{
#if CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL // maybe not needed for uCOS-III
    CPU_SR  cpu_sr;
#endif
    CPU_INT08U  i;
    CPU_INT08U  j;

    (void)p_arg;
    OS_ERR  err;

    BSP_InitIO();            /* Initialize BSP functions                                 */

#if OS_CFG_STAT_TASK_EN > 0  // Set in os_cfg.h
    OSStatTaskCPUUsageInit(&err);
    if (err != OS_ERR_NONE){
      putsU1("Error starting OSStatTaskCPUUsageInit ");
    }
#endif

    initU1();           // Initialize UART1

    AppTaskCreate();         /* Create application tasks
                                                            */

    while (DEF_TRUE) {        /* Task body, always written as an infinite loop.            */

//#if OS_CFG_STAT_TASK_EN > 0 // Set in os_cfg.h
        //OSSchedLock(&err);  // Don't let another task run as it might change cursor position
	//Screen_MoveCursor(40,2);	// before  writting to the screen
        //UART_PrintNum(OSStatTaskCPUUsage);
 	//Screen_MoveCursor(40,3);	// before  writting to the screen
        //UART_PrintNum(OSTaskQty);
        //OSSchedUnlock(&err);		// Ok for other tasks to run
//#endif

        for (j = 0; j < 2; j++) {
            for (i = 1; i < 9; i++) {
                LED_Toggle(i);
                OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);
            }

            for (i = 0; i < 8; i++) {
                LED_Toggle(0);
                 OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);
            }
        }

        for ( ; j > 0; j--) {
            for (i = 9; i > 0; --i) {
                LED_Toggle(i);
                OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);
            }

            for (i = 0; i < 8; i++) {
                LED_Toggle(0);
                OSTimeDlyHMSM(0, 0, 0, 500,OS_OPT_TIME_HMSM_STRICT,&err);
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

static  void  AppTaskCreate (void)
{

        OS_ERR  os_err, err;
        unsigned char i;
        char key;
/*
        Screen_Init();
        OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);

        //Screen_MoveCursor(8,8);
        putsU1("uC/OS-III, The Real-Time Kernel PIC32 \n"
                          " ROBOT\n");

        OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);// Wait two seconds
        if (err != OS_ERR_NONE){
          putsU1("Error OSTimeDlyHMSM ");
         }
*/

     OSTaskCreate((OS_TCB      *)&App_Task_left_motorTCB,                        /* Create the Left task                                    */
                 (CPU_CHAR    *)"Left",
                 (OS_TASK_PTR  )App_left_motor,
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_left_motor_PRIO,
                 (CPU_STK     *)&App_Task_left_motorStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_LEFT_MOTOR_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_LEFT_MOTOR_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

      if (os_err != OS_ERR_NONE){
          putsU1("Error starting left task: ");
      }

      OSTaskCreate((OS_TCB      *)&App_Task_right_motorTCB,                        /* Create the Right task                                    */
                 (CPU_CHAR    *)"Right",
                 (OS_TASK_PTR  )App_right_motor,
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_right_motor_PRIO,
                 (CPU_STK     *)&App_Task_right_motorStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_RIGHT_MOTOR_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

       if (os_err != OS_ERR_NONE){
          putsU1("Error starting Right task: ");
      }

      OSTaskCreate((OS_TCB      *)&App_Task_BumpTCB,
                 (CPU_CHAR    *)"BUMP",
                 (OS_TASK_PTR  )App_Bump,
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_Bump_PRIO,
                 (CPU_STK     *)&App_Task_BumpStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_BUMP_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_BUMP_STK_SIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

       if (os_err != OS_ERR_NONE){
          putsU1("Error starting Bump task: ");
      }

}


/*$PAGE*/


/* ********************************************************************* */
/* Local functions */
// *********************************************************************
void Screen_Clear (void)
{
    putU1(0x1B);
    putU1('c');
}

void Screen_Init(void)
{
	int i;
	Screen_Clear();
}

// ------------------------------------------------------------
// Initialize ADC
// ------------------------------------------------------------
// initialize the ADC for single conversion, select input pins

void initADC( int amask)
{
    AD1PCFG = amask;    // select analog input pins:
    AD1CON1 = 0x00E0;   // auto convert after end of sampling
    AD1CSSL = 0;        // no scanning required
    AD1CON2 = 0;        // use MUXA, AVss/AVdd used as Vref+/-
    AD1CON3 = AD1CON3_BITS;
    AD1CON1SET = 0x8000;// turn on the ADC
    AD1CHSbits.CH0SA = CH;      // select analog input channel
} //initADC

int readADC( int ch)
{/*
    AD1CHSbits.CH0SA = ch;      // select analog input channel
    AD1CON1bits.SAMP = 1;       // start sampling
    while (!AD1CON1bits.DONE);  // wait to complete conversion
    return ADC1BUF0;            // read the conversion result
    */
} // readADC

void Device_On(int i)	// FET on turns on heater or fan
{
  mPORTDSetBits(1<<i);
}

void Device_Off(int i) // FET off turns off heater or fan
{
  mPORTDClearBits(1<<i);
}

void Device_Init(void) // Port bits connected to FETs set as outputs and turned off
{
mPORTDOutputConfig((IOPORT_BIT_0 | IOPORT_BIT_1 |   IOPORT_BIT_2 | IOPORT_BIT_3));
mPORTDClearBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3));
}

void UART_PrintNum( int i)
{
    putU1(i/10u + '0');
    putU1(i%10u + '0');
}

void Screen_MoveCursor (int Xpos, int Ypos)
{
    putU1(0x1B);
    putU1('[');
    UART_PrintNum(Ypos);
    putU1(';');
    UART_PrintNum(Xpos);
    putU1('H');
}

int Screen_WriteChar(int x, int y, char c)
{
    OS_ERR err;
	//if ((x>SCREEN_X_END) || (x<SCREEN_X_START) ||
	//	(y>SCREEN_Y_END) || (y<SCREEN_Y_START)) {
	//	return 1;			// Error
	//}
	OSSchedLock(&err);  // Don't let another task run as it might change cursor position
	Screen_MoveCursor(x,y);	// before the character is written to the screen
	putU1(c);
	OSSchedUnlock(&err);		// Ok for other tasks to run
}

int Screen_WriteNumber(int x, int y, int number)
{
    OS_ERR err;
	//if ((x>SCREEN_X_END) || (x<SCREEN_X_START) ||
		//(y>SCREEN_Y_END) || (y<SCREEN_Y_START)) {
		//return 1;			// Error
	//}
	OSSchedLock(&err);  // Don't let another task run as it might change cursor position
	Screen_MoveCursor(x,y);	// before writing the value to the screen
	UART_PrintNum(number);
	OSSchedUnlock(&err);		// Ok for other tasks to run
}



void PB_Config_BS(void)
{
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
}

void PB_IntInit_BS (void)
{
    CPU_INT32U  dummy_read;
    CPU_INT16U  config;

    config = CHANGE_INT_ON
           | CHANGE_INT_PRI_3;

    CNCON = 0x8000;

    EnableCN14();     // BTN2, RD5, CN14
    EnableCN15();     // BTN3, RD6, CN15
    EnableCN16();     // BTN4, RD7, CN16


    dummy_read = PORTD;

    mCNClearIntFlag();

    ConfigIntCN(config);
}

void  PB_Init_BS(void)
{
    PB_Config_BS();
    PB_IntInit_BS();
}


void BSP_CNHandler_BS(void)
{
    OS_ERR err;


    reg_val = PORTD;   /* Read register to clear change notice mismatch condition  */

    OSTaskSemPost(&App_Task_BumpTCB,OS_OPT_POST_NONE,&err);
    mCNClearIntFlag();

}


void App_left_motor (void *data)
{

   OS_ERR err;
   CPU_TS ts;

   left_forward();

   while(1)
   {
      /* if(left_bumper == 1 && right_bumper == 0)
       {
           left_backward();
           right_backward();
           OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
           left_forward();
           OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
           right_forward();
           left_bumper = 0;
       }

       if(left_bumper == 0 && right_bumper == 0)
       {
           left_forward();
       }*/
       //while(left_bumper == 0 && right_bumper == 0)
       //{
           //OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);
       //}
       OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);

   }
}

void App_right_motor (void *data)
{

    OS_ERR err;

    int decide = 0;

    right_forward();

   while(1)
   {

       decide = read_sensors();

     /*  if(right_bumper == 1 && left_bumper == 0)
       {
           left_backward();
           right_backward();
           OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
           right_forward();
           OSTimeDlyHMSM(0, 0, 1, 0,OS_OPT_TIME_HMSM_STRICT,&err);
           left_forward();
           right_bumper = 0;
       }
*/
       if(left_bumper == 0 && right_bumper == 0)
       {
           right_forward();
       }
       //while(left_bumper == 0 && right_bumper == 0)
       //{
           //OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);
       //}
       if(decide == 0)
       {
           right_forward();
           left_forward();
           OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);
       }
       if(decide == 2)
       {
           right_forward();
           left_backward();
           OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);
       }

       if(decide == 1)
       {
           left_forward();
           right_backward();
           OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);
       }

       OSTimeDlyHMSM(0, 0, 0, 50,OS_OPT_TIME_HMSM_STRICT,&err);
   }

}



void App_Bump(void *pdata)
{
     OS_ERR err;
  CPU_TS ts;
  OS_TICK timeout=0;

  OSTimeDlyHMSM(0, 0, 0,20, OS_OPT_TIME_HMSM_STRICT, &err); // Wait -- give another task a chance to run


  while (1)
    {

      //order=Check_Sensor();
     // LED_Toggle(9);
      OSTimeDlyHMSM(0, 0, 0,50, OS_OPT_TIME_HMSM_STRICT, &err); // Wait -- give another task a chance to run

      OSTaskSemPend(timeout,OS_OPT_PEND_BLOCKING,&ts,&err);
     if (reg_val & BTN3) left_bumper = 1;
     if (reg_val & BTN2) right_bumper = 1;
      OSTimeDlyHMSM(0, 0, 0,50, OS_OPT_TIME_HMSM_STRICT, &err); // Wait -- give another task a chance to run

    }
}

void left_forward(void)
{
    mPORTDSetBits(IOPORT_BIT_0);  // pin 3 left forward
    mPORTDClearBits(IOPORT_BIT_1);// pin 5
}
void left_backward(void)
{
    mPORTDClearBits(IOPORT_BIT_0);       // left backswards
    mPORTDSetBits(IOPORT_BIT_1);
}
void right_forward(void)
{
    mPORTDSetBits(IOPORT_BIT_2);       //  pin 6 right forward
    mPORTDClearBits(IOPORT_BIT_3);     //  pin 9
}
void right_backward(void)
{
    mPORTDClearBits(IOPORT_BIT_2);       // right backwards
    mPORTDSetBits(IOPORT_BIT_3);
}

void init_sensors(void)
{
    OS_ERR err;
 int i;
 for(i=0;i<5;i++)
    {
     right_room += readADC(A0);
     left_room += readADC(A1);

       OSTimeDlyHMSM(0, 0, 0,40, OS_OPT_TIME_HMSM_STRICT, &err); // Wait -- give another task a chance to run
    }

 right_room = right_room/5;
 left_room = left_room/5;

}

int read_sensors(void)
{
    int left = 0;
    int right = 0;
    int decide = 0;
    int check = 0;
    int check1 = 0;

    right = (readADC(A0) - right_room)+1000;
    left = (readADC(A1) - left_room)+1000;

    check = right - left;
    check1 = left - right;


    if ( check > 250) // turn  left
    {
        decide = 1;
    }

    if ( check1 > 250)
    {
        decide = 2; // turn right
    }

    return decide;

}






