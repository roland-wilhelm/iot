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
** @FILENAME@:       ASC_API.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ASC 
**
** =============================================================================
** Contents: This file contains #defines, data structures and function prototypes
**           required for the ASC device driver
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      Bhavjit Walha        Release after code review.
**
** @CHANGE_HISTORY@
** =============================================================================
*/	
/* @doc API */


/*
    @topic1 ASC HAL Application Program Interface |
    This section defines the interface between the peripheral hardware 
    abstraction layer and the application software. It defines the constants,
    typedef names, function names and limitations of the HAL.
    The ASC HAL API utilizes a range of constants and typedef names in order 
    to interact in a logical way with the application program. The first 
    section of this chapter will look at these constants and data types.
    
    Please refer to Appendix A - Infineon IFX types for details on the 
    IFX data types. 
*/


#ifndef __ASC_API_H
#define __ASC_API_H

#include "compiler.h"
#include "asc_cfg.h"
#include "sys_api.h"
#include "asc_idl.h"

/*----------------------------------------------------------------------------
-------------------------*/

/*
  @topic2 API constants and typedefs
*/

/*
@def  ASC_API_V_MAJ  | 
ASC_API_V_MAJ is defined to the major version of this API which the ASC HAL
supports. This version is defined as 0.1 so the following define will be in
ASC_API.h:

#define ASC_API_V_MAJ 0

Application software may check this field to determine if the HAL API 
version is acceptable. ASC_API_V_MAJ will be advanced whenever a change is 
made to this API which will result in it being incompatible with older 
versions, this will only be done if the	API cannot be extended in a 
way which maintains backwards compatibility*/
#define ASC_API_VER_MAJ 0     
/*
@def  ASC_API_V_MIN  |
ASC_API_V_MIN is defined to the minor version of this API which the ASC HAL
supports. This version is defined as 0.1 so the following define will be in 
ASC_API.h:

#define ASC_API_V_MIN 1

Application software may check this field to determine if the HAL API 
version is acceptable. ASC_API_V_MIN will be advanced whenever an extension 
is made to this	API which does not affect backwards compatibility. 
*/
#define ASC_API_VER_MIN 1


/*
  @type ASC_DEVICE typedef | This indicates the Device ID
  @comm ASC_DEVICE is used in the API wherever a device must be selected. 
  This is required because many ASC peripherals may be implemented in 
  the same system.
*/
typedef IFX_UINT8 ASC_DEVICE;


/*
  @enum ASC_STATUS | 
  @comm Many of the following API functions will return an ASC_STATUS data 
  type. This is a typedef name which is defined as an enumeration, it can 
  be found in ASC_API.h. ASC_STATUS is used by the HAL to return both the 
  initial status of an operation and to	communicate any errors encountered 
  during data transmission back to the application via a user call back 
  function.
*/
typedef enum
{
  /*@emem ASC_SUCCESS indicates that an operation completed successfully.*/
  ASC_SUCCESS = 0,     
  /*@emem ASC_ERR is used to indicate that an unspecified error was 
  encountered by the HAL.ASC_ERR will only be used as a last resort 
  when the HAL is unable to describe the error using a more specific error 
  code.*/
  ASC_ERR = 1,         
  /*@emem ASC_ERR_RES is used to indicate that the 
  ASC HAL was unable to reserve a system  resource required to carry out 
  the requested operation. This will only be used when the resource is not 
  covered by the other ASC_ERR_RES constants.*/
  ASC_ERR_RES = 2,     
  /*@emem ASC_ERR_RES_INT is used to indicate that a required interrupt
   number/priority is currently unavailable for use by the HAL. This 
   error will be encountered either when an attempt is made to change 
   an interrupt number/	priority during run time or when ASC_initialise_dev 
   is called. If interrupt numbers/priorities cannot be dynamically 
   changed due to hardware limitations then ASC_ERR_NOT_SUPPORTED_HW will 
   be returned upon any attempt to use an incompatible number/priority.*/
  ASC_ERR_RES_INT = 3, 
  /*@emem ASC_ERR_RES_MEM is used to indicate that the HAL was unable to 
  allocate enough memory to complete the requested operation.*/
  ASC_ERR_RES_MEM = 4, 
  /*@emem ASC_ERR_RES_IO is used to indicate that one or more physical 
  connection lines are unavailable. This may be because a line is shared 
  with another peripheral (and has been	reserved) or if it is currently 
  in use as a general purpose I/O line.*/
  ASC_ERR_RES_IO = 5,  
  /*@emem ASC_ERR_NOT_SUPPORTED is used to indicate that a requested operation
   cannot be performed because it is not supported in software. This may be 
   because a required  software module has been compiled out*/
  ASC_ERR_NOT_SUPPORTED = 6, 
  /*@emem ASC_ERR_NOT_SUPPORTED_HW is used to indicate that a requested 
  operation	cannot be performed because a required feature is not 
  supported in hardware.*/
  ASC_ERR_NOT_SUPPORTED_HW = 7, 
    /*@emem ASC_ERR_UNKNOWN_DEV indicates that a device ID passed to an 
    API function was not valid.*/
  ASC_ERR_UNKNOWN_DEV = 8,   
  /*@emem ASC_ERR_BUSY is returned if the ASC HAL is already busy performing
   an operation	and the request queue is full or disabled. See Configuring 
   the ASC HAL for information about disabling/enabling request queuing in 
   the ASC HAL.*/
  ASC_ERR_BUSY = 9,            
  /*@emem ASC_ERR_NOT_INITIALISED is returned if an API function is called 
  before the HAL has been successfully initialised. This checking may be 
  configured out to improve runtime	performance, see Configuring the ASC 
  HAL for information*/
  ASC_ERR_NOT_INITIALISED = 10, 
  /*@emem ASC_ERR_OVR indicates that a data overrun has occurred during 
  data reception (data has been lost because it was not retrieved from 
  the peripheral in time).*/
  ASC_ERR_OVR = 11,            
  /*@emem ASC_ERR_PARITY is used to inform the user that a parity error
   was detected during data reception.*/
  ASC_ERR_PARITY = 12,          
  /*@emem ASC_ERR_FRAME indicates that a frame error was detected during 
  data reception.*/
  ASC_ERR_FRAME = 13           
} ASC_STATUS;


