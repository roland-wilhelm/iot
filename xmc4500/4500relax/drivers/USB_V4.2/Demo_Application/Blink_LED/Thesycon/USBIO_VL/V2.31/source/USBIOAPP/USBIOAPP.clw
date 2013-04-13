; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgPgDevice
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "usbioapp.h"
LastPage=0

ClassCount=23
Class1=CDialogPageCtrl
Class2=CDlgPgConfig
Class3=CDlgPgDesc
Class4=CDlgPgDevice
Class5=CDlgPgDevreq
Class6=CDlgPgFeature
Class7=CDlgPgInterface
Class8=CDlgPgOther
Class9=CDlgPgPipes
Class10=CEnumBox
Class11=CHyperLinkStatic
Class12=COutputWinDlg
Class13=COutputWin
Class14=CPDlgPgBuffer
Class15=CPDlgPgFromFile
Class16=CPDlgPgPipeControl
Class17=CPDlgPgPipeParams
Class18=CPDlgPgToFile
Class19=CPDlgPgToWin
Class20=CPipeDialog
Class21=CUSBIOAPPApp
Class22=CAboutDlg
Class23=CUSBIOAPPDlg

ResourceCount=18
Resource1=IDD_OUTPUT_WINDOW
Resource2=IDD_DIALOGPAGE_INTERFACE
Resource3=IDD_DIALOGPAGE_OTHER
Resource4=IDD_DIALOGPAGE_DEVREQ
Resource5=IDD_DIALOGPAGE_DEVICE
Resource6=IDD_DIALOGPAGE_PIPES
Resource7=IDD_DIALOGPAGE_CONFIG
Resource8=IDD_DIALOGPAGE_FEATURE
Resource9=IDD_DIALOGPAGE_PIPEREQ
Resource10=IDD_PDIALOGPAGE_READTOFILE
Resource11=IDD_DIALOGPAGE_DESC
Resource12=IDD_PDIALOGPAGE_WRITEFROMFILE
Resource13=IDD_PDIALOGPAGE_PIPEPARAMS
Resource14=IDD_PIPE_DIALOG
Resource15=IDD_ABOUTBOX (English (U.S.))
Resource16=IDD_PDIALOGPAGE_READTOWIN
Resource17=IDD_PDIALOGPAGE_BUFFER
Resource18=IDD_USBIOAPP_DIALOG (English (U.S.))

[CLS:CDialogPageCtrl]
Type=0
BaseClass=CTabCtrl
HeaderFile=DialogPageCtrl.h
ImplementationFile=DialogPageCtrl.cpp

[CLS:CDlgPgConfig]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgConfig.h
ImplementationFile=DlgPgConfig.cpp

[CLS:CDlgPgDesc]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgDesc.h
ImplementationFile=DlgPgDesc.cpp
LastObject=IDC_EDIT_OS_CONFIG_DESC

[CLS:CDlgPgDevice]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgDevice.h
ImplementationFile=DlgPgDevice.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_OPEN

[CLS:CDlgPgDevreq]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgDevreq.h
ImplementationFile=DlgPgDevreq.cpp
LastObject=IDC_EDIT_BUFFER
Filter=D
VirtualFilter=dWC

[CLS:CDlgPgFeature]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgFeature.h
ImplementationFile=DlgPgFeature.cpp

[CLS:CDlgPgInterface]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgInterface.h
ImplementationFile=DlgPgInterface.cpp

[CLS:CDlgPgOther]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgOther.h
ImplementationFile=DlgPgOther.cpp

[CLS:CDlgPgPipes]
Type=0
BaseClass=CDialog
HeaderFile=DlgPgPipes.h
ImplementationFile=DlgPgPipes.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgPgPipes

[CLS:CEnumBox]
Type=0
BaseClass=CComboBox
HeaderFile=EnumBox.h
ImplementationFile=EnumBox.cpp

[CLS:CHyperLinkStatic]
Type=0
BaseClass=CStatic
HeaderFile=hlstatic.h
ImplementationFile=hlstatic.cpp

[CLS:COutputWinDlg]
Type=0
BaseClass=CDialog
HeaderFile=OutputWindow.h
ImplementationFile=OutputWindow.cpp

[CLS:COutputWin]
Type=0
BaseClass=CWinThread
HeaderFile=OutputWindow.h
ImplementationFile=OutputWindow.cpp

[CLS:CPDlgPgBuffer]
Type=0
BaseClass=CDialog
HeaderFile=PDlgPgBuffer.h
ImplementationFile=PDlgPgBuffer.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_BUFFER_SET_DEFAULTS

