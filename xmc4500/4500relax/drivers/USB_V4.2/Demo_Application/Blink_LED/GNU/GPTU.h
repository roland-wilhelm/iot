//****************************************************************************
// @Module        General Purpose Timer Unit (GPTU)
// @Filename      GPTU.h
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      GNU
//
// @Codegenerator 1.3
//
// @Description   This file contains all function prototypes and macros for 
//                the GPTU module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:16:16 AM
//
//****************************************************************************

// USER CODE BEGIN (GPTU_Header,1)

// USER CODE END



#ifndef _GPTU_H_
#define _GPTU_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (GPTU_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPTU_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

#define GPTU_BASE 0xF0000600

// Timer T0A Count Register
#define GPTU_T0A       (*((ubyte volatile *) (GPTU_BASE + 0x34)))

// Timer T0B Count Register
#define GPTU_T0B       (*((ubyte volatile *) (GPTU_BASE + 0x35)))

// Timer T0C Count Register
#define GPTU_T0C       (*((ubyte volatile *) (GPTU_BASE + 0x36)))

// Timer T0D Count Register
#define GPTU_T0D       (*((ubyte volatile *) (GPTU_BASE + 0x37)))

// Timer T0A / T0B Count Register
#define GPTU_T0A_B     (*((ushort volatile *) (GPTU_BASE + 0x34)))

// Timer T0C / T0D Count Register
#define GPTU_T0C_D     (*((ushort volatile *) (GPTU_BASE + 0x36)))

// Timer T0A / T0B / T0C Count Register
#define GPTU_T0A_C     (*((uword volatile *) (GPTU_BASE + 0x38)))

// Timer T0A / T0B / T0C / T0D Count Register
#define GPTU_T0A_D     (*((uword volatile *) (GPTU_BASE + 0x34)))

// Timer T0RA Reload Register
#define GPTU_T0RA      (*((ubyte volatile *) (GPTU_BASE + 0x3C)))

// Timer T0RB Reload Register
#define GPTU_T0RB      (*((ubyte volatile *) (GPTU_BASE + 0x3D)))

// Timer T0RC Reload Register
#define GPTU_T0RC      (*((ubyte volatile *) (GPTU_BASE + 0x3E)))

// Timer T0RD Reload Register
#define GPTU_T0RD      (*((ubyte volatile *) (GPTU_BASE + 0x3F)))

// Timer T0RA / T0RB Reload Register
#define GPTU_T0RA_B    (*((ushort volatile *) (GPTU_BASE + 0x3C)))

// Timer T0RC / T0RD Reload Register
#define GPTU_T0RC_D    (*((ushort volatile *) (GPTU_BASE + 0x3E)))

// Timer T0RA / T0RB / T0RC Reload Register
#define GPTU_T0RA_C    (*((uword volatile *) (GPTU_BASE + 0x40)))

// Timer T0RA / T0RB / T0RC / T0RD Reload Register
#define GPTU_T0RA_D    (*((uword volatile *) (GPTU_BASE + 0x3C)))

// Timer T1A Count Register
#define GPTU_T1A       (*((ubyte volatile *) (GPTU_BASE + 0x44)))

// Timer T1B Count Register
#define GPTU_T1B       (*((ubyte volatile *) (GPTU_BASE + 0x45)))

// Timer T1C Count Register
#define GPTU_T1C       (*((ubyte volatile *) (GPTU_BASE + 0x46)))

// Timer T1D Count Register
#define GPTU_T1D       (*((ubyte volatile *) (GPTU_BASE + 0x47)))

// Timer T1A / T1B Count Register
#define GPTU_T1A_B     (*((ushort volatile *) (GPTU_BASE + 0x44)))

// Timer T1C / T1D Count Register
#define GPTU_T1C_D     (*((ushort volatile *) (GPTU_BASE + 0x46)))

// Timer T1A / T1B / T1C Count Register
#define GPTU_T1A_C     (*((uword volatile *) (GPTU_BASE + 0x48)))

// Timer T1A / T1B / T1C / T1D Count Register
#define GPTU_T1A_D     (*((uword volatile *) (GPTU_BASE + 0x44)))

