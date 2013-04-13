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
** @FILENAME@:       ssc_iil.c
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: SSC 
**
** =============================================================================
** Contents: Provides implementation for SSC low level driver.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 17/03/2004      Bhavjit Walha        Release after code review.
**
** @CHANGE_HISTORY@
** =============================================================================
*/	

/*
All required includes are done in SSC_API.H, this
allows the end user to easily find what is used by
the HAL.
*/
#include "compiler.h"
#include "common.h"
#include "ssc_cfg.h"
#include "ssc_api.h"
#include "ssc_idl.h"
#include "ssc_iil.h"
#include "sys_api.h"
#include "sys_cfg.h"

/* Globals for storing communiaction parameters */
IFX_UINT32 SSC_baud_rate[ SSC_HW_NUM ];         
IFX_UINT32 SSC_clk_freeq[SSC_HW_NUM];
IFX_UINT8  SSC_data_bits[ SSC_HW_NUM ];
IFX_UINT8  SSC_idle_clock[ SSC_HW_NUM ];
IFX_UINT8  SSC_clock_phase[ SSC_HW_NUM ];
IFX_UINT8  SSC_shift_dir[ SSC_HW_NUM ];
IFX_UINT8  SSC_slave_num[SSC_HW_NUM];

/*GPIO port configuration*/
#if SSC_PRODUCT == TC1130
IFX_SINT8 SSC_gpio_tab[SSC_HW_NUM][SSC_NUM_PORTS][SYS_PIN_CFG] = 
{
  {
    {SYS_GPIO_SSC0_MRST}, {SYS_GPIO_SSC0_MTSR}, {SYS_GPIO_SSC0_SCLK}, {SYS_GPIO_SSC0_SLSI},
    {SYS_GPIO_SSC0_SLSO00}, {SYS_GPIO_SSC0_SLSO01}, {SYS_GPIO_SSC0_SLSO02}, {SYS_GPIO_SSC0_SLSO03},
    {SYS_GPIO_SSC0_SLSO04}, {SYS_GPIO_SSC0_SLSO05}, {SYS_GPIO_SSC0_SLSO06}, {SYS_GPIO_SSC0_SLSO07}
  },
  {
    {SYS_GPIO_SSC1_MRST}, {SYS_GPIO_SSC1_MTSR},   {SYS_GPIO_SSC1_SCLK}, {SYS_GPIO_SSC1_SLSI},
    {SYS_GPIO_SSC1_SLSO10}, {SYS_GPIO_SSC1_SLSO11}, {SYS_GPIO_SSC1_SLSO12}, {SYS_GPIO_SSC1_SLSO13},
    {SYS_GPIO_SSC1_SLSO14}, {SYS_GPIO_SSC1_SLSO15}, {SYS_GPIO_SSC1_SLSO16}, {SYS_GPIO_SSC1_SLSO17}
  }
};
#endif

IFX_UINT32 SSC_data_mask[ SSC_HW_NUM ];  

/* Base Address Look Up Table Macro: */
/*
  This Table contains all the SSC peripherals
  For example, in the case of 3 SSC modules, the definition would be
  #define SSC_HW_ADDR_TABLE IFX_UINT32 SSC_addr_table [SSC_HW_NUM] = {SSC_HW_0_ADDR, SSC_HW_1_ADDR, SSC_HW_2_ADDR}
*/
#if (SSC_HW_NUM == 1)
#define SSC_HW_ADDR_TABLE IFX_UINT32 SSC_addr_table [SSC_HW_NUM] = {SSC_HW_0_ADDR}
#elif (SSC_HW_NUM == 2)
#define SSC_HW_ADDR_TABLE IFX_UINT32 SSC_addr_table [SSC_HW_NUM] = {SSC_HW_0_ADDR, SSC_HW_1_ADDR}
#endif


/* Pointers and counts for Reads and Writes */
IFX_UINT8  *SSC_write_ptr_8[ SSC_HW_NUM ];  /* Points to Application Write Buffer for data bits <= 8 */
IFX_UINT8  *SSC_read_ptr_8[ SSC_HW_NUM ]; /* Points to Application Read  Buffer for data bits <= 8 */
IFX_UINT16 *SSC_write_ptr_16[ SSC_HW_NUM ]; /* Points to Application Read  Buffer for data bits > 8 */
IFX_UINT16 *SSC_read_ptr_16[ SSC_HW_NUM ];  /* Points to Application Write Buffer for data bits > 8 */ 

/*
  The number of data bytes still written to IO ports of the current pending write request.
*/
IFX_VUINT32 SSC_npackets2write[ SSC_HW_NUM ]; 

/*
  The number of data bytes still to read from IO ports of the current pending read request.
*/
IFX_VUINT32 SSC_npackets2read[ SSC_HW_NUM ];   

SSC_MODE     SSC_mode[ SSC_HW_NUM ];       /* Operating mode of device*/
IFX_STUINT8  *SSC_writeto8[ SSC_HW_NUM ];  /* Points to Application Write Buffer for data bits < 9 */
IFX_STUINT8  *SSC_readfrom8[ SSC_HW_NUM ]; /* Points to Application Read  Buffer for data bits < 9 */
IFX_STUINT16 *SSC_readfrom16[ SSC_HW_NUM ];/* Points to Application Write Buffer for data bits = 9 */ 
IFX_STUINT16 *SSC_writeto16[ SSC_HW_NUM ]; /* Points to Application Read  Buffer for data bits = 9 */
SSC_STATUS   SSC_error_rd_msg[ SSC_HW_NUM ];  /* To store read request status */
SSC_STATUS   SSC_error_wr_msg[ SSC_HW_NUM ];/* To store write request status */


/* The Read and Write request queues */
#if SSC_CFG_REQUEST_QUEUE_RD > 0
/*
  List to maintain the pending read requests.
*/
SSC_TRANSFER *SSC_readq[ SSC_HW_NUM ][ SSC_CFG_REQUEST_QUEUE_RD ];

/*
  List to maintain the pending request status
*/
SSC_STATUS   SSC_read_status[ SSC_HW_NUM ][ SSC_CFG_REQUEST_QUEUE_RD ];

/*
  Head pointer to pending read request lsit. This is the current pending request 
  and seriviced to be first upon receiving data from IO ports (used in SSC_RIR_ISR).
*/
IFX_STUINT8   SSC_readq_head[ SSC_HW_NUM ];

/*
  Tail pointer to pending read request queue. The new read request will be added to the tail end of list
  (used in SSC_read API).
*/
IFX_STUINT8    SSC_readq_tail[ SSC_HW_NUM ];

/*
  The number of pending read requests.
*/
IFX_VUINT8    SSC_pending_reads[ SSC_HW_NUM ];
#endif

#if SSC_CFG_REQUEST_QUEUE_WR > 0
/*
  List to maintain the pending write requests.
*/
SSC_TRANSFER   *SSC_writeq[ SSC_HW_NUM ][ SSC_CFG_REQUEST_QUEUE_WR ];

/*
  Head pointer to pending write request lsit(used in SSC_TBIR_ISR and SSC_TIR_ISR).
*/
IFX_STUINT8    SSC_writeq_head[ SSC_HW_NUM ];

/*
  List to maintain the pending request status
*/
SSC_STATUS   SSC_write_status[ SSC_HW_NUM ][ SSC_CFG_REQUEST_QUEUE_WR ];

/*
  Tail pointer to pending write request lsit (used in SSC_write API).
*/
IFX_STUINT8    SSC_writeq_tail[ SSC_HW_NUM ];

/*
  The number of pending write requests.
*/
IFX_VUINT8  SSC_pending_writes[ SSC_HW_NUM ]; 
#endif


#if SSC_CFG_STAT_LOG == 1
IFX_STUINT8 SSC_phase_err[ SSC_HW_NUM ];
IFX_STUINT8 SSC_baud_err[ SSC_HW_NUM ];
IFX_STUINT32 SSC_receive_err[ SSC_HW_NUM ];
IFX_STUINT32 SSC_transmit_err[ SSC_HW_NUM ];
IFX_STUINT32 SSC_successful[ SSC_HW_NUM ];
#endif


/*
The following pre-proccessor directives check if the system HAL matches the 
implemententation dependent layer for the SSC HAL. If these do not match
then the compilation is stopped with an error to indicate this conflict to 
the user.
This check has been introduced because the IDL file names are identical, regardless
of the product they are written for, this could easily result in the wrong files 
being used.
*/
#if SYS_PRODUCT != SSC_PRODUCT
#error SSC HAL Error: Either SSC_IDL.H file is incorrect or else the wrong System HAL is being used.
#endif


/*
Check that the IDL layer is usable:
*/
#if (SSC_API_V_MAJ > 0)
#error SSC HAL Error: Incompatible components, please make sure you have the latest SSC HAL distribution.
#endif

/* 
Define initialised flags and flag management macros if 
initialisation checking is to be done.
If initialisation checking is not to be performed then
define the macros to do nothing.
*/
#if SSC_CFG_INIT_CHK == 1
  IFX_UINT8 SSC_initialised_flags [SSC_HW_NUM] = {SSC_HW_INIT(0x00)};
#endif  /* SSC_CFG_INIT_CHK == 1 */


#if !((SSC_HW_FIFO_TX > 0) && (SSC_CFG_TX_FIFO_LEVEL > 0))
IFX_VUINT8 SSC_canwrite = 1;
#endif

/*
This macro defines an address look up table for the SSC devices.
*/
SSC_HW_ADDR_TABLE;

/*
Reguest buffers and 
*/

