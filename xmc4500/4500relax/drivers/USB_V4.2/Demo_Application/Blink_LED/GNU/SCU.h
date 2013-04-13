//****************************************************************************
// @Module        System Control Unit (SCU)
// @Filename      SCU.h
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      GNU
//
// @Codegenerator 1.3
//
// @Description   This file contains all function prototypes and macros for 
//                the SCU module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:16:17 AM
//
//****************************************************************************

// USER CODE BEGIN (SCU_Header,1)

// USER CODE END



#ifndef _SCU_H_
#define _SCU_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (SCU_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (SCU_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

//   period in normal watchdog mode =  699.051 ms
//   period in time-out mode =  682.667 µs
#define SCU_WDT_RELOAD 0xF000

//   use the last latched hardware configuration for booting after software 
//   reset (external inputs CFG[3:0])
//   external devices are not reset on software reset through activating 
//   #HRST pin
//   the system timer is not reset on software reset
#define SCU_RESET_OPTIONS 0x00200000

// USER CODE BEGIN (SCU_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (SCU_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (SCU_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (SCU_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void SCU_vInit(void);


// USER CODE BEGIN (SCU_Header,8)

// USER CODE END


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (SCU_Header,9)

// USER CODE END


#endif  // ifndef _SCU_H_
