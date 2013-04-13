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
** @FILENAME@:       eth_iil_dmur.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file provides the API which are related to DMUR module. The
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
** 29/04/2004      Ruby					  Rizal's comments SD algorithm
**                                     removed DMUR alignment as a config param
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
* Function Name:     ETH_initialise_dmur
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  None
*
* Description:
*  Initilise the Data Management Unit Receive by initializing configuration regs 
*  and allocating DMUR data descriptors(linked list) and buffers. Issue a INIT
*  command
*
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  ETH_setup      -  Configuration parameters
*
* Output parameters: DMUR descriptor linked list and data buffers
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

ETH_STATUS ETH_initialise_dmur(ETH_DEVICE ETH_device, ETH_COM_PARAMS *ETH_setup)
{
  IFX_UINT8 desc_num = 0; 
  #ifndef IFX_COMPILER_TASKING
  int i;
  IFX_UINT32 *cache_addr;
  #endif //IFX_COMPILER_TASKING

  /* Check if the receive data buffer size < 64K & it is a multiple of 4 bytes */
  /* If not return error */
  if(ETH_DMUR_SIZE_CHECK(ETH_CFG_DMUR_DBUFF_SIZE) == ETH_ERR)
  {
    return ETH_ERR;
  }
  /*Create the DMUR descriptors linked list*/
  while(desc_num < ETH_CFG_DMUR_DESC_NUM)
  {
    /*Assign descriptor id*/
    ETH_drdesc[desc_num].desc_id = desc_num;
    ETH_drdesc[desc_num].rhi     = ETH_HW_RST;
    /*
      update the number field with the maximum number of data bytes 
      that one descriptor can hold
    */
    ETH_drdesc[desc_num].no      = ETH_CFG_DMUR_DBUFF_SIZE;


    if(desc_num < (ETH_CFG_DMUR_DESC_NUM - 1))
    {
      /*Pointer to next descriptor in an array*/
      ETH_drdesc[desc_num].next   = &ETH_drdesc[desc_num+1];
    }
 	 /*Associate the data buffer to the descriptor */
     ETH_drdesc[desc_num].data     = &ETH_drdata[desc_num][0]; 
     desc_num++;
  }/*end of while*/

  /*Make a circular linked list */
  ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1].next = &ETH_drdesc[0];

  /*
    Set the hold bit to 1 in last descriptor to notify the DMUR that this
    is the last descriptor 
  */
  ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1].hold = ETH_HW_SET;
 
  #ifndef IFX_COMPILER_TASKING
  if(((((IFX_UINT32)ETH_drdesc) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drdesc) & 0xF0000000) == 0xC0000000))
  {
    desc_num = 0;
    while(desc_num < ETH_CFG_DMUR_DESC_NUM) {
	  cache_addr = (int *) &ETH_drdesc[desc_num];
	  for (i = 0; i <= (sizeof(ETH_RXDESC) >> 4); i++) {
		  cachea_w(cache_addr);
		  cache_addr += 4;
	  }
	  desc_num++;
    }
  }
  #endif //IFX_COMPILER_TASKING
  /*
    Set the values of head and tail pointers of DMUR free descriptor list.
  */
  ETH_drfree_head = &ETH_drdesc[0];
  ETH_drfree_tail = &ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1]; 

  /*Set DR modification register to frame mode*/
  ETH_HW_DRMOD  = BIT32_MASK(ETH_HW_DMUR_FRAME,ETH_HW_DRMOD_FRM); 

  /*Assign the value of head pointer of the free descriptor list to the 
    DRFRDA register.*/
  ETH_HW_DRFRDA = (IFX_UINT32)ETH_drfree_head;
 
  /*Set DMUR interrupt mask */
  ETH_HW_DRIMR  = ~(BIT32_MASK(ETH_HW_SET,ETH_HW_DRIMR_SD)   |
                    BIT32_MASK(ETH_HW_SET, ETH_HW_DRIMR_CDMC)|
                    BIT32_MASK(ETH_HW_SET, ETH_HW_DRIMR_HRAB)|
                    BIT32_MASK(ETH_HW_SET,ETH_HW_DRIMR_FE));

  /*Set the DRConf register values, endian and alignment mode*/
  ETH_HW_DRCONF  = 
   (BIT32_MASK(ETH_setup->dmur_conf.alignment, ETH_HW_DRCONF_ENA)|
    BIT32_MASK(ETH_setup->dmur_conf.endian_mode, ETH_HW_DRCONF_LBE));


  /*Set interrupt service request control register*/
  ETH_HW_DRSRC |= (BIT32_MASK(ETH_SRC_CPU, ETH_SRC_TOS)|
                   BIT32_MASK(SYS_ETH_DMUR, ETH_SRC_SRPN)|
                   BIT32_MASK(ETH_SRC_ENABLE, ETH_SRC_SRE)); 

  /*isuue a DMUR init command*/
  ETH_HW_DRCMD = ETH_HW_DMUR_INIT;

  return ETH_SUCCESS;
}

