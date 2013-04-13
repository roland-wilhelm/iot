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
** @FILENAME@:       eth_api.h
** @VERSION@:        2.4
** @DATE@:           20/1/2006 
**
** =============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** =============================================================================
** Contents: This file contains #defines, data structures and function 
**            prototypes required for the Ethernet device driver
**
** =============================================================================
** References: ETH API book
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby,Rajesh    Release after code review.
** 06/04/2004                             Version number bumped to 2.1 to match 
**                                        the version of the C files 
** 29/04/2004                             change of DMUT Queuing strategy
** 12/11/2004      Tomar Ruby,	
**   		       Badarinath Jayashree
**		           (IFIN SCC AI)          change of ETH_CAM_TBL_LEN value. 
**                                        Additional fields added ETH_MAC_TX_CONF
**                                        and ETH_MAC_RX_CONF structure for Pause
** 20/1/2006        Jayashree Badarinath  Version number modified to 2.4
**                  (IFIN CSW AIM)
** @CHANGE_HISTORY@
** =============================================================================
*/
/* @doc API */ 
 
/*
    @topic2 Ethernet HAL Application Program Interface |
    This section defines the interface between the peripheral hardware 
    abstraction layer and the application software. It defines the constants, 
    typedef names, function names and limitations of the HAL.
    The Ethernet HAL API utilizes a range of constants and typedef names in 
    order to interact in a logical way with the application program. 
    The first section of this chapter will look at these constants and data 
    types.
    
    Please refer to Appendix A - Infineon IFX types for details on the IFX data
    types. 
*/

#ifndef __ETH__API_H
#define __ETH__API_H

/*-------------------- Include user defined header file --------------------*/
#include "compiler.h"
#include "common.h"	
#include "sys_api.h"
#include "eth_idl.h"
#include "sys_cfg.h"
#include "eth_cfg.h"
#include "eth_iil.h"

/*
  @def  ETH_API_V_MAJ  | API Major Version Number,
  ETH_API_V_MAJ is defined as the major version of this API which the Ethernet 
  HAL supports. This version is defined as 0.1.
  Application software may check this field to determine if the HAL API version 
  is acceptable.
*/
#define ETH_API_V_MAJ 0
/*
  @def  ETH_API_V_MIN  | API Minor Version Number,
  ETH_API_V_MIN is defined to the minor version of this API which the Ethernet
  HAL supports. This version is defined as 0.1.
  Application software may check this field to determine if the HAL API version 
  is acceptable.
*/
#define ETH_API_V_MIN 1

/*
  @def:(DESIGN)   ETH_CAM_TBL_LEN  | CAM Table Length,
  the CAM contains 20 MAC addresses each of 6 bytes that can be programmed
  i.e. a total of 120 bytes. Before programming the CAM these addresses
  are stored in an array of IFX_UINT32. Therefore the 120 bytes are mapped
  into an integer array mac_addrs[] of length ETH_CAM_TBL_LEN.
  The struct ETH_CAM_DATA uses the mac_addrs[].
*/
#define ETH_CAM_TBL_LEN    20  

/*
  @def:(DESIGN)  ETH_MACADDR_CONV_FACTOR, 
  This factor is used to convert 6 bytes MAC addresses to UINT arrays  
  */


#define ETH_MACADDR_CONV_FACTOR 1.5


/* 
  @type ETH_DEVICE typedef | This indicates the Device ID
  @comm ETH_DEVICE is used in the API wherever a device must be selected. This
  is required because many ETH peripherals may be implemented in the same 
  system. ETH_DEVICE is simply a typedef name which is defined as IFX_UINT8
*/

typedef IFX_UINT8 ETH_DEVICE;


/*
  @enum ETH_STATUS | Ethernet Status Enumeration
  @comm The ETH_STATUS enum constants will be used to return the status from the
  functions.If the function execute successfully then it will return the 
  ETH_SUCCESS or it will return the specific error code. This return code will 
  be useful for the application to learn about failure.
*/
typedef enum
{
  ETH_SUCCESS = 0,  
  /*@emem ETH_SUCCESS indicates that an operation completed successfully. */
  ETH_ERR,    
  /*@emem ETH_ERR is used to indicate that an unspecified error was encountered
   by the HAL. ETH_ERR will only be used as a last resort when the HAL is unable
   o describe the error using a more specific error code.*/
  ETH_ERR_RES,         
  /*@emem ETH_ERR_RES is used to indicate that the Ethernet HAL was unable to 
    allocate a system resource required to carry out the requested operation. 
    This will only be used when the resource is not covered by the other
    ETH_ERR_RES constants.See also ETH_ERR_RES_INT, ETH_ERR_RES_MEM and 
    ETH_ERR_RES_IO.*/
  ETH_ERR_RES_INT,   
  /*@emem ETH_ERR_RES_INT is used to indicate that a required interrupt number
    priority are currently unavailable for use by the HAL. This error will be
    encountered either when an attempt is made to change an interrupt number
    priority during run time or when ETH_initialise_dev is called. If interrupt
    numbers/priorities cannot be dynamically changed due to hardware limitations
   then ETH_ERR_NOT_SUPPORTED_HW will be returned.*/
  ETH_ERR_RES_MEM, 
  /*@emem ETH_ERR_RES_MEM is used to indicate that the HAL was unable to 
    allocate enough memory to complete the requested operation.*/
  ETH_ERR_RES_IO, 
  /*@emem ETH_ERR_RES_IO is used to indicate that one or more physical 
    connection lines are unavailable. This may be because a line is shared with
    another peripheral (and has been allocated) or if it is currently in use 
    as a general purpose I/O line.*/
  ETH_ERR_NOT_SUPPORTED,  
  /*@emem ETH_ERR_NOT_SUPPORTED is used to indicate that a requested operation 
    cannot be performed because it is not supported in software. This may be
    because a required software module has been compiled out (see configuring 
    the Ethernet HAL).*/
  ETH_ERR_NOT_SUPPORTED_HW, 
  /*@emem ETH_ERR_NOT_SUPPORTED_HW is used to indicate that a requested 
    operation cannot be performed because a required feature is not supported in
    hardware.*/
  ETH_ERR_UNKNOWN_DEV, 
  /*@emem ETH_ERR_UNKNOWN_DEV indicates that a device ID passed to an API 
    function was not valid.*/
  ETH_ERR_NOT_INITIALISED 
  /*@emem ETH_ERR_NOT_INITIALISED is returned if an API function is called 
    before the HAL has been successfully initialized. This checking may be 
    configured out to improve runtime performance, see Configuring the Ethernet 
    HAL for information*/
}ETH_STATUS;

/*
  @enum ETH_CTRL_CODE | Ethernet Control Enumeration
  @comm The ETH_CTRL_CODE enum will be used in ETH_control_dev (IOCTL) function.
  The enum specifies which particular unit or functional entity would be changed 
  at run time. 
  
  The user application will pass this enum as an argument to ETH_control_dev 
  function, the ETH_control_dev() will then branch to the appropriate function,
  which would change the configuration according to the data provided.
*/
typedef enum
{
  ETH_CTRL_MAC = 0,
  /*@emem  This enumeration constant is used with ETH_control_dev API function. 
   ETH_CTRL_MAC may be used to provide basic control to modify MAC parameters,
   other than MAC transmitter and receiver */

  ETH_CTRL_MAC_TX,
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
    ETH_CTRL_MAC_TX may be used to provide basic control to modify MAC 
    transmitter parameters */

  ETH_CTRL_MAC_RX,
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
    ETH_CTRL_MAC_RX may be used to provide basic control to modify MAC receiver
    parameters */

  ETH_CTRL_PHY,  
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
    ETH_CTRL_PHY may be used to provide basic control to modify Physical device 
    parameters*/

  ETH_CTRL_CAM,
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
    ETH_CTRL_CAM may be used to provide basic control to modify CAM parameters*/

  ETH_CTRL_TB,
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
    ETH_CTRL_TB may be used to provide basic control to reset transmit buffer 
    configuration parameters*/

  ETH_CTRL_DMUR,
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
    ETH_CTRL_DMUR may be used to provide basic control to reset DMUR
    configuration parameters*/

  ETH_CTRL_DMUT 
  /*@emem  This enumeration constant is used with ETH_control_dev API function.
   ETH_CTRL_DMUT may be used to provide basic control to reset DMUT 
   configuration parameters.*/
} ETH_CTRL_CODE;
 
