#ifndef __NEIGHBOR_AO_H__
#define __NEIGHBOR_AO_H__

#include "uip6.h"
// #include "uip.h"



typedef struct ReachableTimEvtTag {

  QTimeEvt  super;
	uint8_t   clk_ctr;

} ReachableTimEvt;


enum NeighborInterfaceTypes {
	ETH,
	SIXLOWPAN
};
/*
 * Neighbor AO
 */
typedef struct NeighborAOTag {
	QActive super;
	uip_ipaddr_t ipaddr;
  uip_eth_addr_t lladdr;
  u8_t isrouter;
  //struct timer reachable;
  //struct timer last_send; /**< last time a ND message was sent */
  //u8_t count_send;        /**< how many ND message were already sent */
  u8_t used;              /**< brief is this neighbor currently used */
	u16_t icmp_seq;
	u8_t interface_type;
	ReachableTimEvt ReachableTimer;
	
} Neighbor_AO;


/*
 * Neighbor Discovery Event
 */
typedef struct NDEvtTag {
    QEvent  super;
		uint8_t   dummy; //because QF needs different event sizes for pool initialization
} NdEvent;



enum Neighbor_AO_Signals {                                         /* all signals for the Base Active  state machine*/
  NS_RECEIVED_SIG = Q_USER_SIG,
	NA_RECEIVED_SIG,
	REACHABLE_TIME_SIG,
	PACKET_SENT_SIG,
	PACKET_RECEIVED_SIG,
	ICMPV6_ECHO_REPLY_SIG,
	REMOVE_NEIGHBOR_SIG
};

void Neighbor_AO_ctor(Neighbor_AO *me);
QState Neighbor_AO_initial(Neighbor_AO * me, QEvent const *e);
QState Neighbor_AO_stale(Neighbor_AO *me, QEvent const *e);
QState Neighbor_AO_delay(Neighbor_AO *me, QEvent const *e);
QState Neighbor_AO_probe(Neighbor_AO *me, QEvent const *e);
QState Neighbor_AO_incomplete(Neighbor_AO *me, QEvent const *e);
QState Neighbor_AO_reachable(Neighbor_AO *me, QEvent const *e);
QState Neighbor_AO_nostate(Neighbor_AO * me, QEvent const *e);


#endif /* __NEIGHBOR_AO_H__ */
