/*----------------------------------------------------------------------------
 * Name:    IRQ.c
 * Purpose: IRQ Handler
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

#include "XMC4500.h"                         /* LPC17xx definitions           */
#include "LED.h"

#ifdef QF_TICK	   
#include "qp_port.h"
#ifdef QK
#include "qk.h"
#endif
#endif

/*----------------------------------------------------------------------------
  Systick Interrupt Handler
  SysTick interrupt happens every 10 ms
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) {

#ifdef QF_TICK
#ifdef QK
 	__disable_irq(); 
  	  ++QK_intNest_; 
#endif  

	QF_INT_UNLOCK();
	QF_tick();

	QF_INT_LOCK(); 
#ifdef QK 
	 --QK_intNest_;
	 if (   QK_intNest_ ==0) 
	   	QK_schedule_();
#endif
		 
#endif 
	 QF_INT_UNLOCK();
	 VADC->BRSMR    |=  (1UL <<  9);            /* generate Load event           */
}
