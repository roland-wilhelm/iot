/************************************************************************
 *
 *  Module:       trc.h
 *  Long name:    local trace settings for project
 *  Description:  
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __TRC_H__
#define __TRC_H__


// enable/disable trace support
#ifdef _DEBUG
// debug build
#define TRACE_SUPPORT		1
#else
// release build
#define TRACE_SUPPORT		0
#endif


// default settings for trace channel
#define DEFAULT_TRACE_MASK			( 0x7 )
#define DEFAULT_TRACE_FEATURES	( TRC_PRINT_PREFIX )

#define DEFAULT_TRACE_TARGET		( TRCTARGET_ODS )

// prefix for all debug messages:
#define TRACE_PREFIX				"USBIOJAVADLL: "


// assigned trace bits
// Note: start with 4 !
//#define TRC_xxx				4





#endif //__TRC_H__

/********************************* EOF *********************************/
