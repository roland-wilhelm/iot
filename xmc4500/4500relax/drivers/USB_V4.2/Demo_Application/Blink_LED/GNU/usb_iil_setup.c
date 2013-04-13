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
** @FILENAME@:       USB_IIL_SETUP.C
** @VERSION@:        4.2
** @DATE@:           23/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements the setup process interfaces as per USB1.1 
**              specification
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
** 12/11/2004     Ranganatha            inlined setup process for faster decoding
**                                      to support enhanced host controller.   
**				                                        
** 03/12/2004				            string descriptor support for index 5 
**                                      removed.
**                                      
** 15/04/2005	  Ronny			        USB_RQStandard and case tree
**                                      removed.
** 19/04/2005	  Jayashree			    ZLP Flag being added to Transmit function, 
**                                      This is used as workaround for ZLP bug in 
**                                      hardware for enumeration with Tasking compiler.
** 17/01/2006     Jayashree             Service for class requests has been added                       
** @CHANGE_HISTORY@
** =============================================================================
*/
#include "usb_iil_api.h"
#include "usb_iil_cfg.h"

/*
The following pre-proccessor directives check if the system HAL matches the 
implemententation dependent layer for the USB HAL. If these do not match
then the compilation is stopped with an error to indicate this conflict to 
the user.
This check has been introduced because the IDL file names are identical, 
regardless of the product they are written for, this could easily result in 
the wrong files being used.
*/
#if SYS_PRODUCT != USB_PRODUCT
#error USB HAL Error: USB HAL is not matching the target CPU!
#endif

/*
Check that the IDL layer is usable:
*/
#if ( USB_API_V_MAJ > 0)
#error USB HAL Error: Incompatible USB HAL distribution version!
#endif

/* Function prototypes */
inline void USB_RQStandard(void);
inline void USB_RQGetDescriptor(void);
void USB_setUpHandler(void);       

extern IFX_SINT32 USBD_transmit(IFX_UINT8 ep, IFX_UINT8 *pData, 
                                IFX_UINT32 bytesRequested, IFX_UINT8 ZLP_flag);
extern IFX_SINT32 USBD_transmit_ep0(IFX_UINT8 *pData, 
                                IFX_UINT32 bytesRequested, IFX_UINT8 ZLP_flag);
                                
#ifdef IFX_COMPILER_GNU

/* Define the setup packet*/	
USB_SETUP_PACKET setUpPkt __attribute__ ((aligned (4)));			    
/* pointer to setup pakcet */
USB_SETUP_PACKET *suPkt = &setUpPkt;    

/* Device descriptor */
USB_DEVICE_DESCRIPTOR USB_deviceDescriptor 
             __attribute__ ((aligned (4))) = { CONFIG_USB_DEVICE_DESCRIPTOR };

/* Configuration descriptor */
IFX_UINT8 usb_device_config_descriptor[CONFIG_USB_TOTBYTES]
             __attribute__ ((aligned (4))) = { CONFIG_USB_TOTAL }; 

#else /*for Tasking*/

/* Define the setup packet*/	
volatile USB_SETUP_PACKET setUpPkt;			    
volatile USB_SETUP_PACKET *suPkt = &setUpPkt;    

#ifndef IFX_COMPILER_LINUX
#pragma align 4
#endif

/* Device descriptor */
USB_DEVICE_DESCRIPTOR USB_deviceDescriptor  = { CONFIG_USB_DEVICE_DESCRIPTOR };

/* Configuration descriptor */
IFX_UINT8 usb_device_config_descriptor[CONFIG_USB_TOTBYTES]
                  = { CONFIG_USB_TOTAL }; 

#ifdef IFX_TASKING_VER1
#pragma align off
#endif
#ifdef IFX_TASKING_VER2
#pragma align restore
#endif

 
#endif /* of IFX_COMPILER_GNU */

#ifdef IFX_COMPILER_GNU
static IFX_UINT8 buffer[64] __attribute__ ((aligned (4))); 
#else   /*for tasking*/
#pragma align 4
static IFX_UINT8 buffer[64];
#ifdef IFX_TASKING_VER1
#pragma align off
#endif
#ifdef IFX_TASKING_VER2
#pragma align restore
#endif
#endif /* of IFX_COMPILER_GNU */

/*==========================================================================
 * Function Name :: USB_RQGetDescriptor()
 *
 * Purpose       :: Called by USB_RQStandard on reception of a 
 *                  GET_DESCRIPTOR request. The routine supports transmission
 *                  of device descriptor, configuration & string descriptors.  					  
 *                  For unknown or not supported request
 *                  the endpoint 0 is stalled.
 *
 * Input         :: USB_SETUP_PACKET token.
 *					
 * Output        :: None.
 *
 * Return Value  :: None
 *					
 *==========================================================================*/
