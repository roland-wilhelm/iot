/*****************************************************************************
* Product: Board Support Package (BSP) for the QM examples
* Keil ARM  BSP for QM Framework Port to XMC-4500
* Dr. Ron Barker Munich Uni of Applied Sciences - 2013
*****************************************************************************/

#ifndef  qmbsp_h
#define qmbsp_h

             /* Exact-width types. WG14/N843 C99 Standard, Section 7.18.1.1 */

#include "XMC4500.h" 
#include "Serial.h"
#include "LED.h"
//#include "ADC.h"


/* defines for AOs */

# define BSP_TICKS_PER_SEC		 12000000/100

/*  bsp function references for the xmc_4500  */

void BSP_LED_Toggle(int led);
void BSP_Init(void);
void BSP_ButtonInit(void);
unsigned int BSP_CheckButton(unsigned int num);



void    _sys_exit(int);

#define _exit(x)  _sys_exit(x)

/* BSP function references for standalone port of QM FSM 7 HSM */

void    delay( int time );

int  _kbhit(void);
int   kbhit(void);
int  _getch(void);
int   getch(void);
void _sys_exit(int);


/* BSP Function reference for QM Example Programs */

void BSP_display(unsigned short  timeout);
void BSP_boom(void);
void BSP_LCD_display_str(char *msg, int pos, int line);
void BSP_display_str(char *msg);
void BSP_exit(void);	 
void BSP_Init(void);
void BSP_delay(int delay);



#endif                                                             /* bsp_h */