/*
  @enum ASC_CTRL_CODE |
  @comm This is a typedef name which is defined as an enumeration.
  ASC_CTRL_CODE defines a number of enumeration constants which are
  used to request a specific operation from the ASC_control_dev API function.
*/
typedef enum
{
  /*@emem This enumeration constant is used with the ASC_control_dev API 
  function.	ASC_CTRL_TRNS_BAUD may be used during runtime to change the 
  baud rate. Please refer to ASC_control_dev and ASC_COM_PARMS for more 
  information.*/
  ASC_CTRL_TRNS_BAUD = 0,    
  /*@emem This enumeration constant is used with the ASC_control_dev API
   function. ASC_CTRL_TRNS_DATA may be used during runtime to change the 
   number of data bits expected per data frame. Please refer to 
   ASC_control_dev, ASC_COM_PARMS and ASC_DATA for more information.*/
  ASC_CTRL_TRNS_DATA = 1,   
  /*@emem This enumeration constant is used with the ASC_control_dev API
   function.ASC_CTRL_TRNS_STOP may be used during runtime to change the 
   number of stop bits expected at the end of a data frame. Please refer 
   to ASC_control_dev,ASC_COM_PARMS and ASC_STOP for more information.*/
  ASC_CTRL_TRNS_STOP = 2,    
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function.	ASC_CTRL_TRNS_PARITY may be used during runtime to set 
  the required parity behavior (no parity, even parity, odd parity etc). 
  Please refer to ASC_control_dev, ASC_COM_PARMS and ASC_PARITY for more 
  information.*/
  ASC_CTRL_TRNS_PARITY = 3,  
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function.ASC_CTRL_TRNS_ALL may be used during runtime to set 
  operating mode, parity, stop bits, data bits and baud rate in one 
  operation. Please refer to ASC_control_dev, ASC_COM_PARMS, ASC_DATA,
   ASC_PARITY and ASC_STOP for more information.*/
  ASC_CTRL_TRNS_ALL = 4,     
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function.	ASC_CTRL_IRDA_CFG may be used during runtime to configure
   IrDA settings. IrDA may not always be supported in hardware. Please refer
    to ASC_control_dev for more	information.*/
  ASC_CTRL_IRDA_CFG = 5,     
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function to return the depth of the receive FIFO supported in 
  hardware. Please refer to ASC_control_dev for	more information.*/
  ASC_CTRL_FIFO_GET_RX_DEPTH = 6,
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function to return the  depth of the transmit FIFO supported in 
  hardware. Please refer to ASC_control_dev for	more information.*/
  ASC_CTRL_FIFO_GET_TX_DEPTH = 7,
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function to return the current filling level of the receive FIFO
   at which an interrupt will be generated. Please refer to ASC_control_dev
    for more information.*/
  ASC_CTRL_FIFO_GET_RX_LEVEL = 8,
  /*@emem This enumeration constant is used with the ASC_control_dev API
   function to return the current filling level of the transmit FIFO at
    which an interrupt will be generated. Please refer to ASC_control_dev 
    for more information.*/
  ASC_CTRL_FIFO_GET_TX_LEVEL = 9,
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function to set the filling level of the receive FIFO at which 
  an interrupt will be generated. If this value is high there will be 
  less interrupt overhead but the risk of losing data will be greater. Please
   refer to ASC_control_dev for more information.*/
  ASC_CTRL_FIFO_SET_RX_LEVEL = 10,
  /*@emem This enumeration constant is used with the ASC_control_dev API 
  function to set the  filling level of the transmit FIFO at which an 
  interrupt will be generated. If this value is	low there will be less 
  interrupt overhead but the risk of losing data will be greater. Please
   refer to ASC_control_dev for more information.*/
  ASC_CTRL_FIFO_SET_TX_LEVEL = 11,
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function.	ASC_CTRL_FLOW may be used to configure hardware and 
  software flow control. Please refer to ASC_control_dev for more information.
   Flow control support can be removed from the HAL, please refer to 
   Configuring the ASC HAL for more information.*/
  ASC_CTRL_FLOW = 12,             
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function.	ASC_CTRL_BAUD_DETECT is used to request baud rate 
  auto-detection in hardware, if there is no support for this then 
  ASC_ERR_NOT_SUPPORTED_HW will be returned. Please refer to ASC_control_dev 
  for more information.*/
  ASC_CTRL_BAUD_DETECT = 13,      
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function. ASC_CTRL_DISABLE may be used to disable an ASC peripheral,
   any IO pins previously allocated will all be set to inputs. 
   Please refer to ASC_control_dev for more	information.*/
  ASC_CTRL_DISABLE = 14,          
  /*@emem This enumeration constant is used with the ASC_control_dev 
  API function. ASC_CTRL_ENABLE may be used to enable an ASC peripheral,
   any IO pins previously allocated will all be set to inputs/outputs as 
   required. Please refer to ASC_control_dev for more information.*/
  ASC_CTRL_ENABLE  = 15           
} ASC_CTRL_CODE;


/*
  @enum ASC_PARITY |
  @comm ASC_PARITY is used to specify a list of parity options supported 
  in the API. Not all of these options will be available on all peripherals.
*/
typedef enum
{
  /*@emem ASC_PARITY_NONE is used to specify no parity bit.*/
  ASC_PARITY_NONE = 0,     
  /*@emem ASC_PARITY_ODD is used to specify odd parity.*/
  ASC_PARITY_ODD = 1,      
  /*@emem ASC_PARITY_EVEN is used to specify even parity.*/
  ASC_PARITY_EVEN = 2,     
  /*@emem ASC_PARITY_STICKY_1is used to specify that the parity bit 
  is always set.*/
  ASC_PARITY_STICKY_1 = 3, 
  /*@emem ASC_PARITY_STICKY_0 is used to specify that the parity bit 
  is always clear.*/
  ASC_PARITY_STICKY_0 = 4  
} ASC_PARITY;


