// PDlgPgPipeParams.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PDlgPgPipeParams.h"
#include "PipeDialog.h"
#include "UsbIoPipe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgPipeParams dialog


CPDlgPgPipeParams::CPDlgPgPipeParams(CWnd* pParent /*=NULL*/)
  : CDialogPage(CPDlgPgPipeParams::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPDlgPgPipeParams)
  m_ShortOk = FALSE;
  //}}AFX_DATA_INIT

  m_OwningPipeDialog = NULL;

}


void CPDlgPgPipeParams::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPDlgPgPipeParams)
  DDX_Check(pDX, IDC_CHECK_SHORT_OK, m_ShortOk);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPDlgPgPipeParams, CDialog)
  //{{AFX_MSG_MAP(CPDlgPgPipeParams)
  ON_BN_CLICKED(IDC_BUTTON_ABORT_PIPE, OnButtonAbortPipe)
  ON_BN_CLICKED(IDC_BUTTON_GET_PIPE_PARAMS, OnButtonGetPipeParams)
  ON_BN_CLICKED(IDC_BUTTON_RESET_PIPE, OnButtonResetPipe)
  ON_BN_CLICKED(IDC_BUTTON_SET_PIPE_PARAMS, OnButtonSetPipeParams)
  //}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgPipeParams message handlers

void CPDlgPgPipeParams::OnButtonAbortPipe() 
{
  if (USBIO_ERR_SUCCESS == PrintError(m_OwningPipeDialog->m_Pipe->AbortPipe(),E_FATAL)) {
    PrintOut("Abort Pipe was successful."NL);
  }
}


void CPDlgPgPipeParams::OnButtonGetPipeParams() 
{
	DWORD err = DoGetPipeParams();
	if ( err ) {
		PrintError(err,E_FATAL);
	} else {
    PrintOut("Get Pipe Parameters was successful."NL);
  }
}


DWORD CPDlgPgPipeParams::DoGetPipeParams() 
{
  USBIO_PIPE_PARAMETERS PipeParameters;
	DWORD err = m_OwningPipeDialog->m_Pipe->GetPipeParameters(&PipeParameters);
	if ( err ) {  
	} else {
		m_ShortOk = (PipeParameters.Flags & USBIO_SHORT_TRANSFER_OK) ? true : false;
    UpdateData(false);
	}
	return err;
}



void CPDlgPgPipeParams::OnButtonResetPipe() 
{
  if (USBIO_ERR_SUCCESS == PrintError(m_OwningPipeDialog->m_Pipe->ResetPipe(),E_FATAL)) {
    PrintOut("Reset Pipe was successful."NL);
  }
}

void CPDlgPgPipeParams::OnButtonSetPipeParams() 
{
  USBIO_PIPE_PARAMETERS PipeParameters;
  if (UpdateData(true)) {
    if (m_ShortOk) PipeParameters.Flags=USBIO_SHORT_TRANSFER_OK;
    else PipeParameters.Flags=0;
    if (PrintError(m_OwningPipeDialog->m_Pipe->SetPipeParameters(&PipeParameters),E_FATAL) == USBIO_ERR_SUCCESS) {
      PrintOut("Set Pipe Parameters was successful."NL);
    }
  }
}

BOOL CPDlgPgPipeParams::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPDlgPgPipeParams::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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
      case IDC_BUTTON_ABORT_PIPE:
        strID = IDS_BUTTON_ABORT_PIPE;
        break;
      case IDC_BUTTON_RESET_PIPE:
        strID = IDS_BUTTON_RESET_PIPE;
        break;
      case IDC_CHECK_SHORT_OK:
        strID = IDS_CHECK_SHORT_OK;
        break;
      case IDC_BUTTON_GET_PIPE_PARAMS:
        strID = IDS_BUTTON_GET_PIPE_PARAMS;
        break;
      case IDC_BUTTON_SET_PIPE_PARAMS:
        strID = IDS_BUTTON_SET_PIPE_PARAMS;
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