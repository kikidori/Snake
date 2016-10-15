#ifndef UART1_C
#define UART1_C

#include "UART1.h"
#define _UART1
//-----------------------------------------------------------------------
// UART FUNCTIONS
//-----------------------------------------------------------------------

//----- Initialize UART1
void initU1 (void)
{
	U1BRG = BRATE;  // initialize the baud rate generator
	U1MODE = U_ENABLE;
	U1STA = U_TX | U_RX;
} // initU1

//----- Output character to UART1
void putU1 (char c)
{
	while (U1STAbits.UTXBF);	// wait while TX buffer is full
	U1TXREG = c;
}

//----- Output zero terminated string to UART1
void putsU1(char *s)
{
	while (*s)	  // loop until *s = \0, end of string
		putU1(*s++);
}

// ----- Get character from UART1
// wait for a new character to arrive to the UART1 serial port
char getU1( void)
{
    while ( !U1STAbits.URXDA);	// wait for a new character to arrive
    return U1RXREG;		// read the character from the receive buffer
}// getU1

// ------------------------------------------------------------
// baseconv
//	convert signed val into base and return as a zero terminated string
//   1<base<=16
// from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
// ------------------------------------------------------------

char* baseconv(int val, int base){
#define BUFSIZE 32
static char buf[BUFSIZE] = {0};
int i = 30;
char sign;

	if (val<0) {
		val = -val;
		sign = '-';
	}
	else sign = '+';

	if (val == 0) {
		buf[i]='0';
	}
	else {
		for(; val && i ; --i, val /= base)
			buf[i] = "0123456789abcdef"[val % base];
		buf[i] = sign;
	}

	return &buf[i];
}


// ------------------------------------------------------------
// uint2str
//  convert unsigned val into base and return as a zero terminated string
//   1<base<=16
// from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
// ------------------------------------------------------------
char* uint2str(unsigned int val, int base){
#define BUFSIZE 32
static char buf[BUFSIZE] = {0};
int i = 30;
char sign;
	for(; val && i ; --i, val /= base)
            buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}
// ------------------------------------------------------------
// fracConv
// convert unsigned val as a fraction with scaleFactor into base with NoDigits in string
// ------------------------------------------------------------
char *fracConv(unsigned int val, unsigned int base, unsigned int scaleFactor, int NoDigits)
{
unsigned int i,j,p;
static char buf[32]={0};
	p=val;
	for (i=0; (i<NoDigits)&&(i<BUFSIZE); i++)
	{
		if (scaleFactor == 0)	// if scale factor is 0 the fraction part is 0
		{
			buf[i] = '0';
		}
		else
		{
			p *= base;
			j=p;
			p <<= (32-scaleFactor);
			p >>= (32-scaleFactor);
			j >>= scaleFactor;
			buf[i] = "0123456789abcdef"[j];
		}
	}
	buf[i] ='\0';	// End of String
	return &buf[0];
}

// ------------------------------------------------------------
// Scaled2String
// Convert signed k with scaleFactor into a noFracDigits string in base
// ------------------------------------------------------------
char * Scaled2String(int k,
  unsigned int base,
  unsigned int scaleFactor,
  unsigned int noFracDigits)
{
char m, numStr[33];
unsigned int i,j,p, q;
static char buf[32] = {0};
char *bufptr;

	buf[0] = '\0';		// Set buffer to empty string
// put sign into string
	if (k<0)
	{
		k = -k;
		strcpy(buf,"-");
	}
	else strcpy(buf,"+");
// process whole part
	p=k;				// whole.frac
	p=p>>scaleFactor;	// whole
	strcat(buf,uint2str(p,base));
// insert radix point
	strcat(buf,".");
// process frac part
	p=k;					//get whole.frac
	p <<= (32-scaleFactor);	//
	p >>= (32-scaleFactor);	// 0.frac
	strcat(buf,fracConv(p,base,scaleFactor,noFracDigits));
// return string
	return &buf[0];
}

// ------------------------------------------------------------
// getsU1
// Get String from UART1.
//       From Programming 32-Bit Microcontrollers in C: Exploring the PIC32,
//		 By Lucio Di Jasio, Newnes Publishing
// ------------------------------------------------------------
char *getsU1( char *s, int len)
{
#define BACKSPACE 0x08
    char *p = s;            // copy the buffer pointer
    do{
        *s = getU1();       // wait for a new character
        putU1( *s);         // echo character

        if (( *s==BACKSPACE)&&( s>p))
        {
            putU1( ' ');     // overwrite the last character
            putU1( BACKSPACE);
            len++;
            s--;            // back the pointer
            continue;
        }
        if ( *s=='\n')      // line feed, ignore it
            continue;
        if ( *s=='\r')      // end of line, end loop
            break;
        s++;                // increment buffer pointer
        len--;
    } while ( len>1 );      // until buffer full

    *s = '\0';              // null terminate the string

    return p;               // return buffer pointer
} // getsn

// Not working correctly
// ----- convert float to ASCII string
//		basic idea from:
//       http://stackoverflow.com/questions/499939/extract-decimal-part-from-a-floating-point-number-in-c
 char* ftoa (float f,int d)
{
//#define N_DECIMAL_POINTS_PRECISION (1000) // n = 3. Three decimal points.
int integerPart = (int)f;
int decimalPart = ((int)(f*d)%d);  //
static char str[32];
	strcpy(str,baseconv(integerPart,10));
	strcat(str,".");
	strcat(str,uint2str(decimalPart,10));
	return str;

}

/* from MATLAB C32 Libraries.pdf
_mon_putc
Description: Write a character to stdout.
Include: None.
Prototype: void _mon_putc(char c);
Argument: c character to be written
Return Value: Writes a character to the FILE associated with stdout.
Remarks: This function as provided always writes to UART 2 and assumes that
the UART has already been initialized. This function can be replaced
with one that writes to another UART or other output device.
*/
void _mon_putc (char c)
{
	putU1(c);
} // _mon_putc


#endif
