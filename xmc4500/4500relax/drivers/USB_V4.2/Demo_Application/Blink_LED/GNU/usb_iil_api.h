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
** @FILENAME@:       USB_IIL_API.H
** @VERSION@:        4.2
** @DATE@:           23/01/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents:  This file contains application interface definitions.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 2/12/2005     Jayashree (IFIN CSW AIM)   
**                                        
** @CHANGE_HISTORY@ The new function for transmit for automatic mode has been added.
** =============================================================================
*/

/* @doc DESIGN */

#ifndef __USB_API_H_
#define __USB_API_H_


/* 
   @topic1 USB API |

   This section defines the interfaces between the USB hardware layer and the
   application layer. 
     
*/
#include "compiler.h"


/*
  @def  USB_API_V_MAJ  | API Major Version Number,
  USB_API_V_MAJ is defined to the major version of this API which the USB HAL
  supports. This version is defined as 0.1.
  Application software may check this field to determine if the HAL API version 
  is acceptable.
*/
#define USB_API_V_MAJ 0



/*
  @def  USB_API_V_MIN  | API Minor Version Number,
  USB_API_V_MIN is defined to the minor version of this API which the USB HAL
  supports. This version is defined as 0.1.
  Application software may check this field to determine if the HAL API version 
  is acceptable.
*/
#define USB_API_V_MIN 1



/*def USB_DEVICE |
  Type define the USB device. Not used. 
*/
typedef IFX_UINT8 USB_DEVICE;



/*
@struct	USB_BUFFER_CB |
usb buffer control block for reception and transmission. 
The handling of this control block and its synchronization 
is taken care at the USB_receive interface level.

@comm In current release used only for reception.
*/
typedef struct USB_BUFFER_CB_t
{
  IFX_UINT32 ep_number;      /* @field endpoint number for this communication */
  IFX_UINT32 cb_number;      /* @field control block number. Not to be used*/
  IFX_UINT32 bytesRequested; /* @field Number of bytes requested 
                                (reception/transmission) for this buffer. To be 
                                filled by application layer.                   
                             */
  IFX_UINT32 bytesReceived;  /* @field Number of bytes received/transmitted for 
                                this buffer. Filled by low-level driver.
                             */
  IFX_UINT32 status;         /* @field status of this control block. See 
                                USB_CB_BUFFER_STATUS 
                             */

  void *pBuffer;             /* @field pointer to application supplied buffer */

  void (*USB_application_call_back) (void *pCB);  
                  /* @field Application call back funtion for low-level 
                       driver. NULL if none. CallBack not supported. */  

} USB_BUFFER_CB;             



/* @enum USB_CB_BUFFER_STATUS |
   Holds the receive control block status. 
*/
typedef enum USB_CB_BUFFER_STATUS
{
  CB_STATUS_FREE = 1,         /* @emem Rx buffer is free. 
                                    Filled by low-level driver */
  RX_STATUS_PENDING = 3,      /* @emem Read pending. 
                                    To be filled by appilcation layer.*/
  RX_STATUS_FILLED = 4,       /* @emem Read complete. */
  
  TX_STATUS_PENDING = 5       /* @emem transfer pending. Not used */
  
} USB_CB_STATUS;


/* @def USB_NUMBER_OF_CB |
   Number of USB_BUFFER_CB control blocks used by application.
   Currently set to 2. The user can initialize based on number of simultaneous 
   request being made at receive interface.
 */
#define USB_NUMBER_OF_CB    2


/* @enum USB_DEVICE_STATES |
   The USB_DEVICE_STATES holds various usb device enumeration 
   and control states.  
*/
typedef enum USB_DEVICE_STATES_t
{
    USB_IDLE = 1,         /* @emem USB device is not connected.     */
    USB_ATTACHED,         /* @emem USB device connected.               */
    USB_RESET,            /* @emem USB device has been reset by host & 
                                    a unique address assigned */
    USB_CONFIGURED,       /* @emem USB device has been configured by host 
                              and host can now use device functions 
                              (transmission or reception on endpoints 
                              can begin).
                           */
    USB_SUSPENDED         /* @emem USB device is in suspende mode   */
} USB_DEVICE_STATES;


/* @enum USB_STATUS |
   The USB_STATUS holds various usb error constants
   returned by funtions being called by appilcations.
   This is the only error mechanism avaiable for appilcation
   interface. So appilcation callee should check specifically 
   for USB_ERROR and proceed further.
*/
typedef enum USB_STATUS_t
{
    USB_OK = 1,          /* @emem Funtion call successful  */
    USB_ERROR = -1       /* @emem Funtion call unsucessful */
} USB_STATUS;


/*
  @func  USB device initialization function.
  This function initializes all the usb resources and the usb device itself.
  
  @comm After initialization the application needs to check for 
  USB_CONFIGURED device state for configuration before transmitting or 
  reception on end point. The configuration files USB_IIL_CFG.H and 
  USB_IDL_CFG.H needs to be initialized for proper device funtioning.

  Returns USB_OK if device initialization is success else USB_ERROR
*/
USB_STATUS USBD_device_initialize (void);


