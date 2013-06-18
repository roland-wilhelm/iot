/* Product:  Basic Active Object Example FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */


#include "qp_port.h"                /* the port of the QEP event processor */
#include "qmbsp.h"

// #include "bsp_uip_ao.h"
#include "uip_ao.h"
#include "uip-nd6.h"
//#include "phy_dev.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>   

				   
void Uip_AO_ctor(Uip_AO *me);

static QState Uip_AO_initial(Uip_AO * me, QEvent const *e);
//static QState Uip_AO_processing(Uip_AO *me, QEvent const *e);
static QState Uip_AO_idle(Uip_AO *me, QEvent const *e);
static QState Uip_AO_receiving(Uip_AO *me, QEvent const *e);

static Uip_AO  l_Uip_AO;    /* the uip active objec----------------------------------------------*/

      
 		  
QActive * const UipAO  = (QActive *) &l_Uip_AO;

QEvent const *l_PrintEvtQSto[ SIZE_OF_EVENT_QUEUE];
QEvent const  *l_Uip_EvtQSto [8];


#define MAX_POOL_SIZE				4
#define MAX_PUB_SIG 				32

//storage for dynamic NewDataEvent queue :: dynamicPoolEthernet contains 4 Ethernet Events at the same time.
static Ethernet_Event dynamicPoolEthernet[MAX_POOL_SIZE];

//ToDO: storage for QF PubSub
static QSubscrList subscriberEthernet[MAX_PUB_SIG];

//storage for dynamic NewDataEvent queue
static IP_Event dynamicPoolIP[MAX_POOL_SIZE];


/*..........................................................................*/
void Uip_AO_ctor(Uip_AO *me) {
  
    QActive_ctor(&me->super, (QStateHandler)&Uip_AO_initial);
	me->eth_inf=DOWN;

}

