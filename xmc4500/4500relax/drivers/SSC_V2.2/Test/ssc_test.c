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
** @FILENAME@:       ssc_test.c
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: Initialise device and start transmission. After some delay stop the
**           transmission by aborting device. Then start transmission at end
**           read all status flags for verification. All aborted transmissions
**           will return SSC_ERR.   
**
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
  Test procedure
  This test file has 3 test cases ranges from 0 to 2. To execute particular 
  test case equate TEST_CASE define value with desired value.

  Note:
    TC1130-A does not support delays and FIFOs.
    To remove the LLD support for FIFOS equate the following macros to zero value
    in SSC_IDl.h file.
	  SSC_HW_FIFO_RX
	  SSC_HW_FIFO_TX  

	To remove the LLD support for delays equate the following macro to zero value
    in SSC_IDl.h file.
      SSC_HW_DEL_SUP

  Test case 0:
    Test carried between SSC0 and SSC1 for 8 bit data.
    Data sent from SSC0 received in SSC1 and vice versa.
  
    Connect SSC0 and SSC1 MRST, MTSR and CLK signals. 

                 MRST               MTSR             CLK   
    SSC0	 802/67  x3.9		 802/65  x3.11   802/63  x3.13

    SSC1	 802/68  x1.9		 802/66  x1.11   802/64  x1.13

    x1, x3 are T2LA board signals.

    SSC0 and SSC1 are initialised to 38.4k baud rate, SSC0 as master and SSC1 as
    slave.

    SSC0 and SSC1 start transmission and after some delay both SSC0 and SSC1 are
    aborted.
    
    After soem delay again they start transmission.
    
    At end observe data in buffer_rx1, buffer_rx2, buffer_rx3 and buffer_rx4
    buffers and read stat1 and stat2 variables to find the status. 
  

  Test case 1:
    Test carried between SSC0 and SSC1 for 16 bit data.
    Data sent from SSC0 received in SSC1 and vice versa.
  
    Connect SSC0 and SSC1 MRST, MTSR and CLK signals. 

                 MRST               MTSR             CLK   
    SSC0	 802/67  x3.9		 802/65  x3.11   802/63  x3.13

    SSC1	 802/68  x1.9		 802/66  x1.11   802/64  x1.13

    x1, x3 are T2LA board signals.

    SSC0 and SSC1 are initialised to 38.4k baud rate, SSC0 as master and SSC1 as
    slave.

    SSC0 and SSC1 start transmission and after some delay both SSC0 and SSC1 are
    terminated and re-initialized.
    
    SSC0 and SSC1 start transmission after re-initialization.
    
    At end observe data in buffer_rx1, buffer_rx2, buffer_rx3 and buffer_rx4
    buffers and read stat1 and stat2 variables to find the status. 


  Test case 2:

    Test carried between SSC0 and SSC1 for 8 bit data in slave select mode.
    Data sent from SSC0 received in SSC1 and vice versa.
  
    Master and slave transmit less data compared to expected receive data.
	Master transmits user configured data(SSC_CFG_DUMMY_DATA) in 
	SSC_CFG.H file when it want to read data without transmit data. 

	Slave transmits user configured data(SSC_CFG_DUMMY_DATA) in 
	SSC_CFG.H file when either it receive data from master or read 
	data when no transmit data. This only when 'SSC_CFG_SLAVE_DUMMY_DAT'
	define value is 1 and value of 'SSC_CFG_DUMMY_DATA' not equal to -1.

    Connect SSC0 and SSC1 MRST, MTSR and CLK signals. 

                 MRST               MTSR             CLK   
    SSC0	 802/67  x3.9		 802/65  x3.11   802/63  x3.13

    SSC1	 802/68  x1.9		 802/66  x1.11   802/64  x1.13

    x1, x3 are T2LA board signals.

    SSC0 and SSC1 are initialised to 38.4k baud rate, SSC0 as master and SSC1 as
    slave.

    SSC0 selects SLSO7 ans SSC1 selects SLSI line, connect SLSO7 and SLSI, by 
    using run time control API.

    SLSO7 804/45   x6.9
	SLSI  801/78   x10.11

    SSC0 and SSC1 start transmission.    
    
    At end observe data in buffer_rx1 and buffer_rx2. 
