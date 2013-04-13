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
** @FILENAME@:       ASC_IIL.c
** @VERSION@:        2.2
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block: ASC 
**
** =============================================================================
** Contents: This file provides the API which are directly availble to the user 
**           application
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
**  The bug for Testcase 2 (Which traps for higher optimization levels has been
**   fixed
** =============================================================================
*/	

#include "compiler.h"
#include "common.h"
#include "asc_cfg.h"
#include "asc_idl.h"
#include "asc_iil.h"
#include "asc_api.h"
#include "sys_api.h"
#include "sys_cfg.h"

/*
  Read buffer to capture the data received from ports when there are no pending 
  read requests.
*/
IFX_STUINT32  ASC_rdbuff[ ASC_HW_NUM ][ASC_CFG_RDBUFF_SIZE];  

/*
  The size of the read buffer.
*/
IFX_VUINT32 ASC_rdfill_size[ ASC_HW_NUM ];

/*
  Pointer to the read location from which the reading will be started in 
  read buffer provided read buffer size more than zero value. Once it 
  reaches the maximum value (ASC_CFG_RDBUFF_SIZE) resets to zero value. 
*/
IFX_STUINT32 ASC_rdbuff_rdptr[ ASC_HW_NUM ];

/*
  Pointer to write location for read buffer. When no pending read requests 
  the data received from IO ports will copy into read from this location. 
  Once it reaches the maximum value (ASC_CFG_RDBUFF_SIZE) resets to zero value.
*/
IFX_STUINT32 ASC_rdbuff_wrptr[ ASC_HW_NUM ]; 

/*
  Status of read buffer. Once it received any data with error the status wil 
  be updated with the corresponding error.The status will be updated to 
  ASC_SUCCESS when the buffer size value will be zero.
*/
ASC_STATUS ASC_rdbuff_stat[ ASC_HW_NUM ];

/*
  The current baud rate of device
*/
IFX_STUINT32 ASC_baudrate[ ASC_HW_NUM ]; 

/*
  The number of data bytes still written to IO ports of the current 
  pending write request.
*/
IFX_VUINT32 ASC_npackets2write[ ASC_HW_NUM ]; 

/*
  The number of data bytes still to read from IO ports of the 
  current pending read request.
*/
IFX_VUINT32 ASC_npackets2read[ ASC_HW_NUM ];   

/*
  The number of data bits(7,8,9) per frame of a device.
*/
IFX_STUINT32 ASC_mask[ ASC_HW_NUM ];   


#if ASC_CFG_STAT_LOG == 1
/*
  Number of frames received
*/
IFX_STUINT32 ASC_successful[ ASC_HW_NUM ];

/*
   Number of frames received with frame error.
*/
IFX_STUINT32 ASC_frame_errs[ ASC_HW_NUM ];

/*
   Number of frames received with parity error.
*/
IFX_STUINT32 ASC_parity_errs[ ASC_HW_NUM ];

/*
   Number of frames received with over run error.
*/
IFX_STUINT32 ASC_ovr_errs[ ASC_HW_NUM ];
#endif

IFX_VUINT8   ASC_canwrite = 1;
/* Flag to avoid overwriting TBUF when FIFOs are not used*/
ASC_MODE     ASC_mode[ ASC_HW_NUM ];       
/* Operating mode of device*/
IFX_STUINT8  *ASC_writeto8[ ASC_HW_NUM ];  
/* Points to Application Write Buffer for data bits < 9 */
IFX_STUINT8  *ASC_readfrom8[ ASC_HW_NUM ]; 
/* Points to Application Read  Buffer for data bits < 9 */
IFX_STUINT16 *ASC_readfrom16[ ASC_HW_NUM ];
/* Points to Application Write Buffer for data bits = 9 */ 
IFX_STUINT16 *ASC_writeto16[ ASC_HW_NUM ]; 
/* Points to Application Read  Buffer for data bits = 9 */
ASC_STATUS   ASC_error_msg[ ASC_HW_NUM ];  
/* To store read request status */
ASC_STATUS   ASC_error_wr_msg[ ASC_HW_NUM ];
/* To store write request status */
IFX_VUINT16  ASC_intr_flag[ ASC_HW_NUM ];  
/* Flag for testing the s/w interrupt */

/* The Read and Write request queues */
#if ASC_CFG_REQUEST_QUEUE_RD > 0
/*
  List to maintain the pending read requests.
*/
ASC_TRANSFER *ASC_readq[ ASC_HW_NUM ][ ASC_CFG_REQUEST_QUEUE_RD ];

/*
  List to maintain the pending request status
*/
ASC_STATUS   ASC_read_status[ ASC_HW_NUM ][ ASC_CFG_REQUEST_QUEUE_RD ];

/*
  Head pointer to pending read request lsit. This is the current 
  pending request and seriviced to be first upon receiving data 
  from IO ports (used in ASC_RIR_ISR).
*/
IFX_STUINT8    ASC_readq_head[ ASC_HW_NUM ];

/*
  Tail pointer to pending read request queue. The new read request will be 
  added to the tail end of list	(used in ASC_read API).
*/
IFX_STUINT8    ASC_readq_tail[ ASC_HW_NUM ];

/*
  The number of pending read requests.
*/
IFX_VUINT8    ASC_pending_reads[ ASC_HW_NUM ];
#endif

#if ASC_CFG_REQUEST_QUEUE_WR > 0
/*
  List to maintain the pending write requests.
*/
ASC_TRANSFER   *ASC_writeq[ ASC_HW_NUM ][ ASC_CFG_REQUEST_QUEUE_WR ];

/*
  Head pointer to pending write request lsit(used in ASC_TBIR_ISR 
  and ASC_TIR_ISR).
*/
IFX_STUINT8    ASC_writeq_head[ ASC_HW_NUM ];

/*
  Tail pointer to pending write request lsit (used in ASC_write API).
*/
IFX_STUINT8    ASC_writeq_tail[ ASC_HW_NUM ];

/*
  The number of pending write requests.
*/
IFX_VUINT8  ASC_pending_writes[ ASC_HW_NUM ]; 
#endif
 
/*
The following pre-proccessor directives check if the system HAL matches the 
implemententation dependent layer for the ASC HAL. If these do not match
then the compilation is stopped with an error to indicate this conflict to 
the user.
This check has been introduced because the IDL file names are identical, 
regardless of the product they are written for, this could easily result 
in the wrong files being used.
*/
#if SYS_PRODUCT != ASC_PRODUCT
#error ASC HAL Error: Either ASC_IDL.h file is incorrect 
  or else the wrong System HAL is being used.
#endif


/*
Check that the IDL layer is usable:
*/
#if (ASC_API_VER_MAJ > 0)
#error ASC HAL Error: Incompatible components, 
  please make sure you have the latest ASC HAL distribution.
#endif


/* 
Define initialised flags and flag management macros if 
initialisation checking is to be done.
If initialisation checking is not to be performed then
define the macros to do nothing.
*/
#if ASC_CFG_INIT_CHK == 1
  IFX_UINT8 ASC_initialised_flags [ASC_HW_NUM] = {ASC_HW_INIT(0x00)};
#endif  /* ASC_CFG_INIT_CHK == 1 */

/* Base Address Look Up Table Macro: */
/*
  This Table contains all the ASC peripherals
  For example, in the case of 3 ASC modules, the definition would be
  #define ASC_HW_ADDR_TABLE IFX_UINT32 ASC_addr_table 
  [ASC_HW_NUM] = {ASC_HW_0_ADDR, ASC_HW_1_ADDR, ASC_HW_2_ADDR}
*/
#if (ASC_HW_NUM == 1)
IFX_UINT32 ASC_addr_table [ASC_HW_NUM] = {ASC_HW_0_ADDR};
#elif (ASC_HW_NUM == 3)
IFX_UINT32 ASC_addr_table [ASC_HW_NUM] = 
  {ASC_HW_0_ADDR, ASC_HW_1_ADDR, ASC_HW_2_ADDR};
#endif


/*
  Stores ASC module frequency
*/
IFX_UINT32 ASC_clk_freeq[ASC_HW_NUM] = {ASC_HW_INIT(0)};

/* Defines for Standard modes: */
#define ASC_HW_MODE_S_D8   0 /* Synchronus ,  8 data bits, no parity */
#define ASC_HW_MODE_A_D8   1 /* Asynchronus, 8 data bits, no parity */
#define ASC_HW_MODE_A_D7_P 3 /* Asynchronus, 7 data bits,    parity */
#define ASC_HW_MODE_A_D9   4 /* Asynchronus, 9 data bits, no parity */
#define ASC_HW_MODE_A_D8_W 5 /* Asynchronus, 8 data bits,    wakeup */
#define ASC_HW_MODE_A_D8_P 7 /* Asynchronus, 8 data bits,    parity */

/* Defines for Special modes: */
#if ASC_HW_IRDA == 1
#define ASC_HW_MODE_I_D8   2 /* IrDA       , 8 data bits            */
#endif


/*
*******************************************************************************
* Function Name:     ASC_set_baud
*
* Description:
*  Sets the Baud Rate according to the user input. May return an
*  error if input is out of bounds or the tolerence setting is
*  too tight.
* 
*******************************************************************************
*/
ASC_STATUS ASC_set_baud
( 
  ASC_DEVICE ASC_device,
  IFX_UINT32 ASC_ctrl_baud
)
{ 
  IFX_UINT32 bg_val = 0, req_baud = 0;
  IFX_SFLOAT fcalc_baud = 0, fcalc_tol = 0, tol = 0;
  IFX_VUINT8  flag = 0;
  IFX_SINT32 fdiv = 0;
  IFX_VUINT16 baud_check = 8192;

  if( ASC_ctrl_baud == 0)
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }

  /*User configured baud rate tolerance value*/
  tol = ASC_CFG_BAUD_TOL;

  req_baud = ASC_ctrl_baud;   /*Required baud rate*/

  /*Check the required baud rate is with in the minimum and maximum levels*/
  if( (ASC_mode[ASC_device] == ASC_SYNC_R) || 
      (ASC_mode[ASC_device] == ASC_SYNC_T) ) /*Synchronous mode*/
  {
    if((req_baud < ASC_GET_FREQ(ASC_clk_freeq[ASC_device],ASC_MIN_CLK_SYNC)) ||
      (req_baud > ASC_GET_FREQ(ASC_clk_freeq[ASC_device],ASC_MAX_CLK_SYNC)))
    {
      ASC_mode[ASC_device] = (ASC_MODE)0;
      return ASC_ERR_NOT_SUPPORTED_HW;
    }
  }
  else /*Asynchronous and IrDA*/
  {
    #if (ASC_HW_FDIV == 1)
    if((req_baud < ASC_GET_FREQ(ASC_clk_freeq[ASC_device],ASC_MIN_CLK_ASYNC))||
      (req_baud > ASC_GET_FREQ(ASC_clk_freeq[ASC_device],
        ASC_MAX_CLK_ASYNC_FDV)))
    {
      ASC_mode[ASC_device] = ASC_ASYNC;
      return ASC_ERR_NOT_SUPPORTED_HW;
    }
    #else
    if((req_baud < ASC_GET_FREQ(ASC_clk_freeq[ASC_device],ASC_MIN_CLK_ASYNC))||
      (req_baud > ASC_GET_FREQ(ASC_clk_freeq[ASC_device],
        ASC_MAX_CLK_ASYNC_NFDV)))
    {
     ASC_mode[ASC_device] = ASC_ASYNC;
     return ASC_ERR_NOT_SUPPORTED_HW;
    }
    #endif /*ASC_HW_FDIV*/
  }

  if( (ASC_mode[ASC_device] == ASC_SYNC_R) 
    || (ASC_mode[ASC_device] == ASC_SYNC_T) ) /*Synchronous mode*/
  {
    fdiv = 8;  /*Baud rate time pre-scalar value is divide by 2 */

    /*Calculate baud rate timer reload value (BG + 1) */
    fcalc_baud = ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]) 
      /(fdiv * (IFX_SFLOAT)req_baud);

    /*If BG value more than the maximum value, use the pre scalar 
    divide by 3 value*/
    if(fcalc_baud > baud_check)
    {
      fdiv = 12;
      fcalc_baud = ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]) 
      /(fdiv * (IFX_SFLOAT)req_baud);
    }   

    /*Check for maximum baud rate timer reload value*/
    if((fcalc_baud <= baud_check) && (fcalc_baud > 0))
    {
      bg_val = (IFX_UINT32)fcalc_baud; 
      /*Baud rate timer reload value (BG + 1)*/
      fcalc_baud = ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]) 
        /(fdiv * (IFX_SFLOAT)bg_val); /*New baud rate*/
      fcalc_tol = (fcalc_baud - (IFX_SFLOAT)req_baud)
        /(IFX_SFLOAT)req_baud; 
        /*Calculate devitation from the requested baud rate*/
      fcalc_tol = (fcalc_tol < 0) ? -fcalc_tol : fcalc_tol;

      /*Check deviation with user defined tolerance level(ASC_CFG_BAUD_TOL)*/
      if(fcalc_tol <= tol)
      {
        #if ASC_HW_FDIV == 1
        RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_FDE );
        #endif

        if ( fdiv == 8)
        { 
          RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_BRS );  
          /*Enable the pre-scalar divide by 2*/
        }
        else
        { 
          SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_BRS );   
          /*Enable the pre-scalar divide by 3*/
        }
        
        /*Program the baud rate timer reload value*/
        WRITEBITS( ASC_HW_BG( ASC_device ),(bg_val - 1), 
          ASC_HW_BG_BR, ASC_HW_BG_BR_loc );
        ASC_baudrate[ ASC_device ] = (IFX_UINT32)fcalc_baud;  
        /*update the global variable for later reference*/
        return ASC_SUCCESS;
      }
      else
      {
        ASC_mode[ASC_device] = (ASC_MODE)0;
        return ASC_ERR_NOT_SUPPORTED; 
        /*New baud rate exceeds the user specified tolerance level*/
      }

    }
    else
    {
      ASC_mode[ASC_device] = (ASC_MODE)0;
      return ASC_ERR_NOT_SUPPORTED; 
      /*No matching values are found for the required baud rate */
    } 

  }
  else  /*Asynchronous communication, IrDA*/
  {
    fdiv = 32; /*Enable the pre-scalar divide by 2 */
      
    /*Calculate the baud rate timer (BG + 1) reload value*/
    fcalc_baud = ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]) 
      /(fdiv * (IFX_SFLOAT)req_baud);

    /*Check for maximum baud rate timer reload value*/
    if(fcalc_baud > baud_check)
    {
      fdiv = 48; /*Enable the pre-scalar divide by 3 */
           
      /*Calculate the baud rate timer (BG + 1) reload value*/
      fcalc_baud = ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]) 
        /(fdiv * (IFX_SFLOAT)req_baud);
    }   
    if(fcalc_baud <= baud_check) 
    /*Check for maximum baud rate timer reload value*/
    {
      bg_val = (IFX_UINT32)fcalc_baud;

      /*Calculate the new baud rate*/  
      fcalc_baud = ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]) 
        /(fdiv * (IFX_SFLOAT)bg_val);
           
      /*Calculate the deviation of new baud rate with the required baud rate*/
      fcalc_tol = (fcalc_baud - (IFX_SFLOAT)req_baud)/(IFX_SFLOAT)req_baud;
      fcalc_tol = (fcalc_tol < 0) ? -fcalc_tol : fcalc_tol;
      fcalc_tol = ((fcalc_tol == 0) ? 1 : fcalc_tol);

      /*Check deviation with user defined tolerance level(ASC_CFG_BAUD_TOL)*/
      if(fcalc_tol <= tol)
      {
        #if ASC_HW_FDIV == 1
        RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_FDE );
        #endif

        if ( fdiv == 32)
        { 
          RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_BRS );  
          /*Program the pre-scalr divider by 2*/
        }
        else
        { 
          SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_BRS );    
          /*Program the pre-scalr divider by 3*/
        }
   
        /*Write the new baud rate timer reload value*/
        WRITEBITS( ASC_HW_BG( ASC_device ),(bg_val - 1), 
          ASC_HW_BG_BR, ASC_HW_BG_BR_loc ); 
        ASC_baudrate[ ASC_device ] = (IFX_UINT32)fcalc_baud; 
        /*Update the global variable*/
        flag = 1;
        return ASC_SUCCESS;
      }
      else
      {
        flag = 0;
      }

    }
    fdiv = 512;
    #if ASC_HW_FDIV == 1
    while((!flag) && (fdiv >= 0)) 
    /*Use fractional divider with starting value 512*/
    {
       for(; fdiv >= 0; fdiv--)
       {
         /*Calculate baud rate timer reload (BG + 1) value*/
         fcalc_baud = (((IFX_SFLOAT)ASC_clk_freeq[ASC_device]/baud_check)
            * (fdiv/(IFX_SFLOAT)req_baud));
         if((fcalc_baud <= baud_check) || (fcalc_baud == 0))
         {
           break;
         }
       }
       bg_val = (IFX_UINT32)fcalc_baud; /*Baud rate timer reload value*/

       /*Calculate new baud rate*/
       fcalc_baud = (((IFX_SFLOAT)ASC_clk_freeq[ASC_device]/baud_check) 
         * (fdiv/(IFX_SFLOAT)bg_val));

       /*Calculate the deviation of new baud rate with the required baud rate*/
       fcalc_tol = (((IFX_SFLOAT)fcalc_baud - (IFX_SFLOAT)req_baud)
         /(IFX_SFLOAT)req_baud);
       fcalc_tol = (fcalc_tol < 0) ? -fcalc_tol : fcalc_tol;
       if( fcalc_tol <= tol )
       {
         SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_FDE ); 
         /*Enable fractional divider*/
         /*Program the baud rate timer reload value*/   
         WRITEBITS( ASC_HW_BG( ASC_device ), (bg_val - 1) , 
           ASC_HW_BG_BR, ASC_HW_BG_BR_loc ); 

         /*Program the fractional divider value*/ 
         WRITEBITS( ASC_HW_FDV( ASC_device ), fdiv, 
           ASC_HW_FDV_FD, ASC_HW_FDV_FD_loc );
         flag = 1;
         ASC_baudrate[ ASC_device ] = (IFX_UINT32)fcalc_baud; 
         /*Update global variable*/
         return ASC_SUCCESS;
       }
       fdiv--;  /*Breaked from 'for' loop, so decrement fdiv by 1*/
    }
    #endif /*ASC_HW_FDIV*/
     return ASC_ERR_NOT_SUPPORTED;  
     /*New baud rate exceeds the user specified tolerance level*/
  }
}