// Timer T1RA Reload Register
#define GPTU_T1RA      (*((ubyte volatile *) (GPTU_BASE + 0x4C)))

// Timer T1RB Reload Register
#define GPTU_T1RB      (*((ubyte volatile *) (GPTU_BASE + 0x4D)))

// Timer T1RC Reload Register
#define GPTU_T1RC      (*((ubyte volatile *) (GPTU_BASE + 0x4E)))

// Timer T1RD Reload Register
#define GPTU_T1RD      (*((ubyte volatile *) (GPTU_BASE + 0x4F)))

// Timer T1RA / T1RB Reload Register
#define GPTU_T1RA_B    (*((ushort volatile *) (GPTU_BASE + 0x4C)))

// Timer T1RC / T1RD Reload Register
#define GPTU_T1RC_D    (*((ushort volatile *) (GPTU_BASE + 0x4E)))

// Timer T1RA / T1RB / T1RC Reload Register
#define GPTU_T1RA_C    (*((uword volatile *) (GPTU_BASE + 0x50)))

// Timer T1RA / T1RB / T1RC / T1RD Reload Register
#define GPTU_T1RA_D    (*((uword volatile *) (GPTU_BASE + 0x4C)))


// Timer T2A Count Register
#define GPTU_T2_A      (*((ushort volatile *) (GPTU_BASE + 0x54)))

// Timer T2B Count Register
#define GPTU_T2_B      (*((ushort volatile *) (GPTU_BASE + 0x56)))

// Timer T2A / T2B Count Register
#define GPTU_T2A_B     (*((uword volatile *) (GPTU_BASE + 0x54)))

// Timer T2A Reload/Capture Register 0
#define GPTU_T2R0_A    (*((ushort volatile *) (GPTU_BASE + 0x58)))

// Timer T2A Reload/Capture Register 1
#define GPTU_T2R1_A    (*((ushort volatile *) (GPTU_BASE + 0x5C)))

// Timer T2B Reload/Capture Register 0
#define GPTU_T2R0_B    (*((ushort volatile *) (GPTU_BASE + 0x5A)))

// Timer T2B Reload/Capture Register 1
#define GPTU_T2R1_B    (*((ushort volatile *) (GPTU_BASE + 0x5E)))

// Timer T2A / T2B Reload/Capture Register 0
#define GPTU_T2R0_A_B  (*((uword volatile *) (GPTU_BASE + 0x58)))

// Timer T2A / T2B Reload/Capture Register 1
#define GPTU_T2R1_A_B  (*((uword volatile *) (GPTU_BASE + 0x5C)))

// USER CODE BEGIN (GPTU_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPTU_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (GPTU_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPTU_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void GPTU_vInit(void);


// USER CODE BEGIN (GPTU_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         GPTU_vStartTmr(TimerName) 
//
//----------------------------------------------------------------------------
// @Description   This macro starts the selected GPTU timer.The timer 
//                continues counting from where it stopped.
//                The following definitions for TimerName are available:
//                 8-bit timer:  GPTU_T0A, GPTU_T0B, GPTU_T0C, GPTU_T0D
//                 8-bit timer:  GPTU_T1A, GPTU_T1B, GPTU_T1C, GPTU_T1D
//                16-bit timer:  GPTU_T0A_B, GPTU_T0C_D
//                16-bit timer:  GPTU_T1A_B, GPTU_T1C_D
//                24-bit timer:  GPTU_T0A_C, GPTU_T1A_C
//                32-bit timer:  GPTU_T0A_D, GPTU_T1A_D
//                16-bit timer:  GPTU_T2A, GPTU_T2B
//                32-bit timer:  GPTU_T2
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerName: 
//                Name of the timer to be started
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

