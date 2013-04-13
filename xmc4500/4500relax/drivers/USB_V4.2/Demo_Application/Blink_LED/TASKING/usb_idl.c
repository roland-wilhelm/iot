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
** @FILENAME@:       USB_IDL.C
** @VERSION@:        4.2
** @DATE@:           23/01/2006     
**
** =============================================================================

** Project: TC1130
** Block: USB MODULE.
**
** =============================================================================
** Contents: Implements hardware fucntionalities for onchip usb device on TC1130
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
** 08/04/2004         
        a. Modified to support EP validation through manual mode or auto mode.
        b. Implemented Software work-around for hardware bug to pass
           synchronous testing .
        c. Read routine fixed for a extra byte read. 
        d. Also fixed fifo memory allocation bug for BSP.
	     
** 2/09/2004	Jayashree and Udo Dannebaum            
	   Firmware Guideline Implementation finished.
	   With Tasking compiler has a delay of 15 Secs in identification of device									   				 				                                   
**	   
** 12/11/2004     Ranganatha      
        a. Removed group processing of EPs in IRQs and 
           optimized IRQs for faster handling of fifo pointers. 
	    b. Device enumeration processing re-arranged for timing issues during
           enumeration process. 
** 01/12/2004     Jayashree and Ranganatha
**      a. set_endpoint_direction logic changed to handle the both logical & 
**         physical endpoints.
**      b. Sequential EP selection bug: Fixed 
**         Description - Before release2.6 the endpoints number cannot be choosen
**         randomly. E.g: In order to work with only EP5, you need to choose all 
**         endpoints from EP0 to EP5. Now this bug has been fixed.
** 06/06/2005	Jayashree : 
**      a.  Optimization of the routines all  for SIS and NEC Host controllers                      
**      b.  Interrupt handling changed.
**      c.  FIFO CNT maintained separately for packet count and NEB count, for ISO
**          mode of transmission and BULK and INTR sync packet transmission.
** 2/12/2005    Jayashree (IFIN CSW AIM) & Dannabaum Udo
**      Functions for automatic mode has been added
**      Switch between manual and automatic mode has been provided.
**
** =============================================================================
*/

#include "usbd_idl_macro.h"
#include "usb_idl_cfg.h"
#include "usb_iil_api.h"
#include "compiler.h"

#define MAXIMUM_NUM_OF_PIPES 12

/* Declares for both GNU & Linux compilers */
#if (IFX_COMPILER_GNU || IFX_COMPILER_LINUX)
/* USBD fifo buffer information */
IFX_UINT8 usbd_buffer_information[USBD_CFG_TOTAL_EP_USED][2]
              __attribute__ ((aligned (4)))  = { GLOBAL_USBD_CFG_BUFFER };

/* USB configuration block for USBD */
IFX_UINT8 usbd_configuration_block[] 
              __attribute__ ((aligned (4))) = {GLOBAL_USBD_CFG_BLOCKS};

/* USBD endpoint interrupt configuration 12- Number of endpoints in USBD */
IFX_UINT8 usbd_ep_interrupt_configuration[12][2]
              __attribute__ ((aligned (4))) = { USBD_CFG_EP_INTERRUPT_GLOBAL };

/* USBD device interrupt configuration */
IFX_UINT16 usbd_device_interrupt_configuration[1][2]
              __attribute__ ((aligned (4))) = { USBD_CFG_DEVICE_INTERRUPT };


/* Only for Active end-point used for transmission */
static IFX_VUINT32 tx_warning_flag[MAXIMUM_NUM_OF_PIPES]  __attribute__ ((aligned (4)));

       /* flag to allocate BSP from start 1- Allocate from start */
static IFX_UINT8 reallocate_bsp __attribute__ ((aligned (4))) = 1;      


extern IFX_UINT8 USBD_register_isr (void);
#endif    



/* Declares for GNU compiler */
#ifdef IFX_COMPILER_GNU
extern void USB_application_initialize( void );
extern volatile USB_BUFFER_CB * USB_for_pending_receive( IFX_UINT32 ep );
inline void USBD_EP1_Interrupt_handler(void);
inline void USBD_EP2_Interrupt_handler(void);
inline void USBD_EP3_Interrupt_handler(void);
inline void USBD_EP4_Interrupt_handler(void);
inline void USBD_EP5_Interrupt_handler(void);
inline void USBD_EP6_to_EP7_Interrupt_handler(void);
inline void USBD_EP8_to_EP11_Interrupt_handler(void);
inline void USBD_Device_Interrupt_handler(void);
#endif



/* Declares for Tasking compiler */
#ifdef IFX_COMPILER_TASKING
extern void USB_application_initialize( void );
extern volatile USB_BUFFER_CB * USB_for_pending_receive( IFX_UINT32 ep );

#pragma align 4
/* USB configuration block for USBD */
IFX_UINT8 usbd_configuration_block[]
                                = {GLOBAL_USBD_CFG_BLOCKS};

/* USBD fifo buffer information */
IFX_UINT8 usbd_buffer_information[USBD_CFG_TOTAL_EP_USED][2] 
                                = { GLOBAL_USBD_CFG_BUFFER };

/* USBD endpoint interrupt configuration 12- Number of endpoints in USBD */
IFX_UINT8 usbd_ep_interrupt_configuration[12][2] 
                                = { USBD_CFG_EP_INTERRUPT_GLOBAL };

/* USBD device interrupt configuration */
IFX_UINT16 usbd_device_interrupt_configuration[1][2]
                                = { USBD_CFG_DEVICE_INTERRUPT };

/* flag to allocate BSP from start 1- Allocate from start */
static IFX_UINT8 reallocate_bsp = 1;      


/* Only valid for active end-point during transmission */
static IFX_VUINT32 tx_warning_flag[MAXIMUM_NUM_OF_PIPES];
 
#ifdef IFX_TASKING_VER1
#pragma align off
#endif
#ifdef IFX_TASKING_VER2
#pragma align restore
#endif
#endif /* of IFX_COMPILER_TASKING */



/*  Declares for Linux Compiler */
#ifdef IFX_COMPILER_LINUX
extern wait_queue_head_t tricoreusb_wait_q;
#endif /* of IFX_COMPILER_LINUX */


/* Hold  device states for application */
USB_DEVICE_STATUS usb_device;       
/*Holds current configuration set by the host*/
/* CAP - Software counter for CAPn EPCP CPU Pointer Register */
static IFX_VUINT16 CAP[MAXIMUM_NUM_OF_PIPES];
/* PSZ - Software counter for PSZn Packet Size for Endpoint */
static IFX_VUINT16 PSZ[MAXIMUM_NUM_OF_PIPES];         
/* BSZ - Software counter for BSZn Packet Size for Endpoint */
static IFX_VUINT16 BSZ[MAXIMUM_NUM_OF_PIPES];
/* Fifo base address pointer */
static IFX_VUINT16 BSP[MAXIMUM_NUM_OF_PIPES]; 
 /* Represents NEB Value Count for OUT endpoints */        
static IFX_VUINT16  epx_neb_cnt[MAXIMUM_NUM_OF_PIPES]; 
 /* Represents BSZ Value Count for IN endpoints */  
static IFX_VUINT16  epy_pkt_cnt[MAXIMUM_NUM_OF_PIPES];     
/* FIFO  pointer for used to get Data */
IFX_UINT8 *FIFO_PTR[MAXIMUM_NUM_OF_PIPES];
/*Holds the endpoint information from the configuration*/
static IFX_UINT8 ep_info[MAXIMUM_NUM_OF_PIPES];

/* Forward declares */
inline void USBD_Initialize_device_interrupts(void);
inline void USBD_Initialize_endpoints_interrupts(void);
inline void USBD_config_device(void);
static void USBD_delay(IFX_UINT16 dcount);
IFX_UINT32 USBD_read_HwFifo(IFX_UINT8 ep, IFX_UINT8 *data,IFX_UINT32 bytesRequested );
void USBD_poll_rx(IFX_UINT8 ep);
IFX_SINT32 USBD_fill_HwFifo_Auto_mode(IFX_UINT8 ep, IFX_UINT8 *data, IFX_UINT32 data_size);
IFX_SINT32 USBD_read_HwFifo_Auto_mode(IFX_UINT8 ep, IFX_UINT8 *data, IFX_UINT32 bytesRequested );


