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
** @FILENAME@:       CAN_API.h
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: This file contains #defines, data structures and function 
**           prototypes required for the CAN device driver
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      S.A.Kazmi          Release after code review.
** 07/05/2004      Mahesh             CAN_read_dev and CAN_write_dev APIs are
**                                    improved to make code re-entrant.    
** 21/06/2004      Mahesh             More comments added to code.  
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

/* @doc API */
/*
    @topic1 CAN HAL Application Program Interface |
    This section defines the interface between the peripheral hardware abstraction layer and
    the application software. It defines the constants, typedef names, function names and
    limitations of the HAL.
    The CAN HAL API utilizes a range of constants and typedef names in order to interact
    in a logical way with the application program. The first section of this chapter will look at
    these constants and data types.
    
    Please refer to Appendix A - Infineon IFX types for details on the IFX data types. 
*/
#ifndef __CAN_API_H
#define __CAN_API_H

#include "compiler.h"
#include "can_cfg.h"
#include "can_idl.h"
#include "sys_cfg.h"
#include "sys_api.h"
/*-----------------------------------------------------------------------------------------------------*/

/*
  @topic2 API constants and typedefs
*/

/*
@def  CAN_API_VER_MAJ  | 
CAN_API_VER_MAJ is defined to the major version of this API which the CAN HAL
supports. This version is defined as 0.1 so the following define will be in CAN_API.h:

#define CAN_API_VER_MAJ 0

Application software may check this field to determine if the HAL API version is
acceptable. CAN_API_VER_MAJ will be advanced whenever a change is made to this API
which will result in it being incompatible with older versions, this will only be done if the
API cannot be extended in a way which maintains backwards compatibility*/

#define CAN_API_VER_MAJ 0
/*
@def  CAN_API_VER_MIN  |
CAN_API_VER_MIN is defined to the minor version of this API which the CAN HAL
supports. This version is defined as 0.1 so the following define will be in CAN_API.h:

#define CAN_API_VER_MIN 1

Application software may check this field to determine if the HAL API version is
acceptable. CAN_API_VER_MIN will be advanced whenever an extension is made to this
API which does not affect backwards compatibility. 
*/
#define CAN_API_VER_MIN 1
/*
  @type CAN_DEVICE typedef | Indicates the Device ID
  @comm CAN_DEVICE is used in the API wherever a device must be selected. 
  This is required to abstract the number of CAN peripherals implemented in the same system.
*/
typedef IFX_UINT8 CAN_DEVICE;

