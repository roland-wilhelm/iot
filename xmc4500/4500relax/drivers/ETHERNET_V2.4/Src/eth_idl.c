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
** @FILENAME@:       eth_idl.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ETHERNET HAL 
**
** =============================================================================
** Contents: This file provides the wrappers for Interrupt Service Routines.
**           The wrappes are compiler dependent.
**
** =============================================================================
** References: ETH_Design_Book.pdf
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh,Ruby          Release after code review.
** 06/04/2004      Ruby					  Rizal's comments
** 29/04/2004      Ruby					  Rizal's comments
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
** 20/1/2006       Badarinath Jayashree   Version number bumped to 2.4 to match
**		           (IFIN CSW AIM)          the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/
#include "eth_api.h"
/*
*******************************************************************************
* Function Name:     ETH_hw_register_isr
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  
*  ETH_alloc_priorities and following compiler dependent function IFX_ISR_INIT
*
* Description   :
*   This routine will allocate the priorities for the Ethernet controller module
*   interrupts. Priorities are defined in INT_CFG.H file. 
*   If the value of define SYS_CFG_ALLOC_INT is 1, the priorities will be allocated 
*   from System HAL and updated in System HAL priority table.
*   This function will return error, If the requested priorities are not available 
*   at System HAL
*   This function will also initialize the ISRs which are compiler dependednt
*   provided the define value of IFX_COMPILER_GNU is 1. The IFX_COMPILER_GNU is defined
*   in COMPILER.H file
*  
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if (IFX_COMPILER_GNU == 1)
IFX_UINT8 ETH_HW_register_isr (IFX_UINT8 ETH_device)
{
  switch (ETH_device)
  {
    case 0:

    /*
      The following are the compiler dependent ISR wrappers.
      The ISR wrapper arguments are priority number, ISR name and 
      hardware module identification number. Priority numbers are defined 
      in INT_CFG.H header file. The ISR wrappers place the ISRs in interrupt
      vector base table.
    */

    IFX_ISR_INIT (SYS_ETH_MACRX0, ETH_MACRX0_ISR, 0);  /*MAC rx0 ISR init wrapper*/
    IFX_ISR_INIT (SYS_ETH_MACTX0, ETH_MACTX0_ISR, 0);  /*MAC tx0 ISR init wrapper*/

    IFX_ISR_INIT (SYS_ETH_RB0,    ETH_RB0_ISR, 0);     /*RB 0 ISR init wrapper*/
    IFX_ISR_INIT (SYS_ETH_RB1,    ETH_RB1_ISR, 0);     /*RB 1 ISR init wrapper*/

    IFX_ISR_INIT (SYS_ETH_TB,     ETH_TB_ISR, 0);      /*TB ISR init wrapper*/

    IFX_ISR_INIT (SYS_ETH_DMUT,   ETH_DMUT_ISR, 0);    /*DMUT ISR init wrapper*/

    IFX_ISR_INIT (SYS_ETH_DMUR,   ETH_DMUR_ISR, 0);   /*DMUR ISR init wrapper*/
      
    break;

    default:
      return 0;
   }
  return 1;
}
#endif /* IFX_COMPILER_GNU == 1 */



/*
*******************************************************************************
* Function Name:     Compiler dependednt general ISR wrappers
*
* Calling Functions: None
*
* Functions Called:  None
*
* Description:         
*   The following routines are compiler dependent ISR wrappers. The arguments
*   are priority and ISR name. Theses ISR wrappers will place the ISRs
*   in Interrupt Vector Base table.
*   The define IFX_COMPILER_TASKING is defined in COMPILER.H file 
*
* Input parameters:
*  Priority, ISR name
*  
* Output parameters: None
*
* Return Values:     None
*
*******************************************************************************
*/



#if IFX_COMPILER_TASKING == 1

# if SYS_ETH_MACRX0
  IFX_ISR_FUNC (SYS_ETH_MACRX0, ETH_HW_ISR_MACRX0) /*MAC Rx0 ISR wrapper*/
  {
    ETH_MACRX0_ISR (ETHERNET_DEVICE);
  }
#endif
#ifdef XXXXXXXXXXXXXXX
# if SYS_ETH_MACTX0
  IFX_ISR_FUNC (SYS_ETH_MACTX0, ETH_HW_ISR_MACTX0) /*MAC tx0 ISR wrapper*/
  { 
    ETH_MACTX0_ISR (ETHERNET_DEVICE);
  }
# endif

# if SYS_ETH_RB0
  IFX_ISR_FUNC (SYS_ETH_RB0, ETH_HW_ISR_RB0)    /*RB 0 ISR wrapper*/
  {
    ETH_RB0_ISR (ETHERNET_DEVICE);
  }
# endif

# if SYS_ETH_RB1
  IFX_ISR_FUNC (SYS_ETH_RB1, ETH_HW_ISR_RB1)   /*RB 1 ISR wrapper*/
  {
    ETH_RB1_ISR (ETHERNET_DEVICE);
  }
# endif

# if SYS_ETH_TB
  IFX_ISR_FUNC (SYS_ETH_TB, ETH_HW_ISR_TB)    /*TB ISR wrapper*/
  {
    ETH_TB_ISR (ETHERNET_DEVICE);
  }
# endif

# if SYS_ETH_DMUT  
  IFX_ISR_FUNC (SYS_ETH_DMUT, ETH_HW_ISR_DMUT) /*DMUT ISR wrapper*/
  {
    ETH_DMUT_ISR (ETHERNET_DEVICE);
  }
# endif

# if SYS_ETH_DMUR
  IFX_ISR_FUNC (SYS_ETH_DMUR, ETH_HW_ISR_DMUR) /*DMUR ISR wrapper*/
  {
    ETH_DMUR_ISR (ETHERNET_DEVICE, NULL);
  }
# endif
#endif /* IFX_COMPILER_TASKING == 1 */
#endif
