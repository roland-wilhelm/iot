/************************************************************************
 *
 *  Module:       CCritSect.h
 *  Long name:    critical section helper class
 *
 *  Description:  
 *  Wrapper class for a critical section object
 *  CAutoCritSect helper class for enter/leave CS by ctor/dtor
 *
 *  Runtime Env.: Win32
 *  Author(s):    Udo Eberhardt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef __CCritSect_h__
#define __CCritSect_h__


//
// CCritSect wrapper class
//
// provides the functionality of a critical section (lock)
//
class CCritSect
{
public:
  // ctor
  CCritSect()
  {
    ::InitializeCriticalSection(&mCritSect);
  }
  
  // dtor
  ~CCritSect()
  { 
    ::DeleteCriticalSection(&mCritSect);
  }

  // enter section (acquire lock)
  void Enter() 
  {
    ::EnterCriticalSection(&mCritSect);
  }

  // leave section (release lock)
  void Leave()
  {
    ::LeaveCriticalSection(&mCritSect);
  }


  // make copy constructor and assignment operator inaccessible
private:
  CCritSect(const CCritSect& );
  CCritSect& operator=(const CCritSect& );

// implementation
protected:
  CRITICAL_SECTION mCritSect;

}; // class CCritSect




//
// CAutoCritSect helper class
//
// locks a critical section if constructed,
// and unlocks it automatically when the lock goes out of scope
//
class CAutoCritSect
{
public:
  // ctor
  CAutoCritSect(CCritSect* Sect)
  {
    mSect = Sect;
    mSect->Enter();
  }
  
  // dtor
  ~CAutoCritSect()
  {
    mSect->Leave(); 
  } //lint !e1740

  // make copy constructor and assignment operator inaccessible
private:
  CAutoCritSect(const CAutoCritSect& );
  CAutoCritSect& operator=(const CAutoCritSect& );

// implementation
protected:
  CCritSect* mSect;

};  //class CAutoCritSect



#endif // __CCritSect_h__
 
/*************************** EOF **************************************/
