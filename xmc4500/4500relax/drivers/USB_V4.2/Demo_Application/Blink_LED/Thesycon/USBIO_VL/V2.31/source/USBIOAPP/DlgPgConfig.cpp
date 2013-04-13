// DlgPgConfig.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgConfig.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CDlgPgConfig dialog


CDlgPgConfig::CDlgPgConfig(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgConfig::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgConfig)
  //}}AFX_DATA_INIT

  // init

  ZeroMemory(m_Ifc,sizeof(m_Ifc));
  m_Ifc[0].InUse = TRUE;
  for ( int i=0; i<NBOF_IFC; i++ ) {
    m_Ifc[i].MaxTransferSize = 65536;
    m_Ifc[i].Interface = i;
  }

  m_ConfigIndex = 0;

  m_Active = FALSE;

}


BOOL CDlgPgConfig::OnInitDialog() 
{
  CDialog::OnInitDialog();  
  UpdateEditState();
  m_Active = TRUE;
  // enable tool tips for child controls
  EnableToolTips(TRUE);

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}




void CDlgPgConfig::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgConfig)
  //}}AFX_DATA_MAP


  // check boxes
  DDX_Check(pDX, IDC_CHECK_IF_0, m_Ifc[0].InUse);
  DDX_Check(pDX, IDC_CHECK_IF_1, m_Ifc[1].InUse);
  DDX_Check(pDX, IDC_CHECK_IF_2, m_Ifc[2].InUse);
  DDX_Check(pDX, IDC_CHECK_IF_3, m_Ifc[3].InUse);


  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format = _T("%d");

  // interface number
  DDX_TextEx(pDX, IDC_EDIT_IFNB_0, format, m_Ifc[0].Interface, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_IFNB_1, format, m_Ifc[1].Interface, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_IFNB_2, format, m_Ifc[2].Interface, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_IFNB_3, format, m_Ifc[3].Interface, nIDPrompt);

  // alternate setting number
  //nIDPrompt = AFX_IDP_PARSE_UINT;
  //format = _T("%d");
  DDX_TextEx(pDX, IDC_EDIT_ASNB_0, format, m_Ifc[0].AlternateSetting, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ASNB_1, format, m_Ifc[1].AlternateSetting, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ASNB_2, format, m_Ifc[2].AlternateSetting, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ASNB_3, format, m_Ifc[3].AlternateSetting, nIDPrompt);

  // max transfer size 
  //nIDPrompt = AFX_IDP_PARSE_UINT;
  //format = _T("%d");
  DDX_TextEx(pDX, IDC_EDIT_MAXTR_0, format, m_Ifc[0].MaxTransferSize, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_MAXTR_1, format, m_Ifc[1].MaxTransferSize, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_MAXTR_2, format, m_Ifc[2].MaxTransferSize, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_MAXTR_3, format, m_Ifc[3].MaxTransferSize, nIDPrompt);

  
  // configuration index
  //nIDPrompt = AFX_IDP_PARSE_UINT;
  //format = _T("%d");
  DDX_TextEx(pDX, IDC_EDIT_CONFIG_INDEX, format, m_ConfigIndex, nIDPrompt);


} //DoDataExchange



