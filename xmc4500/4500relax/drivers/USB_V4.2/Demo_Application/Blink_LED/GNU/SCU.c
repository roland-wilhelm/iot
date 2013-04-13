//****************************************************************************
// @Module        System Control Unit (SCU)
// @Filename      SCU.c
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      GNU
//
// @Codegenerator 1.3
//
// @Description   This file contains functions that use the SCU module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:16:17 AM
//
//****************************************************************************

// USER CODE BEGIN (SCU_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (SCU_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (SCU_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (SCU_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (SCU_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (SCU_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (SCU_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (SCU_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (SCU_General,9)

// USER CODE END


//****************************************************************************
// @Function      void SCU_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the SCU function 
//                library. It is assumed that the SFRs used by this library 
//                are in its reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void SCU_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  SCU Control:
  ///  -----------------------------------------------------------------------
  ///  - USB Clock Divider is 2:1
  ///  - USB Clock Input from internal CGU

  ///  -----------------------------------------------------------------------
  ///  Settings for the Power Management:
  ///  -----------------------------------------------------------------------
  ///  - no internal hardware reset will be performed on exit from deep sleep
  ///  - no Deep Sleep Mode Requested

  MAIN_vResetENDINIT();
  SCU_CON        =  0xFF00D008;  // load SCU control register 

  PMG_CON        =  0x00000000;  // load power management control register
  MAIN_vSetENDINIT();

  ///  -----------------------------------------------------------------------
  ///  Settings for the Watchdog Timer:
  ///  -----------------------------------------------------------------------
  ///  - the watchdog timer is enabled
  ///  - the input frequency is SYSCLK / 16384
  ///  - period in normal watchdog mode =  699.051 ms
  ///  - period in time-out mode =  682.667 µs

  MAIN_vWriteWDTCON0(0xF0000000);
  WDT_CON1       =  0x00000000;  // load watchdog control register 1
  MAIN_vSetENDINIT();

  ///  -----------------------------------------------------------------------
  ///  Soft Reset Options:
  ///  -----------------------------------------------------------------------
  ///  - use the last latched hardware configuration for booting after 
  ///    software reset (external inputs CFG[3:0])
  ///  - external devices are not reset on software reset through activating 
  ///    #HRST pin
  ///  - the system timer is not reset on software reset


  // USER CODE BEGIN (Init,3)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  External Request Unit:
  ///  -----------------------------------------------------------------------
  ///  REQLINE0 configuration:
  ///  - use signal REQ0 (= none) as input

  ///  REQLINE1 configuration:
  ///  - use signal REQ2 (= none) as input

  ///  REQLINE2 configuration:
  ///  - use signal REQ4 (= none) as input

  ///  REQLINE3 configuration:
  ///  - use signal REQ6 (= none) as input

  ///  Output channel 0 configuration:
  ///  - the detected pattern is not taken into account; an activation of 
  ///    IOUT0 is always possible due to a trigger event

  ///  Output channel 1 configuration:
  ///  - the detected pattern is not taken into account; an activation of 
  ///    IOUT1 is always possible due to a trigger event

  ///  Output channel 2 configuration:
  ///  - the detected pattern is not taken into account; an activation of 
  ///    IOUT2 is always possible due to a trigger event

  ///  Output channel 3 configuration:
  ///  - the detected pattern is not taken into account; an activation of 
  ///    IOUT3 is always possible due to a trigger event

  EICR0          =  0x00000000;  // external input channel 0 register
  EICR1          =  0x00000000;  // external input channel 1 register
  IGCR0          =  0x00000000;  // interrupt gating 0 register
  IGCR1          =  0x00000000;  // interrupt gating 1 register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used ERU Port Pins:
  ///  -----------------------------------------------------------------------

} //  End of function SCU_vInit



// USER CODE BEGIN (SCU_General,10)

// USER CODE END

