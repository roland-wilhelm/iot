/************************************************************************
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 ************************************************************************/

/************************************************************************
 *
 *  Module:       PnPHandler.cpp
 *  Long name:    PnPHandler class definition/implementation
 *  Description:  implements the CPnPNotifyHandler interface.
 *
 *  Runtime Env.: Win32
 *  Author(s):    Guenter Hildebrandt
 *  Company:      Thesycon GmbH, Ilmenau
 ************************************************************************/

// unicode is not supported
#ifdef UNICODE
#undef UNICODE
#endif
// define WINVER to 5.00 to enable RegisterDeviceNotification and 
// UnregisterDeviceNotification in WINDOWS.H and associated stuff in DBT.H
#ifdef WINVER
#undef WINVER
#endif
#define WINVER 0x0500
#include <windows.h>
#include <dbt.h>
#include <stdio.h>

#include "PnPHandler.h"


void 
CPnPHandler::HandlePnPMessage(
  UINT uMsg,
  WPARAM wParam,  // specifies event type
  LPARAM lParam   // points to event-specific data
  )
{

  LRESULT retcode = 0;

  DEV_BROADCAST_HDR *pointer;
  DEV_BROADCAST_DEVICEINTERFACE *devpointer;
  //CThreadPnPNotify *NotifyThread = NULL;

    switch(wParam) {
      case DBT_DEVICEARRIVAL:
      {
        // device was added
        if (lParam!=NULL) {
          pointer = (DEV_BROADCAST_HDR*)lParam;
          if (pointer->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
            devpointer = (DEV_BROADCAST_DEVICEINTERFACE*)pointer; //lint !e740 !e826
            if (m_PnPNotifyEvent!=NULL) {
              ::SetEvent(m_PnPNotifyEvent);
              fprintf(stdout,"Sending DBT_DEVICEARRIVAL notification\n");
              fprintf(stdout,"Device >%s< added\n",devpointer->dbcc_name);
            }
          }
        }
      }
      break;
      case DBT_DEVICEREMOVECOMPLETE :
      {
        // device was removed
        if (lParam!=NULL) {
          pointer = (DEV_BROADCAST_HDR*)lParam;
          if (pointer->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
            devpointer = (DEV_BROADCAST_DEVICEINTERFACE*)pointer; //lint !e740 !e826
            if (m_PnPNotifyEvent!=NULL) {
              ::SetEvent(m_PnPNotifyEvent);
              fprintf(stdout,"Sending DBT_DEVICEREMOVECOMPLETE notification\n");
              fprintf(stdout,"Device >%s< removed\n",devpointer->dbcc_name);
            }
          }
        }
      }
      break;
      default:
        break;
    } //switch (wParam)

}