*/


#ifndef TEST_CASE
#define TEST_CASE 0
#endif

#if (TEST_CASE == 0)

#include "compiler.h"
#include "ssc_cfg.h"
#include "ssc_api.h"
#include "ssc_idl.h"
#include "ssc_iil.h"
#include "sys_api.h"
#include "sys_cfg.h"
#include <stdio.h> /* =========== for debugging only ========= */


IFX_UINT8 flag1 = 0, flag2 = 0, flag3 = 0;

void ssc_hal_ucb_tx( SSC_TRANSFER *trans_struct, SSC_STATUS stat )
{
  if(stat == SSC_SUCCESS)
  {
    flag1++;
  }
}

void ssc_hal_ucb_rx( SSC_TRANSFER *trans_struct, SSC_STATUS stat )
{
  if(stat == SSC_SUCCESS)
  {
    flag2++;
  }
}

unsigned char buffer_tx1[120] = "555555555555555555555555555555555555555555555555555555555555555555555555";
unsigned char buffer_tx2[120] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst";
unsigned char buffer_rx1[120] = {0};
unsigned char buffer_rx2[120] = {0};

unsigned char buffer_tx3[120] = "123456789012345678901234567890123456789012345678901234567890123456789012";
unsigned char buffer_tx4[120] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst";
unsigned char buffer_rx3[120] = {0};
unsigned char buffer_rx4[120] = {0};

SSC_TRANSFER transfer_tx1,transfer_tx2, transfer_rx1, transfer_rx2;
SSC_TRANSFER transfer_tx3,transfer_tx4, transfer_rx3, transfer_rx4;

SSC_STAT_INF stat1, stat2;

int main()
{
	SSC_COM_PARMS parms1, parms2;
	IFX_VUINT32 i = 0xffffff;

	// MASTER SSC0 
	parms1.SSC_com_baud = 38400;
	parms1.SSC_com_clock = SSC_CLOCK_IDLE_LOW;
	parms1.SSC_com_data = 8;	   // data width
	parms1.SSC_com_phase = SSC_LATCH_FALLING;
	parms1.SSC_com_shift = SSC_LSB_FIRST;
	parms1.SSC_mode = SSC_MASTER;
	parms1.SSC_slave_num = 0;

	// SLAVE  SSC1
	parms2.SSC_com_baud = 38400;
	parms2.SSC_com_clock = SSC_CLOCK_IDLE_LOW;
	parms2.SSC_com_data = 8;        // Data width
	parms2.SSC_com_phase = SSC_LATCH_FALLING;
	parms2.SSC_com_shift = SSC_LSB_FIRST;
	parms2.SSC_mode = SSC_SLAVE;
	parms2.SSC_slave_num = 0;

	transfer_tx1.SSC_buffer = (IFX_UINT32 *) &buffer_tx1;
	transfer_tx1.SSC_buffer_size = 72;
	transfer_tx1.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx1.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_tx2.SSC_buffer = (IFX_UINT32 *) &buffer_tx2;
	transfer_tx2.SSC_buffer_size = 72;
	transfer_tx2.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx2.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_rx1.SSC_buffer = (IFX_UINT32 *) &buffer_rx1;
	transfer_rx1.SSC_buffer_size = 72;
	transfer_rx1.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx1.SSC_trans_ucb = ssc_hal_ucb_rx;

	transfer_rx2.SSC_buffer = (IFX_UINT32 *) &buffer_rx2;
	transfer_rx2.SSC_buffer_size = 72;
	transfer_rx2.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx2.SSC_trans_ucb = ssc_hal_ucb_rx;
	
	if(SSC_initialise_dev(0, &parms1) != SSC_SUCCESS)
	{
	  printf("Fail0\n");
	  return 0;
	}
	
	if(SSC_initialise_dev(1, &parms2) != SSC_SUCCESS)
	{
	  printf("Fail1\n");
	  return 0;
	}

	SSC_read(1, &transfer_rx2);
    SSC_write(1, &transfer_tx2);
	SSC_read(0, &transfer_rx1);
    SSC_write(0, &transfer_tx1);

    i = 0xffffff; /*Sufficeint delay to complete all transfers, flag1 = 4, flag2 = 4*/

    for(;i>0;i--)
	{
	}
	SSC_abort(0);
	SSC_abort(1);

    i = 0xffff;
    for(;i>0;i--)
	{
	}

	transfer_tx3.SSC_buffer = (IFX_UINT32 *) &buffer_tx3;
	transfer_tx3.SSC_buffer_size = 72;
	transfer_tx3.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx3.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_tx4.SSC_buffer = (IFX_UINT32 *) &buffer_tx4;
	transfer_tx4.SSC_buffer_size = 72;
	transfer_tx4.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx4.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_rx3.SSC_buffer = (IFX_UINT32 *) &buffer_rx3;
	transfer_rx3.SSC_buffer_size = 72;
	transfer_rx3.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx3.SSC_trans_ucb = ssc_hal_ucb_rx;

	transfer_rx4.SSC_buffer = (IFX_UINT32 *) &buffer_rx4;
	transfer_rx4.SSC_buffer_size = 72;
	transfer_rx4.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx4.SSC_trans_ucb = ssc_hal_ucb_rx;

	SSC_read(1, &transfer_rx4);
    SSC_write(1, &transfer_tx4);
	SSC_read(0, &transfer_rx3);
    SSC_write(0, &transfer_tx3);

    i = 0xfffff;
    for(;i>0;i--)
	{
	}

    SSC_status_dev(0, &stat1);
    SSC_status_dev(1, &stat2);
    while(1)
	{
	}
	return 0;
}

