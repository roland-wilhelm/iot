/* Product:  Basic Active Object Example FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */


#include "qp_port.h"                /* the port of the QEP event processor */

// #include "bsp_uip_ao.h"
#include "qmbsp.h"
#include "uip_ao.h"
#include "uip_arp.h"

//-----------------------------------------------------------------------------
//         Headers
//-----------------------------------------------------------------------------

#include "uip6.h"
#include "uip.h"
#include "uip_arp.h"
#include "uip-nd6.h"
#include "uip-icmp6.h"

#include "udp_socket.h"

/// The MAC address used for demo
// static const struct uip_eth_addr MacAddress = {{0x00, 0x45, 0x56, 0x78, 0x9a, 0xbc}};
static const struct uip_eth_addr MacAddress = {{0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}};

/// The IP address used for demo (ping ...)
static const unsigned char HostIpAddress[4] = {192, 168, 178, 100};

/// Set the default router's IP address.
static const unsigned char RoutIpAddress[4] = {192, 168, 178, 1};

// The NetMask address
static const unsigned char NetMask[4] = {255, 255, 255, 0};

/// The IP address used for demo (ping ...)
/*
static const u16_t HostIPv6Address[8] = 
{ 0x2001
, 0x0db8
, 0x2530
, 0xfa13
, 0xf2de
, 0xf1ff
, 0xfe52
, 0xaa62
};

/// Set the default router's IP address.
static const u16_t RoutIPv6Address[8] = 
{ 0x2001
, 0x0db8
, 0x2530
, 0xfa13
, 0xf2de
, 0xf1ff
, 0xfe52
, 0xaa64
};*/



static const u16_t HostIPv6Address[8] = 
{ 0x2001
, 0x4dd0
, 0xfe8d
, 0xa000
, 0x0000
, 0x0000
, 0x0000
, 0x100a
};

/// Set the default router's IP address.
static const u16_t RoutIPv6Address[8] = 
{ 0x2001
, 0x4dd0
, 0xfe8d
, 0xa000
, 0xbe05
, 0x43ff
, 0xfe18
, 0x5298
};
/*
static const u16_t HostIPv6Address[8] = 
{ 0xfe80
, 0x0000
, 0x0000
, 0x0000
, 0x9847
, 0xe356
, 0xf016
, 0x76ff
};

/// Set the default router's IP address.
static const u16_t RoutIPv6Address[8] = 
{ 0x2001
, 0x4dd0
, 0xfe8d
, 0xa000
, 0xbe05
, 0x43ff
, 0xfe18
, 0x5298
};*/

/**** Globals */
//uip_ipaddr_t uip_hostaddr, uip_draddr;
// uip_eth_addr_t uip_ethaddr;

void initalise_uip(void) {
	 uip_ipaddr_t ipaddr;
	 uip_init();

 // Set the IP address of this host
    uip_ipaddr(ipaddr, HostIpAddress[0], HostIpAddress[1],
                       HostIpAddress[2], HostIpAddress[3]);
    uip_sethostaddr(ipaddr);

    uip_ipaddr(ipaddr, RoutIpAddress[0], RoutIpAddress[1],
                       RoutIpAddress[2], RoutIpAddress[3]);
    uip_setdraddr(ipaddr);

    uip_ipaddr(ipaddr, NetMask[0], NetMask[1], NetMask[2], NetMask[3]);
    uip_setnetmask(ipaddr);

	 uip_setethaddr(MacAddress);
}

void initalise_uipv6(void) {
		
	 u16_t const* ip_part = &HostIPv6Address[0];
	 uip_ipaddr_t ipaddr;

	 uip_init();
	
 // Set the IP address of this host
    uip_ip6addr
			( ipaddr
			, ip_part[0]
			, ip_part[1]
			, ip_part[2]
			, ip_part[3]
			, ip_part[4]
			, ip_part[5]
			, ip_part[6]
			, ip_part[7]
	    );
    uip_sethostaddr(ipaddr);
	  //set Router ip address
		ip_part = &RoutIPv6Address[0];

    uip_ip6addr
			( ipaddr
			, ip_part[0]
			, ip_part[1]
			, ip_part[2]
			, ip_part[3]
			, ip_part[4]
			, ip_part[5]
			, ip_part[6]
			, ip_part[7]
	    );
    uip_setdraddr(ipaddr);

	  uip_setethaddr(MacAddress);
 
		udp_setup_test_port(9999);

}

//void process_icmp_packet(

//void process_data_from_event(NewDataEvent *e)
#ifdef DUALPROTOCOL
int  resolve_protocol_type(NewDataEvent *e)
{
	struct uip_tcpip_hdr * tcpip_hdr;
	struct uip_icmp_hdr * icmp_hdr;
	int rtc;
	tcpip_hdr = ( struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	
	
	//only process IPV6 Packets
	if (IP_VERSION_V6 != tcpip_hdr->vtc)
		return ( IP_VERSION_NOT_SUPPORTED);
	
	
	if ( !uip_is_multicast(tcpip_hdr->destipaddr) &&
			 !uip_is_hostaddr(&tcpip_hdr->destipaddr) ) {
		e->super.sig = SEND_DATA_SIG;
		QF_publish((QEvent *) e);
		return ( IP_MULI_CAST_CHECK );
	}
	
	//if not multicast and not for my interfaces
		//find target interface through prefix
	//send to

	if (tcpip_hdr->proto == UIP_PROTO_ICMP6) {
		icmp_hdr = (struct uip_icmp_hdr *)&e->buf[uip_l2_l3_hdr_len];
		switch(icmp_hdr->type) {
			case ICMP6_NS:
				uip_nd6_io_ns_input((NewDataEvent *)e);
				break;
			case ICMP6_NA:
				uip_nd6_io_na_input((NewDataEvent *) e);
				break;
			case ICMP6_RA:
				//uip_nd6_io_ra_input();
				break;
			case ICMP6_RS:
				//uip_nd6_io_rs_input();
				break;
			case ICMP6_ECHO_REQUEST:
				uip_icmp6_echo_request_input((NewDataEvent *)e);
				break;
			case ICMP6_ECHO_REPLY:
				/** \note We don't implement any application callback for now */
			  uip_icmp6_echo_reply_input((NewDataEvent *)e);
				//printf("Received an icmp6 echo reply\n");
				break;
			default:
				// printf("Unknown icmp6 message type %d\n", icmp_hdr->type);
				break;
		}
		rtc=UIP_PROTO_ICMP6;
	}
	if (tcpip_hdr->proto == UIP_PROTO_UDP)
	{
			handle_inc_udp(e, uip_l2_l3_hdr_len);
			rtc=UIP_PROTO_UDP;
	}
	
	return (rtc);
}
#endif

#ifdef YY
void poll_phydev(void )  {

	QF_INT_LOCK(); 			// does this have any effect
        phy_dev_read();
   	QF_INT_UNLOCK(); 
}
#endif
