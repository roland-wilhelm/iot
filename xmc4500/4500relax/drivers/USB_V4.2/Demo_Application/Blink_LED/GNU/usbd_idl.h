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
** @FILENAME@:       USBD_IDL.H
** @VERSION@:        4.2
** @DATE@:           23/01/2006  
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Abstracts the hardware definitions.
**            
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004     Ranganatha (DC BA)      
**                                        
** @CHANGE_HISTORY@
** =============================================================================
*/

#ifndef _USBD_IDL_H_
#define _USBD_IDL_H_

#include "usb_iil_common.h" 
#include "compiler.h"

/*----------------------------------------------------------------------*
 * Memory Map         Range			   Size			Description
 *
 * USBD_RAM_BASE     0xF00E2000-219F    416 Bytes   Ram Based Registers.
 * 
 * USBD_FIFO_BASE    0xF00E21A0-27FF    1.6KBytes   Ram base buffer Area  
 * 
 * USBD_SFR_BASE     0xF00E2800-28FF    256 Bytes   SFR Area 
 *-----------------------------------------------------------------------*/
#define USBD_RAM_BASE	    0xF00E2000 
#define USBD_FIFO_BASE	    0xF00E21A0 
#define USBD_SFR_BASE		0xF00E2800
#define USBD_FIFO_BASE_END  0xF00E27FF      




/* Setup Token Area - Low & High Byte Registers */
#define USBD_SUTL		*(IFX_VUINT32 *)(USBD_RAM_BASE + 0x0000)        
#define USBD_SUTH		*(IFX_VUINT32 *)(USBD_RAM_BASE + 0x0004)        


/* Endpoint properties Area
 * For End Point 0 Area. Other endpoints can be derived from this. 
 */
#define USBD_EPUP_BASE	    0xF00E2010       /*EPn USB Pointer Register*/
#define USBD_EPCP_BASE	    0xF00E2014       /*EPn CPU Pointer Register*/
#define USBD_EPIC_BASE	    0xF00E2018       /*EPn Interrupt Control Register*/
#define USBD_EPBC_BASE	    0xF00E201C       /*EPn Buffer Control Register.*/
#define USBD_EPP_BASE       USBD_EPUP_BASE   /*EP properties Base*/

/*EP0 Interrupt Control Register*/
#define USBD_EPIC0		*(IFX_VUINT32 *)(USBD_RAM_BASE + 0x0018)        


/*System registers*/
/*Clock Control Port*/     
#define USBD_CLC		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x00)    
 /*Input Port Selection register*/
#define USBD_PISEL   	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x04)   
/*Id register*/
#define USBD_ID      	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x08)    

/*Control & status registers*/
/*Device Control register*/  
#define USBD_DCR	   	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x10)  
/*Device status register*/  
#define USBD_DSR	   	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x14)  
/*EP STALL register*/  
#define USBD_EPSTL		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x18)  
/*EP Set/Reset register */  
#define USBD_EPSSR		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x1C)  
/*Configuration Request Register*/  
#define USBD_CNFR		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x20)  

/* FIFO control Registers*/
/*Frame Number register*/ 
#define USBD_FNR	   	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x24)   
/*EP Direction register*/ 
#define USBD_EPDIR		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x28)   
/*EP Direction Set/Reset register*/ 
#define USBD_EPDSR		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x2C)   
/*FIFO Control Register*/ 
#define USBD_FCON		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x30)   
/*CPU local Pointer Register*/ 
#define USBD_CPLPR		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x34)   
/*Data Reg for 32-bit data access*/ 
#define USBD_DATA32		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x38)   
/*For 16-bit data access*/
#define USBD_DATA16		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x3C)   
/*For 8-bit data access*/
#define USBD_DATA8		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x40)   
/*EP valid Register*/ 
#define USBD_EPVLD		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x44)   
/*EP Valid set/reset reg*/ 
#define USBD_EVSR		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x48)   

/*Zero Length packetEnable reg*/
#define USBD_ZLPEN		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x90)   
/*Zero Length packet set/reset reg*/
#define USBD_ZLPSR		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x94)   


/* Interrupt Registers*/
#define USBD_DIER		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x4C)    
#define USBD_DIRR		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x50)    
#define USBD_DIRST	        *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x54)    
#define USBD_DINP		  *(IFX_VUINT32 *)(USBD_SFR_BASE + 0x58)    

#define USBD_EPIR0		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x5C)    
#define USBD_EPIR1		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x60)    
#define USBD_EPIR2		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x64)    
#define USBD_EPIR3		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x68)    


#define USBD_EPIRST_BASE	(USBD_SFR_BASE + 0x6C)    
#define USBD_EPIRST0	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x6C)    
#define USBD_EPIRST1	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x70)    
#define USBD_EPIRST2	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x74)    
#define USBD_EPIRST3	*(IFX_VUINT32 *)(USBD_SFR_BASE + 0x78)    

#define USBD_SRC7		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xE0)    
#define USBD_SRC6		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xE4)    
#define USBD_SRC5       *(IFX_VUINT32 *)(USBD_SFR_BASE + 0xE8)    
#define USBD_SRC4		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xEC)    
#define USBD_SRC3		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xF0)    
#define USBD_SRC2		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xF4)    
#define USBD_SRC1		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xF8)    
#define USBD_SRC0		*(IFX_VUINT32 *)(USBD_SFR_BASE + 0xFC)    



/*Register bit masks for all the above registers are defined below*/
#define USBD_CLC_DISR_BIT    BIT_0      /*Module Disable Request bit*/
#define USBD_CLC_DISS_BIT    BIT_1      /*Module Disable Status bit*/
#define USBD_CLC_RMC_BIT     BIT_8      /*Clock divider for normal run mode*/
#define USBD_CLC_SMC_BIT     BIT_16     /*Clock divider for sleep mode*/ 

