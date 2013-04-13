/************************************************************************
 *
 *  Module:       CDbgTrace.cpp
 *  Long name:    Debug Trace class
 *  Description:  
 *
 *  Runtime Env.: Win32
 *  Author(s):    Frank Hofmann
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include "stdafx.h"
#include <windows.h>

#include <stdio.h>
#include <stdarg.h>

#include "CDbgTrace.h"


// convert byte to ASCII
static const char DbgHexDigits[] = "0123456789ABCDEF";

#define DBG_BYTE_TO_ASC(b,str)                                  \
    {                                                           \
      *(str)++ = DbgHexDigits[ ((unsigned char)(b)) >> 4 ];     \
      *(str)++ = DbgHexDigits[ ((unsigned char)(b)) & 0x0F ];   \
    }


//ctor
CDbgTrace::CDbgTrace(const char* Prefix)
{
	// prefix
	mPrefix = Prefix;
	// default targets
	mTarget = TRCTARGET_ODS;
	mTraceFile = NULL;
	// default mask
	mMask = 0x3;
	// default features
	mFeatures = 0;

	mLastTS = 0;
}



// set trace destinations, 0 = all off
void
CDbgTrace::SetTarget(unsigned long TargetMask, FILE* TraceFile)
{
	mTarget = TargetMask;
	mTraceFile = TraceFile;
}


// print trace, conforms to printf conventions
void
CDbgTrace::Print(const char *format, ...)
{
	va_list argptr;
	char buffer[4096];

	va_start(argptr,format);

	int maxs = sizeof(buffer) - 1;
	int n = 0;

	// print TS
	if ( mFeatures&TRC_PRINT_TIMESTAMP ) {
		unsigned long ts = ::GetTickCount();
		n += _snprintf(&buffer[n],maxs-n, "%08d", ts);
		if ( mFeatures&TRC_PRINT_TIMESTAMP_DIFF ) {
			n += _snprintf(&buffer[n],maxs-n, "(%04d)", ts-mLastTS );
			mLastTS = ts;
		}
		buffer[n++] = ' ';
	}

	// print TS diff
	if ( (mFeatures&TRC_PRINT_PREFIX) && mPrefix!=0 ) {
		n += _snprintf(&buffer[n],maxs-n, "%s: ", mPrefix);
	}

	// print arguments
	_vsnprintf(&buffer[n],maxs-n, format, argptr);
	// force termination
	buffer[maxs] = 0;

	// print to target
	if ( mTarget&TRCTARGET_PRINTF ) {
		fprintf(stderr,"%s",buffer);
	}
	if ( mTarget&TRCTARGET_ODS ) {
		OutputDebugString(buffer);
	}
	if ( (mTarget&TRCTARGET_FILE) && (mTraceFile!=NULL) ) {
		fprintf(mTraceFile,"%s",buffer);
		fflush(mTraceFile);
	}

	va_end(argptr);

} //Print

void CDbgTrace::PrintDump(const void* data, unsigned long length)
{
	char buffer[100]; // 100 chars max
	char *p = buffer;
	char *pp = buffer;
  unsigned char *datap = (unsigned char *)data;
  unsigned long *dptr;
  int i;
  union {
    unsigned long ofs;
    unsigned char ofsb[4];
  } uu;
  unsigned char b;

  uu.ofs = 0;
  
  if ( length==0 ) {
		Print("<<NULL>>\n");
		return;
	}

	while ( length-- ) {

		b = *datap++;

		if ( (uu.ofs & 0x000F) == 0 ) {
			/* fill line with spaces */
			for (i=20,dptr=(unsigned long*)buffer; i--; ) *dptr++ = 0x20202020;
			p = buffer;
			pp = p + (4+1+1+(4*(4*3+1))) + 1;
			/* write ofs */
			DBG_BYTE_TO_ASC(uu.ofsb[1],p);
			DBG_BYTE_TO_ASC(uu.ofsb[0],p);
			*p++ = ':';
			*p++ = ' ';
		}

		/* write byte (hex) */
		DBG_BYTE_TO_ASC(b,p);
		*p++ = ' ';
		/* write byte (ascii) */
		*pp++ = ( (b>=0x20) && (b<=0x7F) ) ? b : '.';			//lint !e734

		if ( (uu.ofs & 0x0003) == 0x0003 ) {
			/* dword complete */
			*p++ = ' ';
		}

		uu.ofs++;
  
		if ( (uu.ofs & 0x000F) == 0 ) {
			/* end of line */
			*pp++ = '\n';
			*pp = '\0';
			Print(buffer);
		}

	} // while

	if ( (uu.ofs & 0x000F) != 0 ) {
		/* terminate last line */
		*pp++ = '\n';
		*pp = '\0';
		Print(buffer);
	}
} //PrintDump



/************************************ EOF *******************************/
