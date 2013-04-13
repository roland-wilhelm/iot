/* Product:  Basic Active Object Example µIP FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment 
* based on Adam Dunkels µIP 
* Copyright (c) 2001, Swedish Institute of Computer Science.
*/

#include <board.h>
#include <utility/trace.h>
#include <emac/emac.h>
#include <pio/pio.h>
#include <aic/aic.h>
#include <rstc/rstc.h>
#include <dbgu/dbgu.h>
#include <usart/usart.h>
#include <string.h>
#include <stdint.h>

#include <dp83848.h>


#include "qp_port.h"                /* the port of the QEP event processor */
#include "uip_ao.h"


static EMAC_Event emac;

extern QActive * const UipAO;



// EMAC power control pin
#if !defined(BOARD_EMAC_POWER_ALWAYS_ON)
static const Pin emacPwrDn[] = {BOARD_EMAC_PIN_PWRDN};
#endif

// The PINs on PHY reset
static const Pin emacRstPins[] = {BOARD_EMAC_RST_PINS};

// The PINs for EMAC
static const Pin emacPins[] = {BOARD_EMAC_RUN_PINS};

// PHY address
#define EMAC_PHY_ADDR 3

// The DP83848 driver instance
static Dp83848 gDp83848;

//-----------------------------------------------------------------------------
/// Emac interrupt handler
//-----------------------------------------------------------------------------
static void ISR_Emac(void)
{
#ifdef QK
 	__disable_irq(); 
  	  ++QK_intNest_; 
#endif  
	QF_INT_UNLOCK();
    EMAC_Handler();
	// QF-event queue trigger
	  emac.type = 1;
	  QActive_postFIFO( UipAO, (QEvent *)&emac); 
	QF_INT_LOCK(); 
#ifdef QK 
	   --QK_intNest_;
	   if (   QK_intNest_ ==0) 
	   		QK_schedule_();
#endif
}
	   /*
 * Init the ethernet physical device
 */
void phy_d83848_init( uint8_t* macaddr )
{
    Dp83848 *pDp = &gDp83848;

	emac.super.sig = 	 EMAC_INT_SIG;
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

