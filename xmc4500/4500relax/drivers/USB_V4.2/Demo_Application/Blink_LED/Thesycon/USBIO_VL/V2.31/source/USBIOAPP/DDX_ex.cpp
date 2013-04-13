//
// DDX extension functions
//

#include "stdafx.h"
#include <afxpriv.h>
#include "DDX_ex.h"


// determine number of elements in an array (not bytes)
#define _countof(array) (sizeof(array)/sizeof(array[0]))


static
void AFXAPI DDX_TextConvert(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, DWORD& value, UINT nIDPrompt )
{

  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  TCHAR szT[40];  // should be enough for any number
  TCHAR *ptr;
  TCHAR *endptr;
  DWORD ul;

  if (pDX->m_bSaveAndValidate) {
    // edit control --> var
    int len = ::GetWindowText(hWndCtrl, szT, _countof(szT));
    szT[_countof(szT)-1] = 0; // terminate at least at the end
    ptr = szT + len;  // ptr to terminating null
#ifdef UNICODE
    ul = wcstoul(szT, &endptr, 0);
#else
    ul = strtoul(szT, &endptr, 0);
#endif
    // check for conversion errors
    if ( endptr!=ptr ) {
      // error
      AfxMessageBox(nIDPrompt);
      pDX->Fail();        // throws exception
    } else {
      // return value
      value = ul;
    }
  } else {
    // var --> edit control
    wsprintf(szT, lpszFormat, value);
    AfxSetWindowText(hWndCtrl, szT);
  }

} // DDX_TextConvert



void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, BYTE& value, UINT nIDPrompt )
{
  DWORD dw = value;
  DDX_TextConvert(pDX,nIDC,lpszFormat,dw,nIDPrompt);
  value = (BYTE)dw;
}


void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, WORD& value, UINT nIDPrompt )
{
  DWORD dw = value;
  DDX_TextConvert(pDX,nIDC,lpszFormat,dw,nIDPrompt);
  value = (WORD)dw;
}


void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, DWORD& value, UINT nIDPrompt )
{
  DWORD dw = value;
  DDX_TextConvert(pDX,nIDC,lpszFormat,dw,nIDPrompt);
  value = dw;
}



// max 256 bytes
#define DDX_TEXTEX_MAX_BYTES  256

// string <--> byte array
void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, CByteArray& ByteArray, UINT nIDPrompt )
{
  HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
  TCHAR *ptr;
  TCHAR *endptr;
  DWORD ul;
  const char *seps = " \t,;"; // separators
  TCHAR textbuffer[DDX_TEXTEX_MAX_BYTES*5];

  if (pDX->m_bSaveAndValidate) {
    // edit control --> var
      
    // empty the array
    ByteArray.RemoveAll();
    
    int len = ::GetWindowText(hWndCtrl, textbuffer, _countof(textbuffer));
    textbuffer[_countof(textbuffer)-1] = 0; // terminate at least at the end

    int pos;
    TCHAR *p = textbuffer;
    TCHAR *limit = textbuffer + len;
    for (;;) {
      
      while ( (*p) && ((pos=strcspn(p,seps))==0) ) {
        p++;
      } 
      if ( !(*p) ) break;
      ptr = p + pos;
      *ptr = 0;
  #ifdef UNICODE
      ul = wcstoul(p, &endptr, 0);
  #else
      ul = strtoul(p, &endptr, 0);
  #endif
      // check for conversion errors
      if ( endptr!=ptr ) {
        // error
        AfxMessageBox(nIDPrompt);
        pDX->Fail();        // throws exception
      } else {
        ByteArray.Add((BYTE)ul);
      }
      p += (pos+1);
      if ( p>=limit ) break;
    }

  } else {
    // var --> edit control
    
    TCHAR *p = textbuffer;
    int size = ByteArray.GetSize();
    if ( size > DDX_TEXTEX_MAX_BYTES ) size = DDX_TEXTEX_MAX_BYTES;
    for ( int i=0; i<size; i++ ) {
      BYTE b = ByteArray.GetAt(i);
      int n = wsprintf(p, lpszFormat, b);
      p += n;
    }
    *p = 0;

    AfxSetWindowText(hWndCtrl, textbuffer);
  }

}

