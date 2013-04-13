VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form USBIOCOMForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "USBIOCOM Visual Basic Application"
   ClientHeight    =   6015
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   9150
   Icon            =   "usbio.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6015
   ScaleWidth      =   9150
   Begin VB.Frame Frame1 
      Caption         =   "Dummy"
      Enabled         =   0   'False
      Height          =   135
      Index           =   0
      Left            =   9000
      TabIndex        =   187
      Top             =   5520
      Visible         =   0   'False
      Width           =   375
   End
   Begin ComctlLib.TabStrip TabStrip1 
      Height          =   5775
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8895
      _ExtentX        =   15690
      _ExtentY        =   10186
      _Version        =   327682
      BeginProperty Tabs {0713E432-850A-101B-AFC0-4210102A8DA7} 
         NumTabs         =   8
         BeginProperty Tab1 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Device"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Descriptor"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Interface"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab4 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Read"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab5 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Write"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab6 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Feature"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab7 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Class or Vendor Request"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab8 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Other"
            Object.Tag             =   ""
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   4
      Left            =   240
      TabIndex        =   83
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.Frame ReadStatistics 
         Caption         =   "Statistic Information"
         Height          =   3015
         Left            =   5400
         TabIndex        =   194
         Top             =   240
         Width           =   3135
         Begin VB.TextBox ReqFailC 
            Height          =   285
            Left            =   1800
            TabIndex        =   202
            Text            =   "0"
            Top             =   1920
            Width           =   1215
         End
         Begin VB.TextBox ReqSuccC 
            Height          =   285
            Left            =   1800
            TabIndex        =   201
            Text            =   "0"
            Top             =   1440
            Width           =   1215
         End
         Begin VB.TextBox RdTotalBytesC 
            Height          =   285
            Left            =   1800
            TabIndex        =   200
            Text            =   "0"
            Top             =   960
            Width           =   1215
         End
         Begin VB.TextBox RdDataRateC 
            Height          =   285
            Left            =   1800
            TabIndex        =   199
            Text            =   "0"
            Top             =   480
            Width           =   1215
         End
         Begin VB.Label RdReqFailL 
            Caption         =   "Requests failed"
            Height          =   255
            Left            =   120
            TabIndex        =   198
            Top             =   1920
            Width           =   1575
         End
         Begin VB.Label RdRequestsSuccL 
            Caption         =   "Requests succeeded"
            Height          =   255
            Left            =   120
            TabIndex        =   197
            Top             =   1440
            Width           =   1695
         End
         Begin VB.Label RdTotalBytesL 
            Caption         =   "Total Bytes"
            Height          =   255
            Left            =   120
            TabIndex        =   196
            Top             =   960
            Width           =   1335
         End
         Begin VB.Label RdDataRateL 
            Caption         =   "Data Rate"
            Height          =   255
            Left            =   120
            TabIndex        =   195
            Top             =   480
            Width           =   1455
         End
      End
      Begin VB.Timer ReadStTimer 
         Enabled         =   0   'False
         Interval        =   1000
         Left            =   7200
         Top             =   4560
      End
      Begin VB.CheckBox InOutputWindow 
         Caption         =   "Print to Output Window"
         Height          =   255
         Left            =   3120
         TabIndex        =   40
         Top             =   2400
         Width           =   2175
      End
      Begin ComctlLib.ProgressBar ProgressBar1 
         Height          =   255
         Left            =   120
         TabIndex        =   181
         Top             =   3360
         Width           =   8415
         _ExtentX        =   14843
         _ExtentY        =   450
         _Version        =   327682
         Appearance      =   1
         Max             =   1000
      End
      Begin VB.CommandButton showoutputwindow 
         Caption         =   "Output Window"
         Height          =   375
         Left            =   240
         TabIndex        =   44
         Top             =   4680
         Width           =   2055
      End
      Begin VB.CheckBox IsoCheck 
         Caption         =   "ISO"
         Height          =   255
         Left            =   1680
         TabIndex        =   35
         Top             =   960
         Width           =   975
      End
      Begin VB.TextBox StartReadFileField 
         Height          =   285
         Left            =   1680
         TabIndex        =   41
         Text            =   "dump.bin"
         Top             =   2760
         Width           =   2535
      End
      Begin VB.CheckBox StartReadCheck 
         Caption         =   "To File"
         Height          =   255
         Left            =   1680
         TabIndex        =   39
         Top             =   2400
         Value           =   1  'Checked
         Width           =   975
      End
      Begin VB.CommandButton Clear 
         Caption         =   "Clear Output Window"
         Height          =   375
         Left            =   2520
         TabIndex        =   45
         Top             =   4680
         Width           =   2055
      End
      Begin VB.CommandButton StopRead 
         Caption         =   "Stop Reading"
         Height          =   495
         Left            =   2880
         TabIndex        =   43
         Top             =   240
         Width           =   2295
      End
      Begin VB.TextBox ReadBufferSizeField 
         Height          =   285
         Left            =   1680
         Locked          =   -1  'True
         TabIndex        =   84
         TabStop         =   0   'False
         Top             =   4080
         Width           =   735
      End
      Begin VB.TextBox StartReadMaxErrorCountField 
         Height          =   285
         Left            =   1680
         TabIndex        =   38
         Text            =   "5"
         Top             =   2040
         Width           =   975
      End
      Begin VB.TextBox StartReadNumberOfBuffersField 
         Height          =   285
         Left            =   1680
         TabIndex        =   37
         Text            =   "5"
         Top             =   1680
         Width           =   975
      End
      Begin VB.TextBox StartReadBufferSizeField 
         Height          =   285
         Left            =   1680
         TabIndex        =   36
         Text            =   "64"
         Top             =   1320
         Width           =   975
      End
      Begin VB.CommandButton StartRead 
         Caption         =   "Start Reading"
         Height          =   495
         Left            =   240
         TabIndex        =   42
         Top             =   240
         Width           =   2295
      End
      Begin VB.Label Label1 
         Caption         =   "Filename"
         Height          =   255
         Left            =   120
         TabIndex        =   173
         Top             =   2760
         Width           =   1455
      End
      Begin VB.Label ReadBufferSizeLabel 
         Caption         =   "Bytes Returned"
         Height          =   255
         Left            =   120
         TabIndex        =   140
         Top             =   4080
         Width           =   1455
      End
      Begin VB.Label StartReadMaxErrorCountLabel 
         Caption         =   "Max Error Count"
         Height          =   255
         Left            =   120
         TabIndex        =   127
         Top             =   2040
         Width           =   1335
      End
      Begin VB.Label StartReadNumberOfBuffersLabel 
         Caption         =   "Number of Buffers"
         Height          =   255
         Left            =   120
         TabIndex        =   126
         Top             =   1680
         Width           =   1455
      End
      Begin VB.Label StartReadBufferSizeLabel 
         Caption         =   "Buffer Size"
         Height          =   255
         Left            =   120
         TabIndex        =   125
         Top             =   1320
         Width           =   1575
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   8
      Left            =   240
      TabIndex        =   90
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.Frame BWInfo 
         Caption         =   "Bandwidth Information"
         Height          =   975
         Left            =   240
         TabIndex        =   188
         Top             =   3960
         Width           =   8175
         Begin VB.TextBox ConsumedBwEdit 
            Height          =   285
            Left            =   6720
            TabIndex        =   191
            Top             =   360
            Width           =   1215
         End
         Begin VB.TextBox TotalBwEdit 
            Height          =   285
            Left            =   3480
            TabIndex        =   190
            Top             =   360
            Width           =   1215
         End
         Begin VB.CommandButton GetBwInfo 
            Caption         =   "Get"
            Height          =   375
            Left            =   240
            TabIndex        =   189
            Top             =   360
            Width           =   1335
         End
         Begin VB.Label ConsumedBwL 
            Caption         =   "Consumed Bandwidth"
            Height          =   255
            Left            =   4920
            TabIndex        =   193
            Top             =   360
            Width           =   1695
         End
         Begin VB.Label TotalBwL 
            Caption         =   "Total Bandwidth"
            Height          =   255
            Left            =   1920
            TabIndex        =   192
            Top             =   360
            Width           =   1455
         End
      End
      Begin VB.TextBox FrameNumberField 
         Height          =   285
         Left            =   6600
         Locked          =   -1  'True
         TabIndex        =   91
         TabStop         =   0   'False
         Top             =   2400
         Width           =   1575
      End
      Begin VB.CommandButton GetCurrentFrameNumber 
         Caption         =   "Get Frame Number"
         Height          =   375
         Left            =   5760
         TabIndex        =   7
         Top             =   1800
         Width           =   1575
      End
      Begin VB.CommandButton CyclePort 
         Caption         =   "Cycle Port"
         Height          =   375
         Left            =   5760
         TabIndex        =   5
         Top             =   600
         Width           =   1575
      End
      Begin VB.CommandButton ResetDevice 
         Caption         =   "Reset Device"
         Height          =   375
         Left            =   5760
         TabIndex        =   6
         Top             =   1200
         Width           =   1575
      End
      Begin VB.Frame ResetFrame 
         Height          =   2535
         Left            =   5040
         TabIndex        =   141
         Top             =   360
         Width           =   3375
         Begin VB.Label FrameNumberLabel 
            Caption         =   "Frame Number"
            Height          =   255
            Left            =   120
            TabIndex        =   142
            Top             =   2040
            Width           =   1215
         End
      End
      Begin VB.Frame GetStatusFrame 
         Caption         =   "Status"
         Height          =   1215
         Left            =   240
         TabIndex        =   96
         Top             =   360
         Width           =   4575
         Begin VB.ComboBox GetStatusRecipientCombo 
            Height          =   315
            Left            =   3120
            TabIndex        =   2
            Text            =   "Combo5"
            Top             =   240
            Width           =   1335
         End
         Begin VB.TextBox GetStatusField 
            Height          =   285
            Left            =   360
            Locked          =   -1  'True
            TabIndex        =   97
            TabStop         =   0   'False
            Top             =   720
            Width           =   1095
         End
         Begin VB.TextBox GetStatusIndexField 
            Height          =   285
            Left            =   3120
            TabIndex        =   3
            Text            =   "0"
            Top             =   720
            Width           =   855
         End
         Begin VB.CommandButton GetStatus 
            Caption         =   "Get Status"
            Height          =   375
            Left            =   360
            TabIndex        =   4
            Top             =   240
            Width           =   1095
         End
         Begin VB.Label GetStatusIndexLabel 
            Caption         =   "Index"
            Height          =   255
            Left            =   1800
            TabIndex        =   99
            Top             =   720
            Width           =   1215
         End
         Begin VB.Label GetStatusRecipientLabel 
            Caption         =   "Recipient"
            Height          =   255
            Left            =   1800
            TabIndex        =   98
            Top             =   240
            Width           =   1215
         End
      End
      Begin VB.Frame DriverPathNameFrame 
         Caption         =   "Driver Path Name"
         Height          =   855
         Left            =   240
         TabIndex        =   94
         Top             =   3000
         Width           =   8175
         Begin VB.TextBox PathField 
            Height          =   285
            Left            =   1920
            Locked          =   -1  'True
            TabIndex        =   95
            TabStop         =   0   'False
            Top             =   360
            Width           =   6015
         End
         Begin VB.CommandButton GetDevicePathName 
            Caption         =   "Get Path"
            Height          =   375
            Left            =   240
            TabIndex        =   11
            Top             =   360
            Width           =   1335
         End
      End
      Begin VB.Frame PowerStateFrame 
         Caption         =   "Power State"
         Height          =   1215
         Left            =   240
         TabIndex        =   92
         Top             =   1680
         Width           =   4575
         Begin VB.ComboBox SetPowerStateCombo 
            Height          =   315
            Left            =   240
            TabIndex        =   8
            Text            =   "Combo6"
            Top             =   720
            Width           =   1695
         End
         Begin VB.TextBox PowerStateField 
            Height          =   285
            Left            =   2520
            Locked          =   -1  'True
            TabIndex        =   93
            TabStop         =   0   'False
            Top             =   720
            Width           =   1695
         End
         Begin VB.CommandButton GetDevicePowerState 
            Caption         =   "Get Power State"
            Height          =   375
            Left            =   2520
            TabIndex        =   10
            Top             =   240
            Width           =   1695
         End
         Begin VB.CommandButton SetDevicePowerState 
            Caption         =   "Set Power State"
            Height          =   375
            Left            =   240
            TabIndex        =   9
            Top             =   240
            Width           =   1695
         End
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   7
      Left            =   240
      TabIndex        =   100
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.TextBox VendorBuffer 
         Height          =   2205
         Left            =   240
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   185
         Top             =   2880
         Width           =   8175
      End
      Begin VB.TextBox TransferSizeText 
         Height          =   285
         Left            =   5280
         TabIndex        =   18
         Text            =   "0"
         Top             =   1800
         Width           =   1215
      End
      Begin VB.ComboBox Combo4 
         Height          =   315
         Left            =   2040
         TabIndex        =   13
         Text            =   "Combo4"
         Top             =   840
         Width           =   1695
      End
      Begin VB.ComboBox VendorDirectionCombo 
         Height          =   315
         Left            =   2040
         TabIndex        =   12
         Text            =   "Combo3"
         Top             =   360
         Width           =   1695
      End
      Begin VB.CommandButton SendRequest 
         Caption         =   "Send Request"
         Height          =   375
         Left            =   5280
         TabIndex        =   19
         Top             =   2280
         Width           =   1215
      End
      Begin VB.ComboBox Combo2 
         Height          =   315
         Left            =   2040
         TabIndex        =   14
         Text            =   "Combo2"
         Top             =   1320
         Width           =   1695
      End
      Begin VB.TextBox VendoIndexField 
         Height          =   285
         Left            =   5280
         TabIndex        =   17
         Text            =   "0"
         Top             =   1320
         Width           =   1215
      End
      Begin VB.TextBox VendorValueField 
         Height          =   285
         Left            =   5280
         TabIndex        =   16
         Text            =   "0"
         Top             =   840
         Width           =   1215
      End
      Begin VB.TextBox VendorRequestField 
         Height          =   285
         Left            =   5280
         TabIndex        =   15
         Text            =   "0"
         Top             =   360
         Width           =   1215
      End
      Begin VB.Label VendorBufferLabel 
         Caption         =   "Buffer"
         Height          =   255
         Left            =   240
         TabIndex        =   186
         Top             =   2640
         Width           =   1095
      End
      Begin VB.Label TransferSizeLabel 
         Caption         =   "Transfer Size"
         Height          =   255
         Left            =   4200
         TabIndex        =   180
         Top             =   1800
         Width           =   975
      End
      Begin VB.Label VendorIndexLabel 
         Caption         =   "Index"
         Height          =   255
         Left            =   4200
         TabIndex        =   106
         Top             =   1320
         Width           =   855
      End
      Begin VB.Label VendorValueLabel 
         Caption         =   "Value"
         Height          =   255
         Left            =   4200
         TabIndex        =   105
         Top             =   840
         Width           =   855
      End
      Begin VB.Label VendorRequestLabel 
         Caption         =   "Request"
         Height          =   255
         Left            =   4200
         TabIndex        =   104
         Top             =   360
         Width           =   855
      End
      Begin VB.Label VendoRecipientLabel 
         Caption         =   "Recipient"
         Height          =   255
         Left            =   720
         TabIndex        =   103
         Top             =   1320
         Width           =   1215
      End
      Begin VB.Label VendorTypeLabel 
         Caption         =   "Type"
         Height          =   255
         Left            =   720
         TabIndex        =   102
         Top             =   840
         Width           =   1215
      End
      Begin VB.Label VendorDirectionLabel 
         Caption         =   "Direction"
         Height          =   255
         Left            =   720
         TabIndex        =   101
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   5
      Left            =   240
      TabIndex        =   146
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.CheckBox WriteIsoCheck 
         Caption         =   "ISO"
         Height          =   255
         Left            =   1680
         TabIndex        =   25
         Top             =   1080
         Width           =   1095
      End
      Begin VB.CheckBox WriteStatusCheck 
         Caption         =   "Write Status"
         Height          =   255
         Left            =   1680
         TabIndex        =   29
         Top             =   2520
         Width           =   1215
      End
      Begin VB.CheckBox StartWriteCheck 
         Caption         =   "Use File"
         Height          =   255
         Left            =   5640
         TabIndex        =   32
         Top             =   1080
         Width           =   1455
      End
      Begin VB.TextBox SendFileField 
         Height          =   285
         Left            =   6000
         TabIndex        =   31
         Text            =   "dump.bin"
         Top             =   1440
         Width           =   1575
      End
      Begin VB.TextBox DefinedBuffersField 
         Height          =   285
         Left            =   4200
         TabIndex        =   30
         Text            =   "0"
         Top             =   1440
         Width           =   735
      End
      Begin VB.TextBox StartWritingMaxErrorCountField 
         Height          =   285
         Left            =   1680
         TabIndex        =   28
         Text            =   "5"
         Top             =   2160
         Width           =   1095
      End
      Begin VB.TextBox StartWritingNumberOfBuffersField 
         Height          =   285
         Left            =   1680
         TabIndex        =   27
         Text            =   "5"
         Top             =   1800
         Width           =   1095
      End
      Begin VB.TextBox StartWritingBufferSizeField 
         Height          =   285
         Left            =   1680
         TabIndex        =   26
         Text            =   "64"
         Top             =   1440
         Width           =   1095
      End
      Begin VB.CommandButton StartWriting 
         Caption         =   "Start Writing"
         Height          =   495
         Left            =   240
         TabIndex        =   33
         Top             =   360
         Width           =   2295
      End
      Begin VB.CommandButton StopWriting 
         Caption         =   "Stop Writing"
         Height          =   495
         Left            =   2760
         TabIndex        =   34
         Top             =   360
         Width           =   2295
      End
      Begin VB.Label FilledWithLabel 
         Caption         =   "Value"
         Height          =   255
         Left            =   3360
         TabIndex        =   156
         Top             =   1440
         Width           =   735
      End
      Begin VB.Label SendFilenameLabel 
         Caption         =   "File"
         Height          =   255
         Left            =   5640
         TabIndex        =   158
         Top             =   1440
         Width           =   375
      End
      Begin VB.Label DefinedBuffersLabel 
         Caption         =   "Send Test Pattern"
         Height          =   255
         Left            =   3360
         TabIndex        =   157
         Top             =   1080
         Width           =   1575
      End
      Begin VB.Label StartWritingMaxErrorCountLabel 
         Caption         =   "Max Error Count"
         Height          =   255
         Left            =   120
         TabIndex        =   149
         Top             =   2160
         Width           =   1335
      End
      Begin VB.Label StartWritingNumerOfBuffersLabel 
         Caption         =   "Number of Buffers"
         Height          =   255
         Left            =   120
         TabIndex        =   148
         Top             =   1800
         Width           =   1335
      End
      Begin VB.Label StartWritingBufferSizeLabel 
         Caption         =   "Buffer Size"
         Height          =   255
         Left            =   120
         TabIndex        =   147
         Top             =   1440
         Width           =   1575
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   6
      Left            =   240
      TabIndex        =   87
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.CommandButton ClearFeature 
         Caption         =   "Clear Feature"
         Height          =   375
         Left            =   3600
         TabIndex        =   24
         Top             =   2640
         Width           =   2055
      End
      Begin VB.CommandButton SetFeature 
         Caption         =   "Set Feature"
         Height          =   375
         Left            =   720
         TabIndex        =   23
         Top             =   2640
         Width           =   2055
      End
      Begin VB.ComboBox Combo1 
         Height          =   315
         Left            =   2520
         TabIndex        =   20
         Top             =   840
         Width           =   1695
      End
      Begin VB.TextBox FeatureIndexField 
         Height          =   285
         Left            =   2520
         TabIndex        =   22
         Text            =   "0"
         Top             =   1680
         Width           =   1695
      End
      Begin VB.TextBox FeatureField 
         Height          =   285
         Left            =   2520
         TabIndex        =   21
         Text            =   "0"
         Top             =   1320
         Width           =   1695
      End
      Begin VB.Label FeatureRecipientLabel 
         Caption         =   "Recipient"
         Height          =   255
         Left            =   1320
         TabIndex        =   128
         Top             =   840
         Width           =   1095
      End
      Begin VB.Label FeatureIndexLabel 
         Caption         =   "Index"
         Height          =   255
         Left            =   1320
         TabIndex        =   89
         Top             =   1680
         Width           =   975
      End
      Begin VB.Label FeatureLabel 
         Caption         =   "Feature"
         Height          =   255
         Left            =   1320
         TabIndex        =   88
         Top             =   1320
         Width           =   975
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   3
      Left            =   240
      TabIndex        =   82
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.Frame SetInterfaceFrame 
         Caption         =   "Set Interface"
         Height          =   2055
         Left            =   3480
         TabIndex        =   150
         Top             =   3120
         Width           =   3135
         Begin VB.TextBox SetInterfaceMaxTransferSizeField 
            Height          =   285
            Left            =   2280
            TabIndex        =   66
            Text            =   "4096"
            Top             =   1080
            Width           =   735
         End
         Begin VB.TextBox SetInterfaceAlternateSettingField 
            Height          =   285
            Left            =   2280
            TabIndex        =   65
            Text            =   "0"
            Top             =   720
            Width           =   735
         End
         Begin VB.TextBox SetInterfaceIndexField 
            Height          =   285
            Left            =   2280
            TabIndex        =   64
            Text            =   "0"
            Top             =   360
            Width           =   735
         End
         Begin VB.CommandButton SetInterface 
            Caption         =   "Set Interface"
            Height          =   375
            Left            =   1080
            TabIndex        =   67
            Top             =   1560
            Width           =   1215
         End
         Begin VB.Label SetInterfaceMaxTransferSizeLabel 
            Caption         =   "Maximum Transfer Size"
            Height          =   255
            Left            =   240
            TabIndex        =   153
            Top             =   1080
            Width           =   1695
         End
         Begin VB.Label SetInterfaceAlternateSettingLabel 
            Caption         =   "Alternate Setting Index"
            Height          =   255
            Left            =   240
            TabIndex        =   152
            Top             =   720
            Width           =   1815
         End
         Begin VB.Label SetInterfaceIndexLabel 
            Caption         =   "Interface Index"
            Height          =   255
            Left            =   240
            TabIndex        =   151
            Top             =   360
            Width           =   1455
         End
      End
      Begin VB.TextBox EndpointAddressDecField 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1031
            SubFormatType   =   1
         EndProperty
         Height          =   285
         Left            =   6960
         TabIndex        =   55
         Text            =   "129"
         Top             =   1320
         Width           =   615
      End
      Begin VB.CommandButton Unbind 
         Caption         =   "Unbind"
         Height          =   375
         Left            =   7080
         TabIndex        =   58
         Top             =   2160
         Width           =   1095
      End
      Begin VB.CommandButton Bind 
         Caption         =   "Bind"
         Height          =   375
         Left            =   7080
         TabIndex        =   57
         Top             =   600
         Width           =   1095
      End
      Begin VB.Frame PipesFrame 
         Caption         =   "Pipes"
         Height          =   4935
         Left            =   6720
         TabIndex        =   138
         Top             =   240
         Width           =   1815
         Begin VB.CommandButton GetShortTransfer 
            Caption         =   "Get Short Transfer"
            Height          =   375
            Left            =   120
            TabIndex        =   63
            Top             =   4320
            Width           =   1575
         End
         Begin VB.CommandButton SetShortTransfer 
            Caption         =   "Set Short Transfer"
            Height          =   375
            Left            =   120
            TabIndex        =   61
            Top             =   3480
            Width           =   1575
         End
         Begin VB.CheckBox ShortTransferCheck 
            Caption         =   "Short Transfer OK"
            Height          =   255
            Left            =   120
            TabIndex        =   62
            Top             =   3960
            Value           =   1  'Checked
            Width           =   1575
         End
         Begin VB.CommandButton AbortPipe 
            Caption         =   "Abort Pipe"
            Height          =   375
            Left            =   360
            TabIndex        =   60
            Top             =   2880
            Width           =   1095
         End
         Begin VB.CommandButton ResetPipe 
            Caption         =   "Reset Pipe"
            Height          =   375
            Left            =   360
            TabIndex        =   59
            Top             =   2400
            Width           =   1095
         End
         Begin VB.TextBox EndpointAddressHexField 
            Height          =   285
            Left            =   240
            MaxLength       =   4
            TabIndex        =   56
            Top             =   1440
            Width           =   615
         End
         Begin VB.Label EndpointAddressHexLabel 
            Caption         =   "Hex"
            Height          =   255
            Left            =   960
            TabIndex        =   144
            Top             =   1440
            Width           =   375
         End
         Begin VB.Label EndpointAddressDecLabel 
            Caption         =   "Dec"
            Height          =   255
            Left            =   960
            TabIndex        =   143
            Top             =   1080
            Width           =   375
         End
         Begin VB.Label EndpointAddressLabel 
            Caption         =   "Endpoint Address"
            Height          =   255
            Left            =   240
            TabIndex        =   139
            Top             =   840
            Width           =   1335
         End
      End
      Begin VB.CommandButton UnconfigureDevice 
         Caption         =   "Unconfigure Device"
         Height          =   375
         Left            =   4440
         TabIndex        =   54
         Top             =   2520
         Width           =   1575
      End
      Begin VB.TextBox GetConfigurationField 
         Height          =   285
         Left            =   4680
         Locked          =   -1  'True
         TabIndex        =   85
         TabStop         =   0   'False
         Top             =   2040
         Width           =   975
      End
      Begin VB.CommandButton GetConfiguration 
         Caption         =   "Get Configuration"
         Height          =   375
         Left            =   4440
         TabIndex        =   53
         Top             =   1560
         Width           =   1575
      End
      Begin VB.TextBox SetConfigurationIndexField 
         Height          =   285
         Left            =   5520
         TabIndex        =   51
         Text            =   "0"
         Top             =   1080
         Width           =   975
      End
      Begin VB.CommandButton SetConfiguration 
         Caption         =   "Set Configuration"
         Height          =   375
         Left            =   4440
         TabIndex        =   52
         Top             =   600
         Width           =   1575
      End
      Begin VB.Frame ConfigurationFrame 
         Caption         =   "Configuration"
         Height          =   2775
         Left            =   3840
         TabIndex        =   136
         Top             =   240
         Width           =   2775
         Begin VB.Label SetConfigurationIndexLabel 
            Caption         =   "Configuration Index"
            Height          =   255
            Left            =   240
            TabIndex        =   137
            Top             =   840
            Width           =   1455
         End
      End
      Begin VB.CommandButton DeleteInterfaces 
         Caption         =   "Delete Interfaces"
         Height          =   375
         Left            =   840
         TabIndex        =   50
         Top             =   2520
         Width           =   1575
      End
      Begin VB.CommandButton AddInterface 
         Caption         =   "Add Interface"
         Height          =   375
         Left            =   840
         TabIndex        =   49
         Top             =   600
         Width           =   1575
      End
      Begin VB.TextBox AddInterfaceMaxTransferSizeField 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1031
            SubFormatType   =   1
         EndProperty
         Height          =   285
         Left            =   2400
         TabIndex        =   48
         Text            =   "64000"
         Top             =   2040
         Width           =   975
      End
      Begin VB.TextBox AddInterfaceAlternateSettingField 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1031
            SubFormatType   =   1
         EndProperty
         Height          =   285
         Left            =   2400
         TabIndex        =   47
         Text            =   "0"
         Top             =   1560
         Width           =   975
      End
      Begin VB.TextBox AddInterfaceIndexField 
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1031
            SubFormatType   =   1
         EndProperty
         Height          =   285
         Left            =   2400
         TabIndex        =   46
         Text            =   "0"
         Top             =   1080
         Width           =   975
      End
      Begin VB.Frame InterfaceFrame 
         Caption         =   "Interfaces"
         Height          =   2775
         Left            =   120
         TabIndex        =   132
         Top             =   240
         Width           =   3615
         Begin VB.Label AddInterfaceMaxTransferSizeLabel 
            Caption         =   "Maximum Transfer Size"
            Height          =   255
            Left            =   360
            TabIndex        =   135
            Top             =   1800
            Width           =   1695
         End
         Begin VB.Label AddInterfaceAlternateSettingLabel 
            Caption         =   "Alternate Setting Index"
            Height          =   255
            Left            =   360
            TabIndex        =   134
            Top             =   1320
            Width           =   1695
         End
         Begin VB.Label AddInterfaceIndexLabel 
            Caption         =   "Interface Index"
            Height          =   255
            Left            =   360
            TabIndex        =   133
            Top             =   840
            Width           =   1695
         End
      End
      Begin VB.CommandButton GetInterface 
         Caption         =   "Get Interface"
         Height          =   375
         Left            =   840
         TabIndex        =   69
         Top             =   3480
         Width           =   1575
      End
      Begin VB.TextBox GetInterfaceAlternateSettingField 
         Height          =   285
         Left            =   2160
         Locked          =   -1  'True
         TabIndex        =   86
         TabStop         =   0   'False
         Top             =   4560
         Width           =   975
      End
      Begin VB.TextBox GetInterfaceIndexField 
         Height          =   285
         Left            =   2160
         TabIndex        =   68
         Text            =   "0"
         Top             =   4080
         Width           =   975
      End
      Begin VB.Frame GetInterfaceFrame 
         Caption         =   "Get Interface"
         Height          =   2055
         Left            =   120
         TabIndex        =   129
         Top             =   3120
         Width           =   3255
         Begin VB.Label GetInterfaceAlternateSettingLabel 
            Caption         =   "Alternate Setting Index"
            Height          =   255
            Left            =   240
            TabIndex        =   131
            Top             =   1440
            Width           =   1695
         End
         Begin VB.Label GetInterfaceIndexLabel 
            Caption         =   "Interface Index"
            Height          =   255
            Left            =   240
            TabIndex        =   130
            Top             =   960
            Width           =   1575
         End
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   2
      Left            =   240
      TabIndex        =   79
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.TextBox MaxDescSizeText 
         Height          =   285
         Left            =   7800
         TabIndex        =   72
         Text            =   "4096"
         Top             =   1440
         Width           =   735
      End
      Begin VB.TextBox DescriptorField 
         Height          =   4935
         Left            =   240
         Locked          =   -1  'True
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   176
         TabStop         =   0   'False
         Top             =   240
         Width           =   5895
      End
      Begin VB.TextBox DescriptorIndexField 
         Height          =   285
         Left            =   7800
         TabIndex        =   71
         Text            =   "0"
         Top             =   1080
         Width           =   735
      End
      Begin VB.TextBox DescriptorTypeField 
         Height          =   285
         Left            =   7800
         TabIndex        =   70
         Text            =   "1"
         Top             =   720
         Width           =   735
      End
      Begin VB.TextBox GetStringDescriptorIndexField 
         Height          =   285
         Left            =   7560
         TabIndex        =   76
         Text            =   "1"
         Top             =   3240
         Width           =   735
      End
      Begin VB.CommandButton ClearAll 
         Caption         =   "Clear All"
         Height          =   375
         Left            =   6600
         TabIndex        =   124
         Top             =   4680
         Width           =   1095
      End
      Begin VB.CommandButton GetDeviceDescriptor 
         Caption         =   "Get Device Descriptor"
         Height          =   375
         Left            =   6240
         TabIndex        =   75
         Top             =   2280
         Width           =   2295
      End
      Begin VB.CommandButton GetConfigurationDescriptor 
         Caption         =   "Get Configuration Descriptor"
         Height          =   375
         Left            =   6240
         TabIndex        =   74
         Top             =   1800
         Width           =   2295
      End
      Begin VB.TextBox GetStringDescriptorTypeField 
         Height          =   285
         Left            =   7560
         Locked          =   -1  'True
         TabIndex        =   81
         TabStop         =   0   'False
         Top             =   3960
         Width           =   735
      End
      Begin VB.TextBox GetStringDescriptorLengthField 
         Height          =   285
         Left            =   7560
         Locked          =   -1  'True
         TabIndex        =   78
         TabStop         =   0   'False
         Top             =   3600
         Width           =   735
      End
      Begin VB.TextBox GetStringDescriptorField 
         Height          =   285
         Left            =   6600
         Locked          =   -1  'True
         TabIndex        =   80
         TabStop         =   0   'False
         Top             =   4320
         Width           =   1695
      End
      Begin VB.CommandButton GetStringDescriptor 
         Caption         =   "Get String Descriptor"
         Height          =   375
         Left            =   6240
         TabIndex        =   77
         Top             =   2760
         Width           =   2295
      End
      Begin VB.CommandButton GetDescriptor 
         Caption         =   "Get Descriptor"
         Height          =   375
         Left            =   6240
         TabIndex        =   73
         Top             =   240
         Width           =   2295
      End
      Begin VB.Label MaxDescSize 
         Caption         =   "Descriptor Size"
         Height          =   255
         Left            =   6360
         TabIndex        =   179
         Top             =   1440
         Width           =   1455
      End
      Begin VB.Label StringTypeLabel 
         Caption         =   "Type"
         Height          =   255
         Left            =   6720
         TabIndex        =   178
         Top             =   3960
         Width           =   735
      End
      Begin VB.Label StringLengthLabel 
         Caption         =   "Length"
         Height          =   255
         Left            =   6720
         TabIndex        =   177
         Top             =   3600
         Width           =   735
      End
      Begin VB.Label DescriptorIndexLabel 
         Caption         =   "Descriptor Index"
         Height          =   255
         Left            =   6360
         TabIndex        =   175
         Top             =   1080
         Width           =   1335
      End
      Begin VB.Label DescriptorTypeLabel 
         Caption         =   "Descriptor Type"
         Height          =   255
         Left            =   6360
         TabIndex        =   174
         Top             =   720
         Width           =   1335
      End
      Begin VB.Label GetStringDescriptorIndexLabel 
         Caption         =   "Index"
         Height          =   255
         Left            =   6720
         TabIndex        =   145
         Top             =   3240
         Width           =   735
      End
   End
   Begin VB.Frame Frame1 
      Height          =   5295
      Index           =   1
      Left            =   240
      TabIndex        =   1
      Top             =   480
      Visible         =   0   'False
      Width           =   8655
      Begin VB.Frame PnPNotificationBox 
         Caption         =   "PnP Notification"
         Height          =   1575
         Left            =   6240
         TabIndex        =   182
         Top             =   2040
         Width           =   2055
         Begin VB.CommandButton DisablePnPNotificationButton 
            Caption         =   "Disable PnP Notification"
            Height          =   495
            Left            =   360
            TabIndex        =   184
            Top             =   960
            Width           =   1455
         End
         Begin VB.CommandButton EnablePnPNotificationButton 
            Caption         =   "Enable PnP Notification"
            Height          =   495
            Left            =   360
            TabIndex        =   183
            Top             =   360
            Width           =   1455
         End
      End
      Begin VB.Frame DeviceOptionFrame 
         Caption         =   "Device Options"
         Height          =   1455
         Left            =   4440
         TabIndex        =   164
         Top             =   3720
         Width           =   3855
         Begin VB.TextBox SetDeviceOptionsField 
            Height          =   285
            Left            =   2640
            TabIndex        =   166
            Text            =   "6"
            Top             =   960
            Width           =   615
         End
         Begin VB.TextBox GetDeviceOptionsField 
            Height          =   285
            Left            =   720
            Locked          =   -1  'True
            TabIndex        =   168
            TabStop         =   0   'False
            Top             =   960
            Width           =   615
         End
         Begin VB.CommandButton SetDeviceOptions 
            Caption         =   "Set Device Options"
            Height          =   375
            Left            =   2040
            TabIndex        =   167
            Top             =   360
            Width           =   1695
         End
         Begin VB.CommandButton GetDeviceOptions 
            Caption         =   "Get Device Options"
            Height          =   375
            Left            =   120
            TabIndex        =   165
            Top             =   360
            Width           =   1695
         End
      End
      Begin VB.Frame RequestTimeoutFrame 
         Caption         =   "Request Timeout"
         Height          =   1455
         Left            =   240
         TabIndex        =   159
         Top             =   3720
         Width           =   4095
         Begin VB.TextBox SetRequestTimeoutField 
            Height          =   285
            Left            =   2760
            TabIndex        =   162
            Text            =   "1000"
            Top             =   960
            Width           =   615
         End
         Begin VB.CommandButton SetRequestTimeout 
            Caption         =   "Set Request Timeout"
            Height          =   375
            Left            =   2160
            TabIndex        =   163
            Top             =   360
            Width           =   1815
         End
         Begin VB.TextBox GetRequestTimeoutField 
            Height          =   285
            Left            =   720
            Locked          =   -1  'True
            TabIndex        =   161
            TabStop         =   0   'False
            Top             =   960
            Width           =   615
         End
         Begin VB.CommandButton GetRequestTimeout 
            Caption         =   "Get Request Timeout"
            Height          =   375
            Left            =   120
            TabIndex        =   160
            Top             =   360
            Width           =   1815
         End
      End
      Begin VB.Frame VersionFrame 
         Caption         =   "Version"
         Height          =   1575
         Left            =   240
         TabIndex        =   114
         Top             =   2040
         Width           =   5775
         Begin VB.TextBox CheckedBuildVersionField 
            Height          =   285
            Left            =   4920
            Locked          =   -1  'True
            TabIndex        =   170
            TabStop         =   0   'False
            Top             =   1080
            Width           =   615
         End
         Begin VB.TextBox DemoVersionField 
            Height          =   285
            Left            =   2520
            Locked          =   -1  'True
            TabIndex        =   169
            TabStop         =   0   'False
            Top             =   1080
            Width           =   615
         End
         Begin VB.TextBox FlagsField 
            Height          =   285
            Left            =   4920
            Locked          =   -1  'True
            TabIndex        =   119
            TabStop         =   0   'False
            Top             =   720
            Width           =   615
         End
         Begin VB.TextBox DriverBuildNumberField 
            Height          =   285
            Left            =   4920
            Locked          =   -1  'True
            TabIndex        =   118
            TabStop         =   0   'False
            Top             =   360
            Width           =   615
         End
         Begin VB.TextBox DriverVersionField 
            Height          =   285
            Left            =   2520
            Locked          =   -1  'True
            TabIndex        =   117
            TabStop         =   0   'False
            Top             =   720
            Width           =   615
         End
         Begin VB.TextBox APIVersionField 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "9.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1031
               SubFormatType   =   0
            EndProperty
            Height          =   285
            Left            =   2520
            Locked          =   -1  'True
            TabIndex        =   116
            TabStop         =   0   'False
            Top             =   360
            Width           =   615
         End
         Begin VB.CommandButton GetVersion 
            Caption         =   "Get Version"
            Height          =   495
            Left            =   120
            TabIndex        =   115
            Top             =   360
            Width           =   1095
         End
         Begin VB.Label CheckedBuildVersionLabe 
            Caption         =   "Checked Build"
            Height          =   255
            Left            =   3360
            TabIndex        =   172
            Top             =   1080
            Width           =   1455
         End
         Begin VB.Label DemoVersionLabel 
            Caption         =   "Demo Version"
            Height          =   255
            Left            =   1320
            TabIndex        =   171
            Top             =   1080
            Width           =   1095
         End
         Begin VB.Label DriverBuildNumberLabel 
            Caption         =   "Driver Build Number"
            Height          =   255
            Left            =   3360
            TabIndex        =   123
            Top             =   360
            Width           =   1455
         End
         Begin VB.Label FlagsLabel 
            Caption         =   "Flags"
            Height          =   255
            Left            =   3360
            TabIndex        =   122
            Top             =   720
            Width           =   975
         End
         Begin VB.Label DriverVersionLabel 
            Caption         =   "Driver Version"
            Height          =   255
            Left            =   1320
            TabIndex        =   121
            Top             =   720
            Width           =   1095
         End
         Begin VB.Label APIVersionLabel 
            Caption         =   "API Version"
            Height          =   255
            Left            =   1320
            TabIndex        =   120
            Top             =   360
            Width           =   1095
         End
      End
      Begin VB.Frame DevicesFrame 
         Caption         =   "Devices"
         Height          =   1575
         Left            =   2760
         TabIndex        =   113
         Top             =   360
         Width           =   5535
         Begin VB.CommandButton ReleaseButton 
            Caption         =   "Release"
            Height          =   495
            Left            =   3480
            TabIndex        =   204
            Top             =   960
            Width           =   1815
         End
         Begin VB.CommandButton AcquireButton 
            Caption         =   "Acquire"
            Height          =   495
            Left            =   3480
            TabIndex        =   203
            Top             =   360
            Width           =   1815
         End
         Begin VB.TextBox DeviceInstanceField 
            Height          =   285
            Left            =   2640
            MaxLength       =   3
            TabIndex        =   110
            Text            =   "0"
            Top             =   480
            Width           =   375
         End
         Begin VB.CommandButton OpenDevice 
            Caption         =   "Open Device"
            Height          =   495
            Left            =   120
            TabIndex        =   111
            Top             =   360
            Width           =   975
         End
         Begin VB.CommandButton CloseDevice 
            Caption         =   "Close Device"
            Height          =   495
            Left            =   120
            TabIndex        =   112
            Top             =   960
            Width           =   975
         End
         Begin VB.Label DeviceInstanceLabel 
            Caption         =   "Device Instance"
            Height          =   255
            Left            =   1200
            TabIndex        =   155
            Top             =   480
            Width           =   1335
         End
      End
      Begin VB.Frame EnumerateFrame 
         Caption         =   "Enumerate"
         Height          =   1575
         Left            =   240
         TabIndex        =   107
         Top             =   360
         Width           =   2415
         Begin VB.CommandButton NumberOfDevices 
            Caption         =   "Enumerate Devices"
            Height          =   495
            Left            =   360
            TabIndex        =   109
            Top             =   360
            Width           =   1695
         End
         Begin VB.TextBox NumberOfDevicesField 
            Height          =   285
            Left            =   1800
            Locked          =   -1  'True
            TabIndex        =   108
            TabStop         =   0   'False
            Top             =   1080
            Width           =   375
         End
         Begin VB.Label NumberOfDevicesLabel 
            Caption         =   "Number of Devices"
            Height          =   255
            Left            =   240
            TabIndex        =   154
            Top             =   1080
            Width           =   1455
         End
      End
   End
