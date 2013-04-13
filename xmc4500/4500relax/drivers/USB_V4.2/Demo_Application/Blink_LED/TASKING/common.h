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
** @FILENAME@:       COMMON.H
** @VERSION@:        3.0
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block:  HAL LLD 
**
** =============================================================================
** Contents: Implements system definitions for the application interface.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                        Comment
** 16/03/2004      Ruby                          Initial release
** 08/06/2002      Jayashree                     Added IFX_DAVE_GEN macro for 
**                                               conditional compilation for DAvE.    
**
** @CHANGE_HISTORY@
** =============================================================================
*/
#ifndef __COMMON_H
#define __COMMON_H

/* Set the bit given by location */
#define SET(reg,location) ( (reg) = ((reg) | (0x00000001 << location)) )
/* Reset the bit given by location */
#define RESET(reg,location) ( (reg) = ((reg) & (~(0x00000001 << location))) )
/* Read the bits as specified by mask and location */
#define READBITS(reg,mask,location) ( (reg & mask ) >> location)
/* Write the value to the bit position as specified by mask and location */
#define WRITEBITS(reg,value,mask,location)\
  (reg = (reg & (~mask)) | (value << location))
/*Set a bit in specified location*/
#define SETBIT( REG, LOCATION ,BIT )	 \
 ((BIT) ? ( REG | ( BIT << LOCATION ) ) : ( REG &= (~( BIT << LOCATION )))) ;

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

#ifndef NULL
#define NULL 0
#endif

/*@def BIT32_MASK | Make the bit value(specified by "value") into 32 bit
  value,
  This define is used to create 32 bit value from the provided value. The 
  provided value(first argument) is left shifted by the given number of 
  locations (second argument).

  E.g. BIT32_MASK(1,4) will return 0x00000010 
*/
#define BIT32_MASK(value,location) (0x00000000 | (value << location))

/*@def NTOHL | Change the Big endian data to the little endian 32 bit value,
  NTOHL is used to change the big endian data to little endian 32 bit value.
  This is mainly used to typecast the char pointer to int pointer.
*/
#define NTOHL(val) (((val) << 24)| (((val) & 0x0000FF00) << 8) |\
       (((val) & 0x00FF0000) >> 8) | (((val) & 0xFF000000) >> 24))

/*
  The following defines are used for general purpose
  to set and reset the values of any variables 
*/
#define SET_BIT     1   /*To set the value of variable*/
#define RESET_BIT   0   /*To reset the value of variable*/
#define MAX16    0xFFFF /* Max 16 bit value */

/* Bit position definitions */
#ifndef IFX_DAVE_GEN
typedef volatile struct
{
	IFX_UINT32	bit0: 1 ;
	IFX_UINT32	bit1: 1 ;
	IFX_UINT32	bit2: 1 ;
	IFX_UINT32	bit3: 1 ;
	IFX_UINT32	bit4: 1 ;
	IFX_UINT32	bit5: 1 ;
	IFX_UINT32	bit6: 1 ;
	IFX_UINT32	bit7: 1 ;
	IFX_UINT32	bit8: 1 ;
	IFX_UINT32	bit9: 1 ;
	IFX_UINT32	bit10: 1 ;
	IFX_UINT32	bit11: 1 ;
	IFX_UINT32	bit12: 1 ;
	IFX_UINT32	bit13: 1 ;
	IFX_UINT32	bit14: 1 ;
	IFX_UINT32	bit15: 1 ;
	IFX_UINT32	bit16: 1 ;
	IFX_UINT32	bit17: 1 ;
	IFX_UINT32	bit18: 1 ;
	IFX_UINT32	bit19: 1 ;
	IFX_UINT32	bit20: 1 ;
	IFX_UINT32	bit21: 1 ;
	IFX_UINT32	bit22: 1 ;
	IFX_UINT32	bit23: 1 ;
	IFX_UINT32	bit24: 1 ;
	IFX_UINT32	bit25: 1 ;
	IFX_UINT32	bit26: 1 ;
	IFX_UINT32	bit27: 1 ;
	IFX_UINT32	bit28: 1 ;
	IFX_UINT32	bit29: 1 ;
	IFX_UINT32	bit30: 1 ;
	IFX_UINT32	bit31: 1 ;
}T_Reg32;
#endif
#endif /*__COMMON_H*/

