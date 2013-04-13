/*****************************************************************************
* Product: Board Support Package (BSP) for the QM examples
* Keil ARM MDK  2300 
* Dr. Ron Barker 
*****************************************************************************/
#include "bsp.h"
#include "LCD.h"

#include <stdio.h>
#include <stdlib.h>

/*..........................................................................*/
void BSP_display(uint8_t timeout) {
    printf("[%3d] ", (int)timeout);
    fflush(stdout);
}

void  BSP_LCD_display_str( char * str, int line, int pos){

  set_cursor (line,pos);
  lcd_print ( (unsigned char const*) str);

  printf("%s",str);
};


/*..........................................................................*/
void BSP_boom(void) {
    printf("BOOM!!!");
    fflush(stdout);
    _sys_exit(0);
}
/*..........................................................................*/
/* this function is used by the QP embedded systems-friendly assertions */
void Q_onAssert(char const * const file, int line) {
    printf("Assertion failed in %s, line %d", file, line);
    fflush(stdout);
    _sys_exit(-1);
}




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
	

void delay ( int val ){

int i;
	for(i=0;i<val; i++);


}


	 #ifdef BSP
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
    fprintf(stderr, "Assertion failed in %s, line %d", file, line);
    _sys_exit(-1);
}
#endif
/*..........................................................................*/
void BSP_display_str(char *msg) {
 // printf("%S", msg);
  BSP_LCD_display_str( msg,0,1);
  
}
/*..........................................................................*/
void BSP_exit(void) {
    printf("Bye, Bye!");
    _sys_exit(0);
}



	void QF_onCleanup(void)	  {

	
	 ;

	 }
	


	void QF_onIdle(void)	  {

	
	 ;

	 }
	 	void QF_onStartup(void)	  {

	
	 ;

	 }
