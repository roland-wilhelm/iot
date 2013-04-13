/* =============================================================================
** Copyright (C) 2006 Infineon Technologies.
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
** @FILENAME@:       eth_iil.h
** @VERSION@:        2.4
** @DATE@:           20/1/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file contains the bit positions pertaining to the Ethernet 
**           driver
** =============================================================================
** References: ETH Design book
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby,Rajesh    Release after code review.
** 06/04/2004                             Version number bumped to 2.1 to match 
**                                        the version of the C files 
** 29/04/2004                             Version number bumped to 2.2 to match 
**                                        the version of the C files 
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
** 20/1/2006       Badarinath Jayashree   Version number bumped to 2.4 to match
**		           (IFIN SCC AI)          the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/
/* @doc DESIGN */ 
#ifndef _ETH_IIL_H
#define	_ETH_IIL_H

/*
  The following defines are used for general purpose
  to set and reset the values of any variables 
*/
#define ETH_HW_SET     TRUE   /*To set the value of variable*/
#define ETH_HW_RST     FALSE   /*To reset the value of variable*/

/*
  Register bits offset values
*/
  /* MACCTRL register */
# define ETH_HW_MACCTRL_HLTREQ        0 
# define ETH_HW_MACCTRL_HLTIMM        1
# define ETH_HW_MACCTRL_RESET         2
# define ETH_HW_MACCTRL_FULLDUP       3
# define ETH_HW_MACCTRL_MACLP         4
# define ETH_HW_MACCTRL_MROLL         10

  /* MAC CAM control 0 register*/
# define ETH_HW_MACCAMCTRL0_STACC     0 
# define ETH_HW_MACCAMCTRL0_GPRACC    1
# define ETH_HW_MACCAMCTRL0_BRDACC    2
# define ETH_HW_MACCAMCTRL0_NEGCAM    3
# define ETH_HW_MACCAMCTRL0_CMPEN     4

  /*MAC CAM address register*/
#define ETH_HW_MACAMADDR_BSY          31 

  /*MAC TXCTRL */
# define ETH_HW_MACTXCTRL_TXEN        0 
# define ETH_HW_MACTXCTRL_TXHLT       1
# define ETH_HW_MACTXCTRL_NOPAD       2
# define ETH_HW_MACTXCTRL_NOCRC       3
# define ETH_HW_MACTXCTRL_NODEF       5
# define ETH_HW_MACTXCTRL_SDPSE       6
# define ETH_HW_MACTXCTRL_MII10       7

  /* MAC TX status register */
# define ETH_HW_MACTXSR_XCOL          4 
# define ETH_HW_MACTXSR_TXDEF         5
# define ETH_HW_MACTXSR_PSE           6
# define ETH_HW_MACTXSR_UNDER         8  
# define ETH_HW_MACTXSR_XDEF          9
# define ETH_HW_MACTXSR_LCAR          10
# define ETH_HW_MACTXSR_LCOL          12 
# define ETH_HW_MACTXSR_TXP           13
# define ETH_HW_MACTXSR_CMP           14 
# define ETH_HW_MACTXSR_TXHLTD        15 
# define ETH_HW_MACTXSR_SQERR         16

  /*MAC Rx Control Register */
# define ETH_HW_MACRXCTRL_RXEN        0
# define ETH_HW_MACRXCTRL_RXHLT       1
# define ETH_HW_MACRXCTRL_LOEN        2
# define ETH_HW_MACRXCTRL_SHEN        3
# define ETH_HW_MACRXCTRL_STRCRC      4
# define ETH_HW_MACRXCTRL_PCTLP       5
# define ETH_HW_MACRXCTRL_IGNCRC      6

  /* MAC Rx status register */
# define ETH_HW_MACRXSR_CTLFRX        5
# define ETH_HW_MACRXSR_ALIGNE        8
# define ETH_HW_MACRXSR_CRCE          9
# define ETH_HW_MACRXSR_OVER          10
# define ETH_HW_MACRXSR_LOE           11
# define ETH_HW_MACRXSR_RXPE          13
# define ETH_HW_MACRXSR_GOOD          14
# define ETH_HW_MACRXSR_RXHLTD        15

  /* MAC Station Management Control register*/
# define ETH_HW_MACSMCTRL_WR          10
# define ETH_HW_MACSMCTRL_BUSY        11
# define ETH_HW_PHY_REG_ADDR          0
# define ETH_HW_PHY_DEV               5

  /*PHY device control register offsets*/
# define ETH_HW_PHY_CTRL_FULLDUP      8
# define ETH_HW_PHY_CTRL_LOOPBACK     14
# define ETH_HW_PHY_CTRL_COL           7
# define ETH_HW_PHY_CTRL_SPEED13      13
# define ETH_HW_PHY_CTRL_AUTONEG      12
# define ETH_HW_PHY_CTRL_ISOLATE      10
# define ETH_HW_PHY_CTRL_RESET        15

  /* MAC CAM address register */
# define ETH_HW_MACCAMADDR_CAW        31


  /*MAC Tx Interrupt Mask Register */