/*
  @enum CAN_STATUS | 
  @comm Many of the HAL API functions return a CAN_STATUS data type. 
  This is a typedef name which is defined as an enumeration, and can be found in CAN_API.h.
  CAN_STATUS is used by the HAL to return both the initial status of an operation and to
  communicate any errors encountered during data transmission back to the application
  via a user call back function.
*/
typedef enum CAN_STATUS{
  /*@emem CAN_SUCCESS indicates that an operation completed successfully.*/
  CAN_SUCCESS	              = 0,
  /*@emem CAN_ERR is used to indicate that an unspecified error was 
          encountered by the HAL.	CAN_ERR will only be used as a last resort 
		  when the HAL is unable to describe the error using a more specific 
		  error code.
  */
  CAN_ERR                     = 1,

  /*@emem CAN_ERR_RES is used to indicate that the CAN HAL was unable to 
          reserve a system resource required to carry out the requested 
          operation. This will only be used when the resource is not covered
          by the other CAN_ERR_RES constants.
  */
  CAN_ERR_RES                 = 2, 

  /*@emem CAN_ERR_RES_INT is used to indicate that a required interrupt
         number/priority is currently unavailable for use by the HAL. 
         This error will be encountered either when an attempt is made 
         to change an interrupt number or priority during run time or 
         when CAN_initialise_dev is called. If interrupt numbers/priorities
         cannot be dynamically changed due to hardware limitations then 
         CAN_ERR_NOT_SUPPORTED_HW will be returned upon any attempt to 
         use an incompatible number/priority.
  */
  CAN_ERR_RES_INT             = 3,

  /*@emem CAN_ERR_RES_MEM is used to indicate that the HAL was unable to 
          allocate enough memory to complete the requested operation.
  */
  CAN_ERR_RES_MEM             = 4,
  
  /*@emem CAN_ERR_RES_IO is used to indicate that one or more physical 
          connection lines are unavailable. This may be because a line 
          is shared with another peripheral (and has been reserved) or 
          if it is currently in use as a general purpose I/O line.
  */
  CAN_ERR_RES_IO              = 5,

  /*@emem CAN_ERR_NOT_SUPPORTED is used to indicate that a requested operation 
  		  cannot be performed because it is not supported in software. This
  		  may be because a required	software module has been compiled out
  */
  CAN_ERR_NOT_SUPPORTED       = 6,

  /*@emem CAN_ERR_NOT_SUPPORTED_HW is used to indicate that a requested 
          operation cannot be performed because a required feature is not
          supported in hardware.
  */
  CAN_ERR_NOT_SUPPORTED_HW    = 7,

  /*@emem CAN_ERR_UNKNOWN_DEV indicates that a device ID passed to an API
         function was not valid.
  */
  CAN_ERR_UNKNOWN_DEV         = 8,

  /*@emem CAN_ERR_BUSY is returned if the CAN HAL is already busy performing an 
   		  operation and the request queue is full or disabled. See Configuring 
		  the CAN HAL for information about disabling/enabling request 
		  queuing in the CAN HAL.												
  */
  CAN_ERR_BUSY                = 9,
  
  /*@emem CAN_ERR_NOT_INITIALISED is returned if an API function is called
          before the HAL has been successfully initialised. This checking
          may be configured out to improve runtime performance, see 
          Configuring the CAN HAL for information
  */
  CAN_ERR_NOT_INITIALISED     = 10,

  /*@emem CAN_ERR_NET_STUFF indicates that 5 equal bits in a sequence have
          occurred in a part or received message, where this is not allowed.
  */
  CAN_ERR_NET_STUFF           = 11,

  /*@emem CAN_ERR_NET_FORM indicates that an error has occurred in a fixed
          format location of the message received.
  */
  CAN_ERR_NET_FORM            = 12,

  /*@emem CAN_ERR_NET_ACK indicates that the transmission was not 
          acknowledged by any node.*/
  CAN_ERR_NET_ACK             = 13,
	
  /*@emem CAN_ERR_NET_CRC indicates that the CRC value contained in the
          received message is different then the CRC value calculated by
          the device for the same message.
  */
  CAN_ERR_NET_CRC             = 14,

  /*@emem CAN_ERR_NET_BIT0: Two different conditions are signaled by this
          error code.

  		  1) During transmission of a message (or ACK bit, active error flag,
  		     or overload flag), the CAN Node tried to send a dominant bit, 
  		     while the monitored bus value was Recessive.
												
		  2) During Bus-off, this code is set each time a sequence of 11 
		     recessive bits have been monitored. The CPU may use this code
		     as indication that the bus is not currently disturbed.
  */
  CAN_ERR_NET_BIT0            = 15,

  /*@emem CAN_ERR_NET_BIT1: It indicates that during transmission, the CAN Node
          tried to send a recessive level outside the arbitration field and the
          acknowledge slot, but the monitored bus value was dominant.	
  */	
  CAN_ERR_NET_BIT1            = 16,

  /*@emem CAN_ERR_NET_STATE_ACT the node has recovered from 
          Bus-Off and is active now.
  */
  CAN_ERR_NET_STATE_ACT       = 17,

  /*@emem CAN_ERR_NET_STATE_PASS indicates that the node has gone in 
          passive mode.
  */
  CAN_ERR_NET_STATE_PASS      = 18,

  /*@emem CAN_ERR_NET_STATE_OFF indicates that the Node has gone into
          Bus-Off mode.*/
  CAN_ERR_NET_STATE_OFF       = 19,

  /*@emem CAN_ERR_MSG_NEW indicates that a new message has been received 
          in the message buffer. */
  CAN_ERR_MSG_NEW             = 20,

  /*@emem CAN_ERR_MSG_LOST indicates that a message has been lost or 
          overwritten in the message buffer.*/
  CAN_ERR_MSG_LOST            = 21,

  /*@emem CAN_ERR_MSG_RX_OK indicates that message reception 
          has successfully completed.*/
  CAN_ERR_RX_OK               = 22,

  /*@emem CAN_ERR_MSG_TX_OK indicates that message transmission 
          has successfully completed.*/
  CAN_ERR_TX_OK               = 23,

  /*@emem CAN_ERR_FRAMECOUNT_OVERFLOW indicates the frame counter has 
          overflows.*/
  CAN_ERR_FRAMECOUNT_OVERFLOW = 24,

  /*@emem CAN_ERR_ERRORCOUNT_WARNING indicates that the number of errors 
          observed has exceeded the warning level set in the error counter.
  */			
  CAN_ERR_ERRORCOUNT_WARNING  = 25,

  /*@emem CAN_ERR_NODE_DISABLED indiacates the CAN node is disabled, all
          operations are disabled.
  */   
  CAN_ERR_NODE_DISABLED       = 26,

  /*
    @emem CAN_READ_DATA indicates CAN LLD copied the received frame data to
    application provided data buffer. This enum used in CAN_Read_Dev API to
    differentiate the request is added to pending read queue or not.
  */
  CAN_READ_DATA               = 27,

  /*
    @emem CAN_WRITE_DATA indicates application provided data frame data copied to
    one of the freely available h/w message objects. This enum used in CAN_Write_Dev API to
    differentiate the request is added to pending write queue or not.
  */
  CAN_WRITE_DATA              = 28

}CAN_STATUS;


/*
  @enum CAN_CTRL_CODE |
  @comm This is a typedef name which is defined as an enumeration.
  CAN_CTRL_CODE defines a number of enumeration constants which are
  used to request a specific operation from the CAN_control_dev API function.
*/

typedef enum
{
   /*@emem	This enumeration constant is used with the CAN_control_dev API function.
     		CAN_CTRL_SET_NODE_ACT may be used during runtime to change the CAN node
	 		state. 
   */
	CAN_CTRL_TRNS_NODE_ACT = 1,							

    /*@emem	This enumeration constant is used with the CAN_control_dev API function.
	        It may be used during runtime to change the CAN node error warning level. 
	*/
	CAN_CTRL_TRNS_NODE_EWRN_LVL = 2,			   

    /*@emem	This enumeration constant is used with the CAN_control_dev API function.
	        It may be used during runtime to change the CAN node frame count
	        counter value. 
    */
	CAN_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE = 3,		

    /*@emem This enumeration constant is used with the CAN_control_dev API function.
			CAN_CTRL_CREATE_GATEWAY may be used during runtime to create a gateway
			between two CAN nodes. 
    */
	CAN_CTRL_TRNS_GATEWAY = 4,					   

    /*@emem This enumeration constant is used with the CAN_control_dev API function.
	   	    CAN_CTRL_SET_BIT may be used during runtime to change the bit timings,
	   	    segments etc. 
    */
	CAN_CTRL_TRNS_BIT = 5, 

	/*@emem This enumeration constant is used with the CAN_control_dev API function.
			CAN_CTRL_DISABLE may be used to disable a CAN peripheral, any IO pins previously
			allocated will all be set to inputs. 
    */
    CAN_CTRL_DISABLE = 6,

    /*@emem This enumeration constant is used with the CAN_control_dev API function.
			CAN_CTRL_ENABLE may be used to enable a CAN peripheral, any IO pins previously
			allocated will all be set to inputs/outputs as required. 
	*/
	CAN_CTRL_ENABLE = 7,

    /*@emem This enumeration constant can be mainly used to initialise 
            the CAN node when CAN LLD statically compiled with linux kernel.
            After opening device the ioctl API called with this argument.
    */       
	CAN_CTRL_OPEN = 8,

    /* @emem This enumeration constant is used to configure the receive
             message objects dynamically. 
    */
    CAN_CTRL_CFG_RXBUFF = 9,

    /* @emem This enumeration constant used to register the user call back
    		 function with CAN LLD. The user call back function will be
			 called by LLD when it receive CAN message frames and no pending
			 read requests available. In user call back function user/application
			 shall call CAN_read_dev API to read the received frame.

			 User call back function will be called inside the ISR, so it is 
			 recommended to return from user call back function immediately
			 to reduce the effect on the other function executions.
    */
	CAN_CTRL_REG_RCV_UCB = 10,

    /* @emem This enumeration constant used to unregister the user call back
    		 function with CAN LLD. 
    */
	CAN_CTRL_UNREG_RCV_UCB = 11
}CAN_CTRL_CODE;

