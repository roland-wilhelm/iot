/* =============================================================================
** Copyright (C) 2006 Infineon Technologies.
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
** @FILENAME@:       eth_main.C
** @VERSION@:        2.4
** @DATE@:           20/1/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: Sample application to test the Ethernet LLD. This program 
** illustrates the initialisation and use of the ethernet LLD to transmit ARP
** packets. The destination address and the packet data has been hardcoded in 
** this sample program. The trnsmit packet data may be changed to suit the users
** requirement. This program transmits 2000 ARP packets and then waits in an 
** infinite loop.
**
** =============================================================================
** References: ETH Design book
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Ruby
** 29/04/2004      Ruby                   Testing with Tasking
**
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
** 20/1/2006       Badarinath Jayashree   Version number bumped to 2.4 to match
**		           (IFIN CSW AIM)          the version of the C files
** @CHANGE_HISTORY@
** =============================================================================
*/

#include "eth_api.h"

#define ARP_PKT_LEN  64
#define ETH_MTU_SIZE 1500     

/* Number of frames which could not be transmitted by the DMUT*/
IFX_UINT32  tx_frames_dropped = 0;

/* Number of frames which were transmitted successfully */
IFX_UINT32  tx_frames = 0;

/* Number of packets that were received successfully */
IFX_UINT32  rx_packets= 0;

/* Data buffer where the rxed data will be copied into */
IFX_UINT8   rx_data[1500];

/* The "data" portion of the pkt to be transmitted */
IFX_UINT8   tx_pktdata[] = {0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00,
                            0x01, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55,
                            0xC0, 0xA8, 0x01, 0xEA, 0x00, 0x00, 0x00, 
                            0x00, 0x00, 0x00, 0xC0, 0xA8, 0x01, 0x02,
                            0x58, 0x51, 0x01, 0x00, 0x10, 0x0F, 0x00, 
                            0x00, 0xC4, 0x12, 0x00, 0x00, 0x07, 0x00,
                            0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
                            0x00};
/* The data buffer containing the tx pkt to be transmitted */
IFX_UINT8   tx_buf[ARP_PKT_LEN];

/* The receive callback function prototype */
void App_rx_cb(ETH_TRANSFER *rcv_frm);
/* The transmit callback function prototype */
void App_tx_cb(ETH_TRANSFER *sent_buff);	
/* A function to simulate a small delay */
void delay(int value);
/* This function performs a byte wise copy from source to dest */
void *copy(void *dest, const void *src, IFX_UINT32 len);

/*
   Main routine which will call the driver initialization routine.
   This routine only for testing purpose.
*/
int main()
{
  IFX_UINT32    i = 0;
  ETH_TRANSFER  ETH_transdata;
  ETH_COM_PARAMS ETH_params; 

#ifdef IFX_COMPILER_GNU
  IFX_INIT_ISR_VECTORS();
#endif

  if(ETH_initialise_dev(0,&ETH_params) != ETH_SUCCESS)  return ETH_ERR;
  ENABLE_GLOBAL_INTERRUPT();

#if 1
  ETH_reg_tx_cb(0,App_tx_cb);
  ETH_read(0,App_rx_cb);
#endif

/* Make a ethernet frame to transmit */
/* Store the destination address. Let the destination address be 00:08:A1:3E:9E:D5  */
  tx_buf[0] = 0x00;
  tx_buf[1] = 0x08;
  tx_buf[2] = 0xA1; 
  tx_buf[3] = 0x3E;
  tx_buf[4] = 0x9E;
  tx_buf[5] = 0xD5;
/* Store the source address. Let the source address be 00:08:00:0B:19:34 */ 
  tx_buf[6] = 0x00;
  tx_buf[7] = 0x08;
  tx_buf[8] = 0x00; 
  tx_buf[9] = 0x0B;
  tx_buf[10] = 0x19;
  tx_buf[11] = 0x34;

/* Store the protocol type. ARP in this case */
 tx_buf[12] = 0x08;
 tx_buf[13] = 0x06;

/* User data in the IP packet */
  copy(&tx_buf[14],tx_pktdata,50);      
//   ETH_HW_MACCTRL |= 0x8;

   /* Give a delay to allow autonegotiation to complete */
   delay(500000);
    
   if(ETH_check_link(0) == ETH_SUCCESS)
   {
#if 1
    /* Transmit the packet */ 
  for(i = 0; i < 200000; i++)
  {
    //if(i>=1000)
     ETH_transdata.ETH_buffer = tx_buf;
    ETH_transdata.ETH_buffer_size = ARP_PKT_LEN;
	if((ETH_write(0, &ETH_transdata)) != ETH_SUCCESS)
    {
      tx_frames_dropped++;
    }
  }
#endif
  
 }


  while(1);
  return 1;
} 

/* This function simulates a delay */
void delay(int value)
{
  int i;
  int x,y;
  x = 997;

  for(i = 0; i < value; i++)
  {
    y = x/8;
    x += 1;
    y = (y+x)/5;
    x = y/3;
  }
}

void App_rx_cb(ETH_TRANSFER *rcv_frm)
{
  IFX_UINT32 len;
  
  #if 1

  rx_packets++;

  len = (rcv_frm->ETH_buffer_size); 
  /* Check if we have received a complete frame.
  If so increment counter to update statistics.
  */
  if(rcv_frm->ETH_return_num.ETH_fe == 1)
  {
	copy(rx_data,rcv_frm->ETH_buffer,len);
  }
  #endif
}

void App_tx_cb(ETH_TRANSFER *sent_buff)
{
  tx_frames++;
}

void *copy(void *dest, const void *src, IFX_UINT32 len)
{ 
  IFX_UINT8 *dstp = (IFX_UINT8*)dest;
  IFX_UINT8 *srcp = (IFX_UINT8*) src; 
  IFX_UINT32 i;

  for (i = 0; i < len; ++i)
  {
    dstp[i] = srcp[i];
  }
  return dest;
} 
