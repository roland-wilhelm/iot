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
** @FILENAME@:       sys_cfg.h
** @VERSION@:        3.0
** @DATE@:           17/01/2006    
**
** =============================================================================
**
** Project: TC1130
** Block: SYS HAL 
**
** =============================================================================
** Contents: Implements Configuration parameters for System resources on TC1130.
**
** =============================================================================
** References: None.
**
** =============================================================================
** History:
**
** Date            Author                 Comment
** 16/03/2004      Mahesh, Ruby          Release after code review.
** 07/05/2004	   Ranga                 Changes made to support DAvE.
** 14/04/2005	   Ronny                 Include support for 48,96MHz
** 19/04/2005	   Jayashree             Include support for 144MHz
** @CHANGE_HISTORY@
** =============================================================================
*/
/* @doc API */
#ifndef __SYS_CFG_H
#define __SYS_CFG_H

#include "sys_api.h"
#include "compiler.h" 


/*
  @topic1 SYS HAL Configurable Parameters |
  This section defines the configurable parameters of the SYS HAL - interrupts,
  GPIO ports, and the clock.
  The user may change only the value associated with the macros to suit 
  application requirements. However, the user may NOT change the name of the 
  macro.
*/


/*
  @topic2 System Clock Frequency |
  The clock must be operational before the controller can function.
  This clock is connected to the peripheral clock control registers, so
  changing the value of this clock frequency will affect all peripherals. 
  The individual peripherals can scale down this frequency according to
  their requirements, for more details please refer to the corresponding 
  user guide documents. 
*/

/*
  @def SYS_CLOCK_48MHZ |
  User needs to configure for the USB System clock to be 48Mhz.
  @def SYS_CLOCK_96MHZ |
  User needs to configure for the USB System clock to be 96Mhz.
  @def SYS_CLOCK_144MHZ |
  User needs to configure for the USB System clock to be 144Mhz.
*/ 

#define SYS_CLOCK_96MHZ  

/*
  @def SYS_CFG_USB_DEVICE_ENABLE |
  User needs to configure whether the USB device has been used.
  @flag 1 | Equate this macro to 1 if onchip USB device is used.
  @flag 0 | Equate this macro to 0 if usb device is not used (default).
*/
#define SYS_CFG_USB_DEVICE_ENABLE  1


/*
  @def SYS_CFG_USB_ONCHIP_CLK |
  User can configure the USB clock generation logic whether it internal or
  external. If clock is external, it will be derived from pin P4.0.  
  @flag 1 | Equate this macro to 1 for internal clock generation 
  @flag 0 | Equate this macro to 0 for external clock generation 

  @comm  Note that if the device is used and usb clock generation is
  internal, then cpu frequency should be programmed either to 48MHZ, 96MHZ
  or 144MHz.
*/
#define SYS_CFG_USB_ONCHIP_CLK  1

/*
  @def SYS_CFG_USB_CLK_DIVISOR |
  User needs to configure the USB clock ratio based upon the USB clock
  frequency. Since clock frequency can be either 48 MHZ, 96 or 144 MHZ,
  the ratio can 1, 2 or 3 respectively.
*/
#ifdef SYS_CLOCK_48MHZ
#define SYS_CFG_USB_CLK_DIVISOR  1
#endif

#ifdef SYS_CLOCK_96MHZ
#define SYS_CFG_USB_CLK_DIVISOR  2
#endif

#ifdef SYS_CLOCK_144MHZ
#define SYS_CFG_USB_CLK_DIVISOR  3
#endif
/*
  @def SYS_CFG_OSC_FREQ |
  User has to configure this with external applied frequency.
*/
#define SYS_CFG_OSC_FREQ  20000000


/*
  @def SYS_CFG_CLK_MODE |
  User needs to configure this macro to any one of the following clock 
  operation mode.
  @flag 0 | Direct drive (CPU clock directly derived from external applied 
  frequency, N, P, and K values are not considered).
  @flag 1 | PLL mode (N, P, K values will be considered to derive CPU clock 
  frequency from external frequency)
  @flag 2 | VCO bypass/pre-scalar mode (N value not considered to derive CPU 
  clock from external frequency).

*/
#define SYS_CFG_CLK_MODE  1

