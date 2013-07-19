
#include "sip_connector.h"

#define INIT_SIP_SIZE 10
const char INIT_SIP[INIT_SIP_SIZE] = "start_sip";

#define SIP_PROTOCOL_SIZE 10
const char SIP_PROTOCOL[SIP_PROTOCOL_SIZE] = "SIP/2.0";

#define SIP_PROT_PORT_SIZE 15
const char SIP_PROT_PORT[SIP_PROT_PORT_SIZE] = "SIP/2.0/UDP";

const uip_ipaddr_t SIP_DEFAULT_TARGET_IP = {0x2001,0x4dd0,0xfe8d,0xa000,0x0204,0x75ff,0xfec2,0xd214};
//const uip_ipaddr_t SIP_DEFAULT_TARGET_IP = {0x2001,0x4dd0,0xfe8d,0xa000,0x0000,0x0000,0x0000,0x1001};


const u16_t SIP_DEFAULT_TARGET_PORT = 4060;
const u16_t SIP_DEFAULT_HOME_PORT = 5060;

#define SIP_DEFAULT_SERVERNAME_SIZE 15
const char SIP_DEFAULT_SERVERNAME[SIP_DEFAULT_SERVERNAME_SIZE] = "open-ims.test";

#define SIP_DEFAULT_USERNAME_SIZE 7
const char SIP_DEFAULT_USERNAME[SIP_DEFAULT_USERNAME_SIZE] = "roland";

#define SIP_DEFAULT_PASSWORD_SIZE 7
const char SIP_DEFAULT_PASSWORD[SIP_DEFAULT_PASSWORD_SIZE] = "roland";

#define SIP_BRANCH_PREFIX_SIZE 8
const char SIP_BRANCH_PREFIX[SIP_BRANCH_PREFIX_SIZE] = "z9hG4bK";

#define SIP_REGISTER_TAG "REGISTER"

// SIP state handlers

void sip_state_handler_register(udp_datagram dg, sip_object* thisObj)
{
	
}

void sip_handle_inc_packet(udp_socket* so, udp_datagram* dg, sip_object* thisObj)
{
	thisObj->state_handler(dg, thisObj);
}

void ipv6_to_hex(uip_ipaddr_t* addr, char* dst)
{
	int i;
	u16_t* digits = (u16_t*) addr;
	for (i = 0; i < 8; i++)
	{
		unsigned char tmp;
		unsigned char a = (char) ((digits[i] & 0xff00) >> 8);
		unsigned char b = (char) (digits[i] & 0xff);
		
		tmp = (a & 0xf0) >> 4;
		if (tmp < 0xa) tmp += '0';
		else tmp += 'a' - 10;
		dst[i * 5] = tmp;
		
		tmp = (a & 0xf);
		if (tmp < 0xa) tmp += '0';
		else tmp += 'a' - 10;
		dst[(i * 5) + 1] = tmp;
		
		tmp = (b & 0xf0) >> 4;
		if (tmp < 0xa) tmp += '0';
		else tmp += 'a' - 10;
		dst[(i * 5) + 2] = tmp;
		
		tmp = (b & 0xf);
		if (tmp < 0xa) tmp += '0';
		else tmp += 'a' - 10;
		dst[(i * 5) + 3] = tmp;
		
		if (i < 7) dst[(i * 5) + 4] = ':';
	}
	return;
}

