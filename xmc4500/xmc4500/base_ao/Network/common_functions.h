#ifndef COMMON_FUNCTIONS_H_INCLUDED_
#	define COMMON_FUNCTIONS_H_INCLUDED_

typedef struct uip_tcpip_hdr* uip_header_ptr;


uip_header_ptr uip_header()
{
	return ((struct uip_tcpip_hdr *)&uip_buf[UIP_LLH_LEN]);
}

typedef enum
{ proto_icmp_v4 = 1
, proto_tcp = 6
, proto_udp = 17
, proto_icmp_v6 = 58
} protocol_id;


protocol_id get_protocol(uip_header_ptr header)
{
	return header->proto;
}


#endif
