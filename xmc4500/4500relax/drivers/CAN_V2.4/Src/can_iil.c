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
** @FILENAME@:       CAN_IIL.c
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: Provides the API which are directly availble to the user 
**           application and the APIs which are internally used by exported
**           APIs.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      S.A.Kazmi          Release after code review.
** 07/05/2004      Mahesh             CAN_control_dev is improved to support 
**                                    RT Linux.
** 02/06/2004      Mahesh             CAN_Init_Node API changed to support 
**                                    full gateway functionality.
** 08/06/2004	   Mahesh             CAN_Init_Node API has changed according to
**                                    'Ursula kelling' inputs. 
** 21/06/2004      Mahesh             More comments added to code.  
**
** @CHANGE_HISTORY@
** =============================================================================
*/	
#include "compiler.h"
#include "common.h"
#include "can_cfg.h"
#include "can_idl.h"
#include "can_iil.h"
#include "can_api.h"	 
#include "sys_api.h"
#include "sys_cfg.h"


/*
The following pre-proccessor directives check if the system HAL matches the 
implemententation dependent layer for the SSC HAL. If these do not match
then the compilation is stopped with an error to indicate this conflict to 
the user.
This check has been introduced because the IDL file names are identical, 
regardless of the product they are written for, this could easily result 
in the wrong files being used.
*/
#if SYS_PRODUCT != CAN_PRODUCT
#error CAN HAL Error: Either CAN_IDL.h file is incorrect or else\
the wrong System HAL is being used.
#endif


/*
Check that the IDL layer is usable:
*/
#if (CAN_API_VER_MAJ > 0)
#error CAN HAL Error: Incompatible components, please make
  sure you have the latest CAN HAL distribution.
#endif

/*
  The maximum number of allowed message objects by hardware is 128. If the 
  user configured message objects more than 128 thrn return compile time error.
*/
#if ((CAN_CFG_TX_BUFFER_SIZE_NODE_0 + CAN_CFG_TX_BUFFER_SIZE_NODE_1 +\
      CAN_CFG_TX_BUFFER_SIZE_NODE_2 + CAN_CFG_TX_BUFFER_SIZE_NODE_3 +\
      CAN_CFG_RX_BUFFER_SIZE_NODE_0 + CAN_CFG_RX_BUFFER_SIZE_NODE_1 +\
      CAN_CFG_RX_BUFFER_SIZE_NODE_2 + CAN_CFG_RX_BUFFER_SIZE_NODE_3) > CAN_HW_MAX_MSGOBJS)
#error CAN HAL Error: Configured TX and RX buffers should be less than\
       CAN_HW_MAX_MSGOBJS   
#endif


void (*CAN_rcv_ucb[CAN_HW_NUM])(void);

/*
  Initialise the number of receive message objects allocated for each 
  can node by application.
*/
IFX_UINT8 CAN_CFG_RXBUFF_SZ[CAN_HW_NUM] = {CAN_CFG_RX_BUFFER_SIZE_NODE_0, 
  CAN_CFG_RX_BUFFER_SIZE_NODE_1, CAN_CFG_RX_BUFFER_SIZE_NODE_2,
  CAN_CFG_RX_BUFFER_SIZE_NODE_3};

/*
  Initialise the number of transmit message objects allocated for each 
  can node by application.
*/
IFX_UINT8 CAN_CFG_TXBUFF_SZ[CAN_HW_NUM] = {CAN_CFG_TX_BUFFER_SIZE_NODE_0, 
  CAN_CFG_TX_BUFFER_SIZE_NODE_1, CAN_CFG_TX_BUFFER_SIZE_NODE_2,
  CAN_CFG_TX_BUFFER_SIZE_NODE_3};

/*
  Return the number of transmit message objects allocated for the corresponding node 
  by application.
*/
#define CAN_TX_Buffer_size(X) CAN_CFG_TXBUFF_SZ[X]

/*
  Return the number of receive message objects allocated for the corresponding node 
  by application.
*/
#define CAN_RX_Buffer_size(X) CAN_CFG_RXBUFF_SZ[X]

/*Initialise all CAN nodes base address*/
CAN_HW_TABLE;

#define TRANSMIT_LOCATION 0 
#define RECEIVE_LOCATION 1

/*
  Used to store the base h/w message object assigned to each node 
  for both TX and RX
*/
IFX_UINT8   FIFOBASEOBJECTS[MAX_NODES][2];

IFX_UINT8   CAN_TFREE_MSOBJ_FLG[CAN_HW_MAX_MSGOBJS];
IFX_UINT8   CAN_NUM_TFREE_MSOBJ[MAX_NODES];

#if CAN_CFG_REQUEST_QUEUE_WR > 0
/*
  List to maintain the pending write requests.
*/
CAN_TRANSFER   *CAN_writeq[ MAX_NODES ][ CAN_CFG_REQUEST_QUEUE_WR ];

/*
  Head pointer to pending write request lsit(used in CAN_ISR_MOBJ).
*/
IFX_UINT8    CAN_writeq_head[ MAX_NODES ];

/*
  Tail pointer to pending write request lsit (used in CAN_write_Dev API).
*/
IFX_STUINT8    CAN_writeq_tail[ MAX_NODES ];

/*
  The number of pending write requests.
*/
IFX_VUINT8  CAN_pending_writes[ MAX_NODES ]; 
#endif

#if CAN_CFG_REQUEST_QUEUE_RD > 0
/*
  The number of pending read requests.
*/
IFX_VUINT8   CAN_pending_reads[ MAX_NODES ];
/*
  Tail pointer to pending write request lsit (used in CAN_read_Dev API).
*/
IFX_UINT8    CAN_readq_tail[ MAX_NODES ];
/*
  Head pointer to pending read request lsit(used in CAN_ISR_MOBJ).
*/
IFX_UINT8    CAN_readq_head[ MAX_NODES ];
/*
  List to maintain the pending read requests.
*/
CAN_TRANSFER *CAN_readq[ MAX_NODES ][ CAN_CFG_REQUEST_QUEUE_RD ];
#endif

/*Stores the CAN clock frequency*/
IFX_UINT32 CAN_clc_freeq = 0; 


/*To store the recent occurred interrupt*/
CAN_STATUS can_node_error[MAX_NODES] ;

/*
  This falg is used to check whether CAN module is initialised or not.
  If any node is initailised and the value of CLC_ALREADYSET is zero then 
  module configuration parameters are initialised like clock and the value
  is set to 1.
*/
IFX_UINT8 	CLC_ALREADYSET = 0 ;

/*
  To store the number of message object ID which just received data
  and ready to serve the following read requests.
*/
IFX_VUINT8  MsgRcvd[MAX_NODES][CAN_HW_MAX_MSGOBJS] ;

/*
  Index to MsgRcvd, to store the upcoming message object which receive data
*/
IFX_UINT8   MsgRcvd_rdptr[MAX_NODES];
IFX_UINT8   MsgRcvd_wrptr[MAX_NODES];
IFX_VUINT8  MsgRcvd_num_obj[MAX_NODES];

#if CAN_CFG_TX_FIFO_ENBL > 0
/*
  This define used to index the transmit FIFO to store the frame
  received from application.
*/
IFX_UINT8 CAN_tfifo_curr_index[MAX_NODES];
#endif

/* 
Define initialised flags and flag management macros if 
initialisation checking is to be done.
If initialisation checking is not to be performed then
define the macros to do nothing.
*/
#if CAN_CFG_INIT_CHK == 1
  IFX_UINT8 CAN_initialised_flags [MAX_NODES] = {0x00, 0x00, 0x00, 0x00};
#endif  /* CAN_CFG_INIT_CHK == 1 */



/*
  Initialises the internal data structures of the HAL related to the device
  selected by CAN_device, allocates any required system resources and 
  configures the peripheral according to the CAN_COM_PARMS structure. 
  The CAN_COM_PARMS structure must be initialised by the user before calling 
  CAN_initialise_dev. 
*/
CAN_STATUS  CAN_Initialise_dev		( CAN_DEVICE can_device,  CAN_COM_PARMS* can_init_parms ) 
{

   #if CAN_CFG_INIT_CHK == 1
   if(CAN_initialised_flags [can_device] == 1)
   {
     return CAN_ERR;
   }
   #endif

	/*Sanity check before proceeding*/	
	if( (can_device > MAX_NODES) || (!can_init_parms) )
	{
		return CAN_ERR_NOT_SUPPORTED_HW;	
	}

#if CAN_CFG_REQUEST_QUEUE_RD > 0
	CAN_pending_reads[ can_device ] = 0 ;
	
	CAN_readq_head[ can_device ]= 0 ;
	CAN_readq_tail[ can_device ] = 0 ;
#endif 

#if	CAN_CFG_REQUEST_QUEUE_WR > 0
	CAN_pending_writes[ can_device ] = 0 ;
	
	CAN_writeq_head[ can_device ] = 0 ;
	CAN_writeq_tail[ can_device ] = 0 ;
#endif

    MsgRcvd_rdptr[can_device]   = 0;
    MsgRcvd_wrptr[can_device]	= 0;
    MsgRcvd_num_obj[can_device]	= 0;

    /*Call implementation dependant node initialisation routine*/
	if (CAN_Init_Node( can_device, can_init_parms) == CAN_SUCCESS )
	{
        #if CAN_CFG_INIT_CHK == 1
        CAN_initialised_flags [can_device] = 1;
		#endif

        /*The node in active state*/  
		can_node_error[can_device] = CAN_ERR_NET_STATE_ACT ;

		return CAN_SUCCESS;
	 }
    
	return CAN_ERR;
}



