/************************************************************************
 *
 *  Module:       CThreadBase.h
 *  Long name:    Thread base class
 *  Description:  
 *  Provides the functionality for managing (start/run/stop) a worker thread.
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __CThreadBase_h__
#define __CThreadBase_h__


//
// CThreadBase
//
// This class implements basic management of a worker thread.
//
class CThreadBase
{
public:
	// ctor
	CThreadBase();
	// dtor
	virtual ~CThreadBase();

////////////////////////////////////////////////////////////
// interface

	// start thread
	// returns true for success, false otherwhise
	bool StartThread();
	
  // shutdown thread
	// The function sets TerminateFlag to true, calls the virtual member function
  // TerminateThread() that should cause the thread to terminate itself, 
	// it does not block until the thread ius terminated
  // IMPORTANT: This function must be called before the CThreadBase object is
  // destroyed, that means before ~CThreadBase() is called !
	// returns true if thread was terminated, false if thread is not running
	void ShutdownThread();

	// this function can be called immediatly after a call to shutdown thread
	// to wait for the compleation
	// it must be called at least in the destructor of the derived class
	bool WaitForThreadTermination();

	// set the thread priority
	BOOL SetPriority(int Priority) {	return SetThreadPriority(mThreadHandle,Priority);}



////////////////////////////////////////////////////////////
// implementation:
protected:

  // This routine is called in the context of ShutdownThread().
	// It has to ensure that the thread will terminate itself by returning
	// from ThreadRoutine().
  virtual void TerminateThread() = 0;

	// This is the main routine that is executed by the thread. 
	// It is executed by the worker thread after startup.
	// It must be implemented by a derived class.
	// The routine has to return when mTerminateFlag is set to true and the mTerminateEvent is set.
	virtual void ThreadRoutine() = 0;

  // This notification handler is called by the worker thread before
  // the thread terminates itself. That means it is called in the context
	// of the worker thread.
	// The function can be overloaded by derived classes to perform 
	// some cleanup processing. CThreadBase provides a default implementation
	// which does nothing.
  virtual void OnThreadExit();



////////////////////////////////////////////////////////////
// CThreadBase internals

	// system thread routine
	static unsigned int __stdcall beginthread_routine(void *StartContext);

	// system thread object
	HANDLE mThreadHandle;
	unsigned int mThreadID;

	// variables used by the thread routine
	volatile bool mTerminateFlag;
	// this event is set if the thread should be terminated
	HANDLE mTerminateEvent;

};	// class CThreadBase



#endif // __CThreadBase_h__
 
/*************************** EOF **************************************/
