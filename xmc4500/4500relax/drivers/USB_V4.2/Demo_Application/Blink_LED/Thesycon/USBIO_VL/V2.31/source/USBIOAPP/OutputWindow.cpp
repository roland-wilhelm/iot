// OutputWindow.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "OutputWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// COutputWinDlg dialog


COutputWinDlg::COutputWinDlg(CWnd* pParent /*=NULL*/)
  : CDialog(COutputWinDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(COutputWinDlg)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

	m_InitialMove = false;
	m_ByMsg = false;
	m_Docked = true;
}


COutputWinDlg::~COutputWinDlg()
{

}



BOOL COutputWinDlg::OnInitDialog() 
{
  RECT rect;
  CDialog::OnInitDialog();
  
  // TODO: Add extra initialization here

	// init font
  BOOL succ = m_font.CreatePointFont(
                100,  //int nPointSize, 
                "Courier",  //LPCTSTR lpszFaceName,
                NULL        // CDC* pDC = NULL
                ); 
  if ( succ ) {
    m_EditControl.SetFont(&m_font);
  } else {
    AfxMessageBox("Unable to initialize font.");
  }
  
  // set text limit to 512K
  m_EditControl.SetLimitText(512*1024);

  // initial position: 1,1
  GetWindowRect(&rect);
  MoveWindow(1,1,rect.right,rect.bottom,true); 


  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}



void COutputWinDlg::OutputString(const char *s)
{
  int len;
  int limit;
  
  // get current length
  len=m_EditControl.GetWindowTextLength(); 
  // get limit
  limit = m_EditControl.GetLimitText() - 2048;

  if ( len > limit ) {
    // delete 8K text
    m_EditControl.SetSel(0,8192);
    m_EditControl.Clear();
    len=m_EditControl.GetWindowTextLength(); 
  }
  // append string
  m_EditControl.SetSel(len,len);
  m_EditControl.ReplaceSel(s, FALSE);
} 




void COutputWinDlg::Clear()
{ 
  // set new contents
  m_EditControl.SetWindowText("");
}



void COutputWinDlg::UpdateClientWindow()
{
  CRect cr;
  
  GetClientRect(cr);
  m_EditControl.MoveWindow(cr);
}


void COutputWinDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(COutputWinDlg)
  DDX_Control(pDX, IDC_EDIT_OUTPUTWIN, m_EditControl);
  //}}AFX_DATA_MAP
}


void COutputWinDlg::OnOK()
{
}

void COutputWinDlg::OnCancel()
{
  // hide window
  ShowWindow(SW_HIDE);
}


BEGIN_MESSAGE_MAP(COutputWinDlg, CDialog)
  //{{AFX_MSG_MAP(COutputWinDlg)
  ON_WM_SIZE()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP

  ON_MESSAGE(WM_USER_PING_OUTPUT_WIN,OnMessagePingOutputWin)
  ON_MESSAGE(WM_USER_PRINT_OUT,OnMessagePrintOut)
  ON_MESSAGE(WM_USER_CLEAR_OUTPUT_WIN,OnMessageClearOutputWin)
  ON_MESSAGE(WM_USER_SHOW_OUTPUT_WIN,OnMessageShowOutputWin)
  ON_MESSAGE(WM_USER_MOVE_OUTPUT_WIN,OnMessageMoveOutputWin)
  ON_MESSAGE(WM_USER_SIZE_OUTPUT_WIN,OnMessageSizeOutputWin)
  ON_MESSAGE(WM_USER_DOCK_OUTPUT_WIN,OnMessageDockOutputWin)
  ON_MESSAGE(WM_USER_DESTROY_OUTPUT_WIN,OnMessageDestroyOutputWin)

END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// COutputWinDlg message handlers


void COutputWinDlg::OnSize(UINT nType, int cx, int cy) 
{
  // call base class
  CDialog::OnSize(nType, cx, cy);
  
  // adjust client window (edit control)
  UpdateClientWindow();
  
/*
	// undock if resized by user
	if ( m_InitialMove && !m_ByMsg ) {
		m_Docked = false;
	}
*/
}


void COutputWinDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// undock if moved by user
	if ( m_InitialMove && !m_ByMsg ) {
		m_Docked = false;
	}
}



//
// Message Handler for WM_USER_PING_OUTPUT_WIN
//
long COutputWinDlg::OnMessagePingOutputWin(UINT nID, LPARAM lParam)
{
	// just return 0
  return 0;
}


//
// Message Handler for WM_USER_PRINT_OUT
//
// get string buffer from message, print out, free buffer
//
long COutputWinDlg::OnMessagePrintOut(UINT nID, LPARAM lParam)
{
  const char* buffer = (const char*)lParam;

  if ( buffer!=NULL ) {
    // print to output window
    OutputString(buffer);
  }

  return 0;
}


//
// Message Handler for WM_USER_CLEAR_OUTPUT_WIN
//
long COutputWinDlg::OnMessageClearOutputWin(UINT nID, LPARAM lParam)
{
  Clear();

  return 0;
}


