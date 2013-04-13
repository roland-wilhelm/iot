#if !defined(AFX_DLGPGINTERFACE_H__843CF9AA_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGINTERFACE_H__843CF9AA_633F_11D2_9E23_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgInterface.h : header file
//

#include "DialogPage.h"



/////////////////////////////////////////////////////////////////////////////
// CDlgPgInterface dialog

class CDlgPgInterface : public CDialogPage
{
// Construction
public:
  CDlgPgInterface(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgInterface)
  enum { IDD = IDD_DIALOGPAGE_INTERFACE };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgInterface)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual const int* GetControlIdArray();


  DWORD m_Interface;
  DWORD m_AlternateSetting;
  DWORD m_MaxTransferSize;


  // Generated message map functions
  //{{AFX_MSG(CDlgPgInterface)
  afx_msg void OnButtonSetInterface();
  afx_msg void OnButtonGetInterface();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGINTERFACE_H__843CF9AA_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