/*--------------------ETH MAC configuration data----------------------------*/
/*
  @struct  ETH_MAC_CONF | MAC Configuration Info
  @comm The ETH_MAC_CONF structure is used to program the MAC controller 
  configuration. This structure is a part of ETH_COM_PARAMS, which has
  the startup configuration of Ethernet driver. 

  This structure is also used to change the run time MAC controller 
  configuration through ETH_ctrl_mac function.
*/
typedef struct
{
  IFX_UINT8 full_duplex:1;/*@field Ethernet controller is in full duplex mode*/
  IFX_UINT8 loop_back:1; /*@field Ethernet controller works in loop back mode*/
}ETH_MAC_CONF ;

/*
  @struct  ETH_MAC_TX_CONF | MAC Transmission Configuration Info

  @comm The ETH_MAC_TX_CONF structure is used to program the MAC controller 
  transmission configurations. This structure is a part of ETH_COM_PARAMS, 
  which has the startup configuration of Ethernet driver. 

  This structure is also used to change the run time MAC TX configuration
  through ETH_ctrl_mac_tx function.
*/
typedef struct
{
  IFX_UINT8 no_pad:1;         
  /*@field No pad added to the out going packet if packet length less than 
  64 bytes*/
  IFX_UINT8 no_crc:1;         
  /*@field No CRC added to the out going packet*/
  IFX_UINT8 no_defer:1;      
  /*@field Defer will not be checked to the out going frame*/
  IFX_UINT8 sqe_check:1;      
  /*@field Signal quality error checking in MII 10 mbps mode*/
  IFX_UINT8 send_pause:1;
  /*@field for sdpause bit enable*/
  IFX_UINT8 tx_enable:1;
  /*@field for txEn*/
}ETH_MAC_TX_CONF;

/*
  @struct  ETH_MAC_RX_CONF | MAC Receive Configuration Info
  @comm The ETH_MAC_RX_CONF structure is used to program the receive MAC 
  controller configurations. This structure is a part of ETH_COM_PARAMS, 
  which has the startup configuration of Ethernet driver. 

  This structure is also used to change the run time MAC RX configuration
  settings through ETH_ctrl_mac_rx function.
*/
typedef struct
{
  IFX_UINT8 accept_long:1;    
  /*@field Accept long frames longer than 1518 bytes*/
  IFX_UINT8 accept_short:1;   
  /*@field Accept short frames of size less than 64 bytes*/
  IFX_UINT8 strip_crc:1;      
  /*@field Strip CRC from received frame and no CRC checking at DMUR */
  IFX_UINT8 pass_ctrl_pkts:1; 
  /*@field Pass the MAC control (pause) frames to the logical link layer (LLC)*/
  IFX_UINT8 ignore_crc:1;     
  /*@field Do not check CRC of a receiving frame*/
  IFX_UINT8 rx_enable:1;
  /*@field for rxEn*/
}ETH_MAC_RX_CONF;

/*
  @struct  ETH_PHY_CONF | Physical Device programming Info
  @comm The ETH_PHY_CONF structure is used to program the PHY device control 
  register configurations. 
  
  This structure is a part of ETH_COM_PARAMS, which has the startup 
  configuration of Ethernet driver. 
*/
typedef struct
{
  IFX_UINT8 speed:1;             
  /*@field Speed  0-->10 Mbps, 1-->100 Mbps*/
  IFX_UINT8 loopback:1;        
  /*@field Ethernet controller operates in PHY device loop back mode */
  IFX_UINT8 full_duplex:1; 
  /*@field PHY device operates in full duplex mode*/
  IFX_UINT8 auto_negotiate:1;    
  /*@field Enable auto negotiation feature of PHY device*/
}ETH_PHY_CONF;
     

/*
  @struct  ETH_PHY_CTRL | Physical Device Control Info

  @comm This PHY device configuration control structure is used to configure 
  the PHY device using the ETH_PHY_CTRL structure the user will be able to read 
  /write any data from/into any of PHY device registers
  The structure ETH_PHY_CTRL is used to change the PHY device configuration 
  settings at run time through ETH_ctrl_mac_phy function.
*/
typedef struct
{
  IFX_UINT16  control:1;  
  /*@field To read from or write to PHY device registers 0-->read, 1-->write*/
  IFX_UINT16  phy_num:5;   
  /*@field PHY device number */
  IFX_UINT16  reg_num:5;   
  /*@field Register number inside PHY device*/
  IFX_UINT32  *data;       
  /*@field Data want to read/write from/to the PHY register*/
}ETH_PHY_CTRL; 
 


/*
  @struct  ETH_CAM_DATA | CAM programming info
  @comm CAM can be programmed to support up to 20 (0-19) MAC addresses 
  each of which are 6 bytes long. The MAC addresses are placed into 
  mac_addrs field of the structure defined below. The MAC addresses
  are to be programmed to the CAM is first written into mac_addrs[]. 
  Then the addresses in mac_addrs[] are programmed into the CAM.
  
  E.g. If the MAC addresses to be programmed into CAM are 0x010203040506, 
  0xAABBCCDDEEFF, then the contents of the mac_addrs[] are as follows.

  mac_addrs[0] = 0x01020304

  mac_addrs[1] = 0x0506AABB

  mac_addrs[2] = 0xCCDDEEFF

  start_mac_addr = 0

  no_of_mac_addrs = 2   

  This structure is included in ETH_CAM_CTRL to add MAC addresses to CAM and enable 
  the particular MAC addresses in CAM at run time.
*/

typedef struct
{
  IFX_UINT8   start_mac_addr;              
  /*@field Starting location of MAC address ranges from 0x0 to 0x13 */
  IFX_UINT8   no_of_mac_addrs;             
  /*@field The number of MAC addresses to be programmed into CAM */ 
  IFX_UINT32  *mac_addrs;                  
  /*@field Pointer to the MAC addresses which are to be programmed into CAM*/
  IFX_UINT32  addr_loc_enable;             
  /*@field The addresses are to be enabled to filter the received frames*/
}ETH_CAM_DATA;

/*
  @enum ETH_CAM_COMMAND | Ethernet CAM Command
  @comm The ETH_CAM_COMMAND enum is used in ETH_CAM_CTRL structure to
  distinguish the provided data and branch to the specific part of code in 
  ETH_ctrl_mac_cam function. 
*/
typedef enum
{
  ETH_ADD_MAC_ADDR,     /*@emem This is used to add new MAC address to CAM */
  ETH_ENABLE_LOC,       /*@emem  This is used to enable MAC addresses in CAM 
                              which are programmed*/
  ETH_RESET_CONF        /*@emem  This is used to reset MAC CAM configuration*/
}ETH_CAM_COMMAND;

