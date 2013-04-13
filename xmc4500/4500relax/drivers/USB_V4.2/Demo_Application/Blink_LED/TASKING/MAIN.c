//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.c
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      Tasking
//
// @Codegenerator 1.3
//
// @Description   This file contains the project initialization function.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:17:41 AM
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

#include "usb_iil_api.h "
#include "compiler.h"
#include "sys_api.h"
// USER CODE BEGIN (MAIN_General,2)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

#define RESET_INDICATOR     ((RST_SR & 0xFF000000) >> 24)
#define DEEPSLEEP_WAKEUP    0x80
#define WATCHDOG_RESET      0x40
#define SOFTWARE_RESET      0x20
#define HARDWARE_RESET      0x10
#define POWERON_RESET       0x08

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************
// USER CODE BEGIN (MAIN_General,7)

int BlinkingLEDState = 1;
unsigned char BlinkingLEDSpeed = 0xf8;

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller.
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

void MAIN_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  //// -----------------------------------------------------------------------
  //// Begin of Important Settings for the Start-Up File
  //// -----------------------------------------------------------------------
  ///  All following settings must be set in the start-up file. You can use 
  ///  DAvE's project file (*.dpt) to include this register values into your 
  ///  compiler EDE.

    ///  ---------------------------------------------------------------------
    ///  FPI Bus Control Unit (BCU):
    ///  ---------------------------------------------------------------------
    ///  BCU starvation protection is enabled
    ///  BCU power saving is disabled
    ///  the debug trace is enabled. Error information is captured in 
    ///  register BCEADD, BCEDAT and BCECON
    ///  sample period of request for starvation protection: 64
    ///  BCU bus time-out value: 65536 cycles

    //// this register must be set in the start-up file
    //// SBCU_CON  =  0x4009FFFF;

    ///  ---------------------------------------------------------------------
    ///  Program Memory Interface (PMI):
    ///  ---------------------------------------------------------------------
    ///  ICACHE settings:
    ///  the instruction cache is bypassed
    ///  the instruction cache is enabled PMI_CON0_CC2SPR = 0
    ///  the instruction cache is in normal operation PMI_CON1_CCINV = 0 

    //// this register must be set in the start-up file
    //// PMI_CON0  =  0x00000002;


    //// this register must be set in the start-up file
    //// PMI_CON1  =  0x00000000;


    //// this register must be set in the start-up file
    //// PMI_CON2  =  0x00000053;

    ///  ---------------------------------------------------------------------
    ///  LMB External Bus Unit (EBU):
    ///  ---------------------------------------------------------------------
    ///  - enable the EBU module clock

    //// this register must be set in the start-up file
    //// EBU_CLC  =  0x00000000;

    ///  External Arbitration:
    ///  - arbitration mode: arbiter mode
    ///  - arbitration inputs are asynchronous
    ///  - external bus is not locked after EBU gains ownership
    ///  - disable Time-out
    ///  - normal region/#CS0 logic is disabled; all external bus accesses 
    ///    are directed to region 0
    ///  - normal region/#CSemu logic is in operation

    ///  Global Chip Select Activation:
    ///  - activate #CSglb on an access to address region 0

    //// this register must be set in the start-up file
    //// EBU_CON  =  0x08010068;

    ///  Address Region 0:
    ///  - enable memory region 0
    ///  - address: No valid segment - 0xA7FFFFFF
    ///  - length of the region: 128 Mbyte
    ///  - asynchronous 32-bit non-mux
    ///  - writes to memory region are disabled
    ///  - external waitstate insertion is disabled
    ///  - pin #WAIT is low active
    ///  - byte control signal control: to follow control signal (RD, RD/WR)
    ///  - data access is always fed from the external bus access
    ///  - alignment is according to the settings of the PORTW field
    ///  - code access never uses prefetch buffer mechanism
    ///  - code prefetch can be aborted by an interrupting data access
    ///  - cycle multiplier is 32
    ///  - address cycles: 3 * 32 = 96 cycles
    ///  - programmed command delay cycles: 7 * 32 = 224 cycles
    ///  - wait states for read accesses: 7 * 32 = 224 cycles
    ///  - wait states for write accesses: 7 * 32 = 224 cycles
    ///  - data hold cycles for write accesses: 3 * 32 = 96 cycles
    ///  - recovery cycles after read accesses: 7 * 32 = 224 cycles
    ///  - recovery cycles after write accesses: 7 * 32 = 224 cycles
    ///  - recovery cycles between read and write accesses: 15 * 32 = 480 
    ///    cycles
    ///  - recovery cycles between different regions: 15 * 32 = 480 cycles

    //// this register must be set in the start-up file
    //// EBU_ADDRSEL0  =  0xA0000001;
    //// EBU_BUSCON0  =  0x8092837F;
    //// EBU_BUSAP0  =  0xFFFFFFFF;

    ///  Address Region 1:
    ///  - disable memory region 1

    //// this register must be set in the start-up file
    //// EBU_ADDRSEL1  =  0x00000000;
    //// EBU_BUSCON1  =  0x8092837F;
    //// EBU_BUSAP1  =  0xFFFFFFFF;

    ///  Address Region 2:
    ///  - disable memory region 2

    //// this register must be set in the start-up file
    //// EBU_ADDRSEL2  =  0x00000000;
    //// EBU_BUSCON2  =  0x8092837F;
    //// EBU_BUSAP2  =  0xFFFFFFFF;

    ///  Address Region 3:
    ///  - disable memory region 3

    //// this register must be set in the start-up file
    //// EBU_ADDRSEL3  =  0x00000000;
    //// EBU_BUSCON3  =  0x8092837F;
    //// EBU_BUSAP3  =  0xFFFFFFFF;

    ///  Emulator Address Region :
    ///  - disable emulator memory region

    //// this register must be set in the start-up file
    //// EBU_EMUAS  =  0xDE000030;
    //// EBU_EMUBC  =  0x01902077;
    //// EBU_EMUBAP  =  0x52484911;

    ///  Overlay Chip Select Activation:
    ///  - no activation selected

    //// this register must be set in the start-up file
    //// EBU_EMUOVL  =  0x00000000;

    ///  Burst Flash:
    ///  - external clock at pin BFCLKO = 1/4 of LMB_CLK (= 24.000 MHz)
    ///  - latency cycle control = 0 LMB_CLK cycles
    ///  - clock signal is only present at pin BFCLKO during a Burst Flash 
    ///    burst access

    ///  Setup 0:
    ///  - flash burst buffer length is 1 data accesses
    ///  - #WAIT input operates as wait data bus function on bursts
    ///  - ADV and BAA are delayed by 1/2 an LMB_CLK period
    ///  - EBU automatically re-aligns any non-aligned burst accesses to a 
    ///    type 0 device so that data can be fetched from the device in a 
    ///    single burst transaction

    ///  Setup 1:
    ///  - flash burst buffer length is 1 data accesses
    ///  - #WAIT input operates as wait data bus function on bursts
    ///  - ADV and BAA are delayed by 1/2 an LMB_CLK period
    ///  - EBU automatically re-aligns any non-aligned burst accesses to a 
    ///    type 1 device so that data can be fetched from the device in a 
    ///    single burst transaction

    //// this register must be set in the start-up file
    //// EBU_BFCON  =  0x001001D0;

    ///  ---------------------------------------------------------------------
    ///  Memory Management Unit (MMU)
    ///  ---------------------------------------------------------------------
    //// this register must be set in the start-up file
    ///  System is configured for Physical Mode 
    ///  Page Size A is 1 KB
    ///  Page Size B is 1 KB
    //// MMU_CON  =  0x000007E0; // load MMU Configuration register

  //// -----------------------------------------------------------------------
  //// End of Important Settings for the Start-Up File
  //// -----------------------------------------------------------------------

  ///  -----------------------------------------------------------------------
  ///  Clock System:
  ///  -----------------------------------------------------------------------
  ///  - external clock frequency: 20.000 MHz
  ///  - input divider (PDIV): 4
  ///  - PLL operation (pin BYPASS = 0)
  ///  - VCO range: 400 MHz - 500 MHz
  ///  - feedback divider (NDIV): 96
  ///  - the VCO output frequency is: 480.000 MHz
  ///  - output divider (KDIV): 5
  ///  - CPU clock: 96.000 MHz
  ///  - the ratio fcpu / fsys is 1 / 1
  //// - the internal system clock is to HIGH (96.000 MHz)

  MAIN_vResetENDINIT();
  PLL_CLC_VCOBYP  =  1;          // set VCO bypass
  PLL_CLC_OSCDISC  =  0;         // connect OSC to PLL
  PLL_CLC        =  0x005F6426;  // set P,N and K divider
  while (!(PLL_CLC & 0x1));     // wait for LOCK
  PLL_CLC_VCOBYP  =  0;          // reset VCO bypass
  MAIN_vSetENDINIT();

  ///  -----------------------------------------------------------------------
  ///  Interrupt System:
  ///  -----------------------------------------------------------------------
  ///  - four arbitration cycles (max. 255 interrupt sources)
  ///  - two clocks per arbitration cycle

  MTCR(0xFE2C,  0x00000000);     // load CPU interrupt control register
  ISYNC();

  ///  -----------------------------------------------------------------------
  ///  Interrupt System:
  ///  -----------------------------------------------------------------------
  ///  - four arbitration cycles (max. 255 interrupt sources)
  ///  - two clocks per arbitration cycle

  ///  -----------------------------------------------------------------------
  ///  Configuration of the DMA Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - enable the DMA module
  ///  - note: the DMA clock is also used for the MLI modules as a common 
  ///    clock that can be individually divided for the MLI modules.

  MAIN_vResetENDINIT();
  DMA_CLC        =  0x00000000;  // DMA clock control register
  MAIN_vSetENDINIT();

  //   -----------------------------------------------------------------------
  //   Initialization of the Peripherals:
  //   -----------------------------------------------------------------------
  //   initializes the General Purpose Timer Unit (GPTU)
  GPTU_vInit();

  //   initializes the Asynchronous Synchronous Serial Interface 0 (ASC0)
  ASC0_vInit();

  //   initializes the System Control Unit (SCU)
  SCU_vInit();

  //   initializes the Universal Serial Bus(USB)
