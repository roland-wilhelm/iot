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
** @FILENAME@:       ASC_IDL.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ASC 
**
** =============================================================================
** Contents: Provides the hardware dependent features like registers address 
**           mapping and control bit position in corresponding register. 
**           While porting to new hardware this file has to be ported
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


#ifndef __ASC_IDL_H
#define __ASC_IDL_H

/*
  Required include files:
*/
#include "compiler.h"
#include "sys_api.h"


/* Define the product this layer is written for: */
#define ASC_PRODUCT TC1130


#define ASC_MAX_CLK_ASYNC_NFDV       32           
/*Maximum ASC clock frequency when fractional divider is disabled in 
asynchronous mode*/
#define ASC_MAX_CLK_ASYNC_FDV        16           
/*Maximum ASC clock frequency when fractional divider is enabled in 
asynchronous mode*/
#define ASC_MIN_CLK_ASYNC            (48 * 8192)  
/*Mnimum ASC clock frequency in asynchronous mode*/
#define ASC_MAX_CLK_SYNC             8            
/*Maximum ASC clock frequency in synchronous mode*/
#define ASC_MIN_CLK_SYNC             (12 * 8192)  
/*Minimum ASC clock frequency in synchronous mode*/


/*
  The following define specifies the number of ASC modules 
  are present on chip
*/
#if (ASC_PRODUCT == TC11IB)
#define ASC_HW_NUM 1            
#elif (ASC_PRODUCT == TC1130)
#define ASC_HW_NUM 3            
#endif

/*
  ASC hardware module base address
*/
#if (ASC_PRODUCT == TC11IB)
#define ASC_HW_0_ADDR 0xF0000800  /*ASC0 module base address*/
#elif (ASC_PRODUCT == TC1130)
#define ASC_HW_0_ADDR 0xF0100300  /*ASC0 module base address*/
#define ASC_HW_1_ADDR 0xF0100400  /*ASC0 module base address*/
#define ASC_HW_2_ADDR 0xF0100500  /*ASC0 module base address*/
#endif
 
/*
    Feature enabling:
*/
#define ASC_HW_IRDA     1     /* IrDA support off(0)/on(1): */
#define ASC_HW_FIFO_RX  8    /* Receive FIFO support off(0)/size(1-X): */
#define ASC_HW_FIFO_TX  8    /* Transmit FIFO support off(0)/size(1-X): */
#define ASC_HW_FDIV     1     /* Fractional Divider off(0)/on(1): */
#define ASC_HW_WHB_REG  1     
/* Hardware dependant bit setting register unavailable(0)/available(1): */
#define ASC_HW_AUTOBAUD 0     
/* Autobaud module unavailable(0)/available(1): */
#define ASC_HW_PISELCT  1     /* Peripheral Input select register*/


/*
    Register offsets:
*/
#define ASC_HW_CLC(n)           (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0000))
 /* Clock control register */

#if ASC_HW_PISELCT == 1 
#define ASC_HW_PISEL(n)         (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0004))
 /* Clock control register */
#endif /*ASC_HW_PISEL*/

#define ASC_HW_CON(n)           (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0010))
 /* Module control register */
#define ASC_HW_BG(n)            (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0014))
 /* Baud Rate / Timer reload register */
#define ASC_HW_FDV(n)           (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0018))
 /* Frequency divider register */
#define ASC_HW_PMW(n)           (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x001C))
 /* ASC IrDA Pulse mode and Width register */
#define ASC_HW_TBUF(n)          (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0020))
 /* ASC Tranmit Buffer register */
#define ASC_HW_RBUF(n)          (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0024))
 /* ASC Receive Buffer register */
#define ASC_HW_RXFCON(n)        (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0040))
 /* ASC Receive FIFO control register */
#define ASC_HW_TXFCON(n)        (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0044))
 /* ASC Transmit FIFO control register */
#define ASC_HW_FSTAT(n)         (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0048))
 /* ASC FIFO status register */
#define ASC_HW_WHB_CON(n)       (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x0050))
 /* ASC FIFO status register */

#define ASC_HW_TSRC(n)          (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x00F0))
 /* ASC Transmit ISR control register */
#define ASC_HW_RSRC(n)          (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x00F4))
 /* ASC Receive ISR control register */
#define ASC_HW_ESRC(n)          (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x00F8))
 /* ASC Error ISR control register */
#define ASC_HW_TBSRC(n)         (*(IFX_VUINT32 *)(ASC_addr_table[n] + 0x00FC))
 /* ASC Transmit Buffer ISR control register */

/* @topic2 ISR implementation details | */

