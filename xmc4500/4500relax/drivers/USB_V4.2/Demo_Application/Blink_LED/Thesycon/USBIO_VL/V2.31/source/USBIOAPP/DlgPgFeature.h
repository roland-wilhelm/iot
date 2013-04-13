#if !defined(AFX_DLGPGFEATURE_H__45E4C431_7231_11D2_9D01_0080C82727F4__INCLUDED_)
#define AFX_DLGPGFEATURE_H__45E4C431_7231_11D2_9D01_0080C82727F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgFeature.h : header file
//
#include "DialogPage.h"
#include "EnumBox.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPgFeature dialog

class CDlgPgFeature : public CDialogPage
{
// Construction
public:
  CDlgPgFeature(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgFeature)
  enum { IDD = IDD_DIALOGPAGE_FEATURE };
  CEnumBox  m_ComboRecipient;
  DWORD m_FeatureSelector;
  DWORD m_Index;
  //}}AFX_DATA

  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgFeature)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual const int* GetControlIdArray();

  // Generated message map functions
  //{{AFX_MSG(CDlgPgFeature)
  afx_msg void OnSetFeature();
  afx_msg void OnClearFeature();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGFEATURE_H__45E4C431_7231_11D2_9D01_0080C82727F4__INCLUDED_)
