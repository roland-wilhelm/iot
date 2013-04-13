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
** @FILENAME@:       eth_iil.c
** @VERSION@:        2.4
** @DATE@:           20/1/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file provides all interfaces to the user application.
**
** =============================================================================
** References: ETH API book
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby,Rajesh    Release after code review.
** 06/04/2004      Ruby					  Rizal's comments
** 29/04/2004      Ruby					  Change in the DMUT queuing strategy
** 12/11/2004      Badarinath Jayashree   Version number bumped to 2.3 to match
**		           (IFIN SCC AI)          the version of the C files
**                                        Casting added for ETH_HW_TBCC and 
**                                        ETH_HW_DTISFIFO to remove Tasking warnings
** 20/1/2006       Mahesh Sriram Babu     This file has been modified to support
**                 (IFIN CSW AIM)         cache with GNU Compiler (Note: The flag
**                                        ETH_CFG_USE_CACHE needs to be set in 
**                                        eth_cfg.h file
**                          
** @CHANGE_HISTORY@
** =============================================================================
*/

/*
  Include all the required header files needed for this file
*/
#include "ETH_API.h"
#include "cache.h"
/*
  The following pre-proccessor directives check if the system HAL matches the 
  implemententation dependent layer for the Ethernet HAL. If these do not match
  then the compilation is stopped with an error to indicate this conflict to 
  the user.
  This check has been introduced because the IDL file names are identical, 
  regardless of the product they are written for, this could easily result in the 
  wrong files being used.
*/
#if SYS_PRODUCT != ETH_PRODUCT
  #error ETH HAL Error:\
 Either ETH_IDL.H file is incorrect or else the wrong System HAL is being used.
#endif


/*
  The following preprocessor directive check if the compatible files are 
  included for compilation. If these do not match then compilation will stopped
  with an error to indicate this conflict to the user.
  The define ETH_HW_API_VER_MAJ is defined in ETH_IDL.H file.
*/
#if (ETH_HW_API_VER_MAJ > 0)
# error ETH HAL Error:\
 Incompatible components, please make sure you have the latest ETH HAL distribution.
#endif

#if ETH_CFG_USE_CAM == 1

IFX_UINT8 ETH_macaddr[20][6] = {
 ETH_CFG_MACADDRS0, ETH_CFG_MACADDRS1, ETH_CFG_MACADDRS2, ETH_CFG_MACADDRS3,
 ETH_CFG_MACADDRS4, ETH_CFG_MACADDRS5, ETH_CFG_MACADDRS6, ETH_CFG_MACADDRS7,
 ETH_CFG_MACADDRS8, ETH_CFG_MACADDRS9, ETH_CFG_MACADDRS10, ETH_CFG_MACADDRS11,
 ETH_CFG_MACADDRS12, ETH_CFG_MACADDRS13, ETH_CFG_MACADDRS14, ETH_CFG_MACADDRS15,
 ETH_CFG_MACADDRS16, ETH_CFG_MACADDRS17, ETH_CFG_MACADDRS18, ETH_CFG_MACADDRS19
};

#endif /*ETH_CFG_USE_CAM*/
  /* DMUT variables :
  In the ETH_write() the user data is copied in the desc pointed out by the 
  ETH_dthead ptr.
  In the ETH_DMUT_ISR() the data buffers are replenished starting from the 
  ETH_dttail pointer
  */
  volatile ETH_TXDESC *ETH_dthead = NULL, *ETH_dttail = NULL;
  /* This variable is used to keep track of whether the desc list full or not*/
  IFX_UINT32 ETH_pending_writes = 0;

  /*
    The following pointers are use to manipulate the free descriptor list
    maintained by DMUR. 

    At the time of drive initialization all DMUR descriptors attached to DMUR 
    free descriptor linked list. Each descriptor associated with one DMUR data
    buffer.The DMUR will copy the received data(from PHY medium) to the first(head) 
    descriptor data buffer of DMUR free descriptor linked list. After receiving the 
    entire frame the frame end interrupt will occur.

    In DMUR ISR, frame end interrupt will remove the head(first) descriptor 
    from the DMUR free descriptor list and attach to the tail end of DMUR 
    filled descriptor list.
  */
  ETH_RXDESC *ETH_drfree_head = NULL, *ETH_drfree_tail = NULL;

  /*The DMUR descriptors*/
#ifdef IFX_COMPILER_TASKING
#ifdef IFX_TASKING_VER2
  ETH_RXDESC ETH_drdesc[ETH_CFG_DMUR_DESC_NUM] __align(32);
#else
#pragma align 4
  ETH_RXDESC ETH_drdesc[ETH_CFG_DMUR_DESC_NUM];
#pragma align restore
#endif
#else
  #ifndef ETH_CFG_USE_CACHE
  ETH_RXDESC ETH_drdesc[ETH_CFG_DMUR_DESC_NUM] __attribute__ ((aligned (32)));
  #else
  ETH_RXDESC ETH_drdesc[ETH_CFG_DMUR_DESC_NUM] __attribute__ ((section(".bss.32align.3")));
  #endif /*ETH_CFG_USE_CACHE*/
#endif

  /*The DMUR data buffers. Each data buffer will be associated with one DMUR
   descriptor */
#ifdef IFX_COMPILER_TASKING
#ifdef IFX_TASKING_VER2
IFX_UINT8 ETH_drdata[ETH_CFG_DMUR_DESC_NUM][ETH_CFG_DMUR_DBUFF_SIZE] __align(32);
#else
#pragma align 32
IFX_UINT8 ETH_drdata[ETH_CFG_DMUR_DESC_NUM][ETH_CFG_DMUR_DBUFF_SIZE];
#pragma align restore
#endif
#else
  #ifndef ETH_CFG_USE_CACHE
  IFX_UINT8 ETH_drdata[ETH_CFG_DMUR_DESC_NUM][ETH_CFG_DMUR_DBUFF_SIZE] __attribute__ ((aligned (32)));
  #else
  IFX_UINT8 ETH_drdata[ETH_CFG_DMUR_DESC_NUM][ETH_CFG_DMUR_DBUFF_SIZE] __attribute__ ((section(".bss.32align.1")));
  #endif /*ETH_CFG_USE_CACHE*/
#endif

 /* The application receive callback function. This is registered with the LLD
     and will be called back in the receive ISR, when the LLD has packets to be
	 delivered to the application
  */
  ETH_APP_RX_CB ETH_app_rcv_cb = NULL;

  /* The application callback function. This function will be called when the 
     transmit complete interrupt occurs 
  */
  ETH_APP_TX_CB ETH_app_tx_cb = NULL;
    
  /* DMUT descriptors*/
#ifdef IFX_COMPILER_TASKING
#ifdef IFX_TASKING_VER2
  ETH_TXDESC ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM] __align(32);