#define USBD_DCR_RPWDS_BIT   BIT_0      /*Rx Power Down Set  */
#define USBD_DCR_RPWDR_BIT   BIT_1      /*Rx Power Down Reset*/
#define USBD_DCR_TPWDS_BIT   BIT_2      /*Tx Power Down Set  */
#define USBD_DCR_TPWDR_BIT   BIT_3      /*Tx Power Down Reset*/
#define USBD_DCR_UCLKS_BIT   BIT_4      /*UDC clock enable   */
#define USBD_DCR_UCLKR_BIT   BIT_5      /*UDC clock disable  */
#define USBD_DCR_RSM_BIT     BIT_6      /*Resume bus activity */
#define USBD_DCR_EOID_BIT    BIT_7      /*End Of Initialization Data */

#define USBD_DCR_SWRS_BIT       BIT_8    /*Software reset */
#define USBD_DCR_SPEEDS_BIT     BIT_9    /*Low/Full Speed Select Bit */
#define USBD_DCR_DADDIDIS_BIT   BIT_10   /*Device attached Signal Disabled */
#define USBD_DCR_DADDIEN_BIT    BIT_11   /*Device attached Signal enabled  */
#define USBD_DCR_USBSRL_BIT     BIT_14   /*CPU Shadow Register Reload */
#define USBD_DCR_CPUSRL_BIT     BIT_15   /*USB Shadow Register Reload */


#define USBD_DSR_RPWD_BIT     BIT_0      /*USB Rx Power down status*/
#define USBD_DSR_TPWD_BIT     BIT_2      /*USB Tx Power down status*/
#define USBD_DSR_UCLK_BIT     BIT_4      /*UDC clock status*/
#define USBD_DSR_SUSP_BIT     BIT_6      /*USB suspend Mode*/
#define USBD_DSR_DINIT_BIT    BIT_7      /*Device Init in progress*/
#define USBD_DSR_SWR_BIT      BIT_8      /*USB suspend Mode*/
#define USBD_DSR_SPEED_BIT    BIT_9      /*low/full speed status*/
#define USBD_DSR_DA_BIT       BIT_11     /*device attached*/
#define USBD_DSR_DIR_BIT      BIT_12     /*Direction of EP0*/
#define USBD_DSR_DADDIDIS_BIT BIT_13     /*device attached/disabled status*/
#define USBD_DSR_UEP_BIT      BIT_16     /* EP in Use*/
/*Transfer in Progress. Host is accessing the device*/
#define USBD_DSR_TIP_BIT      BIT_23     

#define USBD_FCON_FVLD_BIT       BIT_8       /*FIFO valid bit*/
#define USBD_FCON_EP1FVLD_BIT    BIT_17       /*EP1 FIFO valid bit*/
#define USBD_FCON_EP2FVLD_BIT    BIT_18       /*EP2 FIFO valid bit*/

  
    
        
#define USBD_FCON_DONE_BIT    BIT_9		    /*Done bit*/	
#define USBD_FCON_CLEAR_BIT   BIT_10      /*clear current ep bit*/  


/* Endpoint interrupts bit-definitions. */
#define USBD_EPIR_ACK_BIT  BIT_0       /*Acknowledge bit*/
#define USBD_EPIR_NACK_BIT BIT_1       /*No-Acknowledge bit*/
#define USBD_EPIR_BNR_BIT  BIT_2       /*Buffer Not ready bit*/
#define USBD_EPIR_WNI_BIT  BIT_3       /*warning level bit*/
#define USBD_EPIR_TRI_BIT  BIT_4       /*Transfer end interrupt bit*/

/* USB_DIRR Bits */
#define USBD_DIRR_DAI  BIT_0			/*Device attached*/
#define USBD_DIRR_DDI  BIT_1			/*Device deattahced*/
#define USBD_DIRR_SBI  BIT_2			/*Suspended begin mask*/
#define USBD_DIRR_SEI  BIT_3			/*Suspend end*/
#define USBD_DIRR_SE0I BIT_4			/*Single end zero*/
#define USBD_DIRR_STI  BIT_8			/*Status interrupt mask*/
#define USBD_DIRR_SUI  BIT_9			/*Set-up interrupt mask*/
#define USBD_DIRR_CFI  BIT_10			/*configuration interrupt mask*/
#define USBD_DIRR_SOFI BIT_11		  /*start of frame mask*/		
#define USBD_DIRR_EDII BIT_12			/*end of init data */
#define USBD_DIRR_FRI  BIT_13			/*Fifo ready interrupt mask*/
#define USBD_DIRR_FNRI BIT_14			/*Fifo not ready mask*/




/* Macro defintions */
#define  USBD_WRITE_REG( reg, value )  reg = value;

#define  USBD_READ_REG( reg )   reg

#define  USBD_SET_BIT( reg, bit_mask )   \
            USBD_WRITE_REG ( reg, ( USBD_READ_REG( reg ) | bit_mask ) ); 

#define  USBD_CLEAR_BIT( reg, bit_mask )   \
            USBD_WRITE_REG ( reg, ( USBD_READ_REG( reg ) & ~bit_mask ) ); 

#define  USBD_READ_MEM( reg )   (*(IFX_VUINT32 *)reg ) 

#define  USBD_WRITE_MEM( reg, value )   (*(IFX_VUINT32 *)reg) = value

#define  SET(reg,location) ( reg = ((reg) | (0x01 << (location))) )



#endif /* _USBD_IDL_H_ */
