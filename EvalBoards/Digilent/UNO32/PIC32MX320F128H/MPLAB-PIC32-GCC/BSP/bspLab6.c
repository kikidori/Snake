/*
*********************************************************************************************************
*                                         Board Support Package
*
*                              (c) Copyright 2010, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                               Microchip
*                                      PIC32 Ethernet Starter Kit
*********************************************************************************************************
*/
// mjb changed mPORTA... to mPORTE for the uno32
#include "includes.h"
#include "osc.h"
#include "system.h"
#include "timer.h"

/*
 *********************************************************************************************************
 *                                          CONFIGURATION DIRECTIVES
 * Changed from 72 MHz and 72 MHz to 80 and 10
 *  SYSCLK = 80MHz
 *  FPB = 10 MHz
 *********************************************************************************************************
 */

#pragma  config  FPLLODIV = DIV_1                                         /* PLL output postscaler - divide by 1                      */
#pragma  config  FPLLMUL  = MUL_20                                        /* PLL Multiplier - 20x multiplier                          */
#pragma  config  FPLLIDIV = DIV_2                                         /* PLL input divider - divide by 2                          */
#pragma  config  FWDTEN   = OFF                                           /* Disable watchdog timer                                   */
#pragma  config  FPBDIV   = DIV_8                                         /* Peripheral Bus Clock divider - divide by 1               */
#pragma  config  POSCMOD  = XT                                            /* Oscillator mode - XT                                     */
#pragma  config  FNOSC    = PRIPLL                                        /* Use primary oscillator with PLL                          */
#pragma  config  CP       = OFF



/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_TMR_RELOAD          (BSP_CLK_FREQ / (2 * OS_CFG_TICK_RATE_HZ))
#define  BSP_DLY_CONST            BSP_CLK_FREQ / 1000000 

#define  PB3_MASK                 _PORTD_RD13_MASK
#define  PB2_MASK                 _PORTD_RD7_MASK
#define  PB1_MASK                 _PORTD_RD6_MASK
#define  PB3_TRIS                 TRISDbits.TRISD13
#define  PB2_TRIS                 TRISDbits.TRISD7
#define  PB1_TRIS                 TRISDbits.TRISD6
#define  PB3_IO                   LATDbits.LATD13
#define  PB2_IO                   LATDbits.LATD7
#define  PB1_IO                   LATDbits.LATD6
#define  PB3                      PORTDbits.RD13
#define  PB2                      PORTDbits.RD7
#define  PB1                      PORTDbits.RD6

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL FUNCTIONS
*********************************************************************************************************
*/

static  void  LED_Init      (void);

static  void  Tmr_Init      (void);

static  void  PB_IntInit    (void);
static  void  PB_Config     (void);
static  void  PB_Init       (void);

/*
*********************************************************************************************************
*                                                 LED ON
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to be ON
*                      1    turns ON LED D0 on the board
*                      .
*                      .
*                      8    turns on LED D9 on the board
*********************************************************************************************************
*/

