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
** @FILENAME@:       ssc_api.h
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: This file contains #defines, data structures and function 
**           prototypes required for the SSC device driver
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      Bhavjit Walha        Release after code review.
** 07/05/2004      Mahesh               Added APIs for delays.
**
** @CHANGE_HISTORY@
** =============================================================================
*/	
/* @doc API */

/*
    @topic1 SSC HAL Application Program Interface |
    This section defines the interface between the peripheral hardware abstraction layer and
    the application software. It defines the constants, typedef names, function names and
    limitations of the HAL.
    The SSC HAL API utilizes a range of constants and typedef names in order to interact
    in a logical way with the application program. The first section of this chapter will look at
    these constants and data types.
    
    Please refer to appendix A - Infineon IFX types for details on the IFX data types. 
*/


#ifndef __SSC_API_H
#define __SSC_API_H


/*
  Header files required by the SSC HAL:
*/
#include "compiler.h" /* For IFX types and ISR macros */
#include "ssc_idl.h"   /* To determine what features are in hardware */
#include "ssc_cfg.h"  /* To determine the current configuration */
#include "sys_api.h"


/*
  @topic2 API constants and typedefs
*/

/*
@def  SSC_API_V_MAJ  | 
SSC_API_V_MAJ is defined to the major version of this API which the SSC HAL
supports. This version is defined as 0.1 so the following define will be in SSC_API.H:

#define SSC_API_V_MAJ 0

Application software may check this field to determine if the HAL API version is
acceptable. SSC_API_V_MAJ will be advanced whenever a change is made to this API
which will result in it being incompatible with older versions, this will only be done if the
API cannot be extended in a way which maintains backwards compatibility*/
#define SSC_API_V_MAJ 0

/*
@def  SSC_API_V_MIN  |
SSC_API_V_MIN is defined to the minor version of this API which the SSC HAL
supports. This version is defined as 0.1 so the following define will be in SSC_API.H:

#define SSC_API_V_MIN 1

Application software may check this field to determine if the HAL API version is
acceptable. SSC_API_V_MIN will be advanced whenever an extension is made to this
API which does not affect backwards compatibility. 
*/
#define SSC_API_V_MIN 1


/*
  @type SSC_DEVICE typedef | This indicates the Device ID
  @comm SSC_DEVICE is used in the API wherever a device must be selected. This is required
  because many SSC peripherals may be implemented in the same system.
*/
typedef IFX_UINT8 SSC_DEVICE;

/*
  @enum SSC_STATUS | 
  @comm Many of the following API functions will return an SSC_STATUS data type. This is a typedef
  name which is defined as an enumeration it can be found in SSC_API.H.
  SSC_STATUS is used by the HAL to return both the initial status of an operation and to
  communicate any errors encountered during data transmission back to the application
  via a user call back function.
*/
typedef enum
{
  SSC_SUCCESS = 0,           /*@emem SSC_SUCCESS indicates that an operation completed successfully.*/
  SSC_ERR = 1,               /*@emem SSC_ERR is used to indicate that an unspecified error was encountered 
                                 by the HAL. SSC_ERR will only be used as a last resort when the HAL is
                                 unable to describe the error using a more specific error code.*/
  SSC_ERR_RES = 2,           /*@emem SSC_ERR_RES is used to indicate that the SSC HAL was unable to allocate 
                                 a system resource required to carry out the requested operation. This 
                                 will only be used when the resource is not covered by the other 
                                 SSC_ERR_RES constants.*/
  SSC_ERR_RES_MEM = 3,       /*@emem SSC_ERR_RES_MEM is used to indicate that the HAL was unable to allocate
                                 enough memory to complete the requested operation.*/
  SSC_ERR_RES_IO = 4,        /*@emem SSC_ERR_RES_IO is used to indicate that one or more physical connection lines 
                                 are unavailable. This may be because a line is shared with another peripheral
                                 (and has been reserved) or if it is currently in use as a general purpose I/O line.*/
  SSC_ERR_NOT_SUPPORTED = 5, /*@emem SSC_ERR_NOT_SUPPORTED is used to indicate that a requested operation cannot be
                                 performed because it is not supported in software. This may be because a required
                                 software module has been configured out (see configuring the SSC HAL).*/
  SSC_ERR_NOT_SUPPORTED_HW = 6, /*@emem SSC_ERR_NOT_SUPPORTED_HW is used to indicate that a requested operation
                                    cannot be performed because a required feature is not supported in hardware.*/
  SSC_ERR_UNKNOWN_DEV = 7,      /*@emem SSC_ERR_UNKNOWN_DEV indicates that a device ID passed to an API function was
                                    not valid. Device ID checking can be removed from the HAL to reduce code size,
                                    see configuring the SSC HAL for details.*/  
  SSC_ERR_NOT_INITIALISED = 8,  /*@emem SSC_ERR_NOT_INITIALISED is returned if an API function is called before the
                                    HAL has been successfully initialised. This checking may be configured out
                                    to improve runtime performance and reduce code size, see configuring the 
                                    SSC HAL for information.*/
  SSC_ERR_PHASE = 9,            /*@emem SSC_ERR_PHASE is returned to indicate that a phase error occurred during
                                    SSC_read or SSC_write operation.*/ 
  SSC_ERR_RECEIVE = 10,          /*@emem SSC_ERR_RECEIVE is returned to indicate that an error occurred during a 
                                    SSC_read operation. This is usually because data was not
                                    read from the peripheral in time and was overwritten by the next incoming
                                    data word.*/
  SSC_ERR_BAUD = 11,             /*@emem SSC_ERR_BAUD is returned to indicate that a baud rate error was detected,
                                    this error will only occur when the peripheral is configured in slave mode.
                                    A baud rate error is detected when the clock signal from the master device
                                    differs substantially from that expected.*/
  SSC_ERR_TRANS = 12            /*@emem SSC_ERR_TRANS is returned to indicate that an error occurred during a 
                                    SSC_write operation. This usually means that data was 
                                    not written to the peripheral in time. This error will only occur when
                                     the peripheral is configured as a slave device.*/
} SSC_STATUS;


