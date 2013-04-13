/************************************************************************
 *
 *  Module:       CPipe.cpp
 *  Long name:    Pipe
 *  Description:  abstraction for a pipe class
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#include "stdafx.h"
#include "Pipe.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPipe::CPipe()
{
#ifdef _DEBUG
	mDbgEndpointAddress = 0;
#endif
}

CPipe::~CPipe()
{

}