#else
#pragma align 4
  ETH_TXDESC ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM];
#pragma align restore
#endif
#else
  #ifndef ETH_CFG_USE_CACHE
  ETH_TXDESC ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM] __attribute__ ((aligned (32)));
  #else
  ETH_TXDESC ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM] __attribute__ ((section(".bss.32align.2")));
  #endif /*ETH_CFG_USE_CACHE*/
#endif

  /*
    The ETH_dmut_hold flag is used to find the occurance of hold bit.
  	The ETH_cam_addrs is used to buffer the value of MAC addresses are enabled
	in cam before sending pause. To send the pause the different MAC addresses 
	are to be enabled. 
  */
  IFX_UINT32 ETH_cam_addrs = 0;
  IFX_VUINT8  ETH_dmut_hold = 0, ETH_dmut_full = 0;
  /* This value is for checking the range of the TB channel parameter reg */
  IFX_UINT8 ETH_TB_threshold[8] = {1,4,8,12,16,24,32,40}; 

/*
  The following ETH_params structure will copy the Ethernet driver 
  initialization configuartion data programmed by the application. 
  Then program the Ethernet controller kernel registers through this structure

  The run time configuartion settings also (which are to be changed through 
  ETH_control_dev routine) are first updated in this structure.
  
  The new configuration settings will be written into registers through the
   updated structure.

   It will also maintain the current interrupts status
*/
  ETH_COM_PARAMS  ETH_params;

/*
  The ETH_phy_device_address is used to store the address at which a 
  valid PHY device is found. Valid ranges are from 0 to 31
*/
  IFX_UINT8 ETH_phy_device_address = 0x0;

/*
  The follwong structure maintains the statistics
*/
ETH_STAT   ETH_statistics;

/*
  The ETH_isr_val variable is used to copy the DMUR interrupt 
  status fifo register value in ISR. 
  It is observed that the status register value is not persisted 
  till the end of ISR, so the value is buffered into ETH_isr_val
  variable.
*/
IFX_UINT32 ETH_isr_val = 0x0;