End
Attribute VB_Name = "USBIOCOMForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'(c) 2001-2002 Thesycon Systemsoftware & Consulting GmbH
'
'This is a sample program for the USBIOCOM interface. It
'requires the registered USBIOCOM interface and the USBIO
'device driver. Furthermore, an USB test device is required.
'
'An USB mouse or keyboard can be used as test device for example.
'Note: The test device cannot be used as a Windows input device at the same time.
'
'For detailed information on the USBIOCOM interface refer to the
'documentation in usbiocom.pdf. For information on the USBIO
'device driver an its API refer to usbioman.pdf.
'
'For latest updates visit http://www.thesycon.de
'
'
'How to use this sample application:
'1. Connect an USB device with at least one IN endpoint to the PC.
'
'2. Use the USBIO install wizard to install the USBIO device driver
'for this device.
'
'3. Make sure that the USBIOCOM interface is registered on the PC.
'Normally, this is done during installation. You can run the command
'>regsvr32 usbiocom.dll
'to register the USBIOCOM interface manually.
'
'4. Run this application and carry out the following actions:
'a) press "Number of Devices" ->  Number of devices should be at least 1
'b) press "Open Device"
'c) switch to the "Interface" page
'd) enter interface and alternate setting, press "Add Interface"
'e) press "Set Configuration"
'f) enter the endpoint address, add 128 (80 hex) for IN endpoints
'g) press "Bind"
'h) switch to the "Read" page
'i) press "Start Read"
'j) press keys on the keyboard or move the mouse
'k) press "Stop Read", the file should contain the received data
'
'


