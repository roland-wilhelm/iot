#include "neighbor_ao.h"
#include <stdio.h>
#include "uip-nd6.h"
#include "uip-icmp6.h"
#include <string.h>

//! Neighbor_AO Handlers
/*!  
	This Module implements the Handlers for the different states
	of the Neighbor_AO
*/

/**
 * \brief reset the specified Neighbor_AO to its default values
 *
 * \param Neighbor_AO
 */
static void resetNeighbor(Neighbor_AO *neighbor)
{
	neighbor->used = 0;
	memset(&neighbor->ipaddr,0, sizeof(uip_ipaddr_t));
	memset(&neighbor->ipaddr,0, sizeof(uip_eth_addr_t));
}

/*..........................................................................*/

/**
 * \brief Neighbor_AO Constructor
 *
 * \param Neighbor_AO
 */
void Neighbor_AO_ctor(Neighbor_AO *me) 
{
	resetNeighbor(me);
  QActive_ctor(&me->super, (QStateHandler)&Neighbor_AO_initial);
	QTimeEvt_ctor(&me->ReachableTimer.super, REACHABLE_TIME_SIG);
}

/**
 * \brief Initial state handler
 *
 * \param Neighbor_AO, QEvent
 */
QState Neighbor_AO_initial(Neighbor_AO *me, QEvent const *e) {
    (void)e;               /* avoid compiler warning about unused parameter */
	return Q_TRAN(&Neighbor_AO_nostate);
}


/**
 * \brief nostate state handler
 *
 * \param Neighbor_AO, QEvent
 */
QState Neighbor_AO_nostate(Neighbor_AO * me, QEvent const *e)
{
	(void)e;               /* avoid compiler warning about unused parameter */
	switch ( e->sig ) {
		case Q_INIT_SIG: {
			printf("\nNeighbor_AO: nostate-INIT\n");
			print_ip6_addr(&me->ipaddr);
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			printf("\nNeighbor_AO: nostate-ENTRY\n");
			print_ip6_addr(&me->ipaddr);
			return Q_HANDLED();
		}
		case NS_RECEIVED_SIG:
		case PACKET_RECEIVED_SIG: {
			return Q_TRAN(&Neighbor_AO_reachable);
		}
	}
	return Q_SUPER(&QHsm_top);
}

/**
 * \brief Reachable state handler
 *
 * \param Neighbor_AO, QEvent
 */
QState Neighbor_AO_reachable(Neighbor_AO *me, QEvent const *e)
{
  (void)e;               /* avoid compiler warning about unused parameter */
	switch ( e->sig ) {
		case Q_INIT_SIG: {
			printf("Neighbor_AO: reachable-INIT\n");
			print_ip6_addr(&me->ipaddr);
			me->ReachableTimer.clk_ctr = UIP_ND6_REACHABLE_TIME;
			QTimeEvt_postEvery(&me->ReachableTimer.super, (QActive *)me, 100);
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			QTimeEvt_disarm(&me->ReachableTimer.super);
			printf("\nNeighbor_AO: reachable-EXIT\n");
			print_ip6_addr(&me->ipaddr);
			return Q_HANDLED();
		}
		case REACHABLE_TIME_SIG: {
			((ReachableTimEvt *)e)->clk_ctr --;
			if (0 == ((ReachableTimEvt *)e)->clk_ctr)
				return Q_TRAN(&Neighbor_AO_delay);
			return Q_HANDLED();
		}
		case PACKET_SENT_SIG: 
		case PACKET_RECEIVED_SIG: {
			me->ReachableTimer.clk_ctr = UIP_ND6_REACHABLE_TIME;
			return Q_HANDLED();
		}
			
	}
	return Q_SUPER(&Neighbor_AO_nostate);
}

/**
 * \brief Stale state handler
 *
 * \param Neighbor_AO, QEvent
 */
