// DlgPgInterface.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgInterface.h"
#include "DDX_ex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgInterface dialog


CDlgPgInterface::CDlgPgInterface(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgInterface::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgInterface)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

  // defaults
  m_Interface = 0;
  m_AlternateSetting = 0;
  m_MaxTransferSize = 65536;

}


void CDlgPgInterface::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgInterface)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP

  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format = _T("%d");

  DDX_TextEx(pDX, IDC_EDIT_IFNB, format, m_Interface, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ASNB, format, m_AlternateSetting, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_MAXTR, format, m_MaxTransferSize, nIDPrompt);

}


BEGIN_MESSAGE_MAP(CDlgPgInterface, CDialog)
  //{{AFX_MSG_MAP(CDlgPgInterface)
  ON_BN_CLICKED(IDC_BUTTON_SET_INTERFACE, OnButtonSetInterface)
  ON_BN_CLICKED(IDC_BUTTON_GET_INTERFACE, OnButtonGetInterface)
  //}}AFX_MSG_MAP
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgInterface message handlers

void CDlgPgInterface::OnButtonSetInterface() 
{
  DWORD err;
  USBIO_INTERFACE_SETTING Setting;
  if ( UpdateData(TRUE) ) {
    // fill in data
    Setting.InterfaceIndex=(USHORT)m_Interface;
    Setting.AlternateSettingIndex=(USHORT)m_AlternateSetting;
    Setting.MaximumTransferSize=m_MaxTransferSize;
    // send the command to the driver 
    err=g_UsbIo.SetInterface(&Setting);
    if (err) {
      PrintError(err);
    } else {
      PrintOut("New Alternate Setting has been successfully set."NL);
    }
  }
}

void CDlgPgInterface::OnButtonGetInterface() 
{ 
  DWORD err;
  UCHAR AlternateSetting;
  if ( UpdateData(TRUE) ) {
    // send the command to the driver 
    err= g_UsbIo.GetInterface(AlternateSetting, (USHORT) m_Interface );
    if (err) {
      PrintError(err);
    } else {
      PrintOut("Current Alternate Setting for Interface %d is %d."NL, m_Interface, AlternateSetting);
    }
  }
}



const int* 
CDlgPgInterface::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_EDIT_IFNB, 
    IDC_EDIT_ASNB,
    IDC_EDIT_MAXTR,
    IDC_BUTTON_SET_INTERFACE,
    IDC_BUTTON_GET_INTERFACE, 
    -1 // end marker
  };

  return ControlIds;
}



BOOL CDlgPgInterface::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_EDIT_IFNB:
        strID = IDS_EDIT_IFNB1;
        break;
      case IDC_EDIT_ASNB:
        strID = IDS_EDIT_ASNB1;
        break;
      case IDC_EDIT_MAXTR:
        strID = IDS_EDIT_MAXTR;
        break;
      case IDC_BUTTON_SET_INTERFACE:
        strID = IDS_BUTTON_SET_INTERFACE;
        break;
      case IDC_BUTTON_GET_INTERFACE:
        strID = IDS_BUTTON_GET_INTERFACE;
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



BOOL CDlgPgInterface::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}
