#ifndef __UIP_6_H__
#define __UIP_6_H__

#include "uip-conf.h"

//ethernet header length
#define UIP_LLH_LEN     14

/* Header sizes. */
#define UIP_IPH_LEN    40
#define UIP_UDPH_LEN    8    /* Size of UDP header */
#define UIP_TCPH_LEN   20    /* Size of TCP header */
#define UIP_ICMPH_LEN   4    /* Size of ICMP header */
#define UIP_ICMP_QUENCH_LEN 4
#define UIP_IPUDPH_LEN (UIP_UDPH_LEN + UIP_IPH_LEN)    /* Size of IP +
							  UDP
							  header */
#define UIP_IPTCPH_LEN (UIP_TCPH_LEN + UIP_IPH_LEN)    /* Size of IP +
							  TCP
							  header */
#define UIP_TCPIP_HLEN UIP_IPTCPH_LEN
#define UIP_IPICMPH_LEN (UIP_IPH_LEN + UIP_ICMPH_LEN) /* size of ICMP
                                                         + IP header */
#define UIP_LLIPH_LEN (UIP_LLH_LEN + UIP_IPH_LEN)    /* size of L2
                                                        + IP header */
																												
#define UIP_ICMP_QUENCH 4

/**
 * The sums below are quite used in ND. When used for uip_buf, we
 * include link layer length when used for uip_len, we do not, hence
 * we need values with and without LLH_LEN we do not use capital
 * letters as these values are variable
 */
#define uip_l2_l3_hdr_len (UIP_LLH_LEN + UIP_IPH_LEN)
#define uip_l2_l3_icmp_hdr_len (UIP_LLH_LEN + UIP_IPH_LEN + UIP_ICMPH_LEN)
#define uip_l3_hdr_len (UIP_IPH_LEN)
#define uip_l3_icmp_hdr_len (UIP_IPH_LEN + UIP_ICMPH_LEN )

/**
 * Representation of a 48-bit Ethernet address.
 */
struct uip_eth_addr {
  u8_t addr[6];
};

typedef struct uip_eth_addr uip_eth_addr_t;
typedef u16_t uip_ip6addr_t[8];
typedef uip_ip6addr_t uip_ipaddr_t;

/* The TCP and IP headers. */
struct uip_tcpip_hdr {
  /* IPv6 header. */
  u8_t vtc,
    tcflow;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
  
  /* TCP header. */
  u16_t srcport,
    destport;
  u8_t seqno[4],
    ackno[4],
    tcpoffset,
    flags,
    wnd[2];
  u16_t tcpchksum;
  u8_t urgp[2];
  u8_t optdata[4];
};

/* The ICMP and IP headers. */
struct uip_icmpip_hdr {
  /* IPv6 header. */
  u8_t vtc,
    tcf;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
  
  /* ICMP (echo) header. */
  u8_t type, icode;
  u16_t icmpchksum;
	u16_t id;
	u16_t seq;
  //u8_t flags, reserved1, reserved2, reserved3;
  u8_t icmp6data[16];
  u8_t options[1];
};

/* The ICMP headers. */
struct uip_icmp_hdr {
  u8_t type, icode;
  u16_t icmpchksum;
};


/* The UDP and IP headers. */
struct uip_udpip_hdr {
  /* IPv6 header. */
  u8_t vtc,
    tcf;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;

  /* UDP header. */
  u16_t srcport,
    destport;
  u16_t udplen;
  u16_t udpchksum;
};

/**** Globals */
extern uip_ipaddr_t uip_hostaddr, uip_draddr;
extern uip_eth_addr_t uip_ethaddr;

//IP Protocol Types
#define IP_VERSION_V6 0x60

#define UIP_PROTO_ICMP  1
#define UIP_PROTO_TCP   6
#define UIP_PROTO_UDP   17
#define UIP_PROTO_ICMP6 58

#define UIP_LLADDR_LEN 6
#define NUM_INTERFACES 2

/**
 * Convert 16-bit quantity from host byte order to network byte order.
 *
 * This macro is primarily used for converting constants from host
 * byte order to network byte order. For converting variables to
 * network byte order, use the htons() function instead.
 *
 * \hideinitializer
 */
