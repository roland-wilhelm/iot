// DlgPgDevreq.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgDevreq.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgDevreq dialog


CDlgPgDevreq::CDlgPgDevreq(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgDevreq::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgDevreq)
  m_ShortOk = TRUE;
  //}}AFX_DATA_INIT


  m_bRequest = 0;
  m_wValue = 0x0000;
  m_wIndex = 0x00;

  m_BufferLength = 8;

  // init buffer
  m_Buffer.Add(0x00);
  m_Buffer.Add(0x00);
  m_Buffer.Add(0x00);
  m_Buffer.Add(0x00);

}




BOOL CDlgPgDevreq::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // TODO: Add extra initialization here
  
  // init combo boxes
  m_ComboDirection.Init(g_DirectionTab);
  m_ComboType.Init(g_RequestTypeTab);
  m_ComboRecipient.Init(g_RecipientTab);


  // enable tool tips for child controls
  EnableToolTips(TRUE);


  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


// this handler is called with:
//   TRUE  when the dialog page is selected
//   FALSE when the dialog page is deselected
void CDlgPgDevreq::OnSelectionChange(BOOL bSelected)
{
	if ( bSelected ) {
	  if ( m_ComboDirection.IsWindowEnabled() ) {
			UpdateEditState();
		}
	}
}



void CDlgPgDevreq::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgDevreq)
	DDX_Control(pDX, IDC_CHECK_SHORT_OK, m_ButtonShortOK);
  DDX_Control(pDX, IDC_EDIT_BUFFER_LENGTH, m_EditBufferLength);
  DDX_Control(pDX, IDC_EDIT_BUFFER, m_EditBuffer);
  DDX_Control(pDX, IDC_COMBO_TYPE, m_ComboType);
  DDX_Control(pDX, IDC_COMBO_RECIPIENT, m_ComboRecipient);
  DDX_Control(pDX, IDC_COMBO_DIRECTION, m_ComboDirection);
  DDX_Check(pDX, IDC_CHECK_SHORT_OK, m_ShortOk);
	//}}AFX_DATA_MAP


  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format;

  format = _T("0x%02X");
  DDX_TextEx(pDX, IDC_EDIT_REQUEST, format, m_bRequest, nIDPrompt);

  format = _T("0x%04X");
  DDX_TextEx(pDX, IDC_EDIT_VALUE, format, m_wValue, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_INDEX, format, m_wIndex, nIDPrompt);

  format = _T("%d");
  DDX_TextEx(pDX, IDC_EDIT_BUFFER_LENGTH, format, m_BufferLength, nIDPrompt);

  format = _T("0x%02X ");
  nIDPrompt = IDS_STRING_INVALID_BUFFER;
  DDX_TextEx(pDX, IDC_EDIT_BUFFER, format, m_Buffer, nIDPrompt);

}


BEGIN_MESSAGE_MAP(CDlgPgDevreq, CDialog)
  //{{AFX_MSG_MAP(CDlgPgDevreq)
  ON_CBN_SELCHANGE(IDC_COMBO_DIRECTION, OnSelchangeComboDirection)
  ON_BN_CLICKED(IDC_BUTTON_SEND_REQUEST, OnButtonSendRequest)
  //}}AFX_MSG_MAP
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgPgDevreq message handlers


void CDlgPgDevreq::UpdateEditState()
{
  DIRECTION dir = (DIRECTION)m_ComboDirection.GetCurItemData();

  switch ( dir ) {
  case HostToDevice:
    m_EditBuffer.EnableWindow(TRUE);
    m_EditBufferLength.EnableWindow(FALSE);
    m_ButtonShortOK.EnableWindow(FALSE);
    break;
  case DeviceToHost:
    m_EditBuffer.EnableWindow(FALSE);
    m_EditBufferLength.EnableWindow(TRUE);
    m_ButtonShortOK.EnableWindow(TRUE);
    break;
  default:
    ASSERT(0);
    break;
  }
}


void CDlgPgDevreq::OnSelchangeComboDirection() 
{
  // TODO: Add your control notification handler code here
  UpdateEditState();
}


void CDlgPgDevreq::OnButtonSendRequest() 
{
  DWORD err;
  DWORD ByteCount;
  DIRECTION dir = (DIRECTION)m_ComboDirection.GetCurItemData();
  DWORD Type = m_ComboType.GetCurItemData();
  DWORD Recipient = m_ComboRecipient.GetCurItemData();
  USBIO_CLASS_OR_VENDOR_REQUEST Request;
  void *Buffer = NULL;
  BYTE *buf = NULL;

  if ( UpdateData(TRUE) ) {

    ZeroMemory(&Request,sizeof(Request));

    // fill in the data
    Request.Type=(USBIO_REQUEST_TYPE)Type;
    Request.Recipient=(USBIO_REQUEST_RECIPIENT)Recipient;
    // this field is in the test application always 0
    Request.RequestTypeReservedBits=0;
    Request.Request=m_bRequest;
    Request.Value=m_wValue;
    Request.Index=m_wIndex;
    if ( m_ShortOk ) Request.Flags|=USBIO_SHORT_TRANSFER_OK;

    switch ( dir ) {
    case HostToDevice:
      // write
      ByteCount=m_Buffer.GetSize();
      buf=m_Buffer.GetData();
      err=g_UsbIo.ClassOrVendorOutRequest(buf, ByteCount, &Request);
      break;
    case DeviceToHost:
      // read
      ByteCount=m_BufferLength;
      if ( ByteCount ) {
        Buffer=new char[ByteCount];
      }
      err=g_UsbIo.ClassOrVendorInRequest(Buffer, ByteCount, &Request);
      break;
    default:
      ASSERT(0);
      return;
    }   

    if (err) {
      // print error message
      PrintError(err, E_FATAL);
    } else {
      PrintOut("Class or Vendor request was successful."NL);
      if ( Buffer ) {
        DumpHex(Buffer, ByteCount);
      }
    }

    if ( Buffer ) delete [] Buffer;

  }

}


const int* 
CDlgPgDevreq::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_COMBO_DIRECTION,
    IDC_COMBO_TYPE,
    IDC_COMBO_RECIPIENT,
    IDC_EDIT_REQUEST,
    IDC_EDIT_VALUE,
    IDC_EDIT_INDEX,
    IDC_EDIT_BUFFER,
    IDC_EDIT_BUFFER_LENGTH,
    IDC_CHECK_SHORT_OK,
    IDC_BUTTON_SEND_REQUEST,
    -1 // end marker
  };

  return ControlIds;
}


BOOL CDlgPgDevreq::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_COMBO_DIRECTION:
        strID = IDS_COMBO_DIRECTION;
        break;
      case IDC_COMBO_TYPE:
        strID = IDS_COMBO_TYPE;
        break;
      case IDC_COMBO_RECIPIENT:
        strID = IDS_COMBO_RECIPIENT;
        break;
      case IDC_EDIT_REQUEST:
        strID = IDS_EDIT_REQUEST;
        break;
      case IDC_EDIT_VALUE:
        strID = IDS_EDIT_VALUE;
        break;
      case IDC_EDIT_INDEX:
        strID = IDS_EDIT_INDEX;
        break;
      case IDC_CHECK_SHORT_OK:
        strID = IDS_CHECK_SHORT_OK;
        break;
      case IDC_EDIT_BUFFER:
        strID = IDS_EDIT_BUFFER;
        break;
      case IDC_EDIT_BUFFER_LENGTH:
        strID = IDS_EDIT_BUFFER_LENGTH;
        break;
      case IDC_BUTTON_SEND_REQUEST:
        strID = IDS_BUTTON_SEND_REQUEST;
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

