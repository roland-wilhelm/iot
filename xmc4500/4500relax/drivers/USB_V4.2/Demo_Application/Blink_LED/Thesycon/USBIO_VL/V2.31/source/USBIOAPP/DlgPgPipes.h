#if !defined(AFX_DLGPGPIPES_H__843CF9AD_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGPIPES_H__843CF9AD_633F_11D2_9E23_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgPipes.h : header file
//

#include "DialogPage.h"



enum PURPOSE {
  Purpose_reserved,
  PipeToWin,
  PipeToFile,
  FileToPipe
};


/////////////////////////////////////////////////////////////////////////////
// CDlgPgPipes dialog

class CDlgPgPipes : public CDialogPage
{
// Construction
public:
  CDlgPgPipes(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgPipes)
	enum { IDD = IDD_DIALOGPAGE_PIPES };
	CButton	m_ButtonPipeToWin;
	CButton	m_ButtonPipeToFile;
	CButton	m_ButtonFileToPipe;
	CListBox	m_ListBoxEndpoints;
	CStatic	m_DevNotConfig;
	//}}AFX_DATA

  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgPipes)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  virtual void OnSelectionChange(BOOL bSelected);


// Implementation
protected:

  virtual const int* GetControlIdArray();

	void UpdateEndpointList();
	void UpdateEndpointSelection();
	void OpenPipe(PURPOSE Purpose);



	// selected endpoint, -1 if invalid
  int m_EndpointAddr;


  // Generated message map functions
  //{{AFX_MSG(CDlgPgPipes)
  afx_msg void OnButtonGetPipeInfo();
  virtual BOOL OnInitDialog();
	afx_msg void OnButtonFileToPipe();
	afx_msg void OnButtonPipeToFile();
	afx_msg void OnButtonPipeToWin();
	afx_msg void OnSelchangeListEndpoints();
	//}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGPIPES_H__843CF9AD_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