[CLS:CPDlgPgFromFile]
Type=0
BaseClass=CDialog
HeaderFile=PDlgPgFromFile.h
ImplementationFile=PDlgPgFromFile.cpp

[CLS:CPDlgPgPipeControl]
Type=0
BaseClass=CDialog
HeaderFile=PDlgPgPipeControl.h
ImplementationFile=PDlgPgPipeControl.cpp

[CLS:CPDlgPgPipeParams]
Type=0
BaseClass=CDialog
HeaderFile=PDlgPgPipeParams.h
ImplementationFile=PDlgPgPipeParams.cpp

[CLS:CPDlgPgToFile]
Type=0
BaseClass=CDialog
HeaderFile=PDlgPgToFile.h
ImplementationFile=PDlgPgToFile.cpp

[CLS:CPDlgPgToWin]
Type=0
BaseClass=CDialog
HeaderFile=PDlgPgToWin.h
ImplementationFile=PDlgPgToWin.cpp

[CLS:CPipeDialog]
Type=0
BaseClass=CDialog
HeaderFile=PipeDialog.h
ImplementationFile=PipeDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON_RESET_PIPE_STATISTICS

[CLS:CUSBIOAPPApp]
Type=0
BaseClass=CWinApp
HeaderFile=USBIOAPP.h
ImplementationFile=USBIOAPP.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=USBIOAPPDlg.cpp
ImplementationFile=USBIOAPPDlg.cpp

[CLS:CUSBIOAPPDlg]
Type=0
BaseClass=CDialog
HeaderFile=USBIOAPPDlg.h
ImplementationFile=USBIOAPPDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CUSBIOAPPDlg

[DLG:IDD_DIALOGPAGE_CONFIG]
Type=1
Class=CDlgPgConfig
ControlCount=30
Control1=IDC_EDIT_CONFIG_INDEX,edit,1350631554
Control2=IDC_BUTTON_SET_CONFIGURATION,button,1342242816
Control3=IDC_CHECK_IF_0,button,1342242819
Control4=IDC_EDIT_IFNB_0,edit,1350631554
Control5=IDC_EDIT_ASNB_0,edit,1350631554
Control6=IDC_EDIT_MAXTR_0,edit,1350631554
Control7=IDC_CHECK_IF_1,button,1342242819
Control8=IDC_EDIT_IFNB_1,edit,1350631554
Control9=IDC_EDIT_ASNB_1,edit,1350631554
Control10=IDC_EDIT_MAXTR_1,edit,1350631554
Control11=IDC_CHECK_IF_2,button,1342242819
Control12=IDC_EDIT_IFNB_2,edit,1350631554
Control13=IDC_EDIT_ASNB_2,edit,1350631554
Control14=IDC_EDIT_MAXTR_2,edit,1350631554
Control15=IDC_CHECK_IF_3,button,1342242819
Control16=IDC_EDIT_IFNB_3,edit,1350631554
Control17=IDC_EDIT_ASNB_3,edit,1350631554
Control18=IDC_EDIT_MAXTR_3,edit,1350631554
Control19=IDC_BUTTON_GET_CONFIGURATION,button,1342242817
Control20=IDC_BUTTON_UNCONFIGURE_DEVICE,button,1342242816
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,button,1342177287
Control30=IDC_BUTTON_BANDWIDTH,button,1342242816

