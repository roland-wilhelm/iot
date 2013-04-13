//
// DDX extension functions
//

#ifndef _DDX_EX_H_
#define _DDX_EX_H_



void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, BYTE& value, UINT nIDPrompt );
void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, WORD& value, UINT nIDPrompt );
void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, DWORD& value, UINT nIDPrompt );

// string <--> byte array
void AFXAPI DDX_TextEx(CDataExchange* pDX, int nIDC, LPCTSTR lpszFormat, CByteArray& ByteArray, UINT nIDPrompt );




#endif  //_DDX_EX_H_