/*
  @enum ASC_MODE |
  @comm ASC_MODE is a typedef name which is defined as an enumeration in 
  ASC_API.h. ASC_MODE is used to specify the operating mode of the ASC device. 
  Not all of these options will be available on all peripherals
*/
typedef enum
{
  /*@emem ASC_ASYNC is used to specify asynchronous mode where 
  only two peripherals are connected.*/
  ASC_ASYNC        = 0,         
  /*@emem ASC_ASYNC_MASTER is used to specify asynchronous mode where 
  many slaves exist and the peripheral controlled by the HAL is a 
  master device.*/
  ASC_ASYNC_MASTER = 1,  
  /*@emem ASC_ASYNC_SLAVE is used to specify asynchronous mode where many 
  slaves exist and the peripheral controlled by the HAL is a slave device.*/
  ASC_ASYNC_SLAVE  = 2,   
  /*@emem ASC_SYNC_R is used to specify synchronous receive mode.*/
  ASC_SYNC_R       = 3,        
  /*@emem ASC_SYNC_T is used to specify synchronous transmit mode.*/
  ASC_SYNC_T       = 4,        
  /*@emem ASC_IRDA is used to specify IrDA mode.*/
  ASC_IRDA         = 5           
} ASC_MODE;


/*
  @enum ASC_STOP |
  @comm ASC_STOP is a typedef name which is defined as an enumeration 
  in ASC_API.h.	ASC_STOP is used to specify a list of stop bit options 
  supported in the API. Not all of these options will be available on 
  all peripherals and some may require that other communication settings 
  be configured in a certain way. */
typedef enum 
{
  /*@emem ASC_STOP_1_5 used to specify 1.5 stop bit, hardware does 
  not support this mode.*/ 
  ASC_STOP_1_5 = 1,    
  /*@emem ASC_STOP_2 used to specify 2 stop bits.*/
  ASC_STOP_2   = 2,
  /*@emem ASC_STOP_1 used to specify 1 stop bit.*/
  ASC_STOP_1   = 3      
} ASC_STOP;


/*
  @enum ASC_DATA |
  @comm ASC_DATA is a typedef name which is defined as an enumeration in 
  ASC_API.h.ASC_DATA is used to specify a list of data bit options supported 
  in the API. Not all of these options will be available on all peripherals.
*/
typedef enum
{
  /*@emem ASC_DATA_5 is used to specify 5 data bits per frame, 
  hardware does not support this mode.*/
  ASC_DATA_5 = 0,   
  /*@emem ASC_DATA_6 is used to specify 6 data bits per frame, 
  hardware does not support this mode.*/
  ASC_DATA_6 = 1,   
  /*@emem ASC_DATA_7 is used to specify 7 data bits per frame*/
  ASC_DATA_7 = 2,   
  /*@emem ASC_DATA_8 is used to specify 8 data bits per frame*/
  ASC_DATA_8 = 3,   
  /*@emem ASC_DATA_9 is used to specify 9 data bits per frame*/
  ASC_DATA_9 = 4   
} ASC_DATA;


/*
  @struct ASC_COM_PARMS |
  @comm ASC_COM_PARMS is a typedef name which is defined as a structure.
  The ASC_COM_PARMS structure is used to specify complete
  communication settings for an ASC device. It is used with the ASC_control_dev
   API function.
*/
typedef struct
{
  ASC_MODE ASC_mode;          /*@field Mode of the module*/
  ASC_PARITY ASC_com_parity;  /*@field Parity of module*/
  ASC_DATA ASC_com_data;      /*@filed Number of data bits*/
  ASC_STOP ASC_com_stop;      /*@field Number of stop bits*/
  IFX_UINT32 ASC_com_baud;    /*@field Baud rate of module*/
} ASC_COM_PARMS;

/*
  @struct ASC_TRANSFER |
  @comm ASC_TRANSFER is used by the ASC_read and ASC_write functions to provide
  information regarding the data transfer that is to be performed.
*/
typedef struct ASC_transfer
{
  /*@field Address of the data buffer which should be pre-initialised with the 
  data to be written.*/
  void *ASC_buffer;                
  /*@field The size of the data buffer, when this number of items has been sent
   by the peripheral the transfer is deemed complete and the application 
   software notified.*/
  IFX_UINT32 ASC_buffer_size;      
  /*@field The number of data frames read/written from/to ASC_buffer*/
  IFX_UINT32 ASC_return_num;       
  /*@field Should be set using one of the constants which are defined in the 
  SYS_TRNS_MODE enum*/
  SYS_TRANS_MODE ASC_transfer_mode;
        /*@field Address of the user call back function to call when 
        the transfer is complete. This may be set to 0 if no user call 
        back function is to be invoked.*/
  void(*ASC_trans_ucb)(struct ASC_transfer *, ASC_STATUS);
  /*@field Address of the slave to write data to if slave addressing 
  is supported in hardware.*/
  IFX_UINT32 ASC_slave_device;     
} ASC_TRANSFER;


/*
  @enum ASC_FLOW_TYPE |
  @comm Select the type of flow control to use on a selected ASC device.
*/
typedef enum
{
  /*@emem Flow control will not be handled by either software or hardware*/
  ASC_FLOW_OFF  = 0,  
  ASC_FLOW_SOFT = 1, /*@emem Flow control will be handled by software*/
  ASC_FLOW_HW   = 2 /*@emem Flow control will be handled by hardware*/
} ASC_FLOW_TYPE;


/*
  @struct ASC_FLOW_CTRL_SETUP |
  @comm Used to enable, disable and set up software
  and hardware flow control on an ASC device. 
*/
typedef struct
{
  ASC_FLOW_TYPE ASC_flow_type;  /*@field Set to one of the constants which are 
                                         defined in ASC_FLOW_TYPE.*/
  /*@field If software flow control is enabled then ASC_soft_xon should be set 
  to the XON character*/
  IFX_UINT16 ASC_soft_xon;      
  /*@field If software flow control is enabled then ASC_soft_xoff  should be set
   to the XOFF character*/
  IFX_UINT16 ASC_soft_xoff;     
} ASC_FLOW_CTRL_SETUP;