#if ASC_HW_IRDA == 1
/*
*******************************************************************************
* Function Name:     ASC_set_irda
*
* Description:
*  Sets the IrDA configuration as desired by the user
* 
*******************************************************************************
*/

ASC_STATUS ASC_set_irda
(
  ASC_DEVICE ASC_device,
  ASC_COM_PARMS *ASC_ctrl_irda
)
{
  IFX_SFLOAT ASC_irda_pw = 0;
  IFX_SFLOAT ASC_fpmw_regval = 0;
  IFX_VSINT32 ASC_pmw_regval = 0; 
  ASC_STATUS temp_stat; 

  if(ASC_ctrl_irda == NULL)
  {
    return ASC_ERR;
  }

  if(ASC_ctrl_irda->ASC_com_baud == 0)
  {
    return ASC_ERR;
  }

  /*Variable IrDA pulse width, pulese width is 3/16 of bit time.*/
  if(ASC_ctrl_irda->ASC_com_stop == ASC_STOP_1) 
  {
    ASC_irda_pw = (3.0 / (16.0 * (IFX_SFLOAT)ASC_ctrl_irda->ASC_com_baud));

    /*Calculate required minimum pulse width to program PMW register*/
    ASC_fpmw_regval =  ASC_irda_pw * 2 * 
      ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]);

    /*Round the float value to the integer value*/
    ASC_pmw_regval = (IFX_UINT32)(ASC_fpmw_regval - 0.5);

    /*Check for allowable maximum and minimum values*/    
    if((ASC_pmw_regval < 0) || (ASC_pmw_regval > 255))
    {
      return ASC_ERR_NOT_SUPPORTED_HW;
    } 
    else
    {
      /*Set the baud rate*/  
      temp_stat = ASC_set_baud(ASC_device, ASC_ctrl_irda->ASC_com_baud);
      if(temp_stat != ASC_SUCCESS)
      {
        return temp_stat;
      }
      /*Program registers*/ 
      WRITEBITS(ASC_HW_PMW(ASC_device), ASC_pmw_regval, 
        ASC_HW_PMW_PW, ASC_HW_PMW_PW_loc);
      RESET( ASC_HW_PMW( ASC_device ), ASC_HW_PMW_IRPW );
    }
  }
  /*fixed IrDA pulse width. Set the pulse width to a user specified 
  value ASC_ctrl_irda->ASC_com_baud in nano seconds*/
  else 
  {
    /*Calculate pulse width register value*/
    ASC_fpmw_regval =  ((IFX_SFLOAT)ASC_ctrl_irda->ASC_com_baud 
      /(1000000000.0)) * ((IFX_SFLOAT)ASC_clk_freeq[ASC_device]);
    ASC_pmw_regval = (IFX_VSINT32)ASC_fpmw_regval;

    /*Check for allowable maximum and minimum values*/    
   
    if((ASC_pmw_regval < 0) || (ASC_pmw_regval > 255))
    {
      return ASC_ERR_NOT_SUPPORTED_HW;
    } 
    else
    {
      /*Program registers*/  
      WRITEBITS(ASC_HW_PMW(ASC_device), ASC_pmw_regval, 
        ASC_HW_PMW_PW, ASC_HW_PMW_PW_loc);
      SET( ASC_HW_PMW( ASC_device ), ASC_HW_PMW_IRPW );
    }

  }

  /*Check for RX pin inverter mode*/
  if( (ASC_ctrl_irda->ASC_com_parity == ASC_PARITY_EVEN)
    ||(ASC_ctrl_irda->ASC_com_parity == ASC_PARITY_ODD))
  {
    SET(ASC_HW_CON(ASC_device), ASC_HW_CON_RXDI);
  }
  else
  {
    RESET(ASC_HW_CON(ASC_device), ASC_HW_CON_RXDI);
  }

  /* Store the value as baud rate */
  ASC_baudrate[ ASC_device ] = ASC_ctrl_irda->ASC_com_baud;

  /* Set the mode */
  WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_I_D8, 
    ASC_HW_CON_M, ASC_HW_CON_M_loc );
  ASC_mask[ ASC_device ] = 0x000000FF;
  
  return ASC_SUCCESS;
}
#endif /* #if ASC_HW_IRDA == 1 */


/*
*******************************************************************************
* Function Name:     ASC_set_all
*
* Description:
*  Sets the Mode, Data, Parity and Stop bits. It also sets the
*  Baud Rate and may set the IrDA configuration if required.
*  It may also change the GPIO config if required.
* 
*  Note : Synchronous mode, IrDA and wake up modes are not supported 
*
*******************************************************************************
*/
ASC_STATUS ASC_set_all
(
  ASC_DEVICE ASC_device,
  ASC_COM_PARMS *ASC_ctrl_all
)
{
  IFX_UINT32 nMODE = 0;
  IFX_UINT32 nSTP = 0;
  IFX_UINT32 nODD = 0;
  IFX_UINT32 nREN = 0;
  IFX_UINT32 ASC_port = 0;
  IFX_UINT32 ASC_pin = 0;
  ASC_STATUS temp_stat;
  IFX_UINT32 nmask = 0;

  if(ASC_ctrl_all == NULL)
  {
    return ASC_ERR;
  }
    
  /* Code to set the Stop Bits */
  if ( ASC_ctrl_all->ASC_com_stop == ASC_STOP_1  
    || ASC_ctrl_all->ASC_mode == ASC_IRDA)
  {
    nSTP = 0;
  }
  else if ( ASC_ctrl_all->ASC_com_stop == ASC_STOP_2 )
  { 
    nSTP = 1;
  }
  else 
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }

  /* Code to set Even/Odd parity */
  if ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_EVEN  
    || ASC_ctrl_all->ASC_com_parity == ASC_PARITY_NONE)
  {
    nODD = 0;
  }
  else
  {
    nODD = 1;
  }

  nREN = 1;                   /* By default, reception is on */
  
  /*Code to set ASC (7 bits, 8 bits and 9 bits, no wake up) modes*/
  if ( (ASC_ctrl_all->ASC_mode == ASC_ASYNC) 
    || (ASC_ctrl_all->ASC_mode == ASC_ASYNC_MASTER) )
  {
    switch (ASC_ctrl_all->ASC_com_data)
    {
      case ASC_DATA_8:
      {
        nmask = 0x000000FF;
        if ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_NONE )
        {
          nMODE = ASC_HW_MODE_A_D8;  /*Asynchronous 8 data bits, no parity*/
        }
        else if ( ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_ODD ) 
          || ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_EVEN ) )
        {
          nMODE = ASC_HW_MODE_A_D8_P;  /*Asynchronous 8 data bits + parity*/
        }
        else
        { 
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
        break;
      } /* case ASC_DATA_8 */
      
      case ASC_DATA_7:
      { 
        nmask = 0x0000007F;
        if ( ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_ODD ) 
          || ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_EVEN ) )
        {
          nMODE = ASC_HW_MODE_A_D7_P; /*Asynchronous 7 data bits + parity*/
        }
        else
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
        break;
      } /* case ASC_DATA_7 */

      case ASC_DATA_9:
      {
        nmask = 0x000001FF;
        if ( ASC_ctrl_all->ASC_com_parity == ASC_PARITY_NONE )
        {
          nMODE = ASC_HW_MODE_A_D9;  /*Aynchronous 9 data bits*/
        }
        else
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
        break;
      } /* case ASC_DATA_9 */

    }  /* end of switch (ASC_ctrl_all->ASC_com_data) */
  } /* end of if( (ASC_ctrl_all->ASC_mode == ASC_ASYNC)
     || (ASC_ctrl_all->ASC_mode == ASC_ASYNC_MASTER) )*/

  else
  { 
    switch (ASC_ctrl_all->ASC_mode)
    {
      case ASC_SYNC_R:  /*Synchronous receive*/
      case ASC_SYNC_T:  /*Synchronous transmit*/
      {
        if ( (ASC_ctrl_all->ASC_com_parity == ASC_PARITY_NONE ) 
          && (ASC_ctrl_all->ASC_com_data == ASC_DATA_8) )
        {
          nmask = 0x000000FF;
          nMODE = ASC_HW_MODE_S_D8;
        }
        else
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
        break;
      }
  
      case ASC_ASYNC_SLAVE:  /*Asynchronous slave (wake up)*/
      {
        if (ASC_ctrl_all->ASC_com_data == ASC_DATA_8)
        {
          nMODE = ASC_HW_MODE_A_D8_W;
          nmask = 0x000000FF;
        }
        else
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
        break;
      }
  
      #if ASC_HW_IRDA == 1
      case ASC_IRDA: /*IrDA mode*/
      if(ASC_set_irda( ASC_device, ASC_ctrl_all ) != ASC_SUCCESS)
      {
        return ASC_ERR;
      }
      nmask = 0x000000FF;
      nMODE = ASC_HW_MODE_I_D8;
      break;
      #endif

    } /* End of switch (ASC_ctrl_all->ASC_mode) */
  } /* End of - else ( (ASC_ctrl_all->ASC_mode == ASC_ASYNC) 
    || (ASC_ctrl_all->ASC_mode == ASC_ASYNC_MASTER) )  */
  
  /*Code to set the Baud rate */
  if(ASC_ctrl_all->ASC_mode != ASC_IRDA)
  {
    ASC_mode[ASC_device] = ASC_ctrl_all->ASC_mode;
    temp_stat = ASC_set_baud( ASC_device, ASC_ctrl_all->ASC_com_baud );
    if(temp_stat != ASC_SUCCESS)
    {
      return temp_stat;
    }
  }
  
  /*If the mode is synchronous set RX pin direction to output*/
  if((ASC_ctrl_all->ASC_mode == ASC_SYNC_R) 
    || (ASC_ctrl_all->ASC_mode == ASC_SYNC_T))
  {
      switch(ASC_device)
      {
        case 0:
          ASC_port = SYS_gpio_get_port(SYS_GPIO_ASC0_RX);
          ASC_pin  = SYS_gpio_get_pin_num(SYS_GPIO_ASC0_RX);
          break;

        #if ASC_HW_NUM > 1
        case 1:
          ASC_port = SYS_gpio_get_port(SYS_GPIO_ASC1_RX);
          ASC_pin  = SYS_gpio_get_pin_num(SYS_GPIO_ASC1_RX);
          break;
        #endif

        #if ASC_HW_NUM > 2
        case 2:
           ASC_port = SYS_gpio_get_port(SYS_GPIO_ASC2_RX);
           ASC_pin  = SYS_gpio_get_pin_num(SYS_GPIO_ASC2_RX);
           break;
        #endif
      }
      SYS_WRITE_REG(((SYS_PORT_BASE + 
        (ASC_port * SYS_PORT_OFFSET))+SYS_DIR),ASC_pin,1);
  }
  else /*For the modes other than Synchronous set Rx pin direction to input*/
  {
    switch(ASC_device)
    {
      case 0:
        ASC_port = SYS_gpio_get_port(SYS_GPIO_ASC0_RX);
        ASC_pin  = SYS_gpio_get_pin_num(SYS_GPIO_ASC0_RX);
        break;

      #if ASC_HW_NUM > 1
      case 1:
        ASC_port = SYS_gpio_get_port(SYS_GPIO_ASC1_RX);
        ASC_pin  = SYS_gpio_get_pin_num(SYS_GPIO_ASC1_RX);
        break;
      #endif

      #if ASC_HW_NUM > 2
      case 2:
        ASC_port = SYS_gpio_get_port(SYS_GPIO_ASC2_RX);
        ASC_pin  = SYS_gpio_get_pin_num(SYS_GPIO_ASC2_RX);
        break;
      #endif
    }
    SYS_WRITE_REG(((SYS_PORT_BASE + 
      (ASC_port * SYS_PORT_OFFSET))+SYS_DIR),ASC_pin,0);
  }

  /*Program control register for mode, data bits, parity and stop bits*/
  WRITEBITS( ASC_HW_CON( ASC_device ), ( ((nMODE << ASC_HW_CON_M_loc) 
    | (nSTP << ASC_HW_CON_STP)) | ((nREN << ASC_HW_CON_REN) | 
      (nODD << ASC_HW_CON_ODD)) ), ASC_HW_CON_TRNS, 0); 
  ASC_mode[ ASC_device ] = ASC_ctrl_all->ASC_mode;  /*Update global variables*/
  ASC_mask[ASC_device] = nmask;
  return ASC_SUCCESS;
}