#if CAN_CFG_FUNC_TERMINATE == 1
/*
  Sets the peripheral, selected by the CAN_device parameter, into a disabled
  state and frees any system resources previously allocated in CAN_initialise.
  After this function has been called CAN_initialise_dev must be called 
  successfully before any of the other API functions are used.
*/
CAN_STATUS CAN_Terminate_dev	( CAN_DEVICE can_device  ) 
{
	IFX_UINT8 msg_obj_num ;

# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

    /*Release all transmitted message objects by clearing MSGVAL bit and data bytes*/
	for( msg_obj_num = FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION] ; msg_obj_num < CAN_TX_Buffer_size(can_device) ; msg_obj_num++ )
	{
		CAN_DelMsgObj(msg_obj_num);
	}					 	

    /*Release all received message objects by clearing MSGVAL bit*/
	for( msg_obj_num = FIFOBASEOBJECTS[can_device][RECEIVE_LOCATION] ; msg_obj_num < CAN_RX_Buffer_size(can_device) ; msg_obj_num++ )
	{
		CAN_DelMsgObj(msg_obj_num);
	}					 	

    /*Disable specific node*/
 	CAN_Disable_Node(can_device);

#if CAN_CFG_REQUEST_QUEUE_RD > 0
	CAN_pending_reads[ can_device ] = 0 ;
	
	CAN_readq_head[ can_device ]= 0 ;
	CAN_readq_tail[ can_device ] = 0 ;
#endif 

#if	CAN_CFG_REQUEST_QUEUE_WR > 0
	CAN_pending_writes[ can_device ] = 0 ;
	
	CAN_writeq_head[ can_device ] = 0 ;
	CAN_writeq_tail[ can_device ] = 0 ;
#endif

# if CAN_CFG_INIT_CHK == 1
  CAN_initialised_flags [can_device] = 0;
# endif

	return CAN_SUCCESS ;
}
#endif /*CAN_CFG_FUNC_TERMINATE*/


#if CAN_CFG_FUNC_ABORT == 1
/*
  Cancels all currently queued data transfers and stops any transfers currently
  being processed on the peripheral module selected by CAN_device. 
  CAN_initialise_dev need not be called after this function before the other 
  API functions can be used, this function merely clears all current and 
  pending transfers it does not terminate the HAL. New transfers may be 
  requested using CAN_read_Dev and/or CAN_write_Dev immediately after this 
  function returns. All aborted transfers will return a CAN_ERR error code.
  This function may be used to clear all requests before changing modes etc.  
*/
CAN_STATUS	CAN_Abort	( CAN_DEVICE can_device ) 
{
	IFX_UINT8 pend_req = 0;

# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

#if CAN_CFG_REQUEST_QUEUE_RD > 0
	/*If there are any pending read requests, notify the user with CAN_ERR status*/
	CAN_pending_reads[ can_device ] = 0 ;
	for(pend_req = 0; pend_req < CAN_pending_reads[ can_device ] ; pend_req++)
	{
		CAN_readq[ can_device ][ CAN_readq_head[ can_device ] ]->CAN_trans_ucb(CAN_readq[ can_device ][ CAN_readq_head[ can_device ] ], CAN_ERR) ;
    } 		

    /*Reset all read queue global variables*/
	CAN_readq_head[ can_device ]= 0 ;
	CAN_readq_tail[ can_device ] = 0 ;
	CAN_pending_reads[ can_device ] = 0 ;
#endif 

#if	CAN_CFG_REQUEST_QUEUE_WR > 0
	/*If there are any pending write requests, notify the user with CAN_ERR status*/
	for(pend_req = 0 ; pend_req < CAN_pending_writes[ can_device ] ; pend_req++)
	{
		CAN_writeq[ can_device ][ CAN_writeq_head[ can_device ] ]->CAN_trans_ucb( (struct can_trans*)CAN_writeq[ can_device ][ CAN_writeq_head[ can_device ] ], CAN_ERR) ;
    }		

    /*Reset all write queue global variables*/
	CAN_pending_writes[ can_device ] = 0 ;
	CAN_writeq_head[ can_device ] = 0 ;
	CAN_writeq_tail[ can_device ] = 0 ;
#endif
  return CAN_SUCCESS;
}
#endif /*CAN_CFG_FUNC_ABORT*/

#if CAN_CFG_FUNC_CONTROL == 1
/*
  Used as a single entry point for all the control functions. The user would 
  call the desired control function and provide new configuration parameters
  through CAN_CTRL_CODE and CAN_ctrl_arg parameters respectively.
*/
CAN_STATUS CAN_Control_dev	( CAN_DEVICE can_device, CAN_CTRL_CODE can_ctrl_code, void* CAN_ctrl_args ) 
{
   CAN_STATUS	ret = CAN_SUCCESS ;
   IFX_UINT32   CAN_val = 0;

# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

   if((can_ctrl_code != CAN_CTRL_UNREG_RCV_UCB) && 
      (can_ctrl_code != CAN_CTRL_DISABLE) && 
      (can_ctrl_code != CAN_CTRL_ENABLE) )
   {
     if(CAN_ctrl_args == NULL)
     {
       return CAN_ERR;
     }
   }

	switch	(can_ctrl_code)
	{

#if CAN_CFG_FUNC_CTRL_ENABLE == 1
        /*Disable CAN module*/
		case CAN_CTRL_DISABLE:
		{
			CAN_val = 0 ;
			ret = CAN_Ctrl_enable( (IFX_UINT32 *)&CAN_val );
		}	
		break;
#endif
#if CAN_CFG_FUNC_CTRL_ENABLE == 1
        /*Enable CAN module*/
		case CAN_CTRL_ENABLE:
		{
		    CAN_val = 1 ;
			ret = CAN_Ctrl_enable( (IFX_UINT32 *)&CAN_val );
		}	
		break;
#endif

#if CAN_CFG_FUNC_CTRL_TRNS_NODE_ACT == 1
        /*Activacte or disable the chosen node at runtime.*/
		case CAN_CTRL_TRNS_NODE_ACT:
		{
			ret = CAN_Ctrl_trns_node_act(can_device, (IFX_UINT32 *)CAN_ctrl_args);
		}
		break;	
#endif
#if CAN_CFG_FUNC_CTRL_NODE_EWRN_LVL == 1 
        /*Set error warning level for CAN node*/
		case CAN_CTRL_TRNS_NODE_EWRN_LVL:
		{
			ret =CAN_Ctrl_Node_Error_Warn_Level(can_device, (IFX_UINT32 *)CAN_ctrl_args);
		}
		break;
#endif
#if CAN_CFG_FUNC_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE == 1
        /*used to set the frame count counter value for the chosen device.*/ 
		case CAN_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE:
		{
			ret =CAN_Ctrl_Node_Frame_Count_Counter_Value(can_device, (IFX_UINT32 *)CAN_ctrl_args);
		}
		break;
#endif
#if CAN_CFG_FUNC_CTRL_CREATE_GATEWAY == 1
        /*used during runtime to create a gateway between two CAN nodes.*/
		case CAN_CTRL_TRNS_GATEWAY:
		{
			ret = CAN_Ctrl_trns_gateway(can_device, (CAN_MESSAGE_OBJECT *)CAN_ctrl_args);
		}	
		break;		
#endif
#if CAN_CFG_FUNC_CTRL_TRNS_BIT == 1
		/*Used to change the bit timings for the chosen device.*/
		case CAN_CTRL_TRNS_BIT:
		{
			ret = CAN_Ctrl_trns_bit(can_device, (NBTR *)CAN_ctrl_args);
		}
		break;
#endif
        /*Configure h/w receive buffers*/
        case CAN_CTRL_CFG_RXBUFF:
        {
		  ret = CAN_Ctrl_config_Rcvbuffer(can_device, (CAN_TRANSFER *)CAN_ctrl_args);
        }
        break;

        case CAN_CTRL_REG_RCV_UCB:
		  CAN_rcv_ucb[can_device] = CAN_ctrl_args; 
		  break;

        case CAN_CTRL_UNREG_RCV_UCB:
		  CAN_rcv_ucb[can_device] = NULL; 
		  break;

	default:
	  {
		ret = CAN_ERR;
		break;
	  }
	}
	return ret;
}
#endif /*CAN_CFG_FUNC_CONTROL*/

#if CAN_CFG_FUNC_STATUS == 1
/*
 Return the present driver configuration parameters and statistics information. 
*/
CAN_STATUS	CAN_Status_dev(	CAN_DEVICE can_device, CAN_STATUS_INF  *can_status_inf )
{
# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

   if(can_status_inf == NULL)
   {
     return CAN_ERR;
   }

    /*Copy the node status from Node status register about transmission, reception, 
      protocol errors and warnings*/
	*(IFX_UINT32*)(&can_status_inf->CAN_node_status)=	CAN_NODE(can_device)->CAN_NSR	 ;
    /*Copy and return all error counters*/
	*(IFX_UINT32*)(&can_status_inf->CAN_node_error)	=	CAN_NODE(can_device)->CAN_NECNT  ;
	*(IFX_UINT32*)(&can_status_inf->CAN_node_status)	
		|=	((CAN_NODE(can_device)->CAN_NFCR   & 0x0000FFFF)<< 16) ;	

	/*Last error occured status*/
	can_status_inf->CAN_Last_Errcode = CAN_node_status(can_device);
    can_node_error[can_device] = CAN_ERR_RX_OK;

	return CAN_SUCCESS ;
}
#endif /*CAN_CFG_FUNC_STATUS*/