/*
  @struct ASC_STAT_INF |
  @comm It is used by the ASC_status_dev API function to return configuration 
  information about an ASC device, which includes the statistics, provided 
  the value of ASC_CFG_STAT_LOG is 1. 
*/
typedef struct
{
  ASC_COM_PARMS ASC_com_parms;  /*@field Configuration parameters of 
  an ASC device.*/

  #if ASC_HW_FIFO_RX > 0
  IFX_UINT8 ASC_rx_fifo_lev;   /*@field Users configured receive FIFO level.
   It will be included in statistics if hardware supports receive FIFO. */
  #endif
  #if ASC_HW_FIFO_TX > 0
  IFX_UINT8 ASC_tx_fifo_lev;  /*@field Users configured transmit FIFO level. 
  It will be included in statistics if hardware supports transmit FIFO. */
  #endif
  #if ASC_CFG_STAT_LOG == 1
  /*@field Number of frames received successfully without errors.*/
  IFX_UINT32 ASC_successful; 
  /*@field Counter for frames received with frame error*/
  IFX_UINT32 ASC_frame_errs; 
  /*@field Number of frames received with parity error*/
  IFX_UINT32 ASC_parity_errs; 
  /*@field Counter for frames received with over run error*/
  IFX_UINT32 ASC_ovr_errs;  
  #endif
} ASC_STAT_INF;

/*
  ASC HAL API function prototypes:
*/

/*   @topic2 API Functions |*/

/*
  @func ASC driver initialization function,
  this function initialises the internal data structures of the HAL related to 
  the device selected by ASC_device, allocates any required system resources 
  and configures the peripheral according to the ASC_COM_PARMS structure. 
  The ASC_COM_PARMS	structure must be initialised by the user before calling 
  ASC_initialise_dev. This function	must be called successfully before any of 
  the other API functions are used and if ASC_terminate_dev is called then 
  ASC_initialise_dev must be called again before using the other API functions.
  Initialisation of one HAL should run to completion (successfully or otherwise)
   before the next HAL is initialised. For this reason ASC_initialise should 
   not be called from an ISR or user callback function.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Enable the module by programming the clock 
  control register.
  @flag: (DESIGN)  | - Set interrupts priorities and IO ports.
  @flag: (DESIGN)  | - Program the controller with the application provided 
  configuration parameters (Mode, number of data bits and stop bits and parity)
                       by calling ASC_set_all API. 
  @flag: (DESIGN)  | - Program receive and transmit FIFOs with the user defined 
  levels.
  @flag: (DESIGN)  | - Initialize all data structures and set the baud rate.
  @flag: (DESIGN)  | - Enable ASC and global interrupt.
  @retval  ASC status
  @flag ASC_SUCCESS | Initialization is success.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Require baud rate and FIFO levels are not 
  with in the device supported limits.
  @flag ASC_ERR_NOT_SUPPORTED    | Not able to get the required baud rate 
  below the user configured tolerance level.
*/
ASC_STATUS ASC_initialise_dev
(
  /*@parm ASC hardware module identification number.*/
  ASC_DEVICE ASC_device,     
  /*@parm Driver initialization configuration parameters.*/
  ASC_COM_PARMS *ASC_setup   
);


#if ASC_CFG_FUNC_TERMINATE == 1
/*
  @func ASC driver termination function,
  this function sets the peripheral, selected by the ASC_device parameter,
   into a disabled state and frees any system resources previously 
   allocated in ASC_initialise. After this function has been called 
   ASC_initialise_dev must be called successfully before any of	the other
    API functions are used.	ASC_terminate_dev should not be called from an
     ISR or user callback function.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Disable the module by programming clock control 
  register.
  @flag: (DESIGN)  | - Reset IO ports.
  @retval  ASC status
  @flag ASC_SUCCESS | Termination of device is success.
*/
ASC_STATUS ASC_terminate_dev
(
  ASC_DEVICE ASC_device /*@parm ASC hardware module identification number.*/
);
#else
#define ASC_terminate_dev(__ASC_PARM) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_ABORT == 1
/*
  @func ASC driver abort function
  cancels all currently queued data transfers and stops any 
  transfers currently being	processed on the peripheral module selected 
  by ASC_device. ASC_initialise_dev need  not be called after this function 
  before the other API functions can be used, this function	merely clears all 
  current and pending transfers it does not terminate the HAL. New transfers 
  may be requested using ASC_read and/or ASC_write immediately after this
  function returns. All aborted transfers will return an ASC_ERR error code. 
  This function	may be used to clear all requests before changing modes etc.  

  @head4 :(DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Reset baud rate run time control bit.
  @flag: (DESIGN)  | - Reset software receive buffer.
  @flag: (DESIGN)  | - Cancel all pending read and write requests.
  @flag: (DESIGN)  | - Flush receive and transmit FIFOs. 
  @flag: (DESIGN)  | - Set baud rate run time control bit.
  @retval  ASC status
  @flag ASC_SUCCESS | Abort of device is success.
*/
ASC_STATUS ASC_abort
(
  ASC_DEVICE ASC_device /*@parm ASC hardware module identification number.*/
);
#else
#define ASC_abort(__ASC_PARM) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_STATUS == 1
/*
  @func ASC driver status function,
  return the present driver configuration parameters and statistics information. 
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - ASC_STAT_INF.ASC_com_parms.ASC_mode will be set to 
                       the mode the device is currently operating in.
  @flag: (DESIGN)  | - ASC_STAT_INF.ASC_com_parms.ASC_com_parity will be set 
                       to the current parity option in use.
  @flag: (DESIGN)  | - ASC_STAT_INF.ASC_com_parms.ASC_com_data will be set 
                       to indicate the number of data bits the device expects 
                       per data frame.
  @flag: (DESIGN)  | - ASC_STAT_INF.ASC_com_parms.ASC_com_stop will be set to 
                       indicate the number of stop bits the device expects at 
                       the end of a data frame.
  @flag: (DESIGN)  | - ASC_STAT_INF.ASC_com_parms.ASC_com_baud will be set to 
                       the currently selected baud rate.
  @flag: (DESIGN)  | - ASC_STAT_INF.ASC_tx_fifo_lev will specify how many data 
                       frames are currently stored in the transmit FIFO.
  @flag: (DESIGN)  | -  ASC_STAT_INF.ASC_rx_fifo_lev will specify how many data
                       frames are currently stored in the receive FIFO.
  @flag: (DESIGN)  | -  If statistics logging is enabled then the following 
                        members of the ASC_STAT_INF structure will be 
                        available:

           – ASC_successful, the number of frames successfully received.

           – ASC_frame_errs, the number of frames which had a framing error.

           – ASC_parity_errs, the number of frames which had a parity error.

           – ASC_ovr_errs, the number of frames lost due to a slow response 
           time.

  @flag: (DESIGN)  | - These frame counters will be reset to 0 after the 
                       ASC_status_dev API has been called. @retval  ASC status
  @flag ASC_SUCCESS | Status of device success fully read and returned to 
  application.
*/
ASC_STATUS ASC_status_dev
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  /*@parm Users provide data structure to write the current status of 
  the device. */
  ASC_STAT_INF *ASC_stat_inf 
);
#else
#define ASC_status_dev(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CONTROL == 1
/*
  @func ASC driver runtime configuration control function, ASC_control_dev
   may be used as a single entry point for all the control functions. 
   The user would call the desired control function and provide new 
   configuration parameters through ASC_CTRL_CODE and ASC_ctrl_arg 
   parameters respectively.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Call control function specified by the ASC_ctrl_code.
   The ASC_ctrl_code is one of the enumeration constants from ASC_CTRL_CODE 
   to specify the operation to perform.
  @flag: (DESIGN) | - Typecast the ASC_ctrl_arg parameter with respect to the 
  called function. 
  @retval  ASC status
  @flag ASC_SUCCESS | Setting the new configuration parameters is success.
  @flag ASC_ERR     | The provided ASC_ctrl_code does not match with any of 
  the values defined in ASC_CTRL_CODE.
*/
ASC_STATUS ASC_control_dev
(
  /*@parm ASC hardware module identification number.*/
  ASC_DEVICE ASC_device,       
  /*@parm Function to call to specify the operation to perform.*/
  ASC_CTRL_CODE ASC_ctrl_code, 
  /*@parm New configuration parameters*/
  void *ASC_ctrl_arg           
);
#else
#define ASC_control_dev(__ASC_PARM1, __ASC_PARM2, __ASC_PARM3) 
  ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_READ == 1
