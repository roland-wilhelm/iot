// USBIOAPPDlg.cpp : implementation file
//

#include "stdafx.h"
#include <dbt.h>
#include "USBIOAPP.h"
#include "USBIOAPPDlg.h"
#include "UsbIoPipe.h"
#include "PipeDialog.h"
#include "hlstatic.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static
const char*
DeviceChangeMsgStr(UINT x);


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_StrVer;
	CString	m_StrCopyright;
	//}}AFX_DATA
	CHyperLinkStatic	m_HlStatic;

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_StrVer.Format("Version %s",MODULE_VERSION_STRING);
	m_StrCopyright.Format("%s",USBIO_COPYRIGHT_STR);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATIC_ABOUT_HL, m_HlStatic);
	DDX_Text(pDX, IDC_STATIC_ABOUT_VER, m_StrVer);
	DDX_Text(pDX, IDC_STATIC_ABOUT_COPYRIGHT, m_StrCopyright);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPDlg dialog

CUSBIOAPPDlg::CUSBIOAPPDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CUSBIOAPPDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CUSBIOAPPDlg)
  //}}AFX_DATA_INIT

  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  //m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  // --> moved to OnInitDialog()
	m_hIcon = NULL;

  m_DevNotify = NULL;
	m_InitialMove = false;

}

CUSBIOAPPDlg::~CUSBIOAPPDlg()
{
  // destroy device list
  CUsbIo::DestroyDeviceList(g_DevList);
  g_DevList = NULL;

}



void CUSBIOAPPDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CUSBIOAPPDlg)
  DDX_Control(pDX, IDC_TAB_MAIN, m_TabControlMain);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUSBIOAPPDlg, CDialog)
  //{{AFX_MSG_MAP(CUSBIOAPPDlg)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON_OUTPUT_WINDOW, OnButtonShowOutputWindow)
  ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
  ON_BN_CLICKED(IDC_BUTTON_CLEAR_OUTPUT_WINDOW, OnButtonClearOutputWindow)
  ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_DOCK_OUTPUT_WINDOW, OnButtonDockOutputWindow)
	//}}AFX_MSG_MAP
  ON_WM_DEVICECHANGE()
  ON_WM_ACTIVATE()
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPDlg message handlers

BOOL CUSBIOAPPDlg::OnInitDialog()
{
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

  // call base class
  CDialog::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  

  // TODO: Add extra initialization here

  // create all dialog page instances, parent window = Tab Control
  VERIFY( m_DlgPgDevice.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgDesc.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgConfig.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgInterface.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgPipes.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgDevreq.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgFeature.Create(&m_TabControlMain) );
  VERIFY( m_DlgPgOther.Create(&m_TabControlMain) );
  // register our dialog page instances with the tab control
  m_TabControlMain.AddDialogPage(&m_DlgPgDevice,IDS_DIALOGPAGE_DEVICE);
  m_TabControlMain.AddDialogPage(&m_DlgPgDesc,IDS_DIALOGPAGE_DESC);
  m_TabControlMain.AddDialogPage(&m_DlgPgConfig,IDS_DIALOGPAGE_CONFIG);
  m_TabControlMain.AddDialogPage(&m_DlgPgInterface,IDS_DIALOGPAGE_INTERFACE);
  m_TabControlMain.AddDialogPage(&m_DlgPgPipes,IDS_DIALOGPAGE_PIPES);
  m_TabControlMain.AddDialogPage(&m_DlgPgDevreq,IDS_DIALOGPAGE_DEVREQ);
  m_TabControlMain.AddDialogPage(&m_DlgPgFeature,IDS_DIALOGPAGE_FEATURE);
  m_TabControlMain.AddDialogPage(&m_DlgPgOther,IDS_DIALOGPAGE_OTHER);
  // update selection
  m_TabControlMain.UpdatePageSelection();

  // set initial state of controls
  UpdateStateOfControls();

	// fill device list
	m_DlgPgDevice.UpdateDeviceList();

  // PrintOut("WinVer %x, OSVer %d"NL,_winver,_osver);
  if (!RegisterDevNotify(&g_UsbioID,&m_DevNotify)) {
    PrintOut("ERROR: Unable to register device notification."NL);
  } 
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  

	// move the main window to its initial position
	CRect rcDlg;
  GetWindowRect(&rcDlg); 
	HWND hwndOwner = ::GetDesktopWindow(); 
	CRect rcOwner;
  ::GetWindowRect(hwndOwner, &rcOwner); 
	int x = rcOwner.left + ((rcOwner.Width() - rcDlg.Width()) / 2) ;
	int y = rcOwner.top + ((rcOwner.Height() - rcDlg.Height() - INITIAL_OUTPUT_WIN_HEIGHT) / 2) ;
	if ( y >= 20 ) y -= 20;
  SetWindowPos(
      &wndTop, 
      x,
      y,
      0, 0,          // ignores size arguments 
      SWP_NOSIZE); 


  return TRUE;  // return TRUE  unless you set the focus to a control
}