USBD_device_initialize();


  // USER CODE BEGIN (Init,3)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  System Start Conditions:
  ///  -----------------------------------------------------------------------

  ///  - the CPU interrupt system is globally enabled
  ENABLE();
}

//****************************************************************************
// @Function      void MAIN_vWriteWDTCON0(uword uwValue) 
//
//----------------------------------------------------------------------------
// @Description   This function writes the parameter uwValue to the WDT_CON0 
//                register which is password protected. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    uwValue: 
//                Value for the WDTCON0 register
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

// USER CODE BEGIN (WriteWDTCON0,1)

// USER CODE END

void MAIN_vWriteWDTCON0(uword uwValue)
{
  uword uwDummy;

  uwDummy  =  WDT_CON0;
  uwDummy |=  0x000000F0;       //  set HWPW1 = 1111b

  if(WDT_CON1_WDTDR)
  {
    uwDummy |=  0x00000008;     //  set HWPW0 = WDTDR
  }
  else
  {
    uwDummy &= ~0x00000008;     //  set HWPW0 = WDTDR
  }
  if(WDT_CON1_WDTIR)
  {
    uwDummy |=  0x00000004;     //  set HWPW0 = WDTIR
  }
  else
  {
    uwDummy &= ~0x00000004;     //  set HWPW0 = WDTIR
  }

  uwDummy &= ~0x00000002;       //  set WDTLCK = 0
  WDT_CON0 =  uwDummy;          //  unlock access

  uwValue  |=  0x000000F2;      //  set HWPW1 = 1111b and WDTLCK = 1
  uwValue  &= ~0x0000000C;      //  set HWPW0 = 00b
  WDT_CON0  =  uwValue;         //  write access and lock

} //  End of function MAIN_vWriteWDTCON0