QState Uip_AO_initial(Uip_AO *me, QEvent const *e) {
    (void)e;               /* avoid compiler warning about unused parameter */
				QActive_subscribe((QActive *)me, NEW_DATA_SIG);
				QActive_subscribe((QActive *)me, SEND_DATA_SIG);
    return Q_TRAN(&Uip_AO_idle);
}
#ifdef XXX
QState Uip_AO_processing (Uip_AO * me, 	  QEvent const *e) {
		  
           (void)me;              /* avoid compiler warning about unused parameter */
           (void)e;               /* avoid compiler warning about unused parameter */
		 
	 	   switch ( e->sig ) {

		   case Q_INIT_SIG: {
 	      
		  	BSP_Info_msg("processing-INIT");
	
			return Q_HANDLED();
  			}

		   	case Q_ENTRY_SIG: {
		    BSP_Info_msg("processing-ENTRY;");
			   return Q_HANDLED();
			}
		   case EMAC_INT_SIG:
		   			if (  me->eth_inf==DOWN ){
						me->eth_inf=UP;	   		   			
				  	    BSP_Info_msg(" eth0: UP ;");
					}
					BSP_LED_Toggle(0);

		   return Q_HANDLED();

		   case BASE_TIME_SIG: {

#ifdef xxxx			  
			   (
			  ((BaseTimEvt *)e)->clk_ctr ++;
				 
   			  if (  ((BaseTimEvt *)e)->clk_ctr >= 10 ){
		  	
			  		 static QEvent const IP_PollEvt = { PROCESS_IP_SIG, 0};
					 BSP_LED_Toggle(0);
			         ((BaseTimEvt *)e)->clk_ctr =0;
			

 		         QActive_postFIFO((QActive *)me, &IP_PollEvt);
				 }
#endif				
			   	return Q_HANDLED();

		   }
	  
		   case Q_EXIT_SIG: {
   				
 			      BSP_Info_msg("processing-EXIT;");
		      	
		   }
		   	  
	}
 
	 return Q_SUPER(&Uip_AO_receiving);	
}
#endif XXX

QState Uip_AO_receiving (Uip_AO *me, QEvent const *e) {
			NewDataEvent * data_evt;
			int status;
	switch ( e->sig ) {

	 		case Q_INIT_SIG: {  

	//			 return Q_TRAN(&Uip_AO_processing);
		   	    
  			}
	      
		   	case Q_ENTRY_SIG: {
			  	 BSP_Info_msg("receiving-ENTRY;");
						// BSP_LED_Toggle(0);
			   return Q_HANDLED();
				}
			
			 case NEW_DATA_SIG: {
				 status = resolve_protocol_type((NewDataEvent *)e);
				 
				if ( status == UIP_PROTO_UDP );
						// BSP_Info_msg("receivign-NEW_DATA - UDP;");
				 return Q_HANDLED();
			 }
			 case SEND_DATA_SIG: {
				// * \todo lookup destination through prefix
				// *		if its Ethernet publish Ethernet event
				// *		else publish 6lowpan event
				// *    for now we directly send to ethernet interface
				// 
		//		 QF_INT_LOCK(); 			// does this have any effect
					data_evt = (NewDataEvent *) e;
			 // status= BSP_GET_CPSR();
					createAndPublishEvent( (unsigned int ) data_evt->len, (unsigned char*)data_evt->buf);
				//	BSP_SET_CPSR(status);
	//			 QF_INT_UNLOCK(); 			// does this have any effect
				 return Q_HANDLED();
			 }
			 
			 case  PROCESS_IP_SIG: { 
				  BSP_LED_Toggle(2);
			
				//if ( me->eth_inf == UP )
				 //	process_packet();
			  return Q_HANDLED();
		   
			 }
			 
	 	   case Q_EXIT_SIG: {
			  	  BSP_Info_msg("receiving-EXIT;");	  	   
			}
	
		 	
	}

 
	 return Q_SUPER(&Uip_AO_idle);

}

 QState Uip_AO_idle(Uip_AO *me, QEvent const *e) {
    switch (e->sig) {
   
    	case Q_INIT_SIG: {
  			
			BSP_Info_msg("idle-INIT;");
       return Q_TRAN(&Uip_AO_receiving);
      }
	
        case Q_ENTRY_SIG: {
						BSP_Info_msg("idle-ENTRY;");
					  initalise_uipv6();
						// initalise_uip();
            return Q_HANDLED();
        }
       
    }
    return Q_SUPER(&QHsm_top);
}

int main ()	{
	
			printf("starttest\n");
	
			// ToDo: Difference BSP_Init??
      BSP_Init();
		
			/* initialize the framework and the underlying RT kernel */
 			QF_init();    

    	/* instantiate and start the active objects... */
  
			/* Situation: 
				1- No Print Event - Plan: Comment - OK
				2- Events not copied - ToDo: Plan: Changing Event with Buffer to only descriptor --> Handler reads from Buffer
				3- Small evvent with just descriptor - Plan: Event should only have descriptor
				4- No Ethernet Active Object, only ISR that creates event.
				*/
			Ethernet_AO_ctor((Ethernet_AO *)ethernetAO);
			
			// ToDo: Change dynamic pool to fixed pool with descriptor values. 255 entries.
			QF_poolInit(dynamicPoolEthernet, sizeof(dynamicPoolEthernet), sizeof(dynamicPoolEthernet[0]));
			QF_psInit(subscriberEthernet, Q_DIM(subscriberEthernet));	
			
			QActive_start(ethernetAO, 1, ethernetQueue, Q_DIM(ethernetQueue), (void *) 0, 0, (QEvent *) 0);	
			QActive_subscribe((QActive *)ethernetAO, IP_TRANSMIT_REQUEST);
			
			init_ethernet();
	
			// uip_nd6_init(l_PrintEvtQSto); ToDo: Neighbour discovery not yet.
	
	////////////////////////////////////////////////////////////////// UIP AO
			uip_nd6_init(l_PrintEvtQSto); 
	

			Uip_AO_ctor(&l_Uip_AO);
      QActive_start((QActive *)&l_Uip_AO, 4, l_Uip_EvtQSto, Q_DIM(l_Uip_EvtQSto),
                  (void *)0, 0, (QEvent *)0);
    	QF_poolInit(dynamicPoolIP, sizeof(dynamicPoolIP), sizeof(dynamicPoolIP[0]));
		
	////////////////////////////////////////////////////////////////// UIP AO
		
			// Check if task level
	
		  QF_run(); /* run the QF application */

		  return(0);
}

int createAndPublishEvent(unsigned int len, unsigned char* buffer) {
	// create event
	IP_Event *ip_evt = Q_NEW(IP_Event, IP_TRANSMIT_REQUEST);
	
	// set the length
	ip_evt->len = len;
	
	// copy the buffer to the event memory
	memcpy(ip_evt->buf, buffer, len);
	
	// publish the event to anyone listening
	// printf("entering: IP_TRANSMIT_REQUEST\n");
	QF_publish((QEvent *) ip_evt);
	
}

void uip_log(char *m)
{
    // TRACE_INFO("-oo-µIP-v6P- %s\n\r", m);
}