/************************************************************************
 *
 *  Module:       ReaderCpp.cpp
 *  Long name:    Read from an Interrupt or Bulk pipe 
 *                using the USBIO C++ Class Library
 *  Description:  
 *  This module is a simple command line application, which reads data from
 *  an USB Pipe (Endpoint) and writes it to a file.
 *  The module uses a specialized class derived from the UsbIoReader class.
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
// our Reader class
#include "MyReader.h"

/********************************** Parameters ***************************/
// check the following parameters and adapt them to the actual USB device

// number of I/O buffers used
#define NB_OF_BUFFERS   5

// A device is defined by its USB Vendor ID and Product ID.
// We need additional the Interrupt endpoint and the fifo (max packet) size for this program
// A buffer will be returned if
//		1. a short packet is received; (A zero packet is also a short packet)
//		2. the buffer is completely filled.
typedef struct _MY_DEVICE_CONFIG {
  unsigned short  Vid;
  unsigned short  Pid;
  unsigned char		EndpointAddress;
  unsigned char		EndpointFifoSize;
// index to be used for "GetConfigurationDescriptor"
// This parameter is greater than 0 for multiconfiguration devices only.
  unsigned short  CfgIdx;
// number of interfaces, all possible interfaces must be activated 
// The number of interfaces can be changed, if the multi-interface or composite
// device driver from Microsoft is installed.
  unsigned short  CfgNumberOfIf;
// settings per interface
  unsigned short  CfgIf;
  unsigned short  CfgAltSetting;
  unsigned long		CfgMaxTransferSize;
} MY_DEVICE_CONFIG;


const MY_DEVICE_CONFIG g_DeviceCfgList[] = {
			// VID		, PID			, EpAddr	, FifoSize	, CfgIdx	, CfgNumberOfIf	, CfgIf		, CfgAltSetting	,	CfgMaxTransferSize
			{  0x046d	,	0xC001	, 0x81		, 0x08			,	0x0000	, 0x0001				, 0x0000	, 0x0000				, 4096	},	// Logitech Mouse
			{  0x05B8	,	0x3002	, 0x81		, 0x03			,	0x0000	, 0x0001				, 0x0000	, 0x0000				, 4096	},	// Anubis Mouse
			{  0x0000	,	0x0000	, 0x00		, 0x00			,	0x0000	, 0x0000				, 0x0000	, 0x0000				, 0	}	// end marker
	};

const MY_DEVICE_CONFIG* gMyDeviceCfgPtr = NULL;


// file name of target file
const char TARGET_FILE_NAME[] = "PipeDump.bin";


// built-in interface ID of the USBIO driver
// Refer to usbio.inf and the documentation for how to define 
// your private interface GUID (strongly recommended).
GUID g_UsbioID = USBIO_IID;

// handle for device list
HDEVINFO g_DevList = NULL;


// 
// forward declarations
// 
void Start(int DevNb);


bool 
DeviceInList(
	unsigned short Vid,
	unsigned short Pid
	)
{

	bool found = false;
	int i = 0;

	while ( g_DeviceCfgList[i].Vid != 0x0000 ) {
		if ( g_DeviceCfgList[i].Vid == Vid ) {
			if ( g_DeviceCfgList[i].Pid == Pid ) {
				gMyDeviceCfgPtr = &g_DeviceCfgList[i];
				found = true;
				break;
			}
		}

		i++;
	}

	return found;

}	// DeviceInList