/*
*******************************************************************************
* Function Name:     ETH_terminate_dmur
*
* Calling Functions: ETH_termiante_dev
*
* Functions Called:  None
*
* Description:
*  Terminate the DMUR by freeing the allocated DMUR data descriptors and data
*  buffers. Issue a OFF command to stop dmur. 
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
ETH_STATUS ETH_terminate_dmur (ETH_DEVICE ETH_device)
{
  /*Issue a DMUR off command*/
  ETH_HW_DRCMD = ETH_HW_DMUR_OFF;

  /*Disable DMUR interrupt*/
  ETH_HW_DRSRC = BIT32_MASK(ETH_HW_RST,ETH_SRC_SRE);
  
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_TERMINATE*/

/*
*******************************************************************************
* Function Name:     ETH_ctrl_dmur
*
* Calling Functions: ETH_control_dev
*
* Functions Called:  None
*
* Description:
*  Reset the DMUR configuration parameters
*
* Input parameters:  
*  ETH_device        - Ethernet controller hardware module identification value
*  ETH_ctrl_data         - New configuration parameter values
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_CTRL_DMUR == 1 
ETH_STATUS ETH_ctrl_dmur(ETH_DEVICE ETH_device, ETH_DMUR_CONF *ETH_ctrl_data)
{
  /*
    Copy the configuration data which are to be updated into the ETH_params
    (global) structure, which will maintain the updated configuartion info
  */
  ETH_params.dmur_conf.endian_mode   = ETH_ctrl_data->endian_mode; /*big/little
                                                                endian mode*/

 /*Write the new configuration into DRCONF register through global
   configuration structure*/
  ETH_HW_DRCONF = 
    BIT32_MASK(ETH_params.dmur_conf.endian_mode, ETH_HW_DRCONF_LBE);

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_CTRL_DMUR*/

