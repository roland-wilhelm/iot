/******************************************************************************/
/*  Harness main program for initialisation of MCB2300 Platform for:
    FSM state tables  Standard Implementation Example Bomb2
	Example Program for Event Driven Seminar Munich Univeristiy
	Dr. Ron Barker  
	Keil 2300 - LPC 2378 
	Standalone - no RTOS
 */
/******************************************************************************/
                  
#include <stdio.h>
#include <LPC23xx.H>                     /* LPC23xx definitions                */ 
#include "LCD.h"                        /* Graphic LCD function prototypes    */
#include "bsp.h"


extern void bomb2main (void);

int main (void) {
  int i;
  

  Init_Timer1( );
  init_serial();                               /* Init UART                   */
  uart_init_0 ( );
  lcd_init();
  lcd_clear();
  lcd_print ("FSM-StateTable Bm2");
  set_cursor (0, 1);
  lcd_print ("EventDrivenSystem");

  for (i = 0; i < 10000; i++);       /* Wait for initial display           */
 

  bomb2main();

 
 

}

