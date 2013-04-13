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
** @FILENAME@:       usb_idl_cfg.h
** @VERSION@:        4.2
** @DATE@:           23/01/2006  
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents:  This file contains functions that use the USBD module.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 2/12/2005     Jayashree (IFIN CSW AIM) The new macro for switch between automatic
**                                        and manual mode has been added
** =============================================================================
*/
/* @doc API */

#ifndef _USB_IDL_CFG_H_
#define _USB_IDL_CFG_H_

#include "compiler.h"
#include "usb_iil_common.h"
#include "sys_cfg.h"

/* 
* The user can configure the USBD parameters like USB configuration block 
* and USBD endpoint properties here.
*/


/*
@def    USBD_CFG_DEVICE_FULL_SPEED | 
This will hold the full speed or low speed device definition. Equate this
to 1 for FULL speed and 0 for LOW speed device. TC1130 supports FULL SPEED
only.
*/


#define USBD_CFG_DEVICE_FULL_SPEED       1


/*
  @def USBD_CFG_TOTAL_EP_USED | 
  Declare the maximum endpoints (logical eps) used by this device including EP0. 
  This defintion will be common to GLOBAL_USBD_CFG_BLOCKS, 
  GLOBAL_USBD_CFG_BUFFER & endpoint interrupts definitions. 
*/

#define USBD_CFG_TOTAL_EP_USED 3

/*
  @def USBD_MANUAL_MODE | USBD_AUTO_MODE 
  This defintion is for switching between the automatic and manual mode.
  USBD_MANUAL_MODE for manual mode and USBD_AUTO_MODE for automatic mode 
*/

//#define USBD_MANUAL_MODE
#define USBD_AUTO_MODE

// EP0 

#define USBD_CFG_BLOCK_00 \
( EP0 << 0x04 ) | CF_0,          /* BYTE0 */ \
( ( IF_0 << 0x04 ) | AS_0),       /* BYTE1 */ \
( EP_TYPE_CNTR << 0x04 ) | ( EP_OUT << 3 ) | (  0x7 & (8  >> 7 )), /* BYTE2 */ \
( ( 8 ) & 0x07F ) << 1 ,          /* BYTE3 */ \
0x00,                             /* BYTE4 */ \
EP0                              /* BYTE5 */

// EP1 at IF1-AS1

#define USBD_CFG_BLOCK_11 \
( EP1 << 0x04 ) | CF_1,          /* BYTE0 */ \
( ( IF_1 << 0x04 ) | AS_1),       /* BYTE1 */ \
( EP_TYPE_BULK << 0x04 ) | ( EP_IN << 3 ) | (  0x7 & (64  >> 7 )), /* BYTE2 */ \
( ( 64 ) & 0x07F ) << 1 ,          /* BYTE3 */ \
0x00,                             /* BYTE4 */ \
EP1                              /* BYTE5 */

// EP2 at IF1-AS1

#define USBD_CFG_BLOCK_21 \
( EP2 << 0x04 ) | CF_1,          /* BYTE0 */ \
( ( IF_1 << 0x04 ) | AS_1),       /* BYTE1 */ \
( EP_TYPE_BULK << 0x04 ) | ( EP_OUT << 3 ) | (  0x7 & (64  >> 7 )), /* BYTE2 */ \
( ( 64 ) & 0x07F ) << 1 ,          /* BYTE3 */ \
0x00,                             /* BYTE4 */ \
EP2                              /* BYTE5 */


/*
@def GLOBAL_USBD_CFG_BLOCKS |
Contains 6-byte USB Configuration block for all EPs
Add all the defined USBD_CFG_BLOCK_n blocks here.
*/
#define GLOBAL_USBD_CFG_BLOCKS \
USBD_CFG_BLOCK_00,\
USBD_CFG_BLOCK_11,\
USBD_CFG_BLOCK_21

/* 
@def USBD_CFG_BLOCK_LENGTH | 
Change this value according to the maximum number of USBD_CFG_BLOCK_n 
defined in GLOBAL_USBD_CFG_BLOCKS. User need not modify this value.
6 bytes for each block.
*/

#define  USBD_CFG_BLOCK_LENGTH      6 * USBD_CFG_TOTAL_EP_USED


