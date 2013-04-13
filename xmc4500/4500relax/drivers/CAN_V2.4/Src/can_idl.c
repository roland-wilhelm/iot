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
** @FILENAME@:       CAN_IDL.c
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: Implements wrappers for Interrupt Service Routines for GNU and 
**           Tasking compilers. The wrappes are compiler dependent.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      S.A.Kazmi          Release after code review.
** 07/05/2004      Mahesh             Restructured ISR registration with GNU and
**                                    Tasking compilers.   
** 21/06/2004      Mahesh             More comments added to code.  
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

#include "compiler.h"
#include "can_cfg.h"
#include "can_idl.h"
#include "can_iil.h"
#include "can_api.h"

#if (IFX_COMPILER_GNU == 1)
/*
*******************************************************************************
* Function Name:     ASC_hw_register_isr
*
* Description   :
*   This routine will allocate the priorities for the ASC controller module
*   interrupts. Priorities are defined in SYS_CFG.h file. 
*   If the value of define SYS_CFG_ALLOC_INT is 1, the priorities will be 
*   allocated from System HAL.
*   This function will also initialize the ISRs which are compiler dependednt
*   provided the define value of IFX_COMPILER_GNU is 1. The IFX_COMPILER_GNU 
*   is defined in COMPILER.h file
*  
*******************************************************************************
*/
void CAN_HW_register_isr (void)
{
    /*
      The following are the compiler dependent ISR wrappers.
      The ISR wrapper arguments are priority number, ISR name and 
      hardware module identification number. Priority numbers are defined 
      in SYS_CFG.h header file. These ISR wrappers place the ISRs in interrupt
      vector base table.

      Note:
      All four CAN nodes have their own CAN_RXMOBJ_ISR and CAN_TXMOBJ_ISR ISRs
	  and remaining ISR's are shared by all nodes.
    */
    IFX_ISR_INIT (SYS_CAN_SRN0,  CAN_TRANSFER_ISR,  0);

    IFX_ISR_INIT (SYS_CAN_SRN1,  CAN_RXMOBJ_ISR,  0);
    IFX_ISR_INIT (SYS_CAN_SRN2,  CAN_RXMOBJ_ISR,  1);
    IFX_ISR_INIT (SYS_CAN_SRN3,  CAN_RXMOBJ_ISR,  2);
    IFX_ISR_INIT (SYS_CAN_SRN4,  CAN_RXMOBJ_ISR,  3);

    IFX_ISR_INIT (SYS_CAN_SRN5,  CAN_TXMOBJ_ISR,  0);
    IFX_ISR_INIT (SYS_CAN_SRN6,  CAN_TXMOBJ_ISR,  1);
    IFX_ISR_INIT (SYS_CAN_SRN7,  CAN_TXMOBJ_ISR,  2);
    IFX_ISR_INIT (SYS_CAN_SRN8,  CAN_TXMOBJ_ISR,  3);

    IFX_ISR_INIT (SYS_CAN_SRN9,  CAN_ALERT_CFC_ISR,  0);
    IFX_ISR_INIT (SYS_CAN_SRN10, CAN_LEC_ISR, 0);

    return; 

}
#endif /*IFX_COMPILER_GNU*/


#if IFX_COMPILER_TASKING == 1
/*
*******************************************************************************
* Function Name:     Compiler dependednt general ISR wrappers
*
* Description:         
*   The following routines are compiler dependent ISR wrappers. The arguments
*   are priority and ISR name. Theses ISR wrappers will place the ISRs
*   in Interrupt Vector Base table.
*   The define IFX_COMPILER_TASKING is defined in COMPILER.h file 
*
*   Note:
*   All four CAN nodes have their own CAN_RXMOBJ_ISR and CAN_TXMOBJ_ISR ISRs
*   and remaining ISR's are shared by all nodes.
*
*******************************************************************************
*/


    IFX_ISR_FUNC(SYS_CAN_SRN0, ISR_SRN0)
	{
		CAN_TRANSFER_ISR(0);
	}
	
	IFX_ISR_FUNC(SYS_CAN_SRN1, ISR_SRN1)
	{
        CAN_RXMOBJ_ISR(0);
	}
	
	IFX_ISR_FUNC(SYS_CAN_SRN2, ISR_SRN2)
	{
        CAN_RXMOBJ_ISR(1);
	}
	
    IFX_ISR_FUNC(SYS_CAN_SRN3, ISR_SRN3)
	{
        CAN_RXMOBJ_ISR(2);
	}
	
    IFX_ISR_FUNC(SYS_CAN_SRN4, ISR_SRN4)
	{
        CAN_RXMOBJ_ISR(3);
	}			

	IFX_ISR_FUNC(SYS_CAN_SRN5, ISR_SRN5)
	{
        CAN_TXMOBJ_ISR(0);
	}

    IFX_ISR_FUNC(SYS_CAN_SRN6, ISR_SRN6)
	{
        CAN_TXMOBJ_ISR(1);
	}
	
	IFX_ISR_FUNC(SYS_CAN_SRN7, ISR_SRN7)
	{
        CAN_TXMOBJ_ISR(2);
	}
	
	IFX_ISR_FUNC(SYS_CAN_SRN8, ISR_SRN8)
	{
        CAN_TXMOBJ_ISR(3);
	}
	 
    IFX_ISR_FUNC(SYS_CAN_SRN9, ISR_SRN9)
	{
      CAN_ALERT_CFC_ISR(0);
	}

    IFX_ISR_FUNC(SYS_CAN_SRN10, ISR_SRN10)
    {
      CAN_LEC_ISR(0);
	}	 
	
#endif /* IFX_COMPILER_TASKING */


