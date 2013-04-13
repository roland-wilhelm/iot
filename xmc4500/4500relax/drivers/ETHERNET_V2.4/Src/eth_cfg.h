/* 
=============================================================================
** Copyright (C) 2006 Infineon Technologies.
**
** All rights reserved.
** ============================================================================
**
** ============================================================================
**
** This document contains proprietary information belonging to Infineon 
** Technologies. Passing on and copying of this document, and communication of 
** its contents is not permitted without prior written authorisation.
**
** ============================================================================
*/
/* ============================================================================
**
** Revision Information :
** @FILENAME@:       eth_cfg.h
** @VERSION@:        2.4
** @DATE@:           20/1/2006
**
** ============================================================================
**
** Project: TC1130
** Block: ETH HAL 
**
** ============================================================================
** Contents: User can configure the required functionality of the Ethernet LLD 
**           in this file. If a praticular feature is required, then the
**           corresponding define is enabled.If the feature is not required
**           then the corresponding feature is disabled.   
** ============================================================================
** References: ETH API book
**
** ============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby,Rajesh    Release after code review.
** 06/04/2004                             Version number bumped to 2.1 to match 
**                                        the version of the C files 
** 29/04/2004                             Removed DMUR align as a config param
** 12/11/2004	   Badarinath Jayashree
**		           (IFIN SCC AI)	      Change in the ETH_CFG_MACADDRS3 value
** 20/1/2006       Mahesh Sriram Babu     ETH_CFG_USE_CACHE Definition has been
**                 (IFIN CSW AIM)         added to support data cache.
** @CHANGE_HISTORY@
** ============================================================================
*/
/* @doc API */
/*
  @topic2 Configuring the Ethernet HAL |
  Although the Ethernet HAL can be used immediately without configuring it to 
  suit a particular application it will often be the case that some features 
  written into the HAL will either be unnecessary; degrade performance to an 
  unacceptable level, take up too much memory or only be required for debugging
  purposes. For this reason the Ethernet HAL has been designed in such a way 
  that it can be easily configured to remove unused features, a number of 
  optional features may be enabled and/or disabled through the ETH_CFG.H file:

  –ETH device number checking

  –Initialisation check on API calls

  Additionally further options which affect the Ethernet HAL may be present in 
  the System HAL. Depending on the actual system in question these, or other, 
  options may be available:

  –On the fly peripheral clock changing

  –Initial interrupts numbers/priorities settings

  –ETH physical interface (GPIO) configuration

  The System HAL User Guide should be available from the same source as this 
  document, please refer to it for more details on the available settings 
  and features.
*/

#ifndef __ETH_CFG_H
#define __ETH_CFG_H

/*@topic2  Ethernet Driver HAL configuration parameters | */

/*
  @def  ETH_CFG_DEV_CHK  | Ethernet device check, 
  this define selects whether device ID 
  checking will be performed in the Ethernet HAL API 
  functions. Disabling this feature will result
  in less code being generated. This checking 
  is normally used when the h/w supports more than 
  one similar module. 

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
#define ETH_CFG_DEV_CHK 1


/*
  @def  ETH_CFG_INIT_CHK  | Ethernet initialization check,
  this define checks if the HAL
  has been initialized before executing.
  Disabling this feature will result in less 
  code being generated. This also acts as a 
  safe guard mechanism

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/

#define ETH_CFG_INIT_CHK 1



/*
  @def  ETH_CFG_STAT_LOG  | Ethernet log statistics enable,
  this define selects whether the ETH 
  HAL should maintain a log of successfully
  received/transmitted frames and frames with errors on 
  each peripheral it controls.
  This allows application software to validate 
  the reliability of the connection.
  
  If this is disabled, then driver handles the 
  interrupt which are critical to RX and TX. 

  Disabling this feature will result
  in smaller code and less data.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
#define ETH_CFG_STAT_LOG    1

/*
  @def ETH_CFG_USE_CACHE |
  This define select whether the cache memory is being used.
  The cache memory will be used only when the GNU compiler is
  used. Tasking compiler would not support this feature.
  ETH_drdesc, ETH_drdata and ETH_dtdesc shall be placed into
  cache memory. 
  
  To use the cache memory update the GNU loader script to place
  '.bss.32align.*' APIs into cache memory location.
  
  E.g.
  To use cache memory
  #define ETH_CFG_USE_CACHE

  Cache memory not used
  //#define ETH_CFG_USE_CACHE

*/
//#define ETH_CFG_USE_CACHE


