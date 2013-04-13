/* Product:  Basic Active Object Example µIP FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment 
* based on Adam Dunkels µIP 
* Copyright (c) 2001, Swedish Institute of Computer Science.
*/
 

#include <board.h>
#include <pio/pio.h>
#include <aic/aic.h>
#include <dbgu/dbgu.h>
#include <usart/usart.h>
#include <emac/emac.h>
#include <dp83848.h>
#include <string.h>
#include <utility/trace.h>
#include <utility/assert.h>
#include "phy_dev.h"


#include "uip_ao.h"

/// EMAC power control pin
#if !defined(BOARD_EMAC_POWER_ALWAYS_ON)
static const Pin emacPwrDn[] = {BOARD_EMAC_PIN_PWRDN};
#endif

/// The PINs' on PHY reset
static const Pin emacRstPins[] = {BOARD_EMAC_RST_PINS};

// THESE ARE UIP GLOBALS !!!!!!!!!!
#ifdef UIP_QF
unsigned char  uip_buf[UIP_BUFSIZE+2];
unsigned short uip_len;
#endif
/// The PINs for EMAC
static const Pin emacPins[] = {BOARD_EMAC_RUN_PINS};

#define PINS_EMAC       {0x3EFFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

const Pin pinsEmac[] = {PINS_EMAC};

// AO
extern QActive * const UipAO;
//static NewDataEvent nd;

/// PHY address

#define EMAC_PHY_ADDR             3



/*---------------------------------------------------------------------------*/
void
phy_dev_init(void)
{



#if !defined(BOARD_EMAC_POWER_ALWAYS_ON)
    // clear PHY power down mode
    PIO_Configure(emacPwrDn, 1);
#endif
 
 phy_d83848_init(MacAddress.addr);

}



delay(int i) {

 



 while( i--);

}

//-----------------------------------------------------------------------------
/// Read for EMAC device
//-----------------------------------------------------------------------------
void
phy_dev_read(void)
{
	unsigned int len;
	unsigned char buf[UIP_CONF_BUFFER_SIZE+2];
	NewDataEvent *e;

    if( EMAC_RX_OK != EMAC_Poll( (unsigned char*)&buf,
                                  UIP_CONF_BUFFER_SIZE,
                                  &len) ) {

        return;
    }

		e= Q_NEW(NewDataEvent, NEW_DATA_SIG);
		e->len = len;
		memcpy(e->buf, buf, sizeof(buf));			
		QF_publish((QEvent *) e);
}

//-----------------------------------------------------------------------------
/// Send to EMAC device
//-----------------------------------------------------------------------------
void phy_dev_send(NewDataEvent *e)
{
    unsigned char emac_rc;

    emac_rc = EMAC_Send( (void*)e->buf, e->len, (EMAC_TxCallback)0);
    if (emac_rc != EMAC_TX_OK) {

        TRACE_ERROR("E: Send, rc 0x%x\n\r", emac_rc);
    }
}

/*---------------------------------------------------------------------------*/

