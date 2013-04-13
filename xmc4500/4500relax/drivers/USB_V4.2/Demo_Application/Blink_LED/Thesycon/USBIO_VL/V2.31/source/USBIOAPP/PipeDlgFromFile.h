#if !defined(_PIPEDLGFROMFILE_H_)
#define _PIPEDLGFROMFILE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "PipeDialog.h"
#include "PDlgPgFromFile.h"
#include "UsbIoWriter.h"


class CPipeDlgFromFile;

//
// derive special class from CUsbIoWriter
//
class CUsbIoWr : public CUsbIoWriter
{
public:
  CUsbIoWr();
  ~CUsbIoWr();

  BOOL OpenFile(const char *Filename);
  void CloseFile();
  
  // overload process buffer function
  virtual void ProcessBuffer(CUsbIoBuf *Buf);

  virtual void BufErrorHandler(CUsbIoBuf* Buf);

  virtual void TerminateThread();

  // virtual function, called in the context of worker thread
  void OnThreadExit();

public:
  CPipeDlgFromFile *m_PipeDialog;

private:
  FILE *file;
  DWORD IsoRest;
};



/////////////////////////////////////////////////////////////////////////////
// CPipeDlgFromFile dialog

class CPipeDlgFromFile : public CPipeDialog
{
// Construction
public:
  CPipeDlgFromFile(CWnd* pParent = NULL);   // standard constructor
  ~CPipeDlgFromFile();

  void OnThreadExitMessage();


// Implementation
protected:

  virtual BOOL OnInitDialog();

  virtual BOOL OnStart();
  virtual void OnStop();


  CUsbIoWr m_Wr;

  // dialog page instances
  CPDlgPgFromFile m_DlgPgFromFile;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_PIPEDLGFROMFILE_H_)
