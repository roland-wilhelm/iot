// DlgPgPipes.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgPipes.h"
#include "DDX_ex.h"

#include "PipeDlgToWin.h"
#include "PipeDlgToFile.h"
#include "PipeDlgFromFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgPipes dialog


CDlgPgPipes::CDlgPgPipes(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgPipes::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgPipes)
  //}}AFX_DATA_INIT

	m_EndpointAddr = -1;
}


BOOL CDlgPgPipes::OnInitDialog() 
{
  CDialog::OnInitDialog();

	m_DevNotConfig.ShowWindow(SW_HIDE);
 
  // enable tool tips for child controls
  EnableToolTips(TRUE);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


// this handler is called with:
//   TRUE  when the dialog page is selected
//   FALSE when the dialog page is deselected
void CDlgPgPipes::OnSelectionChange(BOOL bSelected)
{
	if ( bSelected ) {
		// default:
		m_EndpointAddr = -1;
		// disable all buttons
		m_ButtonPipeToWin.EnableWindow(FALSE);
		m_ButtonPipeToFile.EnableWindow(FALSE);
		m_ButtonFileToPipe.EnableWindow(FALSE);
		// update list box
		UpdateEndpointList();
		UpdateEndpointSelection();
	}
}


void CDlgPgPipes::UpdateEndpointList()
{
 	CString str;

	// clear endpoint list
	m_ListBoxEndpoints.ResetContent();
	m_DevNotConfig.ShowWindow(SW_SHOW);

  // get info on current configuration from driver
	USBIO_CONFIGURATION_INFO Info;
  DWORD err = g_UsbIo.GetConfigurationInfo(&Info);
  if ( err==USBIO_ERR_SUCCESS ) {
		// fill list box with active endpoints
		for ( DWORD i=0; i<Info.NbOfPipes; i++ ) {
			UCHAR ep = Info.PipeInfo[i].EndpointAddress;
			USBIO_PIPE_TYPE type = Info.PipeInfo[i].PipeType;
			str.Format("0x%02X  %s %s",
						ep,
						PipeTypeStr(type),
						EndpointDirectionStr(ep)
						);
			int index = m_ListBoxEndpoints.AddString(str);
			if ( index >= 0 ) {
				m_ListBoxEndpoints.SetItemData(index, ep);
			}
		}
		if ( Info.NbOfPipes > 0 ) {
			// there are active pipes, the device is configured
			m_DevNotConfig.ShowWindow(SW_HIDE);
			// select first endpoint				
			m_ListBoxEndpoints.SetCurSel(0);
		}
	}
}



void CDlgPgPipes::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgPipes)
	DDX_Control(pDX, IDC_BUTTON_OPEN_PIPE_TOWIN, m_ButtonPipeToWin);
	DDX_Control(pDX, IDC_BUTTON_OPEN_PIPE_TOFILE, m_ButtonPipeToFile);
	DDX_Control(pDX, IDC_BUTTON_OPEN_PIPE_FROMFILE, m_ButtonFileToPipe);
	DDX_Control(pDX, IDC_LIST_ENDPOINTS, m_ListBoxEndpoints);
	DDX_Control(pDX, IDC_STATIC_DEV_NOT_CONFIGURED, m_DevNotConfig);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgPgPipes, CDialog)
  //{{AFX_MSG_MAP(CDlgPgPipes)
  ON_BN_CLICKED(IDC_BUTTON_GET_PIPE_INFO, OnButtonGetPipeInfo)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PIPE_FROMFILE, OnButtonFileToPipe)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PIPE_TOFILE, OnButtonPipeToFile)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PIPE_TOWIN, OnButtonPipeToWin)
	ON_LBN_SELCHANGE(IDC_LIST_ENDPOINTS, OnSelchangeListEndpoints)
	//}}AFX_MSG_MAP
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgPipes message handlers

