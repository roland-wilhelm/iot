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
** @FILENAME@:       ssc_cfg.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: User can configure the required functionality of the SSC LLD. If a 
**           praticular feature is required, then the corresponding define is 
**           enabled. If the feature is not required then the corresponding 
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

#ifndef __SSC_CFG_H
#define __SSC_CFG_H

/*
  @topic1 Configure/Optimise SSC HAL |
  Although the SSC HAL can be used immediately without configuring it to suit a 
  particular application it will often be the case that some features written into 
  the HAL will either be unnecessary; degrade performance to an unacceptable level, 
  take up too much memory or only be required for debugging purposes. For this 
  reason the SSC HAL has been designed in such a way that it can be easily configured 
  to remove unused features, a number of optional features may be enabled and/or 
  disabled through the SSC_CFG.H file:

  –SSC device number checking

  –Initialisation check on API calls

  Additionally further options which affect the SSC HAL may be present in the System HAL. 
  Depending on the actual system in question these, or other, options may be available:

  –Initial interrupts numbers/priorities settings

  –SSC physical interface (GPIO) configuration

  The System HAL User Guide should be available from the same source as this document, 
  please refer to it for more details on the available settings and features.
*/



/* 
  @topic1 SSC driver HAL configuration parameters
*/
/* 
  @def SSC_CFG_DEV_CHK |
  The following define selects whether device ID 
  checking will be performed in the SSC HAL API 
  functions. Disabling this feature will result
  in less code being generated.

  @flag 0 | Disable device number check
  @flag 1 | Enable device number check
*/
#define SSC_CFG_DEV_CHK 0


/*
  @def SSC_CFG_INIT_CHK |
  The following define selects whether certain
  SSC HAL API functions will check if the HAL
  has been initialised before executing.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable initialisation check
  @flag 1 | Enable initialisation check
*/
#define SSC_CFG_INIT_CHK 0




/*
  @def SSC_CFG_STAT_LOG |
  The following define selects whether the SSC 
  HAL should maintain counts of successfully
  received frames and frames with errors on 
  each peripheral it controls.
  This allows application software to gauge 
  the reliability of the connection.
  Disabling this feature will result
  in smaller code and less data.

  @flag 0 | To disable statistics logging use
  @flag 1 | To enable statistics logging use
*/
#define SSC_CFG_STAT_LOG  1

/*
  @def SSC_CFG_PCP_SUP |
  The following define may be used to  
  include or exclude PCP support from the 
  SSC HAL.
  Including PCP support results in larger 
  code and more data.
  For systems which do not have a PCP this 
  setting is ignored.

  Note: Hardware does not support this feature.

  @flag 0 | To disable PCP support use
  @flag 1 | To enable PCP support use

*/
#define SSC_CFG_PCP_SUP 0


/*
  @def SSC_CFG_DMA_SUP |
  The following define may be used to  
  include or exclude DMA support from the 
  SSC HAL.
  Including DMA support results in larger 
  code and more data.
  For systems which do not have a DMA 
  controller this setting is ignored.

  Note: Present version of software does not support this feature.

  @flag 0 | To disable DMA support use
  @flag 1 | To enable DMA support use
*/
#define SSC_CFG_DMA_SUP 0



/*
  @topic2 API Function Exclusion |
  If certain API functions are not required then they may be removed in order to reduce
  code size. In the HAL distribution all the API functions will be included by default, in order
  to remove an API function the relevant define should located and value is changed from 1 to 0.
  This sections detail defines which are available to exclude API functions
  from the HAL.
  Set Macro value as one to include corresponding function code.
  Setting the value to zero not to include the function code
*/

