#include "uip6.h"
#include <string.h>
#include "phy_dev.h"
#include "uip-nd6.h"

//! uip6 helper methods
/*!  
	This Module contains helper methods
*/

/*---------------------------------------------------------------------------*/

/**
 * \brief Print IPv6 Address to console
 *
 * \param uip_ip6addr_t
 */
void print_ip6_addr(uip_ip6addr_t * addr) {
	printf(" %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x ",
	((u8_t *)addr)[0],
	((u8_t *)addr)[1],
	((u8_t *)addr)[2],
	((u8_t *)addr)[3],
	((u8_t *)addr)[4],
	((u8_t *)addr)[5],
	((u8_t *)addr)[6],
	((u8_t *)addr)[7],
	((u8_t *)addr)[8],
	((u8_t *)addr)[9],
	((u8_t *)addr)[10], 
	((u8_t *)addr)[11], 
	((u8_t *)addr)[12], 
	((u8_t *)addr)[13], 
	((u8_t *)addr)[14], 
	((u8_t *)addr)[15]);
}

/*---------------------------------------------------------------------------*/
/* Methods for calculation of IP Header Checksum taken from original uip stack
	 and slightly modified to work with our implementation
*/

u16_t
htons(u16_t val)
{
  return HTONS(val);
}

void uip_init(void)
{

}

static u16_t
chksum6(u16_t sum, const u8_t *data, u16_t len)
{
  u16_t t;
  const u8_t *dataptr;
  const u8_t *last_byte;

  dataptr = data;
  last_byte = data + len - 1;
  
  while(dataptr < last_byte) {	/* At least two more bytes */
    t = (dataptr[0] << 8) + dataptr[1];
    sum += t;
    if(sum < t) {
      sum++;		/* carry */
    }
    dataptr += 2;
  }
  
  if(dataptr == last_byte) {
    t = (dataptr[0] << 8) + 0;
    sum += t;
    if(sum < t) {
      sum++;		/* carry */
    }
  }

  /* Return sum in host byte order. */
  return sum;
}



u16_t
uip6_chksum(u16_t *data, u16_t len)
{
  return htons(chksum6(0, (u8_t *)data, len));
}


u16_t
uip6_ipchksum(u16_t *data)
{
  u16_t sum;
  sum = chksum6(0, (u8_t *)data[UIP_LLH_LEN], UIP_IPH_LEN);
  return (sum == 0) ? 0xffff : htons(sum);
}

u16_t
upper_layer_chksum6(unsigned char buf[1068])
{
  u16_t upper_layer_len;
  u16_t sum;
	struct uip_tcpip_hdr * tcpip_hdr;
	tcpip_hdr = ( struct uip_tcpip_hdr *) &buf[UIP_LLH_LEN];
  
  upper_layer_len = (((u16_t)(tcpip_hdr->len[0]) << 8) + tcpip_hdr->len[1]);
  
  /* First sum pseudoheader. */
  
  /* IP protocol and length fields. This addition cannot carry. */
  sum = upper_layer_len + tcpip_hdr->proto;
  /* Sum IP source and destination addresses. */
  sum = chksum6(sum, (u8_t *)&tcpip_hdr->srcipaddr[0], 2 * sizeof(uip_ipaddr_t));

  /* Sum TCP header and data. */
  sum = chksum6(sum, &buf[UIP_IPH_LEN + UIP_LLH_LEN],
	       upper_layer_len);
    
  return (sum == 0) ? 0xffff : htons(sum);
}

/*-------------------------------------------------------------------------------*/

/**
 * \brief check if ip address is a multicast address
 *
 * \param uip_ipaddr_t a
 */
u8_t uip_is_multicast(uip_ipaddr_t a)
{
	u8_t * pb = (u8_t *) a;
	u8_t res = (pb[0] == 0xFF);
	return res;
}

/**
 * \brief Switch Eth addresses in Ethernet Header
 * 
 * \param NewDataEvent e
 */
void switch_eth_addr(NewDataEvent * e)
{
	//offset 0 = destination eth addr
	//offset 6 = source eth addr
	memcpy(&e->buf[0], &e->buf[6], 6);
	memcpy(&e->buf[6], &uip_ethaddr, 6);
}


/**
 * \brief Set Source Ethernet Address in NewDataEvent Buffer
 * 
 * \param NewDataEvent e, uip_eth_addr_t addr
 */
void set_eth_src_addr(NewDataEvent * e, uip_eth_addr_t  * addr)
{
	memcpy(&e->buf[6], addr, 6);
}


/**
 * \brief Set Destination Ethernet Address in NewDataEvent Buffer
 * 
 * \param NewDataEvent e, uip_eth_addr_t addr
 */
void set_eth_dst_addr(NewDataEvent * e, uip_eth_addr_t  * addr)
{
	memcpy(&e->buf[0], addr, 6);
}


/**
 * \brief Set Destination Multicast Ethernet Address in NewDataEvent Buffer
 * 
 * \param NewDataEvent e, uip_eth_addr_t addr
 */
void set_eth_dst_addr_multicast(NewDataEvent * e, uip_ipaddr_t * tgt)
{
	uip_eth_addr_t addr;
	u8_t * pa = (u8_t *) tgt;
	addr.addr[0] = 0x33;
	addr.addr[1] = 0x33;
	addr.addr[2] = 0xff;
	addr.addr[3] = pa[13];
	addr.addr[4] = pa[14];
	addr.addr[5] = pa[15];
	set_eth_dst_addr(e, &addr);
}


/**
 * \brief Set Local Address as Source Ethernet Address in NewDataEvent Buffer
 * 
 * \param NewDataEvent e
 */
void set_eth_src_addr_local(NewDataEvent * e)
{
	set_eth_src_addr(e, &uip_ethaddr);
}


/**
 * \brief Calculate Solicitied Node multicast address for IPv6 Neighbor Discovery
 * 				and write it to param b
 * 
 * \param NewDataEvent e, uip_ipaddr_t  b
 */
void uip_create_solicited_node(uip_ipaddr_t * a, uip_ipaddr_t *  b)    {
	u8_t * pb = (u8_t *) b;
	u8_t * pa = (u8_t *) a;
	u16_t * pb16 = (u16_t *) b;
	u16_t * pa16 = (u16_t *) a;
  pb[0] = 0xFF;                        
  pb[1] = 0x02;                        
  pb16[1] = 0;                          
  pb16[2] = 0;                          
  pb16[3] = 0;                         
  pb16[4] = 0;                          
  pb[10] = 0;                          
  pb[11] = 0x01;                       
  pb[12] = 0xFF;                       
  pb[13] = pa[13];              
  pb16[7] = pa16[7];
}


/**
 * \brief Check if given IP Adress is one of our own IP Adresses
 * 
 * \param uip_ipaddr_t  ipaddr
 */
u8_t uip_is_hostaddr(uip_ipaddr_t * ipaddr)
{
	/* \todo: search local hostaddresses 
	 * and return true if found */
	return 1;
}
