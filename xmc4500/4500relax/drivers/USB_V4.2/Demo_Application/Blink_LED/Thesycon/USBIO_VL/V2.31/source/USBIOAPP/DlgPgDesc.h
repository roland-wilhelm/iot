#if !defined(AFX_DLGPGDESC_H__4E7ABA6F_6059_11D2_9E20_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGDESC_H__4E7ABA6F_6059_11D2_9E20_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgDesc.h : header file
//

#include "DialogPage.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgPgDesc dialog

class CDlgPgDesc : public CDialogPage
{
// Construction
public:
  CDlgPgDesc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgDesc)
  enum { IDD = IDD_DIALOGPAGE_DESC };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA


  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgDesc)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual const int* GetControlIdArray();

  void DoGetDeviceDesc();
  void DoGetConfigDesc();
  void DoGetStringDesc();
	void DoGetDeviceQualifierDesc();
	void DoGetOtherSpeedConfigDesc();
	void DoGetAnyDesc();


  DWORD m_ConfigDescIndex;
  DWORD m_StringDescIndex;
  DWORD m_StringDescLangID;
	DWORD m_AnyDescType;
  DWORD m_AnyDescIndex; 
  DWORD m_AnyDescLength;



  // Generated message map functions
  //{{AFX_MSG(CDlgPgDesc)
  afx_msg void OnButtonDeviceDesc();
  afx_msg void OnButtonStringDesc();
  afx_msg void OnButtonConfigDesc();
  virtual BOOL OnInitDialog();
	afx_msg void OnButtonDeviceQualifierDesc();
	afx_msg void OnButtonOtherSpeedConfigDesc();
	afx_msg void OnButtonAnyDesc();
	//}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGDESC_H__4E7ABA6F_6059_11D2_9E20_0080C8272F6C__INCLUDED_)
