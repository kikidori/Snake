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

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  BSP_CLK_FREQ               72000000
#define  JTAG_ENABLE                DEF_ENABLED
#define  LCD_LINE_1                 0x02
#define  LCD_LINE_2                 0xC0

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