/*
  Sets the interrupt priority and enable the indivadual interrupts.
*/
void CAN_ISR_INIT(void)
{
    #if (IFX_COMPILER_GNU == 1)
    CAN_HW_register_isr ();
    #endif

    /*
	  Service request control register 
	  0 -- Transfer interrupt for all 4 nodes

	  1 -- Receive  message object interrupt for node 0
	  2 -- Receive  message object interrupt for node 1
	  3 -- Receive  message object interrupt for node 2
	  4 -- Receive  message object interrupt for node 3

	  5 -- Transmit message object interrupt for node 0
	  6 -- Transmit message object interrupt for node 0
	  7 -- Transmit message object interrupt for node 0
	  8 -- Transmit message object interrupt for node 0

	  9  -- Alert anf CFC interrupts for all 4 nodes
	  10 -- LEC interrupt for all 4 nodes
    */


	CAN_HW_SRC0	=	( (IFX_UINT32) SYS_CAN_SRN0 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;	
	CAN_HW_SRC1	=	( (IFX_UINT32) SYS_CAN_SRN1 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC2	=	( (IFX_UINT32) SYS_CAN_SRN2 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC3	=	( (IFX_UINT32) SYS_CAN_SRN3 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC4	=	( (IFX_UINT32) SYS_CAN_SRN4 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC5	=	( (IFX_UINT32) SYS_CAN_SRN5 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC6	=	( (IFX_UINT32) SYS_CAN_SRN6 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC7	=	( (IFX_UINT32) SYS_CAN_SRN7 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC8	=	( (IFX_UINT32) SYS_CAN_SRN8 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC9	=	( (IFX_UINT32) SYS_CAN_SRN9 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
	CAN_HW_SRC10	=	( (IFX_UINT32) SYS_CAN_SRN10 ) | 
					( ( (IFX_UINT32) 1 ) << SRCN_SRE_LOCATION ) ;
}

#if CAN_CFG_FUNC_READ == 1
/*
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Check number of receive message objects in s/w LLD receive buffer.
  @flag: (DESIGN)  | - If number of message objects associated with s/w read buffer
                       greater than zero.
  @flag: (DESIGN)  | - Get teh h/w message object number which has the received frame data.
  @flag: (DESIGN)  | - Copy the data to application provided data buffer by calling
                       'CAN_vGetMsgObj' API.
  @flag: (DESIGN)  | - Call the callback function associated with read request.
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
  @flag CAN_READ_DATA | Successfully read the received frame data from h/w message buffer
                        to application data buffer.
  @flag CAN_SUCCESS | Request added to pending read request queue.
  @flag CAN_ERR_RES | The number of pending requests crosses the user configured CAN_CFG_REQUEST_QUEUE_RD level or
                      user callback function not provided with request.
*/
CAN_STATUS CAN_Read_Dev(CAN_DEVICE can_device, CAN_TRANSFER* can_transfer)
{
  IFX_UINT8 mobj = 0;

  if(MsgRcvd_num_obj[can_device] > 0)
  {
    mobj = MsgRcvd[can_device][MsgRcvd_rdptr[can_device]];
    MsgRcvd_rdptr[can_device]++;
    if(MsgRcvd_rdptr[can_device] >= CAN_HW_MAX_MSGOBJS)
    {
      MsgRcvd_rdptr[can_device] = 0;
    } 
    CAN_vGetMsgObj(mobj, can_transfer->can_buffer);
    if(can_transfer->CAN_trans_ucb != NULL)
    {
	  can_transfer->CAN_trans_ucb(can_transfer, CAN_SUCCESS);
    } 
    CAN_MSGOBJ[mobj].MOCTR = (CAN_MOCTRX_RXPND | CAN_MOCTRX_NEWDAT | 0x00200000);
    MsgRcvd_num_obj[can_device]--;
    return CAN_READ_DATA;
  }

  #if CAN_CFG_REQUEST_QUEUE_RD > 0
  if( (CAN_pending_reads[can_device] < CAN_CFG_REQUEST_QUEUE_RD ) && 
      (can_transfer->CAN_trans_ucb != NULL)
	)
  {
    CAN_readq[ can_device ][ CAN_readq_tail[ can_device ] ] = can_transfer; 
    CAN_pending_reads[ can_device ] = CAN_pending_reads[ can_device ] + 1;
    CAN_readq_tail[ can_device ]++;
    if(CAN_readq_tail[ can_device ] >= CAN_CFG_REQUEST_QUEUE_RD)
    {
      CAN_readq_tail[ can_device ] = 0;
    } 
    return CAN_SUCCESS; 
  }
  else
  {
   return CAN_ERR_RES;
  } 
  #else
  return CAN_ERR_RES;
  #endif /*CAN_CFG_REQUEST_QUEUE_RD*/

}/*CAN_Read_Dev*/


#endif /*CAN_CFG_FUNC_READ*/

#if CAN_CFG_FUNC_WRITE == 1
/*
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
  @flag CAN_WRITE_DATA | Successfully copied the application provided frame data to h/w message objects.
  @flag CAN_SUCCESS | Added the write request to pending write request queue.
  @flag CAN_ERR_RES | The number of pending requests crosses the user configured CAN_CFG_REQUEST_QUEUE_WR level or
                      callback function not provided with application.
*/
CAN_STATUS CAN_Write_Dev(CAN_DEVICE can_device, CAN_TRANSFER* can_transfer)
{
  IFX_UINT8 start_msg_obj = 0, last_msg_obj = 0, flag = 0, nloop = 0;

  if(CAN_NUM_TFREE_MSOBJ[can_device] > 0)
  {
    #if CAN_CFG_TX_FIFO_ENBL > 0
    /*Disable local interrupts*/
    start_msg_obj = CAN_tfifo_curr_index[can_device];
    CAN_tfifo_curr_index[can_device]++;
    if(CAN_tfifo_curr_index[can_device] >= 
      (FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION] + CAN_TX_Buffer_size(can_device)) )
    {
        CAN_tfifo_curr_index[can_device] = FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION];
    }
    /*Enable local interrupts*/
    CAN_vConfigMsgObj(start_msg_obj, can_transfer->can_buffer);
    CAN_MSGOBJ[start_msg_obj].MOCTR = TRANSMIT_ENABLE;
    CAN_NUM_TFREE_MSOBJ[can_device]--;
    if(can_transfer->CAN_trans_ucb != NULL)
	{
	  can_transfer->CAN_trans_ucb(can_transfer, CAN_SUCCESS);
	}
	return CAN_WRITE_DATA;
    #else

    start_msg_obj = FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION];
    last_msg_obj  = start_msg_obj + CAN_TX_Buffer_size(can_device);
    flag = 0;

    do
    {
      if(CAN_TFREE_MSOBJ_FLG[start_msg_obj] == 1)
      {
        CAN_vConfigMsgObj(start_msg_obj, can_transfer->can_buffer);
        CAN_MSGOBJ[start_msg_obj].MOCTR = TRANSMIT_ENABLE;
        flag = 1;
        CAN_TFREE_MSOBJ_FLG[start_msg_obj] = 0;  
        CAN_NUM_TFREE_MSOBJ[can_device]--;
        if(can_transfer->CAN_trans_ucb != NULL)
	    {
	      can_transfer->CAN_trans_ucb(can_transfer, CAN_SUCCESS);
    	}
        return CAN_WRITE_DATA;
      }
      else
      {
        start_msg_obj++; 
      }
    }while((flag == 0) && (start_msg_obj < last_msg_obj) ); 
    #endif /*CAN_CFG_TX_FIFO_ENBL*/
  }
  else
  {
     #if  CAN_CFG_REQUEST_QUEUE_WR > 0
     if( (CAN_pending_writes[ can_device ] < CAN_CFG_REQUEST_QUEUE_WR) &&
	     (can_transfer->CAN_trans_ucb != NULL)
	   )
     {
        nloop = CAN_writeq_tail[can_device];
        CAN_writeq[ can_device ][ nloop ] = can_transfer;
        CAN_pending_writes[ can_device ]++;
        CAN_writeq_tail[can_device]++;
        if(CAN_writeq_tail[can_device] >= CAN_CFG_REQUEST_QUEUE_WR)
        {
          CAN_writeq_tail[can_device] = 0;        
        }  
        return CAN_SUCCESS;
     }  
     else
     {
       return CAN_ERR_RES;
     }
     #else
     return CAN_ERR_RES;
     #endif /*CAN_CFG_REQUEST_QUEUE_WR*/
  } 
  return CAN_SUCCESS;
}/*CAN_Write_Dev*/

#endif /*CAN_CFG_FUNC_WRITE*/




#if CAN_CFG_FUNC_CTRL_ENABLE == 1
/*Eanble the CAN module*/
CAN_STATUS CAN_Ctrl_enable( IFX_UINT32  *CAN_ctrl_args )
{
	if (CAN_ctrl_args == NULL)
	{
	  return CAN_ERR;
	}

    /*Unlock the watch dog timer to unprotect clock control register
      to write update information*/
	UNLOCK_ENDINIT_PROTECT ;
		if (*CAN_ctrl_args == 1)
		{
            /*Do not request to disable clock to CAN module*/
			CAN_CLC_DISR =  0;
		}
		else
		{
            /*Request to disable clock to CAN module*/
			CAN_CLC_DISR =  1;	
		}
    /*Lock the watch dog timer to protect all critical control registers*/
	LOCK_ENDINIT_PROTECT ;
	return CAN_SUCCESS	;
}
#endif

#if CAN_CFG_FUNC_CTRL_TRNS_NODE_ACT == 1
/* 
 CAN_Ctrl_trns_node_act is used to activacte or disable the chosen node at
 runtime.
*/
CAN_STATUS CAN_Ctrl_trns_node_act(CAN_DEVICE can_device, IFX_UINT32 *CAN_ctrl_args)
{
# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

	if (CAN_ctrl_args == NULL)
	{
	  return CAN_ERR;
	}
	
	if (*CAN_ctrl_args > 0)
	{
        /*
        Setting this bit terminates the participation of this node in the CAN traffic. 
        Any ongoing frame transfer is cancelled and the transmit line goes recessive.
        */ 
		CAN_NODE(can_device)->CAN_NCR |= 0x00000001  ;
	}
	else
	{
        /*Resetting bit INIT enables the participation of the node in the CAN traffic.*/
		CAN_NODE(can_device)->CAN_NCR &= ~0x00000001  ;		
	}
	return CAN_SUCCESS ;
}
#endif



#if CAN_CFG_FUNC_CTRL_NODE_EWRN_LVL == 1
/*
  CAN driver runtime error warning level configuration control function,
  this function is used to change the error warning level of the chosen Node
*/
CAN_STATUS 	CAN_Ctrl_Node_Error_Warn_Level(CAN_DEVICE can_device,  IFX_UINT32 *CAN_ctrl_args)
{
# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

	if (CAN_ctrl_args == NULL)
	{
	  return CAN_ERR;
	}

    /*Set NCR->CCE bit to write update new parameters to error counter registers */
    CAN_NODE(can_device)->CAN_NCR |= 0x00000040; 
	WRITEBITS( CAN_NODE(can_device)->CAN_NECNT , (*(IFX_UINT32*)CAN_ctrl_args) , NECNTX_EWRNLVL_MASK, NECNTX_EWRNLVL_LOCATION ) ;	
    CAN_NODE(can_device)->CAN_NCR &= ~(0x00000040); /*Reset NCR->CCE bit */

	return CAN_SUCCESS ;
}			   
#endif /*CAN_CFG_FUNC_CTRL_NODE_EWRN_LVL*/

#if CAN_CFG_FUNC_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE == 1
/*
  CAN driver runtime frame counter value control function, 
  CAN_Ctrl_Node_Frame_Count_Counter_Value is used to set 
  the frame count counter value for the chosen device.
*/
CAN_STATUS CAN_Ctrl_Node_Frame_Count_Counter_Value(CAN_DEVICE can_device, IFX_UINT32 *CAN_ctrl_args)
{
# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

	if (CAN_ctrl_args == NULL)
	{
	  return CAN_ERR;
	}

   /*
	NFCR reg can only be set if the CCE bit of corresponding NCR is set and Node is disabled
	hence set it first 
   */
	CAN_NODE(can_device)->CAN_NCR |= INIT_AND_CCE ;
	WRITEBITS( CAN_NODE(can_device)->CAN_NFCR , (*(IFX_UINT32*)CAN_ctrl_args) , NFCRX_CFC_MASK, NFCRX_CFC_LOCATION ) ;
	CAN_NODE(can_device)->CAN_NCR &= ~INIT_AND_CCE ;
	
	return CAN_SUCCESS ;
}
#endif /*CAN_CFG_FUNC_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE*/ 



/*Return the CAN protocol error status*/
CAN_STATUS CAN_node_status(CAN_DEVICE can_device)
{
	CAN_STATUS result = CAN_ERR;

	switch(CAN_NODE(can_device)->CAN_NSR & 0x00000007) /*Get Status from LEC*/
	{
	case 0 :  /*No error*/
		result = CAN_SUCCESS ;
		break ;
	case 1:	  /*Stuff error, either dominat/recissive bits occured more times than allowable times*/
		result = CAN_ERR_NET_STUFF ;
		break ;
	case 2:  /*error has occurred in a fixed format location of the message received.*/
		result = CAN_ERR_NET_FORM ;
		break ;
	case 3: /*Not even single acknolodge for transmitted message object*/
		result = CAN_ERR_NET_ACK ;
		break ;
	case 4: /*CRC error*/
		result = CAN_ERR_NET_CRC ;
		break ;
	case 5:  /*Bit zero error*/
		result = CAN_ERR_NET_BIT0 ;
		break ;
	case 6:	/*Bit one error*/
		result = CAN_ERR_NET_BIT1 ;
		break ;
	default:
		
		break ;
	}
	return result;
	
}


#if CAN_CFG_FUNC_CTRL_TRNS_BIT == 1 
/*
  CAN_ctrl_trns_baud is used to change the bit timings for the chosen device.
*/
CAN_STATUS CAN_Ctrl_trns_bit(	CAN_DEVICE can_device,	NBTR  *CAN_ctrl_args)	
{
	IFX_VUINT8 TSeg1   = 0x00 ;
	IFX_VUINT8 TSeg2   = 0x00 ;
	IFX_VUINT8 Brp 	  = 0x00 ;
	IFX_VUINT8 Tsync   = 0x0;

# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif
  
   if(CAN_ctrl_args == NULL)
   {
     return CAN_ERR;
   } 
   
   /*Check maximum and mininum for TSeg1 control field*/
	TSeg1 = ((*((IFX_UINT32 *)CAN_ctrl_args)) & NBTRX_TSEG1_MASK) >> 8 ;
    if((TSeg1 > 15) || (TSeg1 < 2))
    {
	  return CAN_ERR_NOT_SUPPORTED_HW;
    }	

   /*Check maximum and mininum for TSeg2 control field*/
	TSeg2 = ((*((IFX_UINT32 *)CAN_ctrl_args)) & NBTRX_TSEG2_MASK) >> 12 ;
    if(TSeg2 > 7 || TSeg2 < 1)
    {
	  return CAN_ERR_NOT_SUPPORTED_HW;
    }	

   /*Check maximum and mininum for TSync control field*/
	Tsync = ((*((IFX_UINT32 *)CAN_ctrl_args)) & NBTRX_SJW_MASK) >> 6 ;
    if(Tsync > 3 || Tsync < 0)
    {
	  return CAN_ERR_NOT_SUPPORTED_HW;
    }	

	Brp  = ((*((IFX_UINT32 *)CAN_ctrl_args)) & 0x3F);

    /*
	NBTR reg can only be set if the CCE bit of corresponding NCR is set and Node is disabled
	hence set it first 
    */
	CAN_NODE(can_device)->CAN_NCR |= INIT_AND_CCE ;
	/*Update bit timing register with new updated fields to get new baud rate*/
	WRITEBITS( CAN_NODE(can_device)->CAN_NBTR , TSeg1 , NBTRX_TSEG1_MASK, NBTRX_TSEG1_LOCATION ) ;
	WRITEBITS( CAN_NODE(can_device)->CAN_NBTR , TSeg2 , NBTRX_TSEG2_MASK, NBTRX_TSEG2_LOCATION ) ;
	WRITEBITS( CAN_NODE(can_device)->CAN_NBTR , Tsync , NBTRX_SJW_MASK, NBTRX_SJW_LOCATION ) ;
	WRITEBITS( CAN_NODE(can_device)->CAN_NBTR , Brp , NBTRX_BRP_MASK, NBTRX_BRP_LOCATION ) ;
    /*Reset INIT and CCE bit*/
	CAN_NODE(can_device)->CAN_NCR &= ~INIT_AND_CCE ;
	return CAN_SUCCESS ;
	
}
#endif


#if CAN_CFG_FUNC_CTRL_CREATE_GATEWAY == 1
/*
  CAN driver runtime gateway configuration control function,
  CAN_Ctrl_create_gateway may be used during runtime to create a gateway
  between two CAN nodes.  For the purposes of this function the argument 
  should be treated as an IFX_UINT8 pointer. 
*/
CAN_STATUS	CAN_Ctrl_trns_gateway
(	CAN_DEVICE can_device,	CAN_MESSAGE_OBJECT *CAN_ctrl_args) 
{
IFX_UINT8	Monum;

CAN_MESSAGE_OBJECT* mobj ;

# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

   if(CAN_ctrl_args == NULL)
   {
     return CAN_ERR;
   }

	Monum = (CAN_ctrl_args)->MoNum ;
	if (Monum > CAN_HW_MAX_MSGOBJS)
	{
		return CAN_ERR_NOT_SUPPORTED_HW ;
	}

    /*Check the gateway source object for which node it belongs to*/
	if( (IFX_UINT8)((CAN_MSGOBJ[Monum].MOCTR & 0x0000F000)>>12) != (can_device + 1))
	{
		return CAN_ERR_RES ;
	}

	mobj = CAN_ctrl_args ;
    /*Reset MSGVAL control field*/
	CAN_MSGOBJ[Monum].MOCTR = 0x00000020 ;	
    /*Set Gateway source message object current pointer to destination object*/
 	CAN_MSGOBJ[Monum].MOFGPR = *(IFX_UINT32*)&mobj->Mofgpr ;
  
	CAN_MSGOBJ[Monum].MOFCR &= ~0x0000000F ;
    /*Set object as Gateway source object*/
	CAN_MSGOBJ[Monum].MOFCR |= 0x00000004 ;

    /*Check and update control fields in Gateway source object to update information
    in destination object
    */
	/*To set TXRQ bit in destination message object*/
	if(mobj->Mofcr.Data_Frame_Send == 1)
	{
	 	CAN_MSGOBJ[Monum].MOFCR |= 0x00000100 ;
	}

    /*To copy ID form source to destination object*/
	if(mobj->Mofcr.ID_Copy == 1)
	{
	  	CAN_MSGOBJ[Monum].MOFCR |= 0x00000200 ;
	}
    /*To copy data length code form source to destination object*/
	if(mobj->Mofcr.DLC_Copy == 1)
	{
		CAN_MSGOBJ[Monum].MOFCR |= 0x00000400 ;
	}
    /*To copy data form source to destination object*/
	if(mobj->Mofcr.Data_Copy == 1)
	{
		CAN_MSGOBJ[Monum].MOFCR |= 0x00000800 ;
	}
    /*Set MSGAVL control field*/
	CAN_MSGOBJ[Monum].MOCTR = 0x00200000 ;
	return CAN_SUCCESS ;
	
}
#endif


/*
  CAN_Ctrl_config_Rcvbuffer will be used to program the hardware message objects with
  user provided message frames data which include the following information for both
  transmit as well as receive data.

  1. Accept standard/extended identifier message frames.

  2. Message ID and message mask 

  3. If the message frame to be sent then fill the data with user provided data.

     3a. Set the new data, Tx enable fields.

	 3b. Set MSGVAL field.

  4. If the message object to be configured for receive

     4a. Clear data fields.

	 4b. Reset new data field.

	 4c. Set MSGVAL field.
*/
CAN_STATUS CAN_Ctrl_config_Rcvbuffer (CAN_DEVICE can_device,CAN_TRANSFER* can_transfer)
{
	IFX_UINT8 msg_obj_num = 0, can_msg_frm = 0 ;

# if CAN_CFG_DEV_CHK == 1
  if (can_device >= CAN_HW_NUM)
  {
    return CAN_ERR_UNKNOWN_DEV;
  }
# endif

# if CAN_CFG_INIT_CHK == 1
  if (CAN_initialised_flags [can_device] != 1)
  {
    return CAN_ERR_NOT_INITIALISED;
  }
# endif

  if(can_transfer == NULL)
  {
    return CAN_ERR;
  }

    /*Check the maximum number of allowed receive message objects for this particular node*/
	if(can_transfer->can_buffer_size > CAN_RX_Buffer_size(can_device))
	{
		return CAN_ERR_RES ;
	}
    /*Get the first hardware message object number allocated for this node*/
	msg_obj_num = FIFOBASEOBJECTS[can_device][RECEIVE_LOCATION] ;
	for (; msg_obj_num < (can_transfer->can_buffer_size + FIFOBASEOBJECTS[can_device][RECEIVE_LOCATION]); msg_obj_num++)
	{
        /*Configure h/w message object with user provided information*/  
		CAN_vConfigMsgObj(msg_obj_num, &can_transfer->can_buffer[can_msg_frm]);
		can_msg_frm++;
	}
	return CAN_SUCCESS ;
}
		


/*
  This function marks the selected message object as not valid. 
  This means that this object cannot be sent or receive data. 
  If the selected object is by (meaning the object is transmitting
  a message or has received a new message) this function returns 
  the value "0" and the object is not deleted.
*/

IFX_UINT8 CAN_DelMsgObj(IFX_UINT8 ObjNr)
{
	IFX_UINT8 ret_val = 0;

	if(!  (CAN_MSGOBJ[ObjNr].MOCTR & 0x0000004C)) 
	{
		CAN_MSGOBJ[ObjNr].MOCTR = 0x00000020;     /* reset MSGVAL, try after some time */
		ret_val = 1;		
	}
    /*Rest MSGVAL control field*/
	CAN_MSGOBJ[ObjNr].MOCTR	 = 0x00000020 ;
    /*Reset all control fields*/
	CAN_MSGOBJ[ObjNr].MOFCR	 = 0x00000000 ; /*Function control register*/
	CAN_MSGOBJ[ObjNr].MOFGPR = 0x00000000 ;	/*FIFO/Gateway control register*/
	CAN_MSGOBJ[ObjNr].MOAMR	 = 0x3FFFFFFF ;	/*ID mask*/
	CAN_MSGOBJ[ObjNr].MOAR	 = 0x00000000 ;	 /*ID and priority*/

    /*Data fields*/
	CAN_MSGOBJ[ObjNr].MODATA[0] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[1] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[2] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[3] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[4] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[5] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[6] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MODATA[7] = 0x00 ;
	CAN_MSGOBJ[ObjNr].MOIPR	 =   0x00000000; /*Interrupt priority control fields*/
    /*Update linked list to set hardware message object as unallocated element*/
	SET_LISTCOMMAND( -1 , ObjNr)	;

	return(ret_val);
}



/*
  This function fills the forwarded SW message object with the content
  of the chosen HW message object. The structure of the SW message object
  is defined in the header file (see CAN_MESSAGE_OBJECT).
*/

void CAN_vGetMsgObj(IFX_UINT8 ObjNr, CAN_MESSAGE_OBJECT *pstObj)
{
	IFX_UINT8 data_loc = 0;

    /*Find the number of data bytes*/
	pstObj->MOCfg  = (CAN_MSGOBJ[ObjNr].MOFCR & DATA_LENGTH_MASK ) >> DLC_LOCATION;
	
    /*copy received data to application provided message object*/
	for(data_loc = 0; data_loc < (IFX_UINT8)((CAN_MSGOBJ[ObjNr].MOFCR & 0x0F000000) >> 24); data_loc++)
	{
		pstObj->Data[data_loc] = CAN_MSGOBJ[ObjNr].MODATA[data_loc] ;
	}

	pstObj->MOCfg  = (pstObj->MOCfg << 4);					/* shift DLC */

	if(CAN_MSGOBJ[ObjNr].MOAR & IS_EXTENDED_IDENTIFIER )	/* extended identifier */
	{
		pstObj->ID    = CAN_MSGOBJ[ObjNr].MOAR & 0x1fffffff;
		pstObj->MOCfg = pstObj->MOCfg | 0x04;				/* set IDE */
	}
	else														/* standard identifier  */
	{
		pstObj->ID   = (CAN_MSGOBJ[ObjNr].MOAR & 0x1fffffff) >> 18;
	}

}

/*
  This function sets up the message objects. This includes the 8 data bytes,
  the identifier (11- or 29-bit), the acceptance mask (11- or 29-bit), 
  the data number (0-8 bytes), the frame counter value and the EDE-bit 
  (standard or extended identifier).  The direction bit (DIR) can not be
  changed. The message is not sent; for this the function CAN_vTransmit 
  might be called. The structure of the SW message object is defined in 
  the header file (see CAN_MESSAGE_OBJECT).
*/

void CAN_vConfigMsgObj(IFX_UINT8 ObjNr, CAN_MESSAGE_OBJECT *pstObj)
{
	IFX_VUINT8 data_loc ;
	CAN_MSGOBJ[ObjNr].MOCTR = 0x00000020 ;       /* reset MSGVAL */

	if((pstObj->MOCfg & 0x0004) == 0x0004)       /* extended identifier */
	{
		CAN_MSGOBJ[ObjNr].MOAR  &= 0xC0000000 ; /*Message object ID*/
		CAN_MSGOBJ[ObjNr].MOAR  |= 0x20000000 | (pstObj->ID & 0x1FFFFFFF); 
		CAN_MSGOBJ[ObjNr].MOAMR = 0x20000000 | (pstObj->Mask  & 0x1FFFFFFF) ;
	}
	else                                         /* standard identifier */
	{
		CAN_MSGOBJ[ObjNr].MOAR  &= 0xC0000000 ; 
        /*expects the ID in lower 11 bits */
		CAN_MSGOBJ[ObjNr].MOAR  |= ((pstObj->ID & 0x7FF)  << 18) ;
		CAN_MSGOBJ[ObjNr].MOAMR = 0x20000000 | ((pstObj->Mask & 0x7FF) << 18) ;
	}

    /*Find number of data bytes*/
	CAN_MSGOBJ[ObjNr].MOFCR  &= 0x00070000;
	CAN_MSGOBJ[ObjNr].MOFCR  |= ((IFX_UINT32)(pstObj->MOCfg & 0x00f0)) << 20;

    /*Copy data to h/w message object*/
	for(data_loc = 0; data_loc < (pstObj->MOCfg & 0x00f0) >> 4; data_loc++)
	{
		CAN_MSGOBJ[ObjNr].MODATA[data_loc] = pstObj->Data[data_loc];
	}

	if((CAN_MSGOBJ[ObjNr].MOCTR & 0x00000800) == 0x00000800)  /* if transmit direction */
	{

     #if CAN_CFG_TX_FIFO_ENBL > 0
		CAN_MSGOBJ[ObjNr].MOCTR  = 0x0A280042;	    /* set NEWDAT, reset RTSEL,  */
													/* set MSGVAL, set TXEN0 */
     #else
		CAN_MSGOBJ[ObjNr].MOCTR  = 0x0E280042;	    /* set NEWDAT, reset RTSEL,  */
													/* set MSGVAL, set TXEN0, TXEN1 */
     #endif /*CAN_CFG_TX_FIFO_ENBL*/ 
 
	}		                                        
	else											/* if receive direction */
	{
		CAN_MSGOBJ[ObjNr].MOCTR  = 0x00A0001D;  /* reset RTSEL, set MSGVAL	  */
	}
}

/* 
  If hardware TRANSMIT OBJECT has to be loaded with data but not with a 
  new identifier, this function may be used instead of the function 
  CAN_vConfigMsgObj. The message object should be accessed by calling
  the function CAN_RequestMsgObj before calling this function. This prevents
  the CAN controller from working with invalid data.
*/
void CAN_vLoadData(IFX_UINT8 ObjNr, IFX_UINT8 *pData)
{
	IFX_VUINT8 data_loc;

	CAN_MSGOBJ[ObjNr].MOCTR = 0x00080000;       /* set NEWDAT */

    /*Copy data*/
	for(data_loc = 0; data_loc < (CAN_MSGOBJ[ObjNr].MOFCR & 0x0f000000) >> 24; data_loc++)
	{
		CAN_MSGOBJ[ObjNr].MODATA[data_loc] = *(pData++);
	}

	CAN_MSGOBJ[ObjNr].MOCTR = 0x00200040;       /* reset RTSEL, set MSGVAL */

}



/*
  Disables specified CAN node
*/
void 		CAN_Disable_Node(CAN_DEVICE can_device)
{
    /*Immediately aborts any transfer. Bs off recovery continues */
	CAN_NODE(can_device)-> CAN_NCR	= CAN_NODE_DISABLE ;		
	CAN_NODE(can_device)-> CAN_NIPR		= 0x00000000 ; 
	CAN_NODE(can_device)-> CAN_NECNT	= 0x00000000 ;
	CAN_NODE(can_device)-> CAN_NPCR		= 0x00000000 ; 
	CAN_NODE(can_device)-> CAN_NBTR		= 0x00000000 ; 
	CAN_NODE(can_device)-> CAN_NFCR		= 0x00000000 ;
}


CAN_STATUS CAN_Init_Node(CAN_DEVICE can_device, CAN_COM_PARMS* can_init_parms)
{
	IFX_VUINT32 msg_obj_num = 0;
	IFX_UINT8 port = 1, dev_num = 0, obj_count = 0, base_obj = 0;	
	IFX_UINT32 sys_freq;
	

	/*---------------------------------------------------------------------
	  Configuration of the Module Clock:
	  These Configurations are global to the multican module, hence should 
	  be done once only
	 ---------------------------------------------------------------------*/
	if (CLC_ALREADYSET != 1)
	{
        UNLOCK_ENDINIT_PROTECT;

        CAN_HW_CLC &= 0xFFFFFFFE;

		CAN_HW_FDR	|=   ( ((IFX_UINT32)(CAN_CFG_CLOCK_FDR_STEP & 0x3FF ))|
						(((IFX_UINT32)CAN_CFG_CLOCK_FDR_DIVIDOR_MODE )  	<< 14	)
					  );/*Load FDR*/

		sys_freq = SYS_CFG_CLK_FREQ;
	
        if(CAN_CFG_CLOCK_FDR_DIVIDOR_MODE == 1)
        { 
       	  CAN_clc_freeq = (IFX_UINT32)(sys_freq / (1024 - (CAN_CFG_CLOCK_FDR_STEP & 0x3FF)));
		}
		else
		{
          CAN_clc_freeq = (IFX_UINT32)((sys_freq * (CAN_CFG_CLOCK_FDR_STEP & 0x3FF))/ 1024);
		}

        LOCK_ENDINIT_PROTECT ;	  

   	    /*Enable particular interrupts and set priority in control registers*/
   		CAN_ISR_INIT();

        dev_num   = 0;
		obj_count = 0;
        /*Update FIFO base pointers for both receive and transmit*/
		while(dev_num < MAX_NODES)
		{
		  FIFOBASEOBJECTS[dev_num][TRANSMIT_LOCATION] = obj_count;
		  obj_count += CAN_TX_Buffer_size(dev_num);
		  FIFOBASEOBJECTS[dev_num][RECEIVE_LOCATION]  = obj_count;
		  obj_count += CAN_RX_Buffer_size(dev_num);
		  dev_num++;
		}

	   	CLC_ALREADYSET = 1 ;
	  }

	/*   - wait until Panel has finished the initialisation the list structure - */
	while(CAN_HW_PANCTR & CAN_PANCTR_BUSY)	{  	}


    /*Configure TX message objects*/
    /*Initialise the number of free transmit message object*/
    CAN_NUM_TFREE_MSOBJ[can_device] = CAN_TX_Buffer_size(can_device);

    msg_obj_num = FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION];
	base_obj    = msg_obj_num;
	obj_count   = msg_obj_num + CAN_TX_Buffer_size(can_device);

	#if CAN_CFG_TX_FIFO_ENBL > 0
	CAN_tfifo_curr_index[can_device] = msg_obj_num;
	#endif

    #if  CAN_CFG_TX_FIFO_ENBL > 0
    do
    {
      if(msg_obj_num == base_obj)
      {
        CAN_MSGOBJ[msg_obj_num].MOCTR  = 0x0E2001DF;
	    CAN_MSGOBJ[msg_obj_num].MOFCR  = 0x00020002 ;
	    CAN_MSGOBJ[msg_obj_num].MOFGPR = (  base_obj | ((obj_count - 1) << 8) | (base_obj << 16) ); 
      }
      else
      {
        CAN_MSGOBJ[msg_obj_num].MOCTR  = 0x0A2001DF;	
	    CAN_MSGOBJ[msg_obj_num].MOFCR  = 0x00020003 ; 
        CAN_MSGOBJ[msg_obj_num].MOFGPR =  (base_obj << 16) ;
      }
      CAN_MSGOBJ[msg_obj_num].MOAR   = 0x40000000;
      CAN_MSGOBJ[msg_obj_num].MOIPR  = ( (IFX_UINT32)(msg_obj_num<<8) ) ;
      CAN_MSGOBJ[msg_obj_num].MOIPR  |= 0x00000050 + (can_device<<4) ;
      SET_LISTCOMMAND( can_device , msg_obj_num) ; 
      while(CAN_HW_PANCTR & CAN_PANCTR_BUSY)	{  	}
      msg_obj_num++;
    }while(msg_obj_num < obj_count);
    #else
	do
    {
	  CAN_MSGOBJ[msg_obj_num].MOCTR = 0x0E2001DF;
	  CAN_MSGOBJ[msg_obj_num].MOAR  = 0x80000000;
	  CAN_MSGOBJ[msg_obj_num].MOIPR = ( (IFX_UINT32)(msg_obj_num<<8) ) ;
  	  CAN_MSGOBJ[msg_obj_num].MOIPR |= 0x00000050 + (can_device<<4) ;	  /* Load IPR */
	  CAN_MSGOBJ[msg_obj_num].MOFCR = 0x00020000 ;
	  SET_LISTCOMMAND( can_device , msg_obj_num) ; 
	  while(CAN_HW_PANCTR & CAN_PANCTR_BUSY)	{  	}
      CAN_TFREE_MSOBJ_FLG[msg_obj_num] = 1;
	  msg_obj_num++;
    }while(msg_obj_num < obj_count);
    #endif /*CAN_CFG_TX_FIFO_ENBL*/     

    /*Configure RX message objects*/
    msg_obj_num = FIFOBASEOBJECTS[can_device][RECEIVE_LOCATION];
    base_obj    = msg_obj_num;
	obj_count   = msg_obj_num + CAN_RX_Buffer_size(can_device);

    #if CAN_CFG_RX_FIFO_ENBL > 0
    do
    {
      if(msg_obj_num == base_obj)
      {
  	    CAN_MSGOBJ[msg_obj_num].MOFCR  = 0x00010001 ;
	    CAN_MSGOBJ[msg_obj_num].MOFGPR = (base_obj | ((obj_count - 1) << 8) | (base_obj) << 16);
      }
      else
      {
	    CAN_MSGOBJ[msg_obj_num].MOFCR  = 0x00010000 ;
        CAN_MSGOBJ[msg_obj_num].MOFGPR = 0;
      }
      CAN_MSGOBJ[msg_obj_num].MOCTR  = 0x00000FFF ;
      CAN_MSGOBJ[msg_obj_num].MOIPR  = ((IFX_UINT32)(msg_obj_num<<8)) ;
      CAN_MSGOBJ[msg_obj_num].MOIPR |= 0x00000001 + can_device ;
      SET_LISTCOMMAND( can_device , msg_obj_num) ; 
      while(CAN_HW_PANCTR & CAN_PANCTR_BUSY)	{  	}
      msg_obj_num++;
    }while(msg_obj_num < obj_count);   
    #else
    do
    {
	  /*just allocate the buffer, make them msg valid, and set direction.
	    config function should be called for the message configuration */
	  CAN_MSGOBJ[msg_obj_num].MOCTR = 0x00000FFF ; /*Set direction*/
	  CAN_MSGOBJ[msg_obj_num].MOFCR = 0x00010000 ; /*Set as general message object*/	
      /*Set interrupt control fields*/
	  CAN_MSGOBJ[msg_obj_num].MOIPR = ((IFX_UINT32)(msg_obj_num<<8)) ;
	  CAN_MSGOBJ[msg_obj_num].MOIPR |= 0x00000001 + can_device ;	  /*Load IPR */
	  SET_LISTCOMMAND( can_device , msg_obj_num) ; 
	  while(CAN_HW_PANCTR & CAN_PANCTR_BUSY)	{  	}
	  msg_obj_num++;
    }while(msg_obj_num < obj_count);
    #endif /*CAN_CFG_RX_FIFO_ENBL*/

    /*Reset the receive user call back pointer*/
    CAN_rcv_ucb[can_device] = NULL;

	/*
	Before initialisation of the module the CCE and the INIT BIT 
	should be set	when Init = 1 the node does not participates in 
	any communication
	*/	

	CAN_NODE(can_device)->CAN_NCR =  INIT_AND_CCE ;

    /* load node bit timing register, to set baud rate */
   	CAN_NODE(can_device)-> CAN_NBTR	=	(*(IFX_UINT32*)(&can_init_parms -> can_bit_timing))& 0x0000FFFF;	
    /*Set node frame count register*/
	CAN_NODE(can_device)-> CAN_NFCR	=	(*(IFX_UINT32*)(&can_init_parms -> can_frame_counter)&0x001FFFFF) ; 
    /*Initialise error count registers*/
	CAN_NODE(can_device)-> CAN_NECNT= 	(*((IFX_UINT32*)(&can_init_parms -> can_error_counter)));
	/*Initialise mode of node*/
	CAN_NODE(can_device)-> CAN_NPCR	= 	(((IFX_UINT32)can_init_parms -> can_mode.Loop_Back) <<	8 );	

    /*Enable interruts according to user configuration */
    switch(can_device)
    {
	  case 0: /*node 0*/
        /*Enable transfer, CFC, alert and LEC interrupts according to user configuration*/
   	    CAN_NODE(can_device)-> CAN_NCR  |=  (CAN_CFG_NODE0_INT_TRANSFER_ENABLED << 1) | \
   	                  (CAN_CFG_NODE0_INT_ALERT_ENABLED << 3) | \
   	                  (CAN_CFG_NODE0_INT_LEC_ENABLED   << 2) ;

		CAN_NODE(can_device)-> CAN_NFCR |= CAN_CFG_NODE0_INT_CFC_ENABLED << 22;

        /*Link source control register with transfer, alert, LEC and CFC interrupts*/ 
		CAN_NODE(can_device)-> CAN_NIPR |= (  (9  << NIPRX_ALINP_LOCATION ) |
		                                      (10 << NIPRX_LECINP_LOCATION) |
		                                      (0  << NIPRX_TRINP_LOCATION)  |
		                                      (9  << NIPRX_CFCINP_LOCATION)  ); 
	    break;

	  case 1: /*node 1*/
   	    CAN_NODE(can_device)-> CAN_NCR  |=  (CAN_CFG_NODE1_INT_TRANSFER_ENABLED << 1) | \
   	                  (CAN_CFG_NODE1_INT_ALERT_ENABLED << 3) | \
   	                  (CAN_CFG_NODE1_INT_LEC_ENABLED   << 2) ;

		CAN_NODE(can_device)-> CAN_NFCR |= CAN_CFG_NODE1_INT_CFC_ENABLED << 22;

        /*Link source control register with transfer, alert, LEC and CFC interrupts*/ 
		CAN_NODE(can_device)-> CAN_NIPR |= (  (9  << NIPRX_ALINP_LOCATION ) |
		                                      (10 << NIPRX_LECINP_LOCATION) |
		                                      (0  << NIPRX_TRINP_LOCATION)  |
		                                      (9  << NIPRX_CFCINP_LOCATION)  ); 
	    break;

	  case 2: /*node 2*/
   	    CAN_NODE(can_device)-> CAN_NCR  |=  (CAN_CFG_NODE2_INT_TRANSFER_ENABLED << 1) | \
   	                  (CAN_CFG_NODE2_INT_ALERT_ENABLED << 3) | \
   	                  (CAN_CFG_NODE2_INT_LEC_ENABLED   << 2) ;

		CAN_NODE(can_device)-> CAN_NFCR |= CAN_CFG_NODE2_INT_CFC_ENABLED << 22;

        /*Link source control register with transfer, alert, LEC and CFC interrupts*/ 
		CAN_NODE(can_device)-> CAN_NIPR |= (  (9  << NIPRX_ALINP_LOCATION ) |
		                                      (10 << NIPRX_LECINP_LOCATION) |
		                                      (0  << NIPRX_TRINP_LOCATION)  |
		                                      (9  << NIPRX_CFCINP_LOCATION)  ); 
	    break;

	  case 3: /*node 3*/
   	    CAN_NODE(can_device)-> CAN_NCR  |=  (CAN_CFG_NODE3_INT_TRANSFER_ENABLED << 1) | \
   	                  (CAN_CFG_NODE3_INT_ALERT_ENABLED << 3) | \
   	                  (CAN_CFG_NODE3_INT_LEC_ENABLED   << 2) ;

		CAN_NODE(can_device)-> CAN_NFCR |= CAN_CFG_NODE3_INT_CFC_ENABLED << 22;

        /*Link source control register with transfer, alert, LEC and CFC interrupts*/ 
		CAN_NODE(can_device)-> CAN_NIPR |= (  (9  << NIPRX_ALINP_LOCATION ) |
		                                      (10 << NIPRX_LECINP_LOCATION) |
		                                      (0  << NIPRX_TRINP_LOCATION)  |
		                                      (9  << NIPRX_CFCINP_LOCATION)  ); 
	    break;
    } 

	/*  Configuration of the selected CAN Port Pins:
	IF CAN NODE is Init and not on LBM */
	if ( ( 	CAN_NODE(can_device)-> CAN_NCR & 0x00000001		) 	&& 
		 (!(CAN_NODE(can_device)-> CAN_NPCR & 0x00000100)	) 
		) 
	{
	  switch(can_device)
	  {
	    case 0: /*node 0*/
          if(SYS_gpio_alloc(SYS_GPIO_CAN0_RX) != SYS_SUCCESS)
          {
            return CAN_ERR;
          }
          if(SYS_gpio_alloc(SYS_GPIO_CAN0_TX) != SYS_SUCCESS)
          {
 			 SYS_gpio_free(SYS_GPIO_CAN0_RX);
             return CAN_ERR;
          }
          if(SYS_gpio_get_port(SYS_GPIO_CAN0_RX) == port )
          {
            CAN_NODE(can_device)-> CAN_NPCR |= 0x1;
          }
		  break;

	    case 1:	/*node 1*/
          if(SYS_gpio_alloc(SYS_GPIO_CAN1_RX) != SYS_SUCCESS)
          {
            return CAN_ERR;
          }
          if(SYS_gpio_alloc(SYS_GPIO_CAN1_TX) != SYS_SUCCESS)
          {
 			 SYS_gpio_free(SYS_GPIO_CAN1_RX);
             return CAN_ERR;
          }
          if(SYS_gpio_get_port(SYS_GPIO_CAN1_RX) == port )
          {
            CAN_NODE(can_device)-> CAN_NPCR |= 0x1;
          }
		  break;

	    case 2:	/*node 2*/
          if(SYS_gpio_alloc(SYS_GPIO_CAN2_RX) != SYS_SUCCESS)
          {
            return CAN_ERR;
          }
          if(SYS_gpio_alloc(SYS_GPIO_CAN2_TX) != SYS_SUCCESS)
          {
 			 SYS_gpio_free(SYS_GPIO_CAN2_RX);
             return CAN_ERR;
          }
		  break;

	    case 3: /*node 3*/
          if(SYS_gpio_alloc(SYS_GPIO_CAN3_RX) != SYS_SUCCESS)
          {
            return CAN_ERR;
          }
          if(SYS_gpio_alloc(SYS_GPIO_CAN3_TX) != SYS_SUCCESS)
          {
 			 SYS_gpio_free(SYS_GPIO_CAN3_RX);
             return CAN_ERR;
          }
		  break;

	    default:
		  return CAN_ERR;
	  }
	}
	
    /*Reset INIT and CCE bit to participate this node in CAN traffic*/
	CAN_NODE(can_device)-> CAN_NCR &= ~0x00000041 ;

    return CAN_SUCCESS;
}

/*
  Message object transmit ISR
*/
void CAN_TXMOBJ_ISR(IFX_UINT8 can_device)
{
  IFX_UINT8     start_msg_obj = 0, last_msg_obj = 0, flag = 0, nloop = 0;
  CAN_TRANSFER  *can_trans;

  start_msg_obj = FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION];
  last_msg_obj  = start_msg_obj + CAN_TX_Buffer_size(can_device);

  do
  {
    if((CAN_MSGOBJ[start_msg_obj].MOCTR & CAN_MOCTRX_TXPND) == CAN_MOCTRX_TXPND)
    {
      flag = 1;
    } 
    else
    {
      start_msg_obj++;
    } 
  }while((flag == 0) && (start_msg_obj < last_msg_obj));

  if(flag == 1)
  {
    CAN_MSGOBJ[start_msg_obj].MOCTR = CAN_MOCTRX_TXPND;    /* reset TXPND */ 

    #if CAN_CFG_REQUEST_QUEUE_WR > 0    
    if( CAN_pending_writes[ can_device ] > 0)
    {
       nloop = CAN_writeq_head[can_device];
       can_trans = CAN_writeq[can_device][nloop];

       #if CAN_CFG_TX_FIFO_ENBL > 0
	   start_msg_obj = CAN_tfifo_curr_index[can_device];
       CAN_tfifo_curr_index[can_device]++;
       if(CAN_tfifo_curr_index[can_device] >= 
         (FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION] + CAN_TX_Buffer_size(can_device)) )
       {
          CAN_tfifo_curr_index[can_device] = FIFOBASEOBJECTS[can_device][TRANSMIT_LOCATION];
       }
	   #endif

       CAN_vConfigMsgObj(start_msg_obj, can_trans->can_buffer) ;
       CAN_MSGOBJ[start_msg_obj].MOCTR = TRANSMIT_ENABLE;
       CAN_writeq_head[can_device]++;
       if(CAN_writeq_head[can_device] >= CAN_CFG_REQUEST_QUEUE_WR)
       {
          CAN_writeq_head[can_device] = 0;
       }

       CAN_pending_writes[can_device]--;

       if(can_trans->CAN_trans_ucb != NULL)
       {
	     can_trans->CAN_trans_ucb(can_trans, CAN_SUCCESS);
	   }
    }
    else
    {
      #if CAN_CFG_TX_FIFO_ENBL == 0
      CAN_TFREE_MSOBJ_FLG[start_msg_obj] = 1;  
	  #endif
      CAN_NUM_TFREE_MSOBJ[can_device]++;
    }
    #else
      #if CAN_CFG_TX_FIFO_ENBL == 0
      CAN_TFREE_MSOBJ_FLG[start_msg_obj] = 1;  
	  #endif
    CAN_NUM_TFREE_MSOBJ[can_device]++;
    #endif /*CAN_CFG_REQUEST_QUEUE_WR*/
  }
  else
  {
    /*Erroneous*/
  } 
}



/*Receive message objects ISR*/
void CAN_RXMOBJ_ISR(IFX_UINT8 CAN_node_num)
{
  IFX_UINT8    start_msg_obj = 0, last_msg_obj = 0, flag = 0;
  CAN_TRANSFER *can_trans;


  start_msg_obj = FIFOBASEOBJECTS[CAN_node_num][RECEIVE_LOCATION];
  last_msg_obj  = start_msg_obj + CAN_RX_Buffer_size(CAN_node_num);

  do
  {
    if((CAN_MSGOBJ[start_msg_obj].MOCTR & CAN_MOCTRX_RXPND) == CAN_MOCTRX_RXPND)
    {
      CAN_MSGOBJ[start_msg_obj].MOCTR = CAN_MOCTRX_RXPND | CAN_MOCTRX_NEWDAT | 0x00000020; 
	  flag = 1;
    }
    else
    {
      start_msg_obj++;   
    }
  }while( (start_msg_obj < last_msg_obj) && (flag == 0));

  if(flag == 1)
  {
    if(CAN_MSGOBJ[start_msg_obj].MOCTR & CAN_MOCTRX_MSGLST)
    {
      can_node_error[CAN_node_num]    = CAN_ERR_MSG_LOST ;
      CAN_MSGOBJ[start_msg_obj].MOCTR = CAN_MOCTRX_MSGLST;	
    } 
    #if CAN_CFG_REQUEST_QUEUE_RD > 0 
    if(CAN_pending_reads[ CAN_node_num ] > 0)
    {
      can_trans = CAN_readq[CAN_node_num][CAN_readq_head[ CAN_node_num ]];
      CAN_vGetMsgObj(start_msg_obj, can_trans->can_buffer); 
      if(can_trans->CAN_trans_ucb != NULL)
      {
	    can_trans->CAN_trans_ucb(can_trans, CAN_SUCCESS);
      } 
      CAN_MSGOBJ[start_msg_obj].MOCTR = (CAN_MOCTRX_RXPND | CAN_MOCTRX_NEWDAT | 0x00200000);
      CAN_readq_head[ CAN_node_num ]++;   
      if(CAN_readq_head[ CAN_node_num ] >= CAN_CFG_REQUEST_QUEUE_RD)
      {
        CAN_readq_head[ CAN_node_num ] = 0;  
      }     
      CAN_pending_reads[ CAN_node_num ]--;
    }
    else
    {
      MsgRcvd[CAN_node_num][MsgRcvd_wrptr[CAN_node_num]] = start_msg_obj;
      MsgRcvd_wrptr[CAN_node_num]++;
      if(MsgRcvd_wrptr[CAN_node_num] >= CAN_HW_MAX_MSGOBJS)
      {
        MsgRcvd_wrptr[CAN_node_num] = 0; 
      }
      MsgRcvd_num_obj[CAN_node_num]++;  
    
	  if(CAN_rcv_ucb[CAN_node_num] != NULL)
	  {
	    CAN_rcv_ucb[CAN_node_num]();
	  }
    }
    #else
    MsgRcvd[CAN_node_num][MsgRcvd_wrptr[CAN_node_num]] = start_msg_obj;
    MsgRcvd_wrptr[CAN_node_num]++;
    if(MsgRcvd_wrptr[CAN_node_num] >= CAN_HW_MAX_MSGOBJS)
    {
      MsgRcvd_wrptr[CAN_node_num] = 0; 
    }
    MsgRcvd_num_obj[CAN_node_num]++;  
    if(CAN_rcv_ucb[CAN_node_num] != NULL)
	{
	  CAN_rcv_ucb[CAN_node_num]();
	}
    #endif /*CAN_CFG_REQUEST_QUEUE_RD*/
  }
  else
  {
    /*Erroneous*/
  } 
}/*CAN_RXMOBJ_ISR*/

/*Transfer status ISR*/
void CAN_TRANSFER_ISR(IFX_UINT8 CAN_node)
{
	IFX_UINT8 CAN_node_num = 0;
	for(CAN_node_num = 0; CAN_node_num < MAX_NODES; CAN_node_num++)
	{
	   if( (CAN_NODE(CAN_node_num)->CAN_NSR) & CAN_HW_NSR_TXOK )/*if TXOK*/
	   {
         /* reset TXOK */
		 CAN_NODE(CAN_node_num)->CAN_NSR &= ~(CAN_HW_NSR_TXOK);	 	                
	   }
	   if( (CAN_NODE(CAN_node_num)->CAN_NSR) & CAN_HW_NSR_RXOK )/*if RXOK*/
	   {
	     /* reset RXOK */
	     CAN_NODE(CAN_node_num)->CAN_NSR &= ~(CAN_HW_NSR_RXOK);
	   }
	}
}




#define CAN_MAX_ERR_LVL 128
#define CAN_RST_LEC     0x00000338
/*CAN module Protocol error ISR*/
void CAN_LEC_ISR(IFX_UINT8 CAN_node)
{
  IFX_UINT8 CAN_node_num = 0, REC_val = 0, TEC_val = 0;

  for(CAN_node_num = 0; CAN_node_num < MAX_NODES; CAN_node_num++)
  {
    /*Transmit error count*/
	TEC_val = (IFX_UINT8)((CAN_NODE(CAN_node_num)->CAN_NECNT & 0x0000FF00)>>8) ;

    /*Receive error count*/
	REC_val = (CAN_NODE(CAN_node_num)->CAN_NECNT & 0x000000FF);

   /*Node is in BUS off state, either TX or RX error counter reaches maximum value i.e. 255*/
    if((CAN_NODE(CAN_node_num)->CAN_NSR) & CAN_HW_NSR_BOFF )
	{
	  can_node_error[CAN_node_num] = CAN_ERR_NET_STATE_OFF ; /**/
	}
    /*Either receive or transmit error counter reaches maximum value i.e. 128*/ 
	else if( TEC_val >= CAN_MAX_ERR_LVL || REC_val >= CAN_MAX_ERR_LVL)
	{
  	  can_node_error[CAN_node_num] = CAN_ERR_NET_STATE_PASS ;
	}
  }
}


/*CAN module Alert ISR*/
void CAN_ALERT_CFC_ISR(IFX_UINT8 CAN_node)
{
  IFX_UINT8 CAN_node_num = 0;

  for(CAN_node_num = 0; CAN_node_num < MAX_NODES; CAN_node_num++)
  {
    if((CAN_NODE(CAN_node_num)->CAN_NSR) & CAN_HW_NSR_ALERT)
	{
        /* if BOFF */
		if( (CAN_NODE(CAN_node_num)->CAN_NSR) & CAN_HW_NSR_BOFF )
		{
			can_node_error[CAN_node_num] = CAN_ERR_NET_STATE_OFF ;

			/*Reset error warning counters*/
			CAN_NODE(CAN_node_num)->CAN_NECNT &= 0xFFFF0000;
            /*Atempt to make the node active */
			CAN_NODE(CAN_node_num)->CAN_NCR &= ~(INIT_AND_CCE);

		}
		if( (CAN_NODE(CAN_node_num)->CAN_NSR) & CAN_HW_NSR_EWRN)  /* if EWRN */
		{
			can_node_error[CAN_node_num] = CAN_ERR_ERRORCOUNT_WARNING ;
		}
		if( (CAN_NODE(CAN_node_num)->CAN_NCR) & NCRX_INIT_MASK)  /* if INIT */
		{
			can_node_error[CAN_node_num] = CAN_ERR_NODE_DISABLED ;				
		}
	}
    /* if frame counter overflow flag 3 */
	if((CAN_NODE(CAN_node_num)->CAN_NFCR) & CAN_NFCR_CFCOV)					
	{
		can_node_error[CAN_node_num] = CAN_ERR_FRAMECOUNT_OVERFLOW ;
        /* reset overflow flag 3 */
		CAN_NODE(CAN_node_num)->CAN_NFCR &= ~(CAN_NFCR_CFCOV);
	}
  }/*end of for*/ 

}


