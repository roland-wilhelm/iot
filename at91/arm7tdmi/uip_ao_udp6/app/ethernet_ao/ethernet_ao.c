#include "uip_ao.h"
//#include "ethernet_ao.h"
#include "ethernet.h"
//#include "ethernet_configuration.h"

// include base suppport package
#include "bsp_uip_ao.h"

// include ip
//#include "mock_ip_ao.h"

// include main.h
//#include "main.h"

//static Ethernet_AO ethernet_ao_local; // the local ethernet_ao
static Ethernet_BaseTimEvt BaseTimer; // TODO remove later if working, no timer is used within the AO

static Ethernet_AO ethernet_ao_local;
QActive * const ethernetAO = (QActive *) &ethernet_ao_local;

//#define ETHERNET_SIZE_OF_EVENT_QUEUE  64
 QEvent const *ethernetQueue[ETHERNET_SIZE_OF_EVENT_QUEUE]; /* Event queue storage for print time */
//QEvent const *ethernetQueue[64]; /* Event queue storage for print time */

// event for upper layers
//static IP_Event ipEvent;


/*..........................................................................*/
void Ethernet_AO_ctor(Ethernet_AO *me) {
	QActive_ctor(&me->super, (QStateHandler) & Ethernet_AO_initial);
	me->eth_inf = DOWN;
	QTimeEvt_ctor(&BaseTimer.super, ETHERNET_BASE_TIME_SIG);
}

QState Ethernet_AO_initial(Ethernet_AO *me, QEvent const *e) {
	(void) e; /* avoid compiler warning about unused parameter */
	return Q_TRAN(&Ethernet_AO_processing);
}



QState Ethernet_AO_processing(Ethernet_AO * me, QEvent const *e) {	

	unsigned int len;
	(void) me; /* avoid compiler warning about unused parameter */
	(void) e; /* avoid compiler warning about unused parameter */

	switch (e->sig) {
		case Q_INIT_SIG: {
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			return Q_HANDLED();
		}
		case ETHERNET_TRANSMIT_SIG: {
			// handle transmit paket requests
			ethernetHandleTransmitRequest();
			return Q_HANDLED();
		}
		case ETHERNET_RECEIVE_SIG: {
			Ethernet_Event *eth_evt;
			// printf("entering: ETHERNET_RECEIVE_SIG\n");
			// create event
			eth_evt = Q_NEW(Ethernet_Event, NEW_DATA_SIG); //NEW_DATA_SIG IP_RECEIVE
			 
			// read from ethernet hardware
			len = receive(eth_evt->buf, EthernetMaxBufferSize);
			eth_evt->len = len;
			
			// should be processed by upper layers. post event and let them do the work :)
			// QActive_postFIFO( ipAO, (QEvent *)&ipEvent);
			
			// publish the event to anyone listening
			QF_publish((QEvent *) eth_evt);
			
			BSP_LED_Toggle(0);

			return Q_HANDLED();
		}
		case IP_TRANSMIT_REQUEST: {
			IP_Event *ip_evt;
			unsigned int len;
			// printf("entering: IP_TRANSMIT_REQUEST\n");
			
			ip_evt = (IP_Event *) e;
			len = ip_evt->len;
			send(ip_evt->buf, len);
			
			return Q_HANDLED();
		}
		case ETHERNET_UNKNOWN_SIG: {
			break;
		}
		case Q_EXIT_SIG: {
			;
		}
	}
	return Q_SUPER(&QHsm_top);
}
