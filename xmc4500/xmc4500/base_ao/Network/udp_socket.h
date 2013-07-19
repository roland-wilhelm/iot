
//UDP Socket als event Handler

#ifndef __UDP_SOCKET_H__
#define __UDP_SOCKET_H__

#include "uip-conf.h"
#include "uip.h"



#define UDP_PROTOCOLL_NR 17
#define IPV6_PROTOCOLL_NR 0x86dd
#define IP_HEADER_SIZE 40

static const u16_t _HOST_IPv6_ADDR[8] = 
{ 0x2001
, 0x4dd0
, 0xfe8d
, 0xa000
, 0x0000
, 0x0000
, 0x0000
, 0x100a
};

typedef struct udp_header_tag {
	u16_t src_port, dst_port, length, chksum;
} udp_header;
#define UDP_HEADER_SIZE (4 * sizeof(u16_t))

#define DATAGRAM_PAYLOAD_SIZE 1400
typedef struct datagram_tag {
	udp_header header;
	char payload[DATAGRAM_PAYLOAD_SIZE];
} datagram;
#define DATAGRAM_SIZE (UDP_HEADER_SIZE + DATAGRAM_PAYLOAD_SIZE)

typedef struct upd_datagram_tag {
	u16_t port;
	uip_ipaddr_t address;
	u16_t len;
	datagram datagram;
} udp_datagram;
static const int UDP_DATAGRAM_SIZE = 2 * sizeof(u16_t) + sizeof(uip_ipaddr_t) + DATAGRAM_SIZE;


typedef void (*udp_observer)(void*, udp_datagram*, void*);


typedef struct udp_socket_tag {
	u16_t port;
	uip_ipaddr_t address;
	udp_observer function;
	void* arguments;
} udp_socket;
#define UDP_SOCKET_SIZE (sizeof(u16_t) + sizeof(uip_ipaddr_t) + 2 * sizeof(int))



typedef struct open_udp_socket_list_element_tag {
	udp_socket open_socket;
	int next;
} open_udp_socket_list_element;
#define OPEN_UDP_SOCKET_LIST_ELEMENT_SIZE (UDP_SOCKET_SIZE + sizeof(int))

void handle_inc_udp(NewDataEvent* frame, int udpBegin);

//UDP Datagram Functions

u16_t udp_datagram_get_payload(udp_datagram*, char*);

u16_t udp_datagram_get_payload_length(udp_datagram*);

u16_t udp_datagram_get_port(udp_datagram*);

void udp_datagram_get_address(udp_datagram*, uip_ipaddr_t*);

void udp_datagram_set_payload(udp_datagram*, char*, u16_t);

void udp_datagram_set_port(udp_datagram*, u16_t);

void udp_datagram_set_address(udp_datagram*, uip_ipaddr_t*);

//UDP Socket Functions

void udp_socket_send_datagram(udp_socket*, udp_datagram*);

udp_socket* udp_open_socket (int port, udp_observer, void*);

void udp_close_socket (udp_socket* socket);



void udp_setup_test_port(int port);

#endif /* __UDP_SOCKET_H__ */

