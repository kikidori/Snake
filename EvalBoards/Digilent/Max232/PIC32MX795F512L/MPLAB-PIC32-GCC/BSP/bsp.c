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

// MJB updating for the Max32 and Basic Shield  9/27/14
//   CORRECTION bsp.h has void        BSP_InitIO          (void); change bsp.c to match
#include "includes.h"
#include "osc.h"
#include "system.h"
#include "timer.h"

/*
*********************************************************************************************************
*                                          CONFIGURATION DIRECTIVES
*********************************************************************************************************
*/
// NEED TO UPDATE FOR Fsys = 80 Mhz and Fpb = 80 MHz as set by the optimization macros
#pragma  config  FPLLODIV = DIV_1                                         /* PLL output postscaler - divide by 1                      */
#pragma  config  FPLLMUL  = MUL_20                                       /* PLL Multiplier - 20x multiplier                          */
#pragma  config  FPLLIDIV = DIV_2                                         /* PLL input divider - divide by 2                          */
#pragma  config  FWDTEN   = OFF                                           /* Disable watchdog timer                                   */
#pragma  config  FPBDIV   = DIV_1                                         /* Peripheral Bus Clock divider - divide by 1               */
#pragma  config  POSCMOD  = XT                                            /* Oscillator mode - XT                                     */
#pragma  config  FNOSC    = PRIPLL                                        /* Use primary oscillator with PLL                          */
#pragma  config  CP       = OFF

#pragma config FSOSCEN = OFF  // mjb Disable secondary osc so can use port C bit 14


/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_TMR_RELOAD          (BSP_CLK_FREQ / (2 * OS_CFG_TICK_RATE_HZ))
#define  BSP_DLY_CONST            BSP_CLK_FREQ / 1000000 


/*
 *
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

            LED1_ON; LED2_ON; LED3_ON; LED4_ON; LED5_ON; LED6_ON; LED7_ON; LED8_ON;

             break;
        case 1:
             LED1_ON; 
             break;
        case 2:
             LED2_ON; 
             break;
        case 3:
             LED3_ON; 
             break;
        case 4:
             LED4_ON; 
             break;
        case 5:
             LED5_ON; 
             break;
        case 6:
             LED6_ON; 
             break;
        case 7:
             LED7_ON; 
             break;
        case 8:
             LED8_ON; 
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
             LED1_OFF; LED2_OFF; LED3_OFF; LED4_OFF; LED5_OFF; LED6_OFF; LED7_OFF; LED8_OFF;
             break;
        case 1:
             LED1_OFF; 
             break;
        case 2:
             LED2_OFF; 
             break;
        case 3:
             LED3_OFF; 
             break;
        case 4:
             LED4_OFF; 
             break;
        case 5:
             LED5_OFF; 
             break;
        case 6:
             LED6_OFF; 
             break;
        case 7:
             LED7_OFF; 
             break;
        case 8:
             LED8_OFF; 
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
            LED1_TOGGLE; LED2_TOGGLE; LED3_TOGGLE; LED4_TOGGLE; LED5_TOGGLE; LED6_TOGGLE; LED7_TOGGLE; LED8_TOGGLE;
             break;
        case 1:
             LED1_TOGGLE;
             break;
        case 2:
             LED2_TOGGLE; 
             break;
        case 3:
             LED3_TOGGLE; 
             break;
        case 4:
             LED4_TOGGLE; 
             break;
        case 5:
             LED5_TOGGLE; 
             break;
        case 6:
             LED6_TOGGLE; 
             break;
        case 7:
             LED7_TOGGLE; 
             break;
        case 8:
             LED8_TOGGLE;
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
    OSCCONSET = 0; // Make sure that the secondary osc is off so can use RC13,RC14 as I/O bit
                                                                                        /* Each LED pin is made an output             */
    LED1_CONFIG; LED2_CONFIG; LED3_CONFIG; LED4_CONFIG; LED5_CONFIG; LED6_CONFIG; LED7_CONFIG; LED8_CONFIG;
    BTN1_CONFIG; BTN2_CONFIG; BTN3_CONFIG; BTN4_CONFIG;
    SW1_CONFIG; SW2_CONFIG; SW3_CONFIG; SW4_CONFIG;
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
