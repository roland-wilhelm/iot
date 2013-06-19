
#include "udp_socket.h"
#include "neighbor_ao.h"
#include "uip-icmp6.h"
#include "uip-nd6.h"
#include "uip.h"
#include <string.h>
#include <stdlib.h>

unsigned int MY_HEAP[MY_HEAP_SIZE / sizeof(int)] = {(MY_HEAP_SIZE / sizeof(int))}; //4k

void* my_malloc(unsigned int i)
{
	unsigned int pointer = 0;
	unsigned int next = 0;
	if (i > MY_HEAP_SIZE - sizeof(int)) return 0;
	do {
		pointer = next;
		next = MY_HEAP[pointer];
		if (next & ~USE_MASK)
		{
			if (((next - pointer - 1) * 8) >= i)
			{
				MY_HEAP[pointer] = pointer + 1 + (i + 7)/8;
				if (MY_HEAP[pointer] != next) MY_HEAP[MY_HEAP[pointer]] = next;
				MY_HEAP[pointer] = MY_HEAP[pointer] | USE_MASK;
				return &MY_HEAP[pointer];
			}
		} else
		{
			next = next & ~USE_MASK;
		}
	} while (next < (MY_HEAP_SIZE / sizeof(int)));
	return 0;
}

void my_free(void* i)
{
	int position;
	int last;
	int next;
	
	last = 0;
	position = 0;
	next = 0;
	
	
	do
	{
		last = position;
		position = next;
		next = MY_HEAP[position & ~USE_MASK];
		
		if (((int) &MY_HEAP[position & ~USE_MASK]) == ((int) i))
		{
			MY_HEAP[position & ~USE_MASK] = next & ~USE_MASK;
			if (!(last & ~USE_MASK))
			{
				MY_HEAP[last] = next & ~USE_MASK;
				position = last;
			}
			if (!(next & ~USE_MASK))
			{
				MY_HEAP[position & ~USE_MASK] = 
						(MY_HEAP[position & ~USE_MASK] & USE_MASK) & 
							MY_HEAP[next & ~USE_MASK];
			}				
		}		
	} while (((int) next) < (((int) & MY_HEAP[0]) + MY_HEAP_SIZE));
}




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

void drop_udp_packet(NewDataEvent* e, int udp_start)
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

void 	datagram_set_dst_port(datagram* packet, u16_t port)
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
	char* s = (char*) ip_hdr;
	int i = 0; //loop counter
	
	for (i = 0; i < 8; ++i)
	{
		t[i << 1] = s[(i <<1) + 1];
		t[(i << 1) + 1] = s[i <<1];
	}
}

void simple_echo(NewDataEvent* e, int udp_start)
{
	//simple Echo
	udp_socket* so;
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
	
	udp_datagram_set_payload(toSend, incUdpPacket->payload, len - UDP_HEADER_SIZE);
	
	udp_socket_send_datagram(so, toSend);
	
}

/*
void simple_echo(NewDataEvent* e, int udp_start)
{
	NewDataEvent zzzz;
	//simple echo as test
	//datagram* incUdpPacket;
	//datagram* outUdpPacket;
	//udp_header* udpHeader;
	//struct uip_tcpip_hdr* tcpip_hdr;
	//Neighbor_AO* neighbor;
	//udp_socket* so;
	char response[38] = "Dies ist eine automatisierte Antwort!";
	int responseLength = 37;
	
	static QEvent const pr_sig = { PACKET_RECEIVED_SIG};
	static QEvent const ps_sig = { PACKET_SENT_SIG};
	
	tcpip_hdr = (struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	incUdpPacket = (datagram *) &(e->buf[udp_start]);
	udpHeader = &(incUdpPacket->header);
	so = get_open_udp_socket(udpHeader->dst_port);
	
	tcpip_hdr = (struct uip_tcpip_hdr *) &zzzz.buf[UIP_LLH_LEN];
	outUdpPacket = (datagram *) &(zzzz.buf[udp_start]);
	udpHeader = &(outUdpPacket->header);
	
	
	//neighbor = uip_nd6_nbrcache_lookup(&tcpip_hdr->srcipaddr);
	//if (NULL != neighbor)
	//	QActive_postFIFO((QActive *)neighbor, &pr_sig);
	
	
	//switch_eth_addr(e);
	
	set_dst_mac_addr(&zzzz, *((uip_eth_addr *) e->buf));
	memcpy(&zzzz.buf[12], &e->buf[12], 2);
	
//	tcpip_hdr->vtc = 0x60;
//	tcpip_hdr->tcflow = 0;
//	tcpip_hdr->flow = 0;
//	tcpip_hdr->len[0] = (u8_t) ((responseLength + UDP_HEADER_SIZE) >> 8);
//	tcpip_hdr->len[1] = (u8_t) (responseLength + UDP_HEADER_SIZE);
//	tcpip_hdr->proto = (u8_t) 17;
//	tcpip_hdr->ttl = (u8_t) 128;
	
	set_up_ipv6_hdr(tcpip_hdr, responseLength + UDP_HEADER_SIZE, UDP_PROTOCOLL_NR, );
	
	datagram_set_dst_port(outUdpPacket, inUdpPacket->Header.src_port);
	datagram_set_payload(outUdpPacket, response, responseLength);
	
	
	
	//datagram_set_dst_port(udpPacket, udpHeader->src_port);
	//datagram_set_payload(udpPacket, response, responseLength);
	//tcpip_hdr->len[0] = (u8_t) ((responseLength + UDP_HEADER_SIZE) >> 8);
	//tcpip_hdr->len[1] = (u8_t) (responseLength + UDP_HEADER_SIZE);
	//e->len = responseLength + UDP_HEADER_SIZE + UIP_IPH_LEN + ETH_HEADER_LEN;
	
	zzzz.len = responseLength + UDP_HEADER_SIZE + UIP_IPH_LEN + ETH_HEADER_LEN;
	
	socket_finalize_datagram(so, udpPacket);
	
	memcpy(&tcpip_hdr->destipaddr, &tcpip_hdr->srcipaddr, sizeof(uip_ipaddr_t));
	memcpy(&tcpip_hdr->srcipaddr, &uip_hostaddr, sizeof(uip_ipaddr_t));
	
	e->super.sig = SEND_DATA_SIG;
	

	//zzzz.super.sig = SEND_DATA_SIG;
	//zzzz.
	
	
	QF_publish((QEvent *) e);
	//QActive_postFIFO((QActive *)neighbor, &ps_sig);
}
*/

