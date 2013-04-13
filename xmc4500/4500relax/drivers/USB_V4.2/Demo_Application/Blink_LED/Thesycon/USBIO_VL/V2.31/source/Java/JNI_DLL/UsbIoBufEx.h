/************************************************************************
 *
 *  Module:       UsbIoBufEx.h
 *  Long name:    Extended buffer pool
 *  Description:  
 *
 *  Runtime Env.: Win32
 *  Author(s):    Frank Hofmann
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#if !defined(AFX_USBIOBUFEX_H__E1499CAF_FAD8_4BBB_94E6_DF378C5E6912__INCLUDED_)
#define AFX_USBIOBUFEX_H__E1499CAF_FAD8_4BBB_94E6_DF378C5E6912__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UsbioPipe.h"

class CUsbIoBufEx : public CUsbIoBuf  
{
public:
	CUsbIoBufEx();
	virtual ~CUsbIoBufEx();

	void* getBufMemPointer() {
		return BufferMem;
	}

	void setBufMemPointer(void* Mem) {
		BufferMem = Mem;
	}

	DWORD getBufMemSize() {
		return BufferSize;
	}

	void setBufMemSize(DWORD Size) {
		BufferSize = Size;
	}

	CUsbIoBufEx* Next;

}; // CUsbIoBufEx

#endif // !defined(AFX_USBIOBUFEX_H__E1499CAF_FAD8_4BBB_94E6_DF378C5E6912__INCLUDED_)

/**********************************  EOF *********************************/
