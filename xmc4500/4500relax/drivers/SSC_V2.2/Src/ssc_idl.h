/* =============================================================================
** Copyright (C) 2004 Infineon Technologies.
**
** All rights reserved.
** =============================================================================
**
** =============================================================================
**
** This document contains proprietary information belonging to Infineon 
** Technologies. Passing on and copying of this document, and communication of 
** its contents is not permitted without prior written authorisation.
**
** =============================================================================
*/
/* =============================================================================
**
** Revision Information :
** @FILENAME@:       ssc_idl.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: Provides the hardware dependent features like registers address 
**           mapping and control bit position in corresponding register. While 
**           porting to new hardware this file has to be ported
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      Bhavjit Walha        Release after code review.
**
** @CHANGE_HISTORY@
** =============================================================================
*/	
/* @doc DESIGN */

#ifndef __SSC_IDL_H
#define __SSC_IDL_H
/*
  Required include files:
*/
#include "compiler.h"
#include "sys_cfg.h"
#include "sys_api.h"

/* Define the product this layer is written for: */
#define SSC_PRODUCT TC1130

/*
  The follwing define decide the up/down counting of FDR.STEP value.
  To get required baud rate this value used as a one fraction apart from
  baud rate reload timer register value
  0 --> Down count, start with 0x3ff value.
  1 --> Up count, start with zero value.
*/
#define LESS_FDR  0 

/* Peripheral Hardware Address And Number Defines: */
#if (SSC_PRODUCT == TC1765)
#define SSC_HW_NUM 2             /* Number of SSC modules on chip: */
#define SSC_HW_0_ADDR 0xF0000A00 /* Base Address Of SSC module 0   */
#define SSC_HW_1_ADDR 0xF0000B00 /* Base Address Of SSC module 1   */
#elif (SSC_PRODUCT == TC1130)
#define SSC_HW_NUM 2             /* Number of SSC modules on chip: */
#define SSC_HW_0_ADDR 0xF0100100 /* Base Address Of SSC module 0   */
#define SSC_HW_1_ADDR 0xF0100200 /* Base Address Of SSC module 1   */
#endif

 
/* Feature enabling */
#define SSC_HW_FIFO_RX 0  /* Receive FIFO support off(0)/size(1-X): */
#define SSC_HW_FIFO_TX 0  /* Transmit FIFO support off(0)/size(1-X): */
#define SSC_HW_DEL_SUP 0  /* Delay support*/
#define SSC_HW_MAX_DLY 3  /* Maximum number of delay cycles used in laed, trail, inactive states.*/


/* Baud rate restrictions */
#define SSC_MIN_CLK            (2 * 0x10000)         /*Mnimum SSC clock frequency*/
#define SSC_FDV_MIN_CLK        (2 * 0x10000 * 1024)  /*Mnimum SSC clock frequency in FDR mode*/
#define SSC_MAX_CLK            (2 * 1)               /*Maximum SSC clock frequency */

/*
    Feature enabling:
*/
#if (SSC_PRODUCT == TC1130)
#define SSC_HW_PISEL_FTR     1
#define SSC_HW_FDV_FTR       1
#define SSC_HW_SLAVE_SEL_FTR 1
#define SSC_HW_SEP_STAT_FTR  1
#define SSC_HW_RMC_FTR       0
#define SSC_NUM_PORTS        24
#elif (SSC_PRODUCT == TC1765)
#define SSC_HW_RMC_FTR       1
#define SSC_NUM_PORTS        6
#endif


/* Register offsets */
#define SSC_HW_CLC(n)           *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0000) /* Clock control register */

#if SSC_HW_PISEL_FTR == 1
#define SSC_HW_PISEL(n)         *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0004) /* Peripheral Input select register */
#endif

#if SSC_HW_FDV_FTR == 1
#define SSC_HW_FDV(n)           *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x000C) /* Fractional divider control register */
#endif

#define SSC_HW_CON(n)           *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0010) /* Module control register */
#define SSC_HW_BR(n)            *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0014) /* Baud Rate / Timer reload register */

#if SSC_HW_SLAVE_SEL_FTR == 1
#define SSC_HW_SSOC(n)          *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0018) /* Slave select output control register */
#define SSC_HW_SSOTC(n)         *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x001C) /* Slave select output timing control register */
#endif