/*
*******************************************************************************
* Function Name:     SSC_set_baud
*
* Description:
*  Sets the Baud Rate according to the user input. May return an
*  error if input is out of bounds or the tolerence setting is
*  too tight.
* 
*******************************************************************************
*/
SSC_STATUS SSC_set_baud
( 
  SSC_DEVICE SSC_device,
  IFX_UINT32 SSC_ctrl_baud
)
{
  IFX_UINT32 bg_val = 0;
  IFX_SFLOAT fcalc_baud = 0, fcalc_tol = 0, tol = 0;
  IFX_UINT32 baud_check = 0x10000;
  IFX_UINT32 fdv = 0, fdv_max = 1024, fdr_res = 0;

  /*User configured baud rate tolerance value*/
  tol = SSC_CFG_BAUD_TOL;

  if(SSC_ctrl_baud == 0)
  {
    return SSC_ERR;
  }

  #if SSC_HW_FDV_FTR == 0
  /*Check the required baud rate is with in the minimum and maximum levels*/
  if((SSC_ctrl_baud < (IFX_UINT32)SSC_GET_FREQ(SSC_clk_freeq[SSC_device],SSC_MIN_CLK)) || 
     (SSC_ctrl_baud > (IFX_UINT32)SSC_GET_FREQ(SSC_clk_freeq[SSC_device],SSC_MAX_CLK))
    )
  {
    return SSC_ERR_BAUD;
  }

  /*Calculate baud rate timer reload value (BG + 1) */
  fcalc_baud = (SSC_clk_freeq[SSC_device] /(2 * SSC_ctrl_baud));

  /*If BG value more than the maximum value, use the pre scalar divide by 3 value*/
  if( (fcalc_baud > 0) && (fcalc_baud < baud_check) )
  {
    bg_val = fcalc_baud; /*Baud rate timer reload value (BG + 1)*/
    fcalc_baud = (SSC_clk_freeq[SSC_device]) /(2 * (IFX_SFLOAT)bg_val);
    fcalc_tol = (fcalc_baud - (IFX_SFLOAT)SSC_ctrl_baud)/(IFX_SFLOAT)SSC_ctrl_baud;
    fcalc_tol = (fcalc_tol < 0) ? -fcalc_tol : fcalc_tol;

    /*Check deviation with user defined tolerance level(SSC_CFG_BAUD_TOL)*/
    if(fcalc_tol <= tol)
    {
      WRITEBITS( SSC_HW_BR( SSC_device ),(bg_val - 1), SSC_HW_BR_BR, SSC_HW_BR_BR_LOC );
      SSC_baud_rate[SSC_device] = SSC_ctrl_baud;
      return SSC_SUCCESS;
    }
  }
  #else
  /*Check the required baud rate is with in the minimum and maximum levels*/
  if((SSC_ctrl_baud < (IFX_UINT32)(SSC_GET_FREQ(SSC_clk_freeq[SSC_device],SSC_FDV_MIN_CLK))) || 
     (SSC_ctrl_baud > (IFX_UINT32)(SSC_GET_FREQ(SSC_clk_freeq[SSC_device],SSC_MAX_CLK)))
    )
  {
    return SSC_ERR_BAUD;
  }
  bg_val = 1;

  #if LESS_FDR == 0
  fdv = fdv_max - 1;
  for(; fdv >= 0; fdv--)
  #else
  for(; fdv < fdv_max; fdv++)
  #endif
  {
    fcalc_baud = (SSC_clk_freeq[SSC_device] /((2 * SSC_ctrl_baud) * (fdv_max - fdv)));

    if( (fcalc_baud > 0) && (fcalc_baud <= baud_check) )
    {
      bg_val = (IFX_UINT32)fcalc_baud; /*Baud rate timer reload value (BG + 1)*/
      fcalc_baud = (SSC_clk_freeq[SSC_device] /((2 * bg_val) * (fdv_max - fdv)));
      /*Calculate devitation from the requested baud rate*/
      fcalc_tol = (fcalc_baud - (IFX_SFLOAT)SSC_ctrl_baud)/(IFX_SFLOAT)SSC_ctrl_baud; 
      fcalc_tol = (fcalc_tol < 0) ? -fcalc_tol : fcalc_tol;

      /*Check deviation with user defined tolerance level(SSC_CFG_BAUD_TOL)*/
      if((fcalc_tol <= tol) )
      {
        WRITEBITS( SSC_HW_BR( SSC_device ), (bg_val - 1), SSC_HW_BR_BR, SSC_HW_BR_BR_LOC );

        fdr_res = ( (fdv << SSC_HW_FDV_STEP_LOC) + (SSC_HW_FDV_NORMAL_MODE << SSC_HW_FDV_MODE_LOC));
        UNLOCK_ENDINIT_PROTECT;
        SSC_HW_FDV( SSC_device ) = fdr_res;
        LOCK_ENDINIT_PROTECT;
        SSC_baud_rate[SSC_device] = (IFX_UINT32)fcalc_baud;
        return SSC_SUCCESS;
      }
    }
  }/*End of for*/
  #endif /*SSC_HW_FDV_FTR*/
  return SSC_ERR_BAUD;
}

/*
*******************************************************************************
* Function Name:     SSC_set_all
*
* Description:
*  Sets the Mode, Data, Parity and Stop bits. It also sets the
*  Baud Rate and may set the IrDA configuration if required.
*  It may also change the GPIO config if required.
* 
*******************************************************************************
*/
SSC_STATUS SSC_set_all
(
  SSC_DEVICE SSC_device,
  SSC_COM_PARMS *SSC_ctrl_all
)
{
  SSC_STATUS temp_stat;

  if(SSC_ctrl_all == NULL)
  {
    return SSC_ERR;
  }
     
  if ((SSC_ctrl_all->SSC_com_data > SSC_HW_BM_MAX) || (SSC_ctrl_all->SSC_com_data < SSC_HW_BM_MIN))
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  else
  {
    temp_stat = SSC_set_baud( SSC_device, SSC_ctrl_all->SSC_com_baud );
    if(temp_stat != SSC_SUCCESS)
    {
      return temp_stat;
    }
    SSC_data_bits[ SSC_device ] = SSC_ctrl_all->SSC_com_data;
    SSC_data_mask[ SSC_device ] = (0x0000FFFF >> (16 - SSC_ctrl_all->SSC_com_data));
    WRITEBITS( SSC_HW_CON( SSC_device ), (SSC_ctrl_all->SSC_com_data - 1), SSC_HW_CON_BM, SSC_HW_CON_BM_LOC );
  }

  SSC_mode[ SSC_device ] = SSC_ctrl_all->SSC_mode;
  if ( SSC_ctrl_all->SSC_mode == SSC_SLAVE )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_MS );
  }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_MS );
  }
  
  SSC_idle_clock[ SSC_device ] = SSC_ctrl_all->SSC_com_clock;
  if ( SSC_ctrl_all->SSC_com_clock == SSC_CLOCK_IDLE_LOW )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PO );
   }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PO );
  }
  
  SSC_clock_phase[ SSC_device ] = SSC_ctrl_all->SSC_com_phase;
  if ( SSC_ctrl_all->SSC_com_phase == SSC_LATCH_FALLING )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PH );
  }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PH );
  }
  
  SSC_shift_dir[ SSC_device ] = SSC_ctrl_all->SSC_com_shift;
  if ( SSC_ctrl_all->SSC_com_shift == SSC_LSB_FIRST )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_HB );
  }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_HB );
  }
  return SSC_SUCCESS;
}

/*
*******************************************************************************
* Function Name:     SSC_set_intr_prior
*
* Description:
*  Writes the respective priorities to the respective registers
*  
*******************************************************************************
*/
void SSC_set_intr_prior
(
  SSC_DEVICE SSC_device,
  IFX_UINT8  SSC_tir,
  IFX_UINT8  SSC_rir,
  IFX_UINT8  SSC_eir
)
{
  WRITEBITS( SSC_HW_RSRC ( SSC_device ), SSC_rir,  SSC_HW_SRC_SRPN, SSC_HW_SRC_SRPN_LOC );
  WRITEBITS( SSC_HW_TSRC ( SSC_device ), SSC_tir,  SSC_HW_SRC_SRPN, SSC_HW_SRC_SRPN_LOC );
  WRITEBITS( SSC_HW_ESRC ( SSC_device ), SSC_eir,  SSC_HW_SRC_SRPN, SSC_HW_SRC_SRPN_LOC );    
}


/*
*******************************************************************************
* Function Name:     SSC_set_gpio_pins
*
*******************************************************************************
*/
SSC_STATUS SSC_set_gpio_pins(SSC_DEVICE SSC_device, SSC_COM_PARMS *SSC_params)
{
  IFX_UINT8  port_conf = 0; 

  if(SSC_params == NULL)
  {
    return SSC_ERR;
  }

  #if SSC_HW_SLAVE_SEL_FTR == 1
  if((SSC_params->SSC_mode == SSC_MASTER) && (SSC_params->SSC_slave_num >= 0) && (SSC_params->SSC_slave_num < 9))
  {
    port_conf = 3 + SSC_params->SSC_slave_num;
  }
  else if((SSC_params->SSC_mode == SSC_SLAVE) && (SSC_params->SSC_slave_num >= 0) && (SSC_params->SSC_slave_num < 2))
  {
    port_conf = 2 + SSC_params->SSC_slave_num;
  }
  else
  {
    return SSC_ERR;
  }
  #endif /*SSC_HW_SLAVE_SEL_FTR*/

  switch(SSC_device)
  {
    case 0:
      if(SYS_gpio_alloc(SYS_GPIO_SSC0_MRST) != SYS_SUCCESS)
      {
        return SSC_ERR;
      }
      if(SYS_gpio_alloc(SYS_GPIO_SSC0_MTSR) != SYS_SUCCESS)
      {
        SYS_gpio_free(SYS_GPIO_SSC0_MRST);
        return SSC_ERR;
      }
      if(SYS_gpio_alloc(SYS_GPIO_SSC0_SCLK) != SYS_SUCCESS)
      {
        SYS_gpio_free(SYS_GPIO_SSC0_MRST);
        SYS_gpio_free(SYS_GPIO_SSC0_MTSR);
        return SSC_ERR;
      }
      break;
    case 1:
      if(SYS_gpio_alloc(SYS_GPIO_SSC1_MRST) != SYS_SUCCESS)
      {
        return SSC_ERR;
      }
      if(SYS_gpio_alloc(SYS_GPIO_SSC1_MTSR) != SYS_SUCCESS)
      {
        SYS_gpio_free(SYS_GPIO_SSC1_MRST);
        return SSC_ERR;
      }
      if(SYS_gpio_alloc(SYS_GPIO_SSC1_SCLK) != SYS_SUCCESS)
      {
        SYS_gpio_free(SYS_GPIO_SSC1_MRST);
        SYS_gpio_free(SYS_GPIO_SSC1_MTSR);
        return SSC_ERR;
      }
      #if SSC_HW_PISEL_FTR == 1
      if(SYS_gpio_get_port(SYS_GPIO_SSC1_MTSR) == SSC_HW_PISEL1_REG )
      {
        SET(SSC_HW_PISEL(SSC_device),SSC_HW_PISEL_MTSR_LOC);
      }
      if(SYS_gpio_get_port(SYS_GPIO_SSC1_MRST) == SSC_HW_PISEL1_REG )
      {
        SET(SSC_HW_PISEL(SSC_device),SSC_HW_PISEL_MRST_LOC);
      }
      if(SYS_gpio_get_port(SYS_GPIO_SSC1_SCLK) == SSC_HW_PISEL1_REG )
      {
        SET(SSC_HW_PISEL(SSC_device),SSC_HW_PISEL_SCLK_LOC);
      }
      #endif/*SSC_HW_PISEL_FTR*/
      break;   
  }

  #if SSC_HW_SLAVE_SEL_FTR == 1
  if(SSC_params->SSC_slave_num == 0)
  {
    SSC_slave_num[SSC_device] = SSC_params->SSC_slave_num;
    return SSC_SUCCESS;
  }

  if(SYS_gpio_alloc(SSC_gpio_tab[SSC_device][port_conf][0], SSC_gpio_tab[SSC_device][port_conf][1],
                   SSC_gpio_tab[SSC_device][port_conf][2], SSC_gpio_tab[SSC_device][port_conf][3],
                   SSC_gpio_tab[SSC_device][port_conf][4], SSC_gpio_tab[SSC_device][port_conf][5],
                   SSC_gpio_tab[SSC_device][port_conf][6], SSC_gpio_tab[SSC_device][port_conf][7]) != SYS_SUCCESS)
  {
    switch(SSC_device)
    {
      case 0:
        SYS_gpio_free(SYS_GPIO_SSC0_MRST);
        SYS_gpio_free(SYS_GPIO_SSC0_MTSR);
        SYS_gpio_free(SYS_GPIO_SSC0_SCLK);
        break;
      case 1:
        SYS_gpio_free(SYS_GPIO_SSC1_MRST);
        SYS_gpio_free(SYS_GPIO_SSC1_MTSR);
        SYS_gpio_free(SYS_GPIO_SSC1_SCLK);
        break;
    }
    return SSC_ERR;
  }

  SSC_slave_num[SSC_device] = SSC_params->SSC_slave_num;

  if(SSC_params->SSC_mode == SSC_MASTER)
  {
    WRITEBITS(SSC_HW_SSOC(SSC_device), 0x00000001, SSC_HW_SSOC_OEN_MASK, (SSC_HW_SSOC_OEN_LOC + (SSC_params->SSC_slave_num - 1)));
  }
  else
  {
    WRITEBITS(SSC_HW_PISEL(SSC_device), SSC_params->SSC_slave_num, SSC_HW_PISEL_SLSIS_MASK, SSC_HW_PISEL_SLSIS_LOC);
    WRITEBITS(SSC_HW_PISEL(SSC_device), SSC_CFG_SLV_IDLE_LVL, SSC_HW_PISEL_STIP_MASK, SSC_HW_PISEL_STIP_LOC);
  }
  #endif

  return SSC_SUCCESS;
}




