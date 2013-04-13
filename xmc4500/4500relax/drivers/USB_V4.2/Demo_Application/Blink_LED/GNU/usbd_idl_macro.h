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
** @FILENAME@:       usb_idl_macro.h
** @VERSION@:        4.2
** @DATE@:           23/01/2006    
**
** =============================================================================
**
** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements wrapper functionalites for accessing the hardware.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004     Ranganatha (DC BA)      
** 18/05/2004     Ranganatha              Added few more macros.                                          
** 01/12/2004	  						  added udc_cfg_block struct	
** @CHANGE_HISTORY@
** =============================================================================
*/

#ifndef _USBD_IDL_MACRO_H_
#define _USBD_IDL_MACRO_H_

/* This file contains Macros for the various functionalities of the 
 *  USB peripheral 
 */
#include "usbd_idl.h"
#include "compiler.h"

/* Defines the target specification for USB HAL */
#define USB_PRODUCT    TC1130


/* Reloads the cpu shadow registers */
#define USBD_RELOAD_CPU_SHADOW_REGISTERS \
    USBD_WRITE_REG(USBD_DCR, USBD_DCR_CPUSRL_BIT) 


/* Reloads the usb shadow registers */
#define USBD_RELOAD_USB_SHADOW_REGISTERS \
   USBD_WRITE_REG(USBD_DCR, USBD_DCR_USBSRL_BIT) 


/* End of initialization Data  */
#define USBD_MARK_END_OF_INIT_DATA \
 USBD_WRITE_REG(USBD_DCR, USBD_DCR_EOID_BIT)


/* Wake-up the USB device */
#define USBD_WAKEUP_DEVICE  \
  ( ( USBD_WRITE_REG(USBD_DCR, USBD_DCR_RSM_BIT) )


/* Reads the current endpoint number being used by USB device */
#define USBD_GET_CURRENT_EP           ( ( USBD_READ_REG(USBD_DSR) ) >> 16)


/* checks whether device is currently being accessed by host or not. 
 *   Returns 1 if true else 0.
 */
#define USBD_CHK_DEVICE_ACCESS_BY_HOST  \
      ( (USBD_READ_REG(USBD_DSR)>> 23) ? 1:0 )


/* checks receiver power down, returns 1 if true */
#define USBD_CHK_RXR_POWER_DOWN_STATUS  \
          ( !( USBD_READ_REG(USBD_DSR) & 1) )?1:0


/* checks transmitter power down, returns 1 if true */
#define USBD_CHK_TXR_POWER_DOWN_STATUS  \
          ( !(USBD_READ_REG(USBD_DSR)) >> 2)?1:0


/* checks if UDC clock is enabled - returns 1 if true */
#define USBD_CHK_UDC_CLOCK          ( (USBD_READ_REG(USBD_DSR)) >> 4)?1:0


/* Checks usb suspend mode & returns 1 if true */
#define USBD_CHK_SUSPEND_MODE       ( (USBD_READ_REG(USBD_DSR)) >> 6)?1:0  


/* Checks usb speed & returns 1 if FULL Speed else 0 for low speed */
#define USBD_CHK_SPEED      ( (USBD_READ_REG(USBD_DSR)) >> 9)?1:0  


/* Retuns 1 if device is attached otherwise 0 */
#define USBD_CHK_DEVICE_ATTACHED    ( (USBD_READ_REG(USBD_DSR)) >> 11)?1:0  


/* Reflects the direction of the last USB access to EP0. Read direction 
 * returns 1 & write direction returns 0.
 */
#define USBD_GET_EP0_DIR            ( (USBD_READ_REG(USBD_DSR)) >> 12)?1:0
 
 
/* Reads Device Detection Pin Logic - internal/exteranl pin.
 * If pin is internal returns 1, else 0. This is internal to TC1130.
 */
#define USBD_GET_DDPIN_LOGIC            ( (USBD_READ_REG(USBD_DSR)) >> 13)?1:0



/* Stalls the endpoint */
#define USBD_STALL_EP( ep )            USBD_WRITE_REG( USBD_EPSSR, (1 << ep) )


/* Remove the stall on endpoint*/
#define USBD_STALL_RESET_EP( ep )     \
        USBD_WRITE_REG( USBD_EPSSR, (0x10000 << ep) )

   
/* checks the stalled ep & returns 1 if true else returns 0.*/
#define USBD_CHK_STALL_EP( ep )     \
       ( ( USBD_READ_REG(USBD_EPSTL) ) & (1 << ep) ) )?1:0