' We define global variables that hold the instances of the USBIO COM object.
' We need to use the "WithEvents" attribute.

' This one represents the USB device.
Dim WithEvents USBDevice As USBIOCOMLib.USBIOInterface3
Attribute USBDevice.VB_VarHelpID = -1

' This one represents a data pipe (USB endpoint).
' Note: To keep it simple we use one data pipe only.
' However, if more that one endpoint shall be used then one instance
' is required for each of them.
Dim WithEvents USBPipe As USBIOCOMLib.USBIOInterface3
Attribute USBPipe.VB_VarHelpID = -1

' The USBIOCOM_ERR_CODES enum is defined in the USBIOCOM Type Library.
Dim status As USBIOCOMLib.USBIOCOM_ERR_CODES

'define an array of bytes used for read and write operations
Dim buffer() As Byte
Dim intbuffer() As Long
Dim intbuffer2() As Long
Dim buf() As Byte

Dim mintCurFrame As Integer

Dim fileopen As Boolean

Dim tempbuf(7) As Byte
Dim UserId As Long
Dim writing As Boolean
Dim reading As Boolean
Dim BufferSize As Long
Dim BufferCount As Long
Dim ErrorCount As Long
Dim IsIsoFlag As Boolean
Dim WriteToFile As Boolean
Dim fifosize As Long
Dim wBufferSize As Long
Dim wBufferCount As Long
Dim wErrorCount As Long
Dim wIsIsoFlag As Boolean
Dim ReadFromFile As Boolean
Dim wBufferValue As Long
Dim WriteStatus As Boolean