#define GPTU_vStartTmr(TimerName) _GPTU_vStartTmr_##TimerName
#define _GPTU_vStartTmr_GPTU_T0A      GPTU_T012RUN_T0ARUN = 1
#define _GPTU_vStartTmr_GPTU_T0B      GPTU_T012RUN_T0BRUN = 1
#define _GPTU_vStartTmr_GPTU_T0C      GPTU_T012RUN_T0CRUN = 1
#define _GPTU_vStartTmr_GPTU_T0D      GPTU_T012RUN_T0DRUN = 1
#define _GPTU_vStartTmr_GPTU_T1A      GPTU_T012RUN_T1ARUN = 1
#define _GPTU_vStartTmr_GPTU_T1B      GPTU_T012RUN_T1BRUN = 1
#define _GPTU_vStartTmr_GPTU_T1C      GPTU_T012RUN_T1CRUN = 1
#define _GPTU_vStartTmr_GPTU_T1D      GPTU_T012RUN_T1DRUN = 1
#define _GPTU_vStartTmr_GPTU_T0A_B    GPTU_T012RUN |= 0x0003
#define _GPTU_vStartTmr_GPTU_T0C_D    GPTU_T012RUN |= 0x000C
#define _GPTU_vStartTmr_GPTU_T1A_B    GPTU_T012RUN |= 0x0030
#define _GPTU_vStartTmr_GPTU_T1C_D    GPTU_T012RUN |= 0x00C0
#define _GPTU_vStartTmr_GPTU_T0A_C    GPTU_T012RUN |= 0x0007
#define _GPTU_vStartTmr_GPTU_T1A_C    GPTU_T012RUN |= 0x0070
#define _GPTU_vStartTmr_GPTU_T0A_D    GPTU_T012RUN |= 0x000F
#define _GPTU_vStartTmr_GPTU_T1A_D    GPTU_T012RUN |= 0x00F0
#define _GPTU_vStartTmr_GPTU_T2A      GPTU_T012RUN_T2ASETR = 1
#define _GPTU_vStartTmr_GPTU_T2B      GPTU_T012RUN_T2BSETR = 1
#define _GPTU_vStartTmr_GPTU_T2       GPTU_T012RUN |= 0x2200


//****************************************************************************
// @Macro         GPTU_vStopTmr(TimerName) 
//
//----------------------------------------------------------------------------
// @Description   This macro stops the selected GPTU timer.The content of the 
//                timer register remains unchanged.
//                The following definitions for TimerName are available:
//                 8-bit timer:  GPTU_T0A, GPTU_T0B, GPTU_T0C, GPTU_T0D
//                 8-bit timer:  GPTU_T1A, GPTU_T1B, GPTU_T1C, GPTU_T1D
//                16-bit timer:  GPTU_T0A_B, GPTU_T0C_D
//                16-bit timer:  GPTU_T1A_B, GPTU_T1C_D
//                24-bit timer:  GPTU_T0A_C, GPTU_T1A_C
//                32-bit timer:  GPTU_T0A_D, GPTU_T1A_D
//                16-bit timer:  GPTU_T2A, GPTU_T2B
//                32-bit timer:  GPTU_T2
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerName: 
//                Name of the timer to be stopped
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

#define GPTU_vStopTmr(TimerName) _GPTU_vStopTmr_##TimerName
#define _GPTU_vStopTmr_GPTU_T0A      GPTU_T012RUN_T0ARUN = 0
#define _GPTU_vStopTmr_GPTU_T0B      GPTU_T012RUN_T0BRUN = 0
#define _GPTU_vStopTmr_GPTU_T0C      GPTU_T012RUN_T0CRUN = 0
#define _GPTU_vStopTmr_GPTU_T0D      GPTU_T012RUN_T0DRUN = 0
#define _GPTU_vStopTmr_GPTU_T1A      GPTU_T012RUN_T1ARUN = 0
#define _GPTU_vStopTmr_GPTU_T1B      GPTU_T012RUN_T1BRUN = 0
#define _GPTU_vStopTmr_GPTU_T1C      GPTU_T012RUN_T1CRUN = 0
#define _GPTU_vStopTmr_GPTU_T1D      GPTU_T012RUN_T1DRUN = 0
#define _GPTU_vStopTmr_GPTU_T0A_B    GPTU_T012RUN &= ~0x0003
#define _GPTU_vStopTmr_GPTU_T0C_D    GPTU_T012RUN &= ~0x000C
#define _GPTU_vStopTmr_GPTU_T1A_B    GPTU_T012RUN &= ~0x0030
#define _GPTU_vStopTmr_GPTU_T1C_D    GPTU_T012RUN &= ~0x00C0
#define _GPTU_vStopTmr_GPTU_T0A_C    GPTU_T012RUN &= ~0x0007
#define _GPTU_vStopTmr_GPTU_T1A_C    GPTU_T012RUN &= ~0x0070
#define _GPTU_vStopTmr_GPTU_T0A_D    GPTU_T012RUN &= ~0x000F
#define _GPTU_vStopTmr_GPTU_T1A_D    GPTU_T012RUN &= ~0x00F0
#define _GPTU_vStopTmr_GPTU_T2A      GPTU_T012RUN_T2ACLRR = 1
#define _GPTU_vStopTmr_GPTU_T2B      GPTU_T012RUN_T2BCLRR = 1
#define _GPTU_vStopTmr_GPTU_T2       GPTU_T012RUN |=  0x4400