QState Neighbor_AO_stale(Neighbor_AO *me, QEvent const *e) {
  (void)e;               /* avoid compiler warning about unused parameter */
  switch ( e->sig ) {
			case Q_INIT_SIG: {
				printf("\nNeighbor_AO: stale-INIT\n");
				print_ip6_addr(&me->ipaddr);
				return Q_HANDLED();
			}
			case Q_ENTRY_SIG: {
				printf("\nSending Echo Request \n");
				uip_icmp6_echo_request_output_to_neighbor(me);
				printf("\nNeighbor_AO: stale-ENTRY\n");
				print_ip6_addr(&me->ipaddr);
				return Q_HANDLED();
			}
			case Q_EXIT_SIG: {
				printf("\nNeighbor_AO: stale-EXIT\n");
				print_ip6_addr(&me->ipaddr);
				return Q_HANDLED();
			}
			case REMOVE_NEIGHBOR_SIG: {
				printf("\nNeighbor_AO: removing neighbor\n");
				print_ip6_addr(&me->ipaddr);
				//QActive_stop((QActive *)me);
				resetNeighbor(me);
				return Q_TRAN(&Neighbor_AO_nostate);
			}
		}
		return Q_SUPER(&Neighbor_AO_nostate);
}


/**
 * \brief Delay state handler
 *
 * \param Neighbor_AO, QEvent
 */
QState Neighbor_AO_delay(Neighbor_AO *me, QEvent const *e)
{
	(void)e;               /* avoid compiler warning about unused parameter */
  switch ( e->sig ) {
			case Q_INIT_SIG: {
				printf("\nNeighbor_AO: delay-INIT\n");
				print_ip6_addr(&me->ipaddr);
				return Q_HANDLED();
			}
			case Q_ENTRY_SIG: {
				printf("\nNeighbor_AO: delay-ENTRY\n");
				print_ip6_addr(&me->ipaddr);
				me->ReachableTimer.clk_ctr = 0;
				QTimeEvt_postIn(&me->ReachableTimer.super, (QActive *)me, ND6_DELAY_STATE_TIMEOUT);
				return Q_HANDLED();
			}
			case REACHABLE_TIME_SIG: {
				return Q_TRAN(&Neighbor_AO_probe);
			}
			case Q_EXIT_SIG: {
				printf("\nNeighbor_AO: delay-EXIT\n");
				print_ip6_addr(&me->ipaddr);
				QTimeEvt_disarm(&me->ReachableTimer.super);
				return Q_HANDLED();
			}
			case ICMPV6_ECHO_REPLY_SIG: {
				return Q_TRAN(&Neighbor_AO_reachable);
			}
		}
		return Q_SUPER(&Neighbor_AO_stale);
}


/**
 * \brief Probe state handler
 *
 * \param Neighbor_AO, QEvent
 */
QState Neighbor_AO_probe(Neighbor_AO *me, QEvent const *e)
{
	(void)e;               /* avoid compiler warning about unused parameter */
  switch ( e->sig ) {
			case Q_INIT_SIG: {
				printf("\nNeighbor_AO: probe-INIT\n");
				print_ip6_addr(&me->ipaddr);
				return Q_HANDLED();
			}

			case Q_ENTRY_SIG: {
				printf("\nNeighbor_AO: probe-ENTRY\n");
				print_ip6_addr(&me->ipaddr);
				printf("\nNeighbor_AO: probe- Sending NS\n");
				uip_nd6_io_ns_output(&uip_hostaddr,&me->ipaddr, &me->lladdr, &me->ipaddr);
				me->ReachableTimer.clk_ctr = 2;
				QTimeEvt_postEvery(&me->ReachableTimer.super, (QActive *)me, 10000);
				return Q_HANDLED();
			}
			case REACHABLE_TIME_SIG: {
				static QEvent const NdEvent = { REMOVE_NEIGHBOR_SIG};
				printf("\nNeighbor_AO: probe- Sending NS\n");
				uip_nd6_io_ns_output(&uip_hostaddr, &me->ipaddr, &me->lladdr, &me->ipaddr);
				((ReachableTimEvt *)e)->clk_ctr --;
				if (0 == ((ReachableTimEvt *)e)->clk_ctr) {
					QTimeEvt_disarm(&me->ReachableTimer.super);	
					QActive_postFIFO((QActive *)me, &NdEvent);
				}
				return Q_HANDLED();
			}
			case Q_EXIT_SIG: {
				printf("\nNeighbor_AO: probe-EXIT\n");
				print_ip6_addr(&me->ipaddr);
				QTimeEvt_disarm(&me->ReachableTimer.super);
				return Q_HANDLED();
			}
			case NA_RECEIVED_SIG: {
				return Q_TRAN(&Neighbor_AO_reachable);
			}
		}
		return Q_SUPER(&Neighbor_AO_stale);
}

