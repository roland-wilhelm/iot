
#include "udp_socket.h"
#include "neighbor_ao.h"
#include "uip-icmp6.h"
#include "uip-nd6.h"
#include "uip.h"
#include <string.h>
#include <stdlib.h>
#include "customHeap.h"

open_udp_socket_list_element *udp_socket_list = 0;

udp_socket* get_open_udp_socket(u16_t port)
{
	open_udp_socket_list_element *list = udp_socket_list;
	while (list)
	{
		if ((list->open_socket).port == port) return &(list->open_socket);
		list = (open_udp_socket_list_element *) list->next;
	}
	return 0;
}

void drop_udp_packet(udp_datagram* dg)
{
	/*
	Neighbor_AO* neighbor;
	static QEvent const pr_sig = { PACKET_RECEIVED_SIG};
	
	neighbor = uip_nd6_nbrcache_lookup(&tcpip_hdr->srcipaddr);
	if (NULL != neighbor)
		QActive_postFIFO((QActive *)neighbor, &pr_sig);
	*/
}

void datagram_set_payload(datagram* packet, char* data, u16_t length)
{
	//memcpy(packet->payload, data, length & 0xffff);
	int i = 0; //loop variable
	for (i = 0; i < length; i++)
	{
		packet->payload[i] = data[i];
	}
	
	length = length + UDP_HEADER_SIZE;
	packet->header.length = (((length << 8) & 0xff00) | ((length >> 8) & 0x00ff));
}

void socket_finalize_datagram(udp_socket* so, datagram* packet)
{
	packet->header.src_port = so->port;
//	packet->header.chksum = calc_chkSum(packet, uip_ip6addr, uip_ip6addr);
}

void datagram_set_dst_port(datagram* packet, u16_t port)
{
	packet->header.dst_port = port;
}

void udp_datagram_set_address(udp_datagram* dg, uip_ipaddr_t* addr)
{
	memcpy(&(dg->address), addr, sizeof(uip_ipaddr_t));
}

void ipv6_get_srcAddr(uip_ip6addr_t* target, struct uip_tcpip_hdr* ip_hdr)
{
	char* t = (char*) target;
	char* s = (char*) & ip_hdr->srcipaddr;
	int i = 0; //loop counter
	
	for (i = 0; i < 8; ++i)
	{
		t[i << 1] = s[(i <<1) + 1];
		t[(i << 1) + 1] = s[i <<1];
	}
}

u16_t udp_datagram_get_payload(udp_datagram* dg, char* c)
{
	memcpy(c, &(dg->datagram.payload), dg->len);
	return udp_datagram_get_payload_length(dg);
}

u16_t udp_datagram_get_payload_length(udp_datagram* dg)
{
	return dg->len;
}

u16_t udp_datagram_get_port(udp_datagram* dg)
{
	return dg->port;
}

void udp_datagram_get_address(udp_datagram* dg, uip_ipaddr_t* t)
{
	memcpy(t, &dg->address, sizeof(uip_ipaddr_t));
}

