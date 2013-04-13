#include "ethernet.h"

// include from old files start
#include "bsp_at91.h"
#include "physical_dp83848.h"
//#include "ethernet_configuration.h"
#include "bsp_uip_ao.h" // for initalise_uipv4();
// include from old files end

struct EthernetRegisterSet ethernetRegisterSet;

/**
 * initialize the PHY and Ethernet Chip, this will enable interrupts and post Events.
 * so make sure the Statemaschine is ready to work!
 * \param handler the method to be registered as an Interrupt Service Routine for the pheripal EMAC
 */
void ethernetInit(void) {
	phy_dev_init();
}

enum EthernetReturnFlags ethernetHandleTransmitRequest(void)
{
	// lookup arp-table for this IP
	{
		// arp entry found
		// ethernet_transmit(ptrToBuffer, paketSize);
	}
	
	// no entry found, return dropped packet
	return ETHERNET_DROP_TRANSMIT_MISSING_ARP_ENTRY;
}

//	------------------------------------------------
//	init_ipv4.h
//	------------------------------------------------
//	Send to EMAC device.
void send(unsigned char *buffer, int size) {
	unsigned char emac_rc;
	emac_rc = EMAC_Send( (void*)buffer, size, (EMAC_TxCallback)0);
	if (emac_rc != EMAC_TX_OK) {
		TRACE_ERROR("E: Send, rc 0x%x\n\r", emac_rc);
	}		
}

//	Read from EMAC device.
unsigned int receive(unsigned char *buffer, int size) {
	unsigned int pkt_len = 0;
    if( EMAC_RX_OK != EMAC_Poll( buffer, size, &pkt_len) ) {
        pkt_len = 0;
    }		
    return pkt_len;
}