# define ETH_HW_MACTXIMR_XCOL         4
# define ETH_HW_MACTXIMR_TXDEF        6
# define ETH_HW_MACTXIMR_PSE          7
# define ETH_HW_MACTXIMR_UNDER        8
# define ETH_HW_MACTXIMR_XDEF         9
# define ETH_HW_MACTXIMR_LCAR         10
# define ETH_HW_MACTXIMR_LCOL         11
# define ETH_HW_MACTXIMR_TXP          12
# define ETH_HW_MACTXIMR_CMP          13
# define ETH_HW_MACTXIMR_TXHLTD       14
# define ETH_HW_MACTXIMR_SQERR        15

  /*MAC Tx Interrupt Status Register */
# define ETH_HW_MACTXISR_XCOL         4
# define ETH_HW_MACTXISR_TXDEF        6
# define ETH_HW_MACTXISR_PSE          7
# define ETH_HW_MACTXISR_UNDER        8
# define ETH_HW_MACTXISR_XDEF         9
# define ETH_HW_MACTXISR_LCAR         10
# define ETH_HW_MACTXISR_LCOL         11
# define ETH_HW_MACTXISR_TXP          12
# define ETH_HW_MACTXISR_CMP          13
# define ETH_HW_MACTXISR_TXHLTD       14
# define ETH_HW_MACTXISR_SQERR        15

  /*MAC Rx Interrupt Mask Register */
# define ETH_HW_MACRXIMR_MROLL        23
# define ETH_HW_MACRXIMR_CTLFRX       24
# define ETH_HW_MACRXIMR_ALIGNE       25
# define ETH_HW_MACRXIMR_CRCE         26
# define ETH_HW_MACRXIMR_OVER         27
# define ETH_HW_MACRXIMR_LOE          28
# define ETH_HW_MACRXIMR_RXPE         29
# define ETH_HW_MACRXIMR_GOOD         30
# define ETH_HW_MACRXIMR_RXHLTD       31

  /*MAC Rx Interrupt Status Register */
# define ETH_HW_MACRXISR_MROLL        23
# define ETH_HW_MACRXISR_CTLFRX       24
# define ETH_HW_MACRXISR_ALIGNE       25
# define ETH_HW_MACRXISR_CRCE         26
# define ETH_HW_MACRXISR_OVER         27
# define ETH_HW_MACRXISR_LOE          28
# define ETH_HW_MACRXISR_RXPE         29 
# define ETH_HW_MACRXISR_GOOD         30
# define ETH_HW_MACRXISR_RXHLTD       31


  /*RB channel burst length register */
# define ETH_HW_RBCBL_FTC             0
# define ETH_HW_RBFPTH_RBDB           0
# define ETH_HW_RBFPTH_RBAQ           16

  /* RBFreePool Monitor register */
# define ETH_HW_RBFPM_FPMM            2
# define ETH_HW_RBFPM_IMASK           5


  /*TB interrupt status register */
# define ETH_HW_TBISR_CMDF            17

  /*TB channel parameter register*/
# define ETH_HW_TBCPR_RTC             8
# define ETH_HW_TBCPR_FTC             12
# define ETH_HW_TBCPR_ITBS            16


  /* DMUR interrupt status FIFO register */
# define ETH_HW_DRISFIFO_SD           7
# define ETH_HW_DRISFIFO_ILEN         8
# define ETH_HW_DRISFIFO_CRC          9
# define ETH_HW_DRISFIFO_RFOD         10
# define ETH_HW_DRISFIFO_MFL          11
# define ETH_HW_DRISFIFO_HRAB         12
# define ETH_HW_DRISFIFO_FE           13
# define ETH_HW_DRISFIFO_RAB          14
# define ETH_HW_DRISFIFO_HI           15
# define ETH_HW_DRISFIFO_CDMC         16

    /* DMUR Interrupt Mask register */
# define ETH_HW_DRIMR_CDMC            0 
# define ETH_HW_DRIMR_SD              2
# define ETH_HW_DRIMR_ILEN            8
# define ETH_HW_DRIMR_CRC             9
# define ETH_HW_DRIMR_RFOD            10
# define ETH_HW_DRIMR_MFL             11
# define ETH_HW_DRIMR_HRAB            12
# define ETH_HW_DRIMR_FE              13
# define ETH_HW_DRIMR_RAB             14

  /*DMUR Configuration register */
# define ETH_HW_DRCONF_ENA            0
# define ETH_HW_DRCONF_LBE            1
# define ETH_HW_DWORD_ALIGN           4
# define ETH_DMUR_SIZE_CHECK(DBUFF)\
(((DBUFF) < MAX16 && !((DBUFF)%ETH_HW_DWORD_ALIGN))?ETH_SUCCESS:ETH_ERR)


  /*DR mod register*/
# define ETH_HW_DRMOD_FRM             0
# define ETH_HW_DMUR_FRAME            0x0 /*This value is not a offset*/



  /*DMUT interrupt mask register */
