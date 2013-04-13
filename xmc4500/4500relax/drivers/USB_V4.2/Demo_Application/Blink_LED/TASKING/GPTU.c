//****************************************************************************
// @Module        General Purpose Timer Unit (GPTU)
// @Filename      GPTU.c
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      Tasking
//
// @Codegenerator 1.3
//
// @Description   This file contains functions that use the GPTU module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:17:41 AM
//
//****************************************************************************

// USER CODE BEGIN (GPTU_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (GPTU_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (GPTU_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (GPTU_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (GPTU_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************


// USER CODE BEGIN (GPTU_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (GPTU_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (GPTU_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (GPTU_General,9)

// USER CODE END


//****************************************************************************
// @Function      void GPTU_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the GPTU function 
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

void GPTU_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - enable the GPTU module
  ///  - clock divider for normal operation mode: System clock / 1 (= 96.0000 
  ///    MHz; 10.417 ns )
  ///  - the GPTU module is stopped during sleep mode

  MAIN_vResetENDINIT();
  GPTU_CLC       =  0x00000100;  // load clock control register
  MAIN_vSetENDINIT();


  ///  -----------------------------------------------------------------------
  ///  Configuration of T0 and T1 Global Inputs:
  ///  -----------------------------------------------------------------------
  ///  - T0 and T1 global input 0 selection: T2A over-/underflow
  ///  - T0 and T1 global input 1 selection: T2B over-/underflow

  ///  -----------------------------------------------------------------------
  ///  Configuration of T0 and T1:
  ///  -----------------------------------------------------------------------
  ///  Timer T0A configuration:
  ///  - timer T0A input selection: Clock input (= 96.000 MHz)
  ///  - timer T0A overflows after 2.6667 탎
  ///  - reload Timer T0A on overflow of timer T0A
  ///  - timer T0A is started

  ///  Timer T1A configuration:
  ///  - timer T1A input selection: Clock input (= 96.000 MHz)
  ///  - timer T1A overflows after 2.6667 탎
  ///  - reload Timer T1A on overflow of timer T1A
  ///  - timer T1A is stopped

  ///  Timer T0B configuration:
  ///  - timer T0B input selection: Carry input from timer T0A (concatenation)
  ///  - timer T0B overflows after 682.6667 탎
  ///  - reload Timer T0B on overflow of timer T0B
  ///  - timer T0B is started

  ///  Timer T1B configuration:
  ///  - timer T1B input selection: Clock input (= 96.000 MHz)
  ///  - timer T1B overflows after 2.6667 탎
  ///  - reload Timer T1B on overflow of timer T1B
  ///  - timer T1B is stopped

  ///  Timer T0C configuration:
  ///  - timer T0C input selection: Carry input from timer T0B (concatenation)
  ///  - timer T0C overflows after 87.3813 ms
  ///  - reload Timer T0C on overflow of timer T0C
  ///  - timer T0C is started

  ///  Timer T1C configuration:
  ///  - timer T1C input selection: Clock input (= 96.000 MHz)
  ///  - timer T1C overflows after 2.6667 탎
  ///  - reload Timer T1C on overflow of timer T1C
  ///  - timer T1C is stopped

  ///  Timer T0D configuration:
  ///  - timer T0D input selection: Carry input from timer T0C (concatenation)
  ///  - timer T0D overflows after 699.0507 ms
  ///  - reload Timer T0D on overflow of timer T0D
  ///  - timer T0D is started

  ///  Timer T1D configuration:
  ///  - timer T1D input selection: Clock input (= 96.000 MHz)
  ///  - timer T1D overflows after 2.6667 탎
  ///  - reload Timer T1D on overflow of timer T1D
  ///  - timer T1D is stopped

  ///  -----------------------------------------------------------------------
  ///  Configuration of T0 and T1 Output Signals:
  ///  -----------------------------------------------------------------------
  ///  - output source selection OUT00: T0D overflow
  ///  - output source selection OUT01: T0A overflow
  ///  - output source selection OUT10: T1A overflow
  ///  - output source selection OUT11: T1A overflow
  ///  - trigger output source selection TRG00: T0A overflow
  ///  - trigger output source selection TRG01: T0A overflow
  ///  - trigger output source selection TRG10: T1A overflow
  ///  - trigger output source selection TRG11: T1A overflow
  ///  - service request source selection SR00: T0A overflow
  ///  - service request source selection SR01: T0A overflow
  ///  - service request source selection SR10: T1A overflow
  ///  - service request source selection SR11: T1A overflow

  GPTU_T01IRS    =  0x000000FC;  // load  T0/T1 input/reload source selection 
                                 // register
  GPTU_T01OTS    =  0x00000003;  // load T0/T1 output/trigger/service req. 
                                 // register
  GPTU_T0DCBA    =  0xF8800000;  // load timer T0 count register
  GPTU_T0RDCBA   =  0xF8800000;  // load timer T0 reload register
  GPTU_T1DCBA    =  0x00000000;  // load timer T1 count register
  GPTU_T1RDCBA   =  0x00000000;  // load timer T1 reload register

  ///  -----------------------------------------------------------------------
  ///  Timer T2 Split Mode:
  ///  -----------------------------------------------------------------------
  ///  - timer T2 operates as one 32-bit timer - control are via T2A controls

  ///  -----------------------------------------------------------------------
  ///  Configuration of T2 External Inputs:
  ///  -----------------------------------------------------------------------
  ///  - external start input selection: input is disabled
  ///  - external stop input selection: input is disabled
  ///  - external up/down input selection: input is disabled
  ///  - external clear input selection: input is disabled
  ///  - external reload/capture 0 input selection: T0A overflow
  ///  - external reload/capture 1 input selection: T0A overflow
  ///  - external count input selection: T0A overflow

  GPTU_T2AIS     =  0x00000000;  // load T2A external input selection register
  GPTU_T2ES      =  0x00000000;  // load T2 external input edge selection 
                                 // register

  ///  -----------------------------------------------------------------------
  ///  Configuration of T2A:
  ///  -----------------------------------------------------------------------
  ///  - timer T2A input clock (= 96.000 MHz)
  ///  - clear on external signal Clear_A (= input is disabled)
  ///  - T2A continues to run after over- or underflow
  ///  - T2A count up (software controlled)
  ///  - timer T2A is stopped
  ///  - T2A overflow is generated for FF..FF -> 00..00, underflow for 00..00 
  ///    -> FF..FF

  ///  T2A capture/reload 0 configuration:
  ///  - T2A capture/reload mode is disabled
  ///  T2A capture/reload 1 configuration:
  ///  - T2A capture/reload mode is disabled

  GPTU_T2CON     =  0x00000000;  // load timer T2 mode control register
  GPTU_T2RCCON   =  0x00000000;  // load T2 reload/capture mode control 
                                 // register
  GPTU_T2RC0     =  0x00000000;  // load timer T2 reload/capture register 0
  GPTU_T2RC1     =  0x00000000;  // load timer T2 reload/capture register 1
  GPTU_T2        =  0x00000000;  // load timer T2 count register

  ///  -----------------------------------------------------------------------
  ///  Configuration of GPTU External Outputs:
  ///  -----------------------------------------------------------------------
  ///  - output 0 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 1 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 2 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 3 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 4 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 5 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 6 source selection: Timer T0 signal OUT00 (= T0D overflow)
  ///  - output 7 source selection: Timer T0 signal OUT00 (= T0D overflow)

  GPTU_OSEL      =  0x00000000;  // load output source selection register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used GPTU Port Pins:
  ///  -----------------------------------------------------------------------
  ///  - P0.7 is used for GPTU output signal (GPTU_OUT7)

  P0_ALTSEL0    |=  0x0080;      // select alternate output function
  P0_DIR        |=  0x0080;      // set direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 7:
  ///  -----------------------------------------------------------------------

  GPTU_SRSEL     =  0x00000000;  // load service request source selection 
                                 // register

  ///  GPTU service request node 0 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 1 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 2 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 3 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 4 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 5 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 6 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)

  ///  GPTU service request node 7 configuration:
  ///  - source selection: Timer T2A signal Start_A (= input is disabled)


  // USER CODE BEGIN (Init,3)

  // USER CODE END

  //   -----------------------------------------------------------------------
  //   Default Settings for Timer Start Flags:
  //   -----------------------------------------------------------------------
  //   - start timer T0D
  //   - start timer T0C
  //   - start timer T0B
  //   - start timer T0A

  GPTU_T012RUN  |=  0x0000000F; 


  // USER CODE BEGIN (Init,4)

  // USER CODE END


} //  End of function GPTU_vInit



// USER CODE BEGIN (GPTU_General,10)

// USER CODE END