/*
*******************************************************************************
* Function Name:     ASC_set_intr_prior
*
* Description:
*  Writes the respective priorities to the respective registers
*  
*******************************************************************************
*/
void ASC_set_intr_prior
(
  ASC_DEVICE ASC_device,
  IFX_UINT8  ASC_tir,
  IFX_UINT8  ASC_rir,
  IFX_UINT8  ASC_tbir,
  IFX_UINT8  ASC_eir
)
{
  /*Set receive interrupt priority*/
  WRITEBITS( ASC_HW_RSRC ( ASC_device ), ASC_rir,  
    ASC_HW_SRC_SRPN, ASC_HW_SRC_SRPN_loc );
  /*Set transmit interrupt priority*/
  WRITEBITS( ASC_HW_TSRC ( ASC_device ), ASC_tir,  
    ASC_HW_SRC_SRPN, ASC_HW_SRC_SRPN_loc );
  /*Set transmit buffer interrupt priority*/
  WRITEBITS( ASC_HW_TBSRC( ASC_device ), ASC_tbir, 
    ASC_HW_SRC_SRPN, ASC_HW_SRC_SRPN_loc );
  /*Set error interrupt priority*/
  WRITEBITS( ASC_HW_ESRC ( ASC_device ), ASC_eir,  
    ASC_HW_SRC_SRPN, ASC_HW_SRC_SRPN_loc );    
}



/*
*******************************************************************************
* Function Name:     ASC_initialise_dev
*
* Description:
*  this function initialises the internal data structures of the 
   HAL related to the device
*  selected by ASC_device, allocates any required system resources 
   and configures the
*  peripheral according to the ASC_COM_PARMS structure. The ASC_COM_PARMS
*  structure must be initialised by the user before calling 
   ASC_initialise_dev. This function
*  must be called successfully before any of the other API 
   functions are used and if
*  ASC_terminate_dev is called then ASC_initialise_dev must be 
   called again before
*  using the other API functions.
*******************************************************************************
*/
ASC_STATUS ASC_initialise_dev
(
  ASC_DEVICE ASC_device,
  ASC_COM_PARMS *ASC_setup
)
{
  ASC_STATUS  TempStatus;
  IFX_UINT32  port_num;

  #if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] == 1) 
  { 
    return ASC_ERR; 
  }
  #endif

  #if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
  #endif
  
  if(ASC_setup == NULL)
  {
    return ASC_ERR;
  }

  /*Check the user configured RMC value correctness*/
  #if( (ASC_CFG_RMC_VAL <= 0) || (ASC_CFG_RMC_VAL > 255))
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  #endif

  ASC_clk_freeq[ASC_device] = (SYS_CFG_CLK_FREQ / ASC_CFG_RMC_VAL);

  #if (IFX_COMPILER_GNU == 1)
  /*If the ISR to be initialised, call the ASC_HW_register_isr function*/
  if (ASC_HW_register_isr (ASC_device) == 0)
  {
    return ASC_ERR_RES_INT;
  }
  #endif
  
  /*Enable the ASC module by programming ASC clock control register.*/
  UNLOCK_ENDINIT_PROTECT;
  SYS_WRITEBITS(ASC_HW_CLC(ASC_device), ASC_CFG_RMC_VAL, SYS_HW_CLC_RMC, 
    SYS_HW_CLC_RMC_loc );
  LOCK_ENDINIT_PROTECT;

  /*Program GPIO registers for direction and functionality of a TX and RX pin*/
  switch(ASC_device)
  {
    case 0:
      if(SYS_gpio_alloc(SYS_GPIO_ASC0_TX) != SYS_SUCCESS) /*ASC0 TX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      if(SYS_gpio_alloc(SYS_GPIO_ASC0_RX) != SYS_SUCCESS) /*ASC0 RX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      break;

    #if ASC_HW_NUM > 1
    case 1:
      if(SYS_gpio_alloc(SYS_GPIO_ASC1_TX) != SYS_SUCCESS) /*ASC1 TX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      if(SYS_gpio_alloc(SYS_GPIO_ASC1_RX) != SYS_SUCCESS) /*ASC1 RX signal*/
      {
        return ASC_ERR_RES_IO;
      }

      /*Set PISEL register*/
      #if ASC_HW_PISELCT == 1
      port_num = SYS_gpio_get_port(SYS_GPIO_ASC1_RX);
      if(port_num == ASC_HW_PISEL_REG)
      {
        SET(ASC_HW_PISEL(ASC_device),ASC_HW_PISEL_loc);
      }     
      else
      {
        RESET(ASC_HW_PISEL(ASC_device),ASC_HW_PISEL_loc);
      }
      #endif /*ASC_HW_PISELCT*/
      break;
    #endif /*ASC_HW_NUM > 1*/

    #if ASC_HW_NUM > 2
    case 2:
      if(SYS_gpio_alloc(SYS_GPIO_ASC2_TX) != SYS_SUCCESS) /*ASC2 TX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      if(SYS_gpio_alloc(SYS_GPIO_ASC2_RX) != SYS_SUCCESS) /*ASC2 RX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      /*Set PISEL register*/
      #if ASC_HW_PISELCT == 1
      port_num = SYS_gpio_get_port(SYS_GPIO_ASC2_RX);
      if(port_num == ASC_HW_PISEL_REG)
      {
        SET(ASC_HW_PISEL(ASC_device),ASC_HW_PISEL_loc);
      }     
      else
      {
        RESET(ASC_HW_PISEL(ASC_device),ASC_HW_PISEL_loc);
      }
      #endif /*ASC_HW_PISELCT*/
      break;
    #endif /*ASC_HW_NUM > 2*/
  }/*End of switch*/

  /*Initialize all the data buffers with default values, for more information
  about the following variables please refer the corresponding decleration in 
  the same file.*/
  ASC_rdfill_size[ ASC_device ] = 0;
  ASC_rdbuff_rdptr[ ASC_device ] = 0; 
  ASC_rdbuff_wrptr[ ASC_device ] = 0; 

  /* Initialize the globals */
  ASC_error_msg[ ASC_device ] = ASC_SUCCESS;
  ASC_npackets2write[ ASC_device ] = 0;
  ASC_npackets2read[ ASC_device ] = 0;
  ASC_rdbuff_stat[ ASC_device ] = ASC_SUCCESS;
  
  #if ASC_CFG_STAT_LOG == 1
  ASC_successful[ ASC_device ] = 0;
  ASC_frame_errs[ ASC_device ] = 0;
  ASC_parity_errs[ ASC_device ] = 0;
  ASC_ovr_errs[ ASC_device ] = 0;
  #endif
  
  #if ASC_CFG_REQUEST_QUEUE_RD > 0
  ASC_readq_head[ ASC_device ] = 0;
  ASC_readq_tail[ ASC_device ] = 0;
  ASC_pending_reads[ ASC_device ] = 0;
  #endif

  #if ASC_CFG_REQUEST_QUEUE_WR > 0
  ASC_writeq_head[ ASC_device ] = 0;
  ASC_writeq_tail[ ASC_device ] = 0;
  ASC_pending_writes[ ASC_device ] = 0;
  #endif

  ASC_intr_flag[ ASC_device ] = 0;

  /*Check for maximum and minimum RX and TX FIFO levels*/
  #if((ASC_CFG_RX_FIFO_LEVEL < 0) || (ASC_CFG_RX_FIFO_LEVEL > ASC_HW_FIFO_RX))
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  #endif

  #if((ASC_CFG_TX_FIFO_LEVEL < 0) || (ASC_CFG_TX_FIFO_LEVEL > ASC_HW_FIFO_TX))
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  #endif

  /*To set the parity, number of stop and data bits and baud rate call the 
  ASC_set_all function*/
  TempStatus = ASC_set_all( ASC_device, ASC_setup );

  if ( TempStatus != ASC_SUCCESS )
  {
    return TempStatus;
  }

  /* initialize RX FIFO control register */
  #if ASC_HW_FIFO_RX > 0 
    #if ASC_CFG_RX_FIFO_LEVEL == 0
    RESET( ASC_HW_RXFCON( ASC_device ), ASC_HW_RXFCON_RXFEN );
    #else  
    SET( ASC_HW_RXFCON(ASC_device ), ASC_HW_RXFCON_RXFEN );
    SET( ASC_HW_RXFCON(ASC_device ), ASC_HW_RXFCON_RXFFLU );
    RESET( ASC_HW_RXFCON(ASC_device ), ASC_HW_RXFCON_RXTMEN );
      #if ASC_CFG_RX_FIFO_LEVEL < ASC_HW_FIFO_RX
      WRITEBITS( ASC_HW_RXFCON(ASC_device ), ASC_CFG_RX_FIFO_LEVEL, 
        ASC_HW_RXFCON_RXFITL, ASC_HW_RXFCON_RXFITL_loc );
      #else
      WRITEBITS( ASC_HW_RXFCON(ASC_device ), ASC_HW_FIFO_RX, 
        ASC_HW_RXFCON_RXFITL, ASC_HW_RXFCON_RXFITL_loc );
      #endif
    #endif
  #endif
 

  /* initialize TX FIFO control register */
  #if ASC_HW_FIFO_TX > 0 
    #if ASC_CFG_TX_FIFO_LEVEL == 0
    RESET( ASC_HW_TXFCON( ASC_device ), ASC_HW_TXFCON_TXFEN );
    #else
    SET( ASC_HW_TXFCON(ASC_device), ASC_HW_TXFCON_TXFEN );
    SET( ASC_HW_TXFCON(ASC_device), ASC_HW_TXFCON_TXFFLU );
    RESET( ASC_HW_TXFCON(ASC_device), ASC_HW_TXFCON_TXTMEN );
      #if ASC_CFG_TX_FIFO_LEVEL < ASC_HW_FIFO_TX
      WRITEBITS( ASC_HW_TXFCON( ASC_device ), ASC_CFG_TX_FIFO_LEVEL, 
        ASC_HW_TXFCON_TXFITL, ASC_HW_TXFCON_TXFITL_loc );
      #else
      WRITEBITS( ASC_HW_TXFCON( ASC_device ), ASC_HW_FIFO_TX, 
        ASC_HW_TXFCON_TXFITL, ASC_HW_TXFCON_TXFITL_loc );
      #endif
    #endif
  #endif

  
  /* Code to initialize the rest of control register  */
  if(ASC_mode[ASC_device] != ASC_IRDA)
  {
    #if ASC_CFG_PEN == 1
    SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_PEN );  
    /*Enable the parity check bit*/
    #else
    RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_PEN ); 
    /*Disable the parity check bit*/
    #endif
  }

  #if ASC_CFG_FRAME_CHK == 1
  SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_FEN );  
  /*Enable the framing error check bit*/
  #else
  RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_FEN );  
  /*Disable the framing error check bit*/
  #endif

  #if ASC_CFG_OVR_CHK == 1
  SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_OEN );  
  /*Enable the over run error check bit*/
  #else
  RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_OEN ); 
  /*Disable the over run error check bit*/
  #endif


  /* Program interrupt priorities */
  switch(ASC_device)
  {
    case 0:
      ASC_set_intr_prior( ASC_device, SYS_ASC0_TIR, SYS_ASC0_RIR, 
        SYS_ASC0_TBIR, SYS_ASC0_EIR );
      break;
    #if ASC_HW_NUM > 1
    case 1:
      ASC_set_intr_prior( ASC_device, SYS_ASC1_TIR, SYS_ASC1_RIR, 
        SYS_ASC1_TBIR, SYS_ASC1_EIR );
      break;
    #endif
    #if ASC_HW_NUM > 2
    case 2:
      ASC_set_intr_prior( ASC_device, SYS_ASC2_TIR, SYS_ASC2_RIR, 
        SYS_ASC2_TBIR, SYS_ASC2_EIR );
      break;
    #endif
  }

  /*Enable indivadual interrupts*/  
  SET( ASC_HW_RSRC(ASC_device), ASC_HW_SRC_SRE );
  SET( ASC_HW_ESRC(ASC_device), ASC_HW_SRC_SRE );
  SET( ASC_HW_TSRC( ASC_device), ASC_HW_SRC_SRE );
  SET( ASC_HW_TBSRC(ASC_device), ASC_HW_SRC_SRE );

  #if ASC_CFG_LPBACK == 1
  SET(ASC_HW_CON(ASC_device), ASC_HW_CON_LB); 
  #endif

  /* Enable Interrupts globally */
  ENABLE_GLOBAL_INTERRUPT();  
 
  /* To finally enable the baud rate generator run time controller */
  SET(ASC_HW_CON( ASC_device ), ASC_HW_CON_R );

# if ASC_CFG_INIT_CHK == 1
  ASC_initialised_flags [ASC_device] = 1;