/* 
  Define initialized flags and flag management macros if 
  initialization checking is to be done.
  If initialisation checking is not to be performed then
  define the macros to do nothing.
*/
#if ETH_CFG_INIT_CHK == 1
IFX_UINT8 ETH_initialised_flags [ETH_HW_NUM] = {ETH_HW_INIT(0x00)};
# define ETH_SET_INIT_FLAG ETH_initialised_flags[ETH_device] = TRUE
# define ETH_CLR_INIT_FLAG ETH_initialised_flags[ETH_device] = FALSE
# define ETH_CHECK_INITED \
    ((ETH_initialised_flags[ETH_device] == 1)?ETH_SUCCESS:ETH_ERR_NOT_INITIALISED)
#else
# define ETH_SET_INIT_FLAG    
# define ETH_CLR_INIT_FLAG 
# define ETH_CHECK_INITED   
#endif  /* ETH_CFG_INIT_CHK == 1 */


/*
  This macro checks the Ethernet controller hardware module identification number,
  if this check has been configured out then it is defined as nothing.
*/
#if ETH_CFG_DEV_CHK == 1
# define ETH_DEV_ID_CHECK\
      ((ETH_device>=ETH_HW_NUM)?ETH_ERR_UNKNOWN_DEV:ETH_SUCCESS)
#else
# define ETH_DEV_ID_CHECK
#endif