/*
  @enum SSC_CTRL_CODE |
  @comm SSC_CTRL_CODE is a typedef name which is defined as an enumeration.
  SSC_CTRL_CODE defines a number of enumeration constants
  that are used to request a specific operation from the SSC_control_dev API function.
*/
typedef enum
{
  SSC_CTRL_TRNS_BAUD = 0,         /*@emem This enumeration constant is used with the SSC_control_dev
                                      API function. SSC_CTRL_TRNS_BAUD may be used during runtime
                                      to change the baud rate. Refer to SSC_control_dev for
                                      more information. The baud rate is set initially by passing 
                                      a pointer to a SSC_COM_PARMS structure, with SSC_com_baud set
                                      appropriately, to SSC_initialise_dev.*/
  SSC_CTRL_TRNS_DATA = 1,         /*@emem This enumeration constant is used with the SSC_control_dev 
                                      API function. SSC_CTRL_TRNS_DATA may be used during runtime
                                      to change the number of bits per SSC data frame, this is the
                                      number of bits the SSC will shift for a single transfer.
                                      Refer to SSC_control_dev and SSC_DATA for more information.
                                      The word size is set initially by passing a pointer to a 
                                      SSC_COM_PARMS structure, with SSC_com_data set appropriately, 
                                      to SSC_initialise_dev.*/
  SSC_CTRL_TRNS_SHIFT = 2,        /*@emem This enumeration constant is used with the SSC_control_dev
                                      API function. SSC_CTRL_TRNS_SHIFT may be used during runtime
                                      to change which bit in the data word will be shifted onto the
                                      transmit line first using one of the enumeration constants in
                                      SSC_SHIFT_DIR. Please refer to SSC_control_dev and SSC_COM_PARMS
                                      for more information. The shift direction is set initially by 
                                      passing a pointer to a SSC_COM_PARMS structure, with SSC_com_shift
                                      set appropriately, to SSC_initialise_dev.*/
  SSC_CTRL_TRNS_PHASE = 3,        /*@emem This enumeration constant is used with the SSC_control_dev API function.
                                      SSC_CTRL_TRNS_PHASE may be used during runtime to change the clock edge 
                                      on which data will be shifted, and on which edge it will be latched, 
                                      using one of the enumeration constants in SSC_PHASE. Refer to SSC_control_dev
                                      and for more information. The phase is set initially by passing a pointer to 
                                      a SSC_COM_PARMS structure, with SSC_com_phase set appropriately, to 
                                      SSC_initialise_dev.*/  
  SSC_CTRL_TRNS_CLOCK = 4,       /*@emem This enumeration constant is used with the SSC_control_dev API function.
                                     SSC_CTRL_TRNS_CLOCK may be used during runtime to set the idle level for
                                     the clock line using one of the enumeration constants in SSC_CLOCK_IDLE.
                                     This is the level at which the clock line will be held when no transfer 
                                     is underway and the SSC is in master mode. Refer to SSC_control_dev
                                     for more information. The idle level for the clock line is set initially 
                                     by passing a pointer to a SSC_COM_PARMS structure, with SSC_com_clock set
                                     appropriately, to SSC_initialise_dev.*/ 
  SSC_CTRL_TX_HANDLING = 5,      /*@emem This enumeration constant is used with the SSC_control_dev API function.
                                    SSC_CTRL_TX_HANDLING may be used during runtime to set the scheme to be
                                    employed when a transmit line is shared. Please refer to SSC_control_dev
                                    and SSC_CFG_TX_OPTIONS for more information.*/
  SSC_CTRL_TRNS_ALL = 6,         /*@emem This enumeration constant is used with the SSC_control_dev API function.
                                    SSC_CTRL_TRNS_ALL may be used at runtime to change the baud rate, 
                                    operating mode, shift direction, phase and the clock idle level in
                                    one operation. Please refer to SSC_control_dev, SSC_DATA, SSC_CLOCK_IDLE,
                                    SSC_SHIFT_DIR and SSC_PHASE for more information. These communication 
                                    parameters are set initially by passing a pointer to an initialised 
                                    SSC_COM_PARMS structure to SSC_initialise_dev.*/
  SSC_CTRL_FIFO_GET_RX_DEPTH = 7, /*@emem This enumeration constant is used with the SSC_control_dev API function
                                      to return the depth of the receive FIFO supported in hardware. Refer to
                                      SSC_control_dev for more information.*/
  SSC_CTRL_FIFO_GET_TX_DEPTH = 8, /*@emem This enumeration constant is used with the SSC_control_dev API function
                                      to return the depth of the transmit FIFO supported in hardware. Refer to
                                      SSC_control_dev for more information.*/
  SSC_CTRL_FIFO_GET_RX_LEVEL = 9, /*@emem This enumeration constant is used with the SSC_control_dev API function
                                      to return the current filling level of the receive FIFO at which an 
                                      interrupt will be generated. Refer to SSC_control_dev for more information.*/
  SSC_CTRL_FIFO_GET_TX_LEVEL = 10, /*@emem This enumeration constant is used with the SSC_control_dev API function to 
                                      return the current filling level of the transmit FIFO at which an interrupt
                                      will be generated. Refer to SSC_control_dev for more information.*/ 
  SSC_CTRL_FIFO_SET_RX_LEVEL = 11, /*@emem This enumeration constant is used with the SSC_control_dev API function
                                      to set the filling level of the receive FIFO at which an interrupt will
                                      be generated. If this value is high there will be less interrupt overhead
                                      but the risk of losing data will be greater. Refer to SSC_control_dev for
                                      more information.*/
  SSC_CTRL_FIFO_SET_TX_LEVEL = 12, /*@emem This enumeration constant is used with the SSC_control_dev API function to
                                      set the filling level of the transmit FIFO at which an interrupt will be 
                                      generated. If this value is low there will be less interrupt overhead but
                                      the risk of losing data will be greater. Refer to SSC_control_dev for more
                                      information.*/
  SSC_CTRL_DISABLE = 13,           /*@emem This enumeration constant is used with the SSC_control_dev API function.
                                      SSC_CTRL_DISABLE may be used to disable any of the SSC peripherals 
                                      controlled by the HAL, any I/O pins previously allocated will all 
                                      be set to inputs, it is the users responsibility to ensure that 
                                      any external SSC devices are unaffected by this. Refer to SSC_control_dev
                                      for more information.*/
  SSC_CTRL_ENABLE = 14,            /*@emem This enumeration constant is used with the SSC_control_dev API function.
                                      SSC_CTRL_ENABLE may be used to enable any of the SSC peripherals 
                                      controlled by the HAL which have previously been disabled using 
                                      SSC_CTRL_DISABLE, any I/O pins previously allocated will all be set to
                                      inputs/outputs as relevant. Refer to SSC_control_dev for more information.*/
  SSC_CTRL_SLV_OSLCT = 15          /*@emem:(IMPLEMENT) This enumeration constant is used with the SSC_ctrl_slv_oslct API function.
                                      SSC_CTRL_SLV_OSLCT may be used to configuration slave select output pin(includes 
                                      lead, trail, inact delays) in master mode. This feature is fully hardware dependent.*/
} SSC_CTRL_CODE;