/*
  @func ASC driver read function,
  the behavior of the ASC_read function depends upon the chosen 
  transfer mode (SYS_TRNS_MCU_INT etc...) and whether or not a user call 
  back function has been provided. If user call back function provided 
  then request will be add it to the tail end of pending list and then return
   ASC_SUCCESS provided the number of pending read requests	are less than 
   ASC_CFG_REQUEST_QUEUE_WR. If no user call back function was supplied then
    the ASC_read API function will not return until the requested transfer has
     completed.	The data will be received in the user specified transfer mode.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - If no user call back function was supplied then the 
  ASC_read API function will not return	until the requested transfer has 
  completed, either successfully or because of an error.
  @flag: (DESIGN)  | - If a user call back function is provided and interrupt
   mode is requested, then the ASC_read function will return immediately with 
   ASC_SUCCESS. 
  @flag: (DESIGN)  | - Once the transfer has completed the user call back 
  function will be invoked and the status of the operation passed to it as 
  an argument. 
  @flag: (DESIGN)  | - The number of frames successfully read will be returned
   in ASC_TRANSFER.ASC_return_num.
  @retval  ASC status
  @flag ASC_SUCCESS | Reading data from device is success.
  @flag ASC_ERR_RES | The number of pending requests crosses the user 
  configured ASC_CFG_REQUEST_QUEUE_RD level or
                      the input parameters do not match.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Requested transfer mode is not supported 
  by hardware.                      
*/
ASC_STATUS ASC_read
(
  /*@parm ASC hardware module identification number.*/
  ASC_DEVICE ASC_device,     
  /*@parm Read request configuration parameter values.*/
  ASC_TRANSFER *ASC_transfer 
);
#else
#define ASC_read(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_WRITE == 1
/*
  @func ASC driver write function,
  the behavior of the ASC_write function depends upon the chosen transfer mode
   (SYS_TRNS_MCU_INT etc...) and whether or not a user call back function has 
   been provided. If no user call back function was supplied then the ASC_write
    API function will not return until the requested transfer has completed.
  If a user call back function is provided and interrupt mode is requested, 
  then the ASC_write function will return immediately with ASC_SUCCESS 
  provided the number of pending write requests	are less than 
  ASC_CFG_REQUEST_QUEUE_WR.Once the transfer has completed the user call back
   function will be invoked and the status of the operation passed to 
   it as an argument. 
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - If no user call back function was supplied then the 
  ASC_write API function will not return
          until the requested transfer has completed.
  @flag: (DESIGN)  | - If a user call back function is provided and interrupt 
  mode is requested, then the
          ASC_write function will return immediately with ASC_SUCCESS. 
  @flag: (DESIGN)  | - Once the transfer has completed the user call back 
  function will be invoked and the 
          status of the operation passed to it as an argument. 
  @flag: (DESIGN)  | - The number of frames successfully written will be 
  returned in ASC_TRANSFER.ASC_return_num.
  @retval  ASC status
  @flag ASC_SUCCESS | Writing data to device is success.
  @flag ASC_ERR_RES | The number of pending requests crosses the user 
  configured ASC_CFG_REQUEST_QUEUE_WR level or
                      the input parameters do not match.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Requested transfer mode is not supported 
  by hardware.                      
*/
ASC_STATUS ASC_write
(
  /*@parm ASC hardware module identification number.*/
  ASC_DEVICE ASC_device,     
  /*@parm Write request configuration parameter values.*/
  ASC_TRANSFER *ASC_transfer 
);
#else
#define ASC_write(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_BAUD == 1
/*
  @func ASC driver runtime baud rate configuration control function,
  ASC_ctrl_trns_baud is used to select the baud rate for the chosen device.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Disable the baud rate generator run control.
  @flag: (DESIGN)  | - Set the application requested baud rate by calling 
                       ASC_set_baud API.
  @flag: (DESIGN)  | - Enable the baud rate generator run control.
  @retval  ASC status
  @flag ASC_SUCCESS | Setting the baud rate of device is success.
  @flag ASC_ERR_NOT_SUPPORTED_HW | The requested baud rate is crosses the hard 
                                  ware supported limits.
  @flag ASC_ERR_NOT_SUPPORTED | Not able to get the requested baud rate with 
                               in the user specified tolerance level.
*/
ASC_STATUS ASC_ctrl_trns_baud
(
  /*@parm ASC hardware module identification number.*/
  ASC_DEVICE ASC_device,   
  /*@parm Application specified baud rate*/
  IFX_UINT32 ASC_ctrl_baud 
);
#else
#define ASC_ctrl_trns_baud(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_DATA == 1
/*
  @func ASC driver data bits run time configuration control function.
  ASC_ctrl_trns_data is used to select the number of data bits per frame. 
  Hardware supports 
  7, 8 and 9 data bits.
  @comm Implemented but not checked
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check the mode of device in which it is operating.
  @flag: (DESIGN)  | - Program the number of data bits provided the mode of 
  device supports.
  @retval  ASC status
  @flag ASC_SUCCESS | The configuration of number of data bits is success.
  @flag ASC_ERR_NOT_SUPPORTED_HW | The present mode of device is not 
  supporting new configuration.
*/
ASC_STATUS ASC_ctrl_trns_data
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  ASC_DATA ASC_ctrl_data /*@parm Specify the required number of data
                                  bits using one of the enumeration constants 
                                  in ASC_DATA.*/
);
#else
#define ASC_ctrl_trns_data(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_STOP == 1
/*
  @func ASC driver stop bits run time configuration control function.
  ASC_ctrl_trns_stop is used to select the number of stop bits expected at 
  the end of a frame. Hardware supports either 1 or 2 stop bits.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Change the number of stop bits provided mode of device 
  supports.
  @retval  ASC status
  @flag ASC_SUCCESS | Parity bit has been set successfully.
  @flag ASC_ERR_NOT_SUPPORTED | The present mode of device is not supporting 
  new configuration.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Hardware is not supporting new configuration
*/
ASC_STATUS ASC_ctrl_trns_stop
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  ASC_STOP ASC_ctrl_stop /*@parm Set to specify the required number of stop 
  bits using one of the enumeration constants in ASC_STOP.*/
);
#else
#define ASC_ctrl_trns_stop(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_PARITY == 1
/*
  @func ASC driver parity bit run time configuration control function.
  ASC_ctrl_trns_parity is used to choose the parity options for a device.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check the operating mode of device.
  @flag: (DESIGN)  | - Change the parity provided mode of device supports.
  @retval  ASC status
  @flag ASC_SUCCESS | Changed the parity bit of device success fully.
  @flag ASC_ERR_NOT_SUPPORTED | The present mode of device is not supporting 
  new configuration.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Hardware is not supporting new configuration
*/
ASC_STATUS ASC_ctrl_trns_parity
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  ASC_PARITY ASC_ctrl_parity  /*@parm Set to the userspecified parity*/
);
#else
#define ASC_ctrl_trns_parity(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_ALL == 1
/*
  @func ASC driver run time configuration control function
  used to configure all the standard communication settings and
  allows the ASC operating mode to be changed.
  The argument should be treated as an ASC_COM_PARMS pointer for the purpose
  of this function, the ASC_COM_PARMS structure, which is pointed to, should be
  initialised to set the desired communication parameters.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Program the parity, number of data bits and stop bits 
  provided the mode supports and the baud rate
                      by calling ASC_set_all API.
  @retval  ASC status
  @flag ASC_SUCCESS | Device is programmed with new configuration values 
  successfully.
  @flag ASC_ERR_NOT_SUPPORTED | Incompatible new configuration parameters 
  or baud rate is not supported by hardware.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Hardware is not supporting new configuration
*/
ASC_STATUS ASC_ctrl_trns_all
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  ASC_COM_PARMS *ASC_ctrl_all  /*@parm New configuration parameters.*/
);
#else
#define ASC_ctrl_trns_all(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif



