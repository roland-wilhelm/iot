/*****************************************************************************
* Model: Hex_O_Pan
* File:  Hex_O_Pan_Send.c
*
* Hochschule Muenchen: Advanced Embedded Systems
* 
* AO implementation of the Hex_O_PAM send functionality
* 
* Group:	- Maurus Kohlmaier
*					- Franziskus Hillreiner
*					- Karl Wallner
*					- Hannes Bergler
*					- Matthias Becker
*****************************************************************************/
#include "qp_port.h"
#include "Hex_O_Pan_Send.h"
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "base_ao.h"

/* define DEBUG_MSG to activate all the serial debug output */
#define DEBUG_MSG

#ifdef DEBUG_MSG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) (void* )0
#endif

/* Makro so it's easy to change the signal of a given event (has to be a HexOPanSendEvt!) */
#define SET_SIGNAL(event, signal)	((HexOPanSendEvt*)event)->super.sig = signal

#define SIXLOWPAN_FRAG_BUF               ((struct sicslowpan_frag_hdr *)me->sixlowpanbuf.data)


/* local objects */
static Hex_O_Pan_SendAO l_SendAO;   /* the sole instance of the Hex_O_Pan_Send active object */

/* Public-scope objects */
QActive * const HexOPan_Send = (QActive *) &l_SendAO;  /* opaque pointer */

