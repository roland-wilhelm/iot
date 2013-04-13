/* Product:  Basic Active Object Example FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */


#include "bsp_at91.h"
#include "phy_dev.h"

extern int GET_CPSR(void);  
extern void SET_CPSR(int val); 
//------------------------------------------------------------------------------
//      App  BSP_Init - Basic Hardware Initialisation Routine for the deRFarm7 
//------------------------------------------------------------------------------

void BSP_uip_app_call(void) {

	 // dummy call for the uip Stack -.((( dumb eh!
}

void BSP_Init_PHY(void);	

void BSP_LED_Toggle(int led){

  BSP_AT91_LED_Toggle( led);

}

	void BSP_Init( ) {

	 BSP_AT91_Init_Debug( "µIP - ICPM6 FSM / Co-Op Kernel)" );
	 BSP_AT91_ConfigurePit();
	 BSP_AT91_ConfigureLeds();
	 BSP_AT91_ConfigureTc();
//	 BSP_Init_PHY();
}

void BSP_Delay(unsigned int  delay) {
   BSP_AT91_Wait(delay);

}

void BSP_Init_PHY(void) {

   phy_dev_init();

}

BSP_Info_msg( char * msg) {

   TRACE_INFO("-uip_AO- %s\n\r", msg);
}


//-----------------------------------------------------------------------------
/// Global function for uIP to use
/// \param m Pointer to string that logged
//-----------------------------------------------------------------------------
void uip_log(char *m)
{
    TRACE_INFO("-oo-µIP-v6P- %s\n\r", m);
}


#ifdef KEY_USAGE

/*..........................................................................*/
void BSP_display(uint8_t timeout) {
    printf("[%3d] ", (int)timeout);
  
}


int BSP_kbhit(void ) {

  	 int i;
	 i=  DBGU_IsRxReady();

	 return(i);
}
				 
int BSP_getch()

{
 return(DBGU_GetChar());	
}
#endif

int BSP_GET_CPSR()

{
 return(GET_CPSR());	
}


void BSP_SET_CPSR(int val){
  SET_CPSR( val );

}


/*..........................................................................*/
/* this function is used by the QP embedded systems-friendly assertions */
void Q_onAssert(char const * const file, int line) {
    printf("Assertion failed in %s, line %d", file, line);
 
    _sys_exit(-1);
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