/*-------------------------------------------------------------------------------------------*/
/*
  @struct CAN_MODE |
  @comm Used to program the device in loop back or in non loop back mode.
  It is used by the CAN_COM_PARMS structure to configure the chosen CAN Node
  at time of initialization. 

  This is also part of CAN_STATUS_INF, which is used to read the status 
  information of a node.     
*/
typedef struct{
	IFX_UINT32	Loop_Back:1;        	/* @field 0--> the chosen node programmed for loop back mode,

                                                  1--> node programmed for non loop back mode */
	IFX_UINT32	Last_Error_Enable:1;	/* Lost error indication interrupt will be enabled. */
	IFX_UINT32	Node_Disable:1;	        /* CAN node will be disabled*/
	IFX_UINT32	Analyzer:1;             /* CAN node will be configured for CAN analyzer mode*/
	IFX_UINT32	Suspend_OCDS:1;         /* Suspend features will be enabled for CAN node for OCDS*/	
	IFX_UINT32	:27;                    /* Unused*/

}CAN_MODE;
/*
@struct CAN_NODE_STATUS |
@comm Used to know the status details of a choosen node 

      E.g.
      
      Frame received/transmitted successfully.

      Alerts, bus off status etc ..

      Part of CAN_STATUS_INF structure, whic is used to read the status of
      choosen node.
*/
typedef struct{
	IFX_UINT32 LEC:3 ;	    /*@field It contains the Last Error code observed in the Node */
	IFX_UINT32 TXOK:1 ;	    /*@field It contains the Information about the successful completion of a frame transmission */
	IFX_UINT32 RXOK:1 ;	    /*@field It contains the Information about the successful completion of a frame reception */	
	IFX_UINT32 ALERT:1 ;	/*@field This bit shows the status of any of these alerts

									a) A change in the bit bus off of the CAN NODE STATUS Register

									b) A change in the Bit EWRN of the CAN NODE STATUS Register

									c) A list Length Error of the Hardware FIFO

									d) Bit init has been set by the MultiCan Hardware
								*/
	IFX_UINT32 EWRN:1 ;	    /*@field This bit gets set if one of the error counters REC or TEC have reached the warning level */
	IFX_UINT32 BUSSOFF:1 ;	/*@field This bit gets set if CAN Node goes in the Bus off State */
	IFX_UINT32 LLE:1 ;	    /*@field This bit gets set if the Hardware list associated with the Node has a Length error*/	
	IFX_UINT32 LOE:1 ;	    /*@field This bit gets set if a hardware message object with wrong list index entry has been detected*/
	IFX_UINT32 SUSACK:1 ;	/*@field This bit gets set if the CAN Node is in suspend mode due to OCDS suspend request*/
	IFX_UINT32 CFCVAL:16;	/*@field These bits contains the frame count/time stamp value of the node Frame counter  */
	IFX_UINT32 :5;          /*Unused*/
	
}CAN_NODE_STATUS;
/*
@struct CAN_NODE_ERROR |
@comm Contains the receive, transmit error counters, error warning level, last error
 (transmit/receive)ocuured and the value increased during last error.

  It is part of CAN_STATUS_INF, which is used to read the status of choosen node.
*/
typedef struct{
	IFX_UINT32 REC:8 ;	    /*@field These bits contain the Receive Error count*/
	IFX_UINT32 TEC:8 ;	    /*@field These bits contain the Transmit Error count*/
	IFX_UINT32 EWRNLVL:8 ;	/*@field These bits contain the Error warning level for the node*/
	IFX_UINT32 LETD:1 ;	    /*@field This bit indicates the direction of last Error, value 0 
										 indicates receive error and 1 indicates transmit error. */
	IFX_UINT32 LECIN:1 ;	/*@field This bit indicates the value by which last Error count was incremented.
								     Value 0 indicates increment by one and value 1 indicates increment by 8. */
	IFX_UINT32 :6 ;	        /*Unused*/

}CAN_NODE_ERROR;
/*
  @struct CAN_STAT_INF |
  @comm It is used by the CAN_status_dev API function to return configuration information 
  about a CAN device, which includes the statistics, provided the value of CAN_CFG_STAT_LOG is 1. 
*/
typedef struct
{
	CAN_MODE		CAN_Mode		;	 /*@field The Mode of operation of the current can node, i.e. normal, loop back etc,
	                                             for details refer CAN_MODE structure definition.*/
	CAN_NODE_STATUS CAN_node_status ;	 /*@field The Node Status for details refer CAN_NODE_STATUS structure definition. */
	CAN_NODE_ERROR  CAN_node_error  ;	 /*@field The Node Error Status, contains the transmit and receive errors, for 
	                                             details refer CAN_NODE_ERROR structure definition.*/
	CAN_STATUS      CAN_Last_Errcode ;	 /*@field The Last Error Code, for more details refer CAN_STATUS enumerated
	                                                  definition section.*/
	IFX_UINT16      CAN_Node_Pend_Reads; /*@field The Node Pending Reads value, in case the transfer mode is SYS_TRX_MCU*/
	IFX_UINT16      CAN_Node_Pend_Writes;/*@field The Node Pending writes value, in case the transfer mode is SYS_TRX_MCU*/
}CAN_STATUS_INF;
/*-------------------------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
			Definition of a structure for the CAN data
  -------------------------------------------------------------------------	*/