/* External definitions */
extern void USB_setUpHandler(void);
extern USB_BUFFER_CB USB_buffer_cb[USB_NUMBER_OF_CB];

#define dev_isr	  1			// = 0: no device interrupts, requests are being polled

short int STI_count=0;
short int STI_enlarge=2;

/*==========================================================================
 * Function Name :: USBD_device_initialize()
 *
 * Purpose       :: Initializes usb device.
 *
 * Input         :: Will take configuration parameters from USB_IDL_CFG file.
 *					
 * Output        :: None.
 *
 * Return Value  :: USB_STATUS
 *
 *==========================================================================*/
USB_STATUS USBD_device_initialize (void)
{
#define ERR_TIME_OUT    100    /* Arbitary value */
/*pointer to information block*/
IFX_UINT16  *pUsbBlock_16 = (IFX_UINT16 *)usbd_configuration_block;   
/*pointer to RAM area*/
IFX_VUINT16 *p16Des = (IFX_VUINT16 *)USBD_RAM_BASE;        		      
IFX_VUINT32 regVal=0, err_flag=0;
IFX_UINT8	count=0, temp=0;

  /* Mark device is in non-attached state */
  usb_device.status = USB_IDLE;	

#if IFX_COMPILER_GNU 
  USBD_register_isr();         /* For GCC (non-OS) only */             
#endif

  UNLOCK_ENDINIT_PROTECT;
  SET(USBD_CLC,8);		                /* Set RMC bit */
  LOCK_ENDINIT_PROTECT;

  regVal = USBD_READ_REG(USBD_CLC);

  /*Check if clock is up. Else return error */
  if( !(regVal & 0x100 ) )
  {
      return (USB_ERROR);
  }

  for (count=0, temp=5; count<USBD_CFG_TOTAL_EP_USED; count++)
  {
     ep_info[count] = usbd_configuration_block[temp]; /*Holds the ep number in the configuration*/
     temp += 6;        /*6th byte holds the info*/
  }
  
  /* Power UP transceiver and set device detectio logic to internal */
  USBD_WRITE_REG(USBD_DCR,USBD_DCR_TPWDS_BIT|USBD_DCR_RPWDS_BIT|USBD_DCR_DADDIDIS_BIT);

  /* Configure for full-speed or low-speed */
#if USBD_CFG_DEVICE_FULL_SPEED
  USBD_WRITE_REG(USBD_DCR,(USBD_DCR_SPEEDS_BIT | USBD_DCR_SWRS_BIT | USBD_DCR_UCLKS_BIT));
#endif

  USBD_delay(4);  /* Wait for soft reset to be complete */
  USBD_WRITE_REG(USBD_DCR, USBD_DCR_TPWDS_BIT|USBD_DCR_RPWDS_BIT);
  USBD_delay(5);

  /* Check for soft reset complete and UDC is waiting for usb configuration block */
  count = 0;
  do {
    regVal = USBD_READ_REG(USBD_DSR);
    if(count++ > ERR_TIME_OUT)                      
    {
      err_flag = 1;
      break; 
    } 
  }while( (regVal&USBD_DSR_SWR_BIT) && !(regVal&USBD_DSR_DINIT_BIT) );     
  
  if(err_flag)  return (USB_ERROR);

  /* Fill usb configuration block. */
  for( count=0; count<(sizeof(usbd_configuration_block)/2); count++)
	  p16Des[count] = pUsbBlock_16[count];			

  USBD_WRITE_REG(USBD_DCR, USBD_DCR_EOID_BIT);     /* Mark EOID for UDC */

  /* Check for EOID complete and tip bit is set */
  count = 0; 
  do  {
    regVal = USBD_READ_REG(USBD_DSR);
    if(count++ > ERR_TIME_OUT)                      /* Random value */
      {
         err_flag  = 1;
      } 
  }while( regVal & 0x00800080 );     
  
  if(err_flag)  return (USB_ERROR);
    
  USBD_config_device();        /* Configure device properties */
  
  return (USB_OK);
}

/*==========================================================================
 * Function Name :: USBD_do_remote_wakeup()
 *
 * Purpose       :: Implements remote wakeup. 
 *
 * Input         :: None.
 *					
 * Output        :: suspend end interrupt.
 *
 * Return Value  :: 0.
 *
 *==========================================================================*/
IFX_UINT32 USBD_do_remote_wakeup(void)
{ 
  USBD_WRITE_REG(USBD_DCR, USBD_DCR_RSM_BIT);   
  
  return 0;
}


/*==========================================================================
 * Function Name :: USBD_delay()
 *
 * Purpose       :: Implements software delay routine.
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
static void  USBD_delay(IFX_UINT16 dcount)
{
  while(dcount)
  {
	dcount--;
  }
}


/*==========================================================================
 * Function Name :: USBD_fill_HwFifo_ep0()
 *
 * Purpose       :: Implements Tx fifo filling in single address interface for EP0.
 *
 * Input         :: data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: None
 *
 *==========================================================================*/

static int fifo_count = 0;

static void USBD_fill_HwFifo_ep0(IFX_UINT8 *data, IFX_UINT32 length)
{
	IFX_UINT32 timeout;

	if (length == 0) {
		fifo_count = 100;
		return;
	}

	// First transmit multiples of 4 
	while (length >= 4) {
		timeout = 100;
		while (--timeout > 0) {
			if (USBD_CHK_FVLD)
				break;
		}

		USBD_WRITE_REG(USBD_DATA32, *(IFX_UINT32*)data);
		data  += 4;
		length -= 4;
	}

        // transmit rest byte-wise 
        while (length-- > 0) {
		timeout = 100;
		while (--timeout > 0) {
			if (USBD_CHK_FVLD)
				break;
		}

 	        USBD_WRITE_REG((*(IFX_UINT8 *)&(USBD_DATA8)),*data++ );
        }
}



/*==========================================================================
 * Function Name :: USBD_transmit_ep0()
 *
 * Purpose       :: Implements packet transmission for End point 0.
 *
 * Input         :: data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: -1 if error. Otherwise number of bytes transmitted.
 *
 *==========================================================================*/
IFX_SINT32 USBD_transmit_ep0(IFX_UINT8 *pData, 
                         IFX_UINT32 bytesRequested, IFX_UINT8 ZLP_flag)
{

  IFX_SINT32 sentBytes;
  IFX_UINT32 fillSize;
  IFX_UINT32 eBlocks;
  IFX_UINT32 *p32_epp;
  
  /*ZLP Flag has been added for the enumeration process for Tasking due to
  Hardware bug in ZLP Flag*/
  ZLP_flag = 0;
  
  sentBytes = bytesRequested;

  p32_epp	= (IFX_UINT32 *)(USBD_EPUP_BASE);       /* Point to EPUP base address */ 

  USBD_SET_IN_DIR(0);				// set DIR 
  USBD_WRITE_REG( USBD_FCON, 0 )	// select EP0
   
  while (sentBytes > 0)   {                     
	    eBlocks	= p32_epp[3]>>16;		            	/* get NEB value */
	    fillSize = (sentBytes >  8 * eBlocks) ?  8 * eBlocks : sentBytes;
	    USBD_fill_HwFifo_ep0(pData, fillSize);
	    sentBytes -= fillSize ;
	    pData	  += fillSize;	
   }
	
   USBD_SET_DONE_BIT (0);         /* command to UDC for transmission */

	/* Return number of transfered Bytes */
   return (bytesRequested);
}


/*==========================================================================
 * Function Name :: USBD_copy()
 *
 * Purpose       :: An algorithm that offers better performance on wider 
                   memory buses.copies 32 bits at a time rather than 8 bits.
 *
 * Input         :: destination pointer, Source pointer, Length
 *					                
*==========================================================================*/
static void USBD_copy(void *dst, void const *src, IFX_UINT32 len)
{
IFX_UINT32 *plDst = (IFX_UINT32 *) dst;
IFX_UINT32 *plSrc = (IFX_UINT32 *) src; 
IFX_UINT8 *bytePtr_dst;
IFX_UINT8 *bytePtr_src;

    while (len >= 4){
		*plDst++ = *plSrc++;
        len -= 4;
    }
    
    bytePtr_dst = (IFX_UINT8 *) plDst;
    bytePtr_src = (IFX_UINT8 *) plSrc;

    while (len--) {
        *bytePtr_dst++ = *bytePtr_src++;
    } 

} 