/* protected: */
static QState Hex_O_Pan_Send_initial(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_top(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_ReadyForPacket(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_NSAddress(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_NormalAddress(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_Compress(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_SendPacket(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_SendFrag1(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_SendFragN(Hex_O_Pan_SendAO * const me, const QEvent* e);
static QState Hex_O_Pan_Send_Solo(Hex_O_Pan_SendAO * const me, const QEvent* e);

/**
 * Former Makros, now functions. used to get the pointer to the 
 * specific parts of the data we receive from the IP stack.
 *
 * Might be transformed back to makros at a later time...
 */
ip_hdr * get_ip_buf(HexOPanSendEvt* ev);
udp_hdr* get_udp_buf(HexOPanSendEvt* ev);
icmp_hdr* get_icmp_buf(HexOPanSendEvt* ev);
nd6_ns* get_ns_buf(HexOPanSendEvt* ev);

/* Active object definition */

/**
 * Constructor of the HexOPan Send Active Object
 * The initial state is set here...
 */
void Hex_O_Pan_Send_ctor(Hex_O_Pan_SendAO * const me) {
	PRINTF("Hex_O_Pan_ctor...\n");
	QActive_ctor(&me->super, (QStateHandler)&Hex_O_Pan_Send_initial);	/* set the initial state */
}

/**
 * Initial state of the active object 
 * We have nothing to do here, so we execute a transition to the 
 * top state of the SM.
 */
static QState Hex_O_Pan_Send_initial(Hex_O_Pan_SendAO * const me, const QEvent* e) {
	(void)e;               /* avoid compiler warning about unused parameter */
	
	/* subscribe to all events we use */
	QActive_subscribe((QActive *)me, ERROR_SIG);
	QActive_subscribe((QActive *)me, NEW_IP_PACKET);
	return Q_TRAN(&Hex_O_Pan_Send_top);
}

/**
 * Top State of the HSM
 * All errors are handled here (it's the only state were the errors are handled)
 */
static QState Hex_O_Pan_Send_top(Hex_O_Pan_SendAO * const me, const QEvent* e) {

	switch (e->sig) {
		/* @(/2/0/1/1/0) */
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_top -> Q_INIT_SIG\n");
			return Q_TRAN(&Hex_O_Pan_Send_ReadyForPacket);
		}
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_top -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
    }
    /* @(/2/0/1/1/1) */
		case ERROR_SIG: {
			PRINTF("Hex_O_Pan_Send_top -> ERROR_SIG\n");
			/* currently we just display the error message, additional cleanup actions 
			   should be done before the error signale is sent */
			PRINTF("Hex_O_Pan: ERROR -> %s\n", ((HexOPanErrorEvt *)e)->errorMsg);
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_top -> Q_EXIT_SIG\n");
			return Q_HANDLED();
    }
  }
	return Q_SUPER(&QHsm_top);	/*see if the top state can handle the event*/
}

/**
 * This state is reached if the HSM currently wait's for a new packet to process. 
 * We then decide if it's a neighbor solicitation packet or a normal one.
 */
static QState Hex_O_Pan_Send_ReadyForPacket(Hex_O_Pan_SendAO * const me, const QEvent* e) {
  HexOPanErrorEvt* errorEvt;
	
	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_ReadyForPacket -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_ReadyForPacket -> Q_ENTRY_SIG\n");
			
			/* initialize all state variables... */
			me->sixlowpan_hdr_len = 0;
			me->uncomp_hdr_len = 0;
			me->my_tag++;
			me->uncomp_hdr_len = 0;
			me->processed_ip_len = 0;
			me->sixlowpan_payload_len = 0;
			return Q_HANDLED();
		}
		case NEW_IP_PACKET: {
			PRINTF("Hex_O_Pan_Send_ReadyForPacket -> NEW_IP_PACKET\n");
			if (((HexOPanSendEvt*)e)->localdest.used == USED) {
				if ((get_ip_buf((HexOPanSendEvt*)e)->proto == IP_PROTO_ICMP6) && (get_icmp_buf((HexOPanSendEvt*)e)->type == IP_ICMP6_NS)){
					SET_SIGNAL(e, SET_NS_ADDRESS_SIG);
					QActive_postFIFO((QActive *) me, e);
					return Q_TRAN(&Hex_O_Pan_Send_NSAddress);
				} else {
					errorEvt = Q_NEW(HexOPanErrorEvt, ERROR_SIG);
					strcpy((char *)errorEvt->errorMsg, "false NS-Address");
					QF_publish((QEvent*)errorEvt);
					return Q_HANDLED();
				}
			} else {
				SET_SIGNAL(e, SET_NORMAL_ADDRESS_SIG);
				QActive_postFIFO((QActive *) me, e);
				return Q_TRAN(&Hex_O_Pan_Send_NormalAddress);
			}
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_ReadyForPacket -> Q_EXIT_SIG\n");
			return Q_HANDLED();
		}
  }
	return Q_SUPER(&Hex_O_Pan_Send_top);	/*see if the top state can handle the event*/
}

/**
 *
 */
static QState Hex_O_Pan_Send_NSAddress(Hex_O_Pan_SendAO * const me, const QEvent* e) {

	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_NSAddress -> Q_INIT_SIG\n");			
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_NSAddress -> Q_ENTRY_SIG\n");			
			return Q_HANDLED();
		}
		case COMPRESS_SIG: {
			PRINTF("Hex_O_Pan_Send_NSAddress -> COMPRESS_SIG\n");
			me->dest.u8[0] = get_ns_buf((HexOPanSendEvt*)e)->tgtipaddr.u8[14];
			me->dest.u8[1] = get_ns_buf((HexOPanSendEvt*)e)->tgtipaddr.u8[15];
			//(send signal)
			return Q_TRAN(&Hex_O_Pan_Send_Compress);
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_NSAddress -> Q_EXIT_SIG\n");			
			return Q_HANDLED();
		}
  }
	return Q_SUPER(&Hex_O_Pan_Send_top);
}

/**
 *
 */
static QState Hex_O_Pan_Send_NormalAddress(Hex_O_Pan_SendAO * const me, const QEvent* e) {
	//printf("1: The signal is: %i\r\n", e->sig);

	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_NormalAddress -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}
    /* @(/2/0/1/1/4/0) */
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_NormalAddress -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
		}
		case SET_NORMAL_ADDRESS_SIG: {
			PRINTF("Hex_O_Pan_Send_NormalAddress -> SET_NORMAL_ADDRESS_SIG\n");

			/* Set the address */
			me->dest.u8[0] = ((HexOPanSendEvt*)e)->localdest.addr[0];
			me->dest.u8[1] = ((HexOPanSendEvt*)e)->localdest.addr[1];
			
			SET_SIGNAL(e, NO_COMPRESSION_SIG);
			QActive_postFIFO((QActive *) me, e);
			return Q_TRAN(&Hex_O_Pan_Send_Compress);
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_NormalAddress -> Q_EXIT_SIG\n");
			return Q_HANDLED();
		}
  }
	return Q_SUPER(&Hex_O_Pan_Send_top);
}

