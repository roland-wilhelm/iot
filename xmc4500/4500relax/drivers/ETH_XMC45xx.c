/*-----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *-----------------------------------------------------------------------------
 *      Name:    ETH_XMC45xx.C
 *      Purpose: Driver for Infineon XMC4500 Ethernet Controller
 *      Rev.:    V4.50
 *-----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2012 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <Net_Config.h>
#include <XMC4500.h>                    /* XMC4500 Definitions                */
#include "ETH_XMC45xx.h"
#include "uip_ao.h" // Import the Ethernet Event
#include <stdio.h>
#include <string.h>
/* The following macro definitions may be used to select the speed
   of the physical link:

  _10MBIT_   - connect at 10 MBit only
  _100MBIT_  - connect at 100 MBit only

  By default an autonegotiation of the link speed is used. This may take 
  longer to connect, but it works for 10MBit and 100MBit physical links.      */

/* Net_Config.c */
// extern U8 own_hw_adr[];
//Assigning Constant MAC Address
const unsigned char own_hw_adr[6] = {0xAA,0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

/* Local variables */
static U32 TxBufIndex;
static U32 RxBufIndex;
static U32 RxBufIndexReadFinish;
static U32 InterruptEntryCounter = 0; // Static default initialized, still
static U32 InterruptExitCounter = 0; // Static default initialized, still
static U32 Cycle,RxLenGlob = 0;
/* ETH local DMA Descriptors. */
static RX_Desc Rx_Desc[NUM_RX_BUF];
static TX_Desc Tx_Desc[NUM_TX_BUF];
static	U32 array[4];

static	U8 index = 0;

/* ETH local DMA buffers. */
static U32 rx_buf[NUM_RX_BUF][ETH_RX_BUF_SIZE>>2];
static U32 tx_buf[NUM_TX_BUF][ETH_TX_BUF_SIZE>>2];

/*-----------------------------------------------------------------------------
 *      ETH Ethernet Driver Functions
 *-----------------------------------------------------------------------------
 *  Required functions for Ethernet driver module:
 *  a. Polling mode: - void init_ethernet ()
 *                   - void send_frame (OS_FRAME *frame)
 *                   - void poll_ethernet (void)
 *  b. Interrupt mode: - void init_ethernet ()
 *                     - void send_frame (OS_FRAME *frame)
 *                     - void int_enable_eth ()
 *                     - void int_disable_eth ()
 *                     - interrupt function 
 *----------------------------------------------------------------------------*/

/* Local Function Prototypes */
static void rx_descr_init (void);
static void tx_descr_init (void);
//static void write_PHY (U32 PhyReg, U16 Value);
void write_PHY (U32 PhyReg, U16 Value);
//static U16  read_PHY (U32 PhyReg);
U16  read_PHY (U32 PhyReg);

// EMAC_Event ethEvent; // Instantinates eth event // Define own event
//static EMAC_Event emac, set this to receive since we only react only on receive
 static Ethernet_Event ethernet_event;// = ETHERNET_RECEIVE_SIG;			
 Ethernet_Event * eth_evtPtr = &ethernet_event;

//static EMAC_Event eth_evt = ETHERNET_RECEIVE_SIG;


// QF_poolInit(dynamicPoolEthernet, sizeof(dynamicPoolEthernet), sizeof(dynamicPoolEthernet[0]));
			
extern QActive * UipAO; // Opaque Ptr, just enough (7.6.)

/**
 * Active Object for Ethernet
 */
extern QActive * const ethernetAO;

// static struct EthernetRegisterSet registerSet = 0;

/*--------------------------- init_ethernet ----------------------------------*/

void init_ethernet (void) {
  /* Initialize the ETH ethernet controller. */
  U32 regv,tout,id1,id2;
	U32 PHYRegisterRead;

  /* Disable parity error and unaligned access trap. */
  SCU_PARITY->PETE = 0;
  PPB->CCR &= ~PPB_CCR_UNALIGN_TRP_Msk;

  /* Enable Clock for Ethernet MAC */
  SCU_CLK->CLKSET = SCU_CLK_CLKSET_ETH0CEN_Msk;

  /* Configure Ethernet Pins  */
  /* P2.0 [ETH_MDIO]  [HWI0]  */
  /* P2.2 [ETH_RXD0A] [Input] */
  /* P2.3 [ETH_RXD1A] [Input] */
  /* P2.7 [ETH_MDC]   [ALT1 ] */
  /* P2.8 [ETH_TXD0]  [ALT1 ] */
  /* P2.9 [ETH_TXD1]  [ALT1 ] */
  
	// Original Configuration
	/*PORT2->IOCR0  &= 0x00000000;
  PORT2->IOCR4  &= 0x00FFFFFF;
  PORT2->IOCR4  |= 0x88000000;
  PORT2->IOCR8  &= 0xFFFF0000;
  PORT2->IOCR8  |= 0x00008888;
  PORT2->HWSEL  &= 0xFFFFFFFC;
  PORT2->HWSEL  |= 0x00000001;*/
	
	PORT2->IOCR0  = 0x80;
  PORT2->IOCR4  = 0x88008800;
  PORT2->IOCR8  = 0x8888;
  PORT2->IOCR12  = 0x0;
	PORT2->HWSEL  = 0x5;

  /* P5.3 - ETH_RXERD [Input] */
  /* P5.9 - ETH_TXEN  [ALT4 ] */

	// Original Configuration
	/*PORT5->IOCR0  &= 0x00FFFFFF;
  PORT5->IOCR8  &= 0xFFFF00FF;
  PORT5->IOCR8  |= 0x0000A000;*/
	
	PORT5->IOCR0  = 0x0;
  PORT5->IOCR4  = 0x0;
  PORT5->IOCR8  = 0xa000;

  /* P15.8 - ETH_CLK_RMIIC [Input] */
  /* P15.9 - ETH_CRS_DVC   [Input] */
  
	// Original Configuration
  //PORT15->IOCR8 &= 0xFFFF0000;
	PORT15->IOCR8 = 0x0;

	// neu hinzugef?gt
  PORT2->PDR0 = 0x22022222; //eth
  PORT2->PDR1 = 0x22222200; //eth
  PORT15->PDISC = 0xf0cc; //eth


  /* Configure ETH0 Port Control, enable RMII */
  ETH0_CON->CON = 0x0440CA00;

  /* Reset Ethernet MAC */
  SCU_RESET->PRSET2 = SCU_RESET_PRSET2_ETH0RS_Msk;
  for (tout = 0; tout < 0xFFFF; tout++);
  SCU_RESET->PRCLR2 = SCU_RESET_PRCLR2_ETH0RS_Msk;

  /* Reset Ethernet DMA */
	regv =ETH0->BUS_MODE;
  ETH0->BUS_MODE |= ETH_BUS_MODE_SWR_Msk;
  for (tout = 0; tout < 0xFFFF; tout++);
  while (ETH0->BUS_MODE & ETH_BUS_MODE_SWR_Msk);

  /* Initialize MAC control registers. */
  ETH0->MAC_CONFIGURATION =  ETH_MAC_CONFIGURATION_CST_Msk |
                             ETH_MAC_CONFIGURATION_ACS_Msk | 0x00008000;

  /* Set MAC address */
  ETH0->MAC_ADDRESS0_HIGH = (U32)own_hw_adr[5] <<  8 | (U32)own_hw_adr[4];
  ETH0->MAC_ADDRESS0_LOW  = (U32)own_hw_adr[3] << 24 | (U32)own_hw_adr[2] << 16 |
                            (U32)own_hw_adr[1] <<  8 | (U32)own_hw_adr[0];

  /* Put the DP83848C in reset mode */
  // write_PHY (PHY_REG_BMCR, 0x8000);
		// Dave Reset
	write_PHY (0,0x8000); //PhyBase, RegOffset,Value
	
	
 id1 = read_PHY (PHY_REG_IDR1);
 id2 = read_PHY (PHY_REG_IDR2);
  /* Wait for hardware reset to end. */
  for (tout = 0; tout < 0x100000; tout++) {
    regv = read_PHY (PHY_REG_BMCR);
    if (!(regv & 0x8800)) {
      /* Reset complete, device not Power Down. */
      break;
    }
  }


	
	
	
	
	
  id1 = read_PHY (PHY_REG_IDR1);
  id2 = read_PHY (PHY_REG_IDR2);
	
  //ID1 = read_PHY (PHY_REG_IDR1);
  //id2 = read_PHY (PHY_REG_IDR2);
	
	// TI-Configuration part
	// Need to do it for Micrel
//   if (((id1 << 16) | (id2 & 0xFFF0)) == DP83848C_ID) {
//     /* Configure the PHY device */
// #if defined (_10MBIT_)
//     /* Connect at 10MBit */
//     write_PHY (PHY_REG_BMCR, PHY_FULLD_10M);
// #elif defined (_100MBIT_)
//     /* Connect at 100MBit */
//     write_PHY (PHY_REG_BMCR, PHY_FULLD_100M);
// #else
//     /* Use autonegotiation about the link speed. */
//     write_PHY (PHY_REG_BMCR, PHY_AUTO_NEG);
//     /* Wait to complete Auto_Negotiation. */
//     for (tout = 0; tout < 0x100000; tout++) {
//       regv = read_PHY (PHY_REG_BMSR);
//       if (regv & 0x0020) {
//         /* Autonegotiation Complete. */
//         break;
//       }
//     }
// #endif
//   }
	
// Micrel Configuration

int_enable_eth();	//Enable Interrupt

// Disable Link Up Interrupt
// write_PHY (0x1b, 0x900); // Make Link Partner Acknowledged, Link UP Interrupt on.
		

	  //if (((id1 << 16) | (id2 & 0xFC0F)) == KSZ8031RLN_DEF_ADR) {
		if (((id1 ==0x22)&&(id2 == 0x1556))){// == KSZ8031RLN_DEF_ADR) {
    /* Configure the PHY device */
#if defined (_10MBIT_)
    /* Connect at 10MBit */
    write_PHY (PHY_REG_BMCR, PHY_FULLD_10M);
#elif defined (_100MBIT_)
    /* Connect at 100MBit */
    write_PHY (PHY_REG_BMCR, PHY_FULLD_100M);
#else
    /* Use autonegotiation about the link speed. */
    write_PHY (PHY_REG_BMCR, KSZ8031RLN_PHY_AUTO_NEG);
    /* Wait to complete Auto_Negotiation. */
    for (tout = 0; tout < 0x100000; tout++) {
      regv = read_PHY (PHY_REG_BMSR);
			PHYRegisterRead = read_PHY (0x1b);

      if (regv & 0x0020) {
        /* Autonegotiation Complete. */
        break;
      }
    }
#endif
  }
	
	
	

  /* Check the link status. */
  for (tout = 0; tout < 0x10000; tout++) {
    regv = read_PHY (PHY_REG_STS);
    if (regv & 0x0001) {
      /* Link is on. */
      break;
    }
  }

  /* Configure Full/Half Duplex mode. */
  if (regv & 0x0004) {
    /* Full duplex is enabled. */
    ETH0->MAC_CONFIGURATION |= ETH_MAC_CONFIGURATION_DM_Msk;
  }
  else {
    /* Half duplex mode. */
    ETH0->MAC_CONFIGURATION |= ETH_MAC_CONFIGURATION_DO_Msk;
  }

  /* Configure 100MBit/10MBit mode. */
  if (regv & 0x0002) {
    /* 10MBit mode. */
  }
  else {
    /* 100MBit mode. */
    ETH0->MAC_CONFIGURATION |= ETH_MAC_CONFIGURATION_FES_Msk;
  }

  /* Initialize Tx and Rx DMA Descriptors */
  rx_descr_init ();
  tx_descr_init ();

  /* Receive Broadcast, Multicast and Perfect Match Packets */
  ETH0->MAC_FRAME_FILTER = ETH_MAC_FRAME_FILTER_PM_Msk |
                           ETH_MAC_FRAME_FILTER_HPF_Msk;

  /* Enable ETH interrupts. */
  ETH0->INTERRUPT_ENABLE = ETH_INTERRUPT_ENABLE_RIE_Msk |
                           ETH_INTERRUPT_ENABLE_TIE_Msk |
                           ETH_INTERRUPT_ENABLE_NIE_Msk;

  /* Reset all interrupts */
  ETH0->STATUS           = ETH_INTERRUPT_ENABLE_RIE_Msk |
                           ETH_INTERRUPT_ENABLE_TIE_Msk |
                           ETH_INTERRUPT_ENABLE_NIE_Msk;

  /* Start MAC receive descriptor ring pooling */
  ETH0->RECEIVE_POLL_DEMAND  = 0;
  ETH0->TRANSMIT_POLL_DEMAND = 0;

  /* Enable receive and transmit mode of MAC Ethernet core. */
  ETH0->MAC_CONFIGURATION |= (ETH_MAC_CONFIGURATION_RE_Msk |
                              ETH_MAC_CONFIGURATION_TE_Msk);
  ETH0->OPERATION_MODE    |= (ETH_OPERATION_MODE_SR_Msk |
                              ETH_OPERATION_MODE_ST_Msk);
															
	
}

/*--------------------------- int_enable_eth ---------------------------------*/

void int_enable_eth (void) {
  /* Ethernet Interrupt Enable function. */
  NVIC_EnableIRQ (ETH0_0_IRQn);
}


/*--------------------------- int_disable_eth --------------------------------*/

void int_disable_eth (void) {
  /* Ethernet Interrupt Disable function. */
  NVIC_DisableIRQ (ETH0_0_IRQn);
}


// /*--------------------------- send_frame -------------------------------------*/

// void send_frame (OS_FRAME *frame) {
//   /* Send frame to ETH ethernet controller */
//   U32 idx,len;
//   U32 *sp,*dp;

//   idx = TxBufIndex;
//   sp  = (U32 *)&frame->data[0];
//   dp  = (U32 *)Tx_Desc[idx].Addr;

//   /* Copy frame data to ETH packet buffer. */
//   for (len = (frame->length + 3) >> 2; len; len--) {
//     *dp++ = *sp++;
//   }
//   Tx_Desc[idx].Size      = frame->length;
//   Tx_Desc[idx].CtrlStat |= TDES0_OWN;
//   if (++idx == NUM_TX_BUF) idx = 0;
//   TxBufIndex = idx;

//   /* Start frame transmission. */
//   ETH0->TRANSMIT_POLL_DEMAND = 0;
// }

/*--------------------------- send_frame -------------------------------------*/

void send_frame2 (IP_Event *ip_evt) {
  /* Send frame to ETH ethernet controller */
  U32 idx,length;
   //U32 *sp,*dp;
  U8 *sp,*dp;

  idx = TxBufIndex;
//   sp  = (U32 *)&frame->data[0];
	 //sp  = (U32 *)(&(ip_evt->buf));
   //dp  = (U32 *)Tx_Desc[idx].Addr;
	sp  = (U8 *)&ip_evt->buf;
  dp  = (U8 *)Tx_Desc[idx].Addr;
	
	
  /* Copy frame data to ETH packet buffer. */
 //  for (len = (frame->length + 3) >> 2; len; len--) {
//     *dp++ = *sp++;
//   }
  //for (length = (ip_evt->len + 3) >> 2; length; length--) {
	printf("ip_evnt->length %02x", ip_evt->len);
	//array[index++] = ip_evt->len;
	//if(index == 4) index = 0;
	for (length = 0; length < ip_evt->len; length++) {
    *dp++ = *sp++;
  }	
//   Tx_Desc[idx].Size      = frame->length;
	Tx_Desc[idx].Size      = ip_evt->len;
  Tx_Desc[idx].CtrlStat |= TDES0_OWN;
  if (++idx == NUM_TX_BUF) idx = 0;
  TxBufIndex = idx;

  /* Start frame transmission. */
  ETH0->TRANSMIT_POLL_DEMAND = 0;
}

//	------------------------------------------------
//	init_ipv4.h
//	------------------------------------------------
//	Send to EMAC device.
// void send2(unsigned char *buffer, int size) {
// 	unsigned char emac_rc;
// 	emac_rc = EMAC_Send( (void*)buffer, size, (EMAC_TxCallback)0);
// 	if (emac_rc != EMAC_TX_OK) {
// 		TRACE_ERROR("E: Send, rc 0x%x\n\r", emac_rc);
// 	}		
// }

//	Read from EMAC device.
unsigned int receive(unsigned char *buffer, unsigned char *rStatus ) {
//	unsigned int pkt_len = 0;
	U32 i,j,idx,frm_err ,RxLen, retRxLen; // int_stat
  U32 *sp,*dp;
//	OS_FRAME *frame;
  
	*rStatus = 0; // <- reset the return status;
	
    /* Packet received, check if packet is valid. */
    idx = RxBufIndex;
    /* Get frame length. */
    for (j = 0; j < NUM_RX_BUF; j++) {
      if (Rx_Desc[idx].Stat & RDES0_LS) {
        break;
      }
      if (++idx == NUM_RX_BUF) idx = 0;
    }
		

		/* ##FETCH## */
		RxLen   = (Rx_Desc[idx].Stat >> 16) & 0x3FFF;
		retRxLen = RxLen; //save the lenght of the packet to return it later 
    frm_err = Rx_Desc[idx].Stat & RDES0_ES;

    if (++idx == NUM_RX_BUF) idx = 0;
		
		if (RxLen > ETH_MTU || frm_err) {
      /* Packet error, ignore it and free buffer. */
					*rStatus = RECEIVE_ERROR;
				goto release;
					//TODO: DO ERROR HANDLING
    }
		
		
			dp = (U32 *)buffer;
			
      for (i = RxBufIndex; i != idx; RxLen -= ETH_RX_BUF_SIZE) {
        sp = (U32 *)(Rx_Desc[i].Addr);
        j = RxLen;
        if (j > ETH_RX_BUF_SIZE) j = ETH_RX_BUF_SIZE;
        for (j = (j + 3) >> 2; j; j--) {
          *dp++ = *sp++;
        }
        if (++i == NUM_RX_BUF) i = 0;
      }
			
			/* ##RELEASE## */
release:
			
			for (j = RxBufIndex; j != idx;  ) {
      Rx_Desc[j].Stat |= RDES0_OWN;
      if (++j == NUM_RX_BUF) j = 0;
    }
			RxBufIndex = idx;
			
			    /* Check if a new packet received. */
    for (j = 0; j < ETH_RX_BUF_NUM; j++) {
      if (Rx_Desc[idx].Stat & RDES0_OWN) {
        break;
      }
      if (Rx_Desc[idx].Stat & RDES0_LS) {
        /* Yes, tell that there is more to fetch and release ETH IO buffer. */
				*rStatus |= RECEIVE_MORE_TO_FETCH;
				return retRxLen;
				//*rStatus = receiveMoreToFetch;
      }
      if (++idx == NUM_RX_BUF) idx = 0;
    }
		*rStatus |= RECEIVE_FINISH;
		return retRxLen;
			
		
			//			(( Uip_AO *)UipAO)->buf = (unsigned char * ) &frame->data[0];
			//			(( Uip_AO *)UipAO)->eth_inf = RxLen;
						
			// Release this frame from ETH IO buffer.*/
			
			
}

/*--------------------------- interrupt_ethernet -----------------------------*/

void ETH0_0_IRQHandler (void) {
  //OS_FRAME *frame;
  U32 int_stat; //i,j, ,frm_err,RxLen

	
	int_stat = ETH0->STATUS;
 	// Check if the reason for the interrupt is a received frame & Reception is complete
  if (int_stat & ETH_STATUS_RI_Msk){// ToDo: Check DisableInterruptLast Register in last RDES1_C from beginning to check if all frames transmitted
		
		// Check if Frame is valid
	  //RxLen   = (Rx_Desc[idx].Stat >> 16) & 0x3FFF;
		//frm_err = Rx_Desc[idx].Stat & RDES0_ES;
		
			//eth_evtPtr = 
		// eth_evtPtr = Q_NEW(EMAC_Event, EMAC_INT_SIG); //NEW_DATA_SIG IP_RECEIVE
		//ToDo: NEW_DATA_SIG enough für ISR ??
		//ToDo: IP_RECEIVE enough für Tx  ??
		eth_evtPtr = Q_NEW(Ethernet_Event, ETHERNET_RECEIVE_SIG); //NEW_DATA_SIG
	  
		//eth_evtPtr->len = RxLen&0xFFFF; 
				
		
		
		// Directly Assigning UIP the start Frame !!!
		// ToDo: Gib als ESV zum AO!!!
						// - Wieso frame verwenden, falls kein Copy??
						// - Timer zum Uip_AO wann initialisieren??
		//(( Uip_AO *)UipAO)->buf = (unsigned char * )(Rx_Desc[RxBufIndex].Addr); // &frame->data[0]; // buf is pointer, points to beginn of data, cast down from 32 Bit pointer to 8 bit pointer
		//(( Uip_AO *)UipAO)->eth_inf = RxLen;
		
		// Use priviledged functions -- Enable to Disable Interrtupts in postFifo
	  __enable_irq();
//		ethEvent.type = 1;
		// FIFO to Ethernet AO
// 		QActive_postFIFO(ethernetAO, (QEvent *)&ethernet_event);
		QActive_postFIFO(ethernetAO, (QEvent *)eth_evtPtr);
	// 	QActive_postFIFO(UipAO,(QEvent*)eth_evtPtr);
		// QF_INT_LOCK();
		__disable_irq();

		  /* Packet error, ignore it and free buffer. */ // Don't send event
			// ToDo: - Clear Interrupt, 
			// 			 - Give Descriptor back to DMA
			//			 - Don't process packets
	
	
//exit: 
		__enable_irq();
}
	ETH0->STATUS |= 0x40; // this resets the interupt
}

	
// 			__disable_irq(); 
// #ifdef QK 
// 	   --QK_intNest_;
// 	   if (   QK_intNest_ ==0) 
// 	   		QK_schedule_();
// #endif
		

/*for (j = RxBufIndex; j != idx;  ) {
      Rx_Desc[j].Stat |= RDES0_OWN;
      if (++j == NUM_RX_BUF) j = 0;
    }
    RxBufIndex = idx;

    // Check if a new packet received. 
    for (j = 0; j < ETH_RX_BUF_NUM; j++) {
      if (Rx_Desc[idx].Stat & RDES0_OWN) {
        break;
      }
      if (Rx_Desc[idx].Stat & RDES0_LS) {
        // Yes, fetch it and release ETH IO buffer. 
        goto fetch;
      }
      if (++idx == NUM_RX_BUF) idx = 0;
    }
		
			//Relase here
	else if(registerSet.receiveStatusRegister & AT91C_EMAC_BNA) {
		// clear buffer by reading and throwing away the package
		unsigned char tmpBuf[1500];
		unsigned int len;
		// read from ethernet hardware
		len = receive(tmpBuf, 1500);
		
		bnaCounter++;
		// clear registers since the buffer is overflown
		printf("ethernet: received to many packages, clearing buffers, bnacounter = %d \n", bnaCounter);
		EMAC_Clear_HardwareBuffers();

		
		
		
  }
	
	// Send Event to UIP Active Object --> Ptr to position
  ETH0->STATUS = int_stat;
}*/
	
void HardFault_Handler (void){
	//for(;;)
	{}
		//SCB->BFAR;
}

/*--------------------------- rx_descr_init ----------------------------------*/

static void rx_descr_init (void) {
  /* Initialize Receive DMA Descriptor array. */
  U32 i;

  RxBufIndex = 0;
  for (i = 0; i < NUM_RX_BUF; i++) {
    Rx_Desc[i].Stat = RDES0_OWN;
    Rx_Desc[i].Ctrl = RDES1_RCH | ETH_RX_BUF_SIZE;
    Rx_Desc[i].Addr = (U32)&rx_buf[i];
    Rx_Desc[i].Next = (U32)&Rx_Desc[i+1];
  }
  Rx_Desc[NUM_RX_BUF-1].Next = (U32)&Rx_Desc[0];

  /* Set ETH Receive List base address. */
  ETH0->RECEIVE_DESCRIPTOR_LIST_ADDRESS = (U32)&Rx_Desc[0];
}


/*--------------------------- tx_descr_init ----------------------------------*/

static void tx_descr_init (void) {
  /* Initialize Transmit DMA Descriptor array. */
  U32 i;

  TxBufIndex = 0;
  for (i = 0; i < NUM_TX_BUF; i++) {
    Tx_Desc[i].CtrlStat = TDES0_TCH | TDES0_LS | TDES0_FS;
    Tx_Desc[i].Addr = (U32)&tx_buf[i];
    Tx_Desc[i].Next = (U32)&Tx_Desc[i+1];
  }
  Tx_Desc[NUM_TX_BUF-1].Next = (U32)&Tx_Desc[0];

  /* Set ETH Transmit List base address. */
  ETH0->TRANSMIT_DESCRIPTOR_LIST_ADDRESS = (U32)&Tx_Desc[0];
}


/*--------------------------- write_PHY --------------------------------------*/

//static void write_PHY (U32 PhyReg, U16 Value) {
void write_PHY (U32 PhyReg, U16 Value) {
  /* Write a data 'Value' to PHY register 'PhyReg'. */
  U32 tout;
  uint32_t Address; 
	//uint32_t PhyBase;
	
  /* Send MDIO write command */
  ETH0->GMII_DATA    = Value;
	// ETH0->GMII_ADDRESS = DP83848C_DEF_ADR << 11  | PhyReg << 6 | 0x01 << 2 |
  //                     ETH_GMII_ADDRESS_MW_Msk | ETH_GMII_ADDRESS_MB_Msk;

	
   Address = ((PhyBase << (uint32_t)GmiiDevShift) & (uint32_t)GmiiDevMask) |((PhyReg << (uint32_t)GmiiRegShift) & (uint32_t)GmiiRegMask) | (uint32_t)GmiiWrite;
	Address = Address | (uint32_t)GmiiBusy; /* Gmii busy bit */
  /* write the Addressess from where the data to be read in GmiiGmiiAddr
   * register of synopGMAC ip
   */
  ETH0->GMII_ADDRESS = Address;	
	
	
  /* Wait until operation completed */
  for (tout = 0; tout < GMII_WR_TOUT; tout++) {
    if (!(ETH0->GMII_ADDRESS & ETH_GMII_ADDRESS_MB_Msk)) {
      break;
    }
  }
}


/*--------------------------- read_PHY ---------------------------------------*/

//static U16 read_PHY (U32 PhyReg) {
U16 read_PHY (U32 PhyReg) {
  /* Read a PHY register 'PhyReg'. */
  U32 tout;
 uint32_t Address;
	
 
  /* Send MDIO read command */
  // ETH0->GMII_ADDRESS = DP83848C_DEF_ADR << 11 | PhyReg << 6 | 0x01 << 2 |
 //                                               ETH_GMII_ADDRESS_MB_Msk;
  Address = ((PhyBase << (uint32_t)GmiiDevShift) & (uint32_t)GmiiDevMask) | ((PhyReg << (uint32_t)GmiiRegShift) & (uint32_t)GmiiRegMask);
  Address = Address | (uint32_t)GmiiBusy; /* Gmii busy bit */
   ETH0->GMII_ADDRESS = Address;	
	
  /* Wait until operation completed */
  for (tout = 0; tout < GMII_RD_TOUT; tout++) {
    if (!(ETH0->GMII_ADDRESS & ETH_GMII_ADDRESS_MB_Msk)) {
      break;
    }
  }
  return (ETH0->GMII_DATA);
}

/*-----------------------------------------------------------------------------
 * End of file
 *----------------------------------------------------------------------------*/