/*
*******************************************************************************
* Function Name:     SSC_initialise_dev
*
* Description:
*  
*******************************************************************************
*/
SSC_STATUS SSC_initialise_dev
(
  SSC_DEVICE SSC_device,
  SSC_COM_PARMS *SSC_setup
)
{
  SSC_STATUS TempStatus;

  if(SSC_setup == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif
  
  #if (IFX_COMPILER_GNU == 1)
  if (SSC_HW_register_isr (SSC_device) == 0)
  {
    return SSC_ERR_RES;
  }
  #endif
  
  /*Check the user configured RMC value correctness*/
  #if SSC_HW_RMC_FTR == 1
  #if((SSC_CFG_RMC_VAL <= 0) || (SSC_CFG_RMC_VAL > 255))
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  #endif
  #endif

  /*Check for maximum and minimum RX and TX FIFO levels*/
  #if((SSC_CFG_RX_FIFO_LEVEL < 0) || (SSC_CFG_RX_FIFO_LEVEL > SSC_HW_FIFO_RX))
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  #endif

  #if((SSC_CFG_TX_FIFO_LEVEL < 0) || (SSC_CFG_TX_FIFO_LEVEL > SSC_HW_FIFO_TX))
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  #endif

  #if SSC_HW_DEL_SUP == 1
    #if((SSC_CFG_TRAIL_DELAY_CYCLS < 0) || (SSC_CFG_TRAIL_DELAY_CYCLS > SSC_HW_MAX_DLY))
    {
      return SSC_ERR_NOT_SUPPORTED_HW;
    }
    #endif

    #if((SSC_CFG_LEAD_DELAY_CYCLS < 0) || (SSC_CFG_LEAD_DELAY_CYCLS > SSC_HW_MAX_DLY))
    {
      return SSC_ERR_NOT_SUPPORTED_HW;
    }
    #endif

    #if((SSC_CFG_INACT_DELAY_CYCLS < 0) || (SSC_CFG_INACT_DELAY_CYCLS > SSC_HW_MAX_DLY))
    {
      return SSC_ERR_NOT_SUPPORTED_HW;
    }
    #endif
  #endif

  /* 
     Enable the module clock. The data written depends 
     on desired value of fSSC
  */
  UNLOCK_ENDINIT_PROTECT;
  #if (SSC_HW_RMC_FTR == 1)
  WRITEBITS( SSC_HW_CLC( SSC_device ), SSC_CFG_RMC_VAL, SSC_HW_CLC_RMC, SSC_HW_CLC_RMC_LOC );
  #else
  RESET(SSC_HW_CLC( SSC_device ),SSC_HW_DIS_CLK_LOC);
  #endif
  LOCK_ENDINIT_PROTECT;

  SSC_slave_num[SSC_device] = 0;
  SSC_mode[SSC_device]      = (SSC_MODE)0;

  #if SSC_CFG_STAT_LOG == 1
  SSC_phase_err[ SSC_device ]  = 0;
  SSC_baud_err[ SSC_device ] = 0;
  SSC_receive_err[ SSC_device ]    = 0;
  SSC_transmit_err[ SSC_device ] = 0;
  SSC_successful[ SSC_device ] = 0;
  #endif
         
  #if SSC_CFG_REQUEST_QUEUE_RD > 0
  SSC_readq_head[ SSC_device ] = 0;
  SSC_readq_tail[ SSC_device ] = SSC_CFG_REQUEST_QUEUE_RD - 1;
  SSC_pending_reads[ SSC_device ] = 0;
  #endif

  #if SSC_CFG_REQUEST_QUEUE_WR > 0
  SSC_writeq_head[ SSC_device ] = 0;
  SSC_writeq_tail[ SSC_device ] = SSC_CFG_REQUEST_QUEUE_WR - 1;
  SSC_pending_writes[ SSC_device ] = 0;
  #endif
  
  #if SSC_HW_RMC_FTR == 1
  SSC_clk_freeq[SSC_device] = (IFX_UINT32)(SYS_CFG_CLK_FREQ / SSC_CFG_RMC_VAL);
  #else
  SSC_clk_freeq[SSC_device] = (IFX_UINT32)(SYS_CFG_CLK_FREQ);
  #endif

  TempStatus = SSC_set_all( SSC_device, SSC_setup );
  if ( TempStatus != SSC_SUCCESS )
  {
    return TempStatus;
  }

  if(SSC_set_gpio_pins(SSC_device, SSC_setup) != SSC_SUCCESS)
  {
    return SSC_ERR_RES_IO;
  }  

  /* Function to initialize RXFCON */
  #if SSC_HW_FIFO_RX != 0 
    #if(SSC_CFG_RX_FIFO_LEVEL == 0)
    RESET( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXFEN );
    #else
    SET( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXFEN );
    RESET( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXFFLU );
    RESET( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXTMEN );
      #if SSC_CFG_RX_FIFO_LEVEL < SSC_HW_FIFO_RX
      WRITEBITS( SSC_HW_RXFCON( SSC_device ), SSC_CFG_RX_FIFO_LEVEL, SSC_HW_RXFCON_RXFITL, SSC_HW_RXFCON_RXFITL_LOC );
      #else
      WRITEBITS( SSC_HW_RXFCON( SSC_device ), SSC_HW_FIFO_RX, SSC_HW_RXFCON_RXFITL, SSC_HW_RXFCON_RXFITL_LOC );
      #endif
    #endif
  #endif
 
  /* Function to initialize TXFCON */
  #if SSC_HW_FIFO_TX != 0 
    #if SSC_CFG_TX_FIFO_LEVEL == 0
    RESET( SSC_HW_TXFCON( SSC_device ), SSC_HW_TXFCON_TXFEN );
    #else
    SET( SSC_HW_TXFCON( SSC_device ), SSC_HW_TXFCON_TXFEN );
    RESET( SSC_HW_TXFCON( SSC_device ), SSC_HW_TXFCON_TXFFLU );
    RESET( SSC_HW_TXFCON( SSC_device ), SSC_HW_TXFCON_TXTMEN );
      #if SSC_CFG_TX_FIFO_LEVEL < SSC_HW_FIFO_TX
      WRITEBITS( SSC_HW_TXFCON( SSC_device ), SSC_CFG_TX_FIFO_LEVEL, SSC_HW_TXFCON_TXFITL, SSC_HW_TXFCON_TXFITL_LOC );
      #else
      WRITEBITS( SSC_HW_TXFCON( SSC_device ), SSC_HW_FIFO_TX, SSC_HW_TXFCON_TXFITL, SSC_HW_TXFCON_TXFITL_LOC );
      #endif
    #endif
  #endif
  
  /* Code to initialize the rest of CON */
  #if SSC_CFG_TX_CHK == 1
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_TEN );
  #else
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_TEN );
  #endif

  #if SSC_CFG_RX_CHK == 1
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_REN );
  #else
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_REN );
  #endif

  #if SSC_CFG_PHASE_CHK == 1
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PEN );
  #else
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PEN );
  #endif

  #if SSC_CFG_BR_CHK == 1
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_BEN );
  #else
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_BEN );
  #endif


  /* Set the default interrupt priorities */
  switch (SSC_device)
  {
    case 0:
      SSC_set_intr_prior( SSC_device, SYS_SSC0_TIR, SYS_SSC0_RIR, SYS_SSC0_EIR );
      break;
    #if SSC_HW_NUM > 1
    case 1:
      SSC_set_intr_prior( SSC_device, SYS_SSC1_TIR, SYS_SSC1_RIR, SYS_SSC1_EIR );
      break;
    #endif
  }
  

  #if SSC_HW_SLAVE_SEL_FTR == 1
  if((SSC_setup->SSC_mode == SSC_MASTER) && (SSC_setup->SSC_slave_num > 0) && (SSC_setup->SSC_slave_num < 9))
  {
    WRITEBITS( SSC_HW_SSOC( SSC_device ), SSC_CFG_TX_IDLE_LEV, SSC_HW_SSOC_AOL_MASK, (SSC_HW_SSOC_AOL_LOC + (SSC_setup->SSC_slave_num - 1)));
    #if (SSC_HW_DEL_SUP == 1)
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_CFG_TRAIL_DELAY_CYCLS, SSC_HW_SSOTC_TRL_DELY_MASK, SSC_HW_SSOTC_TRL_DELY_LOC);
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_CFG_LEAD_DELAY_CYCLS, SSC_HW_SSOTC_LEAD_DELY_MASK, SSC_HW_SSOTC_LEAD_DELY_LOC);
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_CFG_INACT_DELAY_CYCLS, SSC_HW_SSOTC_INCT_DELY_MASK, SSC_HW_SSOTC_INCT_DELY_LOC);
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_CFG_DELAY, SSC_HW_SSOTC_SLSO7_MASK, SSC_HW_SSOTC_SLSO7_LOC);
    #endif
  }
  #endif

  /* Enable interrupts */
  if ((SSC_CFG_TX_CHK == 1) || (SSC_CFG_RX_CHK == 1) || (SSC_CFG_PHASE_CHK == 1) || (SSC_CFG_BR_CHK == 1))
  {
    SET( SSC_HW_ESRC( SSC_device ), SSC_HW_SRC_SRE );
  }
  
  SET( SSC_HW_RSRC( SSC_device ), SSC_HW_SRC_SRE );
  SET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SRE );
  

  ENABLE_GLOBAL_INTERRUPT();

  /*Set SSC device in loopback mode*/
  #if SSC_CFG_LPBACK == 1
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_LB );
  #endif

  /* To finally enable the module */
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );

  #if ( (SSC_CFG_DUMMY_DATA != -1) && (SSC_CFG_SLAVE_DUMMY_DAT == 1) )
  if(SSC_setup->SSC_mode == SSC_SLAVE)
  {
    WRITEBITS( SSC_HW_TB( SSC_device ), (SSC_CFG_DUMMY_DATA & SSC_data_mask[ SSC_device ]), SSC_data_mask[ SSC_device ], 0 );
  }
  #endif
   
# if SSC_CFG_INIT_CHK == 1
  SSC_initialised_flags [SSC_device] = 1;
