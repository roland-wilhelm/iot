// PDlgPgToWin.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDialog.h"
#include "PDlgPgToWin.h"
#include "UsbIoPipe.h"
#include "UsbIoThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgToWin dialog


CPDlgPgToWin::CPDlgPgToWin(CWnd* pParent /*=NULL*/)
  : CDialogPage(CPDlgPgToWin::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPDlgPgToWin)
  //}}AFX_DATA_INIT

  m_OwningPipeDialog = NULL;

}



void CPDlgPgToWin::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPDlgPgToWin)
	DDX_Control(pDX, IDC_BUTTON_STOP_READINGTOWIN, m_ButtonStop);
	DDX_Control(pDX, IDC_BUTTON_START_READINGTOWIN, m_ButtonStart);
	//}}AFX_DATA_MAP
  DDX_Check(pDX, IDC_CHECK_PRINT_OUT, m_OwningPipeDialog->m_EnablePrint);
}


BEGIN_MESSAGE_MAP(CPDlgPgToWin, CDialog)
  //{{AFX_MSG_MAP(CPDlgPgToWin)
  ON_BN_CLICKED(IDC_BUTTON_START_READINGTOWIN, OnButtonStartReading)
  ON_BN_CLICKED(IDC_BUTTON_STOP_READINGTOWIN, OnButtonStopReading)
  //}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgToWin message handlers

BOOL CPDlgPgToWin::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CPDlgPgToWin::OnButtonStartReading() 
{
  if ( m_OwningPipeDialog->OnStart() ) {
    m_ButtonStart.EnableWindow(FALSE);
		// enable statistics display
		m_OwningPipeDialog->StartStatisticsTimer();
  }
}

void CPDlgPgToWin::OnButtonStopReading() 
{
  m_OwningPipeDialog->OnStop();
	// disable statistics display
	m_OwningPipeDialog->StopStatisticsTimer();
	// update display to reflect current counter values
	m_OwningPipeDialog->UpdatePipeStatistics();
}



BOOL CPDlgPgToWin::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_CHECK_PRINT_OUT:
        strID = IDS_CHECK_PRINT_OUT;
        break;
      case IDC_BUTTON_START_READINGTOWIN:
        strID = IDS_BUTTON_START_READINGTOFILE;
        break;
      case IDC_BUTTON_STOP_READINGTOWIN:
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

