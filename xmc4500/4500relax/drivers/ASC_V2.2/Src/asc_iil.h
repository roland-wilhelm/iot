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
** @FILENAME@:       ASC_IIL.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ASC 
**
** =============================================================================
** Contents: Contains the bit positions and bit masks related to ASC module.  
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

#ifndef __ASC_IIL_H
#define __ASC_IIL_H


#include "compiler.h"
#include "asc_idl.h"

/*
    ASC Register fields:
*/

#define ASC_HW_CON_STP  3 /* Stop bit selection bit */
#define ASC_HW_CON_REN  4 /* Receiver enable control */
#define ASC_HW_CON_PEN  5 /* Parity check enable bit */
#if ASC_HW_IRDA == 1
#define ASC_HW_CON_RXDI 5 /* IrDA only RXD invert bit */
#endif
#define ASC_HW_CON_FEN  6 /* Framing error check enable bit */
#define ASC_HW_CON_OEN  7 /* Overrun check enable bit       */
#define ASC_HW_CON_PE   8 /* Parity error flag bit  */
#define ASC_HW_CON_FE   9 /* Framing error flag bit */
#define ASC_HW_CON_OE   10 /* Overrun error flag bit */
#if ASC_HW_FDIV == 1
#define ASC_HW_CON_FDE  11 /* Fractional divider enable bit */
#endif 
#define ASC_HW_CON_ODD  12   /* Parity selection bit (odd/even) */
#define ASC_HW_CON_BRS  13 /* Baud rate prescaler select bit */
#define ASC_HW_CON_LB   14 /* Loop back mode enable bit */
/* Baud rate generator run control (ASC enable) bit */
#define ASC_HW_CON_R    15 

/* IrDA pulse mode/width register bit */
#if ASC_HW_IRDA == 1
#define ASC_HW_PMW_IRPW 8 /* IrDA pulse width mode control bit */ 
#endif

/* Receive FIFO control bits */
#define ASC_HW_RXFCON_RXFEN     0 /* Receive FIFO enable bit */
#define ASC_HW_RXFCON_RXFFLU    1 /* Receive FIFO flush bit */
#define ASC_HW_RXFCON_RXTMEN    2 
/* Receive FIFO transparent mode enable bit */

 /* Transmit FIFO control bits */
#define ASC_HW_TXFCON_TXFEN     0 /* Transmit FIFO enable bit */
#define ASC_HW_TXFCON_TXFFLU    1 /* Transmit FIFO flush bit */
#define ASC_HW_TXFCON_TXTMEN    2 
/* Transmit FIFO transparent mode enable bit */

/* Interrupt Service Request Control bits */
#define ASC_HW_SRC_SRE      12 /* Service request enable bit */
#define ASC_HW_SRC_SRR      13 /* Service request flag bit */
#define ASC_HW_SRC_CLRR     14 /* Service request enable control bit */
#define ASC_HW_SRC_SETRR    15 /* Service request disable control bit */

  
/*
    Masks and location 
*/
#define ASC_HW_SET       1
#define ASC_HW_RST       0

/* Control register mode selection bits */
#define ASC_HW_CON_M    0x00000007 /* Mode selection */
#define ASC_HW_CON_M_loc 0 

/* Receive buffer register bits */
#define ASC_HW_TBUF_TD 0x000001FF   /* Transmit data register value */

/* Receive buffer register bits */
#define ASC_HW_RBUF_RD 0x000001FF   /* Receive data register value */

/* Baud rate timer/reload register bits */
#define ASC_HW_BG_BR    0x00001FFF  /* Baud rate reload value bit field */
#define ASC_HW_BG_BR_loc 0

/* Fractional Divider Register bits */
#if ASC_HW_FDIV == 1
#define ASC_HW_FDV_FD   0x000001FF /* Fractional divider value bit field */
#define ASC_HW_FDV_FD_loc 0
#endif

/* IrDA Pulse mode/width register bits */
#if ASC_HW_IRDA == 1
#define ASC_HW_PMW_PW   0x000000FF /* IrDA pulse width value bit field */ 
#define ASC_HW_PMW_PW_loc 0
#endif


/* Receive FIFO control register bits */
#define ASC_HW_RXFCON_RXFITL    0x00000F00 
/* Receive FIFO interrupt trigger level */
#define ASC_HW_RXFCON_RXFITL_loc    8 
/* Receive FIFO interrupt trigger level */

/* Transmit FIFO control register bits */
#define ASC_HW_TXFCON_TXFITL    0x00000F00 
/* Transmit FIFO interrupt trigger level */
#define ASC_HW_TXFCON_TXFITL_loc    8 
/* Transmit FIFO interrupt trigger level */

/* FIFO status register bits */
#define ASC_HW_FSTAT_RXFFL    0x0000000F /* Receive FIFO filling level */
#define ASC_HW_FSTAT_RXFFL_loc    0      
/* Receive FIFO filling level location */
#define ASC_HW_FSTAT_TXFFL    0x00000F00 
/* Transmit FIFO filling level */
#define ASC_HW_FSTAT_TXFFL_loc      8

/* Interrupt Service Request Control register bit fields */
#define ASC_HW_SRC_SRPN    0x000000FF 
/* Service request Priority number field */
#define ASC_HW_SRC_SRPN_loc  0

#define ASC_HW_SRC_TOS     0x00000C00 /* Type of Service field */

#define ASC_HW_CLC_RMC     0x0000FF00
#define ASC_HW_CLC_RMC_loc 8

/* Other custom masks */
#define ASC_HW_CON_TRNS    0x0000101F 
/* Control for mode, Receive, Parity and Stop bits */
#define ASC_HW_CON_ERRS    0x000000E0 /* Control of Error checking enables*/

#define  ASC_HW_CON_ERRORS       0x000000700
#define  ASC_HW_CON_ERRORS_loc   8  

#if ASC_HW_WHB_REG == 1
#define ASC_HW_WHB_ERRORS      0x000000700
#define ASC_HW_WHB_ERRORS_loc  8
#define ASC_HW_WHB_SET_REN_loc  5
#define ASC_HW_WHB_CLR_REN_loc  4
#endif /*ASC_HW_WHB_REG*/

#if ASC_HW_PISELCT == 1 
#define ASC_HW_PISEL_REG         0
#define ASC_HW_PISEL_loc         0
#endif /*ASC_HW_PISEL*/

#define ASC_GET_FREQ(parm1, parm2)   (((parm2) == 0) ? 0 : (parm1 / parm2)) 

#endif /*__ASC_IIL_H*/

