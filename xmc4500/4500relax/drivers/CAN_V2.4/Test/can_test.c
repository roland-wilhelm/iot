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
** @FILENAME@:       CAN_TEST.c
** @VERSION@:        2.4
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: CAN 
**
** =============================================================================
** Contents: Test cases
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      S.A.Kazmi          Release after code review.
** 07/05/2004      Mahesh             More test cases are added.
** 21/06/2004      Mahesh             More comments are added to code.  
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

/*
  Test procedure:
  For all the test cases make sure the following configuration is correct
  in CAN_CFG.h file

  CAN_CFG_TX_BUFFER_SIZE_NODE_0    5					
  CAN_CFG_TX_BUFFER_SIZE_NODE_1    5
  CAN_CFG_TX_BUFFER_SIZE_NODE_2	   5				
  CAN_CFG_TX_BUFFER_SIZE_NODE_3	   5				

  CAN_CFG_RX_BUFFER_SIZE_NODE_0    5					
  CAN_CFG_RX_BUFFER_SIZE_NODE_1    5
  CAN_CFG_RX_BUFFER_SIZE_NODE_2	   5				
  CAN_CFG_RX_BUFFER_SIZE_NODE_3	   5				

  Test case 0:
    a. Test all 4 CAN nodes in loop back mode.
	b. CAN node 0 receive 5 CAN message frames into swobjudum[0] to swobjudum[4]
	   transmitted by CAN node 1 with message ID number 0x15555554. 
	c. CAN node 2 receive 5 CAN message frames into swobjudum[5] to swobjudum[9]
	   transmitted by CAN node 3 with message ID number 0x15555555.


  Test case 1:
    a. Test CAN node 0 with CAN analyser.
    b. Set CAN analyser to 25k baud, with message ID number as 0x15555554.
    c. Connect CAN analyser CAN_H and CAN_L pins to CAN node pins.
    d. Transmit CAN frame from CAN analyser to CAN node 0, as soon as node 0 
       receive frame it also send one frame to CAN analyser.

  Test case 2:
    a. This is to test the Gateway functionality of CAN module.
	b. Initialise CAN node3, node2 in loopback node1 and node0 in non loopback mode.
	c. Configure node0, node2 receive buffers.
	d. Configure node2 receive message objects as gateway source objects and node1
	   message objects as gateway destination objects.
	e. Connect nod0, node1 externally.
	f. node1 transmits receive message (through node2 by using gateway) on 
	   external bus, which are also received by node0. 
	g. Compiler, download and  debug application.
	h. swobjdum[5-9] message objects contain the data received by node0, 
	   swobjdum[0-4] contain message objects received by node2.
	   Please note that can node1 and node0 are in non loopback mode. The data
	   received by can node0 is from can node1, node1 from node2 by using 
	   gateway.   
  

  Note 1:
  To enable Transmit FIFO configure define CAN_CFG_TX_FIFO_ENBL to value 1 in CAN_CFG.H file.
  To enable receive FIFO configure define CAN_CFG_RX_FIFO_ENBL to value 1 in CAN_CFG.H file.

  Configure the transmit and read request queue as follows in CAN_CFG.h file.
  #define CAN_CFG_REQUEST_QUEUE_WR 20
  #define CAN_CFG_REQUEST_QUEUE_WR 20

  Note 2:
    CAN hardware message objects are allocated for each node depend on user
    configuration CAN_CFG_TX_BUFFER_SIZE_NODE_x and CAN_CFG_RX_BUFFER_SIZE_NODE_x 

    Node number     1st TX message object            1st Receive message object

        0			     0                          CAN_CFG_TX_BUFFER_SIZE_NODE_0
        

        1           CAN_CFG_TX_BUFFER_SIZE_NODE_0   CAN_CFG_TX_BUFFER_SIZE_NODE_0   
						       + 							 +
				    CAN_CFG_RX_BUFFER_SIZE_NODE_0   CAN_CFG_RX_BUFFER_SIZE_NODE_0
					                                         +
												    CAN_CFG_TX_BUFFER_SIZE_NODE_1



        2           CAN_CFG_TX_BUFFER_SIZE_NODE_0   CAN_CFG_TX_BUFFER_SIZE_NODE_0   
						        +							 +
				    CAN_CFG_RX_BUFFER_SIZE_NODE_0   CAN_CFG_RX_BUFFER_SIZE_NODE_0
					            +                            +
					CAN_CFG_TX_BUFFER_SIZE_NODE_1   CAN_CFG_TX_BUFFER_SIZE_NODE_1
								+							 +
					CAN_CFG_RX_BUFFER_SIZE_NODE_1	CAN_CFG_RX_BUFFER_SIZE_NODE_1
                                                             +  
													CAN_CFG_TX_BUFFER_SIZE_NODE_2

     The same procedure applies to node 3 also.

*/															 
#ifndef TEST_CASE
#define TEST_CASE 2
#endif

