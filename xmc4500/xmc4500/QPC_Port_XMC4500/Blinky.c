/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
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

#include <stdio.h>
#include "XMC4500.h"                         /* XMC4500 definitions           */
//#include "Serial.h"
//#include "LED.h"
#include "qp_port.h"
#include "bsp.h"
#include "base_ao.h"
#include "Hex_O_Pan_Send.h"
#include "LED.h"

#define SIZE_OF_EVENT_QUEUE  10
#define MAX_PUB_SIG					 50

typedef union smallPool_T_{
	BaseTimEvt		timeEvt;
	BasePrintEvt	printEvt;
}smallPool_T;

/**
 * put all medium events in here
 */
typedef union mediumPool_T_{
	HexOPanErrorEvt errorEvt;
	HexOPanSendEvt receiveEvt;
}mediumPool_T;

static QEvent const * l_baseAOQueue[5];
static QEvent const * l_SendAOQueue[10];

static smallPool_T 	smallPool[ SIZE_OF_EVENT_QUEUE ];		/* get the junk of storage for the small event pool */
static mediumPool_T mediumPool[ SIZE_OF_EVENT_QUEUE ];	/* get the junk of storage for the medium event pool */

static QSubscrList	subscrList[ MAX_PUB_SIG ];					/* publish subscribe */

/* Import external variables from IRQ.c file                                  */
extern uint8_t  clock_1s;

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
	bsp_Init();

  SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms */
	printf("Hello World!\n");
	QF_init();    /* Initialize the framework and the underlying RT kernel */
	
  /* explicitly invoke the active objects' constructors... */
	BaseAO_ctor((BaseAO *)Base);
	Hex_O_Pan_Send_ctor((Hex_O_Pan_SendAO *) HexOPan_Send);
		
	printf("Small Poolsize: %i\r\n", sizeof(smallPool[0]));
	printf("Medium Poolsize: %i\r\n", sizeof(mediumPool[0]));
	
	/*test publish subscribe stuff*/
	QF_poolInit(smallPool, sizeof(smallPool), sizeof(smallPool[0]));		/* initialize the small event pool... */
	QF_poolInit(mediumPool, sizeof(mediumPool), sizeof(mediumPool[0]));	/* initialize the medium event pool... */
	
	QF_psInit(subscrList, Q_DIM(subscrList));	/* initialize publish subscribe */

	LED_On(1);
	
	/* Start the active objects... */
	QActive_start((QActive *) Base, 									/* global pointer to the active object */
								1, 																			/* priority (lowest) */
								l_baseAOQueue, Q_DIM(l_baseAOQueue),													
                (void *)0, 0,														/* no per-thread stack */
								(QEvent *)0);														/* no initialization event */
					
	QActive_start((QActive *)HexOPan_Send, 							/* global pointer to the active object */
								2, 																			/* priority */
								//(void*) 0, 0,
								l_SendAOQueue, Q_DIM(l_SendAOQueue),  	/* event queue */
                (void *)0, 0,														/* no per-thread stack */
								(QEvent *)0);														/* no initialization event */				
					
  QF_run();		/* run the QF application */

  return(0);
}
