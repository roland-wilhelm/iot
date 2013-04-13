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
** @FILENAME@:       eth_iil_dmut.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006    
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file provides the API which are related to DMUT module. The
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
** 29/04/2004      Ruby                   Change of DMUT queuing strategy
**
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
** 20/1/2006       Mahesh Sriram Babu     This file has been modified to support
**                 (IFIN CSW AIM)         cache with GNU Compiler (Note: The flag
**                                        ETH_CFG_USE_CACHE needs to be set in 
**                                        eth_cfg.h file
** @CHANGE_HISTORY@
** =============================================================================
*/
/*
  Include all the required header files needed for this file
*/
#include "eth_api.h"
#include "cache.h"
/*
*******************************************************************************
* Function Name:     ETH_initialise_dmut
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  None
*
* Description:
*  Initilise the Data Management Unit Transmit by initializing config registers
*  and allocating DMUT data descriptors(linked list) and buffers. Issue a INIT
*  comamnd
*
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  ETH_setup      -  Configuration parameters
*
* Output parameters: DMUT descriptor linked list and data buffers
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_initialise_dmut(ETH_DEVICE ETH_device,ETH_COM_PARAMS *ETH_setup)
{
  IFX_UINT8 desc_count = 0; 
  ETH_TXDESC  *ETH_saved_head = NULL;
  
  #ifndef IFX_COMPILER_TASKING
  int i;
  IFX_UINT32 *cache_addr;
  #endif //IFX_COMPILER_TASKING
 
  while(desc_count < ETH_CFG_DMUT_DESC_NUM)
  {
    ETH_dtdesc[desc_count].desc_id  = desc_count;
	ETH_dtdesc[desc_count].thi      = ETH_HW_SET;
    ETH_dtdesc[desc_count].cmp_en   = ETH_HW_SET;

    if( desc_count < (ETH_CFG_DMUT_DESC_NUM - 1))
    {
      ETH_dtdesc[desc_count].next   = &ETH_dtdesc[desc_count+1];
    }
    desc_count++;
  }
  /* Make a circular linked list where the next pointer of the last descriptor
     points to the first descriptor	 
  */     
  ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM - 1].next = &ETH_dtdesc[0];


  #ifndef IFX_COMPILER_TASKING
  if(((((IFX_UINT32)&ETH_dtdesc[0]) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)&ETH_dtdesc[0]) & 0xF0000000) == 0xC0000000))
  {
    desc_count = 0;
    while(desc_count < ETH_CFG_DMUT_DESC_NUM) {
       cache_addr = (int *) &ETH_dtdesc[desc_count];
       for (i = 0; i <= (sizeof(ETH_TXDESC) >> 4); i++) {
            cachea_w(cache_addr);
            cache_addr += 4;
       }
       desc_count++;
    }
  }
  #endif //IFX_COMPILER_TASKING
  /* Initialise the pointers and variables */
  ETH_pending_writes = 0;
  /* Head points to the last desc */
  ETH_dthead = &ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM - 1];
  /* Tail points to the first desc */
  ETH_dttail = &ETH_dtdesc[0];

  /*  Give the fisrt desc to the HW. Initialize it with dummy data */
  /* Save a pointer to the head desc */
  ETH_saved_head = (ETH_TXDESC*)ETH_dthead;
  /* Make the head point to an empty desc */
  ETH_dthead = ETH_dthead->next;
  /* Update the desc pointed by the head with dummy data to initialize the HW*/
  ETH_dthead->frm_end = ETH_HW_SET;  
  ETH_dthead->hold = ETH_HW_SET;
  ETH_dthead->no   = ETH_HW_RST;
  ETH_dthead->data = NULL;

  #ifndef IFX_COMPILER_TASKING
  if(((((IFX_UINT32)ETH_dthead) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_dthead) & 0xF0000000) == 0xC0000000))
  {
    cache_addr = (int *) ETH_dthead;
    for (i = 0; i <= (sizeof(ETH_TXDESC) >> 4); i++) {
       cachea_w(cache_addr);
       cache_addr += 4;
    }
  }
  #endif //IFX_COMPILER_TASKING
  /* Clear the HOLD bit of the previous desc */
  ETH_saved_head->hold = 0;

  #ifndef IFX_COMPILER_TASKING
  if(((((IFX_UINT32)ETH_saved_head) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_saved_head) & 0xF0000000) == 0xC0000000))
  {
    cachea_w(ETH_saved_head);
  }
  #endif //IFX_COMPILER_TASKING
  
  /* Increment the pending_writes flag */
  ETH_pending_writes++;

  /* Give the tail pointer to the Hardware */
  ETH_HW_DTFTDA         = (IFX_UINT32)ETH_dttail;

  /*Set the interrupt mask register*/
  ETH_HW_DTIMR  = BIT32_MASK(ETH_HW_SET,ETH_HW_DTIMR_CMDC)|
                  BIT32_MASK(ETH_HW_SET,ETH_HW_DTIMR_TAB);
   
  /*Set the endian mode*/
  ETH_HW_DTCONF  = 
    BIT32_MASK(ETH_setup->dmut_conf.endian_mode, ETH_HW_DTCONF_LBE);
 
  /*Set the burst length of a DTCONF3 register, which is constant */
  ETH_HW_DTCONF3 = ETH_HW_DT_BURST_LEN; 

  /*enable the DMUT interrupt*/
  ETH_HW_DTSRC  = (BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                   BIT32_MASK(SYS_ETH_DMUT, ETH_SRC_SRPN)|
                   BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE)); 
  /*Issue the init command to initialize the DMUT*/
  ETH_HW_DTCMD = ETH_HW_DMUT_INIT;

  return ETH_SUCCESS;
}