#define USB_EP_SET_STALL      USBD_STALL_EP 


/* Returns 10-bit frame number*/
#define USBD_GET_FRAME_NUMBER          USBD_READ_REG( (USBD_FNR) ) 


/* Reads the configuration value requested by the host*/
#define USBD_GET_CF_VALUE            ( USBD_READ_REG(USBD_CNFR) >> 12 )


/* Reads the Interface value requested by the host*/
#define USBD_GET_IF_VALUE            ( USBD_READ_REG(USBD_CNFR) >> 4 )


/* Reads the Alternate Setting value requested by the host*/
#define USBD_GET_AS_VALUE            ( USBD_READ_REG(USBD_CNFR) & 0x0000000F )


/* Reads the set-up tokens from registers*/
#define GET_SETUP_TOKEN_MSB         ( USBD_READ_REG(USBD_SUTH) )
#define GET_SETUP_TOKEN_LSB         ( USBD_READ_REG(USBD_SUTL) )


/* sends NACK or ZLP on endpoint (EP invalid) */
#define USBD_NACK_EP( ep )          USBD_WRITE_REG( USBD_EVSR, (0x10000 << ep) )


/* sends ACK  on endpoint (EP invalid) */
#define USBD_ACK_EP( ep )          USBD_WRITE_REG( USBD_EVSR, (1 << ep) )


/* Check validity of endpoint (EP ready for transfer or not). 
   Returns 1 if valid else 0 
*/
#define USBD_CHK_EP_VALID( ep )   \
       ( USBD_READ_REG(USBD_EPVLD) & (1 << ep) )? 1 : 0 

#define NACK_EP  USBD_NACK_EP 
#define ACK_EP   USBD_ACK_EP 

#define INVALID_EP  USBD_NACK_EP 
#define VALID_EP   USBD_ACK_EP 



/* sets the Zero-length packet */
#define USBD_ENABLE_ZERO_PACKET( ep ) USBD_WRITE_REG( (USBD_ZLPSR), (1 << ep) )


/* Resets the Zero-length packet */
#define USBD_DISABLE_ZERO_PACKET( ep )  \
        USBD_WRITE_REG( (USBD_ZLPSR), (0x10000 << ep) )             


/* Returns the zero-packet length status. IF ZLPn=1 & EPVn=0, the next pakcet 
 * will be sent with as zero-packet-length. Thereafter the ZLPn is reset.
 */
#define USBD_CHK_ZLP_ENABLE( ep )  \
        ( USBD_READ_REG(USBD_ZLPEN)  & (1 << ep) ) ?1:0 


/*IN-Packet: Data flow is from cpu to host */
#define USBD_SET_IN_DIR( ep )     USBD_WRITE_REG( USBD_EPDSR, (1 << ep) )


/*OUT-Packet: Data flow is from host to cpu */
#define USBD_SET_OUT_DIR( ep )    USBD_WRITE_REG( USBD_EPDSR, (0x10000 << ep) )


/* Selects the EP for transfer. Reload of cpu register is required to 
 * bug in hardware. For more details see errata sheet.
 */
#if 1 
#define USBD_SELECT_EP( ep )  USBD_WRITE_REG( USBD_FCON, ep ); \
 USBD_RELOAD_CPU_SHADOW_REGISTERS 
#else
#define USBD_SELECT_EP( ep )  USBD_WRITE_REG( USBD_FCON, ep )
#endif

 /* Clears endpoint - reset the buffer & control bits of both UDC & CPU */
#define USBD_CLEAR_EP( ep ) USBD_WRITE_REG( USBD_FCON, ep ); \
 USBD_WRITE_REG( USBD_FCON, USBD_FCON_CLEAR_BIT )   


/* checks the FIFO validity & returns 1 if valid */
#define USBD_CHK_FVLD     (USBD_READ_REG(USBD_FCON) & USBD_FCON_FVLD_BIT)? 1:0