//
// Message Handler for WM_USER_SHOW_OUTPUT_WIN
//
// show/hide output window
//
long COutputWinDlg::OnMessageShowOutputWin(WPARAM wParam, LPARAM lParam)
{
	int force = lParam;
	int show = wParam;

	m_ByMsg = true;

  if ( show ) {
		
		if ( force || (IsWindowVisible() && !IsIconic()) ) {
			// make sure our win is the top window
			SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			SetWindowPos(&CWnd::wndNoTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			ShowWindow(SW_SHOWNORMAL);

			//m_EditControl.SetSel(-1, 0);
		}
  
  } else {
    // hide window
    ShowWindow(SW_HIDE);
  }

	m_ByMsg = false;

  return 0;
}


//
// Message Handler for WM_USER_MOVE_OUTPUT_WIN
//
// move output window
//
long COutputWinDlg::OnMessageMoveOutputWin(WPARAM wParam, LPARAM lParam)
{
	int x = wParam;
	int y = lParam;
	
	if ( !m_Docked ) {
		// ignore this mesage
		return 0;
	}
	
	m_ByMsg = true;

	// current pos and size
	CRect wr;
	GetWindowRect(wr);
	wr.NormalizeRect();
	// new rect
	CRect r(CPoint(x,y), wr.Size());
  MoveWindow(r,true);

	if ( !m_InitialMove ) {
		// show window after initial move
		ShowWindow(SW_SHOW);
		m_InitialMove = true;
	}

	m_ByMsg = false;

  return 0;
}


//
// Message Handler for WM_USER_SIZE_OUTPUT_WIN
//
// resize output window
//
long COutputWinDlg::OnMessageSizeOutputWin(WPARAM wParam, LPARAM lParam)
{
	int cx = wParam;
	int cy = lParam;
	
	m_ByMsg = true;

	// current pos and size
	CRect wr;
	GetWindowRect(wr);
	wr.NormalizeRect();
	// new rect
	CRect r(wr.TopLeft(), CSize(cx,cy));
  MoveWindow(r,true);

	m_ByMsg = false;

  return 0;
}


//
// Message Handler for WM_USER_DOCK_OUTPUT_WIN
//
// move and dock output window
//
long COutputWinDlg::OnMessageDockOutputWin(WPARAM wParam, LPARAM lParam)
{
	int x = wParam;
	int y = lParam;
	
	m_Docked = true;
	
	m_ByMsg = true;

	// current pos and size
	CRect wr;
	GetWindowRect(wr);
	wr.NormalizeRect();
	// new rect
	CRect r(CPoint(x,y), wr.Size());
  MoveWindow(r,true);

	m_ByMsg = false;

  return 0;
}


//
// Message Handler for WM_USER_DESTROY_OUTPUT_WIN
//
// destroy the window 
//
long COutputWinDlg::OnMessageDestroyOutputWin(UINT nID, LPARAM lParam)
{

  // destroy output window,
  // this sends WM_QUIT to the owning thread
  DestroyWindow();

  return 0;
}




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// COutputWin
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(COutputWin, CWinThread)

COutputWin::COutputWin()
{
  m_hWndMainWindow = NULL;
}

COutputWin::~COutputWin()
{
}


BOOL COutputWin::InitInstance()
{
  BOOL succ = TRUE;

	// get/create pointer to parent win
  //CWnd* pParent = CWnd::FromHandle(m_hwndParent);
  // use Desktop
  CWnd* pParent = NULL;
  // create the dialog window, this must be done from this thread context
  succ = m_Dialog.Create(COutputWinDlg::IDD, pParent);


  // It is important to set CWinThread::m_pMainWnd to the user interface
  // window.  This is required so that when the m_pMainWnd is destroyed,
  // the CWinThread is also automatically destroyed.  For insight into
  // how the CWinThread is automatically destroyed when the m_pMainWnd
  // window is destroyed, see the implementation of CWnd::OnNcDestroy
  // in wincore.cpp of the MFC sources.
  if (succ) {
    m_pMainWnd = &m_Dialog;

    // save window handle
    m_hWndMainWindow = m_pMainWnd->m_hWnd;

    // don't delete COutputWin object at thread termination
    // this is done by CloseAndTerminate()
    m_bAutoDelete = FALSE;
  }

  return succ;
}


int COutputWin::ExitInstance()
{
  // invalidate handle
  m_hWndMainWindow = NULL;

  return CWinThread::ExitInstance();
}


//
// called in the context of the APPs main thread
//
BOOL COutputWin::CloseAndTerminate()
{
  // destroy output window,
  // this terminates the thread, too
  SendMessageToMainWnd(WM_USER_DESTROY_OUTPUT_WIN,0,0);
  
  // wait for termination of the thread
  if ( m_hThread!=NULL ) {
    ::WaitForSingleObject(m_hThread,INFINITE);
  }

  // delete this object
  delete this;

  return TRUE;
}



BEGIN_MESSAGE_MAP(COutputWin, CWinThread)
  //{{AFX_MSG_MAP(COutputWin)
    // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