/*
  @def ETH_CFG_USE_CAM |
  This define select whether the CAM feature
  should be included or excluded from the driver code.
  By using CAM the application would be accept or reject the 
  frames from the particular PHY devices by programming the 
  corresponding MAC address into CAM.
  CAM also provides the facilities like accepting/reject
  unicast, multicast or broadcast frames.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
#define ETH_CFG_USE_CAM   1

/*---------------------Starting of select routines -------------------------*/
/*
  @topic2 API Function Exclusion |
  If certain API functions are not required then they may be removed in order 
  to reduce code size. In the HAL distribution all the API functions will be 
  included by default, in order to remove an API function the relevant define 
  should located and value is changed from 1 to 0. This sections detail 
  defines which are available to exclude API functions from the HAL.
  Set Macro value as 1 to include corresponding function code.
  Setting the value zero not to include the function code
*/
/* 
  @def  ETH_CFG_FUNC_TERMINATE  |
  This controls whether or not the ETH_terminate_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ETH_CFG_FUNC_TERMINATE          1
/*
  @def  ETH_CFG_FUNC_ABORT  |
  This controls whether or not the ETH_abort API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ETH_CFG_FUNC_ABORT              1

/*
  @def  ETH_CFG_FUNC_STATUS  |
   This controls whether or not the ETH_status_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ETH_CFG_FUNC_STATUS             1

/*
  @def  ETH_CFG_FUNC_CONTROL  |
  This controls whether or not the ETH_control_dev API function is included.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ETH_CFG_FUNC_CONTROL            1
/*
  @def  ETH_CFG_FUNC_READ  |
  This controls whether or not the ETH_read API function is included. 
  Application cannot read the data received from PHY medium if this 
  feature is disabled.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ETH_CFG_FUNC_READ               1
/*
  @def  ETH_CFG_FUNC_WRITE  | 
  This controls whether or not the ETH_write API function is included. 
  Application cannot send data to PHY medium if this feature is disabled. 

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
#define ETH_CFG_FUNC_WRITE              1

#if ETH_CFG_FUNC_CONTROL == 1
/*
  This defines are used to change the current configuration of driver, 
  during run time. Only properties which are enabled here can be changed 
  during run time. If these are disabled they cannot be changed during 
  run time.
*/

/*
  @def  ETH_CFG_FUNC_CTRL_MAC  |
  This controls whether or not the ETH_ctrl_mac API function is included. 
  By disabling this feature the application is not able to change the MAC 
  configuration at run time.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_MAC           1

/*
  @def  ETH_CFG_FUNC_CTRL_CAM  |
  This controls whether or not the ETH_ctrl_mac_cam API function is included. 
  The application cannot add the MAC addresses and change the configuration 
  settings at run time if this feature is disabled.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_CAM           1

/*
  @def ETH_CFG_FUNC_CTRL_MAC_TX | 
   This controls whether or not the ETH_ctrl_mac_tx API function is included.
   If this feature is disabled the 
   application cannot change the MAC TX configuration settings during run time.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_MAC_TX        1

/*
  @def ETH_CFG_FUNC_CTRL_MAC_RX |
   This controls whether or not the ETH_ctrl_mac_rx API function is included. 
   If this feature is disabled the application cannot change the MAC receiver 
   configuration settings during run time. 

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_MAC_RX        1

/*
  @def ETH_CFG_FUNC_CTRL_MAC_PHY |
  This controls whether or not the ETH_ctrl_mac_phy API function is included. 
  Application may not able to   program the PHY devices at run time if this 
  feature is disabled.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_MAC_PHY       1

/*
  @def ETH_CFG_FUNC_CTRL_TB |
  This controls whether or not the ETH_ctrl_tb API function is included. 
  To change the threshold codes at run time this feature has to be enabled.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_TB            1

/*
  @def ETH_CFG_FUNC_CTRL_DMUR |
  This controls whether or not the ETH_ctrl_dmur API function is included. 
  By disabling this feature the application may not be able to change the 
  DMUR endian and alignment modes at run time.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_DMUR          1

/*
  @def  ETH_CFG_FUNC_CTRL_DMUT |
  This controls whether or not the ETH_ctrl_dmut API function is included. 
  The application is not able to change the endian mode at run time if this
  feature is disabled.

  @flag 1 | Include the function code in driver code

  @flag 0 | Exclude the function code from driver code
*/
# define ETH_CFG_FUNC_CTRL_DMUT          1

# endif /*ETH_CFG_FUNC_CONTROL*/