BEGIN_MESSAGE_MAP(CDlgPgConfig, CDialog)
  //{{AFX_MSG_MAP(CDlgPgConfig)
  ON_BN_CLICKED(IDC_BUTTON_SET_CONFIGURATION, OnButtonSetConfiguration)
  ON_EN_KILLFOCUS(IDC_EDIT_CONFIG_INDEX, OnKillfocusEditConfigIndex)
  ON_BN_CLICKED(IDC_BUTTON_GET_CONFIGURATION, OnButtonGetConfiguration)
  ON_BN_CLICKED(IDC_BUTTON_UNCONFIGURE_DEVICE, OnButtonUnconfigureDevice)
	ON_BN_CLICKED(IDC_BUTTON_BANDWIDTH, OnButtonBandwidth)
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_CHECK_IF_0, OnCheckIf)
  ON_BN_CLICKED(IDC_CHECK_IF_1, OnCheckIf)
  ON_BN_CLICKED(IDC_CHECK_IF_2, OnCheckIf)
  ON_BN_CLICKED(IDC_CHECK_IF_3, OnCheckIf)
  ON_EN_KILLFOCUS(IDC_EDIT_IFNB_0, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_IFNB_1, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_IFNB_2, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_IFNB_3, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_ASNB_0, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_ASNB_1, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_ASNB_2, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_ASNB_3, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_MAXTR_0, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_MAXTR_1, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_MAXTR_2, OnKillfocusEditIf)
  ON_EN_KILLFOCUS(IDC_EDIT_MAXTR_3, OnKillfocusEditIf)
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgConfig message handlers

void CDlgPgConfig::OnButtonSetConfiguration() 
{
  // TODO: Add your control notification handler code here
  
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoSetConfiguration();   
  }

}


// called when any of the IF edit controls loses focus
void CDlgPgConfig::OnKillfocusEditIf() 
{
}


void CDlgPgConfig::OnKillfocusEditConfigIndex() 
{
}



// support functions

void CDlgPgConfig::UpdateEditState(UINT nIDCheckBox, UINT nIDEdit1, UINT nIDEdit2, UINT nIDEdit3) 
{
  BOOL enable;
  
  if ( ((CButton*)GetDlgItem(nIDCheckBox))->GetCheck()==0 ) {
    enable = FALSE;
  } else {
    enable = TRUE;
  }

  ((CWnd*)GetDlgItem(nIDEdit1))->EnableWindow(enable);
  ((CWnd*)GetDlgItem(nIDEdit2))->EnableWindow(enable);
  ((CWnd*)GetDlgItem(nIDEdit3))->EnableWindow(enable);
}


void CDlgPgConfig::UpdateEditState()
{
  UpdateEditState(IDC_CHECK_IF_0, IDC_EDIT_IFNB_0, IDC_EDIT_ASNB_0, IDC_EDIT_MAXTR_0);
  UpdateEditState(IDC_CHECK_IF_1, IDC_EDIT_IFNB_1, IDC_EDIT_ASNB_1, IDC_EDIT_MAXTR_1);
  UpdateEditState(IDC_CHECK_IF_2, IDC_EDIT_IFNB_2, IDC_EDIT_ASNB_2, IDC_EDIT_MAXTR_2);
  UpdateEditState(IDC_CHECK_IF_3, IDC_EDIT_IFNB_3, IDC_EDIT_ASNB_3, IDC_EDIT_MAXTR_3);
}


void CDlgPgConfig::OnCheckIf() 
{
  // TODO: Add your control notification handler code here
  UpdateEditState();
}




void CDlgPgConfig::DoSetConfiguration()
{
  USBIO_SET_CONFIGURATION SetConfig;
  USBIO_INTERFACE_SETTING *Setting;
  ULONG nb;
  DWORD err;

  // setup config struct
  ZeroMemory(&SetConfig,sizeof(SetConfig));
  SetConfig.ConfigurationIndex = (USHORT)m_ConfigIndex;
  nb = 0;
  for ( int i=0; i<NBOF_IFC; i++ ) {
    INTERFACE *ifc = &m_Ifc[i];
    if ( ifc->InUse ) {
      Setting = &SetConfig.InterfaceList[nb];
      Setting->InterfaceIndex = (USHORT)ifc->Interface;
      Setting->AlternateSettingIndex = (USHORT)ifc->AlternateSetting;
      Setting->MaximumTransferSize = ifc->MaxTransferSize;
      nb++;
    }
  }
  ASSERT(nb<=USBIO_MAX_INTERFACES);
  SetConfig.NbOfInterfaces = (USHORT)nb;

  // send command to driver
  err= g_UsbIo.SetConfiguration(&SetConfig);
  if (err) {
    PrintError(err);
  } else {
    PrintOut("The configuration has been successfully set."NL);
  }
}


