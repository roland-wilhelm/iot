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
** @FILENAME@:       ASC_CFG.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ASC 
**
** =============================================================================
** Contents: User can configure the required functionality of the ASC LLD. 
**           If a praticular feature is required, then the corresponding define 
**           is enabled. If the feature is not required then the corresponding
**           feature is disabled.   
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

#ifndef __ASC_CFG_H
#define __ASC_CFG_H
/*
  @topic1 Configuring the ASC HAL |
  Although the ASC HAL can be used immediately without configuring it to suit a 
  particular application it will often be the case that some features written 
  into the HAL will either be unnecessary; degrade performance to an 
  unacceptable level, take up too much memory or only be required for debugging
   purposes. For this reason the ASC HAL has been designed in such a way that 
   it can be easily configured to remove unused features, a number of optional
    features may be enabled and/or disabled through the ASC_CFG.h file:

  –ASC device number checking

  –Initialisation check on API calls

  Additionally further options which affect the ASC HAL may be present in the 
  System HAL. Depending on the actual system in question these, or other, 
  options may be available:

  –On the fly peripheral clock changing

  –Initial interrupts numbers/priorities settings

  –ASC physical interface (GPIO) configuration

  The System HAL User Guide should be available from the same source as this 
  document, please refer to it for more details on the available settings
   and features.
*/

/* 
  @topic1 ASC driver HAL configuration parameters
*/
/* 
  @def ASC_CFG_DEV_CHK |
  The following define selects whether device ID 
  checking will be performed in the ASC HAL API 
  functions. Disabling this feature will result
  in less code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define ASC_CFG_DEV_CHK  0


/*
  @def ASC_CFG_INIT_CHK |
  The following define selects whether certain
  ASC HAL API functions will check if the HAL
  has been initialised before executing.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define ASC_CFG_INIT_CHK 0


/*
  @def ASC_CFG_STAT_LOG |
  The following define selects whether the ASC 
  HAL should maintain counts of successfully
  received frames and frames with errors on 
  each peripheral it controls.
  This allows application software to gauge 
  the reliability of the connection.

  Disabling this feature will result
  in smaller code and less data.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define ASC_CFG_STAT_LOG    1

/*
  @def ASC_CFG_PCP_SUP |
  The following define may be used to  
  include or exclude PCP support from the 
  ASC HAL.
  Including PCP support results in larger 
  code and more data.
  For systems which do not have a PCP this 
  setting is ignored.
  
  @comm Present version of software is not supporting this feature.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define ASC_CFG_PCP_SUP     0

/*
  @def ASC_CFG_DMA_SUP |
  The following define may be used to  
  include or exclude DMA support from the 
  ASC HAL.
  Including DMA support results in larger 
  code and more data.
  For systems which do not have a DMA 
  controller this setting is ignored.
  
  @comm Present version of software is not supporting this feature.
  
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define ASC_CFG_DMA_SUP     0


/*
  @def ASC_CFG_FLOW |
  The following define may be used to disable
  or enable hardware and software flow control 
  support in the ASC HAL.
  Disabling flow control support in the HAL
  results in smaller code and less data.
  
  @comm Hardware does not support this feature.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define ASC_CFG_FLOW 0


/*
  @topic2 API Function Exclusion |
  If certain API functions are not required then they may be removed in order 
  to reduce	code size. In the HAL distribution all the API functions will 
  be included by default, in order to remove an API function the relevant 
  define should located and value is changed from 1 to 0. This sections detail 
  defines which are available to exclude API functions
  from the HAL.
  Set Macro value as one to include corresponding function code.
  Setting the value to zero not to include the function code
*/

/*
  @def ASC_CFG_FUNC_TERMINATE |
  This controls whether or not the ASC_terminate_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_TERMINATE 1

/*
  @def ASC_CFG_FUNC_READ |
  This controls whether or not the ASC_read API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_READ 1

/*
  @def ASC_CFG_FUNC_WRITE |
  This controls whether or not the ASC_write API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_WRITE 1

/*
  @def ASC_CFG_FUNC_ABORT |
  This controls whether or not the ASC_abort_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_ABORT 1

/*
  @def ASC_CFG_FUNC_STATUS |
  This controls whether or not the ASC_status_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_STATUS 1

/*
  @def ASC_CFG_FUNC_CONTROL |
  This controls whether or not the ASC_control_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CONTROL 1

/*
  @def ASC_CFG_FUNC_CTRL_BAUD |
  This controls whether or not the ASC_ctrl_trns_baud API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_BAUD 1

/*
  @def ASC_CFG_FUNC_CTRL_DATA |
  This controls whether or not the ASC_ctrl_trns_data API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_DATA 1

/*
  @def ASC_CFG_FUNC_CTRL_STOP |
  This controls whether or not the ASC_ctrl_trns_stop API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_STOP 1

/*
  @def ASC_CFG_FUNC_CTRL_PARITY |
  This controls whether or not the ASC_ctrl_trns_parity API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_PARITY 1

/*
  @def ASC_CFG_FUNC_CTRL_ALL |
  This controls whether or not the ASC_ctrl_trns_all API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_ALL 1

/*
  @def ASC_CFG_FUNC_CTRL_IRDA |
  This controls whether or not the ASC_ctrl_irda_cfg API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_IRDA 1

/*
  @def ASC_CFG_FUNC_CTRL_AUTOBAUD |
  This controls whether or not the ASC_ctrl_baud_detect API function is        
  included.

  @comm Hardware is not supporting this feature.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_AUTOBAUD 1

/*
  @def ASC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH |
  This controls whether or not the ASC_ctrl_fifo_get_rx_depth API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH 1

/*
  @def ASC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH |
  This controls whether or not the ASC_ctrl_fifo_get_tx_depth API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH 1

/*
  @def ASC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL |
  This controls whether or not the ASC_ctrl_fifo_get_rx_level API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL 1

/*
  @def ASC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL |
  This controls whether or not the ASC_ctrl_fifo_get_tx_level API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL 1

/*
  @def ASC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL |
  This controls whether or not the ASC_ctrl_fifo_set_rx_level API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL 1

/*
  @def ASC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL |
  This controls whether or not the ASC_ctrl_fifo_set_tx_level API function is 
  included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL 1

/*
  @def ASC_CFG_FUNC_CTRL_FLOW |
  This controls whether or not the ASC_ctrl_flow API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_FLOW 1

/*
  @def ASC_CFG_FUNC_CTRL_ENABLE |
  This controls whether or not the ASC_ctrl_enable API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_ENABLE 1


/*
  @def ASC_CFG_FUNC_CTRL_DISABLE |
  This controls whether or not the ASC_ctrl_disable API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ASC_CFG_FUNC_CTRL_DISABLE 1

/*
User can configure the required functionality of the
ASC LowLevelDriver in this file. If a praticular
feature is required, then the corresponding define is enabled.
If the feature is not required then the corresponding feature
is disabled.   
*/

