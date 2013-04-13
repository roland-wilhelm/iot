#if !defined(AFX_PDLGPGPIPECONTROL_H__45E4C432_7231_11D2_9D01_0080C82727F4__INCLUDED_)
#define AFX_PDLGPGPIPECONTROL_H__45E4C432_7231_11D2_9D01_0080C82727F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PDlgPgPipeControl.h : header file
//
#include "DialogPage.h"
#include "EnumBox.h"

class CPipeDialog;

/////////////////////////////////////////////////////////////////////////////
// CPDlgPgPipeControl dialog

class CPDlgPgPipeControl : public CDialogPage
{
// Construction
public:
  CPDlgPgPipeControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CPDlgPgPipeControl)
  enum { IDD = IDD_DIALOGPAGE_PIPEREQ };
  CEdit m_EditBufferLength;
  CEdit m_EditBuffer;
  CEnumBox  m_ComboDirection;
  BOOL  m_ShortOk;
  //}}AFX_DATA

  BOOL Create(CPipeDialog* OwningPipeDialog, CWnd* pParent = NULL)
        { m_OwningPipeDialog = OwningPipeDialog; return CDialog::Create(IDD,pParent); }

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPDlgPgPipeControl)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  CByteArray  m_PipeSetup;
  CByteArray  m_Buffer;

  DWORD m_BufferLength;

  void UpdateEditState();
  CPipeDialog *m_OwningPipeDialog;

  // Generated message map functions
  //{{AFX_MSG(CPDlgPgPipeControl)
  afx_msg void OnButtonPipeSendRequest();
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangePipeComboDirection();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDLGPGPIPECONTROL_H__45E4C432_7231_11D2_9D01_0080C82727F4__INCLUDED_)
