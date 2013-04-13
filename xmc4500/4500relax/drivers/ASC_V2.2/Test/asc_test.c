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
** @FILENAME@:       ASC_TEST.c
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: Test cases
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      Bhavjit Walha        Release after code review.
** 07/05/2004      Mahesh S 			Test file improved to add more test
**                                      cases
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

/*
  Test procedure:
  Total 2 test cases available ranges from 0 to 1, to execute
  particul test case equate TEST_CASE define value with desired value.

  Test case 0:
    Open PC hyper terminal (Start->programs->Accessories->communications->
    hyper terminal)
    Set the following configuration to hyper terminal.

      Select port and configure the following values.
        baud rate  : 38400
        data bits  : 8
        parity     : None 
        stop bits  : 1 

	  Hyper terminal-> File->properties->Settings->ASCII setup
	    Select 'echo typed characters locally' check box.

     Connect ASC0 to PC->COM port.
     Downlaod image to triboard and start debug.
     Wecome message appear on hyper terminal and asking to enter 20 characters.
     As soon as 20 characters are typed on hyper terminal same will be dispayed 
     and program exits.

  Test case 1:  
    This test case will test ASC0 and ASC1 for 9 bit data.
	Cross connect ASC0 and ASC1 receive and transmit pins.
	Data sent from ASC0 received by ASC1 and vice versa.

    Following are T2LA board extension configuration. 

              ASC0                  ASC1
    RX	    802/X4.5              802/X2.5

    TX 		802/X4.3               802/X2.3  

   Received data can be observed in buffer_tx2 and buffer_tx4.
*/
#ifndef TEST_CASE
#define TEST_CASE 0
#endif

#if (TEST_CASE == 0)
#include "compiler.h"
#include "asc_cfg.h"
#include "asc_idl.h"
#include "asc_iil.h"
#include "sys_cfg.h"
#include "asc_api.h"
#include <stdio.h> /*test*/

void asc_hal_ucb( ASC_TRANSFER *trans_struct, ASC_STATUS stat );

void asc_hal_ucb_rx( ASC_TRANSFER *trans_struct, ASC_STATUS stat );

unsigned int  flag2 = 0, flag1 = 0;

unsigned char buffer_tx1[100]  = "\r\nWelcome to ASC LLD ...!  Please enter data [20 characters]\r\n";
unsigned char buffer_tx2[100]  = "";
unsigned char buffer_tx3[100]  = "\r\nEntered data ..\r\n";
unsigned char buffer_tx4[100]  = "\r\nGood bye ...!";

ASC_TRANSFER transfer_tx1, transfer_tx2, transfer_tx3, transfer_tx4;

int main()
{
  ASC_COM_PARMS parms;
  IFX_UINT32    i = 0xFFFFF;   

  SYS_clk_initialise(); /*Initialise the system clock to 95MHZ*/

  /* Iniatialization parameters */
  parms.ASC_com_data =   ASC_DATA_8;
  parms.ASC_com_stop = ASC_STOP_1;
  parms.ASC_com_parity = ASC_PARITY_NONE;
  parms.ASC_mode = ASC_ASYNC;
  parms.ASC_com_baud = 38400;
  
  /* Setting the transfer ( read or write ) buffer characteristics */
  transfer_tx1.ASC_buffer = (IFX_UINT8 *) &buffer_tx1[0];
  transfer_tx1.ASC_buffer_size = 62;
  transfer_tx1.ASC_transfer_mode = SYS_TRNS_MCU_INT;
  transfer_tx1.ASC_trans_ucb = NULL;    

  transfer_tx2.ASC_buffer = (IFX_UINT8 *) &buffer_tx2[0];
  transfer_tx2.ASC_buffer_size = 20;
  transfer_tx2.ASC_transfer_mode = SYS_TRNS_MCU_INT;
  transfer_tx2.ASC_trans_ucb = NULL;    

  /* Initialize the device */
  if(ASC_initialise_dev(0, &parms ) != ASC_SUCCESS)
  {
    printf("error\n");
    return 0;
  }

  ASC_write(0, &transfer_tx1);
  ASC_read(0, &transfer_tx2);
  transfer_tx1.ASC_buffer = (IFX_UINT8 *) &buffer_tx3[0];
  transfer_tx1.ASC_buffer_size = 19;
  ASC_write(0, &transfer_tx1);
  transfer_tx1.ASC_buffer = (IFX_UINT8 *) &buffer_tx2[0];
  transfer_tx1.ASC_buffer_size = 20;
  ASC_write(0, &transfer_tx1);
  transfer_tx1.ASC_buffer = (IFX_UINT8 *) &buffer_tx4[0];
  transfer_tx1.ASC_buffer_size = 15;
  ASC_write(0, &transfer_tx1);

  while(1)
  {
  }
 return 0;
}