#elif (TEST_CASE == 1)
#include "compiler.h"
#include "ssc_cfg.h"
#include "ssc_api.h"
#include "ssc_idl.h"
#include "ssc_iil.h"
#include "sys_api.h"
#include "sys_cfg.h"
#include <stdio.h> /* =========== for debugging only ========= */


IFX_UINT8 flag1 = 0, flag2 = 0, flag3 = 0;

void ssc_hal_ucb_tx( SSC_TRANSFER *trans_struct, SSC_STATUS stat )
{
  if(stat == SSC_SUCCESS)
  {
    flag1++;
  }
}

void ssc_hal_ucb_rx( SSC_TRANSFER *trans_struct, SSC_STATUS stat )
{
  if(stat == SSC_SUCCESS)
  {
    flag2++;
  }
}

unsigned short buffer_tx1[120] = {0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111,0x1111};
unsigned short buffer_tx2[120] = {0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222,0x2222};
unsigned short buffer_rx1[120] = {0};
unsigned short buffer_rx2[120] = {0};

unsigned short buffer_tx3[120] = {0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333,0x3333};
unsigned short buffer_tx4[120] = {0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444,0x4444};
unsigned short buffer_rx3[120] = {0};
unsigned short buffer_rx4[120] = {0};

SSC_TRANSFER transfer_tx1,transfer_tx2, transfer_rx1, transfer_rx2;
SSC_TRANSFER transfer_tx3,transfer_tx4, transfer_rx3, transfer_rx4;