#ifndef HTONS
#   if UIP_CONF_BYTE_ORDER == UIP_BIG_ENDIAN
#      define HTONS(n) (n)
#   else /* UIP_BYTE_ORDER == UIP_BIG_ENDIAN */
#      define HTONS(n) (u16_t)((((u16_t) (n)) << 8) | (((u16_t) (n)) >> 8))
#   endif /* UIP_BYTE_ORDER == UIP_BIG_ENDIAN */
#else
#error "HTONS already defined!"
#endif /* HTONS */

/**
 * Convert 16-bit quantity from host byte order to network byte order.
 *
 * This function is primarily used for converting variables from host
 * byte order to network byte order. For converting constants to
 * network byte order, use the HTONS() macro instead.
 */
#ifndef htons
u16_t htons(u16_t val);
#endif /* htons */
#ifndef ntohs
#define ntohs htons
#endif

/**
 * Construct an IPv6 address from eight 16-bit words.
 *
 * This function constructs an IPv6 address.
 *
 * \hideinitializer
 */
#define uip_ip6addr(addr, addr0,addr1,addr2,addr3,addr4,addr5,addr6,addr7) do { \
                     ((u16_t *)(addr))[0] = HTONS((addr0)); \
                     ((u16_t *)(addr))[1] = HTONS((addr1)); \
                     ((u16_t *)(addr))[2] = HTONS((addr2)); \
                     ((u16_t *)(addr))[3] = HTONS((addr3)); \
                     ((u16_t *)(addr))[4] = HTONS((addr4)); \
                     ((u16_t *)(addr))[5] = HTONS((addr5)); \
                     ((u16_t *)(addr))[6] = HTONS((addr6)); \
                     ((u16_t *)(addr))[7] = HTONS((addr7)); \
                  } while(0)

/**
 * Copy an IP address to another IP address.
 *
 * Copies an IP address from one place to another.
 *
 * Example:
 \code
 uip_ipaddr_copy(&ipaddr2, &ipaddr1);
 \endcode
 *
 * \param dest The destination for the copy.
 * \param src The source from where to copy.
 *
 * \hideinitializer
 */
#define uip_ipaddr_copy(dest, src) memcpy(dest, src, sizeof(uip_ip6addr_t))


/**
 * Set the IP address of this host.
 *
 * The IP address is represented as a 4-byte array where the first
 * octet of the IP address is put in the first member of the 4-byte
 * array.
 *
 * Example:
 \code

 uip_ipaddr_t addr;

 uip_ipaddr(&addr, 192,168,1,2);
 uip_sethostaddr(&addr);
 
 \endcode
 * \param addr A pointer to an IP address of type uip_ipaddr_t;
 *
 * \sa uip_ipaddr()
 *
 * \hideinitializer
 */
#define uip_sethostaddr(addr) uip_ipaddr_copy(uip_hostaddr, (addr))

/**
 * Set the default router's IP address.
 *
 * \param addr A pointer to a uip_ipaddr_t variable containing the IP
 * address of the default router.
 *
 * \sa uip_ipaddr()
 *
 * \hideinitializer
 */
#define uip_setdraddr(addr) uip_ipaddr_copy(uip_draddr, (addr))

/**
 * Specifiy the Ethernet MAC address.
 *
 * The ARP code needs to know the MAC address of the Ethernet card in
 * order to be able to respond to ARP queries and to generate working
 * Ethernet headers.
 *
 * \note This macro only specifies the Ethernet MAC address to the ARP
 * code. It cannot be used to change the MAC address of the Ethernet
 * card.
 *
 * \param eaddr A pointer to a struct uip_eth_addr containing the
 * Ethernet MAC address of the Ethernet card.
 *
 * \hideinitializer
 */
#define uip_setethaddr(eaddr) do {uip_ethaddr.addr[0] = eaddr.addr[0]; \
                              uip_ethaddr.addr[1] = eaddr.addr[1];\
                              uip_ethaddr.addr[2] = eaddr.addr[2];\
                              uip_ethaddr.addr[3] = eaddr.addr[3];\
                              uip_ethaddr.addr[4] = eaddr.addr[4];\
                              uip_ethaddr.addr[5] = eaddr.addr[5];} while(0)



/****** HELPERS *******/

/**
 * \brief Is IPv6 addresss a the unspecified address
 * a is of type uip_ipaddr_t
 */