/*
  @struct MOFGPR |
  @comm The MOFGPR contains a set of message object link pointer used for gateway functionality.
  It is a part of CAN_MSG_OBJ structure which is used to configure the receive, transmit 
  and gateway message objects.

  All the following information applicable only to Gateway source object.
*/
typedef  struct
{
	IFX_UINT8	BOT; /*For future use, currently not used*/
	IFX_UINT8	TOP; /*For future use, currently not used*/
	IFX_UINT8	CUR; /*@field The current object pointer links to the actual target
                              object within a Gateway structure.*/
	IFX_UINT8	SEL; /*For future use, currently not used*/
}MOFGPR;

/*
  @struct MOFCR |
  @comm Used to configure Gateway control parameters like ID, data etc.. copying from source
  object to destination object. 

  All the following information applicable only to Gateway source object.
*/
typedef struct
{
	IFX_UINT8	Data_Frame_Send:1 ; /*@field If value set then TXRQ is set in the 
	                                         Gateway destination object after transfer of 
	                                         data frame from Gateway source to destination, else
											 TXRQ not set in destination object
	                                         */
	IFX_UINT8	ID_Copy:1 ;         /*@field If set then the identifier of the gateway source
                                             object (after storing the received frame in the source)
                                             is copied to the gateway destination.*/  
	IFX_UINT8	DLC_Copy:1;			/*@field If set then the data length code of the gateway
                                             source object (after storing the received frame in
                                             the source) is copied to the gateway destination.*/
	IFX_UINT8	Data_Copy:1;	   /*@field If set then the data field (registers MODATA0
                                            and MODATA4) of the gateway source object (after
                                            storing the received frame in the source) is copied to
                                            the gateway destination.*/
}MOFCR ;

/*	
	@struct CAN_MESSAGE_OBJECT |
	
	@comm The following data type serves as a software message object. Each access to
	a hardware message object has to be made by forward a pointer to a software
	message object (CAN_MESSAGE_OBJECT). The data type has the following fields:

	MOCfg:

	This byte contains the "Data Length Code" (DLC), the 
	"Extended Identifier" (IDE) and the "Message Direction" (DIR).

	ID: 

	This field is four bytes long and contains either the 11-bit identifier 
	or the 29-bit identifier

	Mask: 

	This field is four bytes long and contains either the 11-bit mask 
	or the 29-bit mask

	Data[8]:
	8 bytes containing the data of a frame
*/
typedef struct
{
	IFX_UINT16		Pri;	  /*@field	Message Object Priority*/	 
	IFX_UINT16		MOCfg;    /*@field	Message object configuration register			*/
	IFX_UINT32		ID;       /*@field	Standard (11-bit)/extended (29-bit) identifier	*/
	IFX_UINT32		Mask;     /*@field  Standard (11-bit)/extended (29-bit) mask		*/
	MOFGPR			Mofgpr ;  /*@field  Message Object Fifo/Gateway Pointer Reg*/
	IFX_UINT8		Data[8];  /*@field  8 data bytes								*/
	IFX_UINT8		MoNum;	  /*@field  This indicates the message object number for Gateway source. 
										This element is ignored for purpose other then Gateway creation.*/	
	MOFCR			Mofcr ;	  /*@field  The Fifo / Gateway pointer control configuration*/	
}CAN_MESSAGE_OBJECT ;

/*
  @struct NECNT |
  @comm Used to set receive, transmit and warning error levels.
  Part of CAN_COM_PARMS, which is used to initialise CAN Node.     
*/
typedef struct{
	IFX_UINT32  Receive_Count:8 ;	/*@field This field contains the receive error counter value of the chosen node*/
	IFX_UINT32  Transmit_Count:8 ;	/*@field This field contains the transmit error counter value of the chosen node*/ 
	IFX_UINT32  Warn_Level:8 ;	    /*@field This field contains the error warning level for the chosen node*/ 
	IFX_UINT32  :8 ;	            /*Unused*/
}NECNT;

/*
  @struct NBTR |
  @comm Used to set the baud rate parameters of CAN node like 
  syncronisation jump width, Tseg1 and tseg2.
  Part of CAN_COM_PARMS, which is used to initialise CAN Node.          
*/
typedef struct
{
	IFX_UINT32  Baud_Prescaler:6 ;	/*@field This field contains the baud rate prescaler value for the chosen node*/ 
	IFX_UINT32  Sync_Jump:2 ;	/*@field This field contains the synchronization jump width value for the chosen node*/	
	IFX_UINT32  Timing_Seg1:4 ;	/*@field This field contains the timing segment 1 value for the chosen node*/
	IFX_UINT32  Timing_Seg2:3 ;	/*@field This field contains the timing segment 2 value for the chosen node*/
	IFX_UINT32  Divider_Mode:1 ;	/*@field If set, the time quantum will last 8 * ( BRP + 1 ) cycles, else time quantum
													will last (BRP + 1) cycles	*/
	IFX_UINT32  :16 ; /*Unused*/	
}NBTR;