void simple_echo(udp_socket* so, udp_datagram* dg)
{
	//simple Echo
	//but sends the reply twice
	char dummy[UDP_DATAGRAM_SIZE];
	char* buffer;
	u16_t len;
	udp_datagram* toSend;
	uip_ipaddr_t addr;
	u16_t port;
	
	dummy[UDP_DATAGRAM_SIZE - 1] = 0;
	toSend = (udp_datagram*) dummy;
	
	port = udp_datagram_get_port(dg);
	udp_datagram_get_address(dg, &addr);
	len = udp_datagram_get_payload_length(dg);
	buffer = &(dg->datagram.payload[0]);
	
	udp_datagram_set_address(toSend, &addr);
	udp_datagram_set_port(toSend, port);
	udp_datagram_set_payload(toSend, buffer, len);
	
	udp_socket_send_datagram(so, toSend);
	
/*	udp_socket* so;
	datagram* incUdpPacket;
	udp_header* incUdp_hdr;
	uip_ip6addr_t addr;
	struct uip_tcpip_hdr* ip_hdr;
	u16_t port;
	u16_t len;
	udp_datagram* toSend;
	char dummy[UDP_DATAGRAM_SIZE];
	
	dummy[UDP_DATAGRAM_SIZE - 1] = 0;
	
	//toSend = malloc(UDP_DATAGRAM_SIZE);
	toSend = (udp_datagram*) dummy;
	
	incUdpPacket = (datagram*) &(e->buf[udp_start]);
	incUdp_hdr = &incUdpPacket->header;
	ip_hdr = (struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	ipv6_get_srcAddr(&addr, ip_hdr);
	//memcpy(&addr, &ip_hdr->srcipaddr, sizeof(uip_ipaddr_t));
	port = incUdp_hdr->dst_port;
	port = ((port << 8) & 0xff00) + ((port >> 8) & 0x00ff);
	len = incUdp_hdr->length;
	len = ((len << 8) & 0xff00) + ((len >> 8) & 0x00ff);
	so = get_open_udp_socket(port);
	
	port = incUdp_hdr->src_port;
	port = ((port << 8) & 0xff00) + ((port >> 8) & 0x00ff);
	
	if (so == 0) return;
	
	dummy[8] = (char) 0xdd;
	
	udp_datagram_set_address(toSend, &addr);
	udp_datagram_set_port(toSend, port);
	
	memcpy(&((incUdpPacket->payload)[len - UDP_HEADER_SIZE]), incUdpPacket->payload, len - UDP_HEADER_SIZE);
	
	udp_datagram_set_payload(toSend, incUdpPacket->payload, (len - UDP_HEADER_SIZE) * 2);
	
	udp_socket_send_datagram(so, toSend);
	*/
}

void reformat_ipv6_addr(uip_ip6addr_t* target, uip_ip6addr_t* source)
{
	int i = 0; //loop counter
	int size = sizeof(uip_ip6addr_t) / sizeof(u16_t);
	u16_t* t = (u16_t*) target;
	char* s = (char*) source;
	for (i = 0; i < size; i++)
	{
		t[i] = (s[i << 1] << 8) + s[(i << 1) + 1];
	}
}

void handle_inc_udp(NewDataEvent* e, int udp_start)
{
	Neighbor_AO* neighbor;
	u16_t port = 0;
	u16_t length = 0;
	uip_ipaddr_t addr;
	udp_socket* so;
	datagram* packet = (datagram *) &(e->buf)[udp_start];
	struct uip_tcpip_hdr* ip_hdr = (struct uip_tcpip_hdr*) &(e->buf[UIP_LLH_LEN]);
	char dummy[UDP_DATAGRAM_SIZE];
	udp_datagram* dg;
	dummy[UDP_DATAGRAM_SIZE - 1] = 0;
	
	dg = (udp_datagram*) dummy;
	
	port = packet->header.dst_port;
	port = ((port << 8) & 0xff00) + ((port >> 8) & 0x00ff);
	so = get_open_udp_socket(port);
	
	port = packet->header.src_port;
	port = ((port << 8) & 0xff00) + ((port >> 8) & 0x00ff);
	
	length = packet->header.length;
	length = ((length << 8) & 0xff00) + ((length >> 8) & 0x00ff);
	length = length - UDP_HEADER_SIZE;
	
	reformat_ipv6_addr(&addr, &ip_hdr->srcipaddr);
	
	neighbor = uip_nd6_nbrcache_lookup(&ip_hdr->destipaddr);
	
	if (neighbor) 
	{
		static QEvent const pr_sig = { PACKET_RECEIVED_SIG};
		QActive_postFIFO((QActive *)neighbor, &pr_sig);
	}
	
	udp_datagram_set_payload(dg, packet->payload, length);
	udp_datagram_set_port(dg, port);
	udp_datagram_set_address(dg, &addr);
	
	//QF_gc((QEvent*) e);
	
	if (so) so->function(so, dg, so->arguments);
	else drop_udp_packet(dg);
}

