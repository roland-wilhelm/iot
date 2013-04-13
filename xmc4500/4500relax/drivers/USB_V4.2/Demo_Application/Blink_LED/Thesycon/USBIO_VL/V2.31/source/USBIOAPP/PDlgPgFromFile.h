#if !defined(AFX_PDLGPGFROMFILE_H__4F9D2A0F_64CE_11D2_9E25_0080C8272F6C__INCLUDED_)
#define AFX_PDLGPGFROMFILE_H__4F9D2A0F_64CE_11D2_9E25_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PDlgPgFromFile.h : header file
//

#include "DialogPage.h"


class CPipeDialog;



/////////////////////////////////////////////////////////////////////////////
// CPDlgPgFromFile dialog

class CPDlgPgFromFile : public CDialogPage
{
// Construction
public:
  CPDlgPgFromFile(CWnd* pParent = NULL);   // standard constructor

  void EnableStartButton()
			{ m_ButtonStart.EnableWindow(TRUE); }


// Dialog Data
  //{{AFX_DATA(CPDlgPgFromFile)
	enum { IDD = IDD_PDIALOGPAGE_WRITEFROMFILE };
	CButton	m_ButtonStop;
	CButton	m_ButtonStart;
	//}}AFX_DATA


  BOOL Create(CPipeDialog* OwningPipeDialog, CWnd* pParent = NULL)
        { m_OwningPipeDialog = OwningPipeDialog; return CDialog::Create(IDD,pParent); }

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPDlgPgFromFile)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  CPipeDialog *m_OwningPipeDialog;


  // Generated message map functions
  //{{AFX_MSG(CPDlgPgFromFile)
  afx_msg void OnButtonSrcFileBrowse();
  afx_msg void OnButtonStartWritingFromFile();
  afx_msg void OnButtonStopWritingFromFile();
  afx_msg void OnButtonSendZeroPacket();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDLGPGFROMFILE_H__4F9D2A0F_64CE_11D2_9E25_0080C8272F6C__INCLUDED_)
