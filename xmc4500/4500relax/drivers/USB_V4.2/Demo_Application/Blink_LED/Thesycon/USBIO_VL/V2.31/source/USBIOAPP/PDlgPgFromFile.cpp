// PDlgPgFromFile.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDialog.h"
#include "PDlgPgFromFile.h"
#include "UsbIoPipe.h"
#include "DDX_ex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgFromFile dialog


CPDlgPgFromFile::CPDlgPgFromFile(CWnd* pParent /*=NULL*/)
  : CDialogPage(CPDlgPgFromFile::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPDlgPgFromFile)
  //}}AFX_DATA_INIT

  m_OwningPipeDialog = NULL;

}


void CPDlgPgFromFile::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPDlgPgFromFile)
	DDX_Control(pDX, IDC_BUTTON_STOP_WRITINGFROMFILE, m_ButtonStop);
	DDX_Control(pDX, IDC_BUTTON_START_WRITINGFROMFILE, m_ButtonStart);
	//}}AFX_DATA_MAP
  UINT nIDPrompt = IDS_STRING_INVALID_NUM;
  LPCTSTR format = _T("%d");

  DDX_TextEx(pDX, IDC_EDIT_SAMPLE_RATE,   format, m_OwningPipeDialog->m_SampleRate, nIDPrompt);
  DDX_TextEx(pDX, IDC_EDIT_SAMPLE_SIZE,   format, m_OwningPipeDialog->m_SampleSize, nIDPrompt);
  DDX_Check(pDX, IDC_REWIND, m_OwningPipeDialog->m_AutoRepeat);
  DDX_Text(pDX, IDC_EDIT_SRC_FILE, m_OwningPipeDialog->m_FileName);
}


BEGIN_MESSAGE_MAP(CPDlgPgFromFile, CDialog)
  //{{AFX_MSG_MAP(CPDlgPgFromFile)
  ON_BN_CLICKED(IDC_BUTTON_SRC_FILE_BROWSE, OnButtonSrcFileBrowse)
  ON_BN_CLICKED(IDC_BUTTON_START_WRITINGFROMFILE, OnButtonStartWritingFromFile)
  ON_BN_CLICKED(IDC_BUTTON_STOP_WRITINGFROMFILE, OnButtonStopWritingFromFile)
  ON_BN_CLICKED(IDC_BUTTON_SEND_ZERO_PACKET, OnButtonSendZeroPacket)
  //}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgFromFile message handlers

void CPDlgPgFromFile::OnButtonSrcFileBrowse() 
{
  // TODO: Add your control notification handler code here

  UpdateData(TRUE);

  CFileDialog FileDlg(
     TRUE,    //BOOL bOpenFileDialog,
     NULL,    //LPCTSTR lpszDefExt = NULL,
     NULL,  //LPCTSTR lpszFileName = NULL,
              //DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
     OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST |
     OFN_NOTESTFILECREATE |
     OFN_HIDEREADONLY |
     OFN_OVERWRITEPROMPT |
     OFN_NODEREFERENCELINKS,
     NULL,    //LPCTSTR lpszFilter = NULL,
     this     //CWnd* pParentWnd = NULL
     );

  if ( FileDlg.DoModal() == IDOK ) {
    m_OwningPipeDialog->m_FileName = FileDlg.GetPathName();
    UpdateData(FALSE);
  }
}


void CPDlgPgFromFile::OnButtonStartWritingFromFile() 
{
  if ( m_OwningPipeDialog->OnStart() ) {
    m_ButtonStart.EnableWindow(FALSE);
		// enable statistics display
		m_OwningPipeDialog->StartStatisticsTimer();
  }
}

void CPDlgPgFromFile::OnButtonStopWritingFromFile() 
{
  m_OwningPipeDialog->OnStop();
	// disable statistics display
	m_OwningPipeDialog->StopStatisticsTimer();
	// update display to reflect current counter values
	m_OwningPipeDialog->UpdatePipeStatistics();
}



void CPDlgPgFromFile::OnButtonSendZeroPacket() 
{
  DWORD Err;
  char buf[8];
  DWORD ByteCount=0;

  Err = m_OwningPipeDialog->m_Pipe->WriteSync(buf,ByteCount,500);
  PrintError(Err);
}



BOOL CPDlgPgFromFile::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CPDlgPgFromFile::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_EDIT_SRC_FILE:
        strID = IDS_EDIT_SRC_FILE;
        break;
      case IDC_BUTTON_SRC_FILE_BROWSE:
        strID = IDS_BUTTON_SRC_FILE_BROWSE;
        break;
      case IDC_BUTTON_START_WRITINGFROMFILE:
        strID = IDS_BUTTON_START_WRITINGFROMFILE;
        break;
      case IDC_BUTTON_STOP_WRITINGFROMFILE:
        strID = IDS_BUTTON_STOP_WRITINGFROMFILE;
        break;
      case IDC_REWIND:
        strID = IDS_REWIND;
        break;
      case IDC_BUTTON_SEND_ZERO_PACKET:
        strID = IDS_BUTTON_SEND_ZERO_PACKET;
        break;
      case IDC_EDIT_SAMPLE_RATE:
        strID = IDS_EDIT_SAMPLE_RATE;
        break;
      case IDC_EDIT_SAMPLE_SIZE:
        strID = IDS_EDIT_SAMPLE_SIZE;
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

