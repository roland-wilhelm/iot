/************************************************************************
 *
 *  Module:       ReadPipe.c
 *  Long name:    Read Pipe sample
 *  Description:  Simple console application that reads data from a
 *                Bulk or Interrupt pipe
 *
 *  Runtime Env.: Win32 application
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

/* 
  This simple demo application shows the usage of the USBIO API from C.
  The program reads data from an USB pipe and writes it to a file.
  The program needs to be adapted to the USB device being used.
*/

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
#include <stdlib.h>
// get IOCTL support
#include <winioctl.h>
// get support for GUIDs and Setup API
#include <setupapi.h>
// get driver interface definitions
#include "usbio_i.h"
#include "usbspec.h"


/********************************** Parameters ***************************/
// check the following parameters and adapt them to the actual USB device

// size of the I/O buffer in bytes
// The size should be a multiple of the endpoint's FIFO size.
// The buffer will be returned if
// 1. a short packet is received; Note: A zero packet is also a short packet.
// 2. the buffer is completely filled.
#define BUFFER_SIZE 64


// configuration
//
// Index to be used for "GetConfigurationDescriptor"
// This parameter is greater than 0 for multiconfiguration devices only.
#define CONFIG_INDEX 0
// number of interfaces, all possible interfaces must be activated 
// The number of interfaces can be changed, if the multi-interface or composite
// device driver from Microsoft is installed.
#define CONFIG_NB_OF_INTERFACES 1
// settings per interface
// This application uses one interface only.
#define CONFIG_INTERFACE    0
#define CONFIG_ALT_SETTING  0
#define CONFIG_TRAN_SIZE    4096



// interface ID (IID) of the USBIO driver
// Refer to usbio.inf and the documentation for how to define 
// your private interface GUID. This is strongly recommended!
GUID g_UsbioID = USBIO_IID;




/************************************************************************
* IoctlSync routine,
* executes an I/O control request synchronously 
************************************************************************/
DWORD 
IoctlSync(
  HANDLE FileHandle,
  DWORD IoctlCode,
  const void *InBuffer,
  DWORD InBufferSize,
  void *OutBuffer,
  DWORD OutBufferSize,
  DWORD *BytesReturned
  )
{
  DWORD Status;
  DWORD BytesRet = 0;
  BOOL succ;
  OVERLAPPED Overlapped;

  ZeroMemory(&Overlapped,sizeof(Overlapped));
  Overlapped.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
  if ( Overlapped.hEvent==NULL ) {
    return USBIO_ERR_NO_MEMORY;
  }

  // call the device driver
  succ = DeviceIoControl(
            FileHandle,         // driver handle
            IoctlCode,          // IOCTL code
            (void*)InBuffer,    // input buffer
            InBufferSize,       // input buffer size
            OutBuffer,          // output buffer
            OutBufferSize,      // output buffer size
            &BytesRet,          // number of bytes returned
            &Overlapped         // OVERLAPPED structure
            );
  if ( succ ) {
    // ioctl completed successfully
    Status = USBIO_ERR_SUCCESS;
  } else {
    Status = GetLastError();
    if ( Status == ERROR_IO_PENDING ) {
      // the operation is pending, wait for completion
      succ = GetOverlappedResult(
                FileHandle,
                &Overlapped,
                &BytesRet,  // number of bytes successfully transferred 
                TRUE        // wait for completion
                );
      if ( succ ) {
        // completed successfully
        Status = USBIO_ERR_SUCCESS;
      } else {
        // completed with error
        Status = GetLastError();
      }
    }
  }

  if ( BytesReturned != NULL ) {
    *BytesReturned = BytesRet;
  }

  CloseHandle(Overlapped.hEvent);

  return Status;

} // IoctlSync