/*
  @struct  ETH_CAM_CONF | CAM Configuration Info

  @comm The ETH_CAM_CONF structure is used to program the CAM controller 
  configurations. This structure is a part of ETH_COM_PARAMS, which has 
  the startup configuration of Ethernet driver. 
  
  This structure is also a part of ETH_CAM_CTRL to change the CAM configuration
  settings at run time through ETH_ctrl_mac_cam function.
*/
typedef struct
{
  IFX_UINT8 uni_cast:1;           /*@field Accept unicast address packets*/
  IFX_UINT8 multi_cast:1;         /*@field Accept Multicast address packets*/
  IFX_UINT8 broad_cast:1;         /*@field Accept Broadcast address packets*/
  IFX_UINT8 negative_cam:1;       /*@field Receive the frames which are not 
                                    recognized by CAM*/
  IFX_UINT8 cam_compare_enable:1; /*@field Enable CAM controller to filter 
                                    the received frames*/
}ETH_CAM_CONF;


/*
  @union  ETH_CAM_UDATACONF | A union contains CAM programming info.
  This union is used in the structure ETH_CAM_CTRL 
*/

typedef union
{
  ETH_CAM_DATA      mac_addr_data;  /*@field Write MAC addresses into CAM and
                                     enable the programmed MAC addresses*/
  ETH_CAM_CONF      conf_params;    /*@field To change CAM configuration 
                                       parameters*/
}ETH_CAM_UCONFDATA;

/*
  @struct  ETH_CAM_CTRL | CAM Control Info
  @comm The structure ETH_CAM_CTRL is used to add the MAC addresses to CAM, 
  enable the MAC addresses in CAM or to change the CAM configuration parameters
  at runtime through ETH_ctrl_mac_cam function
*/

typedef struct
{
  ETH_CAM_COMMAND command;/*@field Contains the CAM command information */
  ETH_CAM_UCONFDATA data;  /*@field Union contains CAM programming info */
}ETH_CAM_CTRL;

/*
  @struct:(design)  ETH_CAM_PROG | CAM Program Info
  @comm The structure ETH_CAM_PROG is used to add the MAC addresses to CAM
  */

typedef struct {
  IFX_UINT8   ETH_cam_addr_hw;	/*@field  Index of the MAC address in the CAM*/
  IFX_UINT8   ETH_cam_addr_user; /*@field  Index of the MAC address in the user 
                                   array */
  IFX_UINT8   ETH_user_array_position; /*@field Flag indicating the start of the
                                          MAC address in the user array */
  IFX_UINT8   ETH_num_addr;	 /*@field Number of addresses to be programmed */
  ETH_CAM_CTRL *ETH_ctrl_data; /*@field Pointer to the ETH_CAM_CTRL structure, 
                                    containing the user settings */
}ETH_CAM_PROG;
/*---------------------- ETH RB configuration data -------------------------*/

/*
  @struct  ETH_RB_CONF | Receive Buffer Configuration
  @comm The ETH_RB_CONF structure is used to program the Receive Buffer 
  configuration values. This structure is a part of ETH_COM_PARAMS, 
  which has the startup configuration of Ethernet driver. 
  
  This structure is also used to change the Receive Buffer configuration vals
  at runtime through ETH_ctrl_rb function.
*/

typedef struct
{
  IFX_UINT16 fwd_threshold:2;      /*@field Receive buffer forward threshold 
                                               code*/
  IFX_UINT16 actq_threshold:6;     /*@field  Receive buffer action queue 
                                                 threshold*/
  IFX_UINT16 free_pool_threshold:8;/*@field Receive buffer free pool threshold*/
}ETH_RB_CONF;


/*------------------ ETH TB configuration data ------------------------------*/
/*
  @struct  ETH_TB_CONF | Transmit Buffer Configuration
  @comm The ETH_TB_CONF structure is used to program the Transmit Buffer 
  configuration values. This structure is a part of ETH_COM_PARAMS, which 
  has the startup configuration of Ethernet driver. 
  
  This structure is also used to change the Transmit Buffer configuration 
  values at runtime through ETH_ctrl_tb function.
*/
typedef struct
{
  IFX_UINT16 ind_tx_buff_size;     /*@field Individual transmitter buffer size*/
  IFX_UINT16 refill_threshold:3;    /*@field Transmit buffer refill threshold
                                        value*/
  IFX_UINT16 fwd_threshold:3;       /*@field Transmit forward threshold value*/
}ETH_TB_CONF;
/*----------------------------------------------------------------------------*/


/*------------------- ETH dmur configuration data -----------------------------*/


/*
  @struct  ETH_RXDESC | Receive Descriptor
  @comm The ETH_RXDESC structure is used to define the DMUR descriptors.
  These descriptors are maintained by DMUR. Each descriptor associated with 
  one data buffer. The data received from PHY medium placed into these 
  descriptors by DMUR. Either the data buffer is filled up or a single frame is 
  received the DMUR branches to next descriptor in descriptor list provided hold 
  bit is not set.
*/
typedef struct ETH_rxdesc
{
  IFX_UINT32         no:16;            
  /*@field Maximum data it can hold*/
  IFX_UINT32         desc_id:6;        
  /*@field Descriptor id*/
  IFX_UINT32         reserved:4;               
  /*Unused */
  IFX_UINT32         offset:3;         
  /*@field Extra header data inside data buffer*/
  IFX_UINT32         rhi:1;            
  /*@field Receive hold indication bit*/
  IFX_UINT32         hold:1;           
  /*@field Hold bit, set to 1 for last descriptor*/
  IFX_UINT32         reserved1:1;               
  /*Unused */
  struct ETH_rxdesc  *next;            
  /*@field Pointer to next descriptor*/
  IFX_UINT8          *data;            
  /*@field Pointer to data buffer*/
  IFX_UINT32         bno:16;           
  /*@field Data buffer size*/
  IFX_UINT32         rab:1;            
  /*@field DMUR abort*/
  IFX_UINT32         il_len:1;         
  /*@field Invalid length*/
  IFX_UINT32         crc:1;            
  /*@field CRC error*/
  IFX_UINT32         rx_frm_ovflow:1;  
  /*@field Receive frame over flow*/
  IFX_UINT32         max_frm_len:1;    
  /*@field Packet exceed the max frame length*/
  IFX_UINT32         reserved2:9;               
  /*Unused */
  IFX_UINT32         cmp:1;            
  /*@field DMUR completely filled the data buffer associated with current 
  descriptor*/
  IFX_UINT32         frm_end:1;        
  /*@field Full frame received*/
}ETH_RXDESC;

/*
  @struct  ETH_DMUR_CONF | DMUR Configuration Register
  @comm The ETH_DMUR_CONF structure is used to program the Data Management
  Unit Receive configuration values. This structure is a part of ETH_COM_PARAMS, 
  which has the startup configuration of Ethernet driver. 
  
  This structure is also used to change the Data Management Unit Receive 
  configuration values at runtime through ETH_ctrl_dmur function.
*/
typedef struct
{
  IFX_UINT8 endian_mode:1;  /*@field Endian mode 0-->little endian, 1-->big 
  endian */
  IFX_UINT8 alignment:1;    /*@field Block boundary alignment for burst is 
  enabled*/
}ETH_DMUR_CONF;

/*---------------------ETH dmut configuration data----------------------------*/
/*
  @struct  ETH_DMUT_CONF | DMUT Configuration Register
  @comm The ETH_DMUT_CONF structure is used to program the Data Management
  Unit Transmit configuration values. This structure is a part of ETH_COM_PARAMS,
  which has the startup configuration of Ethernet driver. 
  
  This structure is also used to change the Data Management Unit Transmit 
  configuration values at runtime through ETH_ctrl_dmut function.
*/
typedef struct
{
  IFX_UINT8 endian_mode; /*@field Endian mode 0->little endian, 1->big endian*/
}ETH_DMUT_CONF;