/************************************************************************
* Main routine
************************************************************************/
int
main(int argc, char** argv) 
{
  // local USBIO device instance, used for temporary opens
  CUsbIo UsbDev;
  // device descriptor buffer
  USB_DEVICE_DESCRIPTOR DevDesc;
  // buffer used to store string descriptor
  unsigned char StrDescBuffer[sizeof(USB_STRING_DESCRIPTOR)+512];
  // pointer to USB string descriptor
  USB_STRING_DESCRIPTOR* StrDesc;
  DWORD StrDescSize;
  // helper variables  
  DWORD Status;
  bool DevFound = false;

  // Search for available USBIO devices 
  fprintf(stdout,"Scanning for attached USB devices...\n");
  // Let the OS build a device list containing all active devices
  // that match the USBIO interface ID.
  g_DevList = CUsbIo::CreateDeviceList(&g_UsbioID);
  if ( g_DevList==NULL ) {
    fprintf(stderr,"Unable to build a device list!\n");
    return 1;
  }

  // open and query each device (max. 127)
  for ( int i=0; i<127; i++ ) {
	  fprintf(stdout,"\n\n");
    StrDesc = NULL;
    // try to temporary open the device, using a local CUsbIo instance
    Status = UsbDev.Open(i,g_DevList,&g_UsbioID);
    if ( Status != USBIO_ERR_SUCCESS ) {
      // no more devices, leave loop
			if ( Status != USBIO_ERR_NO_SUCH_DEVICE_INSTANCE ) {
				fprintf(stderr,"UsbDev.Open returned with error 0x%08X\n",Status);
			}
      break;
    }
    // we have found a device, query the device descriptor
    Status = UsbDev.GetDeviceDescriptor(&DevDesc);
    if ( Status == USBIO_ERR_SUCCESS ) {
      // found one valid device
      DevFound = true;
      // Does the device have a serial number?
      if ( DevDesc.iSerialNumber!=0 ) {
        // yes, query the corresponding string descriptor
        StrDesc = (USB_STRING_DESCRIPTOR*)StrDescBuffer;
        StrDescSize = sizeof(StrDescBuffer);
        Status = UsbDev.GetStringDescriptor(StrDesc,StrDescSize,DevDesc.iSerialNumber);
        if ( Status != USBIO_ERR_SUCCESS ) {
          fprintf(stderr,"Query Serial Number String Descriptor failed, status:0x%08X\n",Status);
          StrDesc = NULL;
        }
      }
      // close device
      UsbDev.Close();
      // print information from descriptor
      fprintf(stdout,"Device %d:  VendorID:0x%04X  ProductID:0x%04X\n",i,DevDesc.idVendor,DevDesc.idProduct);
      fprintf(stdout,"  SerialNumber: ");
      if ( StrDesc!=NULL ) {
        // print serial number string, UNICODE !
        fprintf(stdout," %S\n",StrDesc->bString);
      } else {
        fprintf(stdout,"not available\n");
      }
      // see if we have the device we are looking for
      if ( DeviceInList(DevDesc.idVendor,DevDesc.idProduct) ) {
        // start our Reader
        fprintf(stdout,"Device found, starting Reader.\n");
        Start(i);
        //break; // leave loop
      }
    } else {
      // "GetDeviceDescriptor" failed, seems not to be a valid USB device.
      fprintf(stderr,"Query Device Descriptor failed, status:0x%08X\n",Status);
      // close device
      UsbDev.Close();
    }
  } // for 

  if ( !DevFound ) {
    // no device found
    fprintf(stderr,"There are no USB devices attached to the USBIO driver.\n");
  } 
  
  // free device list
  CUsbIo::DestroyDeviceList(g_DevList);
  
  return 0;
} //main



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
}