/*
  @def SYS_CFG_FREQ_SEL  |
  This define decide the frequency ration between CPU and system, this is 
  independent from the clock mode selection(SYS_CFG_CLK_MODE).
  @flag 0 | Ratio of fcpu/fsys is 2.
  @flag 1 | Ratio of fcpu/fsys is 1 i.e. fcpu = fsys.
*/ 
#ifdef SYS_CLOCK_144MHZ
#define SYS_CFG_FREQ_SEL  0
#else 
#define SYS_CFG_FREQ_SEL  1 
#endif


/*
  @def SYS_CFG_KDIV |
  User has to configure this with a value ranges from 1 to 16, used for both 
  PLL and VCO bypass modes.
*/
#ifdef SYS_CLOCK_48MHZ
#define SYS_CFG_KDIV      10 			   
#endif

#ifdef SYS_CLOCK_96MHZ
#define SYS_CFG_KDIV      8 			   
#endif

#ifdef SYS_CLOCK_144MHZ
#define SYS_CFG_KDIV      4 			   
#endif

/*
  @def SYS_CFG_PDIV |
  User has to configure this with a value ranges from 1 to 8, used for both PLL 
  and VCO bypass modes. 
*/
#ifdef SYS_CLOCK_48MHZ
#define SYS_CFG_PDIV      1
#endif

#ifdef SYS_CLOCK_96MHZ
#define SYS_CFG_PDIV      1
#endif

#ifdef SYS_CLOCK_144MHZ
#define SYS_CFG_PDIV      1
#endif

/*
  @def SYS_CFG_NDIV |
  User has to configure this with a value ranges from 1 to 128, used only for 
  PLL mode. 
  @comm Advisable value range is 20 to 100.
*/
#ifdef SYS_CLOCK_48MHZ
#define SYS_CFG_NDIV      24		   
#endif

#ifdef SYS_CLOCK_96MHZ
#define SYS_CFG_NDIV      38		   
#endif

#ifdef SYS_CLOCK_144MHZ
#define SYS_CFG_NDIV      29		   
#endif
/*
  @def SYS_CFG_FIX_TC1130A_BUG |
  User can use this definition for software workaround done for TC1130A
  at system driver and not at module level. 
  @flag 1 | Enbale software work-around for hardware bug fixes.
  @flag 0 | Disbale software work-around for hardware bug fixes.
*/
#define SYS_CFG_FIX_TC1130A_BUG      1


/*
  @topic2 Interrupt priorities configuration |
  The following priorities are used for interrupts. Corresponding to these 
  priorities ISR code will be placed in Interrupt base Vector Table.
  The user can edit the priorities according to application
  requirements. These priorities will be static.

  Priorities range from 1 to 255. Each interrupt should have a unique priority.
  1 is the lowest priority and 255 is the highest priority. 
*/


/*
  Note to user:
  Start ISR priorities low and work up, high bits aren't checked when
  you reduce the number of arb cycles.
*/
#define SYS_CFG_MAX_INT 255 /* Set down arb cycles as per range */

/*                   SSC0 INTERRUPT PRIORITIES                                */
/*----------------------------------------------------------------------------*/
#define SYS_SSC0_RIR   15 /* Initial receive interrupt for SSC 0              */
#define SYS_SSC0_TIR   14 /* Initial transmit interrupt for SSC 0             */
#define SYS_SSC0_EIR   16 /* Initial error interrupt for SSC 0                */

/*                   SSC1 INTERRUPT PRIORITIES                                */
/*----------------------------------------------------------------------------*/
#define SYS_SSC1_RIR   17 /* Initial receive interrupt for SSC 1              */
#define SYS_SSC1_TIR   18 /* Initial transmit interrupt for SSC 1             */
#define SYS_SSC1_EIR   19 /* Initial error interrupt for SSC 1                */


/*                   ASC0 INTERRUPT PRIORITIES                                */
/*----------------------------------------------------------------------------*/
#define SYS_ASC0_RIR   20
#define SYS_ASC0_TBIR  0
#define SYS_ASC0_TIR   22
#define SYS_ASC0_EIR   23