//****************************************************************************
// @Macro         GPTU_vSetReload(TimerName, Value) 
//
//----------------------------------------------------------------------------
// @Description   This macro loads the reload register of the selected GPTU 
//                timer.
//                The following definitions for TimerName are available:
//                 8-bit timer:  GPTU_T0A, GPTU_T0B, GPTU_T0C, GPTU_T0D
//                 8-bit timer:  GPTU_T1A, GPTU_T1B, GPTU_T1C, GPTU_T1D
//                16-bit timer:  GPTU_T0A_B, GPTU_T0C_D
//                16-bit timer:  GPTU_T1A_B, GPTU_T1C_D
//                24-bit timer:  GPTU_T0A_C, GPTU_T1A_C
//                32-bit timer:  GPTU_T0A_D, GPTU_T1A_D
//                16-bit timer:  GPTU_T2A_RC0, GPTU_T2A_RC1
//                16-bit timer:  GPTU_T2B_RC0, GPTU_T2B_RC1
//                32-bit timer:  GPTU_T2_RC0, GPTU_T2_RC1
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    TimerName: 
//                Name of the timer to be used
// @Parameters    Value: 
//                8/16/24/32-bit value for the reload register
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

#define GPTU_vSetReload(TimerName, Value) _GPTU_vSetReload_##TimerName(Value)
#define _GPTU_vSetReload_GPTU_T0A(Value)      GPTU_T0RA = Value
#define _GPTU_vSetReload_GPTU_T0B(Value)      GPTU_T0RB = Value
#define _GPTU_vSetReload_GPTU_T0C(Value)      GPTU_T0RC = Value
#define _GPTU_vSetReload_GPTU_T0D(Value)      GPTU_T0RD = Value
#define _GPTU_vSetReload_GPTU_T1A(Value)      GPTU_T1RA = Value
#define _GPTU_vSetReload_GPTU_T1B(Value)      GPTU_T1RB = Value
#define _GPTU_vSetReload_GPTU_T1C(Value)      GPTU_T1RC = Value
#define _GPTU_vSetReload_GPTU_T1D(Value)      GPTU_T1RD = Value
#define _GPTU_vSetReload_GPTU_T0A_B(Value)    GPTU_T0RA_B = Value
#define _GPTU_vSetReload_GPTU_T0C_D(Value)    GPTU_T0RC_D = Value
#define _GPTU_vSetReload_GPTU_T1A_B(Value)    GPTU_T1RA_B = Value
#define _GPTU_vSetReload_GPTU_T1C_D(Value)    GPTU_T1RC_D = Value
#define _GPTU_vSetReload_GPTU_T0A_C(Value)    GPTU_T0RA_C = Value
#define _GPTU_vSetReload_GPTU_T1A_C(Value)    GPTU_T1RA_C = Value
#define _GPTU_vSetReload_GPTU_T0A_D(Value)    GPTU_T0RA_D = Value
#define _GPTU_vSetReload_GPTU_T1A_D(Value)    GPTU_T1RA_D = Value
#define _GPTU_vSetReload_GPTU_T2A_RC0(Value)  GPTU_T2R0_A = Value
#define _GPTU_vSetReload_GPTU_T2A_RC1(Value)  GPTU_T2R1_A = Value
#define _GPTU_vSetReload_GPTU_T2B_RC0(Value)  GPTU_T2R0_B = Value
#define _GPTU_vSetReload_GPTU_T2B_RC1(Value)  GPTU_T2R1_B = Value
#define _GPTU_vSetReload_GPTU_T2_RC0(Value)   GPTU_T2R0_A_B = Value
#define _GPTU_vSetReload_GPTU_T2_RC1(Value)   GPTU_T2R1_A_B = Value


