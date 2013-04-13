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
** @FILENAME@:       ssc_idl.c
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
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
** 17/03/2004      Bhavjit Walha        Release after code review.
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

#include "compiler.h"
#include "ssc_idl.h"
#include "sys_cfg.h"

#if (IFX_COMPILER_GNU == 1)
IFX_UINT8 SSC_HW_register_isr (IFX_UINT8 SSC_hw_device)
{
  switch (SSC_hw_device)
  {
    case 0:
      IFX_ISR_INIT (SYS_SSC0_TIR, SSC_TIR_ISR, 0);
      IFX_ISR_INIT (SYS_SSC0_RIR, SSC_RIR_ISR, 0);
      IFX_ISR_INIT (SYS_SSC0_EIR, SSC_EIR_ISR, 0);
    break;

    case 1:
      #if SSC_HW_NUM > 1
      IFX_ISR_INIT (SYS_SSC1_TIR, SSC_TIR_ISR, 1);
      IFX_ISR_INIT (SYS_SSC1_RIR, SSC_RIR_ISR, 1);
      IFX_ISR_INIT (SYS_SSC1_EIR, SSC_EIR_ISR, 1);
      #endif /*SSC_HW_NUM*/
    break;
  }
  return 1;
}
#endif /* IFX_COMPILER_GNU == 1 */


#if IFX_COMPILER_TASKING == 1

/* ISR wrappers for each SSC 0 interrupt */
IFX_ISR_FUNC (SYS_SSC0_TIR, SSC_0_HW_ISR_TIR)
{
  SSC_TIR_ISR (0);
}

IFX_ISR_FUNC (SYS_SSC0_RIR, SSC_0_HW_ISR_RIR)
{
  SSC_RIR_ISR (0);
}

IFX_ISR_FUNC (SYS_SSC0_EIR, SSC_0_HW_ISR_EIR)
{
  SSC_EIR_ISR (0);
}

/* ISR wrappers for each SSC 1 interrupt */
IFX_ISR_FUNC (SYS_SSC1_TIR, SSC_1_HW_ISR_TIR)
{
  SSC_TIR_ISR (1);
}

IFX_ISR_FUNC (SYS_SSC1_RIR, SSC_1_HW_ISR_RIR)
{
  SSC_RIR_ISR (1);
}

IFX_ISR_FUNC (SYS_SSC1_EIR, SSC_1_HW_ISR_EIR)
{
  SSC_EIR_ISR (1);
}

#endif /* IFX_COMPILER_TASKING == 1 */