/*
  @struct  ETH_TXDESC | Transmit Descriptor
  @comm The ETH_TXDESC structure is used to define the DMUT descriptors.
  The data coming from applications will be buffered into data buffer and 
  associated with these descriptors.

  The filled descriptors are added to the DMUT, the DMUT will transfer the
  data associated with descriptor to the TB (towards PHY medium). Once  
  the data is transferred the DMUT will branch to the next descriptor in list.
*/
typedef struct ETH_txdesc
{
  IFX_UINT32         no:16;             /*@field Max data size of data buffer*/
  IFX_UINT32         desc_id:6;         /*@field Descriptor id*/
  IFX_UINT32         reserved:6;                /*Unused */
  IFX_UINT32         cmp_en:1;          /*@field Complete interrupt is enabled*/
  IFX_UINT32         thi:1;             /*@field TX host indication bit*/
  IFX_UINT32         hold:1;            /*@field Hold bit, last descriptor set 
                                               this bit to 1*/
  IFX_UINT32         frm_end:1;         /*@field Complete frame transmitted*/
  struct ETH_txdesc  *next;             /*@field Pointer to next descriptor*/
  IFX_UINT8          *data;             /*@field Pointer to data buffer*/
  IFX_UINT32         reserved1:30;               /*Unused*/ 
  IFX_UINT32         cmp:1;             /*@field Complete*/
  IFX_UINT32         :1;                /*Unused */
  void              *os_specific;    /* @field A cookie field for any OS driver */
  IFX_UINT32         dummy;			  /* @field required for alignment reasons */
  IFX_UINT32         dummy_1;		  /* @field required for alignment reasons */
  IFX_UINT32         dummy_2;		  /* @field required for alignment reasons */
}ETH_TXDESC;

/*
  @struct  ETH_COM_PARAMS | Ethernet Configuration Setting
  @comm The ETH_COM_PARMS structure is used to specify complete configuration 
  settings for the Ethernet driver. The elements of this structure contains 
  the configuration information for the individual units of the Ethernet 
  controller
  This structure is used with the ETH_initialise_dev() API function during the 
  initialization of the device driver
*/

typedef struct
{
  ETH_MAC_CONF      mac_conf;    /*@field MAC configuration data*/
  ETH_CAM_CONF      cam_conf;    /*@field CAM configuration data*/
  ETH_MAC_TX_CONF   tx_conf;     /*@field MAC TX configuration data*/
  ETH_MAC_RX_CONF   rx_conf;     /*@field MAC RX configuration data*/
  ETH_PHY_CONF      phy_conf;    /*@field PHY device configuration data*/
  ETH_CAM_DATA      cam_data;    /*@field MAC CAM configuration data*/
  ETH_DMUR_CONF     dmur_conf;   /*@field DMUR configuration data*/
  ETH_DMUT_CONF     dmut_conf;   /*@field DMUT configuration data*/
  ETH_RB_CONF       rb_conf;     /*@field Receive buffer configuration data*/
  ETH_TB_CONF       tb_conf;     /*@field Transmit buffer configuration data*/
}ETH_COM_PARAMS;
/*--------------------------------------------------------------------------*/

/*
 @struct  ETH_RETURN_NUM | Bit Fields for the ETH_return_num field in the 
 ETH_transfer structure.
 @comm    These bit fields are used to indicate the status of the data 
 received to the application. Depending on the size of the receive buffer,
  an ethernet frame may be spread accross more than one descriptor.
  The 'fe' bit in the ETH_return_num field in the ETH_transfer structure
  indicates to the application that the end of a frame has reached.
*/
typedef struct ETH_return_number
{
  IFX_UINT32 ETH_fe:1;	 /*@field End of frame reached*/
  IFX_UINT32 ETH_rab:1;   /*@field Receive Abort bit set*/
  IFX_UINT32 ETH_ilen:1;	 /*@field Illegal Length of incoming data packets*/
  IFX_UINT32 ETH_crc:1;	 /*@field CRC Error*/
  IFX_UINT32 ETH_rfod:1;	 /*@field Receive Frame Overflow*/
  IFX_UINT32 ETH_mfl:1;	 /*@field Inconimg data packet length exceeded the
                                maximum allowed frame length*/
}ETH_RETURN_NUM;


/*
 @struct  ETH_TRANSFER | Ethernet Data Transfer Structure
 @comm This structure is used to exchange data transfer between driver and 
 application.As soon as the destination receives the data it will return the
 status.
*/
typedef struct ETH_transfer
{
  IFX_UINT8     *ETH_buffer;  /*@field Pointer to data buffer*/
  IFX_UINT32     ETH_buffer_size;         /*@field Data size*/
  ETH_RETURN_NUM ETH_return_num;      /*@field Bit fields (described above) 
                             indicating the status of the receive operation.*/
  void          *ETH_cookie;
}ETH_TRANSFER;


/*
 @struct  ETH_STAT | Ethernet statistics Structure
 @comm 	ETH_STAT is used to maintain the statistics of the received and 
 transmitted frames. Once any counter reaches maximum value it will
  automatically reset to zero. So the application
 can keep track of these counters from time to time.
*/
typedef struct
{
  IFX_UINT32 rsrc_err;	/*@field The received frames are discarded because of 
                                  data buffers are not available
                                 both at DMUR and DMUT */
  IFX_UINT32 tx_def;  	/*@field Transmission is deferred for out going frame*/
  IFX_UINT32 tx_lst_car; /*@field Carrier is lost */
  IFX_UINT32 tx_good_frms; /*@field Frames transmitted without any errors*/
  IFX_UINT32 tx_under;	   /*@field MAC TX FIFO under run*/
  IFX_UINT32 tx_excs_coll; /*@field Excessive collision occurred while 
                               transmitting frames*/
  IFX_UINT32 tx_late_coll; /*@field Late collision occurred while transmitting 
                                    frames*/
  IFX_UINT32 tx_pause;	   /*@field Ethernet controller send control frames
                                    to the sources of frames*/
  IFX_UINT32 rx_pause;	   /*@field Received control frames*/
  IFX_UINT32 rx_align_err; /*@field Received the frames with alignment error*/
  IFX_UINT32 rx_crc_err;   /*@field Received frames with CRC error */
  IFX_UINT32 rx_lng_frm;   /*@field Received long frames size more than 1518 
                                    bytes, when received long frames option is 
                                    disabled*/
  IFX_UINT32 rx_over;      /*@field Receiver is overflowed*/
  IFX_UINT32 rx_good_frms; /*@field Good frames received*/
}ETH_STAT;


/*
  @struct ETH_STAT_INF |Ethernet driver status info, 
  this struct contains the current configuration values of all the
  configuration registers, required. It also contains the current values 
  of all the interrupts. This structure is derived from some of the structures 
  defined above.
*/
typedef struct
{
  ETH_COM_PARAMS  ETH_conf_params;  /*@field Driver current configuration 
                                             parameters*/
# if ETH_CFG_STAT_LOG == 1
  ETH_STAT ETH_stat_cntrs; 		   /*@field Received and transmit frames 
                                             status counters*/
# endif
}ETH_STAT_INF; 

typedef void (*ETH_APP_RX_CB)(ETH_TRANSFER *);
typedef void (*ETH_APP_TX_CB)(ETH_TRANSFER *);
/*----------------------------------------------------------------------------*/
/*
  All the following extern variables are decleared and defined in ETH_IIL.C file.
  Explanation for all variables can be found in same file.
*/
extern  volatile ETH_TXDESC *ETH_dthead, *ETH_dttail, *ETH_saved_head;
extern IFX_UINT32 ETH_pending_writes;

//extern  volatile ETH_TXDESC *ETH_dtfill_head, *ETH_dtfill_tail;

extern  ETH_RXDESC *ETH_drfree_head, *ETH_drfree_tail;

extern  ETH_RXDESC ETH_drdesc[ETH_CFG_DMUR_DESC_NUM]; 