/*
  @struct NFCR |
  @comm Used to configure the frame couting mode and incrementing mode.
  Part of CAN_COM_PARMS, which is used to initialise CAN Node.          
*/
typedef struct
{
	IFX_UINT32	Count_value:16	;	        /*@field This field contains the frame count value/ time stamp value for the chosen node*/ 
	IFX_UINT32	Frame_Count_select:3;		/*@field The following modes are possible for Frame Count Mode

												 1) Value = 1:	CFC incremented on Remote Frame

												 2) Value = 2:	CFC incremented on correct Reception

												 3) Value = 4:	CFC incremented on correct Transmission

												The following modes are possible when the Frame Count Mode is in BIT
												Timing Mode:

												1) Value = 0 
														whenever a dominant edge (transition from 1 to 0) is monitored on the receive
														input the time (measured in clock cycles) between this edge and the most
														recent dominant edge is stored in CFC.

												2) Value = 1
														whenever a recessive edge (transition from 0 to 1) is monitored on the receive
														input the time (measured in clock cycles) between this edge and the most
														recent dominant edge is stored in CFC.

												3) Value = 2
														whenever a dominant edge is received as a result of a transmitted dominant
														edge the time (clock cycles) between both edges is stored in CFC.

												4) Value = 3
														whenever a recessive edge is received as a result of a transmitted recessive
														edge the time (clock cycles) between both edges is stored in CFC.

												5) Value = 4
														whenever a dominant edge that qualifies for synchronization is monitored on
														the receive input the time (measured in clock cycles) between this edge and
														the most recent sample point is stored in CFC.

												6) Value = 5
														with each sample point, the time (measured in clock cycles) between the start
														of the new bit time and the start of the previous bit time is stored in CFC[11:0].
														Additional information is written to CFC[15:12] at each sample point:
														
														CFC[15] : Transmit value of actual bit time

														CFC[14] : Receive sample value of actual bit time

														CFC[13:12] : CAN bus information 

											*/
	IFX_UINT32	Frame_Count_mode:2	;	    /*@field The following modes are possible
													 
													 1) Value = 0:	Frame Count Mode
													 	
													 2) Value = 1:	Time Stamp Mode 	

													 3) Value = 2:	Bit Timing Mode
											*/
	IFX_UINT32	:11;                        /*Unused*/
}NFCR;

/*
  @struct CAN_COM_PARMS |
  @comm It is used by CAN_Initialise_dev API to initialise chosen CAN Node,
  for more details of each member field refer to the corresponding structure 
  definition section.     
*/
typedef struct
{
	CAN_MODE             can_mode			;  	/*@field	The Node Operation Mode										*/
	NECNT                can_error_counter	;	/*@field	Node Error Counter settings for the MultiCan Module			*/
	NBTR                 can_bit_timing		;	/*@field	Node Bit timing settings for the MultiCan Module			*/
	NFCR                 can_frame_counter	;	/*@field	Node Frame Counter settings for the MultiCan Module			*/
}CAN_COM_PARMS ;


/*
  @struct CAN_TRANSFER |
  @comm CAN_TRANSFER is used by the CAN_read_Dev and CAN_write_Dev functions to provide
  information regarding the data transfer that is to be performed.
*/

typedef struct can_trans{
	CAN_MESSAGE_OBJECT   *can_buffer ;		/*@field Address of the data buffer					*/
	IFX_UINT8            can_buffer_size ; 	/*@field Number of message objects in the buffer, 
	                                                 used only incase CAN_Ctrl_config_Rcvbuffer API.*/
	SYS_TRANS_MODE       sys_trns_mode ;   /*Transfer mode for the transfer			*/
	void (*CAN_trans_ucb)(struct can_trans*, CAN_STATUS);/*@filed Pointer to user call back function used only incase of
	                                                              CAN_Read_Dev and CAN_Write_Dev APIs,

                                                                  Value 0(zero)--> Blocked read/write API    

        		                 							      Value other than zero make read/write API as non blocked. */

}CAN_TRANSFER ;


/*-----------------------------------------------------------------------------------------------------*/


/*
  CAN HAL API function prototypes:
*/

/*   @topic2 API Functions |*/

/*
  @func CAN driver initialization function,
  this function initialises the internal data structures of the HAL related to the device
  selected by CAN_device, allocates any required system resources and configures the
  peripheral according to the CAN_COM_PARMS structure. The CAN_COM_PARMS
  structure must be initialised by the user before calling CAN_initialise_dev. This function
  must be called successfully before any of the other API functions are used and if
  CAN_terminate_dev is called then CAN_initialise_dev must be called again before
  using the other API functions.
  Initialisation of one HAL should run to completion (successfully or otherwise) before 
  the next HAL is initialised. For this reason CAN_initialise should not be called from 
  an ISR or user callback function.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Enable the module by programming the clock control register.
  @flag: (DESIGN)  | - Set interrupt priorities and IO ports.
  @flag: (DESIGN)  | - Program the controller with the application provided configuration parameters (Mode, number of data bits and stop bits and parity)
                       by calling CAN_Init_Node API. 
  @flag: (DESIGN)  | - Initialise transmit/receive h/w message objects.
  @flag: (DESIGN)  | - If CAN_CFG_TX_FIFO_ENBL macro value set to 1, then TX h/w message objects are
                       programmed for FIFO.
  @flag: (DESIGN)  | - If CAN_CFG_RX_FIFO_ENBL macro value set to 1, then RX h/w message objects are
                       programmed for FIFO.
  @flag: (DESIGN)  | - Initialize all data structures and set the baud rate.
  @flag: (DESIGN)  | - Enable CAN and global interrupt.
  @retval  CAN status
  @flag CAN_SUCCESS | Initialization is success.
  @flag CAN_ERR_NOT_SUPPORTED_HW | Require baud rate and FIFO levels are not with in the device supported limits.
  
*/
CAN_STATUS CAN_Initialise_dev	
( 
	CAN_DEVICE can_device,			/*@parm CAN node hardware module identification number, e.g. 0 --> CAN0, 1 --> CAN1.*/	
	CAN_COM_PARMS* CAN_COM_PARMS	/*@parm Driver initialization configuration parameters.	*/		 
);