#define uip_is_addr_unspecified(a)               \
  ((((a)->u16[0]) == 0) &&                       \
   (((a)->u16[1]) == 0) &&                       \
   (((a)->u16[2]) == 0) &&                       \
   (((a)->u16[3]) == 0) &&                       \
   (((a)->u16[4]) == 0) &&                       \
   (((a)->u16[5]) == 0) &&                       \
   (((a)->u16[6]) == 0) &&                       \
   (((a)->u16[7]) == 0))

/** \brief Is IPv6 addresss a the link local all-nodes multicast address */
#define uip_is_addr_linklocal_allnodes_mcast(a)     \
  ((((a)->u8[0]) == 0xff) &&                        \
   (((a)->u8[1]) == 0x02) &&                        \
   (((a)->u16[1]) == 0) &&                          \
   (((a)->u16[2]) == 0) &&                          \
   (((a)->u16[3]) == 0) &&                          \
   (((a)->u16[4]) == 0) &&                          \
   (((a)->u16[5]) == 0) &&                          \
   (((a)->u16[6]) == 0) &&                          \
   (((a)->u8[14]) == 0) &&                          \
   (((a)->u8[15]) == 0x01))

/** \brief Is IPv6 addresss a the link local all-routers multicast address */
#define uip_is_addr_linklocal_allrouters_mcast(a)     \
  ((((a)->u8[0]) == 0xff) &&                        \
   (((a)->u8[1]) == 0x02) &&                        \
   (((a)->u16[1]) == 0) &&                          \
   (((a)->u16[2]) == 0) &&                          \
   (((a)->u16[3]) == 0) &&                          \
   (((a)->u16[4]) == 0) &&                          \
   (((a)->u16[5]) == 0) &&                          \
   (((a)->u16[6]) == 0) &&                          \
   (((a)->u8[14]) == 0) &&                          \
   (((a)->u8[15]) == 0x02))

/** \brief set IP address a to unspecified */
#define uip_create_unspecified(a) uip_ip6addr(a, 0, 0, 0, 0, 0, 0, 0, 0)

/** \brief set IP address a to the link local all-nodes multicast address */
#define uip_create_linklocal_allnodes_mcast(a) uip_ip6addr(a, 0xff02, 0, 0, 0, 0, 0, 0, 0x0001)

/** \brief set IP address a to the link local all-routers multicast address */
#define uip_create_linklocal_allrouters_mcast(a) uip_ip6addr(a, 0xff02, 0, 0, 0, 0, 0, 0, 0x0002)

/**
 * \brief  is addr (a) a solicited node multicast address, see RFC3513
 *  a is of type uip_ipaddr_t*
 */
#define uip_is_addr_solicited_node(a)           \
  ((((a)->u8[0]) == 0xFF) &&                     \
  (((a)->u8[1]) == 0x02) &&                     \
  (((a)->u16[1]) == 0) &&                       \
  (((a)->u16[2]) == 0) &&                       \
  (((a)->u16[3]) == 0) &&                       \
  (((a)->u16[4]) == 0) &&                       \
  (((a)->u16[5]) == 1) &&                       \
  (((a)->u8[12]) == 0xFF))


/**
 * \brief is addr (a) a link local unicast address, see RFC3513
 *  i.e. is (a) on prefix FE80::/10
 *  a is of type uip_ipaddr_t*
 */
#define uip_is_addr_link_local(a) \
  ((((a)->u8[0]) == 0xFE) && \
  (((a)->u8[1]) == 0x80))

#define uip_is_addr_multicast(a) \
  (((a)->u8[0]) == 0xFF)

/**
 * \brief was addr (a) forged based on the mac address m
 * a type is uip_ipaddr_t
 * m type is uiplladdr_t
 */

/* Set this based on what size 6lowpan layer is using */
#define uip_is_addr_mac_addr_based uip_is_addr_mac16_addr_based

#define uip_is_addr_mac64_addr_based(a, m) \
  ((((a)->u8[8])  == (((m)->addr[0]) ^ 0x02)) &&   \
   (((a)->u8[9])  == (m)->addr[1]) &&            \
   (((a)->u8[10]) == (m)->addr[2]) &&            \
   (((a)->u8[11]) == (m)->addr[3]) &&            \
   (((a)->u8[12]) == (m)->addr[4]) &&            \
   (((a)->u8[13]) == (m)->addr[5]) &&            \
   (((a)->u8[14]) == (m)->addr[6]) &&            \
   (((a)->u8[15]) == (m)->addr[7]))

