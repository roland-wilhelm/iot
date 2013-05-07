	
/* Product:  Button driver for XMC-4500 Relax Kit
* Last Updated for Version: 4.1.01
* Date of the Last Update:  May 06, 2013
* Ported to XMC-4500 Relax Kit 
* Keil  ARM - µLink Environment
*/


#include "XMC4500.h"                         /* XMC4500 definitions           */

void BSP_ButtonInit(void){
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

unsigned int BSP_CheckButton(unsigned int num){
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