/*==========================================================================
 * Function Name :: USBD_fill_HwFifo()
 *
 * Purpose       :: Implements Tx fifo filling with Direct copy to FIFO.
 *
 * Input         :: ep, data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: 0 if datasize is 0. Otherwise number of bytes transmitted.
 *
 *==========================================================================*/

static void USBD_fill_HwFifo ( IFX_UINT8 ep,IFX_UINT8 *data, IFX_UINT32 data_size)
{

	IFX_UINT32 *p32_epp; 

    if(!data_size)   
		return;         /* if no data to be filled */
	
    
	USBD_copy(FIFO_PTR[ep],data,data_size);
       
	/* calculation of correct CAP  with Short Package */   
	CAP[ep] =(IFX_UINT32)FIFO_PTR[ep] + data_size - 1 - (USBD_RAM_BASE);
 
    	/* Calculate EPCP EP address, clean CAP and write new CAP to EPCP[ep].CAP */
	p32_epp = (IFX_UINT32 *)(USBD_EPUP_BASE + (ep * 0x0010));    
	p32_epp[1] &= 0x0000FFFF; 
	p32_epp[1] = ((CAP[ep])<<16)|(p32_epp[1]);                         
        	
	DISABLE_GLOBAL_INTERRUPT();   
	 
	/* increase the private packet counter */      
	epy_pkt_cnt[ep]++;   
      	
	ENABLE_GLOBAL_INTERRUPT();
	       	    	     	     
	/* Force reload of USB Shadow registers */
	USBD_WRITE_REG(USBD_DCR, (USBD_DCR_USBSRL_BIT));    
   
	/* Set endpoint[ep] valid */
	VALID_EP(ep);   	
        	
	/* Calculate private FIFO WRITE pointer	*/
	/* Assign calculated address to FIFO_WR_PTR */
    FIFO_PTR[ep]=(FIFO_PTR[ep]  + (8<<PSZ[ep]));
	
	/* Has FIFO_WR_PTR exceeded the last byte  ? */
	if(FIFO_PTR[ep] >= ((IFX_UINT8 *)USBD_RAM_BASE + BSP[ep] - 1 + ((8<<PSZ[ep]) * BSZ[ep])))
		/* Put private WRITE pointer back to BSP[ep] */
		FIFO_PTR[ep] = (IFX_UINT8 *)(USBD_RAM_BASE + BSP[ep]);

} 

/*==========================================================================
 * Function Name :: USBD_transmit()
 *
 * Purpose       :: Implements packet transmission for EP other than Zero.
 *
 * Input         :: ep number, data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: -1 if error. Otherwise number of bytes transmitted.
 *
 *==========================================================================*/
IFX_SINT32 USBD_transmit(IFX_UINT8 ep, IFX_UINT8 *pData, 
                         IFX_UINT32 bytesRequested, IFX_UINT8 ZLP_flag)
{

	IFX_SINT32 sentBytes = bytesRequested;
	IFX_UINT32 fillSize;
	IFX_UINT32 eSpace, blockSz, eBlocks;
	IFX_UINT32 *p32_epp;   
    
  	p32_epp = (IFX_UINT32 *)(USBD_EPUP_BASE + (ep * 0x0010));        /* Point to EPUP base address */ 
  	blockSz = p32_epp[0] & 0x00000007;				   /* get PSZ value */
  	blockSz = 8<<blockSz;
    
	tx_warning_flag[ep] = 0;    
	
	while (sentBytes > 0)	{       
		if(!tx_warning_flag[ep]) {
     	    eBlocks = BSZ[ep]-epy_pkt_cnt[ep];
			eSpace		= blockSz * eBlocks;          
			fillSize	= (sentBytes > eSpace)? eSpace : sentBytes;	
			USBD_fill_HwFifo(ep, pData, fillSize);
			sentBytes	-= fillSize ;
			pData		+= fillSize;
	    }
	   else
		    break;
	   }	
  /* Return number of transfered Bytes */	  	  
  return (bytesRequested - sentBytes);	  
}


/*==========================================================================
 * Function Name :: USBD_read_HwFifo()
 *
 * Purpose       :: Implements Read from hardware fifo in single address 
 *                  interface.
 *
 * Input         :: ep number, data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: 0 if datasize is 0. Otherwise number of bytes read.
 *
 *==========================================================================*/
IFX_UINT32 USBD_read_HwFifo(IFX_UINT8 ep, IFX_UINT8 *data, 
                            IFX_UINT32 bytesRequested )
{
  IFX_UINT8  *pDes_8 = data;       /* destination buffer pointer */
  IFX_UINT32 bsp=0;
  IFX_UINT32 readSize=0;
  IFX_UINT32 wIndex=0;
  IFX_UINT32 read_epup=0;
  IFX_UINT32 *p32_epp; 

  
  /*
    Note CEDAR_USB fifo Operation : 
    The fifo is writting always from base address once the fifo is read.
    Suppose: base Address is 0x260 after receving 8 bytes from host, the
    UAP becomes 0x268; after cpu reads this data CAP = 0x268. Now if host
    another 5 bytes, UAP = 0x265 whereas CAP is at 0x268. So this not normal
    flow for wrapping functionality. The normal way is increment UAP 
    until it reaches the max-limit & then over-roll it. But here based on
    each packet interrupt roll over is happening. So always (UAP-BSP) is 
    giving the info. 
    Here wIndex = UAP; 
  */
   read_epup =  (USBD_READ_MEM( (USBD_EPUP_BASE + (ep*16)) ));
   wIndex  =  (read_epup >> 16);          /* get uap */       
   bsp     =  (read_epup & 0x0000FFF8);
   
   
   /* Determine actaul number of bytes available for reading.  */
   readSize = (wIndex % (8<<PSZ[ep])); /* Get the readsize in that block */
         
   /* As index starts with 0 */
   readSize++;     
   
   /* Check whether the request exceeds the actual number of bytes available 
     in fifo */    
   readSize = (bytesRequested < readSize) ? bytesRequested : readSize;
  
  /* Get data from USB */
  USBD_copy(pDes_8,FIFO_PTR[ep],readSize); 
    
   
  /* Point p32_epp to EPCP ep address */
  p32_epp = (IFX_UINT32 *)(USBD_EPUP_BASE + (ep * 0x0010));       
   
  /* Clean CAP of EPCP EP */
  p32_epp[1] &= 0x0000FFFF; 
  
     
  /* Calculate new CAP value for EP */
  CAP[ep] =((IFX_UINT32)FIFO_PTR[ep] + (8<<PSZ[ep]) -1 - (USBD_RAM_BASE));
   
  /* Write CAP to EPCP EP USB SFR */
  p32_epp[1] = ((CAP[ep])<<16)|(p32_epp[1]);                         
   
  /* Disable the Global Interrupts */
  DISABLE_GLOBAL_INTERRUPT();                                                                      
  
  /* Increment private NEB couter for EP */	               
  epx_neb_cnt[ep]++;   
  
  /* Clear EPBC.NEB[ep] */     
  p32_epp[3] &= 0x0000FFFF;

  /* Write NEB value to EPCP.NEB[ep] register */
  p32_epp[3] = (((epx_neb_cnt[ep])<<16)|(p32_epp[3])); 
  
  /* Enable the Global Interrupts */
  ENABLE_GLOBAL_INTERRUPT();

     	    	     	     
  /* Hit USBSRL Bit in order to force relead of USB shadow register */
  USBD_WRITE_REG(USBD_DCR, (USBD_DCR_USBSRL_BIT));    
   
  /* Set EP valid after */
  VALID_EP(ep);   	
  
  
  /* Calculation of private READ pointer. Pointer points to last read byte. */
  FIFO_PTR[ep]=(FIFO_PTR[ep]  + (8<<PSZ[ep]));
  /* Has private READ pointer exceeded the last byte of EP Buffer +1?? */
  if(FIFO_PTR[ep] >= ((IFX_UINT8 *)USBD_RAM_BASE + BSP[ep] - 1 + ((8<<PSZ[ep]) * BSZ[ep])))
  {
    // Put private READ pointer back to ep buffer base
    FIFO_PTR[ep] = (IFX_UINT8 *)(USBD_RAM_BASE+ BSP[ep]);
  }	
   														       							       			 				       
  return (readSize);    
}

