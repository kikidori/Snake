/*
*********************************************************************************************************
*                                          Board Support Package
*
*                             (c) Copyright 2010, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                               Microchip
*                                      PIC32 Ethernet Starter Kit
*********************************************************************************************************
*/
// Modified for the Max32 board and the Basic Shield.  MJB 9/27/2014
/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_CLK_FREQ               80000000 //72000000
#define  JTAG_ENABLE                DEF_DISABLED // mjb DEF_ENABLED


// Max32 with Basic Shield defines mjb
#define LED8_ON (mPORTDSetBits(IOPORT_BIT_7))
#define LED8_OFF (mPORTDClearBits(IOPORT_BIT_7))
#define LED8_TOGGLE (mPORTDToggleBits(IOPORT_BIT_7))
#define LED8_CONFIG (mPORTDOutputConfig(IOPORT_BIT_7))

#define LED7_ON (mPORTDSetBits(IOPORT_BIT_13))
#define LED7_OFF (mPORTDClearBits(IOPORT_BIT_13))
#define LED7_TOGGLE (mPORTDToggleBits(IOPORT_BIT_13))
#define LED7_CONFIG (mPORTDOutputConfig(IOPORT_BIT_13))

#define LED6_ON (mPORTCSetBits(IOPORT_BIT_13))
#define LED6_OFF (mPORTCClearBits(IOPORT_BIT_13))
#define LED6_TOGGLE (mPORTCToggleBits(IOPORT_BIT_13))
#define LED6_CONFIG (mPORTCOutputConfig(IOPORT_BIT_13))

#define LED5_ON (mPORTDSetBits(IOPORT_BIT_9))
#define LED5_OFF (mPORTDClearBits(IOPORT_BIT_9))
#define LED5_TOGGLE (mPORTDToggleBits(IOPORT_BIT_9))
#define LED5_CONFIG (mPORTDOutputConfig(IOPORT_BIT_9))

#define LED4_ON (mPORTASetBits(IOPORT_BIT_5))
#define LED4_OFF (mPORTAClearBits(IOPORT_BIT_5))
#define LED4_TOGGLE (mPORTAToggleBits(IOPORT_BIT_5))
#define LED4_CONFIG (mPORTAOutputConfig(IOPORT_BIT_5))

#define LED3_ON (mPORTASetBits(IOPORT_BIT_4))
#define LED3_OFF (mPORTAClearBits(IOPORT_BIT_4))
#define LED3_TOGGLE (mPORTAToggleBits(IOPORT_BIT_4))
#define LED3_CONFIG (mPORTAOutputConfig(IOPORT_BIT_4))

#define LED2_ON (mPORTASetBits(IOPORT_BIT_1))
#define LED2_OFF (mPORTAClearBits(IOPORT_BIT_1))
#define LED2_TOGGLE (mPORTAToggleBits(IOPORT_BIT_1))
#define LED2_CONFIG (mPORTAOutputConfig(IOPORT_BIT_1))

#define LED1_ON (mPORTASetBits(IOPORT_BIT_0))
#define LED1_OFF (mPORTAClearBits(IOPORT_BIT_0))
#define LED1_TOGGLE (mPORTAToggleBits(IOPORT_BIT_0))
#define LED1_CONFIG (mPORTAOutputConfig(IOPORT_BIT_0))

// Push Buttons:  Basic Shield connections for Max32
#define BTN1 (_RC14)
#define BTN1_CONFIG (mPORTCInputConfig(IOPORT_BIT_14))

#define BTN2 (_RG1)
#define BTN2_CONFIG (mPORTGInputConfig(IOPORT_BIT_1))

#define BTN3 (_RA6)
#define BTN3_CONFIG (mPORTAInputConfig(IOPORT_BIT_6))

#define BTN4 (_RA7)
#define BTN4_CONFIG (mPORTAInputConfig(IOPORT_BIT_7))

// Slide Switches:  Basic Shield connections for Max32
#define SW1 _RE8
#define SW1_CONFIG (mPORTEInputConfig(IOPORT_BIT_8))

#define SW2 _RE9
#define SW2_CONFIG (mPORTEInputConfig(IOPORT_BIT_9))

#define SW3 _RD12
#define SW3_CONFIG (mPORTDInputConfig(IOPORT_BIT_12))

#define SW4 _RG0
#define SW4_CONFIG (mPORTGInputConfig(IOPORT_BIT_0))





/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/    

void        LED_Toggle          (CPU_INT08U led);
void        LED_Off             (CPU_INT08U led);
void        LED_On              (CPU_INT08U led);

void        BSP_TickISR_Handler (void);
void        BSP_Except_Handler  (void);

void        BSP_InitIO          (void);
void        BSP_IntDisableALL   (void);

void        BSP_Dly             (CPU_INT32U  us);


