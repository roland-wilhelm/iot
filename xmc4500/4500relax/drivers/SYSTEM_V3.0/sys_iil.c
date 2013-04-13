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
** @FILENAME@:       sys_iil.c
** @VERSION@:        3.0
** @DATE@:           17/01/2006   
**
** =============================================================================
**
** Project: TC1130
** Block:  SYS HAL
**
** =============================================================================
** Contents: Implements system interfaces.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby          Release after code review.
** 07/05/2004      Ranaga                To support TC1130-B step 
**                                       redesigned SYS_clk_initialise API.       
**
** 08/02/2004      Mahesh                Code changed in SYS_clk_initialise API
**                                       according to 'Ursula Kelling' inputs. 
**
** 15/04/2005	   Ronny		 Enable code cache in PMI con per default	
**
** @CHANGE_HISTORY@
** =============================================================================
*/
#include "sys_cfg.h"
#include "sys_api.h"      


IFX_UINT16 SYS_port_base[SYS_NUM_PORTS] = {0};



/*==========================================================================
* Function Name ::     SYS_gpio_free
*
* Purpose       :: 
*  This function frees the ports allocated by the SYS_gpio_alloc() function
*
* Input ::
*   SYS_port    GPIO Port number
*   SYS_pin     GPIO Port lines 
*   SYS_dir     Ignored
*   SYS_altsel0 Ignored
*   SYS_altsel1 Ignored
*   SYS_pudsel  Ignored
*   SYS_puden   Ignored
*   SYS_od      Ignored
*
* Output :: None
*
* Return Value  ::      Success or Failure
*
*==========================================================================*/
SYS_STATUS SYS_gpio_free(
  IFX_SINT32 SYS_port,
  IFX_SINT32 SYS_pin,
  IFX_SINT32 SYS_dir,
  IFX_SINT32 SYS_altsel0,
  IFX_SINT32 SYS_altsel1,
  IFX_SINT32 SYS_od,
  IFX_SINT32 SYS_pudsel,
  IFX_SINT32 SYS_puden
)
{
  if( (SYS_port_base[SYS_port] & (0x0001 <<  SYS_pin)) >= 1 )
  {
    SYS_port_base[SYS_port] &=  ~(0x0001 << SYS_pin); 
  }
  else
  {
    return SYS_GPIO_ERR;
  }
  SYS_dir = SYS_altsel0 = SYS_altsel1 = SYS_pudsel = SYS_puden = SYS_od = 0;
  return SYS_SUCCESS;
}




/*==========================================================================
 * Function Name :: SYS_gpio_alloc()
 *
 * Purpose       :: 
 *  This function allocates the ports as defined by the user in the SYS CFG 
 *  file. If the ports which the user wants to configure are already used by 
 *  another peripheral, the function returns error, else if there are no 
 *  conflicts, it returns SYS_SUCCESS.
 *
 * Input         :: none
 *   SYS_port    GPIO Port number
 *   SYS_pin     GPIO Port lines 
 *   SYS_dir     Value to be programmed in the GPIO Port Dir register
 *   SYS_altsel0 Value to be programmed in the GPIO Port Altsel0 register
 *   SYS_altsel1 Value to be programmed in the GPIO Port Altsel1 register
 *   SYS_pudsel  Value to be programmed in the GPIO Pull-up/Pull-down select 
 *               register 
 *   SYS_puden   Value to be programmed in the GPIO Pull-up/Pull-down enable 
 *               register
 *   SYS_od      Value to be programmed in the GPIO Open drain control register 
 *
 * Output        :: None.
 *
 * Return Value  :: Success or Failure
 *
 *==========================================================================*/