/*
  @def SSC_CFG_FUNC_TERMINATE |
  This controls whether or not the SSC_terminate_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_TERMINATE              1

/*
  @def SSC_CFG_FUNC_READ |
  This controls whether or not the SSC_read API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_READ                   1

/*
  @def SSC_CFG_FUNC_WRITE |
  This controls whether or not the SSC_write API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_WRITE                  1

/*
  @def SSC_CFG_FUNC_ABORT |
  This controls whether or not the SSC_abort API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_ABORT                  1

/*
  @def SSC_CFG_FUNC_STATUS |
  This controls whether or not the SSC_status_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_STATUS                 1

/*
  @def SSC_CFG_FUNC_CONTROL |
  This controls whether or not the SSC_control_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CONTROL                1

/*
  @def SSC_CFG_FUNC_CTRL_BAUD |
  This controls whether or not the SSC_ctrl_trns_baud API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_BAUD              1

/*
  @def SSC_CFG_FUNC_CTRL_DATA |
  This controls whether or not the SSC_ctrl_trns_data API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_DATA              1

/*
  @def SSC_CFG_FUNC_CTRL_CLOCK |
  This controls whether or not the SSC_ctrl_trns_clock API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_CLOCK             1

/*
  @def SSC_CFG_FUNC_CTRL_PHASE |
  This controls whether or not the SSC_ctrl_trns_phase API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_PHASE             1

/*
  @def SSC_CFG_FUNC_CTRL_SHIFT |
  This controls whether or not the SSC_ctrl_trns_shift API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_SHIFT             1

/*
  @def SSC_CFG_FUNC_CTRL_ALL |
  This controls whether or not the SSC_ctrl_trns_all API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_ALL               1

/*
  @def SSC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH |
  This controls whether or not the SSC_ctrl_fifo_get_rx_depth API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH 1

/*
  @def SSC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH |
  This controls whether or not the SSC_ctrl_fifo_get_tx_depth API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH 1

/*
  @def SSC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL |
  This controls whether or not the SSC_ctrl_fifo_get_rx_level API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL 1

/*
  @def SSC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL |
  This controls whether or not the SSC_ctrl_fifo_get_tx_level API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL 1

/*
  @def SSC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL |
  This controls whether or not the SSC_ctrl_fifo_set_rx_level API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL 1

/*
  @def SSC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL |
  This controls whether or not the SSC_ctrl_fifo_set_tx_level API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL 1

/*
  @def SSC_CFG_FUNC_CTRL_ENABLE |
  This controls whether or not the SSC_ctrl_enable API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_ENABLE            1

/*
  @def SSC_CFG_FUNC_CTRL_DISABLE |
  This controls whether or not the SSC_ctrl_disable API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_CTRL_DISABLE           1

/*
  @def SSC_CFG_FUNC_SLVE_SLCT |
  This controls whether or not the SSC_ctrl_slv_oslct API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define SSC_CFG_FUNC_SLV_OSLCT_CFG          1


/*
User can configure the required functionality of the SSC LowLevelDriver
in this file. If a praticular feature is required, then the corresponding
define is enabled. If the feature is not required then the corresponding 
feature is disabled.   
*/

/*
  @def SSC_CFG_DUMMY_DATA |
  The following define should be set to the value which is to be sent out, 
  where requested number of read frames are more than transmitted frames.
  
  Note: If the value of this macro is -1, then this feature will be disabled.
*/
#define SSC_CFG_DUMMY_DATA      '2'

/*
  @def SSC_CFG_SLAVE_DUMMY_DAT |
  The following define decides whether slave should send dummy data when there is no data to
  be transmitted, provided SSC_CFG_DUMMY_DATA (data value to be used to transmit) feature is enabled.
  @flag 0 | Slave does not send dummy data
  @flag 1 | Slave sends dummy data (SSC_CFG_DUMMY_DATA)
*/
#define SSC_CFG_SLAVE_DUMMY_DAT  0

/*
  @def SSC_CFG_TX_IDLE_LEV |
  The following define specifies the level at which the 
  transmit line will be held at when the device is  
  selected. This option may be used with devices which
  have a slave select ability.

  @flag 0 | To hold the transmit line at logic level 0 during active time.
  @flag 1 | To hold the transmit line at logic level 1 during active time.
*/
#define SSC_CFG_TX_IDLE_LEV   0


/*
  @def SSC_CFG_DELAY |
  This define selects delay for the selected(SLSO7) device.
  This feature is fully hardware dependent, software ignore
  this feature if hardware does not support.

  @flag 0 | Device operates in normal mode without delays.
  @flag 1 | Device operates in delayed mode.
*/
#define SSC_CFG_DELAY              0

/*
  @def SSC_CFG_TRAIL_DELAY_CYCLS |
  This define specifies the number of trailing delay cycles and 
  this feature is fully hardware dependent. Software ignores this feature 
  if hardware does not support this feature.

  Value ranges from 0 to 3
*/
#define SSC_CFG_TRAIL_DELAY_CYCLS  0

/*
  @def SSC_CFG_LEAD_DELAY_CYCLS |
  This define specifies the number of leading delay cycles and 
  this feature is fully hardware dependent. Software ignores this feature 
  if hardware does not support this feature.

  Value ranges from 0 to 3
*/
#define SSC_CFG_LEAD_DELAY_CYCLS   0
  

/*
  @def SSC_CFG_INACT_DELAY_CYCLS |
  This define specifies the number of delay cycles when device is 
  in inactive state and this feature is fully hardware dependent. 
  Software ignores this feature if hardware does not support this feature.

  Value ranges from 0 to 3
*/
#define SSC_CFG_INACT_DELAY_CYCLS  0


