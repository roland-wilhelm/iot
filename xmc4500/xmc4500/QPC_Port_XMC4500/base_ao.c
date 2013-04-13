/* Product:  Basic Active Object Example FSM with Generic Event Processor - Preemptive RT QK Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */


#include "qp_port.h"                /* the port of the QEP event processor */

#include "base_ao.h"
#include <stdio.h>
#include <stdlib.h>  
#include "LED.h"
#include "captures.h"
#include "Hex_O_Pan_Send.h"
#include "bsp.h"

/**
 * uncomment this line if you like debug output from the baseAO
 */
//#define DBG

/* the sole instance of the Base active object */
static BaseAO l_BaseAO;

/* opaque pointer to the BaseAO */
QActive * const Base  = (QActive *) &l_BaseAO;

/* state handler functions */
static QState BaseAO_initial(BaseAO * me, QEvent const *e);
static QState BaseAO_processing(BaseAO *me, QEvent const *e);
static QState BaseAO_idle(BaseAO *me, QEvent const *e);
static QState BaseAO_displaying(BaseAO *me, QEvent const *e);

static BaseTimEvt BaseTimer;  

/*..........................................................................*/
void BaseAO_ctor(BaseAO *me) {
	QActive_ctor(&me->super, (QStateHandler)&BaseAO_initial);
  QTimeEvt_ctor(&BaseTimer.super, BASE_TIME_SIG);
}

/**********************************************************************
 * Initial transition
 **********************************************************************/
QState BaseAO_initial(BaseAO *me, QEvent const *e) {
  (void)e;               /* avoid compiler warning about unused parameter */
#ifdef DBG
	printf("initial;\r\n");
#endif
		/* subscribe to all interresting signals... */
	QActive_subscribe((QActive *) me, SER_DISPLAY_SIG);
	QActive_subscribe((QActive *) me,  HEX_TO_MAC);
	return Q_TRAN(&BaseAO_idle);
}

/**********************************************************************
 * State: BAseAO_processing
 **********************************************************************/