extern  IFX_UINT8  ETH_drdata[ETH_CFG_DMUR_DESC_NUM][ETH_CFG_DMUR_DBUFF_SIZE];

extern ETH_APP_RX_CB ETH_app_rcv_cb;

extern  ETH_APP_TX_CB ETH_app_tx_cb;

extern  ETH_TXDESC ETH_dtdesc[ETH_CFG_DMUT_DESC_NUM];

extern  IFX_UINT32 ETH_cam_addrs;

extern  IFX_VUINT8  ETH_dmut_hold, ETH_dmut_full;

extern IFX_UINT8 ETH_TB_threshold[8];

extern ETH_COM_PARAMS  ETH_params;

extern IFX_UINT32 ETH_isr_val;

extern IFX_UINT8 ETH_phy_device_address;

extern ETH_STAT   ETH_statistics;
/*
  Ethernet HAL API function prototypes:
*/

/*@func:(DESIGN) ETH_gpio_alloc | Allocate the ports for Ethernet controller
  @head4 Implementation Details |
  @flag | - Get the ports and reserve the port bits for the Ethernet controller
  from System HAL, by calling the system HAL provided API.
  @retval  Success/Failure
  @flag 1 | The requested ports are allocated. 
  @flag 0 | The requested ports are not allocated. 
*/
IFX_UINT8 ETH_gpio_alloc(
void  /*@parm None */
);

/*@func:(DESIGN) ETH_gpio_free | Free the ports and return to System HAL
  @head4 Implementation Details |
  @flag | - Release and return the ports to the System HAL. 
  @retval  Success/Failure
  @flag 1 | The ports are being freed and returned to System HAL
  @flag 0 | The ports are not being freed and not returned to System HAL
*/

IFX_UINT8 ETH_gpio_free(
void  /*@parm None */
);

/* 
   @topic2 Ethernet API Functions |
   @func Ethernet Driver Initialization function,
   this function initializes the internal data structures of the HAL related 
   to the device selected by ETH_DEVICE, allocates any required system resources
   and configures the peripheral according to the ETH_COM_PARAMS structure. 
   The ETH_COM_PARAMS structure must be initialized by the user before calling 
   ETH_initialise_dev. This function must be called successfully before any of 
   the other API functions are used and if ETH_terminate_dev is called then 
   ETH_initialise_dev must be called again before using the other API functions.
   @head4: (DESIGN) Implementation Details |
   @flag | - Copy the driver initialization configuration parameters to 
                   ETH_COM_PARAMS data structure.
   @flag | - Get the interrupt priorities from System HAL, which are defined in 
             SYS_CFG.H file
   @flag | - Reserve the required port bits for driver defined in GPIO_CFG.H 
             file.
   @flag | - Check the reserved interrupt priorities and port bits are not 
             clashing with any other module.
   @flag | - Enable the global interrupt through System HAL.
   @flag | - Call the functional blocks(DMUT, DMUR, TB, RB and MAC) 
              initialization routines in a specific sequence 
             in order not to lose any frames receiving either from PHY medium or
              from application.

   @retval  Returns Ethernet Status
   @flag ETH_SUCCESS | Initialization is success.
   @flag ETH_ERR_RES_INT | Requested priorities are not available
   @flag ETH_ERR_RES_IO | Requested ports are not available
   @flag ETH_ERR | Functional blocks are not initialized.
*/

ETH_STATUS ETH_initialise_dev
(
  ETH_DEVICE     ETH_device, /* @parm Ethernet controller hardware module identification value */ 
  ETH_COM_PARAMS *ETH_setup  /* @parm Configuration parameters, to be programmed to the Ethernet
                                controller kernel registers. These parameters are ignored.  */

);


/* ETH MAC HAL initialise function */
/*
  @func:(DESIGN) Ethernet MAC controller initialization function
  @head4: (DESIGN) Implementation Details |
  @flag | - MAC initialization routine should not be exposed to application and 
            it will called by only ETH_initialise_dev routine.

  @flag | - Write the application provided MAC addresses into CAM. 

  @flag | - If ETH_CFG_USE_PAUSE feature is enabled program the pause related 
            addresses and data into CAM.

  @flag | - Configure the PHY device and program the interrupt mask registers.

  @flag | - If ETH_CFG_STAT_LOG feature is enabled, the following interrupts 
            will be enabled in their corresponding  interrupt mask registers. 

  @flag | . MAC TX - late collision, excessive collision, under run, lost 
            carrier, remote pause and frame sent without errors.
  
  @flag | . MAC RX - Alignment error, CRC error, over flow error, control frame
            received, long frame error and good frame received.

  @flag | - Else only the MAC TX control frame sent interrupt will be enabled.

  @flag | - Program the MAC TX and RX control blocks and enables both receiver 
            and transmitter. 
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | MAC initialization is success
*/
ETH_STATUS ETH_initialise_mac
(
 ETH_DEVICE     ETH_device, 
  /*@parm Ethernet controller hardware module identification value */
  ETH_COM_PARAMS *ETH_setup  
  /*@parm Configuration parameters, to be programmed to the MAC kernel registers*/
);

  /* ETH PHY HAL initialise function */
/*
  @func:(DESIGN) Ethernet PHY initialisation function
  @head4: (DESIGN) Implementation Details |
  @flag | - PHY initialisation routine should not be exposed to application and
            it will called by only ETH_initialise_mac routine.

  @flag | - Check if a valid PHY is present

  @flag | - Find the address of the PHY

  @flag | - Reset the PHY

  @flag | - Configure the initialisation parameters in the PHY (full duplex,
            speed 10/100), loopback.
   
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | PHY initialisation is successful
*/
ETH_STATUS ETH_initialise_phy(
  ETH_DEVICE     ETH_device,  /* @parm Ethernet controller hardware module 
                                       identification value */ 
  ETH_PHY_CONF  *ETH_phy_conf /* @parm Configuration parameters, to be 
                                       programmed in the PHY */  
);

/*
   @func Ethernet check link function,
   this function reads the PHY status register to detrmine if the link is up or
   not. The application can call this function before transmitting or receiving 
   data to determine if the link is up or not.
   @head4: (DESIGN) Implementation Details |
   @flag | - Read the PHY status register
   @flag | - Check if link is up, if yes retun ETH_SUCCESS else return ETH_ERR
   @retval  Returns Ethernet Status
   @flag ETH_SUCCESS | Link is up
   @flag ETH_ERR | Link is down
*/

ETH_STATUS ETH_check_link(
 ETH_DEVICE ETH_device /* @parm Ethernet controller hardware module 
                                       identification value */ 
);

  /* ETH detect PHY function */
/*
  @func:(DESIGN) Ethernet PHY autoneg
  @head4: (DESIGN) Implementation Details |
  @flag | - PHY autoneg routine should not be exposed to application and it will
            called by only ETH_initialise_phy routine.
  @flag | - Program the PHY for Autonegotiating with the link partner.
  @flag | - Set the start autoneg
  @flag |  - First try to find whether the PHY is present in the default address
  @flag |  - If found return success
  @flag |  -If not found, loop through all the addresses & store the address
            of the PHY
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | PHY detection is successful
*/

ETH_STATUS ETH_phy_autoneg(
  ETH_DEVICE     ETH_device
);


  /* ETH read PHY function */
/*
  @func:(DESIGN) Ethernet read PHY function
  @head4: (DESIGN) Implementation Details |
  @flag | - PHY initialisation routine should not be exposed to application 
            and it will called by only ETH_detect_phy routine.

  @flag | - Program the station management control register with the phy
           address, register address, command (read) & set the busy flag

  @flag | - Read the values of the station management data register
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | PHY detection is successful
*/
void ETH_read_phy(
  ETH_DEVICE    ETH_device,   /* @parm Ethernet controller hardware module 
                                       identification value */
  ETH_PHY_CTRL *ETH_phy_ctrl, /* @parm Pointer to structure containing the
                                       PHY address & register address*/
  IFX_UINT16   *ETH_mdio_data  /* @parm Pointer to data which was read from 
                                        the PHY register */
);
 /* Run time CAM programming function */
