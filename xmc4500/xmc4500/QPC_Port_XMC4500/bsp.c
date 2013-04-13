
#include "bsp.h"
#include "stdio.h"
#include "XMC4500.h"                         /* XMC4500 definitions           */

/**
 *	Function to initialize the XMC4500 Relax Lite Kit
 */
void bsp_Init(void){	
  LED_Init();                                /* LED Initialization            */
  SER_Init();                                /* UART Initialization           */
	bsp_ButtonInit();													 /* Button initialization					*/
	//ADC_Init();
}

void bsp_ButtonInit(void){
	/*
	 * Configuratoin of the Pin P1.14
	 */
	PORT1->OMR |= (0<< 14);													/* Initialize low */
  PORT1->PDR1  &= (~(PORT1_PDR1_PD14_Msk));				/* Medium Driver */
  PORT1->PDR1  |= ((4 << PORT1_PDR1_PD14_Pos) & \
                                     PORT1_PDR1_PD14_Msk);
  PORT1->IOCR12 |= (1 << 21); 										/* Inverted Input, no pull device active */
	
	/*
	 * Configuratoin of the Pin P1.14
	 */
	PORT1->OMR |= (0<< 15);													/* Initialize low */
  PORT1->PDR1  &= (~(PORT1_PDR1_PD15_Msk));				/* Medium Driver */
  PORT1->PDR1  |= ((4 << PORT1_PDR1_PD15_Pos) & \
                                     PORT1_PDR1_PD15_Msk);
  PORT1->IOCR12 |= (1 << 29); 										/* Inverted Input, no pull device active */
}

unsigned int bps_checkButton(unsigned int num){
	if(num == 1){
		if( ( PORT1->IN >> 14 ) & 1U )	/* check Button 1 */
		{
			return 1;
		}else{
			return 0;
		}
	}else if(num == 2){
		if( ( PORT1->IN >> 15 ) & 1U )	/* check Button 2 */
		{
			return 1;
		}else{
			return 0;
		}
	}else{
		return 99;
	}
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
	 
	 
