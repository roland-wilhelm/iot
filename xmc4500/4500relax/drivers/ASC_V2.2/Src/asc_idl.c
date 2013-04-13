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
** @FILENAME@:       ASC_IDL.c
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ASC 
**
** =============================================================================
** Contents: This file provides the wrappers for Interrupt Service Routines. 
**           The wrappes are GNU and Tasking compiler dependent.
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

#include "compiler.h"
#include "asc_idl.h"
#include "sys_cfg.h"

#if (IFX_COMPILER_GNU == 1)
/*
*******************************************************************************
* Function Name:     ASC_hw_register_isr
*
* Description   :
*   This routine will allocate the priorities for the ASC controller module
*   interrupts. Priorities are defined in SYS_CFG.h file. 
*   If the value of define SYS_CFG_ALLOC_INT is 1, the priorities will be 
allocated 
*   from System HAL.
*   This function will also initialize the ISRs which are compiler dependednt
*   provided the define value of IFX_COMPILER_GNU is 1. The IFX_COMPILER_GNU 
is defined
*   in COMPILER.h file
*  
*******************************************************************************
*/
IFX_UINT8 ASC_HW_register_isr (IFX_UINT8 ASC_hw_device)
{
  switch (ASC_hw_device)
  {
    /*
      The following are the compiler dependent ISR wrappers.
      The ISR wrapper arguments are priority number, ISR name and 
      hardware module identification number. Priority numbers are defined 
      in SYS_CFG.h header file. These ISR wrappers place the ISRs in interrupt
      vector base table.
    */
    case 0:
      #if SYS_ASC0_TIR > 0
      IFX_ISR_INIT (SYS_ASC0_TIR, ASC_TIR_ISR, 0);
      #endif

      #if SYS_ASC0_TBIR > 0
      IFX_ISR_INIT (SYS_ASC0_TBIR, ASC_TBIR_ISR, 0);
      #endif

      IFX_ISR_INIT (SYS_ASC0_RIR, ASC_RIR_ISR, 0);
      IFX_ISR_INIT (SYS_ASC0_EIR, ASC_EIR_ISR, 0);
    break;

    case 1:
      #if SYS_ASC1_TIR > 0
      IFX_ISR_INIT (SYS_ASC1_TIR, ASC_TIR_ISR, 1);
      #endif

      #if SYS_ASC1_TBIR > 0
      IFX_ISR_INIT (SYS_ASC1_TBIR, ASC_TBIR_ISR, 1);
      #endif

      IFX_ISR_INIT (SYS_ASC1_RIR, ASC_RIR_ISR, 1);
      IFX_ISR_INIT (SYS_ASC1_EIR, ASC_EIR_ISR, 1);
    break;

    case 2:
      #if SYS_ASC2_TIR > 0
      IFX_ISR_INIT (SYS_ASC2_TIR, ASC_TIR_ISR, 2);
      #endif

      #if SYS_ASC2_TBIR > 0
      IFX_ISR_INIT (SYS_ASC2_TBIR, ASC_TBIR_ISR, 2);
      #endif

      IFX_ISR_INIT (SYS_ASC2_RIR, ASC_RIR_ISR, 2);
      IFX_ISR_INIT (SYS_ASC2_EIR, ASC_EIR_ISR, 2);
    break;
 
    default:
      return 0;
  }
  return 1;
}
#endif /* IFX_COMPILER_GNU == 1 */


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
*******************************************************************************
*/

/* ISR wrappers for each ASC 0 interrupt */
# if ASC_HW_NUM >= 1

#if SYS_ASC0_TIR > 0
IFX_ISR_FUNC (SYS_ASC0_TIR, ASC_0_HW_ISR_TIR)
{
  ASC_TIR_ISR (0);
}
#endif

#if SYS_ASC0_TBIR > 0
IFX_ISR_FUNC (SYS_ASC0_TBIR, ASC_0_HW_ISR_TBIR)
{
  ASC_TBIR_ISR (0);
}
#endif

IFX_ISR_FUNC (SYS_ASC0_RIR, ASC_0_HW_ISR_RIR)
{
  ASC_RIR_ISR (0);
}

IFX_ISR_FUNC (SYS_ASC0_EIR, ASC_0_HW_ISR_EIR)
{
  ASC_EIR_ISR (0);
}
# endif /*ASC_HW_NUM >= 1*/


/* ISR wrappers for each ASC 1 interrupt */
# if ASC_HW_NUM >= 2

#if SYS_ASC1_TIR
IFX_ISR_FUNC (SYS_ASC1_TIR, ASC_1_HW_ISR_TIR)
{
  ASC_TIR_ISR (1);
}
#endif

#if SYS_ASC1_TBIR
IFX_ISR_FUNC (SYS_ASC1_TBIR, ASC_1_HW_ISR_TBIR)
{
  ASC_TBIR_ISR (1);
}
#endif

IFX_ISR_FUNC (SYS_ASC1_RIR, ASC_1_HW_ISR_RIR)
{
  ASC_RIR_ISR (1);
}

IFX_ISR_FUNC (SYS_ASC1_EIR, ASC_1_HW_ISR_EIR)
{
  ASC_EIR_ISR (1);
}
# endif /*ASC_HW_NUM >= 2*/

/* ISR wrappers for each ASC 2 interrupt */
# if ASC_HW_NUM >= 3

#if SYS_ASC2_TIR > 0
IFX_ISR_FUNC (SYS_ASC2_TIR, ASC_2_HW_ISR_TIR)
{
  ASC_TIR_ISR (2);
}
#endif

#if SYS_ASC2_TBIR > 0
IFX_ISR_FUNC (SYS_ASC2_TBIR, ASC_2_HW_ISR_TBIR)
{
  ASC_TBIR_ISR (2);
}
#endif

IFX_ISR_FUNC (SYS_ASC2_RIR, ASC_2_HW_ISR_RIR)
{
  ASC_RIR_ISR (2);
}

IFX_ISR_FUNC (SYS_ASC2_EIR, ASC_2_HW_ISR_EIR)
{
  ASC_EIR_ISR (2);
}
# endif /* ASC_HW_NUM >= 3 */


#endif /* IFX_COMPILER_TASKING == 1 */