void CDlgPgPipes::OnButtonGetPipeInfo() 
{
  DWORD err;
  USBIO_CONFIGURATION_INFO Info;

  if ( UpdateData(TRUE) ) {
    // send the command to the driver 
    err= g_UsbIo.GetConfigurationInfo(&Info);
    if (err) {
      PrintError(err);
    } else {
      if ( Info.NbOfInterfaces==0 ) {
				// device is not configured
				PrintOut("The device is not configured."NL);
				PrintOut("Use the button Set Configuration on the Configuration page first."NL);
			} else {
				// display the information
				DumpConfigInfo(&Info);
			}
    }
  } 
}



void CDlgPgPipes::UpdateEndpointSelection()
{
	// no selection
	m_EndpointAddr = -1;
	// disable all buttons
	m_ButtonPipeToWin.EnableWindow(FALSE);
	m_ButtonPipeToFile.EnableWindow(FALSE);
	m_ButtonFileToPipe.EnableWindow(FALSE);
	
	int index = m_ListBoxEndpoints.GetCurSel();
	if ( index >= 0 ) {
		m_EndpointAddr = m_ListBoxEndpoints.GetItemData(index);
		if ( m_EndpointAddr & 0x80 ) {
			// IN endpoint
			m_ButtonPipeToWin.EnableWindow(TRUE);
			m_ButtonPipeToFile.EnableWindow(TRUE);
		} else {
			// OUT endpoint
			m_ButtonFileToPipe.EnableWindow(TRUE);
		}
	} else {
		// no selection
	}
}


void CDlgPgPipes::OnSelchangeListEndpoints() 
{
	UpdateEndpointSelection();
}



void CDlgPgPipes::OpenPipe(PURPOSE Purpose) 
{ 
  DWORD err;

  CWnd *ParentWin = GetDesktopWindow();
  CPipeDialog *dlg = NULL;
  
  switch ( Purpose ) {
  case PipeToWin:
    dlg = new CPipeDlgToWin(ParentWin);
    break;
  case PipeToFile:
    dlg = new CPipeDlgToFile(ParentWin);
    break;
  case FileToPipe:
    dlg = new CPipeDlgFromFile(ParentWin);
    break;
  default:
    break;
  }

	if ( dlg != NULL ) {
		// bind the pipe
		err = dlg->BindPipe(g_DeviceNumber,m_EndpointAddr);
		if ( err ) {
			// bind failed, destroy the window
			dlg->DestroyWindow();
			// display error
			PrintError(err,E_FATAL);
		} else {
			// add dialog to list       
			g_PipeDialogList.AddTail(dlg);
			// show the new dialog on screen
			dlg->ShowWindow(SW_SHOW);
		}
	}
}


void CDlgPgPipes::OnButtonFileToPipe() 
{
	OpenPipe(FileToPipe);
}

void CDlgPgPipes::OnButtonPipeToFile() 
{
	OpenPipe(PipeToFile);
}

void CDlgPgPipes::OnButtonPipeToWin() 
{
	OpenPipe(PipeToWin);
}



const int* 
CDlgPgPipes::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_BUTTON_GET_PIPE_INFO,
    IDC_LIST_ENDPOINTS,
    IDC_BUTTON_OPEN_PIPE_TOWIN,
    IDC_BUTTON_OPEN_PIPE_TOFILE,
    IDC_BUTTON_OPEN_PIPE_FROMFILE,
    -1 // end marker
  };

  return ControlIds;
}



BOOL CDlgPgPipes::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_BUTTON_GET_PIPE_INFO:
        strID = IDS_BUTTON_GET_PIPE_INFO;
        break;
      case IDC_BUTTON_OPEN_PIPE_TOWIN:
        strID = IDS_BUTTON_OPEN_PIPE_TOWIN;
        break;
      case IDC_BUTTON_OPEN_PIPE_TOFILE:
        strID = IDS_BUTTON_OPEN_PIPE_TOFILE;
        break;
      case IDC_BUTTON_OPEN_PIPE_FROMFILE:
        strID = IDS_BUTTON_OPEN_PIPE_FROMFILE;
        break;
      case IDC_LIST_ENDPOINTS:
        strID = IDS_LIST_ENDPOINTS;
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

