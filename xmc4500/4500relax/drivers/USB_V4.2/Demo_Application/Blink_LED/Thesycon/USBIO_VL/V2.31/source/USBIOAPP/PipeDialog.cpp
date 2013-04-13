// PipeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "PipeDialog.h"

#include "UsbIoPipe.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define PIPE_DIALOG_STATISTICS_TIMER_ID		0x8827



/////////////////////////////////////////////////////////////////////////////
// CPipeDialog dialog


CPipeDialog::CPipeDialog(CWnd* pParent /*=NULL*/)
  : CDialog(CPipeDialog::IDD, pParent)
{
  //{{AFX_DATA_INIT(CPipeDialog)
  //}}AFX_DATA_INIT

  // init members
  ZeroMemory(&m_PipeInfo,sizeof(m_PipeInfo));

	m_DlgSubKey = NULL;
  m_Pipe = NULL;
  m_Running = FALSE;
	m_StatisticsTimer = 0;

  m_IsoHeaderSize = 0;

  m_SampleRate = 44100;
  m_SampleSize = 2;
  m_EnablePrint = TRUE;
  m_AutoRepeat = TRUE;

  m_SizeOfBuffer = 64;
	m_NumberOfIsoPackets = 32;
  m_NumberOfBuffers = 5;
  m_MaxErrorCount = 5;
}



CPipeDialog::~CPipeDialog()
{

  // remove this dialog from list
  POSITION p = g_PipeDialogList.Find(this);
  if ( p != NULL ) {
    g_PipeDialogList.RemoveAt(p);
  }

  // close the pipe
  if ( m_Pipe != NULL ) {
    m_Pipe->Close();
  }
}



BOOL CPipeDialog::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  // create all dialog page instances
  VERIFY( m_DlgPgPipeParams.Create(this,&m_TabControl) );
  VERIFY( m_DlgPgBuffer.Create(this,&m_TabControl) );
  VERIFY( m_DlgPgPipeControl.Create(this,&m_TabControl) );
  // register our dialog page instances with the tab control
  m_TabControl.AddDialogPage(&m_DlgPgPipeParams,IDS_PDIALOGPAGE_PIPE_PARAMS);
  m_TabControl.AddDialogPage(&m_DlgPgBuffer,IDS_PDIALOGPAGE_BUFFER);
  if ((m_PipeInfo.PipeType & 3) == 0) {
    m_TabControl.AddDialogPage(&m_DlgPgPipeControl,IDS_PDIALOGPAGE_CONTROL);
  }
  m_TabControl.UpdatePageSelection();

  // enable tool tips for child controls
  EnableToolTips(TRUE);
    
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CPipeDialog::OnButtonResetPipeStatistics() 
{
	if ( m_Pipe != NULL ) {
		// reset counters
		m_Pipe->ResetPipeStatistics();
		UpdatePipeStatistics();
	}
}



DWORD CPipeDialog::BindPipe(int DeviceNumber, int EndpointAddress)
{
  USBIO_CONFIGURATION_INFO Info;
  DWORD err;

  err =  m_Pipe->Bind(DeviceNumber,EndpointAddress,g_DevList,&g_UsbioID);
  if ( !err ) {
    // get Pipe Info
    err= g_UsbIo.GetConfigurationInfo(&Info);
    if ( err ) {
      // failed
      // display error
      PrintError(err,E_FATAL);
      m_Pipe->Unbind();
    } else {
    
      // find pipe info
      for (DWORD i=0;i<Info.NbOfPipes;i++) {
        if (Info.PipeInfo[i].EndpointAddress == EndpointAddress) {
          m_PipeInfo = Info.PipeInfo[i]; // struct copy
          break;
        }
      }
			
      m_DlgPgBuffer.m_EditIsoPacketCount.EnableWindow(FALSE);

      // pipe type
      switch ( m_PipeInfo.PipeType ) {
      case PipeTypeControl:
        break;
      case PipeTypeIsochronous:
	      m_DlgPgBuffer.m_EditIsoPacketCount.EnableWindow(TRUE);
        break;
      case PipeTypeBulk:
        break;
      case PipeTypeInterrupt:
        break;
      default:
        PrintOut("FATAL: unknown pipe type: 0x%X."NL, m_PipeInfo.PipeType);
	      m_Pipe->Unbind();
				return USBIO_ERR_FAILED;
			}
			
			// set default buffer parameters
			SetBufferDefaults();
			// load recent parameters from registry
			LoadRecentSettings();
			UpdateAllData(FALSE);

      // set dialog titel
      CString txt;
			txt.Format("USBIOAPP - %s %s Pipe 0x%02X", 
						PipeTypeStr(m_PipeInfo.PipeType), 
						EndpointDirectionStr(EndpointAddress), 
						EndpointAddress
						);
      SetWindowText(txt);
      // set error prefix
      m_PipePrefix.Format("Pipe%02X", EndpointAddress);
      
			// update pipe params
      m_DlgPgPipeParams.DoGetPipeParams();

			// update statistics display
			UpdatePipeStatistics();
    }
  }

  return err;
}



