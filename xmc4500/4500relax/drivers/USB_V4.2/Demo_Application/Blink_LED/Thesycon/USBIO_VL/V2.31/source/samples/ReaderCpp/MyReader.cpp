/************************************************************************
 *
 *  Module:       CMyReader.cpp
 *  Long name:    Specialized Reader
 *  Description:  Demonstrates the usage of USBIO Class Library USBIOLIB
 *
 *  Runtime Env.: Win32 application
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

#include "MyReader.h"



// default constructor
CMyReader::CMyReader()
{
  file = NULL;
}


// destructor
CMyReader::~CMyReader()
{
  if ( file != NULL ) {
    fclose(file);
    file = NULL;
  }
}


// open the output file
// returns TRUE for success, FALSE otherwise
BOOL CMyReader::OpenFile(const char* Filename)
{
  if ( file!=NULL ) {
    // already open, close first
    fclose(file);
  }
  // create file, in binary mode
  file = fopen(Filename,"wb");
  if ( file==NULL ) {
    return FALSE;
  } else { 
    return TRUE;
  }
}


// ProcessData, called by the base class if a read operation completes
void CMyReader::ProcessData(CUsbIoBuf* Buf)
{
  if ( Buf->Status==USBIO_ERR_SUCCESS ) {
    // read operation completed successfully
    // print a dot, so the user sees something is happening
    fprintf(stdout,"."); 
    fflush(stdout);
    
    // Write the data bytes we received to the output file.
    // Note that Buf->BytesTransferred contains the number of
    // valid bytes in the buffer. This can be less than the 
    // buffer size if the device has sent a short packet.
    if ( file!=NULL ) {
      fwrite(Buf->Buffer(),1,Buf->BytesTransferred,file);
    }

  } else {
    // read operation completed with error
    char strbuf[256];
    fprintf(stderr,"ProcessData: %s\n",CUsbIo::ErrorText(strbuf,sizeof(strbuf),Buf->Status));
  }
}


/************************************ EOF *********************************/