/*
  @func  USB device state.
  This function returns the USB_DEVICE_STATES defined above. The application 
  can check for device conditions like attached, idle etc. After device
  initialization the application needs to check for USB_CONFIGURED device 
  state for configuration before transmitting or reception on end point. 

  Returns the current device state.
*/
IFX_UINT8  USBD_get_device_state( void );


/*
  @func  USB transmit function. This function is implemented as synchronous call.
  The application needs to call this for transmitting data on any end-point.
  The caller is blocked until return is executed. The function is not
  re-entrant and currently implemented as low-level driver call. 
  Eventhough call is not re-entrant (global tx fifo filling warning flag used), 
  even if a call comes during execution of this routine, since fifo validity 
  check inside this funtion gets negated, this function will return error code.

  @retval usb status 
  @flag  USB_ERROR | if trasnmit request fails
  @flag  Else | Actual number of bytes transmitted.

  @comm This interface doenot check whether the endpoint is configured for
  reception or transmission. So it is upto the application for raising the
  transmit request on proper endpoint number. 
  
*/
IFX_SINT32 USBD_transmit_ep0
( 
 IFX_UINT8 *pData,      /*@parm pointer to application data buffer*/
 IFX_UINT32 bytesRequested, /*@parm Number of bytes requested by application 
                              for transmission*/
 IFX_UINT8 ZLP_flag         /*@parm zero length packet flag. set this to 1 for.
                              ZLP (ZeroLengthPacket) transmission*/
);

/*
  @func  USB transmit function. This function is implemented as synchronous call.
  The application needs to call this for transmitting data on any end-point.
  The caller is blocked until return is executed. The function is not
  re-entrant and currently implemented as low-level driver call. 
  Eventhough call is not re-entrant (global tx fifo filling warning flag used), 
  even if a call comes during execution of this routine, since fifo validity 
  check inside this funtion gets negated, this function will return error code.

  @retval usb status 
  @flag  USB_ERROR | if trasnmit request fails
  @flag  Else | Actual number of bytes transmitted.

  @comm This interface doenot check whether the endpoint is configured for
  reception or transmission. So it is upto the application for raising the
  transmit request on proper endpoint number. 
  
*/
IFX_SINT32 USBD_transmit
( 
 IFX_UINT8 ep,          /*@parm endpoint number for transmission*/
 IFX_UINT8 *pData,      /*@parm pointer to application data buffer*/
 IFX_UINT32 bytesRequested, /*@parm Number of bytes requested by application 
                              for transmission*/
 IFX_UINT8 ZLP_flag         /*@parm zero length packet flag. set this to 1 for.
                              ZLP (ZeroLengthPacket) transmission*/
);

/*
  @func  USB transmit function for automatic mode. This function is implemented as 
  synchronous call. The application needs to call this for transmitting data on any 
  end-point.
  The caller is blocked until return is executed. The function is not
  re-entrant and currently implemented as low-level driver call. 
  Eventhough call is not re-entrant (global tx fifo filling warning flag used), 
  even if a call comes during execution of this routine, since fifo validity 
  check inside this funtion gets negated, this function will return error code.

  @retval usb status 
  @flag  USB_ERROR | if trasnmit request fails
  @flag  Else | Actual number of bytes transmitted.

  @comm This interface doenot check whether the endpoint is configured for
  reception or transmission. So it is upto the application for raising the
  transmit request on proper endpoint number. 
  
*/
IFX_SINT32 USBD_transmit_Auto_mode
( 
 IFX_UINT8 ep,          /*@parm endpoint number for transmission*/
 IFX_UINT8 *pData,      /*@parm pointer to application data buffer*/
 IFX_UINT32 bytesRequested, /*@parm Number of bytes requested by application 
                              for transmission*/
 IFX_UINT8 ZLP_flag         /*@parm zero length packet flag. set this to 1 for.
                              ZLP (ZeroLengthPacket) transmission*/
);


/*
  @func  USB receive function. This function is implemented as synchronous call.
  The application needs to call this for receving data on any end-point 
  exculding EP0. The caller is blocked until some bytes get filled on the 
  supplied end-point. If actual number of bytes received are lesser than the 
  requested bytes then also this function gets unblocked and returns. If doesnot
  wait until requested number of bytes are received by low-level driver.  
 
  @comm This interface doenot check whether the endpoint is configured for
  reception or transmission. So it is upto the application for raising the
  receive request on proper endpoint number. 

  @retval usb status
  @flag  USB_ERROR | if receive request fails
  @flag  Else | Actual number of bytes received
*/
IFX_SINT32 USB_receive
(
 IFX_UINT8 *pData,          /*@parm pointer to application data buffer.*/
 IFX_UINT16 requestNbytes,  /*@parm Number of bytes requested by application 
                               for reception.*/
 IFX_UINT8 ep               /*@parm endpoint number for reception*/
);


/*
  @func  USB remote wakeup function. This function implements remote wakeup if 
  the usb bus is in suspended mode. The application should check for bus 
  suspension USB_SUSPENDED mode and then can do a call back to this 
  interface.
 
  @retval Always 0
*/
IFX_UINT32 USBD_do_remote_wakeup
(
void                      
);


#endif /* __USB_API_H_ */

