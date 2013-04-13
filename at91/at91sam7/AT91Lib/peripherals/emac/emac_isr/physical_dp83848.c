/* Product:  Basic Active Object Example :P FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - ?ink Environment 
* based on Adam Dunkels :P 
* Copyright (c) 2001, Swedish Institute of Computer Science.
*/
 

#include <board.h>
#include <pio/pio.h>
#include <aic/aic.h>
#include <dbgu/dbgu.h>
#include <usart/usart.h>
#include <emac/emac.h>
#include <rstc/rstc.h>
#include <dp83848.h>
#include <string.h>
#include <utility/trace.h>
#include <utility/assert.h>
#include "uip_arp.h"

// Ethernet Includes START
#include "ethernet_configuration.h"
#include "physical_dp83848.h"
#include "ethernet_isr.h" // to setup the interrupt service routine
// Ethernet Includes END

/// EMAC power control pin
#if !defined(BOARD_EMAC_POWER_ALWAYS_ON)
static const Pin emacPwrDn[] = {BOARD_EMAC_PIN_PWRDN};
#endif

/// The PINs' on PHY reset
static const Pin emacRstPins[] = {BOARD_EMAC_RST_PINS};


/// The PINs for EMAC
static const Pin emacPins[] = {BOARD_EMAC_RUN_PINS};

#define PINS_EMAC       {0x3EFFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

const Pin pinsEmac[] = {PINS_EMAC};

// PHY address
#define EMAC_PHY_ADDR             3

// The DP83848 driver instance
static Dp83848 gDp83848;

/*
 * Init the ethernet physical device
 */
void phy_d83848_init( uint8_t* macaddr, void (*handler)(void)) {
    Dp83848 *pDp = &gDp83848;

	/* Disable pull up on RXDV => PHY normal mode (not in test mode),
		PHY has internal pull down. */
	AT91C_BASE_PIOB->PIO_PPUDR &= ~AT91C_PIO_PB15;

	// clear PHY power down mode
    PIO_Configure(emacPwrDn, 1);
    PIO_Set(emacPwrDn);

    // Enable external reset
    RSTC_SetUserResetEnable(/*AT91C_BASE_RSTC, TODO @@@jwg: wo kam das her!?*/ 1);

    // Init DP83848 driver
    DP83848_Init(pDp, EMAC_PHY_ADDR);

    // PHY initialize
	if ( !DP83848_InitPhy(pDp, BOARD_MCK, emacRstPins, PIO_LISTSIZE(emacRstPins),
										  emacPins, PIO_LISTSIZE(emacPins)) ) {
		TRACE_ERROR("PHY Initialize ERROR!\n\r");
		return;
	}

	// Setup EMAC buffers and interrupts
	AIC_ConfigureIT(AT91C_ID_EMAC, AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL, ISR_Emac);
	AIC_EnableIT(AT91C_ID_EMAC);

	// Init EMAC driver structure
	EMAC_Init(AT91C_ID_EMAC, macaddr, EMAC_CAF_ENABLE, EMAC_NBC_DISABLE);

	DP83848_Setup(pDp);

	TRACE_INFO("ethdev_init() done\n\r");

//	LED_Set(2);
}

/*---------------------------------------------------------------------------*/
void phy_dev_init() {
#if !defined(BOARD_EMAC_POWER_ALWAYS_ON)
    // clear PHY power down mode
    PIO_Configure(emacPwrDn, 1);
#endif
	
	// add a f*cking typecast since every shitty application has to re-create every typedef again and again
	phy_d83848_init((uint8_t*)&MacAddress.mac[0], ISR_Emac);
}