void udp_datagram_set_payload(udp_datagram* udp_dg, char* data, u16_t length)
{
	datagram_set_payload(&(udp_dg->datagram), data, length);
	udp_dg->len = length;
}

void udp_datagram_set_port(udp_datagram* dg, u16_t port)
{
	dg->port = port;
}

void setup_eth_hdr(NewDataEvent* e, const struct uip_eth_addr* dst, u16_t protocoll_nr)
{
	memcpy(&e->buf[0], dst, 6);
	memcpy(&e->buf[6], &uip_ethaddr, 6);
	e->buf[12] = ((char*) &protocoll_nr)[1];
	e->buf[13] = ((char*) &protocoll_nr)[0];
}

void setup_IPv6_hdr(struct uip_tcpip_hdr* ip_hdr, int payload_len, u8_t payload_prot, uip_ipaddr_t* src, uip_ipaddr_t* dst)
{
	char* d;
	char* s;
	int i = 0;
	
	ip_hdr->vtc = 0x60;
	ip_hdr->tcflow = 0;
	ip_hdr->flow = 0;
	ip_hdr->len[0] = ((u8_t*) &(payload_len))[1];
	ip_hdr->len[1] = ((u8_t*) &(payload_len))[0];
	ip_hdr->proto = (u8_t) payload_prot;
	ip_hdr->ttl = (u8_t) 128;
	
	s = (char*) src;
	d = (char*) &ip_hdr->srcipaddr;
	
	for (i = 0; i < sizeof(uip_ipaddr_t); i = i + 2)
	{
		d[i] = s[i + 1];
		d[i + 1] = s[i];
	}
	
	s = (char*) dst;
	d = (char*) &ip_hdr->destipaddr;
	
	for (i = 0; i < sizeof(uip_ipaddr_t); i = i + 2)
	{
		d[i] = s[i + 1];
		d[i + 1] = s[i];
	}
	//memcpy(&ip_hdr->srcipaddr, src, sizeof(uip_ipaddr_t));
	//memcpy(&ip_hdr->destipaddr, dst, sizeof(uip_ipaddr_t));
}

u16_t calc_UPD_chksum(uip_ipaddr_t* srcIP, uip_ipaddr_t* dstIP, const u16_t len, const datagram* dataG)
{
	long chksum = 0;
	int i = 0; // loop counter
	
	for (i = 0; i < 8; i = i + 1)
	{
		chksum = chksum + ((u16_t*) srcIP)[i];
		chksum = chksum + ((u16_t*) dstIP)[i];
	}
	chksum = chksum + UDP_PROTOCOLL_NR;
	chksum = chksum + len;
	
	//dataG must be with preset header
	for (i = 1; i < len; i = i + 2)
	{
		chksum = chksum + (((char*) dataG)[i - 1] << 8);
		chksum = chksum + (((char*) dataG)[i]);
	}

	if (len % 2 != 0) chksum = chksum + (((char*) dataG)[len - 1] << 8);
	
	while (chksum >> 16)
	{
		chksum = (chksum & 0xffff) + (chksum >> 16);
	}
	
	chksum = chksum ^ 0xffff;
	
	return (u16_t) chksum;
}

void preset_UDP_hdr(udp_header* hdr, u16_t src, u16_t dst, u16_t len)
{
	hdr->src_port = (((u8_t) src) << 8) + ((u8_t*) &src)[1];
	hdr->dst_port = (((u8_t) dst) << 8) + ((u8_t*) &dst)[1];
	hdr->length = (((u8_t) len) << 8) + ((u8_t*) &len)[1];
	hdr->chksum = 0;
}

void set_UDP_chksum(udp_header* hdr, u16_t chksum)
{
	hdr->chksum = (((u8_t) chksum) << 8) + ((u8_t*) &chksum)[1];
}