/*
------------------------------------------------------------------------
*	Below are EPP defintions 
------------------------------------------------------------------------
*/ 
#define BUFFER_SIZE_8       0               /*Buffer size is 8    bytes*/
#define BUFFER_SIZE_16      1               /*Buffer size is 16   bytes*/
#define BUFFER_SIZE_32      2               /*Buffer size is 32   bytes*/
#define BUFFER_SIZE_64      3               /*Buffer size is 64   bytes*/
#define BUFFER_SIZE_128     4               /*Buffer size is 128  bytes*/
#define BUFFER_SIZE_256     5               /*Buffer size is 256  bytes*/
#define BUFFER_SIZE_512     6               /*Buffer size is 512  bytes*/
#define BUFFER_SIZE_1024    7               /*Buffer size is 1024 bytes*/


/* 
@def USBD_CFG_BUFFER_EPx[0-11] |
 
Configure the buffer area for endpoint 0 
The fisrt parameter is buffer size & second is number of buffers. 
The total size is each buffer size multiplied by number of buffers. 
Donot change the configuration of EP0.

*/

/*@def 	 USBD_CFG_BUFFER_EP EP_00 */
#define	 USBD_CFG_BUFFER_EP0     BUFFER_SIZE_8,12


/*@def 	 USBD_CFG_BUFFER_EP EP_01 */
#define	 USBD_CFG_BUFFER_EP1     BUFFER_SIZE_64,6


/*@def 	 USBD_CFG_BUFFER_EP EP_02 */
#define	 USBD_CFG_BUFFER_EP2     BUFFER_SIZE_64,6


/* @def 	 GLOBAL_USBD_CFG_BUFFER | 
Holds all the cofigured buffer properties for all endpoints. 
*/
#define   GLOBAL_USBD_CFG_BUFFER \
{ USBD_CFG_BUFFER_EP0 },\
{ USBD_CFG_BUFFER_EP1 },\
{ USBD_CFG_BUFFER_EP2 }

/*
@def USBD_CFG_BLOCK_LENGTH |
Holds the lenght of total bytes used in GLOBAL_USBD_CFG_BUFFER.
User need not modify this value. 2 bytes for each buffer.
*/

#define  USBD_CFG_GLOBAL_BUFFER_LENGTH      2 * USBD_CFG_TOTAL_EP_USED


/************************************************************************
@head2 | 
Configure the End point properties defintions.
All device interrupts are on source node 0.
EP1 on source node 1 
EP2 on source node 2 
EP3 on source node 3 
EP4 on source node 4 
EP5 on source node 5 
EP6, EP7 on source node 6 
EP8, EP9, EP10  are on source node 7 
Non-supported endpoints should be filled with value 0x00.
************************************************************************/

/* Definitions for usb source nodes */
#define USBD_IRQ_SRC_NODE_0     0
#define USBD_IRQ_SRC_NODE_1     1
#define USBD_IRQ_SRC_NODE_2     2
#define USBD_IRQ_SRC_NODE_3     3
#define USBD_IRQ_SRC_NODE_4     4
#define USBD_IRQ_SRC_NODE_5     5
#define USBD_IRQ_SRC_NODE_6     6
#define USBD_IRQ_SRC_NODE_7     7

/* priority for source nodes */
#define USB_SRC7_PRIORITY		0x57
#define USB_SRC6_PRIORITY		0x56
#define USB_SRC5_PRIORITY		0x55
#define USB_SRC4_PRIORITY		0x54
#define USB_SRC3_PRIORITY		0x53
#define USB_SRC2_PRIORITY		0x52
#define USB_SRC1_PRIORITY		0x51
#define USB_SRC0_PRIORITY		0x50

/* @def    USBD_CFG_DEVICE_INTERRUPT |
This will hold the for all device interrupts for DIER register.
This will also hold interrupt source node of device interrupts.
Currently all Device interrupts are configure on source node 0.
*/
#define USBD_CFG_DEVICE_INTERRUPT  { USBD_IRQ_SRC_NODE_0, 0x77FF }


#define USBD_CFG_INTERRUPT_EP0    USBD_IRQ_SRC_NODE_0,0x0000

#define USBD_CFG_INTERRUPT_EP1    USBD_IRQ_SRC_NODE_1,0x0001

#define USBD_CFG_INTERRUPT_EP2    USBD_IRQ_SRC_NODE_2,0x0001

/* @def    USBD_CFG_EP_INTERRUPT_GLOBAL |
This will hold all endpoint interrupt values for EPICn register.
Eventhough definition includes all interrupts, the driver will
use upto the maximum EPs configured - USBD_CFG_TOTAL_EP_USED.
Donot modify this value.
*/

#define   USBD_CFG_EP_INTERRUPT_GLOBAL \
{ USBD_CFG_INTERRUPT_EP0 },\
{ USBD_CFG_INTERRUPT_EP1 },\
{ USBD_CFG_INTERRUPT_EP2 }

#endif  /* _USB_IDL_CFG_H_ */
