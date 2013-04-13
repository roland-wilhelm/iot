// USBIOAPP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// registry path where the app settings will be stored
// relative to HKEY_CURRENT_USER\\Software
static const char sAppRegKey[] = "Thesycon\\USBIO\\V" VERSION_STR ;



/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPApp

BEGIN_MESSAGE_MAP(CUSBIOAPPApp, CWinApp)
  //{{AFX_MSG_MAP(CUSBIOAPPApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPApp construction

CUSBIOAPPApp::CUSBIOAPPApp()
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
  m_OutputWin = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUSBIOAPPApp object

CUSBIOAPPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPApp initialization

BOOL CUSBIOAPPApp::InitInstance()
{

  // create a separate thread that controls the output window
  m_OutputWin = (COutputWin*)AfxBeginThread(RUNTIME_CLASS(COutputWin));
  ASSERT(m_OutputWin!=NULL);

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

	#if _MFC_VER < 0x0700
		#ifdef _AFXDLL
			Enable3dControls();     // Call this when using MFC in a shared DLL
		#else
			Enable3dControlsStatic(); // Call this when linking to MFC statically
		#endif
	#endif

	// set path where our settings will be stored
	SetRegistryKey(sAppRegKey);

	// wait until the output window thread has entered its message loop
	while ( 0 != SendMsgToOutputWin(WM_USER_PING_OUTPUT_WIN,0,0) ) {
		::Sleep(10);
	}

  // execute main dialog
	m_pMainWnd = &m_MainDlg;
  int nResponse = m_MainDlg.DoModal();
  // dialog was closed
  if (nResponse == IDOK)
  {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with OK
  }
  else if (nResponse == IDCANCEL)
  {
    // TODO: Place code here to handle when the dialog is
    //  dismissed with Cancel
  }

  // Since the dialog has been closed, return FALSE so that we exit the
  //  application, rather than start the application's message pump.
  return FALSE;
}



int CUSBIOAPPApp::ExitInstance()
{
  // destroy output window
  if ( m_OutputWin!=NULL ) {
    m_OutputWin->CloseAndTerminate();
    m_OutputWin = NULL;
  }

  // call base class
  return CWinApp::ExitInstance();
}