' *****************************************************
' Enumeration Page
' *****************************************************

'enumerate devices
Private Sub NumberOfDevices_Click()
    'number of devices, -1 in case of an error
    Dim Devices As Long
    ' Enumerate the available devices.
    ' We use the USBIO default GUID here.
    ' In production-level code a custom GUID should be used which is defined in usbio.inf.
    USBDevice.EnumerateDevices "{325ddf96-938c-11d3-9e34-0080c82727f4}", Devices
    NumberOfDevicesField.Text = Devices
End Sub

'open device
Private Sub OpenDevice_Click()
    USBDevice.OpenDevice Val(DeviceInstanceField.Text), status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        USBPipe.OpenDevice Val(DeviceInstanceField.Text), status
        Call error(status)
    End If
End Sub

'close device
Private Sub CloseDevice_Click()
    USBDevice.CloseDevice
    USBPipe.CloseDevice
End Sub

'get driver information
Private Sub GetVersion_Click()
    Dim APIVersion As Long
    Dim DriverVersion As Long
    Dim DriverBuildNumber As Long
    Dim Flags As Long
    'get driver info
    USBDevice.GetDriverInfo APIVersion, DriverVersion, DriverBuildNumber, Flags, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        'output driver info
        APIVersionField.Text = Hex(APIVersion)
        DriverVersionField.Text = DriverVersion \ 256 & "." & DriverVersion Mod 256
        DriverBuildNumberField.Text = DriverBuildNumber
        FlagsField.Text = Flags
        DemoVersionField.Text = USBDevice.IsDemoVersion
        CheckedBuildVersionField.Text = USBDevice.IsCheckedBuild
    End If
