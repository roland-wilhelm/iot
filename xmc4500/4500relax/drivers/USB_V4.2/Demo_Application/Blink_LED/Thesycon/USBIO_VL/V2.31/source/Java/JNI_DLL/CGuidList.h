/************************************************************************
 *
 *  Module:       CGuidList.h
 *  Long name:    GUID List
 *  Description:  contains a list of GUID's, used for the notification of
 *                several interfaces
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/


#if !defined(AFX_CGUIDLIST_H__75CCFB72_A102_49E0_BB01_ADF20414B354__INCLUDED_)
#define AFX_CGUIDLIST_H__75CCFB72_A102_49E0_BB01_ADF20414B354__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCritSect.h"
#include "CDlList.h"


class CThreadPnPNotify;


class CGuidList  
{
// struct that is used in the list
// it is an element that consists of an guid,
// a pointer to the CThreadPnPNotify class
// and a pointer to the next element
// the pointer is NULL if no more element is in the list
typedef struct _ListElement {
	CDlListEntry _mDlListEntry;	// link element, used by CDlList
  GUID guid;
  CThreadPnPNotify *NotifyThread;
} ListElement;

public:
	// constructor
	CGuidList();

	// destructor
	// delete the list an all classes that are ín the list
	~CGuidList();

	// remove an element from the list
	// the element will be deleted not the CThreadPnPNotify class
	// the caller get the pointer to the class
	// the caller must delete it
	bool Remove(const GUID& guid, CThreadPnPNotify **NotifyThread);

	// search fo an GUID in the list
	// returns false and a pointer to NULL if the GUID is not in the list
	bool Lookup(const GUID& guid, CThreadPnPNotify **NotifyThread);

	// add a GUID to the list
	// the caller must alloc the class
	void Add(const GUID& guid, CThreadPnPNotify *NotifyThread);


protected:
	CCritSect mCS;
	// list
	CDlList<ListElement> mList;
};

#endif // !defined(AFX_CGUIDLIST_H__75CCFB72_A102_49E0_BB01_ADF20414B354__INCLUDED_)
