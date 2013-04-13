// DlgPgDevice.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgDevice.h"
#include "DDX_ex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDlgPgDevice dialog


CDlgPgDevice::CDlgPgDevice(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgDevice::IDD, pParent)
{
  //{{AFX_DATA_INIT(CDlgPgDevice)
  m_ResetOnClose = FALSE;
  m_DeviceRequestTimeout = 0;
  m_UnconfigureOnClose = FALSE;
  m_DriverVersionInfo = _T("");
  m_EnableWakeup = FALSE;
	m_DeviceInfo = _T("");
	//}}AFX_DATA_INIT
}

CDlgPgDevice::~CDlgPgDevice()
{
}


BOOL CDlgPgDevice::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
	m_ListBoxDevices.EnableWindow(FALSE);
	m_ButtonOpen.EnableWindow(FALSE);

  // enable tool tips for child controls
  EnableToolTips(TRUE);


  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgPgDevice::UpdateDeviceList(bool PrintInfo /*=false*/)
{
	CString str;
	CString s;
  CUsbIo UsbDev;
  DWORD Status;
	int devcount = 0;
	USB_DEVICE_DESCRIPTOR desc;

  if ( PrintInfo ) {
		PrintOut(NL"Scanning for attached USB devices:" NL NL);
	}

	// clear list box
	m_ListBoxDevices.ResetContent();

  // destroy current device list
  CUsbIo::DestroyDeviceList(g_DevList);
  // create new device list
  g_DevList = CUsbIo::CreateDeviceList(&g_UsbioID);
  if ( g_DevList!=NULL ) {
    // iterate through the list
    for ( int i=0; ; i++ ) {
      Status = UsbDev.GetDeviceInstanceDetails(i,g_DevList,&g_UsbioID);
      if (Status != USBIO_ERR_SUCCESS) {
        // we have reached the end of the list
        break;
      }
			// valid device
			devcount++;
			s = "";
			if ( PrintInfo ) {
				// open the device instance
				Status = UsbDev.Open(i,g_DevList,&g_UsbioID);
				if (Status == USBIO_ERR_SUCCESS) {
					PrintOut("USBIO Device%d: ",i);
					// get device descriptor and print out IDs
					Status = UsbDev.GetDeviceDescriptor(&desc);
					if (Status == USBIO_ERR_SUCCESS) {
						s.Format("VID:0x%04X PID:0x%04X", desc.idVendor, desc.idProduct);
						PrintOut("VendorID:0x%04X  ProductID:0x%04X"NL, desc.idVendor, desc.idProduct);
					} else {
						PrintError(Status, E_ERROR, "GetDeviceDescriptor failed: ");
					}
					UsbDev.Close();
				}
			}
      // add entry to list box
			str.Format("Device%d   %s", i, (const char*)s );
			int index = m_ListBoxDevices.AddString(str);
			if ( index >= 0 ) {
				m_ListBoxDevices.SetItemData(index, i);
			}
    } // for 
  }

	if ( devcount == 0 ) {
		if ( PrintInfo ) {
	    PrintOut("There are no USB devices attached to the USBIO driver."NL);
		}
		str = "No devices";
		m_ListBoxDevices.AddString(str);
		m_ListBoxDevices.EnableWindow(FALSE);
		if ( !g_UsbIo.IsOpen() ) {
			m_ButtonOpen.EnableWindow(FALSE);
	    // update enable/disable state of controls
		  theApp.UpdateStateOfControls();
		}
	} else {
		m_ListBoxDevices.EnableWindow(TRUE);
		if ( !g_UsbIo.IsOpen() ) {
			m_ButtonOpen.EnableWindow(TRUE);
	    // update enable/disable state of controls
		  theApp.UpdateStateOfControls();
		}
		// select first entry
		m_ListBoxDevices.SetCurSel(0);
	}

}//UpdateDeviceList