void  LED_On (CPU_INT08U led)
{
    switch (led) {
        case 0:
             mPORTESetBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                            IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
             break;
        case 1:
             mPORTESetBits(IOPORT_BIT_0);
             break;
        case 2:
             mPORTESetBits(IOPORT_BIT_1);
             break;
        case 3:
             mPORTESetBits(IOPORT_BIT_2);
             break;
        case 4:
             mPORTESetBits(IOPORT_BIT_3);
             break;
        case 5:
             mPORTESetBits(IOPORT_BIT_4);
             break;
        case 6:
             mPORTESetBits(IOPORT_BIT_5);
             break;
        case 7:
             mPORTESetBits(IOPORT_BIT_6);
             break;
        case 8:
             mPORTESetBits(IOPORT_BIT_7);
             break;
        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                                LED OFF
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to turn OFF
*                      0    indicates that you want ALL the LEDs to be OFF
*                      1    turns OFF LED D0 on the board
*                      .
*                      .
*                      8    turns OFF LED D8 on the board
*********************************************************************************************************
*/

void  LED_Off (CPU_INT08U led)
{
    switch (led) {
        case 0:
             mPORTEClearBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                              IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
             break;
        case 1:
             mPORTEClearBits(IOPORT_BIT_0);
             break;
        case 2:
             mPORTEClearBits(IOPORT_BIT_1);
             break;
        case 3:
             mPORTEClearBits(IOPORT_BIT_2);
             break;
        case 4:
             mPORTEClearBits(IOPORT_BIT_3);
             break;
        case 5:
             mPORTEClearBits(IOPORT_BIT_4);
             break;
        case 6:
             mPORTEClearBits(IOPORT_BIT_5);
             break;
        case 7:
             mPORTEClearBits(IOPORT_BIT_6);
             break;
        case 8:
             mPORTEClearBits(IOPORT_BIT_7);
             break;
        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                              LED TOGGLE
*
* Description : This function is used to alternate the state of an LED
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to toggle
*                      1    toggle LED D0 on the board
*                      .
*                      .
*                      8    toggle LED D8 on the board
*********************************************************************************************************
*/

void  LED_Toggle (CPU_INT08U led)
{
    switch (led) {
        case 0:
             mPORTEToggleBits((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                               IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));
             break;
        case 1:
             mPORTEToggleBits(IOPORT_BIT_0);
             break;
        case 2:
             mPORTEToggleBits(IOPORT_BIT_1);
             break;
        case 3:
             mPORTEToggleBits(IOPORT_BIT_2);
             break;
        case 4:
             mPORTEToggleBits(IOPORT_BIT_3);
             break;
        case 5:
             mPORTEToggleBits(IOPORT_BIT_4);
             break;
        case 6:
             mPORTEToggleBits(IOPORT_BIT_5);
             break;
        case 7:
             mPORTEToggleBits(IOPORT_BIT_6);
             break;
        case 8:
             mPORTEToggleBits(IOPORT_BIT_7);
             break;
        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                       LED_Init()
*
* Description: This function initializes all of the board's leds
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

static  void  LED_Init (void)
{
    LED_Off(0);                                                               /* Turn off all of the LEDs                   */
}

/*
*********************************************************************************************************
*                                          INITIALIZE I/Os
*
* Description : This function initializes the GPIO pins.  All the I/O pins are initialized in this function
*               so you don't have to look at multiple places for I/O initialization.
*
* Arguments   : None
*
*********************************************************************************************************
*/

static  void  BSP_IO_Init (void)
{
                                                                              /* Each LED pin is made an output             */
    mPORTEOutputConfig((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
                             IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));

    // mjb mPORTBOutputConfig(IOPORT_BIT_15);                                          /* The pins for the LCD are made outputs      */

    // mjb mPORTDOutputConfig((IOPORT_BIT_4 | IOPORT_BIT_5));

    // mjb mPORTEOutputConfig((IOPORT_BIT_0 | IOPORT_BIT_1 | IOPORT_BIT_2 | IOPORT_BIT_3 |
    // mjb                          IOPORT_BIT_4 | IOPORT_BIT_5 | IOPORT_BIT_6 | IOPORT_BIT_7));

    // mjb mPORTDInputConfig(IOPORT_BIT_6);                                            /* The pin for button S3 is made an input     */
}

/*
*********************************************************************************************************
*                                       Tmr_Init()
*
* Description: This function should intialize the timers used by your application
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  Tmr_Init (void)
{
    OpenCoreTimer(BSP_TMR_RELOAD);                                            /* Initialize the Count and Compare registers */                                               
    mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_3));                        /* Enable the core timer's interrupt          */      
}

/*
*********************************************************************************************************
*                                  BSP_TickISR_Handler()
*
* Description : 
*
* Arguments   : None
*********************************************************************************************************
*/

void  BSP_TickISR_Handler (void)
{
    UpdateCoreTimer(BSP_TMR_RELOAD);                                          /* Prepare for the next core timer interrupt  */
    mCTClearIntFlag();                                                        /* Clear the core timer interrupt             */
}

/*
*********************************************************************************************************
*                                    BSP_Except_Handler()
*
* Description: This function offers a means of servicing exceptions that are not triggered by interrupts
*              or the syscall instruction.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_Except_Handler (void)
{
}

/*
*********************************************************************************************************
*                                    BSP_DefaultHandler()
*
* Description: If an interrupt occurs, and no application-specific code has been written for that 
*              interrupt, this function will be invoked.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_DefaultHandler (void)
{
}

/*
*********************************************************************************************************
*                                    OSProbe_TmrInit()
*
* Description: Initialize the timer used by uC/Probe.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  OSProbe_TmrInit (void)
{
    OpenTimer1(T1_ON | T1_PS_1_1 | T1_SOURCE_INT, 0);
}

/*
*********************************************************************************************************
*                                    OSProbe_TmrRd()
*
* Description: Read the value of the 32-bit timer used by uC/Probe
*
* Arguments  : None
*
* Returns    : The current 32-bit value of the timer
*********************************************************************************************************
*/

CPU_INT32U  OSProbe_TmrRd (void)
{
    return  (ReadTimer1());
}  

/*
*********************************************************************************************************
*                                                BSP_Dly()
* 
* Description: Perform a short delay (~1uS) by performing multiple NOP.
*
* Arguments  : us           The number of uS to delay (approximate).
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_Dly (CPU_INT32U  us)
{
    CPU_INT32U  dly;
    
    
    dly = us * BSP_DLY_CONST;
    
    while (dly--) {
        asm("NOP");
    }    
}    
    
/*
*********************************************************************************************************
*                                             BSP_IntDisAll()
* 
* Description: Disable all interrupts at the interrupt controller.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    INTDisableInterrupts();
}

/*
*********************************************************************************************************
*                                      BSP_InitIntCtrl()
*
* Description: This function intializes the external interrupt controller.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

static  void  BSP_InitIntCtrl (void) 
{
    INTCONSET = 0x1000; 
    INTEnableSystemMultiVectoredInt();
}

/*
*********************************************************************************************************
*                                             BSP_InitIO()
* 
* Description: Initialize all the I/O devices.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_InitIO (void)    
{
                                                                        /* Enable optimal performance                       */
    SYSTEMConfigPerformance(BSP_CLK_FREQ);
    mOSCSetPBDIV(0);                                                    /* Use 1:1 CPU Core:Peripheral clocks               */

#if JTAG_ENABLE 
    DDPCONbits.JTAGEN = 1;                                              /* Maintain the port pins for JTAG use              */
#else
    DDPCONbits.JTAGEN = 0;                                              /* Free the JTAG port pins for use as GPIO          */
#endif

    BSP_InitIntCtrl();                                                  /* Initialize the interrupt controller              */
    BSP_IO_Init();                                                      /* Initialize the board's I/Os                      */
    Tmr_Init();                                                         /* Initialize the timers                            */
    LED_Init();                                                         /* Initialize LEDs                                  */
}