/*
  @enum SSC_MODE |
  @comm SSC_MODE is used with SSC_ctrl_trns_all to specify the operating mode of the SSC
  device.
*/
typedef enum
{
  SSC_MASTER = 0, /*@emem Peripheral will generate a clock to read or write data.*/
  SSC_SLAVE  = 1 /*@emem Peripheral will wait for a clock to be generated by another master 
                      device in order to read or write data.*/
} SSC_MODE;


/*
  @enum SSC_DATA |
  @comm SSC_DATA is used with SSC_ctrl_trns_all or SSC_ctrl_trns_data to set the width of
  a data word (the number of bits which the SSC will try to shift for each transfer). The
  lower limit is defined, in this API, as 2 bits and the upper as 16 bits. 

  typedef IFX_UINT8 SSC_DATA;
*/
typedef IFX_UINT8 SSC_DATA;

/*
  @enum SSC_SHIFT_DIR |
  @comm SSC_SHIFT_DIR may be used with SSC_ctrl_trns_all or SSC_ctrl_trns_shift to set
  which bit of the data word the SSC peripheral should shift out first.
*/
typedef enum
{
  SSC_MSB_FIRST = 0, /*@emem Transmit/receive most significant bit first.*/
  SSC_LSB_FIRST = 1  /*@emem Transmit/receive least significant bit first.*/
} SSC_SHIFT_DIR;


/*
  @enum SSC_CLOCK_IDLE |
  @comm SSC_CLOCK_IDLE may be used with SSC_ctrl_trns_all or SSC_ctrl_trns_clock to set the 
  level at which the clock line should remain when no data transfer is underway. This 
  will be ignored if the SSC is configured as a slave device.
*/
typedef enum
{
  SSC_CLOCK_IDLE_LOW  = 0, /*@emem Idle clock line is low, leading clock edge is low-to-high transition.*/
  SSC_CLOCK_IDLE_HIGH = 1  /*@emem Idle clock line is high, leading clock edge is high-to-low transition.*/
} SSC_CLOCK_IDLE;


/*
  @enum SSC_PHASE |
  @comm SSC_PHASE may be used with SSC_ctrl_trns_all or SSC_ctrl_trns_phase to set the
  clock edge on which data should be shifted and on which edge it should be latched.
*/
typedef enum
{
  SSC_LATCH_RISING  = 0, /*@emem Shifts transmit data on the leading clock edge, latch on trailing edge.*/
  SSC_LATCH_FALLING = 1  /*@emem Latch receive data on leading clock edge, shift on trailing edge.*/
} SSC_PHASE;


/*
 @struct SSC_COM_PARMS |
 @comm SSC_COM_PARMS is a typedef name which is defined as a structure, it can be found
 in SSC_API.H. The SSC_COM_PARMS structure is used to specify complete
 communication settings for the SSC devices controlled by the HAL. It is used with the
 SSC_ctrl_trns_all and SSC_status_dev API functions. 
*/
typedef struct
{
  SSC_MODE       SSC_mode;      /*@field Mode of device is currently operating either in slave/master.*/
  SSC_DATA       SSC_com_data;  /*@field Number of data bits that the device expects per data frame.*/
  IFX_UINT8      SSC_slave_num; /*@field Slave select input (slave mode[1])/output (master mode[1 - 8]) number,
                                         if value is zero slave select functionality not provided*/
  SSC_CLOCK_IDLE SSC_com_clock; /*@field Level of clock line will remain at idle state.*/
  SSC_PHASE      SSC_com_phase; /*@field Clock edge the SSC shifts data out and on which edge it latches data in.*/
  SSC_SHIFT_DIR  SSC_com_shift; /*@field Bit of the data word SSC shifts out first.*/
  IFX_UINT32     SSC_com_baud;  /*@field Baud rate of device.*/
} SSC_COM_PARMS;

/*
  @struct SSC_OSLAVE_OPT |
  @comm This structure is used to configure the slave select output line at run time.
  This feature is fully hardware dependent feature.
*/
typedef struct
{
  IFX_UINT16 SSC_lead_dly:2;      /*@field Number of leading delay cycles, ranges from 0 - 3.*/
  IFX_UINT16 SSC_trl_dly:2;       /*@field Number of trail delay cycles, ranges from 0 - 3.*/
  IFX_UINT16 SSC_inact_dly:2;     /*@field Number of inact delay cycles, ranges from 0 - 3.*/
  IFX_UINT16 SSC_delay:1;         /*@field Specifies the mode of device 0 --> normal, 1 --> delay.*/
  IFX_UINT16 SSC_line_logic_lvl:1; /*@filed Logic level (0/1) of output line during slave select active time.*/
  IFX_UINT16 SSC_slv_idl_lvl:1;    /*@field Defines the logic level of the slave mode
                                            transmit signal MRST when the SSC is deselected*/  
  IFX_UINT16 SSC_slv_num:7;        /*@field Slave select number output (master)/input (slave)*/
}SSC_OSLAVE_OPT;


/*
  @struct SSC_TRANSFER |
  @comm SSC_TRANSFER is used by the SSC_read and SSC_write functions to provide
  information regarding the data transfer that is to be performed.
*/
typedef struct SSC_transfer
{
  void *SSC_buffer;             /*@field Address of the data buffer which is to be used for transmit data 
                                         or filled with data read from the selected SSC device.*/
  IFX_UINT32 SSC_buffer_size;   /*@field Size of data buffer used to read or transmit.*/
  IFX_UINT32 SSC_return_num;    /*@field Actual number of data frames read or transmitted.*/
  SYS_TRANS_MODE SSC_transfer_mode; /*@field Set with one of the constants defined in the SYS_TRNS_MODE enum.*/
  void (*SSC_trans_ucb)(struct SSC_transfer *, SSC_STATUS);
                                 /*@field Address of the user call back function to call when the transfer 
                                 is complete. This may be set to 0 if no user call back function is to be 
                                 invoked.*/   
  IFX_UINT32 SSC_slave_device;  /*@field Address of the slave to write data to if slave addressing 
                                          is supported in hardware.*/
} SSC_TRANSFER;

