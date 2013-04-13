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
** @FILENAME@:       COMPILER.H
** @VERSION@:        3.0
** @DATE@:           17/01/2006    
**
** =============================================================================
**
** Project: TC1130
** Block: ALL MODULES.
**
** =============================================================================
** Contents:  This file contains Compiler dependent specific definitions for 
**            LLDs compatibility with different tool chains.
**            The compiler being used will be auto detected.
**            The currently supported compilers are 
**            GNU     - 2.4 version onwards.
**            TASKING - 1.5, 2.0x version onwards.
**            eLINUX -  2.4.19 version onwards. 
**            The DAVE compatible definitions are also supported.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 05/12/2002 	  Jonathan Fox (DC BRS)	   Created.    
** 16/03/2004     Ranganatha (DC BA)       Rewrote to support linux, tasking and 
**                                         GNU definitions. 
** 2/08/2004      Jayashree(DC BA)         Added support for eLinux enable and 
**                                         disable definitions
** @CHANGE_HISTORY@
** =============================================================================
*/
/*@doc API */

#ifndef __IFX_TYPES_H
#define __IFX_TYPES_H

/* 
 * @topic2 Compiler dependent APIs | 
 *			  Compiler dependent specific definitions for compatibility 
 *            purposes. The compiler being used will be auto detected.
 *            The currently supported compilers are 
 *            GNU     - 2.4 version onwards.
 *            TASKING - 1.5, 2.0x version onwards.
 *            eLINUX -  2.4.19 version onwards. 
 *            The DAVE compatible definitions are also supported.
 *            Appropriate errors are generated at compile time if compilers
 *            are old versions and also if there is a mismatch.
 */


/*--------------------------------------------------------------------
 * Storage macros
 *-------------------------------------------------------------------*/

/*
  'U' - unsigned
  'S' - signed
  'V' - volatile
  'ST' - static
  'STU' - static unsigned char

  Note: Some compilers provide option to treat char as insigned char.
  If that option is enabled, then IFX_SINT8 here will be treated as 
  unsigned. User is recommended not to enable that option.
*/   
#define IFX_SINT8    char
#define IFX_UINT8    unsigned char
#define IFX_VUINT8   volatile unsigned char
#define IFX_VSINT8   volatile char
#define IFX_STINT8   static char
#define IFX_STUINT8  static unsigned char

#define IFX_SINT16   short
#define IFX_UINT16   unsigned short
#define IFX_VUINT16  volatile unsigned short
#define IFX_VSINT16  volatile short
#define IFX_STINT16  static short
#define IFX_STUINT16 static unsigned short

#define IFX_SINT32   int
#define IFX_UINT32   unsigned int
#define IFX_VUINT32  volatile unsigned int
#define IFX_VSINT32  volatile int
#define IFX_STUINT32 static unsigned int
#define IFX_STUINT32 static unsigned int
#define IFX_ULONG    unsigned long
#define IFX_SFLOAT   float
#define IFX_CONSTANT const


#define IFX_ISR_FUNC(_INT_NUMBER, _FUNC_NAME) \
         void _interrupt(_INT_NUMBER) _FUNC_NAME(void)

/* 
@def  ENABLE_GLOBAL_INTERRUPT |
Use this for enabling the global interrupt definition.   
*/
#ifdef __KEIL__


#define ENABLE_GLOBAL_INTERRUPT   __enable_irq

#define DISABLE_GLOBAL_INTERRUPT  __disable_irq

#else 
#define ENABLE_GLOBAL_INTERRUPT  _enable
/*
@def  DISABLE_GLOBAL_INTERRUPT |
Use this for disabling the global interrupt definition.   
*/
#define DISABLE_GLOBAL_INTERRUPT _disable
#endif 
#endif /* #ifndef __IFX_TYPES_H */