#define SSC_HW_TB(n)            *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0020) /* SSC Tranmit Buffer register */
#define SSC_HW_RB(n)            *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0024) /* SSC Receive Buffer register */

#if SSC_HW_SEP_STAT_FTR == 1
#define SSC_HW_STAT(n)          *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0028) /* Slave select output control register */
#define SSC_HW_EFM(n)           *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x002C) /* Slave select output control register */
#endif

#define SSC_HW_RXFCON(n)        *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0030) /* SSC Receive FIFO control register */
#define SSC_HW_TXFCON(n)        *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0034) /* SSC Transmit FIFO control register */
#define SSC_HW_FSTAT(n)         *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x0038) /* SSC FIFO status register */
#define SSC_HW_TSRC(n)          *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x00F4) /* SSC Transmit ISR control register */
#define SSC_HW_RSRC(n)          *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x00F8) /* SSC Receive ISR control register */
#define SSC_HW_ESRC(n)          *(IFX_VUINT32 *)(SSC_addr_table[n] + 0x00FC) /* SSC Error ISR control register */


/* @topic2 ISR implementation details | */

/*
  @func SSC_TIR_ISR | SSC transmit Interrupt Service Routine
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Find the number of bytes can be written to IO ports.
  @flag: (DESIGN)  | - Write the pending request data to IO ports.
  @flag: (DESIGN)  | - Decrement the pending request size by the number of data values written to ports.
  @flag: (DESIGN)  | - If the pending request size value is zero call the user callback function provided the
          pending request support user callback function feature.
  @retval  None
*/
void SSC_TIR_ISR (
  IFX_UINT8 SSC_device /*@parm SSC hardware module identification number.*/
);

/*
  @func SSC_RIR_ISR | SSC receive Interrupt Service Routine
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Copy the data bytes from read buffer to the pending request. Decrement the pending request size value
          by the number of data values read from read buffer. 
  @flag: (DESIGN)  | - Update the read buffer pointers.
  @flag: (DESIGN)  | - If the data received from IO ports, read the received data to the pending request.
  @flag: (DESIGN)  | - Read the received data from IO ports to the read buffer, if there are no pending requests or the number of
          bytes received from IO ports more than the size of pending request.
  @flag: (DESIGN)  | - If the pending request size is zero call the user callback function provided pending request support the user callback function feature.                  
  @retval  None
*/
void SSC_RIR_ISR (
  IFX_UINT8 SSC_device /*@parm SSC hardware module identification number.*/
);

/*
  @func SSC_EIR_ISR | SSC error Interrupt Service Routine
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Find the cause of error by reading control register.
  @flag: (DESIGN)  | - Increment the corresponding statistics counter.
  @flag: (DESIGN)  | - Reset error flags.
  @retval  None
*/
void SSC_EIR_ISR (
  IFX_UINT8 SSC_device /*@parm SSC hardware module identification number.*/
);

#if (IFX_COMPILER_GNU == 1)
/*
  @func SSC_HW_register_isr | ISR initializer
  @head4 Implementation Details |
  @flag: (DESIGN)  | - If IFX_COMPILER_GNU feature is enabled the ISR will be initialized.
  @retval  Success/Failure
  @flag 1 | On success
  @flag 0 | On failure
*/
IFX_UINT8 SSC_HW_register_isr (
  IFX_UINT8 SSC_device /*@parm SSC hardware module identification number.*/
);
#else
#define SSC_HW_register_isr(__SSC_HW_PARM)
#endif



/*
  Repeat the number of times as many units are present
  For example if the No. of SSC units are 2, use
  #define SSC_HW_INIT(__SSC_INIT_VAL) __SSC_INIT_VAL, __SSC_INIT_VAL, __SSC_INIT_VAL
*/
#if (SSC_HW_NUM == 1)
#define SSC_HW_INIT(__SSC_INIT_VAL) __SSC_INIT_VAL
#elif (SSC_HW_NUM == 2)
#define SSC_HW_INIT(__SSC_INIT_VAL) __SSC_INIT_VAL, __SSC_INIT_VAL
#elif (SSC_HW_NUM == 3)
#define SSC_HW_INIT(__SSC_INIT_VAL) __SSC_INIT_VAL, __SSC_INIT_VAL, __SSC_INIT_VAL
#endif

#endif /*__SSC_IDL_H*/

