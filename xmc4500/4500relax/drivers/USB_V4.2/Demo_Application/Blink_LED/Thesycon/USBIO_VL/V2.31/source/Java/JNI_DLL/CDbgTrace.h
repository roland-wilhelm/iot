/************************************************************************
 *
 *  Module:       CDbgTrace.h
 *  Long name:    Debug Trace class
 *  Description:  
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __CDbgTrace_h__
#define __CDbgTrace_h__

// for definition of FILE
#include <stdio.h>


// common trace levels 
#define TRCERR					 0	// fatal errors
#define TRCWRN					 1	// warnings
#define TRCINF					 2	// infos

// trace destinations
#define TRCTARGET_PRINTF		0x00000001		// printf to console
#define TRCTARGET_ODS			0x00000002		// OutputDebugString
#define TRCTARGET_FILE			0x00000004		// trace file


// trace features

// print timestamp, in ms, at the beginning of each line (off by default)
// ex: >07632763 trace text<
#define TRC_PRINT_TIMESTAMP					0x00000001

// additionally, print diff between current timestamp and last timestamp (off by default)
// ex: >07632763(0483) trace text<
#define TRC_PRINT_TIMESTAMP_DIFF			0x00000002

// print "PREFIX:" at the beginning of each line (on by default)
// ex: >SRV: trace text<
#define TRC_PRINT_PREFIX					0x00000100



//
// Trace Object
//
// represents a trace channel
//
class CDbgTrace 
{
public:
	//ctor
	// Prefix can be NULL  --> no prefix
	// Prefix points to string, must be persistent!
	CDbgTrace(const char* Prefix =0);

	//dtor
	//~CDbgTrace();

	// set trace targets, 0 = all off
	void SetTarget(unsigned long TargetMask, FILE* TraceFile =NULL);
	// get current trace targets
	unsigned long GetTarget()		{ return mTarget; }

	// set trace mask
	void SetMask(unsigned long NewMask)		{ mMask = NewMask; }
	// get current trace mask
	unsigned long GetMask()		{ return mMask; }

	// set trace features
	void SetFeatures(unsigned long FeatureMask)		{ mFeatures = FeatureMask; }
	// get current trace features set
	unsigned long GetFeatures()		{ return mFeatures; }

	// print trace, conforms to printf conventions
	void Print(const char *format, ...);

	// printdump trace, conforms to printf conventions
	void PrintDump(const void* data, unsigned long length);


// implementation
public:
	// current trace mask
	unsigned long mMask;
protected:
	// prefix, optional
	const char* mPrefix;
	// trace targets
	unsigned long mTarget;
	// file, optional
	FILE* mTraceFile;
	// feature mask
	unsigned long mFeatures;
	// last time stamp
	unsigned long mLastTS;

};	// class CDbgTrace



#endif //__CDbgTrace_h__

/************************************ EOF *******************************/
