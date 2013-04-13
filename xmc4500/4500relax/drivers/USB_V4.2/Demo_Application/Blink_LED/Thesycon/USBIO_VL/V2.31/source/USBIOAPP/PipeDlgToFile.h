#if !defined(_PIPEDLGTOFILE_H_)
#define _PIPEDLGTOFILE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "PipeDialog.h"
#include "PDlgPgToFile.h"
#include "UsbIoReader.h"

class CPipeDlgToFile;


//
// derive special class from CUsbIoReader
//
class CUsbIoRd : public CUsbIoReader
{
public:
  CUsbIoRd();
  ~CUsbIoRd();

  BOOL OpenFile(const char *Filename);
  void CloseFile();
  
  // overload process data function
  virtual void ProcessData(CUsbIoBuf *Buf);
  virtual void ProcessBuffer(CUsbIoBuf *Buf);

  virtual void TerminateThread();
  virtual void BufErrorHandler(CUsbIoBuf* Buf);
  void OnThreadExit();

  CPipeDlgToFile *m_PipeDialog;


private:
  FILE *file;

};



/////////////////////////////////////////////////////////////////////////////
// CPipeDlgToFile dialog

class CPipeDlgToFile : public CPipeDialog
{
// Construction
public:
  CPipeDlgToFile(CWnd* pParent = NULL);   // standard constructor
  ~CPipeDlgToFile();

  void OnThreadExitMessage();


// Implementation
protected:

  virtual BOOL OnInitDialog();

  virtual BOOL OnStart();
  virtual void OnStop();


  CUsbIoRd m_Rd;

  // dialog page instances
  CPDlgPgToFile m_DlgPgToFile;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_PIPEDLGTOFILE_H_)