#if CAN_CFG_FUNC_TERMINATE == 1
/*
  @func CAN driver termination function,
  this function sets the peripheral, selected by the CAN_device parameter, into a disabled
  state and frees any system resources previously allocated in CAN_initialise. After this
  function has been called CAN_initialise_dev must be called successfully before any of
  the other API functions are used.
  CAN_terminate_dev should not be called from an ISR or user callback function.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Disable the module by programming clock control register.
  @flag: (DESIGN)  | - reset transmit and receive h/w message objects are 
                       associated with particular node.
  @flag: (DESIGN)  | - Reset s/w read and write queue pointers.
  @flag: (DESIGN)  | - Reset IO ports.
  @retval  CAN status
  @flag CAN_SUCCESS | Termination of device is success.
*/
CAN_STATUS	CAN_Terminate_dev 
( 
	CAN_DEVICE can_device /*@parm CAN node hardware module identification number.*/
) ;
#else
#define CAN_Terminate_dev(__CAN_PARM) CAN_ERR_NOT_SUPPORTED 
#endif

#if CAN_CFG_FUNC_ABORT == 1
/*
  @func CAN driver abort function,
  cancels all currently queued data transfers and stops any transfers currently being
  processed on the peripheral module selected by CAN_device. CAN_initialise_dev need
  not be called after this function before the other API functions can be used, this function
  merely clears all current and pending transfers it does not terminate the HAL. New
  transfers may be requested using CAN_read_Dev and/or CAN_write_Dev immediately after this
  function returns. All aborted transfers will return a CAN_ERR error code. This function
  may be used to clear all requests before changing modes etc.  

  @head4 :(DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Call user call back functions associated with read and write
                       software queues with CAN_ERROR as status.
  @flag: (DESIGN)  | - Reset s/w read and write queue pointers.
  @retval  CAN status
  @flag CAN_SUCCESS | Abort of device is success.
*/
CAN_STATUS CAN_Abort 
( 
	CAN_DEVICE can_device /*@parm CAN node hardware module identification number.*/	
) ;
#else
#define CAN_Abort (__CAN_PARM1) CAN_ERR_NOT_SUPPORTED 
#endif
#if CAN_CFG_FUNC_STATUS	== 1
/*
  @func CAN driver status function,
  return the present driver configuration parameters and statistics information. 
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - CAN_STAT_INF.CAN_Mode will specify the operating mode of the Node.
  @flag: (DESIGN)  | - CAN_STAT_INF.CAN_Node_status will specify the current status of the Node.        
  @flag: (DESIGN)  | - CAN_STAT_INF.CAN_node_error will specify the current error counts of the Node.
  @flag: (DESIGN)  | - If queuing facility is enabled, the Node_Pend_Reads, and Node_Pend_Writes will 
						tell the status of the pending read and writes for the Node. 

  @flag: (DESIGN)  | - CAN_STAT_INF.CAN_tx_fifo_lev will specify how many data frames are currently stored
						in the transmit FIFO.
  @flag: (DESIGN)  | -  CAN_STAT_INF.CAN_rx_fifo_lev will specify how many data frames are currently
						stored in the receive FIFO.
  @flag: (DESIGN)  | - The frame counters will be reset to 0 after the CAN_status_dev API has been called.  
  @retval  CAN status
  @flag CAN_SUCCESS | Status of device success fully read and returned to application.
*/
CAN_STATUS	CAN_Status_dev
(	
   CAN_DEVICE can_device,				/*@parm CAN node hardware module identification number.*/
   CAN_STATUS_INF*	can_status_inf		/*@parm Users provide data structure to write the current status of the device. */
);
#else
#define CAN_Status_dev (__CAN_PARM1) CAN_ERR_NOT_SUPPORTED 
#endif

#if CAN_CFG_FUNC_CONTROL == 1
/*
  @func CAN driver runtime configuration control function,
  CAN_control_dev may be used as a single entry point for all the control functions. The user would 
  call the desired control function and provide new configuration parameters through CAN_CTRL_CODE and
  CAN_ctrl_arg parameters respectively.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Call control function specified by the can_ctrl_code. The can_ctrl_code is one of the enumeration 
                      constants from CAN_CTRL_CODE to specify the operation to perform.
  @flag: (DESIGN) | - Typecast the CAN_ctrl_arg parameter with respect to the called function. 
  @retval  CAN status
  @flag CAN_SUCCESS | Setting the new configuration parameters is success.
  @flag CAN_ERR     | The provided CAN_ctrl_code does not match with any of the values defined in CAN_CTRL_CODE.
*/
CAN_STATUS	CAN_Control_dev	
( 
	CAN_DEVICE can_device,			/*@parm CAN node hardware module identification number.*/
	CAN_CTRL_CODE can_ctrl_code,	/*@parm CAN control Code to specify the operation to perform.*/	
	void* CAN_ctrl_args				/*@parm New configuration parameters, may not be required by all Control codes.*/
) ;
#else
#define CAN_Control_dev	 (__CAN_PARM1) CAN_ERR_NOT_SUPPORTED 
#endif

