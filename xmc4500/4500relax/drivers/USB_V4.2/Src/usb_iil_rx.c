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
** @FILENAME@:       USB_IIL_RX.C
** @VERSION@:        4.2
** @DATE@:           23/01/2006  
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements reception funtionality for USB device.
**            
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004     Ranganatha (DC BA)      
**                 
**
** 30/07/2004      Udo Dannebaum
** Reveive function waits repeats until all packets of a DAS message are collected
** 2/12/2005    Jayashree (IFIN CSW AIM): USB_Receive functions are more optimized.	 
** 17/01/2006   Jayashree (IFIN CSW AIM): The while loop has been removed.                             
** @CHANGE_HISTORY@
** =============================================================================
*/


#include "compiler.h"
#include "usb_iil_api.h"
#include "usb_iil_common.h" 

extern void  Sys_BackGround(void);			// system background activity during receive loop 


/* Compile this file for GNU and Tasking only */
#ifndef IFX_COMPILER_LINUX   

/* keeps track of number of CBs used. */
static IFX_UINT32 cb_number = 0; 

/* Buffer control block for Reception */
volatile USB_BUFFER_CB  USB_buffer_cb[ USB_NUMBER_OF_CB ];

/* Application initialization routine */
void USB_application_initialize( void );

/* Receive pending check function. */
volatile USB_BUFFER_CB * USB_for_pending_receive( IFX_UINT32 ep );


extern void USBD_poll_rx(IFX_UINT8 ep);

/*==========================================================================
 * Function Name :: USB_receive()
 *
 * Purpose       :: Implements usb read in synochronous fashion. 
 *                  It also queues the number of requests from application
 *                  upto the maximum number of control block defined.
 * 
 * Input         :: ep number, data pointer & number of bytes to be 
 *                  received.
 *					
 * Output        :: None.
 *
 * Return Value  :: Actual number of bytes received.
 *
 * Others        :: With little modification can be ported to OS level
 *==========================================================================*/
IFX_SINT32 USB_receive(IFX_UINT8 *pData, IFX_UINT16 requestNbytes,IFX_UINT8 ep )
{
IFX_UINT32 nBytesRx=0;          /* number of bytes received */
IFX_UINT32 count=0;        


   count = cb_number;
   cb_number++;         
   if( cb_number >= USB_NUMBER_OF_CB)
   cb_number = 0;

         
     
   if( USB_buffer_cb[count].status != CB_STATUS_FREE)     /* request pending */
       return (USB_ERROR);

    /* fill the control block */
      USB_buffer_cb[count].bytesRequested = requestNbytes;
      USB_buffer_cb[count].bytesReceived =   0;
      USB_buffer_cb[count].pBuffer =  (void *)pData;
      USB_buffer_cb[count].ep_number = ep;               
      USB_buffer_cb[count].cb_number = count;               

      USB_buffer_cb[count].USB_application_call_back =   NULL;

     /* do it here at the end so that any dumy interrupts at this time are
      taken care.
     */
      USB_buffer_cb[count].status = RX_STATUS_PENDING;     

      /* Wait until some bytes are filled in buffer. Give timeout here */
    
      USBD_poll_rx(ep);
    
    /* Get actual number if read */
      nBytesRx = USB_buffer_cb[count].bytesReceived; 
   
    /* Free the control block and return number of bytes read */
      USB_buffer_cb[count].bytesRequested =  0 ;
      USB_buffer_cb[count].bytesReceived =   0;
      USB_buffer_cb[count].pBuffer =  NULL;
      USB_buffer_cb[count].ep_number = 0;               /* Currently none. */
      USB_buffer_cb[count].status = CB_STATUS_FREE; 

      
       return(nBytesRx);

}




/*==========================================================================
 * Function Name :: USB_application_initialize()
 *
 * Purpose       :: Initializes all non-hardware related resources used by 
 *                  driver.
 *                  
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
void USB_application_initialize( void )
{
IFX_UINT32 count=0;

/* Free Control blocks */
 for(count=0; count<USB_NUMBER_OF_CB; count++)
 {       
      USB_buffer_cb[count].bytesRequested =  0 ;
      USB_buffer_cb[count].bytesReceived =   0;
      USB_buffer_cb[count].pBuffer =  NULL;
      USB_buffer_cb[count].ep_number = 0;               
      USB_buffer_cb[count].status = CB_STATUS_FREE;     
 } 

}                                   


/*==========================================================================
 * Function Name :: USB_for_pending_receive()
 *
 * Purpose       :: checks the waiting control block. Called at receive
 *                  interrupt level.    
 *                  
 * Input         :: end point number.
 *					
 * Output        :: None.
 *
 * Return Value  :: pointer to control block.
 *
 *==========================================================================*/
volatile USB_BUFFER_CB * USB_for_pending_receive( IFX_UINT32 ep )
{
 volatile USB_BUFFER_CB *pCB = USB_buffer_cb;
 IFX_UINT32 count=0;

 /* poll for waiting block */
 for(count=0; count < USB_NUMBER_OF_CB; count++)
 {       
      if ( (pCB->ep_number == ep) && (pCB->status == RX_STATUS_PENDING) )
      {
          return pCB;  
      }   
      pCB++;
 }
 
 return (volatile USB_BUFFER_CB *)(NULL);
}


#endif /* IFX_COMPILER_LINUX */