/*==========================================================================
 * Function Name :: USBD_Rx_process()
 *
 * Purpose       :: Implements Read process. Called by rx irq Handler.
 *
 * Input         :: ep number 
 *					
 * Output        :: Marks the buffer status as filled state so that waiter
 *                  can free himself.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
inline static void USBD_Rx_process ( IFX_UINT8 ep)
{

#ifdef IFX_COMPILER_LINUX
  USB_BUFFER_CB *pCB = NULL;
#else
  volatile USB_BUFFER_CB *pCB = NULL;    /*volatile required for non-OS*/
#endif  

  /* checks pending application buffer  */
  pCB = USB_for_pending_receive( ep ); 	
  
  #ifdef USBD_MANUAL_MODE
  if ( pCB != NULL )
  {                     
             /* Call USBD_read_HwFiFo to read FIFO */
             pCB->bytesReceived = USBD_read_HwFifo(ep, (IFX_UINT8*)pCB->pBuffer,
                                        pCB->bytesRequested); 
    		if(pCB->bytesReceived)         
    		{
    		/* wake-up the wait process. if no waiter than, 
       		get app buffer will return NULL. */
    		pCB->status = RX_STATUS_FILLED;
			#ifdef IFX_COMPILER_LINUX
    				wake_up_interruptible(&tricoreusb_wait_q);      
			#endif
    		}     
   }
   #endif  

  #ifdef USBD_AUTO_MODE
  if( (USBD_CHK_PIPE_OUT (ep))  && (pCB != NULL) )
  {  
     		pCB->bytesReceived = USBD_read_HwFifo_Auto_mode(ep, (IFX_UINT8*)pCB->pBuffer,
                                        pCB->bytesRequested); 
  
   		 if(pCB->bytesReceived)         
   		 {
    		 /* wake-up the wait process. if no waiter than, 
       		 get app buffer will return NULL. */
    		 pCB->status = RX_STATUS_FILLED;
			#ifdef IFX_COMPILER_LINUX
  				wake_up_interruptible(&tricoreusb_wait_q);      
			#endif
    		}  
   }   
   #endif    
}

/*==========================================================================
 * Function Name :: USBD_allocate_bsp()
 *
 * Purpose       :: Keeps track of next avaiable free memory in fifo.
 *
 * Input         :: None.
 *                   
 * Output        :: None.
 *
 * Return Value  :: -1 if error. Otherwise current free memory address
 *
 *==========================================================================*/
inline IFX_SINT16 USBD_allocate_bsp(IFX_UINT16 memSz)
{
 static IFX_UINT16 pNextMemory=0;
 IFX_UINT16 pCurrMemory = (IFX_UINT16)(USBD_FIFO_BASE & 0x0FFF);


	    /* for fresh allocation of memory from start of fifo */
	if (reallocate_bsp ==1 )
	{          
	    pNextMemory = 0;
		reallocate_bsp=0;
	}
 
	if(pNextMemory == 0)
	{
	    pNextMemory = pCurrMemory + memSz;
	}
	else
	{
	   pCurrMemory = pNextMemory; 
	   pNextMemory = memSz + pCurrMemory;
	}
	
	if(pCurrMemory >  (IFX_UINT16)(USBD_FIFO_BASE_END & 0x0FFF))
	{ 
	   return (-1);
	}

	return (pCurrMemory);
}

/*==========================================================================
 * Function Name :: USBD_config_epp()
 *
 * Purpose       :: Initialzes the endpoint property area 
 *
 * Input         ::  usbd_ep_interrupt_configuration,
 *                   usbd_buffer_information
 *					
 * Output        :: None.
 *
 * Return Value  :: 1 if success else 0.
 *
 *==========================================================================*/
inline IFX_SINT32 USBD_config_epp(void)
{
IFX_UINT8 ep=0, ep_count=0;
IFX_UINT16 maxSize=0;
IFX_UINT32 epic_ir_val = 0, epic_node_val=0;
IFX_UINT32 *p32_epp; 
IFX_UINT16 UAM = 1;		 /* For EP == 0 UAM = 1, Manual Mode for EP!=0 */
IFX_UINT16 lPSZ = 0;             /* Packet Size */
IFX_UINT16 lBSZ = 0;		 /* Number of multiple packets */
IFX_SINT16 lBSP = 0;             /* Fifo base address pointer*/

 /* For re-request set this flag to 1 */
 reallocate_bsp = 1;         

 /* Print Buffer size information */
 for (ep_count=0; ep_count < USBD_CFG_TOTAL_EP_USED; ep_count++) 
 {
     ep = ep_info[ep_count];

     /*Point to EPUP base address */
     p32_epp = (IFX_UINT32 *)( (IFX_UINT8 *)USBD_EPUP_BASE + (ep * 0x0010) );        

     /* get source node value */
     epic_node_val = usbd_ep_interrupt_configuration[ep_count][0]; 
     
     /* get ep interrupts enable value */
     epic_ir_val = usbd_ep_interrupt_configuration[ep_count][1];   

     /* Get PSZ and BSZ from configuration */
     lPSZ = usbd_buffer_information[ep_count][0];              
     lBSZ = usbd_buffer_information[ep_count][1];

#ifdef USBD_MANUAL_MODE
     /* Set NEB counter initially to BSZ */
     epx_neb_cnt[ep] = BSZ[ep];

          
     /* Set epy_pkt_cnt intially to zero */
     epy_pkt_cnt[ep] = 0;
#endif     

     /* Calculate max buffer size of endpoint */                     
     maxSize = (8<<lPSZ) * lBSZ;
     /* Get next avaiable free memory in fifo */ 
     lBSP = USBD_allocate_bsp(maxSize);     
     /*if no space, error*/
     if(lBSP < 0)                                    
     { 
        return (-1);
     }
     /*store theses counters for later use.*/
     PSZ[ep] = lPSZ;
     BSZ[ep] = lBSZ;
     BSP[ep] = lBSP;
     
     p32_epp[0]  =  ( (lBSP<<16)| (lBSP | lPSZ) );  
     
     /* CAP = BSP initially */
     p32_epp[1]  =  (lBSP<<16)|((lBSZ << 3) | UAM);
     
#ifdef USBD_MANUAL_MODE
     /*  for other EP's UAM = 0 */
     UAM = 0;
#endif     
     /* Get CAP value from EPCP */
     CAP[ep] = (p32_epp[1] >> 16);
 
     p32_epp[2]  = ( (epic_node_val<<16)| (epic_node_val<<20)| 
                     (epic_node_val<<24)| (epic_node_val<<28)| epic_ir_val );

     /* NEB = BSZ initially */
     p32_epp[3]  =  (lBSZ << 16) | lBSZ;                

#ifdef USBD_MANUAL_MODE

   	 USBD_WRITE_REG(USBD_DCR, (USBD_DCR_USBSRL_BIT|USBD_DCR_CPUSRL_BIT));    
	   
     /* Set FIFO_PTR initially to BSP[ep] */
     FIFO_PTR[ep] = (IFX_UINT8 *)(USBD_RAM_BASE + BSP[ep]);
#endif     
     }  
  
return 1; /*Success*/
}


/*==========================================================================
 * Function Name :: USBD_Initialize_device_interrupts()
 *
 * Purpose       :: Initializes device related interrupts 
 *
 * Input         :: Configured device interrupts value.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
inline void USBD_Initialize_device_interrupts(void)
{
  /*All device irqs on line 0*/
  USBD_WRITE_REG(USBD_DINP, usbd_device_interrupt_configuration[0][0]);   

#if (dev_isr == 1)  
  /*Enbale device irqs on line 0*/
  // firstly we will poll only the device events
  USBD_WRITE_REG(USBD_DIER, usbd_device_interrupt_configuration[0][1]);   