#if (TEST_CASE == 0)
#include "COMPILER.h"
#include "CAN_CFG.h"
#include "CAN_IDL.h"
#include "CAN_IIL.h"
#include "CAN_API.h"

CAN_MESSAGE_OBJECT swobj[10], swobjdum[10] ;
IFX_VUINT8          rcv_msg_frms0 = 0, rcv_msg_frms2 = 0;

CAN_TRANSFER canT,   canT1,   canT2,   canT3,   canT4 ;
CAN_TRANSFER canT5,  canT6,   canT7,   canT8,   canT9 ;

CAN_TRANSFER canR,   canR1,   canR2,   canR3,   canR4 ;
CAN_TRANSFER canR5,  canR6,   canR7,   canR8,   canR9 ;

void delay(void);
void rx_ucb(struct can_trans *t, CAN_STATUS s);
void tx_ucb(struct can_trans *t, CAN_STATUS s);
void rcv_ucb0(void);
void rcv_ucb2(void);

void main(void)
{
	IFX_UINT8 i = 0 ;
	CAN_COM_PARMS can_init_parms ;

    /*Initialise global system clock frequency*/
    SYS_clk_initialise();

	/*Init the CAN Mode structure*/
	can_init_parms.can_mode.Loop_Back = 1 ;	 /*Set node in loopback mode*/

	/*Baud rate configuration parameters*/
	can_init_parms.can_bit_timing.Baud_Prescaler = 0 ;
	can_init_parms.can_bit_timing.Divider_Mode = 0 ;
	can_init_parms.can_bit_timing.Sync_Jump = 2;
	can_init_parms.can_bit_timing.Timing_Seg1 = 5 ;
	can_init_parms.can_bit_timing.Timing_Seg2 = 4 ;

	/*Error counter configuration parameters*/
	can_init_parms.can_error_counter.Receive_Count = 0 ;
	can_init_parms.can_error_counter.Transmit_Count = 0 ;
	can_init_parms.can_error_counter.Warn_Level = 96 ;

    /*Frame counter configuration parameters*/
   	can_init_parms.can_frame_counter.Count_value = 0 ;
   	can_init_parms.can_frame_counter.Frame_Count_mode = 0 ;
   	can_init_parms.can_frame_counter.Frame_Count_select = 7 ;

    CAN_Initialise_dev(0, &can_init_parms) ;  /*Initialise CAN node 0*/
	CAN_Initialise_dev(1, &can_init_parms) ;  /*Initialise CAN node 1*/
    CAN_Initialise_dev(2, &can_init_parms) ;  /*Initialise CAN node 2*/
	CAN_Initialise_dev(3, &can_init_parms) ;  /*Initialise CAN node 3*/

    /*Enable interrupts globally*/
    ENABLE_GLOBAL_INTERRUPT() ;

    /*Register user call back with LLD to receive a notification when LLD
    receives a message frame*/
    CAN_Control_dev(0, CAN_CTRL_REG_RCV_UCB, &rcv_ucb0);
    CAN_Control_dev(2, CAN_CTRL_REG_RCV_UCB, &rcv_ucb2);

    /*Clear receive data buffers*/
    for(i=0; i<10; i++)
	{
	  swobjdum[i].Data[0] =  0 ;
	  swobjdum[i].Data[1] =  0 ;
	  swobjdum[i].Data[2] =  0 ;
	  swobjdum[i].Data[3] =  0 ;
	  swobjdum[i].Data[4] =  0 ;
	  swobjdum[i].Data[5] =  0 ;
	  swobjdum[i].Data[6] =  0 ;
	  swobjdum[i].Data[7] =  0 ;
	}
	


    /*Configure message objects to receive message frames with ID --> 0x15555554
    , for CAN node 0*/
	for(i = 0 ; i < 5 ; i++)
	{
		swobj[i].Data[0] = 0 ;
		swobj[i].Data[1] = 0;
		swobj[i].Data[2] = 0;
		swobj[i].Data[3] = 0;
		swobj[i].Data[4] = 0;
		swobj[i].Data[5] = 0;
		swobj[i].Data[6] = 0;
		swobj[i].Data[7] = 0;
		swobj[i].ID 	 = 0x15555554 ; /*Message frame ID*/
		swobj[i].Mask	 = 0x1FFFFFFF ;
		swobj[i].MOCfg	 = 0x0084 ;	   /*Extended identifier*/	
	}
	
	canT.can_buffer_size = 5 ; /*Number of message objects to be configured*/
	canT.can_buffer = &swobj[0] ;  /*Adress of application specified first message object*/	 

    /* The application provided message object configuration parameters specified in swobj[0..4]
	   or copied to node0 allocated receive hardware message objects */
    if (CAN_Ctrl_config_Rcvbuffer( 0, &canT ) != CAN_SUCCESS) 
 	{
      return;
	}

    /* The application provided message object configuration parameters specified in swobj[5..9]
	   or copied to node2 allocated receive hardware message objects */
	for(i = 5 ; i < 10 ; i++)
	{
		swobj[i].Data[0] = 0 ;
		swobj[i].Data[1] = 0;
		swobj[i].Data[2] = 0;
		swobj[i].Data[3] = 0;
		swobj[i].Data[4] = 0;
		swobj[i].Data[5] = 0;
		swobj[i].Data[6] = 0;
		swobj[i].Data[7] = 0;
		swobj[i].ID 	 = 0x15555555 ;	 /*Message frame ID*/
		swobj[i].Mask	 = 0x1FFFFFFF ;
		swobj[i].MOCfg	 = 0x0084 ;	   /*Extended identifier*/	
	}
	
	canT.can_buffer_size = 5 ; /*Number of message objects to be configured*/
	canT.can_buffer = &swobj[5] ;  /*Adress of application specified first message object*/	 

    /* configure message object for recieve of CAN node2 */
    if (CAN_Ctrl_config_Rcvbuffer( 2, &canT ) != CAN_SUCCESS) 
 	{
      return;
	}


    /*Configure transmit message objects to send frames over CAN node 1 */
   	for(i = 0 ; i < 5 ; i++)
	{
		swobj[i].Data[0] = 1 + i;
		swobj[i].Data[1] = 1 + i;
		swobj[i].Data[2] = 1 + i;
		swobj[i].Data[3] = 1 + i;
		swobj[i].Data[4] = 1 + i;
		swobj[i].Data[5] = 1 + i;
		swobj[i].Data[6] = 1 + i;
		swobj[i].Data[7] = 1 + i;
		swobj[i].ID 	 = 0x15555554 ;
		swobj[i].Mask	 = 0x1FFFFFFF ;
		swobj[i].MOCfg	 = 0x0084 ;	   //DLC	
	}


    /*Configure transmit message objects to send frames over CAN node 3 */
   	for(i = 5 ; i < 10 ; i++)
	{
		swobj[i].Data[0] = 2 + i;
		swobj[i].Data[1] = 2 + i;
		swobj[i].Data[2] = 2 + i;
		swobj[i].Data[3] = 2 + i;
		swobj[i].Data[4] = 2 + i;
		swobj[i].Data[5] = 2 + i;
		swobj[i].Data[6] = 2 + i;
		swobj[i].Data[7] = 2 + i;
		swobj[i].ID 	 = 0x15555555 ; /*Message object ID*/
		swobj[i].Mask	 = 0x1FFFFFFF ;	/*Message object ID mask*/
		swobj[i].MOCfg	 = 0x0084 ;	   /*Extended identifier*/	
	}


	canT.can_buffer = &swobj[0] ;     /*Application provided data buffers to send data*/	 
	canT.CAN_trans_ucb = tx_ucb ;     /*Application provided user callback function*/	 
	CAN_Write_Dev(1,&canT);
	canT1.can_buffer = &swobj[1] ;  
	canT1.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(1,&canT1);
	canT2.can_buffer = &swobj[2] ;  
	canT2.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(1,&canT2);
	canT3.can_buffer = &swobj[3] ;  
	canT3.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(1,&canT3);
	canT4.can_buffer = &swobj[4] ;  
	canT4.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(1,&canT4);

    delay();

    canT5.can_buffer = &swobj[5] ;
	canT5.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(3,&canT5);
	canT6.can_buffer = &swobj[6] ;
	canT6.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(3,&canT6);
	canT7.can_buffer = &swobj[7] ;
	canT7.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(3,&canT7);
	canT8.can_buffer = &swobj[8] ;
	canT8.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(3,&canT8);
	canT9.can_buffer = &swobj[9] ;
	canT9.CAN_trans_ucb = tx_ucb ;
	CAN_Write_Dev(3,&canT9);

    delay();

    /*Wait till all transmitted frames received*/
    while((rcv_msg_frms2 < 5) && (rcv_msg_frms0 < 5))
	{
	}

	canR5.can_buffer = &swobjdum[5] ;  /*Application provided data buffers to read data*/	 
	canR5.CAN_trans_ucb = rx_ucb ;     /*Application provided user callback function*/	 
	CAN_Read_Dev(2,&canR5);
	canR6.can_buffer = &swobjdum[6] ;
	canR6.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(2,&canR6);
	canR7.can_buffer = &swobjdum[7] ;  
	canR7.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(2,&canR7);
	canR8.can_buffer = &swobjdum[8] ;  
	canR8.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(2,&canR8);
	canR9.can_buffer = &swobjdum[9] ;  
	canR9.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(2,&canR9);

	canR.can_buffer = &swobjdum[0] ;  
	canR.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(0,&canR);
	canR1.can_buffer = &swobjdum[1] ; 
	canR1.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(0,&canR1);
	canR2.can_buffer = &swobjdum[2] ; 
	canR2.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(0,&canR2);
	canR3.can_buffer = &swobjdum[3] ; 
	canR3.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(0,&canR3);
	canR4.can_buffer = &swobjdum[4] ; 
	canR4.CAN_trans_ucb = rx_ucb ;
	CAN_Read_Dev(0,&canR4);

   	while(1)
   	{
   	}

}


