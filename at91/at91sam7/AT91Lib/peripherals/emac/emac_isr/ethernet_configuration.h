/*
 * ethernet.h
 *
 *  Created on: 02.11.2012
 *      Author: kater
 */

#ifndef ETHERNET_CONFIGURATION_H_
#define ETHERNET_CONFIGURATION_H_

// add old includes from phy_dev.h
#include <board.h>
#include <pio/pio.h>
#include <aic/aic.h>
#include <dbgu/dbgu.h>
#include <usart/usart.h>
#include <emac/emac.h>
#include <string.h>
#include <dbgu/dbgu.h>
#include <utility/trace.h>
#include <utility/assert.h>

/**
 * CONFIGURATION START
 */
typedef unsigned short u16_t;
typedef unsigned char u8_t;
 
typedef struct mac_addr_tag {
 u8_t mac[6];
} mac_addr;

typedef struct ip_addr_tag {
	u8_t ip[4];
} ip_addr;

 
// The MAC address used for demo
static const mac_addr MacAddress = {{0xBE, 0xAF, 0x00, 0x00, 0xBE, 0xAF}};

static const mac_addr Broadcast = {{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};

static const mac_addr BroadcastTarget = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

// The IP address used for demo (ping ...), changed to 123 instead of 100 -> to avoid collisisions with other pcs
static const ip_addr HostIpAddress = {{ 192, 168, 178, 123 }};

// Set the default router's IP address.
static const ip_addr RoutIpAddress = {{192, 168, 178, 1}};

// The NetMask address
static const ip_addr  NetMask = {{255, 255, 255, 0}};

#define EthernetMaxBufferSize 1068 

/**
 * CONFIGURATION END
 */
 
#endif /* ETHERNET_CONFIGURATION_H_ */

