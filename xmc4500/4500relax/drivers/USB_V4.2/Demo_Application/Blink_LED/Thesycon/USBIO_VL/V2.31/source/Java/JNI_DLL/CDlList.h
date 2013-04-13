/************************************************************************
 *
 *  Module:       CDlList.h
 *  Long name:    Basic implementation of a double linked list
 *  Description:  
 *  Definition of list utility classes that provide easy and efficient
 *  management of objects by means of a double linked list.
 *
 *  Runtime Env.: any
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

//
// Classes:
// class CDlListEntry   -- Double Linked List Entry
// class CDlList        -- Double Linked List 
//
// Dependencies:
// This file requires no other include files except that
// a definition of the null pointer (NULL) must be available.
//

#ifndef __CDlList_h__
#define __CDlList_h__


//
// Double Linked List Entry
//
// This object is used as a list entry (list node).
//
class CDlListEntry 
{
//////// INTERFACE ////////
public:
// ctor
  CDlListEntry()  { Reset(); }

  // returns true if entry is linked into a list
  bool IsLinked()  { return ( !(mNext==this) ); }

  // return pointer to next element
  CDlListEntry* Next()  { return mNext; }
  // return pointer to previous element
  CDlListEntry* Prev()  { return mPrev; }

  // set to initial state, so that IsLinked returns false
  void Reset()  { mNext = mPrev = this; }


//////// IMPLEMENTATION ////////
protected:
  // link NewEntry after Entry
  static void _link(CDlListEntry* NewEntry, CDlListEntry* Entry)
        {
          NewEntry->mNext = Entry->mNext;
          NewEntry->mPrev = Entry;
          Entry->mNext->mPrev = NewEntry;
          Entry->mNext = NewEntry;
        }

  // unlink entry
  static void _unlink(CDlListEntry* Entry)
        {
          Entry->mPrev->mNext = Entry->mNext;
          Entry->mNext->mPrev = Entry->mPrev;
          Entry->mNext = Entry->mPrev = Entry;
        }

protected:
  CDlListEntry* mNext;  // next element
  CDlListEntry* mPrev;  // previous element

// disable copy constructor and assignment operator
private:
  CDlListEntry(const CDlListEntry& );
  CDlListEntry& operator=(const CDlListEntry& );
}; //class CDlListEntry



//
// Double Linked List
//
// This class template provides the implementation of a double linked
// list of objects of type T.
// The list is *not* interlocked, means *not* thread-safe.
//
// IMPORTANT:
// Every object that is to be managed by this list has to contain
// the following member variable:
//   CDlListEntry _mDlListEntry;
// The variable either has to be public or access has to be allowed
// by a friend declaration.
//
template <class T, bool Counted =false>
class CDlList : private CDlListEntry
{
//////// INTERFACE ////////
public:
  // ctor
  CDlList()  { mSize = 0; }


  // Returns true if the list is empty, false otherwise.
  bool IsEmpty()  { return ( mNext==this ); }

  // Returns the current number of elements in the list.
  // The size is maintained only if Counted is true.
  int Size()      { return mSize; }


  // Get pointer to head item.
  // Returns NULL if the list is empty.
  T* Head()  { return _head_item(); }
    
  // Get pointer to tail item.
  // Returns NULL if the list is empty.
  T* Tail()  { return _tail_item(); }


  // Get the next item after Item, or the head item if Item is NULL.
  // Returns NULL if tail of list is reached.
  T* Next(T* Item)  { return ( (Item==NULL) ? _head_item() : _next_item(_listentry(Item)) ); }

  // Get the previous item before Item, or the tail item if Item is NULL.
  // Returns NULL if head of list is reached.
  T* Prev(T* Item)  { return ( (Item==NULL) ? _tail_item() : _prev_item(_listentry(Item)) ); }


  // Insert a new item at head of list.
  void InsertHead(T* NewItem)  { _insert_head(_listentry(NewItem)); _inc(); }

  // Insert a new item at tail of list.
  void InsertTail(T* NewItem)  { _insert_tail(_listentry(NewItem)); _inc(); }


  // Insert NewItem after Item.
  // NewItem is inserted at head of list if Item is NULL.
  void InsertAfter(T* NewItem, T* Item)  { if (Item==NULL) _insert_head(_listentry(NewItem)); else _link(_listentry(NewItem),_listentry(Item)); _inc(); }

  // Insert NewItem before Item.
  // NewItem is inserted at tail of list if Item is NULL.
  void InsertBefore(T* NewItem, T* Item) { if (Item==NULL) _insert_tail(_listentry(NewItem)); else _link(_listentry(NewItem),_listentry(Item)->Prev()); _inc(); }

  
  // Remove Item from list. Returns Item.
  T* Remove(T* Item)  { _unlink(_listentry(Item)); _dec(); return Item; }

  // Remove head item from list.
  // Returns pointer to item or NULL if list is empty.
  T* RemoveHead()  { return ( (mNext==this) ? NULL : _containing_obj(_remove_head()) ); }

  // Remove tail item from list.
  // Returns pointer to item or NULL if list is empty.
  T* RemoveTail()  { return ( (mPrev==this) ? NULL : _containing_obj(_remove_tail()) ); }


  // Reset list, re-init list head.
  // The list is empty after that call.
  void Reset()  { CDlListEntry::Reset(); mSize = 0; }


//////// IMPLEMENTATION ////////
protected:
// helper functions:

  // inc/dec element counter
  void _inc()   { if ( Counted ) ++mSize; }		//lint !e774
  void _dec()   { if ( Counted ) --mSize; }		//lint !e774

  // return head item or NULL if list is empty
  T* _head_item()
      { return ( (mNext==this) ? NULL : _containing_obj(mNext) ); }
  // return tail item or NULL if list is empty
  T* _tail_item()
      { return ( (mPrev==this) ? NULL : _containing_obj(mPrev) ); }

  // return next item or NULL if list head is reached
  T* _next_item(CDlListEntry* Entry)
      { return ( (Entry->Next()==this) ? NULL : _containing_obj(Entry->Next()) ); }
  // return previous item or NULL if list head is reached
  T* _prev_item(CDlListEntry* Entry)
      { return ( (Entry->Prev()==this) ? NULL : _containing_obj(Entry->Prev()) ); }

  // insert a new entry at head of list
  void _insert_head(CDlListEntry* NewEntry) { _link(NewEntry,this); }
  // insert a new entry at tail of list
  void _insert_tail(CDlListEntry* NewEntry) { _link(NewEntry,mPrev); }

  // remove head entry, return entry pointer
  CDlListEntry* _remove_head() { CDlListEntry* p = mNext; _unlink(p); _dec(); return p; }
  // remove tail entry, return entry pointer
  CDlListEntry* _remove_tail() { CDlListEntry* p = mPrev; _unlink(p); _dec(); return p; }

  // get pointer to list entry from object
  static CDlListEntry* _listentry(T* p)
      { return ( &p->_mDlListEntry ); }

  // calculate pointer to object from pointer to CDlListEntry member
  static T* _containing_obj(CDlListEntry* p) 
      { return ( (T*) (((char*)p) - ((char*)&((T*)0)->_mDlListEntry)) ); }	//lint !e413

protected:
  // current number of elements, only maintained if Counted==true
  int mSize;

// disable copy constructor and assignment operator
private:
  CDlList(const CDlList& );
  CDlList& operator=(const CDlList& );
}; //class CDlList


#endif  // __CDlList_h__

/*************************** EOF **************************************/