/**
 *
 */
static QState Hex_O_Pan_Send_Compress(Hex_O_Pan_SendAO * const me, const QEvent* e) {

	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_Compress -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_Compress -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
		}
    /* @(/2/0/1/1/5/0) */
		case NO_COMPRESSION_SIG: {
			PRINTF("Hex_O_Pan_Send_Compress -> NO_COMPRESSION_SIG\n");
			
			me->sixlowpanbuf.data[0] = SICSLOWPAN_DISPATCH_IPV6;
			me->sixlowpan_hdr_len += SICSLOWPAN_IPV6_HDR_LEN;
			memcpy(me->sixlowpanbuf.data, ((HexOPanSendEvt *)e)->ip_to_hex_buf, IP_IPH_LEN);
			me->sixlowpan_hdr_len += IP_IPH_LEN;
			me->uncomp_hdr_len += IP_IPH_LEN;
			
			SET_SIGNAL(e, START_FRAGMENTATION_SIG);
			QActive_postFIFO((QActive *) me, e);
			return Q_TRAN(&Hex_O_Pan_Send_SendPacket);
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_Compress -> Q_EXIT_SIG\n");
			return Q_HANDLED();
		}
  }
	return Q_SUPER(&Hex_O_Pan_Send_top);
}

/**
 *
 */
static QState Hex_O_Pan_Send_SendPacket(Hex_O_Pan_SendAO * const me, const QEvent* e) {
	BaseReceiveEvt* macEvt;
	int i;
	
	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_SendPacket -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}		
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_SendPacket -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
		}
		case START_FRAGMENTATION_SIG: {
			PRINTF("Hex_O_Pan_Send_SendPacket -> START_FRAGMENTATION_SIG\n");
						
			if((((HexOPanSendEvt *)e)->bufferDataLen - me->uncomp_hdr_len) < (MAC_MAX_PAYLOAD - me->sixlowpan_hdr_len)){
				/* send at once */
				PRINTF("Hex_O_Pan_Send_SendPacket -> no fragmentation needed\n");
				SET_SIGNAL(e, SEND_SOLO_FRAME_SIG);
				QActive_postFIFO((QActive *) me, e);
				return Q_TRAN(&Hex_O_Pan_Send_Solo);
			} else {
				/* fragmentation */
				PRINTF("Hex_O_Pan_Send_SendPacket -> fragmentation needed\n");
				SET_SIGNAL(e, SEND_FIRST_FRAME_SIG);
				QActive_postFIFO((QActive *) me, e);
				return Q_TRAN(&Hex_O_Pan_Send_SendFrag1);
			}
		}
     /* @(/2/0/1/1/6/3) */
		case SEND_SIG: {
			PRINTF("Hex_O_Pan_Send_SendPacket -> SEND_SIG\n");
			
			macEvt = Q_NEW(BaseReceiveEvt, HEX_TO_MAC);
			
			for(i = 0; i < me->sixlowpanbuf.datalen; i++){ //103; i++){
				macEvt->data[i] = me->sixlowpanbuf.data[i];
			}
			macEvt->len = me->sixlowpanbuf.datalen;
			macEvt->address = (me->dest.u8[0]<<8)&(me->dest.u8[1]);
			
			QF_publish((QEvent*)macEvt);
			
			SET_SIGNAL(e, CONTINUE_SIG);	/* need to handle the possibility that more fragments have to be sent */
			QActive_postFIFO((QActive *) me, e);
			return Q_HANDLED();
    }
    /* @(/2/0/1/1/6/4) */
		case SENT_PACKET_SIG: {
			PRINTF("Hex_O_Pan_Send_SendPacket -> SENT_PACKET_SIG\n");
			return Q_TRAN(&Hex_O_Pan_Send_ReadyForPacket);
		}
  }
  return Q_SUPER(&Hex_O_Pan_Send_top);
}

/**
 *
 */