/*                   ASC1 INTERRUPT PRIORITIES                                */
/*----------------------------------------------------------------------------*/
#define SYS_ASC1_RIR   24 /* Initial receive interrupt for ASC 1              */
#define SYS_ASC1_TBIR  0  /* Initial transmit buffer interrupt for ASC 1      */
#define SYS_ASC1_TIR   26 /* Initial transmit interrupt for ASC 1             */
#define SYS_ASC1_EIR   27 /* Initial error interrupt for ASC 1                */

/*                   ASC2 INTERRUPT PRIORITIES                                */
/*----------------------------------------------------------------------------*/

#define SYS_ASC2_RIR   28 /* Initial receive interrupt for ASC 2              */
#define SYS_ASC2_TBIR  0  /* Initial transmit buffer interrupt for ASC 2      */
#define SYS_ASC2_TIR   30  /* Initial transmit interrupt for ASC 2             */
#define SYS_ASC2_EIR   31 /* Initial error interrupt for ASC 2                */

#ifndef  IFX_DAVE_GEN 
/*                   ETHERNET INTERRUPT PRIORITIES                            */
/*----------------------------------------------------------------------------*/
#define SYS_ETH_MACRX0 40 /* Initial Ethernet MACRX0 interrupt priority */
#define SYS_ETH_MACRX1 41 /* Initial Ethernet MACRX1 interrupt priority */
#define SYS_ETH_MACTX0 42 /* Initial Ethernet MACTX0 interrupt priority */
#define SYS_ETH_MACTX1 43 /* Initial Ethernet MACTX1 interrupt priority */
#define SYS_ETH_RB0    44 /* Initial Ethernet RB0 interrupt priority    */
#define SYS_ETH_RB1    45 /* Initial Ethernet RB1 interrupt priority    */
#define SYS_ETH_TB     46 /* Initial Ethernet TB interrupt priority     */
#define SYS_ETH_DMUR   47 /* Initial Ethernet DMUR interrupt priority   */
#define SYS_ETH_DMUT   48 /* Initial Ethernet DMUT interrupt priority   */

/*----------------------------------------------------------------------------*/

/*                   USB INTERRUPT PRIORITIES                                 */
/*----------------------------------------------------------------------------*/
#define SYS_USB_SRC0   50 /* Line 0 interrupt priority */
#define SYS_USB_SRC1   51 /* Line 1 interrupt priority */
#define SYS_USB_SRC2   52 /* Line 2 interrupt priority */
#define SYS_USB_SRC3   53 /* Line 3 interrupt priority */
#define SYS_USB_SRC4   54 /* Line 4 interrupt priority */
#define SYS_USB_SRC5   55 /* Line 5 interrupt priority */
#define SYS_USB_SRC6   56 /* Line 6 interrupt priority */
#define SYS_USB_SRC7   57 /* Line 7 interrupt priority */
#endif  /*IFX_DAVE_GEN*/

/*----------------------------------------------------------------------------*/

/*                   CAN INTERRUPT PRIORITIES                                 */
/*----------------------------------------------------------------------------*/
#define		SYS_CAN_SRN0							1
#define		SYS_CAN_SRN1							6
#define		SYS_CAN_SRN2							7
#define		SYS_CAN_SRN3							8
#define		SYS_CAN_SRN4							9
#define		SYS_CAN_SRN5							2
#define		SYS_CAN_SRN6							3
#define		SYS_CAN_SRN7							4
#define		SYS_CAN_SRN8							5
#define		SYS_CAN_SRN9							10
#define		SYS_CAN_SRN10							11
#define		SYS_CAN_SRN11							72
#define		SYS_CAN_SRN12							73
#define		SYS_CAN_SRN13							74
#define		SYS_CAN_SRN14							75
#define		SYS_CAN_SRN15							76


/*----------------------------------------------------------------------------*/
/*      GPIO Configuration values                                             */