/*
  @func ASC_TIR_ISR | ASC transmit Interrupt Service Routine
  @comm The implementation of this ISR is same as ASC_TBIR_ISR, enable either 
  TBIR or TIR interrupt at a time. This interrupt should be enabled for DMA 
  transmission mode. 
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Find the number of bytes can be written to IO ports.
  @flag: (DESIGN)  | - Write the pending request data to IO ports.
  @flag: (DESIGN)  | - Decrement the pending request size by the number of 
  data values written to ports.
  @flag: (DESIGN)  | - If the pending request size value is zero call the 
  user callback function provided the
          pending request support user callback function feature.
  @retval  None
*/
void ASC_TIR_ISR 
(
  IFX_UINT8  ASC_device /*@parm ASC hardware module identification number.*/
);

/*
  @func ASC_TBIR_ISR | ASC transmit buffer Interrupt Service Routine
  @comm The implementation of this ISR is same as ASC_TIR_ISR, enable either 
  TBIR or TIR interrupt at a time.
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Find the number of bytes can be written to IO ports.
  @flag: (DESIGN)  | - Write the pending request data to IO ports.
  @flag: (DESIGN)  | - Decrement the pending request size by the number of 
  data values written to ports.
  @flag: (DESIGN)  | - If the pending request size value is zero call the user
   callback function provided the
          pending request support user callback function feature.
  @retval  None
*/
void ASC_TBIR_ISR
(
  IFX_UINT8 ASC_device /*@parm ASC hardware module identification number.*/
);

/*
  @func ASC_RIR_ISR | ASC receive Interrupt Service Routine
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Copy the data bytes from read buffer to the pending 
  request. Decrement the pending request size value
          by the number of data values read from read buffer. 
  @flag: (DESIGN)  | - Update the read buffer pointers.
  @flag: (DESIGN)  | - If the data received from IO ports, read the received 
  data to the pending request.
  @flag: (DESIGN)  | - Read the received data from IO ports to the read buffer,
   if there are no pending requests or the number of
          bytes received from IO ports more than the size of pending request.
  @flag: (DESIGN)  | - If the pending request size is zero call the user 
  callback function provided pending request support the user callback function 
  feature.                  
  @retval  None
*/
void ASC_RIR_ISR
(
  IFX_UINT8 ASC_device /*@parm ASC hardware module identification number.*/
);

/*
  @func ASC_EIR_ISR | ASC error Interrupt Service Routine
  @head4 Implementation Details |
  @flag: (DESIGN)  | - Find the cause of error by reading control register.
  @flag: (DESIGN)  | - Increment the corresponding statistics counter.
  @flag: (DESIGN)  | - Read the received data if there are any pending requests
                       and update the request status with error value.
  @flag: (DESIGN)  | - Decrement the pending request size by the number of data
                       values copied.
  @flag: (DESIGN)  | - If no pending requests are available or the number
                       of bytes received data more than the pending requests,
          read data to read buffer and update the buffer status flag with error
           value.
  @flag | If the pending request size value becomes zero call the user callback
                     function provided pending request support.
  @retval  None
*/
void ASC_EIR_ISR
(
  IFX_UINT8 ASC_device /*@parm ASC hardware module identification number.*/
);


#if (IFX_COMPILER_GNU == 1)
/*
  @func ASC_HW_register_isr | Interrupt priority allocator and ISR initializer
  @head4 Implementation Details |
  @flag: (DESIGN)  | - If IFX_COMPILER_GNU feature is enabled the ISR will be 
  initialized.
  @retval  Success/Failure
  @flag 1 | On success
  @flag 0 | On failure
*/
IFX_UINT8 ASC_HW_register_isr (IFX_UINT8 ASC_hw_device);
#else
#define ASC_HW_register_isr(__ASC_HW_PARM)
#endif



/*
  Repeat the number of times as many units are present
  For example if the No. of ASC units are 3, use
  #define ASC_HW_INIT(__ASC_INIT_VAL) __ASC_INIT_VAL, __ASC_INIT_VAL,
   __ASC_INIT_VAL
*/
#if (ASC_HW_NUM == 1)
#define ASC_HW_INIT(__ASC_INIT_VAL) __ASC_INIT_VAL
#elif (ASC_HW_NUM == 3)
#define ASC_HW_INIT(__ASC_INIT_VAL) __ASC_INIT_VAL, __ASC_INIT_VAL,\
  __ASC_INIT_VAL
#endif

//***** Maybe a redundant function for setting the parity bit 
#define ASC_HW_set_stop(__ASC_HW_DEV, __ASC_HW_S)  

#endif /*__ASC_IDL_H*/

