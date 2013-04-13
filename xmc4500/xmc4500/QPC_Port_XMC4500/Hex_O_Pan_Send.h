/*****************************************************************************
* Model: Hex_O_Pan
* File:  Hex_O_Pan_Send.h
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
#ifndef HEX_O_PAN_H
#define HEX_O_PAN_H

#include "base_ao.h"

/**
 * maximal length of the error string
 */
#define HEXOPAN_ERROR_LEN 25

/**
 * May consider to do something like this...
 * #define SEND_BUFSIZE UIP_BUFSIZE
 * to be sure that the uip packet fits in buffer we use
 *
 * the current sice is determined by the UIP_LINK_MTU (1280) and the 
 * UIP_LLH_LEN (14) of the given reference implementation (see uipopt.h line 507)
 */
#define IP_TO_HEX_BUFSIZE 1294

/* all the other stuff we need... */
/** Rimebuf fake stuff **/
typedef struct {
	uint8_t  src[2];
	uint8_t  dest[2];
	uint8_t  data[103];	//see reference tuip.c line 87
	uint16_t datalen;
} HexOPan_sixlowpanbuf_t;

typedef union {
	uint8_t  u8[2];
} sixlowpanaddr_t;

typedef __packed struct  _lladdr_t {
  uint8_t addr[8];
	uint8_t used;
}lladdr_t;

#define USED 0xff

typedef __packed union  ip6addr_t {
  uint8_t  u8[16];			/* Initializer, must come first!!! */
  uint16_t u16[8];
}  ip6addr_t;

typedef ip6addr_t ipaddr_t;

typedef struct _ip_header{
	uint8_t vtc;
  uint8_t tcflow;
  uint16_t flow;
  uint8_t len[2];
  uint8_t proto, ttl;
  ip6addr_t srcipaddr, destipaddr;
}ip_hdr;

/* The UDP headers. */
typedef struct _udp_hdr {
  uint16_t srcport;
  uint16_t destport;
  uint16_t udplen;
  uint16_t udpchksum;
}udp_hdr;

/* The ICMP headers. */
typedef struct _icmp_hdr {
  uint8_t type, icode;
  uint16_t icmpchksum;
}icmp_hdr;

/**
 * \brief A neighbor solicitation constant part
 *
 * Possible option is: SLLAO
 */
typedef struct _nd6_ns {
  uint32_t reserved;
  ip6addr_t tgtipaddr;
}nd6_ns;

#define IP_PROTO_ICMP  1
#define IP_PROTO_TCP   6
#define IP_PROTO_UDP   17
#define IP_PROTO_ICMP6 58
#define IP_ICMP6_NS                        135  /**< Neighbor Solicitation */


/*wie macht man das am geschicktesten dass man in dem define immer noch das 
  jeweilige AO nutzt, denn da ist der sixlowpanbuf versteckt*/
#define sixlowpanbuf_dataptr(ao)       (ao).sixlowpanbuf.data
#define sixlowpanbuf_datalen(ao)       (ao).sixlowpanbuf.datalen
#define sixlowpanbuf_set_datalen(ao,x)  (ao).sixlowpanbuf.datalen = x

#define sixlowpanbuf_addr(ao, x)				 (ao).sixlowpanbuf.x
#define  sixlowpanbuf_clear(ao)        (ao).sixlowpanbuf.datalen = 0


//#define get_ip_buf(ev)		((struct ip_hdr *) &((ev).ip_to_hex_buf[(ev).hex_llh_len]))
//#define get_udp_buf(ev)		((struct uip_udp_hdr *) &((ev).ip_to_hex_buf[(ev).hex_lliph_len]))
//#define get_icmp_buf(ev)	((struct uip_icmp_hdr *) &((ev).ip_to_hex_buf[(ev).hex_icmp_len]))
//#define get_ns_buf(ev)		((struct uip_nd6_ns *) &((ev).ip_to_hex_buf[(ev).hex_12_13_icmp_hdr_len]))

/* original defines...
#define UIP_IP_BUF                ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UIP_UDP_BUF          ((struct uip_udp_hdr *)&uip_buf[UIP_LLIPH_LEN])
#define UIP_ICMP_BUF ((struct uip_icmp_hdr *)&uip_buf[UIP_LLIPH_LEN + uip_ext_len])
#define UIP_NS_BUF ((struct uip_nd6_ns *) &uip_buf[uip_12_13_icmp_hdr_len])
*/

#define SICSLOWPAN_DISPATCH_IPV6                    0x41 /* 01000001 = 65 */
#define SICSLOWPAN_DISPATCH_HC1                     0x42 /* 01000010 = 66 */
#define SICSLOWPAN_DISPATCH_IPHC                    0x03 /* 00000011 = 3 */
#define SICSLOWPAN_DISPATCH_FRAG1                   0xc0 /* 11000xxx */
#define SICSLOWPAN_DISPATCH_FRAGN                   0xe0 /* 11100xxx */