volatile unsigned int cx = 0;
void delay(void)
{
    volatile int cc = 0;
    cx = 0;
    for (cc = 0 ; cc < 5 ; cc++)
    {
      for (cx = 0; cx < 0xFFFFF ; cx++);
    }
}

IFX_UINT32 tx_s = 0, tx_f = 0, rx_s = 0, rx_f = 0;

void rx_ucb(struct can_trans *t, CAN_STATUS s)
{
  if(s == CAN_SUCCESS)
  {
    rx_s++;
  }
  else
  {
    rx_f++;
  }
}

void tx_ucb(struct can_trans *t, CAN_STATUS s)
{
  if(s == CAN_SUCCESS)
  {
    tx_s++;
  }
  else
  {
    tx_f++;
  }
}


void rcv_ucb0(void)
{
  rcv_msg_frms0++;
}

void rcv_ucb2(void)
{
  rcv_msg_frms2++;
}


#elif (TEST_CASE == 1)
#include "CAN_IDL.h"
#include "SYS_API.H"					 
#include "COMPILER.h"
#include "CAN_API.h"


/*
  swobj --> Used for TX message objects
  swobjdum --> Used for RX message objects
*/
CAN_MESSAGE_OBJECT swobj[1], swobjdum[1] ;

/*
  canTx --> Used for RX and TX transfer message objects.
*/
CAN_TRANSFER canT, canT1, canT2 ;

