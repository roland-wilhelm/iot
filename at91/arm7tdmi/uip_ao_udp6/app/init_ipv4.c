/* Product:  Basic Active Object Example FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */


#include "qp_port.h"                /* the port of the QEP event processor */

#include "bsp_uip_ao.h"
#include "uip_ao.h"

//-----------------------------------------------------------------------------
//         Headers
//-----------------------------------------------------------------------------

#include "uip6.h"
#include "uip-nd6.h"
#include "uip-icmp6.h"

#include "phy_dev.h"

/**** Globals */
uip_ipaddr_t uip_hostaddr, uip_draddr;
uip_eth_addr_t uip_ethaddr;

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
 

}

//void process_icmp_packet(

//void process_data_from_event(NewDataEvent *e)
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
				printf("Received an icmp6 echo reply\n");
				break;
			default:
				printf("Unknown icmp6 message type %d\n", icmp_hdr->type);
				break;
		}
		rtc=UIP_PROTO_ICMP6;
	}
	if (tcpip_hdr->proto == UIP_PROTO_UDP)
			rtc=UIP_PROTO_UDP;
	
	return (rtc);
}

#ifdef YY
void poll_phydev(void )  {

	QF_INT_LOCK(); 			// does this have any effect
        phy_dev_read();
   	QF_INT_UNLOCK(); 
}
#endif