/* checks the  EP1 FIFO validity & returns 1 if valid */
#define USBD_CHK_EP1FVLD     (USBD_READ_REG(USBD_FCON) & USBD_FCON_EP1FVLD_BIT)? 1:0
/* checks the EP2 FIFO validity & returns 1 if valid */
#define USBD_CHK_EP2FVLD     (USBD_READ_REG(USBD_FCON) & USBD_FCON_EP2FVLD_BIT)? 1:0




/* Set the Done bit. */
#define USBD_SET_DONE_BIT( ep )   \
     USBD_WRITE_REG( USBD_FCON, (USBD_FCON_DONE_BIT | ep) )

/* Checks validity of endpoint between UDC & CPU */
#define  USBD_CHK_EP_READY( ep )  \
         ( USBD_READ_REG(USBD_FCON)  & (0x10000 << ep) )?1:0 


    /*Return packet size programmed (PSZ) from EPUP register*/
#define USBD_GET_BLOCK_SZ( ep )      \
        ( 8 << (USBD_READ_MEM((USBD_RAM_BASE + 0x10) + (ep*0x10)) & 0x03) )


    /*Return number of packets programmed (BSZ) from EPCP register*/
#define USBD_GET_NBLOCK( ep )   \
        ((USBD_READ_MEM( (USBD_RAM_BASE + 0x14) + (ep*0x10) )) >> 3)


    /*Return the number of empty packets (NEB) available from EPBC register */
#define USBD_GET_EBLOCK( ep )  \
        ((USBD_READ_MEM( (USBD_RAM_BASE + 0x1C) + (ep*0x10) )) >> 16)


/* Gets the current UDC access pointer (UAP) from EPUP register*/
#define USBD_GET_UAP_INDEX( ep )    \
        (USBD_READ_MEM( (USBD_EPUP_BASE + (ep*16)) ) >> 16)


/* Gets the current CPU access pointer (CAP) from EPCP register*/
#define USBD_GET_CAP_INDEX( ep )    \
        (USBD_READ_MEM( (USBD_EPCP_BASE + (ep*16)) ) >> 16)   


/* Gets the Base pointer (BSP) from EPUP register. Last 3 bits belongs to PSZ. 
   Store this as a constant for access purpose
 */                                 
#define USBD_GET_BSP_INDEX( ep )    \
        (USBD_READ_MEM( (USBD_EPUP_BASE + (ep*16)) ) & (0x0000FFF8) )


/* Checks whether the packet is configured as IN or OUT packet from
   USB configuration block for initial set-up. 
  */
#define USBD_CHECK_IN_PACKET( BYTE2 )    (BYTE2 & 0x08)?1:0 


/* Checks Pipe direction for IN packet
  */
#define USBD_CHK_PIPE_IN( ep )  \
        ( ( USBD_READ_REG(USBD_EPDIR) & (1 << ep) )?1:0 )


/* Checks Pipe direction for OUT packet
 */
#define USBD_CHK_PIPE_OUT( ep )  \
        ( ( USBD_READ_REG(USBD_EPDIR) & (1 << ep) )?0:1 )

/* Sends ZLP packet if EPVn=0 & ZLP=1. Since Auto Fifo is implemented EPVn=0 
   will be taken care automatically
*/
#define USBD_TX_ZERO_LENGTH_PKT( ep )  USBD_WRITE_REG( USBD_ZLPSR, (1<<ep))


/* Holds the udc usb config structure */
volatile typedef struct{
	IFX_UINT8  epCFG:4,
			   epNum:4;	
	IFX_UINT8  epAS:4,
			   epIF:4; 		
	IFX_UINT8  res_1:3,
			   epDir:1,
			   epType:4;		  
	  
IFX_UINT8   res_2;
IFX_UINT8   res_3;
IFX_UINT8   res_4;
}udc_cfg_block;

/*
@struct USB_DEVICE_STATUS |
 Holds different usb device  states like connected, configured
 suspended, disconnected. The status is filled based on the 
 device interrupts enabled. Note that the application can receive and
 transmit packets only in configured state.
*/
typedef struct USB_DEVICE_STATUS_t
{
  IFX_UINT8 status;                     /* Holds device status */
}USB_DEVICE_STATUS;

#endif  /*_USBD_IDL_MACRO_H_ */