/*
  @func:(DESIGN) This function is used for CAM run time address programming
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be
            called by ETH_cam_ctrl() function at run time when the user wants to
            prog the CAM addresses
  @flag | - Addresses are divided into 3 cases A, B & C for ease of programming.
	       case A addresses are the 1st, 4th, 7th, 10th.. as programmed by the
           user they take the shape 
	    ______________
       |_____________|    
       |______|         in the CAM hardware array.

           case B addresses are the 2nd, 5th, 8th ... as programmed by the user
	       they take the shape 
  	          ________
        _____|_______|
       |_____________|	in the CAM hardware array.
	        Case C addresses are the 3rd, 6th, 9th ... as programmed by the user
		    They take the same shape as the case B addresses.

  @flag | - This function programs a single MAC address in the CAM.
  @flag | - The user_array_position field of the input parameter defines
            the position of the start of MAC address in the user array.
  @retval  None
*/
void ETH_camctrl_caseAodd(
  ETH_DEVICE    ETH_device,	   /* @parm Ethernet controller hardware module 
                                       identification value */

  ETH_CAM_PROG *ETH_cam_prog   /* @parm CAM programming parameters */
);
  /* Run time CAM programming function */
/*
  @func:(DESIGN) This function is used for CAM run time address programming
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be
            called by ETH_cam_ctrl() function at run time when the user wants 
            to prog the CAM addresses
  @flag | - This function programs sets of 2 MAC address in the CAM.
  @flag | - The addresses programmed by this function take the form
			  ______________
             |_____________|    
             |______|______|
             |_____________| 
			 ............ or multiples of these
  @flag | - The user_array_position field of the input parameter defines
            the position of the start of MAC address in the user array.
  @retval  None
*/
void ETH_camctrl_caseAeven(
  ETH_DEVICE    ETH_device,	  /* @parm Ethernet controller hardware module 
                                       identification value */
  ETH_CAM_PROG *ETH_cam_prog /* @parm CAM programming parameters */
);

  /* Run time CAM programming function */
/*
  @func:(DESIGN) This function is used for CAM run time address programming
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be
            called by ETH_cam_ctrl() function at run time when the user wants 
            to prog the CAM addresses
  @flag | - This is the case when the CAM addr have the position    
              ________										  
        ______|______|										  
       |_____________|
 

  @flag | - The user_array_position field of the input parameter defines
            the position of the start of MAC address in the user array.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Receive Buffer initialization is success
*/
void ETH_camctrl_caseB(
  ETH_DEVICE    ETH_device,	/* @parm Ethernet controller hardware module 
                                       identification value */
  ETH_CAM_PROG *ETH_cam_prog /* @parm CAM programming parameters */
);
/*
  @func:(DESIGN) Receive Buffer Initialization function
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be 
            called by ETH_initialise_dev()function at the time of driver 
            initialization.
  @flag | - Program the threshold codes.
  @flag | - Enable the Receive Buffer interrupts.
  @flag | - Initialize the RB by issuing an init command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Receive Buffer initialization is success
*/
ETH_STATUS ETH_initialise_rb
(
  ETH_DEVICE     ETH_device,/* @parm Ethernet controller hardware module 
                            identification value */ 
  ETH_COM_PARAMS *ETH_setup /* @parm Configuration parameters, to be programmed 
                              to the RB kernel registers  */
);

/*
  @func:(DESIGN) Transmit Buffer initialization function
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be
             called by ETH_initialise_dev() function at init time
  @flag | - Program the forward, refill threshold codes and individual transmit
               buffer size.
  @flag | - Enable the Transmit Buffer interrupts.
  @flag | - Initialize the TB by issuing an init command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Transmit Buffer initialization is success
*/
ETH_STATUS ETH_initialise_tb
(
  ETH_DEVICE     ETH_device, /*@parm Ethernet controller hardware module 
                                 identification value */
  ETH_COM_PARAMS *ETH_setup  /*@parm Configuration parameters, to be programmed 
                                    to the TB kernel registers  */
);

/*
  @func:(DESIGN) Data Management Unit Receive initialization function
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be 
             called by ETH_initialise_dev() function at init time 
  @flag | - Create and program the DMUR descriptors as a linked list and update
            all fields. Each DMUR descriptor will be associated with one data 
             buffer. 
  @flag | - ETH_CFG_DMUR_DESC_NUM and ETH_CFG_DMUR_DBUFF_SIZE are defined in 
            ETH_CFG.H file specifies the number of DMUR descriptors and each 
            data buffer size associated with descriptor respectively.
  @flag | - Program the configuration registers. Command complete, silent discard
             and frame end interrupts will be enabled 
            in the interrupt mask register.
  @flag | - Enable the DMUR interrupt.
  @flag | - Initialize the DMUR by issuing an init command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | DMUR initialization is success
*/
ETH_STATUS ETH_initialise_dmur
(
  ETH_DEVICE     ETH_device, /*@parm Ethernet controller hardware module 
                                     identification value */
  ETH_COM_PARAMS *ETH_setup /*@parm Configuration parameters, to be programmed 
                                 to the DR kernel registers  */
);

/*
  @func:(DESIGN) Data Management Unit Transmit Initialization function
  @head4: (DESIGN) Implementation Details |
  @flag | - This initialization function not exposed to application, it will be 
            called by ETH_initialise_dev()
            function at the time of driver initialization.
  @flag | - Create and program the DMUT descriptors as a linked list and update 
             all fields. 
  @flag | - The DMUT descriptors are not associated with data buffers each 
            descriptor will set the HI bit.
  @flag | - The define ETH_CFG_DMUT_DESC_NUM defined in ETH_CFG.H file specifies 
            the number of DMUT descriptors.
  @flag | - Program the configuration registers. Command complete, transmission
            abort and hold transmission abort interrupts are 
            enabled in the interrupt mask register. Host Indication bit also set
             in each descriptor.
  @flag | - Enable the DMUT interrupt.
  @flag | - Initialize the DMUT by issuing an init command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | DMUT initialization is success
*/
ETH_STATUS ETH_initialise_dmut
(
  ETH_DEVICE     ETH_device, /*@parm Ethernet controller hardware module 
  identification value */
  ETH_COM_PARAMS *ETH_setup  /*@parm Configuration parameters, to be programmed 
  to the kernel registers  */
);

#if ETH_CFG_FUNC_TERMINATE == 1
/*
  @func Ethernet Driver Terminate function, 
  this function sets the peripheral, selected by the ETH_device parameter, into 
  a disabled state and frees any system resources previously allocated in 
  ETH_initialise_dev. After this function has been called ETH_initialise_dev 
  must be called successfully before any of
  the other API functions are used.
  @head4: (DESIGN) Implementation Details |
  @flag | - API will be exposed to application.
  @flag | - Release the interrupt priorities and return to System HAL.
  @flag | - Free the ports and return to System HAL.
  @flag | - Call the each functional block(DMUR, DMUT, RB, TB and MAC) terminate
            routines.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of driver is success
  @flag ETH_ERR     | Termination of driver is failure.
*/
  ETH_STATUS ETH_terminate_dev
  (
    ETH_DEVICE ETH_device  /*@parm Ethernet controller hardware module 
                                    identification value*/
  );