#endif
  
  /*Clear  all device irqs on line 0 and enable node 0 */
  USBD_WRITE_REG(USBD_DIRST,0xFFFF);   
  USBD_WRITE_REG(USBD_SRC0, 0x1000|USB_SRC0_PRIORITY);   
}

/*==========================================================================
 * Function Name :: USBD_Initialize_endpoints_interrupts()
 *
 * Purpose       :: Initializes endpoint related interrupts 
 *
 * Input         :: None
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
inline void USBD_Initialize_endpoints_interrupts(void)
{

/*Clear all EP nodes*/
#if USB_SRC7_PRIORITY
    USBD_WRITE_REG(USBD_SRC7, 0x4000|USB_SRC7_PRIORITY);   
#endif

#if USB_SRC6_PRIORITY
    USBD_WRITE_REG(USBD_SRC6, 0x4000|USB_SRC6_PRIORITY);   
#endif

#if  USB_SRC5_PRIORITY
    USBD_WRITE_REG(USBD_SRC5, 0x4000|USB_SRC5_PRIORITY);  
#endif

#if  USB_SRC4_PRIORITY
    USBD_WRITE_REG(USBD_SRC4, 0x4000|USB_SRC4_PRIORITY);   
#endif

#if  USB_SRC3_PRIORITY
    USBD_WRITE_REG(USBD_SRC3, 0x4000|USB_SRC3_PRIORITY);  
#endif

#if  USB_SRC2_PRIORITY
    USBD_WRITE_REG(USBD_SRC2, 0x4000|USB_SRC2_PRIORITY);   
#endif

#if  USB_SRC1_PRIORITY
    USBD_WRITE_REG(USBD_SRC1, 0x4000|USB_SRC1_PRIORITY);   
#endif

    USBD_WRITE_REG(USBD_EPIRST0, 0x1F1F1F1F);   /*Clear EP0...3 interrupts*/
    USBD_WRITE_REG(USBD_EPIRST1, 0x1F1F1F1F);   /*Clear EP4...7 interrupts*/
    USBD_WRITE_REG(USBD_EPIRST2, 0x1F1F1F1F);   /*Clear EP8...11 interrupts*/

/*Enable all EP nodes*/
#if USB_SRC7_PRIORITY
    USBD_WRITE_REG(USBD_SRC7, 0x1000|USB_SRC7_PRIORITY);   
#endif

#if USB_SRC6_PRIORITY
    USBD_WRITE_REG(USBD_SRC6, 0x1000|USB_SRC6_PRIORITY);   
#endif

#if  USB_SRC5_PRIORITY
    USBD_WRITE_REG(USBD_SRC5, 0x1000|USB_SRC5_PRIORITY);  
#endif

#if  USB_SRC4_PRIORITY
    USBD_WRITE_REG(USBD_SRC4, 0x1000|USB_SRC4_PRIORITY);   
#endif

#if  USB_SRC3_PRIORITY
    USBD_WRITE_REG(USBD_SRC3, 0x1000|USB_SRC3_PRIORITY);  
#endif

#if  USB_SRC2_PRIORITY
    USBD_WRITE_REG(USBD_SRC2, 0x1000|USB_SRC2_PRIORITY);   
#endif

#if  USB_SRC1_PRIORITY
    USBD_WRITE_REG(USBD_SRC1, 0x1000|USB_SRC1_PRIORITY);   
#endif
    
}



/*==========================================================================
 * Function Name :: USBD_set_endpoint_direction()
 *
 * Purpose       :: sets the direction of endpoints and validate the ep
 *                  for UDC according to the config setting by host.
 *
 * Input         :: None.
 *                   
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
inline void USBD_set_endpoint_direction(void)
{
udc_cfg_block *pudcBlock = (udc_cfg_block *)usbd_configuration_block;
IFX_UINT8 BlockSz = sizeof (usbd_configuration_block);
IFX_UINT8 numOfeps = (BlockSz/6);
IFX_UINT8 ep;
IFX_UINT32 newCFGval = USBD_READ_REG(USBD_CNFR); /* read from hardware */
IFX_UINT8 newIf = 0, newAs=0;


newAs =  ( (newCFGval) & 0x0F); /* derive alternate & interface numbers */
newIf =  ( (newCFGval) >> 4);

  

/* Note that 
 * a. there are no separate counters provided for BSZ, FIFO_CNT etc for fifo opertaions.
 *    i.e these are common to both logical and physical endpoints. So the other operations are
 *    transparent...
 * b. Since CAP (and hence UAP pointers) are updated according to the FIFO_CNT, no need to flush
 *    them separately.
 */
	for(ep=0; ep < numOfeps;ep++) {
		/* do this for the active configurations choosen by the host....*/
		if( (pudcBlock->epIF == newIf) && (pudcBlock->epAS == newAs) ) {			
				/* check for IN packet or OUT packet */
			if(pudcBlock->epDir) {				
				USBD_SET_IN_DIR( pudcBlock->epNum );
		        /* Set packet counter intially to zero */
			}
			else {		
		        USBD_SET_OUT_DIR( pudcBlock->epNum );
				/* validate the out packet for UDC */
	 	        VALID_EP(pudcBlock->epNum);   		
		       /* Set NEB counter initially to BSZ */

			}
		
		}
		pudcBlock++;                      /* goto next block */
	}
  
}



/*==========================================================================
 * Function Name :: USBD_config_device()
 *
 * Purpose       :: Device configuration function.
 *
 * Input         :: None.
 *                   
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
inline void USBD_config_device(void)
{

  USBD_config_epp(); 

  USBD_Initialize_device_interrupts();			

}

/*==========================================================================
 * Function Name :: USBD_configuration_handler()
 *
 * Purpose       :: Handles the configuration request change from host.
 *               :: Should be processed only if any alternate setting 
 *                  is changed. Currently re-initializes all, to handle 
 *                  any bug in this driver.
 * 
 * Input         :: None.
 *
 * Output        :: None.
 *
 * Return Value  :: none.
 *
 * Others        :: All other current requests are cancelled due to this 
 *                  reset.
 *==========================================================================*/
inline void USBD_configuration_handler( void )
{
#ifndef IFX_COMPILER_LINUX
  USB_application_initialize();
#endif
  USBD_set_endpoint_direction();			
  USBD_Initialize_endpoints_interrupts();
}
	
