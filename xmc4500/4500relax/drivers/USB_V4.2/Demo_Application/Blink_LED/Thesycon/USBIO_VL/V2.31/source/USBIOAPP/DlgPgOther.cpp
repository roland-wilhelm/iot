// DlgPgOther.cpp : implementation file
//

#include "stdafx.h"
#include "USBIOAPP.h"
#include "DlgPgOther.h"
#include "DDX_ex.h"
#include "UsbIoPipe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPgOther dialog


CDlgPgOther::CDlgPgOther(CWnd* pParent /*=NULL*/)
  : CDialogPage(CDlgPgOther::IDD, pParent)
{
  m_Index = 0;
}

BOOL CDlgPgOther::OnInitDialog() 
{
  CDialog::OnInitDialog();
  
  m_ComboRecipient.Init(g_RecipientTab);
  m_ComboPower.Init(g_PowerTab);

  // enable tool tips for child controls
  EnableToolTips(TRUE);
  
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPgOther::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPgOther)
	DDX_Control(pDX, IDC_COMBO_POWER, m_ComboPower);
	DDX_Control(pDX, IDC_COMBO_RECIPIENT3, m_ComboRecipient);
	//}}AFX_DATA_MAP

	UINT nIDPrompt = IDS_STRING_INVALID_NUM;
	LPCTSTR format;

	format = _T("0x%02X");

	DDX_TextEx(pDX, IDC_EDIT_INDEX3, format, m_Index, nIDPrompt);

	//DDX_Control(pDX, IDC_BUTTON_GET_STATUS, m_Button_Get_Status);
}


BEGIN_MESSAGE_MAP(CDlgPgOther, CDialog)
  //{{AFX_MSG_MAP(CDlgPgOther)
  ON_BN_CLICKED(IDC_BUTTON_GET_CURRENT_FNB, OnButtonGetCurrentFnb)
  ON_BN_CLICKED(IDC_BUTTON_RESET_DEVICE, OnButtonResetDevice)
  ON_BN_CLICKED(IDC_BUTTON_GET_STATUS, OnButtonGetStatus)
  ON_BN_CLICKED(IDC_BUTTON_TEST1, OnButtonTest1)
  ON_BN_CLICKED(IDC_BUTTON_TEST2, OnButtonTest2)
  ON_BN_CLICKED(IDC_BUTTON_SET_POWER, OnButtonSetPower)
  ON_BN_CLICKED(IDC_BUTTON_GET_POWER, OnButtonGetPower)
  ON_BN_CLICKED(IDC_BUTTON_CYCLE_PORT, OnButtonCyclePort)
  //}}AFX_MSG_MAP
  // tool tips
  ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNeedText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPgOther message handlers

void CDlgPgOther::OnButtonGetCurrentFnb() 
{
  DWORD err;
  DWORD FrameNumber;

  err = g_UsbIo.GetCurrentFrameNumber(FrameNumber);
  if (err) {
    // print error message
    PrintError(err, E_FATAL);
  } else {
    PrintOut("Current Frame Number is 0x%04X."NL,FrameNumber);
  } 
}

void CDlgPgOther::OnButtonResetDevice() 
{
  DWORD err;

  err = g_UsbIo.ResetDevice();
  if (err) {
    // print error message
    PrintError(err, E_FATAL);
  } else {
    PrintOut("Reset Device was successful."NL);
  }
}

void CDlgPgOther::OnButtonCyclePort() 
{
  DWORD err;

  err = g_UsbIo.CyclePort();
  if (err) {
    // print error message
    PrintError(err, E_FATAL);
  } else {
    PrintOut("Cycle Port was successful."NL);
  }
  
}


void CDlgPgOther::OnButtonGetStatus() 
{
  USHORT StatusValue;
  USBIO_REQUEST_RECIPIENT Recipient;
  DWORD err;

  if ( UpdateData(true) ) {
    Recipient=(USBIO_REQUEST_RECIPIENT)m_ComboRecipient.GetCurItemData();
    err = g_UsbIo.GetStatus(StatusValue,
            Recipient,
            (USHORT)m_Index
            );
    if (err != USBIO_ERR_SUCCESS) {
      PrintError(err);
    } else {
      PrintOut("Status: 0x%04X"NL,StatusValue);
    } 
  }
}

void CDlgPgOther::OnButtonSetPower() 
{
  DWORD err;

  if ( UpdateData(true) ) {
    USBIO_DEVICE_POWER_STATE DevicePowerState = (USBIO_DEVICE_POWER_STATE)m_ComboPower.GetCurItemData();
    PrintOut("Setting PowerState %d."NL,DevicePowerState);
    err = g_UsbIo.SetDevicePowerState(DevicePowerState);
    if (err != USBIO_ERR_SUCCESS) {
      PrintError(err);
    } 
  }
}

void CDlgPgOther::OnButtonGetPower() 
{
  DWORD err;

  USBIO_DEVICE_POWER_STATE DevicePowerState;
  err = g_UsbIo.GetDevicePowerState(DevicePowerState);
  if (err != USBIO_ERR_SUCCESS) {
    PrintError(err);
  } else {
    PrintOut("Current Power State is D%d"NL, DevicePowerState);
  } 
  m_ComboPower.SetCurItemData(DevicePowerState);

  UpdateData(false); 
}


void CDlgPgOther::OnButtonTest1() 
{
  // insert a test sequence here
  PrintOut("Insert a test sequence here."NL);
}

void CDlgPgOther::OnButtonTest2() 
{
  // insert a test sequence here
  PrintOut("Insert a test sequence here."NL);
}



const int* 
CDlgPgOther::GetControlIdArray()
{
  static const int ControlIds[] = 
  {
    IDC_BUTTON_RESET_DEVICE,
    IDC_BUTTON_CYCLE_PORT,
    IDC_BUTTON_GET_CURRENT_FNB,
    IDC_BUTTON_SET_POWER,
    IDC_COMBO_RECIPIENT3,
    IDC_EDIT_INDEX3,
    IDC_COMBO_POWER,
    IDC_BUTTON_GET_STATUS,
    IDC_BUTTON_GET_POWER,
    -1 // end marker
  };

  return ControlIds;
}



BOOL CDlgPgOther::OnToolTipNeedText(UINT id, NMHDR* ttt1, LRESULT* pResult )
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

      case IDC_BUTTON_GET_CURRENT_FNB:
        strID = IDS_BUTTON_GET_CURRENT_FNB;
        break;
      case IDC_BUTTON_RESET_DEVICE:
        strID = IDS_BUTTON_RESET_DEVICE;
        break;
      case IDC_BUTTON_CYCLE_PORT:
        strID = IDS_BUTTON_CYCLE_PORT;
        break;
      case IDC_BUTTON_GET_STATUS:
        strID = IDS_BUTTON_GET_STATUS;
        break;
      case IDC_COMBO_RECIPIENT3:
        strID = IDS_COMBO_RECIPIENT3;
        break;
      case IDC_EDIT_INDEX3:
        strID = IDS_EDIT_INDEX3;
        break;
      case IDC_BUTTON_SET_POWER:
        strID = IDS_BUTTON_SET_POWER;
        break;
      case IDC_COMBO_POWER:
        strID = IDS_COMBO_POWER;
        break;
      case IDC_BUTTON_GET_POWER:
        strID = IDS_BUTTON_GET_POWER;
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