/*---------------------Ending of select routines -------------------------*/
/*
  @topic2 Ethernet driver initialization parameters |
  The application or user may configure the driver initialization parameters.
  These parameters can be changed at run time provided the corresponding 
  IOCTL function is included in driver. This can be done by enabling defines 
  ETH_CFG_FUNC_CTRL_xx.
*/

/* 
  @def ETH_CFG_FULLDUPLEX |
  Full duplex - Receive and transmit data simultaneously

  Half duplex - Either receive or transmit data at a specified time.

  @flag 1 |Enable the full duplex feature

  @flag 0 | Enable half duplex feature 
 
*/
# define ETH_CFG_FULLDUPLEX   1
/* 
  @def ETH_CFG_MAC_LOOPBACK  |
  In MAC loop back mode the frames transmitted at MAC TX will be received 
  at MAC RX. The data won't be propagated through the PHY device. This 
  feature mainly used for debugging the Ethernet controller. This 
  feature would be enabled when Ethernet controller operates in full duplex 
  mode.
    
  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_MAC_LOOPBACK     0
/* 
  @def  ETH_CFG_PHYDEV_LOOPBACK |
  In PHY device loop back mode the frames transmitted at MAC TX will be 
  received at MAC RX. The data will be propagated through the PHY device.
  This feature mainly used for debugging the Ethernet controller including 
  PHY device. This feature would be enabled when Ethernet controller 
  operates in full duplex mode.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_PHYDEV_LOOPBACK  0  /*1 = Phy device loop back */

/* 
   @def ETH_CFG_SPEED |
   By default Ethernet controller support both 100Mbps and 10Mbps modes. 
   This configuration value is used to configure the PHY device which is 
   attached to Ethernet controller.

  @flag 1 | 100Mbps mode

  @flag 0 | 10Mbps mode
*/
# define ETH_CFG_SPEED        1    /*0 = 10 Mbps, 1 = 100 Mbps*/


/*
  @def ETH_CFG_USE_PAUSE |
  This feature is used to send control frame when the device operates in 
  full duplex mode. If this feature is enabled the driver will send PAUSE 
  when there are no resources(data buffers) to receive the incoming data.
  If this feature is enabled the address (01-80-C2-00-00-01) is programmed 
  into CAM (ETH_CFG_MACADDRS0) to use as destination address for PAUSE. 
  The ETH_CFG_MACADDRS2 will be a source address.

  @flag 1 | Feature is enabled

  @flag 0 | Feature is disabled
*/
# define ETH_CFG_USE_PAUSE     0

/*
  @def ETH_CFG_PAUSE_TIME |
  The first 2 most significant bytes indicate the length of pause control 
  frame, ranges from 0x00 to 0xFFFF. This length is used in pause control 
  frame.

  The length of pause is measured in quanta, which is equal to 512 bit times.
*/
# define ETH_CFG_PAUSE_TIME    0x00FF0000

/*
  @def ETH_CFG_USE_CAM |
  This feature is used to filter the incoming frames on basis of destination 
  address encoded in received frame header with the MAC address in CAM table. 

  The user can program the desired MAC addresses in CAM.

  @flag 1 | Feature is enabled

  @flag 0 | Feature is disabled
*/
# if ETH_CFG_USE_CAM == 1

/*
  @def ETH_CFG_NEGATIVECAM  |
  The MAC controller will reject the frame which CAM recognizes and accept 
  the other frames. This feature has an effect when CAM is enabled.
  
  @flag 1 | Reject the frames which are CAM recognizes, accept others
 
  @flag 0 | Accept all frames, which is recognized by CAM
*/
#   define ETH_CFG_NEGATIVECAM   0

/* @def ETH_CFG_UNICAST |
   Accept all frames with the destination address of a single host.
   When this feature is enabled CAM does not have any effect on unicast 
   frames. When this feature is disabled and CAM is enabled,
   controller will accept the frames which are recognized by CAM.
    
  @flag 1 | Accept all unicast frames.

  @flag 0 | Accept the frames which are recognized by CAM, provided CAM 
  is enabled
*/
#   define ETH_CFG_UNICAST      1

/* 
  @def  ETH_CFG_MULTICAST |
  Accept all the frames which have the multicast address as destination 
  address irrespective of CAM table.

  @flag 1 | Accept all frames with multicast address as destination address

  @flag 0 | Reject multicast frames
*/
#   define ETH_CFG_MULTICAST    1

/* 
  @def ETH_CFG_BROADCAST |
  Accept all the frames which have the broadcast address as destination 
  address irrespective of CAM table.

  @flag 1 | Accept all frames with broadcast address as destination address

  @flag 0 | Reject broadcast frames
*/
#   define ETH_CFG_BROADCAST     1

