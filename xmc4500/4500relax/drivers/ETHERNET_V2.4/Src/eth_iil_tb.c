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
** @FILENAME@:       eth_iil_tb.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006    
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file provides the API which are related to Transmit Buffer
**           module. The provided APIs are not directly available to user 
**           application
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
** 29/04/2004      Ruby					  Rizal's appl note
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
** 20/01/2006      Badarinath Jayashree   Version number bumped to 2.4 to match
**		           (IFIN CSW AIM)          the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/

/*
  Include all the required header files needed for this file
*/
#include "eth_api.h"
/*
*******************************************************************************
* Function Name:     ETH_initialise_tb
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  None
*
* Description:
*   Initialise the Transmit Buffer controlller by setting the config registers
*   and issueing an INIT command
*
* Input parameters:  
*   ETH_device      - Ethernet controller hardware module identification value
*   ETH_setup       - Configuration parameters
*
* Output parameters: None
*
* Return Values:    Success or Failure
*
*******************************************************************************
*/
ETH_STATUS ETH_initialise_tb (
ETH_DEVICE     ETH_device,
ETH_COM_PARAMS *ETH_setup
)
{
  /*Program the TB threshold codes*/
  /*The individual TX buffer size should be more than the sum of FWD and Refill 
    threshold codes*/
  if ( ((ETH_setup->tb_conf.fwd_threshold > ETH_HW_MAX_TBFTC) |
       (ETH_setup->tb_conf.refill_threshold > ETH_HW_MAX_TBRTC) | 
       (ETH_setup->tb_conf.ind_tx_buff_size > ETH_HW_MAX_TBBUFSIZE)) )
  {
    return ETH_ERR;
  }
  /* Check that the RTC + FTC < tx buffer size */  
  if((ETH_TB_threshold[ETH_setup->tb_conf.fwd_threshold] + 
      ETH_TB_threshold[ETH_setup->tb_conf.refill_threshold]) <
	  ETH_setup->tb_conf.ind_tx_buff_size)
  {
    ETH_HW_TBCPR = 
      BIT32_MASK(ETH_setup->tb_conf.fwd_threshold, ETH_HW_TBCPR_FTC)|  
      BIT32_MASK(ETH_setup->tb_conf.refill_threshold, ETH_HW_TBCPR_RTC)|
      BIT32_MASK(ETH_setup->tb_conf.ind_tx_buff_size, ETH_HW_TBCPR_ITBS); 
  
    /*Enable the TB interrupt*/
    ETH_HW_TBSRC |= (BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                     BIT32_MASK(SYS_ETH_TB, ETH_SRC_SRPN)|
                     BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE)); 

    /*Initialise the Transmit Buffer by issuing a init comamnd*/
    ETH_HW_TBCC = ETH_HW_TB_INIT;
  }
  else
  {
    return ETH_ERR;
  }
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
*   Initialise the Transmit Buffer controlller by setting the configuration 
*   registers and issueing an OFF command. reset the TB interrupt control reg
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification val
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_TERMINATE == 1
ETH_STATUS ETH_terminate_tb (ETH_DEVICE ETH_device)
{
  /*Disable the TB interrupt*/
  ETH_HW_TBSRC = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);

  /*stop the TB, by issueing an off command*/
  ETH_HW_TBCC = ETH_HW_TB_OFF;

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_TERMINATE*/


/*
*******************************************************************************
* Function Name:     ETH_ctrl_tb
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*   Reset the TX buffer configuration parameters like threshold values
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification val
*   ETH_ctrl_data     - New configuration parametrs
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_CTRL_TB == 1 
ETH_STATUS ETH_ctrl_tb (
ETH_DEVICE ETH_device,
ETH_TB_CONF *ETH_ctrl_data 
)
{

  if( (ETH_ctrl_data->fwd_threshold > ETH_HW_MAX_TBFTC) |
      (ETH_ctrl_data->refill_threshold > ETH_HW_MAX_TBRTC ) |
      (ETH_ctrl_data->ind_tx_buff_size > ETH_HW_MAX_TBBUFSIZE)
    )
    {
      return ETH_ERR;
    }
  /*
    Copy the configuration data which are to be updated into the ETH_params 
    (global) structure, which will maintain the updated configuartion 
    information
  */
  ETH_params.tb_conf.fwd_threshold     = ETH_ctrl_data->fwd_threshold;
  ETH_params.tb_conf.ind_tx_buff_size  = ETH_ctrl_data->ind_tx_buff_size;
  ETH_params.tb_conf.refill_threshold  = ETH_ctrl_data->refill_threshold; 

  /*Program the new configuration data into threshold code register through
    global configuration structure*/
  if((ETH_TB_threshold[ETH_params.tb_conf.fwd_threshold] + 
      ETH_TB_threshold[ETH_params.tb_conf.refill_threshold]) <
	  ETH_params.tb_conf.ind_tx_buff_size)
  {
    ETH_HW_TBCPR = BIT32_MASK(ETH_params.tb_conf.fwd_threshold,ETH_HW_TBCPR_FTC)|
                   BIT32_MASK(ETH_params.tb_conf.refill_threshold, ETH_HW_TBCPR_RTC)|
                   BIT32_MASK(ETH_params.tb_conf.ind_tx_buff_size, ETH_HW_TBCPR_ITBS);
  }
  else
  {
    return ETH_ERR;
  }
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_CTRL_TB*/

/*
*******************************************************************************
* Function Name:     ETH_TB_ISR
*
* Calling Functions: External peripheral TX buffer interrupt
*
* Functions Called:  
*
* Description:
*   This function will take the approprite action depend upon the interrupt 
*   occurred either by calling user provided routine or the defalut action 
*   provided by HAL
*
* Input parameters:  
*   ETH_device        - Ethernet controller hardware module identification val
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

void ETH_TB_ISR (IFX_UINT8 ETH_dev)
{
  ETH_isr_val = ETH_HW_TBISR;

  if(ETH_isr_val == BIT32_MASK(ETH_HW_SET,ETH_HW_TBISR_CMDF))
  {
    /* NO action */  
  }    
}

