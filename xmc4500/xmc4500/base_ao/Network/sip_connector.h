

#ifndef SIP__CONNECTOR_H
#define SIP__CONNECTOR_H

#include "milenage.h"
#include "udp_socket.h"
#include "uip.h"
#include "customHeap.h"
#include <stdio.h>
#include <string.h>

#define LINE_FEED "\r\n"

#define CALL_ID_SIZE 32 + 1
#define SERVERNAME_MAX_SIZE 100
#define USERNAME_MAX_SIZE 100
#define PASSWORD_MAX_SIZE 16

typedef void (*sip_state_handler)(udp_datagram*, void*);

typedef struct sip_object_tag {
	sip_state_handler state_handler;
	udp_socket* so;
	unsigned int tag;
	unsigned int last_branch_suffix;
	unsigned int cseq;
	char call_id[CALL_ID_SIZE];
	char servername[SERVERNAME_MAX_SIZE];
	char username[USERNAME_MAX_SIZE];
	char password[PASSWORD_MAX_SIZE];
	uip_ipaddr_t targetIP;
	u16_t targetPort;
} sip_object;
#define SIP_OBJECT_SIZE ((5 * sizeof(int)) + CALL_ID_SIZE + SERVERNAME_MAX_SIZE + USERNAME_MAX_SIZE + PASSWORD_MAX_SIZE + sizeof(uip_ipaddr_t) + sizeof(u16_t))

void sip_init(u16_t home_port, uip_ipaddr_t *server_addr, u16_t server_port,
							char* servername, char* username, char* password,
							unsigned int random_number);

void sip_control_method(udp_socket* so, udp_datagram* dg);

#endif
