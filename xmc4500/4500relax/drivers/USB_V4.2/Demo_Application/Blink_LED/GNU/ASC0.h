//****************************************************************************
// @Module        Asynchronous Synchronous Serial Interface 0 (ASC0)
// @Filename      ASC0.h
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      GNU
//
// @Codegenerator 1.3
//
// @Description   This file contains all function prototypes and macros for 
//                the ASC0 module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:16:17 AM
//
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,1)

// USER CODE END



#ifndef _ASC0_H_
#define _ASC0_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ASC0_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void ASC0_vInit(void);
void ASC0_vSendData(ushort usData);
ushort ASC0_usGetData(void);
ubyte ASC0_ubTxDataReady(void);


// USER CODE BEGIN (ASC0_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         ASC0_ubTxBufFree() 
//
//----------------------------------------------------------------------------
// @Description   This macro can be used for checking the status of the 
//                transmit buffer register. The transmit buffer may only be 
//                written to if it is empty, this implies that the previous 
//                content of the transmit buffer have been loaded into the 
//                transmit shift register.
//
//----------------------------------------------------------------------------
// @Returnvalue   0 if buffer is not empty, else 1
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

#define ASC0_ubTxBufFree() ASC0_TBSRC_SRR


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define ASC0_RINT    0x4B

// USER CODE BEGIN (ASC0_Header,9)

// USER CODE END


#endif  // ifndef _ASC0_H_
