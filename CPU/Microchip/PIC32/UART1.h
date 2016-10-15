// UART1.h

#ifndef UART1_H
#define UART1_H

#include <p32xxxx.h>
#include <stdio.h>
//#include <plib.h>
#include <inttypes.h>
#include <includes.h>

//-----------------------------------------------------------------------
// UART1 DEFINES
//-----------------------------------------------------------------------
#define U_TX 0x0400
#define U_RX 0x1000
#define U_ENABLE 0x8008 // enable, BREGH = 1, 1 stop, no parity
#define BAUD_RATE (115200)
//#define BRATE 86 	// 115,200 Baud Rate = FPB / 4(U1BRG + 1))  FPB = freq of peripheral clock
					// U1BRG = ((FPB/Desired Baud Rate)/4) - 1
					// if BREGH = 0 then use 16 in place of 4 in above formulas
//#define BRATE 155       // 72 MHz clock with Fpb = 72 MHz
#define BRATE ((BSP_CLK_FREQ/4) / (BAUD_RATE))-1

//-----------------------------------------------------------------------
// UART FUNCTIONS
//-----------------------------------------------------------------------

//----- Initialize UART1
void initU1 (void);

//----- Output character to UART1
void putU1 (char c);

//----- Output zero terminated string to UART1
void putsU1(char *s);


// ----- Get character from UART1
// wait for a new character to arrive to the UART1 serial port
char getU1( void);

// ------------------------------------------------------------
// uint2str
//  convert unsigned val into base and return as a zero terminated string
//   1<base<=16
// from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
// ------------------------------------------------------------
char* uint2str(unsigned int val, int base);

// ----- convert val into base and return as a zero terminated string
//   1<base<=16
// from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
char* baseconv(int val, int base);

// ----- convert scaled val into whole.frac base and return as a zero terminated string
//   1<base<=16

char * Scaled2String(int k,
  unsigned int base,
  unsigned int scaleFactor,
  unsigned int noFracDigits);

// ----- Get String from U1.
//       From Programming 32-Bit Microcontrollers in C: Exploring the PIC32,
//		 By Lucio Di Jasio, Newnes Publishing.
char *getsU1( char *s, int len);

#endif 