# endif

  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/

  
#if SSC_CFG_FUNC_TERMINATE == 1
/*
*******************************************************************************
* Function Name:     SSC_terminate_dev
*
* Description:
*  Terminates the device by disabling the Module clock and removing
*  the interrupt module related interrupt priorities from the 
*  the common System Interrupt table.
*  
*******************************************************************************
*/
SSC_STATUS SSC_terminate_dev (SSC_DEVICE SSC_device)
{
  IFX_UINT8 port_conf = 0;

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

#if SSC_HW_PISEL_FTR == 1
  SSC_HW_PISEL(SSC_device) = 0;
#endif

#if SSC_HW_SLAVE_SEL_FTR == 1
  SSC_HW_SSOC(SSC_device)  = 0;
#endif

#if SSC_HW_DEL_SUP == 1
  SSC_HW_SSOTC(SSC_device)  = 0;
#endif

  /* Disable SSC module */
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );

  /* Disable the clock to the module */
  UNLOCK_ENDINIT_PROTECT;
  #if (SSC_HW_RMC_FTR == 1)
  WRITEBITS( SSC_HW_CLC( SSC_device ), SYS_RST, SSC_HW_CLC_RMC, SSC_HW_CLC_RMC_LOC );
  #else
  SET(SSC_HW_CLC( SSC_device ),SSC_HW_DIS_CLK_LOC);
  #endif
  LOCK_ENDINIT_PROTECT;
  
   switch(SSC_device)
   {
     case 0:
       SYS_gpio_free(SYS_GPIO_SSC0_MTSR);
       SYS_gpio_free(SYS_GPIO_SSC0_MRST);
       SYS_gpio_free(SYS_GPIO_SSC0_SCLK);
       break;
     #if SSC_HW_NUM > 1
     case 1:
       SYS_gpio_free(SYS_GPIO_SSC1_MTSR);
       SYS_gpio_free(SYS_GPIO_SSC1_MRST);
       SYS_gpio_free(SYS_GPIO_SSC1_SCLK);
       break;
     #endif
   }

  #if SSC_HW_SLAVE_SEL_FTR == 1
  if(SSC_mode[SSC_device] == SSC_MASTER)
  {
    port_conf = 3;
  } 
  else
  {
    port_conf = 2;
  }
  port_conf += SSC_slave_num[SSC_device];

  SYS_gpio_free(SSC_gpio_tab[SSC_device][port_conf][0], SSC_gpio_tab[SSC_device][port_conf][1],
                   SSC_gpio_tab[SSC_device][port_conf][2], SSC_gpio_tab[SSC_device][port_conf][3],
                   SSC_gpio_tab[SSC_device][port_conf][4], SSC_gpio_tab[SSC_device][port_conf][5],
                   SSC_gpio_tab[SSC_device][port_conf][6], SSC_gpio_tab[SSC_device][port_conf][7]);
  #endif 

# if SSC_CFG_INIT_CHK == 1
  SSC_initialised_flags [SSC_device] = 0;
# endif

  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_ABORT == 1
/*
*******************************************************************************
* Function Name:     SSC_abort
*
* Description:
*  Aborts the ongoing transmission by flushing the input and ouput
*  FIFOs. It also flushes the Circular Buffer( if enabled ).
*
*******************************************************************************
*/
SSC_STATUS SSC_abort (SSC_DEVICE SSC_device)
{
  IFX_SINT8 pend_req = 0;

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  /* Flush receive FIFO */
  #if ( ( SSC_CFG_RX_FIFO_LEVEL > 0) && (SSC_HW_FIFO_RX > 0) )
  SET( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXFFLU );
  #endif

  /* Flush transmit FIFO */
  #if ( ( SSC_CFG_TX_FIFO_LEVEL > 0) && (SSC_HW_FIFO_RX > 0) )
  SET( SSC_HW_TXFCON( SSC_device ), SSC_HW_TXFCON_TXFFLU );
  #endif

  /*Reset baud rate run time control bit*/
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );

  /* Flush the queued read pending requests and return an error */
  #if SSC_CFG_REQUEST_QUEUE_RD > 0
  if ( SSC_pending_reads[ SSC_device ] > 0 )
  {
    SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ]->SSC_return_num = SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ]->SSC_buffer_size - SSC_npackets2read[ SSC_device ];
    SSC_npackets2read[ SSC_device ] = 0;
    SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ]->SSC_trans_ucb( SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ], SSC_ERR );      
    #if SSC_CFG_REQUEST_QUEUE_RD > 1
    for ( pend_req = SSC_pending_reads[ SSC_device ] - 1; pend_req > 0; pend_req-- )
    {
      SSC_readq_head[ SSC_device ]++;
      if ( SSC_readq_head[ SSC_device ] == SSC_CFG_REQUEST_QUEUE_RD )
      {
        SSC_readq_head[ SSC_device ] = 0;
      }
      SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ]->SSC_return_num = 0;
      SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ]->SSC_trans_ucb( SSC_readq[ SSC_device][ (SSC_readq_head[ SSC_device ]) ], SSC_ERR );      
    }
    #endif
    SSC_pending_reads[ SSC_device ] = 0;
    SSC_readq_head[ SSC_device ] = 0;
    SSC_readq_tail[ SSC_device ] = SSC_CFG_REQUEST_QUEUE_RD - 1;
  }
  #else
  SSC_error_rd_msg[ SSC_device ] = SSC_ERR; /*Update status*/
  SSC_npackets2read[ SSC_device ] = 0; /*If pending read requests not supported then make pending reads as zero.*/
  #endif
  
  /*Flush queud write pending requests and return an error*/
  #if SSC_CFG_REQUEST_QUEUE_WR > 0
  if ( SSC_pending_writes[ SSC_device ] > 0 )
  {
    SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ]->SSC_return_num = SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ]->SSC_buffer_size - SSC_npackets2write[ SSC_device ];
    SSC_npackets2write[ SSC_device ] = 0;
    SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ]->SSC_trans_ucb( SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ], SSC_ERR );      
    #if SSC_CFG_REQUEST_QUEUE_WR > 1
    for ( pend_req = SSC_pending_writes[ SSC_device ] - 1; pend_req > 0; pend_req-- )
    {
      SSC_writeq_head[ SSC_device ]++;
      if ( SSC_writeq_head[ SSC_device ] == SSC_CFG_REQUEST_QUEUE_WR )
      {
        SSC_writeq_head[ SSC_device ] = 0;
      }
      SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ]->SSC_return_num = 0;
      if(SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ]->SSC_trans_ucb != NULL)
      {
        SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ]->SSC_trans_ucb( SSC_writeq[ SSC_device][ (SSC_writeq_head[ SSC_device ]) ], SSC_ERR );      
      }
    }
    #endif
    SSC_pending_writes[ SSC_device ] = 0; 
    SSC_writeq_head[ SSC_device ] = 0;
    SSC_writeq_tail[ SSC_device ] = SSC_CFG_REQUEST_QUEUE_WR - 1;
  }
  #else
  SSC_error_wr_msg[ SSC_device ] = SSC_ERR;   /*Update status*/
  SSC_npackets2write[ SSC_device ] = 0; /*If pending write requests not supported then make pending writes as zero.*/
  #endif
  
  /*Set baud rate run time control bit*/
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );

  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_STATUS == 1