/*
  @func:(DESIGN) Ethernet MAC controller terminate function
  @head4: (DESIGN) Implementation Details |
  @flag | - This function is not exposed to application and called by 
            ETH_terminate_dev at the time of driver termination.
  @flag | - Disable the MAC interrupts.
  @flag | - Disable the MAC receiver and transmitter.
  @flag | - Isolate PHY device.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of MAC is success
*/
  ETH_STATUS ETH_terminate_mac
  (
    ETH_DEVICE ETH_device  /*@parm Ethernet controller hardware module 
                            identification value*/
  ); 

/*
  @func:(DESIGN) Receive Buffer terminate function
  @head4: (DESIGN) Implementation Details |
  @flag | - This function is not exposed to application and called by 
            ETH_terminate_dev at the time of driver termination.
  @flag | - Disables the free pool monitor and action queue count interrupts.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of Receive Buffer is success
*/
  ETH_STATUS ETH_terminate_rb
  (
    ETH_DEVICE ETH_device /*@parm Ethernet controller hardware module 
                            identification value*/
  ); 

/*
  @func:(DESIGN) Transmit Buffer terminate function
  @head4: (DESIGN) Implementation Details |
  @flag | - This function is not exposed to application and called by 
            ETH_terminate_dev at the time of driver termination.
  @flag | - Disable the Transmit Buffer interrupt.
  @flag | - Stop the TB by issuing an off command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of Transmit Buffer is success
*/
  ETH_STATUS ETH_terminate_tb
  (
    ETH_DEVICE ETH_device /*@parm Ethernet controller hardware module 
                                   identification value*/
  ); 

/*
  @func:(DESIGN) Data Management Unit Receive terminate function
  @head4: (DESIGN) Implementation Details |
  @flag | - This function is not exposed to application and called by 
            ETH_terminate_dev at the time of driver termination.
  @flag | - Disables the interrupts associated with DMUR.
  @flag | - Stop the DMUR by issuing an off command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of DMUR is success
*/
  ETH_STATUS ETH_terminate_dmur
  (
    ETH_DEVICE ETH_device /*@parm Ethernet controller hardware module 
                             identification value*/
  );


/*
  @func:(DESIGN) Data Management Unit Transmit terminate function
  @head4: (DESIGN) Implementation Details |
  @flag | - This function is not exposed to application and called by 
            ETH_terminate_dev at the time of driver termination.
  @flag | - Disables the interrupts associated with DMUT.
  @flag | - Free the data buffers associated with DMUT and waiting for 
             transmission.
  @flag | - Stop the DMUT by issuing an off command.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of DMUT is success
*/
  ETH_STATUS ETH_terminate_dmut
  (
    ETH_DEVICE ETH_device /*@parm Ethernet controller hardware module 
                             identification value*/
  ); 

#else
#define ETH_terminate_dev(__ETH_PARM) ETH_ERR_NOT_SUPPORTED 
#endif /*ETH_CFG_FUNC_TERMINATE*/

#if ETH_CFG_FUNC_ABORT == 1
/*
  @func Ethernet driver abort function,
  this function cancels all currently queued data transfers and stops any 
  transfers currently being processed on the peripheral module selected by 
  ETH_device. 
  ETH_initialise_dev need not be called after this function before the other 
  API functions can be used, this function merely clears all current and pending
  transfers it does not terminate the HAL. New transfers may be requested using
  ETH_read and/or ETH_write immediately after this function returns. 
  This function may be used to clear all requests before changing modes
  @head4: (DESIGN) Implementation Details |
  @flag | - Stop the MAC TX and RX control blocks.
  @flag | - Set a flag to indicate the application that device is busy.
  @flag | - Issue an off command to the DMUT, DMUR and TB.
  @flag | - Free the pending TX request data buffers (memory) associated with 
            DMUT.
  @flag | - Rearrange all descriptors and data buffers associated with DMUR and 
            DMUT.
  @flag | - Enable all the functional blocks of Ethernet controller to make the 
            driver ready to receive and transmit frames.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Termination of DMUT is success
*/
ETH_STATUS ETH_abort
(
  ETH_DEVICE ETH_device /*@parm Ethernet controller hardware module 
                           identification number*/
);
#else
#define ETH_abort(__ETH_PARM1) ETH_ERR_NOT_SUPPORTED 
#endif


#if ETH_CFG_FUNC_STATUS == 1
/*
  @func Ethernet driver status function
  read and returns the current driver configuration settings. 
  Optionally returns the driver statistics counters provided ETH_CFG_STAT_LOG 
  feature is enabled.
  @head4: (DESIGN) Implementation Details |
  @flag | - Copy all the functional unit driver configuration parameters to the
            application provided data structure.
  @flag | - Copy the statistics counters optionally to the user provided data 
             structure.
  @flag | - The statistics counters only copied when ETH_CFG_STAT_LOG feature is
            enabled in ETH_CFG.H file. 
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Reading and returning the status of Ethernet driver is 
             success.
*/
ETH_STATUS ETH_status_dev
(
  ETH_DEVICE     ETH_device,  /*@parm Ethernet controller hardware module 
                                identification number */
  ETH_STAT_INF *ETH_stat_inf  /*@parm User provided structure to read present 
                                 configuration parameters
                                of a particular module */
);
#else
#define ETH_status_dev(__ETH_PARM1, __ETH_PARM2) ETH_ERR_NOT_SUPPORTED 
#endif  /*ETH_CFG_FUNC_STATUS*/


#if ETH_CFG_FUNC_CONTROL == 1
/* 
  @func Ethernet Controller runtime configuration control function,
  this function is used to change the existing configuration of driver 
  during the run time. This function will call the particular control function 
  depending upon the ETH_CTRL_CODE argument provided. 
  During these changes the driver will not be aborted from transmission and 
  reception of frames.

  @head4: (DESIGN) Implementation Details |
  @flag | - This function would be used to change the configuration settings of 
            a particular block of Ethernet controller. 
  @flag | - Check for the ETH_ctrl_code argument to identify the application 
             requested functional block to change the configuration parameters.
  @flag | - Depending upon the ETH_ctrl_code value call the appropriate IOCTL
            function.
  @flag | - To the called function pass the new configuration values (ctrl_data)
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
  @flag ETH_ERR | Change of configuration settings is failure
*/
ETH_STATUS ETH_control_dev
(
  ETH_DEVICE ETH_device,       /*@parm Ethernet controller hardware module 
                                 identification number. */
  ETH_CTRL_CODE ETH_ctrl_code, /*@parm The functional block which configuration
                                     has to be changed.*/
  void *ctrl_data              /*@parm The new configuration parameters.*/
);
#else
#define ETH_control_dev(__ETH_PARM1, __ETH_PARM2, __ETH_PARM3) ETH_ERR_NOT_SUPPORTED 
#endif

#if (ETH_CFG_FUNC_CTRL_MAC == 1)
/* 
  @func MAC controller runtime configuration control function,
  this function is used to change the MAC configuration during the run time.
   The configuration includes loop back and duplex modes.
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Function will change the MAC controller configuration parameters.
  @flag | - The parameters are duplex mode and loop back mode.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_mac
(
  ETH_DEVICE ETH_device,   /*@parm Ethernet controller hardware module 
                                 identification number */
  ETH_MAC_CONF *ctrl_data  /*@parm The new configuration data */
);
#endif 

#if (ETH_CFG_FUNC_CTRL_CAM == 1)
/*
  @func CAM controller runtime configuration control function,
  this function will be called by ETH_control_dev routine for
  Adding the MAC addresses to CAM, enable only the specified MAC addresses to 
  filter the receiving frames and change the configuration parameters.

  The application cannot remove the MAC addresses which are programmed into CAM.
   Either it can disable the MAC address or over writing the particular address 
   with all zeros.

  @head4: (DESIGN) Implementation Details |
  @flag | - Analyze the requested operation which is embedded in ETH_CAM_CTRL 
            argument.
  @flag | - To add/remove MAC addresses to/from CAM, writhe the application 
            provided addresses into CAM at specified address. 
  @flag | - Enable only the specified MAC addresses.
  @flag | - Change configuration parameters.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_cam
(
  ETH_DEVICE   ETH_device, /*@parm Ethernet controller hardware module 
                                identification number */
  ETH_CAM_CTRL *ctrl_data  /*@parm The new configuration data */
);
#endif