void CDlgPgConfig::OnButtonGetConfiguration() 
{
  DWORD err;
  UCHAR ConfigurationValue;
  err= g_UsbIo.GetConfiguration(ConfigurationValue );
  if (err) {
    PrintError(err);
  } else {
    PrintOut("Current Configuration Value is %d."NL,ConfigurationValue);
    if ( ConfigurationValue==0 ) {
      PrintOut("  Device is not configured."NL);
    }
  }
  
}

void CDlgPgConfig::OnButtonUnconfigureDevice() 
{
  DWORD err;

  err= g_UsbIo.UnconfigureDevice();
  if (err) {
    PrintError(err);
  } else {
    PrintOut("Device is unconfigured."NL);
  }
  
}

void CDlgPgConfig::OnButtonBandwidth() 
{
  DWORD err;
	USBIO_BANDWIDTH_INFO BandwidthInfo;

  err= g_UsbIo.GetBandwidthInfo(&BandwidthInfo);
  if (err) {
    PrintError(err);
  } else {
    PrintOut( "Total Bandwidth   : %6d kbps"NL
							"Consumed Bandwidth: %6d kbps"NL,
							BandwidthInfo.TotalBandwidth,
							BandwidthInfo.ConsumedBandwidth);
  }	
}


const int* 
CDlgPgConfig::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_BUTTON_SET_CONFIGURATION,
    IDC_BUTTON_GET_CONFIGURATION,
    IDC_BUTTON_UNCONFIGURE_DEVICE,
		IDC_BUTTON_BANDWIDTH,
    IDC_EDIT_CONFIG_INDEX,
    IDC_CHECK_IF_0,
    IDC_CHECK_IF_1,
    IDC_CHECK_IF_2,
    IDC_CHECK_IF_3,
    IDC_EDIT_IFNB_0,
    IDC_EDIT_ASNB_0,
    IDC_EDIT_MAXTR_0,
    -1 // end marker
  };

  return ControlIds;
}




BOOL CDlgPgConfig::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_EDIT_CONFIG_INDEX:
        strID = IDS_EDIT_CONFIG_INDEX;
        break;
      case IDC_BUTTON_SET_CONFIGURATION:
        strID = IDS_BUTTON_SET_CONFIGURATION;
        break;
      case IDC_BUTTON_GET_CONFIGURATION:
        strID = IDS_BUTTON_GET_CONFIGURATION;
        break;
      case IDC_BUTTON_UNCONFIGURE_DEVICE:
        strID = IDS_BUTTON_UNCONFIGURE_DEVICE;
        break;
			case IDC_BUTTON_BANDWIDTH:
        strID = IDS_BUTTON_BANDWIDTH;
				break;
      case IDC_EDIT_IFNB_0:
      case IDC_EDIT_IFNB_1:
      case IDC_EDIT_IFNB_2:
      case IDC_EDIT_IFNB_3:
        strID = IDS_EDIT_IFNB;
        break;
      case IDC_EDIT_ASNB_0:
      case IDC_EDIT_ASNB_1:
      case IDC_EDIT_ASNB_2:
      case IDC_EDIT_ASNB_3:
        strID = IDS_EDIT_ASNB;
        break;
      case IDC_EDIT_MAXTR_0:
      case IDC_EDIT_MAXTR_1:
      case IDC_EDIT_MAXTR_2:
      case IDC_EDIT_MAXTR_3:
        strID = IDS_EDIT_MAXTR;
        break;
      case IDC_CHECK_IF_0:
      case IDC_CHECK_IF_1:
      case IDC_CHECK_IF_2:
      case IDC_CHECK_IF_3:
        strID = IDS_CHECK_IF;
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