// set default settings
void CPipeDialog::SetBufferDefaults()
{
  // defaults:
	if ( 	g_UsbIo.IsOperatingAtHighSpeed() ) {
		// high speed
	  m_SizeOfBuffer = 512;
		m_NumberOfIsoPackets = 256;
	} else {
		// full speed or low speed
	  m_SizeOfBuffer = 64;
	  m_NumberOfIsoPackets = 32;
	}

  m_NumberOfBuffers = 5;
  m_MaxErrorCount = 5;

  // pipe type
  switch ( m_PipeInfo.PipeType ) {
  case PipeTypeControl:
    break;
  case PipeTypeIsochronous:
		m_SizeOfBuffer = sizeof(USBIO_ISO_TRANSFER) + m_NumberOfIsoPackets * (m_PipeInfo.MaximumPacketSize + sizeof(USBIO_ISO_PACKET));
    break;
  case PipeTypeBulk:
		m_SizeOfBuffer = m_PipeInfo.MaximumTransferSize;
    break;
  case PipeTypeInterrupt:
		m_SizeOfBuffer = m_PipeInfo.MaximumPacketSize;
    break;
  default:
		break;
	}

}//SetBufferDefaults




// load recent settings
void CPipeDialog::LoadRecentSettings() 
{
// helper macros
#define READ_INT(x)	{ m_##x = theApp.GetProfileInt(m_DlgSubKey, #x, m_##x); }
#define READ_STR(x)	{ m_##x = theApp.GetProfileString(m_DlgSubKey, #x, m_##x); }

	if ( m_DlgSubKey != NULL ) {
		READ_INT(SizeOfBuffer)
		READ_INT(NumberOfBuffers)
		READ_INT(MaxErrorCount)
		READ_INT(NumberOfIsoPackets)
		READ_INT(SampleRate)
		READ_INT(SampleSize)
		READ_INT(EnablePrint)
		READ_INT(AutoRepeat)
		READ_STR(FileName)

		// force either 0 or 1
		m_EnablePrint = ( 0 != m_EnablePrint );
		m_AutoRepeat = ( 0 != m_AutoRepeat );
	}

}//LoadRecentSettings


// save recent settings
void CPipeDialog::SaveRecentSettings() 
{
// helper macros
#define WRITE_INT(x)	{ theApp.WriteProfileInt(m_DlgSubKey, #x, m_##x); }
#define WRITE_STR(x)	{ theApp.WriteProfileString(m_DlgSubKey, #x, m_##x); }

	if ( m_DlgSubKey != NULL ) {
		WRITE_INT(SizeOfBuffer)
		WRITE_INT(NumberOfBuffers)
		WRITE_INT(MaxErrorCount)
		WRITE_INT(NumberOfIsoPackets)
		WRITE_INT(SampleRate)
		WRITE_INT(SampleSize)
		WRITE_INT(EnablePrint)
		WRITE_INT(AutoRepeat)
		WRITE_STR(FileName)
	}

}//SaveRecentSettings



// start statistics timer
void CPipeDialog::StartStatisticsTimer() 
{
	StopStatisticsTimer();

	if ( m_Pipe != NULL ) {
		// reset counters
		m_Pipe->ResetPipeStatistics();
		// enable average rate calculation
		m_Pipe->SetupPipeStatistics(MEANRATE_AVERAGING_INTERVAL_MS);
		// start timer
		m_StatisticsTimer = SetTimer(PIPE_DIALOG_STATISTICS_TIMER_ID, STATISTICS_UPDATE_INTERVAL_MS, NULL);
	}

}//StartStatisticsTimer


// stop statistics timer
void CPipeDialog::StopStatisticsTimer() 
{
	if ( m_StatisticsTimer!=0 ) {
		KillTimer(m_StatisticsTimer);
		m_StatisticsTimer = 0;
	}

	if ( m_Pipe != NULL ) {
		// disable average rate calculation
		m_Pipe->SetupPipeStatistics(0);
	}

}//StartStatisticsTimer



// helper function
static
void
FormatNumber(const char* InputStr, char* OutputStr)
{
	char s[100];
	const char* p;
	char* d;
	int cnt;

	// insert dots
	cnt = 0;
	d = s;
	p = InputStr + strlen(InputStr);
	while ( p != InputStr ) {
		*d++ = *(--p);
		cnt++;
		if ( p == InputStr ) {
			break;
		}
		if ( (cnt%3) == 0 ) {
			*d++ = '.';
		}
	}
	*d = 0;

	// reverse string
	d = OutputStr;
	p = s + strlen(s);
	while ( p != s ) {
		*d++ = *(--p);
	}
	*d = 0;
	
}//FormatNumber