SYS_STATUS SYS_gpio_alloc(
  IFX_SINT32 SYS_port,
  IFX_SINT32 SYS_pin,
  IFX_SINT32 SYS_dir,
  IFX_SINT32 SYS_altsel0,
  IFX_SINT32 SYS_altsel1,
  IFX_SINT32 SYS_od,
  IFX_SINT32 SYS_pudsel,
  IFX_SINT32 SYS_puden
)
{
  if( (SYS_port_base[SYS_port] >> SYS_pin == 1 ) || (SYS_port >= SYS_NUM_PORTS) )
  {
    return SYS_GPIO_ERR;
  }

  if(SYS_dir == 0 || SYS_dir == 1)
  {       
    SYS_WRITE_REG(((SYS_PORT_BASE + (SYS_port * SYS_PORT_OFFSET))+SYS_DIR),
    SYS_pin,SYS_dir);
  }

  if(SYS_altsel0 == 0 || SYS_altsel0 == 1)
  {
    SYS_WRITE_REG(((SYS_PORT_BASE + (SYS_port * SYS_PORT_OFFSET))+SYS_ALTSEL0),
    SYS_pin,SYS_altsel0);
  }
  if(SYS_altsel1 == 0 || SYS_altsel1 == 1)
  {
    SYS_WRITE_REG(((SYS_PORT_BASE + (SYS_port * SYS_PORT_OFFSET))+SYS_ALTSEL1),
    SYS_pin,SYS_altsel1);
  }
  if(SYS_od == 0 || SYS_od == 1)
  {
    SYS_WRITE_REG(((SYS_PORT_BASE + (SYS_port * SYS_PORT_OFFSET))+SYS_OD),
    SYS_pin,SYS_od);
  }

#if SYS_CFG_PULL_ENBL == 1
  if(SYS_pudsel == 0 || SYS_pudsel == 1)
  {
    SYS_WRITE_REG(((SYS_PORT_BASE + (SYS_port * SYS_PORT_OFFSET))+SYS_PUDSEL),
    SYS_pin,SYS_pudsel);
  }
  if(SYS_puden == 0 || SYS_puden == 1)
  {
    SYS_WRITE_REG(((SYS_PORT_BASE + (SYS_port * SYS_PORT_OFFSET))+SYS_PUDEN),
    SYS_pin,SYS_puden);
  }
#endif

  SYS_port_base[SYS_port] |=  (1 << SYS_pin);

  return SYS_SUCCESS;
}



/*==========================================================================
 * Function Name :: SYS_gpio_get_pin_num()
 *
 * Purpose       :: Gives port number
 *
 * Input         :: none
 *					
 * Output        :: None.
 *
 * Return Value  :: Returns port number.
 *
 *==========================================================================*/
IFX_SINT32 SYS_gpio_get_port(
  IFX_SINT32 SYS_port,    /* @parm GPIO Port number */ 
  IFX_SINT32 SYS_pin,     /* @parm GPIO Port lines */ 
  IFX_SINT32 SYS_dir,     /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel0, /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel1, /* @parm Ignored */ 
  IFX_SINT32 SYS_od,      /* @parm Ignored */ 
  IFX_SINT32 SYS_pudsel,  /* @parm Ignored */ 
  IFX_SINT32 SYS_puden    /* @parm Ignored */ 
)
{
  SYS_pin = SYS_dir = SYS_altsel0 = SYS_altsel1 = SYS_pudsel = SYS_puden = 
  SYS_od = 0;
  
  return SYS_port;
}




/*==========================================================================
 * Function Name :: SYS_gpio_get_pin_num()
 *
 * Purpose       :: Gives pin number
 *
 * Input         :: none
 *					
 * Output        :: None.
 *
 * Return Value  :: Returns pin number.
 *
 *==========================================================================*/
IFX_SINT32 SYS_gpio_get_pin_num(
  IFX_SINT32 SYS_port,    /* @parm GPIO Port number */ 
  IFX_SINT32 SYS_pin,     /* @parm GPIO Port lines */ 
  IFX_SINT32 SYS_dir,     /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel0, /* @parm Ignored */ 
  IFX_SINT32 SYS_altsel1, /* @parm Ignored */ 
  IFX_SINT32 SYS_od,      /* @parm Ignored */ 
  IFX_SINT32 SYS_pudsel,  /* @parm Ignored */ 
  IFX_SINT32 SYS_puden    /* @parm Ignored */ 
)
{
  SYS_port = SYS_dir = SYS_altsel0 = SYS_altsel1 = SYS_pudsel = SYS_puden 
           = SYS_od = 0;
  
  return SYS_pin;
}

