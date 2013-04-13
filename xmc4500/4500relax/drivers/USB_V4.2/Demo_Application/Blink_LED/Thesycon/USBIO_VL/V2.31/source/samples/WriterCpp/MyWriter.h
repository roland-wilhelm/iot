/************************************************************************
 *
 *  Module:       MyWriter.h
 *  Long name:    Specialized Writer, transmits a file to an OUT endpoint
 *  Description:  Demonstrates the usage of USBIO Class Library USBIOLIB
 *
 *  Runtime Env.: Win32 application
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __MYWRITER_H__
#define __MYWRITER_H__



// get includes from USBIOLIB
#include "UsbIoWriter.h"

extern HANDLE g_TerminateEvent;

//
// CMyWriter class
//
// Provides a specialized Writer implementation
// by overwriting some of the virtual functions of the 
// base class CUsbIoWriter.
//
class CMyWriter : public CUsbIoWriter
{
public:
  // default constructor
  CMyWriter();
  // destructor
  ~CMyWriter();

  // open the input file
  // returns TRUE for success, FALSE otherwise
  BOOL OpenFile(const char* Filename);

  
// implementation
protected :

  // ProcessBuffer is called by the base class if a buffer needs to be 
	// prepared for a write operation.
  // overwritten from CUsbIoWriter
  void ProcessBuffer(CUsbIoBuf* Buf);
  // OnThreadExit is called by the base class if the thread terminates.
  // It can be used to send a message to an application.
  // only a dummy implementation here
  void OnThreadExit();
  // BufErrorHandler is called if an error occurs
  void BufErrorHandler(CUsbIoBuf* Buf);

  // output file handle
  FILE* m_file;
  // counter
  DWORD m_cnt;

};


#endif //__MYWRITER_H__

/************************************ EOF *********************************/