// update pipe statistics display
void CPipeDialog::UpdatePipeStatistics()
{
	if ( m_Pipe == NULL ) {
		return;
	}

	USBIO_PIPE_STATISTICS stats;
	DWORD err = m_Pipe->QueryPipeStatistics(&stats);
	if ( err != USBIO_ERR_SUCCESS ) {
		// failed
		return;
	}
	
	char s[100];
	char num[100];

	sprintf(s,"%u",stats.AverageRate);
	FormatNumber(s,num);
	m_EditStatsMeanRate.SetWindowText(num);

	unsigned __int64 n = stats.BytesTransferred_H;
	n <<= 32;
	n += stats.BytesTransferred_L;
	sprintf(s,"%I64u",n);
	FormatNumber(s,num);
	m_EditStatsBytesTransferred.SetWindowText(num);

	sprintf(s,"%u",stats.RequestsSucceeded);
	FormatNumber(s,num);
	m_EditStatsReqSucceeded.SetWindowText(num);

	sprintf(s,"%u",stats.RequestsFailed);
	FormatNumber(s,num);
	m_EditStatsReqFailed.SetWindowText(num);


}//UpdatePipeStatistics




// overload CDialogs DestroyWindow function here
BOOL CPipeDialog::DestroyWindow() 
{
  // call virtual member to notify derived class
  // this will shutdown the worker thread
  OnStop();

	// save parameters 
	SaveRecentSettings();

  // call base class
  return CDialog::DestroyWindow();
}



void CPipeDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPipeDialog)
	DDX_Control(pDX, IDC_EDIT_STATS_BYTES_TRANSFERRED, m_EditStatsBytesTransferred);
	DDX_Control(pDX, IDC_EDIT_STATS_REQ_SUCCEEDED, m_EditStatsReqSucceeded);
	DDX_Control(pDX, IDC_EDIT_STATS_REQ_FAILED, m_EditStatsReqFailed);
	DDX_Control(pDX, IDC_EDIT_STATS_MEAN_RATE, m_EditStatsMeanRate);
  DDX_Control(pDX, IDC_TAB_PIPE, m_TabControl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPipeDialog, CDialog)
  //{{AFX_MSG_MAP(CPipeDialog)
  ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PIPE, OnSelchangeTabPipe)
  ON_MESSAGE(WM_USER_THREAD_TERMINATED, OnMessageThreadExit)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESET_PIPE_STATISTICS, OnButtonResetPipeStatistics)
	//}}AFX_MSG_MAP
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPipeDialog message handlers


void CPipeDialog::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == PIPE_DIALOG_STATISTICS_TIMER_ID ) {
		UpdatePipeStatistics();
	}	
	
	CDialog::OnTimer(nIDEvent);
}




void CPipeDialog::OnOK()
{
  // destroy the window
  DestroyWindow();
}



void CPipeDialog::OnCancel()
{
  // destroy the window
  DestroyWindow();
}


void CPipeDialog::OnDestroy() 
{
	StopStatisticsTimer();
	CDialog::OnDestroy();
}


void CPipeDialog::PostNcDestroy() 
{
  CDialog::PostNcDestroy();

  // delete the dialog object
  delete this;
}



void CPipeDialog::OnSelchangeTabPipe(NMHDR* pNMHDR, LRESULT* pResult) 
{
  // TODO: Add your control notification handler code here

  if ( UpdateAllData(TRUE) ) {
    m_TabControl.UpdatePageSelection();
  }
  
  *pResult = 0;
}


// handler for WM_USER_THREAD_TERMINATED, called in the context of main thread
LONG CPipeDialog::OnMessageThreadExit(UINT, LONG)
{

  m_Running = FALSE;

  // call virtual member function
  OnThreadExitMessage();

  return 0;
}



// notification function, called in the context of worker thread!
void CPipeDialog::OnThreadExit()
{
  // post message, the termination event is handled by the window message-handler
  if ( IsWindow(m_hWnd) )  PostMessage(WM_USER_THREAD_TERMINATED);
}




BOOL CPipeDialog::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
{
  UINT strID = 0;

  TOOLTIPTEXT* ttt = (TOOLTIPTEXT *)ttt1;
  
  if ( ttt->hdr.code==TTN_NEEDTEXT ) {
 
    UINT nID = ttt->hdr.idFrom;
    if ( ttt->uFlags & TTF_IDISHWND ) {
      // idFrom is actually the HWND of the child
      nID = ::GetDlgCtrlID((HWND)nID);
    }

    if( nID!=0 ) {
      // get string resource
      switch ( nID ) {

      case IDC_EDIT_STATS_MEAN_RATE:
        strID = IDS_EDIT_STATS_MEAN_RATE;
        break;
      case IDC_EDIT_STATS_BYTES_TRANSFERRED:
        strID = IDS_EDIT_STATS_BYTES_TRANSFERRED;
        break;
      case IDC_EDIT_STATS_REQ_SUCCEEDED:
        strID = IDS_EDIT_STATS_REQ_SUCCEEDED;
        break;
      case IDC_EDIT_STATS_REQ_FAILED:
        strID = IDS_EDIT_STATS_REQ_FAILED;
        break;

      default:
        break;
      } //switch

      // return ID of string resource
      if ( strID!=0 ) {
        ttt->hinst = AfxGetResourceHandle();
        ttt->lpszText = MAKEINTRESOURCE(strID);
        *pResult = 0;
        return TRUE;
      }
    }
    
  }

  return FALSE;
  
} // OnToolTipNeedText

