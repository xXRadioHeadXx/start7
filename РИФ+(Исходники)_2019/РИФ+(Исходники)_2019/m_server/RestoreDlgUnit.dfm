object RestoreDlg: TRestoreDlg
  Left = 245
  Top = 108
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = #1042#1086#1089#1089#1090#1072#1085#1086#1074#1083#1077#1085#1080#1077' '#1080#1079' '#1088#1077#1079#1077#1088#1074#1085#1086#1081' '#1082#1086#1087#1080#1080'...'
  ClientHeight = 153
  ClientWidth = 786
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Microsoft Sans Serif'
  Font.Pitch = fpFixed
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  PrintScale = poNone
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 10
    Top = 10
    Width = 759
    Height = 90
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 30
    Top = 30
    Width = 67
    Height = 13
    Caption = #1060#1072#1081#1083' '#1072#1088#1093#1080#1074#1072
  end
  object OKBtn: TButton
    Left = 298
    Top = 113
    Width = 92
    Height = 31
    Caption = 'OK'
    Default = True
    Enabled = False
    ModalResult = 1
    TabOrder = 0
    OnClick = OKBtnClick
  end
  object CancelBtn: TButton
    Left = 396
    Top = 113
    Width = 93
    Height = 31
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 30
    Top = 49
    Width = 572
    Height = 21
    TabStop = False
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 2
  end
  object Button1: TButton
    Left = 620
    Top = 44
    Width = 132
    Height = 31
    Caption = #1053#1072#1081#1090#1080
    TabOrder = 3
    OnClick = Button1Click
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '7z'
    Filter = #1060#1072#1081#1083#1099' '#1072#1088#1093#1080#1074#1072' '#1082#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1080'|*.7z'
    Left = 8
    Top = 88
  end
end
