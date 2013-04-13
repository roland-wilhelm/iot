#if !defined(AFX_DLGPGDEVREQ_H__843CF9AB_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGDEVREQ_H__843CF9AB_633F_11D2_9E23_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgDevreq.h : header file
//

#include "DialogPage.h"
#include "EnumBox.h"



/////////////////////////////////////////////////////////////////////////////
// CDlgPgDevreq dialog

class CDlgPgDevreq : public CDialogPage
{
// Construction
public:
  CDlgPgDevreq(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgDevreq)
	enum { IDD = IDD_DIALOGPAGE_DEVREQ };
	CButton	m_ButtonShortOK;
  CEdit m_EditBufferLength;
  CEdit m_EditBuffer;
  CEnumBox  m_ComboType;
  CEnumBox  m_ComboRecipient;
  CEnumBox  m_ComboDirection;
  BOOL  m_ShortOk;
	//}}AFX_DATA

  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }

  // this handler is called with:
  //   TRUE  when the dialog page is selected
  //   FALSE when the dialog page is deselected
  virtual void OnSelectionChange(BOOL bSelected);


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgDevreq)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual const int* GetControlIdArray();

  void UpdateEditState();


  BYTE m_bRequest;
  WORD m_wValue;
  WORD m_wIndex;

  CByteArray m_Buffer;

  DWORD m_BufferLength;

  // Generated message map functions
  //{{AFX_MSG(CDlgPgDevreq)
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeComboDirection();
  afx_msg void OnButtonSendRequest();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGDEVREQ_H__843CF9AB_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