/*
  @topic2 GPIO Port Configuration Parameters |
  This section defines the configurable port settings of the peripherals.
  These macros define the following parameters:
  @flag Peripheral Module | - Name of the macro which includes the name of the 
                              peripheral and the port line (Transmit/Receive).
  @flag Port              | - Port Number.
  @flag Pin               | - Bit Number in the Port.
  @flag Dir               | - Value of the bit in the Dir register.
  @flag Alt0              | - Value of the bit in the Altsel0 register.
  @flag Alt1              | - Value of the bit in the Altsel1 register.
  @flag Od                | - Value of the bit in the Open Drain register.
  @flag Pullsel           | - Value of the bit in the Pull up/Pull down 
                              selection register.
  @flag Pullen            | - Value of the bit in the Pull up/Pull down enable 
                              register.

  Note: User may use -1, to indicate an unused (or don't care) value.

  These macros should be defined has a set of values in above sequence and 
  separated by commas (,).
  E.g. #define SYS_GPIO_ASC0_TX 1, 7, 1, 1, -1, -1, -1, -1
*/

/*      Port configuration for the TC1130                                     */

/*----- Peripheral Module  Port Pin  Dir   Alt0  Alt1  Od Pullsel Pullen----*/
/*         ASC0                                                               */
#define SYS_GPIO_ASC0_RX    2,   0,  0,    0,    0,   -1,  -1,   -1
#define SYS_GPIO_ASC0_TX    2,   1,  1,    1,    0,   -1,  -1,   -1

#define SYS_GPIO_ASC1_RX    2,   8,  0,    0,    0,   -1,  -1,   -1
#define SYS_GPIO_ASC1_TX    2,   9,  1,    1,    0,   -1,  -1,   -1

#define SYS_GPIO_ASC2_RX    2,  10,  0,    0,    0,   -1,  -1,   -1
#define SYS_GPIO_ASC2_TX    2,  11,  1,    1,    0,   -1,  -1,   -1

/*         SSC0                                                              */
#define SYS_GPIO_SSC0_MRST  2,    2,  0,    1,   0,   -1,  -1,   -1
#define SYS_GPIO_SSC0_MTSR  2,    3,  1,    1,   0,   -1,  -1,   -1
#define SYS_GPIO_SSC0_SCLK  2,    4,  1,    1,   0,   -1,  -1,   -1
#define SYS_GPIO_SSC0_SLSI  1,   15,  0,   -1,  -1,   -1,  -1,   -1         

#define SYS_GPIO_SSC0_SLSO00 0,   6,  1,    1,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC0_SLSO01 1,  11,  1,    0,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC0_SLSO02 1,  13,  1,    0,  1,    -1,  -1,   -1
#define SYS_GPIO_SSC0_SLSO03 2,  12,  1,    0,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC0_SLSO04 2,  14,  1,    0,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC0_SLSO05 3,   7,  1,    1,  0,    -1,  -1,   -1 
#define SYS_GPIO_SSC0_SLSO06 3,   9,  1,    1,  0,    -1,  -1,   -1 
#define SYS_GPIO_SSC0_SLSO07 3,  11,  1,    1,  0,    -1,  -1,   -1 

/*         SSC1                                                             */
#define SYS_GPIO_SSC1_MRST   2,   5,  1,    1,   0,   -1,  -1,   -1
#define SYS_GPIO_SSC1_MTSR   2,   6,  0,    1,   0,   -1,  -1,   -1
#define SYS_GPIO_SSC1_SCLK   2,   7,  0,    1,   0,   -1,  -1,   -1
#define SYS_GPIO_SSC1_SLSI   0,   4,  0,   -1,  -1,   -1,  -1,   -1

#define SYS_GPIO_SSC1_SLSO10 0,   7,  1,    1,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC1_SLSO11 1,  12,  1,    0,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC1_SLSO12 1,  14,  1,    0,  1,    -1,  -1,   -1
#define SYS_GPIO_SSC1_SLSO13 2,  13,  1,    0,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC1_SLSO14 2,  15,  1,    0,  1,    -1,  -1,   -1 
#define SYS_GPIO_SSC1_SLSO15 3,   8,  1,    1,  0,    -1,  -1,   -1 
#define SYS_GPIO_SSC1_SLSO16 3,  10,  1,    1,  0,    -1,  -1,   -1 
#define SYS_GPIO_SSC1_SLSO17 3,  12,  1,    1,  0,    -1,  -1,   -1 