/*
*******************************************************************************
* Function Name:     SSC_status_dev
*
* Description:
* Reports the status of the device and stores the parameters into the
* structure pointed to by SSC_stat_inf. If logging is enabled, this
* function also reports the status of the packets received since
* the last time this function was called. 
* 
*******************************************************************************
*/
SSC_STATUS SSC_status_dev
(
  SSC_DEVICE SSC_device,
  SSC_STAT_INF *SSC_stat_inf
)
{

  if(SSC_stat_inf == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  SSC_stat_inf->SSC_current_progress        = 
                  READBITS( SSC_HW_CON( SSC_device ), SSC_HW_CON_BM, SSC_HW_CON_BM_LOC );
  SSC_stat_inf->SSC_com_parms.SSC_com_baud  = SSC_baud_rate[ SSC_device ];
  SSC_stat_inf->SSC_com_parms.SSC_com_clock = (SSC_CLOCK_IDLE)SSC_idle_clock[ SSC_device ];
  SSC_stat_inf->SSC_com_parms.SSC_com_data  = (SSC_DATA)SSC_data_bits[ SSC_device ];
  SSC_stat_inf->SSC_com_parms.SSC_com_phase = (SSC_PHASE)SSC_clock_phase[ SSC_device ];
  SSC_stat_inf->SSC_com_parms.SSC_slave_num = SSC_slave_num[ SSC_device ];
  SSC_stat_inf->SSC_com_parms.SSC_com_shift = (SSC_SHIFT_DIR)SSC_shift_dir[ SSC_device ];
  SSC_stat_inf->SSC_com_parms.SSC_mode      = (SSC_MODE)SSC_mode[ SSC_device ];

  #if SSC_CFG_STAT_LOG == 1
  SSC_stat_inf->SSC_phase_err       = SSC_phase_err[ SSC_device ];
  SSC_stat_inf->SSC_baud_err        = SSC_baud_err[ SSC_device ];
  SSC_stat_inf->SSC_receive_err     = SSC_receive_err[ SSC_device ];
  SSC_stat_inf->SSC_transmit_err    = SSC_transmit_err[ SSC_device ];
  SSC_stat_inf->SSC_successful      = (SSC_successful[ SSC_device ] - (SSC_phase_err[ SSC_device ] + 
                                        SSC_baud_err[ SSC_device ] + SSC_receive_err[ SSC_device ] + 
                                        SSC_transmit_err[ SSC_device ]) ); 
  SSC_phase_err[ SSC_device ]       = 0;
  SSC_baud_err[ SSC_device ]        = 0;
  SSC_receive_err[ SSC_device ]     = 0;
  SSC_transmit_err[ SSC_device ]    = 0;
  SSC_successful[ SSC_device ]      = 0;
  #endif

  #if ((SSC_HW_FIFO_RX > 0) && (SSC_CFG_RX_FIFO_LEVEL > 0))
  SSC_stat_inf->SSC_rx_fifo_lev = READBITS( SSC_HW_FSTAT( SSC_device ), SSC_HW_FSTAT_RXFFL, SSC_HW_FSTAT_RXFFL_LOC ); 
  #else
  SSC_stat_inf->SSC_rx_fifo_lev = 0;
  #endif

  #if ((SSC_HW_FIFO_TX > 0) && (SSC_CFG_TX_FIFO_LEVEL > 0))
  SSC_stat_inf->SSC_tx_fifo_lev = READBITS( SSC_HW_FSTAT( SSC_device ), SSC_HW_FSTAT_TXFFL, SSC_HW_FSTAT_TXFFL_LOC ); 
  #else
  SSC_stat_inf->SSC_tx_fifo_lev = 0;
  #endif
  
  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CONTROL == 1
/*
*******************************************************************************
* Function Name:     SSC_control_dev
*
* Description:
*  Gives a common entry point for controlling all the
*  parameters of the SSC module. This function calls
*  other HAL API functions.
*
*******************************************************************************
*/
SSC_STATUS SSC_control_dev
(
  SSC_DEVICE SSC_device,
  SSC_CTRL_CODE SSC_ctrl_code,
  void *SSC_ctrl_arg
)
{
  if(SSC_ctrl_arg == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif
  
  switch (SSC_ctrl_code)
  {
    #if SSC_CFG_FUNC_CTRL_BAUD == 1
    case SSC_CTRL_TRNS_BAUD:
      return SSC_ctrl_trns_baud( SSC_device, *(IFX_UINT32 *)SSC_ctrl_arg );
    #endif

    #if SSC_CFG_FUNC_CTRL_DATA == 1
    case SSC_CTRL_TRNS_DATA:
      return SSC_ctrl_trns_data( SSC_device, *(SSC_DATA *)SSC_ctrl_arg );
    #endif

    #if SSC_CFG_FUNC_CTRL_ALL == 1    
    case SSC_CTRL_TRNS_ALL:
      return SSC_ctrl_trns_all( SSC_device, (SSC_COM_PARMS *)SSC_ctrl_arg );
    #endif
    
    #if SSC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH == 1
    case SSC_CTRL_FIFO_GET_RX_DEPTH:
      return SSC_ctrl_fifo_get_rx_depth( SSC_device, (IFX_UINT8 *)SSC_ctrl_arg);
    #endif

    #if SSC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH == 1
    case SSC_CTRL_FIFO_GET_TX_DEPTH:
      return SSC_ctrl_fifo_get_tx_depth( SSC_device, (IFX_UINT8 *)SSC_ctrl_arg);
    #endif

    #if SSC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL == 1  
    case SSC_CTRL_FIFO_GET_RX_LEVEL:
      return SSC_ctrl_fifo_get_rx_level( SSC_device, (IFX_UINT8 *)SSC_ctrl_arg);
    #endif

    #if SSC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL == 1    
    case SSC_CTRL_FIFO_GET_TX_LEVEL:
      return SSC_ctrl_fifo_get_tx_level( SSC_device, (IFX_UINT8 *)SSC_ctrl_arg);
    #endif
  
    #if SSC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL == 1
    case SSC_CTRL_FIFO_SET_RX_LEVEL:
      return SSC_ctrl_fifo_set_rx_level( SSC_device, *(IFX_UINT8 *)SSC_ctrl_arg );   
    #endif
  
    #if  SSC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL == 1
    case SSC_CTRL_FIFO_SET_TX_LEVEL:
      return SSC_ctrl_fifo_set_tx_level( SSC_device, *(IFX_UINT8 *)SSC_ctrl_arg );
    #endif

    #if SSC_CFG_FUNC_CTRL_DISABLE == 1 
    case SSC_CTRL_DISABLE:
      return SSC_ctrl_disable( SSC_device );
    #endif
   
    #if SSC_CFG_FUNC_CTRL_ENABLE == 1  
    case SSC_CTRL_ENABLE:
      return SSC_ctrl_enable( SSC_device );
    #endif

    #if SSC_CFG_FUNC_CTRL_CLOCK == 1
    case SSC_CTRL_TRNS_CLOCK:
      return SSC_ctrl_trns_clock(SSC_device, *(SSC_CLOCK_IDLE *)SSC_ctrl_arg);
    #endif

    #if SSC_CFG_FUNC_CTRL_PHASE == 1
    case SSC_CTRL_TRNS_PHASE:
      return SSC_ctrl_trns_phase(SSC_device, *(SSC_PHASE *)SSC_ctrl_arg);  
    #endif

    #if SSC_CFG_FUNC_CTRL_SHIFT == 1
    case SSC_CTRL_TRNS_SHIFT:
      return SSC_ctrl_trns_shift(SSC_device, *(SSC_SHIFT_DIR *)SSC_ctrl_arg);
    #endif

    #if SSC_CFG_FUNC_SLV_OSLCT_CFG == 1
    #if SSC_HW_SLAVE_SEL_FTR == 1
    case SSC_CTRL_SLV_OSLCT:
      return SSC_ctrl_slv_oslct(SSC_device, ( *(SSC_OSLAVE_OPT *)SSC_ctrl_arg));
	#else
	  return SSC_ERR_NOT_SUPPORTED_HW;
	#endif /*SSC_HW_SLAVE_SEL_FTR*/
    #endif

    default:
      return SSC_ERR;
  }
  
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_BAUD == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_trns_baud
*
* Description:
*  Sets the Baud Rate according to the user input. May return an
*  error if input is out of bounds or the tolerence setting is
*  too tight. While the baud rate is being updated, the module
*  is temporarily disabled. This may cause errors if simultaneous
*  reception of packets is going on.
*
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_trns_baud
(
  SSC_DEVICE SSC_device,
  IFX_UINT32 SSC_ctrl_baud
)
{
  SSC_STATUS TempStatus;

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  /* Need to disable the module first */
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  TempStatus = SSC_set_baud( SSC_device, SSC_ctrl_baud );   
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );

  return TempStatus;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_DATA == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_trns_data
*
* Description:
*  Changes the no. of data bits to the desired value (2 to 16)
*  For data consistency, the HAL circular buffers need to be 
*  flushed.
*
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_trns_data
(
  SSC_DEVICE SSC_device,
  SSC_DATA SSC_ctrl_data
)
{
# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  if ((SSC_ctrl_data > SSC_HW_BM_MAX) || (SSC_ctrl_data < SSC_HW_BM_MIN))
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  else
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
    WRITEBITS( SSC_HW_CON( SSC_device ), (SSC_ctrl_data - 1), SSC_HW_CON_BM, SSC_HW_CON_BM_LOC );
    SSC_data_bits[ SSC_device ] = SSC_ctrl_data;
    SSC_data_mask[ SSC_device ] = (0x0000FFFF >> (16 - SSC_ctrl_data));
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  }  
  return SSC_SUCCESS;
}

/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_CLOCK == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_trns_clock
*
* Description:
*
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_trns_clock
(
  SSC_DEVICE SSC_device,
  SSC_CLOCK_IDLE SSC_ctrl_clock
)
{
# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  SSC_idle_clock[ SSC_device ] = SSC_ctrl_clock;
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  if ( SSC_ctrl_clock == SSC_CLOCK_IDLE_LOW )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PO );
   }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PO );
  }
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  return SSC_SUCCESS;
}

