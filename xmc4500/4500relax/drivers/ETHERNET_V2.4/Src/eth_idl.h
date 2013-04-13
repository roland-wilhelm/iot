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
** @FILENAME@:       eth_idl.h
** @VERSION@:        2.4
** @DATE@:           20/1/2006
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: Provides the hardware dependent features like registers address
**           mapping and control bit position in corresponding register. 
**           While porting to new hardware this file has to be ported.User can
**           configure the required functionality of the Ethernet LLD 
**           in this file.
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
** 20/1/2006       Badarinath Jayashree   Verison number bumped to 2.4 to match
**                 (IFIN CSW AIM)         the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/
/* @doc DESIGN */

#ifndef __ETH_IDL_H
#define __ETH_IDL_H

/*----------------------include user defined header files------------------------*/
#include "compiler.h"
#include "sys_api.h"

/*--------------- Product and version deffinition macros ------------------------*/

/* Define the product this layer is written for: */
#define ETH_PRODUCT TC1130
/* ETH IDL Major Version 0 compliant layer: */
#define ETH_HW_API_VER_MAJ 0     
/* ETH IDL Minor Version 1 compliant layer: */
#define ETH_HW_API_VER_MIN 1
/* Internal HAL version: */
#define ETH_HW_HAL_VER "Implemenation for ETH IDL API Specification V0.1"

/*
  The following define specifies the number of Ethernet modules 
  are present on chip
*/
#define ETH_HW_NUM          1            /* Number of ETH modules on chip: */
#define ETHERNET_DEVICE     0



/***--------------- Implementation specific memory map definitions -------***/

/*
  Following defines are for the Ethernet controller module in TC11IB. All 
  macros point to the corresponding value located at their respective address.
  To read/write into any of these locations the macros mentioned below will be
   used as normal variables. 
*/

/*---------------- Implementation specific memory map definitions -------**/
#define ETH_HW_0_ADDR            0xF2000100


/****************************** MAC unit register addresses mapping****************************************/
# define ETH_HW_MACCTRL           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0210) /* MAC control register */
# define ETH_HW_MACCAMCTRL0       *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0214) /* MAC CAM control register 0 */
# define ETH_HW_MACTXCTRL         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0218) /* MAC Transmit control register */
# define ETH_HW_MACTXSTAT         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x021C) /* MAC transmit status register */
# define ETH_HW_MACRXCTRL         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0220) /* MAC receive control register */
# define ETH_HW_MACRXSTAT         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0224) /* MAC receive status register */
# define ETH_HW_MACSMDATA         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0228) /* MAC station management data register */
# define ETH_HW_MACSMCTRL         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x022C) /* MAC station management control register */        
# define ETH_HW_MACCAMADDR        *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0230) /* MAC CAM address register */
# define ETH_HW_MACCAMDATA        *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0234) /* MAC CAM data register */
# define ETH_HW_MACCAMCTRL1       *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0238) /* MAC CAM control register 1 */
# define ETH_HW_MACMERRCNT        *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x023C) /* MAC missed error count register */
# define ETH_HW_MACPSECNT         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0240) /* MAC pause count register */
# define ETH_HW_MACRPSECNT        *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0244) /* MAC remote pause count register */
# define ETH_HW_MACTX0IMR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0248) /* MAC transmit 0 interrupt mask register */
# define ETH_HW_MACTX0ISR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x024C) /* MAC tranmsit 0 interrupt status register */
# define ETH_HW_MACTX1IMR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0250) /* MAC transmit 1 interrupt mask register */
# define ETH_HW_MACTX1ISR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0254) /* MAC transmit 1 interrupt mask register */
# define ETH_HW_MACRX0IMR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0268) /* MAC receive 0 interrupt mask register */
# define ETH_HW_MACRX0ISR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x026C) /* MAC receive 0 interrupt status register */
# define ETH_HW_MACRX1IMR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0270) /* MAC receive 1 interrupt mask register */
# define ETH_HW_MACRX1ISR         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0274) /* MAC receive 1 interrupt status register */



