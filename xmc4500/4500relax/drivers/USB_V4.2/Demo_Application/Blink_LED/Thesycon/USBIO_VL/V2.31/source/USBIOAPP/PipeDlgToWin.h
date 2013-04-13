#if !defined(_PIPEDLGTOWIN_H_)
#define _PIPEDLGTOWIN_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "PipeDialog.h"
#include "PDlgPgToWin.h"
#include "UsbIoReader.h"


class CPipeDlgToWin;


//
// derive a special class from CUsbIoReader
//
class CUsbIoDump : public CUsbIoReader
{
public:
  CUsbIoDump();
  ~CUsbIoDump();

  void Init(CPipeDlgToWin *ptr, HWND Hwnd);

  virtual void BufErrorHandler(CUsbIoBuf* Buf);

private:
  // overload notification handler
  virtual void OnThreadExit();
  // overload process data function
  virtual void ProcessData(CUsbIoBuf *Buf);
  // overload process buffer function
  virtual void ProcessBuffer(CUsbIoBuf *Buf);
 
  // members
  CPipeDialog *m_PipeDialog;
  DWORD m_PrintPos;
  HWND m_hwnd;

};



/////////////////////////////////////////////////////////////////////////////
// CPipeDlgToWin dialog

class CPipeDlgToWin : public CPipeDialog
{
// Construction
public:
   ~CPipeDlgToWin();
  CPipeDlgToWin(CWnd* pParent = NULL);   // standard constructor


// Implementation

  virtual BOOL OnInitDialog();

  virtual BOOL OnStart();
  virtual void OnStop();

  void OnThreadExitMessage();


  CUsbIoDump m_Dump;

  // dialog page instances
  CPDlgPgToWin m_DlgPgToWin;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_PIPEDLGTOWIN_H_)