/*==========================================================================
 * Function Name :: USBD_Device_Interrupt_handler()
 *
 * Purpose       :: Handles all device interrupts
 *
 * Input         :: None
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC0_PRIORITY, USBD_Device_Interrupt_handler_1)
#else /* for GNU and elinux  */
inline void USBD_Device_Interrupt_handler( void )
#endif
{

	IFX_UINT32 read_DIRR = USBD_READ_REG(USBD_DIRR);		// read actual requests

#if (dev_isr == 0)	
	if (read_DIRR == 0)
		return;									// nothing to do
#endif

	USBD_WRITE_REG(USBD_DIRST, read_DIRR);		// immediately reset all of them

	if ((read_DIRR & (USBD_DIRR_SE0I | USBD_DIRR_STI | USBD_DIRR_SUI | USBD_DIRR_CFI | USBD_DIRR_DDI)) == 0)
		return;					// nothing to do...
		
 	/*****************************************************************************/
 	/* SE0I -  reset issued by host */
 	/*****************************************************************************/
	if (read_DIRR & USBD_DIRR_SE0I) {		/* SE0I -  reset issued by host */  

		IFX_UINT32* p32_epp;
		IFX_UINT32	base;
			
		//USBD_config_device();                 /* Configure device properties */
		USBD_config_epp();
	        
		// Clears endpoint - reset the buffer & control bits of both UDC & CPU 	         
		USBD_CLEAR_EP(0);
   
		p32_epp	= (IFX_UINT32 *)(USBD_EPUP_BASE);       /* Point to EPUP base address */ 
		base	= p32_epp[0] & 0xFFF8;

		// reset all the FIFO-Pointers
		p32_epp[0]  = (p32_epp[0] & 0xFFFF) | (base << 16);	// set USB Pointer
	        p32_epp[1]  = (p32_epp[1] & 0xFFFF) | (base << 16);	// set CPU Pointer
	        p32_epp[3]  = ((p32_epp[1] & 0xFFF8) >> 3) | ((p32_epp[1] & 0xFFF8) << 13);
		USBD_CPLPR  = base;			// set also CPU FIFO-Base

	    usb_device.status = USB_RESET;
	    return;			// no further check needed
	} 

	/*****************************************************************************/
 	/* STI - Status */
 	/*****************************************************************************/
	if (read_DIRR & USBD_DIRR_STI) {			  /* STI - Status */
	
	if (STI_count==STI_enlarge){			//STI enlage for very fast Hosts like SIS and SIS + Hub
		if (USBD_READ_REG(USBD_EPDIR) & 0x01) {    /* if IN make it OUT */
 
			// to clear the endpoint 
			
			IFX_UINT32* p32_epp;
			IFX_UINT32	base;
			
			/* Clears endpoint - reset the buffer & control bits of both UDC & CPU */ 	         
			USBD_CLEAR_EP(0);
   
			p32_epp	= (IFX_UINT32 *)(USBD_EPUP_BASE);       /* Point to EPUP base address */ 
			base	= p32_epp[0] & 0xFFF8;

			// reset all the FIFO-Pointers
			p32_epp[0]  = (p32_epp[0] & 0xFFFF) | (base << 16);	// set USB Pointer
		        p32_epp[1]  = (p32_epp[1] & 0xFFFF) | (base << 16);	// set CPU Pointer
		        p32_epp[3]  = ((p32_epp[1] & 0xFFF8) >> 3) | ((p32_epp[1] & 0xFFF8) << 13);
			USBD_CPLPR  = base;			// set also CPU FIFO-Base

			USBD_SET_OUT_DIR( 0 );  
		}
		STI_count=0; 
		VALID_EP(0);
	}	
		STI_count++;

	}	
	
    	/*****************************************************************************/
 	/* SUI - Setup Hanlder */
 	/*****************************************************************************/
	if(read_DIRR & USBD_DIRR_SUI) {        /* SUI - Setup Handler */
	
		USB_setUpHandler();

		read_DIRR = USBD_READ_REG(USBD_DIRR);		// read again actual requests
		USBD_WRITE_REG(USBD_DIRST, read_DIRR);		// immediately reset all of them
	}	           
		
 	/*****************************************************************************/
 	/* CFI - Configuration Handler */
 	/*****************************************************************************/
	if (read_DIRR & USBD_DIRR_CFI) {			/* CFI - Configuration Handler */

		USBD_configuration_handler();
		usb_device.status = USB_CONFIGURED;	 /* Device configured */ 
	}  

 	/*****************************************************************************/
 	/* DDI - Device Detached */
 	/*****************************************************************************/
	if(read_DIRR & USBD_DIRR_DDI)			/* DDI - Device Detached */
		usb_device.status = USB_IDLE;	 

}

/*==========================================================================
 * Function Name :: USBD_get_device_state()
 *
 * Purpose       :: device state interface
 *
 * Input         :: None.
 *                   
 * Output        :: None.
 *
 * Return Value  :: Returns the usb device state.
 *
 *==========================================================================*/
IFX_UINT8 USBD_get_device_state( void )
{
  return( usb_device.status); 
}

/*==========================================================================
 * Function Name :: USBD_Rx_irq_process()
 *
 * Purpose       :: IRQ Handler for Receive end points
 *
 * Input         :: ep Number and epir bit mask value.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *                   
*==========================================================================*/
inline static void USBD_Rx_irq_process ( IFX_UINT8 ep)
{  
#ifdef USBD_MANUAL_MODE

IFX_UINT32 *p32_epp;

/* Get EPBC.NEB [ep] address */
p32_epp = (IFX_UINT32 *)( (IFX_UINT8 *)USBD_EPUP_BASE + (ep * 0x0010) ); 

/* Clear EPBC.NEB[ep] */
p32_epp[3] &= 0x0000FFFF;


/* Decrement the NEB count for Out */
epx_neb_cnt[ep]--;

/* Write new NEB value into EPBC.NEB [ep] */
p32_epp[3] = (((epx_neb_cnt[ep])<<16)|(p32_epp[3])); 


/* Set EP invalid if NEB count == 0 */ 
if(epx_neb_cnt[ep] == 0)
{ 
  INVALID_EP(ep);
}
#endif

#ifdef IFX_COMPILER_LINUX

  wake_up_interruptible(&tricoreusb_wait_q);      

#endif

}

/*==========================================================================
 * Function Name :: USBD_Tx_irq_process()
 *
 * Purpose       :: IRQ Handler for Transmit end points
 *
 * Input         :: ep Number and epir bit mask value.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *                   
 *==========================================================================*/
inline static void USBD_Tx_irq_process ( IFX_UINT8 ep)
{   				
#ifdef USBD_MANUAL_MODE
/* Number of multiple packets */

IFX_UINT32 *p32_epp; 

INVALID_EP(ep); 
if(epy_pkt_cnt[ep] > 0)
{
/* Get EPBC.NEB[ep] address */
p32_epp = (IFX_UINT32 *)( (IFX_UINT8 *)USBD_EPUP_BASE + (ep * 0x0010) );

/* Clear EPBC.NEB[ep] */    
p32_epp[3] &= 0x0000FFFF;

/* Decrement packet count */
epy_pkt_cnt[ep]--;   

/* Write BSZ[ep]-pkt_cnt = NEB value to EPCP.NEB[ep] register */
p32_epp[3] = ((BSZ[ep] - epy_pkt_cnt[ep])<<16)|(p32_epp[3]);
}

/* Set Ep invalid if packet count <= 0 */
if(epy_pkt_cnt[ep] <= 0)
{
  INVALID_EP(ep); 
}     
else 
{
   VALID_EP(ep);
}
#endif
}

/*==========================================================================
 * Function Name :: poll_rx()
 *
 * Purpose       :: Receives Packets from BulkOut FIFO as long neb_cnt< BSZ(ep)
 *
 * Input         :: endpoint number
 *					                
*==========================================================================*/
void USBD_poll_rx(IFX_UINT8 ep)
{ 
#ifdef USBD_AUTO_MODE
    /*IFX_UINT32 *p32_epp;
    // Check of NEB(ep < BSZ(ep)!  Mandatory! 
    p32_epp = (IFX_UINT32 *)( (IFX_UINT8 *)USBD_EPUP_BASE + (ep * 0x0010) );
    if((p32_epp[3]>>16) < BSZ[ep]) {
    */
      USBD_Rx_process( ep );
    //}
#endif

#ifdef USBD_MANUAL_MODE
if (epx_neb_cnt[ep]<BSZ[ep])
     USBD_Rx_process( ep );
#endif

} 

/*==========================================================================
 * Function Name :: USBD_Warning_level_Interrupt()
 *
 * Purpose       :: For handling the warning level interrupt
 *
 * Input         :: endpoint number
 *					                
*==========================================================================*/
inline void USBD_Warning_level_Interrupt(IFX_UINT32 temp, IFX_UINT8 ep )
{	  
IFX_UINT8 *pReg = (IFX_UINT8*)(USBD_EPIRST_BASE + (ep*4));

   if( USBD_EPIR_WNI_BIT & temp )
    {
	  *pReg = (USBD_EPIR_WNI_BIT);      /* clear WNI bit, again set by hardware, if reqd. */
	  tx_warning_flag[ep] = 1;          	  
    }
     
}

/*==========================================================================
 * Function Name :: USBD_receive_acknowledge_Interrupt()
 *
 * Purpose       :: Handle only ACK for RX pipe
 *
 * Input         :: endpoint number
 *					                
*==========================================================================*/


inline void USBD_receive_acknowledge_Interrupt(IFX_UINT32 temp, IFX_UINT8 ep)
{
IFX_UINT8 *pReg = (IFX_UINT8*)(USBD_EPIRST_BASE + (ep*4));
   if( USBD_EPIR_ACK_BIT & temp )
    {	   
	   *pReg = (USBD_EPIR_ACK_BIT);     
	    USBD_Rx_irq_process( ep );  
    }
      
}


/*==========================================================================
 * Function Name :: USBD_transmit_acknowledge_Interrupt()
 *
 * Purpose       :: Handle only ACK for TX pipe
 *
 * Input         :: endpoint number
 *					                
*==========================================================================*/

