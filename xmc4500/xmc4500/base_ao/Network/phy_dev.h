/*
* Product:  Basic Active Object Example FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment */



#ifndef __PHY_DEV_H__
#define __PHY_DEV_H__
// #include <board.h>
// #include <pio/pio.h>
// #include <aic/aic.h>
// #include <dbgu/dbgu.h>
// #include <usart/usart.h>
// #include <emac/emac.h>
//#include <dm9161.h>
#include <string.h>
#include <dbgu/dbgu.h>
#include <utility/trace.h>
#include <utility/assert.h>
#include "uip_ao.h"
#include "uip6.h"

/// The MAC address used for demo
static const struct uip_eth_addr MacAddress = {{0x00, 0x45, 0x56, 0x78, 0x9a, 0xbc}};
/// The IP address used for demo (ping ...)
static const unsigned char HostIpAddress[4] = {192, 168, 178, 100};

/// Set the default router's IP address.
static const unsigned char RoutIpAddress[4] = {192, 168, 178, 1};

/// The IP address used for demo (ping ...)
/*
static const u16_t HostIPv6Address[8] = 
{ 0x2001
, 0x0db8
, 0x2530
, 0xfa13
, 0xf2de
, 0xf1ff
, 0xfe52
, 0xaa62
};

/// Set the default router's IP address.
static const u16_t RoutIPv6Address[8] = 
{ 0x2001
, 0x0db8
, 0x2530
, 0xfa13
, 0xf2de
, 0xf1ff
, 0xfe52
, 0xaa64
};
*/
static const u16_t HostIPv6Address[8] = 
{ 0x2001
, 0x4dd0
, 0xfe8d
, 0x0000
, 0x0000
, 0x0000
, 0x0000
, 0x100a
};

/// Set the default router's IP address.
static const u16_t RoutIPv6Address[8] = 
{ 0x2001
, 0x4dd0
, 0xfe8d
, 0x0000
, 0xbe05
, 0x43ff
, 0xfe18
, 0x5298
};

// The NetMask address
static const unsigned char NetMask[4] = {255, 255, 255, 0};


void phy_dev_init(void);
void phy_dev_read(void);
void phy_dev_send(NewDataEvent * e);
void phy_d83848_init(const unsigned char  mac[]);


#endif /* __PHY_DEV_H__ */