//****************************************************************************
// @Macro         GPTU_uwGetReload(TimerName) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the content of the reload register of 
//                the selected GPTU timer.
//                The following definitions for TimerName are available:
//                 8-bit timer:  GPTU_T0A, GPTU_T0B, GPTU_T0C, GPTU_T0D
//                 8-bit timer:  GPTU_T1A, GPTU_T1B, GPTU_T1C, GPTU_T1D
//                16-bit timer:  GPTU_T0A_B, GPTU_T0C_D
//                16-bit timer:  GPTU_T1A_B, GPTU_T1C_D
//                24-bit timer:  GPTU_T0A_C, GPTU_T1A_C
//                32-bit timer:  GPTU_T0A_D, GPTU_T1A_D
//                16-bit timer:  GPTU_T2A_RC0, GPTU_T2A_RC1
//                16-bit timer:  GPTU_T2B_RC0, GPTU_T2B_RC1
//                32-bit timer:  GPTU_T2_RC0, GPTU_T2_RC1
//
//----------------------------------------------------------------------------
// @Returnvalue   Current 8/16/24/32-bit value of the reload register
//
//----------------------------------------------------------------------------
// @Parameters    TimerName: 
//                Name of the timer to be used
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

#define GPTU_uwGetReload(TimerName) _GPTU_uwGetReload_##TimerName
#define _GPTU_uwGetReload_GPTU_T0A      GPTU_T0RA
#define _GPTU_uwGetReload_GPTU_T0B      GPTU_T0RB
#define _GPTU_uwGetReload_GPTU_T0C      GPTU_T0RC
#define _GPTU_uwGetReload_GPTU_T0D      GPTU_T0RD
#define _GPTU_uwGetReload_GPTU_T1A      GPTU_T1RA
#define _GPTU_uwGetReload_GPTU_T1B      GPTU_T1RB
#define _GPTU_uwGetReload_GPTU_T1C      GPTU_T1RC
#define _GPTU_uwGetReload_GPTU_T1D      GPTU_T1RD
#define _GPTU_uwGetReload_GPTU_T0A_B    GPTU_T0RA_B
#define _GPTU_uwGetReload_GPTU_T0C_D    GPTU_T0RC_D
#define _GPTU_uwGetReload_GPTU_T1A_B    GPTU_T1RA_B
#define _GPTU_uwGetReload_GPTU_T1C_D    GPTU_T1RC_D
#define _GPTU_uwGetReload_GPTU_T0A_C    GPTU_T0RA_C
#define _GPTU_uwGetReload_GPTU_T1A_C    GPTU_T1RA_C
#define _GPTU_uwGetReload_GPTU_T0A_D    GPTU_T0RA_D
#define _GPTU_uwGetReload_GPTU_T1A_D    GPTU_T1RA_D
#define _GPTU_uwGetReload_GPTU_T2A_RC0  GPTU_T2R0_A
#define _GPTU_uwGetReload_GPTU_T2A_RC1  GPTU_T2R1_A
#define _GPTU_uwGetReload_GPTU_T2B_RC0  GPTU_T2R0_B
#define _GPTU_uwGetReload_GPTU_T2B_RC1  GPTU_T2R1_B
#define _GPTU_uwGetReload_GPTU_T2_RC0   GPTU_T2R0_A_B
#define _GPTU_uwGetReload_GPTU_T2_RC1   GPTU_T2R1_A_B


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************


// USER CODE BEGIN (GPTU_Header,9)

// USER CODE END


#endif  // ifndef _GPTU_H_