#if CAN_CFG_FUNC_READ == 1
/*
  @func CAN driver read function,
  Received data will be copied to application provided data buffer when s/w LLD 
  receive buffer has any h/w message objects which contain received information.
  If no h/w message objects associated with s/w LLD receive buffer add it to the
  penidng read request queue provided it is configured (CAN_CFG_REQUEST_QUEUE_RD > 0)
  by application in CAN_CFG.H file.

  Note:

  Only one frame can be read per request.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check number of receive message objects in s/w LLD receive buffer.
  @flag: (DESIGN)  | - If number of message objects associated with s/w read buffer
                       greater than zero.
  @flag: (DESIGN)  | - Get teh h/w message object number which has the received frame data.
  @flag: (DESIGN)  | - Copy the data to application provided data buffer by calling
                       'CAN_vGetMsgObj' API.
  @flag: (DESIGN)  | - Call the callback function associated with read request.
  @flag: (DESIGN)  | - Set MSGVAL bit of h/w message object.
  @flag: (DESIGN)  | - Return Success .
  @flag: (DESIGN)  | - Else (no message objects associated with s/w LLD read buffer).
  @flag: (DESIGN)  | - Check receive transfer queues are enabled and callback function
                       provided with the request.
  @flag: (DESIGN)  | - If queus are enabled and current number of pending requests in queue is
                       less than queue depth.
  @flag: (DESIGN)  | - Add current read request to the tail end of queue and increase the number
                       of pending read requests.
  @flag: (DESIGN)  | - Else return error.
  @retval  CAN status
  @flag CAN_SUCCESS | Suuccessfully read data or add it to pending read request queue.
  @flag CAN_ERR_RES | The number of pending requests crosses the user configured CAN_CFG_REQUEST_QUEUE_RD level or
                      user callback function not provided with request.
  @flag CAN_ERR_NOT_SUPPORTED_HW | Pending read queues are not configured and s/w LLD receive buffer contain no
                                   received h/w message objects.                      
*/
CAN_STATUS CAN_Read_Dev(
                      CAN_DEVICE can_device, /*@parm CAN node hardware module identification number*/
                      CAN_TRANSFER* can_transfer /*@parm Read request to read receive message frames

                      	           can_transfer->CAN_trans_ucb == NULL --> blocked read request

                                   can_transfer->CAN_trans_ucb <> NULL --> unblocked read request 
                         */
                      );
#else
#define CAN_Read_Dev(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif
#if CAN_CFG_FUNC_WRITE == 1
/*
  @func CAN driver write function,
  Transmit data will be copied to free transmit h/w message object when number of 
  free transmit h/w message objects value greater than zero. Call user callback 
  function provided along with teh request.

  If no free transmit h/w message objects aavailable add request to the
  penidng write request queue provided it is configured (CAN_CFG_REQUEST_QUEUE_WR > 0)
  by application in CAN_CFG.H file.

  Note:

  Only one frame can be read per request.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check the number of free transmit h/w message objects.
  @flag: (DESIGN)  | - If number of free transmit message objects greater than zero value.
  @flag: (DESIGN)  | - Check the number of transmit h/w message object number.
  @flag: (DESIGN)  | - Configure the transmit h/w message object with the application 
                       provided data by calling 'CAN_vConfigMsgObj' API.
  @flag: (DESIGN)  | - Enable transmit eanble bit.
  @flag: (DESIGN)  | - Set TXRQ bit of h/w message object incase FIFOs are not configured.
  @flag: (DESIGN)  | - Decrease the number of free h/w transmit meesage objects.
  @flag: (DESIGN)  | - Call teh user callback function associated with request.
  @flag: (DESIGN)  | - Else (no free h/w transmit message objects)
  @flag: (DESIGN)  | - Check transmit transfer queues are enabled and callback function
                       provided with the request.
  @flag: (DESIGN)  | - If queus are enabled and current number of pending requests in queue is
                       less than queue depth.
  @flag: (DESIGN)  | - Add current request to the tail end of transmit queue and increase the number
                       of pending write requests.
  @flag: (DESIGN)  | - Else return error.

  @retval  CAN status
  @flag CAN_SUCCESS | Successfully data written to h/w message objects or added to queue.
  @flag CAN_ERR_RES | The number of pending requests crosses the user configured CAN_CFG_REQUEST_QUEUE_WR level or
                      callback function not provided with application.
  @flag CAN_ERR_NOT_SUPPORTED_HW | Queues are not configured by application.                      
*/
CAN_STATUS CAN_Write_Dev(
       CAN_DEVICE can_device,  /*@parm CAN node hardware module identification number*/
       CAN_TRANSFER* can_transfer /*@parm write request configuration parameters to send CAN frames.
       
                                    can_transfer->can_trans_ucb == NULL --> blocked write request.
                                     
                                    can_transfer->can_trans_ucb <> NULL --> unblocked write request.
                                     
       */
       );
#else
#define CAN_Write_Dev(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif




#if CAN_CFG_FUNC_CTRL_TRNS_NODE_ACT == 1
/*
  @func CAN driver runtime node activate function,
  CAN_Ctrl_trns_node_act is used to activacte or disable the chosen node at runtime.

  If argument value >  0 (zero) --> terminates the participation of this node in the CAN traffic. 
  
               Value == 0 (Zero) --> enables the participation of the node in the CAN traffic.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check if node is busy.
  @flag: (DESIGN)  | - Activate / disable the node .
  @retval  CAN status
  @flag CAN_SUCCESS | Operation successfully completed.
  @flag CAN_ERR_NOT_SUPPORTED_HW | The requested node does not exist.
  @flag CAN_ERR_NOT_SUPPORTED | Not able to support the function.
*/
CAN_STATUS CAN_Ctrl_trns_node_act( 
	  CAN_DEVICE can_device,	/*@parm CAN hardware identification.*/
	  IFX_UINT32 *CAN_ctrl_args		/*@parm Configuration parameters*/
								  ) ;
#else
#define CAN_Ctrl_trns_node_act(__CAN_PARM1 ) CAN_ERR_NOT_SUPPORTED 
#endif

#if CAN_CFG_FUNC_CTRL_NODE_EWRN_LVL == 1 
/*
  @func CAN driver runtime error warning level configuration control function,
  this function is used to change the error warning level of the chosen Node.
  Receive and transmit counters are not effected.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Set the application requested level by calling the API.
  @retval  CAN status
  @flag CAN_SUCCESS | Level set successfully.
  @flag CAN_ERR_NOT_SUPPORTED_HW | The requested level crosses the hard ware supported limits.
  @flag CAN_ERR_NOT_SUPPORTED | Function not supported
*/
CAN_STATUS CAN_Ctrl_Node_Error_Warn_Level(	
	CAN_DEVICE can_device,	/*@parm CAN hardware identification.*/
	IFX_UINT32 *CAN_ctrl_args		/*@parm Configuration parameters*/
) ;
#else
#define CAN_Ctrl_Node_Error_Warn_Level(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif


