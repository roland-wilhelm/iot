//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.h
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      GNU
//
// @Codegenerator 1.3
//
// @Description   This file contains all function prototypes and macros for 
//                the MAIN module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:16:16 AM
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,1)

// USER CODE END



#ifndef _MAIN_H_
#define _MAIN_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************
#define GNU

// compiler dependent names of builtin functions
#define MTCR _mtcr
#define ISYNC _isync
#define DISABLE _disable
#define ENABLE _enable

#define IFX_DAVE_GEN 1

// USER CODE BEGIN (MAIN_Header,4)

// USER CODE END




//****************************************************************************
// @Typedefs
//****************************************************************************

typedef unsigned char  ubyte;    // 1 byte unsigned; prefix: ub 
typedef signed char    sbyte;    // 1 byte signed;   prefix: sb 
typedef unsigned short ushort;   // 2 byte unsigned; prefix: us 
typedef signed short   sshort;   // 2 byte signed;   prefix: ss 
typedef unsigned int   uword;    // 4 byte unsigned; prefix: uw 
typedef signed int     sword;    // 4 byte signed;   prefix: sw 

typedef volatile struct
{
  unsigned int    bit0      : 1;
  unsigned int    bit1      : 1;
  unsigned int    bit2      : 1;
  unsigned int    bit3      : 1;
  unsigned int    bit4      : 1;
  unsigned int    bit5      : 1;
  unsigned int    bit6      : 1;
  unsigned int    bit7      : 1;
  unsigned int    bit8      : 1;
  unsigned int    bit9      : 1;
  unsigned int    bit10     : 1;
  unsigned int    bit11     : 1;
  unsigned int    bit12     : 1;
  unsigned int    bit13     : 1;
  unsigned int    bit14     : 1;
  unsigned int    bit15     : 1;
  unsigned int    bit16     : 1;
  unsigned int    bit17     : 1;
  unsigned int    bit18     : 1;
  unsigned int    bit19     : 1;
  unsigned int    bit20     : 1;
  unsigned int    bit21     : 1;
  unsigned int    bit22     : 1;
  unsigned int    bit23     : 1;
  unsigned int    bit24     : 1;
  unsigned int    bit25     : 1;
  unsigned int    bit26     : 1;
  unsigned int    bit27     : 1;
  unsigned int    bit28     : 1;
  unsigned int    bit29     : 1;
  unsigned int    bit30     : 1;
  unsigned int    bit31     : 1;
}  T_Reg32;

// USER CODE BEGIN (MAIN_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void MAIN_vWriteWDTCON0(uword uwValue);



// USER CODE BEGIN (MAIN_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         MAIN_vSetENDINIT() 
//
//----------------------------------------------------------------------------
// @Description   This macro sets the EndInit bit, which controls access to 
//                system critical registers. Setting the EndInit bit locks 
//                all EndInit protected registers.
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

#define MAIN_vSetENDINIT() MAIN_vWriteWDTCON0(WDT_CON0 | 0x00000001)


//****************************************************************************
// @Macro         MAIN_vResetENDINIT() 
//
//----------------------------------------------------------------------------
// @Description   This macro clears the EndInit bit, which controls access to 
//                system critical registers. Clearing the EndInit bit unlocks 
//                all EndInit protected registers. Modifications of the 
//                EndInit bit are monitored by the watchdog timer such that 
//                after clearing EndInit, the watchdog timer enters a defined 
//                time-out mode; EndInit must be set again before the 
//                time-out expires.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          6/9/2004
//
//****************************************************************************

#define MAIN_vResetENDINIT() MAIN_vWriteWDTCON0(WDT_CON0 & ~0x00000001)


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (MAIN_Header,9)

// USER CODE END


//****************************************************************************
// @Project Includes
//****************************************************************************

#include  <machine/intrinsics.h>
#include  <machine/cint.h>             
#include  "TC1130Regs.h"
#include  "GPTU.h"
#include  "ASC0.h"
#include  "SCU.h"

// USER CODE BEGIN (MAIN_Header,10)

// USER CODE END


#endif  // ifndef _MAIN_H_