//
// Start our Reader for the given device
//
void Start(int DevNb)
{
  // local USBIO device instance, used to configure the device
  CUsbIo Dev;
  // local instance of our Reader class, used to read from the pipe
  CMyReader Pipe;
  // helper variables
  USBIO_SET_CONFIGURATION Conf;
  DWORD Status;
  
  // open the device
  Status = Dev.Open(DevNb,g_DevList,&g_UsbioID);
  if ( Status != USBIO_ERR_SUCCESS ) {
    PrintError(Status);
    return;
  }

  // set up the configuration request
  ZeroMemory(&Conf,sizeof(Conf));

  Conf.ConfigurationIndex = gMyDeviceCfgPtr->CfgIdx;
  Conf.NbOfInterfaces = gMyDeviceCfgPtr->CfgNumberOfIf;
  Conf.InterfaceList[0].InterfaceIndex = gMyDeviceCfgPtr->CfgIf;
  Conf.InterfaceList[0].AlternateSettingIndex = gMyDeviceCfgPtr->CfgAltSetting;
  Conf.InterfaceList[0].MaximumTransferSize = gMyDeviceCfgPtr->CfgMaxTransferSize;
  // configure the device
  printf("Configuring the device...\n");
  Status = Dev.SetConfiguration(&Conf);
  if ( Status != USBIO_ERR_SUCCESS ) {
    PrintError(Status);
    return;
  }
  
//
// Optionally, activate the following code to 
// send a vendor-specific request to the device.
//
/*
  printf("Sending Vendor Request...\n");
  USBIO_CLASS_OR_VENDOR_REQUEST Request;
  // set up the request, this is device-specific
  ZeroMemory(&Request,sizeof(Request));
  Request.Flags = 0;
  Request.Type = RequestTypeVendor;
  Request.Recipient = RecipientDevice;
  Request.RequestTypeReservedBits = 0;
  Request.Request = 0x01;
  Request.Value = 4;
  Request.Index = 0;
  // send request
  Status = Dev.ClassOrVendorOutRequest(
                    NULL,       // no buffer
                    0,          // no data Stage
                    &Request    // USBIO_CLASS_OR_VENDOR_REQUEST structure
                    );  
  PrintError(Status);
*/

  // create the target file 
  if ( !Pipe.OpenFile(TARGET_FILE_NAME) ) {
    fprintf(stderr,"Unable to create target file %s.\n",TARGET_FILE_NAME);
		Dev.UnconfigureDevice();
    return;
  }
  
  // open the pipe and bind the pipe instance to the endpoint
  Status = Pipe.Bind(DevNb,gMyDeviceCfgPtr->EndpointAddress,g_DevList,&g_UsbioID);
  if ( Status != USBIO_ERR_SUCCESS ) {
    PrintError(Status);
		Dev.UnconfigureDevice();
    return;
  }

//
// The following code shows how to implement a simple
// synchronous (blocking) read operation for an IN pipe.
//
/*
  // size of read buffer in bytes
  const int RdBufSize = 128; 
  // read buffer
  char RdBuf[RdBufSize];
  // number of bytes to read
  DWORD RdByteCount = RdBufSize;
  // read from pipe, this call blocks until the request completes
  // or the timeout interval of 1000 ms expires
  Status = Pipe.ReadSync(RdBuf,&RdByteCount,1000);
  if ( Status == USBIO_ERR_SUCCESS ) {
    // RdByteCount contains the number of bytes successfully read.
    // This can be less than RdBufSize.
  } else {
    // timeout or failed 
    PrintError(Status);
  }
*/
//
// Note: A similar function, CUsbIo::WriteSync(), is available
// to implement blocking writes to an OUT pipe.
//


//
// In the following we use a more advanced approach, based 
// on asynchronous (non-blocking) reads. We use a pool of buffers
// and a separate worker thread to implement this approach.
// This is all already implemented in the classes provided by USBIOLIB.
// We use our CMyReader class, derived from CUsbIoReader.
//
// Note that the asynchronous approach is the only way to guarantee
// a continuous flow of data from the device to the application.
//
  
  // allocate the buffer pool used by the worker thread
  if ( !Pipe.AllocateBuffers(gMyDeviceCfgPtr->EndpointFifoSize, NB_OF_BUFFERS) ) {
    printf("Unable to allocate buffer pool.\n");
		Dev.UnconfigureDevice();
    return;
  }
  // start the worker thread
  printf("Starting worker thread...\n");
  if ( !Pipe.StartThread() ) {
    printf("Unable to start worker thread.\n");
		Dev.UnconfigureDevice();
    return;
  }
  printf("Worker thread is running.\n");

  // The worker thread is running now. It is responsible for 
  // processing the continuous data flow.
  // The current thread continues and would be able to do other tasks,
  // for example processing user interface requests (Window messages).

  // At this point, we simply wait until a key is pressed.
  printf("Press any key to stop the worker thread.\n\n");
  getch();

  // stop the worker thread
  // This call blocks until the worker thread has exited.
  Pipe.ShutdownThread();

  // close pipe, close device
  // Note: This is not absolute necessary because each 
  // instance will be closed by its destructor.
  Pipe.Close();
	Dev.UnconfigureDevice();
  Dev.Close();

} //Start


/*************************** EOF **************************************/