/*
*******************************************************************************
* Function Name:     ETH_terminate_dmut
*
* Calling Functions: ETH_termiante_dev
*
* Functions Called:  None
*
* Description:
*  Terminate the DMUT by freeing the allocated DMUT data descriptors and data
*  buffers. Issue a OFF comamnd to stop dmut. 
*
* Input parameters:  
*  ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_TERMINATE == 1
ETH_STATUS ETH_terminate_dmut (ETH_DEVICE ETH_device)
{
  ETH_TRANSFER ETH_tx;

  /*Issue an off comamnd, to stop the DMUT*/
  ETH_HW_DTCMD = ETH_HW_DMUT_OFF;

  while(ETH_pending_writes)
  {
    /* Release the data in the Transmit Descriptors */
	if(ETH_dttail->data != NULL)
    {
      /* Send the data buffer to the application.
	     The application is free to re-use this buffer 
	  */
      ETH_tx.ETH_buffer      = ETH_dttail->data;
      ETH_tx.ETH_buffer_size = ETH_dttail->no;
	  ETH_tx.ETH_cookie      = ETH_dttail->os_specific;
      if(ETH_app_tx_cb != NULL)
      { 
        ETH_app_tx_cb(&ETH_tx);
      }
    } /* End of if */
	ETH_dttail = ETH_dttail->next;
	ETH_pending_writes--;
  }
  /*Disable DMUT interrupt*/
//  ETH_HW_DTSRC = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_TERMINATE*/

/*
*******************************************************************************
* Function Name:     ETH_ctrl_dmut
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*  Reset the DMUT configuration parameters
*
* Input parameters:  
*  ETH_device        - Ethernet controller hardware module identification value
*  ETH_ctrl_data         - New configuration parameter values
*
* Output parameters: None
*
* Return Values:    Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_CTRL_DMUT == 1 
ETH_STATUS ETH_ctrl_dmut(ETH_DEVICE ETH_device,ETH_DMUT_CONF *ETH_ctrl_data)
{
  /*
    Copy the configuration data which are to be updated into the ETH_params 
    (global) structure, which will maintain the updated configuartion info
  */
  ETH_params.dmut_conf.endian_mode  =  ETH_ctrl_data->endian_mode;

  /*Write the new configuration data into DTCONF register through global
    configuration structure*/
  ETH_HW_DTCONF = 
    BIT32_MASK(ETH_params.dmut_conf.endian_mode, ETH_HW_DTCONF_LBE);

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_CTRL_DMUT*/


/*
*******************************************************************************
* Function Name:     ETH_DMUT_ISR
*
* Calling Functions: Peripheral DMUT interrupt
*
* Functions Called:  None
*
* Description:
*  This function will take the approprite action depend upon the interrupt 
*  occurred either by calling user provided routine or the defalut action 
*  provided by HAL
*
* Input parameters:  
*  ETH_device        - Ethernet controller hardware module identification value
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
void ETH_DMUT_ISR (IFX_UINT8 ETH_dev)
{
  ETH_TRANSFER ETH_tx;
  
  #ifndef IFX_COMPILER_TASKING
  IFX_UINT32 *cache_addr;
  int i;
  #endif //IFX_COMPILER_TASKING

  /*Copy the interrupt status FIFO register value*/
  ETH_isr_val = ETH_HW_DTISFIFO;

  /*Command completed interrupt*/
  if((ETH_isr_val & ETH_HW_DTCHANNEL_FMT) == ETH_HW_DTCMD_FMT) 
  {
     /*No action*/
  }
  /*Channel related interrupts*/
  else if((ETH_isr_val & ETH_HW_DTCHANNEL_FMT) == ETH_HW_DTCHANNEL_FMT)
  {	 
    /* Host initiation interrupt issued when the DMUT finishes an old descriptor
	   and branches to the next one 
	   HTAB -  This interrupt is issued when HOLD = 1 and FE = 0. This will be
	   issued after the data section is transferred completely
	*/
   if((ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DTISFIFO_HI)) ||
      (ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DTISFIFO_HTAB))||
	  (ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DTISFIFO_TAB)))
   {
      /* Get the first Tx desc which was transmitted */
      ETH_dttail->cmp     = ETH_HW_RST;

      #ifndef IFX_COMPILER_TASKING 
      if(((((IFX_UINT32)ETH_dttail) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_dttail) & 0xF0000000) == 0xC0000000))
      {
        cache_addr = (int *) ETH_dttail;
        for (i = 0; i <= (sizeof(ETH_TXDESC) >> 4); i++) {
               cachea_wi(cache_addr);
               cache_addr += 4;
        }
	  }
	  #endif //IFX_COMPILER_TASKING
      
      if(ETH_pending_writes > 0)
	  {
      if(ETH_dttail->data != NULL)
      {
        /* Send the data to the application only if it a HI interrupt */
        if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DTISFIFO_HI))
        {
          /* Send the data buffer to the application.
             The application is free to re-use this buffer 
     	  */
          ETH_tx.ETH_buffer      = ETH_dttail->data;
          ETH_tx.ETH_buffer_size = ETH_dttail->no;
          ETH_tx.ETH_cookie      = ETH_dttail->os_specific;

          if(ETH_app_tx_cb != NULL)
          {
            ETH_app_tx_cb(&ETH_tx);
          }
        }
	  }
      ETH_dttail       = ETH_dttail->next;
	  ETH_pending_writes--;
	  }
    }/*DMUT HI interrupt*/
  }/*((ETH_isr_val & ETH_HW_DTCHANNEL_FMT) == ETH_HW_DTCHANNEL_FMT)*/
}