#define SICSLOWPAN_IPV6_HDR_LEN                     1    /*one byte*/
#define SICSLOWPAN_HC1_HDR_LEN                      3
#define SICSLOWPAN_HC1_HC_UDP_HDR_LEN               7
#define SICSLOWPAN_FRAG1_HDR_LEN                    4
#define SICSLOWPAN_FRAGN_HDR_LEN                    5

#define IP_IPH_LEN    40

#define MAC_MAX_PAYLOAD 102

/**
 * \brief The header for fragments
 * \note We do not define different structuresfor FRAG1
 * and FRAGN headers, which are different. For FRAG1, the
 * offset field is just not used
 */
struct sicslowpan_frag_hdr {
  uint16_t dispatch_size;
  uint16_t tag;
  uint8_t offset;
};

/* Active object class -----------------------------------------------------*/

/**
 * The main event of the sixlowPAN functionality. The initial event is sent
 * by the IPv6 stack and contains the former uipbuf with all it's data
 */
typedef struct HexOPanSendEvtTag {
    QEvent super;	/* extend the QEvent class */
	
	  /**
	   * this buffer is filled by the ip layer before the event is 
		 * send to the HexOPan SM, it contains the packet. (In the reference 
	   * implementation tis was called uip_buf...)
	   */
	  uint8_t ip_to_hex_buf[IP_TO_HEX_BUFSIZE+2];
	
		uint16_t bufferDataLen;
	  /**
	   * this is set by the ip layer. contains the destonation address
	   * of this packet. (In the reference implementation this was calles
	   * localdest and was handed to the sicslowpan_send function trough a 
	   * pointer).
	   */
	  lladdr_t localdest;
	
	  uint16_t	hex_llh_len;		//see	UIP_LLH_LEN
	
		uint16_t	hex_lliph_len;	//see UIP_LLIPH_LEN
	
		uint16_t	hex_icmp_len;		//see UIP_LLIPH_LEN + uip_ext_len
		
		uint16_t	hex_12_13_icmp_hdr_len;	//see uip_12_13_icmp_hdr_len
} HexOPanSendEvt;

/**
 *
 */
typedef struct HexOPanErrorEvtTag {
	QEvent super;	/* extend the QEvent class */
	
	/**
	 * The error message to be displayed
	 */
	uint8_t errorMsg[HEXOPAN_ERROR_LEN];
} HexOPanErrorEvt;

/** 
* Test active object
*/
typedef struct Hex_O_Pan_SendTag {
    QActive super;	/* extend the QActive class */
		/**
		 * uncomp_hdr_len is the length of the headers before compression (if HC2
	   * is used this includes the UDP header in addition to the IP header).
	   */
	  uint8_t uncomp_hdr_len;
		/**
		 * The length of the payload in the Rime buffer.
	   * The payload is what comes after the compressed or uncompressed
	   * headers (can be the IP payload if the IP header only is compressed
	   * or the UDP payload if the UDP header is also compressed).
	   */
	  uint8_t sixlowpan_payload_len;
		/**
		 * sixlowpan_hdr_len is the total length of (the processed) 6lowpan headers
     * (fragmented headers, IPv6 or HC1, HC2, and HC1 and HC2 non compressed
     * fields).	 
	   */
	  uint8_t sixlowpan_hdr_len;
	
		/**
		 * buffer we need to assemble the packets we send over mac
	   */
    HexOPan_sixlowpanbuf_t sixlowpanbuf;
		
		/**
		 * destiation address for the MAC packet
	   */
		sixlowpanaddr_t dest;
		
		/** Datagram tag to be put in the fragments I send. */
		uint16_t my_tag;

		/**
		* length of the ip packet already sent / received.
		* It includes IP and transport headers.
		*/
		uint16_t processed_ip_len;

		BaseReceiveEvt* hex_to_mac_evt;
} Hex_O_Pan_SendAO;

/* signals used by the active object */
//enum Hex_O_PAN_Send_AO_Signals {	/* all signals for the Base Active  state machine*/
//  ERROR_SIG = Q_USER_SIG,
//	NEW_IP_PACKET,
//	SET_NS_ADDRESS_SIG,
//	SET_NORMAL_ADDRESS_SIG,
//	COMPRESS_SIG,
//	SEND_PACKET_SIG,
//	START_FRAGMENTATION_SIG,
//	SET_SIZE_SIG,
//	SET_TAG_SIG,
//	SEND_SIG,
//	SEND_CONSECUTIVE_FRAME_SIG,
//	SENT_PACKET_SIG//,
	/* insert other signals here... */
	//MAX_SIG	/* the last signal (keep always last) */
//};

/* active objects constructors */
void Hex_O_Pan_Send_ctor(Hex_O_Pan_SendAO * const me);

/* opaque pointer to the active object in the application */
extern QActive* const HexOPan_Send;

static HexOPanSendEvt sendEvent;


#endif /* #ifdef HEX_O_PAN_H */
