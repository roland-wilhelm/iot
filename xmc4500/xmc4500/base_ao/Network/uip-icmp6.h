#ifndef __ICMP6_H__
#define __ICMP6_H__

#include "uip_ao.h"
#include "uip6.h"
// #include "uip.h"
#include "neighbor_ao.h"


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


/** \name ICMPv6 Destination Unreachable message codes*/
/** @{ */
#define ICMP6_DST_UNREACH_NOROUTE         0 /**< no route to destination */
#define ICMP6_DST_UNREACH_ADMIN	         1 /**< administratively prohibited */
#define ICMP6_DST_UNREACH_NOTNEIGHBOR     2 /**< not a neighbor(obsolete) */
#define ICMP6_DST_UNREACH_BEYONDSCOPE     2 /**< beyond scope of source address */
#define ICMP6_DST_UNREACH_ADDR	         3 /**< address unreachable */
#define ICMP6_DST_UNREACH_NOPORT          4 /**< port unreachable */
/** @} */

/** \name ICMPv6 Time Exceeded message codes*/
/** @{ */
#define ICMP6_TIME_EXCEED_TRANSIT         0 /**< ttl==0 in transit */
#define ICMP6_TIME_EXCEED_REASSEMBLY      1 /**< ttl==0 in reass */
/** @} */

/** \name ICMPv6 Parameter Problem message codes*/
/** @{ */
#define ICMP6_PARAMPROB_HEADER            0 /**< erroneous header field */
#define ICMP6_PARAMPROB_NEXTHEADER        1 /**< unrecognized next header */
#define ICMP6_PARAMPROB_OPTION            2 /**< unrecognized option */
/** @} */

/** \brief Echo Request constant part length */
#define UIP_ICMP6_ECHO_REQUEST_LEN        4

/** \brief ICMPv6 Error message constant part length */
#define UIP_ICMP6_ERROR_LEN               4

/** \brief ICMPv6 Error message constant part */
struct uip_icmp6_error{
  u32_t param;
};

/** \name ICMPv6 RFC4443 Message processing and sending */
/** @{ */
/** \
 * brief Process an echo request
 *
 * Perform a few checks, then send an Echop reply. The reply is
 * built here.
  */
void
uip_icmp6_echo_request_input(NewDataEvent * e);

void uip_icmp6_echo_request_output(uip_ipaddr_t * ipaddr);

void uip_icmp6_echo_request_output_to_neighbor(Neighbor_AO * neighbor);

void uip_icmp6_echo_reply_input(NewDataEvent * e);

/**
 * \brief Send an icmpv6 error message
 * \param type type of the Error message
 * \param code of the error message
 * \param type 32 bit parameter of the error message, semantic depends on error
 */
void
uip_icmp6_error_output(u8_t type, u8_t code, u32_t param);

/** @} */

#endif /*__ICMP6_H__*/
/** @} */
