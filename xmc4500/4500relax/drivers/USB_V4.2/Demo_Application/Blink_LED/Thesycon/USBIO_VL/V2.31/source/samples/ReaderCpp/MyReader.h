/************************************************************************
 *
 *  Module:       CMyReader.h
 *  Long name:    Specialized Reader
 *  Description:  Demonstrates the usage of USBIO Class Library USBIOLIB
 *
 *  Runtime Env.: Win32 application
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __MYREADER_H__
#define __MYREADER_H__

// get includes from USBIOLIB
#include "UsbIoReader.h"


//
// CMyReader class
//
// Provides a specialized Reader implementation
// by overwriting some of the virtual functions of the 
// base class CUsbIoReader.
//
class CMyReader : public CUsbIoReader
{
public:
  // default constructor
  CMyReader();
  // destructor
  ~CMyReader();

  // open the output file
  // returns TRUE for success, FALSE otherwise
  BOOL OpenFile(const char* Filename);

  
// implementation
protected :

  // ProcessData is called if a read operation completes.
  // The function checks for an error and processes the received
  // data if the read operation was successful.
  // overwritten from CUsbIoReader
  virtual void ProcessData(CUsbIoBuf* Buf);

  // output file handle
  FILE* file;

};


#endif //__MYREADER_H__

/************************************ EOF *********************************/
