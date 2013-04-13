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
** @FILENAME@:       sys_api.h
** @VERSION@:        3.0
** @DATE@:           17/01/2006    
**
** =============================================================================
**
** Project: TC1130
** Block: SYS HAL 
**
** =============================================================================
** Contents: Implements system definitions for the application interface.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby          Release after code review.
**
** @CHANGE_HISTORY@
** =============================================================================
*/

 /* @doc API */

#ifndef __SYS_API_H
#define __SYS_API_H

#include "compiler.h"
/*
  @def  TC1130  | Controller type, 
  this defines TC1130 to 1
*/
#define TC1130  1



/*
  @def  SYS_PRODUCT  | Controller type, 
  this define allows the user to select the type of the 
  microcontroller. 
*/
#define SYS_PRODUCT  TC1130


#define SYS_CFG_PULL_ENBL 1 

#define SYS_NUM_PORTS     5

#define SYS_PORT_BASE     0xF0000C00

#define SYS_DATA_OUT     0x10  /*Data in register offset */
#define SYS_DATA_IN      0x14  /*Data in register offset */
#define SYS_DIR          0x18  /*Direction register offset */
#define SYS_OD           0x1C  /*Open drain control register */
#define SYS_PUDSEL       0x28
#define SYS_PUDEN        0x2C
#define SYS_ALTSEL0      0x44  /*Alternate select 0 register */
#define SYS_ALTSEL1      0x48  /*Alternate select 1 register */


#define SYS_PIN_CFG           8 

#define SYS_OSC_CON          (*(IFX_VUINT32 *)(0xF0000018))  
#define SYS_WDT_CON0         (*(IFX_VUINT32 *)(0xF0000020))  
#define SYS_WDT_CON1         (*(IFX_VUINT32 *)(0xF0000024))  
#define SYS_PORT_OFFSET      0x100
#define SYS_PLL_CLC          (*(IFX_VUINT32 *)(0xF0000040))
#define SYS_SCU_CON          (*(IFX_VUINT32 *)(0xF0000050))
#define SYS_PMI_CON0          (*(IFX_VUINT32 *)(0xF87FFD10))   

#define SYS_PLL_CLC_KDIV_loc    8
#define SYS_PLL_CLC_PDIV_loc    13
#define SYS_PLL_CLC_NDIV_loc    16
#define SYS_PLL_CLC_SYSFSL_loc  2
#define SYS_PLL_CLC_VCOBYP_loc  5

#define SYS_PLL_CLC_VCOBYP_MASK  0x00000020


extern IFX_UINT16 SYS_port_base[SYS_NUM_PORTS];
extern IFX_UINT32 SYS_clk_init;

#define SYS_SET   1
#define SYS_RST   0

/*
  @enum SYS_STATUS | SYS HAL Status Enumeration
  @comm The SYS_STATUS enum constants return the status from the SYS HAL functions.
*/
typedef enum
{
  SYS_GPIO_ERR, /*@emem SYS_GPIO_ERR indicates a problem in the allocation of GPIO ports. */
  SYS_PRTY_ERR, /*@emem SYS_PRTY_ERR indicates a problem in the allocation of interrupt priority. */
  SYS_CLK_ERR,  /*@emem SYS_CLK_ERR indicates a problem in the clock setting. */
  SYS_SUCCESS   /*@emem SYS_SUCCESS indicates that an operation completed successfully. */
}SYS_STATUS;


/*
  @enum SYS_TRANS_MODE |
  Depending upon the system the HAL is operating in there may be several different
  options available regarding data transfers. Some systems have a DMA controller
  available, others have a PCP, some have both of these and some have neither. The
  system HAL provides constants which can be used to specify the desired data transfer
  option, the typedef name SYS_TRANS_MODE is used wherever such a constant is
  expected.
  The data transfer option must be initialised in the SSC_TRANSFER structure passed to
  the SSC_read and SSC_write API functions. If the transfer operation is not available in
  the system then SSC_ERR_NOT_SUPPORTED_HW will be returned. 
*/
typedef enum
{
  SYS_TRNS_DMA,     /*@emem Use the DMA controller to move the data*/
  SYS_TRNS_PCP,     /*@emem Use the PCP to manage the transfer*/
  SYS_TRNS_MCU_INT, /*@emem Use the microcontroller unit to manage the transfer using interrupts.*/
  SYS_TRNS_MCU      /*@emem Use the microcontroller unit to manage the transfer by polling the SSC peripheral.*/
} SYS_TRANS_MODE;

#define SYS_HW_CLC_RMC     0x0000FF00
#define SYS_HW_CLC_RMC_loc 8


#define SYS_portreg(reg_val) (*(IFX_VUINT32 *)(reg_val))
#define SYS_WRITE_REG(SYS_addr, SYS_pos, SYS_val)  SYS_portreg(SYS_addr) = SYS_portreg(SYS_addr) | ((SYS_val) << (SYS_pos))
#define SYS_WRITEBITS(reg,value,mask,location) (reg = (reg & (~mask)) | (value << location))


/* Below are marcos to access the protected area in superviosry mode. Note that
 * instruction  "isync" was required for pipeline coherency.
 */
#define SYS_WDT_PASSWORD_ACCESS \
do \
{ \
  IFX_ULONG wcon0, wcon1; \
  wcon0 = SYS_WDT_CON0; \
  wcon1 = SYS_WDT_CON1; \
  wcon0 &= 0xFFFFFF01; \
  wcon0 |= 0xF0; \
  wcon0 |= (wcon1 & 0xc); \
  IFX_ISYNC(); \
  SYS_WDT_CON0 = wcon0; \
}while(0)

