// DialogPageCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DialogPageCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogPageCtrl

CDialogPageCtrl::CDialogPageCtrl()
{
  int i;

  // init table
  for ( i=0; i<MAX_DIALOG_PAGE; i++ ) {
    m_DialogPage[i] = NULL;
  }

  m_IndexCounter = 0;

}

CDialogPageCtrl::~CDialogPageCtrl()
{
}



BOOL CDialogPageCtrl::AddDialogPage(CDialogPage *DlgPg, UINT CaptionID)
{
  CString caption;
  
  caption.LoadString(CaptionID);

  return AddDialogPage(DlgPg,(const char *)caption);
}


BOOL CDialogPageCtrl::AddDialogPage(CDialogPage *DlgPg, const char *Caption)
{
  TC_ITEM tc;
  int i;
  BOOL succ = FALSE;

  ZeroMemory(&tc,sizeof(tc));
  
  tc.mask = TCIF_TEXT|TCIF_STATE;
  tc.pszText = (char*)Caption;
  tc.dwState = TCIS_BUTTONPRESSED;

  i = InsertItem(m_IndexCounter,&tc);
  if ( i>=0 && i<MAX_DIALOG_PAGE ) {
    m_DialogPage[i] = DlgPg;
    DlgPg->SetTabControlIndex(i);
    m_IndexCounter++;
    succ = TRUE;
  } 

  return succ;
}



void CDialogPageCtrl::UpdatePageSelection()
{
  int sel,i;
  
  sel = GetCurSel();

  if ( sel < 0 ) {
    // no selection
    return;
  }

  // hide all pages
  for ( i=0; i<MAX_DIALOG_PAGE; i++ ) {
    CDialogPage *pg = m_DialogPage[i];
    if ( pg == NULL ) {
      break;
    } else {
      if ( ::IsWindow(pg->m_hWnd) && pg->IsWindowVisible() ) {
        pg->ShowWindow(SW_HIDE);
        pg->OnSelectionChange(FALSE);
      }
    }
  }
  
  // get rect of text item
  CRect rc;
  GetItemRect(sel, &rc);
  // show selected page
  if ( sel>=0 && sel<MAX_DIALOG_PAGE ) {
    CDialogPage *pg = m_DialogPage[sel];
    if ( pg != NULL ) {
      if ( ::IsWindow(pg->m_hWnd) ) {
        pg->SetWindowPos(NULL, 4, rc.Height()+4, 0,0, 
              SWP_NOSIZE|SWP_NOZORDER|SWP_SHOWWINDOW);
        pg->OnSelectionChange(TRUE);
      }
    }
  }

}


BOOL CDialogPageCtrl::UpdateAllData( BOOL bSaveAndValidate /*= TRUE*/ )
{

  for ( int i=0; i<MAX_DIALOG_PAGE; i++ ) {
    CDialogPage *pg = m_DialogPage[i];
    if ( pg == NULL ) {
      break;
    } else {
      if ( !pg->UpdateData(bSaveAndValidate) ) {
        // display failed tab
        SetCurSel(pg->GetTabControlIndex());
        return FALSE;
      }
    }
  }

  return TRUE;

}


BEGIN_MESSAGE_MAP(CDialogPageCtrl, CTabCtrl)
  //{{AFX_MSG_MAP(CDialogPageCtrl)
    // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPageCtrl message handlers
