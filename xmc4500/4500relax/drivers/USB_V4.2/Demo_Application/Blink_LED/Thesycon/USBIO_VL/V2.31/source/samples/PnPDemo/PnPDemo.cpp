/************************************************************************
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 ************************************************************************/

/************************************************************************
 *
 *  Module:       PnPDemo.cpp
 *  Long name:    USBIO list available devices example
 *  Description:  This sample demonstrates how to scan for available
 *                USBIO devices.
 *                This sample is based on the USBIOLib C++ class library.
 *
 *  Runtime Env.: implemented as Win32 console application
 *  Used link libraries:
 *                USBIOlib.lib, setupapi.lib, user32.lib
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

// standard includes
#include <stdio.h>
#include <conio.h>

// define WINVER to 5.00 to enable RegisterDeviceNotification and 
// UnregisterDeviceNotification in WINDOWS.H and associated stuff in DBT.H
#ifdef WINVER
#undef WINVER
#endif
#define WINVER 0x0500
#include <windows.h>
// get setup API functions (only available in Win98 and later systems)
#include <setupapi.h>

// definitions of used classes
#include "usbio_i.h"
#include "usbio.h"
#include "PnPNotificator.h"
#include "PnPHandler.h"


// print prefixes
#define PFX   "PnPDemo: "
#define PFXERR  "PnPDemo Error: "


// GLOBAL VARIABLES

// CPnPNotificatorinstance, catches WM_DEVICECHANGE messages
CPnPNotificator g_PnpNotificator;
// CPnPHandler instance, implements the interface used by CPnpNotificator
// to deliver PnP messages
CPnPHandler g_PnPHandler;

// device list that contains devices providing a specific interface
// interface ID of interest
// please refer to to the documentation (chapter 7.4) for details on how 
// to define your private interface (strongly recommended)
const GUID g_UsbIoDefaultIID = USBIO_IID;




// scan for available devices, display device information
void ScanForDevices()
{
  fprintf(stdout, "\n"PFX"Scanning for available devices ...\n");

  // prepare an OS-internal device list used for the open call
  // device list will contain devices that provide the USBIO_IID interface
  // please refer to to the documentation (chapter 7.4) for details on how 
  // to define your private interface (strongly recommended)
  HDEVINFO DevList = CUsbIo::CreateDeviceList(&g_UsbIoDefaultIID);
  if ( DevList == NULL ) {
    // ERROR !!!
    fprintf(stderr, PFXERR"CreateDeviceList failed\n");
    return;
  }

  CUsbIo Device;
  unsigned long Status;
  USBIO_DRIVER_INFO driver;
  
  for ( int i=0; i<63; i++ ) {
    // open a handle to the device
    Status = Device.Open(i,DevList,&g_UsbIoDefaultIID);
    if ( Status == USBIO_ERR_SUCCESS ) {
      // device opened, query device identification

      // all information available, print it on screen
      if ( i == 0 ) {
        // print driver version
        memset(&driver,0x0,sizeof(USBIO_DRIVER_INFO));
        Status = Device.GetDriverInfo(&driver);
        if ( Status != USBIO_ERR_SUCCESS ) {
          // ERROR !!!
          fprintf(stderr, PFXERR"Failed to get driver information (0x%08X)\n",Status);
          // close device handle and exit
          Device.Close();
          break;
        }
        fprintf(stdout, "\n USBIO Version %d.%02d (Build %d) %s%s\n",
          (unsigned short)((driver.DriverVersion>>8)&0x00FF), (unsigned short)(driver.DriverVersion&0xff),
          driver.DriverBuildNumber,
          (driver.Flags &  USBIO_INFOFLAG_CHECKED_BUILD ) ? "checked build" : "release build",
          (driver.Flags &  USBIO_INFOFLAG_DEMO_VERSION ) ? " (demo version)" : ""
          );
        fprintf(stdout, " Api Version %d.%02d\n",
          (unsigned short)((driver.APIVersion>>8)&0x00FF), (unsigned short)(driver.APIVersion&0x000000ff)
          );

      }

      // done with this device handle, close it
      Device.Close();
    } else {
      // error while opening device i, check if we have reached the and of the list
      if ( Status == USBIO_ERR_NO_SUCH_DEVICE_INSTANCE ) {
        // end of list reached
        break;
      } else {
        // ERROR !!!
        fprintf(stderr, PFXERR"Failed to open device %d (0x%08X)\n",i,Status);
        // try to continue with next device
      }
    }
  } // for

  if ( i == 0 ) {
    fprintf(stdout, PFX"No devices available\n");
  }

  CUsbIo::DestroyDeviceList(DevList);

} // ScanForDevices


/*******************************************************************/
// main function
/*******************************************************************/
int __cdecl main(int argc, char *argv[])
{

/*******************************************************************/
// initialize PnP message handling

  // initialize g_PnpNotificator
  if ( !g_PnpNotificator.Initialize(::GetModuleHandle(NULL),&g_PnPHandler) ) {
    // ERROR !!!
    fprintf(stderr, PFXERR"g_PnpNotificator.Initialize failed\n");
    goto Exit;
  }

  // enable PnP messages for our interface
  if ( !g_PnpNotificator.EnableDeviceNotifications(g_UsbIoDefaultIID) ) {
    // ERROR !!!
    fprintf(stderr, PFXERR"g_PnpNotificator.EnableDeviceNotifications failed\n");
    goto Exit;
  }


/*******************************************************************/
// scan for devices, wait for PnP messages

  // initially display information for available devices
  ScanForDevices();
  fprintf(stdout, "\n"PFX"Waiting for PnP notifications ... press any key to exit\n");

  HANDLE NotifyEvent; NotifyEvent = g_PnPHandler.GetNotificationEvent();
  unsigned long WaitResult;
  for ( ;; ) {

    // wait for PnP messages
    WaitResult = ::WaitForSingleObject(NotifyEvent,500);
    if ( WaitResult == WAIT_OBJECT_0 ) {
      // device arrival/removal
      // display information for available devices
      ScanForDevices();
      fprintf(stdout, "\n"PFX"Waiting for PnP notifications ... press any key to exit\n");

    } else if ( WaitResult == WAIT_TIMEOUT ) {
      // wait timeout, just wait again or terminate
    } else {
      // ERROR !!!
      fprintf(stderr, PFXERR"WaitForSingleObject failed (0x%08X)\n",WaitResult);
      break;
    }

    // check for user break
    if ( _kbhit() ) {
      _getch();
      break;
    }

  } // for()



/*******************************************************************/
// ERROR!!! or normal exit

Exit:
  g_PnpNotificator.DisableDeviceNotifications(g_UsbIoDefaultIID);
  g_PnpNotificator.Shutdown();

  return 0;

} // main

/*************************** EOF **************************************/
