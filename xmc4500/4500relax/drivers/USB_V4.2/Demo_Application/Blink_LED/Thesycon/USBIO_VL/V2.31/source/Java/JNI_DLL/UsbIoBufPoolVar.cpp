/************************************************************************
 *
 *  Module:       UsbIoBufPoolVar.cpp
 *  Long name:    Buffer Pool Variable
 *  Description:  new variable buffer pool
 *
 *  Runtime Env.: Win32
 *  Author(s):    Frank Hofmann
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/


#include "stdafx.h"
#include "UsbIoBufPoolVar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsbIoBufPoolVar::CUsbIoBufPoolVar()
{
  Head = NULL;
  Count = 0;

  InitializeCriticalSection(&CritSect);
} // CUsbIoBufPoolVar

CUsbIoBufPoolVar::~CUsbIoBufPoolVar()
{
  Free();
  DeleteCriticalSection(&CritSect);
} // ~CUsbIoBufPoolVar


void CUsbIoBufPoolVar::Free()
{
	CUsbIoBufEx* Buf;
  EnterCriticalSection(&CritSect);

	while (!BufVector.empty()) {
		Buf = BufVector.back();
		BufVector.pop_back();
		delete Buf;
	}

  Head = NULL;
  Count = 0;

  LeaveCriticalSection(&CritSect);
} // Free


// returns the next buffer or NULL if empty
CUsbIoBufEx* CUsbIoBufPoolVar::Get()
{
  CUsbIoBufEx *buf;

  EnterCriticalSection(&CritSect);

  buf = Head;
  if (buf == NULL) {
    // pool is empty
  } else {
    Head = buf->Next;
    buf->Next = NULL;
    InterlockedDecrement(&Count);
  }

  LeaveCriticalSection(&CritSect);

  return buf;
} // Get



void CUsbIoBufPoolVar::Put(CUsbIoBufEx* Buf)
{
  EnterCriticalSection(&CritSect);

  Buf->Next = Head;
  Head = Buf;
  InterlockedIncrement(&Count);

  LeaveCriticalSection(&CritSect);
} // Put


BOOL CUsbIoBufPoolVar::IncreaseBufPoolSize(DWORD NumberOfBuffers)
{
  DWORD i;
  CUsbIoBufEx *buf;
  BOOL succ = TRUE;

  EnterCriticalSection(&CritSect);


	for (i=0;i<NumberOfBuffers;i++) {
		buf = new CUsbIoBufEx();
    if ( buf==NULL ) {
      // failed
			succ = FALSE;
			break;
    }
    buf->setBufMemPointer(NULL);
    buf->setBufMemSize(0);
    buf->Next = Head;
    Head = buf;
		BufVector.push_back(buf);
		InterlockedIncrement(&Count);
	}

  LeaveCriticalSection(&CritSect);

  return succ;
} // IncreaseBufPoolSize


/****************************** EOF ********************************/