[DLG:IDD_DIALOGPAGE_DESC]
Type=1
Class=CDlgPgDesc
ControlCount=22
Control1=IDC_BUTTON_DEVICE_DESC,button,1342242817
Control2=IDC_EDIT_CONFIG_DESC,edit,1350631554
Control3=IDC_BUTTON_CONFIG_DESC,button,1342242816
Control4=IDC_EDIT_STRING_DESC,edit,1350631554
Control5=IDC_EDIT_STRING_DESC_LID,edit,1350631554
Control6=IDC_BUTTON_STRING_DESC,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BUTTON_DEVICE_QUALIFIER_DESC,button,1342242816
Control12=IDC_BUTTON_OTHER_SPEED_CONFIG_DESC,button,1342242816
Control13=IDC_EDIT_ANY_DESC_TYPE,edit,1350631554
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_ANY_DESC_INDEX,edit,1350631554
Control17=IDC_STATIC,static,1342308354
Control18=IDC_EDIT_ANY_DESC_LENGTH,edit,1350631554
Control19=IDC_BUTTON_ANY_DESC,button,1342242816
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOGPAGE_DEVICE]
Type=1
Class=CDlgPgDevice
ControlCount=19
Control1=IDC_BUTTON_SCAN,button,1342242816
Control2=IDC_BUTTON_OPEN,button,1342242817
Control3=IDC_BUTTON_CLOSE,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_UNCONFIGURE_ON_CLOSE,button,1342242819
Control7=IDC_RESET_ON_CLOSE,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_DEVICE_REQUEST_TIMEOUT,edit,1350631554
Control10=IDC_GET_DEVICE_PARAMETER,button,1342242816
Control11=IDC_SET_DEVICE_PARAMETERS,button,1342242816
Control12=IDC_STATIC_VERSION,button,1342177287
Control13=IDC_VERSION_INFO,static,1342308352
Control14=IDC_ENABLE_WAKEUP,button,1342242819
Control15=IDC_STATIC_DEV_HL,static,1342308354
Control16=IDC_LIST_DEVICES,listbox,1352728835
Control17=IDC_DEVICE_INFO,static,1342308352
Control18=IDC_BUTTON_ACQUIRE,button,1342242816
Control19=IDC_BUTTON_RELEASE,button,1342242816

[DLG:IDD_DIALOGPAGE_DEVREQ]
Type=1
Class=CDlgPgDevreq
ControlCount=18
Control1=IDC_COMBO_DIRECTION,combobox,1344339970
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_TYPE,combobox,1344339970
Control6=IDC_COMBO_RECIPIENT,combobox,1344339970
Control7=IDC_EDIT_REQUEST,edit,1350631554
Control8=IDC_EDIT_VALUE,edit,1350631554
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_INDEX,edit,1350631554
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_BUFFER,edit,1350631552
Control13=IDC_EDIT_BUFFER_LENGTH,edit,1350631554
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_CHECK_SHORT_OK,button,1342242819
Control18=IDC_BUTTON_SEND_REQUEST,button,1342242817

[DLG:IDD_DIALOGPAGE_FEATURE]
Type=1
Class=CDlgPgFeature
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_RECIPIENT4,combobox,1344339970
Control5=IDC_EDIT_FEATURE_SELECTOR,edit,1350631554
Control6=IDC_EDIT_INDEX4,edit,1350631554
Control7=IDC_SET_FEATURE,button,1342242817
Control8=IDC_CLEAR_FEATURE,button,1342242816

[DLG:IDD_DIALOGPAGE_INTERFACE]
Type=1
Class=CDlgPgInterface
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_IFNB,edit,1350631554
Control6=IDC_EDIT_ASNB,edit,1350631554
Control7=IDC_EDIT_MAXTR,edit,1350631554
Control8=IDC_BUTTON_SET_INTERFACE,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON_GET_INTERFACE,button,1342242817

[DLG:IDD_DIALOGPAGE_OTHER]
Type=1
Class=CDlgPgOther
ControlCount=16
Control1=IDC_BUTTON_GET_CURRENT_FNB,button,1342242817
Control2=IDC_BUTTON_RESET_DEVICE,button,1342242816
Control3=IDC_BUTTON_CYCLE_PORT,button,1342242816
Control4=IDC_BUTTON_GET_STATUS,button,1342242816
Control5=IDC_COMBO_RECIPIENT3,combobox,1344339970
Control6=IDC_EDIT_INDEX3,edit,1350631554
Control7=IDC_BUTTON_SET_POWER,button,1342242816
Control8=IDC_COMBO_POWER,combobox,1344339970
Control9=IDC_BUTTON_GET_POWER,button,1342242816
Control10=IDC_BUTTON_TEST1,button,1208025088
Control11=IDC_BUTTON_TEST2,button,1208025088
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGPAGE_PIPES]
Type=1
Class=CDlgPgPipes
ControlCount=9
Control1=IDC_BUTTON_GET_PIPE_INFO,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC_DEV_NOT_CONFIGURED,static,1342308352
Control5=IDC_LIST_ENDPOINTS,listbox,1352728833
Control6=IDC_BUTTON_OPEN_PIPE_TOWIN,button,1342251008
Control7=IDC_BUTTON_OPEN_PIPE_TOFILE,button,1342251008
Control8=IDC_BUTTON_OPEN_PIPE_FROMFILE,button,1342251008
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_OUTPUT_WINDOW]
Type=1
Class=COutputWinDlg
ControlCount=1
Control1=IDC_EDIT_OUTPUTWIN,edit,1353777348

