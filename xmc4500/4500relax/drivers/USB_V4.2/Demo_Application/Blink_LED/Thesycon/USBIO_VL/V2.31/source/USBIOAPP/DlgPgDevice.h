#if !defined(AFX_DLGPGDEVICE_H__4E7ABA6E_6059_11D2_9E20_0080C8272F6C__INCLUDED_)
#define AFX_DLGPGDEVICE_H__4E7ABA6E_6059_11D2_9E20_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPgDevice.h : header file
//

#include "DialogPage.h"
#include "hlstatic.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgPgDevice dialog

class CDlgPgDevice : public CDialogPage
{
// Construction
public:
  CDlgPgDevice(CWnd* pParent = NULL);   // standard constructor
   ~CDlgPgDevice();

// Dialog Data
  //{{AFX_DATA(CDlgPgDevice)
	enum { IDD = IDD_DIALOGPAGE_DEVICE };
	CButton	m_ButtonAcquire;
	CButton	m_ButtomRelease;
	CButton	m_ButtonOpen;
	CListBox	m_ListBoxDevices;
  BOOL  m_ResetOnClose;
  DWORD m_DeviceRequestTimeout;
  BOOL  m_UnconfigureOnClose;
  CString m_DriverVersionInfo;
  BOOL  m_EnableWakeup;
	CString	m_DeviceInfo;
	//}}AFX_DATA
	CHyperLinkStatic	m_HlStatic;


  BOOL Create(CWnd* pParent = NULL) { return CDialog::Create(IDD,pParent); }

	void UpdateDeviceList(bool PrintInfo =false);

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDlgPgDevice)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL



// Implementation
protected:

  virtual const int* GetControlIdArray();


  // Generated message map functions
  //{{AFX_MSG(CDlgPgDevice)
  afx_msg void OnButtonScan();
  afx_msg void OnButtonOpen();
  afx_msg void OnButtonClose();
  afx_msg void OnSetDeviceParameters();
  afx_msg void OnGetDeviceParameter();
  virtual BOOL OnInitDialog();
	afx_msg void OnButtonAcquire();
	afx_msg void OnButtonRelease();
	//}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPGDEVICE_H__4E7ABA6E_6059_11D2_9E20_0080C8272F6C__INCLUDED_)