#define SYS_GPIO_CAN0_RX     0,   8,  0,    1,  0,    -1,   1,    1 
#define SYS_GPIO_CAN0_TX     0,   9,  1,    1,  0,    -1,   0,    0 
#define SYS_GPIO_CAN1_RX     0,  10,  0,    1,  0,    -1,   1,    1 
#define SYS_GPIO_CAN1_TX     0,  11,  1,    1,  0,    -1,   0,    0 
#define SYS_GPIO_CAN2_RX     0,  12,  0,    1,  0,    -1,   1,    1 
#define SYS_GPIO_CAN2_TX     0,  13,  1,    1,  0,    -1,   0,    0 
#define SYS_GPIO_CAN3_RX     0,  14,  0,    1,  0,    -1,   1,    1 
#define SYS_GPIO_CAN3_TX     0,  15,  1,    1,  0,    -1,   0,    0 
#define SYS_GPIO_USBCLK      4,   0,  0,    0,  0,  -1,  -1,   -1


/* Leave this for Ethernet LLD with DAVE */
/*         Ethernet                                                */
#define SYS_GPIO_ETH_TX0    1,   0,   1,    1,   0,   -1,  1,   1
#define SYS_GPIO_ETH_TX1    1,   1,   1,    1,   0,   -1,  1,   1
#define SYS_GPIO_ETH_TX2    1,   2,   1,    1,   0,   -1,  1,   1
#define SYS_GPIO_ETH_TX3    1,   3,   1,    1,   0,   -1,  1,   1
#define SYS_GPIO_ETH_TXER   1,   4,   1,    1,   0,   -1,  0,   1
#define SYS_GPIO_ETH_TXEN   1,   5,   1,    1,   0,   -1,  0,   1
#define SYS_GPIO_ETH_MDC    1,   6,   1,    1,   0,   -1,  1,   1
#define SYS_GPIO_ETH_RXDV   1,   7,   0,   -1,  -1,   -1,  0,   1
#define SYS_GPIO_ETH_CRS    1,   8,   0,   -1,  -1,   -1,  0,   1
#define SYS_GPIO_ETH_COL    1,   9,   0,   -1,  -1,   -1,  0,   1
#define SYS_GPIO_ETH_RX0    1,   10,  0,   -1,  -1,   -1,  1,   1
#define SYS_GPIO_ETH_RX1    1,   11,  0,   -1,  -1,   -1,  1,   1
#define SYS_GPIO_ETH_RX2    1,   12,  0,   -1,  -1,   -1,  1,   1
#define SYS_GPIO_ETH_RX3    1,   13,  0,   -1,  -1,   -1,  1,   1
#define SYS_GPIO_ETH_RXER   1,   14,  0,   -1,  -1,   -1,  0,   1


/* Not valid if integrated with DAVE */
#ifndef  IFX_DAVE_GEN 

/***************************************************************************/
/* DONOT MODIFY ANY ITEMS BELOW                                            */
/* Bail out if  CONFIGURATION VALUES doesnot match with datasheet          */
/***************************************************************************/


/* Boundary value for K divisor */
#if ( (SYS_CFG_KDIV > 16) || (SYS_CFG_KDIV < 1) )   
#error "Please select valid value for K-Divisor."
#endif

/* Boundary value for P divisor */
#if ( (SYS_CFG_PDIV > 8) || (SYS_CFG_PDIV < 1) )   
#error "Please select valid value for P-Divisor."
#endif

/* Boundary value for N divisor */
#if ( (SYS_CFG_NDIV >100) || (SYS_CFG_NDIV < 20) )   
#error "Please select valid value for N-Divisor."
#endif

/* If Fcpu/Fsys ratio doesnot match */
#if ( (SYS_CFG_FREQ_SEL > 1) || (SYS_CFG_FREQ_SEL < 0))  
#error "Please select valid Fcpu/Fsys ratio."
#endif

