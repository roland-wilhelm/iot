/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains re-implementations of functions whose
** C library implementations rely on semihosting.
**
** Defining USE_SERIAL_PORT targets the I/O
** to the model's serial port.  Otherwise, I/O is targeted
** to the debugger console.
*/

#include <stdio.h>
#include "uart.h"
#include "pseudo_intrinsics.h"
#include "timer.h"

#define TRUE 1
#define FALSE 0
extern void uart_putc_polled(char c);
extern char uart_getchar_polled(void);

/*
** Importing __use_no_semihosting ensures that our image doesn't link
** with any C Library code that makes direct use of semihosting.
**
** Build with STANDALONE to include this symbol.
*/

#ifdef STANDALONE
#define USE_SERIAL_PORT
#pragma import(__use_no_semihosting)
#endif


/*
** Retargeted I/O
** ==============
** The following C library functions make use of semihosting
** to read or write characters to the debugger console: fputc(),
** fgetc(), and _ttywrch().  They must be retargeted to write to
** the model's UART.  __backspace() must also be retargeted
** with this layer to enable scanf().  See the Compiler and
** Libraries Guide.
*/

#ifdef USE_SERIAL_PORT

/*
** These must be defined to avoid linking in stdio.o from the
** C Library
*/

struct __FILE { int handle;   /* Add whatever you need here */};

/*
** __backspace must return the last char read to the stream
** fgetc() needs to keep a record of whether __backspace was
** called directly before it
*/
int last_char_read;
int backspace_called;



int fgetc(FILE *f)
{
    unsigned char tempch;
    tempch = uart_getchar_polled();
    last_char_read = (int)tempch;       /* backspace must return this value */
    return tempch;
}

int fputc(int ch, FILE *f)
{
    unsigned char tempch = ch;
    uart_putc_polled(tempch);
    return ch;
}




void _ttywrch(int ch)
{
    unsigned char tempch = ch;
    uart_putc_polled(tempch);
}

/*
** The effect of __backspace() should be to return the last character
** read from the stream, such that a subsequent fgetc() will
** return the same character again.
*/

int __backspace(FILE *f)
{
    backspace_called = TRUE;
    return 1;
}

/* END of Retargeted I/O */
#endif  //USE_SERIAL_PORT

/*
** Exception Signaling and Handling
** ================================
** The C library implementations of ferror() uses semihosting directly
** and must therefore be retargeted.  This is a minimal reimplementation.
** _sys_exit() is called after the user's main() function has exited.  The C library
** implementation uses semihosting to report to the debugger that the application has
** finished executing.
*/



int ferror(FILE *f)
{
    return EOF;
}

void _sys_exit(int return_code)
{
    while(1);
}
