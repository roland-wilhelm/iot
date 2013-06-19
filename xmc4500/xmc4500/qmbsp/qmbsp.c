/*****************************************************************************
* Product: Board Support Package (BSP) for the QM examples
* Keil ARM - Infineon XMC 4500
* Dr. Ron Barker 
*****************************************************************************/

#include "qmbsp.h"


#include <stdio.h>
#include <stdlib.h>


/*BSP Init for the XMC-4500 */

void BSP_uip_app_call(void) {

	 // dummy call for the uip Stack -.((( dumb eh!

}

void BSP_Init( ) {

	  SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms */
		LED_Init();
	  SER_Init();
}
void BSP_Delay(unsigned int  delay) {
  // todo  XMC - 4500 HW Timer delay function 
  if ( delay )
		while (delay--);
			
}


void BSP_LED_Toggle(int led){

   LED_toggle(led);
	

}


void BSP_Info_msg(char* msg) {

//   TRACE_INFO("-uip_AO- %s\n\r", msg);
}

#ifdef QM

/*..........................................................................*/
void BSP_display(uint8_t timeout) {
    printf("[%3d] ", (int)timeout);
    fflush(stdout);
}


/*..........................................................................*/
void BSP_display_str(char *msg) {
     printf("%s", msg);

  
}
/*..........................................................................*/
void BSP_exit(void) {
    printf("Bye, Bye!");
    _sys_exit(0);
}

void BSP_delay ( int val ){

int i;
	for(i=0;i<val; i++);

}


#ifdef BOMB
void BSP_boom(void) {

	printf("boom!!!!\n");
	_sys_exit(0);
}
#endif

void  BSP_LCD_display_str( char * str, int line, int pos){

  set_cursor (line,pos);
  lcd_print ( (unsigned char const*) str);


};



#ifdef BSP_KEYBOARD


int _kbhit(void ) {

	int i;
	 i = 0xFF;
	 return(i);
}


int _getch()

{
	 FILE *f;
 return	 ( fgetc(  f) );
}
	

#endif 


#endif

/*..........................................................................*/
/* this function is used by the QP embedded systems-friendly assertions */
void Q_onAssert(char const * const file, int line) {
    printf("Assertion failed in %s, line %d", file, line);
//    fflush(stdout);
    _sys_exit(-1);
}
/*..........................................................................*/
/* Application specific callbacks from the framework  */
void QF_onCleanup(void)	  {

	 ;

	 }

void QF_onIdle(void)	  {

	
	 ;

	 }
void QF_onStartup(void)	  { 
	}

	 	