#if (ASC_CFG_FUNC_CTRL_IRDA == 1) && (ASC_HW_IRDA == 1)
/*
  @func ASC driver run time IrDA configuration control function,
  ASC_ctrl_irda_cfg may be used to configure IrDA when this support is 
  available in hardware.ASC_baud will be used to specify the required pulse 
  width in fixed mode (in nano seconds) or baud rate in variable pulse 
  width (3/16 of bit time) mode.ASC_com_stop used to specify the selected 
  mode (fixed or variable). ASC_STOP_1 used for variable pulse width and 
  ASC_STOP_2 for fixed pulse width.	ASC_com_parity used for RXD input inverted
   mode. ASC_PARITY_ODD or ASC_PARITY_EVEN for RXD input inverted mode and 
   ASC_PARITY_NONE for RXD input non invert mode. Set ASC_mode to ASC_IRDA 
   value.
  @comm Implemented but not checked.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Reset baud rate run time control bit.
  @flag: (DESIGN)  | - call ASC_set_irda API.
  @flag: (DESIGN)  | - Set baud rate run time control bit.
  @retval ASC status
  @flag ASC_SUCCESS | Device is configured for IrDA successfully.
  @flag ASC_ERR     | Selected mode is not IrDA.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Selected baud rate or pulse width is 
  not supported by h/w.
*/
ASC_STATUS ASC_ctrl_irda_cfg
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  ASC_COM_PARMS *ASC_ctrl_irda /*@parm IrDA configuration parameters.*/ 
);
#elif ASC_HW_IRDA == 0 /* No hardware support */
#define ASC_ctrl_irda_cfg(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED_HW 
#else
#define ASC_ctrl_irda_cfg(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_AUTOBAUD == 1
/*
  @func ASC driver run time baud rate detect control function,
  this function is used to attempt to automatically detect the baud rate of an 
  asynchronous
  serial connection.
  @comm Hardware not supported.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Not implemented
  @retval  ASC status
  @flag ASC_SUCCESS | Baud rate is detected and programmed successfully.
*/
ASC_STATUS ASC_ctrl_baud_detect
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  IFX_UINT32 ASC_ctrl_autobaud_hint /*@parm Hint baud rate.*/
);
#else
#define ASC_ctrl_baud_detect(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif


#if (ASC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH == 1)
/*
  @func ASC driver run time receive FIFO depth read control function,
  Return the depth of the receive FIFO available on an ASC
  peripheral controlled by the HAL.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Return receive FIFO depth.
  @retval ASC status
  @flag ASC_SUCCESS | Successfully return the receive FIFO depth.
*/
IFX_UINT8 ASC_ctrl_fifo_get_rx_depth
( 
  ASC_DEVICE ASC_device /*@parm ASC hardware module identification number.*/
);
#else
#define ASC_ctrl_fifo_get_rx_depth(__ASC_PARM1) 0 
#endif

#if ASC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH == 1
/*
  @func ASC driver run time transmit FIFO depth read control function,
  Return the depth of the transmit FIFO available on an ASC peripheral 
  controlled by the HAL.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Return transmit FIFO depth.
  @retval ASC status
  @flag ASC_SUCCESS | Successfully return the receive FIFO depth.
*/
IFX_UINT8 ASC_ctrl_fifo_get_tx_depth
(
  ASC_DEVICE ASC_device /*@parm ASC hardware module identification number.*/
);
#else
#define ASC_ctrl_fifo_get_tx_depth(__ASC_PARM1) 0 
#endif

#if ASC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL == 1
  #if ASC_HW_FIFO_RX > 0
/*
  @func ASC driver run time receive FIFO level read control function,
  Return the filling level at which the receive FIFO will generate an 
  interrupt.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Return receive FIFO interrupt trigger level.
  @retval ASC status
  @flag ASC_SUCCESS | Successfully return the receive FIFO interrupt trigger 
  level.
*/
  IFX_UINT8 ASC_ctrl_fifo_get_rx_level
  ( 
    ASC_DEVICE ASC_device /*@parm ASC hardware module identification number.*/
  );
  #else
  #define ASC_ctrl_fifo_get_rx_level(__ASC_PARM1) 0 
  #endif
#else
#define ASC_ctrl_fifo_get_rx_level(__ASC_PARM1) 0 
#endif

#if ASC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL == 1
  #if ASC_HW_FIFO_TX > 0
/*
  @func ASC driver run time transmit FIFO level read control function,
  Return the filling level at which the transmit FIFO will generate an 
  interrupt.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Return transmit FIFO interrupt trigger level.
  @retval ASC status
  @flag ASC_SUCCESS | Successfully return the transmit FIFO interrupt trigger 
  level.
*/
  IFX_UINT8 ASC_ctrl_fifo_get_tx_level
  ( 
    ASC_DEVICE ASC_device /*@parm ASC hardware module identification number.*/
  );
  #else
  #define ASC_ctrl_fifo_get_tx_level(__ASC_PARM1) 0 
  #endif
#else
#define ASC_ctrl_fifo_get_tx_level(__ASC_PARM1) 0 
#endif



#if ASC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL == 1
  #if ASC_HW_FIFO_RX > 0
/*
  @func ASC driver run time receive FIFO level set control function,
  Set the filling level at which the receive FIFO will generate an interrupt.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program the receive FIFO interrupt trigger level.
  @retval ASC status
  @flag ASC_SUCCESS | Successfully program the receive FIFO interrupt trigger 
  level.
  @flag ASC_ERR_NOT_SUPPORTED_HW | The requested values is not supported by 
  hardware or hardware does not support receive FIFO. 
*/
  ASC_STATUS ASC_ctrl_fifo_set_rx_level 
  (
    /*@parm ASC hardware module identification number.*/
    ASC_DEVICE ASC_device, 
    /*@parm Receive FIFO interrupt trigger level*/
    IFX_UINT8 ASC_fifo_rx_lev_set 
  );
  #else
  #define ASC_ctrl_fifo_set_rx_level(__ASC_PARM1, __ASC_PARM2) 
    ASC_ERR_NOT_SUPPORTED_HW
  #endif
#else
#define ASC_ctrl_fifo_set_rx_level(__ASC_PARM1, __ASC_PARM2) 
  ASC_ERR_NOT_SUPPORTED 
#endif

#if ASC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL == 1
  #if ASC_HW_FIFO_TX > 0
/*
  @func ASC driver run time transmit FIFO level set control function,
  Set the filling level at which the transmit FIFO will generate an 
  interrupt.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program the transmit FIFO interrupt trigger 
  level.
  @retval ASC status
  @flag ASC_SUCCESS | Successfully program the transmit FIFO interrupt 
  trigger level.
  @flag ASC_ERR_NOT_SUPPORTED_HW | The requested values is not supported
   by hardware or hardware does not support transmit FIFO. 
*/
  ASC_STATUS ASC_ctrl_fifo_set_tx_level
  (
    /*@parm ASC hardware module identification number.*/
    ASC_DEVICE ASC_device, 
    /*@parm Transmit FIFO interrupt trigger level.*/
    IFX_UINT8 ASC_fifo_tx_lev_set 
  );
  #else
  #define ASC_ctrl_fifo_set_tx_level(__ASC_PARM1, __ASC_PARM2) 
    ASC_ERR_NOT_SUPPORTED 
  #endif
#else
#define ASC_ctrl_fifo_set_tx_level(__ASC_PARM1, __ASC_PARM2) 
  ASC_ERR_NOT_SUPPORTED 
#endif



#if ASC_CFG_FUNC_CTRL_FLOW == 1
/*
  @func ASC driver run time flow control configuration function,
  Used to set the flow control settings of an ASC peripheral.
  @comm Not implemented.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Hardware does not support this feature.
  @retval  ASC status
*/
ASC_STATUS ASC_ctrl_flow
(
  ASC_DEVICE ASC_device, /*@parm ASC hardware module identification number.*/
  ASC_FLOW_CTRL_SETUP *ASC_ctrl_flow_settings /*@parm Pointer to an 
  ASC_FLOW_CTRL_SETUP structure.*/
);
#else
#define ASC_ctrl_flow(__ASC_PARM1, __ASC_PARM2) ASC_ERR_NOT_SUPPORTED 
#endif