/*
  @def ETH_CFG_MACADDR_STRT_LOC |
  Starting location of MAC addresses which are programmed into CAM. 
  If the pause feature is enabled then this value should be zero.
  The sum of ETH_CFG_MACADDR_STRT_LOC ranges from 0x0 to 0x13.
*/
#   define ETH_CFG_MACADDR_STRT_LOC 0

/*@def ETH_CFG_NUM_OF_MACADDR |
  The user can program up to 20 MAC addresses including the pause control 
  address fields. If the pause feature is not used then the user can 
  program up to 20 MAC addresses to filter the receiving frames from PHY 
  medium. Ranges from 0x1 to 0x14
  The sum of ETH_CFG_MACADDR_STRT_LOC and ETH_CFG_NUM_OF_MACADDR should be 
  less than or equal to 0x14.
*/
#   define ETH_CFG_NUM_OF_MACADDR   0x14

/*
  @def ETH_CFG_ENBL_MACADDRS |
  The following define is used to enable the MAC addresses programmed 
  into CAM. Each bit value corresponds to one MAC address i.e. 

  The MAC address 0 corresponds to least significant bit of 
  ETH_CFG_ENBL_MACADDRS.

  The MAC address 1 corresponds to second least significant bit of 
  ETH_CFG_ENBL_MACADDRS.

  The MAC address 2 corresponds to third least significant bit of 
  ETH_CFG_ENBL_MACADDRS.
*/
#   define ETH_CFG_ENBL_MACADDRS    0xFFF

/*
  The following ETH_CFG_MACADDRSx defines are used to program the MAC 
  addresses in CAM. If the user selects ETH_CFG_USE_PAUSE feature then 
  the value of  ETH_CFG_MACADDRS0 should be 01-80-c2-00-00-01 which is 
  used to send control (pause) frame when the driver is unable to 
  receive the frames. The ETH_CFG_MACADDRS1 is the source MAC address, which
  is also used control frame. The remaining 18 MAC addresses ranges from 
  2 t0 19 can be used to filter the received frames. The application no 
  need to program the MAC addresses incase it won't need to filter the 
  received frames.
*/
#   define ETH_CFG_MACADDRS0  {0x00,0x50,0x04,0x53,0x95,0x12}
#   define ETH_CFG_MACADDRS1  {0x11,0x22,0x33,0x44,0x55,0x66}
#   define ETH_CFG_MACADDRS2  {0x17,0x27,0x37,0x47,0x57,0x67}
#   define ETH_CFG_MACADDRS3  {0x12,0x34,0x56,0x78,0x9A,0xBC}
#   define ETH_CFG_MACADDRS4  {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS5  {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS6  {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS7  {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS8  {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS9  {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS10 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS11 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS12 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS13 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS14 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS15 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS16 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS17 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS18 {0,0,0,0,0,0}
#   define ETH_CFG_MACADDRS19 {0,0,0,0,0,0}
#  endif /*ETH_CFG_USE_CAM*/

/*
  MAC TX controller creates and adds the following data to 
  the out going frame, depinding on the configuration
*/

/* 
  @def  ETH_CFG_ADDPAD|
  If ETH_CFG_ADDPAD is enabled the MAC TX controller will add the pad 
  automatically, when the transmitted frame size less is than 64 bytes.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_ADDPAD       1

/* 
  @def ETH_CFG_ADDCRC |
  MAC TX controller will calculate and append the CRC to the out going frame.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_ADDCRC       1

/* 
  @def ETH_CFG_XDEFER | 
  MAC TX controller will check for excessive delays for the out going frame.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_XDEFER        1

/* 
  @def  ETH_CFG_SQECHECK |
  MAC TX controller will check for Signal Quality Error in 10Mbps mode

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_SQECHECK     1

/*
  The MAC unit can be configured to accept or reject certain packets
  depending on the MAC configuration, which are controlled by the following 
  defines. If any of the following options is enabled, MAC performs the 
  corresponding functionality, if any option is disabled MAC does not perform 
  the corresponding functionality.
*/

/*@def  ETH_CFG_RCVSHORT |
  MAC receive controller will accept the frames with frame length less 
  than 64 bytes. 

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_RCVSHORT     1

/*@def  ETH_CFG_RCVLONG |
  MAC RX controller will accept the frames with frame length more than 
  1518 bytes and long frame received interrupt won't be occurred upon 
  receiving long frames. 

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_RCVLONG      1

/*@def ETH_CFG_STRIPCRC |
  MAC RX controller will strip the CRC from received frames before it 
  storing on system memory.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_STRIPCRC     1

/*@def ETH_CFG_PASSCTRLPKTS | 

  MAC controller will pass the received control frames to the upper 
  layers(Logical Link Control layer).

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_PASSCTRLPKTS 1

/*@def ETH_CFG_NOTCHECKCRC |

  MAC RX controller will not check the CRC of received frames.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 
*/
# define ETH_CFG_NOTCHECKCRC  1