/*
  @struct SSC_STAT_INF |
  @comm It is used by the SSC_status_dev API function to return information about any of the SSC peripherals
  controlled by the HAL.
*/
typedef struct
{
  SSC_COM_PARMS SSC_com_parms;     /*@field Current configuration of the selected SSC device.*/
  #if SSC_CFG_STAT_LOG == 1
  IFX_UINT32    SSC_receive_err;   /*@field Current value of the internal receive error counter, after
                                            this call this counter will be reset to 0. SSC_receive_err
                                            will only be present if status logging is enabled in the 
                                            SSC HAL, see configuring the SSC HAL for details.*/
  IFX_UINT32    SSC_transmit_err;  /*@field Current value of the internal transmit error counter, after
                                            this call this counter will be reset to 0. SSC_transmit_err
                                            will only be present if status logging is enabled in the 
                                            SSC HAL, see configuring the SSC HAL for details.*/
  IFX_UINT32    SSC_successful;    /*@field Number of words sent of received without error, after this
                                            call the counter will be reset to 0. SSC_successful will 
                                            only be present if status logging is enabled in the SSC HAL,
                                            see configuring the SSC HAL for details.*/
  IFX_UINT8     SSC_phase_err;     /*@field Current value of the internal phase error counter, after this
                                            call this counter will be reset to 0. SSC_phase_err will only
                                            be present if status logging is enabled in the SSC HAL, 
                                            see configuring the SSC HAL for details.*/
  IFX_UINT8     SSC_baud_err;      /*@field Current value of the internal baud error counter, after this
                                            call this counter will be reset to 0. SSC_baud_err will only
                                            be present if status logging is enabled in the SSC HAL, 
                                            see configuring the SSC HAL for details.*/
  #endif

  IFX_UINT8     SSC_tx_fifo_lev;   /*@field Number of words currently in the transmit FIFO or 0 if
                                            there is no transmit FIFO on the device.*/
  IFX_UINT8     SSC_rx_fifo_lev;   /*@field Number of words currently in the receive FIFO or 0 if 
                                            there is no receive FIFO on the device.*/
  SSC_DATA      SSC_current_progress; /*@field Set to the number of bits that have been shifted in the
                                               current transaction.*/
} SSC_STAT_INF;


/*   @topic2 API Functions |*/

/*
  @func SSC driver initialization function,
  this function initialises the internal data structures of the HAL related to the device
  selected by SSC_device, allocates any required system resources and configures the peripheral
  according to the SSC_COM_PARMS structure. The SSC_COM_PARMS structure must be initialised by 
  the user before calling SSC_initialise_dev. This function must be called successfully before 
  any of the other API functions are used and if SSC_terminate_dev is called then 
  SSC_initialise_dev must be called again before using the other API functions.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Enable the module by programming the clock control register.
  @flag: (DESIGN)  | - Set interrupts priorities and IO ports.
  @flag: (DESIGN)  | - Program controller with the application provided configuration parameters (Mode, 
                       number of bits per data frame, polarity and phase) by calling SSC_set_all API. 
  @flag: (DESIGN)  | - Program receive and transmit FIFOs with the user defined interrupt trigger levels.
  @flag: (DESIGN)  | - Initialize all global variables and set the baud rate.
  @flag: (DESIGN)  | - Enable SSC and global interrupts.
  @retval  SSC status
  @flag SSC_SUCCESS              | Initialization is successful.
  @flag SSC_ERR_NOT_SUPPORTED_HW | FIFO levels are not with in the device supported limits.
  @flag SSC_ERR_BAUA             | Not able to get the required baud rate within user configured tolerance level.
  @flag SSC_ERR_RES_IO           | System HAL is not able to reserve required ports required by SSC.
*/
SSC_STATUS SSC_initialise_dev
(
  SSC_DEVICE SSC_device,   /*@parm SSC hardware module identification number (e.g. 0-->SSC0, 1-->SSC1).*/
  SSC_COM_PARMS *SSC_setup /*@parm Driver initialization configuration parameters.*/
);