int main()
{
	SSC_COM_PARMS parms1, parms2;
	IFX_VUINT32 i = 0xffffff;

	// MASTER SSC0 
	parms1.SSC_com_baud = 38400;
	parms1.SSC_com_clock = SSC_CLOCK_IDLE_LOW;
	parms1.SSC_com_data = 16;	   // data width
	parms1.SSC_com_phase = SSC_LATCH_FALLING;
	parms1.SSC_com_shift = SSC_LSB_FIRST;
	parms1.SSC_mode = SSC_MASTER;
	parms1.SSC_slave_num = 0;

	// SLAVE  SSC1
	parms2.SSC_com_baud = 38400;
	parms2.SSC_com_clock = SSC_CLOCK_IDLE_LOW;
	parms2.SSC_com_data = 16;        // Data width
	parms2.SSC_com_phase = SSC_LATCH_FALLING;
	parms2.SSC_com_shift = SSC_LSB_FIRST;
	parms2.SSC_mode = SSC_SLAVE;
	parms2.SSC_slave_num = 0;

	transfer_tx1.SSC_buffer = (IFX_UINT32 *) &buffer_tx1;
	transfer_tx1.SSC_buffer_size = 72;
	transfer_tx1.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx1.SSC_trans_ucb = NULL;

	transfer_tx2.SSC_buffer = (IFX_UINT32 *) &buffer_tx2;
	transfer_tx2.SSC_buffer_size = 72;
	transfer_tx2.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx2.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_rx1.SSC_buffer = (IFX_UINT32 *) &buffer_rx1;
	transfer_rx1.SSC_buffer_size = 72;
	transfer_rx1.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx1.SSC_trans_ucb = ssc_hal_ucb_rx;

	transfer_rx2.SSC_buffer = (IFX_UINT32 *) &buffer_rx2;
	transfer_rx2.SSC_buffer_size = 72;
	transfer_rx2.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx2.SSC_trans_ucb = ssc_hal_ucb_rx;
	
	if(SSC_initialise_dev(0, &parms1) != SSC_SUCCESS)
	{
	  printf("Fail0\n");
	  return 0;
	}
	
	if(SSC_initialise_dev(1, &parms2) != SSC_SUCCESS)
	{
	  printf("Fail1\n");
	  return 0;
	}

	SSC_read(1, &transfer_rx2);
    SSC_write(1, &transfer_tx2);
	SSC_read(0, &transfer_rx1);
    SSC_write(0, &transfer_tx1);

    i = 0xffffff;

    for(;i>0;i--)
	{
	}
	SSC_terminate_dev(0);
	SSC_terminate_dev(1);

    i = 0xffff;
    for(;i>0;i--)
	{
	}

	if(SSC_initialise_dev(0, &parms1) != SSC_SUCCESS)
	{
	  printf("Fail0\n");
	  return 0;
	}
	
	if(SSC_initialise_dev(1, &parms2) != SSC_SUCCESS)
	{
	  printf("Fail1\n");
	  return 0;
	}

	transfer_tx3.SSC_buffer = (IFX_UINT32 *) &buffer_tx3;
	transfer_tx3.SSC_buffer_size = 72;
	transfer_tx3.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx3.SSC_trans_ucb = NULL;

	transfer_tx4.SSC_buffer = (IFX_UINT32 *) &buffer_tx4;
	transfer_tx4.SSC_buffer_size = 72;
	transfer_tx4.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx4.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_rx3.SSC_buffer = (IFX_UINT32 *) &buffer_rx3;
	transfer_rx3.SSC_buffer_size = 72;
	transfer_rx3.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx3.SSC_trans_ucb = ssc_hal_ucb_rx;

	transfer_rx4.SSC_buffer = (IFX_UINT32 *) &buffer_rx4;
	transfer_rx4.SSC_buffer_size = 72;
	transfer_rx4.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx4.SSC_trans_ucb = ssc_hal_ucb_rx;

	SSC_read(1, &transfer_rx4);
    SSC_write(1, &transfer_tx4);
	SSC_read(0, &transfer_rx3);
    SSC_write(0, &transfer_tx3);

    while(1)
	{
	}
	return 0;
}
#elif (TEST_CASE == 2)
#include "compiler.h"
#include "ssc_cfg.h"
#include "ssc_api.h"
#include "ssc_idl.h"
#include "ssc_iil.h"
#include "sys_api.h"
#include "sys_cfg.h"
#include <stdio.h> /* =========== for debugging only ========= */


IFX_UINT8 flag1 = 0, flag2 = 0, flag3 = 0;

void ssc_hal_ucb_tx( SSC_TRANSFER *trans_struct, SSC_STATUS stat )
{
  if(stat == SSC_SUCCESS)
  {
    flag1++;
  }
}

void ssc_hal_ucb_rx( SSC_TRANSFER *trans_struct, SSC_STATUS stat )
{
  if(stat == SSC_SUCCESS)
  {
    flag2++;
  }
}

