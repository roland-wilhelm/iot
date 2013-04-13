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
** @FILENAME@:       usbmain_das.C
** @VERSION@:        4.2
** @DATE@:           06/02/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements the sample program (DAS) to test USB HAL on non-OS. 
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date         Author                  Comment
** 17/03/2004   Ranganatha (DC BA)      
**
** 30/07/2004	Dannebaum (AI MUC)	Adaptation of usb_main to DAS protocol
**                                        
** 14/04/2005	Schulze (AI MUC)	insert of stop polling loop if device is not anymore configured
**                                      insert Sys_BackGround function  
**
** 06/02/2006   Dannebaum (AI MUC)	DAS Application for AUTO mode improved.
**              Badarinath (DC BA)      Both Modes available via define ( Manual mode and automatic mode)
**			     
** 14/02/2006   Dannebaum (AI MUC)	Change for DAS Application. Receive function is blocked during transmit of 
**                                      a DAS Message
**                                      
**                                        
**                                        
** =============================================================================
*/

#include "compiler.h"
#include "usb_iil_api.h"
#include "usb_idl_cfg.h"
#include "sys_api.h"
#include "usbd_idl_macro.h"




#ifdef IFX_COMPILER_GNU
static IFX_UINT8 main_buffer[520] __attribute__ ((aligned (4))); 
static IFX_UINT8 main_buffer2[520] __attribute__ ((aligned (4))); 
static IFX_UINT8 main_buffer3[64] __attribute__ ((aligned (4))); 

#else   /*for tasking*/
#pragma align 4
static IFX_UINT8 main_buffer[520];
static IFX_UINT8 main_buffer2[520];
static IFX_UINT8 main_buffer3[64];

#ifdef IFX_TASKING_VER1
#pragma align off
#endif
#ifdef IFX_TASKING_VER2
#pragma align restore
#endif

#endif /* of IFX_COMPILER_GNU */


extern void *copy(void *dest, const void *src, IFX_UINT32 len);

#define P0_DIR                 (*((IFX_UINT32 volatile *) 0xF0000C18))
#define P0_OUT                 (*((IFX_UINT32 volatile *) 0xF0000C10))


/*==========================================================================
 * Function Name :: main()
 *
 * Purpose       :: This function does the following -
 *					1. Initializes the USB clock.
 *					2. Initializes the USB device
 *					3. Waits for the data to be received
 *                  4. Transmits the received data.
 *
 * Input         :: None
 *                  
 *					
 * Output        :: None.
 *
 * Return Value  :: None
 *
 *==========================================================================*/
