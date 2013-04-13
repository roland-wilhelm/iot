/*****************************************************************************

* Date of the Last Update:  31.10.2011
* Dr. Ron Barker - Port to FreeRtos for ARM7TDMI - NXP 2378 - Keil 2300
* Example Program for Event Driven Seminar Munich Univeristiy	- DPP 
*	Dr. Ron Barker  
*	Keil 2300 - LPC 2378 
*	FreeRTOS


*/
#ifndef bsp_h
#define bsp_h


 void uart_init_0(void );
 void    _sys_exit(int);
 #define _exit(x)  _sys_exit(x)

/* bsp function references for standalone port of QM FSM 7 HSM */



int  _kbhit(void);
int   kbhit(void);
int  _getch(void);
int   getch(void);
void _sys_exit(int);




void BSP_Init(void );


#endif                                                             /* bsp_h */

