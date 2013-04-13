#if !defined(AFX_DLGPGCONFIG_H__D6635FED_610F_11D2_9E21_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGCONFIG_H__D6635FED_610F_11D2_9E21_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgConfig.h : header file
//

#include "DialogPage.h"


#define NBOF_IFC    4


/////////////////////////////////////////////////////////////////////////////
// CDlgPgConfig dialog

class CDlgPgConfig : public CDialogPage
{

// interface settings
struct INTERFACE {
  BOOL InUse;
  DWORD Interface;
  DWORD AlternateSetting;
  DWORD MaxTransferSize;
};



// Construction
public:
  CDlgPgConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CDlgPgConfig)
  enum { IDD = IDD_DIALOGPAGE_CONFIG };
  //}}AFX_DATA

  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgConfig)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  virtual const int* GetControlIdArray();

  void UpdateEditState(UINT nIDCheckBox, UINT nIDEdit1, UINT nIDEdit2, UINT nIDEdit3);
  void UpdateEditState(void);

  void DoSetConfiguration();


  INTERFACE m_Ifc[NBOF_IFC];
  DWORD m_ConfigIndex;
  BOOL m_Active;


  // Generated message map functions
  //{{AFX_MSG(CDlgPgConfig)
  afx_msg void OnButtonSetConfiguration();
  virtual BOOL OnInitDialog();
  afx_msg void OnKillfocusEditConfigIndex();
  afx_msg void OnButtonGetConfiguration();
  afx_msg void OnButtonUnconfigureDevice();
	afx_msg void OnButtonBandwidth();
	//}}AFX_MSG
  afx_msg void OnKillfocusEditIf();
  afx_msg void OnCheckIf();
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGCONFIG_H__D6635FED_610F_11D2_9E21_0080C8272F6C__INCLUDED_)