End Sub

'get request timeout
Private Sub GetRequestTimeout_Click()
    GetRequestTimeoutField.Text = USBDevice.DeviceRequestTimeout
End Sub

'set request timeout
Private Sub SetRequestTimeout_Click()
    USBDevice.DeviceRequestTimeout = Val(SetRequestTimeoutField.Text)
End Sub

'get device options
Private Sub GetDeviceOptions_Click()
    GetDeviceOptionsField.Text = USBDevice.DeviceOptions
End Sub

'set device options
Private Sub SetDeviceOptions_Click()
    USBDevice.DeviceOptions = Val(SetDeviceOptionsField.Text)
End Sub

'DisablePnPNotificationButton_Click
Private Sub DisablePnPNotificationButton_Click()
    ' We use the USBIO default GUID here.
    ' In production-level code a custom GUID should be used which is defined in usbio.inf.
    USBDevice.DisablePnPNotification "{325ddf96-938c-11d3-9e34-0080c82727f4}", status
    Call error(status)
End Sub

'EnablePnPNotificationButton_Click
Private Sub EnablePnPNotificationButton_Click()
    ' We use the USBIO default GUID here.
    ' In production-level code a custom GUID should be used which is defined in usbio.inf.
    USBDevice.EnablePnPNotification "{325ddf96-938c-11d3-9e34-0080c82727f4}", status
    Call error(status)
