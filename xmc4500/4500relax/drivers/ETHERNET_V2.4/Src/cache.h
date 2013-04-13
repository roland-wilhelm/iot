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
** @FILENAME@:       cache.h
** @VERSION@:        2.4
** @DATE@:           20/1/2006
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file contains #defines, data structures and function 
**            prototypes required for the Ethernet device driver
**
** =============================================================================
** References: ETH API book
**
** =============================================================================
** History:
**
** Date            Author                           Comment
** 20/01/2006      Adescom eLinux version 3.0       This file has been used to 
**                                      support data cache problem    
** @CHANGE_HISTORY@
** =============================================================================
*/
/* @doc API */ 
/*
 * arch/tricore/kernel/cache.h
*/

#include "sys_api.h"
# define PMU_CON1           *(IFX_VUINT32 *)(0xF87FFD14) /* PMU configuration register 1 */

#ifdef __KEIL__


#else 
#ifndef IFX_COMPILER_TASKING

static inline void cachea_w(void * addr)
{
#ifndef CONFIG_TRICORE_TRIBOARD_TC1130A
#ifdef CONFIG_TRICORE_TRIBOARD_TC1130B
	__asm__ __volatile__ ("nop");		/* DMI_TC_012 erratum */
#endif // CONFIG_TRICORE_TRIBOARD_TC1130B
	__asm__ __volatile__("cachea.w [%0]0" : : "a"(addr) : "memory");
#endif // CONFIG_TRICORE_TRIBOARD_TC1130A
} // cachea_w()

static inline void cachea_wi(void * addr)
{
#ifndef CONFIG_TRICORE_TRIBOARD_TC1130A
#ifdef CONFIG_TRICORE_TRIBOARD_TC1130B
	__asm__ __volatile__ ("nop");		/* DMI_TC_012 erratum */
#endif // CONFIG_TRICORE_TRIBOARD_TC1130B
	__asm__ __volatile__("cachea.wi [%0]0" : : "a"(addr) : "memory");
#endif // CONFIG_TRICORE_TRIBOARD_TC1130A
} // cachea_wi()

static inline void cachea_i(void * addr)
{
#ifndef CONFIG_TRICORE_TRIBOARD_TC1130A
#ifdef CONFIG_TRICORE_TRIBOARD_TC1130B
	__asm__ __volatile__ ("nop");		/* DMI_TC_012 erratum */
#endif // CONFIG_TRICORE_TRIBOARD_TC1130B
	__asm__ __volatile__("cachea.i [%0]0" : : "a"(addr) : "memory");
#endif // CONFIG_TRICORE_TRIBOARD_TC1130A
} // cachea_i()

static inline void invalidate_code_cache(void)
{
	unsigned icr;
	asm volatile("mfcr %0, $ICR; disable" : "=d"(icr));
	UNLOCK_ENDINIT_PROTECT
	PMU_CON1 |= 1;
	PMU_CON1 &= ~1;
	LOCK_ENDINIT_PROTECT
	asm volatile("mtcr $ICR, %0" : : "d"(icr));
} // invalidate_code_cache()
#endif 
#endif //IFX_COMPILER_TASKING

