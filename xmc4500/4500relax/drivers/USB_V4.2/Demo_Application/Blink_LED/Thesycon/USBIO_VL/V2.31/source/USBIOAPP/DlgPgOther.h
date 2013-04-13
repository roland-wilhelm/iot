#if !defined(AFX_DLGPGOTHER_H__843CF9AC_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGOTHER_H__843CF9AC_633F_11D2_9E23_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgOther.h : header file
//

#include "DialogPage.h"
#include "EnumBox.h"
#include "afxwin.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgPgOther dialog

class CDlgPgOther : public CDialogPage
{
// Construction
public:
  CDlgPgOther(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgOther)
  enum { IDD = IDD_DIALOGPAGE_OTHER };
  CEnumBox  m_ComboPower;
  CEnumBox  m_ComboRecipient;
  //}}AFX_DATA

  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgOther)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual const int* GetControlIdArray();


  WORD m_Index;

  // Generated message map functions
  //{{AFX_MSG(CDlgPgOther)
  afx_msg void OnButtonGetCurrentFnb();
  afx_msg void OnButtonResetDevice();
  afx_msg void OnButtonGetStatus();
  virtual BOOL OnInitDialog();
  afx_msg void OnButtonTest1();
  afx_msg void OnButtonTest2();
  afx_msg void OnButtonSetPower();
  afx_msg void OnButtonGetPower();
  afx_msg void OnButtonCyclePort();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
public:
	//CButton m_Button_Get_Status;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGOTHER_H__843CF9AC_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