/*@def ETH_CFG_AUTONEGOTIATE |
  Auto-negotiation is a mechanism that enables devices to negotiate the 
  SPEED and MODE (duplex or half-duplex) of an Ethernet Link. This bit 
  can be set
  provided the PHY device also support this feature.

  @flag 1 | Enable the feature

  @flag 0 | Disable the feature 

  This feature is not supported in this version.
*/

# define ETH_CFG_AUTONEGOTIATE     1

/*@def ETH_CFG_TBFTC |
  The Transmit Buffer forward threshold code determines
  number of buffer locations which must be filled
  before protocol machines (e.g. Ethernet MAC) start
  transmission/segmentation. Nevertheless, the Transmit
  Buffer forwards data packets to the protocol machine as
  soon as an entire packet or the end of a packet is stored
  in the Transmit Buffer.

  @flag 0 | Correspond to 1 DWORD

  @flag 1 | Correspond to 4 DWORDS

  @flag 2 | Correspond to 8 DWORDS

  @flag 3 | Correspond to 12 DWORDS

  @flag 4 | Correspond to 16 DWORDS

  @flag 5 | Correspond to 24 DWORDS

  @flag 6 | Correspond to 32 DWORDS

  @flag 7 | Correspond to 40 DWORDS
*/
# define ETH_CFG_TBFTC       7

/*@def ETH_CFG_TBRTC |
  The internal Transmit Buffer has a programmable
  number of buffer locations per channel. When number of free locations 
  reaches Transmit Buffer refill threshold, internal Transmit Buffer requests
  new data from the DMUT.
  
  @flag 0 | Correspond to 1 DWORD

  @flag 1 | Correspond to 4 DWORDS

  @flag 2 | Correspond to 8 DWORDS

  @flag 3 | Correspond to 12 DWORDS

  @flag 4 | Correspond to 16 DWORDS

  @flag 5 | Correspond to 24 DWORDS

  @flag 6 | Correspond to 32 DWORDS

  @flag 7 | Correspond to 40 DWORDS
*/
# define ETH_CFG_TBRTC       2

/*@def ETH_CFG_BUFFSIZE |
  The Transmit Buffer size configures the number of
  internal Transmit Buffer locations for a particular
  channel. Buffer locations will be allocated on command
  transmit init and released after command transmit off.

  The sum of transmit forward threshold and
  the transmit refill threshold must be smaller than
  the internal buffer size.
  
  Ranges from 0x00 to 0xFF
*/
# define ETH_CFG_BUFFSIZE    0xFF 


/*@def ETH_CFG_DMUR_ENDIAN |
  Data Management Unit Receive will store the received frame in big/little 
  endian mode.

  @flag 0 | Little endian

  @flag 1 | Big endian
*/
# define ETH_CFG_DMUR_ENDIAN  0
 
/*@def ETH_CFG_DMUT_ENDIAN |
  Data Management Unit Transmit will transmit the frames in big/little 
  endian mode.

  @flag 0 | Little endian

  @flag 1 | Big endian
*/
# define ETH_CFG_DMUT_ENDIAN   0



/*@def ETH_CFG_DMUR_DESC_NUM |
  The number of descriptors and data buffers is maintained by DMUR. Each
  descriptor will be associated with one data buffer. 
*/
# define ETH_CFG_DMUR_DESC_NUM         0x8      

/*@def ETH_CFG_DMUR_DBUFF_SIZE |
  Size of data buffers which are associated with DMUR descriptor. 
  It is recommended that each data buffer size is good enough to 
  receive complete frame, it will save the execution time. Note 
  that the device handles the status (CRC, frame status) of frame based
  protocols (Ethernet) internally in the same way as payload data. 
  Therefore, byte number should include four bytes more than the 
  maximum length of incoming frames.
*/
# define ETH_CFG_DMUR_DBUFF_SIZE       2048
/*@def ETH_CFG_DMUT_DESC_NUM |
  The number of descriptors is maintained by DMUT. One descriptor 
  is not being used actively, to make the ISRs re-entrant.
*/
# define ETH_CFG_DMUT_DESC_NUM         0x8           

#endif /*__ETH_CFG_H*/
