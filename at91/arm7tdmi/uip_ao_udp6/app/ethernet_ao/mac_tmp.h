#include "uip_ao.h"
#include "uip6.h"



/// The MAC address used for demo
static const unsigned char MacAddress[6] = {0x00, 0x45, 0x56, 0x78, 0x9a, 0xbc};

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
, 0x1002
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
