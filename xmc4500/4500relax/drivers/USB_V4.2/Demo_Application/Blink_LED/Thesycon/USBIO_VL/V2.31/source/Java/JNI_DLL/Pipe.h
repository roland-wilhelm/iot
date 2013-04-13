/************************************************************************
 *
 *  Module:       CPipe.cpp
 *  Long name:    Pipe
 *  Description:  abstraction for a pipe class
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#if !defined(AFX_PIPE_H__D29A8FF1_B452_4256_BD4E_8B0DCAAA9FDF__INCLUDED_)
#define AFX_PIPE_H__D29A8FF1_B452_4256_BD4E_8B0DCAAA9FDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UsbIoBufPoolVar.h"

class CPipe : public CUsbIoPipe  
{
public:
	CPipe();
	virtual ~CPipe();

	CUsbIoBufPoolVar BufPool;

#ifdef _DEBUG
	UCHAR mDbgEndpointAddress;
#endif
};

#endif // !defined(AFX_PIPE_H__D29A8FF1_B452_4256_BD4E_8B0DCAAA9FDF__INCLUDED_)
