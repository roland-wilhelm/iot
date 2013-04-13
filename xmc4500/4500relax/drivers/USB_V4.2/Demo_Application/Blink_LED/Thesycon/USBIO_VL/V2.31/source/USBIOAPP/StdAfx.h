// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3F6259ED_6055_11D2_9E20_0080C8272F6C__INCLUDED_)
#define AFX_STDAFX_H__3F6259ED_6055_11D2_9E20_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//
// Depending on what version of header files you are using,
// you may need to define WINVER to 5.00
// This will enable the declaration of RegisterDeviceNotification() and 
// UnregisterDeviceNotification() in WINUSER.H.
//
// Note:
// Consequently, the application will run on Win98, WinME, and Win2000 only.
// This should not be a problem because USBIO supports only these platforms.
//
#define WINVER 0x500


// Exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN    

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3F6259ED_6055_11D2_9E20_0080C8272F6C__INCLUDED_)
