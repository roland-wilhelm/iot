
#include "stdafx.h"
#include "USBIOAPP.h"
#include "USBIOAPPdlg.h"
#include "EnumBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// global variables

// 
// default device interface GUID exported by USBIO
//
// IMPORTANT:
// Don't use this GUID for your own (custom) application. Generate a new one
// that is private to you and put it in the USBIO INF file and use it in 
// your application. Refer to the USBIO manual for further instructions.
// The tool guidgen.exe can be used to create private GUIDs.
//
const GUID g_UsbioID = USBIO_IID;

// global USBIO device object
CUsbIo g_UsbIo;
// device number
int g_DeviceNumber = -1;

// handle for device list
HDEVINFO g_DevList = NULL;

// list containing the open pipe dialogs
CObList g_PipeDialogList;


EnumBoxEntry g_DirectionTab[] = {
  { _T("HostToDevice"), HostToDevice },
  { _T("DeviceToHost"), DeviceToHost },
  { NULL, 0 } // end of table
};

EnumBoxEntry g_RequestTypeTab[] = {
  { _T("Class"),  RequestTypeClass },
  { _T("Vendor"), RequestTypeVendor },
  { NULL, 0 } // end of table
};

EnumBoxEntry g_RecipientTab[] = {
  { _T("Device"),     RecipientDevice },
  { _T("Interface"),  RecipientInterface },
  { _T("Endpoint"),   RecipientEndpoint },
  { _T("Other"),      RecipientOther },
  { NULL, 0 } // end of table
};

EnumBoxEntry g_PowerTab[] = {
  { _T("DevicePowerD0"),  DevicePowerStateD0 },
  { _T("DevicePowerD1"),  DevicePowerStateD1 },
  { _T("DevicePowerD2"),  DevicePowerStateD2 },
  { _T("DevicePowerD3"),  DevicePowerStateD3 },
  { NULL, 0 } // end of table
};


/////////////////////////////////////////////////////////////////////////////
// global functions

//
// print to output window
//
// Note:
// This is a global function that is called from any thread context.
// It is not possible to call MFC objects from a thread context that is
// created by using non-MFC means.
// So we use SendMessage to access the OutputWindow.
//
void PrintOut(const char *format, ...)
{
  const int buffersize = 2048;
  va_list argptr;
  
  char buffer[buffersize];

  // print to buffer
  va_start(argptr,format);
  _vsnprintf(buffer,buffersize-1,format,argptr);
  buffer[buffersize-1] = 0;

  // send buffer to output window (synchronous behavior)
  theApp.SendMsgToOutputWin(WM_USER_PRINT_OUT,0,(long)buffer);


  va_end(argptr);

}


// print error message according to ErrorCode, returns ErrorCode
DWORD PrintError(DWORD ErrorCode, DWORD Flags, const char *Prefix/*=NULL*/)
{
  char ErrBuffer[MAX_ERROR_MSG_LENGTH];
  char Buffer[MAX_ERROR_MSG_LENGTH];
  
  if ( ErrorCode != 0 ) {
    
    // build message string
    if ( Prefix!=NULL ) {
      _snprintf(Buffer,sizeof(Buffer),"%s: %s", Prefix, CUsbIo::ErrorText(ErrBuffer,sizeof(ErrBuffer),ErrorCode));
    } else {
      _snprintf(Buffer,sizeof(Buffer),"%s", CUsbIo::ErrorText(ErrBuffer,sizeof(ErrBuffer),ErrorCode));
    }
    
    // print to output window
    PrintOut("%s"NL,Buffer);

    if ( Flags&E_FATAL ) {
      // display message box
      ::AfxMessageBox(Buffer, MB_OK, MB_ICONEXCLAMATION);
    }

  }

  return ErrorCode;
}



// message box
void DisplayMessageBox(const char *format, ...)
{
  char buffer[2048];
  va_list argptr;

  // print to buffer
  va_start(argptr,format);
  _vsnprintf(buffer,sizeof(buffer)-1,format,argptr);
  buffer[sizeof(buffer)-1] = 0;

  // display message box
  ::AfxMessageBox(buffer, MB_OK, MB_ICONEXCLAMATION);
  
  va_end(argptr);

}


// return string for pipe type
const char* PipeTypeStr(USBIO_PIPE_TYPE PipeType)
{
	return (
		(PipeType==PipeTypeControl) ?			"Control" :
		(PipeType==PipeTypeIsochronous) ? "Isochronous" :
		(PipeType==PipeTypeBulk) ?				"Bulk" :
		(PipeType==PipeTypeInterrupt) ?		"Interrupt" :	"unknown"
		);
}


// return string for endpoint direction
const char* EndpointDirectionStr(UCHAR EndpointAddress)
{
	return ( (EndpointAddress&0x80) ?	"IN" : "OUT" );
}