End Sub



'PnP add Notification Event
Private Sub USBDevice_PnPAddNotification(ByVal Obj As Object)
    MsgBox "Device added"
End Sub

'PnP remove Notification Event
Private Sub USBDevice_PnPRemoveNotification(ByVal Obj As Object)
    MsgBox "Device removed"
End Sub


' *****************************************************
' Descriptor Page
' *****************************************************

'get string descriptor
Private Sub GetStringDescriptor_Click()
    Dim Descriptor(256) As Byte
    Dim ByteCount As Long
    ByteCount = 256
    ' call USBIOCOM object
                USBDevice.GetStringDescriptor Descriptor, ByteCount, Val(GetStringDescriptorIndexField.Text), 0, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        GetStringDescriptorField.Text = ""
        GetStringDescriptorLengthField.Text = Descriptor(0)
        GetStringDescriptorTypeField.Text = Descriptor(1)
        ' display the descriptor in a readable format
        For n = 2 To ByteCount
            If Val(GetStringDescriptorIndexField.Text) = 0 Then
                If Descriptor(n) < 16 Then
                    GetStringDescriptorField.Text = GetStringDescriptorField.Text & "0" & Hex(Descriptor(n)) & " "
                Else
                    GetStringDescriptorField.Text = GetStringDescriptorField.Text & Hex(Descriptor(n)) & " "
                End If
            Else
                GetStringDescriptorField.Text = GetStringDescriptorField.Text & Chr(Descriptor(n))
            End If
        Next n
    End If
End Sub

'get descriptor
Private Sub GetDescriptor_Click()
    Dim ByteCount As Long
    ByteCount = Val(MaxDescSizeText.Text)
    Dim Descriptor(4096) As Byte
    ' call USBIOCOM object
    USBDevice.GetDescriptor Descriptor, ByteCount, 0, Val(DescriptorTypeField.Text), Val(DescriptorIndexField.Text), 0, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        If (ByteCount - 1) > 0 Then
            DescriptorField.Text = DescriptorField.Text & "Descriptor" & vbNewLine
            PrintDescriptor Descriptor, ByteCount, MaxDescSizeText
        End If
    End If
End Sub

'get configuration descriptor
Private Sub GetConfigurationDescriptor_Click()
    Dim ByteCount As Long
    ByteCount = 4096
    Dim Descriptor(4096) As Byte
    ' call USBIOCOM object
    USBDevice.GetConfigurationDescriptor Descriptor, ByteCount, 0, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        If (ByteCount - 1) > 0 Then
            DescriptorField.Text = DescriptorField.Text & "Configuration Descriptor" & vbNewLine
            PrintDescriptor Descriptor, ByteCount, ByteCount
         End If
    End If
End Sub


'get device descriptor
Private Sub GetDeviceDescriptor_Click()
    Dim ByteCount As Long
    ByteCount = 4096
    Dim Descriptor(4096) As Byte
    ' call USBIOCOM object
    USBDevice.GetDeviceDescriptor Descriptor, ByteCount, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        If (ByteCount - 1) > 0 Then
            DescriptorField.Text = DescriptorField.Text & "Device Descriptor" & vbNewLine
            'display the descriptor in a readable format
            PrintDescriptor Descriptor, ByteCount, ByteCount
        End If
    End If
End Sub

'clear descriptor display
Private Sub ClearAll_Click()
    'clear fields
    DescriptorField.Text = ""
    GetStringDescriptorLengthField.Text = ""
    GetStringDescriptorTypeField.Text = ""
    GetStringDescriptorField.Text = ""
End Sub


' *****************************************************
' Interface Page
' *****************************************************

'add interface
Private Sub AddInterface_Click()
    USBDevice.AddInterface Val(AddInterfaceIndexField.Text), Val(AddInterfaceAlternateSettingField.Text), Val(AddInterfaceMaxTransferSizeField.Text), status
    Call error(status)
End Sub

'delete interface
Private Sub DeleteInterfaces_Click()
    USBDevice.DeleteInterfaces
End Sub

'set configuration
Private Sub SetConfiguration_Click()
    'configure device
    USBDevice.SetConfiguration Val(SetConfigurationIndexField.Text), status
    Call error(status)
End Sub

'get configuration
Private Sub GetConfiguration_Click()
    Dim conf As Byte
    USBDevice.GetConfiguration conf, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        GetConfigurationField.Text = conf
    End If
End Sub

'unconfigure device
Private Sub UnconfigureDevice_Click()
    USBDevice.UnconfigureDevice status
    Call error(status)
End Sub

'convert dec to hex
Private Sub EndpointAddressDecField_Change()
    EndpointAddressHexField.Text = Hex(Val(EndpointAddressDecField.Text))
End Sub

'convert hex to dec
Private Sub EndpointAddressHexField_Change()
    EndpointAddressDecField.Text = Val("&H" & (EndpointAddressHexField.Text))
End Sub

'bind pipe
Private Sub Bind_Click()
    USBPipe.Bind Val(EndpointAddressDecField.Text), status
    Call error(status)
End Sub

'unbind pipe
Private Sub Unbind_Click()
    USBPipe.Unbind status
    Call error(status)
End Sub

'reset pipe
Private Sub ResetPipe_Click()
    USBPipe.ResetPipe status
    Call error(status)
End Sub

'abort pipe
Private Sub AbortPipe_Click()
    USBPipe.AbortPipe status
    Call error(status)
End Sub

'set short transfer flag
Private Sub SetShortTransfer_Click()
    USBPipe.ShortTransferOK = ShortTransferCheck.Value
End Sub

'get short transfer flag
Private Sub GetShortTransfer_Click()
    ShortTransferCheck.Value = USBPipe.ShortTransferOK
End Sub

'set interface
Private Sub SetInterface_Click()
    USBDevice.SetInterface Val(SetInterfaceIndexField.Text), Val(SetInterfaceAlternateSettingField.Text), Val(SetInterfaceMaxTransferSizeField.Text), status
    Call error(status)
End Sub

'get interface
Private Sub GetInterface_Click()
    Dim a As Byte
    USBDevice.GetInterface a, Val(GetInterfaceIndexField.Text), status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        GetInterfaceAlternateSettingField.Text = a
    End If
End Sub


' *****************************************************
' Read Page
' *****************************************************