static QState Hex_O_Pan_Send_Solo(Hex_O_Pan_SendAO * const me, const QEvent* e) {

	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_Solo -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_Solo -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
		}
		case SEND_SOLO_FRAME_SIG: {
			PRINTF("Hex_O_Pan_Send_Solo -> SEND_SOLO_FRAME_SIG\n");
			
			/* copy the payload */
			memcpy((me->sixlowpanbuf.data + me->sixlowpan_hdr_len), (void *) (((HexOPanSendEvt*)e)->ip_to_hex_buf + me->uncomp_hdr_len), 
						(((HexOPanSendEvt*)e)->bufferDataLen) - me->uncomp_hdr_len);
			
			/* set the data length */
			me->sixlowpanbuf.datalen = (((HexOPanSendEvt*)e)->bufferDataLen) - me->uncomp_hdr_len + me->sixlowpan_hdr_len;
				
			/* call the send state */
			SET_SIGNAL(e, SEND_SIG);
			QActive_postFIFO((QActive *) me, e);
			return Q_HANDLED();
		}
		case CONTINUE_SIG: {
			PRINTF("Hex_O_Pan_Send_Solo -> CONTINUE_SIG\n");
			
			/* the packet was sent sucessfully so we can send the sent signal */
			SET_SIGNAL(e, SENT_PACKET_SIG);
			QActive_postFIFO((QActive *) me, e);
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_Solo -> Q_EXIT_SIG\n");
			return Q_HANDLED();
		}
  }
  return Q_SUPER(&Hex_O_Pan_Send_SendPacket);
}

/**
 *
 */
static QState Hex_O_Pan_Send_SendFrag1(Hex_O_Pan_SendAO * const me, const QEvent* e) {

	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFrag1 -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			printf("Hex_O_Pan_Send_SendFrag1 -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
		}
    /**
		 * Build the first Frame for the fragmentation
		 */
		case SEND_FIRST_FRAME_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFrag1 -> SEND_FIRST_FRAME_SIG\n");
			
			/* build the first fragment here */
			/* move the current header so we can insert the frag1 header in fron of it */
			memmove(me->sixlowpanbuf.data + SICSLOWPAN_FRAG1_HDR_LEN, me->sixlowpanbuf.data, me->sixlowpan_hdr_len);
			
			/*
				check if the length is correct! the sicslowpan documentation says thet the 
				lengths has to be in units of 8 bytes (do we do that here? (basically its just copied :)))
			*/
			SIXLOWPAN_FRAG_BUF->dispatch_size = /*htons*/((SICSLOWPAN_DISPATCH_FRAG1 << 8) | me->sixlowpanbuf.datalen);
			SIXLOWPAN_FRAG_BUF->tag = /*htons*/(me->my_tag);
			
			/* set the new header and payload length */
			me->sixlowpan_hdr_len += SICSLOWPAN_FRAG1_HDR_LEN;
			me->sixlowpan_payload_len += (MAC_MAX_PAYLOAD - me->sixlowpan_hdr_len) & 0xf8;	/* what does the oxf8 do??? */
			PRINTF("  (len %d, tag %d)\n", me->sixlowpan_payload_len, me->my_tag);
			
			/* copie the payload */
			memcpy(me->sixlowpanbuf.data + me->sixlowpan_hdr_len, (void *) ((((HexOPanSendEvt *)e)->ip_to_hex_buf) + me->uncomp_hdr_len), me->sixlowpan_payload_len);
			
			/* set the data length */
			me->sixlowpanbuf.datalen = (((HexOPanSendEvt*)e)->bufferDataLen) - me->uncomp_hdr_len + me->sixlowpan_hdr_len;
						
			/* set the processed_ip_len to what we already sent from the IP payload */
			me->processed_ip_len = me->sixlowpan_payload_len + me->uncomp_hdr_len;
			
			SET_SIGNAL(e, SEND_SIG);
			QActive_postFIFO((QActive *)me, e);
			return Q_HANDLED();
		}
		case CONTINUE_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFrag1 -> CONTINUE_SIG\n");

			/* we sent the first fragment, so there has to be another one (no need to check) */
			/* all following frames have the same sixlowpan_hdr_len and some other values are the same
         we set them here so we just have to do it once... */
			me->sixlowpan_hdr_len = SICSLOWPAN_FRAGN_HDR_LEN;
			SIXLOWPAN_FRAG_BUF->dispatch_size = /*htons*/((SICSLOWPAN_DISPATCH_FRAGN << 8) | ((HexOPanSendEvt*)e)->bufferDataLen);
			me->sixlowpan_payload_len = (MAC_MAX_PAYLOAD - me->sixlowpan_hdr_len) & 0xf8;
			
			SET_SIGNAL(e, SEND_CONSECUTIVE_FRAME_SIG);
			QActive_postFIFO((QActive *)me, e);
			return Q_TRAN(&Hex_O_Pan_Send_SendFragN);
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFrag1 -> Q_EXIT_SIG\n");
			return Q_HANDLED();
		}
  }
  return Q_SUPER(&Hex_O_Pan_Send_SendPacket);
}