# define ETH_HW_DTIMR_CMDC            0
# define ETH_HW_DTIMR_TAB             1
# define ETH_HW_DTIMR_HTAB            2

  /* DMUT Configuration register */
# define ETH_HW_DTCONF_LBE            1

  /*DMUT interrupt status FIFO register */
# define ETH_HW_DTISFIFO_HTAB         2
# define ETH_HW_DTISFIFO_CMDC         2
# define ETH_HW_DTISFIFO_TAB          3
# define ETH_HW_DTISFIFO_HI           4

/*
  The following macros are values not bit positions in
  the registers. These values can be used directly without
  using BIT32_MASK macro.
*/

  /*Pause control frames fields*/
# define ETH_HW_PAUSE_FIELDS 0x88080001/*which includes type field and opcode*/

# define ETH_HW_CAM_FILL_DATA         0x00000000  /*CAM filling data*/

# define ETH_HW_MAC_PAUSE_ADDR_FLDS  3

/*Pause control frame data storage location in CAM table*/                                         
# define ETH_HW_PAUSE_LOC1            30           
# define ETH_HW_PAUSE_LOC2            (ETH_HW_PAUSE_LOC1)+ 0x1                                                    
# define ETH_HW_PAUSE_LOC3            (ETH_HW_PAUSE_LOC1)+ 0x2
# define ETH_HW_PAUSE_LOC4            (ETH_HW_PAUSE_LOC1)+ 0x3
# define ETH_HW_PAUSE_LOC5            (ETH_HW_PAUSE_LOC1)+ 0x4

# define ETH_HW_PAUSE_CAM_MACADDR     0x00300003 /* TO Enable MAC addresses 
                                    in the CAM to send a pause control frame */

  /*PHY device constants*/
# define ETH_HW_PHY_RESET            0x8000
# define ETH_HW_FIRSTPHYDEV           0

# define ETH_HW_PHY_CTRL_REG          0
# define ETH_HW_PHY_STAT_REG          1
# define ETH_HW_PHY_WRITE             1 
# define ETH_HW_PHY_READ              0 
# define ETH_HW_SUP_PHYDEV            31 
# define ETH_HW_SUP_PHYREG            31 
# define ETH_HW_MIN_PHY_ADDR           1
# define ETH_HW_MAX_PHY_ADDR          31
# define ETH_HW_PHY_DEFAULT_ADDR       0 
# define ETH_HW_PHY_ANEG_CAPABLE      0x0008
# define ETH_HW_PHY_ANEG_ENABLE       0x1000
# define ETH_HW_PHY_ANEG_RESTART      0x0200    
# define ETH_HW_PHY_ANEG_COMPLETE     0x0020

/*
  The following defines are masks not bit positions. 
*/
# define ETH_HW_RB_INIT               0x00010000

# define ETH_HW_TB_INIT               0x01000000
# define ETH_HW_TB_OFF                0x02000000

# define ETH_HW_MAX_TBFTC             0x7
# define ETH_HW_MAX_TBRTC             0x7
# define ETH_HW_MAX_TBBUFSIZE         0xFF
   
# define ETH_HW_MAX_RBFTC             0x3
# define ETH_HW_MAX_RBFPC			  0xFF
# define ETH_HW_MAX_RBAQC			  0x20

  /*DMUR format modes*/
# define ETH_HW_DRCHANNEL_FMT         0xA8000000
# define ETH_HW_DRCMD_FMT             0x80000000

  /*DMUR commands*/
# define ETH_HW_DMUR_INIT             0x00010000
# define ETH_HW_DMUR_OFF              0x00020000
# define ETH_HW_DMUR_ABORT            0x00040000
# define ETH_HW_DMUR_HRST             0x00100000

  /*DMUT formats*/
# define ETH_HW_DT_FMTMASK            0x0000F800  
# define ETH_HW_DTCHANNEL_FMT         0x0000B800
# define ETH_HW_DTCMD_FMT             0x00009000

  /*DMUT commands*/
# define ETH_HW_DMUT_INIT             0x01000000
# define ETH_HW_DMUT_OFF              0x02000000
# define ETH_HW_DMUT_ABORT            0x04000000
# define ETH_HW_DMUT_HRST             0x08000000

  /*DMUT burst length constant*/
# define ETH_HW_DT_BURST_LEN          0x00020000

/*
  Following defines are the constants used to program the 
  Service Request Control register
*/
#define ETH_SRC_CPU      0x0 /*CPU define for the TOS bit*/
#define ETH_SRC_PCP      0x1 /*PCP define for the TOS bit*/
#define ETH_SRC_ENABLE   0x1 /*Set the value of interrupt arbitration bit*/
#define ETH_SRC_DISABLE  0x0 /*Reset the value of interrupt arbitration bit*/

/*
  Bit positions in a SRC register
*/
#define ETH_SRC_TOS   10   /*interrupt service provider*/
#define ETH_SRC_SRPN  0    /*interrupt priority*/
#define ETH_SRC_SRE   12   /*interrupt arbitration*/
#define ETH_SRC_SETR  15   /*To generate a s/w interrupt*/


#endif /* _ETH_IIL_H */