#if SSC_CFG_FUNC_TERMINATE == 1
/*
  @func SSC driver termination function,
  this function sets the peripheral, selected by the SSC_device parameter, into a disabled
  state and frees any system resources previously allocated in SSC_initialise. After this
  function has been called SSC_initialise_dev must be called successfully before any of
  the other API functions are used.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Disable the module by programming clock control and control registers.
  @flag: (DESIGN)  | - Return ports to the System HAL.
  @retval  SSC status
  @flag SSC_SUCCESS    | Termination of device is successful.
  @flag SSC_ERR_RES_IO | Error occurred while returning ports to System HAL.
*/
SSC_STATUS SSC_terminate_dev
(
  SSC_DEVICE SSC_device /*@parm SSC hardware module identification number.*/
);
#else
#define SSC_terminate_dev(__SSC_PARM) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_ABORT == 1
/*
  @func SSC driver abort function
  cancels all currently queued data transfers and stops any transfers currently being
  processed on the peripheral module selected by SSC_device. SSC_initialise_dev need
  not be called after this function before the other API functions can be used, this function
  merely clears all current and pending transfers it does not terminate the HAL. New
  transfers may be requested using SSC_read and/or SSC_write immediately after this
  function returns. All aborted transfers will return an SSC_ERR error code. This function
  may be used to clear all requests before changing modes etc.  

  @head4 :(DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Disable the controller by programming control register.
  @flag: (DESIGN)  | - Cancel all pending read and write requests by returning SSC_ERR status.
  @flag: (DESIGN)  | - Flush receive and transmit FIFOs. 
  @flag: (DESIGN)  | - Enable the controller by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Abort of device is successful.
*/
SSC_STATUS SSC_abort
(
  SSC_DEVICE SSC_device /*@parm SSC hardware module identification number.*/
);
#else
#define SSC_abort(__SSC_PARM) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_STATUS == 1
/*
  @func SSC driver status function,
  return the present driver configuration parameters and statistics information. Configuration 
  parameters include number of data bits per frame, phase, polarity, baud rate and FIFO levels.
  Statistics include number of data frames received/transmitted success fully without errors, 
  phase errors, transfer, receive and baud rate errors. After returning from this function all
  statistics counters will re reset to zero. 
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_com_parms.SSC_mode will be set to the mode the device is
                       currently operating in.
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_com_parms.SSC_com_data will be set to indicate the number of
                       data bits the device expects per data frame.
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_com_parms.SSC_com_baud will be set to the currently selected
                       baud rate.
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_com_parms.SSC_com_clock will be set to indicate the level the
                       clock line will remain at when idle.  
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_com_parms.SSC_com_phase will be set according to the clock
                       edge the SSC shifts data out and on which edge it latches data in.
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_com_parms.SSC_com_shift will be set to indicate which bit of the
                       data word the SSC shifts out first.
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_rx_fifo_lev will specify how many data frames are currently
                       stored in the receive FIFO.
  @flag: (DESIGN)  | - SSC_STAT_INF.SSC_tx_fifo_lev will specify how many data frames are currently
                       stored in the transmit FIFO.
  @flag: (DESIGN)  | - If statistics logging is enabled then the following members of the SSC_STAT_INF
                       structure will be available:

           – SSC_successful, number of frames successfully received or transmitted.

           – SSC_phase_err, number of frames received with phase error.

           – SSC_receive_err, number of frames with receive error.

           – SSC_transmit_err, number of frames with transmit error.

  @flag: (DESIGN)  | - These frame counters will be reset to 0 after the SSC_status_dev API has been called.  
  @retval  SSC status
  @flag SSC_SUCCESS | Status of device success fully read and returned to application.
*/
SSC_STATUS SSC_status_dev
(
  SSC_DEVICE SSC_device,     /*@parm SSC hardware module identification number.*/
  SSC_STAT_INF *SSC_stat_inf /*@parm Data structure to write the current status of the device. */
);
#else
#define SSC_status_dev(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif



#if SSC_CFG_FUNC_CONTROL == 1
/*
  @func SSC driver runtime configuration control function,
  SSC_control_dev may be used as a single entry point for all the control functions, such
  as set baud rate, which are provided in the SSC HAL API.

  The device to configure must be selected by using the SSC_device parameter.
  
  The function to call is specified by the SSC_ctrl_code. One of the enumeration constants
  from SSC_CTRL_CODE must be used to specify the operation to perform.
  
  The SSC_ctrl_arg parameter is used to pass arguments to the configuration function, it
  is a void pointer because its actual use depends upon the function requested.
  
  The direct call equivalents are also described, it is quicker to use the function directly without
  going through SSC_control_dev.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Call control function specified by the SSC_ctrl_code. The SSC_ctrl_code is one of the enumeration 
                      constants from SSC_CTRL_CODE to specify the operation to perform.
  @flag: (DESIGN) | - Typecast the SSC_ctrl_arg parameter with respect to the called function. 
  @retval  SSC status
  @flag SSC_SUCCESS | Setting the new configuration parameters is successful.
  @flag SSC_ERR     | The provided SSC_ctrl_code does not match with any of the values defined in SSC_CTRL_CODE.
*/
SSC_STATUS SSC_control_dev
(
  SSC_DEVICE SSC_device,       /*@parm SSC hardware module identification number.*/
  SSC_CTRL_CODE SSC_ctrl_code, /*@parm Operation to perform is specified by one of the enum in SSC_CTRL_CODE.*/
  void *SSC_ctrl_arg           /*@parm New configuration parameters.*/
);
#else
#define SSC_control_dev(__SSC_PARM1, __SSC_PARM2, __SSC_PARM3) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_BAUD == 1
/*
  @func SSC driver run time baud rate control function 
  used to select the baud rate for the chosen device. The argument should be treated as an 
  IFX_UINT32 data type and should be set to specify the required baud rate.

  E.g. IFX_UINT32 SSC_baud_rate = 32000;
       SSC_ctrl_trns_baud(first_dev, SSC_baud_rate);

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable SSC device by programming control register.
  @flag: (DESIGN) | - Program required baud rate by calling SSC_set_baud API.
  @flag: (DESIGN) | - Update global variable with new baud rate.
  @flag: (DESIGN) | - Enable SSC device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Setting the new Baud rate is successful.
  @flag SSC_ERR     | New baud rate is not supported by hardware or not able to get with in 
                      user specified tolerance level.
*/
SSC_STATUS SSC_ctrl_trns_baud
(
  SSC_DEVICE SSC_device,    /*@parm SSC hardware module identification number.*/
  IFX_UINT32 SSC_ctrl_baud  /*@parm New baud rate to be programmed.*/  
);
#else
#define SSC_ctrl_trns_baud(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_DATA == 1
/*
  @func SSC driver run time data control function,
  used to select the number of data bits per frame. The argument
  should be treated as an SSC_DATA data type and should be set between 
  2 and 16 (inclusive) to specify the required number of data bits.

  E.g. SSC_DATA SSC_ctrl_data = 7;
       SSC_ctrl_trns_data(first_dev, SSC_ctrl_data);

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable SSC device by programming control register.
  @flag: (DESIGN) | - Program new number of bits per data frame.
  @flag: (DESIGN) | - Update global variable with new configuration.
  @flag: (DESIGN) | - Enable SSC device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Setting number of bits per data frame is successful.
  @flag SSC_ERR     | New configuration is not supported by hardware.
*/
SSC_STATUS SSC_ctrl_trns_data
(
  SSC_DEVICE SSC_device, /*@parm SSC hardware module identification number.*/
  SSC_DATA SSC_ctrl_data /*@parm New configuration specifies number of bits per frame.*/
);
#else
#define SSC_ctrl_trns_data(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_CLOCK == 1
/*
  @func SSC driver run time clock control function,
  used to select the level the clock line should remain at while the
  SSC is idle. The argument should be treated as an SSC_CLOCK_IDLE enumeration constant and should
  be set using one of the enumeration constants defined in SSC_CLOCK_IDLE.

  E.g. SSC_CLOCK_IDLE SSC_ctrl_clk = SSC_CLOCK_IDLE_HIGH;
       SSC_ctrl_trns_clock(first_dev, SSC_ctrl_clk);

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable SSC device by programming control register.
  @flag: (DESIGN) | - Program new idle state of clock.
  @flag: (DESIGN) | - Update global variable with new configuration.
  @flag: (DESIGN) | - Enable SSC device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Setting new idle state of clock is successful.
*/
SSC_STATUS SSC_ctrl_trns_clock
(
  SSC_DEVICE SSC_device,       /*@parm SSC hardware module identification number.*/
  SSC_CLOCK_IDLE SSC_ctrl_clock /*@parm New configuration parameters.*/
);
#else
#define SSC_ctrl_trns_clock(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif

#if SSC_CFG_FUNC_CTRL_PHASE == 1
/*
  @func SSC driver run time phase control function,
  used to select the clock edge that should be used to shift data
  and which edge should be used to latch data. The argument should be treated as an
  SSC_PHASE data type. The SSC_PHASE enumeration constant should be set using one 
  of the enumeration constants defined in SSC_PHASE.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable SSC device by programming control register.
  @flag: (DESIGN) | - Program new clock phase.
  @flag: (DESIGN) | - Update global variable with new configuration.
  @flag: (DESIGN) | - Enable SSC device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Setting new phase of clock is successful.
*/
SSC_STATUS SSC_ctrl_trns_phase
(
  SSC_DEVICE SSC_device,  /*@parm SSC hardware module identification number.*/
  SSC_PHASE SSC_ctrl_phase /*@parm New configuration parameters.*/
);
#else
#define SSC_ctrl_trns_phase(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_SHIFT == 1
/*
  @func SSC driver run time data shift (LSB/MSB) control function,
  used to select which bit is shifted out by the SSC first. The
  argument should be treated as an SSC_SHIFT_DIR data type. The 
  SSC_SHIFT_DIR enumeration constant should be set using one
  of the enumeration constants defined in SSC_SHIFT_DIR.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable SSC device by programming control register.
  @flag: (DESIGN) | - Program new first bit position (MSB/LSB) of data to receive/transmit.
  @flag: (DESIGN) | - Update global variable with new configuration.
  @flag: (DESIGN) | - Enable SSC device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Setting new configuration is successful.
*/
SSC_STATUS SSC_ctrl_trns_shift
(
  SSC_DEVICE SSC_device,       /*@parm SSC hardware module identification number.*/
  SSC_SHIFT_DIR SSC_ctrl_shift /*@parm New configuration parameters.*/
);
#else
#define SSC_ctrl_trns_shift(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_ALL == 1
/*
  @func SSC driver run time configuration control function 
  used to configure all the SSC communication settings and allows the operating
  mode to be changed. The argument should be treated as a SSC_COM_PARMS data type.
  The SSC_COM_PARMS structure should be initialised to set the desired communication parameters.
  @comm Slave select configuration do not handled in this routine, user has to configure separately by
  calling SSC_ctrl_slv_oslct API.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable SSC device by programming control register.
  @flag: (DESIGN) | - Program new configuration parameters by calling SSC_set_all API.
  @flag: (DESIGN) | - Enable SSC device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS | Setting new configuration is successful.
*/
SSC_STATUS SSC_ctrl_trns_all
(
  SSC_DEVICE SSC_device,      /*@parm SSC hardware module identification number.*/
  SSC_COM_PARMS *SSC_ctrl_all /*@parm New configuration parameters.*/ 
);
#else
#define SSC_ctrl_trns_all(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif

#if SSC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH == 1
/*
  @func SSC driver run time receive FIFO depth read control function,
  used to return the depth of the receive FIFO available on a SSC    
  peripheral controlled by the HAL. For the purposes of this function the argument should
  be treated as an IFX_UINT8 pointer. If there is no receive FIFO then
  SSC_ERR_NOT_SUPPORTED_HW will be returned and the IFX_UINT8 pointed to will
  be set to 0. If a receive FIFO is available then the IFX_UINT8 will be set to the depth of
  the receive FIFO and SSC_SUCCESS will be returned from SSC_control_dev.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Return hardware supported receive FIFO depth.
  @retval  SSC status
  @flag SSC_SUCCESS              | Successfully return the receive FIFO depth.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Receive FIFO not supported by hardware.
*/
SSC_STATUS SSC_ctrl_fifo_get_rx_depth
(
  SSC_DEVICE SSC_device,  /*@parm SSC hardware module identification number.*/
  IFX_UINT8 *rx_fifo_depth /*@parm Pointer to read RX FIFO depth.*/
);
#else
#define SSC_ctrl_fifo_get_rx_depth(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif

#if SSC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH == 1
/*
  @func SSC driver run time transmit FIFO depth read control function,
  used to return the depth of the transmit FIFO available on a SSC
  peripheral controlled by the HAL. For the purposes of this function the argument should
  be treated as an IFX_UINT8 pointer. If there is no transmit FIFO then
  SSC_ERR_NOT_SUPPORTED_HW will be returned and the IFX_UINT8 pointed to will
  be set to 0. If a transmit FIFO is available then the IFX_UINT8 will be set to the depth of
  the transmit FIFO and SSC_SUCCESS will be returned from SSC_control_dev.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Return hardware supported transmit FIFO depth.
  @retval  SSC status
  @flag SSC_SUCCESS              | Successfully return the transmit FIFO depth.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Transmit FIFO not supported by hardware.
*/
SSC_STATUS SSC_ctrl_fifo_get_tx_depth
( 
  SSC_DEVICE SSC_device,   /*@parm SSC hardware module identification number.*/
  IFX_UINT8 *tx_fifo_depth /*@parm Pointer to read RX FIFO depth.*/
);
#else
#define SSC_ctrl_fifo_get_tx_depth(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL == 1
/*
  @func SSC driver run time receive FIFO level read control function,
  used to return the number of data frames to be in receive FIFO available for receive on a SSC
  peripheral controlled by the HAL. For the purposes of this function the argument should
  be treated as an IFX_UINT8 pointer. If there is no receive FIFO then
  SSC_ERR_NOT_SUPPORTED_HW will be returned and the IFX_UINT8 pointed to will
  be set to 0. If a receive FIFO is available then the IFX_UINT8 will be set to level of
  the receive FIFO and SSC_SUCCESS will be returned from SSC_control_dev.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Return the number of data frames in receive FIFO.
  @retval  SSC status
  @flag SSC_SUCCESS              | Successfully return the number of data frames in receive FIFO.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Transmit FIFO not supported by hardware.
*/
SSC_STATUS SSC_ctrl_fifo_get_rx_level
(
  SSC_DEVICE SSC_device, /*@parm SSC hardware module identification number.*/
  IFX_UINT8 *rx_fifo_lvl /*@parm Pointer to read RX FIFO level.*/
);
#else
#define SSC_ctrl_fifo_get_rx_level(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL == 1
/*
  @func SSC driver run time transmit FIFO level read control function,
  used to return the number of data frames to be in transmit FIFO available for transmit on a SSC
  peripheral controlled by the HAL. For the purposes of this function the argument should
  be treated as an IFX_UINT8 pointer. If there is no transmit FIFO then
  SSC_ERR_NOT_SUPPORTED_HW will be returned and the IFX_UINT8 pointed to will
  be set to 0. If a transmit FIFO is available then the IFX_UINT8 will be set to level of
  the transmit FIFO and SSC_SUCCESS will be returned from SSC_control_dev.  
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Return the number of data frames in transmit FIFO.
  @retval  SSC status
  @flag SSC_SUCCESS              | Successfully return the number of data frames in transmit FIFO.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Transmit FIFO not supported by hardware.
*/
SSC_STATUS SSC_ctrl_fifo_get_tx_level(
  SSC_DEVICE SSC_device,  /*@parm SSC hardware module identification number.*/
  IFX_UINT8 *tx_fifo_lvl  /*@parm Pointer to read TX FIFO level.*/
);
#else
#define SSC_ctrl_fifo_get_tx_level(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif

#if SSC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL == 1
/*
  @func SSC driver run time receive FIFO level write control function,
  this function may be used to set the filling level at which the receive FIFO will generate
  an interrupt. For the purposes of this function the argument should be treated as an
  IFX_UINT8 variable. If there is no receive FIFO then SSC_ERR_NOT_SUPPORTED_HW will be returned.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Set the interrupt trigger level of RX FIFO.
  @retval  SSC status
  @flag SSC_SUCCESS              | Successfully programmed receive FIFO interrupt trigger level.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Receive FIFO not supported by hardware or disabled by software.
*/
SSC_STATUS SSC_ctrl_fifo_set_rx_level 
(
  SSC_DEVICE SSC_device,   /*@parm SSC hardware module identification number.*/
  IFX_UINT8 SSC_fifo_rx_lev_set /*@parm Specifies the programmable RX FIFO interrupt trigger level*/
);
#else
#define SSC_ctrl_fifo_set_rx_level(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif

#if SSC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL == 1
/*
  @func SSC driver run time transmit FIFO level write control function,
  this function may be used to set the filling level at which the transmit FIFO will generate
  an interrupt. For the purposes of this function the argument should be treated as an
  IFX_UINT8 variable. If there is no transmit FIFO then SSC_ERR_NOT_SUPPORTED_HW will be returned.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Set the interrupt trigger level of TX FIFO.
  @retval  SSC status
  @flag SSC_SUCCESS              | Successfully programmed receive FIFO interrupt trigger level.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Receive FIFO not supported by hardware or disabled by software.
*/
SSC_STATUS SSC_ctrl_fifo_set_tx_level
(
  SSC_DEVICE SSC_device,   /*@parm SSC hardware module identification number.*/
  IFX_UINT8 SSC_fifo_tx_lev_set /*@parm Specifies the programmable TX FIFO interrupt trigger level*/
);
#else
#define SSC_ctrl_fifo_set_tx_level(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_DISABLE == 1
/*
  @func SSC driver run time disable control function 
  used to disable the peripheral without terminating it. The result of calling this 
  function is that all the GPIO pins the SSC HAL has allocated will be set to inputs 
  and the peripheral disconnected. This allows the peripheral to be isolated from the
  outside world while communication parameters are changed or while GPIO configurations
  are switched. The behavior of this function may vary in some systems but it should 
  always stop the peripheral sending and receiving data.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Disable the device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS  | Successfully disabled the device.
*/
SSC_STATUS SSC_ctrl_disable(
  SSC_DEVICE SSC_device /*@parm SSC hardware module identification number.*/
);
#else
#define SSC_ctrl_disable(__SSC_PARM1) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_CTRL_ENABLE == 1
/*
  @func SSC driver run time enable control function 
  must be called after SSC_ctrl_disable before the peripheral will be able
  to communicate with other connected devices. The peripheral will be reconnected to the
  outside world and the GPIO lines set according to the configuration the peripheral has
  been set into. The behavior of this function may vary in some systems but it should
  always restore the peripheral to the state last configured successfully.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Enable the device by programming control register.
  @retval  SSC status
  @flag SSC_SUCCESS  | Successfully enabled the device.
*/
SSC_STATUS SSC_ctrl_enable(
  SSC_DEVICE SSC_device /*@parm SSC hardware module identification number.*/
);
#else
#define SSC_ctrl_enable(__SSC_PARM1) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_SLV_OSLCT_CFG == 1
/*
  @func SSC driver run time slave select output control function,
  this function is used to configure slave select output line. Configuration includes lead, 
  trail, inact delays and delayed/normal mode. This feature is fully hardware dependent.
  This function is used to swap the slave select lines and program delay cycles. 
  SSC controller configures slave select line as input or output in salve or master mode 
  respectively. These features are fully hardware dependent.
  It will free the pre-allocated port line and return to system HAL and reserve the new requested port line.

  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN) | - Release pre-allocated port number.
  @flag: (DESIGN) | - Reserve the new requested port number.
  @flag: (DESIGN) | - Program trail, lead and inact delays.
  @flag: (DESIGN) | - Program the delay or normal mode.
  @retval  SSC status
  @flag SSC_SUCCESS  | Successfully configured the device.
*/
SSC_STATUS SSC_ctrl_slv_oslct(
  SSC_DEVICE      SSC_device,   /*@parm SSC hardware module identification number.*/
  SSC_OSLAVE_OPT  SSC_slave_cfg /*@parm Slave select output line configuration parameters.*/
);
#else
#define SSC_ctrl_slv_oslct(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED_HW 
#endif

