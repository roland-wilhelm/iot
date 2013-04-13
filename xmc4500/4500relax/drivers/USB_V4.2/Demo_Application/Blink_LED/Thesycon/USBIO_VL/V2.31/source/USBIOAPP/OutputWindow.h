#if !defined(AFX_OUTPUTWINDOW_H__D6635FEC_610F_11D2_9E21_0080C8272F6C__INCLUDED_)
#define AFX_OUTPUTWINDOW_H__D6635FEC_610F_11D2_9E21_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutputWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputWinDlg dialog, derived from CDialog

class COutputWinDlg : public CDialog
{
// Construction
public:
  COutputWinDlg(CWnd* pParent = NULL);   // standard constructor
  ~COutputWinDlg();

// Dialog Data
  //{{AFX_DATA(COutputWinDlg)
  enum { IDD = IDD_OUTPUT_WINDOW };
  CEdit m_EditControl;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(COutputWinDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  void OnOK();
  void OnCancel();



// Interface
public:
  
  void UpdateDisplayOn()  { m_EditControl.SetRedraw(TRUE); }
  void UpdateDisplayOff() { m_EditControl.SetRedraw(FALSE); }

  void ScrollDisplay()
    { m_EditControl.LineScroll(m_EditControl.GetLineCount(),0); }


  void Clear();

  void OutputString(const char *s);


// Implementation
protected:

  void UpdateClientWindow();

  CFont m_font;
	
	// intial move is done
	bool m_InitialMove;
	// we are executing a WM_USER_xxx command
	bool m_ByMsg;
	// output win docked to main window
	bool m_Docked;

  // Generated message map functions
  //{{AFX_MSG(COutputWinDlg)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
  afx_msg long OnMessagePingOutputWin(UINT nID, LPARAM lParam);
  afx_msg long OnMessagePrintOut(UINT nID, LPARAM lParam);
  afx_msg long OnMessageClearOutputWin(UINT nID, LPARAM lParam);
  afx_msg long OnMessageShowOutputWin(WPARAM wParam, LPARAM lParam);
  afx_msg long OnMessageMoveOutputWin(WPARAM wParam, LPARAM lParam);
  afx_msg long OnMessageSizeOutputWin(WPARAM wParam, LPARAM lParam);
  afx_msg long OnMessageDockOutputWin(WPARAM wParam, LPARAM lParam);
  afx_msg long OnMessageDestroyOutputWin(UINT nID, LPARAM lParam);
  DECLARE_MESSAGE_MAP()

};  //class COutputWinDlg




/////////////////////////////////////////////////////////////////////////////
// COutputWin thread, derived from CWinThread

class COutputWin : public CWinThread
{
  DECLARE_DYNCREATE(COutputWin)

  // construction
protected:
  COutputWin();  // protected constructor used by dynamic creation

  // destruction
protected:
  virtual ~COutputWin();


  // interface
public:

  // send message to output window
  LRESULT SendMessageToMainWnd(UINT Msg, WPARAM wParam, LPARAM lParam)
      { return (m_hWndMainWindow==NULL) ? (-1) : ::SendMessage(m_hWndMainWindow,Msg,wParam,lParam); }

  // close window, terminate thread
  BOOL CloseAndTerminate();


  // embedded dialog window
  COutputWinDlg m_Dialog;

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(COutputWin)
  public:
  virtual BOOL InitInstance();
  virtual int ExitInstance();
  //}}AFX_VIRTUAL



  // handle of main window (dialog)
  HWND m_hWndMainWindow;

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(COutputWin)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};  // class COutputWin

/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTWINDOW_H__D6635FEC_610F_11D2_9E21_0080C8272F6C__INCLUDED_)