void CDlgPgDevice::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CDlgPgDevice)
	DDX_Control(pDX, IDC_BUTTON_ACQUIRE, m_ButtonAcquire);
	DDX_Control(pDX, IDC_BUTTON_RELEASE, m_ButtomRelease);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_ButtonOpen);
	DDX_Control(pDX, IDC_LIST_DEVICES, m_ListBoxDevices);
  DDX_Check(pDX, IDC_RESET_ON_CLOSE, m_ResetOnClose);
  DDX_Text(pDX, IDC_DEVICE_REQUEST_TIMEOUT, m_DeviceRequestTimeout);
  DDX_Check(pDX, IDC_UNCONFIGURE_ON_CLOSE, m_UnconfigureOnClose);
  DDX_Text(pDX, IDC_VERSION_INFO, m_DriverVersionInfo);
  DDX_Check(pDX, IDC_ENABLE_WAKEUP, m_EnableWakeup);
	DDX_Text(pDX, IDC_DEVICE_INFO, m_DeviceInfo);
	DDX_Control(pDX, IDC_STATIC_DEV_HL, m_HlStatic);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgPgDevice, CDialog)
  //{{AFX_MSG_MAP(CDlgPgDevice)
  ON_BN_CLICKED(IDC_BUTTON_SCAN, OnButtonScan)
  ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
  ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
  ON_BN_CLICKED(IDC_SET_DEVICE_PARAMETERS, OnSetDeviceParameters)
  ON_BN_CLICKED(IDC_GET_DEVICE_PARAMETER, OnGetDeviceParameter)
	ON_BN_CLICKED(IDC_BUTTON_ACQUIRE, OnButtonAcquire)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, OnButtonRelease)
	//}}AFX_MSG_MAP

  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDlgPgDevice message handlers

void CDlgPgDevice::OnButtonScan() 
{
	// update device list box
	// open each device instance and get device desc
	UpdateDeviceList(true);
}


void CDlgPgDevice::OnButtonOpen() 
{
  DWORD err;
	int DeviceNumber;
  USBIO_DRIVER_INFO DriverInfo;
	USBIO_DEVICE_INFO DeviceInfo;

  if ( !UpdateData(TRUE) ) {
		return;
	}

	if ( g_UsbIo.IsOpen() ) {
    PrintOut("A device is already opened."NL);
		return;
	}

	// get current selection from device list
	int index = m_ListBoxDevices.GetCurSel();
	if ( index >= 0 ) {
		DeviceNumber = m_ListBoxDevices.GetItemData(index);
    // try to open the device
    err = g_UsbIo.Open(DeviceNumber, g_DevList, &g_UsbioID);
    if ( !err ) {       
      // if success: update global var
      g_DeviceNumber = DeviceNumber;
      PrintOut("Device%d successfully opened."NL, DeviceNumber);
			m_ButtonOpen.EnableWindow(FALSE);

      // get current device settings
      OnGetDeviceParameter();
      // get version info
      if ( g_UsbIo.GetDriverInfo(&DriverInfo) ) {
        PrintOut("GetDriverInfo failed."NL);
      } else {
        // set version string
        m_DriverVersionInfo.Format(
          "USBIO Driver Version %d.%02d Build %d (%s), API Version %X.%02X",
          DriverInfo.DriverVersion>>8,
          DriverInfo.DriverVersion&0xff,
          DriverInfo.DriverBuildNumber,
          (DriverInfo.Flags&USBIO_INFOFLAG_CHECKED_BUILD) ? "debug" : "release",
          DriverInfo.APIVersion>>8,
          DriverInfo.APIVersion&0xff
					);
				if ( DriverInfo.Flags&USBIO_INFOFLAG_DEMO_VERSION ) {
					m_DriverVersionInfo += ", demo version";
				} else {
					if ( DriverInfo.Flags&USBIO_INFOFLAG_LIGHT_VERSION ) {
						if ( DriverInfo.Flags&USBIO_INFOFLAG_VS_LIGHT_VERSION ) {
							m_DriverVersionInfo += ", vendor-specific light version";
						} else {
							m_DriverVersionInfo += ", light version";
						}
					}
				}
				m_DeviceInfo = "";
				if ( g_UsbIo.GetDeviceInfo(&DeviceInfo) ) {
					PrintOut("GetDeviceInfo failed."NL);
				} else {	
					if (DeviceInfo.Flags & USBIO_DEVICE_INFOFLAG_HIGH_SPEED) {
						m_DeviceInfo += "High Speed";
					} else {
						m_DeviceInfo += "Low/Full Speed";
					}
				}

        UpdateData(FALSE);
      }
    } else {
      // Open failed
			PrintError(err, E_FATAL);
    }
  
    // update enable/disable state of controls
    theApp.UpdateStateOfControls();

	} else {
		// no selection
		PrintOut("No device selected. Select a device instance to open!."NL);
	}
}



void CDlgPgDevice::OnButtonClose() 
{
  // close device
  g_UsbIo.Close();
  PrintOut("Device%d closed."NL, g_DeviceNumber);

  // update global var
  g_DeviceNumber = -1;
  
  // update enable/disable state of controls
	m_ButtonOpen.EnableWindow(TRUE);
  theApp.UpdateStateOfControls();
}