/*
  @def ASC_CFG_PEN |
  The following define selects whether the
  parity bit should be checked when a 
  packet is received by the ASC module.

  This define is ignored when the module is 
  operating in IrDA mode.
  
  @flag 0 | Disable the parity error interrupt
  @flag 1 | Enable the parity error interrupt

*/
#define ASC_CFG_PEN       0

/*
  @def ASC_CFG_OVR_CHK |
  The following define selects whether the
  over run check bit should be checked when a 
  packet is received by the ASC module.

  @flag 0 | Disable the over run error interrupt
  @flag 1 | Enable the over run error interrupt
*/
#define ASC_CFG_OVR_CHK   0


/*
  @def ASC_CFG_FRAME_CHK  |
  The following define selects whether the
  frame error check bit should be checked when a 
  packet is received by the ASC module.

  @flag 0 | Disable the frame error interrupt
  @flag 1 | Enable the frame error interrupt
*/
#define ASC_CFG_FRAME_CHK 0



/*
  @def ASC_CFG_LPBACK  |
  The following define select the device to operate 
  in loop back mode

  @flag 0 | Device operates in non loop back mode
  @flag 1 | Device operates in loop back mode
*/
#define ASC_CFG_LPBACK   0


/*
  @def ASC_CFG_REQUEST_QUEUE_WR |
  The following define selects whether read
  requests should be buffered by the ASC HAL.
  If this define is set to 0 then the 
  application program must wait, after using 
  ASC_read, for the transfer to complete 
  before it may start the next read request.
  This setting (0) results in smaller faster 
  code and less data will be used.
  
  If this define is set to a non zero value
  then the ASC_read API function will be able
  to queue this number of read requests.
  This will result in a small amount of extra
  code and extra data for each request which 
  is to be queued.      
*/
#define ASC_CFG_REQUEST_QUEUE_WR  4            


/*
  @def ASC_CFG_REQUEST_QUEUE_RD |
  The following define selects whether write
  requests should be buffered by the ASC HAL. 
  If this define is set to 0 then the 
  application program must wait, after using 
  ASC_write, for the transfer to complete 
  before it may start the next write request.
  This setting (0) results in smaller, 
  faster, code and less data will be used.
  
  If this define is set to a non zero value
  then the ASC_write API function will be able
  to queue this number of write requests.
  This will result in a small amount of extra
  code and extra data for each request which 
  is to be queued.      
*/
#define ASC_CFG_REQUEST_QUEUE_RD 4

/*
  @def ASC_CFG_RX_FIFO_LEVEL |
  Defines a receive FIFO interrupt trigger level. A
  receive interrupt request (RIR) is always generated
  after the reception of a byte when the filling level of
  the receive FIFO is equal to or greater than ASC_CFG_RX_FIFO_LEVEL
  @comm The value should be in range of 0 to 8.
*/
#define ASC_CFG_RX_FIFO_LEVEL    0

/*
  @def ASC_CFG_TX_FIFO_LEVEL | 
  Defines a transmit FIFO interrupt trigger level. A
  transmit interrupt request (TIR) is always generated
  after the transfer of a byte when the filling level of the
  transmit FIFO is equal to or lower than ASC_CFG_TX_FIFO_LEVEL.
  @comm The value should be in range of 0 to 8.
*/
#define ASC_CFG_TX_FIFO_LEVEL    0


/*
  @def ASC_CFG_BAUD_TOL |
  The user defined baud rate tolerance either positive or negative.
  This tolerance will be calculated by using the following formulae.
  (calculate_baudrate - required_baudrate) / required_baudrate.
  @comm All the standard baud rates can be able to set with the tolerance
  value of 0.0003 when ASC clock frequency at 48MHz.
*/
#define ASC_CFG_BAUD_TOL        0.3

/*
  @def ASC_CFG_RDBUFF_SIZE |
  The software read buffer size. Software buffer will store the received data
  when there are no pending read requests. The stored data will be copied into 
  the read proceeding read requests. Hence this software will buffer try to 
  avoid the receiving data loss.  
  @flag | The buffer size value should be in range of 1 to 4294967295.
*/
#define ASC_CFG_RDBUFF_SIZE     256


/*
  @def ASC_CFG_RMC_VAL |
  This value is used to lower down the ASC clock frequency.
  If this value is zero then ASC module will be disabled.
  @flag The value should be in range of 1 - 255.
*/
#define ASC_CFG_RMC_VAL         1


#endif /* __ASC_CFG_H */