#if (ETH_CFG_FUNC_CTRL_MAC_TX == 1)
/*
  @func MAC TX controller runtime configuration control function,
  this function is used to change the attributes of the MAC Transmission 
  like adding CRC or pad during run time. 
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Change the MAC TX configuration values. 
  @flag | - Configuration values include adding pad to the out going frame, 
  provided the frame size is less than 64 bytes, adding CRC, checking defer.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_mac_tx
(
  ETH_DEVICE ETH_device,      /*@parm Ethernet controller hardware module
                                  identification number */
  ETH_MAC_TX_CONF *ctrl_data  /*@parm The new configuration data */
);
#endif

#if (ETH_CFG_FUNC_CTRL_MAC_RX == 1)
/*
  @func MAC RX controller runtime configuration control function,
  this function is used to change the attributes of the MAC RX during run time,
  like accept long/short frames, ignore CRC. 
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Change the MAC receiver control block configuration parameters.
  @flag | - The configuration parameters include checking the CRC, stripping 
               the CRC from received frames.
  @flag | - Accept or reject short(less than 64 bytes) and long(longer than
              1518 bytes) frames.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_mac_rx
(
  ETH_DEVICE ETH_device,      /*@parm Ethernet controller hardware module 
                                identification number */
  ETH_MAC_RX_CONF *ctrl_data  /*@parm The new configuration data */
);
#endif
 
#if (ETH_CFG_FUNC_CTRL_MAC_PHY == 1)
/*
  @func PHY device runtime configuration control function,
  change the physical device configuration settings like speed, duplex mode 
  during run time.
  The application can able to read/program any physical device and any of the 
  register which is inside PHY.
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - The application can be read/write the data from/to any register in 
            any of the PHY device.
  @flag | - This configuration is not updated in driver configuration parameters
              data structure.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_mac_phy
(
  ETH_DEVICE   ETH_device, /*@parm Ethernet controller hardware module 
                              identification number */
  ETH_PHY_CTRL *ctrl_data  /*@parm The new configuration data */
);
#endif

#if (ETH_CFG_FUNC_CTRL_TB == 1)
/*
  @func Transmit Buffer runtime configuration control function,
  change the transmit buffer configuration parameters like threshold values 
  during run time.
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Program the forward and refill threshold codes.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_tb
(
  ETH_DEVICE ETH_device,  /*@parm Ethernet controller hardware module 
                              identification number */
  ETH_TB_CONF *ctrl_data  /*@parm The new configuration data */
);
#endif

#if (ETH_CFG_FUNC_CTRL_DMUR == 1)
/*
  @func Data Management Unit Receive runtime configuration control function,
  changes the DMUR configuration parameters during run time. 
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Program the DMUR endian configuration value.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_dmur
(
  ETH_DEVICE ETH_device,   /*@parm Ethernet controller hardware module
                               identification number */
  ETH_DMUR_CONF *ctrl_data /*@parm The new configuration data */
);
#endif
  
#if (ETH_CFG_FUNC_CTRL_DMUT == 1)
/*
  @func To change the DMUT configuration,
  change the DMUT configuration parameters during run time.
  This function will be invoked internally by ETH_control_dev() function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Program the DMUT endian configuration value.
  @retval  Returns Ethernet Status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_ctrl_dmut
(
  ETH_DEVICE ETH_device,   /*@parm Ethernet controller hardware module 
                               identification number */
  ETH_DMUT_CONF *ctrl_data /*@parm The new configuration data */
);
#endif


#if ETH_CFG_FUNC_READ == 1
/* 
  @func Read data/frame received from PHY medium,
  this function is used by the application to register call back routine.
  When a complete descriptor is received, the receive ISR will call the 
  application receive callback function and pass the pointer to the data 
  buffer. The application is required to copy the data in its own
  (application’s buffer). The application must not make any assumptions
  about the data buffer once the callback function is exited.
  @head4: (DESIGN) Implementation Details |
  @flag | - Register the application provided call back function to the HAL. 
            This call back function will receive the frames coming from PHY 
             medium.
  @flag | - The call back function will copy the received frame into local data buffer 
            and release the buffer associated with frame.
  @flag | - The call back function should have a specific prototype 

            E.g. void app_callback(ETH_TRANSFER *rcvd_frm)
  @retval  Returns Ethernet status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_read
(
  ETH_DEVICE ETH_device,     /*@parm Ethernet controller hardware module 
                             identification number */
  ETH_APP_RX_CB ETH_app_rx_cb
);
#else
#define ETH_read(__ETH_PARM1, __ETH_PARM2) ETH_ERR_NOT_SUPPORTED 
#endif

#if ETH_CFG_FUNC_WRITE == 1
/* 
  @func This function is used by the application to register the transmit
  complete callback function with the Ethernet driver. The driver calls 
  the callback function to free the data buffer, after the data has been
  transmitted by the controller. 
  The callback function is passed as argument to this function.
  @head4: (DESIGN) Implementation Details |
  @flag | - Register the application provided call back function with the HAL.
            This callback function will be called by the driver in the DMUT ISR
            after a frmae has been transmitted by the controller.
  @flag | - The callback function will send the data buffer back to the appl 
            after which the application is free to reuse the buffer.
  @flag | - The call back function should have a specific prototype 
            E.g. void app_callback(ETH_TRANSFER *sent_buff)
  @retval  Returns Ethernet status
  @flag ETH_SUCCESS | Change of configuration settings is success
*/
ETH_STATUS ETH_reg_tx_cb
(
  ETH_DEVICE ETH_device,     /*@parm Ethernet controller hardware module 
                                    identification number */
  ETH_APP_TX_CB APP_tx_cb   /*@parm Pointer to application call back routine*/
);
#else
#define ETH_reg_tx_cb(__ETH_PARM1, __ETH_PARM2) ETH_ERR_NOT_SUPPORTED 
#endif

#if ETH_CFG_FUNC_WRITE == 1
/*
  @func Application writes data/frame to the driver, 
  this function will associate the data(frame) received from application to
  the DMUT free descriptor list. As soon as the data buffer is associated with 
  DMUT, this function will return the ETH_SUCCESS to calling function. If there
   is any failure it will return the failure status. The DMUT will automate the 
   process of transmission.
  @head4: (DESIGN) Implementation Details |
  @flag | - The DMUT will maintain 2 descriptor lists, one is free and another 
             one is fill descriptor list.
  @flag | - The frame received from application will be associated to free 
d           descriptor. This free descriptor will
            be disassociated from free descriptor list and attached to the tail
            end of DMUT fill descriptor list.
  @flag | - Check for the DMUT hold bit status, if the DMUT sets the hold bit 
            then it issues a hold reset command.
  @flag | - Always at least one free descriptor is maintained to protect global
            variables, which in turn make the ISRs   reentrant. 
  @retval  Returns Ethernet status
  @flag ETH_SUCCESS | The frame is associated to DMUT
  @flag ETH_ERR | The frame is not associated to DMUT, because of no free 
                  descriptors are available
*/
ETH_STATUS ETH_write
(
  ETH_DEVICE ETH_device,     /*@parm Ethernet controller hardware module 
                                     identification number */
  ETH_TRANSFER *ETH_transfer /*@parm Pointer to frame data*/
);
#else
#define ETH_write(__ETH_PARM1, __ETH_PARM2) ETH_ERR_NOT_SUPPORTED 
#endif
#endif /* __ETH_API_H */