/* Not valid for DAVE */
#ifndef IFX_DAVE_GEN

/*==========================================================================
 * Function Name :: SYS_clk_initialise()
 *
 * Purpose       :: Initializes system clock Fsys and Fcpu according to 
 *                  configuration. 
 *
 * Input         :: none
 *					
 * Output        :: None.
 *
 * Return Value  :: 1 if success else 0 for error.
 *
 *==========================================================================*/
IFX_UINT32 SYS_clk_initialise(void)
{
  IFX_VUINT32  SYS_pll_clc = 0;
  IFX_VUINT32  SYS_pll_val = 0, scu_con_data=0; 

  /* Get PLL default value */
  SYS_pll_clc = SYS_PLL_CLC;  

 /* Check configuration for direct drive */
  #if (SYS_CFG_CLK_MODE == 0) 
  if((SYS_pll_clc & 0x20000000) == 0)
  {
    return 0;  /* error */
  }
  #endif


  SYS_pll_val = SYS_PLL_VAL;  /* Get configured PLL VAL */
 /* Select the Fcpu/Fsys ratio */
  SYS_pll_val |= (SYS_CFG_FREQ_SEL << SYS_PLL_CLC_SYSFSL_loc);    
  SYS_pll_val |= 0x00000002; /* restart lock detection (RESLD bit)*/

#if SYS_CFG_FIX_TC1130A_BUG
  SYS_pll_val |= SYS_PLL_CLC_VCOBYP_MASK; /* Set the VCOBypass mode */
#endif

  UNLOCK_ENDINIT_PROTECT;    /* unlock endinit protection */

  /* Select VCOBYPASS MODE (required for setting NDIV) */
  SYS_PLL_CLC |= 0x00000020; 

  /* Connect OSC to PLL */
  SYS_PLL_CLC &= (~(0x01000000)); 

  /* Program the desired frequency */
  SYS_PLL_CLC = SYS_pll_val;  

  LOCK_ENDINIT_PROTECT;

  IFX_ISYNC();      /* Wait for write sync */

  /* Wait until frequency is set. */
  while( !(SYS_PLL_CLC & 1)); 


  UNLOCK_ENDINIT_PROTECT;    /* unlock endinit protection */

  /* Deselect VCOBYPASS MODE */
  SYS_PLL_CLC &= ~(0x00000020); 

  /* Lock endinit protection */
  LOCK_ENDINIT_PROTECT;

  /* Enable USB clock logic if device is configured */
#if SYS_CFG_USB_DEVICE_ENABLE

  #if (SYS_CFG_USB_ONCHIP_CLK == 0)  
	/* usb clock is external, from pin 4.0 */
	 SYS_gpio_alloc(SYS_GPIO_USBCLK);   /* configure P4.0 for input */
  #endif

	/* Read the SCU con register */
   UNLOCK_ENDINIT_PROTECT;
     scu_con_data = SYS_SCU_CON;          /*Read SCU CON REG*/
     scu_con_data &= (~0x0000F000);       /*Clear the bits 15 .. 12*/
     scu_con_data |= SCU_CON_VAL;		  /*Set configured value*/
     SYS_SCU_CON = scu_con_data;		  /*Write SCU CON REG*/
   LOCK_ENDINIT_PROTECT;
#endif /* SYS_CFG_USB_DEVICE_ENABLE */

	/* enables the code cache */
#if (IFX_COMPILER_GNU || IFX_COMPILER_LINUX)
   UNLOCK_ENDINIT_PROTECT;
    SYS_PMI_CON0 = 0;		  /*Write SCU PMI REG*/
   LOCK_ENDINIT_PROTECT;
#endif
  return 1;
}

#endif  /* IFX_DAVE_GEN */


