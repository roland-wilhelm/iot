#ifndef __UIP_ND6_H__
#define __UIP_ND6_H__

#include "uip_ao.h"
#include "uip-conf.h"
#include "neighbor_ao.h"


/** \brief HOP LIMIT to be used when sending ND messages (255) */
#define UIP_ND6_HOP_LIMIT               255
/** \brief INFINITE lifetime */
#define UIP_ND6_INFINITE_LIFETIME       0xFFFFFFFF
/** @} */

/** \name ICMPv6 message types */
/** @{ */
#define ICMP6_DST_UNREACH                 1	/**< dest unreachable */
#define ICMP6_PACKET_TOO_BIG	            2	/**< packet too big */
#define ICMP6_TIME_EXCEEDED	            3	/**< time exceeded */
#define ICMP6_PARAM_PROB	               4	/**< ip6 header bad */
#define ICMP6_ECHO_REQUEST              128  /**< Echo request */
#define ICMP6_ECHO_REPLY                129  /**< Echo reply */

#define ICMP6_RS                        133  /**< Router Solicitation */
#define ICMP6_RA                        134  /**< Router Advertisement */
#define ICMP6_NS                        135  /**< Neighbor Solicitation */
#define ICMP6_NA                        136  /**< Neighbor advertisement */
#define ICMP6_REDIRECT                  137  /**< Redirect */
/** @} */


/** \name ND6 option length in bytes */
/** @{ */
#define UIP_ND6_OPT_HDR_LEN            2
#define UIP_ND6_OPT_PREFIX_INFO_LEN    32
#define UIP_ND6_OPT_MTU_LEN            8


/** \name ND6 option types */
/** @{ */
#define UIP_ND6_OPT_SLLAO               1
#define UIP_ND6_OPT_TLLAO               2
#define UIP_ND6_OPT_PREFIX_INFO         3
#define UIP_ND6_OPT_REDIRECTED_HDR      4
#define UIP_ND6_OPT_MTU                 5
/** @} */

/** \name Neighbor Advertisement flags masks */
/** @{ */
#define UIP_ND6_NA_FLAG_ROUTER          0x80
#define UIP_ND6_NA_FLAG_SOLICITED       0x40
#define UIP_ND6_NA_FLAG_OVERRIDE        0x20
/** @} */

/** \name ND6 message length (excluding options) */
/** @{ */
#define UIP_ND6_NA_LEN                  20
#define UIP_ND6_NS_LEN                  20
#define UIP_ND6_RA_LEN                  12
#define UIP_ND6_RS_LEN                  4
/** @} */

#define UIP_CONF_ND6_MAX_NEIGHBORS 2
#define UIP_ND6_REACHABLE_TIME 100
#define ND6_DELAY_STATE_TIMEOUT 50000 //ticks

/*------------------------------------------------------------------*/


/**
 * \brief A neighbor solicitation constant part
 *
 * Possible option is: SLLAO
 */
struct uip_nd6_ns {
  u32_t reserved;
  uip_ipaddr_t tgtipaddr;
};

/** \brief ND option: both TLLAO and SLLAO */
struct uip_nd6_opt_llao {
  u8_t type;
  u8_t len;
  u8_t addr[6];
};

/**
 * \brief A neighbor advertisement constant part.
 *
 * Possible option is: TLLAO
 */
struct uip_nd6_na {
  u8_t flagsreserved;
  u8_t reserved[3];
  uip_ipaddr_t tgtipaddr;
};

void uip_nd6_io_ns_input(NewDataEvent * e);

void uip_nd6_io_ns_output(uip_ipaddr_t *src, uip_ipaddr_t *dest, uip_eth_addr_t * ethaddr,  uip_ipaddr_t *tgt);

void uip_nd6_io_na_input(NewDataEvent * e);

Neighbor_AO * add_neighbor_to_cache(uip_ip6addr_t * ipaddr, u8_t * lladdr, u8_t isrouter);

void uip_nd6_init(const QEvent ** evtStorage);

Neighbor_AO * uip_nd6_nbrcache_lookup(uip_ip6addr_t *ipaddr);

#endif  /* __UIP_ND6_H__ */
