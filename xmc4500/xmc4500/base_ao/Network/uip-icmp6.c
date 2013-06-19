#include "uip-icmp6.h"
#include "uip-nd6.h"
#include <string.h>

// #include "phy_dev.h"
#include "neighbor_ao.h"

//! uip-icmp6
/*!  
	This Module handles incoming and outgoing ICMPv6 Packets
*/

/**
 * \brief handle incoming echo request
 *
 * \param the incoming NewDataEvent
 */
void uip_icmp6_echo_request_input(NewDataEvent * e)
{
	struct uip_icmp_hdr * icmp_hdr;
	struct uip_tcpip_hdr * tcpip_hdr;
	Neighbor_AO * neighbor;
	static QEvent const pr_sig = { PACKET_RECEIVED_SIG};
	static QEvent const ps_sig = { PACKET_SENT_SIG};
	tcpip_hdr = ( struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	icmp_hdr = (struct uip_icmp_hdr *)&e->buf[uip_l2_l3_hdr_len];
	
	neighbor = uip_nd6_nbrcache_lookup(&tcpip_hdr->srcipaddr);
	if (NULL != neighbor)
		QActive_postFIFO((QActive *)neighbor, &pr_sig);
	
	switch_eth_addr(e);
	
	memcpy(&tcpip_hdr->destipaddr, &tcpip_hdr->srcipaddr, sizeof(uip_ipaddr_t));
	memcpy(&tcpip_hdr->srcipaddr, &uip_hostaddr, sizeof(uip_ipaddr_t));
	icmp_hdr->type = ICMP6_ECHO_REPLY;
  icmp_hdr->icode = 0;
  icmp_hdr->icmpchksum = 0;
  icmp_hdr->icmpchksum = ~upper_layer_chksum6((unsigned char *) &e->buf);
	e->super.sig = SEND_DATA_SIG;
	QF_publish((QEvent *) e);
	QActive_postFIFO((QActive *)neighbor, &ps_sig);
}

/**
 * \brief Get Neighbor_AO by IP Address and send an ICMPv6 Echo Request
 * 
 * \param destination ip address
 */
void uip_icmp6_echo_request_output(uip_ipaddr_t * dst)
{
	Neighbor_AO * neighbor;
	neighbor = uip_nd6_nbrcache_lookup(dst);
	if (NULL != neighbor)
		uip_icmp6_echo_request_output_to_neighbor(neighbor);
}

/**
 * \brief Send an ICMPv6 Echo Request to Neighbor
 * 
 * \param Destination Neighbor_AO
 */
void uip_icmp6_echo_request_output_to_neighbor(Neighbor_AO * neighbor)
{
	NewDataEvent *e;
	struct uip_icmpip_hdr * icmpip_hdr;
	static QEvent const ps_sig = { PACKET_SENT_SIG};
	e= Q_NEW(NewDataEvent, SEND_DATA_SIG);
	icmpip_hdr = ( struct uip_icmpip_hdr *) &e->buf[UIP_LLH_LEN];

	
	set_eth_src_addr_local(e);
	set_eth_dst_addr(e, &neighbor->lladdr);
	
	/* IP header fields */
  icmpip_hdr->vtc = 0x60;
  icmpip_hdr->tcf = 0;
  icmpip_hdr->flow = 0;
  icmpip_hdr->proto = UIP_PROTO_ICMP6;
  icmpip_hdr->ttl = UIP_ND6_HOP_LIMIT;
	
	memcpy(&icmpip_hdr->destipaddr, &neighbor->ipaddr, sizeof(uip_ipaddr_t));
	memcpy(&icmpip_hdr->srcipaddr, &uip_hostaddr, sizeof(uip_ipaddr_t));
	
	icmpip_hdr->len[0] = 0; /* length will not be more than 255 */
	icmpip_hdr->len[1] = UIP_ICMPH_LEN + UIP_ICMP_QUENCH_LEN+ 32;
	
	e->len = UIP_LLH_LEN + UIP_IPH_LEN + UIP_ICMPH_LEN + UIP_ICMP_QUENCH_LEN + 32;
	icmpip_hdr->type = ICMP6_ECHO_REQUEST;
  icmpip_hdr->icode = 0;
	//ICMP QUENCH
	icmpip_hdr->id = htons(0x0002);
	icmpip_hdr->seq = htons(neighbor->icmp_seq);
	neighbor->icmp_seq++;
	
  icmpip_hdr->icmpchksum = 0;
  icmpip_hdr->icmpchksum = ~upper_layer_chksum6((unsigned char *) &e->buf);

	QF_publish((QEvent *) e);
	QActive_postFIFO((QActive *)neighbor, &ps_sig);
}

/**
 * \brief Reply incoming ICMPv6 Echo Request with an Echo Reply
 * 
 * \param incoming NewDataEvent
 */
void uip_icmp6_echo_reply_input(NewDataEvent * e)
{
	Neighbor_AO * neighbor;
	struct uip_icmpip_hdr * icmpip_hdr;
	static QEvent const icmpr_sig = { ICMPV6_ECHO_REPLY_SIG};
	icmpip_hdr = ( struct uip_icmpip_hdr *) &e->buf[UIP_LLH_LEN];
	
	neighbor = uip_nd6_nbrcache_lookup(&icmpip_hdr->srcipaddr);
	if (NULL != neighbor)
		QActive_postFIFO((QActive *)neighbor, &icmpr_sig);
}
