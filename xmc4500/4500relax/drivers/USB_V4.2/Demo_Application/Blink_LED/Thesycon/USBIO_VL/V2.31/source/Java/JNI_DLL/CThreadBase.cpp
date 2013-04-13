/************************************************************************
 *
 *  Module:       CThreadBase.cpp
 *  Long name:    Thread base class
 *  Description:  
 *  Provides the functionality for managing (start/run/stop) a worker thread.
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

// for shorter and faster windows.h
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
// unicode is not supported by USBIOLIB
#ifdef UNICODE
#undef UNICODE
#endif

#include "stdafx.h"
/*
#include <windows.h>*/
#include <process.h>
#include "CThreadBase.h"


// ctor
CThreadBase::CThreadBase()
{
	mThreadHandle = NULL;
	mThreadID = 0;
	mTerminateFlag = false;
	mTerminateEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
}


CThreadBase::~CThreadBase()
{
	HANDLE ThreadHandle;

	ThreadHandle = (HANDLE)InterlockedExchange((long *)&mThreadHandle,NULL); //lint !e740
	if ( ThreadHandle!=NULL ) {
		WaitForSingleObject(ThreadHandle,INFINITE);	//lint !e534
		// close thread handle
		CloseHandle(ThreadHandle);	
	}
	if (mTerminateEvent != NULL) {
		CloseHandle(mTerminateEvent);
		mTerminateEvent = NULL;
	}
}




bool
CThreadBase::StartThread()
{
	bool succ = false;

	if ( mThreadHandle != NULL  && mTerminateFlag) {
			// not yet completet
			WaitForThreadTermination();	//lint !e534
	} 

	if ( mThreadHandle != NULL ) {
		// already started
	} else {
	
		// init flag
		mTerminateFlag = false;
		ResetEvent(mTerminateEvent);
		
		// create new thread
		// we use _beginthreadex, it is a wrapper for the Win32 API CreateThread
		mThreadHandle = (HANDLE)
			_beginthreadex( 
						NULL,									// void *security,
						0,										// unsigned stack_size, 
						beginthread_routine,	// unsigned ( __stdcall *start_address )( void * ),
						this,									// void *arglist,
						0,										// unsigned initflag,
						&mThreadID						// unsigned *thrdaddr
						);
		if ( mThreadHandle == NULL ) {
			// failed
		} else {
			// success
			succ = true;
		}
	}

	return succ;
}



void
CThreadBase::ShutdownThread()
{

	if ( mThreadHandle == NULL ) {
		// not running
	} else {
		// set flag to force termination
		mTerminateFlag = true;
		// set the event to wake up the thread
		SetEvent(mTerminateEvent);
		// call virtual member function
		TerminateThread();
	}
}


bool
CThreadBase::WaitForThreadTermination()
{
	bool succ = false;
	HANDLE ThreadHandle;

	ThreadHandle = (HANDLE)InterlockedExchange((long *)&mThreadHandle,NULL);	//lint !e740
	if ( ThreadHandle == NULL ) {
		// not running
	} else {
		// wait on thread handle
		DWORD err = WaitForSingleObject(ThreadHandle,INFINITE);
		if ( err ) {
			succ = false;
		} else {
			succ = true;
		}

		// close thread handle
		CloseHandle(ThreadHandle);
	}

	return succ;
}

// system thread routine
unsigned int
__stdcall 
CThreadBase::beginthread_routine(void *StartContext)
{
	CThreadBase *This = (CThreadBase*)StartContext;
	// call virtual member function
	This->ThreadRoutine();
	// call notification handler
	This->OnThreadExit();

	// terminate the thread
	return 0;
}



// default implementation of virtual functions


void
CThreadBase::OnThreadExit()
{
	// empty
}




/*************************** EOF **************************************/
