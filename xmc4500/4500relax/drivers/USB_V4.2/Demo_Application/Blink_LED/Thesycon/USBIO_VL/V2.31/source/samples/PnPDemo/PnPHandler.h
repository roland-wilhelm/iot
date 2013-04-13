/************************************************************************
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 ************************************************************************/

/************************************************************************
 *
 *  Module:       PnPHandler.h
 *  Long name:    PnPHandler class definition/implementation
 *  Description:  implements the CPnPNotifyHandler interface.
 *
 *  Runtime Env.: Win32
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

#ifndef _PnPHandler_h_
#define _PnPHandler_h_

#include "PnPNotificator.h"

//
// CPnPHandler class
// This class implements the interface defined by CPnPNotifyHandler.
//
class CPnPHandler : public CPnPNotifyHandler
{
public:
  // Construction
  CPnPHandler()
      { m_PnPNotifyEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL); }
  // destructor
  ~CPnPHandler()
      {
        ::CloseHandle(m_PnPNotifyEvent);
        m_PnPNotifyEvent = NULL;
      }

  // ----------------
  // interface

  // return handle of notification event
  HANDLE GetNotificationEvent(void)
      { return m_PnPNotifyEvent; }


  // ----------------
  // CPnPNotifyHandler overloaded functions

  // These notification handlers are called in the context of
  // the worker thread.

  // called if a WM_DEVICECHANGE is issued by the system
  virtual 
  void HandlePnPMessage(
    UINT uMsg,
    WPARAM wParam,  // specifies event type
    LPARAM lParam   // points to event-specific data
    );

// implementation
protected:

  // --------------
  // member variables

  // event will be set if a HandlePnPMessage call is received
  // 
  HANDLE m_PnPNotifyEvent;


}; // class CPnPHandler


#endif // !defined(_PnPHandler_h_)

/*************************** EOF **************************************/
