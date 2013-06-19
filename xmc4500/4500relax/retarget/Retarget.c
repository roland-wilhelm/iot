/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2012 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_misc.h>
#include "Serial.h"


#pragma import(__use_no_semihosting_swi)

#define USE_JLINK_PRINTF  1

#ifdef USE_JLINK_PRINTF
	#define ITM_Port8(n)	(* ((volatile unsigned char *) (0xE0000000+4*n)))
	#define ITM_Port16(n)	(* ((volatile unsigned short *) (0xE0000000+4*n)))
	#define ITM_Port32(n)	(* ((volatile unsigned long *) (0xE0000000+4*n)))
	
	#define DEMCR					(* ((volatile unsigned long *) (0xE000EDFC)))
	#define TRCENA				0x01000000
#endif

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
#ifdef USE_JLINK_PRINTF
	if (DEMCR & TRCENA) {
		while (ITM_Port32(0) == 0);
		ITM_Port8(0) = c;
	}
	return (c);
#else
  return (SER_PutChar(c));
#endif
}


int fgetc(FILE *f) {
  return (SER_GetChar());
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  SER_PutChar(c);
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}
