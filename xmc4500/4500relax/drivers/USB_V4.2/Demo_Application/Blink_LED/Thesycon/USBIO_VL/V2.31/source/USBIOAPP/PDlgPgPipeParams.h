#if !defined(AFX_PDLGPGPIPEPARAMS_H__4F9D2A0D_64CE_11D2_9E25_0080C8272F6C__INCLUDED_)
#define AFX_PDLGPGPIPEPARAMS_H__4F9D2A0D_64CE_11D2_9E25_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PDlgPgPipeParams.h : header file
//

#include "DialogPage.h"


class CPipeDialog;


/////////////////////////////////////////////////////////////////////////////
// CPDlgPgPipeParams dialog

class CPDlgPgPipeParams : public CDialogPage
{
friend class CPipeDialog;
// Construction
public:
  CPDlgPgPipeParams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CPDlgPgPipeParams)
  enum { IDD = IDD_PDIALOGPAGE_PIPEPARAMS };
  BOOL  m_ShortOk;
  //}}AFX_DATA


  BOOL Create(CPipeDialog* OwningPipeDialog, CWnd* pParent = NULL)
        { m_OwningPipeDialog = OwningPipeDialog; return CDialog::Create(IDD,pParent); }


	DWORD DoGetPipeParams();

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPDlgPgPipeParams)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  CPipeDialog *m_OwningPipeDialog;

  // Generated message map functions
  //{{AFX_MSG(CPDlgPgPipeParams)
  afx_msg void OnButtonAbortPipe();
  afx_msg void OnButtonGetPipeParams();
  afx_msg void OnButtonResetPipe();
  afx_msg void OnButtonSetPipeParams();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );

  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDLGPGPIPEPARAMS_H__4F9D2A0D_64CE_11D2_9E25_0080C8272F6C__INCLUDED_)