void sip_send_register(sip_object* sipObj)
{
	int i;
	udp_datagram toSend;
	int position = 0;
	char* udp_payload = toSend.datagram.payload;
	char dstIPasHex[40];
	char srcIPasHex[40];
	dstIPasHex[39] = 0;
	srcIPasHex[39] = 0;
	ipv6_to_hex(&(sipObj->targetIP), dstIPasHex);
	ipv6_to_hex(&(sipObj->so->address), srcIPasHex);
	
	sipObj->last_branch_suffix++;
	sipObj->cseq++;
	
	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"%s sip:%s %s%s", SIP_REGISTER_TAG, sipObj->servername, SIP_PROTOCOL, LINE_FEED);
	position += i;
	
	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Via: %s [%s]:%d;branch=%s%s;rport%s", SIP_PROT_PORT, srcIPasHex,
											sipObj->so->port, SIP_BRANCH_PREFIX, (char*) (sipObj->last_branch_suffix), LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"From: <sip:%s@%s>;tag=%d%s", sipObj->username, sipObj->servername, sipObj->tag, LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"To: <sip:%s@%s>%s", sipObj->username, sipObj->servername, LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Contact: <sip:%s@[%s]:%d;transport=udp>;expires600000;+g.oma.sip-im%s",
								sipObj->username, srcIPasHex, sipObj->so->port, LINE_FEED);
	position += i;
	
	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Call-ID: %s%s",
								sipObj->call_id, LINE_FEED);
	position += i;
	
	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"CSeq: %d %s&%s",
								sipObj->cseq, SIP_REGISTER_TAG, LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Content-Length: 0%s",
								LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Max-Forwards: 70%s",
								LINE_FEED);
	position += i;
	
	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Authorization: Digest username=\"%s@%s\",realm=\"%s\",nonce=\"\",uri=\"sip:%s\",response=\"\"%s",
								sipObj->username, sipObj->servername, sipObj->servername, sipObj->servername, LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Allow: MESSAGE, BYE%s",
								LINE_FEED);
	position += i;
	
	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"Privacy: none%s",
								LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"User-Agent: raindrop sensor/pre alpha%s",
								LINE_FEED);
	position += i;

	i = snprintf(&(udp_payload[position]), DATAGRAM_PAYLOAD_SIZE - position,
								"P-Preferred-Identity: <sip:%s@%s>%s%s",
								sipObj->username, sipObj->servername, LINE_FEED, LINE_FEED);
	position += i;
	
	udp_datagram_set_address(&toSend, &(sipObj->targetIP));
	udp_datagram_set_port(&toSend, sipObj->targetPort);
	toSend.len = position;
	udp_socket_send_datagram(sipObj->so, &toSend);
}

void bytes_to_hex(unsigned char* dst, unsigned char* src, unsigned int len)
{
	unsigned int i;
	for (i = 0; i < len; i++)
	{
		char tmp;
		
		tmp = ((0xf0 & src[i]) >> 4);
		if (tmp < 0xa) dst[i << 1] = tmp + '0';
		else dst[i << 1] = tmp + 'a' - 0xa;
		
		tmp = (0xf & src[i]);
		if (tmp < 0xa) dst[(i << 1) + 1] = tmp + '0';
		else dst[(i << 1) +1] = tmp + 'a' - 0xa;
	}
}

void sip_init(u16_t home_port, uip_ipaddr_t *server_addr, u16_t server_port,
							char* servername, char* username, char* password,
							unsigned int random_number)
{
	char call_id_bytes[16];
	int i;
	udp_socket* so;
	sip_object* newSip = (sip_object*) cst_malloc(SIP_OBJECT_SIZE);
	newSip->state_handler = &sip_state_handler_register;
	newSip->last_branch_suffix = random_number;
	newSip->cseq = random_number;
	newSip->tag = random_number;
	rnd_fillArray(call_id_bytes, 16);
	bytes_to_hex((unsigned char *) &(newSip->call_id[0]), (unsigned char *) call_id_bytes, 16);


	
	
	for (i = 0; i < SERVERNAME_MAX_SIZE; i++)
	{
		if (servername[i]) newSip->servername[i] = servername[i];
		else
		{
			newSip->servername[i] = 0;
			break;
		}
	}
	
	for (i = 0; i < USERNAME_MAX_SIZE; i++)
	{
		if (username[i]) newSip->username[i] = username[i];
		else
		{
			newSip->username[i] = 0;
			break;
		}
	}
	
	for (i = 0; i < PASSWORD_MAX_SIZE; i++) newSip->password[i] = 0;
	for (i = 0; i < PASSWORD_MAX_SIZE; i++)
		if (password[i]) newSip->password[i] = password[i];
		else break;

	memcpy(&(newSip->targetIP), server_addr, sizeof(uip_ipaddr_t));
	newSip->targetPort = server_port;
	so = udp_open_socket(home_port, &sip_handle_inc_packet, newSip);
	newSip->so = so;
	
	sip_send_register(newSip);
}

void sip_init_default()
{
	sip_init(SIP_DEFAULT_HOME_PORT, (uip_ipaddr_t*) &SIP_DEFAULT_TARGET_IP, SIP_DEFAULT_TARGET_PORT,
						(char*) SIP_DEFAULT_SERVERNAME, (char*) SIP_DEFAULT_USERNAME, (char*) SIP_DEFAULT_PASSWORD, 0);
}

void sip_control_method(udp_socket* so, udp_datagram* dg)
{
	char* data = &(dg->datagram.payload[0]);
	int i;
	for (i = 0; i <= INIT_SIP_SIZE; i++)
	{
		if (INIT_SIP[i])
		{
			if (INIT_SIP[i] != data[i]) break;
		}
		else
		{
			sip_init_default();
			return;
		}
	}
}

