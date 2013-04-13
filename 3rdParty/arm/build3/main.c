/*
** Copyright (C) ARM Limited, 2006. All rights reserved.
*/

/*
** This file contains the main() program.
*/

#include <stdio.h>
#include "uart.h"
#include "pseudo_intrinsics.h"
#include "scs.h"
#include "timer.h"


void Display_80(const char* the_char);
static void short_delay(void);


int main(void)
{
 	int SYSm;

    /* Initialise MPU, I/O and SysTick */
    SCS_init();
    UART_init();
    SysTick_init();

    /* Finally change Thread mode to unprivileged
     * but continue using Main Stack Pointer */
    SYSm = __MRS_control();
    SYSm |= 1;
    __MSR_control(SYSm);

    /* Flush and refill pipline with unprivileged permissions */
    __ISB();

    printf("Cortex-M3 Example - Build 3\n");

    /* Loop forever */
    while( 1 )
    {
        Display_80((char*) ".");
    }
}


/* Output "the_char" 80 times, with delay between
 * each to make it easier to interrupt              */
void Display_80(const char* the_char)
{
   int count=80;

   /* Move to new line */
   printf(" \r\n");

   /* Print "the_char" 80 times with short delay between each */
   while(--count >= 0)
   {
      printf(the_char);
      short_delay();
   }
}


/* Function to create a short delay,
 * __inline instructs compiler to consider inlining function */
__inline static void short_delay(void)
{
   volatile int delay=10000;
   while(--delay > 0)
   {
   }
}