void CUSBIOAPPDlg::PostNcDestroy() 
{
  // TODO: Add your specialized code here and/or call the base class

  // destroy all pipe dialog windows
  CPipeDialog *dlg;
  while ( !g_PipeDialogList.IsEmpty() ) {
    dlg = (CPipeDialog*)g_PipeDialogList.GetHead();
    dlg->DestroyWindow();
  }

  // call base class  
  CDialog::PostNcDestroy();
}



void CUSBIOAPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  }
  else
  {
    CDialog::OnSysCommand(nID, lParam);
  }
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUSBIOAPPDlg::OnPaint() 
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSBIOAPPDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}



//////////////////////////////////////////////////////
// control notification handlers
//////////////////////////////////////////////////////

void CUSBIOAPPDlg::OnButtonShowOutputWindow() 
{
  // show output window on screen
  theApp.SendMsgToOutputWin(WM_USER_SHOW_OUTPUT_WIN,1,1);
}


void CUSBIOAPPDlg::OnButtonClearOutputWindow() 
{
  // send msg to output window
  theApp.SendMsgToOutputWin(WM_USER_CLEAR_OUTPUT_WIN,0,0);
}


void CUSBIOAPPDlg::OnButtonDockOutputWindow() 
{
	CRect wr;
	GetWindowRect(wr);

	// send move command to output win
	int x = wr.left;
	int y = wr.bottom;
	theApp.SendMsgToOutputWin(WM_USER_DOCK_OUTPUT_WIN, x, y);

  // show output window on screen
  theApp.SendMsgToOutputWin(WM_USER_SHOW_OUTPUT_WIN,1,1);
}



// called if main window is activated
void CUSBIOAPPDlg::OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized )
{
	TRACE("CUSBIOAPPDlg::OnActivate: nState=%d pWndOther=%08X bMinimized=%d\n",nState,pWndOther,bMinimized);

	if ( !bMinimized ) {
		switch ( nState ) {
		case WA_INACTIVE:
			break;
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			if ( !theApp.IsOutputWindow(pWndOther) ) {
				// show output window on screen
				theApp.SendMsgToOutputWin(WM_USER_SHOW_OUTPUT_WIN,1,0);
			}
			break;
		default:
			break;
		}

	}
}




void CUSBIOAPPDlg::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
  // TODO: Add your control notification handler code here
  
  m_TabControlMain.UpdatePageSelection();

  *pResult = 0;
}



void CUSBIOAPPDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
		
	CRect wr;
	GetWindowRect(wr);

	if ( (wr.top!=0 && wr.left!=0) || m_InitialMove ) {

		if ( !m_InitialMove ) {
			// resize the output window
			int cx = wr.Width();
			int cy = INITIAL_OUTPUT_WIN_HEIGHT;
			theApp.SendMsgToOutputWin(WM_USER_SIZE_OUTPUT_WIN, cx, cy);
			// activate our main dialog
			SetForegroundWindow();
			m_InitialMove = true;
		}

		// send move command to output win
		// will be ignored if not docked
		int x = wr.left;
		int y = wr.bottom;
		theApp.SendMsgToOutputWin(WM_USER_MOVE_OUTPUT_WIN, x, y);
	}
}



void CUSBIOAPPDlg::OnDestroy() 
{
  // close device
  g_UsbIo.Close();

  // The following is a work-around for a bug in Win98,
  // the system becomes unstable if UnregisterDeviceNotification is called
  // Therefore we don't call it on Win98.
  if ( _winver >= 0x500 ) {
    if ( m_DevNotify!=NULL ) {
      UnregisterDeviceNotification(m_DevNotify);
      m_DevNotify = NULL;
    } 
  }

  // call base class
  CDialog::OnDestroy();

}



BOOLEAN CUSBIOAPPDlg::RegisterDevNotify(
  const GUID *InterfaceClassGuid, 
  HDEVNOTIFY *hDevNotify
  )
/*
Routine Description:
    Registers for notification of changes in the device interfaces for
    the specified interface class GUID. 

Parameters:
    InterfaceClassGuid - The interface class GUID for the device 
        interfaces. 

    hDevNotify - Receives the device notification handle. On failure, 
        this value is NULL.

Return Value:
    If the function succeeds, the return value is TRUE.

    If the function fails, the return value is FALSE.
*/
{
    DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;

    ZeroMemory(&NotificationFilter, sizeof(NotificationFilter) );
    NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
    NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    NotificationFilter.dbcc_classguid = *InterfaceClassGuid;

    // device notifications should be send to the main dialog
    *hDevNotify = RegisterDeviceNotification(
                      m_hWnd, 
                      &NotificationFilter,
                      DEVICE_NOTIFY_WINDOW_HANDLE
                      );
    if ( !(*hDevNotify) ) {
      DWORD Err = GetLastError();
      PrintOut("RegisterDeviceNotification failed, errcode:%08X"NL,Err);
      return FALSE;
    }

    return TRUE;
}