/************************************************************************
* Main routine
************************************************************************/
int
main(int argc, char** argv) 
{
  // variables needed for device enumeration
  HDEVINFO                        DevList;
  SP_DEVICE_INTERFACE_DATA        DevData;
  SP_INTERFACE_DEVICE_DETAIL_DATA* DevDetail = NULL;
  DWORD                           ReqLen;
  
  // device handle
  HANDLE                          DevHandle;
  // configuration struct
  USBIO_SET_CONFIGURATION         Config;
  // bind struct
  USBIO_BIND_PIPE                 BindPipe;
                                  
  // OVERLAPPED struct, needed for asynchronous I/O operations
  OVERLAPPED                      Overlapped;

  // other variables              
  FILE*                           OutputFile;
  UCHAR                           Buffer[BUFFER_SIZE];
  DWORD                           Status;
  DWORD                           EndpointAddress;
  DWORD                           BytesTransferred;
  BOOL                            succ;

  // check command line parameters
  if ( argc < 3 ) {
    printf(
      "Usage: ReadPipe OutputFileName EndpointAddress\n"
      "  EndpointAddress can be given in decimal or hex (0x prefix)\n"
      );
    return 0;
  }

  // create the output file
  OutputFile = fopen(argv[1],"wb");
  if ( OutputFile == NULL ) {
    printf("Unable to create output file %s.\n",argv[1]);
    return 1;
  }

  // get the endpoint address from the command line
  if ( sscanf(argv[2],"%i",&EndpointAddress) <= 0 ) {
    printf("Invalid EndpointAddress given: '%s'\n",argv[2]);
    return 1;
  }


  ////////////////////////////////////////////////
  // enumerate available USBIO devices
  ////////////////////////////////////////////////
  
  // create a list of attached devices
  DevList = SetupDiGetClassDevs(
              &g_UsbioID,                           // LPGUID ClassGuid, 
              NULL,                                 // PCTSTR Enumerator, 
              NULL,                                 // HWND hwndParent, 
              DIGCF_DEVICEINTERFACE | DIGCF_PRESENT // DWORD Flags
              );
  if (DevList == NULL) {
    printf("SetupDiGetClassDevs failed, err=%d\n",GetLastError());
    fclose(OutputFile);
    return 1;
  }

  // enumerate device interfaces, for simplicity we use index 0 only
  ZeroMemory(&DevData,sizeof(DevData));
  DevData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
  succ = SetupDiEnumDeviceInterfaces(DevList, NULL, &g_UsbioID, 0, &DevData );
  if (!succ) {
    printf("SetupDiEnumDeviceInterfaces failed, err=%d\n",GetLastError());
    printf("USBIO is not installed on a device or device is not connected to the PC.\n");
    fclose(OutputFile);
    SetupDiDestroyDeviceInfoList(DevList);
    return 1;
  }
  // get length of INTERFACE_DEVICE_DETAIL_DATA, allocate buffer
  // This function call returns the system error "buffer too small" (code 122).
  // We ignore this return code.
  SetupDiGetDeviceInterfaceDetail(DevList, &DevData, NULL, 0, &ReqLen, NULL);
  DevDetail = (SP_INTERFACE_DEVICE_DETAIL_DATA*)malloc(ReqLen);
  if ( DevDetail==NULL ) {
    printf("Memory allocation failed\n",ReqLen);
    fclose(OutputFile);
    SetupDiDestroyDeviceInfoList(DevList);
    return 1;
  }
  // now get the INTERFACE_DEVICE_DETAIL_DATA struct
  ZeroMemory(DevDetail,ReqLen);
  DevDetail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
  succ = SetupDiGetDeviceInterfaceDetail(DevList, &DevData, DevDetail, ReqLen, &ReqLen, NULL);
  if (!succ) {
    printf("SetupDiGetDeviceInterfaceDetail(2) failed, err=%d\n",GetLastError());
    fclose(OutputFile);
    free(DevDetail);
    SetupDiDestroyDeviceInfoList(DevList);
    return 1;
  }

  // open the device in overlapped mode 
  DevHandle = CreateFile(
                DevDetail->DevicePath,              // device name
                GENERIC_READ | GENERIC_WRITE,       // access mode
                FILE_SHARE_WRITE | FILE_SHARE_READ, // share mode
                NULL,                               // security descriptor
                OPEN_EXISTING,                      // how to create
                FILE_FLAG_OVERLAPPED,               // file attributes
                NULL                                // template file
                );
  if ( DevHandle == INVALID_HANDLE_VALUE ) {
    printf("Unable to open the USBIO device\n");
    fclose(OutputFile);
    free(DevDetail);
    SetupDiDestroyDeviceInfoList(DevList);
    return 1;
  }
  printf("Device opened\n");
  
  // free resources
  free(DevDetail);
  DevDetail = NULL;
  SetupDiDestroyDeviceInfoList(DevList);
  DevList = NULL;


  // configure the USB device
  ZeroMemory(&Config,sizeof(Config));
  Config.ConfigurationIndex = CONFIG_INDEX;
  Config.NbOfInterfaces = CONFIG_NB_OF_INTERFACES;
  Config.InterfaceList[0].InterfaceIndex = CONFIG_INTERFACE;
  Config.InterfaceList[0].AlternateSettingIndex = CONFIG_ALT_SETTING;
  Config.InterfaceList[0].MaximumTransferSize = CONFIG_TRAN_SIZE;
  // send the configuration request
  Status = IoctlSync(
              DevHandle,
              IOCTL_USBIO_SET_CONFIGURATION,
              &Config,
              sizeof(USBIO_SET_CONFIGURATION),
              NULL,
              0,
              NULL
              );
  if ( Status != USBIO_ERR_SUCCESS ) {
    printf("SET_CONFIGURATION failed, status=0x%08X.\n",Status);
    CloseHandle(DevHandle);
    fclose(OutputFile);
    return 1;
  }
  printf("Device configured\n");

  // bind the handle to a pipe
  // Note: a handle can be bound to one pipe only
  ZeroMemory(&BindPipe,sizeof(BindPipe));
  BindPipe.EndpointAddress = (UCHAR)EndpointAddress;
  // send bind request to USBIO
  Status = IoctlSync(
              DevHandle,
              IOCTL_USBIO_BIND_PIPE,
              &BindPipe,
              sizeof(USBIO_BIND_PIPE),
              NULL,
              0,
              NULL
              );
  if ( Status != USBIO_ERR_SUCCESS ) {
    printf("Unable to bind pipe 0x%02X, status=0x%08X.\n",EndpointAddress,Status);
    CloseHandle(DevHandle);
    fclose(OutputFile);
    return 1;
  }
  printf("Pipe bound to EP 0x%02X\n",EndpointAddress);

  // initialize overlapped struct, create an event object
  ZeroMemory(&Overlapped,sizeof(Overlapped));
  Overlapped.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
  if ( Overlapped.hEvent==NULL ) {
    printf("Unable to create Event Object\n");
    CloseHandle(DevHandle);
    fclose(OutputFile);
    return 1;
  }

  // go into a loop that continuously reads from the pipe
  printf("Start reading, press any key to abort.\n");
  for (;;) {
    // check for key pressed
    if (_kbhit()) {
      getch();
      break;
    }
    // read data into the buffer
    // the ReadFile function does not block, it returns immediately
    succ = ReadFile(
            DevHandle,          // handle of file to read
            Buffer,             // pointer to buffer that receives data
            BUFFER_SIZE,        // number of bytes to read
            &BytesTransferred,  // number of bytes read
            &Overlapped         // pointer to OVERLAPPED struct
            );
    if ( succ ) {
      // read operation completed immediately and successfully
      Status = USBIO_ERR_SUCCESS;
    } else {
      // read operation is pending or an error is ocurred
      Status = GetLastError();
      if ( Status==ERROR_IO_PENDING ) {
        // read operation is pending, wait for completion with a timeout of 1 second
        // The timeout is used to enable periodical checking for keyboard events.
        while ( WaitForSingleObject(Overlapped.hEvent,1000) == WAIT_TIMEOUT ) {
          if (_kbhit()) {
            getch();
            goto Exit;
          }
        } 
        // operation completed, get final status
        succ = GetOverlappedResult(
                  DevHandle,
                  &Overlapped,
                  &BytesTransferred,  // number of bytes read
                  FALSE               // do not wait for completion
                  );
        if ( succ ) {
          // success
          Status = USBIO_ERR_SUCCESS;
        } else {
          // read operation completed with error
          Status = GetLastError();
          printf("Read request returned with error code 0x%08X.\n",Status);
          break;
        }
      } else {
        // read operation completed with error
        printf("Read request returned with error code 0x%08X.\n",Status);
        break;
      }
    }
    if ( Status == USBIO_ERR_SUCCESS ) {
      // the operation was successful
      // Write the received data bytes to the output file.
      // Note that BytesTransferred contains the number of valid bytes
      // in Buffer. This can be different from the buffer size.
      fwrite(Buffer,1,BytesTransferred,OutputFile);
      // print a dot, so the user sees something is still happening
      fprintf(stdout,".");
      fflush(stdout);
    }
  } // for 

Exit:
  // close handles
  CloseHandle(Overlapped.hEvent);
  CloseHandle(DevHandle);
  fclose(OutputFile);
  
  return 0;

} // main


/*************************** EOF **************************************/
