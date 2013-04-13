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
** @FILENAME@:       USB_IIL_COMMON.H
** @VERSION@:        4.2
** @DATE@:           23/01/2006  
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents:  This file contains common definitions used across the USB 
**            HAL files
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004     Ranganatha (DC BA)      
**                                        
** @CHANGE_HISTORY@
** =============================================================================
*/
#ifndef _USB_IIL_COMMON_H_
#define _USB_IIL_COMMON_H_


/* bit positions */
#define BIT_0   0x00000001
#define BIT_1   0x00000002
#define BIT_2   0x00000004
#define BIT_3   0x00000008
#define BIT_4   0x00000010
#define BIT_5   0x00000020
#define BIT_6   0x00000040
#define BIT_7   0x00000080
#define BIT_8   0x00000100
#define BIT_9   0x00000200
#define BIT_10  0x00000400
#define BIT_11  0x00000800
#define BIT_12  0x00001000
#define BIT_13  0x00002000
#define BIT_14  0x00004000
#define BIT_15  0x00008000

#define BIT_16  (16<<BIT_0)
#define BIT_17  (16<<BIT_1)
#define BIT_18  (16<<BIT_2)
#define BIT_19  (16<<BIT_3)
#define BIT_20  (16<<BIT_4)
#define BIT_21  (16<<BIT_5)
#define BIT_22  (16<<BIT_6)
#define BIT_23  (16<<BIT_7)
#define BIT_24  (16<<BIT_8)
#define BIT_25  (16<<BIT_9)
#define BIT_26  (16<<BIT_10)
#define BIT_27  (16<<BIT_11)
#define BIT_28  (16<<BIT_12)
#define BIT_29  (16<<BIT_13)
#define BIT_30  (16<<BIT_14)
#define BIT_31  (16<<BIT_15)

#ifndef IFX_MIN
#define IFX_MIN(X,Y)  ((X) < (Y) ? (X) : (Y))
#endif

#ifndef IFX_MAX
#define IFX_MAX(X,Y)  ((X) > (Y) ? (X) : (Y))
#endif



#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


/*
  Bit definitions of USB devices 
*/
#define EP0    0
#define EP1    1
#define EP2    2 
#define EP3    3
#define EP4    4
#define EP5    5
#define EP6    6
#define EP7    7
#define EP8    8
#define EP9    9
#define EP10   10

#define CF_0   0
#define CF_1   1

#define IF_0   0
#define IF_1   1
#define IF_2   2
#define IF_3   3

#define AS_0   0
#define AS_1   1
#define AS_2   2

#define EP_IN   1		   /*device to host*/
#define EP_OUT  0          /*host to device*/

#define EP_TYPE_CNTR   0x00			/*Control EP */
#define EP_TYPE_ISO    0x01        /*Isochronous EP*/ 
#define EP_TYPE_BULK   0x02		   /*Bulk type EP*/
#define EP_TYPE_INTR   0x03		   /*Interrupt EP*/

#ifndef NULL
#define NULL 0
#endif

#endif /*_USB_IIL_COMMON_H_*/


