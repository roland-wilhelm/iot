/* Product:  Basic Active Object Example :P FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - ?ink Environment 
* based on Adam Dunkels :P 
* Copyright (c) 2001, Swedish Institute of Computer Science.
*/
 
#ifndef __PHYSICAL_DP83848_H__
#define __PHYSICAL_DP83848_H__

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
#include "uip.h"
#include "uip_arp.h"
#include "uip.h"


// THESE ARE UIP GLOBALS !!!!!!!!!!
#ifdef UIP_QF
unsigned char  uip_buf[UIP_BUFSIZE+2];
unsigned short uip_len;
#endif

#define PINS_EMAC       {0x3EFFF, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

// PHY address
#define EMAC_PHY_ADDR 3

/*---------------------------------------------------------------------------*/
extern void phy_dev_init(void);

//-----------------------------------------------------------------------------
/// Read for EMAC device
//-----------------------------------------------------------------------------
extern unsigned int phy_dev_read(void);

//-----------------------------------------------------------------------------
/// Send to EMAC device
//-----------------------------------------------------------------------------
extern void phy_dev_send(void);

/*---------------------------------------------------------------------------*/

#endif /* __PHYSICAL_DP83848_H__ */