unsigned char buffer_tx1[120] = "555555555555555555555555555555555555555555555555555555555555555555555555";
unsigned char buffer_tx2[120] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrst";
unsigned char buffer_rx1[120] = {0};
unsigned char buffer_rx2[120] = {0};

SSC_TRANSFER transfer_tx1,transfer_tx2, transfer_rx1, transfer_rx2;

int main()
{
	SSC_COM_PARMS parms1, parms2;
	IFX_VUINT32 i = 0xffffff;
	SSC_OSLAVE_OPT  SSC0_opt, SSC1_opt;

	// MASTER SSC0 
	parms1.SSC_com_baud = 38400;
	parms1.SSC_com_clock = SSC_CLOCK_IDLE_LOW;
	parms1.SSC_com_data = 8;	   // data width
	parms1.SSC_com_phase = SSC_LATCH_FALLING;
	parms1.SSC_com_shift = SSC_LSB_FIRST;
	parms1.SSC_mode = SSC_MASTER;
	parms1.SSC_slave_num = 0;

	// SLAVE  SSC1
	parms2.SSC_com_baud = 38400;
	parms2.SSC_com_clock = SSC_CLOCK_IDLE_LOW;
	parms2.SSC_com_data = 8;        // Data width
	parms2.SSC_com_phase = SSC_LATCH_FALLING;
	parms2.SSC_com_shift = SSC_LSB_FIRST;
	parms2.SSC_mode = SSC_SLAVE;
	parms2.SSC_slave_num = 0;

	transfer_tx1.SSC_buffer = (IFX_UINT32 *) &buffer_tx1;
	transfer_tx1.SSC_buffer_size = 70;
	transfer_tx1.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx1.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_tx2.SSC_buffer = (IFX_UINT32 *) &buffer_tx2;
	transfer_tx2.SSC_buffer_size = 68;
	transfer_tx2.SSC_transfer_mode = SYS_TRNS_MCU_INT; 
	transfer_tx2.SSC_trans_ucb = ssc_hal_ucb_tx;

	transfer_rx1.SSC_buffer = (IFX_UINT32 *) &buffer_rx1;
	transfer_rx1.SSC_buffer_size = 72;
	transfer_rx1.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx1.SSC_trans_ucb = ssc_hal_ucb_rx;

	transfer_rx2.SSC_buffer = (IFX_UINT32 *) &buffer_rx2;
	transfer_rx2.SSC_buffer_size = 72;
	transfer_rx2.SSC_transfer_mode = SYS_TRNS_MCU_INT;
	transfer_rx2.SSC_trans_ucb = ssc_hal_ucb_rx;
	
	if(SSC_initialise_dev(0, &parms1) != SSC_SUCCESS)
	{
	  printf("Fail0\n");
	  return 0;
	}
	
	if(SSC_initialise_dev(1, &parms2) != SSC_SUCCESS)
	{
	  printf("Fail1\n");
	  return 0;
	}

   SSC0_opt.SSC_delay     = 0;
   SSC0_opt.SSC_inact_dly = 0;
   SSC0_opt.SSC_lead_dly  = 0;
   SSC0_opt.SSC_line_logic_lvl = 0;
   SSC0_opt.SSC_slv_idl_lvl = 0;
   SSC0_opt.SSC_slv_num = 8;
   SSC0_opt.SSC_trl_dly = 0;

   SSC1_opt.SSC_delay     = 0;
   SSC1_opt.SSC_inact_dly = 0;
   SSC1_opt.SSC_lead_dly  = 0;
   SSC1_opt.SSC_line_logic_lvl = 0;
   SSC1_opt.SSC_slv_idl_lvl = 0;
   SSC1_opt.SSC_slv_num = 1;
   SSC1_opt.SSC_trl_dly = 0;

   SSC_ctrl_slv_oslct(0, SSC0_opt);
   SSC_ctrl_slv_oslct(1, SSC1_opt);
   
   SSC_read(1, &transfer_rx2);
   SSC_write(1, &transfer_tx2);
   SSC_read(0, &transfer_rx1);
   SSC_write(0, &transfer_tx1);

    while(1)
	{
	}
	return 0;
}

#endif
