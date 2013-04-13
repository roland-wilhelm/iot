#if !defined(AFX_PIPEDIALOG_H__843CF9A9_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
#define AFX_PIPEDIALOG_H__843CF9A9_633F_11D2_9E23_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PipeDialog.h : header file
//

#include "DialogPageCtrl.h"
#include "PDlgPgPipeParams.h"
#include "PDlgPgBuffer.h"
#include "PDlgPgPipeControl.h"


class CUsbIoPipe;
//class CPDlgPgPipeControl;


/////////////////////////////////////////////////////////////////////////////
// CPipeDialog dialog

class CPipeDialog : public CDialog
{
// Construction
public:
  CPipeDialog(CWnd* pParent = NULL);   // standard constructor
  virtual ~CPipeDialog(); // desctructor

// Dialog Data
  //{{AFX_DATA(CPipeDialog)
	enum { IDD = IDD_PIPE_DIALOG };
	CEdit	m_EditStatsBytesTransferred;
	CEdit	m_EditStatsReqSucceeded;
	CEdit	m_EditStatsReqFailed;
	CEdit	m_EditStatsMeanRate;
  CDialogPageCtrl m_TabControl;
	//}}AFX_DATA

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPipeDialog)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void PostNcDestroy();
  //}}AFX_VIRTUAL


// Interface
public:

  DWORD BindPipe(int DeviceNumber, int EndpointAddress);

  BOOL UpdateAllData( BOOL bSaveAndValidate = TRUE )
      { return m_TabControl.UpdateAllData(bSaveAndValidate); }

	// return pipe prefix string
	const char* Prefix()
			{ return m_PipePrefix; }

	// set defaults
	void SetBufferDefaults();

	// load/save recent settings
	void LoadRecentSettings();
	void SaveRecentSettings();

	// start/stop statistics timer
	void StartStatisticsTimer();
	void StopStatisticsTimer();

	// update pipe statistics display
	void UpdatePipeStatistics();


  // overload CDialogs virtual DestroyWindow function here
  virtual BOOL DestroyWindow();

  // virtual functions that must be overloaded by derived classes
  virtual BOOL OnStart() = 0;
  virtual void OnStop() = 0;
  virtual void OnThreadExitMessage() = 0;

  // notification function, called in the context of worker thread!
  void OnThreadExit();


  USBIO_PIPE_CONFIGURATION_INFO m_PipeInfo;
  
	// prefix string, used for printing messages
  CString m_PipePrefix;

	// registry subkey where recent settings for this dialog will be stored
	const char* m_DlgSubKey;
	
	// dialog data member (for all pages)
  DWORD m_SizeOfBuffer;
  DWORD m_NumberOfBuffers;
  DWORD m_MaxErrorCount;
  DWORD m_NumberOfIsoPackets;
  DWORD m_SampleRate;
  DWORD m_SampleSize;

  BOOL m_EnablePrint;
  BOOL m_AutoRepeat;

  DWORD m_IsoHeaderSize;

  CString m_FileName;

  // pointer to USBIO pipe
  CUsbIoPipe *m_Pipe;

  // TRUE if worker thread is running
  BOOL m_Running;


// Implementation
protected:
  
  virtual void OnOK();
  virtual void OnCancel();

  
  // dialog page instances
  CPDlgPgPipeParams   m_DlgPgPipeParams;
  CPDlgPgBuffer       m_DlgPgBuffer;
  CPDlgPgPipeControl  m_DlgPgPipeControl;

	UINT m_StatisticsTimer;

  // Generated message map functions
  //{{AFX_MSG(CPipeDialog)
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeTabPipe(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LONG OnMessageThreadExit( UINT, LONG ); 
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonResetPipeStatistics();
	//}}AFX_MSG
  BOOL OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult );
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIPEDIALOG_H__843CF9A9_633F_11D2_9E23_0080C8272F6C__INCLUDED_)
