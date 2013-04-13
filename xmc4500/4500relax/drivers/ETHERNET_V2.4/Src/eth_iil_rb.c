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
** @FILENAME@:       eth_iil_rb.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006  
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file provides the API which are related to RB module. The
**           provided APIs are not directly available to user application
**
** =============================================================================
** References: ETH Design book
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby,Rajesh    Release after code review.
** 06/04/2004      Ruby					  Rizal's comments
** 29/04/2004      Ruby					  Rizal's application note
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
** 20/01/2006      Badarinath Jayashree   Version number bumped to 2.4 to match
**		           (IFIN SCC AI)          the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/

/*
  Include all the required header files needed for this file
*/
#include "eth_api.h"
/*
*******************************************************************************
* Function Name:     ETH_initialise_rb
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  None
*
* Description:
*   Initialise the Receive Buffer controller by setting the config registers and
*   issueing an INIT command
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*   ETH_setup         - Configuration parameters
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_initialise_rb(
  ETH_DEVICE     ETH_device,/* Ethernet controller hardware module 
                              identification value */
  ETH_COM_PARAMS *ETH_setup /* Configuration parameters, to be programmed to the
                                  RB kernel registers  */

)
{

 if((ETH_setup->rb_conf.fwd_threshold > ETH_HW_MAX_RBFTC )||
    (ETH_setup->rb_conf.actq_threshold > ETH_HW_MAX_RBAQC )
    )
 {
   return ETH_ERR;
 } 

  /*Set the forward threshold code*/
  ETH_HW_RBCBL = BIT32_MASK(ETH_setup->rb_conf.fwd_threshold, ETH_HW_RBCBL_FTC);  

  /*Set free pool and action queue count values*/
  ETH_HW_RBFPTH = 
       BIT32_MASK(ETH_setup->rb_conf.actq_threshold, ETH_HW_RBFPTH_RBAQ) | 
       BIT32_MASK(ETH_setup->rb_conf.free_pool_threshold, ETH_HW_RBFPTH_RBDB);
 
 
  /*Enable RB0 interrupt*/
  ETH_HW_RBSRC0 |= (BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                    BIT32_MASK(SYS_ETH_RB0, ETH_SRC_SRPN)|
                    BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE)); 

  /*Enable the RB1 interrupt*/
  ETH_HW_RBSRC1 |= (BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                    BIT32_MASK(SYS_ETH_RB1, ETH_SRC_SRPN)|
                    BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE)); 

  /*Initialize the RB channel, by issueing an INIT command*/
  ETH_HW_RBCC = ETH_HW_RB_INIT;

 return ETH_SUCCESS;
}

/*
*******************************************************************************
* Function Name:     ETH_terminate_rb
*
* Calling Functions: ETH_terminate_dev
*
* Functions Called:  None
*
* Description:
*   Stop the receive buffer and reset the RB interrupt control registers.
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_TERMINATE == 1
ETH_STATUS ETH_terminate_rb(ETH_DEVICE ETH_device)
{
  /*Disable free pool monitor and action queue interrupts*/
  ETH_HW_RBSRC0 = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);
  ETH_HW_RBSRC1 = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_TERMINATE*/

/*
*******************************************************************************
* Function Name:     ETH_RB0_ISR
*
* Calling Functions: External peripheral receive buffer zero interrupt
*
* Functions Called:  
*
* Description:
*   This function will take the approprite action depend upon the interrupt 
*   occurred either by calling user provided routine or the defalut action 
*   provided by HAL
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

void ETH_RB0_ISR (IFX_UINT8 ETH_dev)
{
# if ETH_CFG_STAT_LOG == 1
  /*
    This ISR will handle the free pool count interrupt. The information is not
    available about the free pool counter to implement the handler code.
  */
# endif	/*ETH_CFG_STAT_LOG*/
}

/*
*******************************************************************************
* Function Name:     ETH_RB1_ISR
*
* Calling Functions: External peripheral receive buffer one interrupt
*
* Functions Called:  
*
* Description:
*   This function will take the approprite action depend upon the interrupt 
*   occurred either by calling user provided routine or the defalut action 
*   provided by HAL
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure 
*
*******************************************************************************
*/

void ETH_RB1_ISR (IFX_UINT8 ETH_dev)
{
# if ETH_CFG_STAT_LOG == 1
  /*
    This ISR will handle the action queue count interrupt. The information is 
    not available about the action queue count to implement the handler code.
  */
# endif	/*ETH_CFG_STAT_LOG*/
}

