/************************************************************************
 *
 *  Module:       trace.h
 *  Long name:    trace support
 *  Description:  
 *
 *  Runtime Env.: Win32
 *  Author(s):    Ralf Elis
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __TRACE_H__
#define __TRACE_H__

#include "CDbgTrace.h"
#include "trc.h"


#if TRACE_SUPPORT
// global trace object
extern CDbgTrace gTrace;
#endif


//
// The following functions are empty if
// trace support is disabled by #define TRACE_SUPPORT 0
//

// init trace module
void 
DbgTraceInit();

// shutdown trace module
void 
DbgTraceShutdown();


// set target
void 
DbgTraceSetTarget(
	unsigned long Target
	);

// set mask 
void 
DbgTraceSetMask(
	unsigned long Mask
	);




// remove any previous macro definition
#ifdef TRACE
#undef TRACE
#endif

// TRACE macro
// active in debug builds only
#if TRACE_SUPPORT && defined(_DEBUG)
#define TRACE(bitnb,x)   if TRCBIT(bitnb) { x; }
#else
#define TRACE(bitnb,x)
#endif


// remove any previous macro definition
#ifdef TRACELOG
#undef TRACELOG
#endif

// TRACELOG macro
// active in debug and release builds
#if TRACE_SUPPORT
#define TRACELOG(bitnb,x)   if TRCBIT(bitnb) { x; }
#else
#define TRACELOG(bitnb,x)
#endif



// returns true if the specified bit is set in TraceMask
#if TRACE_SUPPORT
#define TRCBIT(bitnb)   ( (gTrace.mMask & (((unsigned long)0x1)<<(bitnb))) != 0 )
#else
#define TRCBIT(bitnb)   0
#endif

// print function 
#ifdef TRACE_SUPPORT
#define tprint gTrace.Print
#else
#define tprint
#endif

// print function 
#ifdef TRACE_SUPPORT
#define tprintdump gTrace.PrintDump
#else
#define tprintdump
#endif



// remove previous ASSERT macros 
#ifdef ASSERT
#undef ASSERT
#endif

#ifdef _ASSERT
#undef _ASSERT
#endif

//
// ASSERT macro
// active in debug builds only
// prints message if bit 0 is set in TraceMask
//
#if DBG || defined(_DEBUG)
/*lint -emacro(506,_ASSERT) -emacro(774,_ASSERT) */
#define _ASSERT(condition)                              \
    if ( !(condition) && TRCBIT(0) ) {                  \
      tprint("\nASSERTION FAILED: (" #condition ")\n" \
            "  %s(%d)\n",                               \
            __FILE__, __LINE__);                        \
    }
#else
#define _ASSERT(condition)
#endif



#endif //__TRACE_H__

/********************************* EOF *********************************/
