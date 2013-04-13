// DlgPgDesc.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgDesc.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgDesc dialog


CDlgPgDesc::CDlgPgDesc(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgDesc::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgDesc)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  m_ConfigDescIndex = 0;
  m_StringDescIndex = 1;
  m_StringDescLangID = 0;
	m_AnyDescType = 0x21;
	m_AnyDescIndex = 0;
	m_AnyDescLength = 256;
}


void CDlgPgDesc::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgDesc)
    // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP


  UINT nIDPrompt = IDS_STRING_INVALID_NUM;

  LPCTSTR format = _T("%d");
  DDX_TextEx(pDX, IDC_EDIT_CONFIG_DESC, format, m_ConfigDescIndex, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_STRING_DESC, format, m_StringDescIndex, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ANY_DESC_INDEX, format, m_AnyDescIndex, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ANY_DESC_LENGTH, format, m_AnyDescLength, nIDPrompt);

	format = _T("0x%02X");
  DDX_TextEx(pDX, IDC_EDIT_ANY_DESC_TYPE, format, m_AnyDescType, nIDPrompt);

  format = _T("0x%04X");
  DDX_TextEx(pDX, IDC_EDIT_STRING_DESC_LID, format, m_StringDescLangID, nIDPrompt);

}


BEGIN_MESSAGE_MAP(CDlgPgDesc, CDialog)
  //{{AFX_MSG_MAP(CDlgPgDesc)
  ON_BN_CLICKED(IDC_BUTTON_DEVICE_DESC, OnButtonDeviceDesc)
  ON_BN_CLICKED(IDC_BUTTON_STRING_DESC, OnButtonStringDesc)
  ON_BN_CLICKED(IDC_BUTTON_CONFIG_DESC, OnButtonConfigDesc)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_QUALIFIER_DESC, OnButtonDeviceQualifierDesc)
	ON_BN_CLICKED(IDC_BUTTON_OTHER_SPEED_CONFIG_DESC, OnButtonOtherSpeedConfigDesc)
	ON_BN_CLICKED(IDC_BUTTON_ANY_DESC, OnButtonAnyDesc)
	//}}AFX_MSG_MAP
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgDesc message handlers

void CDlgPgDesc::OnButtonDeviceDesc() 
{
  // TODO: Add your control notification handler code here
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoGetDeviceDesc();    
  }
}

void CDlgPgDesc::OnButtonStringDesc() 
{
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoGetStringDesc();    
  }
}

void CDlgPgDesc::OnButtonConfigDesc() 
{
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoGetConfigDesc();    
  }
}

void CDlgPgDesc::OnButtonDeviceQualifierDesc() 
{
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoGetDeviceQualifierDesc();    
  }
}

void CDlgPgDesc::OnButtonOtherSpeedConfigDesc() 
{
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoGetOtherSpeedConfigDesc();    
  }
}

void CDlgPgDesc::OnButtonAnyDesc()
{
  // update member variables
  if ( UpdateData(TRUE) ) {
    DoGetAnyDesc();    
  }
}


void CDlgPgDesc::DoGetDeviceDesc()
{
  USB_DEVICE_DESCRIPTOR Desc;
  DWORD err;

  // send command to driver
  err=g_UsbIo.GetDeviceDescriptor(&Desc);
  if (err) {
    // print error message
    PrintError(err, E_ERROR);
  } else {
    DumpDescriptor(&Desc, sizeof(USB_DEVICE_DESCRIPTOR));
  }
}

void CDlgPgDesc::DoGetDeviceQualifierDesc()
{
  char Buffer[MAX_DESCRIPTOR_BUFFER_SIZE];
  DWORD ByteCount = MAX_DESCRIPTOR_BUFFER_SIZE;
  DWORD err;

  // send command to driver
  err=g_UsbIo.GetDescriptor(
							Buffer, // void* Buffer,
							ByteCount, // DWORD& ByteCount,
							RecipientDevice, // USBIO_REQUEST_RECIPIENT Recipient,
							USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE //UCHAR DescriptorType,
							);
  if (err) {
    // print error message
    PrintError(err, E_ERROR);
  } else {
    DumpDescriptor(Buffer, ByteCount);
  }
}


void CDlgPgDesc::DoGetConfigDesc()
{
  char Buffer[MAX_DESCRIPTOR_BUFFER_SIZE];
  DWORD ByteCount = MAX_DESCRIPTOR_BUFFER_SIZE;
  UCHAR idx = (UCHAR) m_ConfigDescIndex;
  DWORD err;

  // send command to driver
  err=g_UsbIo.GetConfigurationDescriptor((USB_CONFIGURATION_DESCRIPTOR*)Buffer,ByteCount,idx);
  if (err) {
    // print error message
    PrintError(err, E_ERROR);
  } else {
    DumpDescriptor(Buffer, ByteCount);
  }
}