#define SYS_WDT_MODIFY_ACCESS \
do \
{  \
  IFX_ULONG wcon0; \
  wcon0 = SYS_WDT_CON0; \
  wcon0 &= 0xFFFFFFF0; \
  wcon0 |= 2; \
  IFX_ISYNC(); \
  SYS_WDT_CON0 = wcon0; \
  wcon0 = SYS_WDT_CON0 ; \
}while(0)

#define SYS_WDT_LOCK_ACCESS \
do \
{ \
  IFX_ULONG wcon0, wcon1; \
  wcon0 = SYS_WDT_CON0; \
  wcon1 = SYS_WDT_CON1; \
  wcon0 &= 0xFFFFFFF0; \
  wcon0 |= 3; \
  IFX_ISYNC(); \
  SYS_WDT_CON0 = wcon0; \
  wcon0 = SYS_WDT_CON0 ; \
}while(0)

/* Macros for protected registers */
#define UNLOCK_ENDINIT_PROTECT {	\
									SYS_WDT_PASSWORD_ACCESS; \
									SYS_WDT_MODIFY_ACCESS; \
							  	}


#define LOCK_ENDINIT_PROTECT {	\
								SYS_WDT_PASSWORD_ACCESS; \
								SYS_WDT_LOCK_ACCESS; \
							  }

/* 
   @topic2 SYS HAL API Functions |
   @func GPIO Port allocation function,
   this function allocates the ports as defined by the user in the 
   SYS CFG file. If the ports which the user wants to configure 
   are already used by another peripheral, the function returns
   error, else if there are no conflicts, it returns SYS_SUCCESS
   @head4: (DESIGN) Implementation Details |
   @flag | - Check if the user settings are not conflicting with any other peripheral or not,
             if conflicting return error.
   @flag | - If the register settings are legal, program the register settings in the GPIO
             else return an error.
   @retval  Returns SYS_STATUS
*/
SYS_STATUS SYS_gpio_alloc(
  IFX_SINT32 SYS_port,    /* @parm GPIO Port number */ 
  IFX_SINT32 SYS_pin,     /* @parm GPIO Port lines */ 
  IFX_SINT32 SYS_dir,     /* @parm Value to be programmed in the GPIO Port Dir register*/ 
  IFX_SINT32 SYS_altsel0, /* @parm Value to be programmed in the GPIO Port Altsel0 register*/ 
  IFX_SINT32 SYS_altsel1, /* @parm Value to be programmed in the GPIO Port Altsel1 register*/ 
  IFX_SINT32 SYS_od,      /* @parm Value to be programmed in the GPIO Open drain control register*/   
  IFX_SINT32 SYS_pudsel,  /* @parm Value to be programmed in the GPIO Pull-up/Pull-down select register*/ 
  IFX_SINT32 SYS_puden    /* @parm Value to be programmed in the GPIO Pull-up/Pull-down enable register*/ 
);

/* 
   @func GPIO Port free function,
   this function frees the ports which were allocated by the 
   SYS_GPIO_alloc() function.
   @head4: (DESIGN) Implementation Details |
   @flag | - This function frees the ports allocated by the SYS_gpio_alloc() function
   @retval  Returns SYS_STATUS
*/
SYS_STATUS SYS_gpio_free(
  IFX_SINT32 SYS_port,    /* @parm GPIO Port number */ 
  IFX_SINT32 SYS_pin,     /* @parm GPIO Port lines */ 
  IFX_SINT32 SYS_dir,     /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel0, /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel1, /* @parm Ignored */ 
  IFX_SINT32 SYS_od,      /* @parm Ignored */ 
  IFX_SINT32 SYS_pudsel,  /* @parm Ignored */ 
  IFX_SINT32 SYS_puden    /* @parm Ignored */ 
);


/* 
   @func GPIO Port number return function,
   this function returns port number is being used.
   @retval  Returns port number
*/
IFX_SINT32 SYS_gpio_get_port(
  IFX_SINT32 SYS_port,    /* @parm GPIO Port number */ 
  IFX_SINT32 SYS_pin,     /* @parm GPIO Port lines */ 
  IFX_SINT32 SYS_dir,     /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel0, /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel1, /* @parm Ignored */ 
  IFX_SINT32 SYS_od,      /* @parm Ignored */ 
  IFX_SINT32 SYS_pudsel,  /* @parm Ignored */ 
  IFX_SINT32 SYS_puden    /* @parm Ignored */ 
);

/* 
   @func GPIO port line (pin number) return function,
   this function returns port line (pin number) is being used.
   @retval  Returns port line (pin number).
*/
IFX_SINT32 SYS_gpio_get_pin_num(
  IFX_SINT32 SYS_port,    /* @parm GPIO Port number */ 
  IFX_SINT32 SYS_pin,     /* @parm GPIO Port lines */ 
  IFX_SINT32 SYS_dir,     /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel0, /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel1, /* @parm Ignored */ 
  IFX_SINT32 SYS_od,      /* @parm Ignored */ 
  IFX_SINT32 SYS_pudsel,  /* @parm Ignored */ 
  IFX_SINT32 SYS_puden    /* @parm Ignored */ 
);


/*
  @func Clock initialisation function,
  this function initialises the system clock by programming PLL_CLC register.
  For 20MHz external crystal oscillator it output 95MHz frequency, by using 
  NDIV = 38, KDIV = 8 and PDIV = 1 values.
*/
IFX_UINT32 SYS_clk_initialise(void);



#endif /*__SYS_API_H*/


