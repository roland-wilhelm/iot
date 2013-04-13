/************************************************************************
 *
 *  Module:       CGuidList.cpp
 *  Long name:    GUID List
 *  Description:  contains a list of GUID's, used for the notification of
 *                several interfaces
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuidList::CGuidList()
{
}


CGuidList::~CGuidList()
{
	// protect the list
	CAutoCritSect lock(&mCS);

	// clear list
	while ( !mList.IsEmpty() ) {
		ListElement* p = mList.RemoveHead();
		delete p;
	}
}


void CGuidList::Add(const GUID& guid, CThreadPnPNotify *NotifyThread)
{
	// protect the list
	CAutoCritSect lock(&mCS);
	
	// alloc the new element
	ListElement *p = new ListElement;
	// write the GUID in the element
	p->guid = guid;
	// write the pointer to the class
	p->NotifyThread = NotifyThread;

	// add to list
	mList.InsertTail(p);
}


bool CGuidList::Lookup(const GUID& guid, CThreadPnPNotify **NotifyThread)
{
	// protect the list
	CAutoCritSect lock(&mCS);

	*NotifyThread = NULL;

	ListElement* p = NULL;
	while ( (p=mList.Next(p)) != NULL ) {
		if (p->guid == guid) {
			// GUID was found
			*NotifyThread = p->NotifyThread;
			break;
		}
	}
	
	if (*NotifyThread == NULL) {
		// return NULL if guid was not found
		return false;
	} else {
		// return pointer to the ThreadNotify class
		return true;
	}
}


bool CGuidList::Remove(const GUID& guid, CThreadPnPNotify **NotifyThread)
{
	// protect the list
	CAutoCritSect lock(&mCS);

	*NotifyThread = NULL;

	ListElement* p = NULL;
	while ( (p=mList.Next(p)) != NULL ) {
		if (p->guid == guid) {
			// GUID was found
			*NotifyThread = p->NotifyThread;
			mList.Remove(p);	//lint !e534
			delete p;
			break;
		}
	}
	
	if (*NotifyThread == NULL) {
		// return NULL if guid was not found
		return false;
	} else {
		// return pointer to the ThreadNotify class
		return true;
	}
}


/****************************** EOF ***********************************/