//****************************************************************************
// @Function      sword main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
//
//----------------------------------------------------------------------------
// @Returnvalue   Returns an sword value
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

// USER CODE BEGIN (Main,1)

void PrintOut(const char *format, ...)
{
	int i;
  const int buffersize = 2048;
  va_list argptr;
  
  char buffer[buffersize];

  // print to buffer
  va_start(argptr,format);
  vsprintf(buffer,format,argptr);
  buffer[buffersize-1] = 0;

  // send buffer to output window (synchronous behavior)
  for (i=0;i<strlen(buffer);i++)
  {
	  while (!ASC0_ubTxBufFree());
	  ASC0_vSendData(buffer[i]);
  }


  va_end(argptr);

}

void SendStatus()
{
	PrintOut("Transmitting status:\n\r\tState is %s\n\r\tSpeed is: 0x%.2x\n\r\t",BlinkingLEDState==0?"Not Blinking":"Blinking",BlinkingLEDSpeed);
}
// USER CODE END

sword main(void)
{
  sword swReturn;

  // USER CODE BEGIN (Main,2)
	unsigned char Buffer[64];
	int nBytesTransmit = 64;
	int val;
  // USER CODE END

  swReturn = 0;

  switch(RESET_INDICATOR)
  {
    case DEEPSLEEP_WAKEUP:       //  the last reset was an external triggered
                                 //  hardware reset in deep sleep mode 
                                 //  (wake-up reset)

         // USER CODE BEGIN (Main,3)

         // USER CODE END

    case WATCHDOG_RESET:         //  the last reset was a watchdog triggered
                                 //  (hardware) reset

         // USER CODE BEGIN (Main,4)

         // USER CODE END

    case SOFTWARE_RESET:         //  the last reset was an internally 
                                 //  triggered software reset

         // USER CODE BEGIN (Main,5)

         // USER CODE END

    case HARDWARE_RESET:         //  the last reset was an externally
                                 //  triggered hardware reset (#HRST pin)

         // USER CODE BEGIN (Main,6)

         // USER CODE END

    case POWERON_RESET:          //  the last reset was an externally
                                 //  triggered power on reset (#POR pin)

         // USER CODE BEGIN (Main,7)

         // USER CODE END

    default:

         // USER CODE BEGIN (Main,8)

         // USER CODE END

         MAIN_vInit();
  }


  // USER CODE BEGIN (Main,9)

	PrintOut("\n\r Welcome to Blinky LED USB Application\n\r");
	PrintOut("\n\r Open the GUI Application\n\r");
	PrintOut("\n\r Click on Open&Configure\n\r");
	PrintOut("\n\r Click on Bind Out Pipe for binding the Out Pipe \n\r");	
	PrintOut("\n\r Click on Bind IN Pipe for binding the IN Pipe \n\r");
	PrintOut("\n\r Click on Start Read-Thread \n\r");	
	PrintOut("\n\r Click on Faster/Slower to vary the speed of LED\n\r");	
	while (1)
	{
		static int count = 0;
		IFX_UINT8 pData[64];
		IFX_SINT16 nBytesRequest = 64, nBytesReceived;
		if (USBD_get_device_state() == USB_CONFIGURED)
		{
			nBytesReceived  = USB_receive(pData, nBytesRequest, 0x02);
			count ++;

			if(nBytesReceived > 0)
			{
				switch (pData[0])
				{
				case '0':
					PrintOut("Request to Stop the Blinking LED\n\r");
					GPTU_vStopTmr(GPTU_T0A_D);
					BlinkingLEDState = 0;
					break;
				case '1':
					PrintOut("Request to Start the Blinking LED\n\r");
					GPTU_vStartTmr(GPTU_T0A_D);
					BlinkingLEDState = 1;
					break;
				case '+':
					if (BlinkingLEDSpeed<0xff)
					{
						BlinkingLEDSpeed ++;
						GPTU_vSetReload(GPTU_T0D,BlinkingLEDSpeed);
						PrintOut("Request to Increase the Blinking LED Speed:\t0x%.2x\n\r",BlinkingLEDSpeed);
					}
					break;
				case '-':
					if (BlinkingLEDSpeed>0xf0)
					{
						BlinkingLEDSpeed --;
						GPTU_vSetReload(GPTU_T0D,BlinkingLEDSpeed);
						PrintOut("Request to Decrease the Blinking LED Speed:\t0x%.2x\n\r",BlinkingLEDSpeed);
					}
					break;
				default:
					break;
				}
				Buffer[0] = (unsigned char)BlinkingLEDState;
				Buffer[1] = BlinkingLEDSpeed;

				val = USBD_transmit(0x01, Buffer, nBytesTransmit, 0);

			}
		//	SendStatus();
		}
	}

  // USER CODE END

  return(swReturn);

} //  End of function main



// USER CODE BEGIN (MAIN_General,10)

// USER CODE END

