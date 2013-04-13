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
** @FILENAME@:       sys_iil.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: Contains the bit positions and bit masks related to the SSC module.  
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

#ifndef __SSC_IIL_H
#define __SSC_IIL_H
/*
  Required include files:
*/
#include "compiler.h"
#include "sys_cfg.h"
#include "ssc_idl.h"

/* Data bits restriction */
#define SSC_HW_BM_MAX    16
#define SSC_HW_BM_MIN    2


/* Control register bits: */
#define SSC_HW_CON_HB       4  /* Heading control */
#define SSC_HW_CON_PH       5  /* Clock phase control bit */
#define SSC_HW_CON_PO       6  /* Clock parity control bit */
#define SSC_HW_CON_LB       7  /* Loop back mode enable bit */
#define SSC_HW_CON_TEN      8  /* Transmit error check enable bit  */
#define SSC_HW_CON_REN      9  /* Error error check enable bit */
#define SSC_HW_CON_PEN      10 /* Phase error check enable bit */
#define SSC_HW_CON_BEN      11 /* Baud rate error check enable bit */
#define SSC_HW_CON_AREN     12 /* Automatic reset enable bit */
#define SSC_HW_CON_MS       14 /* Mode ( master/slave ) select bit */
#define SSC_HW_CON_EN       15 /* Enable bit */

#define SSC_HW_CON_ERRORS       0x00000F00 
#define SSC_HW_CON_ERRORS_LOC   8 

/* Control register bits */
#define SSC_HW_CON_TE       8  /* Transmit error flag */
#define SSC_HW_CON_RE       9  /* Error error flag */
#define SSC_HW_CON_PE       10 /* Phase error flag */
#define SSC_HW_CON_BE       11 /* Baud rate error flag */
#define SSC_HW_CON_BSY      12 /* Busy flag */

#if SSC_HW_PISEL_FTR == 1
#define SSC_HW_PISEL1_REG       3
#define SSC_HW_PISEL_MRST_LOC   0       
#define SSC_HW_PISEL_MTSR_LOC   1
#define SSC_HW_PISEL_SCLK_LOC   2
#define SSC_HW_PISEL_SLSIS_LOC  3
#define SSC_HW_PISEL_STIP_LOC   8
#define SSC_HW_PISEL_SLSIS_MASK 0x00000038
#define SSC_HW_PISEL_STIP_MASK  0x00000100
#endif

#if SSC_HW_SLAVE_SEL_FTR == 1
#define SSC_HW_SSOC_AOL_LOC     0
#define SSC_HW_SSOC_AOL_MASK    0x000000FF
#define SSC_HW_SSOC_OEN_LOC     8
#define SSC_HW_SSOC_OEN_MASK    0x0000FF00

#define SSC_HW_SSOTC_LEAD_DELY_LOC     0
#define SSC_HW_SSOTC_LEAD_DELY_MASK    0x00000003
#define SSC_HW_SSOTC_TRL_DELY_LOC      2
#define SSC_HW_SSOTC_TRL_DELY_MASK     0x0000000C
#define SSC_HW_SSOTC_INCT_DELY_LOC     4
#define SSC_HW_SSOTC_INCT_DELY_MASK    0x00000030
#define SSC_HW_SSOTC_SLSO7_LOC         8
#define SSC_HW_SSOTC_SLSO7_MASK        0x00000100
#endif

#if SSC_HW_FDV_FTR == 1
#define SSC_HW_FDV_STEP_LOC     0
#define SSC_HW_FDV_MODE_LOC     14
#define SSC_HW_FDV_NORMAL_MODE  1       
#define SSC_HW_FDV_FRACTN_MODE  2       
#define SSC_HW_FDV_MASK         0x0000C000
#define SSC_HW_SUSPCTRL         0 
#define SSC_HW_SUSPCTRL_MASK    0x00003000 
#define SSC_HW_SUSPCTRL_LOC     12
#endif

#if SSC_HW_RMC_FTR == 0
#define SSC_HW_DIS_CLK_LOC 0
#endif

/* Receive FIFO control bits */
#define SSC_HW_RXFCON_RXFEN     0 /* Receive FIFO enable bit */
#define SSC_HW_RXFCON_RXFFLU    1 /* Receive FIFO flush bit */
#define SSC_HW_RXFCON_RXTMEN    2 /* Receive FIFO transparent mode enable bit */

 /* Transmit FIFO control bits */
#define SSC_HW_TXFCON_TXFEN     0 /* Transmit FIFO enable bit */
#define SSC_HW_TXFCON_TXFFLU    1 /* Transmit FIFO flush bit */
#define SSC_HW_TXFCON_TXTMEN    2 /* Transmit FIFO transparent mode enable bit */

/* Interrupt Service Request Control bits */
#define SSC_HW_SRC_SRE      12 /* Service request enable bit */
#define SSC_HW_SRC_SRR      13 /* Service request flag bit */
#define SSC_HW_SRC_CLRR     14 /* Service request enable control bit */
#define SSC_HW_SRC_SETR     15 /* Service request disable control bit */


/* Interrupt Service Request Control register bit fields */
#define SSC_HW_SRC_SRPN      0x000000FF /* Service request Priority number field */
#define SSC_HW_SRC_TOS       0x00000400 /* Type of Service field */
#define SSC_HW_SRC_SRPN_LOC  0

/*
    SSC Register masks:
*/
/* Control register mode selection bits */
#define SSC_HW_CON_BM        0x0000000F /* Data width selection */
#define SSC_HW_CON_BM_LOC    0 
#define SSC_HW_CON_BC        0x0000000F /* Data width selection */
#define SSC_HW_CON_BC_LOC    0

/* Baudrate timer/reload register bits */
#define SSC_HW_BR_BR         0x0000FFFF /* Baud rate reload value bit field */
#define SSC_HW_BR_BR_LOC     0

/* Receive buffer register bits */
#define SSC_HW_TB_TD_VALUE 0x0000FFFF  /* Transmit data register value */
#define SSC_HW_TB_TD_LOC   0

/* Receive buffer register bits */
#define SSC_HW_RB_RD_VALUE 0x0000FFFF  /* Receive data register value */
#define SSC_HW_RB_RD_LOC   0

/* Receive FIFO control register bits */
#define SSC_HW_RXFCON_RXFITL        0x00000700 /* Recive FIFO interrupt trigger level */
#define SSC_HW_RXFCON_RXFITL_LOC    8 /* Receive FIFO interrupt trigger level */

/* Transmit FIFO control register bits */
#define SSC_HW_TXFCON_TXFITL        0x00000700 /* Transmit FIFO interrupt trigger level */
#define SSC_HW_TXFCON_TXFITL_LOC    8 /* Transmit FIFO interrupt trigger level */

/* FIFO status register bits */
#define SSC_HW_FSTAT_RXFFL        0x00000007 /* Receive FIFO filling level */
#define SSC_HW_FSTAT_RXFFL_LOC    0      /* Receive FIFO filling level location */
#define SSC_HW_FSTAT_TXFFL        0x00000700 /* Transmit FIFO filling level */
#define SSC_HW_FSTAT_TXFFL_LOC    8

#define SSC_HW_CLC_RMC     0x0000FF00
#define SSC_HW_CLC_RMC_LOC 8

#define SSC_GET_FREQ(parm1, parm2) ((parm2 == 0) ? 0 : ( (parm1 * 1.0) / (parm2 * 1.0) ))

#endif /*__SSC_IIL_H*/

