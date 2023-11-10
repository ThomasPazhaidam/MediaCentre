#include "GLCD.h"
#include "LED.h"
#include "LPC17xx.h"
#include <stdio.h> 
#include "string.h"
//#include "Font_6x8_h.h"
//#include "Font_16x24_h.h"

#define __FI        1                      /* Font index 16x24               */
#define __DEBUG   0										/* Uncomment to use the LCD */

//------------------------------------------------------------------- //
//------- ITM Stimulus Port definitions for printf ------------------- //
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
//------------------------------------------------------------------- //
