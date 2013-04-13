// EnumBox.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "EnumBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnumBox

CEnumBox::CEnumBox()
{
}

CEnumBox::~CEnumBox()
{
}


void CEnumBox::Init(EnumBoxEntry* EntryTab)
{
  while ( EntryTab->lpszString != NULL ) {
    AddEntry(EntryTab);
    EntryTab++;
  }
  SetCurSel(0);
}



void CEnumBox::AddEntry(EnumBoxEntry* Entry)
{
  int idx = AddString(Entry->lpszString);
  if ( idx >= 0 ) {
    SetItemData(idx,Entry->dwItemData);
  } else {
    ASSERT(0);
  }
}


DWORD CEnumBox::GetCurItemData()
{
  DWORD dwItemData = 0xFFFFFFFF;
  int idx = GetCurSel();
  if ( idx >= 0 ) {
    dwItemData = GetItemData(idx);
  } else {
    ASSERT(0);
  }
  return dwItemData;
}

void CEnumBox::SetCurItemData(DWORD value)
{
  DWORD i,m;
  m=GetCount();
  for (i=0;i<m;i++) {
    if (value == GetItemData(i)) {
      SetCurSel(i);
      break;
    }
  }
}



BEGIN_MESSAGE_MAP(CEnumBox, CComboBox)
  //{{AFX_MSG_MAP(CEnumBox)
    // NOTE - the ClassWizard will add and remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnumBox message handlers
