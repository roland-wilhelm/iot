object Form1: TForm1
  Left = 357
  Top = 111
  Width = 332
  Height = 198
  Caption = 'USBIO Delphi Simple'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = OnCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 96
    Width = 68
    Height = 13
    Caption = 'Bytes returned'
  end
  object Label2: TLabel
    Left = 104
    Top = 56
    Width = 26
    Height = 13
    Caption = 'Bytes'
  end
  object Label3: TLabel
    Left = 192
    Top = 56
    Width = 46
    Height = 13
    Caption = 'Filled with'
  end
  object InitDevice: TButton
    Left = 16
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Init Device'
    TabOrder = 0
    OnClick = InitDeviceClick
  end
  object Write: TButton
    Left = 16
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Write'
    TabOrder = 1
    OnClick = WriteClick
  end
  object BytesReturned: TEdit
    Left = 104
    Top = 96
    Width = 41
    Height = 21
    ReadOnly = True
    TabOrder = 2
    Text = '0'
  end
  object Bytes: TEdit
    Left = 136
    Top = 56
    Width = 33
    Height = 21
    TabOrder = 3
    Text = '64'
  end
  object FillWith: TEdit
    Left = 248
    Top = 56
    Width = 41
    Height = 21
    TabOrder = 4
    Text = '32'
  end
  object Text: TEdit
    Left = 16
    Top = 128
    Width = 289
    Height = 21
    ReadOnly = True
    TabOrder = 5
  end
end