#define uip_is_addr_mac48_addr_based(a, m)\
	  ((((a)->u8[8])  == (((m)->addr[0]) ^ 0x02)) &&   \
	   (((a)->u8[9])  == (m)->addr[1]) &&            \
	   (((a)->u8[10]) == (m)->addr[2]) &&            \
	   (((a)->u8[11]) == 0xff) &&            \
	   (((a)->u8[12]) == 0xfe) &&            \
	   (((a)->u8[13]) == (m)->addr[3]) &&            \
	   (((a)->u8[14]) == (m)->addr[4]) &&            \
	   (((a)->u8[15]) == (m)->addr[5]))

#define uip_is_addr_mac16_addr_based(a, m)\
	  ((((a)->u8[8])  == ((tuip_panid[0]) | 0x02)) &&   \
	   (((a)->u8[9])  == tuip_panid[1]) &&            \
	   (((a)->u8[10]) == 0) &&            \
	   (((a)->u8[11]) == 0xff) &&            \
	   (((a)->u8[12]) == 0xfe) &&            \
	   (((a)->u8[13]) == 0) &&            \
	   (((a)->u8[14]) == (m)->addr[0]) &&            \
	   (((a)->u8[15]) == (m)->addr[1]))

/**
 * \brief is address a multicast address, see RFC 3513
 * a is of type uip_ipaddr_t*
 * */
#define uip_is_addr_mcast(a)                    \
  (((a)->u8[0]) == 0xFF)

/**
 * \brief is group-id of multicast address a
 * the all nodes group-id
 */
#define uip_is_mcast_group_id_all_nodes(a) \
  ((((a)->u16[1])  == 0) &&                 \
   (((a)->u16[2])  == 0) &&                 \
   (((a)->u16[3])  == 0) &&                 \
   (((a)->u16[4])  == 0) &&                 \
   (((a)->u16[5])  == 0) &&                 \
   (((a)->u16[6])  == 0) &&                 \
   (((a)->u8[14])  == 0) &&                 \
   (((a)->u8[15])  == 1))

/**
 * \brief is group-id of multicast address a
 * the all routers group-id
 */
#define uip_is_mcast_group_id_all_routers(a) \
  ((((a)->u16[1])  == 0) &&                 \
   (((a)->u16[2])  == 0) &&                 \
   (((a)->u16[3])  == 0) &&                 \
   (((a)->u16[4])  == 0) &&                 \
   (((a)->u16[5])  == 0) &&                 \
   (((a)->u16[6])  == 0) &&                 \
   (((a)->u8[14])  == 0) &&                 \
   (((a)->u8[15])  == 2))
	 
	 
/***** END HELPERS *********/

/**
 * uIP initialization function.
 *
 * This function should be called at boot up to initilize the uIP
 * TCP/IP stack.
 */
void uip_init(void);

u8_t uip_is_multicast(uip_ipaddr_t a);

u16_t upper_layer_chksum6(unsigned char buf[1068]);

void switch_eth_addr(NewDataEvent * e);

void set_eth_src_addr(NewDataEvent * e, uip_eth_addr_t  * addr);

void set_eth_dst_addr(NewDataEvent * e, uip_eth_addr_t  * addr);

void set_eth_dst_addr_multicast(NewDataEvent * e, uip_ipaddr_t * tgt);

void set_eth_src_addr_local(NewDataEvent * e);

void print_ip6_addr(uip_ip6addr_t * addr);

/**
 * \brief put in b the solicited node address corresponding to address a
 * both a and b are of type uip_ipaddr_t*
 * \param uip_addr_t * a
 * \param uip_addr_t * b
 */
void uip_create_solicited_node(uip_ipaddr_t * a, uip_ipaddr_t * b);

/**
 * \brief Check if address is configured on local host
 * \param uip_addr_t * ipaddr
 */
u8_t uip_is_hostaddr(uip_ipaddr_t * ipaddr);

#endif  /* __UIP_6_H__ */
