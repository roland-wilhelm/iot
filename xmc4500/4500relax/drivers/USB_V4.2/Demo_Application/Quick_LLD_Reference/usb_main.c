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
** @FILENAME@:       usb_main.c
** @VERSION@:        4.2
** @DATE@:           23/01/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements the sample program to test USB HAL on non-OS. 
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
** 30/07/2004	Dannebaum (AI MUC)	Adaptation of usb_main to DAS protocol
**                                        
** 06/06/2005	Jayashree	insert of stop polling loop if device is not anymore configured
**                                      insert Sys_BackGround function  
**                                        
**                                        
** =============================================================================
*/

#include "compiler.h"
#include "usb_iil_api.h"
#include "sys_api.h"
#include "usb_idl_cfg.h"


#ifdef IFX_COMPILER_GNU
static IFX_UINT8 main_buffer[1200] __attribute__ ((aligned (4))); 
#else   /*for tasking*/
#pragma align 4
static IFX_UINT8 main_buffer[1200];
#ifdef IFX_TASKING_VER1
#pragma align off
#endif
#ifdef IFX_TASKING_VER2
#pragma align restore
#endif

#endif /* of IFX_COMPILER_GNU */


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
IFX_SINT16 nBytesRequest=0, nBytesReceived=0;
IFX_UINT32 status;
#define RX_PIPE 2
#define TX_PIPE 1

             
              DISABLE_GLOBAL_INTERRUPT();
              /* Initialize USB clock. */
              SYS_clk_initialise();
              for(status = 1; status<1200;status++, pData++)
              {
               *pData = (IFX_UINT8)status;
              }
              pData = main_buffer;
              
              while( USBD_device_initialize() != USB_OK );     /* Init error */
              ENABLE_GLOBAL_INTERRUPT();
	      
	      
    //LED init
    P0_DIR = 0x080;
    P0_OUT = 0x080;	      
    
    while (1)
    {
              status = USBD_get_device_state();
              switch(status)
              {   
              case(USB_CONFIGURED):
              P0_OUT = 0x000;
              /*Max request can be 1023 bytes only*/
              nBytesRequest = 64;

              nBytesReceived  = USB_receive(pData, nBytesRequest, RX_PIPE );  
              if(nBytesReceived > 0)                
			        {
                           nBytesReceived = USBD_transmit( TX_PIPE,  pData, nBytesReceived, 0);   
                    }
              break;
              default:
              break;  
             }
    }

return 0;
} /* end of main */


/*==========================================================================
 * Function Name :: Sys_BackGround()
 *
 * Purpose       :: Tis function ist used during the poll of receive data
 *
 * Input         :: 
 *					                
*==========================================================================*/
void Sys_BackGround(void)
{
//switch the LED off in case the USB device is Detached
if (USBD_get_device_state() != USB_CONFIGURED)P0_OUT = 0x080;		
}
