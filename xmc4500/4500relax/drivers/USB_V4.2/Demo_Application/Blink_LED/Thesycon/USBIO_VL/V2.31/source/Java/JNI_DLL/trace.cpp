/************************************************************************
 *
 *  Module:       Trace.cpp
 *  Long name:    Trace support
 *  Description:  
 *
 *  Runtime Env.: Win32
 *  Author(s):    Ralf Elis
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#include "stdafx.h"
#include "trace.h"


//
// globals
//

#if TRACE_SUPPORT

// global trace object
CDbgTrace gTrace(TRACE_PREFIX);

// trace file
static FILE* gTraceFile = NULL;

#endif //TRACE_SUPPORT




// init trace module
void DbgTraceInit()
{
#if TRACE_SUPPORT

#ifdef DEFAULT_TRACE_FILE
	// open trace file
	gTraceFile = fopen( DEFAULT_TRACE_FILE, "wt" );
#endif
	
	// default target
	gTrace.SetTarget( DEFAULT_TRACE_TARGET, gTraceFile );
	// default mask
	gTrace.SetMask( DEFAULT_TRACE_MASK );
	// default features
	gTrace.SetFeatures( DEFAULT_TRACE_FEATURES );

#endif //TRACE_SUPPORT
} 




// shutdown trace module
void DbgTraceShutdown()
{
#if TRACE_SUPPORT

	if ( gTraceFile!=NULL ) {
		fclose(gTraceFile);
		gTraceFile = NULL;
	}

#endif //TRACE_SUPPORT
}




// set target
void DbgTraceSetTarget(unsigned long Target)
{
#if TRACE_SUPPORT
	gTrace.SetTarget(Target,gTraceFile);
#endif
} 


// set mask
void DbgTraceSetMask(unsigned long Mask)
{
#if TRACE_SUPPORT
	gTrace.SetMask(Mask);
#endif
} 



/********************************* EOF *********************************/