#if ASC_CFG_FUNC_CTRL_DISABLE == 1
/*
  @func ASC driver run time disable control function,
  ASC_ctrl_disable may be used to disable the peripheral, without terminating 
  it. The result of calling this function is that all the GPIO pins the ASC HAL
   has allocated will be set to inputs and the peripheral disconnected. 
   This allows the peripheral to be isolated from the outside world while 
   communication parameters are changed or while GPIO configurations are 
   switched. The behavior of this function may vary in some systems but
  it should always stop the peripheral sending and receiving data.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Reset baud rate run time control bit.
  @retval  ASC status
  @flag ASC_SUCCESS | Successfully disabled ASC module.
*/
ASC_STATUS ASC_ctrl_disable (ASC_DEVICE ASC_device);
#else
#define ASC_ctrl_disable(__ASC_PARM1) ASC_ERR_NOT_SUPPORTED 
#endif


#if ASC_CFG_FUNC_CTRL_ENABLE == 1
/*
  @func ASC driver run time enable control function,
  ASC_ctrl_enable must be called after ASC_ctrl_disable before the peripheral 
  will be able to communicate with other connected devices. The peripheral 
  will be reconnected to the outside world and the GPIO lines set according 
  to the configuration the peripheral has been set into. The behavior 
  of this function may vary in some systems but it should always restore 
  the peripheral to the state last configured successfully.	
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Set baud rate run time control bit.
  @retval  ASC status
  @flag ASC_SUCCESS | Successfully enabled ASC module.
*/
ASC_STATUS ASC_ctrl_enable
(
 ASC_DEVICE ASC_device   /*@parm ASC hardware module identification number.*/
);
#else
#define ASC_ctrl_enable(__ASC_PARM1) ASC_ERR_NOT_SUPPORTED 
#endif

/*
  @func: (DESIGN)  
  Set the mode, data, parity and stop bits. It also sets the
  Baud Rate and may set the IrDA configuration if required.
  @comm: (DESIGN) Synchronous mode, IrDA and wake up modes are not supported 
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program the parity, number of data and stop bits 
  provided the device mode supports.
  @flag: (DESIGN)  | - Disable baud rate run time control bit.
  @flag: (DESIGN)  | - Set the baud rate by calling ASC_set_baud API.
  @flag: (DESIGN)  | - Enable baud rate run time control bit.
  @retval  ASC status
  @flag ASC_ERR_NOT_SUPPORTED_HW | Requested parity, number of data and stop 
  bits not supported by hardware,
                                    baud rate not in supported range of 
                                    hardware.
  @flag ASC_SUCCESS | Successfully program all configuration parameters.                                     

*/
ASC_STATUS ASC_set_all
(
  ASC_DEVICE ASC_device,  /*@parm ASC hardware module identification number.*/
  ASC_COM_PARMS *ASC_ctrl_all  /*@parm Driver configuration parameters.*/
);


/*
  @func: (DESIGN)
  Set priorities for ASC interrupts.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program all ASC service request control registers 
  with the corresponding priority
                       defined in SYS_CFG.h file.
  @retval None
*/
void ASC_set_intr_prior
(
  ASC_DEVICE ASC_device,  /*@parm ASC hardware module identification number.*/
  IFX_UINT8  ASC_tir,     /*@parm Priority for transmit interrupt*/
  IFX_UINT8  ASC_rir,     /*@parm Priority for receive interrupt*/
  IFX_UINT8  ASC_tbir,    /*@parm Priority for transmit buffer interrupt*/
  IFX_UINT8  ASC_eir      /*@parm Priority for error interrupt*/
);



/*
  @func: (DESIGN)
  Set the baud rate according to the user input. May return an
  error if input is out of bounds or the tolerance setting is
  too tight.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check whether required baud rate is with in the limits.
  @flag: (DESIGN)  | - Calculate baud rate timer reload value first without 
                       using fractional divider by using baud rate timer pre 
                       scalar value.
  @flag: (DESIGN)  | - Calculate the baud rate with above resultant baud rate
                       timer reload value.
  @flag: (DESIGN)  | - If the calculate baud rate not with in the user 
                       specified tolerance level use fractional divider.
  @flag: (DESIGN)  | - Use fractional divider with value maximum value. 
  @flag: (DESIGN)  | - By using both fractional divider and desired baud
                       rate values calculate baud rate timer reload value.  
  @flag: (DESIGN)  | - With the resultant baud rate timer reload and fractional
                       divider value calculate the baud rate.
  @flag: (DESIGN)  | - If the calculate baud rate not with in the user 
                       specified tolerance decrement fractional divider by 1.
  @flag: (DESIGN)  | - Repeat the above 3 steps until either fractional divider
                       value becomes zero or the new baud rate with in the user
                        specified tolerance level.
  @retval  ASC status
  @flag ASC_SUCCESS | Setting the baud rate of device is success.
  @flag ASC_ERR_NOT_SUPPORTED_HW | The requested baud rate is crosses
                                   the hard ware supported limits.
  @flag ASC_ERR_NOT_SUPPORTED | Not able to get the requested baud 
                                rate with in the user specified tolerance 
                                level.

*/
ASC_STATUS ASC_set_baud
( 
  /*@parm ASC hardware module identification number.*/
  ASC_DEVICE ASC_device,   
  /*@parm Requested baud rate*/
  IFX_UINT32 ASC_ctrl_baud 
);

/*
  @func: (DESIGN)
  Sets the IrDA configuration as desired by the user
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check the ASC_ctrl_irda->ASC_com_stop to 
                       identify the selected mode (variable or fixed).
  @flag: (DESIGN)  | - If pulse width is variable, call ASC_set_baud 
                       to program the baud rate, else program pulse width 
                       control register.
  @flag: (DESIGN)  | - Program RXD input invert mode.
  @retval  ASC status
  @flag ASC_SUCCESS | Setting the IrDA configuration is success.
  @flag ASC_ERR_NOT_SUPPORTED_HW | Requested pulse width or baud rate are 
                                   not supported by hard ware.
*/
ASC_STATUS ASC_set_irda
(
  ASC_DEVICE ASC_device,   /*@parm ASC hardware module identification number.*/
  ASC_COM_PARMS *ASC_ctrl_irda /*@parm IrDA configuration parameters.*/
);


#endif /* ASC_API_H */

