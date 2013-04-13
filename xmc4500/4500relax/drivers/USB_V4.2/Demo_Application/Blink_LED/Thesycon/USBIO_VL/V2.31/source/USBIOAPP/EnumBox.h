#if !defined(AFX_ENUMBOX_H__21D2A0CB_6800_11D2_9E27_0080C8272F6C__INCLUDED_)
#define AFX_ENUMBOX_H__21D2A0CB_6800_11D2_9E27_0080C8272F6C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EnumBox.h : header file
//


struct EnumBoxEntry {
  LPCTSTR lpszString;
  DWORD dwItemData;
};



/////////////////////////////////////////////////////////////////////////////
// CEnumBox window

class CEnumBox : public CComboBox
{
// Construction
public:
  CEnumBox();

// Attributes
public:

// Operations
public:

  void Init(EnumBoxEntry* EntryTab);

  void AddEntry(EnumBoxEntry* Entry);

  DWORD GetCurItemData();
  void CEnumBox::SetCurItemData(DWORD value);



// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CEnumBox)
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CEnumBox();

  // Generated message map functions
protected:
  //{{AFX_MSG(CEnumBox)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENUMBOX_H__21D2A0CB_6800_11D2_9E27_0080C8272F6C__INCLUDED_)
