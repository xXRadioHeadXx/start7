object OperatorsDlg: TOperatorsDlg
  Left = 245
  Top = 108
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1086#1088' '#1086#1087#1077#1088#1072#1090#1086#1088#1072' '#1082#1086#1084#1087#1083#1077#1082#1089#1072
  ClientHeight = 194
  ClientWidth = 313
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Microsoft Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 12
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 297
    Height = 137
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 83
    Height = 12
    Caption = #1060#1048#1054' '#1086#1087#1077#1088#1072#1090#1086#1088#1072
  end
  object Label2: TLabel
    Left = 16
    Top = 80
    Width = 38
    Height = 12
    Caption = #1055#1072#1088#1086#1083#1100
  end
  object OKBtn: TButton
    Left = 119
    Top = 156
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 40
    Width = 281
    Height = 20
    Style = csDropDownList
    ItemHeight = 12
    TabOrder = 2
  end
  object MaskEdit1: TMaskEdit
    Left = 16
    Top = 96
    Width = 281
    Height = 20
    PasswordChar = '*'
    TabOrder = 0
  end
end
