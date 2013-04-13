// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B37CB8B6_1F40_4E00_A42D_31E07969EB17__INCLUDED_)
#define AFX_STDAFX_H__B37CB8B6_1F40_4E00_A42D_31E07969EB17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER 0x500


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include "objbase.h"
#include <hash_map>
#include "jni.h"
#include "Pipe.h"
#include "trace.h"
#include "RegAcc.h"
#include "CThreadPnPNotify.h"
#include <dbt.h>
#include "CThreadBase.h"
#include "CGuidList.h"





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B37CB8B6_1F40_4E00_A42D_31E07969EB17__INCLUDED_)