[DLG:IDD_PDIALOGPAGE_BUFFER]
Type=1
Class=CPDlgPgBuffer
ControlCount=10
Control1=IDC_EDIT_BUF_SIZE,edit,1350631554
Control2=IDC_EDIT_BUF_COUNT,edit,1350631554
Control3=IDC_EDIT_MAX_ERRCOUNT,edit,1350631554
Control4=IDC_EDIT_ISO_PACKET_COUNT,edit,1350631554
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_NB_ISO,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_BUTTON_BUFFER_SET_DEFAULTS,button,1342242816

[DLG:IDD_PDIALOGPAGE_WRITEFROMFILE]
Type=1
Class=CPDlgPgFromFile
ControlCount=14
Control1=IDC_EDIT_SRC_FILE,edit,1350631552
Control2=IDC_BUTTON_SRC_FILE_BROWSE,button,1342242816
Control3=IDC_BUTTON_START_WRITINGFROMFILE,button,1342242817
Control4=IDC_BUTTON_STOP_WRITINGFROMFILE,button,1342242816
Control5=IDC_REWIND,button,1342242819
Control6=IDC_BUTTON_SEND_ZERO_PACKET,button,1342242816
Control7=IDC_EDIT_SAMPLE_RATE,edit,1350631552
Control8=IDC_EDIT_SAMPLE_SIZE,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGPAGE_PIPEREQ]
Type=1
Class=CPDlgPgPipeControl
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PIPE_EDIT_BUFFER,edit,1350631552
Control3=IDC_PIPE_EDIT_BUFFER_LENGTH,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON_PIPE_SEND_REQUEST,button,1342242817
Control6=IDC_PIPE_COMBO_DIRECTION,combobox,1344339970
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PIPE_SETUP,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SHORT_TRANSFER_OK,button,1342242819

[DLG:IDD_PDIALOGPAGE_PIPEPARAMS]
Type=1
Class=CPDlgPgPipeParams
ControlCount=6
Control1=IDC_BUTTON_ABORT_PIPE,button,1342242817
Control2=IDC_BUTTON_RESET_PIPE,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_CHECK_SHORT_OK,button,1342242851
Control5=IDC_BUTTON_GET_PIPE_PARAMS,button,1342242816
Control6=IDC_BUTTON_SET_PIPE_PARAMS,button,1342242816

[DLG:IDD_PDIALOGPAGE_READTOFILE]
Type=1
Class=CPDlgPgToFile
ControlCount=5
Control1=IDC_EDIT_DST_FILE,edit,1350631552
Control2=IDC_BUTTON_DST_FILE_BROWSE,button,1342242816
Control3=IDC_BUTTON_START_READINGTOFILE,button,1342242817
Control4=IDC_BUTTON_STOP_READINGTOFILE,button,1342242816
Control5=IDC_STATIC,button,1342177287

[DLG:IDD_PDIALOGPAGE_READTOWIN]
Type=1
Class=CPDlgPgToWin
ControlCount=3
Control1=IDC_CHECK_PRINT_OUT,button,1342242819
Control2=IDC_BUTTON_START_READINGTOWIN,button,1342242817
Control3=IDC_BUTTON_STOP_READINGTOWIN,button,1342242816

[DLG:IDD_PIPE_DIALOG]
Type=1
Class=CPipeDialog
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDC_TAB_PIPE,SysTabControl32,1342177280
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_STATS_MEAN_RATE,edit,1350568066
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_STATS_BYTES_TRANSFERRED,edit,1350568066
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_STATS_REQ_SUCCEEDED,edit,1350568066
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_STATS_REQ_FAILED,edit,1350568066
Control12=IDC_STATIC,button,1342177287
Control13=IDC_BUTTON_RESET_PIPE_STATISTICS,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_USBIOAPP_DIALOG]
Type=1
Class=CUSBIOAPPDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC_ABOUT_COPYRIGHT,static,1342308481
Control4=IDOK,button,1342373889
Control5=IDC_STATIC_ABOUT_VER,static,1342308481
Control6=IDC_STATIC_ABOUT_HL,static,1342308353

[DLG:IDD_USBIOAPP_DIALOG (English (U.S.))]
Type=1
Class=CUSBIOAPPDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_TAB_MAIN,SysTabControl32,1342177280
Control3=IDC_BUTTON_OUTPUT_WINDOW,button,1342242816
Control4=IDC_BUTTON_CLEAR_OUTPUT_WINDOW,button,1342242816
Control5=IDC_BUTTON_DOCK_OUTPUT_WINDOW,button,1342242816
Control6=IDC_STATIC,button,1342177287