/*
*******************************************************************************
* Function Name:     ETH_initialise_dev
*
* Calling Functions: 
*
* Functions Called:  
*   ETH_initialise_dmur, ETH_initialise_dmut, ETH_initialise_tb, 
*   ETH_initialise_rb, ETH_initialise_mac,
*   ETH_HW_register_isr, ETH_gpio_alloc         
*
* Description:
*   This function initializes the internal data structures of the HAL related
*   to the device selected by ETH_device, allocates any required system 
*   resources and configures the peripheral according to the ETH_COM_PARMS
*   structure. The ETH_COM_PARMS structure must be initialized by the user 
*   before calling ETH_initialise_dev. This function must be called 
*   successfully before any of the other API functions are used and if
*   ETH_terminate_dev is called then ETH_initialise_dev must be called
*   again before using the other API functions.
*
* Input parameters:
*   ETH_device     -  Ethernet controller hardware module identification number
*   ETH_setup      -  Configuration parameters
*
* Output parameters: None
*
* Return Values:      Success or Failure
*
*******************************************************************************
*/
ETH_STATUS ETH_initialise_dev(
  ETH_DEVICE  ETH_device,
  ETH_COM_PARAMS * ETH_parameters
)
{
# if ETH_CFG_INIT_CHK == 1
  if(ETH_initialised_flags[ETH_device] == 1) 
  return ETH_ERR;
# endif  

# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif
   
  /*
    copy the initialization configuration into ETH_params structure and pass this 
    structure as argument to ETH_initialize_dev routine 
  */
   /*MAC conf*/ 
  ETH_params.mac_conf.full_duplex = ETH_CFG_FULLDUPLEX;
  ETH_params.mac_conf.loop_back   = ETH_CFG_MAC_LOOPBACK;  

  /*MAC rx conf*/
  ETH_params.rx_conf.accept_long  = ETH_CFG_RCVLONG;
  ETH_params.rx_conf.accept_short = ETH_CFG_RCVSHORT;
  ETH_params.rx_conf.ignore_crc   = ETH_CFG_NOTCHECKCRC;
  ETH_params.rx_conf.pass_ctrl_pkts = ETH_CFG_PASSCTRLPKTS;
  ETH_params.rx_conf.strip_crc      = ETH_CFG_STRIPCRC;

  /*MAC tx conf*/
# if ETH_CFG_ADDCRC == 1
  ETH_params.tx_conf.no_crc   = ETH_HW_RST;
# else
  ETH_params.tx_conf.no_crc   = ETH_HW_SET;
# endif

# if ETH_CFG_XDEFER == 1
  ETH_params.tx_conf.no_defer      = ETH_HW_RST;
# else
  ETH_params.tx_conf.no_defer      = ETH_HW_SET;
# endif

# if ETH_CFG_ADDPAD == 1
  ETH_params.tx_conf.no_pad        = ETH_HW_RST;
# else
  ETH_params.tx_conf.no_pad        = ETH_HW_SET;
# endif
  ETH_params.tx_conf.sqe_check     = ETH_CFG_SQECHECK;

  /*CAM configuration*/
# if ETH_CFG_USE_CAM == 1
  ETH_params.cam_conf.broad_cast   = ETH_CFG_BROADCAST;
  ETH_params.cam_conf.multi_cast   = ETH_CFG_MULTICAST;
  ETH_params.cam_conf.uni_cast     = ETH_CFG_UNICAST;
  ETH_params.cam_conf.negative_cam = ETH_CFG_NEGATIVECAM;
  ETH_params.cam_conf.cam_compare_enable = ETH_CFG_USE_CAM; 

  /*
    Read the MAC address from application and program into the CAM table
  */
  ETH_params.cam_data.start_mac_addr   =  ETH_CFG_MACADDR_STRT_LOC;
  ETH_params.cam_data.no_of_mac_addrs  =  ETH_CFG_NUM_OF_MACADDR;
  ETH_params.cam_data.addr_loc_enable = ETH_CFG_ENBL_MACADDRS;  
  ETH_params.cam_data.mac_addrs       = (IFX_UINT32 *)&ETH_macaddr[0][0];
# endif	/*ETH_CFG_USE_CAM*/

  /*PHY device control register configuration*/
  ETH_params.phy_conf.full_duplex  = ETH_CFG_FULLDUPLEX;
  ETH_params.phy_conf.speed        = ETH_CFG_SPEED;
  ETH_params.phy_conf.loopback     = ETH_CFG_PHYDEV_LOOPBACK;
  /* As auto neg is not supported in this version, set it to zero */
  ETH_params.phy_conf.auto_negotiate = ETH_CFG_AUTONEGOTIATE;

  /*RB configuration*/
  /* A foward threshold of 0x02 is mentaioned in the HW manual */
  ETH_params.rb_conf.fwd_threshold = 0x02;
  ETH_params.rb_conf.actq_threshold = 0x10;
  ETH_params.rb_conf.free_pool_threshold = 0x80;

  /*TB configuration*/
  ETH_params.tb_conf.fwd_threshold        = ETH_CFG_TBFTC;
  ETH_params.tb_conf.refill_threshold     = ETH_CFG_TBRTC;
  ETH_params.tb_conf.ind_tx_buff_size     = ETH_CFG_BUFFSIZE;

  /*dmur configuration */
  ETH_params.dmur_conf.endian_mode       = ETH_CFG_DMUR_ENDIAN;
  ETH_params.dmur_conf.alignment         = ETH_HW_SET;

  /*DMUT configuration */
  ETH_params.dmut_conf.endian_mode        = ETH_CFG_DMUT_ENDIAN;

  /*
    Allocate the priorities for the interrupts and initialize the 
    compiler dependent ISR wrappers if the value of IFX_COMPILER_GNU
    is set to 1
  */

#if (IFX_COMPILER_GNU == 1)
  if(ETH_HW_register_isr (ETH_device) != 1)
  {
    return ETH_ERR_RES_INT;
  }
#endif /*IFX_COMPILER_GNU */         
  /*
    Allocate the port bits for the Ethernet controller from System HAL
  */
  ETH_gpio_alloc();

  /* Initialize the Hardware*/

  /* First Initialize the MAC functional unit*/
  if(ETH_initialise_mac(ETH_device, &ETH_params) != ETH_SUCCESS)
  {
    ETH_gpio_free();
    return ETH_ERR;
  }
  
  /* Initialise the PHY */
  if(ETH_initialise_phy(ETH_device, &(ETH_params.phy_conf)) == ETH_ERR)
  {
    ETH_gpio_free();
    return ETH_ERR; 
  }
  /* Initialize the DMUR functional unit*/
  if(ETH_initialise_dmur(ETH_device,&ETH_params) != ETH_SUCCESS)
  {
    ETH_gpio_free();
#   if (ETH_CFG_FUNC_TERMINATE == 1)
    ETH_terminate_mac(ETH_device);
#   endif
    return ETH_ERR;                           
  }
  /*Initialize RB functional unit*/
  if(ETH_initialise_rb(ETH_device, &ETH_params) != ETH_SUCCESS)
  {
    ETH_gpio_free();
#   if (ETH_CFG_FUNC_TERMINATE == 1)
    ETH_terminate_mac(ETH_device);
    ETH_terminate_dmur(ETH_device);
#   endif
    return ETH_ERR;                           
  }
  /*Initialize the DMUT functional unit*/
  if((ETH_initialise_dmut(ETH_device, &ETH_params)) != ETH_SUCCESS)
  {
    ETH_gpio_free();
#   if (ETH_CFG_FUNC_TERMINATE == 1)
    ETH_terminate_mac(ETH_device);
    ETH_terminate_dmur(ETH_device);
    ETH_terminate_rb(ETH_device);
#   endif
    return ETH_ERR;                           
  }

  /*Initialize the TB functional unit*/
  if( ETH_initialise_tb(ETH_device, &ETH_params) != ETH_SUCCESS)
  {
    ETH_gpio_free();
#   if (ETH_CFG_FUNC_TERMINATE == 1)
    ETH_terminate_mac(ETH_device);
    ETH_terminate_dmur(ETH_device);
    ETH_terminate_dmut(ETH_device);
    ETH_terminate_rb(ETH_device);
#   endif
    return ETH_ERR;                           
  }/*( ETH_initialise_tb(ETH_device, ETH_setup) != ETH_SUCCESS) */

  /* Start the MAC Tx and Rx */
  ETH_HW_MACRXCTRL = BIT32_MASK(ETH_HW_SET,ETH_HW_MACRXCTRL_RXEN);
  ETH_HW_MACTXCTRL = BIT32_MASK(ETH_HW_SET,ETH_HW_MACTXCTRL_TXEN);
  ETH_SET_INIT_FLAG;
  return ETH_SUCCESS;
} 