# endif
  return ASC_SUCCESS;
}
/*---------------------------------------------------------------------------*/

  
#if ASC_CFG_FUNC_TERMINATE == 1
/*
*******************************************************************************
* Function Name:     ASC_terminate_dev
*
* Description:
*  Terminates the device by disabling the Module clock and removing
*  the interrupt module related interrupt priorities from the 
*  the common System Interrupt table.
*  
*******************************************************************************
*/
ASC_STATUS ASC_terminate_dev (ASC_DEVICE ASC_device)
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if(ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /* Flush receive FIFO */
  #if ( ( ASC_CFG_RX_FIFO_LEVEL > 0) && (ASC_HW_FIFO_RX > 0) )
  SET( ASC_HW_RXFCON( ASC_device ), ASC_HW_RXFCON_RXFFLU );
  #endif

  /* Flush transmit FIFO */
  #if ( ( ASC_CFG_TX_FIFO_LEVEL > 0) && (ASC_HW_FIFO_RX > 0) )
  SET( ASC_HW_TXFCON( ASC_device ), ASC_HW_TXFCON_TXFFLU );
  #endif

  /*Reset baud rate run time control bit*/
  RESET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);

  /*Disable the ASC module by programming the clock control register RMC 
  value to zero */
  UNLOCK_ENDINIT_PROTECT;
  SYS_WRITEBITS(ASC_HW_CLC(ASC_device), SYS_RST, SYS_HW_CLC_RMC, 
    SYS_HW_CLC_RMC_loc );
  LOCK_ENDINIT_PROTECT;

  /*Release and return the ports to sytem HAL used by ASC module, 
  the system HAL will 
  update its global data accordingly.*/
  switch(ASC_device)
  {
    case 0:
      if(SYS_gpio_free(SYS_GPIO_ASC0_TX) != SYS_SUCCESS) 
      /*Release ASC0 TX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      if(SYS_gpio_free(SYS_GPIO_ASC0_RX) != SYS_SUCCESS) 
      /*Release ASC0 RX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      break;

    #if ASC_HW_NUM > 1
    case 1:
      if(SYS_gpio_free(SYS_GPIO_ASC1_TX) != SYS_SUCCESS) 
      /*Release ASC1 TX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      if(SYS_gpio_free(SYS_GPIO_ASC1_RX) != SYS_SUCCESS) 
      /*Release ASC1 RX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      break;
    #endif
    
    #if ASC_HW_NUM > 2
    case 2:
      if(SYS_gpio_free(SYS_GPIO_ASC2_TX) != SYS_SUCCESS) 
      /*Release ASC2 TX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      if(SYS_gpio_free(SYS_GPIO_ASC2_RX) != SYS_SUCCESS) 
      /*Release ASC2 RX signal*/
      {
        return ASC_ERR_RES_IO;
      }
      break;
    #endif

    default: 
      return ASC_ERR_NOT_SUPPORTED_HW;
  }

# if ASC_CFG_INIT_CHK == 1
  ASC_initialised_flags [ASC_device] = 0;
# endif
  return ASC_SUCCESS;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_ABORT == 1
/*
*******************************************************************************
* Function Name:     ASC_abort
*
* Description:
*  Aborts the ongoing transmission by flushing the input and ouput
*  FIFOs. It also flushes the Circular Buffer( if enabled ).
*
*******************************************************************************
*/
ASC_STATUS ASC_abort (ASC_DEVICE ASC_device)
{
  IFX_SINT8 pending_req;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] == 1) 
  { 
    return ASC_ERR; 
  }
# endif

  /*Reset baud rate run time control bit*/
  RESET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);

  /*Reset the read buffer and pointers*/
  ASC_rdfill_size[ASC_device] = 0;
  ASC_rdbuff_rdptr[ASC_device] = 0;
  ASC_rdbuff_wrptr[ASC_device] = 0;

  /* Flush the queued read pending requests and return an error */
  #if ASC_CFG_REQUEST_QUEUE_RD > 0
  if ( ASC_pending_reads[ ASC_device ] > 0 )
  {
    ASC_readq[ ASC_device][ (ASC_readq_head[ ASC_device ]) ]->ASC_return_num = 
      ASC_readq[ ASC_device][ (ASC_readq_head[ ASC_device ]) ]->
        ASC_buffer_size - ASC_npackets2read[ ASC_device ];
    ASC_npackets2read[ ASC_device ] = 0;
    ASC_readq[ ASC_device][ (ASC_readq_head[ ASC_device ]) ]->
      ASC_trans_ucb( ASC_readq[ ASC_device][ (ASC_readq_head[ ASC_device ]) ],
         ASC_ERR );      
    #if ASC_CFG_REQUEST_QUEUE_RD > 1
    for ( pending_req = ASC_pending_reads[ ASC_device ] - 1; 
      pending_req > 0; pending_req-- )
    {
      ASC_readq_head[ ASC_device ]++;
      if ( ASC_readq_head[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_RD )
      {
        ASC_readq_head[ ASC_device ] = 0;
      }
      ASC_readq[ ASC_device][ (ASC_readq_head[ ASC_device ]) ]->
        ASC_return_num = 0;
      ASC_readq[ ASC_device][ (ASC_readq_head[ ASC_device ]) ]->
        ASC_trans_ucb( ASC_readq[ ASC_device]
          [ (ASC_readq_head[ ASC_device ]) ], ASC_ERR );      
    }
    #endif
    ASC_pending_reads[ ASC_device ] = 0;
    ASC_readq_head[ ASC_device ] = 0;
    ASC_readq_tail[ ASC_device ] = ASC_CFG_REQUEST_QUEUE_RD - 1;
  }
  #else
  ASC_error_msg[ ASC_device ] = ASC_ERR; /*Update status*/
  ASC_npackets2read[ ASC_device ] = 0; 
  /*If pending read requests not supported then make pending reads as zero.*/
  #endif
  
  /*Flush queud write pending requests and return an error*/
  #if ASC_CFG_REQUEST_QUEUE_WR > 0
  if ( ASC_pending_writes[ ASC_device ] > 0 )
  {
    ASC_writeq[ ASC_device][ (ASC_writeq_head[ ASC_device ]) ]->
      ASC_return_num = ASC_writeq[ ASC_device]
        [ (ASC_writeq_head[ ASC_device ]) ]->
          ASC_buffer_size - ASC_npackets2write[ ASC_device ];
    ASC_npackets2write[ ASC_device ] = 0;
    ASC_writeq[ ASC_device][ (ASC_writeq_head[ ASC_device ]) ]->
      ASC_trans_ucb( ASC_writeq[ ASC_device]
        [ (ASC_writeq_head[ ASC_device ]) ], ASC_ERR );      
    #if ASC_CFG_REQUEST_QUEUE_WR > 1
    for ( pending_req = ASC_pending_writes[ ASC_device ] - 1; 
      pending_req > 0; pending_req-- )
    {
      ASC_writeq_head[ ASC_device ]++;
      if ( ASC_writeq_head[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_WR )
      {
        ASC_writeq_head[ ASC_device ] = 0;
      }
      ASC_writeq[ ASC_device][ (ASC_writeq_head[ ASC_device ]) ]->
        ASC_return_num = 0;
      ASC_writeq[ ASC_device][ (ASC_writeq_head[ ASC_device ]) ]->
        ASC_trans_ucb( ASC_writeq[ ASC_device]
          [ (ASC_writeq_head[ ASC_device ]) ], ASC_ERR );      
    }
    #endif
    ASC_pending_writes[ ASC_device ] = 0; 
    ASC_writeq_head[ ASC_device ] = 0;
    ASC_writeq_tail[ ASC_device ] = ASC_CFG_REQUEST_QUEUE_WR - 1;
  }
  #else
  ASC_error_wr_msg[ ASC_HW_NUM ] = ASC_ERR;   /*Update status*/
  ASC_npackets2write[ ASC_device ] = 0; /*If pending write requests 
  not supported then make pending writes as zero.*/
  #endif
  
  /* Flush receive FIFO */
  #if ( ( ASC_CFG_RX_FIFO_LEVEL > 0) && (ASC_HW_FIFO_RX > 0) )
  SET( ASC_HW_RXFCON( ASC_device ), ASC_HW_RXFCON_RXFFLU );
  #endif

  /* Flush transmit FIFO */
  #if ( ( ASC_CFG_TX_FIFO_LEVEL > 0) && (ASC_HW_FIFO_RX > 0) )
  SET( ASC_HW_TXFCON( ASC_device ), ASC_HW_TXFCON_TXFFLU );
  #endif

  /*Set baud rate run time control bit*/
  SET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);

  return ASC_SUCCESS;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_STATUS == 1
/*
*******************************************************************************
* Function Name:     ASC_status_dev
*
* Description:
* Reports the status of the device and stores the parameters into the
* structure pointed to by ASC_stat_inf. If logging is enabled, this
* function also reports the status of the packets received since
* the last time this function was called. 
* 
*******************************************************************************
*/
ASC_STATUS ASC_status_dev
(
  ASC_DEVICE ASC_device,
  ASC_STAT_INF *ASC_stat_inf
)
{
  IFX_UINT32 mode = 0;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] == 1) 
  { 
    return ASC_ERR; 
  }
# endif

  if(ASC_stat_inf == NULL)
  {
    return ASC_ERR;
  }

  ASC_stat_inf->ASC_com_parms.ASC_mode = ASC_mode[ ASC_device ];  
  /*Mode of device*/

  #if ASC_CFG_STAT_LOG == 1
  ASC_stat_inf->ASC_frame_errs = ASC_frame_errs[ ASC_device ]; 
  /*Frames received with framing error*/

  /*Frames received successfully without any errors*/
  ASC_stat_inf->ASC_successful = ASC_successful[ ASC_device ] - 
    ( ASC_parity_errs[ ASC_device ] + ASC_frame_errs[ ASC_device ] + 
      ASC_ovr_errs[ ASC_device ] ) ;
  ASC_stat_inf->ASC_ovr_errs   = ASC_ovr_errs[ ASC_device ];  
  /*Frames received with over run errors*/
  ASC_stat_inf->ASC_parity_errs = ASC_parity_errs[ ASC_device ]; 
   /*Frames received with parity errors*/

  /*Reset all counters to zero value */
  ASC_successful[ ASC_device ] = 0;
  ASC_frame_errs[ ASC_device ] = 0;
  ASC_frame_errs[ ASC_device ] = 0;
  ASC_ovr_errs[ ASC_device ]   = 0;
  #endif


  /* Read the number of stop bits */
  if ( READBITS( ASC_HW_CON( ASC_device ), 0x00000008, ASC_HW_CON_STP ) == 0 )
  {
    ASC_stat_inf->ASC_com_parms.ASC_com_stop = ASC_STOP_1;
  }
  else
  { 
    ASC_stat_inf->ASC_com_parms.ASC_com_stop = ASC_STOP_2;
  }

  /* Read Baud Rate */
  ASC_stat_inf->ASC_com_parms.ASC_com_baud = ASC_baudrate[ ASC_device ];
    
  /* Determine the mode, data bits and parity */
  switch(ASC_mask[ASC_device])
  {
    case 0x0000007F:
      ASC_stat_inf->ASC_com_parms.ASC_com_data = ASC_DATA_7;
      break;
    case 0x000000FF:
      ASC_stat_inf->ASC_com_parms.ASC_com_data = ASC_DATA_8;
      break;
    case 0x000001FF:
      ASC_stat_inf->ASC_com_parms.ASC_com_data = ASC_DATA_9;
      break;
  }

  /*Read parity*/
  if ( READBITS( ASC_HW_CON( ASC_device ), 0x00001000 ,ASC_HW_CON_ODD ) == 0 )
  {
    mode = READBITS(ASC_HW_CON(ASC_device), ASC_HW_CON_M, ASC_HW_CON_M_loc);
    if((mode == ASC_HW_MODE_A_D8) || (mode == ASC_HW_MODE_S_D8) || 
      (mode == ASC_HW_MODE_A_D9) ) 
    {
      ASC_stat_inf->ASC_com_parms.ASC_com_parity = ASC_PARITY_NONE;
    }
    else
    {
      ASC_stat_inf->ASC_com_parms.ASC_com_parity = ASC_PARITY_EVEN;
      mode = READBITS(ASC_HW_CON(ASC_device), 0x00000020, ASC_HW_CON_RXDI);
      if((ASC_mode[ASC_device] == ASC_IRDA) && (mode == 0))
      {
        ASC_stat_inf->ASC_com_parms.ASC_com_parity = ASC_PARITY_NONE;
      }
    }
  }
  else
  {
    ASC_stat_inf->ASC_com_parms.ASC_com_parity = ASC_PARITY_ODD;
  }

  /* Reaturn the FIFO levels */
  #if ASC_HW_FIFO_RX > 0
  ASC_stat_inf->ASC_rx_fifo_lev = READBITS( ASC_HW_FSTAT( ASC_device ), 
    ASC_HW_FSTAT_RXFFL, ASC_HW_FSTAT_RXFFL_loc );
  #endif
  #if ASC_HW_FIFO_TX > 0
  ASC_stat_inf->ASC_tx_fifo_lev = READBITS( ASC_HW_FSTAT( ASC_device ), 
    ASC_HW_FSTAT_TXFFL, ASC_HW_FSTAT_TXFFL_loc );
  #endif

  return ASC_SUCCESS;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CONTROL == 1
