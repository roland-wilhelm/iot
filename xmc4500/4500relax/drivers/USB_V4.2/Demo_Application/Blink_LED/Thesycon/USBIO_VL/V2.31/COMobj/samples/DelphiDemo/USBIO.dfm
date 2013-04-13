object MainDlg: TMainDlg
  Left = 434
  Top = 115
  BorderStyle = bsSingle
  Caption = 'USBIO COM Interface Delphi Example'
  ClientHeight = 398
  ClientWidth = 627
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    00008000800080800000C0C0C000808080000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00000000000007777777FFFFFFFFFFFF000000
    000000799999977FFFFFFFFFFF000000000007999999991FFFFFFFFFFF000000
    000079999999111FFFFFFFFFFF000000000079999911FFFFFFFFFFFFFF000000
    00007999991FFFFFFFFFFFFFFF00000000007999991FFFFCCCCCCCCCFF000000
    00007999991FFFFCCCCCCCCCCF00000000007999991FFFFFFFFFFFFFCF000000
    00007999991FFFFCCCCCCCCCCF00000000007999991FFFFCCCCCCCCCFF000000
    00007999991FFFFFFFFFFFFFFF00000000007999991FFFFFCCCFFCCCFF000000
    00007999991FFFFCCCCCFCCCCF00000000007999991FFFFCFFFCCFFFCF000000
    00007999991FFFFCCCFFCCCCCF00000000007999991FFFFFCCFFFCCCFF000000
    00007999991FFFFFFFFFFFFFFF00000000007999991FFFFCCCCCCCCCCF000000
    00007999991FFFFCCCCCCCCCCF00000000007999991FFFFCFFFCFFFFCF000000
    00007999991FFFFCCCCCCCCCCF00000000007999991FFFFFCCCFCCCCFF000000
    00007999991FFFFFFFFFFFFFFF00000000007999991FFFFFFFFFFFFFFF000000
    00007999991FFFFFFFFFFFFFFF00007777777999991111111111111FFF000799
    999999999999999999999991FF0000799999999999999999999999991F000007
    9999999999999999999999999100000077777777777777777777777777000000
    0000000000000000000000000000FFE00003FFC00003FF800003FF000003FF00
    0003FF000003FF000003FF000003FF000003FF000003FF000003FF000003FF00
    0003FF000003FF000003FF000003FF000003FF000003FF000003FF000003FF00
    0003FF000003FF000003FF000003FF000003FF000003C000000380000003C000
    0003E0000003F0000003FFFFFFFF280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    000000808000800000008000800080800000C0C0C000808080000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00000007777FFFFFF00000
    79999FFFFFF000009991CCCCCCF00000999FFFFFFFC00000999FCCCCCCF00000
    999FFFFFFFF00000999FFCCFCCF00000999FCFFCFFC00000999FFCFFCCF00000
    999FFFFFFFF00000999FCCCCCCC00000999FCFFCFFC00000999FFCCFCCF00777
    999111111FF009999999999999F00077777777777770F8010000F0010000F001
    0000F0010000F0010000F0010000F0010000F0010000F0010000F0010000F001
    0000F0010000F00100008001000080010000C0010000}
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ErrorText: TEdit
    Left = 8
    Top = 336
    Width = 409
    Height = 21
    TabOrder = 0
  end
  object ClearError: TButton
    Left = 424
    Top = 336
    Width = 65
    Height = 25
    Caption = 'Clear Error'
    TabOrder = 1
    OnClick = ClearErrorClick
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 609
    Height = 321
    ActivePage = TabSheet1
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = 'Device'
      object GroupBox1: TGroupBox
        Left = 8
        Top = 0
        Width = 521
        Height = 113
        Caption = 'Device'
        TabOrder = 0
        object Label1: TLabel
          Left = 176
          Top = 24
          Width = 91
          Height = 13
          Caption = 'Number of Devices'
        end
        object Label2: TLabel
          Left = 176
          Top = 56
          Width = 74
          Height = 13
          Caption = 'Device Number'
        end
        object Enumerate: TButton
          Left = 16
          Top = 16
          Width = 81
          Height = 25
          Caption = 'Enumerate'
          TabOrder = 0
          OnClick = EnumerateClick
        end
        object NumberOfDevices: TEdit
          Left = 128
          Top = 16
          Width = 41
          Height = 21
          TabOrder = 1
        end
        object OpenDevice: TButton
          Left = 16
          Top = 48
          Width = 81
          Height = 25
          Caption = 'Open'
          TabOrder = 2
          OnClick = OpenDeviceClick
        end
        object DeviceNumber: TEdit
          Left = 128
          Top = 52
          Width = 41
          Height = 21
          TabOrder = 3
          Text = '0'
        end
        object CloseDevice: TButton
          Left = 16
          Top = 80
          Width = 81
          Height = 25
          Caption = 'Close'
          TabOrder = 4
          OnClick = CloseDeviceClick
        end
        object AcquireButton: TButton
          Left = 336
          Top = 16
          Width = 121
          Height = 25
          Caption = 'Acquire'
          TabOrder = 5
          OnClick = AcquireButtonClick
        end
        object ReleaseButton: TButton
          Left = 336
          Top = 56
          Width = 121
          Height = 25
          Caption = 'Release'
          TabOrder = 6
          OnClick = ReleaseButtonClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 124
        Width = 345
        Height = 157
        Caption = 'Driver Info'
        TabOrder = 1
        object Label3: TLabel
          Left = 80
          Top = 24
          Width = 55
          Height = 13
          Caption = 'API Version'
        end
        object Label4: TLabel
          Left = 80
          Top = 72
          Width = 66
          Height = 13
          Caption = 'Driver Version'
        end
        object Label5: TLabel
          Left = 264
          Top = 24
          Width = 61
          Height = 13
          Caption = 'Build Version'
        end
        object Label6: TLabel
          Left = 264
          Top = 72
          Width = 56
          Height = 13
          Caption = 'Driver Flags'
        end
        object DriverInfo: TButton
          Left = 224
          Top = 120
          Width = 81
          Height = 25
          Caption = 'Driver Info'
          TabOrder = 0
          OnClick = DriverInfoClick
        end
        object ApiVersion: TEdit
          Left = 8
          Top = 20
          Width = 65
          Height = 21
          TabOrder = 1
        end
        object DriverVersion: TEdit
          Left = 8
          Top = 68
          Width = 65
          Height = 21
          TabOrder = 2
        end
        object BuildVersion: TEdit
          Left = 192
          Top = 20
          Width = 65
          Height = 21
          TabOrder = 3
        end
        object DriverFlags: TEdit
          Left = 192
          Top = 68
          Width = 65
          Height = 21
          TabOrder = 4
        end
      end
      object PnPNotification: TGroupBox
        Left = 368
        Top = 128
        Width = 161
        Height = 113
        Caption = 'PnP Notification'
        TabOrder = 2
        object EnablePnPNotification: TButton
          Left = 8
          Top = 24
          Width = 137
          Height = 25
          Caption = 'Enable PnP Notification'
          TabOrder = 0
          OnClick = EnablePnPNotificationClick
        end
        object DisablePnPNotification: TButton
          Left = 8
          Top = 72
          Width = 137
          Height = 25
          Caption = 'Disable PnP Notification'
          TabOrder = 1
          OnClick = DisablePnPNotificationClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Descriptor'
      ImageIndex = 1
      object GroupBox3: TGroupBox
        Left = 8
        Top = 16
        Width = 185
        Height = 149
        Caption = 'String Descriptor'
        TabOrder = 0
        object Label7: TLabel
          Left = 8
          Top = 24
          Width = 59
          Height = 13
          Caption = 'String Index:'
        end
        object GetStringDesc: TButton
          Left = 8
          Top = 64
          Width = 161
          Height = 25
          Caption = 'Get String Descriptor'
          TabOrder = 0
          OnClick = GetStringDescClick
        end
        object StringDesc: TEdit
          Left = 8
          Top = 104
          Width = 161
          Height = 21
          TabOrder = 1
        end
        object StringIndex: TEdit
          Left = 136
          Top = 24
          Width = 33
          Height = 21
          TabOrder = 2
          Text = '1'
        end
      end
      object Devicedescriptorbox: TGroupBox
        Left = 8
        Top = 176
        Width = 353
        Height = 65
        Caption = 'Device Descriptor'
        TabOrder = 1
        object getdevicedescriptor: TButton
          Left = 16
          Top = 24
          Width = 121
          Height = 25
          Caption = 'Get Device Descriptor'
          TabOrder = 0
          OnClick = getdevicedescriptorClick
        end
      end
      object GroupBox11: TGroupBox
        Left = 208
        Top = 16
        Width = 153
        Height = 149
        Caption = 'Descriptor'
        TabOrder = 2
        object Label23: TLabel
          Left = 8
          Top = 48
          Width = 52
          Height = 13
          Caption = 'Desc Type'
        end
        object Label24: TLabel
          Left = 8
          Top = 80
          Width = 54
          Height = 13
          Caption = 'Desc Index'
        end
        object Label25: TLabel
          Left = 8
          Top = 112
          Width = 48
          Height = 13
          Caption = 'Desc Size'
        end
        object GetDesc: TButton
          Left = 8
          Top = 16
          Width = 121
          Height = 25
          Caption = 'Get Descriptor'
          TabOrder = 0
          OnClick = GetDescClick
        end
        object DescType: TEdit
          Left = 72
          Top = 48
          Width = 57
          Height = 21
          TabOrder = 1
          Text = '1'
        end
        object DescIndex: TEdit
          Left = 72
          Top = 80
          Width = 57
          Height = 21
          TabOrder = 2
          Text = '0'
        end
        object DescSize: TEdit
          Left = 72
          Top = 112
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '4096'
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Interface'
      ImageIndex = 2
      object GroupBox4: TGroupBox
        Left = 8
        Top = 4
        Width = 313
        Height = 93
        Caption = 'Interface'
        TabOrder = 0
        object Label8: TLabel
          Left = 8
          Top = 24
          Width = 74
          Height = 13
          Caption = 'Interface Index:'
        end
        object Label9: TLabel
          Left = 8
          Top = 48
          Width = 81
          Height = 13
          Caption = 'Alternate Setting:'
        end
        object Label10: TLabel
          Left = 8
          Top = 72
          Width = 88
          Height = 13
          Caption = 'Max Transfer Size:'
        end
        object AddInterface: TButton
          Left = 176
          Top = 16
          Width = 81
          Height = 25
          Caption = 'Add Interface'
          TabOrder = 0
          OnClick = AddInterfaceClick
        end
        object DeleteInterface: TButton
          Left = 176
          Top = 48
          Width = 81
          Height = 25
          Caption = 'Del Interface'
          TabOrder = 1
          OnClick = DeleteInterfaceClick
        end
        object InterfaceIndex: TEdit
          Left = 112
          Top = 16
          Width = 41
          Height = 21
          TabOrder = 2
          Text = '0'
        end
        object AlternateSetting: TEdit
          Left = 112
          Top = 40
          Width = 41
          Height = 21
          TabOrder = 3
          Text = '0'
        end
        object MaxTransferSize: TEdit
          Left = 112
          Top = 64
          Width = 41
          Height = 21
          TabOrder = 4
          Text = '64000'
        end
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 104
        Width = 313
        Height = 81
        Caption = 'Configuration'
        TabOrder = 1
        object Label11: TLabel
          Left = 8
          Top = 24
          Width = 94
          Height = 13
          Caption = 'Configuration Index:'
        end
        object SetConf: TButton
          Left = 176
          Top = 16
          Width = 81
          Height = 25
          Caption = 'Set Conf'
          TabOrder = 0
          OnClick = SetConfClick
        end
        object ConfIndex: TEdit
          Left = 112
          Top = 16
          Width = 41
          Height = 21
          TabOrder = 1
          Text = '0'
        end
        object UnConfigure: TButton
          Left = 176
          Top = 48
          Width = 81
          Height = 25
          Caption = 'Unconf'
          TabOrder = 2
          OnClick = UnConfigureClick
        end
      end
      object GroupBox6: TGroupBox
        Left = 8
        Top = 192
        Width = 313
        Height = 81
        Caption = 'Pipe'
        TabOrder = 2
        object Label12: TLabel
          Left = 8
          Top = 32
          Width = 64
          Height = 13
          Caption = 'Pipe Number:'
        end
        object Bind: TButton
          Left = 176
          Top = 16
          Width = 81
          Height = 25
          Caption = 'Bind'
          TabOrder = 0
          OnClick = BindClick
        end
        object PipeNumber: TEdit
          Left = 112
          Top = 24
          Width = 41
          Height = 21
          TabOrder = 1
          Text = '129'
        end
        object UnBind: TButton
          Left = 176
          Top = 48
          Width = 81
          Height = 25
          Caption = 'Unbind'
          TabOrder = 2
          OnClick = UnBindClick
        end
      end
      object GroupBox14: TGroupBox
        Left = 328
        Top = 0
        Width = 185
        Height = 185
        Caption = 'Bandwidth Info'
        TabOrder = 3
        object Label38: TLabel
          Left = 8
          Top = 56
          Width = 77
          Height = 13
          Caption = 'Total Bandwidth'
        end
        object Label39: TLabel
          Left = 8
          Top = 80
          Width = 103
          Height = 13
          Caption = 'Consumed Bandwidth'
        end
        object GetBandwidthInfo: TButton
          Left = 16
          Top = 16
          Width = 121
          Height = 25
          Caption = 'Get Bandwidth Info'
          TabOrder = 0
          OnClick = GetBandwidthInfoClick
        end
        object TotalBandwidthEdit: TEdit
          Left = 120
          Top = 48
          Width = 57
          Height = 21
          TabOrder = 1
        end
        object ConsumedBandwidthEdit: TEdit
          Left = 120
          Top = 80
          Width = 57
          Height = 21
          TabOrder = 2
        end
      end
      object GroupBox15: TGroupBox
        Left = 328
        Top = 192
        Width = 185
        Height = 81
        Caption = 'Get Device Info'
        TabOrder = 4
        object GetDeviceInfo: TButton
          Left = 8
          Top = 24
          Width = 89
          Height = 25
          Caption = 'Get Device Info'
          TabOrder = 0
          OnClick = GetDeviceInfoClick
        end
        object GetDeviceInfoCheck: TCheckBox
          Left = 8
          Top = 56
          Width = 153
          Height = 17
          Caption = 'Is High Speed'
          Enabled = False
          TabOrder = 1
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Read'
      ImageIndex = 3
      object GroupBox7: TGroupBox
        Left = 8
        Top = 4
        Width = 353
        Height = 277
        Caption = 'Read'
        TabOrder = 0
        object Label13: TLabel
          Left = 8
          Top = 120
          Width = 47
          Height = 13
          Caption = 'File Name'
        end
        object Label14: TLabel
          Left = 8
          Top = 24
          Width = 82
          Height = 13
          Caption = 'Isochronous Pipe'
        end
        object Label15: TLabel
          Left = 8
          Top = 48
          Width = 136
          Height = 13
          Caption = 'Buffer size/Frames per buffer'
        end
        object Label16: TLabel
          Left = 8
          Top = 72
          Width = 28
          Height = 13
          Caption = 'Buffer'
        end
        object Label17: TLabel
          Left = 8
          Top = 96
          Width = 74
          Height = 13
          Caption = 'Max error count'
        end
        object Label30: TLabel
          Left = 8
          Top = 200
          Width = 44
          Height = 13
          Caption = 'Progress:'
        end
        object StartReading: TButton
          Left = 248
          Top = 24
          Width = 81
          Height = 25
          Caption = 'Start Read'
          TabOrder = 0
          OnClick = StartReadingClick
        end
        object BufferSize: TEdit
          Left = 168
          Top = 48
          Width = 41
          Height = 21
          TabOrder = 1
          Text = '64'
        end
        object NoOfBuffer: TEdit
          Left = 168
          Top = 72
          Width = 41
          Height = 21
          TabOrder = 2
          Text = '5'
        end
        object MaxErrorCount: TEdit
          Left = 168
          Top = 96
          Width = 41
          Height = 21
          TabOrder = 3
          Text = '5'
        end
        object StopRead: TButton
          Left = 248
          Top = 56
          Width = 81
          Height = 25
          Caption = 'Stop Read'
          TabOrder = 4
          OnClick = StopReadClick
        end
        object IsIso: TCheckBox
          Left = 168
          Top = 24
          Width = 57
          Height = 17
          Caption = 'ISO'
          TabOrder = 5
        end
        object FileName: TEdit
          Left = 168
          Top = 120
          Width = 169
          Height = 21
          TabOrder = 6
          Text = 'dump.bin'
        end
        object ProgressBar1: TProgressBar
          Left = 8
          Top = 216
          Width = 337
          Height = 16
          Min = 0
          Max = 100
          TabOrder = 7
        end
        object SaveFile: TButton
          Left = 168
          Top = 152
          Width = 81
          Height = 25
          Caption = 'Browse'
          TabOrder = 8
          OnClick = SaveFileClick
        end
        object WriteToFile: TCheckBox
          Left = 8
          Top = 144
          Width = 97
          Height = 17
          Caption = 'Write to File'
          TabOrder = 9
        end
        object DisableProgressBar: TCheckBox
          Left = 16
          Top = 240
          Width = 185
          Height = 17
          Caption = 'Disable progress for small buffers'
          TabOrder = 10
        end
      end
      object GroupBox13: TGroupBox
        Left = 368
        Top = 0
        Width = 217
        Height = 281
        Caption = 'Statistics'
        TabOrder = 1
        object Label33: TLabel
          Left = 8
          Top = 44
          Width = 113
          Height = 13
          Caption = 'ActualAveragingInterval'
        end
        object Label34: TLabel
          Left = 8
          Top = 68
          Width = 63
          Height = 13
          Caption = 'AverageRate'
        end
        object Label35: TLabel
          Left = 8
          Top = 92
          Width = 80
          Height = 13
          Caption = 'BytesTransferred'
        end
        object Label36: TLabel
          Left = 8
          Top = 116
          Width = 100
          Height = 13
          Caption = 'RequestsSucceeded'
        end
        object Label37: TLabel
          Left = 8
          Top = 140
          Width = 73
          Height = 13
          Caption = 'RequestsFailed'
        end
        object AveragingInterval: TLabel
          Left = 8
          Top = 204
          Width = 83
          Height = 13
          Caption = 'AveragingInterval'
        end
        object QueryStatistics: TButton
          Left = 8
          Top = 16
          Width = 89
          Height = 25
          Caption = 'QueryStatistics'
          TabOrder = 0
          OnClick = QueryStatisticsClick
        end
        object ActualAveragingIntervalEdit: TEdit
          Left = 128
          Top = 40
          Width = 81
          Height = 21
          TabOrder = 1
        end
        object AverageRateEdit: TEdit
          Left = 128
          Top = 64
          Width = 81
          Height = 21
          TabOrder = 2
        end
        object BytesTransferredEdit: TEdit
          Left = 128
          Top = 88
          Width = 81
          Height = 21
          TabOrder = 3
        end
        object RequestsSucceededEdit: TEdit
          Left = 128
          Top = 112
          Width = 81
          Height = 21
          TabOrder = 4
        end
        object RequestsFailedEdit: TEdit
          Left = 128
          Top = 136
          Width = 81
          Height = 21
          TabOrder = 5
        end
        object SetupPipeStatistics: TButton
          Left = 8
          Top = 168
          Width = 113
          Height = 25
          Caption = 'Set AveragingInterval'
          TabOrder = 6
          OnClick = SetupPipeStatisticsClick
        end
        object AveragingIntervalEdit: TEdit
          Left = 128
          Top = 200
          Width = 73
          Height = 21
          TabOrder = 7
          Text = '0'
        end
        object ResetStatistics: TButton
          Left = 8
          Top = 224
          Width = 113
          Height = 25
          Caption = 'Reset Statistics'
          TabOrder = 8
          OnClick = ResetStatisticsClick
        end
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'Write'
      ImageIndex = 4
      object GroupBox12: TGroupBox
        Left = 0
        Top = 8
        Width = 537
        Height = 273
        Caption = 'Write'
        TabOrder = 0
        object Label26: TLabel
          Left = 16
          Top = 96
          Width = 74
          Height = 13
          Caption = 'Max error count'
        end
        object Label27: TLabel
          Left = 16
          Top = 72
          Width = 84
          Height = 13
          Caption = 'Number of buffers'
        end
        object Label28: TLabel
          Left = 16
          Top = 48
          Width = 49
          Height = 13
          Caption = 'Buffer size'
        end
        object Label29: TLabel
          Left = 16
          Top = 168
          Width = 64
          Height = 13
          Caption = 'Fill buffer with'
        end
        object Label31: TLabel
          Left = 16
          Top = 24
          Width = 82
          Height = 13
          Caption = 'Isochronous Pipe'
        end
        object Label32: TLabel
          Left = 16
          Top = 48
          Width = 136
          Height = 13
          Caption = 'Buffer size/Frames per buffer'
        end
        object StartWrite: TButton
          Left = 328
          Top = 24
          Width = 105
          Height = 25
          Caption = 'Start Write'
          TabOrder = 0
          OnClick = StartWriteClick
        end
        object StopWrite: TButton
          Left = 328
          Top = 56
          Width = 105
          Height = 25
          Caption = 'Stop Write'
          TabOrder = 1
          OnClick = StopWriteClick
        end
        object writebuffersize: TEdit
          Left = 176
          Top = 48
          Width = 89
          Height = 21
          TabOrder = 2
          Text = '64'
        end
        object writenumberofbuffers: TEdit
          Left = 176
          Top = 72
          Width = 89
          Height = 21
          TabOrder = 3
          Text = '5'
        end
        object writeerrorcount: TEdit
          Left = 176
          Top = 96
          Width = 89
          Height = 21
          TabOrder = 4
          Text = '5'
        end
        object writeisocheck: TCheckBox
          Left = 176
          Top = 24
          Width = 97
          Height = 17
          Caption = 'ISO'
          TabOrder = 5
        end
        object writefile: TEdit
          Left = 88
          Top = 216
          Width = 257
          Height = 21
          TabOrder = 6
        end
        object WriteStatusCheck: TCheckBox
          Left = 176
          Top = 120
          Width = 97
          Height = 17
          Caption = 'Write Status'
          TabOrder = 7
        end
        object OpenFile: TButton
          Left = 16
          Top = 216
          Width = 57
          Height = 25
          Caption = 'Browse'
          TabOrder = 8
          OnClick = OpenFileClick
        end
        object FromFileCheck: TCheckBox
          Left = 16
          Top = 192
          Width = 97
          Height = 17
          Caption = 'From File'
          TabOrder = 9
        end
        object FilledWith: TEdit
          Left = 112
          Top = 166
          Width = 33
          Height = 21
          TabOrder = 10
          Text = '255'
        end
      end
    end
    object Feature: TTabSheet
      Caption = 'Feature'
      ImageIndex = 4
      object Featurebox: TGroupBox
        Left = 8
        Top = 8
        Width = 457
        Height = 281
        Caption = 'Feature'
        TabOrder = 0
        object Label20: TLabel
          Left = 104
          Top = 48
          Width = 45
          Height = 13
          Caption = 'Recipient'
        end
        object Label21: TLabel
          Left = 104
          Top = 80
          Width = 36
          Height = 13
          Caption = 'Feature'
        end
        object Label22: TLabel
          Left = 104
          Top = 112
          Width = 26
          Height = 13
          Caption = 'Index'
        end
        object setfeature: TButton
          Left = 104
          Top = 160
          Width = 81
          Height = 33
          Caption = 'Set Feature'
          TabOrder = 0
          OnClick = setfeatureClick
        end
        object featurecombo: TComboBox
          Left = 184
          Top = 48
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Items.Strings = (
            'Device'
            'Interface'
            'Endpoint'
            'Other')
        end
        object featurefield: TEdit
          Left = 184
          Top = 80
          Width = 145
          Height = 21
          TabOrder = 2
          Text = '0'
        end
        object featureindexfield: TEdit
          Left = 184
          Top = 112
          Width = 145
          Height = 21
          TabOrder = 3
          Text = '0'
        end
        object clearfeature: TButton
          Left = 264
          Top = 160
          Width = 81
          Height = 33
          Caption = 'Clear Feature'
          TabOrder = 4
          OnClick = clearfeatureClick
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Class or Vendor Request'
      ImageIndex = 7
      object ClassOrVendorRequestBox: TGroupBox
        Left = 8
        Top = 8
        Width = 457
        Height = 281
        Caption = 'Class or Vendor Request'
        TabOrder = 0
        object VendorDirectionLabel: TLabel
          Left = 16
          Top = 32
          Width = 42
          Height = 13
          Caption = 'Direction'
        end
        object VendorTypeLabel: TLabel
          Left = 16
          Top = 72
          Width = 24
          Height = 13
          Caption = 'Type'
        end
        object VendorRecipientLabel: TLabel
          Left = 16
          Top = 112
          Width = 45
          Height = 13
          Caption = 'Recipient'
        end
        object VendorRequestLabel: TLabel
          Left = 248
          Top = 32
          Width = 40
          Height = 13
          Caption = 'Request'
        end
        object VendorValueLabel: TLabel
          Left = 248
          Top = 72
          Width = 27
          Height = 13
          Caption = 'Value'
        end
        object VendorIndexLabel: TLabel
          Left = 248
          Top = 112
          Width = 26
          Height = 13
          Caption = 'Index'
        end
        object VendorBufferSizeLabel: TLabel
          Left = 8
          Top = 176
          Width = 49
          Height = 13
          Caption = 'Buffer size'
        end
        object VendorBufferLabel: TLabel
          Left = 8
          Top = 216
          Width = 28
          Height = 13
          Caption = 'Buffer'
        end
        object VendorDirectionCombo: TComboBox
          Left = 104
          Top = 32
          Width = 113
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'VendorDirectionCombo'
          Items.Strings = (
            'Host to Device'
            'Device to Host')
        end
        object VendorTypeCombo: TComboBox
          Left = 104
          Top = 72
          Width = 113
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = 'VendorTypeCombo'
          Items.Strings = (
            'Class'
            'Vendor')
        end
        object VendorRecipientCombo: TComboBox
          Left = 104
          Top = 112
          Width = 113
          Height = 21
          ItemHeight = 13
          TabOrder = 2
          Text = 'VendorRecipientCombo'
          Items.Strings = (
            'Device'
            'Interface'
            'Endpoint'
            'Other')
        end
        object VendorRequest: TEdit
          Left = 312
          Top = 32
          Width = 57
          Height = 21
          TabOrder = 3
          Text = '0'
        end
        object VendorValueText: TEdit
          Left = 312
          Top = 72
          Width = 57
          Height = 21
          TabOrder = 4
          Text = '0'
        end
        object VendorIndexText: TEdit
          Left = 312
          Top = 112
          Width = 57
          Height = 21
          TabOrder = 5
          Text = '0'
        end
        object VendorBufferSizeText: TEdit
          Left = 64
          Top = 176
          Width = 49
          Height = 21
          TabOrder = 6
          Text = '0'
        end
        object VendorBufferText: TEdit
          Left = 64
          Top = 216
          Width = 361
          Height = 21
          TabOrder = 7
          Text = '$00 $00 $00'
        end
        object VendorSendButton: TButton
          Left = 312
          Top = 152
          Width = 89
          Height = 25
          Caption = 'Send Request'
          TabOrder = 8
          OnClick = VendorSendButtonClick
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Other'
      ImageIndex = 5
      object GroupBox8: TGroupBox
        Left = 8
        Top = 8
        Width = 113
        Height = 201
        TabOrder = 0
        object CyclePort: TButton
          Left = 8
          Top = 16
          Width = 97
          Height = 25
          Caption = 'Cycle Port'
          TabOrder = 0
          OnClick = CyclePortClick
        end
        object ResetDevice: TButton
          Left = 8
          Top = 48
          Width = 97
          Height = 25
          Caption = 'Reset Device'
          TabOrder = 1
          OnClick = ResetDeviceClick
        end
        object getframeno: TButton
          Left = 8
          Top = 112
          Width = 97
          Height = 25
          Caption = 'Get Frame Number'
          TabOrder = 2
          OnClick = getframenoClick
        end
        object frmno: TEdit
          Left = 8
          Top = 144
          Width = 97
          Height = 21
          TabOrder = 3
        end
      end
      object GroupBox9: TGroupBox
        Left = 8
        Top = 224
        Width = 457
        Height = 65
        Caption = 'Get Device PathName'
        TabOrder = 1
        object GetDevicePathName: TButton
          Left = 8
          Top = 24
          Width = 73
          Height = 25
          Caption = 'Get Path'
          TabOrder = 0
          OnClick = GetDevicePathNameClick
        end
        object GetDevicePathNamefield: TEdit
          Left = 96
          Top = 24
          Width = 353
          Height = 21
          TabOrder = 1
        end
      end
      object PowerState: TGroupBox
        Left = 136
        Top = 8
        Width = 273
        Height = 89
        Caption = 'Power State'
        TabOrder = 2
        object getpowerstate: TButton
          Left = 16
          Top = 16
          Width = 89
          Height = 25
          Caption = 'Get Power State'
          TabOrder = 0
          OnClick = getpowerstateClick
        end
        object getpowerstatefield: TEdit
          Left = 16
          Top = 48
          Width = 89
          Height = 21
          ReadOnly = True
          TabOrder = 1
        end
        object setpowerstate: TButton
          Left = 120
          Top = 16
          Width = 137
          Height = 25
          Caption = 'Set Power State'
          TabOrder = 2
          OnClick = setpowerstateClick
        end
        object powerstatecombo: TComboBox
          Left = 120
          Top = 48
          Width = 137
          Height = 21
          ItemHeight = 13
          TabOrder = 3
          Items.Strings = (
            'DevicePowerD0'
            'DevicePowerD1'
            'DevicePowerD2'
            'DevicePowerD3')
        end
      end
      object GroupBox10: TGroupBox
        Left = 136
        Top = 104
        Width = 273
        Height = 105
        Caption = 'Status'
        TabOrder = 3
        object Label18: TLabel
          Left = 16
          Top = 16
          Width = 45
          Height = 13
          Caption = 'Recipient'
        end
        object Label19: TLabel
          Left = 16
          Top = 40
          Width = 26
          Height = 13
          Caption = 'Index'
        end
        object getstatus: TButton
          Left = 16
          Top = 64
          Width = 81
          Height = 25
          Caption = 'Get Status'
          TabOrder = 0
          OnClick = getstatusClick
        end
        object statusindex: TEdit
          Left = 120
          Top = 40
          Width = 25
          Height = 21
          TabOrder = 1
          Text = '0'
        end
        object statuscombo: TComboBox
          Left = 120
          Top = 16
          Width = 137
          Height = 21
          ItemHeight = 13
          TabOrder = 2
          Items.Strings = (
            'Device'
            'Interface'
            'Endpoint'
            'Other')
        end
        object statusout: TEdit
          Left = 120
          Top = 64
          Width = 121
          Height = 21
          TabOrder = 3
        end
      end
    end
  end
  object showwindow: TButton
    Left = 88
    Top = 368
    Width = 81
    Height = 25
    Caption = 'Show Output'
    TabOrder = 3
    OnClick = showwindowClick
  end
  object hidewindow: TButton
    Left = 176
    Top = 368
    Width = 81
    Height = 25
    Caption = 'Hide Output'
    TabOrder = 4
    OnClick = hidewindowClick
  end
  object clearoutput: TButton
    Left = 264
    Top = 368
    Width = 97
    Height = 25
    Caption = 'Clear Output'
    TabOrder = 5
    OnClick = clearoutputClick
  end
  object OpenDialog1: TOpenDialog
    Left = 4
    Top = 336
  end
  object SaveDialog1: TSaveDialog
    Left = 36
    Top = 340
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 68
    Top = 340
  end
end
