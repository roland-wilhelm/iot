/*
 * ethernet.h
 *
 *  Created on: 02.11.2012
 *      Author: kater
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_

// USE includes from the old file: phy_dev.h
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
#include "uip.h"
#include "uip_arp.h"

/**
 * initialize the PHY and Ethernet Chip, this will enable interrupts and post Events.
 * so make sure the Statemaschine is ready to work!
 */
extern void ethernetInit(void);

/**
 * \TODO change this method so it can be used before ethernetInit();
 * configure the PHY and Ethernet Chip, if this method is called without parameters, the defaults are used
 */
extern void ethernetConfigure(void);

/**
 * Method should be called by the Ethernet Active Object.
 * This method handles ARP Requests (for this device only)
 * Additionally all other
 */ 
enum EthernetReturnFlags ethernetPacketProcess(void);

/**
 * This Method handles transmit request from MAC and IP to the network.
 * NOTE: if no entry ARP-Entry for the Destination 
 * IP exist -> The Request will be dropped and an ARP-Request will be sent instead
 */
enum EthernetReturnFlags ethernetHandleTransmitRequest(void);

/**
 * Enumeration of Flags to indicate the meaning of return values
 */ 
enum EthernetReturnFlags {
	// Flag to signal that the packet was handled internaly, e.g. no posting to other Active Objects is required
	ETHERNET_HANDLED,
	// Flag to signalt that the packet should be handled by the upper layers
	ETHERNET_POST_TO_UPPER_LAYER,
	// no ARP-Cache Entry was found, Transmit request will be droped and an ARP-Request will be sent instead
	ETHERNET_DROP_TRANSMIT_MISSING_ARP_ENTRY
};

/**
 * Flag to indicate why the Interrupt Service Routine for Ethernet (ISR_Emac) was called.
 */
enum EMACISRFlags {
	EMAC_UNKNOWN = 0,
	EMAC_TRANSMIT,
	EMAC_RECEIVE,
	EMAC_MANAGEMENT
};

struct EthernetRegisterSet {
	unsigned int interruptStatusRegister;
	unsigned int receiveStatusRegister;
	unsigned int transmitStatusRegister;
};

extern struct EthernetRegisterSet ethernetRegisterSet;

//	Send to EMAC device.
void send(unsigned char *buffer, int size);

//	Read from EMAC device.
unsigned int receive(unsigned char *buffer, int size);

#endif /* ETHERNET_H_ */

