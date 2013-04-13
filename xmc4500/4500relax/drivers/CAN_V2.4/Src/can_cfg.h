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
** @FILENAME@:       CAN_CFG.h
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: User can configure the required functionality of the CAN LLD. If a 
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
** 17/03/2004      S.A.Kazmi          Release after code review.
** 07/05/2004      Mahesh             Some configuration variable namess are
**                                    changed.  
** 21/06/2004      Mahesh             More comments added to code.  
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

/* @doc API */

#ifndef __CAN_CFG_H
#define __CAN_CFG_H
/*
  @topic1 Configuring the CAN HAL |
  Although the CAN HAL can be used immediately without configuring it to suit a 
  particular application it will often be the case that some features written into 
  the HAL will either be unnecessary; degrade performance to an unacceptable level, 
  take up too much memory or only be required for debugging purposes. For this 
  reason the CAN HAL has been designed in such a way that it can be easily configured 
  to remove unused features, a number of optional features may be enabled and/or 
  disabled through the CAN_CFG.h file:

  –CAN device number checking

  –Initialisation check on API calls

  Additionally further options which affect the CAN HAL may be present in the System HAL. 
  Depending on the actual system in question these, or other, options may be available:

  –On the fly peripheral clock changing

  –Initial interrupts numbers/priorities settings

  –CAN physical interface (GPIO) configuration

  The System HAL User Guide should be available from the same source as this document, 
  please refer to it for more details on the available settings and features.
*/

/* 
  @topic1 CAN driver HAL configuration parameters
*/
/* 
  @def CAN_CFG_DEV_CHK |
  The following define selects whether device ID 
  checking will be performed in the CAN HAL API 
  functions. Disabling this feature will result
  in less code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_DEV_CHK 0


/*
  @def CAN_CFG_INIT_CHK |
  The following define selects whether certain
  CAN HAL API functions will check if the HAL
  has been initialised before executing.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_INIT_CHK 0
/*
  @def CAN_CFG_FUNC_TERMINATE |
  The following define selects whether the HAL API Function
  CAN_Terminate_dev should be included for compilation.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_TERMINATE 1
/*
  @def CAN_CFG_FUNC_ABORT |
  The following define selects whether the HAL API Function
  CAN_Abort should be included for compilation.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_ABORT 1
/*
  @def CAN_CFG_FUNC_STATUS |
  The following define selects whether the HAL API Function
  CAN_Status_dev should be included for compilation.
  Disabling this feature will result in less 
  code being generated.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_STATUS 1
/*
  @def CAN_CFG_FUNC_CONTROL |
  The following define selects whether the HAL API Function
  should be included for compilation.
  Disabling this feature will result in less 
  code being generated.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_CONTROL 1
/*
  @def CAN_CFG_FUNC_READ |
  The following define selects whether the HAL API Function
  CAN_Control_dev should be included for compilation.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_READ 1
/*
  @def CAN_CFG_FUNC_WRITE |
  The following define selects whether the HAL API Function
  CAN_Write_Dev should be included for compilation.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_WRITE 1
/*
  @def CAN_CFG_FUNC_CTRL_TRNS_NODE_ACT |
  The following define selects whether the HAL API Function
  CAN_Ctrl_trns_node_act should be included for compilation.
  Disabling this feature will result in less 
  code being generated.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_CTRL_TRNS_NODE_ACT 1
/*
  @def CAN_CFG_FUNC_CTRL_NODE_EWRN_LVL |
  The following define selects whether the HAL API Function
  CAN_Ctrl_Node_Error_Warn_Level should be included for compilation.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_CTRL_NODE_EWRN_LVL 1
/*
  @def CAN_CFG_FUNC_CTRL_TRNS_BIT |
  The following define selects whether the HAL API Function
  CAN_Ctrl_trns_bit should be included for compilation.
  Disabling this feature will result in less 
  code being generated.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_CTRL_TRNS_BIT 1
/*
  @def CAN_CFG_FUNC_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE |
  The following define selects whether the HAL API Function
  CAN_Ctrl_Node_Frame_Count_Counter_Value should be included for compilation.
  Disabling this feature will result in less 
  code being generated.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE 1
/*
  @def CAN_CFG_FUNC_CTRL_CREATE_GATEWAY |
  The following define selects whether the HAL API Function
  CAN_Ctrl_trns_gateway should be included for compilation.
  Disabling this feature will result in less 
  code being generated.
  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/
#define CAN_CFG_FUNC_CTRL_CREATE_GATEWAY 1

/*
  @def CAN_CFG_FUNC_CTRL_ENABLE |
  The following define selects whether the HAL API Function
  CAN_Ctrl_enable should be included for compilation.
  Disabling this feature will result in less 
  code being generated.

  @flag 0 | Disable the feature
  @flag 1 | Enable the feature
*/

#define CAN_CFG_FUNC_CTRL_ENABLE 1

/*
  @def CAN_CFG_TX_FIFO_ENBL |
  The define decides whether to use FIFO by CAN LLD for a frame transmission.
  Changing this configuration during runtime has no effect.

  @flag 0 | CAN LLD uses standard message object methodology for transmittin a frame.
  @flag 1 | CAN LLD uses FIFO methodology for transmitting a frame.
*/
#define CAN_CFG_TX_FIFO_ENBL        1


/*
  @def CAN_CFG_RX_FIFO_ENBL |
  The define decides whether to use FIFO by CAN LLD for a frame reception.
  Changing this configuration during runtime has no effect.

  @flag 0 | CAN LLD uses standard message object methodology to receive a frame.
  @flag 1 | CAN LLD uses FIFO methodology to receive a frame.
*/
#define CAN_CFG_RX_FIFO_ENBL        1


