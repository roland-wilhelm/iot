// PDlgPgBuffer.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDialog.h"
#include "PDlgPgBuffer.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgBuffer dialog


CPDlgPgBuffer::CPDlgPgBuffer(CWnd* pParent /*=NULL*/)
  : CDialogPage(CPDlgPgBuffer::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPDlgPgBuffer)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT

  m_OwningPipeDialog = NULL;
}


void CPDlgPgBuffer::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPDlgPgBuffer)
  DDX_Control(pDX, IDC_EDIT_ISO_PACKET_COUNT, m_EditIsoPacketCount);
  //}}AFX_DATA_MAP


  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format = _T("%d");

  DDX_TextEx(pDX, IDC_EDIT_BUF_SIZE,    format, m_OwningPipeDialog->m_SizeOfBuffer, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_BUF_COUNT,   format, m_OwningPipeDialog->m_NumberOfBuffers, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_MAX_ERRCOUNT,format, m_OwningPipeDialog->m_MaxErrorCount, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_ISO_PACKET_COUNT,format, m_OwningPipeDialog->m_NumberOfIsoPackets, nIDPrompt);

}


BEGIN_MESSAGE_MAP(CPDlgPgBuffer, CDialog)
  //{{AFX_MSG_MAP(CPDlgPgBuffer)
	ON_BN_CLICKED(IDC_BUTTON_BUFFER_SET_DEFAULTS, OnButtonBufferSetDefaults)
	//}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgBuffer message handlers



BOOL CPDlgPgBuffer::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}



void CPDlgPgBuffer::OnButtonBufferSetDefaults() 
{
	if ( m_OwningPipeDialog!=NULL ) {
		m_OwningPipeDialog->SetBufferDefaults();
		UpdateData(FALSE);
	}
}



BOOL CPDlgPgBuffer::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_EDIT_BUF_SIZE:
        strID = IDS_EDIT_BUF_SIZE;
        break;
      case IDC_EDIT_BUF_COUNT:
        strID = IDS_EDIT_BUF_COUNT;
        break;
      case IDC_EDIT_MAX_ERRCOUNT:
        strID = IDS_EDIT_MAX_ERRCOUNT;
        break;
      case IDC_EDIT_ISO_PACKET_COUNT:
        strID = IDS_EDIT_ISO_PACKET_COUNT;
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

