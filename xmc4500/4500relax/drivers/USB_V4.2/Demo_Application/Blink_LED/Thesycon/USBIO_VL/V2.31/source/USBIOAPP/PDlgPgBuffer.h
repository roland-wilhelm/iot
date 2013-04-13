#if !defined(AFX_PDLGPGBUFFER_H__33536498_644B_11D2_9E24_0080C8272F6C__INCLUDED_)
#define AFX_PDLGPGBUFFER_H__33536498_644B_11D2_9E24_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PDlgPgBuffer.h : header file
//

#include "DialogPage.h"


class CPipeDialog;


/////////////////////////////////////////////////////////////////////////////
// CPDlgPgBuffer dialog

class CPDlgPgBuffer : public CDialogPage
{
// Construction
public:
  CPDlgPgBuffer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CPDlgPgBuffer)
  enum { IDD = IDD_PDIALOGPAGE_BUFFER };
  CEdit m_EditIsoPacketCount;
  //}}AFX_DATA


  BOOL Create(CPipeDialog* OwningPipeDialog, CWnd* pParent = NULL)
        { m_OwningPipeDialog = OwningPipeDialog; return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPDlgPgBuffer)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  CPipeDialog *m_OwningPipeDialog;


  // Generated message map functions
  //{{AFX_MSG(CPDlgPgBuffer)
  virtual BOOL OnInitDialog();
	afx_msg void OnButtonBufferSetDefaults();
	//}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDLGPGBUFFER_H__33536498_644B_11D2_9E24_0080C8272F6C__INCLUDED_)
