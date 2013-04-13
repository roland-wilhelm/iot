/************************************************************************
 *
 *  Module:       UsbIoBufPoolVar.h
 *  Long name:    Buffer Pool Variable
 *  Description:  new variable buffer pool
 *
 *  Runtime Env.: Win32
 *  Author(s):    Frank Hofmann
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#if !defined(AFX_USBIOBUFPOOLVAR_H__2F866A7A_546E_478D_A715_6CCE4162EB34__INCLUDED_)
#define AFX_USBIOBUFPOOLVAR_H__2F866A7A_546E_478D_A715_6CCE4162EB34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "UsbIoBufEx.h"

class CUsbIoBufPoolVar  
{
public:
	CUsbIoBufPoolVar();
	virtual ~CUsbIoBufPoolVar();

  //
  // free all elements of the buffer pool
  //
  void
  Free();

  //
  // returns the current number of buffers in the pool
  //
  long
  CurrentCount()    { return Count; }

  //
  // get a buffer from pool
  // returns NULL if the pool is empty
  //
  CUsbIoBufEx* 
  Get();

  //
  // put a buffer back to the pool
  //
  void
  Put(
    CUsbIoBufEx* Buf
    );

	BOOL
	IncreaseBufPoolSize(
		DWORD NumberOfBuffers
		);


protected:
	std::vector<CUsbIoBufEx*> BufVector;

  // current number of buffers in pool
  long Count;

  // head of buffer chain
  CUsbIoBufEx* Head;
	
  // protects the pool
  CRITICAL_SECTION CritSect;

};

#endif // !defined(AFX_USBIOBUFPOOLVAR_H__2F866A7A_546E_478D_A715_6CCE4162EB34__INCLUDED_)

/*********************************** EOF ***********************************/