/*
*******************************************************************************
* Function Name:     ETH_DMUR_ISR
*
* Calling Functions: Peripheral DMUR interrupt
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
void ETH_DMUR_ISR(
  IFX_UINT8 ETH_device,
  void     *ETH_os_specific
)
{
  ETH_RXDESC    *ETH_drtemp   = NULL;
  ETH_TRANSFER   ETH_rx;
  IFX_UINT32     prev_descid = 0;
  IFX_UINT8      count = 0;
  IFX_UINT8      ETH_last_descriptor = 0;

  #ifndef IFX_COMPILER_TASKING
  int 		 i;
  IFX_UINT32	*cache_addr;
  #endif //IFX_COMPILER_TASKING

  ETH_isr_val = ETH_HW_DRISFIFO;

  /*command complete interrupt*/
  if((ETH_isr_val & ETH_HW_DRCHANNEL_FMT) == ETH_HW_DRCMD_FMT)
  {
    /* No action */	
  }
  /*channel related interrupts*/
  else if((ETH_isr_val & ETH_HW_DRCHANNEL_FMT) == ETH_HW_DRCHANNEL_FMT)
  {
    /* Check the Frame End interrupt */
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_FE))    
    {
      /* Get the pointer to the head of the list where the DMUR has stored
         the data received */
      ETH_drtemp = ETH_drfree_head;
  	  /* Loop through all the descriptors till the FE bit is set */
      while(!ETH_last_descriptor)
      {
        /* Send the buffer to the application */
        /* Update the ETH_rx struct */
	     #ifndef IFX_COMPILER_TASKING
         if(((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0xC0000000))
	     {
	       cache_addr = (int *) ETH_drtemp;
	       for (i = 0; i <= (sizeof(ETH_RXDESC) >> 4); i++) {
	         cachea_i(cache_addr);
		     cache_addr += 4;
	       }
		 }
         #endif  //IFX_COMPILER_TASKING
        ETH_rx.ETH_buffer      = ETH_drtemp->data;
        /* Bug:  BNO will sometime shows a wrong number (dribble bit error in
          the ERRATA) */
        ETH_rx.ETH_buffer_size = ETH_drtemp->bno;
        ETH_rx.ETH_cookie      = ETH_os_specific;
        /* Update the FE bit to indicate to the application that 
          this is the last descriptor of the frame. */
        ETH_rx.ETH_return_num.ETH_fe = ETH_drtemp->frm_end;

        /* Update the bit fields to indicate to the user the status of the rx
           frame */
        ETH_rx.ETH_return_num.ETH_crc  = ETH_drtemp->crc;
        ETH_rx.ETH_return_num.ETH_rab  = ETH_drtemp->rab;
        ETH_rx.ETH_return_num.ETH_ilen = ETH_drtemp->il_len;
        ETH_rx.ETH_return_num.ETH_mfl  = ETH_drtemp->max_frm_len;
        ETH_rx.ETH_return_num.ETH_rfod = ETH_drtemp->rx_frm_ovflow;

        /* Check for the Frame End bit of the current descriptor */
        if(ETH_drtemp->frm_end == ETH_HW_SET)
		{ 
          /* Make the ETH_last_descriptor = 1 */
          ETH_last_descriptor = 1;
        }
      
        /* Send the data pointer up to the application via a call to the
           call back function */
        if(ETH_app_rcv_cb != NULL)
        {	
          ETH_app_rcv_cb(&ETH_rx);
        }
	    /* Set the HOLD bit of the current descriptor*/
        ETH_drtemp->hold      = ETH_HW_SET;
        ETH_drtemp->cmp       = ETH_HW_RST;
        #ifndef IFX_COMPILER_TASKING
        if(((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0xC0000000))
	    {
          cache_addr = (int *) ETH_drtemp;
          for (i = 0; i <= (sizeof(ETH_RXDESC) >> 4); i++) {
                cachea_w(cache_addr);
                cache_addr += 4;
          }
		}
        #endif //IFX_COMPILER_TASKING
        /* Remove the HOLD bit from the free tail */
        ETH_drfree_tail->hold = ETH_HW_RST;
        #ifndef IFX_COMPILER_TASKING
        if(((((IFX_UINT32)ETH_drfree_tail) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drfree_tail) & 0xF0000000) == 0xC0000000))
	    {
          cachea_w(ETH_drfree_tail);	// is enough
		}
        #endif //IFX_COMPILER_TASKING
        /* update the free head to the next descriptor */
        ETH_drfree_head       = ETH_drfree_head->next;
        /* Make the free tail point to the current descriptor */
        ETH_drfree_tail       = ETH_drtemp;
        /* Update the current descriptor */
		ETH_drtemp = ETH_drtemp->next;
        /* Issue the HOLD reset command */
        ETH_HW_DRMOD  = ETH_HW_DMUR_HRST;
      } /* End of last_desc */
    } /* end of if FE bit set */

    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_SD))
    {
      ETH_isr_val = ETH_HW_DRISFIFO;
      /* Loop till the SD bit is cleared */
      while(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_SD))
      {
# if ETH_CFG_STAT_LOG == 1
        ETH_statistics.rsrc_err++;
# endif /*ETH_CFG_STAT_LOG*/ 
        ETH_isr_val = ETH_HW_DRISFIFO;
      }
      /* Reset the hold bit from all desc */
      for(count = 0;count < (ETH_CFG_DMUR_DESC_NUM - 1); count++)
      {
        ETH_drdesc[count].hold = ETH_HW_RST;
        #ifndef IFX_COMPILER_TASKING 
        if(((((IFX_UINT32)&ETH_drdesc[count]) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)&ETH_drdesc[count]) & 0xF0000000) == 0x80000000))
	    {
	      cachea_w(&ETH_drdesc[count]);	// is be enough
		}
		#endif //IFX_COMPILER_TASKING
      }
      /* set the hold bit of the last desc */
      ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1].hold = ETH_HW_SET;
 	  
      #ifndef IFX_COMPILER_TASKING
      if(((((IFX_UINT32)&ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1]) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)&ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1]) & 0xF0000000) == 0xC0000000))
      {
        cachea_w(&ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1]);
	  }
 	  #endif //IFX_COMPILER_TASKING
      /*
      Set the values of head and tail pointers of DMUR free descriptor list.
      */
      ETH_drfree_head = &ETH_drdesc[0];
      ETH_drfree_tail = &ETH_drdesc[ETH_CFG_DMUR_DESC_NUM - 1];
      ETH_HW_DRFRDA   = (IFX_UINT32)ETH_drfree_head;
	  ETH_HW_DRCMD    = ETH_HW_DMUR_INIT;
    }

    ETH_last_descriptor = ETH_HW_RST;
    /* Processing the HRAB interrupt */
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_HRAB))
    {
      ETH_drtemp = ETH_drfree_head;
       /* Discard all the descriptors from the ETH_drfree_head in which
          in which the Complete bit is set */
      while(!ETH_last_descriptor)
      {
        #ifndef IFX_COMPILER_TASKING
        if(((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0xC0000000))
        {
          cache_addr = (int *) ETH_drtemp;
          for (i = 0; i <= (sizeof(ETH_RXDESC) >> 4); i++) {
                cachea_i(cache_addr);
                cache_addr += 4;
          }
		}
 		#endif //IFX_COMPILER_TASKING
        if (ETH_drtemp->cmp == ETH_HW_SET)
        {
          /* Update the ETH_rcvd_frm struct to send to the application */
          ETH_rx.ETH_buffer      = ETH_drtemp->data;
          ETH_rx.ETH_buffer_size = ETH_drtemp->bno;
          /* Update the bit fields to indicate that this frame was aborted */
          ETH_rx.ETH_return_num.ETH_fe   = ETH_drtemp->frm_end;
          ETH_rx.ETH_return_num.ETH_crc  = ETH_drtemp->crc;
          ETH_rx.ETH_return_num.ETH_rab  = ETH_drtemp->rab;
          ETH_rx.ETH_return_num.ETH_ilen = ETH_drtemp->il_len;
          ETH_rx.ETH_return_num.ETH_mfl  = ETH_drtemp->max_frm_len;
          ETH_rx.ETH_return_num.ETH_rfod = ETH_drtemp->rx_frm_ovflow;

          /* Send the data pointer up to the application via a call to the call-
             back function */
          if(ETH_app_rcv_cb != NULL)
          {
            ETH_app_rcv_cb(&ETH_rx);
          }
          ETH_drtemp->cmp = ETH_HW_RST;
		  #ifndef IFX_COMPILER_TASKING
          if(((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0xC0000000))
          {
            cache_addr = (int *) ETH_drtemp;
            for (i = 0; i <= (sizeof(ETH_RXDESC) >> 4); i++) {
                cachea_wi(cache_addr);
                cache_addr += 4;
            }
		  }
          #endif //IFX_COMPILER_TASKING
          if(ETH_drtemp->hold == ETH_HW_SET)
          {
            ETH_last_descriptor = ETH_HW_SET;
            ETH_drtemp->hold  = ETH_HW_RST;
            ETH_drfree_head   = ETH_drtemp->next;
            if(ETH_drtemp->desc_id == 0)
            {
              prev_descid = ETH_CFG_DMUR_DESC_NUM - 1;
            }
            else
            {
              prev_descid = ETH_drtemp->desc_id - 1;
            }
            /* The hold bit of the previous desc is set. This descriptor is also
               pointed by the ETH_drfree_tail.
            */
			#ifndef IFX_COMPILER_TASKING
            if(((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_drtemp) & 0xF0000000) == 0xC0000000))
            {
              cache_addr = (int *) ETH_drtemp;
              for (i = 0; i <= (sizeof(ETH_RXDESC) >> 4); i++) {
                cachea_w(cache_addr);
                cache_addr += 4;
              }
			}
			#endif //IFX_COMPILER_TASKING
            ETH_drdesc[prev_descid].hold = ETH_HW_SET;
            #ifndef IFX_COMPILER_TASKING
            if(((((IFX_UINT32)&ETH_drdesc[prev_descid]) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)&ETH_drdesc[prev_descid]) & 0xF0000000) == 0xC0000000))
            {
	          cachea_w(&ETH_drdesc[prev_descid]); // is enough
			}
	    	#endif //IFX_COMPILER_TASKING
            /* Update the tail of the desc list */
            ETH_drfree_tail = &ETH_drdesc[prev_descid];
            ETH_HW_DRCMD  = ETH_HW_DMUR_HRST;
          } /* End of if (HOLD)*/
          ETH_drtemp      = ETH_drtemp->next;
        } /*  End of if(C bit set) */
      } /* End of while(! last desc )*/
    }  /* End of HRAB interrupt processing */

    /*invalid length*/
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET, ETH_HW_DRISFIFO_ILEN)) 
    {
       /*No action*/
    }
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET, ETH_HW_DRISFIFO_CRC)) /*CRC error*/
    {
       /*No action*/
    }
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_RFOD)) 
    {
       /* Process the receive queue as fast as possible, probably by
          increasing the priority of the receive buffer interrupt and keeping
          the ISRs small */
    }
    /*maximum frame length*/
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_MFL)) 
    {
       /*No action*/
    }
    /*receive abort*/
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_RAB))     
    {
      /* No action */
    }
	/*host indication*/
    if(ETH_isr_val & BIT32_MASK(ETH_HW_SET,ETH_HW_DRISFIFO_HI)) 
    {
      /* No action */
    }
  }/* ETH_isr_val   & ETH_HW_DRCHANNEL_FMT) == ETH_HW_DRCHANNEL_FMT*/
}

