/*----------------------------------------------------------------------------
 * Name:    LED.c
 * Purpose: Low Level LED functions
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2012 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "XMC4500.h"                         /* XMC4500 definitions           */
#include "LED.h"

//const unsigned long led_mask[] = {1UL << 9 };              /* GPIO P3.9       */

/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED_Init (void) {

 	/* Configuration for Pin P1.1 
	 * The pin is connected to LED1 on the XMC4500 Relax Lite Board
	 */
	PORT1->OMR |= (0<< 1);													/* Initialize low */
	PORT1->PDR0 &= (~(PORT1_PDR0_PD1_Msk));					/* Medium Driver */
  PORT1->PDR0   |= ((4 << PORT1_PDR0_PD1_Pos) & \
                          PORT1_PDR0_PD1_Msk);
	PORT1->IOCR0 |= (1 << 15); 											/* GPIO Push-Pull */

	/* Configuration for Pin P1.0 
	 * The pin is connected to LED2 on the XMC4500 Relax Lite Board
 	 */
	PORT1->OMR |= (0<< 0);													/* Initialize low */
	PORT1->PDR0 &= (~(PORT1_PDR0_PD0_Msk));					/* Medium Driver */
  PORT1->PDR0   |= ((4 << PORT1_PDR0_PD0_Pos) & \
                          PORT1_PDR0_PD0_Msk);
	PORT1->IOCR0 |= (1 << 7);												/* GPIO Push-Pull */
	
}


/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On (unsigned int num) {

  if (num == 1) {
		PORT1->OMR =  0x00000002;
  } else if (num == 2){
		PORT1->OMR =  0x00000001;
	}
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off (unsigned int num) {

  if (num == 1) {
		PORT1->OMR =  0x00020000;
  } else if (num == 2){
		PORT1->OMR =  0x00010000;
	}
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1 << i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}

/*----------------------------------------------------------------------------
  Function that toggles the requested LEDs
 *----------------------------------------------------------------------------*/
void LED_toggle (unsigned int num) {
	if (num == 1) {
		PORT1->OMR =  0x00020002;
  } else if (num == 2){
		PORT1->OMR =  0x00010001;
	}
}