void asc_hal_ucb( ASC_TRANSFER *trans_struct, ASC_STATUS stat )
{
} 

void asc_hal_ucb_rx( ASC_TRANSFER *trans_struct, ASC_STATUS stat )
{
  flag1++;
} 

#elif (TEST_CASE == 1)
#include "compiler.h"
#include "asc_cfg.h"
#include "asc_idl.h"
#include "asc_iil.h"
#include "sys_cfg.h"
#include "asc_api.h"
#include <stdio.h> /*test*/

void asc_hal_ucb( ASC_TRANSFER *trans_struct, ASC_STATUS stat );

void asc_hal_ucb_rx( ASC_TRANSFER *trans_struct, ASC_STATUS stat );

volatile unsigned int  flag2 = 0, flag1 = 0;

unsigned short buffer_tx1[100]  = {0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111,0x111};
unsigned short buffer_tx2[100] = {0};
unsigned short buffer_tx3[100]  = {0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122,0x122};
unsigned short buffer_tx4[100] = {0};

ASC_TRANSFER transfer_tx1, transfer_tx2, transfer_tx3, transfer_tx4;

int main()
{
  ASC_COM_PARMS parms;
  IFX_UINT32    i = 0xFFFFF;   

  SYS_clk_initialise(); /*Initialise the system clock to 95MHZ*/

  /* Iniatialization parameters */
  parms.ASC_com_data =   ASC_DATA_9;
  parms.ASC_com_stop = ASC_STOP_1;
  parms.ASC_com_parity = ASC_PARITY_NONE;
  parms.ASC_mode = ASC_ASYNC;
  parms.ASC_com_baud = 38400;
  
  /* Setting the transfer ( read or write ) buffer characteristics */
  transfer_tx1.ASC_buffer = (IFX_UINT8 *) &buffer_tx1[0];
  transfer_tx1.ASC_buffer_size = 72;
  transfer_tx1.ASC_transfer_mode = SYS_TRNS_MCU_INT;
  transfer_tx1.ASC_trans_ucb = asc_hal_ucb;

  transfer_tx2.ASC_buffer = (IFX_UINT8 *) &buffer_tx2[0];
  transfer_tx2.ASC_buffer_size = 72;
  transfer_tx2.ASC_transfer_mode = SYS_TRNS_MCU_INT; 
  transfer_tx2.ASC_trans_ucb = asc_hal_ucb_rx;

  transfer_tx3.ASC_buffer = (IFX_UINT8 *) &buffer_tx3[0];
  transfer_tx3.ASC_buffer_size = 72;
  transfer_tx3.ASC_transfer_mode = SYS_TRNS_MCU_INT; 
  transfer_tx3.ASC_trans_ucb = asc_hal_ucb;

  transfer_tx4.ASC_buffer = (IFX_UINT8 *) &buffer_tx4[0];
  transfer_tx4.ASC_buffer_size = 72;
  transfer_tx4.ASC_transfer_mode = SYS_TRNS_MCU_INT; 
  transfer_tx4.ASC_trans_ucb = asc_hal_ucb_rx;

  /* Initialize the device */
  if(ASC_initialise_dev(0, &parms ) != ASC_SUCCESS)
  {
    printf("error\n");
    return 0;
  }

  /* Initialize the device */
  if(ASC_initialise_dev(1, &parms ) != ASC_SUCCESS)
  {
    printf("error\n");
    return 0;
  }

  ASC_read(0, &transfer_tx2);
  ASC_write(1, &transfer_tx1);
  ASC_read(1, &transfer_tx4);
  ASC_write(0, &transfer_tx3);

  while(1)
  {
  }
}

void asc_hal_ucb( ASC_TRANSFER *trans_struct, ASC_STATUS stat )
{
  flag2++;
} 

void asc_hal_ucb_rx( ASC_TRANSFER *trans_struct, ASC_STATUS stat )
{
  flag1++;
} 
#endif