int main( void ) 
{
IFX_UINT8 *pData = main_buffer;
IFX_UINT8 *pData2 = main_buffer2;
IFX_UINT8 *pData3 = main_buffer3;
//IFX_UINT32 c;

IFX_SINT16 nBytesRequest, nBytesReceived=0;
#ifdef USBD_AUTO_MODE
IFX_SINT16 nBytesTransmitted;
//IFX_SINT32 loopend=100000;

#endif

#ifdef USBD_MANUAL_MODE
IFX_UINT32 i;
#endif

IFX_UINT32 status;
static IFX_UINT16 total_length, expected_das_pkt_length, expected_das_pkt_length2 ;
//static IFX_UINT16 second_das_pkt_length=0;
//static IFX_UINT16 pi;
static IFX_UINT16 old_expected_das_pkt_length, size_already_found, free_mainbuffer2;
IFX_UINT16 FillSize;
#define RX_PIPE 2
#define TX_PIPE 1

             
    DISABLE_GLOBAL_INTERRUPT();

    // Initialize USB clock
    SYS_clk_initialise();
 
    // Initialise main_buffers 
    for(status = 1; status<520;status++, pData++)
    {
      *pData = (IFX_UINT8)status;
    } 
    pData = main_buffer;

    for(status = 1; status<520;status++, pData2++)
    {
      *pData2 = (IFX_UINT8)status;
    } 
    pData2 = main_buffer2;

    for(status = 1; status<64;status++, pData3++)
    {
      *pData3 = (IFX_UINT8)status;
    } 
    pData3 = main_buffer3;
        
    while( USBD_device_initialize() != USB_OK );     // Init error 
  
    ENABLE_GLOBAL_INTERRUPT();

    total_length = 0;
    expected_das_pkt_length = 0;
    old_expected_das_pkt_length = 0;
    size_already_found=0;
    free_mainbuffer2 = 0;
    expected_das_pkt_length2=0;
    FillSize =0;
    // LED init
    P0_DIR = 0x080;
    // Switch off yellow LED
    P0_OUT = 0x080;
    	      

    while (1)
    {
              // Get USB_11D device status
	      status = USBD_get_device_state();
              
	      switch(status)
              {   
                 case(USB_CONFIGURED):
		               	
		        // Switch on yellow LED
              		P0_OUT = 0x000;
			
			//#################################################################
			// Collect DAS Message
			//#################################################################
			
					
//##############################################################################################
// Routine for AUTOMATIC MODE
// for TC1130 BB steps only
//##############################################################################################

			#ifdef USBD_AUTO_MODE
			
			//Max request can be 1023 bytes only
			nBytesRequest   = 64;
			nBytesReceived  = 0;
			
			// Get 64 bytes from FIFO as long as device is configured
			if (!free_mainbuffer2){
			
		  	  // Check of NEB(ep < BSZ(ep)!  Mandatory!
			  IFX_UINT32 *p32_epp;
                          p32_epp = (IFX_UINT32 *)( (IFX_UINT8 *)USBD_EPUP_BASE + (2 * 0x0010) );
                          if((p32_epp[3]>>16) < 6) {
			    // Get 64 bytes from FIFO as long as device is configured
    			    nBytesReceived  = USB_receive(pData, nBytesRequest, RX_PIPE );
			  }
			}
			
			// Check received message for DAS header, especially for size 
			if (nBytesReceived){
			  if (!size_already_found){
			  
			    // Net length = received bytes
			    total_length = nBytesReceived;
			  
			    // Reset Main Buffer since header packet arrived
			    pData = main_buffer;
			
			    // Get the length of DAS Message
			    copy(&expected_das_pkt_length, main_buffer, 2);
			    
			    // Debug stuff
			    if (expected_das_pkt_length > 520){
			      P0_OUT = 0x080;
			    }
			    
			    // ShortPacket Check I (Packet < 64 byte)
			    if ((expected_das_pkt_length%64)&&(expected_das_pkt_length<64)){
			      //DAS Header + Short Package
			      total_length=expected_das_pkt_length;
			      pData+= total_length;
			    } else {
			      pData+= nBytesReceived;
			    }
						
			    // Enable "Collect following packets" routine							    		    		    		    
			    size_already_found=1;
			    		    
		   	  } else {
			          total_length += nBytesReceived;
				  // ShortPacket Check II (Packet > 64 byte)
				  if (total_length > expected_das_pkt_length){
				    total_length = expected_das_pkt_length;
				  }				    				  
			          // Increase pData pointer to next free byte
				  pData += nBytesReceived;
			  }
		        }
								
			//#################################################################
			// COPY collected DAS Message from main_buffer to main_buffer2
			//#################################################################
			
                	if ((total_length!=0)&&(total_length >= expected_das_pkt_length)&&(!free_mainbuffer2)) {
				
				// Reset main_buffer
				pData = main_buffer;
				
				// Copy the length of DAS Message to main_buffer2 variable
				expected_das_pkt_length2=expected_das_pkt_length;
				
				//reset length value for main_buffer
				expected_das_pkt_length=0;
				
				// Copy mainBuffer to mainBuffer2
			        for(status = 0; status<expected_das_pkt_length2;status++, pData2++){
                                  *pData2 = pData[status];
                                }		
				
				// Reset main_buffers
			        pData = main_buffer;
			        pData2 = main_buffer2;
			 	
				// Change third byte from 0x4e to 0xce
				pData2[2] = 0xCE;
				
				// Reset main_buffers
			        pData2 = main_buffer2;

			        // DONE Bit OR Zero Length Packet after Transmit ? 
			        FillSize = (expected_das_pkt_length2 % 64);
			        
			        // Enable main_buffer2: Ready to transmit!
			        free_mainbuffer2=1;
			        
			        // Enable DAS Msg Collect routine for next DAS Header
			        size_already_found=0;
				
				// Reset total_length
				total_length = 0;
		
			}				
			
			//#################################################################
			// Transmit DAS Message from main_buffer2
			//#################################################################
			
			if (free_mainbuffer2){
			  
			 IFX_UINT32 Transmitted_Bytes=0 ;
		   	
							  
				// Trigger Single USB Transmit of 64 or less bytes			
				if (expected_das_pkt_length2 >= 64){
				  nBytesTransmitted = USBD_transmit_Auto_mode( TX_PIPE, pData2, 64, 0);
				  Transmitted_Bytes+=nBytesTransmitted;
				} else {
				  nBytesTransmitted = USBD_transmit_Auto_mode( TX_PIPE, pData2, expected_das_pkt_length2, 0);
				  Transmitted_Bytes+=64;
				}
						
				// Recalculate leaving DAS message-length
			        expected_das_pkt_length2-=nBytesTransmitted;
				pData2+=nBytesTransmitted;
			       
				// Send Zero Length Packet, when Size%64 = 0 
				// Transfer ends with even packetsize = 64
				// This signals an end of transfer to the Host
				
			        if ((expected_das_pkt_length2==0)&&(!FillSize)) {
			          free_mainbuffer2=0;
				  pData2 = main_buffer2;
			          USBD_TX_ZERO_LENGTH_PKT(TX_PIPE)
			        }
				
			        // Write DONE-Bit, when Size%64 != 0
				// Transfer ends with odd paketsize =< 64
			        // This signals an end of transfer to the Host
				
				if ((expected_das_pkt_length2==0)&&(FillSize)) {
			          free_mainbuffer2=0;
				  pData2 = main_buffer2;
			          USBD_SET_DONE_BIT(TX_PIPE);
			        }
			}
		
			#endif
			
			
//##############################################################################################
// Routine for MANUAL MODE
// for TC1130 AA and BA steps
//##############################################################################################

			
			
			#ifdef USBD_MANUAL_MODE
			//Max request can be 1023 bytes only
			nBytesRequest = 64;
			// Get 64 bytes from FIFO as long device is configured
			while (((nBytesReceived  = USB_receive(pData, nBytesRequest, RX_PIPE )) < 2) && (USBD_get_device_state() == USB_CONFIGURED)); 
     
	                // Get USB_11D device status, if USB_receive loop is exit with a non confugured state, stop the case
	                if (USBD_get_device_state() != USB_CONFIGURED)break;    

			// DAS ECF changes
			// Update current length of DAS packet
			total_length = nBytesReceived;
			      
			// Get real length of DAS packet (first two bytes of a DAS packet)
			pData = main_buffer;
			
			copy(&expected_das_pkt_length, main_buffer, 2);
			
			// Collect complete DAS packet
			while (total_length < expected_das_pkt_length)
			{
				// Update pdata pointer with last read length
				pData += nBytesReceived;
				// Get 64 bytes from FIFO
				nBytesReceived  = USB_receive(pData, nBytesRequest, RX_PIPE );
				// Update of current length variable
				total_length += nBytesReceived;
			}
	        		
			if ((expected_das_pkt_length%64) != 0)
			{
			  // save odd length
			  old_expected_das_pkt_length = expected_das_pkt_length;
			
	    	  	  // calculate new expected_das_pkt_length
			  expected_das_pkt_length = expected_das_pkt_length - (expected_das_pkt_length % 64) + 64;
			      
			  for (i = old_expected_das_pkt_length; i < expected_das_pkt_length; i++) 
              		  {
	          			main_buffer[i] = 0;
	         		 }
	        		}
            
           			 pData = main_buffer;
            			
			while (expected_das_pkt_length>0)
			{
			    nBytesReceived = USBD_transmit( TX_PIPE, pData, 64,0);
			    expected_das_pkt_length-=nBytesReceived;
			    pData+=nBytesReceived;
			}   			
			// Reset main_buffer
			pData = main_buffer;

                        #endif
			
			break;
			
              
	       default:
           break;  
            
          }
    }
   
return 0;

} /* end of main */

/*==========================================================================
 * Function Name :: copy()
 *
 * Purpose       :: Copy the memory in the fifo
 *
 * Input         :: destination pointer, Source pointer, Length
 *					                
*==========================================================================*/
void *copy(void *dest, const void *src, IFX_UINT32 len)
{ 
  IFX_UINT8 *dstp = (IFX_UINT8*)dest;
  IFX_UINT8 *srcp = (IFX_UINT8*)src; 
  IFX_UINT32 i;

  for (i = 0; i < len; ++i)
  {
    dstp[i] = srcp[i];
  }
  return dest;
} 


