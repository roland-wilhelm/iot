#if !defined(AFX_PDLGPGTOWIN_H__4F9D2A0B_64CE_11D2_9E25_0080C8272F6C__INCLUDED_)
#define AFX_PDLGPGTOWIN_H__4F9D2A0B_64CE_11D2_9E25_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PDlgPgToWin.h : header file
//

#include "DialogPage.h"


class CPipeDialog;


/////////////////////////////////////////////////////////////////////////////
// CPDlgPgToWin dialog

class CPDlgPgToWin : public CDialogPage
{
// Construction
public:
  CPDlgPgToWin(CWnd* pParent = NULL);   // standard constructor

  void EnableStartButton()
			{ m_ButtonStart.EnableWindow(TRUE); }


// Dialog Data
  //{{AFX_DATA(CPDlgPgToWin)
	enum { IDD = IDD_PDIALOGPAGE_READTOWIN };
	CButton	m_ButtonStop;
	CButton	m_ButtonStart;
	//}}AFX_DATA


  BOOL Create(CPipeDialog* OwningPipeDialog, CWnd* pParent = NULL)
        { m_OwningPipeDialog = OwningPipeDialog; return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPDlgPgToWin)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  CPipeDialog *m_OwningPipeDialog;


  // Generated message map functions
  //{{AFX_MSG(CPDlgPgToWin)
  afx_msg void OnButtonStartReading();
  afx_msg void OnButtonStopReading();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDLGPGTOWIN_H__4F9D2A0B_64CE_11D2_9E25_0080C8272F6C__INCLUDED_)
