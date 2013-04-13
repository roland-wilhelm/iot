/************************************************************************
 *
 *  Module:       CThreadPnPNotify.cpp
 *  Long name:    Thread PnP notification
 *  Description:  covers the PnP notification for applications
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// globals
CGuidList gGuidList;


// window class name registered
const char gWndClassName[] = "USBIOJAVA_ThreadPnPNotify_WndClass";

// window title
const char gWndTitle[] = "USBIOJAVA PnP Notify";


long CThreadPnPNotify::smInstanceCounter = 0;




// Window Proc
// Processes messages for the main window.
static
LRESULT
CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT retcode = 0;

	DEV_BROADCAST_HDR *pointer;
	DEV_BROADCAST_DEVICEINTERFACE *devpointer;
	CThreadPnPNotify *NotifyThread;

	NotifyThread = NULL;
	switch (message) {

	case WM_DEVICECHANGE:
		{
			switch(wParam)
			{
			case DBT_DEVICEARRIVAL:
				{
					// device was added
					if (lParam!=NULL) {
						pointer = (DEV_BROADCAST_HDR*)lParam;
						if (pointer->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
							devpointer = (DEV_BROADCAST_DEVICEINTERFACE*)pointer;	//lint !e740 !e826
							if (gGuidList.Lookup(devpointer->dbcc_classguid, &NotifyThread)) {
								if (NotifyThread!=NULL) {
									TRACE(4,tprint("sending DBT_DEVICEARRIVAL notification\n"));
									NotifyThread->SetEv(NOTIFY_ADD);
								}
							}	
						}
					}
				}
				break;
			case DBT_DEVICEREMOVECOMPLETE :
				{
					// device was removed
					if (lParam!=NULL) {
						pointer = (DEV_BROADCAST_HDR*)lParam;
						if (pointer->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
							devpointer = (DEV_BROADCAST_DEVICEINTERFACE*)pointer;	//lint !e740 !e826
							if (gGuidList.Lookup(devpointer->dbcc_classguid, &NotifyThread)) {
								if (NotifyThread!=NULL) {
									TRACE(4,tprint("sending DBT_DEVICEREMOVECOMPLETE notification\n"));
									NotifyThread->SetEv(NOTIFY_REMOVE);
								}
							}	
						}
					}
				}
				break;
			default:
				break;
			}//switch
		}
		break;
	
	case WM_CLOSE:
	default:
		// let DefWindowProc handle the message
		// it handles standard messages like WM_CLOSE, WM_QUIT...
		retcode = DefWindowProc(hWnd, message, wParam, lParam);
		break;
  }//switch
  
	return retcode;
}//WndProc


static
ATOM
RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex,sizeof(wcex));
	wcex.cbSize = sizeof(wcex); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	//wcex.cbClsExtra		= 0;
	//wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	//wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= gWndClassName;
	//wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}//RegisterWndClass


static
void
UnregisterWndClass(HINSTANCE hInstance)
{
	UnregisterClass(gWndClassName, hInstance);	//lint !e534
}//UnregisterWndClass




CThreadPnPNotify::CThreadPnPNotify()
{
	TRACE(4,tprint("CThreadPnPNotify\n"));

	mDevNotify = NULL;
	ZeroMemory(&mGuid,sizeof(mGuid));
	mhWnd = NULL;
	mCallbackFunction = NULL;
	mContext = NULL;

	if ( 1==InterlockedIncrement(&smInstanceCounter) ) {
		//RegisterWndClass(_Module.GetModuleInstance());	//lint !e534
		RegisterWndClass(NULL);	//lint !e534
	}
}


CThreadPnPNotify::~CThreadPnPNotify()
{
	TRACE(4,tprint("~CThreadPnPNotify\n"));

	if ( 0==InterlockedDecrement(&smInstanceCounter) ) {
		//UnregisterWndClass(_Module.GetModuleInstance());
		UnregisterWndClass(NULL);
	}
	mDevNotify = NULL;
	mhWnd = NULL;
	mCallbackFunction = NULL;
	mContext = NULL;
}






void CThreadPnPNotify::ThreadRoutine()
{

	TRACE(4,tprint("Entering CThreadPnPNotify::ThreadRoutine\n"));

	// create our one and only window	
  mhWnd = CreateWindow(
								gWndClassName, 
								gWndTitle, 
								WS_OVERLAPPEDWINDOW,	// window style
								20,				// horizontal position of window
								20,										// vertical position of window
								300,				// window width
								200,				// window height
								NULL,					// handle to parent or owner window
								NULL,					// menu handle or child identifier
								NULL, //_Module.GetModuleInstance(), 
								NULL
								);
	if ( mhWnd==NULL ) {
		// failed
		//CoUninitialize();
		TRACE(1,tprint("CThreadPnPNotify::ThreadRoutine: CreateWindow failed\n"));
		return;
	}

	// show/hide window on screen
	ShowWindow(mhWnd, SW_HIDE);	//lint !e534
  UpdateWindow(mhWnd);	//lint !e534

  DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	// fill structure
  ZeroMemory(&NotificationFilter, sizeof(NotificationFilter) );
  NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
  NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
  NotificationFilter.dbcc_classguid = mGuid;

  // device notifications should be send to the main dialog
  mDevNotify = ::RegisterDeviceNotification(
                    mhWnd, 
                    &NotificationFilter,
                    DEVICE_NOTIFY_WINDOW_HANDLE
                    );
  if ( mDevNotify==NULL ) {
		TRACE(1,tprint("CThreadPnPNotify::ThreadRoutine: RegisterDeviceNotification failed\n"));
		CoUninitialize();
    return;
  }


	MSG msg;

	// enter message loop
	TRACE(4,tprint("CThreadPnPNotify::ThreadRoutine: Entering message loop\n"));
	// process windows messages
	while ( GetMessage(&msg, NULL, 0, 0) )  {
		TranslateMessage(&msg);	//lint !e534
		DispatchMessage(&msg);	//lint !e534
	}
	// end while with WM_QUIT message
	TRACE(4,tprint("CThreadPnPNotify::ThreadRoutine: Message loop terminated\n"));

	CoUninitialize();
	TRACE(4,tprint("Leaving CThreadPnPNotify::ThreadRoutine\n"));
	return;
}


void CThreadPnPNotify::TerminateThread()
{
}


void CThreadPnPNotify::SetEv(DWORD Type)
{
	if (mCallbackFunction!=NULL && mContext!=NULL) {
		// send PnP Event
		TRACE(4,tprint("CThreadPnPNotify: Issuing PnP Event %d\n",Type));
		(*mCallbackFunction)(mContext,Type);
	}
}


void CThreadPnPNotify::ShutdownThread()
{
	TRACE(4,tprint("Entering CThreadPnPNotify::ShutdownThread\n"));

	CThreadBase::ShutdownThread();
	TRACE(4,tprint("CThreadPnPNotify::ShutdownThread: thread stopped\n"));

  if ( _winver >=0x500 ) {
    if ( mDevNotify!=NULL ) {
			// Unregister the Device Notification winver>=500
			TRACE(4,tprint("CThreadPnPNotify::ShutdownThread: calling UnregisterDeviceNotification\n"));
      ::UnregisterDeviceNotification(mDevNotify);	//lint !e534
      mDevNotify = NULL;
    } 
  }
	if (mhWnd!=NULL) {
		// WM_QUIT is used because our WinProc does not handle the 
		// WM_CLOSE message
		::PostMessage(mhWnd,WM_QUIT,NULL,NULL);	//lint !e534
	}

	TRACE(4,tprint("Leaving CThreadPnPNotify::ShutdownThread\n"));	
}


void CThreadPnPNotify::RegisterCallback(void *Context, BASE_CLASS_CALLBACK_FUNCTION *CallbackFunction)
{
	// register the callback function
  mContext = Context;
  mCallbackFunction = CallbackFunction;
}

void* CThreadPnPNotify::GetContext() {
	return mContext;
}

bool CThreadPnPNotify::Start()
{
	return StartThread();
}


bool CThreadPnPNotify::Stop()
{
	// stop Thread
	TRACE(4,tprint("Entering CThreadPnPNotify::Stop\n"));
	CThreadPnPNotify::ShutdownThread();
	WaitForThreadTermination();	//lint !e534
	TRACE(4,tprint("Leaving CThreadPnPNotify::Stop\n"));
	return true;
}

/******************************* EOF *******************************/