/*********************Receive buffer unit register addresses mapping**********/
# define ETH_HW_RBCC              *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0318) /*RB channel command register */
# define ETH_HW_RBCBL             *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x031C) /*RB channel burst length register */
# define ETH_HW_RBFPM             *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0320) /*RB free pool monitor register */
# define ETH_HW_RBFPTH            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0324) /*RB free pool threshold register */
# define ETH_HW_RBFPCNT           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0330) /*RB free pool count register */


/********************Transmit buffer unit register addresses mapping**********/
# define ETH_HW_TBISR            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0414) /*TB interrupt status register */
# define ETH_HW_TBCC             *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0418) /*TB channel command register */
# define ETH_HW_TBCPR            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x041C) /*TB channel parameter register */


/*********Data Management Unit receive unit register addresses mapping********/
# define ETH_HW_DRISFIFO         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0018) /*DMUR interrupt staus FIFO */
# define ETH_HW_DRFFCR           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x001C) /*DMUR FIFO full counter register */
# define ETH_HW_DRCMD            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0020) /*DMUR command register */
# define ETH_HW_DRMOD            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0024) /*DMUR mode register */
# define ETH_HW_DRFRDA           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x002C) /*DMUR first receive descriptor address register */
# define ETH_HW_DRIMR            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0030) /*DMUR interrupt mask register */
# define ETH_HW_DRCONF           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0034) /*DMUR configuration register */



/*********Data Management Unit transmit unit register addresses mapping********/
# define ETH_HW_DTCMD            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0118) /*DMUT command register */
# define ETH_HW_DTFTDA           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0120) /*DMUT first transmit descriptor address register */
# define ETH_HW_DTIMR            *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0124) /*DMUT interrupt mask register */
# define ETH_HW_DTCONF           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0128) /*DMUT configuration register */
# define ETH_HW_DTCONF3          *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x012C) /*DMUT configuration 3 register */
# define ETH_HW_DTISFIFO         *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x0138) /*DMUT interrupt status FIFO register */
# define ETH_HW_DTFFCR           *(IFX_VUINT32 *)(ETH_HW_0_ADDR + 0x013C) /*DMUT FIFO full counter register */

/*
  Ethernet Service Request Control registers address mapping
*/

#define ETH_HW_MACTX0SRC        *(IFX_VUINT32 *)(0xF000007C) /*MACTX0 Service Request Control register*/
#define ETH_HW_MACRX0SRC        *(IFX_VUINT32 *)(0xF0000080) /*MACRX0 Service Request Control register*/
#define ETH_HW_MACTX1SRC        *(IFX_VUINT32 *)(0xF0000084) /*MACTX1 Service Request Control register*/
#define ETH_HW_MACRX1SRC        *(IFX_VUINT32 *)(0xF0000088) /*MACRX1 Service Request Control register*/

#define ETH_HW_RBSRC0           *(IFX_VUINT32 *)(0xF000008C) /*RB0 Service Request Control register */
#define ETH_HW_RBSRC1           *(IFX_VUINT32 *)(0xF0000090) /*RB1 Service Request Control register */ 

#define ETH_HW_TBSRC            *(IFX_VUINT32 *)(0xF0000094) /*TB Service Request Control register */

#define ETH_HW_DRSRC            *(IFX_VUINT32 *)(0xF0000098) /*DMUR Service Request Control register */

#define ETH_HW_DTSRC            *(IFX_VUINT32 *)(0xF000009C) /*DMUT Service Request Control register */

/* @topic2 ISR implementation details | */

/*
  @func ETH_MACRX0_ISR | MAC receive control Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - Analyze the interrupt cause from the interrupt status register.
  @flag | - Update the statistics counters provided ETH_CFG_STAT_LOG feature is enabled.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_MACRX0_ISR(
  IFX_UINT8 ETH_device	/*@parm Ethernet controller hardware module identification number*/
);