BOOL CUSBIOAPPDlg::OnDeviceChange( UINT nEventType, DWORD dwData )
{
  DEV_BROADCAST_DEVICEINTERFACE *data=(DEV_BROADCAST_DEVICEINTERFACE*)dwData;

  PrintOut("OnDeviceChange message: %08X (%s)"NL,nEventType,DeviceChangeMsgStr(nEventType));

  // check if data is valid
  if (data == NULL || data->dbcc_name == NULL || strlen(data->dbcc_name)==0) {
    return TRUE;
  }

  // convert interface name to CString
  CString Name(data->dbcc_name);
  POSITION pos;

  // there is some strange behavior in Win98
  // there are notifications with dbcc_name = "."
  // we ignore this
  if (Name.GetLength() < 5) {
    return TRUE;
  }

  switch (nEventType) {
  case DBT_DEVICEREMOVECOMPLETE:
    // a device with our interface has been removed or is stopped
    PrintOut("The USB device %s has been removed."NL,data->dbcc_name);
    // close the global  handle
    if ( g_UsbIo.GetDevicePathName() && (0==Name.CompareNoCase(g_UsbIo.GetDevicePathName())) ) {
      PrintOut("Closing driver interface"NL NL);
      g_UsbIo.Close();
    }
    // close all derived dialogs (pipe instances), associated with this device
    CPipeDialog *dlg;
    pos=g_PipeDialogList.GetHeadPosition();
    while (pos != NULL) {
      dlg = (CPipeDialog*)g_PipeDialogList.GetNext(pos); 
      if ( dlg->m_Pipe->GetDevicePathName() && (0==Name.CompareNoCase(dlg->m_Pipe->GetDevicePathName())) ) {
        // destroy this pipe dialog
        dlg->DestroyWindow();
      }
    } 
		// re-create device list
		m_DlgPgDevice.UpdateDeviceList();
    break;
  case DBT_DEVICEARRIVAL:
    // a device with our interface has been activated (started)
    PrintOut("A new USB device has been plugged in and is now available."NL); 
    PrintOut("Device path is: %s."NL NL,data->dbcc_name); 
		// re-create device list
		m_DlgPgDevice.UpdateDeviceList();
    break;
  case DBT_DEVICEQUERYREMOVE:
    // windows asked, if our device can be removed, we answer with TRUE (yes)
    PrintOut("MSG: DBT_DEVICEQUERYREMOVE -- Application returned success."NL);
    break;
  case DBT_DEVICEREMOVEPENDING:
    // device remove is pending
    PrintOut("MSG: DBT_DEVICEREMOVEPENDING."NL);
    break;
  default:
    break;
  } 

  return TRUE;
}



// update enable/disable state of controls
void CUSBIOAPPDlg::UpdateStateOfControls()
{
  m_DlgPgDevice.UpdateStateOfControls();
  m_DlgPgDesc.UpdateStateOfControls();
  m_DlgPgConfig.UpdateStateOfControls();
  m_DlgPgInterface.UpdateStateOfControls();
  m_DlgPgPipes.UpdateStateOfControls();
  m_DlgPgDevreq.UpdateStateOfControls();
  m_DlgPgFeature.UpdateStateOfControls();
  m_DlgPgOther.UpdateStateOfControls();
}




BOOL CUSBIOAPPDlg::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
{
  UINT strID = 0;

  TOOLTIPTEXT* ttt = (TOOLTIPTEXT *)ttt1;
  
  if ( ttt->hdr.code==TTN_NEEDTEXT ) {
 
    UINT nID = ttt->hdr.idFrom;
    if ( ttt->uFlags & TTF_IDISHWND ) {
      // idFrom is actually the HWND of the child
      nID = ::GetDlgCtrlID((HWND)nID);
    }

    if( nID!=0 ) {
      // get string resource
      switch ( nID ) {

      case IDC_BUTTON_OUTPUT_WINDOW:
        strID = IDS_BUTTON_OUTPUT_WINDOW;
        break;
      case IDC_BUTTON_CLEAR_OUTPUT_WINDOW:
        strID = IDS_BUTTON_CLEAR_OUTPUT_WINDOW;
        break;
      case IDOK:
        strID = IDS_IDOK;
        break;

      default:
        break;
      } //switch

      // return ID of string resource
      if ( strID!=0 ) {
        ttt->hinst = AfxGetResourceHandle();
        ttt->lpszText = MAKEINTRESOURCE(strID);
        *pResult = 0;
        return TRUE;
      }
    }
    
  }

  return FALSE;
  
} // OnToolTipNeedText



//
// helper functions
//

//lint -save -e773
#define _ENUMSTR(e) \
    (x==(e)) ? #e
//lint -restore

static
const char*
DeviceChangeMsgStr(UINT x)
{
  return (
    _ENUMSTR(DBT_DEVICEARRIVAL) :
    _ENUMSTR(DBT_DEVICEQUERYREMOVE) :
    _ENUMSTR(DBT_DEVICEQUERYREMOVEFAILED) :
    _ENUMSTR(DBT_DEVICEREMOVEPENDING) :
    _ENUMSTR(DBT_DEVICEREMOVECOMPLETE) :
    _ENUMSTR(DBT_DEVICETYPESPECIFIC) :
    _ENUMSTR(DBT_CUSTOMEVENT) :
    _ENUMSTR(DBT_USERDEFINED) :
    _ENUMSTR(DBT_DEVNODES_CHANGED) :
    "unknown"
  );
}