#if CAN_CFG_FUNC_CTRL_TRNS_BIT == 1 
/*
  @func CAN driver runtime bit timing configuration control function,
  CAN_Ctrl_trns_bit used to change the bit timings for the chosen device mainly to
  change the baud rate. For more details please refer to NBTR structure definition
  section.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Disable the Node.
  @flag: (DESIGN)  | - Set the application requested bit timing by calling the API.
  @flag: (DESIGN)  | - Enable the Node.
  @retval  CAN status
  @flag CAN_SUCCESS | Setting the timing segment of device is success.
  @flag CAN_ERR_NOT_SUPPORTED_HW | The requested settings exceed the Hardware limits.
  @flag CAN_ERR_NOT_SUPPORTED | Function not supported.
*/
CAN_STATUS CAN_Ctrl_trns_bit(	
	CAN_DEVICE can_device,	  /*@parm CAN hardware identification.*/
	NBTR       *CAN_ctrl_args /*@parm Baud rate configuration parameters*/
) ;
#else
#define CAN_Ctrl_trns_bit(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif


#if CAN_CFG_FUNC_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE == 1
/*
  @func CAN driver runtime frame counter value control function,
  CAN_Ctrl_Node_Frame_Count_Counter_Value is used to set the frame count counter value 
  for the chosen node and reamaining fields are not effected. 

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Set the application requested value by calling API.
  @retval  CAN status
  @flag CAN_SUCCESS | Operation completed successfully.
  @flag CAN_ERR_NOT_SUPPORTED_HW | The requested value exceeds the hard ware supported limits.
  @flag CAN_ERR_NOT_SUPPORTED | Function not supported.
*/
CAN_STATUS CAN_Ctrl_Node_Frame_Count_Counter_Value(	
	CAN_DEVICE can_device,	   /*@parm CAN hardware identification.*/
	IFX_UINT32 *CAN_ctrl_args  /*@parm Configuration parameters*/
) ;
#else
#define CAN_Ctrl_Node_Frame_Count_Counter_Value(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif


#if CAN_CFG_FUNC_CTRL_CREATE_GATEWAY == 1
/*
  @func CAN driver runtime gateway configuration control function,
  CAN_Ctrl_trns_gateway may be used during runtime to create a gateway
  between two CAN nodes. 

  CAN_ctrl_args->MoNum      --> refers to gateway source object.

  CAN_ctrl_args->Mofgpr.CUR --> refers to gateway destination object.

  CAN_ctrl_args->Mofgpr.Data_Copy --> data copied from source to destination object.

  CAN_ctrl_args->Mofgpr.Data_Frame_Send --> set TXRQ in destination object.

  CAN_ctrl_args->Mofgpr.DLC_Copy --> number of data bytes copied to destination object.

  CAN_ctrl_args->Mofgpr.ID_Copy --> message object ID copy to destination object.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - create gateway .
  
  @retval  CAN status
  @flag CAN_SUCCESS | Operation completed successfully.
  @flag CAN_ERR_NOT_SUPPORTED_HW | No receive fifo configured for this device
  @flag CAN_ERR_NOT_SUPPORTED | Function not supported.
*/
CAN_STATUS	CAN_Ctrl_trns_gateway
(	
	CAN_DEVICE can_device,	/*@parm CAN hardware identification.*/
	CAN_MESSAGE_OBJECT *CAN_ctrl_args		/*@parm Configuration parameters*/
) ;
#else
#define CAN_Ctrl_trns_gateway(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif						
												
#if CAN_CFG_FUNC_CTRL_ENABLE == 1
/*
  @func CAN driver runtime Peripheral enable/Disable function,
  CAN_Ctrl_enable may be used to enable a CAN peripheral and any IO pins required
  will be set to node Tx/Rx as required, or may be relinquished to system if peripheral is disabled. 

  If argument value 1 --> do not request to disable clock to CAN module.

              value 0 --> request to disable clock to CAN module.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check if all nodes are idle  .
  @flag: (DESIGN)  | - Enable/Disable the Peripheral .
  @retval  CAN status
  @flag CAN_SUCCESS | Operation completed successfully.
  @flag CAN_ERR_NOT_SUPPORTED | Function not supported.
*/
CAN_STATUS	CAN_Ctrl_enable(	
	IFX_UINT32 *CAN_ctrl_args		/*@parm Configuration parameters*/
) ;
#else
#define CAN_Ctrl_enable(__CAN_PARM1, __CAN_PARM2) CAN_ERR_NOT_SUPPORTED 
#endif	

/*
  @func CAN_Ctrl_config_Rcvbuffer will be used to program the hardware message objects with
  user provided message frames data which include the following information for both
  transmit as well as receive data.

  1. Accept standard/extended identifier message frames.

  2. Message ID and message mask 

  3. If the message frame to be sent then fill the data with user provided data.

     3a. Set the new data, Tx enable fields.

	 3b. Set MSGVAL field.

  4. If the message object to be configured for receive

     4a. Clear data fiels.

	 4b. Reset new data field.

	 4c. Set MSGVAL field.
*/
CAN_STATUS CAN_Ctrl_config_Rcvbuffer (
    CAN_DEVICE can_device, /*@parm CAN node hardware module identification number*/
    CAN_TRANSFER* can_transfer /*@parm Configuration parameters for hardware message object*/
    );

/*
  CAN_node_status will return the protocol related errors of type

  a. CAN_SUCCESS --> When no error has occured.

  b. Bus off error

  c. Stuff error

  d. Acknowledge, CRC, BIT0 and BIT1 errors.
*/
CAN_STATUS CAN_node_status(CAN_DEVICE can_device) ;


extern IFX_UINT8   CAN_NUM_TFREE_MSOBJ[];
extern IFX_VUINT8  MsgRcvd_num_obj[];

#endif /*__CAN_API_H*/