/*
*******************************************************************************
* Function Name:     ASC_control_dev
*
* Description:
*  Gives a common entry point for controlling all the
*  parameters of the ASC module. This function calls
*  other HAL API functions.
*
*******************************************************************************
*/
ASC_STATUS ASC_control_dev
(
  ASC_DEVICE ASC_device,
  ASC_CTRL_CODE ASC_ctrl_code,
  void *ASC_ctrl_arg
)
{
  IFX_UINT8 temp_stat;
  
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif
  
  if(ASC_ctrl_arg == NULL)
  {
    return ASC_ERR;
  }

  switch (ASC_ctrl_code)
  {
    #if ASC_CFG_FUNC_CTRL_BAUD == 1
    case ASC_CTRL_TRNS_BAUD:  /*To program new baud rate*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_trns_baud( ASC_device, *(IFX_UINT32 *)ASC_ctrl_arg );
    #endif
    
    #if ASC_CFG_FUNC_CTRL_DATA == 1
    case ASC_CTRL_TRNS_DATA:   /*Chnage number of data bits*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_trns_data( ASC_device, *(ASC_DATA *)ASC_ctrl_arg );
    #endif
    
    #if ASC_CFG_FUNC_CTRL_STOP == 1
    case ASC_CTRL_TRNS_STOP:  /*Program number of stop bits*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_trns_stop( ASC_device, *(ASC_STOP *)ASC_ctrl_arg );
    #endif
    
    #if ASC_CFG_FUNC_CTRL_PARITY == 1
    case ASC_CTRL_TRNS_PARITY: /*Program parity*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_trns_parity( ASC_device, *(ASC_PARITY *)ASC_ctrl_arg );
    #endif
    
    #if ASC_CFG_FUNC_CTRL_ALL == 1
    case ASC_CTRL_TRNS_ALL:  
    /*Change number of data bits, parity, stop bits and baud rate*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_trns_all( ASC_device, (ASC_COM_PARMS *)ASC_ctrl_arg );
    #endif
    
    #if ASC_CFG_FUNC_CTRL_IRDA == 1
    case ASC_CTRL_IRDA_CFG: /*Program IrDA configuration*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_irda_cfg( ASC_device, (ASC_COM_PARMS *)ASC_ctrl_arg );
    #endif
    
    #if ASC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH == 1
    case ASC_CTRL_FIFO_GET_RX_DEPTH:  /*Read h/w supported receive FIFO level*/
      temp_stat = ASC_ctrl_fifo_get_rx_depth( ASC_device );
      if ( temp_stat == 0 )
      {
        return ASC_ERR_NOT_SUPPORTED;
      }
      return ASC_SUCCESS;
    #endif

    #if ASC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH == 1
    case ASC_CTRL_FIFO_GET_TX_DEPTH:  
    /*Read the h/w supported transmit FIFO level*/
      temp_stat = ASC_ctrl_fifo_get_tx_depth( ASC_device );
      if ( temp_stat == 0 )
      {
        return ASC_ERR_NOT_SUPPORTED;
      }
      return ASC_SUCCESS;
    #endif /*ASC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH*/
   
    #if ASC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL == 1
    case ASC_CTRL_FIFO_GET_RX_LEVEL:
      #if (ASC_HW_FIFO_RX == 0)
      return ASC_ERR_NOT_SUPPORTED_HW;
      #elif (ASC_CFG_RX_FIFO_LEVEL == 0)
      return ASC_ERR_NOT_SUPPORTED;
      #else
      temp_stat = ASC_ctrl_fifo_get_rx_level( ASC_device ); 
      /*Read h/w supported receive FIFO level*/
      if ( temp_stat == 0 )
      {
        return ASC_ERR_NOT_SUPPORTED;
      }
      return ASC_SUCCESS;
      #endif
    #endif /*ASC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL*/  
  
    #if ASC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL == 1
    case ASC_CTRL_FIFO_GET_TX_LEVEL:
      #if (ASC_HW_FIFO_TX == 0)
      return ASC_ERR_NOT_SUPPORTED_HW;
      #elif (ASC_CFG_TX_FIFO_LEVEL == 0)
      return ASC_ERR_NOT_SUPPORTED;
      #else
      temp_stat = ASC_ctrl_fifo_get_rx_level( ASC_device ); 
      /*Read h/w supported transmit FIFO level*/
      if ( temp_stat == 0 )
      {
        return ASC_ERR_NOT_SUPPORTED;
      }
      return ASC_SUCCESS;
      #endif
    #endif /*ASC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL*/
  
    #if ASC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL == 1
    case ASC_CTRL_FIFO_SET_RX_LEVEL:  /*Set receive FIFO level*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_fifo_set_rx_level( ASC_device, 
        *(IFX_UINT8 *) ASC_ctrl_arg );   
    #endif
  
    #if ASC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL
    case ASC_CTRL_FIFO_SET_TX_LEVEL:  /*Set transmit FIFO level*/
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_fifo_set_tx_level( ASC_device, 
        *(IFX_UINT8 *) ASC_ctrl_arg );
    #endif

    #if ASC_CFG_FUNC_CTRL_FLOW == 1
    case ASC_CTRL_FLOW:  /*Set flow control */
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_flow( ASC_device, (ASC_FLOW_CTRL_SETUP *) ASC_ctrl_arg );
    #endif

    #if ASC_CFG_FUNC_CTRL_AUTOBAUD == 1
    case ASC_CTRL_BAUD_DETECT:
      if(ASC_ctrl_arg == NULL)
      {
        return ASC_ERR;
      }
      return ASC_ctrl_baud_detect( ASC_device, *(IFX_UINT32 *) ASC_ctrl_arg );
    #endif 

    #if ASC_CFG_FUNC_CTRL_DISABLE == 1  
    case ASC_CTRL_DISABLE: /*Disable module temporarily*/
      return ASC_ctrl_disable( ASC_device );
    #endif
  
    #if ASC_CFG_FUNC_CTRL_ENABLE == 1
    case ASC_CTRL_ENABLE: /*Enable module temporarily*/
      return ASC_ctrl_enable( ASC_device );
    #endif
  }
  return ASC_ERR;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_READ == 1
/*
*******************************************************************************
* Function Name:     ASC_read
*
* Description:
* Reports the status of the device and stores the parameters into the
* structure pointed to by ASC_stat_inf. If logging is enabled, this
* function also reports the status of the packets received since
* the last time this function was called. 
* 
*******************************************************************************
*/
ASC_STATUS ASC_read
(
  ASC_DEVICE ASC_device,
  ASC_TRANSFER *ASC_transfer
)
{
  ASC_STATUS TempStatus;
  
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  if(ASC_transfer == NULL)
  {
    return ASC_ERR;
  }

  /*Hardware supports only interrupt mode data transmission mode*/  
  if( (ASC_transfer->ASC_transfer_mode == SYS_TRNS_MCU) || (ASC_transfer->
    ASC_transfer_mode == SYS_TRNS_PCP) || 
       (ASC_transfer->ASC_transfer_mode == SYS_TRNS_DMA) )
  {
     return ASC_ERR_NOT_SUPPORTED_HW;
  }

  /*If module is operating in half duplex synchronous 
  mode set receive enable bit*/
  if((ASC_mode[ASC_device] == ASC_SYNC_R) || (ASC_mode[ASC_device] == 
    ASC_SYNC_T))
  {
    #if ASC_HW_WHB_REG == 0
    SET(ASC_HW_CON(ASC_device), ASC_HW_CON_REN); 
    #else
    SET(ASC_HW_WHB_CON(ASC_device), ASC_HW_WHB_SET_REN_loc);
    #endif  
  }

  /*If read has call back function and not the polling mode*/
  if ( ( ASC_transfer->ASC_trans_ucb != NULL ) && 
    ( ASC_transfer->ASC_transfer_mode == SYS_TRNS_MCU_INT ))
  {
    #if ASC_CFG_REQUEST_QUEUE_RD > 0
    /*Disable local interrupt*/  
    RESET(ASC_HW_RSRC( ASC_device ), ASC_HW_SRC_SRE);
    if ( ASC_pending_reads[ ASC_device ] >=  ASC_CFG_REQUEST_QUEUE_RD )  
    /*Check for maximum pending requests*/
    { 
      /*Enable local interrupt*/  
      SET(ASC_HW_RSRC( ASC_device ), ASC_HW_SRC_SRE);
      return ASC_ERR_RES;
    }
    else 
    {
      /*Update global variables if there is no other pending read requests*/
      if (ASC_pending_reads[ ASC_device ] == 0 )
      {
        ASC_npackets2read[ ASC_device ] = ASC_transfer->ASC_buffer_size;
        ASC_readfrom8[ ASC_device ] = (IFX_UINT8 *)(ASC_transfer->ASC_buffer);
        ASC_readfrom16[ ASC_device ] = (IFX_UINT16 *)
          (ASC_transfer->ASC_buffer);
      }  
      
      ASC_pending_reads[ ASC_device ] = ASC_pending_reads[ ASC_device ] + 1; 
      /*Enable local interrupt*/  
      SET(ASC_HW_RSRC( ASC_device ), ASC_HW_SRC_SRE);

      /*Add the pending read request to the queue. */
      ASC_readq[ ASC_device ][ (ASC_readq_tail[ ASC_device ]) ] = ASC_transfer;
      /*Increment the number of pending requests*/
      /*Update the status of just added pending request, 
      by default it is ASC_SUCCESS*/
      ASC_read_status[ ASC_device ][ (ASC_readq_tail[ ASC_device ]) ] 
        = ASC_SUCCESS;

      /*
        Tail(ASC_readq_tail) pointer is used in ASC_read API and 
        Head(ASC_readq_head) is used in ASC_RIR_ISR. 
        These two pointers will make the read queue as re-entrant.
      */
      ASC_readq_tail[ ASC_device ] = ASC_readq_tail[ ASC_device ] + 1;
      if ( ASC_readq_tail[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_RD )
      {
        ASC_readq_tail[ ASC_device ] = 0;
      }

      /*If data already available in read buffer raise read 
      software interrupt*/
      if(ASC_rdfill_size[ASC_device] > ASC_transfer->ASC_buffer_size)
      {
         ASC_intr_flag[ ASC_device ] = 1;
         SET( ASC_HW_RSRC( ASC_device ), ASC_HW_SRC_SETRR);
      }
      return ASC_SUCCESS;
    }
    #else
    return ASC_ERR_RES;  
    #endif /* #if ASC_CFG_REQUEST_QUEUE_RD > 0 */   
  } /* if a UCB is requested */
    
  /* If queues are enabled, wait for pending transfers */
  #if ASC_CFG_REQUEST_QUEUE_RD > 0
  while( ASC_pending_reads[ ASC_device ] != 0 )
  { 
  }
  #endif
  
  /*If no user call back function the control will come here. 
  Update the global variables*/  
  ASC_readfrom8[ ASC_device ] = (IFX_UINT8 *)(ASC_transfer->ASC_buffer);
  ASC_readfrom16[ ASC_device ] = (IFX_UINT16 *)(ASC_transfer->ASC_buffer);
  ASC_npackets2read[ ASC_device ] = ASC_transfer->ASC_buffer_size;
  
  /* Reset the status */
  TempStatus = ASC_SUCCESS;
  
  /* Ignore previous status, have been handled already*/
  ASC_error_msg[ ASC_device ] = ASC_SUCCESS;

  switch (ASC_transfer->ASC_transfer_mode)
  {
    case SYS_TRNS_MCU_INT:
    {
      /*If data already available in read buffer raise read 
      software interrupt*/
      if(ASC_rdfill_size[ASC_device] > ASC_transfer->ASC_buffer_size)
      {
         ASC_intr_flag[ ASC_device ] = 1; 
         SET( ASC_HW_RSRC( ASC_device ), ASC_HW_SRC_SETRR);
      }

      /* Loop till the Reception is completes */ 
      while ( ASC_npackets2read[ ASC_device ] > 0 )
      {
      }
      break;
    } /* End of - case SYS_TRNS_MCU_INT */

    case SYS_TRNS_PCP:  /*PCP is not supported*/
      return ASC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_DMA: /*DMA transmission is not supported*/
      return ASC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_MCU:   /*Polling mode is not supported*/
      return ASC_ERR_NOT_SUPPORTED_HW;

    default: 
      return ASC_ERR_NOT_SUPPORTED_HW;

  } /* End of switch */

  /*Update the status and number of data bytes are read*/
  ASC_transfer->ASC_return_num = ASC_transfer->ASC_buffer_size;
  TempStatus = ASC_error_msg[ ASC_device ];
  return TempStatus;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_WRITE == 1
/*
*******************************************************************************
* Function Name:     ASC_write
*
* Description:
*  Writes the data in the Application buffer in a controlled manner
*  to TBUF, so that it may be transmitted.
*
*******************************************************************************
*/
ASC_STATUS ASC_write
(
  ASC_DEVICE ASC_device,
  ASC_TRANSFER *ASC_transfer
)
{
  IFX_UINT32 nLoop;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  if(ASC_transfer == NULL)
  {
    return ASC_ERR;
  }

  /*Hardware supports only interrupt mode data transmission mode*/  
  if( (ASC_transfer->ASC_transfer_mode == SYS_TRNS_MCU) || (ASC_transfer->
    ASC_transfer_mode == SYS_TRNS_PCP) || 
       (ASC_transfer->ASC_transfer_mode == SYS_TRNS_DMA) )
  {
     return ASC_ERR_NOT_SUPPORTED_HW;
  }

  /*
    If ASC module operating in half duplex synchronous mode and non loop 
    back mode reset receive enable bit.
  */
  #if ASC_CFG_LPBACK == 0
  if( (ASC_mode[ASC_device] == ASC_SYNC_R) || (ASC_mode[ASC_device] == 
    ASC_SYNC_T))
  {
    #if ASC_HW_WHB_REG == 0
    RESET(ASC_HW_CON(ASC_device), ASC_HW_CON_REN); 
    #else
    SET(ASC_HW_WHB_CON(ASC_device), ASC_HW_WHB_CLR_REN_loc);
    #endif  
  }
  #endif  /*ASC_CFG_LPBACK*/

  /*Check for user call back function (non block request)*/
  if ( ( ASC_transfer->ASC_trans_ucb != NULL ) && (ASC_transfer->
    ASC_transfer_mode == SYS_TRNS_MCU_INT) )
  {
    #if ASC_CFG_REQUEST_QUEUE_WR > 0
    /*Disable local interrupts*/
    RESET( ASC_HW_TSRC( ASC_device ), ASC_HW_SRC_SRE ); 
    RESET( ASC_HW_TBSRC( ASC_device ), ASC_HW_SRC_SRE ); 

    if ( ASC_pending_writes[ ASC_HW_NUM ] ==  ASC_CFG_REQUEST_QUEUE_WR ) 
    /*Check for maximum pending writes*/
    { 
      /*Enable local interrupts*/
      SET( ASC_HW_TSRC( ASC_device ), ASC_HW_SRC_SRE ); 
      SET( ASC_HW_TBSRC( ASC_device ), ASC_HW_SRC_SRE ); 
      return ASC_ERR_RES;  /* If the Request queue is full */
    }
    else 
    {
      /*Add the pending write request to the Tail pointer of queue 
      (ASC_writeq_tail). ASC_writeq_tail is used in ASC_write. 
      ASC_writeq_head is used in ASC_TBIR_ISR and ASC_TIR_ISR. 
      These tail and head pointers will make the
      driver write portion as re-entrant*/
      if ( ASC_pending_writes[ ASC_device ] == 0 )
      {
        nLoop = ASC_writeq_tail[ ASC_device ];

        /*Add the pending write request to queue */ 
        ASC_writeq[ ASC_device ][ nLoop ] = ASC_transfer;

        /*If there are no other pending write request 
        in queue update global variables*/
        ASC_npackets2write[ ASC_device ] = ASC_transfer->ASC_buffer_size;
        ASC_writeto8[ ASC_device ] = (IFX_UINT8 *)(ASC_transfer->ASC_buffer);
        ASC_writeto16[ ASC_device ] = (IFX_UINT16 *)(ASC_transfer->ASC_buffer);

        ASC_pending_writes[ ASC_device ] = ASC_pending_writes[ ASC_device ] + 1;

        ASC_writeq_tail[ ASC_device ] = ASC_writeq_tail[ ASC_device ] + 1;
        if ( ASC_writeq_tail[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_WR )
        {
          ASC_writeq_tail[ ASC_device ] = 0;
        }

        /*Enable local interrupts*/
        SET( ASC_HW_TSRC( ASC_device ), ASC_HW_SRC_SRE ); 
        SET( ASC_HW_TBSRC( ASC_device ), ASC_HW_SRC_SRE ); 

        /* Generate first interrupt - which one TBIR or TIR */
        SET( ASC_HW_TSRC( ASC_device ), ASC_HW_SRC_SETRR ); 
        SET( ASC_HW_TBSRC( ASC_device ), ASC_HW_SRC_SETRR ); 

        return ASC_SUCCESS;
      }/* if ( ASC_pending_reads[ ASC_device ] == 0 ) */
      else
      {
        ASC_pending_writes[ ASC_device ] = ASC_pending_writes[ ASC_device ] + 1;
        /*Enable local interrupts*/
        SET( ASC_HW_TSRC( ASC_device ), ASC_HW_SRC_SRE ); 
        SET( ASC_HW_TBSRC( ASC_device ), ASC_HW_SRC_SRE ); 

        nLoop = ASC_writeq_tail[ ASC_device ];
        ASC_writeq[ ASC_device ][ nLoop ] = ASC_transfer;
        ASC_writeq_tail[ ASC_device ] = ASC_writeq_tail[ ASC_device ] + 1;
        if ( ASC_writeq_tail[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_WR )
        {
          ASC_writeq_tail[ ASC_device] = 0;
        }
        return ASC_SUCCESS;
      }
    }
    #else
    return ASC_ERR_RES;
    #endif
  }
  
  /*If current pending request does not have call back function the control 
  will come here*/
  /* If queues are enabled, wait for previous pending requests completion */
  #if ASC_CFG_REQUEST_QUEUE_WR > 0
  while( ASC_pending_writes[ ASC_device ] != 0 )
  {
  }
  #endif
  
  /*update global variables*/
  ASC_writeto8[ ASC_device ] = (IFX_UINT8 *)(ASC_transfer->ASC_buffer);
  ASC_writeto16[ ASC_device ] = (IFX_UINT16 *)(ASC_transfer->ASC_buffer);
  ASC_npackets2write[ ASC_device ] = ASC_transfer->ASC_buffer_size;

  ASC_error_wr_msg[ ASC_HW_NUM ] = ASC_SUCCESS; 
  /*Ignore previous hnadled status*/
  
  switch (ASC_transfer->ASC_transfer_mode)
  {
    case SYS_TRNS_MCU_INT:
    {
      /* Need to wait if without FIFOs */ 
      #if !((ASC_HW_FIFO_TX > 0) && (ASC_CFG_TX_FIFO_LEVEL > 0))
      while( ASC_canwrite == 0 )  /*Ensure that the transmit buffer is empty*/
      {
      }
      #endif
  
      /* Create the first interrupt artificially */
      SET( ASC_HW_TSRC( ASC_device ), ASC_HW_SRC_SETRR );
      SET( ASC_HW_TBSRC( ASC_device ), ASC_HW_SRC_SETRR ); 
   
      /*Wait till all the pending data to be written to transmit buffer*/
      while ( ASC_npackets2write[ ASC_device ] > 0 ) 
      {
      }

      break;
    } /* End of case SYS_TRNS_MCU_INT */

    case SYS_TRNS_PCP:
      return ASC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_DMA:
      return ASC_ERR_NOT_SUPPORTED_HW;

    case SYS_TRNS_MCU:
      return ASC_ERR_NOT_SUPPORTED_HW;

    default: 
      return ASC_ERR_NOT_SUPPORTED_HW;

  } /* switch */

  ASC_transfer->ASC_return_num = ASC_transfer->ASC_buffer_size;
  return ASC_error_wr_msg[ ASC_HW_NUM ];
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_BAUD == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_trns_baud
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
ASC_STATUS ASC_ctrl_trns_baud
(
  ASC_DEVICE ASC_device,
  IFX_UINT32 ASC_ctrl_baud
)
{
  
  ASC_STATUS TempStatus;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /*Disable the baud rate run time control bit*/
  RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_R );
  /*Set the new baud rate*/
  TempStatus = ASC_set_baud( ASC_device, ASC_ctrl_baud );    
  /*Enable the baud rate run time control bit*/
  SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_R );
  return TempStatus;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_DATA == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_trns_data
*
* Description:
*  Changes the no. of data bits to the desired value (7,8 or 9)
*  For data consistency, the HAL circular buffers need to be 
*  flushed.
*
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_trns_data
(
  ASC_DEVICE ASC_device,
  ASC_DATA ASC_ctrl_data
)
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  switch (ASC_ctrl_data)
  {
    case ASC_DATA_8:
    {
      switch( READBITS( ASC_HW_CON( ASC_device ), ASC_HW_CON_M, 
        ASC_HW_CON_M_loc ) )
      {
        case ASC_HW_MODE_A_D7_P: 
        /*If earlier is (7 bits + parity) then change to 
        (8 bits + parity) mode*/
        {
          WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_A_D8_P, 
            ASC_HW_CON_M, ASC_HW_CON_M_loc );
          ASC_mask[ ASC_device ] = 0x000000FF;
          return ASC_SUCCESS;
        }

        case ASC_HW_MODE_A_D9: /*If earlier is (9 bits + no parity) 
        then change to (8 bits + no parity) mode*/
        {  
          WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_A_D8, 
            ASC_HW_CON_M, ASC_HW_CON_M_loc );
          ASC_mask[ ASC_device ] = 0x000000FF;
          return ASC_SUCCESS;
        }
        
        case ASC_HW_MODE_A_D8_P: 
        /*If it is already 8 bits then return success*/
        case ASC_HW_MODE_A_D8:
        {
          return ASC_SUCCESS;
        } 

        default:
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
      }
    } /* case ASC_DATA_8 */

    case ASC_DATA_9:
    {
      switch( READBITS( ASC_HW_CON( ASC_device ), ASC_HW_CON_M, 
        ASC_HW_CON_M_loc ))
      {
        case ASC_HW_MODE_A_D8: 
        /*If earlier is (8 bits + no parity) then change to 
        (9 bits + no parity)*/
        case ASC_HW_MODE_A_D8_W:
        {
          WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_A_D9, 
            ASC_HW_CON_M, ASC_HW_CON_M_loc );
          ASC_mask[ ASC_device ] = 0x000001FF;
          return ASC_SUCCESS;
        }

        case ASC_HW_MODE_A_D9: /*If it is already 9 bits return success*/
        {
          return ASC_SUCCESS;
        }

        default:
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
      } /* switch READBITS() */
    } /* case ASC_DATA_9 */

    case ASC_DATA_7:
    { 
      switch READBITS( ASC_HW_CON( ASC_device ), ASC_HW_CON_M, 
        ASC_HW_CON_M_loc )
      {
        case ASC_HW_MODE_A_D8_P: 
        /*If earlier is (8 bits + parity) then change to (7 bits + parity)*/
        {
          WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_A_D7_P, 
            ASC_HW_CON_M, ASC_HW_CON_M_loc );
          ASC_mask[ ASC_device ] = 0x0000007F;
          return ASC_SUCCESS;
        }

        case ASC_HW_MODE_A_D7_P: 
        /*If it is already 7 bits then return success*/
        {
          return ASC_SUCCESS;
        }

        default:
        {
          return ASC_ERR_NOT_SUPPORTED_HW;
        }
      } /* switch READBITS() */
    } /* case ASC_DATA_7 */

    default:
    {
      return ASC_ERR_NOT_SUPPORTED_HW;
    }
  } /* switch ASC_ctrl_data */

}