/*
  @func ETH_MACTX0_ISR | MAC TX control Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - Analyze the interrupt cause from the interrupt status register.
  @flag | - Update the statistics counters provided ETH_CFG_STAT_LOG feature is enabled.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_MACTX0_ISR( 
  IFX_UINT8 ETH_device /*@parm Ethernet controller hardware module identification number*/
);

/*
  @func ETH_RB0_ISR | Receive Buffer free pool Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - Update the statistics counters provided ETH_CFG_STAT_LOG feature is enabled.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_RB0_ISR( 
  IFX_UINT8 ETH_device /*@parm Ethernet controller hardware module identification number*/
);

/*
  @func ETH_RB1_ISR | Receive Buffer action queue count Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - Update the statistics counters provided ETH_CFG_STAT_LOG feature is enabled.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_RB1_ISR( 
  IFX_UINT8 ETH_device /*@parm Ethernet controller hardware module identification number*/
);

/*
  @func ETH_TB_ISR | Transmit Buffer Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - If this interrupt occurs set the flag to indicate that the 
            commands(init, off) issued are failure.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_TB_ISR(
  IFX_UINT8 ETH_device /*@parm Ethernet controller hardware module identification number*/
);

/*
  @func ETH_DMUT_ISR | Data Management Unit Transmit Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - Analyze the interrupt cause from the interrupt status register.
  @flag | - By default handles the HI (Host Initiated) interrupt when DMUT branching 
            from one descriptor to next descriptor.
  @flag | - In HI interrupt handler release the data buffer of current descriptor, and update the descriptor list pointers.
  @flag | - Update the statistics counters provided ETH_CFG_STAT_LOG feature is enabled.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_DMUT_ISR(
  IFX_UINT8 ETH_device /*@parm Ethernet controller hardware module identification number*/
);

/*
  @func ETH_DMUR_ISR | Data Management Unit Receive Interrupt Service Routine
  @head4 Implementation Details |
  @flag | - Analyze the interrupt cause from the interrupt status register.
  @flag | - By default handles the FE (Frame End) and HTAB (Hold Transmit Abort) interrupts.
  @flag | - In Frame End interrupt find the length of frame, create the buffer of size as frame length. Copy
            the frame data into created buffer. Call the application registered call back function and pass the buffer.
  @flag | - Update the descriptor list pointers.
  @flag | - In HTAB interrupt handler stop the DMUR and MAC receiver cancel all the data buffers which contain the 
            frame fragments. Rearrange the descriptors and data buffers. Enable the DMUR and MAC receiver.
  @flag | - Update the statistics counters provided ETH_CFG_STAT_LOG feature is enabled in ETH_CFG.H file.
  @flag | - Enable the global interrupts as soon as enter into ISR.
  @flag | - This function should be compiler independent.
  @retval  None
*/
void ETH_DMUR_ISR(
  IFX_UINT8 ETH_device, /*@parm Ethernet controller hardware module identification number*/
  void     *ETH_os_specific
);

#if (IFX_COMPILER_GNU == 1)
/*
  @func ETH_HW_register_isr | Interrupt priority allocator and ISR initializer
  @head4 Implementation Details |
  @flag | - If SYS_CFG_ALLOC_INT feature is enabled requested priorities will be allocated
            through the System HAL.
  @flag | - If IFX_COMPILER_GNU feature is enabled the ISR will be initialized.
  @retval  Success/Failure
  @flag 1 | On success
  @flag 0 | On failure
*/
IFX_UINT8 ETH_HW_register_isr (
  IFX_UINT8 ETH_hw_device /*@parm Ethernet controller hardware module identification number*/
);
#else
# define ETH_HW_register_isr(__ETH_HW_PARM)
#endif
/*
  This is used as a initial value to initialize the init and busy flag arrays 
*/

#define ETH_HW_INIT(__ETH_INIT_VAL) __ETH_INIT_VAL

#define ETH_HW_set_stop(__ETH_HW_DEV, __ETH_HW_S) 

#endif /*__ETH_IDL_H */