' start reading
Private Sub StartRead_Click()
    Dim ActualAveragingInterval As Long
    Dim AverageRate As Long
    Dim BytesTransferred_L As Long
    Dim BytesTransferred_H As Long
    Dim RequestsSucceeded As Long
    Dim RequestsFailed As Long
    'init reading
    reading = False
    BufferSize = Val(StartReadBufferSizeField.Text)
    BufferCount = Val(StartReadNumberOfBuffersField.Text)
    IsIsoFlag = IsoCheck.Value
    ErrorCount = Val(StartReadMaxErrorCountField.Text)
    WriteToFile = StartReadCheck.Value
    If USBPipe.EndpointFifoSize = 0 Then
        MsgBox "Endpoint not configured"
        GoTo Exit1
    End If
    If IsIsoFlag Then
        ReDim buffer((BufferSize * USBPipe.EndpointFifoSize) - 1) As Byte
        ReDim intbuffer(BufferSize - 1) As Long
    Else
        ReDim buffer(BufferSize - 1) As Byte
    End If
    If Not (IsIsoFlag And (BufferSize * BufferCount)) > 1024 Then
        If fileopen = False Then
            'create and open a file, overwrite existing file
            Open StartReadFileField.Text For Binary Access Write As #1
            fileopen = True
        End If
        'reset the pipe, work-around for a bug in the UHC driver
        USBPipe.ResetPipe status
        If status = USBIO_ERR_SUCCESS Then
            'start reading
            USBPipe.StartReading BufferSize, BufferCount, ErrorCount, status
            If status = USBIO_ERR_SUCCESS Then
                reading = True
                USBPipe.SetupPipeStatistics 1000, status
                If status <> USBIO_ERR_SUCCESS Then
                    Call error(status)
                Else
                    ' enable statistics timer
                    ReadStTimer.Enabled = True
                    ' reset pipe statistics
                    USBPipe.QueryPipeStatistics ActualAveragingInterval, AverageRate, BytesTransferred_L, BytesTransferred_H, RequestsSucceeded, RequestsFailed, USBIOCOM_QPS_FLAG_RESET_ALL_COUNTERS, status
                    RdDataRateC = 0
                    RdTotalBytesC = 0
                    ReqSuccC = 0
                    ReqFailC = 0
                End If
            End If
        End If
        Call error(status)
    Else
        MsgBox ("Iso Frames in Buffer * Number of Buffers <= 1024")
    End If
Exit1:
End Sub

'stop reading
Private Sub StopRead_Click()
    USBPipe.SetupPipeStatistics 0, status
    If status <> USBIO_ERR_SUCCESS Then
        Call error(status)
    End If
    ReadStTimer.Enabled = False
    reading = False
    ' stop reading
    USBPipe.StopReading
    If fileopen Then
        'close file
        Close #1
        fileopen = False
    End If
End Sub
' timer to get statistics
Private Sub ReadStTimer_Timer()
    Dim ActualAveragingInterval As Long
    Dim AverageRate As Long
    Dim BytesTransferred_L As Long
    Dim BytesTransferred_H As Long
    Dim RequestsSucceeded As Long
    Dim RequestsFailed As Long

    USBPipe.QueryPipeStatistics ActualAveragingInterval, AverageRate, BytesTransferred_L, BytesTransferred_H, RequestsSucceeded, RequestsFailed, 0, status
    If status <> USBIO_ERR_SUCCESS Then
        Call error(status)
    Else
        RdDataRateC = AverageRate
        RdTotalBytesC = BytesTransferred_L
        ReqSuccC = RequestsSucceeded
        ReqFailC = RequestsFailed
    End If
End Sub

'clear output window
Private Sub Clear_Click()
    Outputwindow.Text1.Text = ""
End Sub

'show/hide output window
Private Sub showoutputwindow_Click()
    If Outputwindow.Visible Then
        Outputwindow.Hide
    Else
        Outputwindow.Show
    End If
End Sub

'ReadComplete Event
'this event is issued by the COM object when buffers are available for reading
Private Sub USBPipe_ReadComplete(ByVal Obj As Object)
    Dim numberofbytes As Long
    If reading Then
        status = USBIO_ERR_SUCCESS
        ' read data until an error is returned
        Do While (status <> USBIO_ERR_NO_DATA) And (status = USBIO_ERR_SUCCESS)
            'read buffer
            If IsIsoFlag Then
                USBPipe.ReadIsoData buffer, numberofbytes, intbuffer, status
            Else
                USBPipe.ReadData buffer, numberofbytes, status
            End If
            If status = USBIO_ERR_SUCCESS Then
                'display in listbox
                ReadBufferSizeField.Text = numberofbytes
                If WriteToFile Then
                    'write data to file
                    If fileopen Then
                        Put #1, , buffer
                    End If
                Else
                    If InOutputWindow.Value = 1 Then
                        For n = 0 To (numberofbytes - 1)
                            ' display in readable format
                            If buffer(n) < 16 Then
                                k = k & "0" & Hex(buffer(n)) & " "
                            Else
                                k = k & Hex(buffer(n)) & " "
                            End If
                            If n = UBound(buffer) Then
                                If Len(Outputwindow.Text1.Text) + Len(k) < 64000 Then
                                    output = Outputwindow.Text1.Text & k
                                    Outputwindow.Text1.Text = output & vbNewLine
                                Else
                                    Outputwindow.Text1.Text = ""
                                End If
                            End If
                        Next n
                    End If
                End If
                If ProgressBar1.Value = ProgressBar1.Max Then
                    ProgressBar1.Value = 0
                End If
                ProgressBar1.Value = ProgressBar1.Value + 1
            End If
        Loop
        If (status <> USBIO_ERR_NO_DATA) And (status <> USBIO_ERR_SUCCESS) Then
            StopRead_Click
            MsgBox (USBDevice.ErrorText(status))
        End If
    End If
End Sub

Private Sub IsoCheck_Click()
    If IsoCheck.Value = 0 Then
        StartReadBufferSizeLabel.Caption = "Buffer Size"
    Else
        StartReadBufferSizeLabel.Caption = "Iso Frames in Buffer"
    End If
End Sub


' *****************************************************
' Write Page
' *****************************************************

'start writing
Private Sub StartWriting_Click()
    fifosize = USBPipe.EndpointFifoSize
    wBufferSize = Val(StartWritingBufferSizeField.Text)
    wBufferCount = Val(StartWritingNumberOfBuffersField.Text)
    wErrorCount = Val(StartWritingMaxErrorCountField.Text)
    wBufferValue = Val(DefinedBuffersField.Text)
    writing = False
    wIsIsoFlag = WriteIsoCheck.Value
    ReadFromFile = StartWriteCheck.Value
    WriteStatus = WriteStatusCheck.Value
    ' check if ep is configured
    If fifosize = 0 Then
        MsgBox "Endpoint not configured"
        GoTo Exit2
    End If
    ' prepare buffer
    If wIsIsoFlag Then
        ReDim buf(wBufferSize * fifosize - 1) As Byte
        ReDim intbuffer(wBufferSize - 1) As Long
        For m = 0 To wBufferSize - 1
            intbuffer(m) = fifosize
        Next m
    Else
        ReDim buf(wBufferSize - 1) As Byte
    End If
    ReDim intbuffer2(wBufferSize - 1) As Long
    
    ' prepare file
    If ReadFromFile Then
        'create file object used to read data
        Set wr = CreateObject("Scripting.FileSystemObject")
        ' open file if exists
        If wr.FileExists(SendFileField.Text) Then
                Open SendFileField.Text For Binary As #2
                Get #2, 1, buf
                Close #2
        Else
            MsgBox ("File does not exist")
            GoTo Exit1
        End If
     Else
        For m = 0 To wBufferSize - 1
            buf(m) = wBufferValue
        Next m
    End If
    
    ' reset device
    USBPipe.ResetPipe status
    If status <> USBIO_ERR_SUCCESS Then
        Call error(status)
        GoTo Exit1
    End If
    
    ' start writing
    USBPipe.StartWriting wBufferSize, wBufferCount, wErrorCount, WriteStatus, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
        GoTo Exit1
    Else
        writing = True
        ' write data, fill all available buffers
        Do
            If wIsIsoFlag Then
                USBPipe.WriteIsoData buf, intbuffer, UserId, status
            Else
                USBPipe.WriteData buf, UserId, status
            End If
            If status = USBIO_ERR_NO_BUFFER Then
                Exit Do
            End If
            If status <> USBIO_ERR_SUCCESS Then
                MsgBox (USBDevice.ErrorText(status))
                GoTo Exit1
            End If
        Loop
    End If
    ' success
    GoTo Exit2
Exit1:
    ' error
    writing = False
Exit2:
End Sub


'stop writing
Private Sub StopWriting_Click()
    writing = False
    USBPipe.StopWriting
End Sub


'change label if iso is checked
Private Sub WriteIsoCheck_Click()
    If WriteIsoCheck.Value = 0 Then
        StartWritingBufferSizeLabel.Caption = "Buffer Size"
    Else
        StartWritingBufferSizeLabel.Caption = "Iso Frames in Buffer"
    End If
End Sub


'WriteComplete Event
'this event is issued by the COM object when free buffers are available
Private Sub USBPipe_WriteComplete(ByVal Obj As Object)
    If writing Then
        ' write data until buffers are exhausted
        Do
            If wIsIsoFlag Then
                USBPipe.WriteIsoData buf, intbuffer, UserId, status
            Else
                USBPipe.WriteData buf, UserId, status
            End If
            If status = USBIO_ERR_NO_BUFFER Then
                Exit Do
            End If
            If status <> USBIO_ERR_SUCCESS Then
                StopWriting_Click
                MsgBox (USBDevice.ErrorText(status))
                Exit Do
            End If
        Loop
    End If
End Sub


'WriteStatusAvailable Event
'this event is issued by the COM object when a write operation was completed
Private Sub USBPipe_WriteStatusAvailable(ByVal Obj As Object)
    Dim ByteCount As Long
    If writing Then
        If wIsIsoFlag Then
            'isochronous
            USBPipe.GetIsoWriteStatus UserId, intbuffer2, ByteCount, status
        Else
            'not isochronous
            USBPipe.GetWriteStatus UserId, status
        End If
        If status <> USBIO_ERR_SUCCESS Then
            StopWriting_Click
        End If
        Call error(status)
    End If