/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_PHASE == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_trns_phase
*
* Description:
*
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_trns_phase
(
  SSC_DEVICE SSC_device,
  SSC_PHASE SSC_ctrl_phase
)
{
# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  if ( SSC_ctrl_phase == SSC_LATCH_FALLING )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PH );
   }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_PH );
  }
  SSC_clock_phase[ SSC_device ] = SSC_ctrl_phase;
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_SHIFT == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_trns_shift
*
* Description:
*
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_trns_shift
(
  SSC_DEVICE SSC_device,
  SSC_SHIFT_DIR SSC_ctrl_shift
)
{
# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  if ( SSC_ctrl_shift == SSC_LSB_FIRST )
  {
    RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_HB );
  }
  else 
  {
    SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_HB );
  }
  SSC_shift_dir[ SSC_device ] = SSC_ctrl_shift;
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_ALL == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_trns_all
*
* Description:
*  Sets the Mode, Data, Parity and Stop bits. It also sets the
*  Baud Rate and may set the IrDA configuration if required.
*  It may also change the GPIO config if required.
*
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_trns_all
(
  SSC_DEVICE SSC_device,
  SSC_COM_PARMS *SSC_ctrl_all
)
{
  SSC_STATUS temp_stat;

  if(SSC_ctrl_all == NULL)
  {
    return SSC_ERR;
  }


# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  /* Need to disable the module first */
  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  temp_stat = SSC_set_all( SSC_device, SSC_ctrl_all );
  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  return temp_stat;
  
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_fifo_get_rx_level
*
* Description:
*  Returns the RxFIFO level at/above which a Receive Buffer Full
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_fifo_get_rx_level ( SSC_DEVICE SSC_device, IFX_UINT8 *rx_fifo_lvl )
{ 
  if(rx_fifo_lvl == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  #if ((SSC_HW_FIFO_RX > 0) && (SSC_CFG_RX_FIFO_LEVEL > 0))
  *rx_fifo_lvl = READBITS( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXFITL, SSC_HW_RXFCON_RXFITL_LOC );
  return SSC_SUCCESS;
  #else
  *rx_fifo_lvl = 0;
  return SSC_ERR_NOT_SUPPORTED_HW;
  #endif
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_fifo_get_tx_level
*
* Description:
*  Returns the TxFIFO level at/below which a Transmit Buffer Empty
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_fifo_get_tx_level( SSC_DEVICE SSC_device, IFX_UINT8 *tx_fifo_lvl )
{ 

  if(tx_fifo_lvl == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  #if((SSC_HW_FIFO_TX > 0) && (SSC_CFG_TX_FIFO_LEVEL > 0))
  *tx_fifo_lvl = READBITS( SSC_HW_TXFCON( SSC_device ), SSC_HW_TXFCON_TXFITL, SSC_HW_TXFCON_TXFITL_LOC );
  return SSC_SUCCESS;
  #else
  *tx_fifo_lvl = 0;
  return SSC_ERR_NOT_SUPPORTED_HW;
  #endif
}
/*----------------------------------------------------------------------------*/
#endif

#if SSC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_fifo_get_rx_depth
*
* Description:
*  Returns the RxFIFO depth 
* 
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_fifo_get_rx_depth( SSC_DEVICE SSC_device, IFX_UINT8 *rx_fifo_depth )
{
  SSC_device = 0;

  if(rx_fifo_depth == NULL)
  {
    return SSC_ERR;
  }

  #if(SSC_HW_FIFO_RX <= 0)
  {
    *rx_fifo_depth = 0;
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  #else
  *rx_fifo_depth = SSC_HW_FIFO_RX;
  return SSC_SUCCESS;
  #endif
}  
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_fifo_get_tx_depth
*
* Description:
*  Returns the TxFIFO depth 
* 
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_fifo_get_tx_depth( SSC_DEVICE SSC_device, IFX_UINT8 *tx_fifo_depth )
{
  SSC_device = 0;

  if(tx_fifo_depth == NULL)
  {
    return SSC_ERR;
  }

  #if(SSC_HW_FIFO_TX <= 0)
  {
    *tx_fifo_depth = 0;
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  #else
  *tx_fifo_depth = SSC_HW_FIFO_TX;
  return SSC_SUCCESS;
  #endif
}  
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_fifo_set_tx_level
*
* Description:
*  Sets the TxFIFO level at/below which a Transmit Buffer Empty
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_fifo_set_tx_level
(
  SSC_DEVICE SSC_device,
  IFX_UINT8 SSC_fifo_tx_lev_set
)
{     
  #if SSC_HW_FIFO_TX == 0
  return SSC_ERR_NOT_SUPPORTED_HW;
  #else
  if ( (SSC_fifo_tx_lev_set > SSC_HW_FIFO_TX) || (SSC_fifo_tx_lev_set == 0) )
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  else
  {
    WRITEBITS( SSC_HW_TXFCON( SSC_device ), SSC_fifo_tx_lev_set, SSC_HW_TXFCON_TXFITL, SSC_HW_TXFCON_TXFITL_LOC );
    return SSC_SUCCESS;
  }
  #endif
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_fifo_set_rx_level
*
* Description:
*  Sets the RxFIFO level at/above which a Receive Buffer Full
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_fifo_set_rx_level
(
  SSC_DEVICE SSC_device,
  IFX_UINT8 SSC_fifo_rx_lev_set
)
{     
  #if SSC_HW_FIFO_RX == 0
  return SSC_ERR_NOT_SUPPORTED_HW;
  #else
  if ( (SSC_fifo_rx_lev_set > SSC_HW_FIFO_RX) || (SSC_fifo_rx_lev_set == 0) )
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  else
  {
    WRITEBITS( SSC_HW_RXFCON( SSC_device ), SSC_fifo_rx_lev_set, SSC_HW_RXFCON_RXFITL, SSC_HW_RXFCON_RXFITL_LOC );
    return SSC_SUCCESS;
  }
  #endif
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_READ == 1
/*
*******************************************************************************
* Function Name:     SSC_read
*
* Description:
* Reports the status of the device and stores the parameters into the
* structure pointed to by SSC_stat_inf. If logging is enabled, this
* function also reports the status of the packets received since
* the last time this function was called. 
* 
*******************************************************************************
*/
SSC_STATUS SSC_read
(
  SSC_DEVICE SSC_device,
  SSC_TRANSFER *SSC_transfer
)
{
  if(SSC_transfer == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  /*Hardware supports only interrupt mode data transmission mode*/  
  if( (SSC_transfer->SSC_transfer_mode == SYS_TRNS_MCU) || (SSC_transfer->SSC_transfer_mode == SYS_TRNS_PCP) || 
       (SSC_transfer->SSC_transfer_mode == SYS_TRNS_DMA) )
  {
     return SSC_ERR_NOT_SUPPORTED_HW;
  }

  /*If read has call back function and not the polling mode*/
  if ( ( SSC_transfer->SSC_trans_ucb != NULL ) && ( SSC_transfer->SSC_transfer_mode == SYS_TRNS_MCU_INT ))
  {
    #if SSC_CFG_REQUEST_QUEUE_RD > 0
    /*Disable local interrupt*/
    RESET( SSC_HW_RSRC( SSC_device ), SSC_HW_SRC_SRE );
    if ( SSC_pending_reads[ SSC_device ] >=  SSC_CFG_REQUEST_QUEUE_RD )  /*Check for maximum pending requests*/
    { 
      /*Enable local interrupt*/
      SET( SSC_HW_RSRC( SSC_device ), SSC_HW_SRC_SRE );
      return SSC_ERR_RES;
    }
    else 
    {
      /*Update global variables if there is no other pending read requests*/
      if (SSC_pending_reads[ SSC_device ] == 0 )
      {
        SSC_npackets2read[ SSC_device ] = SSC_transfer->SSC_buffer_size;
        SSC_readfrom8[ SSC_device ] = (IFX_UINT8 *)SSC_transfer->SSC_buffer;
        SSC_readfrom16[ SSC_device ] = (IFX_UINT16 *)SSC_transfer->SSC_buffer;
      }  
      /*Increment the number of pending requests*/
      SSC_pending_reads[ SSC_device ] = SSC_pending_reads[ SSC_device ] + 1; 
      /*Enable local interrupt*/
      SET( SSC_HW_RSRC( SSC_device ), SSC_HW_SRC_SRE );

      /*
        Tail(SSC_readq_tail) pointer is used in SSC_read API and Head(SSC_readq_head) 
        is used in SSC_RIR_ISR. These two pointers will make the read queue as re-entrant.
      */
      SSC_readq_tail[ SSC_device ] = SSC_readq_tail[ SSC_device ] + 1;
      if ( SSC_readq_tail[ SSC_device ] == SSC_CFG_REQUEST_QUEUE_RD )
      {
        SSC_readq_tail[ SSC_device ] = 0;
      }
      /*Add the pending read request to the queue. */
      SSC_readq[ SSC_device ][ (SSC_readq_tail[ SSC_device ]) ] = SSC_transfer; 
      /*Update the status of just added pending request, by default it is SSC_SUCCESS*/
      SSC_read_status[ SSC_device ][ (SSC_readq_tail[ SSC_device ]) ] = SSC_SUCCESS;

      return SSC_SUCCESS;
    }
    #else
    return SSC_ERR_RES;  
    #endif /* #if SSC_CFG_REQUEST_QUEUE_RD > 0 */   
  } /* if a UCB is requested */
    
  /* If queues are enabled, wait for pending transfers */
  #if SSC_CFG_REQUEST_QUEUE_RD > 0
  while( SSC_pending_reads[ SSC_device ] != 0 )
  { 
  }
  #endif
  
  /*If no user call back function the control will come here. Update the global variables*/  
  SSC_readfrom8[ SSC_device ] = (IFX_UINT8 *)SSC_transfer->SSC_buffer;
  SSC_readfrom16[ SSC_device ] = (IFX_UINT16 *)SSC_transfer->SSC_buffer;
  SSC_npackets2read[ SSC_device ] = SSC_transfer->SSC_buffer_size;
  
  /* Ignore previous status, have been handled already*/
  SSC_error_rd_msg[ SSC_device ] = SSC_SUCCESS;

  switch (SSC_transfer->SSC_transfer_mode)
  {
    case SYS_TRNS_MCU_INT:
    {
      /* Loop till the Reception is completes */ 
      while ( SSC_npackets2read[ SSC_device ] > 0 )
      {
      }
      break;
    } /* End of - case SYS_TRNS_MCU_INT */

    case SYS_TRNS_PCP:  /*PCP is not supported*/
      return SSC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_DMA: /*DMA transmission is not supported*/
      return SSC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_MCU:   /*Polling mode is not supported*/
      return SSC_ERR_NOT_SUPPORTED_HW;

    default: 
      return SSC_ERR_NOT_SUPPORTED_HW;

  } /* End of switch */

  /*Update the status and number of data bytes are read*/
  SSC_transfer->SSC_return_num = SSC_transfer->SSC_buffer_size;
  return SSC_error_rd_msg[ SSC_device ];
}/*----------------------------------------------------------------------------*/
#endif



#if SSC_CFG_FUNC_WRITE == 1
/*
*******************************************************************************
* Function Name:     SSC_write
*
* Description:
*  Writes the data in the Application buffer in a controlled manner
*  to TBUF, so that it may be transmitted.
*
*******************************************************************************
*/
SSC_STATUS SSC_write
(
  SSC_DEVICE SSC_device,
  SSC_TRANSFER *SSC_transfer
)
{
  IFX_UINT32 nLoop;

  if(SSC_transfer == NULL)
  {
    return SSC_ERR;
  }

# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  /*Hardware supports only interrupt mode data transmission mode*/  
  if( (SSC_transfer->SSC_transfer_mode == SYS_TRNS_MCU) || (SSC_transfer->SSC_transfer_mode == SYS_TRNS_PCP) || 
       (SSC_transfer->SSC_transfer_mode == SYS_TRNS_DMA) )
  {
     return SSC_ERR_NOT_SUPPORTED_HW;
  }

  /*Check for user call back function (non block request)*/
  if ( ( SSC_transfer->SSC_trans_ucb != NULL ) && (SSC_transfer->SSC_transfer_mode == SYS_TRNS_MCU_INT) )
  {
    #if SSC_CFG_REQUEST_QUEUE_WR > 0
    /*Disable local interrupt*/ 
    RESET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SRE );
    if ( SSC_pending_writes[ SSC_device ] ==  SSC_CFG_REQUEST_QUEUE_WR )
    { 
      /*Enable local interrupt*/ 
      SET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SRE );
      return SSC_ERR_RES;
    }
    else 
    {
      SSC_writeq_tail[ SSC_device ] = SSC_writeq_tail[ SSC_device ] + 1;
      if ( SSC_writeq_tail[ SSC_device ] == SSC_CFG_REQUEST_QUEUE_WR )
      {
        SSC_writeq_tail[ SSC_device ] = 0;
      }
      nLoop = SSC_writeq_tail[ SSC_device ];

      SSC_writeq[ SSC_device ][ nLoop ] = SSC_transfer;
      SSC_write_status[ SSC_device ][ nLoop ] = SSC_SUCCESS;

      if ( SSC_pending_writes[ SSC_device ] == 0 )
      {
        SSC_pending_writes[ SSC_device ] = SSC_pending_writes[ SSC_device ] + 1;
        /*Enable local interrupt*/ 
        SET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SRE );
        SSC_npackets2write[ SSC_device ] = SSC_transfer->SSC_buffer_size;
        SSC_writeto8[ SSC_device ] = (IFX_UINT8 *)SSC_transfer->SSC_buffer;
        SSC_writeto16[ SSC_device ] = (IFX_UINT16 *)SSC_transfer->SSC_buffer;
        if((SSC_mode[SSC_device] == SSC_MASTER) || (SSC_CFG_DUMMY_DATA == -1) || (SSC_CFG_SLAVE_DUMMY_DAT == 0)) 
        {
          SET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SETR );
        }
      }
      else
      {
        SSC_pending_writes[ SSC_device ] = SSC_pending_writes[ SSC_device ] + 1;
        /*Enable local interrupt*/ 
        SET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SRE );
      }

      return SSC_SUCCESS;
    }
    #else
    return SSC_ERR_RES;
    #endif
  }
  
  /*If current pending request does not have call back function the control will come here*/
  /* If queues are enabled, wait for previous pending requests completion */
  #if SSC_CFG_REQUEST_QUEUE_WR > 0
  while( SSC_pending_writes[ SSC_device ] != 0 )
  {
  }
  #endif
  
  /*update global variables*/
  SSC_writeto8[ SSC_device ] = (IFX_UINT8 *)SSC_transfer->SSC_buffer;
  SSC_writeto16[ SSC_device ] = (IFX_UINT16 *)SSC_transfer->SSC_buffer;
  SSC_npackets2write[ SSC_device ] = SSC_transfer->SSC_buffer_size;

  SSC_error_wr_msg[ SSC_device ] = SSC_SUCCESS; /*Ignore previous handled status*/
  
  switch (SSC_transfer->SSC_transfer_mode)
  {
    case SYS_TRNS_MCU_INT:
    {
      /* Need to wait if without FIFOs */ 
      #if !((SSC_HW_FIFO_TX > 0) && (SSC_CFG_TX_FIFO_LEVEL > 0))
      while( SSC_canwrite == 0 )  /*Ensure that the transmit buffer is empty*/
      {
      }
      #endif
  
      /* Create the first interrupt artificially */
      if((SSC_mode[SSC_device] == SSC_MASTER) || (SSC_CFG_DUMMY_DATA == -1) || (SSC_CFG_SLAVE_DUMMY_DAT == 0)) 
      {
        SET( SSC_HW_TSRC( SSC_device ), SSC_HW_SRC_SETR );
      }
   
      /*Wait till all the pending data to be written to transmit buffer*/
      while ( SSC_npackets2write[ SSC_device ] > 0 ) 
      {
      }

      break;
    } /* End of case SYS_TRNS_MCU_INT */

    case SYS_TRNS_PCP:
      return SSC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_DMA:
      return SSC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_MCU:
      return SSC_ERR_NOT_SUPPORTED_HW;

    default: 
      return SSC_ERR_NOT_SUPPORTED_HW;

  } /* switch */

  SSC_transfer->SSC_return_num = SSC_transfer->SSC_buffer_size;
  return SSC_error_wr_msg[ SSC_device ];
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_SLV_OSLCT_CFG == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_slv_oslct
*
* Description:
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_slv_oslct(SSC_DEVICE SSC_device, SSC_OSLAVE_OPT  SSC_slave_cfg)
{
  IFX_UINT8 port_conf = 0;

  #if SSC_HW_SLAVE_SEL_FTR == 1
  
  #if (SSC_HW_DEL_SUP == 1)
  if( (SSC_slave_cfg.SSC_inact_dly < 0 || SSC_slave_cfg.SSC_inact_dly > SSC_HW_MAX_DLY) ||
      (SSC_slave_cfg.SSC_lead_dly  < 0 || SSC_slave_cfg.SSC_lead_dly > SSC_HW_MAX_DLY) ||
      (SSC_slave_cfg.SSC_trl_dly   < 0 || SSC_slave_cfg.SSC_trl_dly > SSC_HW_MAX_DLY) ||
      (SSC_slave_cfg.SSC_line_logic_lvl < 0 || SSC_slave_cfg.SSC_line_logic_lvl > 1) ||
      (SSC_slave_cfg.SSC_delay < 0 || SSC_slave_cfg.SSC_delay > 1))
  {
    return SSC_ERR_NOT_SUPPORTED_HW;
  }
  #endif

  if(SSC_slave_num[SSC_device] != 0)
  {
    if(SSC_mode[SSC_device] == SSC_MASTER)
    {
      port_conf = 3;
    }
    else
    {
      port_conf = 2;
    }
    port_conf += SSC_slave_num[SSC_device];

    if(SYS_gpio_free(SSC_gpio_tab[SSC_device][port_conf][0], SSC_gpio_tab[SSC_device][port_conf][1],
                   SSC_gpio_tab[SSC_device][port_conf][2], SSC_gpio_tab[SSC_device][port_conf][3],
                   SSC_gpio_tab[SSC_device][port_conf][4], SSC_gpio_tab[SSC_device][port_conf][5],
                   SSC_gpio_tab[SSC_device][port_conf][6], SSC_gpio_tab[SSC_device][port_conf][7]) != SYS_SUCCESS)
    {
      return SSC_ERR;
    } 
    SSC_slave_num[SSC_device] = 0;
  }

  WRITEBITS(SSC_HW_PISEL(SSC_device), 0x0, SSC_HW_PISEL_SLSIS_MASK, SSC_HW_PISEL_SLSIS_LOC);
  WRITEBITS(SSC_HW_PISEL(SSC_device), 0x0, SSC_HW_PISEL_STIP_MASK, SSC_HW_PISEL_STIP_LOC);
  WRITEBITS(SSC_HW_SSOC(SSC_device),  0x0, SSC_HW_SSOC_OEN_MASK, SSC_HW_SSOC_OEN_LOC);
  WRITEBITS(SSC_HW_SSOTC(SSC_device), 0x0, 0xffffffff, 0);
  WRITEBITS(SSC_HW_SSOC( SSC_device), 0x0, SSC_HW_SSOC_AOL_MASK, SSC_HW_SSOC_AOL_LOC);

  
  if(SSC_slave_cfg.SSC_slv_num > 0)
  {
    if((SSC_mode[SSC_device] == SSC_MASTER) && (SSC_slave_cfg.SSC_slv_num < 9))
    {
      port_conf = 3 + SSC_slave_cfg.SSC_slv_num;
    }
    else if((SSC_mode[SSC_device] == SSC_SLAVE) && (SSC_slave_cfg.SSC_slv_num < 2))
    {
      port_conf = 2 + SSC_slave_cfg.SSC_slv_num;
    }

    if(SYS_gpio_alloc(SSC_gpio_tab[SSC_device][port_conf][0], SSC_gpio_tab[SSC_device][port_conf][1],
                   SSC_gpio_tab[SSC_device][port_conf][2], SSC_gpio_tab[SSC_device][port_conf][3],
                   SSC_gpio_tab[SSC_device][port_conf][4], SSC_gpio_tab[SSC_device][port_conf][5],
                   SSC_gpio_tab[SSC_device][port_conf][6], SSC_gpio_tab[SSC_device][port_conf][7]) != SYS_SUCCESS)
    {
      return SSC_ERR_RES_IO;
    } 
    SSC_slave_num[SSC_device] = SSC_slave_cfg.SSC_slv_num;

    if(SSC_mode[SSC_device] == SSC_MASTER)
    {
      WRITEBITS(SSC_HW_SSOC(SSC_device), 0x00000001, SSC_HW_SSOC_OEN_MASK, (SSC_HW_SSOC_OEN_LOC + (SSC_slave_cfg.SSC_slv_num -1) ));
      WRITEBITS(SSC_HW_SSOC( SSC_device), SSC_slave_cfg.SSC_line_logic_lvl, SSC_HW_SSOC_AOL_MASK, (SSC_HW_SSOC_AOL_LOC + (SSC_slave_cfg.SSC_slv_num -1) ));
    }
    else
    {
      WRITEBITS(SSC_HW_PISEL(SSC_device), SSC_slave_cfg.SSC_slv_num, SSC_HW_PISEL_SLSIS_MASK, SSC_HW_PISEL_SLSIS_LOC);
      WRITEBITS(SSC_HW_PISEL(SSC_device), SSC_slave_cfg.SSC_slv_idl_lvl, SSC_HW_PISEL_STIP_MASK, SSC_HW_PISEL_STIP_LOC);
    }
  }

  #if (SSC_HW_DEL_SUP == 1)
  if(SSC_mode[SSC_device] == SSC_MASTER)
  {
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_slave_cfg.SSC_trl_dly, SSC_HW_SSOTC_TRL_DELY_MASK, SSC_HW_SSOTC_TRL_DELY_LOC);
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_slave_cfg.SSC_lead_dly, SSC_HW_SSOTC_LEAD_DELY_MASK, SSC_HW_SSOTC_LEAD_DELY_LOC);
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_slave_cfg.SSC_inact_dly, SSC_HW_SSOTC_INCT_DELY_MASK, SSC_HW_SSOTC_INCT_DELY_LOC);
    WRITEBITS( SSC_HW_SSOTC( SSC_device ), SSC_slave_cfg.SSC_delay, SSC_HW_SSOTC_SLSO7_MASK, SSC_HW_SSOTC_SLSO7_LOC);
  }
  #endif

  #endif
  
  return SSC_SUCCESS;
}
/*-----------------------------------------------------------------------------------------*/
#endif

#if SSC_CFG_FUNC_CTRL_DISABLE == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_disable
*
* Description:
*  Disables the Module without terminating it. The peripheral is 
*  virtually disconnected. All the GPIO pins are set to input. 
*  The module cannot receive or transmit anything.
*  
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_disable (SSC_DEVICE SSC_device)
{
# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  RESET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );

  return SSC_SUCCESS;
}
/*----------------------------------------------------------------------------*/
#endif


#if SSC_CFG_FUNC_CTRL_ENABLE == 1
/*
*******************************************************************************
* Function Name:     SSC_ctrl_enable
*
* Description:
*  Enables the Module after SSC_ctrl_diasable. The GPIO config
*  and Receive Enable is restored.
*  
*******************************************************************************
*/
SSC_STATUS SSC_ctrl_enable (SSC_DEVICE SSC_device)
{
# if SSC_CFG_DEV_CHK == 1
  if (SSC_device >= SSC_HW_NUM)
  {
    return SSC_ERR_UNKNOWN_DEV;
  }
# endif

# if SSC_CFG_INIT_CHK == 1
  if (SSC_initialised_flags [SSC_device] != 1)
  {
    return SSC_ERR_NOT_INITIALISED;
  }
# endif

  SET( SSC_HW_CON( SSC_device ), SSC_HW_CON_EN );
  
  return SSC_SUCCESS ;
}
/*----------------------------------------------------------------------------*/
#endif

/*
*******************************************************************************
* Function Name:     SSC_TIR_ISR
*
* Description:
*  If the TxFIFO is enabled, the function checks if there is
*  space in the FIFO and writes data from the Application Buffer
*  to TBUF. If the FIFO is disabled, a single packet is written.
*  ( Provided there are transfers pending ).
*
*******************************************************************************
*/
void SSC_TIR_ISR (IFX_UINT8 SSC_device)
{
  IFX_UINT32 nLoop;

  if ( SSC_npackets2write[ SSC_device ] > 0 )
  { 
    #if ((SSC_HW_FIFO_TX > 0) && (SSC_CFG_TX_FIFO_LEVEL > 0)) 
    nLoop = SSC_HW_FIFO_TX - READBITS( SSC_HW_FSTAT( SSC_device ), SSC_HW_FSTAT_TXFFL, SSC_HW_FSTAT_TXFFL_LOC );
      #if SSC_CFG_STAT_LOG == 1
      SSC_successful[ SSC_device ] = SSC_successful[ SSC_device ] + nLoop;
      #endif
    if ( nLoop > SSC_npackets2write[ SSC_device ] )
    {
      nLoop = SSC_npackets2write[ SSC_device ];
    }
    #else
    nLoop = 1;
      #if SSC_CFG_STAT_LOG == 1
      SSC_successful[ SSC_device ] = SSC_successful[ SSC_device ] + nLoop;
      #endif
    SSC_canwrite = 0;
    #endif

    /*Decrement the waiting pending data bytes by number of empty locations, 
    and write data to transmit buffer*/      
    SSC_npackets2write[ SSC_device ] = SSC_npackets2write[ SSC_device ] - nLoop;
    if ( SSC_data_mask[ SSC_device ] > 0x000000FF )
    {
      for (; nLoop > 0; nLoop-- )
      {
        WRITEBITS( SSC_HW_TB( SSC_device ), *SSC_writeto16[ SSC_device ], SSC_data_mask[ SSC_device ], 0 );
        SSC_writeto16[ SSC_device ]++;
      }
    } 
    else
    {
      for (; nLoop > 0; nLoop-- )
      {
        WRITEBITS( SSC_HW_TB( SSC_device ), *SSC_writeto8[ SSC_device ], SSC_data_mask[ SSC_device ], 0 );
        SSC_writeto8[ SSC_device ]++;
      }
    }

    /*If pending writes are zero call user call back function provided pending write request support*/
    #if SSC_CFG_REQUEST_QUEUE_WR > 0
    if ( SSC_npackets2write[ SSC_device ] == 0 )
    {
      if ( SSC_pending_writes[ SSC_device ] > 0 )
      {
        SSC_writeq[ SSC_device ][ SSC_writeq_head[ SSC_device ] ]->SSC_return_num = SSC_writeq[ SSC_device ][ SSC_writeq_head[ SSC_device ] ]->SSC_buffer_size;
        if(SSC_writeq[ SSC_device ][ SSC_writeq_head[ SSC_device ] ]->SSC_trans_ucb != NULL)
        { 
          SSC_writeq[ SSC_device ][ SSC_writeq_head[ SSC_device ] ]->SSC_trans_ucb( SSC_writeq[ SSC_device ][ SSC_writeq_head[ SSC_device ] ], SSC_write_status[ SSC_device ][ SSC_writeq_head[ SSC_device]]) ;
        }
        SSC_writeq_head[ SSC_device ]++;

        if ( SSC_writeq_head[ SSC_device ] == SSC_CFG_REQUEST_QUEUE_WR )
        {
          SSC_writeq_head[ SSC_device ] = 0;
        }

        if ( SSC_pending_writes[ SSC_device ] > 1 )
        {
          SSC_npackets2write[ SSC_device ] = SSC_writeq[ SSC_device ][ (SSC_writeq_head[ SSC_device ]) ]->SSC_buffer_size;
          SSC_writeto8[ SSC_device ] = (IFX_UINT8 *)SSC_writeq[ SSC_device ][ (SSC_writeq_head[ SSC_device ]) ]->SSC_buffer;
          SSC_writeto16[ SSC_device ] = (IFX_UINT16 *)SSC_writeq[ SSC_device ][ (SSC_writeq_head[ SSC_device ]) ]->SSC_buffer;
        }
        SSC_pending_writes[ SSC_device ]--;
      }
    }
    #endif

  } /* if ( SSC_npackets2write[ SSC_device ] > 0 ) */
  #if(SSC_CFG_DUMMY_DATA != -1)
  else
  { 
    if(SSC_mode[SSC_device] == SSC_MASTER)
    {
      #if((SSC_CFG_REQUEST_QUEUE_RD > 0) && (SSC_CFG_REQUEST_QUEUE_WR > 0))
      if((SSC_pending_writes[ SSC_device ] <= 0) && (SSC_pending_reads[ SSC_device ] > 0) && (SSC_npackets2read[SSC_device] > 1) )
      #elif((SSC_CFG_REQUEST_QUEUE_RD > 0) && (SSC_CFG_REQUEST_QUEUE_WR <= 0))
      if((SSC_pending_reads[ SSC_device ] > 0) && (SSC_npackets2read[SSC_device] > 1) )
      #elif((SSC_CFG_REQUEST_QUEUE_RD <= 0) && (SSC_CFG_REQUEST_QUEUE_WR > 0))
      if((SSC_pending_writes[ SSC_device ] <= 0) && (SSC_npackets2read[SSC_device] > 1) )
      #else
      if(SSC_npackets2read[SSC_device] > 1)
      #endif
      {
        WRITEBITS( SSC_HW_TB( SSC_device ), (SSC_CFG_DUMMY_DATA & SSC_data_mask[ SSC_device ]), SSC_data_mask[ SSC_device ], 0 );
      }
    }
    #if (SSC_CFG_SLAVE_DUMMY_DAT == 1)
    else if(SSC_mode[SSC_device] == SSC_SLAVE)
    {
      WRITEBITS( SSC_HW_TB( SSC_device ), (SSC_CFG_DUMMY_DATA & SSC_data_mask[ SSC_device ]), SSC_data_mask[ SSC_device ], 0 );
    }
    #endif /*SSC_CFG_SLAVE_DUMMY_DAT*/
  }
  #endif /*SSC_CFG_DUMMY_DATA*/

  #if !((SSC_HW_FIFO_TX > 0) && (SSC_CFG_TX_FIFO_LEVEL > 0))
  SSC_canwrite = 1; /*If FIFOs are not enabled set flag that the transmit buffer is empty*/
  #endif
}
/*----------------------------------------------------------------------------*/



/*
*******************************************************************************
* Function Name:     SSC_RIR_ISR
*
* Description:
*  If there are transfers pending the incoming data is moved
*  to the Application Buffer. Otherwise it is simply written
*  to HAL circular buffer ( if enabled ).
*
*******************************************************************************
*/
void SSC_RIR_ISR (IFX_UINT8 SSC_device)
{
  IFX_UINT32 nLoop = 0;
  
  /*Find the number of bytes to be read from Rx FIFO*/
  #if ((SSC_HW_FIFO_RX > 0) && (SSC_CFG_RX_FIFO_LEVEL > 0))
  nLoop = READBITS( SSC_HW_FSTAT( SSC_device ), SSC_HW_FSTAT_RXFFL, SSC_HW_FSTAT_RXFFL_LOC );
  #else
  nLoop = 1; /*If FIFOs are not enabled make number of bytes to be read as one*/
  #endif

  /*If error condition occurs return from this ISR and read data from error ISR*/
  if ( READBITS( SSC_HW_ESRC( SSC_device ), 0x00002000, SSC_HW_SRC_SRR ) == 1 ) return;

  #if SSC_CFG_STAT_LOG == 1
  SSC_successful[ SSC_device ] = SSC_successful[ SSC_device ] + nLoop;
  #endif

  if( ( SSC_npackets2read[ SSC_device ] > 0 ))
  {
    if ( nLoop > SSC_npackets2read[ SSC_device ] )
    {
      nLoop = SSC_npackets2read[ SSC_device ];
    }
    SSC_npackets2read[ SSC_device ] = SSC_npackets2read[ SSC_device ] - nLoop;
    
    if ( SSC_data_mask[ SSC_device ] > 0x000000FF )
    {
      for (; nLoop > 0; nLoop-- )
      {
        *SSC_readfrom16[ SSC_device ] = READBITS( SSC_HW_RB( SSC_device ), SSC_data_mask[ SSC_device ], 0 );
        SSC_readfrom16[ SSC_device ] ++;
      }
    }
    else
    {
      for (; nLoop > 0; nLoop-- )
      {  
        *SSC_readfrom8[ SSC_device ] = READBITS( SSC_HW_RB( SSC_device ), SSC_data_mask[ SSC_device ], 0 );
        SSC_readfrom8[ SSC_device ]++;
      }
    }

   /*If number of pending bytes is zero call user call back function provided
     the pending request support user call back function.
   */  
    #if SSC_CFG_REQUEST_QUEUE_RD > 0
    if ( SSC_npackets2read[ SSC_device ] == 0 )
    { 
      if ( SSC_pending_reads[ SSC_device ] > 0 )
      {
        /*Update global variable*/
        nLoop = SSC_readq_head[ SSC_device ];
        SSC_readq[ SSC_device ][ nLoop ]->SSC_return_num = SSC_readq[ SSC_device ][ nLoop ]->SSC_buffer_size;
        SSC_readq[ SSC_device ][ nLoop ]->SSC_trans_ucb( SSC_readq[ SSC_device ][ nLoop ], SSC_read_status[ SSC_device ][ nLoop ]) ;

        SSC_readq_head[ SSC_device ] = SSC_readq_head[ SSC_device ] + 1;
        if ( SSC_readq_head[ SSC_device ] == SSC_CFG_REQUEST_QUEUE_RD )
        {
          SSC_readq_head[ SSC_device ] = 0;
        }
      
        /* 
         If there is another transfer pending, move to the next pending read request
        */
        if ( SSC_pending_reads[ SSC_device ] > 1 )
        {
          SSC_npackets2read[ SSC_device ] = SSC_readq[ SSC_device ][ SSC_readq_head[ SSC_device ] ]->SSC_buffer_size;
          SSC_readfrom8[ SSC_device ] = (IFX_UINT8 *)SSC_readq[ SSC_device ][ SSC_readq_head[ SSC_device ] ]->SSC_buffer;
          SSC_readfrom16[ SSC_device ] = (IFX_UINT16 *)SSC_readq[ SSC_device ][ SSC_readq_head[ SSC_device ] ]->SSC_buffer;
        }
        SSC_pending_reads[ SSC_device ]--;
      }
    }  /* if ( SSC_npackets2read[ SSC_device ] == 0 ) */
    #endif /* #if SSC_CFG_REQUEST_QUEUE_RD > 0 */

  } /* if ( SSC_npackets2read[ SSC_device ] > 0 ) */
  else  /*If no pending read requests read data to read buffer*/
  {
    #if ((SSC_HW_FIFO_RX > 0) && (SSC_CFG_RX_FIFO_LEVEL > 0))
    SET( SSC_HW_RXFCON( SSC_device ), SSC_HW_RXFCON_RXFFLU );
    #else
    READBITS( SSC_HW_RB( SSC_device ), SSC_data_mask[ SSC_device ], 0 );
    #endif
  }
}
/*----------------------------------------------------------------------------*/


/*
*******************************************************************************
* Function Name:     SSC_EIR_ISR
*
* Description:
*  The data before the faulty/corrupt data is moved to the
*  Application Buffer ( if some transfer is pending ) or to
*  the HAL Circular Buffer. The faulty packet is flushed out.
*
*******************************************************************************
*/
void SSC_EIR_ISR (IFX_UINT8 SSC_device)
{
  IFX_UINT32 SSC_error_val;

  #if SSC_HW_SEP_STAT_FTR == 0
  SSC_error_val = (IFX_UINT32)(SSC_HW_CON(SSC_device));
  WRITEBITS(SSC_HW_CON(SSC_device), 0, SSC_HW_CON_ERRORS, SSC_HW_CON_ERRORS_LOC);
  #else
  SSC_error_val = (IFX_UINT32)(SSC_HW_STAT(SSC_device));
  WRITEBITS(SSC_HW_EFM(SSC_device), 0, SSC_HW_CON_ERRORS, SSC_HW_CON_ERRORS_LOC);
  #endif

  #if SSC_CFG_STAT_LOG == 1
  if( (SSC_error_val & (0x00000001 << SSC_HW_CON_BE) ) >= 1)  /*Check for baudrate error*/
  {
    SSC_baud_err[SSC_device]++;
    #if (SSC_CFG_REQUEST_QUEUE_RD > 0)
    SSC_read_status[ SSC_device ][ SSC_readq_head[ SSC_device]] = SSC_ERR_BAUD;
    #endif
    SSC_error_rd_msg[ SSC_device ] = SSC_ERR_BAUD;
  }
  if( (SSC_error_val & (0x00000001 << SSC_HW_CON_PE) ) >= 1) /*Check for parity error*/
  {
    SSC_phase_err[SSC_device]++;
    #if(SSC_CFG_REQUEST_QUEUE_RD > 0)
    SSC_read_status[ SSC_device ][ SSC_readq_head[ SSC_device]] = SSC_ERR_PHASE; /*Check for phase error*/
    #endif
    SSC_error_rd_msg[ SSC_device ] = SSC_ERR_PHASE;
  }
  if( (SSC_error_val & (0x00000001 << SSC_HW_CON_RE) ) >= 1) /*Check for receive buffer over written error*/
  {
    SSC_receive_err[SSC_device]++;
    #if(SSC_CFG_REQUEST_QUEUE_RD > 0)
    SSC_read_status[ SSC_device ][ SSC_readq_head[ SSC_device]] = SSC_ERR_RECEIVE;
    #endif
    SSC_error_rd_msg[ SSC_device ] = SSC_ERR_RECEIVE;
  }
  if( (SSC_error_val & (0x00000001 << SSC_HW_CON_TE) ) >= 1) /*Check for transmit buffer under flow error*/
  {
    SSC_transmit_err[SSC_device]++;
    #if(SSC_CFG_REQUEST_QUEUE_WR > 0)
    SSC_write_status[ SSC_device ][ SSC_writeq_head[ SSC_device]] = SSC_ERR_TRANS;
    #endif
    SSC_error_wr_msg[ SSC_device ] = SSC_ERR_TRANS;
  }
  #endif
}



