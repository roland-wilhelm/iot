// PDlgPgPipeControl.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PDlgPgPipeControl.h"
#include "PipeDialog.h"
#include "UsbIoPipe.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgPipeControl dialog


CPDlgPgPipeControl::CPDlgPgPipeControl(CWnd* pParent /*=NULL*/)
  : CDialogPage(CPDlgPgPipeControl::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPDlgPgPipeControl)
  m_ShortOk = TRUE;
  //}}AFX_DATA_INIT

  m_OwningPipeDialog = NULL;
  m_BufferLength = 0;
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);
  m_PipeSetup.Add(0x00);

  m_Buffer.Add(0x00);
  m_Buffer.Add(0x00);

}

BOOL CPDlgPgPipeControl::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  m_ComboDirection.Init(g_DirectionTab);

  UpdateEditState();

  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CPDlgPgPipeControl::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPDlgPgPipeControl)
  DDX_Control(pDX, IDC_PIPE_EDIT_BUFFER_LENGTH, m_EditBufferLength);
  DDX_Control(pDX, IDC_PIPE_EDIT_BUFFER, m_EditBuffer);
  DDX_Control(pDX, IDC_PIPE_COMBO_DIRECTION, m_ComboDirection);
  DDX_Check(pDX, IDC_SHORT_TRANSFER_OK, m_ShortOk);
  //}}AFX_DATA_MAP
  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format;

  format = _T("%d");
  DDX_TextEx(pDX, IDC_PIPE_EDIT_BUFFER_LENGTH, format, m_BufferLength, nIDPrompt);

  format = _T("0x%02X ");
  nIDPrompt = IDS_STRING_INVALID_BUFFER;
  DDX_TextEx(pDX, IDC_PIPE_SETUP, format, m_PipeSetup, nIDPrompt);
  DDX_TextEx(pDX, IDC_PIPE_EDIT_BUFFER, format, m_Buffer, nIDPrompt);
}


BEGIN_MESSAGE_MAP(CPDlgPgPipeControl, CDialog)
  //{{AFX_MSG_MAP(CPDlgPgPipeControl)
  ON_BN_CLICKED(IDC_BUTTON_PIPE_SEND_REQUEST, OnButtonPipeSendRequest)
  ON_CBN_SELCHANGE(IDC_PIPE_COMBO_DIRECTION, OnSelchangePipeComboDirection)
  //}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgPipeControl message handlers

void CPDlgPgPipeControl::OnButtonPipeSendRequest() 
{
  DWORD err;
  DWORD ByteCount;
  USBIO_PIPE_CONTROL_TRANSFER Request;
  DIRECTION dir = (DIRECTION)m_ComboDirection.GetCurItemData();
  void *Buffer = NULL;
  BYTE *buf = NULL;
  BYTE SetupBuf[8];
  int i,m;

  if (UpdateData(true)) {

    ZeroMemory(&Request,sizeof(Request));
    ZeroMemory(SetupBuf,sizeof(SetupBuf));

    if (m_ShortOk) Request.Flags|=USBIO_SHORT_TRANSFER_OK;
    m=__min(8,m_PipeSetup.GetSize());
    for (i=0;i<m;i++) SetupBuf[i]=m_PipeSetup.GetAt(i);

    switch ( dir ) {
    case HostToDevice:
      // write
      ByteCount=m_Buffer.GetSize();
      buf=m_Buffer.GetData();
      err=m_OwningPipeDialog->m_Pipe->PipeControlTransferOut(buf, ByteCount, &Request);
      break;
    case DeviceToHost:
      // read
      ByteCount=m_BufferLength;
      if ( ByteCount ) {
        Buffer=new char[ByteCount];
        if ( !Buffer ) {
          err = USBIO_ERR_OUT_OF_MEMORY;
          break;
        }
      }
      err=m_OwningPipeDialog->m_Pipe->PipeControlTransferOut(Buffer, ByteCount, &Request);
      break;
    default:
      ASSERT(0);
      return;
    }   
    if (err) {
      // print error message
      PrintError(err, E_FATAL);
    } else {
      PrintOut("Pipe Control Request was successful."NL);
      if ( Buffer ) {
        DumpHex(Buffer, ByteCount);
      }
    }

    if ( Buffer ) delete [] Buffer;

  }
}


void CPDlgPgPipeControl::UpdateEditState()
{
  DIRECTION dir = (DIRECTION)m_ComboDirection.GetCurItemData();

  switch ( dir ) {
  case HostToDevice:
    m_EditBuffer.EnableWindow(TRUE);
    m_EditBufferLength.EnableWindow(FALSE);
    break;
  case DeviceToHost:
    m_EditBuffer.EnableWindow(FALSE);
    m_EditBufferLength.EnableWindow(TRUE);
    break;
  default:
    ASSERT(0);
    break;
  }
  
}


void CPDlgPgPipeControl::OnSelchangePipeComboDirection() 
{
  UpdateEditState();
}

BOOL CPDlgPgPipeControl::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_PIPE_COMBO_DIRECTION:
        strID = IDS_PIPE_COMBO_DIRECTION;
        break;
      case IDC_SHORT_TRANSFER_OK:
        strID = IDS_SHORT_TRANSFER_OK;
        break;
      case IDC_PIPE_SETUP:
        strID = IDS_PIPE_SETUP;
        break;
      case IDC_PIPE_EDIT_BUFFER:
        strID = IDS_PIPE_EDIT_BUFFER;
        break;
      case IDC_PIPE_EDIT_BUFFER_LENGTH:
        strID = IDS_PIPE_EDIT_BUFFER_LENGTH;
        break;
      case IDC_BUTTON_PIPE_SEND_REQUEST:
        strID = IDS_BUTTON_PIPE_SEND_REQUEST;
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

