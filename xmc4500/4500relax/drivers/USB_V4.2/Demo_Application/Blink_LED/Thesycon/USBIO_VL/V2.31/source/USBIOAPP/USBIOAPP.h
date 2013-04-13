// USBIOAPP.h : main header file for the USBIOAPP application
//

#if !defined(AFX_USBIOAPP_H__3F6259E9_6055_11D2_9E20_0080C8272F6C__INCLUDED_)
#define AFX_USBIOAPP_H__3F6259E9_6055_11D2_9E20_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"   // main symbols

#include "global.h"
#include "USBIOAPPDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPApp:
// See USBIOAPP.cpp for the implementation of this class
//

class CUSBIOAPPApp : public CWinApp
{
public:
  CUSBIOAPPApp();

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CUSBIOAPPApp)
  public:
  virtual BOOL InitInstance();
  virtual int ExitInstance();
  //}}AFX_VIRTUAL

  // send message to output window (synchronous)
  LRESULT SendMsgToOutputWin(UINT Msg, WPARAM wParam, LPARAM lParam)
      { return (m_OutputWin==NULL) ? (-1) : m_OutputWin->SendMessageToMainWnd(Msg,wParam,lParam); }


  // update enable/disable state of controls
  void UpdateStateOfControls()  { m_MainDlg.UpdateStateOfControls(); }

	// returns true if pWnd points to the output window
	bool IsOutputWindow(CWnd* pWnd)
		{ return ( (pWnd==NULL || m_OutputWin==NULL) ? false : (pWnd->m_hWnd == m_OutputWin->m_hWndMainWindow) ); }

// Implementation
protected:

  // pointer to output window instance
  // created by AfxBeginThread
  COutputWin* m_OutputWin; 
  // the application's main dialog
  CUSBIOAPPDlg m_MainDlg;

public:
  //{{AFX_MSG(CUSBIOAPPApp)
    // NOTE - the ClassWizard will add and remove member functions here.
    //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// The one and only CUSBIOAPPApp object

extern CUSBIOAPPApp theApp;



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_USBIOAPP_H__3F6259E9_6055_11D2_9E20_0080C8272F6C__INCLUDED_)
