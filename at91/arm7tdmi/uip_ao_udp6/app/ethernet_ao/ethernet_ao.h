#ifndef ETHERNET_AO_H_
#define ETHERNET_AO_H_

#include "qp_port.h"                /* the port of the QEP event processor */
//#include "main.h"

// used within the statemaschine to indicate if interface is up or down
#define DOWN 0
#define UP 1
#define ETHERNET_SIZE_OF_EVENT_QUEUE  128

/**
 * Max supported Ethernet Frame Size by this Application
 * using some random number here. This value will greatly influence the memory usage for the whole Application
 * 1066 + 2 (where does the 2 come from?)
 */
#define EthernetFrameSize 1068 

typedef struct EthernetBaseAOTag {
	QActive super;
	unsigned char eth_inf;  // not really used, TODO should be used or removed
} Ethernet_AO;

// typedef struct Ethernet_EventTag {
// 	QEvent super;
// 	unsigned short unused_placeholder; // ununsed
// } Ethernet_Event;

// enum Ethernet_AO_Signals { /* all signals for the Base Active  state machine*/
// 	ETHERNET_SIG = Q_USER_SIG, /* TODO, remove me, if working since its no longer required */ ETHERNET_BASE_TIME_SIG
// };

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

#endif /* ETHERNET_AO_H_ */