#if SSC_CFG_FUNC_READ == 1
/*
  @func SSC driver read function,
  the behavior of the SSC_read function depends upon the chosen transfer mode (SYS_TRNS_MCU_INT etc...) and
  whether or not a user call back function has been provided.
  If user call back function provided then request will be add it to the tail end of pending
  list and then return SSC_SUCCESS provided the number of pending read requests
  are less than SSC_CFG_REQUEST_QUEUE_WR. 
  If no user call back function was supplied then the SSC_read API function will not return
  until the requested transfer has completed.
  The data will be received in the user specified transfer mode.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - If no user call back function was supplied then the SSC_read API function will not return
          until the requested transfer has completed, either successfully or because of an error.
  @flag: (DESIGN)  | - If a user call back function is provided and interrupt mode is requested, then the
          SSC_read function will return immediately with SSC_SUCCESS. 
  @flag: (DESIGN)  | - Once the transfer has completed the user call back function will be invoked and the status 
          of the operation passed to it as an argument. 
  @flag: (DESIGN)  | - The number of frames successfully read will be returned in SSC_TRANSFER.SSC_return_num.
  @retval  SSC status
  @flag SSC_SUCCESS | Reading data from device is successful.
  @flag SSC_ERR_RES | The number of pending requests crosses the user configured SSC_CFG_REQUEST_QUEUE_RD level or
                      the input parameters do not match.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Requested transfer mode is not supported by hardware.                      
*/
SSC_STATUS SSC_read
(
  SSC_DEVICE SSC_device,    /*@parm SSC hardware module identification number.*/
  SSC_TRANSFER *SSC_transfer /*@parm Read request configuration parameter values.*/
);
#else
#define SSC_read(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif


#if SSC_CFG_FUNC_WRITE == 1
/*
  @func SSC driver write function,
  the behavior of the SSC_write function depends upon the chosen transfer mode (SYS_TRNS_MCU_INT etc...) and
  whether or not a user call back function has been provided.
  If no user call back function was supplied then the SSC_write API function will not return
  until the requested transfer has completed.
  If a user call back function is provided and interrupt mode is requested, then the
  SSC_write function will return immediately with SSC_SUCCESS provided the number of pending write requests
  are less than SSC_CFG_REQUEST_QUEUE_WR. 
  Once the transfer has completed the user call back function will be invoked and the 
  status of the operation passed to it as an argument. 
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - If no user call back function was supplied then the SSC_write API function will not return
          until the requested transfer has completed.
  @flag: (DESIGN)  | - If a user call back function is provided and interrupt mode is requested, then the
          SSC_write function will return immediately with SSC_SUCCESS. 
  @flag: (DESIGN)  | - Once the transfer has completed the user call back function will be invoked and the 
          status of the operation passed to it as an argument. 
  @flag: (DESIGN)  | - The number of frames successfully written will be returned in SSC_TRANSFER.SSC_return_num.
  @retval  SSC status
  @flag SSC_SUCCESS | Writing data to device is successful.
  @flag SSC_ERR_RES | The number of pending requests crosses the user configured SSC_CFG_REQUEST_QUEUE_WR level or
                      the input parameters do not match.
  @flag SSC_ERR_NOT_SUPPORTED_HW | Requested transfer mode is not supported by hardware.                      
*/
SSC_STATUS SSC_write
(
  SSC_DEVICE SSC_device,    /*@parm SSC hardware module identification number.*/
  SSC_TRANSFER *SSC_transfer /*@parm Write request configuration parameter values.*/
);
#else
#define SSC_write(__SSC_PARM1, __SSC_PARM2) SSC_ERR_NOT_SUPPORTED 
#endif

/*
  @func: (DESIGN)
  Program device configuration parameters include number of bits per data frame, phase, polarity and baud rate.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program number of bits per data frame, phase and polarity.
  @flag: (DESIGN)  | - Set the baud rate by calling SSC_set_baud API.
  @retval SSC status
  @flag SSC_ERR_NOT_SUPPORTED_HW | Requested configuration is not supported by hardware.
  @flag SSC_ERR_BAUD | Requested baud rate is not supported by hardware or not able to program with in user specified level.
  @flag SSC_SUCCESS | Successfully program all configuration parameters.                                     
*/
SSC_STATUS SSC_set_all
(
  SSC_DEVICE SSC_device,       /*@parm SSC hardware module identification number.*/
  SSC_COM_PARMS *SSC_ctrl_all  /*@parm New configuration parameters.*/
);


/*
  @func: (DESIGN)
  Set priorities for SSC interrupts.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program all SSC service request control registers with the corresponding priority
                       defined in SYS_CFG.H file.
  @retval None
*/
void SSC_set_intr_prior
(
  SSC_DEVICE SSC_device, /*@parm SSC hardware module identification number.*/
  IFX_UINT8  SSC_tir,    /*@parm Priority defined for transmit interrupt*/
  IFX_UINT8  SSC_rir,    /*@parm Priority defined for receive interrupt*/
  IFX_UINT8  SSC_eir     /*@parm Priority defined for error interrupt*/
);


/*
  @func: (DESIGN)
  Reserve GPIO pins for SSC module at system HAL.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program all SSC service request control registers with the corresponding priority
                       defined in SYS_CFG.H file.
  @retval SSC status
  @flag SSC_SUCCESS    | All Ports are reserved successfully.
  @flag SSC_ERR_RES_IO | Error in reserving ports, requested port pins is already reserved by other module.
*/
SSC_STATUS SSC_set_gpio_pins
(
  SSC_DEVICE    SSC_device, /*@parm SSC hardware module identification number.*/
  SSC_COM_PARMS *SSC_parm    /*@parm SSC configuration parameters*/
);


/*
  @func: (DESIGN)
  Set baud rate for SSC device.
  @head4: (DESIGN) Implementation Details |
  @flag: (DESIGN)  | - Program baud rate reload timer.
  @flag: (DESIGN)  | - Program fractional divider step value provided hardware supports.
  @retval SSC status
  @flag SSC_ERR_BAUD | Requested baud rate is not supported by hardware or not able to program with in user specified level.
  @flag SSC_SUCCESS | Successfully program baud rate.                                     
*/
SSC_STATUS SSC_set_baud
( 
  SSC_DEVICE SSC_device,
  IFX_UINT32 SSC_ctrl_baud
);

#endif /* __SSC_API_H */

