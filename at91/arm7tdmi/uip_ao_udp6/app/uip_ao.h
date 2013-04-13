


#ifndef uip_ao_h
#define uip_ao_h



#include "qp_port.h"                /* the port of the QEP event processor */


#include <stdlib.h>  

/* Active object class -----------------------------------------------------*/

 
#define DOWN 0
#define UP 1

#define SIZE_OF_EVENT_QUEUE  24// 128
#define MAX_PUB_SIG 32

/**
 * Max supported Ethernet Frame Size by this Application
 * using some random number here. This value will greatly influence the memory usage for the whole Application
 * 1066 + 2 (where does the 2 come from?)
 */
#define EthernetFrameSize 1068 
 
typedef struct EMACvtTag {
    QEvent super;                                            /* derive from the QEvent structure */
    unsigned short  type;                           /* the a/d conversion value */
} EMAC_Event;


typedef struct BaseTimEvtTag {

    QTimeEvt  super;
		uint8_t   clk_ctr;

} BaseTimEvt;

typedef struct BasePrintEvtTag {
    QEvent  super;
} BasePrintEvt;

typedef struct NewDataEvtTag {
	QEvent super;
	unsigned char buf[1066+2];
	unsigned int len;
} NewDataEvent;

typedef struct BaseAOTag {
    QActive super;
	unsigned char eth_inf;
	
} Uip_AO;

// Event used by  Event driven µIP Layer
typedef struct IPEvtTag {
	QEvent super;
	unsigned char buf[EthernetFrameSize];
	unsigned int len;
	unsigned int placeholder; // used to artificialy increase the Event Size since QF requires the Events to be greater then the previously initialized events
  unsigned int placeholder1;
	}  IP_Event;



// Ethernet_AO defines 
#define ETHERNET_SIZE_OF_EVENT_QUEUE  64 // 128

#define EthernetMaxBufferSize 1068 

typedef struct EthernetBaseAOTag {
	QActive super;
	unsigned char eth_inf;  // not really used, TODO should be used or removed
} Ethernet_AO;

// TODO remove later, no timer is used
typedef struct Ethernet_BaseTimEvtTag {
	QTimeEvt super;
	uint8_t clk_ctr;
} Ethernet_BaseTimEvt;

// TODO remove later, this is only used for sizeof(Ethernet_BasePrintEvt)
typedef struct Ethernet_BasePrintEvtTag {
	QEvent super;
	int unused_placeholder; // use this variable to change the size of this event, qf_poolinit requires that the eventsizres are different each time
} Ethernet_BasePrintEvt;


typedef struct EthernetEvtTag {
	QEvent super;
	unsigned char buf[EthernetFrameSize];
	unsigned int len;
} Ethernet_Event;

/**
 * Active Object for Ethernet
 */
extern QActive * const ethernetAO;
extern QEvent const *ethernetQueue[ETHERNET_SIZE_OF_EVENT_QUEUE];

// methods of the state machine
extern void Ethernet_AO_ctor(Ethernet_AO *me);
extern QState Ethernet_AO_initial(Ethernet_AO * me, QEvent const *e);
extern QState Ethernet_AO_processing(Ethernet_AO *me, QEvent const *e);



enum Uip_AO_Signals {                                         /* all signals for the Base Active  state machine*/
  PROCESS_IP_SIG = Q_USER_SIG,
	BASE_TIME_SIG,
	EMAC_INT_SIG,
	NEW_DATA_SIG,
	SEND_DATA_SIG,
	
	
	/* Ethernet Signals, PHY eth team (definition is not final, may change!) */
	ETHERNET_UNKNOWN_SIG,
	ETHERNET_TRANSMIT_SIG,
	ETHERNET_RECEIVE_SIG,
	ETHERNET_BASE_TIME_SIG, 
	
	MAC_SIG, 
	
	/* IP Signals, (definition is not final, may change!) */
	IP_RECEIVE,
	IP_TRANSMIT_REQUEST
   
};




typedef struct uip_state {
 
  char inputbuffer[10];
  char name[40];
} uip_tcp_appstate_t;


/* Finally we define the application function to be called by uIP. */
void BSP_uip_app_call(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL BSP_uip_app_call
#endif /* UIP_APPCALL */




#endif	 // uip_ao.h
