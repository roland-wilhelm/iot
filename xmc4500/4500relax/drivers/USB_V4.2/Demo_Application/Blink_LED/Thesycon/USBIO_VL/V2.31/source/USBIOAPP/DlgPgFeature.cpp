// DlgPgFeature.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgFeature.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgFeature dialog


CDlgPgFeature::CDlgPgFeature(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgFeature::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgFeature)
  m_FeatureSelector = 0;
  m_Index = 0;
  //}}AFX_DATA_INIT
}

BOOL CDlgPgFeature::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  m_ComboRecipient.Init(g_RecipientTab);
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPgFeature::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgFeature)
  DDX_Control(pDX, IDC_COMBO_RECIPIENT4, m_ComboRecipient);
  //}}AFX_DATA_MAP

  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format;

  format = _T("0x%04X");

  DDX_TextEx(pDX, IDC_EDIT_FEATURE_SELECTOR, format, m_FeatureSelector, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_INDEX4, format, m_Index, nIDPrompt);

}


BEGIN_MESSAGE_MAP(CDlgPgFeature, CDialog)
  //{{AFX_MSG_MAP(CDlgPgFeature)
  ON_BN_CLICKED(IDC_SET_FEATURE, OnSetFeature)
  ON_BN_CLICKED(IDC_CLEAR_FEATURE, OnClearFeature)
  //}}AFX_MSG_MAP
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgFeature message handlers

void CDlgPgFeature::OnSetFeature() 
{
  USBIO_REQUEST_RECIPIENT Recipient;
  DWORD err;

  if ( UpdateData(true) ) {
    Recipient=(USBIO_REQUEST_RECIPIENT)m_ComboRecipient.GetCurItemData();
    err = g_UsbIo.SetFeature(
            Recipient,
            (USHORT)m_FeatureSelector,
            (USHORT)m_Index
            );
    if (err != USBIO_ERR_SUCCESS) {
      PrintError(err);
    } else {
      PrintOut("Set Feature was successful."NL);
    } 
  } 
}

void CDlgPgFeature::OnClearFeature() 
{
  USBIO_REQUEST_RECIPIENT Recipient;
  DWORD err;

  if ( UpdateData(true) ) {
    Recipient=(USBIO_REQUEST_RECIPIENT)m_ComboRecipient.GetCurItemData();
    err = g_UsbIo.ClearFeature(
            Recipient,
            (USHORT)m_FeatureSelector,
            (USHORT)m_Index
            );
    if (err != USBIO_ERR_SUCCESS) {
      PrintError(err);
    } else {
      PrintOut("Clear Feature was successful."NL);
    } 
  } 
}



const int* 
CDlgPgFeature::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_COMBO_RECIPIENT4,
    IDC_EDIT_FEATURE_SELECTOR,
    IDC_EDIT_INDEX4,
    IDC_SET_FEATURE,
    IDC_CLEAR_FEATURE,
    -1 // end marker
  };

  return ControlIds;
}



BOOL CDlgPgFeature::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_COMBO_RECIPIENT4:
        strID = IDS_COMBO_RECIPIENT4;
        break;
      case IDC_EDIT_FEATURE_SELECTOR:
        strID = IDS_EDIT_FEATURE_SELECTOR;
        break;
      case IDC_EDIT_INDEX4:
        strID = IDS_EDIT_INDEX4;
        break;
      case IDC_SET_FEATURE:
        strID = IDS_SET_FEATURE;
        break;
      case IDC_CLEAR_FEATURE:
        strID = IDS_CLEAR_FEATURE;
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



