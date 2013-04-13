/************************************************************************
 *
 *  Module:       CMyWriter.cpp
 *  Long name:    Specialized Writer
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
// The MyWriter class is derived from CUsbIoWriter.
// It inherits all the functions of CUsbIo and CUsbIoPipe.
#include "MyWriter.h"



// default constructor
CMyWriter::CMyWriter()
{
  // initialize variables
  m_file = NULL;
  m_cnt = 0;
} // CMyWriter


// destructor
CMyWriter::~CMyWriter()
{
  // close the file if still open
  if ( m_file != NULL ) {
    fclose(m_file);
    m_file = NULL;
  }
} // ~CMyWriter


// open the input file
// returns TRUE for success, FALSE otherwise
// This function must be called before starting the worker thread.
// The worker thread reads the data from this file.
BOOL CMyWriter::OpenFile(const char* Filename)
{
  if ( m_file!=NULL ) {
    // already open, close first
    fclose(m_file);
  }
  // open file, in binary mode
  m_file = fopen(Filename,"rb");
  if ( m_file==NULL ) {
    return FALSE;
  } else { 
    return TRUE;
  }
} // OpenFile


// prepare a buffer
// The buffer is sent to the USBIO driver by the CUsbIoWriter class.
void CMyWriter::ProcessBuffer(CUsbIoBuf* Buf)
{
  // check if the file handle is valid
  if ( m_file!=NULL ) {
    // read data from file
    Buf->NumberOfBytesToTransfer = fread(Buf->Buffer(),1,Buf->Size(),m_file);
    // if the file end has been reached, "fread" returns 0
    if (Buf->NumberOfBytesToTransfer == 0) {
      if (m_cnt>0) {
        // terminate the thread by setting the OperationFinished flag
        Buf->OperationFinished = true;
        printf("-\n");
      } else {
        // send a zero packet the first time the file end is reached
        // Whether this zero packet is required depends on the protocol.
        printf("0");
      }
      // increment the counter
      m_cnt++;
    } else {
      // set the OperationFinished flag to false
      // This indicates to the CUsbIoWriter class that this 
      // is not the end of data transmission.
      Buf->OperationFinished = false;
      // print a '*' for each buffer transferred
      printf("*");
    }
  } else {
    // the file handle is not valid
    printf("File was not opened!\n");
    // tell the CUsbIoWriter class to stop the worker thread
    Buf->OperationFinished = true;
  }
} // ProcessBuffer


void CMyWriter::OnThreadExit()
{
  // At this point the main process can be informed
  // that the thread is finished.
  printf("Worker thread exits.\n");
  // set the global event in order to signal the main thread
  if ( g_TerminateEvent!=NULL )  SetEvent(g_TerminateEvent);

} // OnThreadExit



void CMyWriter::BufErrorHandler(CUsbIoBuf* Buf)
{
  printf("Write error: 0x%X\n",Buf->Status);

} // BufErrorHandler


/************************************ EOF *********************************/