/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_STOP == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_trns_stop
*
* Description:
*  Changes the no. of stop bits to the desired value (1 or 2)
*  1.5 Stop bits are not supported.
*
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_trns_stop
(
  ASC_DEVICE ASC_device,
  ASC_STOP ASC_ctrl_stop
)
{
# if ASC_CFG_DEV_CHK == 1
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  if ( ASC_ctrl_stop == ASC_STOP_1 )
  {
    RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_STP );  
    /*Change the number of stop bits to 1*/
    return ASC_SUCCESS;
  }
  else if ( ASC_ctrl_stop == ASC_STOP_2 )
  { 
#   if ASC_HW_IRDA == 1   /*Change the number of stop bits to 1*/
    /*IrDA mode does not support 2 stop bits*/
    if(ASC_mode[ASC_device] == ASC_IRDA)
    {
       return ASC_ERR_NOT_SUPPORTED;
    }
#   endif

    SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_STP );
    return ASC_SUCCESS;
  }
  /*Hardware won't support 1.5 stop bits*/
  else if ( ASC_ctrl_stop == ASC_STOP_1_5 )
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  return ASC_ERR;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_PARITY == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_trns_parity
*
* Description:
*  Changes the parity to the desired value ( even, odd and no 
*  parity) are supported.
*
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_trns_parity
(
  ASC_DEVICE ASC_device,
  ASC_PARITY ASC_ctrl_parity
)
{
 
 IFX_VUINT8 flag = 0;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif
  
  if (( ASC_ctrl_parity == ASC_PARITY_ODD ) || ( ASC_ctrl_parity == 
    ASC_PARITY_EVEN ))
  {
    switch(READBITS( ASC_HW_CON( ASC_device ), ASC_HW_CON_M, 
      ASC_HW_CON_M_loc ))
    {
      /* 2 Cases in which the parity can be switched on */
      case ASC_HW_MODE_A_D8:
        WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_A_D8_P, 
          ASC_HW_CON_M, ASC_HW_CON_M_loc );
        flag = 1;
        break;

      /* The following 2 cases already have the parity enabled */
      case ASC_HW_MODE_A_D8_P:
        flag = 1;
        break;

      case ASC_HW_MODE_A_D7_P:
        flag = 1;
        break;

      default:
        /* Cases in which the parity bit is not supported */
        return ASC_ERR_NOT_SUPPORTED_HW;
   
    } /* End of - switch READBITS( ASC_HW_CON( ASC_device ), 
      ASC_HW_CON_M, ASC_HW_CON_M_loc ) */

    /*Check flag*/
    if(flag == 1)
    {
      if ( ASC_ctrl_parity == ASC_PARITY_ODD ) 
      {
        SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_ODD );
      }
      else
      {
        RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_ODD );
      }
    } /*flag == 1*/

  } /* End of if (( ASC_ctrl_parity == ASC_PARITY_ODD ) || 
    ( ASC_ctrl_parity == ASC_PARITY_EVEN )) */

  else if ( ASC_ctrl_parity == ASC_PARITY_NONE )
  {
    switch READBITS( ASC_HW_CON( ASC_device ), ASC_HW_CON_M, ASC_HW_CON_M_loc ) 
    {
      case ASC_HW_MODE_A_D8_P: 
      /*If it 8 bits + parity then change to 8 bits mode*/
      WRITEBITS( ASC_HW_CON( ASC_device ), ASC_HW_MODE_A_D8, ASC_HW_CON_M, 
        ASC_HW_CON_M_loc );
      return ASC_SUCCESS;

      default: 
        return ASC_ERR_NOT_SUPPORTED_HW;
    }

  } /* End of - else if( ASC_ctrl_parity == ASC_PARITY_NONE ) */
  else
  { 
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  return ASC_SUCCESS;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_ALL == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_trns_all
*
* Description:
*  Sets the Mode, Data, Parity and Stop bits. It also sets the
*  Baud Rate and may set the IrDA configuration if required.
*  It may also change the GPIO config if required.
*
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_trns_all
(
  ASC_DEVICE ASC_device,
  ASC_COM_PARMS *ASC_ctrl_all
)
{
  ASC_STATUS temp_stat;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /*Reset baud rate run time control bit*/
  RESET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);
  /*Program number of data bits, stop bits, parity and baud rate*/
  temp_stat = ASC_set_all( ASC_device, ASC_ctrl_all );
  /*Set baud rate run time control bit*/
  SET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);

  return temp_stat;
}
/*---------------------------------------------------------------------------*/
#endif


#if (ASC_CFG_FUNC_CTRL_IRDA == 1) && (ASC_HW_IRDA == 1)
/*
*******************************************************************************
* Function Name:     ASC_ctrl_irda_cfg
*
* Description:
*  Sets the IrDA configuration as desired by the user
* 
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_irda_cfg
(
  ASC_DEVICE ASC_device,
  ASC_COM_PARMS *ASC_ctrl_irda
)
{
  ASC_STATUS temp_stat;
  ASC_MODE   temp_mode;

# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /*Check for IrDA mode*/  
  if((ASC_ctrl_irda->ASC_mode != ASC_IRDA) || (ASC_ctrl_irda == NULL))
  {
    return ASC_ERR;
  }

  temp_mode = ASC_mode[ASC_device];

  /*Reset baud rate run time control bit*/
  RESET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);
  /*Program IrDA mode*/
  temp_stat =  ASC_set_irda( ASC_device, ASC_ctrl_irda ); 
  if(temp_stat != ASC_SUCCESS)
  {
    ASC_mode[ASC_device] = temp_mode;
  }
  else
  {
    ASC_mode[ASC_device] = ASC_IRDA;
  }
  /*Set baud rate run time control bit*/
  SET(ASC_HW_CON(ASC_device), ASC_HW_CON_R);
  
  return temp_stat;
}  
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_AUTOBAUD == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_baud_detect
*
* Description:
*  Automatically detects Baud Rate. Feature not supported in TC11IB and TC1130
* 
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_baud_detect
(
  ASC_DEVICE ASC_device,
  IFX_UINT32 ASC_ctrl_autobaud_hint
)
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  ASC_device = ASC_ctrl_autobaud_hint = 0;

  #if ASC_HW_AUTOBAUD == 0
  return ASC_ERR_NOT_SUPPORTED_HW;
  #endif
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_FIFO_GET_RX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_fifo_get_rx_level
*
* Description:
*  Returns the RxFIFO level at/above which a Receive Buffer Full
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
IFX_UINT8 ASC_ctrl_fifo_get_rx_level ( ASC_DEVICE ASC_device )
{ 
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif
  
  /*Return the number of bytes are in receive FIFO */
  return READBITS( ASC_HW_RXFCON( ASC_device ), ASC_HW_RXFCON_RXFITL, 
  ASC_HW_RXFCON_RXFITL_loc );
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_FIFO_GET_TX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_fifo_get_tx_level
*
* Description:
*  Returns the TxFIFO level at/below which a Transmit Buffer Empty
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
IFX_UINT8 ASC_ctrl_fifo_get_tx_level( ASC_DEVICE ASC_device )
{ 
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /*Return the number of bytes are in transmit FIFO*/
  return READBITS( ASC_HW_TXFCON( ASC_device ), ASC_HW_TXFCON_TXFITL, 
    ASC_HW_TXFCON_TXFITL_loc );
}
/*---------------------------------------------------------------------------*/
#endif

#if ASC_CFG_FUNC_CTRL_FIFO_GET_RX_DEPTH == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_fifo_get_rx_depth
*
* Description:
*  Returns the RxFIFO depth 
* 
*******************************************************************************
*/
IFX_UINT8 ASC_ctrl_fifo_get_rx_depth( ASC_DEVICE ASC_device )
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  ASC_device = 0;
  
  /*Return h/w supportd receive FIFO width*/
  return ASC_HW_FIFO_RX;
}  
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_FIFO_GET_TX_DEPTH == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_fifo_get_tx_depth
*
* Description:
*  Returns the TxFIFO depth 
* 
*******************************************************************************
*/
IFX_UINT8 ASC_ctrl_fifo_get_tx_depth( ASC_DEVICE ASC_device )
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  ASC_device = 0;

  /*Return h/w supportd transmit FIFO width*/
  return ASC_HW_FIFO_TX;
}  
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_FIFO_SET_TX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_fifo_set_tx_level
*
* Description:
*  Sets the TxFIFO level at/below which a Transmit Buffer Empty
*  Interrupt will be generated. 
*
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_fifo_set_tx_level
(
  ASC_DEVICE ASC_device,
  IFX_UINT8 ASC_fifo_tx_lev_set
)
{     
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  #if ASC_HW_FIFO_TX == 0
  return ASC_ERR_NOT_SUPPORTED_HW;
  #else
  if ( (ASC_fifo_tx_lev_set > ASC_HW_FIFO_TX) || (ASC_fifo_tx_lev_set == 0) )
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  else
  {
    /*Program transmit FIFO interrupt trigger level*/
    WRITEBITS( ASC_HW_TXFCON( ASC_device ), ASC_fifo_tx_lev_set, 
      ASC_HW_TXFCON_TXFITL, ASC_HW_TXFCON_TXFITL_loc );
    return ASC_SUCCESS;
  }
  #endif
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_FIFO_SET_RX_LEVEL == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_fifo_set_rx_level
*
* Description:
*  Sets the RxFIFO level at/above which a Receive Buffer Full
*  Interrupt will be generated. 
* 
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_fifo_set_rx_level
(
  ASC_DEVICE ASC_device,
  IFX_UINT8 ASC_fifo_rx_lev_set
)
{     
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  #if ASC_HW_FIFO_RX == 0
  return ASC_ERR_NOT_SUPPORTED_HW;
  #else
  if ( (ASC_fifo_rx_lev_set > ASC_HW_FIFO_RX) || (ASC_fifo_rx_lev_set == 0) )
  {
    return ASC_ERR_NOT_SUPPORTED_HW;
  }
  else
  {
    /*Program receive FIFO interrupt trigger level*/
    WRITEBITS( ASC_HW_RXFCON( ASC_device ), ASC_fifo_rx_lev_set, 
      ASC_HW_RXFCON_RXFITL, ASC_HW_RXFCON_RXFITL_loc );
    return ASC_SUCCESS;
  }
  #endif
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_FLOW == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_flow
*
* Description:
*  Returns an Error since it is not supported in TC11IB 
* 
*******************************************************************************
*/

ASC_STATUS ASC_ctrl_flow
(
  ASC_DEVICE ASC_device,
  ASC_FLOW_CTRL_SETUP *ASC_ctrl_flow_settings
)
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  if(ASC_ctrl_flow_settings == NULL)
  {
    return ASC_ERR;
  }

  ASC_device = 0;
  ASC_ctrl_flow_settings = (ASC_FLOW_CTRL_SETUP *) 0;

  #if ASC_CFG_FLOW == 0
  return ASC_ERR_NOT_SUPPORTED;
  #else
  return ASC_ERR_NOT_SUPPORTED_HW;
  #endif
}
/*---------------------------------------------------------------------------*/
#endif




#if ASC_CFG_FUNC_CTRL_DISABLE == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_disable
*
* Description:
*  Disables the Module without terminating it. The peripheral is 
*  virtually disconnected. All the GPIO pins are set to input. 
*  The module cannot receive or transmit anything.
*  
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_disable (ASC_DEVICE ASC_device)
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /* Disable baud rate run time control bit  */
  RESET( ASC_HW_CON( ASC_device ), ASC_HW_CON_R);
  
  return ASC_SUCCESS;
}
/*---------------------------------------------------------------------------*/
#endif


