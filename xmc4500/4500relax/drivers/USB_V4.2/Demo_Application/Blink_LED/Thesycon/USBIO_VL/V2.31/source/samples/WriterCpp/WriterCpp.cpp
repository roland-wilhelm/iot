/************************************************************************
 *
 *  Module:       WriterCpp.cpp
 *  Long name:    Write to an Interrupt or Bulk pipe 
 *                using the USBIO C++ Class Library
 *  Description:  
 *  This module is a simple command line application, which writes data to
 *  an USB Pipe (Endpoint).
 *  The module shows three ways to send data to an USB device. One method
 *  uses a specialized class derived from the UsbIoWriter class.
 *
 *
 *  Runtime Env.: Win32 console application
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

// for shorter and faster windows.h
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

/********************************** Includes *****************************/
// Windows
#include <windows.h>
// standard libraries
#include <stdio.h>
#include <conio.h>
// our Writer class
// The MyWriter class is derived from CUsbIoWriter.
// It inherits all the functions of CUsbIo and CUsbIoPipe.
#include "MyWriter.h"

/********************************** Parameters ***************************/
// check the following parameters and adapt them to the actual USB device

// size of the I/O buffer in bytes
// The size should be a multiple of the endpoint's fifo size.
#define BUFFER_SIZE     640

// number of I/O buffers used
#define NB_OF_BUFFERS   5


// configuration
//
// index to be used for "GetConfigurationDescriptor"
// This parameter is greater than 0 for multiconfiguration devices only.
#define CONFIG_INDEX  0
// number of interfaces, all possible interfaces must be activated 
// The number of interfaces can be changed, if the MultiInterface (Composit) 
// device driver from Microsoft is installed
#define CONFIG_NB_OF_INTERFACES   1
// settings per interface
// This application uses one interface only.
#define CONFIG_INTERFACE    0
#define CONFIG_ALT_SETTING  0
#define CONFIG_TRAN_SIZE    4096


// built-in interface ID of the USBIO driver
// Refer to usbio.inf and to the documentation for how to define 
// your private interface GUID (strongly recommended).
GUID g_UsbioID = USBIO_IID;

// handle for device list
HDEVINFO g_DevList = NULL;

// global event, will be set if the worker thread terminates
HANDLE g_TerminateEvent = NULL;

//
// Helper function
// Prints an error code as text 
//
void
PrintError(DWORD Err)
{
  char strbuf[256];

  if ( Err != USBIO_ERR_SUCCESS ) {
    fprintf(stderr,"%s\n",CUsbIo::ErrorText(strbuf,sizeof(strbuf),Err));
  }
} // PrintError