/*
*******************************************************************************
* Function Name:     ETH_terminate_dev
*
* Calling Functions: 
*
* Functions Called:  
*  ETH_terminate_dmur, ETH_terminate_dmut, ETH_terminate_tb, 
*  ETH_terminate_rb, ETH_terminate_mac,
*  ETH_free_priorities, ETH_gpio_free
*
* Description:
*   This function will terminate Ethernet driver. It will free the allocated 
*   resources like priorities and ports.It will top the device from 
*   transmitting and sending frames
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_TERMINATE == 1
ETH_STATUS ETH_terminate_dev (ETH_DEVICE ETH_device)
{
   IFX_UINT32 dtisfifo_val,tb_value;
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif

   /* 
    Free the ports allocate dby SYS_gpio_alloc()
  */
  ETH_gpio_free(); 
  
  /*Mask all DMUT interrupt*/
  ETH_HW_DTIMR = 0xFFFFFFFF;

  /*Halt Request*/
  ETH_HW_MACCTRL = 0x01;

  /*TB OFF command*/
  ETH_HW_TBCC = 0x02000000;

  /* Make sure TB is written correctly */
  tb_value = ETH_HW_TBCC;

  /*MAC reset and HALT */
  ETH_HW_MACCTRL = 0x05;

  /* DR off command */
  ETH_HW_DRCMD = 0x00020000;

  /* Read DTICFIFO to clear interrupt caused by TB off command */
  dtisfifo_val = ETH_HW_DTISFIFO;
  ETH_CLR_INIT_FLAG;
  return ETH_SUCCESS;
}
# endif /*ETH_CFG_FUNC_TERMINATE*/

/*
*******************************************************************************
* Function Name:     ETH_abort
*
* Calling Functions: 
*
* Functions Called:  None
*
* Description:
*  This function will abort the driver from receiving and tranmitting frames.
*  The driver functionality can be resumed by calling "ETH_ctrl_resume" IOCTL routine
*  through ETH_control_dev routine
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_ABORT == 1
ETH_STATUS ETH_abort (ETH_DEVICE ETH_device)
{
  ETH_COM_PARAMS ETH_setup;
  IFX_UINT8 dtisfifo_val;
  IFX_UINT8 tb_value;
 
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif

  /*Mask all DMUT interrupt*/
  ETH_HW_DTIMR = 0xFFFFFFFF;

  /*Halt Request*/
  ETH_HW_MACCTRL = 0x01;

  /*TB OFF command*/
  ETH_HW_TBCC = 0x02000000;

  /* Make sure TB is written correctly */
  tb_value = (IFX_UINT8)ETH_HW_TBCC;

  /*MAC reset and HALT */
  ETH_HW_MACCTRL = 0x05;

  /* DR off command */
  ETH_HW_DRCMD = 0x00020000;

  /* Read DTICFIFO to clear interrupt caused by TB off command */
  dtisfifo_val = (IFX_UINT8)ETH_HW_DTISFIFO;
   ETH_CLR_INIT_FLAG;

  ETH_initialise_dev(0, &ETH_setup);
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_ABORT*/

