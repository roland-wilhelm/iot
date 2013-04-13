CAN Release notes - Version 2.4 
-----------------------------------

1. CAN
   The required files are 

   The following files are in the Src directory
   CAN_API.H
   CAN_CFG.H
   CAN_IDL.H
   CAN_IIL.H
   CAN_IDL.c
   CAN_IIL.c  

   The following files are in the TC1130_LLD_V4.00\SYSTEM_V3.0 directory
   COMMON.H,
   COMPILER.H,
   SYS_API.H,
   SYS_CFG.H,
   SYS_IIL.c
   MAIN.H


   CAN_Test.c -- This file is used to test CAN driver. It is in the Test directory. 


  All the source files of the CAN LLD should be placed in the same directory of the 
  project space.

A Note on the test set up:
----------------------------------------------------------------------------------
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

        0			     0              CAN_CFG_TX_BUFFER_SIZE_NODE_0
        

        1           CAN_CFG_TX_BUFFER_SIZE_NODE_0   CAN_CFG_TX_BUFFER_SIZE_NODE_0   
			      + 				+
		    CAN_CFG_RX_BUFFER_SIZE_NODE_0   CAN_CFG_RX_BUFFER_SIZE_NODE_0
					                        +
												                                                        CAN_CFG_TX_BUFFER_SIZE_NODE_1



        2           CAN_CFG_TX_BUFFER_SIZE_NODE_0   CAN_CFG_TX_BUFFER_SIZE_NODE_0   
			      +					+
		    CAN_CFG_RX_BUFFER_SIZE_NODE_0   CAN_CFG_RX_BUFFER_SIZE_NODE_0
			      +                                 +
		    CAN_CFG_TX_BUFFER_SIZE_NODE_1   CAN_CFG_TX_BUFFER_SIZE_NODE_1
			      +					+
		    CAN_CFG_RX_BUFFER_SIZE_NODE_1   CAN_CFG_RX_BUFFER_SIZE_NODE_1
                                                                +  
													                                                    CAN_CFG_TX_BUFFER_SIZE_NODE_2

     The same procedure applies to node 3 also.