/************************************************************************
* Main routine
************************************************************************/
int
main(int argc, char** argv) 
{
  // local USBIO device instance, used to configure the device
  CUsbIo Dev;
  // local instance of our Writer class, used to write to the pipe
  CMyWriter Pipe;
  // helper variables
  USBIO_SET_CONFIGURATION Conf;
  // status with default error value
  DWORD Status = USBIO_ERR_FAILED;
  // endpoint address
  UCHAR EndpointAddress;

  // variables used for example 1
  const DWORD BufSize = 128;
  char Buffer[BufSize];
  DWORD TransSize, i;

  // variables used for example 2
  // The CUsbIoBuf class stores information about the buffer (buffer descriptor).
  // This includes also the completion status of the operation.
  CUsbIoBuf BufferDesc(BufSize);
  // a buffer pointer, used to access the buffer
  char* BufPtr;

  // check command line parameters
  if ( argc < 3 ) {
    printf(
      "Usage: WriterCpp InputFileName EndpointAddress\n"
      "  EndpointAddress can be given in decimal or hexadecimal (0x prefix) format\n"
      );
    return 0;
  }

  // get the endpoint address from the command line
  // The specified endpoint has to be an OUT endpoint (Bit7=0).
  if ( sscanf(argv[2],"%i",&EndpointAddress) <= 0 ) {
    printf("Invalid EndpointAddress given: '%s'\n",argv[2]);
    return 1;
  }

  // initialize the global event
  g_TerminateEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
  if (g_TerminateEvent == NULL ) {
    printf("CreateEvent failed.\n");
    return GetLastError();
  }

  
  // Let the OS build a device list containing all active devices
  // that match the USBIO interface ID.
  g_DevList = CUsbIo::CreateDeviceList(&g_UsbioID);
  if ( g_DevList==NULL ) {
    fprintf(stderr,"Unable to build a device list!\n");
    goto Exit;
  }
  
  // Assumption: There is one USB device connected to the USBIO driver.
  // Refer to the ReaderCpp sample for how to enumerate more than one device.
  
  // open the device
  // Note: The parameter 0 in the open function selects the first device from g_DevList.
  // This is the first USB device which is connected to the USBIO driver.
  Status = Dev.Open(0,g_DevList,&g_UsbioID);
  if ( Status != USBIO_ERR_SUCCESS ) {
    PrintError(Status);
    goto Exit;
  }

  // set up the configuration request
  ZeroMemory(&Conf,sizeof(Conf));
  Conf.ConfigurationIndex = CONFIG_INDEX;
  Conf.NbOfInterfaces = CONFIG_NB_OF_INTERFACES;
  Conf.InterfaceList[0].InterfaceIndex = CONFIG_INTERFACE;
  Conf.InterfaceList[0].AlternateSettingIndex = CONFIG_ALT_SETTING;
  Conf.InterfaceList[0].MaximumTransferSize = CONFIG_TRAN_SIZE;
  // configure the device
  printf("Configuring the device...\n");
  Status = Dev.SetConfiguration(&Conf);
  if ( Status != USBIO_ERR_SUCCESS ) {
    PrintError(Status);
    // ignore the error: USBIO_ERR_ALREADY_CONFIGURED
    // Maybe another app has been started and the device is configured already.
    if (Status != USBIO_ERR_ALREADY_CONFIGURED) {
      goto Exit;
    }
  }
  
  // open the pipe and bind the pipe instance to the endpoint
  Status = Pipe.Bind(0,EndpointAddress,g_DevList,&g_UsbioID);
  if ( Status != USBIO_ERR_SUCCESS ) {
    PrintError(Status);
    goto Exit;
  }


  // ******************************************************************
  // 1. Example:
  //    write a single buffer to the endpoint
  //    Note: This method does not support continuous data transfer.
  //    This is because of the synchronous behaviour of WriteSync().
  //    There will be gaps between the OUT tokens on the bus.
  //    The full performance of USB cannot be reached with this method.
  // ******************************************************************
  // prepare the buffer
  for ( i=0; i<BufSize; i++ ) {
    Buffer[i] = (char)i;
  }
  // set the length of the transfer in bytes
  TransSize = BufSize;
  // Notes: TransSize is an input and output parameter!
  // A timeout of 1000 ms is set.
  // To send a zero-packet, set TransSize to 0!

  // The function WriteSync() blocks until the buffer is transmitted
  // or the timeout interval has elapsed.
  Status = Pipe.WriteSync(Buffer,TransSize,1000);
  if ( Status != USBIO_ERR_SUCCESS ) {
    // Abort if the data has not been sent in 1000 ms or if
    // another error occurs. In the case of an error,
    // there is no information about the amount of data which has 
    // been sent already.
    printf("WriteSync failed!\n");
    PrintError(Status);
    goto Exit;
  }


  // ******************************************************************
  // 2. Example
  //    use the asyncronous function Write()
  //    This allows some other processing to be done while the data buffer 
  //    is sent to the USB device.
  // ******************************************************************
  // prepare the buffer (fill with some test data)
  BufPtr = (char*)BufferDesc.Buffer();
  for ( i=0; i<BufSize; i++ ) {
    *BufPtr++ = (char)i;
  }
  // Important: The NumberOfBytesToTransfer member must be set before Write() is called.
  BufferDesc.NumberOfBytesToTransfer = BufSize;
  Pipe.Write(&BufferDesc);
  // The Write() function returns immediately, no blocking will occur.
  // We can ignore the return status from Write(). We can get the final status
  // of the operation later on by calling WaitForCompletion().
 
  // At this point we can do some other processing, while the USB Host Controller
  // sends the data bytes to the USB device.
  // We could also send another buffer to this pipe or to a different pipe.

  // Now we go into a loop that waits until the send operation is finished.
  // We ask for the status of the operation by calling WaitForCompletion() periodically.
  printf("Press any key to abort the write operation...\n");
  for (;;) {
    // wait for 100 ms 
    Status = Pipe.WaitForCompletion(&BufferDesc,100);
    // check the status
    if (Status == USBIO_ERR_SUCCESS) {
      // OK, the write operation has been completed with success.
      break;
    }   
    if (Status == USBIO_ERR_TIMEOUT) {
      // not yet finished, wait
    } else {
      // any other error
      PrintError(Status);
      break;
    }
    // check the keyboard
    if ( _kbhit() ) {
      getch();
      // cancel the pending write operation
      Pipe.AbortPipe();
      // Important: wait until the buffer is completed
      Pipe.WaitForCompletion(&BufferDesc);
      // leave the loop
      break;
    }
  }//for
  

  // ******************************************************************
  // 3. Example
  //    Use a separate worker thread to continuously send a
  //    large amount of data.
  //
  // In the following we use a more advanced approach, based 
  // on asynchronous (non-blocking) writes. We use a pool of buffers
  // and a separate worker thread to implement this approach.
  // This is all already implemented in the classes provided by USBIOLIB.
  // We use our CMyWriter class, derived from CUsbIoWriter.
  //
  // Note that the asynchronous approach is the only way to guarantee
  // a continuous flow of data from the application to the device.
  //
  // ******************************************************************
  
  // open source file
  if ( !Pipe.OpenFile(argv[1]) ) {
    fprintf(stderr,"Unable to open source file %s.\n",argv[1]);
    goto Exit;
  }
  // allocate the buffer pool used by the worker thread
  if ( !Pipe.AllocateBuffers(BUFFER_SIZE, NB_OF_BUFFERS) ) {
    printf("Unable to allocate buffer pool.\n");
    goto Exit;
  }
  // start the worker thread
  printf("Starting worker thread...\n");
  if ( !Pipe.StartThread() ) {
    printf("Unable to start worker thread.\n");
    goto Exit;
  }
  printf("Worker thread is running.\n");

  // The worker thread is running now. It is responsible for 
  // processing the continuous data flow.
  // The current thread continues and would be able to do other tasks,
  // for example processing user interface requests (Window messages).

  // At this point, we wait until a key is pressed or the worker thread terminates.
  printf("Press any key to stop the worker thread.\n\n");
  // wait for 100 ms 
  while ( WAIT_TIMEOUT == WaitForSingleObject(g_TerminateEvent,100) ) {
    // check the keyboard
    if ( _kbhit() ) {
      getch();
      // leave the loop
      break;
    }
  }//while

  // stop the worker thread
  // This call blocks until the worker thread has exited.
  // Important: The worker thread must be stopped before the CMyWriter instance
  // can be deleted.
  Pipe.ShutdownThread();

  // close pipe, close device
  // Note: This is not absolutely necessary because each 
  // instance will be closed by its destructor.
  Pipe.Close();
  Dev.Close();

Exit:
  // free resources
  if (g_DevList != NULL ) {
    CUsbIo::DestroyDeviceList(g_DevList);
  }
  if (g_TerminateEvent != NULL) {
    CloseHandle(g_TerminateEvent);
  }
  return Status;

} //main



/*************************** EOF **************************************/