inline void USBD_transmit_acknowledge_Interrupt(IFX_UINT32 temp, IFX_UINT8 ep)
{
IFX_UINT8 *pReg = (IFX_UINT8*)(USBD_EPIRST_BASE + (ep*4));

   if( USBD_EPIR_ACK_BIT & temp )
    {
	   *pReg = (USBD_EPIR_ACK_BIT);      
      	   USBD_Tx_irq_process( ep ); 
    }
      
}


/*==========================================================================
 * Function Name :: USBD_EP1_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 1 ACK interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 * Info          :: This Endpoint is configured for transmit. If the                    
 *                  configuration need to be changed, the ISR for EP1   
 *                  needs also to be adapted for the new settings! 
 *                   
 *                   
 *==========================================================================*/
#if USB_SRC1_PRIORITY	 /*Compile if node priority is defined*/
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC1_PRIORITY, USBD_EP1_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP1_Interrupt_handler(void)
#endif
{
IFX_UINT32 read_EPIR0 = USBD_READ_REG(USBD_EPIR0);
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR0;     /*pointer to IR read value*/
   	
   if ( USBD_CHK_PIPE_IN( 1 ) ) {
   	
   	USBD_transmit_acknowledge_Interrupt( pIR_8[1], 1);			 
	USBD_Warning_level_Interrupt( pIR_8[1], 1 );
      }
      else
      {
	USBD_receive_acknowledge_Interrupt( pIR_8[1], 1);  
      }  
	/* 
	Clears the soucre of the interrupt bit. 
	*/
	USBD_WRITE_REG(USBD_EPIRST0, read_EPIR0);   
}
#endif

/*==========================================================================
 * Function Name :: USBD_EP2_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 2 interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 * Info          :: This Endpoint is configured for receive. If the                    
 *                  configuration need to be changed, the ISR for EP2   
 *                  needs also to be adapted for the new settings! 
 *                   
 *                   
 *==========================================================================*/ 
#if USB_SRC2_PRIORITY	 /*Compile if node priority is defined*/
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC2_PRIORITY, USBD_EP2_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP2_Interrupt_handler(void)
#endif
{
IFX_UINT32 read_EPIR0 = USBD_READ_REG(USBD_EPIR0);
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR0;     /*pointer to IR read value*/

   if ( USBD_CHK_PIPE_IN( 2 ) ) {
    USBD_transmit_acknowledge_Interrupt( pIR_8[2], 2);
	USBD_Warning_level_Interrupt( pIR_8[2], 2 );
      }
      else
      {
      	//EP2 is configured as recieve
	USBD_receive_acknowledge_Interrupt( pIR_8[2], 2);  
      }  
	
	/* 
	Clears the soucre of the interrupt bit. 
	*/
	USBD_WRITE_REG(USBD_EPIRST0, read_EPIR0);   /*Clear the source*/
}	  
#endif

/*==========================================================================
 * Function Name :: USBD_EP3_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 3 interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *                   
 *==========================================================================*/
#if USB_SRC3_PRIORITY	 /*Compile if node priority is defined*/
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC3_PRIORITY, USBD_EP3_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP3_Interrupt_handler(void)
#endif
{
IFX_UINT32 read_EPIR0 = USBD_READ_REG(USBD_EPIR0);
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR0;     /*pointer to IR read value*/

      if ( USBD_CHK_PIPE_IN( 3 ) ) {
    	USBD_transmit_acknowledge_Interrupt( pIR_8[3], 3);
	USBD_Warning_level_Interrupt( pIR_8[3], 3 );
      }
      else
      {
      	//EP3 is configured as recieve
	USBD_receive_acknowledge_Interrupt( pIR_8[3], 3);  
      }  

     USBD_WRITE_REG(USBD_EPIRST0, read_EPIR0);   
}
#endif


/*==========================================================================
 * Function Name :: USBD_EP4_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 4 ACK interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/

#if USB_SRC4_PRIORITY	 /*Compile if node priority is defined*/
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC4_PRIORITY, USBD_EP4_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP4_Interrupt_handler(void)
#endif
{
IFX_UINT32 read_EPIR1 = USBD_READ_REG(USBD_EPIR1);
IFX_UINT8 ep=4;
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR1;      /*pointer to IR read value*/
IFX_UINT8 temp=0; 

    temp = pIR_8[(ep-4)];            /* Get epir value */
   if ( USBD_CHK_PIPE_IN( ep ) ) {
   	
   	USBD_transmit_acknowledge_Interrupt( temp, ep);
   	USBD_Warning_level_Interrupt( temp, ep );			 
   }
  else { 	
	USBD_receive_acknowledge_Interrupt( temp, ep);
  }
    USBD_WRITE_REG(USBD_EPIRST1, read_EPIR1);  
}
#endif

/*==========================================================================
 * Function Name :: USBD_EP5_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 5 ACK interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/

#if USB_SRC5_PRIORITY	 /*Compile if node priority is defined*/
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC5_PRIORITY, USBD_EP5_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP5_Interrupt_handler(void)
#endif
{

IFX_UINT32 read_EPIR1 = USBD_READ_REG(USBD_EPIR1);
IFX_UINT8 ep=5;
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR1;      /*pointer to IR read value*/
IFX_UINT8 temp=0; 

    temp = pIR_8[(ep-4)];            /* Get epir value */

   if ( USBD_CHK_PIPE_IN( ep ) ) {
   	
   	USBD_transmit_acknowledge_Interrupt( temp, ep );
   	USBD_Warning_level_Interrupt( temp, ep );			 
   }
   else { 	
	USBD_receive_acknowledge_Interrupt( temp, ep );
   }
    USBD_WRITE_REG(USBD_EPIRST1, read_EPIR1);          
}
#endif

/*==========================================================================
 * Function Name :: USBD_EP6_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 6 ACK interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/

#if USB_SRC6_PRIORITY	 /*Compile if node priority is defined*/
/* Handles both EP6 and EP7 pipes */
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC6_PRIORITY, USBD_EP6_to_EP7_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP6_to_EP7_Interrupt_handler(void)
#endif
{
IFX_UINT32 read_EPIR1 = USBD_READ_REG(USBD_EPIR1);
IFX_UINT8 ep=6;
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR1;      /*pointer to IR read value*/
IFX_UINT8 temp=0; 


   for(ep=6;ep<8;ep++) {
		
	    temp = pIR_8[(ep-4)];            /* Get epir value */

	   if ( USBD_CHK_PIPE_IN( ep ) ) {
	   	
	   	USBD_transmit_acknowledge_Interrupt( temp, ep );
	   	USBD_Warning_level_Interrupt( temp, ep );			 
	   }
	   else { 	
		USBD_receive_acknowledge_Interrupt( temp, ep );
	   }
   }   
      USBD_WRITE_REG(USBD_EPIRST1, read_EPIR1);  
}
#endif

/*==========================================================================
 * Function Name :: USBD_EP7_Interrupt_handler()
 *
 * Purpose       :: Handler for end point 7 ACK interrupts
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: None.
 *
 *==========================================================================*/

#if USB_SRC7_PRIORITY	 /*Compile if node priority is defined*/
/* Handles EP8 to EP11 endpoints */
#if IFX_COMPILER_TASKING
IFX_ISR_FUNC (USB_SRC7_PRIORITY, USBD_EP8_to_EP11_Interrupt_handler)
#else /* for GNU and elinux  */
inline void USBD_EP8_to_EP11_Interrupt_handler(void)
#endif
{
IFX_UINT32 read_EPIR2 = USBD_READ_REG(USBD_EPIR2);
IFX_UINT8 ep=8;
IFX_UINT8 *pIR_8 = (IFX_UINT8 *)&read_EPIR2;      /*pointer to IR read value*/
IFX_UINT8 temp=0; 


 /* check for all EPs */
    for( ep = 8; ep < 12; ep++) {

	    temp = pIR_8[(ep-8)];            /* Get epir value */

	   if ( USBD_CHK_PIPE_IN( ep ) ) {
	   	
	   	USBD_transmit_acknowledge_Interrupt( temp, ep );
	   	USBD_Warning_level_Interrupt( temp, ep );			 
	   }
	   else { 	
		USBD_receive_acknowledge_Interrupt( temp, ep );
	   }
   }	
	
    USBD_WRITE_REG(USBD_EPIRST2, read_EPIR2);  
}
#endif

