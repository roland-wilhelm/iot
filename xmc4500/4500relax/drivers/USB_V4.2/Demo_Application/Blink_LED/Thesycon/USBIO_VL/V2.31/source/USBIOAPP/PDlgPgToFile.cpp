// PDlgPgToFile.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDialog.h"
#include "PDlgPgToFile.h"
#include "UsbIoPipe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPDlgPgToFile dialog


CPDlgPgToFile::CPDlgPgToFile(CWnd* pParent /*=NULL*/)
  : CDialogPage(CPDlgPgToFile::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPDlgPgToFile)
  //}}AFX_DATA_INIT

  m_OwningPipeDialog = NULL;
}


BOOL CPDlgPgToFile::OnInitDialog() 
{
  CDialog::OnInitDialog();

  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CPDlgPgToFile::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPDlgPgToFile)
	DDX_Control(pDX, IDC_BUTTON_STOP_READINGTOFILE, m_ButtonStop);
	DDX_Control(pDX, IDC_BUTTON_START_READINGTOFILE, m_ButtonStart);
	//}}AFX_DATA_MAP

  DDX_Text(pDX, IDC_EDIT_DST_FILE, m_OwningPipeDialog->m_FileName);

}



BEGIN_MESSAGE_MAP(CPDlgPgToFile, CDialog)
  //{{AFX_MSG_MAP(CPDlgPgToFile)
  ON_BN_CLICKED(IDC_BUTTON_DST_FILE_BROWSE, OnButtonDstFileBrowse)
  ON_BN_CLICKED(IDC_BUTTON_START_READINGTOFILE, OnButtonStartReadingToFile)
  ON_BN_CLICKED(IDC_BUTTON_STOP_READINGTOFILE, OnButtonStopReadingToFile)
  //}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgToFile message handlers

void CPDlgPgToFile::OnButtonDstFileBrowse() 
{
  // TODO: Add your control notification handler code here

  UpdateData(TRUE);

  CFileDialog FileDlg(
     TRUE,    //BOOL bOpenFileDialog,
     NULL,    //LPCTSTR lpszDefExt = NULL,
     NULL,  //LPCTSTR lpszFileName = NULL,
              //DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
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


void CPDlgPgToFile::OnButtonStartReadingToFile() 
{
  if ( m_OwningPipeDialog->OnStart() ) {
    m_ButtonStart.EnableWindow(FALSE);
		// enable statistics display
		m_OwningPipeDialog->StartStatisticsTimer();
  }
}

void CPDlgPgToFile::OnButtonStopReadingToFile() 
{
  m_OwningPipeDialog->OnStop();
	// disable statistics display
	m_OwningPipeDialog->StopStatisticsTimer();
	// update display to reflect current counter values
	m_OwningPipeDialog->UpdatePipeStatistics();
}



BOOL CPDlgPgToFile::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_EDIT_DST_FILE:
        strID = IDS_EDIT_DST_FILE;
        break;
      case IDC_BUTTON_DST_FILE_BROWSE:
        strID = IDS_BUTTON_DST_FILE_BROWSE;
        break;
      case IDC_BUTTON_START_READINGTOFILE:
        strID = IDS_BUTTON_START_READINGTOFILE;
        break;
      case IDC_BUTTON_STOP_READINGTOFILE:
        strID = IDS_BUTTON_STOP_READINGTOFILE;
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

