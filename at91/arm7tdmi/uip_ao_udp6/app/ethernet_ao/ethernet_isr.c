/* Product:  Basic Active Object Example µIP FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment 
* based on Adam Dunkels µIP 
* Copyright (c) 2001, Swedish Institute of Computer Science.
*/

#include "ethernet_isr.h"
#include "ethernet.h"
#include "uip_ao.h"


//static EMAC_Event emac, set this to receive since we only react only on receive
static Ethernet_Event ethernet_event = ETHERNET_RECEIVE_SIG;

//extern QActive * const UipAO;
extern QActive * const ethernetAO;

static struct EthernetRegisterSet registerSet = 0;

static unsigned int bnaCounter = 0;
//-----------------------------------------------------------------------------
/// Emac interrupt handler
//-----------------------------------------------------------------------------
void ISR_Emac(void) {
#ifdef QK
 	__disable_irq(); 
  	  ++QK_intNest_; 
#endif  
	QF_INT_UNLOCK();
	registerSet = EMAC_Handler();
	
	// check if the reason for the interrupt is a received frame
	if((registerSet.interruptStatusRegister & AT91C_EMAC_RCOMP)|| (registerSet.receiveStatusRegister & AT91C_EMAC_REC)) {
 		// Post Event to handle interrupt
		// printf("ethernet_ISR posting into queue\n");
 		QActive_postFIFO(ethernetAO, (QEvent *)&ethernet_event);
	}
	else if(registerSet.receiveStatusRegister & AT91C_EMAC_BNA) {
		// clear buffer by reading and throwing away the package
		unsigned char tmpBuf[1500];
		unsigned int len;
		// read from ethernet hardware
		len = receive(tmpBuf, 1500);
		
		bnaCounter++;
		// clear registers since the buffer is overflown
		printf("ethernet: received to many packages, clearing buffers, bnacounter = %d \n", bnaCounter);
		EMAC_Clear_HardwareBuffers();
	}
	
	QF_INT_LOCK(); 
#ifdef QK 
	   --QK_intNest_;
	   if (   QK_intNest_ ==0) 
	   		QK_schedule_();
#endif
}