IFX_VUINT8 rcv_msg_frms0 = 0;
void rcv_ucb0(void);
IFX_VUINT32 rcv_pkts = 0;

void main(void)
{
	IFX_UINT8 i = 0 ;
	IFX_UINT32 temp = 0;
    CAN_COM_PARMS can_init_parms ;	 
	NBTR          baud_change;

    SYS_clk_initialise(); /*Initialise system clock*/

	/*Init the CAN Mode structure*/
	can_init_parms.can_mode.Loop_Back = 0 ;

	/*Node NBTR*/
	can_init_parms.can_bit_timing.Baud_Prescaler = 0 ;
	can_init_parms.can_bit_timing.Divider_Mode = 0 ;
	can_init_parms.can_bit_timing.Sync_Jump = 1;
	can_init_parms.can_bit_timing.Timing_Seg1 = 3 ;
	can_init_parms.can_bit_timing.Timing_Seg2 = 2 ;


	/**Error Counts*/
	can_init_parms.can_error_counter.Receive_Count = 0 ;
	can_init_parms.can_error_counter.Transmit_Count = 0 ;
	can_init_parms.can_error_counter.Warn_Level = 91 ;

    /***/
   	can_init_parms.can_frame_counter.Count_value = 0 ;
   	can_init_parms.can_frame_counter.Frame_Count_mode = 0 ; 
   	can_init_parms.can_frame_counter.Frame_Count_select = 7 ;

    CAN_Initialise_dev(0, &can_init_parms) ;

    ENABLE_GLOBAL_INTERRUPT() ;

	
	for(i = 0 ; i < 1 ; i++)
	{
		swobj[i].Data[0] = 0 ;
		swobj[i].Data[1] = 0;
		swobj[i].Data[2] = 0;
		swobj[i].Data[3] = 0;
		swobj[i].Data[4] = 0;
		swobj[i].Data[5] = 0;
		swobj[i].Data[6] = 0;
		swobj[i].Data[7] = 0;
		swobj[i].Mask	 = 0x1FFFFFFF ;
		swobj[i].ID 	 = 0x15555554 ; //extended identifier
		swobj[i].MOCfg	 = 0x0084 ;  //extended identifier  
	}
	
	canT.can_buffer_size = 1 ;
	canT.can_buffer = &swobj[0] ;	 

	//configure message object for recieve
    if (CAN_Ctrl_config_Rcvbuffer(0, &canT ) != CAN_SUCCESS) 
 	{
      return;
	}


    /*Register user call back with LLD to receive a notification when LLD
    receives a message frame*/
    CAN_Control_dev(0, CAN_CTRL_REG_RCV_UCB, &rcv_ucb0);

    CAN_Control_dev(0, CAN_CTRL_DISABLE, 0);

	/*The message buffer's Acceptance masks need to be configured properly 
   	in order to rcv the message correctly*/
    for(i=0; i<1; i++)
	{
	  swobjdum[i].Data[0] =  0 ;
	  swobjdum[i].Data[1] =  0 ;
	  swobjdum[i].Data[2] =  0 ;
	  swobjdum[i].Data[3] =  0 ;
	  swobjdum[i].Data[4] =  0 ;
	  swobjdum[i].Data[5] =  0 ;
	  swobjdum[i].Data[6] =  0 ;
	  swobjdum[i].Data[7] =  0 ;
	}

   	for(i = 0 ; i < 1 ; i++)
	{
		swobj[i].Data[0] = 0x1 ;
		swobj[i].Data[1] = 0x2 ;
		swobj[i].Data[2] = 0x3 ;
		swobj[i].Data[3] = 0x4 ;
		swobj[i].Data[4] = 0x5 ;
		swobj[i].Data[5] = 0x6 ;
		swobj[i].Data[6] = 0x7 ;
		swobj[i].Data[7] = 0x8 ;
		swobj[i].Mask	 = 0x1FFFFFFF ;
		swobj[i].ID 	 = 0x15555554 ; //extended identifier
		swobj[i].MOCfg	 = 0x0084 ;  //extended identifier  
	}


    CAN_Control_dev(0, CAN_CTRL_ENABLE, 0);

    baud_change.Baud_Prescaler = 0;
	baud_change.Sync_Jump      = 1;
	baud_change.Divider_Mode   = 0;
	baud_change.Timing_Seg1    = 6;
	baud_change.Timing_Seg2    = 7;
	CAN_Control_dev(0, CAN_CTRL_TRNS_BIT, &baud_change);

	canT1.can_buffer = &swobjdum[0] ;	 
	canT1.CAN_trans_ucb = 0x00000000 ;
	canT2.can_buffer = &swobj[0] ;	 
	canT2.CAN_trans_ucb = 0x00000000 ;


    while(1)
	{
      while(rcv_msg_frms0 <= 0)
	  {
	  }
	  rcv_msg_frms0 = 0;

      if(rcv_pkts == 100)
	  {
        temp = 0;
        CAN_Control_dev(0, CAN_CTRL_TRNS_NODE_EWRN_LVL, &temp);
        temp = 0;
        CAN_Control_dev(0, CAN_CTRL_NODE_FRAME_COUNT_COUNTER_VALUE, &temp);
	  }

  	  CAN_Read_Dev(0,&canT1);
      CAN_Write_Dev(0,&canT2);
	  rcv_pkts++;
	}
}

