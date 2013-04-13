/* Product:  Basic Active Object Example µIP FSM with Generic Event Processor - Vanilla Non Preemptive Kernel
* Last Updated for Version: 4.1.01
* Date of the Last Update:  Oct 01, 2012
* Ported to dresden elektronic deRFarm7 Gateway - Atmel AT91SAM7X-512 MCPU
* Keil  ARM - µLink Environment 
* based on Adam Dunkels µIP 
* Copyright (c) 2001, Swedish Institute of Computer Science.
*/

//#include <board.h>
//#include <utility/trace.h>
#include <emac/emac.h>
//#include <pio/pio.h>
//#include <aic/aic.h>
//#include <rstc/rstc.h>
//#include <dbgu/dbgu.h>
//#include <usart/usart.h>
//#include <string.h>
//#include <stdint.h>

//#include <dp83848.h>


//#include "qp_port.h"                /* the port of the QEP event processor */
#include "main.h" // TODO remove this include after testing is finished, uip is not our concern

// include Active Object Ethernet
#include "ethernet_ao.h"

/**
 * Interrupt Service Routine to handle peripherial EMAC
 */
void ISR_Emac(void);