void CDlgPgDesc::DoGetOtherSpeedConfigDesc()
{
  char Buffer[MAX_DESCRIPTOR_BUFFER_SIZE];
  DWORD ByteCount = MAX_DESCRIPTOR_BUFFER_SIZE;
  UCHAR idx = (UCHAR) m_ConfigDescIndex;
  DWORD err;

  // send command to driver
  err=g_UsbIo.GetDescriptor(
							Buffer, // void* Buffer,
							ByteCount, // DWORD& ByteCount,
							RecipientDevice, // USBIO_REQUEST_RECIPIENT Recipient,
							USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE, //UCHAR DescriptorType,
					    idx							//UCHAR DescriptorIndex =0,
							);
  if (err) {
    // print error message
    PrintError(err, E_ERROR);
  } else {
    DumpDescriptor(Buffer, ByteCount);
  }
}


void CDlgPgDesc::DoGetStringDesc()
{
  char Buffer[MAX_DESCRIPTOR_BUFFER_SIZE];
  DWORD ByteCount = MAX_DESCRIPTOR_BUFFER_SIZE;
  UCHAR idx = (UCHAR) m_StringDescIndex;
  USHORT lid = (USHORT) m_StringDescLangID; 
  DWORD err;
  USB_STRING_DESCRIPTOR *StrDesc;

  // send command to driver
  err=g_UsbIo.GetStringDescriptor((USB_STRING_DESCRIPTOR*)Buffer,ByteCount,idx,lid);
  if (err) {
    // print error message
    PrintError(err, E_ERROR);
  } else {
    if (idx == 0) {
      PrintOut("String Descriptor Language ID's"NL);
      DumpHex(Buffer, ByteCount);
      if (ByteCount >= 4) {
        StrDesc = (USB_STRING_DESCRIPTOR*)Buffer;
        m_StringDescLangID = StrDesc->bString[0];
        UpdateData(FALSE);
      }
    } else {
      DumpDescriptor(Buffer, ByteCount);
    }
  }
}


void CDlgPgDesc::DoGetAnyDesc() 
{
  UCHAR idx = (UCHAR) m_AnyDescIndex;
  DWORD length = m_AnyDescLength & 0xFFFF;
  char *Buffer = new char[length];
  DWORD err;

  // send command to driver
  err=g_UsbIo.GetDescriptor(Buffer,length,RecipientDevice,(unsigned char)m_AnyDescType,idx);
  if (err) {
    // print error message
    PrintError(err, E_ERROR);
  } else {
    DumpHex(Buffer, length);
  }

	delete[] Buffer;
}



BOOL CDlgPgDesc::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


const int* 
CDlgPgDesc::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_BUTTON_DEVICE_DESC,
    IDC_BUTTON_CONFIG_DESC,
    IDC_BUTTON_STRING_DESC,
    IDC_EDIT_CONFIG_DESC,
    IDC_EDIT_STRING_DESC,
    IDC_EDIT_STRING_DESC_LID,
		IDC_BUTTON_DEVICE_QUALIFIER_DESC,
		IDC_BUTTON_OTHER_SPEED_CONFIG_DESC,
		IDC_EDIT_ANY_DESC_TYPE,
		IDC_EDIT_ANY_DESC_INDEX,
		IDC_EDIT_ANY_DESC_LENGTH,
		IDC_BUTTON_ANY_DESC,
    -1 // end marker
  };

  return ControlIds;
}



BOOL CDlgPgDesc::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_BUTTON_DEVICE_DESC:
        strID = IDS_BUTTON_DEVICE_DESC;
        break;
      case IDC_BUTTON_DEVICE_QUALIFIER_DESC:
        strID = IDS_BUTTON_DEVICE_QUALIFIER_DESC;
        break;

      case IDC_EDIT_CONFIG_DESC:
        strID = IDS_EDIT_CONFIG_DESC;
        break;
      case IDC_BUTTON_CONFIG_DESC:
        strID = IDS_BUTTON_CONFIG_DESC;
        break;
      case IDC_BUTTON_OTHER_SPEED_CONFIG_DESC:
        strID = IDS_BUTTON_OTHER_SPEED_CONFIG_DESC;
        break;

      case IDC_EDIT_STRING_DESC:
        strID = IDS_EDIT_STRING_DESC;
        break;
      case IDC_EDIT_STRING_DESC_LID:
        strID = IDS_EDIT_STRING_DESC_LID;
        break;
      case IDC_BUTTON_STRING_DESC:
        strID = IDS_BUTTON_STRING_DESC;
        break;

			case IDC_EDIT_ANY_DESC_TYPE:
        strID = IDS_EDIT_ANY_DESC_TYPE;
        break;
			case IDC_EDIT_ANY_DESC_INDEX:
        strID = IDS_EDIT_ANY_DESC_INDEX;
        break;
			case IDC_EDIT_ANY_DESC_LENGTH:
        strID = IDS_EDIT_ANY_DESC_LENGTH;
        break;
			case IDC_BUTTON_ANY_DESC:
        strID = IDS_BUTTON_ANY_DESC;
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





