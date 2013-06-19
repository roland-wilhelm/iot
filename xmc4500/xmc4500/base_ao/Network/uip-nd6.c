#include "uip-nd6.h"
#include "uip6.h"
#include "uip.h"
#include <string.h>
#include <stdio.h>
#include "neighbor_ao.h"
// #include "phy_dev.h"
#include "uip_ao.h"

//! IPv6 Neighbor Discovery
/*!  
	This Module implements Methods needed for IPv6 Neighbor Discovery
*/

static Neighbor_AO nd6_neighbor_cache[UIP_CONF_ND6_MAX_NEIGHBORS];


/**
 * \brief handle incoming Data Event
 *
 * \param NewDataEvent* e
 */
void uip_nd6_io_ns_input(NewDataEvent * e)
{
	struct uip_icmp_hdr * icmp_hdr;
	struct uip_tcpip_hdr * tcpip_hdr;
	struct uip_nd6_opt_llao * opt_llao;
	unsigned int opt_llao_offset;
	uint8_t UIP_ND6_OPT_LLAO_LEN;
	struct uip_nd6_na * nd6_na;
	Neighbor_AO * neighbor;
	static QEvent const NdEvent_i = { NS_RECEIVED_SIG};
	nd6_na	= (struct uip_nd6_na *)&e->buf[uip_l2_l3_icmp_hdr_len];
	tcpip_hdr = ( struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	icmp_hdr = (struct uip_icmp_hdr *)&e->buf[uip_l2_l3_hdr_len];
	
	/**
	 * drop packet if its a multicast address or no 
	 *
	 */
	if (uip_is_multicast(nd6_na->tgtipaddr))
		return;
	
	if (0 != memcmp(&nd6_na->tgtipaddr, &uip_hostaddr, sizeof(uip_ipaddr_t)))
		return;
	//send back neighbor advertisement

	switch_eth_addr(e);
  //Remove fractional part!
  UIP_ND6_OPT_LLAO_LEN = (UIP_LLADDR_LEN + 2) - ((UIP_LLADDR_LEN + 2) % 8);

  if ((UIP_LLADDR_LEN + 2) % 8) {
	  UIP_ND6_OPT_LLAO_LEN += 8;
  }

	opt_llao = (struct uip_nd6_opt_llao *)&e->buf[uip_l2_l3_icmp_hdr_len + UIP_ND6_NA_LEN];
	
	if (0 == opt_llao->len)
		return;
	
	neighbor = uip_nd6_nbrcache_lookup(&tcpip_hdr->srcipaddr);
	if (NULL == neighbor) {
		neighbor = add_neighbor_to_cache(&tcpip_hdr->srcipaddr, (u8_t *)&opt_llao->addr, 0);
		QActive_postFIFO((QActive *)neighbor, &NdEvent_i);
	}
	
	/* IP header */
  tcpip_hdr->vtc = 0x60;
  tcpip_hdr->tcflow = 0;
  tcpip_hdr->flow = 0;
  tcpip_hdr->len[0] = 0; /* length will not be more than 255 */
  tcpip_hdr->len[1] = UIP_ICMPH_LEN + UIP_ND6_NA_LEN + UIP_ND6_OPT_LLAO_LEN;
  tcpip_hdr->proto = UIP_PROTO_ICMP6;
  tcpip_hdr->ttl = UIP_ND6_HOP_LIMIT;
	memcpy(&tcpip_hdr->destipaddr, &tcpip_hdr->srcipaddr, sizeof(uip_ipaddr_t));
	memcpy(&tcpip_hdr->srcipaddr, &uip_hostaddr, sizeof(uip_ipaddr_t));
	
	/* ICMP header */
  icmp_hdr->type = ICMP6_NA;
  icmp_hdr->icode = 0;
	
	/* NA static part */
	nd6_na->flagsreserved = UIP_ND6_NA_FLAG_SOLICITED;
  memcpy(&nd6_na->tgtipaddr, &uip_hostaddr, sizeof(uip_ipaddr_t));
	
	/* NA option: TLLAO. note that length field is in unit of 8 bytes */
  e->len = UIP_LLH_LEN + UIP_IPH_LEN + UIP_ICMPH_LEN + UIP_ND6_NA_LEN + UIP_ND6_OPT_LLAO_LEN;
  
	opt_llao_offset = uip_l2_l3_icmp_hdr_len + UIP_ND6_NA_LEN;
  opt_llao->type = UIP_ND6_OPT_TLLAO;
  opt_llao->len = UIP_ND6_OPT_LLAO_LEN >> 3; //number of bytes has to be set not bits therefore >> 3
  memcpy(&opt_llao->addr, &uip_ethaddr, UIP_LLADDR_LEN);
	
	/* padding if needed */
  memset(&opt_llao->addr + UIP_LLADDR_LEN, 0, UIP_ND6_OPT_LLAO_LEN - 2 - UIP_LLADDR_LEN);
	
	/*ICMP checksum*/
	icmp_hdr->icmpchksum = 0;
	icmp_hdr->icmpchksum = ~upper_layer_chksum6((unsigned char *) &e->buf);
	e->super.sig = SEND_DATA_SIG;
	QF_publish((QEvent *) e);
}

/**
 * \brief send an Neighbor Solicitation
 *
 * \param NewDataEvent* e
 */
void
uip_nd6_io_ns_output(uip_ipaddr_t *src, uip_ipaddr_t *dest, uip_eth_addr_t * ethaddr,  uip_ipaddr_t *tgt)
{
	struct uip_icmp_hdr * icmp_hdr;
	struct uip_tcpip_hdr * tcpip_hdr;
	struct uip_nd6_opt_llao * opt_llao;
	unsigned int opt_llao_offset;
	uint8_t UIP_ND6_OPT_LLAO_LEN;
	struct uip_nd6_na * nd6_na;
	NewDataEvent *e;
	e= Q_NEW(NewDataEvent, SEND_DATA_SIG);
	nd6_na	= (struct uip_nd6_na *)&e->buf[uip_l2_l3_icmp_hdr_len];
	tcpip_hdr = ( struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	icmp_hdr = (struct uip_icmp_hdr *)&e->buf[uip_l2_l3_hdr_len];
	

	//Remove fractional part!
	UIP_ND6_OPT_LLAO_LEN = (UIP_LLADDR_LEN + 2) - ((UIP_LLADDR_LEN + 2) % 8);

	if ((UIP_LLADDR_LEN + 2) % 8) {
		UIP_ND6_OPT_LLAO_LEN += 8;
	}
	
	set_eth_src_addr_local(e);
	if (NULL == ethaddr) {
		set_eth_dst_addr_multicast(e, tgt);
	} else {
		set_eth_dst_addr(e, ethaddr);
	}

  /* IP header fields */
  tcpip_hdr->vtc = 0x60;
  tcpip_hdr->tcflow = 0;
  tcpip_hdr->flow = 0;
  tcpip_hdr->proto = UIP_PROTO_ICMP6;
  tcpip_hdr->ttl = UIP_ND6_HOP_LIMIT;
	
	/*
   * The caller must put a valid tgt address.
   * For dest, if the caller is doing DAD or Address resolution, he sets
   * dest to NULL and we forge dest as the sollicited node mcast address
   * for tgt.
   * If the caller is sending the NS for NUD, dest is unicast and the caller
   * specifies it in the arguments
   */
  if(dest == NULL) {
    uip_create_solicited_node(tgt, &tcpip_hdr->destipaddr);
  } else {
    uip_ipaddr_copy(&tcpip_hdr->destipaddr, dest);
  }
	
	
  icmp_hdr->type = ICMP6_NS;
  icmp_hdr->icode = 0;
  //nd6_na->reserved = 0;

  /* Copy the tgt address */
  uip_ipaddr_copy((uip_ipaddr_t *)&nd6_na->tgtipaddr, tgt);

  tcpip_hdr->len[0] = 0; /* length will not be more than 255 */
	
	uip_ipaddr_copy(&tcpip_hdr->srcipaddr, src);
	

	tcpip_hdr->len[1] = UIP_ICMPH_LEN + UIP_ND6_NS_LEN + UIP_ND6_OPT_LLAO_LEN;

	e->len = UIP_LLH_LEN + UIP_IPH_LEN + UIP_ICMPH_LEN + UIP_ND6_NS_LEN + UIP_ND6_OPT_LLAO_LEN;
	opt_llao = (struct uip_nd6_opt_llao *)&e->buf[uip_l2_l3_icmp_hdr_len + UIP_ND6_NS_LEN];
	opt_llao->type = UIP_ND6_OPT_SLLAO; /* type of the option */
	/*
	 * length of the option: 2 bytes for type, length, plus the length of
	 * the L2 address. It must be in units of 8 bytes
	 */
	opt_llao->len = UIP_ND6_OPT_LLAO_LEN >> 3;
	memcpy(&opt_llao->addr, &uip_ethaddr, UIP_LLADDR_LEN);
	/* padding if needed */
	memset((void *)((&opt_llao->addr) + UIP_LLADDR_LEN), 0, UIP_ND6_OPT_LLAO_LEN - 2 - UIP_LLADDR_LEN);

  icmp_hdr->icmpchksum = 0;
  icmp_hdr->icmpchksum = ~upper_layer_chksum6((unsigned char *) &e->buf);

	//free(e);
  QF_publish((QEvent *) e);
}


/**
 * \brief Inform Neighbor_AO that we got a Neighbor Advertisement
 *
 * \param NewDataEvent* e
 */
void uip_nd6_io_na_input(NewDataEvent * e)
{
	struct uip_tcpip_hdr * tcpip_hdr;
	Neighbor_AO * neighbor;
	static QEvent const nar_sig = { NA_RECEIVED_SIG};
	struct uip_nd6_na * nd6_na;
	nd6_na	= (struct uip_nd6_na *)&e->buf[uip_l2_l3_icmp_hdr_len];
	tcpip_hdr = ( struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];

	neighbor = uip_nd6_nbrcache_lookup(&tcpip_hdr->srcipaddr);
	
	if (NULL == neighbor)
		return;
	if (0 != memcmp(&nd6_na->tgtipaddr, &neighbor->ipaddr, sizeof(uip_ipaddr_t)))
		return;
	
  QActive_postFIFO((QActive *)neighbor, &nar_sig);
}


/**
 * \brief Initialise Neighbor Discovery Cache
 *
 * \param QEvent ** evtStorage
 */
void
uip_nd6_init(const QEvent ** evtStorage)
{
	u8_t i;
	
  /* INITIALIZE NEIGHBOR DISCOVERY*/
  for(i = 0; i < UIP_CONF_ND6_MAX_NEIGHBORS; i ++) {
		Neighbor_AO_ctor(&(nd6_neighbor_cache[i]));
		QActive_start((QActive *)&(nd6_neighbor_cache[i]),       /* Neighbor AO */
								i+2,                      /* priority */
								evtStorage, Q_DIM(evtStorage),/*queue */
								(void *)0, 0,/*uC/OS-II stack */
								(QEvent *)0);         /* initialization event */
  }
}



/**
 * \brief Add New Neighbor to Neighbor Discovery Cache
 *
 * \param uip_ip6addr_t * ipaddr, u8_t * lladdr, u8_t isrouter
 */
Neighbor_AO * add_neighbor_to_cache(uip_ip6addr_t * ipaddr, u8_t * lladdr, u8_t isrouter)
{
	u8_t i;
	u8_t j;
	Neighbor_AO *neighbor = NULL;
	for(i = 0; i < UIP_CONF_ND6_MAX_NEIGHBORS; i ++) {
    if(nd6_neighbor_cache[i].used == 0) {
      break;
    }
	}
	if (i == UIP_CONF_ND6_MAX_NEIGHBORS) {
		printf("Neighbor Cache Full");
		return neighbor;
	}
	
	neighbor = &(nd6_neighbor_cache[i]);
  memcpy(&neighbor->ipaddr, ipaddr, sizeof(uip_ip6addr_t));
  if(&lladdr != NULL){
		for(j = 0; j < UIP_LLADDR_LEN; j++)
			neighbor->lladdr.addr[j] = lladdr[j];
  } else {
    memset(&(neighbor->lladdr), 0, UIP_LLADDR_LEN);
  }

  neighbor->isrouter = isrouter;
  neighbor->used = 1;
	neighbor->icmp_seq = 0x0001;
	neighbor->interface_type = ETH;
	
	return neighbor;
}


/**
 * \brief Lookup Neighbor in Neighbor Discovery Cache
 *
 * \param uip_ip6addr_t *ipaddr
 */
Neighbor_AO *
uip_nd6_nbrcache_lookup(uip_ip6addr_t *ipaddr)
{
	u8_t i;
  Neighbor_AO *neighbor = NULL;

  for(i = 0; i < UIP_CONF_ND6_MAX_NEIGHBORS; i ++) {
    if(nd6_neighbor_cache[i].used == 0) {
      continue;
    }
    if(memcmp(nd6_neighbor_cache[i].ipaddr, ipaddr, sizeof(uip_ip6addr_t)) == 0) {
      neighbor = &nd6_neighbor_cache[i];
      break;
    }
  }
  return neighbor;
}