inline void USB_RQGetDescriptor(void)
{
IFX_UINT8 zeropack=1;
IFX_UINT8 *pString   = 0;

  /* Check the type of the requested descriptor */
	switch ( (suPkt->usbSetUpPackets.wValue >> 8) )   
	{
	 	case USB_DEVICE_DESCRIPTOR_TYPE:

			/* Transmit the USB device descriptor */
        		zeropack = (USB_deviceDescriptor.bLength == 
                 		suPkt->usbSetUpPackets.wLength)? FALSE : TRUE;
                 
	   	        USBD_transmit_ep0 ((IFX_UINT8*)&USB_deviceDescriptor,
          		IFX_MIN(USB_deviceDescriptor.bLength,suPkt->usbSetUpPackets.wLength),
          			zeropack);
       			break;

	 	case USB_CONFIGURATION_DESCRIPTOR_TYPE:

			/* Is the host requesting a descriptor for a not supported configuration */
        		if ((suPkt->usbSetUpPackets.wValue & 0xFF) > (CONFIG_USB_NUMBER_OF_CONFIGURATIONS - 1) )
			{
          		/* Requests for not declared descriptor indexes must be refused */				
			USB_EP_SET_STALL(0);
			break;
			}
	    		zeropack = (sizeof(usb_device_config_descriptor)==
                        	suPkt->usbSetUpPackets.wLength)? FALSE : TRUE;
                        
        		USBD_transmit_ep0 (usb_device_config_descriptor,
                     		IFX_MIN( sizeof(usb_device_config_descriptor),
                     	suPkt->usbSetUpPackets.wLength ),zeropack);
	   		break;

	   	case USB_STRING_DESCRIPTOR_TYPE:
			switch((suPkt->usbSetUpPackets.wValue & 0xFF))
                 	{
			    case 0: 
			 	    pString = (IFX_UINT8 *)&LANGID_Descriptor;
			        break;
			    case 1:
			  	    pString = (IFX_UINT8 *)&Manufacturer_Descriptor;
				    break;
			    case 2:
			      	pString = (IFX_UINT8 *) &Product_Descriptor;
				    break;
			    case 3:
			  	    pString = (IFX_UINT8 *) &USB_Serial_number_descriptor;
				    break;
		            case 5:
			        pString = (IFX_UINT8 *)&USB_Hidden_string_descriptor;
			        break;
			    default: 
				    USB_EP_SET_STALL( 0 );
	            	return;
			}
     			zeropack = (pString[0]==suPkt->usbSetUpPackets.wLength)? FALSE : TRUE;
     
     			USBD_transmit_ep0(pString, IFX_MIN(pString[0],suPkt->usbSetUpPackets.wLength),
                          	zeropack);
			break;
			

	 		default: 
			/* The host has issued a not supported request */
			USB_EP_SET_STALL( 0 );             
			break;
	}/*end of Switch*/
}


/*==========================================================================
 * Function Name :: USB_RQClassVendor()
 *
 * Purpose       :: The routine supports Class Vendor request to check EP0 in IN 
 *                  direction. For unknown or not supported request
 *                  the endpoint 0 is stalled.
 *
 * Input         :: USB_SETUP_PACKET token.
 *					
 * Output        :: None.
 *
 * Return Value  :: None
 *					
 *==========================================================================*/
void USB_RQClassVendor(void)
{
IFX_UINT8 zeropack=1;
IFX_UINT32 status;
IFX_UINT8 *pData1 = buffer;

    // Initialise main_buffer 
    for(status = 1; status<64;status++, pData1++)
    {
      *pData1 = (IFX_UINT8)status;
    } 
    pData1 = buffer;

   // Get 64 bytes from FIFO as long device is configured			
   USBD_transmit_ep0(pData1, 64,zeropack);
}

/*==========================================================================
 * Function Name :: USB_setUpHandler()
 *
 * Purpose       :: Reads the setup token sent by host and decodes the same.
 *                  For not supported request the endpoint 0 is stalled.
 *                  This is called by Setup irq handler. 
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None
 *
 * Others        :: Vendor request is not supported.
 *==========================================================================*/
void  USB_setUpHandler(void)       
{
   /* Read setup packet from hardware */
   setUpPkt.usb_SUP.SUTH = GET_SETUP_TOKEN_MSB;   
   setUpPkt.usb_SUP.SUTL = GET_SETUP_TOKEN_LSB;   

	/* service the set-up request received by the host */
if((suPkt->usbSetUpPackets.bmRequestType & USB_SETUP_RQ_TYPE_MASK) == USB_RQ_TYPE_STANDARD)
  {
	
    if(suPkt->usbSetUpPackets.bRequest==USB_RQ_GET_DESCRIPTOR)
		USB_RQGetDescriptor();
	else
        /* The host has issued a not supported request */
		USB_EP_SET_STALL(0); 			
  }
else

// service for class requests

if((suPkt->usbSetUpPackets.bmRequestType & USB_SETUP_RQ_TYPE_MASK) == USB_RQ_TYPE_CLASS)
  {
	
    if(suPkt->usbSetUpPackets.bRequest==USB_RQ_CLASS_REQUEST_UPLOAD)
		
	USB_RQClassVendor();	
		
	else
        /* The host has issued a not supported request */
		USB_EP_SET_STALL(0); 			
  }

else 
/* Stall all unknown and unsupported requests on EP0*/
USB_EP_SET_STALL(0);      /*epNum =0*/
}


