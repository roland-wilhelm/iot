// USBIOAPPDlg.h : header file
//

#if !defined(AFX_USBIOAPPDLG_H__3F6259EB_6055_11D2_9E20_0080C8272F6C__INCLUDED_)
#define AFX_USBIOAPPDLG_H__3F6259EB_6055_11D2_9E20_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "winuser.h"
#include "OutputWindow.h"
#include "DialogPageCtrl.h"
#include "DlgPgDevice.h"
#include "DlgPgDesc.h"
#include "DlgPgConfig.h"
#include "DlgPgInterface.h"
#include "DlgPgPipes.h"
#include "DlgPgDevreq.h"
#include "DlgPgFeature.h"
#include "DlgPgOther.h"





/////////////////////////////////////////////////////////////////////////////
// CUSBIOAPPDlg dialog

class CUSBIOAPPDlg : public CDialog
{
// Construction
public:
  CUSBIOAPPDlg(CWnd* pParent = NULL); // standard constructor
// Destruction
  ~CUSBIOAPPDlg();

  BOOLEAN RegisterDevNotify(const GUID *InterfaceClassGuid, HDEVNOTIFY *hDevNotify);


  // update enable/disable state of controls
  void UpdateStateOfControls();


// Dialog Data
  //{{AFX_DATA(CUSBIOAPPDlg)
	enum { IDD = IDD_USBIOAPP_DIALOG };
  CDialogPageCtrl m_TabControlMain;
	//}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CUSBIOAPPDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  virtual void PostNcDestroy();
  //}}AFX_VIRTUAL


// Implementation
protected:
  HICON m_hIcon;

  HDEVNOTIFY m_DevNotify;
	bool m_InitialMove;

//////////////////////////////////////////////////////
  // dialog page instances
  CDlgPgDevice      m_DlgPgDevice;
  CDlgPgDesc        m_DlgPgDesc;
  CDlgPgConfig      m_DlgPgConfig;
  CDlgPgInterface   m_DlgPgInterface;
  CDlgPgPipes       m_DlgPgPipes;
  CDlgPgDevreq      m_DlgPgDevreq;
  CDlgPgFeature     m_DlgPgFeature;
  CDlgPgOther       m_DlgPgOther;


//////////////////////////////////////////////////////
protected:
  // Generated message map functions
  //{{AFX_MSG(CUSBIOAPPDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnButtonShowOutputWindow();
  afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnButtonClearOutputWindow();
  afx_msg void OnDestroy();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnButtonDockOutputWindow();
	//}}AFX_MSG
	afx_msg void OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
  afx_msg BOOL OnDeviceChange( UINT nEventType, DWORD dwData );
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBIOAPPDLG_H__3F6259EB_6055_11D2_9E20_0080C8272F6C__INCLUDED_)