/*
  @def CAN_CFG_REQUEST_QUEUE_WR |
  The following define sets the maximum number of Write requests that can be 
  supported by the CAN HAL
  
  @flag 0 | Disable the feature
  @flag >0 | Enable the feature
*/
#define CAN_CFG_REQUEST_QUEUE_WR 20

/*
  @def CAN_CFG_REQUEST_QUEUE_RD |
  The following define sets the maximum number of read requests that can be 
  supported by the CAN HAL
  
  @flag 0 | Disable the feature
  @flag >0 | Enable the feature
*/
#define CAN_CFG_REQUEST_QUEUE_RD 20

/*
  @def CAN_CFG_CLOCK_FDR_STEP |
  Value will be used to derive CAN clock from system frequency and
  it ranges from 1 to 1023 in decimal.
*/
#define		CAN_CFG_CLOCK_FDR_STEP						0x00004310	

/*
  @def CAN_CFG_CLOCK_FDR_DIVIDOR_MODE |
  This define select the clock fractional divider mode.
  @flag 1 | Normal
  @flag 2 | Fractional divider mode     
*/
#define		CAN_CFG_CLOCK_FDR_DIVIDOR_MODE				1

/*
  @def CAN_CFG_TX_BUFFER_SIZE_NODE_x[0-3] |
  Configure number of transmit message objects required for CAN 
  corresponding to Node0, Node1, Node2 and Node3.

  Note: the sum of required transmit and receive message objects
  of all nodes should not exceed the limit of 128.
*/
#define		CAN_CFG_TX_BUFFER_SIZE_NODE_0						5
#define		CAN_CFG_TX_BUFFER_SIZE_NODE_1						5
#define		CAN_CFG_TX_BUFFER_SIZE_NODE_2						5
#define		CAN_CFG_TX_BUFFER_SIZE_NODE_3						5

/*
  @def CAN_CFG_RX_BUFFER_SIZE_NODE_x[0-3] |
  Configure number of receive message objects required for CAN  
  corresponding to Node0, Node1, Node2 and Node3.

  Note: the sum of required transmit and receive message objects
  of all nodes should not exceed the limit of 128.
*/
#define		CAN_CFG_RX_BUFFER_SIZE_NODE_0						5
#define		CAN_CFG_RX_BUFFER_SIZE_NODE_1						5
#define		CAN_CFG_RX_BUFFER_SIZE_NODE_2						5
#define		CAN_CFG_RX_BUFFER_SIZE_NODE_3						5	   															   

/*
  @def CAN_CFG_NODEx[0 - 3 ]_INT_TRANSFER_ENABLED |
  Transfer interrupt will be triggered for corresponding node when its belonging
  message object received/transmit message frame. This is true only when
  the define CAN_CFG_NODEx_INTERRUPT_ENABLED value set to 1.

  @flag 0 | Don't trigger interrupt when message frame received/transmitted.
  @flag 1 | Trigger interrupt when message frame received/transmitted.
*/
#define		CAN_CFG_NODE0_INT_TRANSFER_ENABLED	0
#define		CAN_CFG_NODE1_INT_TRANSFER_ENABLED	0
#define		CAN_CFG_NODE2_INT_TRANSFER_ENABLED	0
#define		CAN_CFG_NODE3_INT_TRANSFER_ENABLED	0

/*
  @def CAN_CFG_NODEx[0 - 3]_INT_ALERT_ENABLED |
  Alert interrupt will be triggered for corresponding node when any one 
  of the following conditions happen.
  
  a) Change of BOFF state.
  
  b) Change of error warning level.
   
  c) List length/list object error.

  d) INIT bit set.

  This is true only when the define CAN_CFG_NODEx_INTERRUPT_ENABLED value
  set to 1.

  @flag 0 | Don't trigger alert interrupt.
  @flag 1 | Trigger alert interrupt.
*/
#define		CAN_CFG_NODE0_INT_ALERT_ENABLED	1
#define		CAN_CFG_NODE1_INT_ALERT_ENABLED	1
#define		CAN_CFG_NODE2_INT_ALERT_ENABLED	1
#define		CAN_CFG_NODE3_INT_ALERT_ENABLED	1

/*
  @def CAN_CFG_NODEx[0 - 3]_INT_CFC_ENABLED |
  Frame counter overflow interrupt will be triggered for corresponding node
  when its frame counter about to overflow.  

  This is true only when the define CAN_CFG_NODEx_INTERRUPT_ENABLED value
  set to 1.

  @flag 0 | Don't trigger frame counter overflow interrupt.
  @flag 1 | Trigger frame counter overflow interrupt.
*/
#define		CAN_CFG_NODE0_INT_CFC_ENABLED	1
#define		CAN_CFG_NODE1_INT_CFC_ENABLED	1
#define		CAN_CFG_NODE2_INT_CFC_ENABLED	1
#define		CAN_CFG_NODE3_INT_CFC_ENABLED	1

/*
  @def CAN_CFG_NODEx[0 - 3]_INT_LEC_ENABLED |
  Protocol error trigger interrupt for corresponding node when 
  it found any protocol error.  

  This is true only when the define CAN_CFG_NODEx_INTERRUPT_ENABLED value
  set to 1.

  @flag 0 | Don't trigger protocol error interrupt.
  @flag 1 | Trigger protocol error interrupt.
*/
#define		CAN_CFG_NODE0_INT_LEC_ENABLED	1
#define		CAN_CFG_NODE1_INT_LEC_ENABLED	1
#define		CAN_CFG_NODE2_INT_LEC_ENABLED	1
#define		CAN_CFG_NODE3_INT_LEC_ENABLED	1

#endif /*__CAN_CFG_H */