void handle_inc_udp(NewDataEvent* e, int udp_start)
{
	int port = 0;
	udp_socket* socket;
	datagram* packet = (datagram *) &(e->buf)[udp_start];
	port = packet->header.dst_port;
	port = ((port << 8) & 0xff00) + ((port >> 8) & 0x00ff);
	
	socket = get_open_udp_socket((u16_t) port);
	if (socket) socket->function(e, udp_start, socket->arguments);
	else drop_udp_packet(e, udp_start);
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

void setup_eth_hdr(NewDataEvent* e, struct uip_eth_addr* dst, u16_t protocoll_nr)
{
	memcpy(&e->buf[0], dst, 6);
	memcpy(&e->buf[6], &uip_ethaddr, 6);
	e->buf[12] = ((char*) &protocoll_nr)[1];
	e->buf[13] = ((char*) &protocoll_nr)[0];
}

void setup_IPv6_hdr(struct uip_tcpip_hdr* ip_hdr, int payload_len, u8_t payload_prot, uip_ipaddr_t* src, uip_ipaddr_t* dst)
{
	ip_hdr->vtc = 0x60;
	ip_hdr->tcflow = 0;
	ip_hdr->flow = 0;
	ip_hdr->len[0] = ((u8_t*) &(payload_len))[1];
	ip_hdr->len[1] = ((u8_t*) &(payload_len))[0];
	ip_hdr->proto = (u8_t) payload_prot;
	ip_hdr->ttl = (u8_t) 128;
	memcpy(&ip_hdr->srcipaddr, src, sizeof(uip_ipaddr_t));
	memcpy(&ip_hdr->destipaddr, dst, sizeof(uip_ipaddr_t));
}

u16_t calc_UPD_chksum(uip_ipaddr_t* srcIP, uip_ipaddr_t* dstIP, const u16_t len, const datagram* dataG)
{
	long chksum = 0;
	int i = 0; // loop counter
	
	for (i = 0; i < 8; i = i + 2)
	{
		chksum = chksum + (((u16_t*) srcIP)[i]) << 8;
		chksum = chksum + ((u16_t*) dstIP)[i + 1];
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
	
	return (u16_t) chksum;
}

void preset_UDP_hdr(udp_header* hdr, u16_t src, u16_t dst, u16_t len)
{
	hdr->src_port = (((u8_t) src) << 8) + ((u8_t*) &src)[1];
	hdr->dst_port = (((u8_t) dst) << 8) + ((u8_t*) &dst)[1];
	hdr->length = (((u8_t) len) << 8) + ((u8_t*) &len)[1];
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
	//int i = 0; //loop counter	
	
	e = Q_NEW(NewDataEvent, SEND_DATA_SIG);
	ip_hdr = (struct uip_tcpip_hdr *) &e->buf[UIP_LLH_LEN];
	dataG = (datagram*) &(e->buf[UIP_LLH_LEN + IP_HEADER_SIZE]);
	udp_hdr = &dataG->header;
	srcIP = &so->address;
	srcPort = so->port;
	dstIP = &dg->address;
	dstPort = dg->port;
	neighbor = uip_nd6_nbrcache_lookup(dstIP);
	
	setup_eth_hdr(e, &neighbor->lladdr, IPV6_PROTOCOLL_NR);
	setup_IPv6_hdr(ip_hdr, dg->len + UDP_HEADER_SIZE, UDP_PROTOCOLL_NR, srcIP, dstIP);
	memcpy(dataG->payload, dg->datagram.payload, dg->len); //copy payload
//	for (i = 0; i < dg->len; i++)
//	{
//		dataG->payload[i] = dg->datagram.payload[i];
//	}
	
	preset_UDP_hdr(udp_hdr, srcPort, dstPort, dg->len + UDP_HEADER_SIZE);
	set_UDP_chksum(udp_hdr, calc_UPD_chksum(srcIP, dstIP, dg->len, dataG));
	
	e->len = dg->len + UDP_HEADER_SIZE + UIP_IPH_LEN + ETH_HEADER_LEN;
	e->super.sig = SEND_DATA_SIG;
	
	QF_publish((QEvent *) e);
	QF_gc((QEvent*) e);
}

udp_socket* udp_open_socket (int port, functiontype f, void* args) {
	open_udp_socket_list_element * socketList = udp_socket_list;
	open_udp_socket_list_element * newListElement = 0;
	udp_socket* so = get_open_udp_socket(port);
	if (so) return 0;

	newListElement = my_malloc(OPEN_UDP_SOCKET_LIST_ELEMENT_SIZE);
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
	//todo release memory
}



void udp_setup_test_port(int port)
{
	udp_open_socket(9999, &simple_echo, 0);
}


