/************************************************************************
 *
 *  Module:       CThreadPnPNotify.h
 *  Long name:    Thread PnP notification
 *  Description:  covers the PnP notification for applications
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#if !defined(AFX_CTHREADPNPNOTIFY_H__9D904304_7A1F_4398_BC0C_AB2965B2FC84__INCLUDED_)
#define AFX_CTHREADPNPNOTIFY_H__9D904304_7A1F_4398_BC0C_AB2965B2FC84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include <Dbt.h>
#include "CThreadBase.h"
#include "CGuidList.h"
#include <windows.h>
#include <stdio.h>

#define NOTIFY_ADD		1
#define NOTIFY_REMOVE 2

extern CGuidList gGuidList;

class CThreadPnPNotify : public CThreadBase
{

public:

	typedef void BASE_CLASS_CALLBACK_FUNCTION (void *Context, int Function);


	// constructor
	CThreadPnPNotify();

	// destructor
	virtual ~CThreadPnPNotify();


	// start the thread
	// GUID must be set first
	bool Start();

	// shutdown thread
	bool Stop();

	// register the callback function
	void RegisterCallback(void *Context, BASE_CLASS_CALLBACK_FUNCTION *CallbackFunction);

	void* GetContext();

	// set the event
	// call the callback function registered with RegisterCallback
	void SetEv(DWORD Type);
	
	// get the GUID
	GUID GetGuid() {return mGuid;}

	// set the guid
	void SetGuid(const GUID& DeviceGuid) {mGuid = DeviceGuid;}


protected:
	// internal shutdown thread
	void ShutdownThread();

	// thread routine
	void ThreadRoutine();

	// terminte thread
	void TerminateThread();


public:
	//HDEVNOTIFY
	HANDLE mDevNotify;

protected:
	// the GUID
	GUID mGuid;

	// window handle
	HWND mhWnd;

	// pointer to the callback function
	BASE_CLASS_CALLBACK_FUNCTION *mCallbackFunction; 

	// pointer to the class of the callback function
	void	*mContext;

	static long smInstanceCounter;

};

#endif // !defined(AFX_CTHREADPNPNOTIFY_H__9D904304_7A1F_4398_BC0C_AB2965B2FC84__INCLUDED_)