/**
 *
 */
static QState Hex_O_Pan_Send_SendFragN(Hex_O_Pan_SendAO * const me, const QEvent* e) {

	switch (e->sig) {
		case Q_INIT_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFragN -> Q_INIT_SIG\n");
			return Q_HANDLED();
		}
		case Q_ENTRY_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFragN -> Q_ENTRY_SIG\n");
			return Q_HANDLED();
		}
		/**
		 * Send one of the consecutive frames
		 */
		case SEND_CONSECUTIVE_FRAME_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFragN -> SEND_CONSECUTIVE_FRAME_SIG\n");
			SIXLOWPAN_FRAG_BUF->offset = me->processed_ip_len >> 3;
			
			/* copy payload and send */
			if(((HexOPanSendEvt*)e)->bufferDataLen - me->processed_ip_len < me->sixlowpan_payload_len){
				/* last fragment! */
				PRINTF("  Last Fragment!\n");
				me->sixlowpan_payload_len = ((HexOPanSendEvt*)e)->bufferDataLen - me->processed_ip_len;
			}
			
			PRINTF("  (offset %d, len %d, tag %d)\n", me->processed_ip_len >> 3, me->sixlowpan_payload_len, me->my_tag);
			
			memcpy(me->sixlowpanbuf.data + me->sixlowpan_hdr_len, (void *) (get_ip_buf(((HexOPanSendEvt *)e)) + me->processed_ip_len), me->sixlowpan_payload_len);
			me->sixlowpanbuf.datalen = me->sixlowpan_payload_len + me->sixlowpan_hdr_len;
			
      SET_SIGNAL(e, SEND_SIG);
			QActive_postFIFO((QActive *)me, e);
			return Q_HANDLED();
    }
		case CONTINUE_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFragN -> CONTINUE_SIG\n");
			/* update the processed ip length */
			me->processed_ip_len += me->sixlowpan_hdr_len;
			
			if(((HexOPanSendEvt*)e)->bufferDataLen - me->processed_ip_len < me->sixlowpan_payload_len){
				SET_SIGNAL(e, SENT_PACKET_SIG);
				QActive_postFIFO((QActive *)me, e);
			} else {
				SET_SIGNAL(e, SEND_CONSECUTIVE_FRAME_SIG);
				QActive_postFIFO((QActive *)me, e);
			}
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			PRINTF("Hex_O_Pan_Send_SendFragN -> Q_EXIT_SIG\n");
			return Q_HANDLED();
		}
  }
  return Q_SUPER(&Hex_O_Pan_Send_SendPacket);
}

/* Helper functions */

/**
 * Function is used to get the pointer to the IP header
 * of the data in the received event
 */
ip_hdr * get_ip_buf(HexOPanSendEvt* ev){
	return (ip_hdr*)ev->ip_to_hex_buf[ev->hex_llh_len];
}

/**
 * Function is used to get the pointer to the UDP header
 * of the data in der received event
 */
udp_hdr* get_udp_buf(HexOPanSendEvt* ev){
	return (udp_hdr*)ev->ip_to_hex_buf[ev->hex_lliph_len];
}

/**
 * Function is used to get the pointer to the ICMP header 
 * of the data in the received event
 */
icmp_hdr* get_icmp_buf(HexOPanSendEvt* ev){
	return (icmp_hdr*)ev->ip_to_hex_buf[ev->hex_icmp_len];
}

/**
 * Function is used to get the pointer to the neighbor solicitation 
 * part of the data in the received event
 */
 nd6_ns* get_ns_buf(HexOPanSendEvt* ev){
	 return (nd6_ns*)ev->ip_to_hex_buf[ev->hex_12_13_icmp_hdr_len];
}