/* Calculate the programable VCO range */
#define SYS_VCO_FREQ    ( ((SYS_CFG_OSC_FREQ/100000)*SYS_CFG_NDIV)/SYS_CFG_PDIV)
#if (SYS_CFG_CLK_MODE == 1) /* PLL MODE */
/* Calculate the VCOSEL MASK according to VCO freq. */
#if ( (SYS_VCO_FREQ > 400) && (SYS_VCO_FREQ < 500) )
#define SYS_VCOSEL_MASK 0x00000000
#elif ( (SYS_VCO_FREQ > 500) && (SYS_VCO_FREQ < 600) )
#define  SYS_VCOSEL_MASK 0x00000040
#elif ( (SYS_VCO_FREQ > 600) && (SYS_VCO_FREQ < 700) )
#define  SYS_VCOSEL_MASK 0x00000080
#elif ( (SYS_VCO_FREQ > 700) || (SYS_VCO_FREQ < 400) ) 
#define  SYS_VCOSEL_MASK 0x00000000     /*As susggested by hardware group*/
#endif
#else 
#define  SYS_VCOSEL_MASK 0x00000000        /* To avoid compile error! */
#endif /* (SYS_CFG_CLK_MODE == 1)  PLL MODE */


/* Check for USB clock ratio configuration */
#if SYS_CFG_USB_DEVICE_ENABLE  
#if SYS_CFG_USB_CLK_DIVISOR > 3
#error "Select valid USB clock ratio."
#elif (SYS_CFG_USB_ONCHIP_CLK == 1) 
/* usb clock is internal (derived from PLL clock) */
#define SCU_CON_VAL  ( ( (SYS_CFG_USB_CLK_DIVISOR-1) << 12) | 0xFF00C000)  
#elif (SYS_CFG_USB_ONCHIP_CLK == 0) 
/* usb clock is external, from pin 4.0 */
#define SCU_CON_VAL  ( ( (SYS_CFG_USB_CLK_DIVISOR-1) << 12) | 0xFF008000)
#endif
#endif

/* Calculate the PLL VALUE */
#if (SYS_CFG_CLK_MODE == 1)  /*PLL MODE*/
#define  SYS_PLL_VAL ( ((SYS_CFG_KDIV - 1) << SYS_PLL_CLC_KDIV_loc) | \
        ((SYS_CFG_NDIV - 1) << SYS_PLL_CLC_NDIV_loc) | \
        ((SYS_CFG_PDIV - 1) << SYS_PLL_CLC_PDIV_loc)  | (SYS_VCOSEL_MASK))
        
#elif(SYS_CFG_CLK_MODE == 2)
  /* Prescaler (VCOBYPASS) mode */
#define  SYS_PLL_VAL  ((SYS_CFG_KDIV - 1) << SYS_PLL_CLC_KDIV_loc) | \
         ((SYS_CFG_PDIV - 1) << SYS_PLL_CLC_PDIV_loc)  
#endif

#ifndef IFX_COMPILER_LINUX
  /*get system freq */   
#if (SYS_CFG_CLK_MODE == 0)   /*Direct drive*/
#define SYS_CFG_CPU_FREQ    SYS_CFG_OSC_FREQ
#elif (SYS_CFG_CLK_MODE == 1) /*PLL drive*/
#define SYS_CFG_CPU_FREQ ((SYS_CFG_OSC_FREQ * SYS_CFG_NDIV) / \
        (SYS_CFG_KDIV * SYS_CFG_PDIV) )
#else						  /*VCO bypass/ pre-scalar mode*/
#define SYS_CFG_CPU_FREQ (SYS_CFG_OSC_FREQ / (SYS_CFG_KDIV * SYS_CFG_PDIV) )
#endif

#if (SYS_CFG_FREQ_SEL == 0)
  #define SYS_CFG_CLK_FREQ   ( SYS_CFG_CPU_FREQ / 2 )
#else
  #define SYS_CFG_CLK_FREQ   SYS_CFG_CPU_FREQ
#endif

#else
  #define SYS_CFG_CLK_FREQ   cpu_frequency(0)
#endif /* IFX_COMPILER_LINUX */

/***************************************************************************/

#else
  #define SYS_CFG_CLK_FREQ   95000000
#endif /* IFX_DAVE_GEN */
/* IFX_DAVE_GEN 
This value has to be provided by user and shall be equal to DAvE generated value.
*/
#endif /* __SYS_CFG_H */