/*
  @def SSC_CFG_SLV_IDLE_LVL |
  This defines the logic level of the slave mode
  transmit signal MRST when the SSC is deselected
  @flag 0 | MRST is 0, when SSC deselected in slave mode.
  @flag 1 | MRST is 1, when SSC deselected in slave mode.
*/
#define SSC_CFG_SLV_IDLE_LVL   0

/*
  @def SSC_CFG_RX_FIFO_LEVEL |
  Defines a receive FIFO interrupt trigger level. A
  receive interrupt request (RIR) is always generated
  after the reception of a byte when the filling level of
  the receive FIFO is equal to or greater than SSC_CFG_RX_FIFO_LEVEL
  @comm The value should be in range of 0 to 8.
 
  Note: Hardware (TC1130 - A) does not support FIFOs, so 
  user should configure this value to zero.
*/
#define SSC_CFG_RX_FIFO_LEVEL 0

/*
  @def SSC_CFG_TX_FIFO_LEVEL | 
  Defines a transmit FIFO interrupt trigger level. A
  transmit interrupt request (TIR) is always generated
  after the transfer of a byte when the filling level of the
  transmit FIFO is equal to or lower than SSC_CFG_TX_FIFO_LEVEL.
  @comm The value should be in range of 0 to 8.

  Note: Hardware (TCC130 - A) does not support FIFOs, so 
  user should configure this value to zero.
*/
#define SSC_CFG_TX_FIFO_LEVEL  0


/*
  @def SSC_CFG_REQUEST_QUEUE_WR |
  The following define selects how many write
  requests should be buffered by the SSC HAL.
  If this define is set to 0 then the 
  application program must wait after using 
  SSC_write, for the transfer to complete 
  before it may start the next write request.
  
  If this define is set to a non zero value
  then the SSC_write API function will be able
  to queue this number of write requests.

  Note: Provide non negative value.
*/
#define SSC_CFG_REQUEST_QUEUE_WR  4

/*
  @def SSC_CFG_REQUEST_QUEUE_RD |
  The following define selects how many read
  requests should be buffered by the SSC HAL.
  If this define is set to 0 then the 
  application program must wait after using 
  SSC_read, for the transfer to complete 
  before it may start the next read request.
  
  If this define is set to a non zero value
  then the SSC_read API function will be able
  to queue this number of read requests.

  Note: Provide non negative value.
*/
#define SSC_CFG_REQUEST_QUEUE_RD  4


/*
  @def SSC_CFG_TX_CHK |
  This is used to enable or to disable transmit error checking.
  @flag 0 | Disable transmit error check.
  @flag 1 | Enable transmit error check.
*/
#define SSC_CFG_TX_CHK          1

/*
  @def SSC_CFG_RX_CHK |
  This is used to enable or to disable receive error checking.
  @flag 0 | Disable receive error check.
  @flag 1 | Enable receive error check.
*/
#define SSC_CFG_RX_CHK          1

/*
  @def SSC_CFG_PHASE_CHK |
  This is used to enable or to disable phase error checking.
  @flag 0 | Disable phase error check.
  @flag 1 | Enable phase error check.
*/
#define SSC_CFG_PHASE_CHK       1

/*
  @def SSC_CFG_BR_CHK |
  This is used to enable or to disable baud rate error checking.
  @flag 0 | Disable baud rate error check.
  @flag 1 | Enable baud rate error check.
*/
#define SSC_CFG_BR_CHK          1


/*
  @def SSC_CFG_BAUD_TOL |
  This value used to compare the resultant baud rate deviation from the required baud rate.
  Tolerance will be calculated using the following formula.

  (calculate_baudrate - required_baudrate) / required_baudrate.
*/
#define SSC_CFG_BAUD_TOL        0.1

/*
  @def SSC_CFG_RMC_VAL |
  This value is used to lower down the SSC clock frequency.
  If this value is zero then SSC module will be disabled.
  @flag The value should be in range of 1 - 255, if hardware supports RMC value (e.g. TC1765).
  Note: This value should be always zero, if hardware does not support RMC value (e.g. TC1130).
*/
#define SSC_CFG_RMC_VAL         1

/*
  @def SSC_CFG_LPBACK  |
  The following define select the device to operate 
  in loop back mode

  @flag 0 | Device operates in non loop back mode
  @flag 1 | Device operates in loop back mode
*/
#define SSC_CFG_LPBACK   0

#endif /* __SSC_CFG_H */