/*
*******************************************************************************
* Function Name:     ETH_status_dev
*
* Calling Functions: 
*
* Functions Called: 
*  ETH_satus_mac or ETH_status_tb or ETH_status_rb or ETH_status_dmur or
*  ETH_status_dmut
*
* Description:
*  This routine will return the current user configuration and interrupt status
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  ETH_stat_inf   -  User provided structure to read present config parameters
*                    of a particular module
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_STATUS == 1
ETH_STATUS ETH_status_dev(ETH_DEVICE ETH_device,ETH_STAT_INF *ETH_stat_inf)
{
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif

  ETH_stat_inf->ETH_conf_params = ETH_params;

# if ETH_CFG_STAT_LOG == 1
  ETH_stat_inf->ETH_stat_cntrs  = ETH_statistics;
#endif

  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_STATUS*/


/*
*******************************************************************************
* Function Name:     ETH_control_dev
*
* Calling Functions: 
*
* Functions Called: 
*  ETH_ctrl_mac, ETH_ctrl_mac_rx, ETH_ctrl_mac_tx, ETH_ctrl_cam, ETH_ctrl_phy,
*  ETH_ctrl_mac_phy, ETH_ctrl_dmur, ETH_ctrl_dmut, ETH_ctrl_rb, ETH_ctrl_tb
*
*
* Description:
*   This routine will change the current configuration of driver, during run time.
*   Only properties which are enabled in the ETH_CFG.H file can be changed.
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  ETH_ctrl_code  -  The configuration need to be reset
*  ETH_ctrl_data  -  The new configuration data
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_CONTROL == 1
ETH_STATUS ETH_control_dev(ETH_DEVICE ETH_device,
                           ETH_CTRL_CODE ETH_ctrl_code, 
                           void *ETH_ctrl_data
)
{
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif
  
  switch(ETH_ctrl_code)
  {
# if ETH_CFG_FUNC_CTRL_MAC == 1
    case ETH_CTRL_MAC:
      return (ETH_ctrl_mac(ETH_device, (ETH_MAC_CONF *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_MAC */