void CDlgPgDevice::OnSetDeviceParameters() 
{
  DWORD err;
  USBIO_DEVICE_PARAMETERS DevParam;

  if (UpdateData(TRUE)) {
    DevParam.Options=0;
    if (m_ResetOnClose) DevParam.Options|= USBIO_RESET_DEVICE_ON_CLOSE;
    if (m_UnconfigureOnClose) DevParam.Options|= USBIO_UNCONFIGURE_ON_CLOSE;
    if (m_EnableWakeup) DevParam.Options |= USBIO_ENABLE_REMOTE_WAKEUP;
    DevParam.RequestTimeout=m_DeviceRequestTimeout;
    err = g_UsbIo.SetDeviceParameters(&DevParam);
    if (err == USBIO_ERR_SUCCESS) {
      PrintOut("Set new device parameters was successful."NL);
    } else {
      PrintError(err);
    }     
  }
}

void CDlgPgDevice::OnGetDeviceParameter() 
{
  DWORD err;
  USBIO_DEVICE_PARAMETERS DevParam;

  err = g_UsbIo.GetDeviceParameters(&DevParam);
  if (err == USBIO_ERR_SUCCESS) {
    // update display
    m_DeviceRequestTimeout=DevParam.RequestTimeout;

    if (DevParam.Options & USBIO_RESET_DEVICE_ON_CLOSE) m_ResetOnClose=true;
    else m_ResetOnClose=false;
    if (DevParam.Options & USBIO_UNCONFIGURE_ON_CLOSE) m_UnconfigureOnClose=true;
    else m_UnconfigureOnClose=false;
    if (DevParam.Options & USBIO_ENABLE_REMOTE_WAKEUP) m_EnableWakeup=true;
    else m_EnableWakeup=false;
    UpdateData(FALSE);
    PrintOut("Get current device parameters was successful."NL);
  } else {
    PrintError(err);
  } 
}




const int* 
CDlgPgDevice::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_BUTTON_CLOSE,
    IDC_RESET_ON_CLOSE,
    IDC_UNCONFIGURE_ON_CLOSE,
    IDC_ENABLE_WAKEUP,
		IDC_BUTTON_ACQUIRE,
		IDC_BUTTON_RELEASE,
    IDC_DEVICE_REQUEST_TIMEOUT,
    IDC_GET_DEVICE_PARAMETER,
    IDC_SET_DEVICE_PARAMETERS,
    -1 // end marker
  };

  return ControlIds;
}



BOOL CDlgPgDevice::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_BUTTON_OPEN:
        strID = IDS_BUTTON_OPEN;
        break;
      case IDC_BUTTON_SCAN:
        strID = IDS_BUTTON_SCAN;
        break;
      case IDC_BUTTON_CLOSE:
        strID = IDS_BUTTON_CLOSE;
        break;
      case IDC_BUTTON_ACQUIRE:
        strID = IDS_BUTTON_ACQUIRE;
        break;
      case IDC_BUTTON_RELEASE:
        strID = IDS_BUTTON_RELEASE;
        break;
      case IDC_GET_DEVICE_PARAMETER:
        strID = IDS_GET_DEVICE_PARAMETER;
        break;
      case IDC_SET_DEVICE_PARAMETERS:
        strID = IDS_SET_DEVICE_PARAMETER;
        break;
      case IDC_UNCONFIGURE_ON_CLOSE:
        strID = IDS_UNCONFIGURE_ON_CLOSE;
        break;
      case IDC_RESET_ON_CLOSE:
        strID = IDS_RESET_ON_CLOSE;
        break;
      case IDC_ENABLE_WAKEUP:
        strID = IDS_ENABLE_WAKEUP;
        break;
      case IDC_DEVICE_REQUEST_TIMEOUT:
        strID = IDS_DEVICE_REQUEST_TIMEOUT;
        break;
      case IDC_DEVICE_NUMBER:
        strID = IDS_DEVICE_NUMBER;
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


void CDlgPgDevice::OnButtonAcquire() 
{
  DWORD err;

  err = g_UsbIo.AcquireDevice();
  if (err == USBIO_ERR_SUCCESS) {
    PrintOut("Acquire device was successful."NL);
  } else {
    PrintError(err);
  } 	
}

void CDlgPgDevice::OnButtonRelease() 
{
  DWORD err;

  err = g_UsbIo.ReleaseDevice();
  if (err == USBIO_ERR_SUCCESS) {
    PrintOut("Release device was successful."NL);
  } else {
    PrintError(err);
  } 	
	
}
