VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Visual Basic Simple"
   ClientHeight    =   3075
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2775
   Icon            =   "vbsimple.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3075
   ScaleWidth      =   2775
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox EPAddr 
      Height          =   285
      Left            =   1800
      TabIndex        =   8
      Text            =   "129"
      Top             =   960
      Width           =   615
   End
   Begin VB.CommandButton StartReading 
      Caption         =   "Start Reading"
      Height          =   375
      Left            =   240
      TabIndex        =   6
      Top             =   1440
      Width           =   1335
   End
   Begin VB.TextBox Data1 
      Height          =   285
      Left            =   240
      TabIndex        =   4
      Top             =   2640
      Width           =   2175
   End
   Begin VB.TextBox EventCount1 
      Height          =   285
      Left            =   1800
      TabIndex        =   3
      Text            =   "0"
      Top             =   1920
      Width           =   615
   End
   Begin VB.TextBox State1 
      Height          =   285
      Left            =   240
      TabIndex        =   1
      Text            =   "Device not connected"
      Top             =   360
      Width           =   2175
   End
   Begin VB.Label Label4 
      Caption         =   "Endpoint Address"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   960
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Received Data"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   2280
      Width           =   2175
   End
   Begin VB.Label Label3 
      Caption         =   "Read Event Count"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   1920
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Device state:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

' (c) 2001-2004 Thesycon Systemsoftware & Consulting GmbH

' This application is a simple example for using the
' USBIO COM interface from Visual Basic.

' After the application is started it tries to open the first USB
' device that is connected to the USBIO driver. If this is successful
' the device status display is updated.

' If the test device provides a bulk or interrupt IN endpoint
' the button "Start Reading" can be used to start reading from this endpoint.

' A typical test device is an USB mouse or a keyboard.
' Note: A mouse or a keyboard used for this test application cannot be used
' as a system input device at the same time.

'******************************************************************
' we define a global variable that represents the instance of the USBIO COM object
' we need to use the "WithEvents" attribute
Dim WithEvents Device1 As USBIOCOMLib.USBIOInterface3
Attribute Device1.VB_VarHelpID = -1
Dim ReadEventCount1 As Long

Private Sub Form_Load()
' some local variables
Dim Devices As Long
Dim Status As Long
' Create the USBIO COM object instance.
Set Device1 = New USBIOCOMLib.USBIOInterface3
' Enumerate the available devices.
' We use the USBIO default GUID here.
' In production-level code a custom GUID should be used which is defined in usbio.inf.
Device1.EnumerateDevices "{325ddf96-938c-11d3-9e34-0080c82727f4}", Devices
' check the number of available devices
If Devices >= 1 Then
    ' open the first device (index 0)
    Device1.OpenDevice 0, Status
    If Status = USBIO_ERR_SUCCESS Then
        Form1.State1 = "USB device opened"
    Else
        MsgBox "Cannot open the USB device"
    End If
Else
    ' show a message if no device is found
    MsgBox "No USB device connected or USBIO device driver not installed"
End If
End Sub
Private Sub StartReading_Click()
Dim Status As Long
    ' add an interface, we assume 0 is a valid interface
    Device1.AddInterface 0, 0, 4096, Status
    If Status = USBIO_ERR_SUCCESS Then
        Form1.State1 = "Interface added"
    End If
    ShowError Status
    ' set the configuration, 0 is ok for single configuration devices
    Device1.SetConfiguration 0, Status
    If Status = USBIO_ERR_SUCCESS Then
        Form1.State1 = "Device configured"
    End If
    ShowError Status
    ' Bind to an IN endpoint provided by a mouse or a keyboard for example.
    ' Typically, the endpoint has the address 0x81.
    Device1.Bind Val(EPAddr), Status
    If Status = USBIO_ERR_SUCCESS Then
        Form1.State1 = "EP bound"
    End If
    ShowError Status
    ' get the FIFO size of the endpoint
    FifoSize = Device1.EndpointFifoSize
    ' Start reading from the endpoint
    Device1.StartReading FifoSize, 5, 5, Status
    If Status = USBIO_ERR_SUCCESS Then
        Form1.State1 = "Reading started"
    End If
    ShowError Status
    ' disable the start button
    StartReading.Enabled = False
End Sub

Sub ShowError(ErrorCode As Long)
    If ErrorCode <> USBIO_ERR_SUCCESS Then
        MsgBox Device1.ErrorText(ErrorCode)
        ' End the program in case of an error.
        End
    End If
End Sub

' This function is called if data was received from the device.
Sub Device1_ReadComplete(ByVal obj As Object)
Dim st As Long
Dim count As Long
' We set the buffer size to fifosize. This is the maximum FIFO size for bulk.
Dim buffer() As Byte

    ReDim buffer(FifoSize) As Byte

    ' count the received read events
    ReadEventCount1 = ReadEventCount1 + 1
    Form1.EventCount1 = ReadEventCount1
    ' read data from the COM object (FifoSize bytes)
    count = FifoSize
    Device1.ReadData buffer, count, st
    ' check status
    If st = USBIO_ERR_SUCCESS Then
        ' display the data bytes in the edit field
        Data1.Text = ""
        For n = 0 To count - 1
            If (buffer(n) < 16) Then
                Data1.Text = Data1.Text + " 0" + Hex(buffer(n))
            Else
                Data1.Text = Data1.Text + " " + Hex(buffer(n))
            End If
        Next n
    Else
        MsgBox Device1.ErrorText(st)
    End If
End Sub

Private Sub Form_Terminate()
    ' stop reading
    Device1.StopReading
    ' close the device
    Device1.CloseDevice
End Sub