# if ETH_CFG_FUNC_CTRL_MAC_TX == 1
    case ETH_CTRL_MAC_TX:
      return (ETH_ctrl_mac_tx(ETH_device, (ETH_MAC_TX_CONF *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_MAC_TX*/

# if ETH_CFG_FUNC_CTRL_MAC_RX == 1
    case ETH_CTRL_MAC_RX:
      return (ETH_ctrl_mac_rx(ETH_device, (ETH_MAC_RX_CONF *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_MAC_RX*/ 

# if ETH_CFG_FUNC_CTRL_MAC_PHY == 1
    case ETH_CTRL_PHY:
      return (ETH_ctrl_mac_phy(ETH_device, (ETH_PHY_CTRL *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_MAC_PHY*/

# if ETH_CFG_FUNC_CTRL_CAM == 1
    case ETH_CTRL_CAM:
      return (ETH_ctrl_cam(ETH_device, (ETH_CAM_CTRL *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_CAM*/

# if ETH_CFG_FUNC_CTRL_TB == 1
    case ETH_CTRL_TB:
      return (ETH_ctrl_tb(ETH_device, (ETH_TB_CONF *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_TB*/

# if ETH_CFG_FUNC_CTRL_DMUR == 1
    case ETH_CTRL_DMUR:
      return(ETH_ctrl_dmur(ETH_device, (ETH_DMUR_CONF *)ETH_ctrl_data)); 
# endif /*ETH_CFG_FUNC_CTRL_DMUR*/
	
# if ETH_CFG_FUNC_CTRL_DMUT == 1
    case ETH_CTRL_DMUT:
      return (ETH_ctrl_dmut(ETH_device, (ETH_DMUT_CONF *)ETH_ctrl_data));
# endif /*ETH_CFG_FUNC_CTRL_DMUT*/

    default: 
      return ETH_ERR; /*Unknown control routine*/

  } /*End of switch statement*/
}
#endif/*ETH_CFG_FUNC_CONTROL*/


/*
*******************************************************************************
* Function Name:     ETH_read
*
* Calling Functions: 
*
* Functions Called: 
*
* Description:
*  This routine is called inside the ISR when DMUR FE bit set, it copy the frame into
*  buffer and send it to the upper layers by calling OS interface call
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  ETH_transfer   - The received data will copied into this structure
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_READ == 1
ETH_STATUS ETH_read(ETH_DEVICE ETH_device, void (*APP_rcv_cb)(ETH_TRANSFER *ETH_rcvd_frm))
{
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif

  ETH_app_rcv_cb = APP_rcv_cb;
 
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_READ*/

 /*
*******************************************************************************
* Function Name:     ETH_reg_tx_cb
*
* Calling Functions: 
*
* Functions Called: 
*
* Description:
*  This routine is called inside the ISR when DMUR FE bit set, it copy the frame into
*  buffer and send it to the upper layers by calling OS interface call
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number
*  ETH_transfer   - The received data will copied into this structure
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
#if ETH_CFG_FUNC_WRITE == 1
ETH_STATUS ETH_reg_tx_cb(
  ETH_DEVICE ETH_device, 
  void (*APP_tx_cb)(ETH_TRANSFER *ETH_sent_buff)
)
{
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif

  ETH_app_tx_cb = APP_tx_cb;
 
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_WRITE*/

/*
*******************************************************************************
* Function Name:     ETH_write
*
* Calling Functions: 
*
* Functions Called: 
*
* Description   :
*  This routine will copy the received data(frame) and put into the DMUT 
*  descriptor lists.
* 
* Input parameters:
*  ETH_device     -  Ethernet controller hardware module identification number    
*  ETH_transfer   - The received data will copied into this structure
*
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/

#if ETH_CFG_FUNC_WRITE == 1
ETH_STATUS ETH_write(ETH_DEVICE ETH_device, ETH_TRANSFER *ETH_transfer)
{
  ETH_TXDESC  *ETH_saved_head = NULL;

  #ifndef IFX_COMPILER_TASKING
  int i;
  IFX_UINT32 *cache_addr;
  #endif // IFX_COMPILER_TASKING
# if ETH_CFG_DEV_CHK == 1
  if(ETH_DEV_ID_CHECK == ETH_ERR_UNKNOWN_DEV)
  {
    return ETH_ERR_UNKNOWN_DEV;
  }
# endif

# if ETH_CFG_INIT_CHK == 1
  if(ETH_CHECK_INITED == ETH_ERR_NOT_INITIALISED)
  {
    return ETH_ERR_NOT_INITIALISED;
  }
# endif

  /* Check if we have room in the DMUT desc list */
  if(ETH_pending_writes >= ETH_CFG_DMUT_DESC_NUM)
  {
    ETH_dmut_full = ETH_HW_SET;
#   if ETH_CFG_STAT_LOG == 1
      ETH_statistics.rsrc_err++;
#   endif /*ETH_CFG_STAT_LOG*/ 
    /* return an error to indicate to the application that 
	   the driver will not be able to transmit this packet */
	return ETH_ERR;
  }
  else
  {
    /* Check for link */
	if(ETH_check_link(ETH_device) == ETH_ERR)
    {
       return ETH_ERR;
    }
	/* Save a pointer to the head desc */
	ETH_saved_head = (ETH_TXDESC *)ETH_dthead;
	ETH_dthead = ETH_dthead->next;
	/* Update the tx desc */
	ETH_dthead->data          = ETH_transfer->ETH_buffer;
    ETH_dthead->frm_end       = ETH_HW_SET;
    ETH_dthead->hold          = ETH_HW_SET;
    ETH_dthead->no            = ETH_transfer->ETH_buffer_size;
	/* This is of use when this HAL Driver is used as a part of
	   an OS driver
	*/
    ETH_dthead->os_specific = ETH_transfer->ETH_cookie;
#ifdef RB_KEIL
    #ifndef IFX_COMPILER_TASKING
    if( ((((IFX_UINT32)ETH_dthead) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_dthead) & 0xF0000000) == 0xC0000000))
	{
      cache_addr = (int *) ETH_dthead;
      for (i = 0; i <= (sizeof(ETH_TXDESC) >> 4); i++) {
           cachea_w(cache_addr);
           cache_addr += 4;
      }
	}
	#endif //IFX_COMPILER_TASKING
    /* Clear the HOLD bit of the previous desc */
#endif
    ETH_saved_head->hold = ETH_HW_RST;
#ifdef RB_KEIL
    #ifndef IFX_COMPILER_TASKING
    if(((((IFX_UINT32)ETH_saved_head) & 0xF0000000) == 0x80000000) || ((((IFX_UINT32)ETH_saved_head) & 0xF0000000) == 0xC0000000))
	{
      cache_addr = (int *) ETH_saved_head;
      for (i = 0; i <= (sizeof(ETH_TXDESC) >> 4); i++) {
           cachea_w(cache_addr);
           cache_addr += 4;
      }
    }
    #endif //IFX_COMPILER_TASKING
#endif
    ETH_pending_writes++;

    ETH_HW_DTCMD          = ETH_HW_DMUT_HRST;
  }
  return ETH_SUCCESS;
}
#endif /*ETH_CFG_FUNC_WRITE*/
/*
*******************************************************************************
* Function Name:     ETH_gpio_alloc
*
* Calling Functions: ETH_initialise_dev
*
* Functions Called:  
*  System HAL library ports allocation function
*
* Description   :
*  Reserve the ports for the Ethernet driver from the common pool.
*  The common pool is maintained by System HAL.
*
* Input parameters:
*  
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
IFX_UINT8 ETH_gpio_alloc(void)
{
  /*
    The exact code implementation will be followed by System HAL
  */
  SYS_gpio_alloc(SYS_GPIO_ETH_TX0);
  SYS_gpio_alloc(SYS_GPIO_ETH_TX1);
  SYS_gpio_alloc(SYS_GPIO_ETH_TX2); 
  SYS_gpio_alloc(SYS_GPIO_ETH_TX3);
  SYS_gpio_alloc(SYS_GPIO_ETH_TX0);
  SYS_gpio_alloc(SYS_GPIO_ETH_TXER);
  SYS_gpio_alloc(SYS_GPIO_ETH_TXEN);
  SYS_gpio_alloc(SYS_GPIO_ETH_MDC); 
  SYS_gpio_alloc(SYS_GPIO_ETH_RXDV);
  SYS_gpio_alloc(SYS_GPIO_ETH_CRS); 
  SYS_gpio_alloc(SYS_GPIO_ETH_COL); 
  SYS_gpio_alloc(SYS_GPIO_ETH_RX0); 
  SYS_gpio_alloc(SYS_GPIO_ETH_RX1); 
  SYS_gpio_alloc(SYS_GPIO_ETH_RX2); 
  SYS_gpio_alloc(SYS_GPIO_ETH_RX3); 
  SYS_gpio_alloc(SYS_GPIO_ETH_RXER); 
  
  return 1;
}

/*
*******************************************************************************
* Function Name:     ETH_gpio_free
*
* Calling Functions: ETH_terminate_dev
*
* Functions Called:  
*  System HAL library ports free function
*
* Description   :
*  Return the ports of the Ethernet driver to the common pool.
*  The common pool is maintained by System HAL.
*
* Input parameters:  None
*  
* Output parameters: None
*
* Return Values:     Success or Failure
*
*******************************************************************************
*/
IFX_UINT8 ETH_gpio_free(void)
{
  SYS_gpio_free(SYS_GPIO_ETH_TX0);
  SYS_gpio_free(SYS_GPIO_ETH_TX1);
  SYS_gpio_free(SYS_GPIO_ETH_TX2); 
  SYS_gpio_free(SYS_GPIO_ETH_TX3);
  SYS_gpio_free(SYS_GPIO_ETH_TX0);
  SYS_gpio_free(SYS_GPIO_ETH_TXER);
  SYS_gpio_free(SYS_GPIO_ETH_TXEN);
  SYS_gpio_free(SYS_GPIO_ETH_MDC); 
  SYS_gpio_free(SYS_GPIO_ETH_RXDV);
  SYS_gpio_free(SYS_GPIO_ETH_CRS); 
  SYS_gpio_free(SYS_GPIO_ETH_COL); 
  SYS_gpio_free(SYS_GPIO_ETH_RX0); 
  SYS_gpio_free(SYS_GPIO_ETH_RX1); 
  SYS_gpio_free(SYS_GPIO_ETH_RX2); 
  SYS_gpio_free(SYS_GPIO_ETH_RX3); 
  SYS_gpio_free(SYS_GPIO_ETH_RXER); 
  return 1;
}

