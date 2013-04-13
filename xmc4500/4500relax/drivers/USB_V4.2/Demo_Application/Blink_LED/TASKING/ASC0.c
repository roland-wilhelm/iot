//****************************************************************************
// @Module        Asynchronous Synchronous Serial Interface 0 (ASC0)
// @Filename      ASC0.c
// @Project       USBBlinkingLED.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1130
//
// @Compiler      Tasking
//
// @Codegenerator 1.3
//
// @Description   This file contains functions that use the ASC0 module.
//
//----------------------------------------------------------------------------
// @Date          12/21/2005 10:17:41 AM
//
//****************************************************************************

// USER CODE BEGIN (ASC0_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (ASC0_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (ASC0_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (ASC0_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (ASC0_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (ASC0_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (ASC0_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (ASC0_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (ASC0_General,9)
void ASC0_viRx(void);

// USER CODE END


//****************************************************************************
// @Function      void ASC0_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the ASC0 function 
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

void ASC0_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - enable the ASC0 module
  ///  - clock divider for normal operation mode: System clock / 1 (= 96.0000 
  ///    MHz; 10.417 ns )
  ///  - the ASC0 module is stopped during sleep mode

  MAIN_vResetENDINIT();
  ASC0_CLC       =  0x00000100;  // load clock control register
  MAIN_vSetENDINIT();

  ///  -----------------------------------------------------------------------
  ///  Configuration of the ASC0 Baudrate Generator:
  ///  -----------------------------------------------------------------------
  ///  - the ASC0 module clock is 96 MHz
  ///  - fractional divider as prescaler for baud rate timer is used

  ASC0_FDV       =  0x01CE;      // load ASC0 fractional divider register

  ///  - required baud rate = 115.200 kbaud
  ///  - real baud rate     = 115.193 kbaud
  ///  - deviation          = -0.006 %

  ASC0_BG        =  0x002E;      // load ASC0 baud rate time reload register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the ASC0 Operation Mode:
  ///  -----------------------------------------------------------------------
  ///  - 8-bit data asychronous operation with one stop bit


  ///  - receiver is enabled

  ASC0_CON       =  0x0811;      // load ASC0 control register

  ///  -----------------------------------------------------------------------
  ///  FIFO Configuration:
  ///  -----------------------------------------------------------------------
  ///  - receive FIFO is disabled
  ///  - transmit FIFO is disabled

  ASC0_RXFCON    =  0x00000100;  // load ASC0 receive FIFO control register
  ASC0_TXFCON    =  0x00000100;  // load ASC0 transmit FIFO control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used ASC0 Port Pins:
  ///  -----------------------------------------------------------------------
  ASC0_PISEL     =  0x0001;      // load peripheral input selection register

  ///  - P2.1 is used for ASC0 transmit output signal (ASC0_TXD)
  ///  - P2.0 is used for ASC0 input/output signal (ASC0_RXD)

  P2_ALTSEL0    |=  0x0002;      // select alternate output function
  P2_DIR        |=  0x0002;      // set direction register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used ASC0 Interrupts:
  ///  -----------------------------------------------------------------------
  ///  - Rx service request node configuration:
  ///  - Rx interrupt priority level (SRPN) = 75
  ///  - Rx CPU interrupt is selected

  ASC0_RSRC      =  0x0000104B;  // set service request control register


  //   -----------------------------------------------------------------------
  //   Default Settings for Service Request Flags:
  //   -----------------------------------------------------------------------
  ASC0_TBSRC_SETR  =  1;         // indicates that the transmit buffer is 
                                 // empty
  ASC0_TSRC_SETR  =  1;          // indicates that the transmit register is 
                                 // empty

  // USER CODE BEGIN (ASC0_Function,3)

  // USER CODE END

  ASC0_CON      |=  0x8000;      // enable baud rate generator


} //  End of function ASC0_vInit


//****************************************************************************
// @Function      void ASC0_vSendData(ushort usData) 
//
//----------------------------------------------------------------------------
// @Description   This function writes a send data initialization word into 
//                the transmit buffer register.
//                
//                Note: 
//                In a multiprocessor system the master with this function 
//                has the possibility to send data to the selected slave. To 
//                achieve this, the 9th bit must set on zero.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    usData: 
//                Data to be send
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

// USER CODE BEGIN (SendData,1)

// USER CODE END

void ASC0_vSendData(ushort usData)
{
  ASC0_TBSRC_CLRR = 1;   //  reset transmit buffer interrupt request 
  ASC0_TBUF  = usData;   //  load transmit buffer register

} //  End of function ASC0_vSendData


//****************************************************************************
// @Function      ushort ASC0_usGetData(void) 
//
//----------------------------------------------------------------------------
// @Description   This function reads out the content of the receive buffer 
//                register which contains the received data.
//
//----------------------------------------------------------------------------
// @Returnvalue   data that has been received
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

// USER CODE BEGIN (GetData,1)

// USER CODE END

ushort ASC0_usGetData(void)
{
  return(ASC0_RBUF);     // return receive buffer register

} //  End of function ASC0_usGetData


//****************************************************************************
// @Function      void ASC0_viRx(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the receive interrupt service routine for the ASC0. 
//                It is called if the data has been received. 
//                Please note that you have to add application specific code 
//                to this function.
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

// USER CODE BEGIN (Rx,1)

void PrintOut(const char *format, ...);
void SendStatus();
extern unsigned char BlinkingLEDSpeed;
extern int BlinkingLEDState;
// USER CODE END

void __interrupt (ASC0_RINT) ASC0_viRx(void)
{

  // USER CODE BEGIN (Rx,2)
		unsigned char c = ASC0_usGetData();
		switch (c)
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
		case 'i':
			PrintOut("Status:\n\rT0RDBCA: 0x%.8x\n\r",GPTU_T0RDCBA);
			PrintOut("T0DBCA: 0x%.8x\n\r",GPTU_T0DCBA);
			break;
		default:
			break;
		}
		SendStatus();

  // USER CODE END

} //  End of function ASC0_viRx


//****************************************************************************
// @Function      ubyte ASC0_ubTxDataReady(void) 
//
//----------------------------------------------------------------------------
// @Description   This function can be used for checking up the status of the 
//                ASC0 transmit interrupt flags. This shows when the sending 
//                of data has terminated. By continuously polling this flag 
//                after the function ASC0_vSendData has been called, it is 
//                possible to establish when the ASC0 has terminated its task.
//
//----------------------------------------------------------------------------
// @Returnvalue   0 if transmitter is busy, else 1
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          12/21/2005
//
//****************************************************************************

// USER CODE BEGIN (TxDataReady,1)

// USER CODE END

ubyte ASC0_ubTxDataReady(void)
{
  ubyte ubReturnValue;

  ubReturnValue = 0;

  if(ASC0_TSRC_SRR)              // if sending of data is terminated
  {
    ubReturnValue = 1;
    ASC0_TSRC_CLRR = 1;
  }
  return(ubReturnValue);         // return receive buffer register

} //  End of function ASC0_ubTxDataReady




// USER CODE BEGIN (ASC0_General,10)

// USER CODE END