End Sub


' *****************************************************
' Feature Page
' *****************************************************

'set feature
Private Sub SetFeature_Click()
    If Combo1.ListIndex > -1 Then
        USBDevice.SetFeature Combo1.ListIndex, Val(FeatureField.Text), Val(FeatureIndexField.Text), status
    End If
    Call error(status)
End Sub

'clear feature
Private Sub ClearFeature_Click()
    If Combo1.ListIndex > -1 Then
         USBDevice.ClearFeature Combo1.ListIndex, Val(FeatureField.Text), Val(FeatureIndexField.Text), status
    End If
    Call error(status)
End Sub


' *****************************************************
' Class or Vendor Request Page
' *****************************************************

'send vendor request
Private Sub SendRequest_Click()
    Dim numberofbytes As Long
    Dim pos As Long
    Dim i As Long
    Dim inputstring As String
    Dim outputstring As String
    Dim con As Boolean
    Dim buffer() As Byte
    ' class or vendor request
    If (Combo2.ListIndex > -1) And (VendorDirectionCombo.ListIndex > -1) And (Combo4.ListIndex > -1) Then
        If VendorDirectionCombo.ListIndex = 0 Then
            numberofbytes = Val(TransferSizeText.Text)
            inputstring = VendorBuffer.Text
            con = True
            If numberofbytes > 0 Then
                ' dim buffer
                ReDim buffer(numberofbytes - 1) As Byte
                pos = 0
                ' fill buffer
                For i = 0 To numberofbytes - 1
                    If con Then pos = InStr(1 + pos, inputstring, "0x", vbTextCompare)
                    If pos > 0 Then
                        buffer(i) = Val("&H" & (Mid(inputstring, pos + 2, 2)))
                    Else
                        con = False
                    End If
                Next i
            End If
            ' send out request
            USBDevice.ClassOrVendorOutRequest buffer, 0, Combo4.ListIndex + 1, Combo2.ListIndex + 1, 0, Val(VendorRequestField.Text), Val(VendorValueField.Text), Val(VendoIndexField.Text), status
        End If
        If VendorDirectionCombo.ListIndex = 1 Then
            numberofbytes = Val(TransferSizeText.Text)
            ' dim buffer
            If numberofbytes > 0 Then ReDim buffer(numberofbytes - 1) As Byte
            ' send in request
            USBDevice.ClassOrVendorInRequest buffer, numberofbytes, 0, Combo4.ListIndex + 1, Combo2.ListIndex + 1, 0, Val(VendorRequestField.Text), Val(VendorValueField), Val(VendoIndexField.Text), status
            ' print out
            VendorBuffer.Text = ""
            For m = 0 To numberofbytes - 1
                If buffer(m) < 16 Then
                    outputstring = outputstring & "0x0" & Hex(buffer(m)) & " "
                Else
                    outputstring = outputstring & "0x" & Hex(buffer(m)) & " "
                End If
            Next m
            VendorBuffer.Text = outputstring
        End If
    End If
    Call error(status)
End Sub


' *****************************************************
' Other Page
' *****************************************************

'get status
Private Sub GetStatus_Click()
    Dim si As Long
    If GetStatusRecipientCombo.ListIndex > -1 Then
        USBDevice.GetStatus si, GetStatusRecipientCombo.ListIndex, Val(GetStatusIndexField.Text), status
        If status <> USBIO_ERR_SUCCESS Then
            MsgBox (USBDevice.ErrorText(status))
        Else
            GetStatusField.Text = si
        End If
    End If
End Sub

'cycle port, simulates a device disconnect/connect
Private Sub CyclePort_Click()
    USBDevice.CyclePort status
    Call error(status)
End Sub

'reset device
Private Sub ResetDevice_Click()
    USBDevice.ResetDevice status
    Call error(status)
End Sub

'get the current USB frame number from host controller
Private Sub GetCurrentFrameNumber_Click()
    Dim Frame As Long
    'get frame number
    USBDevice.GetCurrentFrameNumber Frame, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        FrameNumberField.Text = Hex(Frame)
    End If
End Sub

'set the device power state
Private Sub SetDevicePowerState_Click()
    If SetPowerStateCombo.ListIndex > -1 Then
        USBDevice.SetDevicePowerState SetPowerStateCombo.ListIndex, status
    Call error(status)
    End If
End Sub

'get the device power state
Private Sub GetDevicePowerState_Click()
    Dim Power As Long
    USBDevice.GetDevicePowerState Power, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        PowerStateField.Text = Power
    End If
End Sub

'get path
Private Sub GetDevicePathName_Click()
    Dim Path As String
    Path = USBDevice.DevicePathName
    ' print out
    PathField.Text = Path
End Sub

Private Sub GetBwInfo_Click()
    Dim TotalBw As Long
    Dim ConsumedBw As Long
    USBDevice.GetBandwidthInfo TotalBw, ConsumedBw, status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    Else
        ConsumedBwEdit = ConsumedBw
        TotalBwEdit = TotalBw
    End If
    
End Sub


' *****************************************************
' Internal helper functions
' *****************************************************

'on load
Private Sub Form_Load()
    TabStrip1_Click
    ' create USBIOCOM object instance
    On Error GoTo ErrorHandler
    Set USBDevice = New USBIOCOMLib.USBIOInterface3
    Set USBPipe = New USBIOCOMLib.USBIOInterface3
    'init combo boxes
    Combo1.AddItem ("Device")
    Combo1.AddItem ("Interface")
    Combo1.AddItem ("Endpoint")
    Combo1.AddItem ("Other")
    Combo1.ListIndex = 0
    Combo2.AddItem ("Device")
    Combo2.AddItem ("Interface")
    Combo2.AddItem ("Endpoint")
    Combo2.AddItem ("Other")
    Combo2.ListIndex = 0
    VendorDirectionCombo.AddItem ("Host to Device")
    VendorDirectionCombo.AddItem ("Device to Host")
    VendorDirectionCombo.ListIndex = 0
    Combo4.AddItem ("Class")
    Combo4.AddItem ("Vendor")
    Combo4.ListIndex = 0
    GetStatusRecipientCombo.AddItem ("Device")
    GetStatusRecipientCombo.AddItem ("Interface")
    GetStatusRecipientCombo.AddItem ("Endpoint")
    GetStatusRecipientCombo.AddItem ("Other")
    GetStatusRecipientCombo.ListIndex = 0
    SetPowerStateCombo.AddItem ("DevicePowerD0")
    SetPowerStateCombo.AddItem ("DevicePowerD1")
    SetPowerStateCombo.AddItem ("DevicePowerD2")
    SetPowerStateCombo.AddItem ("DevicePowerD3")
    SetPowerStateCombo.ListIndex = 0
    EndpointAddressHexField.Text = Hex(EndpointAddressDecField.Text)
    ' init flags
    fileopen = False
    writing = False
    reading = False
    Exit Sub
ErrorHandler:
    ' dll is not registered
    MsgBox "USBIOCOM object is not registered. Use 'regsvr32 usbiocom.dll'." & vbNewLine & Err.HelpContext
    End
End Sub

'on unload
Private Sub Form_Unload(Cancel As Integer)
    ' close output window
    Outputwindow.down
End Sub

'show an error
Private Sub error(status As Long)
    If status <> USBIO_ERR_SUCCESS Then
        'get an error text for the error code
        MsgBox (USBDevice.ErrorText(status))
    End If
End Sub


'switch pages
Private Sub TabStrip1_Click()
    If TabStrip1.SelectedItem.Index = mintCurFrame _
      Then Exit Sub ' No need to change frame.
    ' Otherwise, hide old frame, show new.
    Frame1(TabStrip1.SelectedItem.Index).Visible = True
    Frame1(TabStrip1.SelectedItem.Index).ZOrder 'bring the context of the tab to the front
    Frame1(mintCurFrame).Visible = False
    ' update mintCurFrame
    mintCurFrame = TabStrip1.SelectedItem.Index
End Sub


'print descriptor
Private Sub PrintDescriptor(Descriptor() As Byte, ByteCount As Long, MaxDescSizeText As Long)
    Dim n As Long
    Dim k As String
    n = 0
    Do While n < ByteCount
        ' convert descriptor to readable format
        If MaxDescSizeText < Descriptor(n) Then
            anzbytes = MaxDescSizeText - 1
        Else
            anzbytes = (Descriptor(n) - 1 + n)
        End If
        For m = n To anzbytes
            If Descriptor(m) < 16 Then
                k = k & "0" & Hex(Descriptor(m)) & " "
            Else
                k = k & Hex(Descriptor(m)) & " "
            End If
        Next m
            ' add to list
            n = n + Descriptor(n)
            DescriptorField.Text = DescriptorField.Text & k & vbNewLine
            k = ""
    Loop
End Sub

Private Sub ReleaseButton_Click()
    USBDevice.ReleaseDevice status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    End If
End Sub

Private Sub AcquireButton_Click()
    USBDevice.AcquireDevice status
    If status <> USBIO_ERR_SUCCESS Then
        MsgBox (USBDevice.ErrorText(status))
    End If
End Sub