void rcv_ucb0(void)
{
 rcv_msg_frms0++; 
}
#elif (TEST_CASE == 2)
#include "COMPILER.h"
#include "CAN_CFG.h"
#include "CAN_IDL.h"
#include "CAN_IIL.h"
#include "CAN_API.h"

CAN_MESSAGE_OBJECT swobj[10], swobjdum[10] ;
CAN_TRANSFER canT, canT1, canT2, canT3, canT4 ;
CAN_TRANSFER canR, canR1, canR2, canR3, canR4 ;
CAN_TRANSFER canR5, canR6, canR7, canR8, canR9 ;


void delay(void);
void rx_ucb(struct can_trans *t, CAN_STATUS s);
void tx_ucb(struct can_trans *t, CAN_STATUS s);

void main(void)
{
	IFX_UINT8 i = 0 ;
    CAN_COM_PARMS can_init_parms ;
    CAN_STATUS    status;	 


    /*Initialise global system clock frequency*/
    SYS_clk_initialise();

	/*Init the CAN Mode structure*/
    /*Device is initialised in loop back mode*/
	can_init_parms.can_mode.Loop_Back = 1 ; 

	/*Baud rate control configuration parameters*/
	can_init_parms.can_bit_timing.Baud_Prescaler = 0 ;
	can_init_parms.can_bit_timing.Divider_Mode = 0 ;
	can_init_parms.can_bit_timing.Sync_Jump = 1;
	can_init_parms.can_bit_timing.Timing_Seg1 = 3 ;
	can_init_parms.can_bit_timing.Timing_Seg2 = 2 ;

	/*Error counters control configuration parameters*/
	can_init_parms.can_error_counter.Receive_Count = 0 ;
	can_init_parms.can_error_counter.Transmit_Count = 0 ;
	can_init_parms.can_error_counter.Warn_Level = 91 ;
    
	/*Frame counter control configuration parameters*/
   	can_init_parms.can_frame_counter.Count_value = 0 ;
   	can_init_parms.can_frame_counter.Frame_Count_mode = 0 ; /*Frmae count mode*/
   	can_init_parms.can_frame_counter.Frame_Count_select = 7 ;

    /*Initialise Node2 and Node3 in loopback mode*/ 
	CAN_Initialise_dev(3, &can_init_parms) ;
    CAN_Initialise_dev(2, &can_init_parms) ;

	can_init_parms.can_mode.Loop_Back = 0 ; /*Non loop back*/

    /*Initialise Node1 and Node0 in non loopback mode*/ 
    CAN_Initialise_dev(1, &can_init_parms) ;
    CAN_Initialise_dev(0, &can_init_parms) ;

    /*Enable interrupts globally*/
    ENABLE_GLOBAL_INTERRUPT() ;

    /*Reset all application receive data buffers*/
    for(i=0;i<10;i++)
	{
	  swobjdum[i].Data[0] =  0 ;
	  swobjdum[i].Data[1] =  0 ;
	  swobjdum[i].Data[2] =  0 ;
	  swobjdum[i].Data[3] =  0 ;
	  swobjdum[i].Data[4] =  0 ;
	  swobjdum[i].Data[5] =  0 ;
	  swobjdum[i].Data[6] =  0 ;
	  swobjdum[i].Data[7] =  0 ;
	}
	
	for(i = 0 ; i < 5 ; i++)
	{
		swobj[i].Data[0] = 0 ;
		swobj[i].Data[1] = 0;
		swobj[i].Data[2] = 0;
		swobj[i].Data[3] = 0;
		swobj[i].Data[4] = 0;
		swobj[i].Data[5] = 0;
		swobj[i].Data[6] = 0;
		swobj[i].Data[7] = 0;
		swobj[i].Mask	 = 0x1FFFFFFF ;
		swobj[i].ID 	 = 0x15555554 + i ; //extended message frame identifier
		swobj[i].MOCfg	 = 0x0084 ;  //extended message frame
	}
	
	canT.can_buffer_size = 5 ; /*Number of message objects to be configured*/
	canT.can_buffer = &swobj[0] ;  /*Adress of application specified first message object*/	 
	
    /*configure message object for recieve for node2*/
	if (CAN_Ctrl_config_Rcvbuffer( 2, &canT ) != CAN_SUCCESS) 
 	{
      return;
	}
  
    /*configure message object for recieve for node0*/
    if (CAN_Ctrl_config_Rcvbuffer( 0, &canT ) != CAN_SUCCESS)
 	{
      return;
	}


	/*Create a gateway between node2 and node1. Node2 message objects 
	  as source and node1 message objects as destination objects*/
    for(i = 0 ; i < 5; i++)
	{
  	  swobj[i].Mofcr.Data_Copy = 1;   /*data copied from source object to destination object*/
	  swobj[i].Mofcr.Data_Frame_Send = 1; /*TXRQ is set in destination object*/
	  swobj[i].Mofcr.DLC_Copy = 1; /*number of data bytes copied from source object to destination object*/
	  swobj[i].Mofcr.ID_Copy = 1;  /*Message object ID copied from source object to destination object*/
	  swobj[i].Mofgpr.CUR = 10 + i; /*Destination object number*/
	  swobj[i].MoNum = 25 + i;		/*Source object number*/
      if(CAN_Control_dev(2, CAN_CTRL_TRNS_GATEWAY, &swobj[i]) != CAN_SUCCESS)
      {
	    return;
      }
	}

	/*Configure application transmit data buffers*/ 
   	for(i = 0 ; i < 5 ; i++)
	{
		swobj[i].Data[0] = 0x11 + i;
		swobj[i].Data[1] = 0x22 + i;
		swobj[i].Data[2] = 0x33 + i;
		swobj[i].Data[3] = 0x44 + i;
		swobj[i].Data[4] = 0x55 + i;
		swobj[i].Data[5] = 0x66 + i;
		swobj[i].Data[6] = 0x77 + i;
		swobj[i].Data[7] = 0x88 + i;
		swobj[i].Mask	 = 0x1FFFFFFF ;

		swobj[i].ID 	 = 0x15555554 + i; //extended message object identifier
		swobj[i].MOCfg	 = 0x0084 ;  //extended identifier  
	}

    
	
	canR.can_buffer    = &swobjdum[0] ; /*Application provided data buffers to read data*/	 
	canR.CAN_trans_ucb = rx_ucb ;       /*Application provided user callback function*/	 
	status = CAN_Read_Dev(2,&canR);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR1.can_buffer = &swobjdum[1] ;
	canR1.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(2,&canR1);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR2.can_buffer = &swobjdum[2] ;
	canR2.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(2,&canR2);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR3.can_buffer = &swobjdum[3] ;
	canR3.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(2,&canR3);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR4.can_buffer = &swobjdum[4] ;
	canR4.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(2,&canR4);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));


	canT.can_buffer    = &swobj[0] ; /*Application provided data buffers to send data*/	 
	canT.CAN_trans_ucb = tx_ucb ;    /*Application provided user callback function*/	 
	status = CAN_Write_Dev(3,&canT);
	if(	(status == CAN_SUCCESS) || (status == CAN_WRITE_DATA));
	canT1.can_buffer = &swobj[1] ; 
	canT1.CAN_trans_ucb = tx_ucb ;
	status = CAN_Write_Dev(3,&canT1);
	if(	(status == CAN_SUCCESS) || (status == CAN_WRITE_DATA));
	canT2.can_buffer = &swobj[2] ; 
	canT2.CAN_trans_ucb = tx_ucb ;
	status = CAN_Write_Dev(3,&canT2);
	if(	(status == CAN_SUCCESS) || (status == CAN_WRITE_DATA));
	canT3.can_buffer = &swobj[3] ; 
	canT3.CAN_trans_ucb = tx_ucb ;
	status = CAN_Write_Dev(3,&canT3);
	if(	(status == CAN_SUCCESS) || (status == CAN_WRITE_DATA));
	canT4.can_buffer = &swobj[4] ; 
	canT4.CAN_trans_ucb = tx_ucb ;
	status = CAN_Write_Dev(3,&canT4);
	if(	(status == CAN_SUCCESS) || (status == CAN_WRITE_DATA));

	canR5.can_buffer = &swobjdum[5] ; 
	canR5.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(0,&canR5);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR6.can_buffer = &swobjdum[6] ; 
	canR6.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(0,&canR6);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR7.can_buffer = &swobjdum[7] ; 
	canR7.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(0,&canR7);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR8.can_buffer = &swobjdum[8] ; 
	canR8.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(0,&canR8);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));
	canR9.can_buffer = &swobjdum[9] ; 
	canR9.CAN_trans_ucb = rx_ucb ; 
	status = CAN_Read_Dev(0,&canR9);
	if((status == CAN_SUCCESS ) || (status == CAN_READ_DATA));

    while(1)
    {
    }

}


volatile unsigned int cx = 0;
void delay(void)
{
    volatile int cc = 0;
    cx = 0;
    for (cc = 0 ; cc < 5 ; cc++)
    {
      for (cx = 0; cx < 0xFFFFF ; cx++);
    }
}

IFX_UINT32 tx_s = 0, tx_f = 0, rx_s = 0, rx_f = 0;

void rx_ucb(struct can_trans *t, CAN_STATUS s)
{
  if(s == CAN_SUCCESS)
  {
    rx_s++;
  }
  else
  {
    rx_f++;
  }
}

void tx_ucb(struct can_trans *t, CAN_STATUS s)
{
  if(s == CAN_SUCCESS)
  {
    tx_s++;
  }
  else
  {
    tx_f++;
  }
}

#endif