#if ASC_CFG_FUNC_CTRL_ENABLE == 1
/*
*******************************************************************************
* Function Name:     ASC_ctrl_enable
*
* Description:
*  Enables the Module after ASC_ctrl_diasable. The GPIO config
*  and Receive Enable is restored.
*  
*******************************************************************************
*/
ASC_STATUS ASC_ctrl_enable (ASC_DEVICE ASC_device)
{
# if ASC_CFG_DEV_CHK == 1
  if (ASC_device >= ASC_HW_NUM)
  { 
    return ASC_ERR_UNKNOWN_DEV;
  }
# endif

# if ASC_CFG_INIT_CHK == 1
  if (ASC_initialised_flags [ASC_device] != 1)
  {
    return ASC_ERR_NOT_INITIALISED;
  }
# endif

  /* Enable baud rate run time control bit  */
  SET( ASC_HW_CON( ASC_device ), ASC_HW_CON_R);
  
  return ASC_SUCCESS ;
}
/*---------------------------------------------------------------------------*/
#endif

/*
*******************************************************************************
* Function Name:     ASC_TIR_ISR
*
* Description:
*  If the TxFIFO is enabled, the function checks if there is
*  space in the FIFO and writes data from the Application Buffer
*  to TBUF. If the FIFO is disabled, a single packet is written.
*  ( Provided there are transfers pending ).
*
*******************************************************************************
*/
void ASC_TIR_ISR (IFX_UINT8 ASC_device)
{
  IFX_UINT32 nLoop;

  if ( ASC_npackets2write[ ASC_device ] > 0 )
  { 
    #if ((ASC_HW_FIFO_TX > 0) && (ASC_CFG_TX_FIFO_LEVEL > 0)) 
    /*Get the number of empty locations in transmit FIFO*/
    nLoop = ASC_HW_FIFO_TX - READBITS( ASC_HW_FSTAT( ASC_device ), 
      ASC_HW_FSTAT_TXFFL, ASC_HW_FSTAT_TXFFL_loc );
    if ( nLoop > ASC_npackets2write[ ASC_device ] )
    {
      nLoop = ASC_npackets2write[ ASC_device ];
    }
    #else
    nLoop = 1; /*If FIFO are not enabled make empty location value as 1*/
    ASC_canwrite = 0; 
    /*If FIFOs are not enabled set flag that the transmit buffer is empty*/
    #endif

    /*Decrement the waiting pending data bytes by number of empty locations, 
    and write data to transmit buffer*/      
    ASC_npackets2write[ ASC_device ] = ASC_npackets2write[ ASC_device ]
       - nLoop;
    if ( ASC_mask[ ASC_device ] == 0x000001FF )
    {
      for (; nLoop > 0; nLoop-- )
      {
        WRITEBITS( ASC_HW_TBUF( ASC_device ), *ASC_writeto16[ ASC_device ], 
          ASC_mask[ ASC_device ], 0 );
        ASC_writeto16[ ASC_device ]++;
      }
    } 
    else
    {
      for (; nLoop > 0; nLoop-- )
      {
        WRITEBITS( ASC_HW_TBUF( ASC_device ), *ASC_writeto8[ ASC_device ], 
          ASC_mask[ ASC_device ], 0 );
        ASC_writeto8[ ASC_device ]++;
      }
    }

    /*If pending writes are zero call user call back function provided 
    pending write request support*/
    #if ASC_CFG_REQUEST_QUEUE_WR > 0
    if ( ASC_npackets2write[ ASC_device ] == 0 )
    {
      if ( ASC_pending_writes[ ASC_device ] > 0 )
      {
        ASC_writeq[ ASC_device ][ ASC_writeq_head[ ASC_device ] ]->
          ASC_return_num = ASC_writeq[ ASC_device ]
            [ ASC_writeq_head[ ASC_device ] ]->ASC_buffer_size;
        ASC_writeq[ ASC_device ][ ASC_writeq_head[ ASC_device ] ]->
          ASC_trans_ucb( ASC_writeq[ ASC_device ]
            [ ASC_writeq_head[ ASC_device ] ], ASC_SUCCESS) ;
        ASC_writeq_head[ ASC_device ]++;

        if ( ASC_writeq_head[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_WR )
        {
          ASC_writeq_head[ ASC_device ] = 0;
        }

        /*If still pending writes are in list move to the next 
        pending write request*/
        if ( ASC_pending_writes[ ASC_device ] > 1 )
        {
          ASC_npackets2write[ ASC_device ] = ASC_writeq[ ASC_device ]
            [ (ASC_writeq_head[ ASC_device ]) ]->ASC_buffer_size;
          ASC_writeto8[ ASC_device ] = (IFX_UINT8 *)(ASC_writeq[ ASC_device ]
            [ (ASC_writeq_head[ ASC_device ]) ]->ASC_buffer);
          ASC_writeto16[ ASC_device ] = (IFX_UINT16 *)(ASC_writeq[ ASC_device ]
            [ (ASC_writeq_head[ ASC_device ]) ]->ASC_buffer);
        }
        ASC_pending_writes[ ASC_device ]--;
      }
    }
    #endif

  } /* if ( ASC_npackets2write[ ASC_device ] > 0 ) */
  
  #if !((ASC_HW_FIFO_TX > 0) && (ASC_CFG_TX_FIFO_LEVEL > 0))
  ASC_canwrite = 1; 
  /*If FIFOs are not enabled set flag that the transmit buffer is empty*/
  #endif
}
/*---------------------------------------------------------------------------*/

/*
  NOTE, THE BODIES OF THE TIR AND TBIF ARE THE SAME
  WE MAY PUT THE BODIES IN A FUNCTION OR GIVE THE
  INTERRUPTS THE SAME ADDRESS IN THE TABLE.
  ONLY ONE SHOULD BE ENABLED AT ANY GIVEN TIME.
  IF 'TIR' IS USED, SUCCESS IS RETURNED ONLY AFTER
  THE DATA HAS ACTUALLY BEEN SENT ON THE LINE. BUT
  TIR MAKES THE SYSTEM SLOWER DUE TO FREQUENT INTERRUPTS.
*/

/*
*******************************************************************************
* Function Name:     ASC_TBIR_ISR
*
* Description:
*  If the TxFIFO is enabled, the function checks if there is
*  space in the FIFO and writes data from the Application Buffer
*  to TBUF. If the FIFO is disabled, a single packet is written.
*  ( Provided there are transfers pending ).
*
*******************************************************************************
*/
void ASC_TBIR_ISR (IFX_UINT8 ASC_device)
{
  IFX_UINT32 nLoop;
  if ( ASC_npackets2write[ ASC_device ] > 0 )
  { 
    #if ((ASC_HW_FIFO_TX > 0) && (ASC_CFG_TX_FIFO_LEVEL > 0)) 
    /*Get the number of empty locations in transmit FIFO*/
    nLoop = ASC_HW_FIFO_TX - READBITS( ASC_HW_FSTAT( ASC_device ), 
      ASC_HW_FSTAT_TXFFL, ASC_HW_FSTAT_TXFFL_loc );
    if ( nLoop > ASC_npackets2write[ ASC_device ] )
    {
      nLoop = ASC_npackets2write[ ASC_device ];
    }
    #else
    nLoop = 1; /*If FIFO are not enabled make empty location value as 1*/
    ASC_canwrite = 0; 
    /*If FIFOs are not enabled set flag that the transmit buffer is empty*/
    #endif

    /*Decrement the waiting pending data bytes by number of empty locations, 
    and write data to transmit buffer*/     
    ASC_npackets2write[ ASC_device ] = ASC_npackets2write[ ASC_device ]
       - nLoop;
    if ( ASC_mask[ ASC_device ] == 0x000001FF )
    {
      for (; nLoop > 0; nLoop-- )
      {
        WRITEBITS( ASC_HW_TBUF( ASC_device ), *ASC_writeto16[ ASC_device ], 
          ASC_mask[ ASC_device ], 0 );
        ASC_writeto16[ ASC_device ]++;
      }
    } 
    else
    {
      for (; nLoop > 0; nLoop-- )
      {
        WRITEBITS( ASC_HW_TBUF( ASC_device ), *ASC_writeto8[ ASC_device ], 
          ASC_mask[ ASC_device ], 0 );
        ASC_writeto8[ ASC_device ]++;
      }
    }

    /*If pending writes are zero call user call back function provided 
    pending write request support*/
    #if ASC_CFG_REQUEST_QUEUE_WR > 0
    if ( ASC_npackets2write[ ASC_device ] == 0 )
    {
      if ( ASC_pending_writes[ ASC_device ] > 0 )
      {
        ASC_writeq[ ASC_device ][ ASC_writeq_head[ ASC_device ] ]->
          ASC_return_num = ASC_writeq[ ASC_device ]
            [ ASC_writeq_head[ ASC_device ] ]->ASC_buffer_size;
        ASC_writeq[ ASC_device ][ ASC_writeq_head[ ASC_device ] ]->
          ASC_trans_ucb( ASC_writeq[ ASC_device ]
            [ ASC_writeq_head[ ASC_device ] ], ASC_SUCCESS) ;
        ASC_writeq_head[ ASC_device ]++;

        if ( ASC_writeq_head[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_WR )
        {
          ASC_writeq_head[ ASC_device ] = 0;
        }

        /*If still pending writes are in list move to the next 
        pending write request*/
        if ( ASC_pending_writes[ ASC_device ] > 1 )
        {
          ASC_npackets2write[ ASC_device ] = ASC_writeq[ ASC_device ]
            [ (ASC_writeq_head[ ASC_device ]) ]->ASC_buffer_size;
          ASC_writeto8[ ASC_device ] = (IFX_UINT8 *)(ASC_writeq[ ASC_device ]
            [ (ASC_writeq_head[ ASC_device ]) ]->ASC_buffer);
          ASC_writeto16[ ASC_device ] = (IFX_UINT16 *)(ASC_writeq[ ASC_device ]
            [ (ASC_writeq_head[ ASC_device ]) ]->ASC_buffer);
        }
        ASC_pending_writes[ ASC_device ]--;
      }
    }
    #endif

  } /* if ( ASC_npackets2write[ ASC_device ] > 0 ) */
  
  #if !((ASC_HW_FIFO_TX > 0) && (ASC_CFG_TX_FIFO_LEVEL > 0))
  ASC_canwrite = 1; 
  /*If FIFOs are not enabled set flag that the transmit buffer is empty*/
  #endif
}
/*---------------------------------------------------------------------------*/


/*
*******************************************************************************
* Function Name:     ASC_EIR_ISR
*
* Description:
*  The data before the faulty/corrupt data is moved to the
*  Application Buffer ( if some transfer is pending ) or to
*  the HAL Circular Buffer. The faulty packet is flushed out.
*
*******************************************************************************
*/

void ASC_EIR_ISR (IFX_UINT8 ASC_device)
{

  IFX_UINT32  nLoop = 0, nBuffLoop = 0;
  IFX_UINT32  nErrorFlags = 0;
  ASC_STATUS Error = ASC_ERR;

  /* Determine the cause of the error */
  nErrorFlags = READBITS( ASC_HW_CON( ASC_device ), ASC_HW_CON_ERRORS, 
    ASC_HW_CON_ERRORS_loc );

  /* Clear the error flags */
  #if ASC_HW_WHB_REG == 0
  WRITEBITS( ASC_HW_CON( ASC_device ), 0, ASC_HW_CON_ERRORS, 
    ASC_HW_CON_ERRORS_loc ); 
  #else
  WRITEBITS( ASC_HW_WHB_CON( ASC_device ), 0, ASC_HW_WHB_ERRORS, 
    ASC_HW_WHB_ERRORS_loc ); 
  #endif /*ASC_HW_WHB_REG*/

  /*Read the number of data bytes in receive FIFO*/
  #if ((ASC_HW_FIFO_RX > 0) && (ASC_CFG_RX_FIFO_LEVEL > 0))
  nLoop = READBITS( ASC_HW_FSTAT( ASC_device ), ASC_HW_FSTAT_RXFFL, 
    ASC_HW_FSTAT_RXFFL_loc );
  #else
  nLoop = 1; /*If no FIFOs are available make the number of bytes value as 1*/
  #endif

  /*Define an error from control register value*/
  if ( nErrorFlags > 3 )
  {
    Error = ASC_ERR_OVR;
  }
  else if ( nErrorFlags > 1)
  { 
    Error = ASC_ERR_FRAME;
  }
  else
  {
    Error = ASC_ERR_PARITY;
  }

  /*Increment the statistics counters depend upon error condition*/
  #if ASC_CFG_STAT_LOG == 1
  ASC_successful[ ASC_device ] = ASC_successful[ ASC_device ] + nLoop;

  if ( Error == ASC_ERR_OVR )
  {
    ASC_ovr_errs[ ASC_device ]++;
  }
  else if ( Error == ASC_ERR_FRAME )
  { 
    ASC_frame_errs[ ASC_device ]++;
  }
  else
  {
    ASC_parity_errs[ ASC_device ]++;
  }
  #endif /*ASC_CFG_STAT_LOG*/


  if( (ASC_mode[ASC_device] == ASC_SYNC_R) || (ASC_mode[ASC_device] == 
    ASC_SYNC_T))
  {
  #if ASC_HW_WHB_REG == 0
  SET(ASC_HW_CON(ASC_device), ASC_HW_CON_REN); 
  #else
  SET(ASC_HW_WHB_CON(ASC_device), ASC_HW_WHB_SET_REN_loc);
  #endif  
  }

  /*Find the number of bytes to be written to pending read requests, 
  if available else write into read buffer*/ 
  if(ASC_npackets2read[ASC_device] > 0)
  {
    if ( nLoop > ASC_npackets2read[ ASC_device ] )
    {
      nBuffLoop = nLoop - ASC_npackets2read[ ASC_device ];
      nLoop = ASC_npackets2read[ ASC_device ];
    }
    ASC_npackets2read[ASC_device] = ASC_npackets2read[ASC_device] - nLoop; 
  }
  else
  {
    nBuffLoop = nLoop;
    nLoop = 0;
  }

  if(nLoop > 0)
  {
    /*Update status of pending read request*/
    /*If pending read requests are in queue read the data from IO ports to 
    pending read request*/
    ASC_read_status[ ASC_device ][ (ASC_readq_head[ ASC_device ]) ] = Error;
    ASC_error_msg[ ASC_device ] = Error;
    if ( ASC_mask[ ASC_device ] == 0x000001FF )
    {
      for (; nLoop > 0; nLoop-- )
      {
        *ASC_readfrom16[ ASC_device ] = READBITS( ASC_HW_RBUF( ASC_device ), 
          ASC_mask[ ASC_device ], 0 );
        ASC_readfrom16[ ASC_device ] ++;
      }
    }
    else
    {
      for (; nLoop > 0; nLoop-- )
      {  
        *ASC_readfrom8[ ASC_device ] = READBITS( ASC_HW_RBUF( ASC_device ), 
          ASC_mask[ ASC_device ], 0 );
        ASC_readfrom8[ ASC_device ]++;
      }
    }

  }

  /*If no pending read request write the data to read buffer and 
  update it status queue*/
  if(nBuffLoop > 0)
  {
    ASC_rdbuff_stat[ ASC_device ] = Error;

    for(; nBuffLoop > 0; nBuffLoop--)
    {
      ASC_rdbuff[ASC_device][ASC_rdbuff_wrptr[ASC_device]++] = 
        READBITS( ASC_HW_RBUF( ASC_device ), ASC_mask[ ASC_device ], 0 );
      ASC_rdfill_size[ASC_device]++;

      if(ASC_rdbuff_wrptr[ASC_device] >= ASC_CFG_RDBUFF_SIZE)
      {
        ASC_rdbuff_wrptr[ASC_device] = 0;
      }

      if(ASC_rdfill_size[ASC_device] >= ASC_CFG_RDBUFF_SIZE)
      {
        ASC_rdfill_size[ASC_device] = ASC_CFG_RDBUFF_SIZE;
      }
    }
  }
  
  /*If number of pending bytes is zero call user call back function provided
    the pending request support user call back function.
  */  
  #if ASC_CFG_REQUEST_QUEUE_RD > 0
  if ( ASC_npackets2read[ ASC_device ] == 0 )
  { 
    if ( ASC_pending_reads[ ASC_device ] > 0 )
    {
      /*Update global variables*/ 
      nLoop = ASC_readq_head[ ASC_device ];
      ASC_readq[ ASC_device ][ nLoop ]->ASC_return_num = 
        ASC_readq[ ASC_device ][ nLoop ]->ASC_buffer_size;
      ASC_readq[ ASC_device ][ nLoop ]->ASC_trans_ucb( ASC_readq[ ASC_device ]
        [ nLoop ], ASC_read_status[ ASC_device ][ nLoop ]) ;
      ASC_readq_head[ ASC_device ] = ASC_readq_head[ ASC_device ] + 1;
     
      if ( ASC_readq_head[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_RD )
      {
        ASC_readq_head[ ASC_device ] = 0;
      }
  
   /* 
     If there is another transfer pending, move to the next pending 
     read request
   */
      if ( ASC_pending_reads[ ASC_device ] > 1 )
      {
        ASC_npackets2read[ ASC_device ] = ASC_readq[ ASC_device ]
          [ ASC_readq_head[ ASC_device ] ]->ASC_buffer_size;
        ASC_readfrom8[ ASC_device ] = (IFX_UINT8 *)(ASC_readq[ ASC_device ]
          [ ASC_readq_head[ ASC_device ] ]->ASC_buffer);
        ASC_readfrom16[ ASC_device ] = (IFX_UINT16 *)(ASC_readq[ ASC_device ]
          [ ASC_readq_head[ ASC_device ] ]->ASC_buffer);
      }
      ASC_pending_reads[ ASC_device ]--;
    }
  }  /* if ( ASC_npackets2read[ ASC_device ] == 0 ) */
  #endif /* #if ASC_CFG_REQUEST_QUEUE_RD > 0 */
}
/*---------------------------------------------------------------------------*/


/*
*******************************************************************************
* Function Name:     ASC_RIR_ISR
*
* Description:
*  If there are transfers pending the incoming data is moved
*  to the Application Buffer. Otherwise it is simply written
*  to HAL circular buffer ( if enabled ).
*
*******************************************************************************
*/
void ASC_RIR_ISR (IFX_UINT8 ASC_device)
{
  IFX_UINT32 nLoop = 0, nBuffLoop = 0;
  
  /*Find the number of bytes to be read from Rx FIFO*/
  #if ((ASC_HW_FIFO_RX > 0) && (ASC_CFG_RX_FIFO_LEVEL > 0))
  nLoop = READBITS( ASC_HW_FSTAT( ASC_device ), ASC_HW_FSTAT_RXFFL, 
    ASC_HW_FSTAT_RXFFL_loc );
  #else
  nLoop = 1; 
  /*If FIFOs are not enabled make the number of bytes to be read as zero*/
  #endif

  /*If error condition occurs return from this ISR and 
  read data from error ISR*/
  if ( READBITS( ASC_HW_ESRC( ASC_device ), 0x00002000, ASC_HW_SRC_SRR ) == 1 )
     return;

  /*The following flag indicates the interrupt is caused by s/w by 
  setting SETR bit. */
  if(ASC_intr_flag[ ASC_device ] == 1)
  {
    nLoop = 0;
    ASC_intr_flag[ ASC_device ] = 0;
  }

  #if ASC_CFG_STAT_LOG == 1
  ASC_successful[ ASC_device ] = ASC_successful[ ASC_device ] + nLoop;
  #endif

  if( (ASC_mode[ASC_device] == ASC_SYNC_R) || (ASC_mode[ASC_device] == 
    ASC_SYNC_T))
  {
  #if ASC_HW_WHB_REG == 0
  SET(ASC_HW_CON(ASC_device), ASC_HW_CON_REN); 
  #else
  SET(ASC_HW_WHB_CON(ASC_device), ASC_HW_WHB_SET_REN_loc);
  #endif  
  }

  if( ( ASC_npackets2read[ ASC_device ] > 0 ))
  {
    /*If read buffer already have some data, read the data from read buffer to 
    pending read request*/
    if(ASC_rdfill_size[ASC_device] > 0)
    {
      nBuffLoop = ASC_rdfill_size[ASC_device];
      if(nBuffLoop > ASC_npackets2read[ASC_device])
      {
        nBuffLoop = ASC_npackets2read[ASC_device];
      }
      ASC_npackets2read[ASC_device] = ASC_npackets2read[ ASC_device ] 
        - nBuffLoop;
      ASC_error_msg[ ASC_device ] = ASC_rdbuff_stat[ ASC_device ];
      ASC_read_status[ ASC_device ][ nLoop ] = ASC_rdbuff_stat[ ASC_device ];
      
      if (ASC_mask[ ASC_device ] == 0x000001FF )
      {
        for (; nBuffLoop > 0; nBuffLoop-- )
        {
          *ASC_readfrom16[ ASC_device ] = (IFX_UINT16)(ASC_rdbuff[ASC_device]
            [ASC_rdbuff_rdptr[ASC_device]++]);
          ASC_readfrom16[ ASC_device ] ++;
          ASC_rdfill_size[ASC_device]--;
          if(ASC_rdbuff_rdptr[ASC_device] > ASC_CFG_RDBUFF_SIZE )
          {
            ASC_rdbuff_rdptr[ASC_device] = 0;
          }
          if(ASC_rdfill_size[ASC_device] <= 0)
          {
            ASC_rdfill_size[ASC_device] = 0;
            ASC_rdbuff_stat[ ASC_device ] = ASC_SUCCESS;
          }
        }
      }
      else
      {
        for (; nBuffLoop > 0; nBuffLoop-- )
        {  
          *ASC_readfrom8[ ASC_device ] =(IFX_UINT8)(ASC_rdbuff[ASC_device]
            [ASC_rdbuff_rdptr[ASC_device]++]);
          ASC_readfrom8[ ASC_device ]++;
          ASC_rdfill_size[ASC_device]--;
          if(ASC_rdbuff_rdptr[ASC_device] > ASC_CFG_RDBUFF_SIZE )
          {
            ASC_rdbuff_rdptr[ASC_device] = 0;
          }
          if(ASC_rdfill_size[ASC_device] <= 0)
          {
            ASC_rdfill_size[ASC_device] = 0;
          }
        }
      }
    } 

    /*Reamaining pending read request bytes read from Io ports. 
    Some times ports may not have any data because in ASC_read API driver is 
    raising software interrupt */
    if ( nLoop > ASC_npackets2read[ ASC_device ] )
    {
      nLoop = ASC_npackets2read[ ASC_device ];
      nBuffLoop = nLoop - ASC_npackets2read[ASC_device];
    }
    ASC_npackets2read[ ASC_device ] = ASC_npackets2read[ ASC_device ] - nLoop;
    
    /*Read data from IO ports to pending read request */
    if ( ASC_mask[ ASC_device ] == 0x000001FF )
    {
      for (; nLoop > 0; nLoop-- )
      {
        *ASC_readfrom16[ ASC_device ] = READBITS( ASC_HW_RBUF( ASC_device ), 
          ASC_mask[ ASC_device ], 0 );
        ASC_readfrom16[ ASC_device ] ++;
      }
    }
    else
    {
      for (; nLoop > 0; nLoop-- )
      {  
        *ASC_readfrom8[ ASC_device ] = READBITS( ASC_HW_RBUF( ASC_device ), 
          ASC_mask[ ASC_device ], 0 );
        ASC_readfrom8[ ASC_device ]++;
      }
    }

    /*Read the remaining data bytes from IO ports to read buffer*/ 
    if(nBuffLoop > 0)
    {
       for(; nBuffLoop > 0; nBuffLoop--)
       {
         ASC_rdbuff[ASC_device][ASC_rdbuff_wrptr[ASC_device]++] = 
           READBITS( ASC_HW_RBUF( ASC_device ), ASC_mask[ ASC_device ], 0 );
         ASC_rdfill_size[ASC_device]++;
         if(ASC_rdbuff_wrptr[ASC_device] >= ASC_CFG_RDBUFF_SIZE)
         {
            ASC_rdbuff_wrptr[ASC_device] = 0;
         }
         if(ASC_rdfill_size[ASC_device] >= ASC_CFG_RDBUFF_SIZE)
         {
           ASC_rdfill_size[ASC_device] = ASC_CFG_RDBUFF_SIZE;
         }
       }
    }
  } /* if ( ASC_npackets2read[ ASC_device ] > 0 ) */
  else  /*If no pending read requests read data to read buffer*/
  {
    for(;nLoop>0; nLoop--)
    {
      ASC_rdbuff[ASC_device][ASC_rdbuff_wrptr[ASC_device]++] = 
        READBITS( ASC_HW_RBUF( ASC_device ), ASC_mask[ ASC_device ], 0 );
      ASC_rdfill_size[ASC_device]++;
      if(ASC_rdbuff_wrptr[ASC_device] >= ASC_CFG_RDBUFF_SIZE )
      {
        ASC_rdbuff_wrptr[ASC_device] = 0;
      }
      if(ASC_rdfill_size[ASC_device] >= ASC_CFG_RDBUFF_SIZE)
      {
        ASC_rdfill_size[ASC_device] = ASC_CFG_RDBUFF_SIZE;
      }
    }
  }
  
   /*If number of pending bytes is zero call user call back function provided
     the pending request support user call back function.
   */  
    #if ASC_CFG_REQUEST_QUEUE_RD > 0
    if ( ASC_npackets2read[ ASC_device ] == 0 )
    { 
      if ( ASC_pending_reads[ ASC_device ] > 0 )
      {
        /*Update global variable*/
        nLoop = ASC_readq_head[ ASC_device ];
        ASC_readq[ ASC_device ][ nLoop ]->ASC_return_num = 
          ASC_readq[ ASC_device ][ nLoop ]->ASC_buffer_size;
        ASC_readq[ ASC_device ][ nLoop ]->
          ASC_trans_ucb( ASC_readq[ ASC_device ][ nLoop ], 
            ASC_read_status[ ASC_device ][ nLoop ]) ;

        ASC_readq_head[ ASC_device ] = ASC_readq_head[ ASC_device ] + 1;
        if ( ASC_readq_head[ ASC_device ] == ASC_CFG_REQUEST_QUEUE_RD )
        {
          ASC_readq_head[ ASC_device ] = 0;
        }
      
        /* 
         If there is another transfer pending, move to the next 
         pending read request
        */
        if ( ASC_pending_reads[ ASC_device ] > 1 )
        {
          ASC_npackets2read[ ASC_device ] = ASC_readq[ ASC_device ]
            [ ASC_readq_head[ ASC_device ] ]->ASC_buffer_size;
          ASC_readfrom8[ ASC_device ] = (IFX_UINT8 *)(ASC_readq[ ASC_device ]
            [ ASC_readq_head[ ASC_device ] ]->ASC_buffer);
          ASC_readfrom16[ ASC_device ] = (IFX_UINT16 *)(ASC_readq[ ASC_device ]
            [ ASC_readq_head[ ASC_device ] ]->ASC_buffer);
        }
        ASC_pending_reads[ ASC_device ]--;
      }
    }  /* if ( ASC_npackets2read[ ASC_device ] == 0 ) */
    #endif /* #if ASC_CFG_REQUEST_QUEUE_RD > 0 */
}



/*---------------------------------------------------------------------------*/



                           