QState BaseAO_processing (BaseAO * me, 	  QEvent const *e) {
//	int status;
//	uint8_t key;					 /* the character we received from the host pc    */
	HexOPanSendEvt* ipEvt;
	lladdr_t address;
	int i = 0;
  (void)me;              /* avoid compiler warning about unused parameter */
	(void)e;               /* avoid compiler warning about unused parameter */
	
	switch ( e->sig ) {
		case Q_INIT_SIG: {  
#ifdef DBG
		  printf("processing-INIT;\r\n");
#endif
			BaseTimer.clk_ctr=0;
			QTimeEvt_postEvery(&BaseTimer.super, (QActive *)me, 1);
			return Q_HANDLED();
  	}
		case Q_ENTRY_SIG: {
#ifdef DBG
		  printf("processing-ENTRY;\r\n");
#endif
			return Q_HANDLED();
		}
		case BASE_TIME_SIG: {
			//status= BSP_GET_CPSR();
			((BaseTimEvt *)e)->clk_ctr ++;

			/* We receive the user commands here.
			 * Send the commands  to the Send-Statemachine
			 */
			if(bps_checkButton(1) == 1){
					printf("IP -> Sending IPv6 Packet #1\r\n");	
					/* send the event to the SendAO */
					
					ipEvt = Q_NEW(HexOPanSendEvt, NEW_IP_PACKET);
					
					for(i = 0; i < LENGTH_PACKET_1; i++){
						ipEvt->ip_to_hex_buf[i] = out_packet_0[i];
					}
					address.addr[0]=0x00;
					address.addr[1]=0x00;
					address.addr[2]=0x00;
					address.addr[3]=0x00;
					address.addr[4]=0x00;
					address.addr[5]=0x00;
					address.addr[6]=0x00;
					address.addr[7]=0x00;
					ipEvt->localdest = address;
					ipEvt->localdest.used = 0x00;
					
					ipEvt->bufferDataLen = LENGTH_PACKET_1;
					//printf("BufferDataLen %i\n", ipEvt->bufferDataLen);
					QF_publish((QEvent*)ipEvt);	/* publish the event */
				} else if(bps_checkButton(2) == 1){
					printf("IP -> Sending IPv6 Packet #2\r\n");	
					/* send the event to the SendAO */
					
					ipEvt = Q_NEW(HexOPanSendEvt, NEW_IP_PACKET);
					
					for(i = 0; i < LENGTH_PACKET_2; i++){
						ipEvt->ip_to_hex_buf[i] = out_packet_1[i];
					}
					address.addr[0]=0x00;
					address.addr[1]=0x00;
					address.addr[2]=0x00;
					address.addr[3]=0x00;
					address.addr[4]=0x00;
					address.addr[5]=0x00;
					address.addr[6]=0x00;
					address.addr[7]=0x00;
					ipEvt->localdest = address;
					ipEvt->localdest.used = 0x00;
					
					ipEvt->bufferDataLen = LENGTH_PACKET_2;
			//printf("BufferDataLen %i\n", ipEvt->bufferDataLen);
					QF_publish((QEvent*)ipEvt);	/* publish the event */
				}
//				} else {
//					printf("\nBaseAO:	Invalid command...\r\n");
//				}
//			}
			
			if (  ((BaseTimEvt *)e)->clk_ctr >= 25 ){
			  //static QEvent const SerDisplayEvt = { SER_DISPLAY_SIG, 0};
				QEvent* SerDisplayEvt = Q_NEW(QEvent, SER_DISPLAY_SIG);	/* get a new event */
			  ((BaseTimEvt *)e)->clk_ctr =0;
				//QActive_postFIFO((QActive *)me, &SerDisplayEvt);
				
				QF_publish(SerDisplayEvt);	/* publish the event */
			}
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {		
#ifdef DBG
			printf("processing-EXIT;\r\n"); 
#endif     	
		}
	}
	return Q_SUPER(&BaseAO_displaying);
}

/**********************************************************************
 * State: BAseAO_displaying
 **********************************************************************/
QState BaseAO_displaying (BaseAO *me, const QEvent* e) {
	int i;
	int k;
	int lines;
	switch ( e->sig ) {
		case Q_INIT_SIG: {  
#ifdef DBG
			printf("display-INIT;\r\n");
#endif
			return Q_TRAN(&BaseAO_processing);    
  	}
	  case Q_ENTRY_SIG: {
#ifdef DBG
			printf("display-ENTRY;\r\n");
#endif
		  return Q_HANDLED();
		} 
		/**
		 * We receive this event if the received tick count reached 
		 * the toggle value
		 */
	  case  SER_DISPLAY_SIG: {
			LED_toggle(1);
			LED_toggle(2);
				//BSP_LED_Toggle(0);
				//BSP_LED_Toggle(1);
#ifdef DBG		
			printf("Serial Display Signal Processed\r\n");
#endif
		  return Q_HANDLED(); 
	  }
		/**
		 * This Signal is received, if we received an event sent by the
		 * HexOPAN Send SM. 
		 */
		case	HEX_TO_MAC:	{
			printf("MAC -> HEX_TO_MAC \r\n");
			/* print the frames */
			lines = ((BaseReceiveEvt *)e)->len / 16;
			printf("   Packet:\n");
			for(i = 0; i < lines; i++){
				printf("   ");
				for(k = 0; k < 16; k++){
					if(((i * 16) + k) <= ((BaseReceiveEvt *)e)->len) printf("0x%2x ", ((BaseReceiveEvt *)e)->data[(i * 16) + k]);
				}
				printf("\n");
			}
			
			return Q_HANDLED();
		}
 	  case Q_EXIT_SIG: {
#ifdef DBG
			printf("display-EXIT;\r\n");	
#endif			
		}
	}
	return Q_SUPER(&BaseAO_idle);
}

/**********************************************************************
 * State: BAseAO_idle
 **********************************************************************/
QState BaseAO_idle(BaseAO *me, QEvent const *e) {
	switch (e->sig) {
		case Q_INIT_SIG: {
#ifdef DBG
			printf("idle-INIT;\r\n");
#endif
			return Q_TRAN(&BaseAO_displaying);
		}
		case Q_ENTRY_SIG: {
#ifdef DBG
			printf("idle-ENTRY;\r\n");
#endif
      return Q_HANDLED();
     }   
	}
	return Q_SUPER(&QHsm_top);
}