/* For GNU compiler */
#ifdef IFX_COMPILER_GNU 
/*==========================================================================
 * Function Name :: USBD_register_isr()
 *
 * Purpose       :: Registers the USB interrupts with the kernel.
 *
 * Input         :: None.
 *					
 * Output        :: None.
 *
 * Return Value  :: 1.
 *
 *==========================================================================*/
IFX_UINT8 USBD_register_isr (void)
{
    IFX_ISR_INIT (USB_SRC0_PRIORITY, USBD_Device_Interrupt_handler, 0);  			/*control endpoint ISR*/

#if USB_SRC1_PRIORITY	
    IFX_ISR_INIT (USB_SRC1_PRIORITY, USBD_EP1_Interrupt_handler, 0);		
#endif

#if USB_SRC2_PRIORITY	
    IFX_ISR_INIT (USB_SRC2_PRIORITY, USBD_EP2_Interrupt_handler, 0);
#endif

#if USB_SRC3_PRIORITY	
    IFX_ISR_INIT (USB_SRC3_PRIORITY, USBD_EP3_Interrupt_handler, 0);
#endif

#if USB_SRC4_PRIORITY	
    IFX_ISR_INIT (USB_SRC4_PRIORITY, USBD_EP4_Interrupt_handler, 0);
#endif

#if USB_SRC5_PRIORITY	
    IFX_ISR_INIT (USB_SRC5_PRIORITY, USBD_EP5_Interrupt_handler, 0);
#endif

#if USB_SRC6_PRIORITY	
    IFX_ISR_INIT (USB_SRC6_PRIORITY, USBD_EP6_to_EP7_Interrupt_handler, 0);
#endif

#if  USB_SRC7_PRIORITY
    IFX_ISR_INIT (USB_SRC7_PRIORITY, USBD_EP8_to_EP11_Interrupt_handler, 0);
#endif

return 1;
}
#endif


/*==========================================================================
 * Function Name :: USBD_transmit_Auto_mode()
 *
 * Purpose       :: Implements packet transmission.
 *
 * Input         :: ep number, data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: -1 if error. Otherwise number of bytes transmitted.
 *
 * Others        :: ZLP transmission implementation pending.
 *==========================================================================*/
IFX_SINT32 USBD_transmit_Auto_mode(IFX_UINT8 ep, IFX_UINT8 *pData, 
                         IFX_UINT32 bytesRequested, IFX_UINT8 ZLP_flag)
{
  IFX_SINT32 sentBytes = bytesRequested;
  IFX_UINT32 fillSize = 0;
  IFX_SINT32 filled_size =0 ; 
  IFX_UINT32 *p32_epp;
  IFX_UINT32 eSpace=0, blockSz=0, eBlocks=0;
  IFX_UINT8  *pSrc_8 = pData;
  IFX_UINT32 timeout;
  
  //ZLP Flag has been added for the enumeration process for Tasking due to
  //Hardware bug in ZLP Flag
  ZLP_flag = 0;

  // Clear ZLPEN Bit 
  USBD_DISABLE_ZERO_PACKET(ep);          
  
  // Get PSZ Value
  p32_epp	= (IFX_UINT32 *)(USBD_EPUP_BASE + (ep * 0x0010));    //Point to EPUP base address  
  blockSz = p32_epp[0] & 0x00000007;				     // get PSZ value 
  blockSz = 8<<blockSz;
  
  // Select Endpoint  
  USBD_WRITE_REG( USBD_FCON, ep )	
   
  // Wait until EP1 FIFO valid
  timeout = 100;
  while (--timeout > 0) {
    if (USBD_CHK_EP1FVLD)
      break;
  }
     
  while (sentBytes > 0)   {                     
    	   eBlocks = p32_epp[3]>>16;				            		 // get NEB value 			    				    
           eSpace = blockSz * eBlocks;           
           fillSize = (sentBytes > eSpace)? eSpace : sentBytes;
    	   filled_size = USBD_fill_HwFifo_Auto_mode(ep, pData, fillSize);	
           sentBytes -= filled_size ;
           pSrc_8 += filled_size ;
  }

  // Return number of transfered Bytes 	  	  
  return (bytesRequested - sentBytes);	 

}


/*==========================================================================
 * Function Name :: USBD_fill_HwFifo_Auto_mode()
 *
 * Purpose       :: Implements Tx fifo filling.
 *
 * Input         :: data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: 0 if datasize is 0. Otherwise number of bytes transmitted.
 *
 *==========================================================================*/
IFX_SINT32 USBD_fill_HwFifo_Auto_mode(IFX_UINT8 ep, IFX_UINT8 *data, IFX_UINT32 data_size)
{
  IFX_UINT8  *pSrc_8 = data;
  IFX_UINT32 nBytes = 0, temp = data_size;
  IFX_UINT32 *p_32;

  if(!data_size) return 0;         // if no data to be filled 

  // First transmit all multiples of 4 
  p_32 = (IFX_UINT32 *)pSrc_8;
  nBytes = 0;                    // number of bytes to be read   
  while(temp >= 4) {
    USBD_WRITE_REG(USBD_DATA32, *p_32); 
    p_32++;
    temp -= 4;       
    nBytes += 4;	
  }

  // Then transmit all byte-wise 
  pSrc_8  = (IFX_UINT8 *)(p_32);
  while (nBytes < data_size) {  
    USBD_WRITE_REG(  (*(IFX_UINT8 *)&(USBD_DATA8) ),*pSrc_8 );
    pSrc_8++;
    nBytes++;	
  }
 
  return ( nBytes );         // return number of bytes transmitted 
} 


/*==========================================================================
 * Function Name :: USBD_read_HwFifo_Auto_mode()
 *
 * Purpose       :: Implements Read from hardware fifo 
 *
 * Input         :: ep number, data pointer & number of bytes to be 
 *                  transmitted.
 *					
 * Output        :: None.
 *
 * Return Value  :: 0 if datasize is 0. Otherwise number of bytes read.
 *
 *==========================================================================*/
IFX_SINT32 USBD_read_HwFifo_Auto_mode(IFX_UINT8 ep, IFX_UINT8 *data, 
                            IFX_UINT32 bytesRequested )
{
  IFX_UINT32 wIndex_uap=0, readSize=0, nBytes=0, bsp=0, temp=0;
  IFX_UINT8  *pDes_8 = data;       // destination buffer pointer 
  IFX_UINT32 read_epup=0;
  IFX_UINT32 *p_32=0 ;            // 32 bit pointer 
  IFX_UINT32 timeout;
 
  // Wait until EP2 FIFO valid
  timeout = 1000;
  while (--timeout > 0) {
    if (USBD_CHK_EP2FVLD)
      break;
  }

   // Select Endpoint 
   USBD_SELECT_EP ( ep );
   // Get UAP and BSP
   read_epup =  (USBD_READ_MEM( (USBD_EPUP_BASE + (ep*16)) ));
   wIndex_uap  =  (read_epup >> 16);                  // get UAP 
   bsp     =  (read_epup & 0x0000FFF8);           
   
   // Get CAP
   /* for future use
   read_epcp =  (USBD_READ_MEM( (USBD_EPCP_BASE + (ep*16)) ));
   wIndex_cap  =  (read_epcp >> 16);                  // get CAP 
   */
  
   // A smart routine should be implemented, which calculates the 
   // correct readSize by CAP, UAP and BSP
   readSize = 64;
         
   temp = readSize;

   // First read all multiples of 4 
   p_32 = (IFX_UINT32 *)pDes_8;
   nBytes = 0;                    // number of bytes to be read   
   
   while(temp >= 4) {
     *p_32 = USBD_READ_REG(USBD_DATA32); 
     p_32++;
     temp -= 4;       
     nBytes += 4;	
   }

   // Then read all byte-wise 
   pDes_8  = (IFX_UINT8 *)(p_32);
   while (nBytes < readSize) {  
     *pDes_8 = (IFX_UINT8)USBD_READ_REG(USBD_DATA8);  
     pDes_8++; 
     nBytes++;	
   }
  
    return ( nBytes ); 

}