void udp_socket_send_datagram(udp_socket* so, udp_datagram* dg)
{
	NewDataEvent* e;
	struct uip_tcpip_hdr* ip_hdr;
	datagram* dataG;
	udp_header* udp_hdr;
	uip_ipaddr_t* srcIP;
	uip_ipaddr_t* dstIP;
	u16_t srcPort;
	u16_t dstPort;
	Neighbor_AO* neighbor;
	
	static QEvent const ps_sig = { PACKET_SENT_SIG};
	
	e = Q_NEW(NewDataEvent, SEND_DATA_SIG);
	e->super.sig = SEND_DATA_SIG;
	ip_hdr = (struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	dataG = (datagram*) &(e->buf[UIP_LLH_LEN + IP_HEADER_SIZE]);
	udp_hdr = &dataG->header;
	srcIP = &so->address;
	srcPort = so->port;
	dstIP = &dg->address;
	dstPort = dg->port;
	
	setup_IPv6_hdr(ip_hdr, dg->len + UDP_HEADER_SIZE, UDP_PROTOCOLL_NR, srcIP, dstIP);
	
	neighbor = uip_nd6_nbrcache_lookup(&ip_hdr->destipaddr);
	
	if (neighbor) 
	{
		setup_eth_hdr(e, &neighbor->lladdr, IPV6_PROTOCOLL_NR);
	}
	else
	{
		const struct uip_eth_addr broadcast = {0xff,0xff,0xff,0xff,0xff,0xff};
		setup_eth_hdr(e, &broadcast, IPV6_PROTOCOLL_NR);
	}
	
	memcpy(dataG->payload, dg->datagram.payload, dg->len);
	
	preset_UDP_hdr(udp_hdr, srcPort, dstPort, dg->len + UDP_HEADER_SIZE);
	set_UDP_chksum(udp_hdr, calc_UPD_chksum(srcIP, dstIP, dg->len + UDP_HEADER_SIZE, dataG));
	
	e->len = dg->len + UDP_HEADER_SIZE + UIP_IPH_LEN + ETH_HEADER_LEN;
	e->super.sig = SEND_DATA_SIG;
	
	QF_publish((QEvent *) e);
	if (neighbor) QActive_postFIFO((QActive *)neighbor, &ps_sig);
	//e->super.dynamic_++;
	//QF_gc((QEvent*) e);
}

udp_socket* udp_open_socket (int port, udp_observer f, void* args) 
{
	open_udp_socket_list_element * socketList = udp_socket_list;
	open_udp_socket_list_element * newListElement = 0;
	udp_socket* so = get_open_udp_socket(port);
	if (so) return 0;

	newListElement = cst_malloc(OPEN_UDP_SOCKET_LIST_ELEMENT_SIZE);
	newListElement->open_socket.port = port;
	newListElement->open_socket.function = f;
	newListElement->open_socket.arguments = args;
	memcpy(&newListElement->open_socket.address, _HOST_IPv6_ADDR, sizeof(uip_ipaddr_t));
	
	newListElement->next = (int) udp_socket_list;
	udp_socket_list = newListElement;
	return &(newListElement->open_socket);
}

void udp_close_socket (udp_socket* socket)
{
	open_udp_socket_list_element * last = udp_socket_list;
	open_udp_socket_list_element * current = udp_socket_list;
	
	//no open sockets
	if (udp_socket_list == 0) return;
	
	//if the first socket in list is to be closed
	if (udp_socket_list->open_socket.port == socket->port && udp_socket_list->open_socket.address == socket->address)
	{
		udp_socket_list = (open_udp_socket_list_element *) udp_socket_list->next;
		cst_free(current);
	}
	
	//if any other socket in list is to be closed
	current = (open_udp_socket_list_element *) current->next;
	while (current)
	{
		if (current->open_socket.port == socket->port && current-> open_socket.address == socket->address)
		{
			last->next = current->next;
			cst_free(current);
			return;
		}
	}
}


// for testing purposes
void udp_setup_test_port(int port)
{
	udp_open_socket(3333, &simple_echo, 0);
	udp_open_socket(19999, &simple_echo, 0);
	udp_open_socket(9999, &simple_echo, 0);
}


