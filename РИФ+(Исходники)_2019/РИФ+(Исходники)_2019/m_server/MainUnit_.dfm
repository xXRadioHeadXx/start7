object MainForm: TMainForm
  Left = 193
  Top = 121
  Width = 1006
  Height = 621
  Caption = #1057#1077#1088#1074#1077#1088
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Microsoft Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  PrintScale = poNone
  Scaled = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 257
    Top = 42
    Width = 3
    Height = 503
    Cursor = crHSplit
    AutoSnap = False
    MinSize = 250
  end
  object Label24: TLabel
    Left = 152
    Top = 32
    Width = 5
    Height = 13
    Caption = #1095
  end
  object Label25: TLabel
    Left = 224
    Top = 32
    Width = 20
    Height = 13
    Caption = #1084#1080#1085
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 545
    Width = 992
    Height = 19
    Panels = <
      item
        Width = 250
      end
      item
        Width = 250
      end
      item
        Width = 250
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 992
    Height = 42
    AutoSize = True
    ButtonHeight = 36
    ButtonWidth = 86
    Caption = 'ToolBar1'
    EdgeBorders = [ebTop, ebBottom]
    Images = ImageList1
    ShowCaptions = True
    TabOrder = 1
    OnResize = ToolBar1Resize
    object ToolButton1: TToolButton
      Left = 0
      Top = 2
      Hint = #1057#1073#1088#1086#1089' '#1079#1074#1091#1082#1086#1074#1086#1081' '#1089#1080#1075#1085#1072#1083#1080#1079#1072#1094#1080#1080
      Caption = #1057#1073#1088#1086#1089' '#1079#1074#1091#1082#1072
      ImageIndex = 41
      OnClick = ToolButton1Click
    end
    object ToolButton2: TToolButton
      Left = 86
      Top = 2
      Hint = #1057#1073#1088#1086#1089' '#1090#1088#1077#1074#1086#1078#1085#1086#1081' '#1089#1080#1075#1085#1072#1083#1080#1079#1072#1094#1080#1080
      Caption = #1057#1073#1088#1086#1089' '#1090#1088#1077#1074#1086#1075
      ImageIndex = 0
      OnClick = ToolButton2Click
    end
    object StaticText30: TStaticText
      Left = 172
      Top = 2
      Width = 86
      Height = 36
      AutoSize = False
      TabOrder = 2
    end
    object StaticText16: TStaticText
      Left = 258
      Top = 2
      Width = 60
      Height = 36
      Alignment = taCenter
      AutoSize = False
      Color = clBlack
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -27
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
    end
    object StaticText31: TStaticText
      Left = 318
      Top = 2
      Width = 10
      Height = 36
      AutoSize = False
      TabOrder = 3
    end
    object StaticText32: TStaticText
      Left = 328
      Top = 2
      Width = 60
      Height = 36
      Alignment = taCenter
      AutoSize = False
      Caption = '   '
      Color = clBlack
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -27
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 4
    end
    object StaticText33: TStaticText
      Left = 388
      Top = 2
      Width = 10
      Height = 36
      AutoSize = False
      TabOrder = 5
    end
    object StaticText34: TStaticText
      Left = 398
      Top = 2
      Width = 60
      Height = 36
      Alignment = taCenter
      AutoSize = False
      Color = clBlack
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -27
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 6
    end
    object StaticText35: TStaticText
      Left = 458
      Top = 2
      Width = 10
      Height = 36
      AutoSize = False
      TabOrder = 7
    end
    object StaticText36: TStaticText
      Left = 468
      Top = 2
      Width = 60
      Height = 36
      Alignment = taCenter
      AutoSize = False
      Color = clBlack
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -27
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 8
    end
    object StaticText37: TStaticText
      Left = 528
      Top = 2
      Width = 10
      Height = 36
      AutoSize = False
      TabOrder = 9
    end
    object ToolButton4: TToolButton
      Left = 538
      Top = 2
      Caption = #1057#1073#1088#1086#1089' '#1090#1072#1073#1083#1086
      ImageIndex = 42
      OnClick = TabloResetItemClick
    end
    object ToolButton3: TToolButton
      Left = 624
      Top = 2
      Caption = #1047#1074#1091#1082' "'#1058#1088#1077#1074#1086#1075#1072'"'
      ImageIndex = 40
      OnClick = SoundSetItemClick
    end
    object StaticText29: TStaticText
      Left = 710
      Top = 2
      Width = 84
      Height = 36
      Alignment = taRightJustify
      Caption = '                    '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 42
    Width = 257
    Height = 503
    Align = alLeft
    Caption = 'Panel1'
    TabOrder = 2
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 255
      Height = 161
      Align = alClient
      TabOrder = 0
      object ObjTree: TTreeView
        Left = 2
        Top = 15
        Width = 251
        Height = 63
        Align = alClient
        HideSelection = False
        Images = ImageList1
        Indent = 19
        PopupMenu = PopupMenu1
        ReadOnly = True
        StateImages = ImageList1
        TabOrder = 0
        OnClick = ObjTreeClick
        OnKeyUp = ObjTreeKeyUp
      end
      object StaticText1: TStaticText
        Left = 2
        Top = 118
        Width = 251
        Height = 41
        Align = alBottom
        AutoSize = False
        BorderStyle = sbsSunken
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object GroupBox5: TGroupBox
        Left = 2
        Top = 78
        Width = 251
        Height = 40
        Align = alBottom
        Caption = #1042#1099#1087#1086#1083#1085#1077#1085#1080#1077' '#1082#1086#1084#1072#1085#1076#1099' '#1059#1047' "'#1052#1086#1085#1086#1083#1080#1090'"'
        TabOrder = 2
        Visible = False
        object CGauge1: TCGauge
          Left = 2
          Top = 15
          Width = 247
          Height = 23
          Align = alClient
          MaxValue = 260
        end
      end
    end
    object GroupBox9: TGroupBox
      Left = 1
      Top = 309
      Width = 255
      Height = 193
      Align = alBottom
      Caption = #1042#1088#1077#1084#1077#1085#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
      TabOrder = 1
      Visible = False
      object Label17: TLabel
        Left = 18
        Top = 32
        Width = 41
        Height = 13
        Caption = #1052#1077#1090#1082#1072' 1'
      end
      object Label18: TLabel
        Left = 18
        Top = 56
        Width = 41
        Height = 13
        Caption = #1052#1077#1090#1082#1072' 2'
      end
      object Label19: TLabel
        Left = 19
        Top = 136
        Width = 38
        Height = 13
        Caption = #1044#1086#1087#1091#1089#1082
      end
      object Label20: TLabel
        Left = 152
        Top = 32
        Width = 5
        Height = 13
        Caption = #1095
      end
      object Label21: TLabel
        Left = 224
        Top = 32
        Width = 20
        Height = 13
        Caption = #1084#1080#1085
      end
      object Label22: TLabel
        Left = 152
        Top = 56
        Width = 5
        Height = 13
        Caption = #1095
      end
      object Label23: TLabel
        Left = 224
        Top = 56
        Width = 20
        Height = 13
        Caption = #1084#1080#1085
      end
      object Label26: TLabel
        Left = 152
        Top = 136
        Width = 5
        Height = 13
        Caption = #1095
      end
      object Label27: TLabel
        Left = 224
        Top = 136
        Width = 20
        Height = 13
        Caption = #1084#1080#1085
      end
      object Label28: TLabel
        Left = 18
        Top = 80
        Width = 41
        Height = 13
        Caption = #1052#1077#1090#1082#1072' 3'
      end
      object Label29: TLabel
        Left = 152
        Top = 80
        Width = 5
        Height = 13
        Caption = #1095
      end
      object Label30: TLabel
        Left = 224
        Top = 80
        Width = 20
        Height = 13
        Caption = #1084#1080#1085
      end
      object Label31: TLabel
        Left = 18
        Top = 104
        Width = 41
        Height = 13
        Caption = #1052#1077#1090#1082#1072' 4'
      end
      object Label32: TLabel
        Left = 152
        Top = 104
        Width = 5
        Height = 13
        Caption = #1095
      end
      object Label33: TLabel
        Left = 224
        Top = 104
        Width = 20
        Height = 13
        Caption = #1084#1080#1085
      end
      object ComboBox8: TComboBox
        Left = 88
        Top = 24
        Width = 57
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = #1085#1077#1090
        Items.Strings = (
          #1085#1077#1090
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23')
      end
      object ComboBox9: TComboBox
        Left = 168
        Top = 24
        Width = 49
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 1
        Text = '00'
        Items.Strings = (
          '00'
          '01'
          '02'
          '03'
          '04'
          '05'
          '06'
          '07'
          '08'
          '09'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31'
          '32'
          '33'
          '34'
          '35'
          '36'
          '37'
          '38'
          '39'
          '40'
          '41'
          '42'
          '43'
          '44'
          '45'
          '46'
          '47'
          '48'
          '49'
          '50'
          '51'
          '52'
          '53'
          '54'
          '55'
          '56'
          '57'
          '58'
          '59')
      end
      object ComboBox11: TComboBox
        Left = 168
        Top = 48
        Width = 49
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 2
        Text = '00'
        Items.Strings = (
          '00'
          '01'
          '02'
          '03'
          '04'
          '05'
          '06'
          '07'
          '08'
          '09'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31'
          '32'
          '33'
          '34'
          '35'
          '36'
          '37'
          '38'
          '39'
          '40'
          '41'
          '42'
          '43'
          '44'
          '45'
          '46'
          '47'
          '48'
          '49'
          '50'
          '51'
          '52'
          '53'
          '54'
          '55'
          '56'
          '57'
          '58'
          '59')
      end
      object ComboBox10: TComboBox
        Left = 88
        Top = 48
        Width = 57
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 3
        Text = #1085#1077#1090
        Items.Strings = (
          #1085#1077#1090
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23')
      end
      object ComboBox14: TComboBox
        Left = 88
        Top = 128
        Width = 57
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 4
        Text = '0'
        Items.Strings = (
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23')
      end
      object ComboBox15: TComboBox
        Left = 168
        Top = 128
        Width = 49
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 5
        Text = '01'
        Items.Strings = (
          '00'
          '01'
          '02'
          '03'
          '04'
          '05'
          '06'
          '07'
          '08'
          '09'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31'
          '32'
          '33'
          '34'
          '35'
          '36'
          '37'
          '38'
          '39'
          '40'
          '41'
          '42'
          '43'
          '44'
          '45'
          '46'
          '47'
          '48'
          '49'
          '50'
          '51'
          '52'
          '53'
          '54'
          '55'
          '56'
          '57'
          '58'
          '59')
      end
      object Button1: TButton
        Left = 56
        Top = 160
        Width = 137
        Height = 25
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        TabOrder = 6
        OnClick = Button1Click
      end
      object ComboBox12: TComboBox
        Left = 88
        Top = 72
        Width = 57
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 7
        Text = #1085#1077#1090
        Items.Strings = (
          #1085#1077#1090
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23')
      end
      object ComboBox13: TComboBox
        Left = 168
        Top = 72
        Width = 49
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 8
        Text = '00'
        Items.Strings = (
          '00'
          '01'
          '02'
          '03'
          '04'
          '05'
          '06'
          '07'
          '08'
          '09'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31'
          '32'
          '33'
          '34'
          '35'
          '36'
          '37'
          '38'
          '39'
          '40'
          '41'
          '42'
          '43'
          '44'
          '45'
          '46'
          '47'
          '48'
          '49'
          '50'
          '51'
          '52'
          '53'
          '54'
          '55'
          '56'
          '57'
          '58'
          '59')
      end
      object ComboBox16: TComboBox
        Left = 88
        Top = 96
        Width = 57
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 9
        Text = #1085#1077#1090
        Items.Strings = (
          #1085#1077#1090
          '0'
          '1'
          '2'
          '3'
          '4'
          '5'
          '6'
          '7'
          '8'
          '9'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23')
      end
      object ComboBox17: TComboBox
        Left = 168
        Top = 96
        Width = 49
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 10
        Text = '00'
        Items.Strings = (
          '00'
          '01'
          '02'
          '03'
          '04'
          '05'
          '06'
          '07'
          '08'
          '09'
          '10'
          '11'
          '12'
          '13'
          '14'
          '15'
          '16'
          '17'
          '18'
          '19'
          '20'
          '21'
          '22'
          '23'
          '24'
          '25'
          '26'
          '27'
          '28'
          '29'
          '30'
          '31'
          '32'
          '33'
          '34'
          '35'
          '36'
          '37'
          '38'
          '39'
          '40'
          '41'
          '42'
          '43'
          '44'
          '45'
          '46'
          '47'
          '48'
          '49'
          '50'
          '51'
          '52'
          '53'
          '54'
          '55'
          '56'
          '57'
          '58'
          '59')
      end
    end
    object ScrollBox2: TScrollBox
      Left = 1
      Top = 162
      Width = 255
      Height = 147
      VertScrollBar.Position = 160
      Align = alBottom
      TabOrder = 2
      Visible = False
      object GroupBox2: TGroupBox
        Left = 0
        Top = -160
        Width = 251
        Height = 500
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
        TabOrder = 0
        object Label11: TLabel
          Left = 8
          Top = 16
          Width = 37
          Height = 13
          Caption = #1055#1086#1088#1086#1075#1080
        end
        object Label12: TLabel
          Left = 128
          Top = 16
          Width = 94
          Height = 13
          Caption = #1059#1089#1083#1086#1074#1080#1077' '#1089#1088#1072#1073#1086#1090#1082#1080
        end
        object Label14: TLabel
          Left = 8
          Top = 64
          Width = 111
          Height = 13
          Caption = #1055#1077#1088#1080#1086#1076' '#1090#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103
        end
        object Label15: TLabel
          Left = 8
          Top = 64
          Width = 37
          Height = 13
          Caption = #1055#1086#1088#1086#1075#1080
        end
        object Label16: TLabel
          Left = 128
          Top = 64
          Width = 94
          Height = 13
          Caption = #1059#1089#1083#1086#1074#1080#1077' '#1089#1088#1072#1073#1086#1090#1082#1080
        end
        object Label37: TLabel
          Left = 8
          Top = 72
          Width = 49
          Height = 13
          Caption = #1060#1080#1083#1100#1090#1088' 1'
        end
        object Label38: TLabel
          Left = 8
          Top = 104
          Width = 49
          Height = 13
          Caption = #1060#1080#1083#1100#1090#1088' 2'
        end
        object Label39: TLabel
          Left = 8
          Top = 136
          Width = 49
          Height = 13
          Caption = #1060#1080#1083#1100#1090#1088' 3'
        end
        object Label40: TLabel
          Left = 128
          Top = 72
          Width = 31
          Height = 13
          Caption = #1055#1086#1088#1086#1075
        end
        object Label41: TLabel
          Left = 128
          Top = 104
          Width = 31
          Height = 13
          Caption = #1055#1086#1088#1086#1075
        end
        object Label42: TLabel
          Left = 128
          Top = 136
          Width = 31
          Height = 13
          Caption = #1055#1086#1088#1086#1075
        end
        object Label93: TLabel
          Left = 8
          Top = 112
          Width = 38
          Height = 13
          Caption = 'Label93'
        end
        object Label94: TLabel
          Left = 128
          Top = 112
          Width = 38
          Height = 13
          Caption = 'Label94'
        end
        object Label104: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label104'
        end
        object Label105: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label105'
        end
        object Label106: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label106'
        end
        object Label107: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label107'
        end
        object Label108: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label108'
        end
        object Label109: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label109'
        end
        object Label110: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label110'
        end
        object Label111: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label111'
        end
        object Label112: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label112'
        end
        object Label113: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label113'
        end
        object Label114: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label112'
        end
        object Label115: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label112'
        end
        object Label116: TLabel
          Left = 8
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label112'
        end
        object Label117: TLabel
          Left = 128
          Top = 112
          Width = 44
          Height = 13
          Caption = 'Label112'
        end
        object Label118: TLabel
          Left = 8
          Top = 64
          Width = 44
          Height = 13
          Caption = 'Label118'
          Visible = False
        end
        object Label119: TLabel
          Left = 128
          Top = 64
          Width = 44
          Height = 13
          Caption = 'Label119'
          Visible = False
        end
        object ComboBox1: TComboBox
          Left = 8
          Top = 32
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 1
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object ComboBox2: TComboBox
          Left = 128
          Top = 32
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 2
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '2 '#1080#1079' 4-'#1093
            '3 '#1080#1079' 4-'#1093)
        end
        object BitBtn2: TBitBtn
          Left = 128
          Top = 160
          Width = 105
          Height = 25
          Hint = #1047#1072#1087#1080#1089#1072#1090#1100' '#1085#1086#1074#1099#1077' '#1085#1072#1089#1090#1088#1086#1081#1082#1080' '#1074' '#1087#1072#1084#1103#1090#1100' '#1076#1072#1090#1095#1080#1082#1072' '#1056#1048#1060
          Caption = #1047#1072#1087#1080#1089#1072#1090#1100
          TabOrder = 3
          OnClick = BitBtn2Click
        end
        object BitBtn1: TBitBtn
          Left = 8
          Top = 160
          Width = 105
          Height = 25
          Hint = #1055#1088#1086#1095#1080#1090#1072#1090#1100' '#1085#1072#1089#1090#1088#1086#1081#1082#1080' '#1080#1079' '#1087#1072#1084#1103#1090#1080' '#1076#1072#1090#1095#1080#1082#1072' '#1056#1048#1060
          Caption = #1055#1088#1086#1095#1080#1090#1072#1090#1100
          TabOrder = 0
          OnClick = BitBtn1Click
        end
        object ComboBox5: TComboBox
          Left = 8
          Top = 80
          Width = 225
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 4
          Text = #1053#1077' '#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          Items.Strings = (
            #1053#1077' '#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            #1054#1089#1085#1086#1074#1085#1086#1081
            #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1081)
        end
        object ComboBox6: TComboBox
          Left = 8
          Top = 80
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 5
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object ComboBox7: TComboBox
          Left = 128
          Top = 80
          Width = 105
          Height = 21
          Style = csDropDownList
          Enabled = False
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 6
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '2 '#1080#1079' 4-'#1093
            '3 '#1080#1079' 4-'#1093)
        end
        object CheckBox1: TCheckBox
          Left = 72
          Top = 72
          Width = 49
          Height = 17
          Caption = #1042#1082#1083
          TabOrder = 7
        end
        object CheckBox2: TCheckBox
          Left = 72
          Top = 104
          Width = 49
          Height = 17
          Caption = #1042#1082#1083
          TabOrder = 8
        end
        object CheckBox3: TCheckBox
          Left = 72
          Top = 136
          Width = 49
          Height = 17
          Caption = #1042#1082#1083
          TabOrder = 9
        end
        object ComboBox18: TComboBox
          Left = 168
          Top = 64
          Width = 65
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 10
        end
        object ComboBox19: TComboBox
          Left = 168
          Top = 96
          Width = 65
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 11
        end
        object ComboBox20: TComboBox
          Left = 168
          Top = 128
          Width = 65
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 12
        end
        object CSpinEdit1: TCSpinEdit
          Left = 168
          Top = 64
          Width = 73
          Height = 22
          MaxValue = 49999
          MinValue = 1
          TabOrder = 13
          Value = 1
        end
        object CSpinEdit2: TCSpinEdit
          Left = 168
          Top = 96
          Width = 73
          Height = 22
          MaxValue = 49999
          MinValue = 1
          TabOrder = 14
          Value = 1
        end
        object CSpinEdit3: TCSpinEdit
          Left = 168
          Top = 128
          Width = 73
          Height = 22
          MaxValue = 49999
          MinValue = 1
          TabOrder = 15
          Value = 1
        end
        object CSpinEdit4: TCSpinEdit
          Left = 8
          Top = 80
          Width = 105
          Height = 22
          TabOrder = 16
        end
        object CSpinEdit5: TCSpinEdit
          Left = 128
          Top = 80
          Width = 105
          Height = 22
          TabOrder = 17
        end
        object ComboBox21: TComboBox
          Left = 8
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 18
        end
        object ComboBox22: TComboBox
          Left = 128
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 19
        end
        object ComboBox23: TComboBox
          Left = 8
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 20
        end
        object ComboBox24: TComboBox
          Left = 128
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 21
        end
        object CSpinEdit6: TCSpinEdit
          Left = 8
          Top = 128
          Width = 105
          Height = 22
          TabOrder = 22
        end
        object CSpinEdit7: TCSpinEdit
          Left = 128
          Top = 128
          Width = 105
          Height = 22
          TabOrder = 23
        end
        object ComboBox25: TComboBox
          Left = 8
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 24
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object ComboBox26: TComboBox
          Left = 128
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 25
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object CSpinEdit8: TCSpinEdit
          Left = 8
          Top = 128
          Width = 105
          Height = 22
          TabOrder = 26
        end
        object CSpinEdit9: TCSpinEdit
          Left = 128
          Top = 128
          Width = 105
          Height = 22
          TabOrder = 27
        end
        object ComboBox27: TComboBox
          Left = 8
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 28
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object ComboBox28: TComboBox
          Left = 128
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 29
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object ComboBox29: TComboBox
          Left = 8
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 30
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object ComboBox30: TComboBox
          Left = 128
          Top = 128
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          ItemIndex = 0
          TabOrder = 31
          Text = #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
          OnChange = ComboBox1Change
          Items.Strings = (
            #1053#1077#1086#1087#1088#1077#1076#1077#1083#1077#1085#1086
            '1 ('#1075#1088#1091#1073#1099#1081')'
            '2'
            '3'
            '4'
            '5'
            '6'
            '7'
            '8'
            '9'
            '10 ('#1095#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1099#1081')')
        end
        object CSpinEdit10: TCSpinEdit
          Left = 8
          Top = 128
          Width = 105
          Height = 22
          TabOrder = 32
        end
        object CSpinEdit11: TCSpinEdit
          Left = 128
          Top = 128
          Width = 105
          Height = 22
          TabOrder = 33
        end
        object ComboBox31: TComboBox
          Left = 8
          Top = 80
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 34
          Visible = False
        end
        object ComboBox32: TComboBox
          Left = 128
          Top = 80
          Width = 105
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 35
          Visible = False
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 260
    Top = 42
    Width = 732
    Height = 503
    Align = alClient
    Caption = 'Panel2'
    TabOrder = 3
    object GroupBox3: TGroupBox
      Left = 146
      Top = 1
      Width = 585
      Height = 501
      Align = alClient
      Caption = #1046#1091#1088#1085#1072#1083' '#1089#1086#1073#1099#1090#1080#1081
      TabOrder = 1
      object DBGrid1: TDBGrid
        Left = 2
        Top = 15
        Width = 581
        Height = 6
        Align = alClient
        DataSource = DataSource1
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        Options = [dgTitles, dgColumnResize, dgRowSelect, dgCancelOnExit, dgMultiSelect]
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Microsoft Sans Serif'
        TitleFont.Style = [fsBold]
        OnDrawColumnCell = DBGrid1DrawColumnCell
        OnDblClick = DBGrid1DblClick
        OnKeyPress = DBGrid1KeyPress
        Columns = <
          item
            Expanded = False
            FieldName = 'Cnt'
            Title.Alignment = taCenter
            Title.Caption = 'N'
            Width = 50
            Visible = True
          end
          item
            Alignment = taCenter
            Expanded = False
            FieldName = 'Dt'
            Title.Alignment = taCenter
            Title.Caption = #1044#1072#1090#1072', '#1074#1088#1077#1084#1103
            Width = 115
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Type2Str'
            Title.Caption = #1057#1086#1073#1099#1090#1080#1077
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Name'
            Title.Caption = #1054#1073#1098#1077#1082#1090
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Comment'
            PopupMenu = PopupMenu2
            Title.Caption = #1055#1088#1080#1095#1080#1085#1072
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Comment2'
            PopupMenu = PopupMenu3
            Title.Caption = #1055#1088#1080#1085#1103#1090#1099#1077' '#1084#1077#1088#1099
            Width = 150
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'OpFio'
            Title.Caption = #1054#1087#1077#1088#1072#1090#1086#1088
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'ClFio'
            Title.Caption = #1050#1083#1080#1077#1085#1090
            Visible = True
          end>
      end
      object GroupBox6: TGroupBox
        Left = 2
        Top = 38
        Width = 581
        Height = 93
        Align = alBottom
        Caption = #1055#1088#1080#1095#1080#1085#1099' '#1080' '#1087#1088#1080#1085#1103#1090#1099#1077' '#1084#1077#1088#1099
        TabOrder = 0
        object Label10: TLabel
          Left = 8
          Top = 24
          Width = 45
          Height = 13
          Caption = #1055#1088#1080#1095#1080#1085#1099
        end
        object Label13: TLabel
          Left = 304
          Top = 24
          Width = 82
          Height = 13
          Caption = #1055#1088#1080#1085#1103#1090#1099#1077' '#1084#1077#1088#1099
        end
        object SpeedButton9: TSpeedButton
          Left = 208
          Top = 40
          Width = 23
          Height = 22
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF87CA87FF3673
            1DFF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C
            37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF675034FF079307FF83CA83FF6FBE
            6EFF90BC8CFF067302FF067702FF067A02FF067E02FF068202FF068402FF0685
            02FF068A02FF068F02FF069302FF069302FF0B8E05FF624B2EFF83CA83FF73C3
            73FFABE1B6FF37B850FF30B345FF29AF3BFF22AB31FF1AA427FF129A1BFF0B91
            10FF07930AFF029603FF009800FF009800FF069302FF694731FF83CA83FF73C3
            73FFB0E6BEFF43C362FF3CBE57FF34B84BFF2CB33FFF59C166FFE2F3E3FFB4DC
            B6FF0B9110FF08990CFF029903FF009800FF069302FF694731FF83C983FF73C3
            73FFB4E8C3FF4BC86DFF43C261FF39BA54FF30B246FF64C371FFFFFFFFFFCCE7
            CDFF0F9116FF0D9A13FF08990CFF029603FF068F02FF694731FF83C983FF73C3
            73FFB7EAC8FF52CC78FF48C369FF3AB555FF2DA742FF61BA6EFFFFFFFFFFCCE6
            CEFF118D19FF0F9116FF0B9110FF07930AFF068A02FF694731FF83C983FF73C2
            73FFB8EBC9FF56CE7DFF83D99EFFD5EFDAFFD2EBD6FFDDF0E0FFFFFFFFFFF4F9
            F4FFCCE6CEFFCCE7CDFFB4DCB6FF0B9110FF068502FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF93E0ACFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFE2F3E3FF129A1BFF068202FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF68D48BFF84DBA0FF82D99EFFA1E1B4FFFFFFFFFFDDF0
            E0FF64BC71FF67C575FF5CC269FF1AA427FF068002FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF57CF7FFF57CF7FFF56CD7DFF82D99DFFFFFFFFFFD2EC
            D7FF30A946FF34B54BFF30B545FF24AC35FF067C02FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF57CF7FFF84DBA0FFFFFFFFFFD5EF
            DBFF3DB759FF3DBD59FF38BB51FF2CB240FF067902FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF57CF7FFF68D48BFF93E0ACFF84D9
            9FFF4BC66EFF46C467FF40C05DFF33B64BFF067502FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF57CF7FFF57CF7FFF56CE
            7EFF54CD7BFF4FCA73FF47C568FF3ABA55FF067102FF694731FF83C983FF73C2
            73FFE0F6E8FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EB
            C9FFB7EAC8FFB5E9C5FFB2E7C1FFADE2B9FF90BB8CFF694731FF83C983FF34A6
            34FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C2
            73FF73C273FF73C273FF73C373FF73C373FF6FBE6EFF2F6E16FF}
          OnClick = SpeedButton9Click
        end
        object SpeedButton11: TSpeedButton
          Left = 504
          Top = 40
          Width = 23
          Height = 22
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF87CA87FF3673
            1DFF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C
            37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF675034FF079307FF83CA83FF6FBE
            6EFF90BC8CFF067302FF067702FF067A02FF067E02FF068202FF068402FF0685
            02FF068A02FF068F02FF069302FF069302FF0B8E05FF624B2EFF83CA83FF73C3
            73FFABE1B6FF37B850FF30B345FF29AF3BFF22AB31FF1AA427FF129A1BFF0B91
            10FF07930AFF029603FF009800FF009800FF069302FF694731FF83CA83FF73C3
            73FFB0E6BEFF43C362FF3CBE57FF34B84BFF2CB33FFF59C166FFE2F3E3FFB4DC
            B6FF0B9110FF08990CFF029903FF009800FF069302FF694731FF83C983FF73C3
            73FFB4E8C3FF4BC86DFF43C261FF39BA54FF30B246FF64C371FFFFFFFFFFCCE7
            CDFF0F9116FF0D9A13FF08990CFF029603FF068F02FF694731FF83C983FF73C3
            73FFB7EAC8FF52CC78FF48C369FF3AB555FF2DA742FF61BA6EFFFFFFFFFFCCE6
            CEFF118D19FF0F9116FF0B9110FF07930AFF068A02FF694731FF83C983FF73C2
            73FFB8EBC9FF56CE7DFF83D99EFFD5EFDAFFD2EBD6FFDDF0E0FFFFFFFFFFF4F9
            F4FFCCE6CEFFCCE7CDFFB4DCB6FF0B9110FF068502FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF93E0ACFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFE2F3E3FF129A1BFF068202FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF68D48BFF84DBA0FF82D99EFFA1E1B4FFFFFFFFFFDDF0
            E0FF64BC71FF67C575FF5CC269FF1AA427FF068002FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF57CF7FFF57CF7FFF56CD7DFF82D99DFFFFFFFFFFD2EC
            D7FF30A946FF34B54BFF30B545FF24AC35FF067C02FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF57CF7FFF84DBA0FFFFFFFFFFD5EF
            DBFF3DB759FF3DBD59FF38BB51FF2CB240FF067902FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF57CF7FFF68D48BFF93E0ACFF84D9
            9FFF4BC66EFF46C467FF40C05DFF33B64BFF067502FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF57CF7FFF57CF7FFF56CE
            7EFF54CD7BFF4FCA73FF47C568FF3ABA55FF067102FF694731FF83C983FF73C2
            73FFE0F6E8FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EB
            C9FFB7EAC8FFB5E9C5FFB2E7C1FFADE2B9FF90BB8CFF694731FF83C983FF34A6
            34FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C2
            73FF73C273FF73C273FF73C373FF73C373FF6FBE6EFF2F6E16FF}
          OnClick = SpeedButton11Click
        end
        object SpeedButton12: TSpeedButton
          Left = 536
          Top = 40
          Width = 23
          Height = 22
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF87CA87FF3673
            1DFF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C
            37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF675034FF079307FF83CA83FF6FBE
            6EFF90BC8CFF067302FF067702FF067A02FF067E02FF068202FF068502FF0688
            02FF068C02FF068F02FF069302FF069302FF0B8E05FF624B2EFF83CA83FF73C3
            73FFABE1B6FF37B850FF30B345FF29AF3BFF22AB31FF1CA828FF15A41FFF0FA0
            15FF089C0CFF029903FF009800FF009800FF069302FF694731FF83CA83FF73C3
            73FFB0E6BEFF43C362FF3CBE57FF34B84BFF2CB340FF25AF36FF1EAB2CFF16A6
            21FF0FA116FF089D0DFF029903FF009800FF069302FF694731FF83C983FF73C3
            73FFB4E8C3FF4BC86DFF43C261FF39BA54FF30B347FF29AE3CFF22AA31FF1BA6
            28FF15A11EFF0F9D15FF08990CFF029603FF068F02FF694731FF83C983FF73C3
            73FFB7EAC8FF52CC78FF48C369FF3AB555FF2DA742FF25A036FF209D2EFF1A9A
            27FF15961FFF109317FF0B9110FF07930AFF068A02FF694731FF83C983FF73C2
            73FFB8EBC9FF56CE7DFF83D99EFFD5EFDAFFD2EBD6FFD0EAD4FFCFE9D2FFCEE9
            D1FFCDE8CFFFCCE7CDFFB4DCB6FF0B9110FF068502FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF93E0ACFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFE2F3E3FF129A1BFF068202FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF68D48BFF84DBA0FF82DA9EFF7FD899FF79D491FF74D0
            89FF6ECC81FF69C979FF5CC269FF1AA427FF068002FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF57CF7FFF57CF7FFF56CE7EFF54CD7BFF4FCA73FF47C5
            67FF3FBF5CFF37BA50FF30B545FF24AC35FF067C02FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF57CF7FFF55CE7CFF4FCB
            73FF47C568FF40C05DFF38BB51FF2CB240FF067902FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF58D080FF57CF7FFF55CE
            7CFF4FCB73FF47C568FF40C05DFF33B64BFF067502FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF58D080FF58D080FF57CF
            7FFF55CE7CFF4FCB73FF47C568FF3ABA55FF067102FF694731FF83C983FF73C2
            73FFE0F6E8FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EB
            C9FFB7EAC8FFB5E9C5FFB2E7C1FFADE2B9FF90BB8CFF694731FF83C983FF34A6
            34FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C2
            73FF73C273FF73C273FF73C373FF73C373FF6FBE6EFF2F6E16FF}
          Visible = False
          OnClick = SpeedButton12Click
        end
        object SpeedButton10: TSpeedButton
          Left = 240
          Top = 40
          Width = 23
          Height = 22
          Glyph.Data = {
            36040000424D3604000000000000360000002800000010000000100000000100
            2000000000000004000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF87CA87FF3673
            1DFF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C
            37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF675034FF079307FF83CA83FF6FBE
            6EFF90BC8CFF067302FF067702FF067A02FF067E02FF068202FF068502FF0688
            02FF068C02FF068F02FF069302FF069302FF0B8E05FF624B2EFF83CA83FF73C3
            73FFABE1B6FF37B850FF30B345FF29AF3BFF22AB31FF1CA828FF15A41FFF0FA0
            15FF089C0CFF029903FF009800FF009800FF069302FF694731FF83CA83FF73C3
            73FFB0E6BEFF43C362FF3CBE57FF34B84BFF2CB340FF25AF36FF1EAB2CFF16A6
            21FF0FA116FF089D0DFF029903FF009800FF069302FF694731FF83C983FF73C3
            73FFB4E8C3FF4BC86DFF43C261FF39BA54FF30B347FF29AE3CFF22AA31FF1BA6
            28FF15A11EFF0F9D15FF08990CFF029603FF068F02FF694731FF83C983FF73C3
            73FFB7EAC8FF52CC78FF48C369FF3AB555FF2DA742FF25A036FF209D2EFF1A9A
            27FF15961FFF109317FF0B9110FF07930AFF068A02FF694731FF83C983FF73C2
            73FFB8EBC9FF56CE7DFF83D99EFFD5EFDAFFD2EBD6FFD0EAD4FFCFE9D2FFCEE9
            D1FFCDE8CFFFCCE7CDFFB4DCB6FF0B9110FF068502FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF93E0ACFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFE2F3E3FF129A1BFF068202FF694731FF83C983FF73C2
            73FFB8EBC9FF57CF7FFF68D48BFF84DBA0FF82DA9EFF7FD899FF79D491FF74D0
            89FF6ECC81FF69C979FF5CC269FF1AA427FF068002FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF57CF7FFF57CF7FFF56CE7EFF54CD7BFF4FCA73FF47C5
            67FF3FBF5CFF37BA50FF30B545FF24AC35FF067C02FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF57CF7FFF55CE7CFF4FCB
            73FF47C568FF40C05DFF38BB51FF2CB240FF067902FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF58D080FF57CF7FFF55CE
            7CFF4FCB73FF47C568FF40C05DFF33B64BFF067502FF694731FF83C983FF73C2
            73FFB8EBC9FF58D080FF58D080FF58D080FF58D080FF58D080FF58D080FF57CF
            7FFF55CE7CFF4FCB73FF47C568FF3ABA55FF067102FF694731FF83C983FF73C2
            73FFE0F6E8FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EB
            C9FFB7EAC8FFB5E9C5FFB2E7C1FFADE2B9FF90BB8CFF694731FF83C983FF34A6
            34FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C2
            73FF73C273FF73C273FF73C373FF73C373FF6FBE6EFF2F6E16FF}
          Visible = False
          OnClick = SpeedButton10Click
        end
        object Label75: TLabel
          Left = 8
          Top = 72
          Width = 117
          Height = 13
          Caption = #1053#1077' '#1086#1073#1088#1072#1073#1086#1090#1072#1085#1086' '#1087#1088#1080#1095#1080#1085':'
        end
        object Label76: TLabel
          Left = 304
          Top = 72
          Width = 153
          Height = 13
          Caption = #1053#1077' '#1086#1073#1088#1072#1073#1086#1090#1072#1085#1086' '#1087#1088#1080#1085#1103#1090#1099#1093' '#1084#1077#1088':'
        end
        object ComboBox3: TComboBox
          Left = 8
          Top = 40
          Width = 193
          Height = 21
          ItemHeight = 13
          MaxLength = 25
          TabOrder = 0
        end
        object ComboBox4: TComboBox
          Left = 304
          Top = 40
          Width = 193
          Height = 21
          ItemHeight = 13
          MaxLength = 25
          TabOrder = 1
        end
        object StaticText38: TStaticText
          Left = 128
          Top = 72
          Width = 53
          Height = 16
          AutoSize = False
          BorderStyle = sbsSingle
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Microsoft Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object StaticText39: TStaticText
          Left = 464
          Top = 69
          Width = 53
          Height = 16
          AutoSize = False
          BorderStyle = sbsSingle
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Microsoft Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
      end
      object ScrollBox1: TScrollBox
        Left = 2
        Top = -262
        Width = 581
        Height = 300
        Align = alBottom
        TabOrder = 2
        Visible = False
        object GroupBox4: TGroupBox
          Left = 0
          Top = 0
          Width = 700
          Height = 1000
          Caption = '???'
          TabOrder = 0
          Visible = False
          object Label1: TLabel
            Left = 8
            Top = 25
            Width = 54
            Height = 13
            Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image1: TImage
            Left = 88
            Top = 24
            Width = 17
            Height = 17
          end
          object Label2: TLabel
            Left = 8
            Top = 153
            Width = 16
            Height = 13
            Caption = #1044#1050
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image2: TImage
            Left = 88
            Top = 152
            Width = 17
            Height = 17
          end
          object Label3: TLabel
            Left = 168
            Top = 153
            Width = 53
            Height = 13
            Caption = #1042#1093#1086#1076' "'#1044#1050'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label4: TLabel
            Left = 8
            Top = 57
            Width = 42
            Height = 13
            Caption = #1058#1088#1077#1074#1086#1075#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label5: TLabel
            Left = 168
            Top = 57
            Width = 87
            Height = 13
            Caption = #1042#1099#1093#1086#1076' "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label6: TLabel
            Left = 8
            Top = 89
            Width = 48
            Height = 13
            Caption = #1057#1088#1072#1073#1086#1090#1082#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label7: TLabel
            Left = 8
            Top = 121
            Width = 50
            Height = 13
            Caption = #1042#1089#1082#1088#1099#1090#1080#1077
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label8: TLabel
            Left = 168
            Top = 121
            Width = 87
            Height = 13
            Caption = #1042#1093#1086#1076' "'#1042#1089#1082#1088#1099#1090#1080#1077'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label9: TLabel
            Left = 8
            Top = 185
            Width = 73
            Height = 13
            AutoSize = False
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1040#1056#1059
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image3: TImage
            Left = 264
            Top = 152
            Width = 17
            Height = 17
          end
          object Image4: TImage
            Left = 88
            Top = 56
            Width = 17
            Height = 17
          end
          object Image5: TImage
            Left = 264
            Top = 56
            Width = 17
            Height = 17
          end
          object Image6: TImage
            Left = 88
            Top = 88
            Width = 17
            Height = 17
          end
          object Image7: TImage
            Left = 88
            Top = 120
            Width = 17
            Height = 17
          end
          object Image8: TImage
            Left = 264
            Top = 120
            Width = 17
            Height = 17
          end
          object Image13: TImage
            Left = 88
            Top = 184
            Width = 17
            Height = 17
          end
          object Label51: TLabel
            Left = 8
            Top = 185
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image51: TImage
            Left = 88
            Top = 184
            Width = 17
            Height = 17
          end
          object Label52: TLabel
            Left = 8
            Top = 217
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-2'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image52: TImage
            Left = 88
            Top = 216
            Width = 17
            Height = 17
          end
          object Label53: TLabel
            Left = 8
            Top = 249
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-3'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image53: TImage
            Left = 88
            Top = 248
            Width = 17
            Height = 17
          end
          object Label54: TLabel
            Left = 8
            Top = 281
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-4'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image54: TImage
            Left = 88
            Top = 280
            Width = 17
            Height = 17
          end
          object Label55: TLabel
            Left = 8
            Top = 321
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1057#1088#1072#1073#1086#1090#1082#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image55: TImage
            Left = 88
            Top = 320
            Width = 17
            Height = 17
          end
          object Label56: TLabel
            Left = 8
            Top = 353
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1057#1088#1072#1073#1086#1090#1082#1072'-2'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image56: TImage
            Left = 88
            Top = 352
            Width = 17
            Height = 17
          end
          object Label57: TLabel
            Left = 8
            Top = 385
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1057#1088#1072#1073#1086#1090#1082#1072'-3'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image57: TImage
            Left = 88
            Top = 384
            Width = 17
            Height = 17
          end
          object Label58: TLabel
            Left = 8
            Top = 417
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1057#1088#1072#1073#1086#1090#1082#1072'-4'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image58: TImage
            Left = 88
            Top = 416
            Width = 17
            Height = 17
          end
          object Label59: TLabel
            Left = 168
            Top = 321
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1093#1086#1076' 1 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image59: TImage
            Left = 264
            Top = 320
            Width = 17
            Height = 17
          end
          object Label60: TLabel
            Left = 168
            Top = 353
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1093#1086#1076' 2 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image60: TImage
            Left = 264
            Top = 352
            Width = 17
            Height = 17
          end
          object Label61: TLabel
            Left = 168
            Top = 385
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1093#1086#1076' 3 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image61: TImage
            Left = 264
            Top = 384
            Width = 17
            Height = 17
          end
          object Label62: TLabel
            Left = 168
            Top = 417
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1093#1086#1076' 4 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image62: TImage
            Left = 264
            Top = 416
            Width = 17
            Height = 17
          end
          object Label69: TLabel
            Left = 344
            Top = 321
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1099#1093#1086#1076' 1 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image69: TImage
            Left = 448
            Top = 320
            Width = 17
            Height = 17
          end
          object Label70: TLabel
            Left = 344
            Top = 353
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1099#1093#1086#1076' 2 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image70: TImage
            Left = 448
            Top = 352
            Width = 17
            Height = 17
          end
          object Label71: TLabel
            Left = 344
            Top = 385
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1099#1093#1086#1076' 3 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image71: TImage
            Left = 448
            Top = 384
            Width = 17
            Height = 17
          end
          object Label72: TLabel
            Left = 344
            Top = 417
            Width = 121
            Height = 13
            AutoSize = False
            Caption = #1042#1099#1093#1086#1076' 4 "'#1058#1088#1077#1074#1086#1075#1072'"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image72: TImage
            Left = 448
            Top = 416
            Width = 17
            Height = 17
          end
          object Label34: TLabel
            Left = 352
            Top = 152
            Width = 122
            Height = 13
            Caption = #1050#1086#1085#1092#1080#1075#1091#1088#1072#1094#1080#1103' "'#1058#1088#1077#1074#1086#1075'"'
          end
          object Label35: TLabel
            Left = 168
            Top = 25
            Width = 116
            Height = 13
            Caption = #1042#1099#1093#1086#1076' "'#1058#1088#1077#1074#1086#1075#1072'='#1060#1083'1"'
          end
          object Image75: TImage
            Left = 296
            Top = 24
            Width = 17
            Height = 17
          end
          object Label36: TLabel
            Left = 168
            Top = 89
            Width = 48
            Height = 13
            Caption = #1057#1088#1072#1073#1086#1090#1082#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image76: TImage
            Left = 296
            Top = 88
            Width = 17
            Height = 17
          end
          object Label77: TLabel
            Left = 210
            Top = 185
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image77: TImage
            Left = 280
            Top = 184
            Width = 20
            Height = 49
            Stretch = True
          end
          object Label95: TLabel
            Left = 400
            Top = 185
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label85: TLabel
            Left = 8
            Top = 185
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label86: TLabel
            Left = 8
            Top = 217
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label87: TLabel
            Left = 8
            Top = 249
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label88: TLabel
            Left = 8
            Top = 281
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label89: TLabel
            Left = 8
            Top = 321
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label90: TLabel
            Left = 8
            Top = 353
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label91: TLabel
            Left = 8
            Top = 385
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label92: TLabel
            Left = 8
            Top = 417
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label78: TLabel
            Left = 210
            Top = 217
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label79: TLabel
            Left = 210
            Top = 249
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label80: TLabel
            Left = 210
            Top = 281
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label81: TLabel
            Left = 210
            Top = 321
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label82: TLabel
            Left = 210
            Top = 353
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label83: TLabel
            Left = 210
            Top = 385
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label84: TLabel
            Left = 210
            Top = 417
            Width = 46
            Height = 13
            Caption = #1054#1093#1088#1072#1085#1072'-1'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label96: TLabel
            Left = 400
            Top = 217
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label97: TLabel
            Left = 400
            Top = 249
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label98: TLabel
            Left = 400
            Top = 281
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label99: TLabel
            Left = 400
            Top = 321
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label100: TLabel
            Left = 392
            Top = 353
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label101: TLabel
            Left = 392
            Top = 385
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label102: TLabel
            Left = 392
            Top = 417
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image78: TImage
            Left = 296
            Top = 216
            Width = 17
            Height = 17
          end
          object Image79: TImage
            Left = 296
            Top = 248
            Width = 17
            Height = 17
          end
          object Image80: TImage
            Left = 272
            Top = 248
            Width = 20
            Height = 49
            Stretch = True
          end
          object Image81: TImage
            Left = 288
            Top = 312
            Width = 17
            Height = 17
          end
          object Image82: TImage
            Left = 288
            Top = 344
            Width = 17
            Height = 17
          end
          object Image83: TImage
            Left = 176
            Top = 208
            Width = 20
            Height = 49
            Stretch = True
          end
          object Image84: TImage
            Left = 288
            Top = 408
            Width = 17
            Height = 17
          end
          object Label292: TLabel
            Left = 376
            Top = 17
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label293: TLabel
            Left = 376
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image293: TImage
            Left = 376
            Top = 48
            Width = 17
            Height = 17
          end
          object Image294: TImage
            Left = 400
            Top = 48
            Width = 17
            Height = 17
          end
          object Label294: TLabel
            Left = 424
            Top = 17
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label295: TLabel
            Left = 424
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label296: TLabel
            Left = 392
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label297: TLabel
            Left = 440
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label298: TLabel
            Left = 392
            Top = 49
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label299: TLabel
            Left = 440
            Top = 49
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image297: TImage
            Left = 392
            Top = 64
            Width = 17
            Height = 17
          end
          object Image298: TImage
            Left = 416
            Top = 64
            Width = 17
            Height = 17
          end
          object Label300: TLabel
            Left = 408
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label301: TLabel
            Left = 456
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label302: TLabel
            Left = 408
            Top = 49
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label303: TLabel
            Left = 456
            Top = 49
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image301: TImage
            Left = 408
            Top = 64
            Width = 17
            Height = 17
          end
          object Image302: TImage
            Left = 432
            Top = 64
            Width = 17
            Height = 17
          end
          object Label304: TLabel
            Left = 528
            Top = 17
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label305: TLabel
            Left = 576
            Top = 17
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label306: TLabel
            Left = 528
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label307: TLabel
            Left = 576
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Image305: TImage
            Left = 176
            Top = 184
            Width = 20
            Height = 49
            Stretch = True
          end
          object Image306: TImage
            Left = 552
            Top = 48
            Width = 17
            Height = 17
          end
          object Bevel1: TBevel
            Left = 8
            Top = 144
            Width = 585
            Height = 17
            Shape = bsTopLine
            Visible = False
          end
          object Label43: TLabel
            Left = 40
            Top = 160
            Width = 38
            Height = 13
            Caption = 'Label43'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label44: TLabel
            Left = 464
            Top = 57
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label45: TLabel
            Left = 536
            Top = 41
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label46: TLabel
            Left = 544
            Top = 49
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Bevel2: TBevel
            Left = 8
            Top = 152
            Width = 585
            Height = 17
            Shape = bsTopLine
            Visible = False
          end
          object Label47: TLabel
            Left = 552
            Top = 57
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label48: TLabel
            Left = 416
            Top = 57
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label49: TLabel
            Left = 424
            Top = 65
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label50: TLabel
            Left = 536
            Top = 25
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label63: TLabel
            Left = 544
            Top = 33
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label64: TLabel
            Left = 552
            Top = 41
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Bevel3: TBevel
            Left = 8
            Top = 160
            Width = 585
            Height = 17
            Shape = bsTopLine
            Visible = False
          end
          object Label65: TLabel
            Left = 472
            Top = 65
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label66: TLabel
            Left = 480
            Top = 73
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label67: TLabel
            Left = 488
            Top = 81
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label103: TLabel
            Left = 400
            Top = 393
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label68: TLabel
            Left = 408
            Top = 193
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label73: TLabel
            Left = 416
            Top = 201
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Label74: TLabel
            Left = 424
            Top = 209
            Width = 44
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsUnderline]
            ParentFont = False
          end
          object Bevel4: TBevel
            Left = 8
            Top = 168
            Width = 585
            Height = 17
            Shape = bsTopLine
            Visible = False
          end
          object StaticText2: TStaticText
            Left = 112
            Top = 24
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object StaticText3: TStaticText
            Left = 112
            Top = 152
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
          end
          object StaticText4: TStaticText
            Left = 288
            Top = 152
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
          end
          object StaticText5: TStaticText
            Left = 112
            Top = 56
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 3
          end
          object StaticText6: TStaticText
            Left = 288
            Top = 56
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 4
          end
          object StaticText7: TStaticText
            Left = 112
            Top = 88
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 5
          end
          object StaticText8: TStaticText
            Left = 112
            Top = 120
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 6
          end
          object StaticText9: TStaticText
            Left = 288
            Top = 120
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 7
          end
          object StaticText10: TStaticText
            Left = 112
            Top = 184
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 8
          end
          object StaticText51: TStaticText
            Left = 112
            Top = 184
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 9
          end
          object StaticText52: TStaticText
            Left = 112
            Top = 216
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 10
          end
          object StaticText53: TStaticText
            Left = 112
            Top = 248
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 11
          end
          object StaticText54: TStaticText
            Left = 112
            Top = 280
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 12
          end
          object StaticText55: TStaticText
            Left = 112
            Top = 320
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 13
          end
          object StaticText56: TStaticText
            Left = 112
            Top = 352
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 14
          end
          object StaticText57: TStaticText
            Left = 112
            Top = 384
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 15
          end
          object StaticText58: TStaticText
            Left = 112
            Top = 416
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 16
          end
          object StaticText59: TStaticText
            Left = 296
            Top = 320
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 17
          end
          object StaticText60: TStaticText
            Left = 288
            Top = 352
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 18
          end
          object StaticText61: TStaticText
            Left = 288
            Top = 384
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 19
          end
          object StaticText62: TStaticText
            Left = 288
            Top = 416
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 20
          end
          object StaticText69: TStaticText
            Left = 472
            Top = 320
            Width = 73
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 21
          end
          object StaticText70: TStaticText
            Left = 472
            Top = 352
            Width = 73
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 22
          end
          object StaticText71: TStaticText
            Left = 472
            Top = 384
            Width = 73
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 23
          end
          object StaticText72: TStaticText
            Left = 472
            Top = 416
            Width = 73
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 24
          end
          object StaticText11: TStaticText
            Left = 480
            Top = 152
            Width = 89
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 25
          end
          object StaticText75: TStaticText
            Left = 320
            Top = 24
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 26
          end
          object StaticText76: TStaticText
            Left = 320
            Top = 88
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 27
          end
          object StaticText77: TStaticText
            Left = 320
            Top = 184
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 28
          end
          object StaticText95: TStaticText
            Left = 452
            Top = 184
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 29
          end
          object StaticText78: TStaticText
            Left = 320
            Top = 216
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 30
          end
          object StaticText79: TStaticText
            Left = 320
            Top = 248
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 31
          end
          object StaticText80: TStaticText
            Left = 320
            Top = 280
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 32
          end
          object StaticText81: TStaticText
            Left = 320
            Top = 312
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 33
          end
          object StaticText82: TStaticText
            Left = 320
            Top = 344
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 34
          end
          object StaticText83: TStaticText
            Left = 320
            Top = 376
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 35
          end
          object StaticText84: TStaticText
            Left = 320
            Top = 408
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 36
          end
          object StaticText96: TStaticText
            Left = 448
            Top = 216
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 37
          end
          object StaticText97: TStaticText
            Left = 448
            Top = 248
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 38
          end
          object StaticText98: TStaticText
            Left = 448
            Top = 280
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 39
          end
          object StaticText99: TStaticText
            Left = 448
            Top = 320
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 40
          end
          object StaticText100: TStaticText
            Left = 448
            Top = 352
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 41
          end
          object StaticText101: TStaticText
            Left = 448
            Top = 384
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 42
          end
          object StaticText102: TStaticText
            Left = 448
            Top = 416
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 43
          end
          object StaticText293: TStaticText
            Left = 376
            Top = 72
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 44
          end
          object StaticText294: TStaticText
            Left = 376
            Top = 96
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 45
          end
          object StaticText295: TStaticText
            Left = 372
            Top = 112
            Width = 157
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 46
          end
          object StaticText297: TStaticText
            Left = 392
            Top = 88
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 47
          end
          object StaticText298: TStaticText
            Left = 392
            Top = 112
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 48
          end
          object StaticText299: TStaticText
            Left = 388
            Top = 128
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 49
          end
          object StaticText301: TStaticText
            Left = 408
            Top = 88
            Width = 41
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 50
          end
          object StaticText302: TStaticText
            Left = 408
            Top = 112
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 51
          end
          object StaticText303: TStaticText
            Left = 404
            Top = 128
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 52
          end
          object StaticText305: TStaticText
            Left = 528
            Top = 72
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 53
          end
          object StaticText306: TStaticText
            Left = 528
            Top = 96
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 54
          end
          object StaticText307: TStaticText
            Left = 524
            Top = 112
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 55
          end
          object StaticText12: TStaticText
            Left = 460
            Top = 192
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 56
          end
          object StaticText13: TStaticText
            Left = 536
            Top = 80
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 57
          end
          object StaticText14: TStaticText
            Left = 544
            Top = 88
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 58
          end
          object StaticText17: TStaticText
            Left = 416
            Top = 96
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 59
          end
          object StaticText18: TStaticText
            Left = 424
            Top = 104
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 60
          end
          object StaticText19: TStaticText
            Left = 432
            Top = 112
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 61
          end
          object StaticText103: TStaticText
            Left = 456
            Top = 360
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 62
          end
          object StaticText20: TStaticText
            Left = 456
            Top = 224
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 63
          end
          object StaticText21: TStaticText
            Left = 464
            Top = 232
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 64
          end
          object StaticText22: TStaticText
            Left = 472
            Top = 240
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 65
          end
          object StaticText23: TStaticText
            Left = 440
            Top = 120
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 66
          end
          object StaticText24: TStaticText
            Left = 448
            Top = 128
            Width = 70
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 67
          end
          object StaticText25: TStaticText
            Left = 200
            Top = 232
            Width = 208
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 68
          end
          object StaticText26: TStaticText
            Left = 208
            Top = 240
            Width = 208
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 69
          end
          object StaticText27: TStaticText
            Left = 216
            Top = 248
            Width = 208
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 70
          end
          object StaticText28: TStaticText
            Left = 224
            Top = 256
            Width = 208
            Height = 17
            AutoSize = False
            BorderStyle = sbsSunken
            Caption = '???'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Microsoft Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 71
          end
        end
      end
      object GroupBox10: TGroupBox
        Left = 2
        Top = 131
        Width = 581
        Height = 368
        Align = alBottom
        Caption = '???'
        TabOrder = 3
        Visible = False
        object AdvStringGrid1: TAdvStringGrid
          Left = 2
          Top = 15
          Width = 577
          Height = 351
          Cursor = crDefault
          Align = alClient
          ColCount = 3
          DefaultColWidth = 200
          DefaultRowHeight = 21
          DefaultDrawing = False
          FixedCols = 0
          RowCount = 5
          FixedRows = 1
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GridLineWidth = 1
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected]
          ParentFont = False
          TabOrder = 0
          GridLineColor = clSilver
          ActiveCellShow = False
          ActiveCellFont.Charset = DEFAULT_CHARSET
          ActiveCellFont.Color = clWindowText
          ActiveCellFont.Height = -11
          ActiveCellFont.Name = 'Microsoft Sans Serif'
          ActiveCellFont.Style = [fsBold]
          Bands.PrimaryColor = clInfoBk
          Bands.PrimaryLength = 1
          Bands.SecondaryColor = clWindow
          Bands.SecondaryLength = 1
          Bands.Print = False
          AutoNumAlign = False
          AutoSize = False
          VAlignment = vtaCenter
          EnhTextSize = True
          EnhRowColMove = False
          SizeWithForm = False
          Multilinecells = True
          OnGetCellColor = AdvStringGrid1GetCellColor
          OnGetAlignment = AdvStringGrid1GetAlignment
          DragDropSettings.OleAcceptFiles = True
          DragDropSettings.OleAcceptText = True
          SortSettings.AutoColumnMerge = False
          SortSettings.Column = 0
          SortSettings.Show = False
          SortSettings.IndexShow = False
          SortSettings.Full = True
          SortSettings.SingleColumn = False
          SortSettings.IgnoreBlanks = False
          SortSettings.BlankPos = blFirst
          SortSettings.AutoFormat = True
          SortSettings.Direction = sdAscending
          SortSettings.FixedCols = False
          SortSettings.NormalCellsOnly = False
          SortSettings.Row = 0
          FloatingFooter.Color = clBtnFace
          FloatingFooter.Column = 0
          FloatingFooter.FooterStyle = fsFixedLastRow
          FloatingFooter.Visible = False
          ControlLook.Color = clBlack
          ControlLook.CheckSize = 15
          ControlLook.RadioSize = 10
          ControlLook.ControlStyle = csClassic
          ControlLook.FlatButton = False
          EnableHTML = True
          EnableWheel = True
          Flat = False
          HintColor = clInfoBk
          SelectionColor = clHighlight
          SelectionTextColor = clHighlightText
          SelectionRectangle = False
          SelectionRTFKeep = False
          HintShowCells = False
          HintShowLargeText = False
          HintShowSizing = False
          PrintSettings.FooterSize = 0
          PrintSettings.HeaderSize = 0
          PrintSettings.Time = ppNone
          PrintSettings.Date = ppNone
          PrintSettings.DateFormat = 'dd/mm/yyyy'
          PrintSettings.PageNr = ppNone
          PrintSettings.Title = ppNone
          PrintSettings.Font.Charset = DEFAULT_CHARSET
          PrintSettings.Font.Color = clWindowText
          PrintSettings.Font.Height = -11
          PrintSettings.Font.Name = 'Microsoft Sans Serif'
          PrintSettings.Font.Style = []
          PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
          PrintSettings.HeaderFont.Color = clWindowText
          PrintSettings.HeaderFont.Height = -11
          PrintSettings.HeaderFont.Name = 'Microsoft Sans Serif'
          PrintSettings.HeaderFont.Style = []
          PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
          PrintSettings.FooterFont.Color = clWindowText
          PrintSettings.FooterFont.Height = -11
          PrintSettings.FooterFont.Name = 'Microsoft Sans Serif'
          PrintSettings.FooterFont.Style = []
          PrintSettings.Borders = pbNoborder
          PrintSettings.BorderStyle = psSolid
          PrintSettings.Centered = False
          PrintSettings.RepeatFixedRows = False
          PrintSettings.RepeatFixedCols = False
          PrintSettings.LeftSize = 0
          PrintSettings.RightSize = 0
          PrintSettings.ColumnSpacing = 0
          PrintSettings.RowSpacing = 0
          PrintSettings.TitleSpacing = 0
          PrintSettings.Orientation = poPortrait
          PrintSettings.FixedWidth = 0
          PrintSettings.FixedHeight = 0
          PrintSettings.UseFixedHeight = False
          PrintSettings.UseFixedWidth = False
          PrintSettings.FitToPage = fpNever
          PrintSettings.PageNumSep = '/'
          PrintSettings.NoAutoSize = False
          PrintSettings.PrintGraphics = False
          HTMLSettings.Width = 100
          HTMLSettings.XHTML = False
          Navigation.AdvanceDirection = adLeftRight
          Navigation.AllowClipboardRowGrow = True
          Navigation.AllowClipboardColGrow = True
          Navigation.InsertPosition = pInsertBefore
          Navigation.CopyHTMLTagsToClipboard = True
          Navigation.HomeEndKey = heFirstLastColumn
          ColumnSize.Location = clRegistry
          CellNode.Color = clSilver
          CellNode.NodeColor = clBlack
          CellNode.ShowTree = False
          MaxEditLength = 0
          IntelliPan = ipVertical
          URLColor = clBlue
          URLShow = False
          URLFull = False
          URLEdit = False
          ScrollType = ssNormal
          ScrollColor = clNone
          ScrollWidth = 16
          ScrollSynch = False
          ScrollProportional = False
          ScrollHints = shNone
          OemConvert = False
          FixedFooters = 0
          FixedRightCols = 0
          FixedColWidth = 200
          FixedRowHeight = 21
          FixedFont.Charset = DEFAULT_CHARSET
          FixedFont.Color = clWindowText
          FixedFont.Height = -11
          FixedFont.Name = 'Tahoma'
          FixedFont.Style = []
          FixedAsButtons = False
          FloatFormat = '%.2f'
          IntegralHeight = False
          WordWrap = False
          Lookup = False
          LookupCaseSensitive = False
          LookupHistory = False
          ShowSelection = False
          BackGround.Top = 0
          BackGround.Left = 0
          BackGround.Display = bdTile
          BackGround.Cells = bcNormal
          Filter = <>
          ColWidths = (
            200
            200
            200)
          RowHeights = (
            21
            21
            21
            21
            21)
        end
      end
    end
    object GroupBox7: TGroupBox
      Left = 1
      Top = 1
      Width = 145
      Height = 501
      Align = alLeft
      Caption = #1056#1040#1057#1058#1056
      TabOrder = 0
      object RastrTree: TTreeView
        Left = 2
        Top = 15
        Width = 141
        Height = 406
        Align = alClient
        Images = ImageList1
        Indent = 19
        ReadOnly = True
        TabOrder = 0
        OnClick = RastrTreeClick
        OnKeyUp = RastrTreeKeyUp
      end
      object StaticText15: TStaticText
        Left = 2
        Top = 421
        Width = 141
        Height = 17
        Align = alBottom
        AutoSize = False
        BorderStyle = sbsSunken
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
      end
      object GroupBox8: TGroupBox
        Left = 2
        Top = 438
        Width = 141
        Height = 61
        Align = alBottom
        TabOrder = 2
        object SpeedButton1: TSpeedButton
          Left = 5
          Top = 8
          Width = 32
          Height = 25
          Hint = #1042#1083#1077#1074#1086
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            1800000000000003000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0
            B0A0C0B0A0C0B0A0FFFFFF604830FFFFFF604830FFFFFFFFFFFFFFFFFFC0B0A0
            FFFFFFFFFFFFFFFFFFFCFBFAF8F5F3F4EFEDF0EAE6836E59FFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FFFFFFFFFFFFFCFBFA800000F4EFEDF0
            EAE6D0B8B07E6953FFFFFFFFFFFFFFFFFF604830FFFFFFFFFFFFFFFFFFC0B0A0
            FFFFFFFCFBFA800000800000F0EAE6EDE5E0D0B8B078634CFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FCFBFA80000080000080000080000080
            0000800000800000800000800000FFFFFF604830FFFFFFFFFFFFFFFFFFC0B0A0
            F8F5F3F4EFED800000800000E9DED8E5D8D0D0B8B06C553EFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0F4EFEDF0EAE6EDE5E0800000E5D8D0E0
            D1C8D0B8B0664F37FFFFFFFFFFFFFFFFFF604830FFFFFFFFFFFFFFFFFFC0B0A0
            F0EAE6D0B8B0D0B8B0D0B8B0D0B8B0D0B8B0D0B8B0604830FFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0836E597E695378634C725C456C553E66
            4F37604830604830FFFFFF604830FFFFFF604830FFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
          Transparent = False
          OnMouseDown = SpeedButton1MouseDown
          OnMouseUp = SpeedButton1MouseUp
        end
        object SpeedButton2: TSpeedButton
          Left = 38
          Top = 8
          Width = 32
          Height = 25
          Hint = #1042#1087#1088#1072#1074#1086
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            1800000000000003000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            604830FFFFFF604830FFFFFFC0B0A0836E597E695378634C725C456C553E664F
            37604830604830FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0F0
            EAE6D0B8B0D0B8B0D0B8B0D0B8B0D0B8B0D0B8B0604830FFFFFFFFFFFFFFFFFF
            604830FFFFFFFFFFFFFFFFFFC0B0A0F4EFEDF0EAE6EDE5E0800000E5D8D0E0D1
            C8D0B8B0664F37FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0F8
            F5F3F4EFEDF0EAE6800000800000E5D8D0D0B8B06C553EFFFFFFFFFFFFFFFFFF
            604830FFFFFF8000008000008000008000008000008000008000008000008000
            00D0B8B0725C45FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FF
            FFFFFCFBFAF8F5F3800000800000EDE5E0D0B8B078634CFFFFFFFFFFFFFFFFFF
            604830FFFFFFFFFFFFFFFFFFC0B0A0FFFFFFFFFFFFFCFBFA800000F4EFEDF0EA
            E6D0B8B07E6953FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FF
            FFFFFFFFFFFFFFFFFCFBFAF8F5F3F4EFEDF0EAE6836E59FFFFFFFFFFFFFFFFFF
            604830FFFFFF604830FFFFFFC0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0
            A0C0B0A0C0B0A0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
          OnMouseDown = SpeedButton2MouseDown
          OnMouseUp = SpeedButton2MouseUp
        end
        object SpeedButton3: TSpeedButton
          Left = 71
          Top = 8
          Width = 32
          Height = 25
          Hint = #1042#1074#1077#1088#1093
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            1800000000000003000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFF604830FFFFFF604830FFFFFF604830FFFFFF604830FFFFFF604830FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFF604830FFFFFFFFFFFFFFFFFF800000FFFFFFFFFFFFFFFFFF604830FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF80
            0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0836E597E695378634C8000006C553E664F37604830604830FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0F0EAE6D0B8B0D0B8B080
            0000D0B8B0D0B8B0D0B8B0604830FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0F4EFEDF0EAE6EDE5E0800000E5D8D0E0D1C8D0B8B0664F37FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0F8F5F3F4EFEDF0EAE680
            0000E9DED8E5D8D0D0B8B06C553EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0FCFBFA800000800000800000800000800000D0B8B0725C45FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FFFFFFFCFBFA80000080
            0000800000EDE5E0D0B8B078634CFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0FFFFFFFFFFFFFCFBFA800000F4EFEDF0EAE6D0B8B07E6953FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FFFFFFFFFFFFFFFFFFFC
            FBFAF8F5F3F4EFEDF0EAE6836E59FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0A0C0B0A0FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
          OnMouseDown = SpeedButton3MouseDown
          OnMouseUp = SpeedButton3MouseUp
        end
        object SpeedButton4: TSpeedButton
          Left = 104
          Top = 8
          Width = 32
          Height = 25
          Hint = #1042#1085#1080#1079
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            1800000000000003000000000000000000000000000000000000FFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0836E597E695378634C72
            5C456C553E664F37604830604830FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0F0EAE6D0B8B0D0B8B0D0B8B0D0B8B0D0B8B0D0B8B0604830FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0F4EFEDF0EAE6EDE5E080
            0000E5D8D0E0D1C8D0B8B0664F37FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0F8F5F3F4EFED800000800000800000E5D8D0D0B8B06C553EFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FCFBFA80000080000080
            0000800000800000D0B8B0725C45FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0FFFFFFFCFBFAF8F5F3800000F0EAE6EDE5E0D0B8B078634CFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0FFFFFFFFFFFFFCFBFA80
            0000F4EFEDF0EAE6D0B8B07E6953FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFC0B0A0FFFFFFFFFFFFFFFFFF800000F8F5F3F4EFEDF0EAE6836E59FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC0B0A0C0B0A0C0B0A0C0B0A080
            0000C0B0A0C0B0A0C0B0A0C0B0A0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF800000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF604830FFFFFFFFFFFFFFFFFF80
            0000FFFFFFFFFFFFFFFFFF604830FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF604830FFFFFF604830FFFFFF60
            4830FFFFFF604830FFFFFF604830FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
          OnMouseDown = SpeedButton4MouseDown
          OnMouseUp = SpeedButton4MouseUp
        end
        object SpeedButton5: TSpeedButton
          Left = 5
          Top = 32
          Width = 32
          Height = 25
          Hint = #1059#1074#1077#1083#1080#1095#1080#1090#1100
          Glyph.Data = {
            36050000424D3605000000000000360400002800000010000000100000000100
            0800000000000001000000000000000000000001000000010000000000001B31
            500025355000233856004550790072747C0098300000C5742D0083716D00927C
            7600997E75003A4B84003B4D87003C4E8A0040639D0072798000777D8A00386B
            C000386CC000548ABC007D90AA00598ED5004D99DE005F93D7006995D500459A
            EB004199EE00479FF2005BABF10068ADEE006CB2F100898280008F8280008D84
            8200968480009C8883009C8A8600918A8800938C8A00A88D8100AC908200AC91
            8500B1948700B1968E00B99E8E00A1959300A4969300AA949000BDA29300BEA3
            9400BFA49B00BBA39D00BCA19C00BEA5A000C4A99300C8AF9E00C7B09900CAB3
            9A00CBB69F00C3AEAA00CDB7A200D2BDA200D6C3A800D7C7AA00DCCCAE00DECF
            B100E0CEAD00FFDBA100FFDDA300FFDEA500E1D3B200E8D8B300EADCBA00FFE5
            AE00FFE6B000FFE4B500FFE8B100FEE9B500F7EABD00F5ECBF00FEEEBA00FFEB
            BC00FFECBF00FFE7C000F1EAC300F7EFC300F2ECC400F2EBCE00FFF2C000FBF3
            C600FCF0CB00FFF9CE00FFEED600FDF1D100F5F1DB00FEF2DA00FFF2DD00FEFA
            DD00FFF3E000FFFBF600FEFEFC00000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000640502646464
            646464646464646464640F0E0C036464646464646464646464641319110C0164
            64646464646464646464151D1B110D016464646464646464646464171E191204
            64642E242221646464646464151C1610082A3D4742360A216464646464181424
            3A4F4D525D5D4827256464646464642C55494B07066060420964646464643B40
            4D4353070660605A28256464646434554B060607060606523A20646464643554
            4D07070707070749382E64646464643E61635C070643454F2864646464646431
            5E646007064350402F6464646464646437575B585858462B6464646464646464
            64343C413E313464646464646464646464646464646464646464}
          OnMouseDown = SpeedButton5MouseDown
          OnMouseUp = SpeedButton5MouseUp
        end
        object SpeedButton6: TSpeedButton
          Left = 38
          Top = 32
          Width = 32
          Height = 25
          Hint = #1059#1084#1077#1085#1100#1096#1080#1090#1100
          Glyph.Data = {
            36050000424D3605000000000000360400002800000010000000100000000100
            0800000000000001000000000000000000000001000000010000000000001B31
            500025355000233856004550790072747C0098300000C5742D0083716D00927C
            7600997E75003A4B84003B4D87003C4E8A0040639D0072798000777D8A00386B
            C000386CC000548ABC007D90AA00598ED5004D99DE005F93D7006995D500459A
            EB004199EE00479FF2005BABF10068ADEE006CB2F100898280008F8280008D84
            8200968480009C8883009C8A8600918A8800938C8A00A88D8100AC908200AC91
            8500B1948700B1968E00B99E8E00A1959300A4969300AA949000BDA29300BEA3
            9400BFA49B00BBA39D00BCA19C00BEA5A000C4A99300C8AF9E00C7B09900CAB3
            9A00CBB69F00C3AEAA00CDB7A200D2BDA200FFD89D00D6C3A800D7C7AA00DCCC
            AE00DECFB100E0CEAD00FFD9A100FFDDA300FFDDA500E1D3B200E8D8B300EADC
            BA00FFE5AE00FFE6B000FFE4B500FFE8B100FEE9B500F7EABD00F5ECBF00FEEE
            BA00FFEBBC00FFECBF00FFE7C000F1EAC300F7EFC300F2ECC400F2EBCE00FFF2
            C000FBF3C600FCF0CB00FFF9CE00FFEFD100FFEED500FDF1D100F5F1DB00FEF1
            D900FFF2DD00FEFADD00FFF3E000FFFBF600FEFEFC0000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000000000000000
            0000000000000000000000000000000000000000000000000000660502666666
            666666666666666666660F0E0C036666666666666666666666661319110C0166
            66666666666666666666151D1B110D016666666666666666666666171E191204
            66662E242221666666666666151C1610082A3D4843360A216666666666181424
            3A504E535F5F4927256666666666662C564A4C5D616161420966666666663B41
            4E45545D6164615B28256666666634564C070606060606533A20666666663555
            4E0707070707064C382E66666666663F63655D45454646502866666666666631
            60666144444553412F6666666666666637585C595959472B6666666666666666
            66343C423F313466666666666666666666666666666666666666}
          OnMouseDown = SpeedButton6MouseDown
          OnMouseUp = SpeedButton6MouseUp
        end
        object SpeedButton7: TSpeedButton
          Left = 71
          Top = 32
          Width = 32
          Height = 25
          Hint = #1060#1086#1082#1091#1089' '#1073#1083#1080#1078#1077
          Glyph.Data = {
            AA030000424DAA03000000000000360000002800000011000000110000000100
            1800000000007403000000000000000000000000000000000000C8D0D4C8D0D4
            C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000
            000000000000000000000000000000000000C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000FFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFF000000000000C8D0D4C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8
            D0D4C8D0D4000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000C8D0D4
            C8D0D4C8D0D4C8D0D46CC8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000FFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFF000000C8D0D4000000C8D0D4C8D0D4C8D0D4FFC8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D4000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
            0000C8D0D4000000C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C8D0D4C8D0D4000000C8
            D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D40000000000000000000000
            00000000000000000000C8D0D4C8D0D4000000C8D0D4C8D0D400C8D0D4C8D0D4
            C8D0D4C8D0D4C8D0D4C8D0D4000000000000C8D0D4C8D0D4C8D0D4C8D0D40000
            00C8D0D4C8D0D4000000C8D0D400C8D0D47B00007B00007B00007B0000C8D0D4
            C8D0D4C8D0D4000000000000C8D0D4C8D0D4C8D0D4000000C8D0D4000000C8D0
            D400C8D0D47B00007B00007B0000C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4
            000000000000C8D0D4C8D0D4000000000000C8D0D400C8D0D47B0000C8D0D47B
            7B7B7B00007B0000C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000000000
            000000000000C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D47B7B7B7B00007B
            0000C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D400C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D47B7B7B7B00007B0000C8D0D4C8
            D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D47B7B7B7B00007B0000C8D0D4C8D0D4C8D0D4C8
            D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D47B7B7B7B00007B0000C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4
            C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D400}
          OnMouseDown = SpeedButton7MouseDown
          OnMouseUp = SpeedButton7MouseUp
        end
        object SpeedButton8: TSpeedButton
          Left = 104
          Top = 32
          Width = 32
          Height = 25
          Hint = #1060#1086#1082#1091#1089' '#1076#1072#1083#1100#1096#1077
          Glyph.Data = {
            AA030000424DAA03000000000000360000002800000011000000110000000100
            1800000000007403000000000000000000000000000000000000C8D0D4C8D0D4
            C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D46DC8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000
            000000000000000000000000000000000000C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D465C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000FFFFFFFFFFFFFFFFFFFFFFFF
            FFFFFF000000000000C8D0D4C8D0D4C8D0D4C8D0D475C8D0D4C8D0D4C8D0D4C8
            D0D4C8D0D4000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000C8D0D4
            C8D0D4C8D0D4C8D0D461C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000FFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFF000000C8D0D4000000C8D0D4C8D0D4C8D0D400C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D4000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
            0000C8D0D4000000C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C8D0D4C8D0D4000000C8
            D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D40000000000000000000000
            00000000000000000000C8D0D4C8D0D4000000C8D0D4C8D0D400C8D0D4C8D0D4
            C8D0D4C8D0D4C8D0D4C8D0D4000000000000C8D0D4C8D0D4C8D0D4C8D0D40000
            00C8D0D4C8D0D4000000C8D0D400C8D0D47B0000C8D0D4C8D0D4C8D0D4C8D0D4
            C8D0D4C8D0D4000000000000C8D0D4C8D0D4C8D0D4000000C8D0D4000000C8D0
            D400C8D0D47B7B7B7B00007B0000C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4
            000000000000C8D0D4C8D0D4000000000000C8D0D400C8D0D4C8D0D4C8D0D47B
            7B7B7B00007B0000C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4000000000000
            000000000000C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D47B7B7B7B00007B
            0000C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D400C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D47B7B7B7B00007B0000C8D0D47B
            7B7B7B0000C8D0D4C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D47B7B7B7B00007B00007B0000C8D0D4C8D0D4C8
            D0D4C8D0D400C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D47B00007B00007B00007B0000C8D0D4C8D0D4C8D0D4C8D0D400C8D0D4C8D0D4
            C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0D4C8D0
            D4C8D0D4C8D0D4C8D0D4C8D0D400}
          OnMouseDown = SpeedButton8MouseDown
          OnMouseUp = SpeedButton8MouseUp
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Images = ImageList1
    Left = 616
    Top = 16
    object ZhurnalItems: TMenuItem
      Caption = #1046#1091#1088#1085#1072#1083
      object ZhurnalToDbItem: TMenuItem
        Caption = #1053#1086#1074#1072#1103' '#1089#1084#1077#1085#1072
        Hint = #1053#1072#1095#1072#1090#1100' '#1085#1086#1074#1091#1102' '#1089#1084#1077#1085#1091
        ImageIndex = 29
        OnClick = ZhurnalToDbItemClick
      end
      object N12: TMenuItem
        Caption = '-'
        Visible = False
      end
      object ZhurnalPrintItem: TMenuItem
        Caption = #1055#1077#1095#1072#1090#1100
        Enabled = False
        Hint = #1042#1099#1074#1086#1076' '#1085#1072' '#1087#1077#1095#1072#1090#1100' '#1078#1091#1088#1085#1072#1083#1072' '#1089#1086#1073#1099#1090#1080#1081
        ImageIndex = 30
        Visible = False
        OnClick = ZhurnalPrintItemClick
      end
      object ZhurnalPrintViewItem: TMenuItem
        Caption = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088
        Enabled = False
        Hint = #1055#1088#1077#1076#1074#1072#1088#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088' '#1078#1091#1088#1085#1072#1083#1072' '#1089#1086#1073#1099#1090#1080#1081
        Visible = False
        OnClick = ZhurnalPrintViewItemClick
      end
      object SpoolerClearItem: TMenuItem
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1086#1095#1077#1088#1077#1076#1100' '#1087#1077#1095#1072#1090#1080
        Enabled = False
        Hint = #1054#1095#1080#1089#1090#1080#1090#1100' '#1086#1095#1077#1088#1077#1076#1100' '#1087#1077#1095#1072#1090#1080
        Visible = False
        OnClick = SpoolerClearItemClick
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object DbItem: TMenuItem
        Caption = #1041#1072#1079#1072' '#1076#1072#1085#1085#1099#1093
        Hint = #1055#1088#1086#1089#1084#1086#1090#1088' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093
        ImageIndex = 4
        ShortCut = 114
        OnClick = DbItemClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object N20: TMenuItem
        Caption = #1056#1072#1079#1084#1077#1088' '#1096#1088#1080#1092#1090#1072' '#1074' '#1078#1091#1088#1085#1072#1083#1077
        object N18: TMenuItem
          Caption = #1059#1074#1077#1083#1080#1095#1080#1090#1100
          OnClick = N18Click
        end
        object N19: TMenuItem
          Caption = #1059#1084#1077#1085#1100#1096#1080#1090#1100
          OnClick = N19Click
        end
      end
      object N17: TMenuItem
        Caption = '-'
      end
      object ExitItem: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        Hint = #1047#1072#1074#1077#1088#1096#1077#1085#1080#1077' '#1088#1072#1073#1086#1090#1099' '#1080' '#1074#1099#1093#1086#1076' '#1080#1079' '#1087#1088#1086#1075#1088#1072#1084#1084#1099
        ImageIndex = 31
        OnClick = ExitItemClick
      end
    end
    object AlarmItems: TMenuItem
      Caption = #1057#1080#1075#1085#1072#1083#1080#1079#1072#1094#1080#1103
      object SoundResetItem: TMenuItem
        Caption = #1057#1073#1088#1086#1089' '#1079#1074#1091#1082#1072
        Hint = #1057#1073#1088#1086#1089' '#1079#1074#1091#1082#1086#1074#1086#1081' '#1089#1080#1075#1085#1072#1083#1080#1079#1072#1094#1080#1080
        ImageIndex = 41
        ShortCut = 27
        OnClick = SoundResetItemClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object AlarmResetItem: TMenuItem
        Caption = #1057#1073#1088#1086#1089' '#1090#1088#1077#1074#1086#1075
        Hint = #1057#1073#1088#1086#1089' '#1090#1088#1077#1074#1086#1078#1085#1086#1081' '#1089#1080#1075#1085#1072#1083#1080#1079#1072#1094#1080#1080
        ImageIndex = 0
        OnClick = AlarmResetItemClick
      end
      object N13: TMenuItem
        Caption = '-'
        Visible = False
      end
      object SoundSetItem: TMenuItem
        Caption = #1047#1074#1091#1082' "'#1058#1088#1077#1074#1086#1075#1072'"'
        ImageIndex = 40
        OnClick = SoundSetItemClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object TabloResetItem: TMenuItem
        Caption = #1057#1073#1088#1086#1089' '#1090#1072#1073#1083#1086
        ImageIndex = 42
        OnClick = TabloResetItemClick
      end
    end
    object ControlItems: TMenuItem
      Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
      object ControlItem: TMenuItem
        Caption = #1050#1086#1085#1090#1088#1086#1083#1100
        Hint = #1057#1085#1103#1090#1100' '#1089' '#1082#1086#1085#1090#1088#1086#1083#1103'/'#1087#1086#1089#1090#1072#1074#1080#1090#1100' '#1087#1086#1076' '#1082#1086#1085#1090#1088#1086#1083#1100' '#1086#1073#1098#1077#1082#1090
        ShortCut = 45
        OnClick = ControlItemClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object DkItem: TMenuItem
        Caption = #1044#1050
        Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050
        object DkRifItem: TMenuItem
          Caption = #1056#1048#1060
          Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1087#1086#1076#1089#1080#1089#1090#1077#1084#1099' '#1056#1048#1060
          object DkRifAllItem: TMenuItem
            Caption = #1054#1073#1097#1080#1081
            Hint = #1042#1099#1087#1086#1083#1085#0#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1074#1089#1077#1093' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1074#1089#1077#1093' '#1082#1072#1085#1072#1083#1086#1074
            OnClick = DkRifAllItemClick
          end
          object N7: TMenuItem
            Caption = '-'
            Visible = False
          end
          object RifsDkItem: TMenuItem
            Caption = #1056#1048#1060'-'#1056#1051#1052'('#1050#1056#1051'), '#1058#1088#1072#1089#1089#1072
            Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1074#1089#1077#1093' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1056#1048#1060'-'#1056#1051#1052'('#1050#1056#1051'), '#1058#1088#1072#1089#1089#1072'-1'#1083
            Visible = False
            OnClick = RifsDkItemClick
          end
          object ConcDkItem: TMenuItem
            Caption = #1050#1086#1085#1094#1077#1085#1090#1088#1072#1090#1086#1088#1099
            Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1074#1089#1077#1093' '#1082#1086#1085#1094#1077#1085#1090#1088#1072#1090#1086#1088#1086#1074
            Visible = False
            OnClick = ConcDkItemClick
          end
          object TorosDkItem: TMenuItem
            Caption = #1058#1086#1088#1086#1089
            Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1074#1089#1077#1093' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1058#1054#1056#1054#1057', '#1058#1088#1072#1089#1089#1072'-2'#1083
            Visible = False
            OnClick = TorosDkItemClick
          end
          object NastDkItem: TMenuItem
            Caption = #1053#1072#1089#1090
            Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1074#1089#1077#1093' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1053#1040#1057#1058
            Visible = False
            OnClick = NastDkItemClick
          end
          object RadarDkItem: TMenuItem
            Caption = #1056#1072#1076#1072#1088
            Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1074#1089#1077#1093' '#1076#1072#1090#1095#1080#1082#1086#1074' '#1056#1040#1044#1040#1056
            Visible = False
            OnClick = RadarDkItemClick
          end
        end
        object GobiDkItem: TMenuItem
          Caption = #1057#1057#1054#1048
          Hint = #1042#1099#1087#1086#1083#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1091' '#1044#1050' '#1076#1083#1103' '#1087#1086#1076#1089#1080#1089#1090#1077#1084#1099' '#1057#1057#1054#1048
          object GobiDkKanalsItem: TMenuItem
            Caption = #1042#1089#1077' '#1082#1072#1085#1072#1083#1099
            OnClick = GobiDkKanalsItemClick
          end
          object GobiDkKan1Item: TMenuItem
            Caption = #1050#1072#1085#1072#1083' 1'
            OnClick = GobiDkKan1ItemClick
          end
          object GobiDkKan2Item: TMenuItem
            Caption = #1050#1072#1085#1072#1083' 2'
            OnClick = GobiDkKan2ItemClick
          end
          object GobiDkKan3Item: TMenuItem
            Caption = #1050#1072#1085#1072#1083' 3'
            OnClick = GobiDkKan3ItemClick
          end
          object GobiDkKan4Item: TMenuItem
            Caption = #1050#1072#1085#1072#1083' 4'
            OnClick = GobiDkKan4ItemClick
          end
        end
      end
      object N16: TMenuItem
        Caption = '-'
      end
      object DiagItem: TMenuItem
        Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072
        OnClick = DiagItemClick
      end
      object N26: TMenuItem
        Caption = '-'
      end
      object SetupItem: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
        OnClick = SetupItemClick
      end
    end
    object HelpItems: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      object AboutItem: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
        OnClick = AboutItemClick
      end
    end
  end
  object ImageList1: TImageList
    Left = 648
    Top = 16
    Bitmap = {
      494C01012F003100040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      000000000000360000002800000040000000D0000000010020000000000000D0
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE000000FE002222EC001212ED000000
      FE000000FE000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE005E5EE200EDEDED00EDEDED007070
      DE000000FE000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE008B8BDF00F6F6F600F8F8F800F8F8F8009494
      D8008B8BDF000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE000000FE000000FE009999E100F6F6F600F8F8F800F6F6F600A4A4DC00D1D1
      E7005E5EE2000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFCFCFCFF818181FF545454FFAAAAAAFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE000000FE007272E100F6F6F600F6F6F6008C8CE700B8B8E200C3C3E5007C7C
      E4000000FE000000FE000000FE000000FE0027273C0027277500282875002728
      7300282858002727270027272B0028296E0028296E0028296E00282964002727
      400028296E0028296E0028296E0028284D00FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFBFBFBFF686868FF494949FF494949FFF7F7F7FF4D8697FF494949FF4A4A
      4AFFA1A1A1FFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE002222EC00F6F6F600F6F6F6009797E9000000FE005E5EE2009797E9000000
      FE000000FE000000FE000000FE000000FE00010138000304E4000304E4000204
      DC00040490000000000001010C000204DC000304E4000304E4000304C5000101
      4C000203E9000304E4000204DC0002027D00FEFEFEFFFEFEFEFFF9F9F9FF6464
      64FF494949FF494949FF494949FF494949FFFEFEFEFF68DDFEFF7DE1FEFF79DF
      FDFF5F92A1FF4A4A4AFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE009999E100F6F6F600F6F6F6002222EC000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE00010138000304E4000304E4000204
      DC000404900004034400020221000204DC000204DC000304E4000304C5000101
      4C000304E4000204DC000204DC0002027D00FEFEFEFFB4B4B4FF494949FF4949
      49FF494949FF494949FF494949FF494949FFFEFEFEFFD3F4FDFF83E2FEFF7AE1
      FEFF90E5FEFF494949FFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE001212
      ED00EDEDED00F6F6F6009999E1000000FE000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE00010138000304E4000304E4000204
      DC00040490000101380002021C000204DC000304E4000304E4000304C5000101
      4C000304E4000304E4000304E40002027D00FEFEFEFF5F5F5FFF494949FF4949
      49FF494949FF494949FF494949FF494949FF5D5D5DFFC6C6C6FFFEFEFEFFFEFE
      FEFFDDF7FEFF494949FFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE006767
      E400F6F6F600F6F6F6002929ED000000FE000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE00010138000304E4000304E4000204
      DC000404900002025700020221000405DA000304E4000204DC000304C5000101
      4C000304E4000304E4000204DC0002027D00FEFEFEFF5F5F5FFF494949FF4949
      49FF494949FF494949FF535353FFECECECFFF8F8F8FFFEFEFEFFC6C6C6FF5C5C
      5CFFABABABFF494949FFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE00AEAE
      E100EDEDED00A8A8E7000000FE000000FE000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE00010138000204DC000204DC000303
      D60004048C0003032800020216000606D5000204DC000204DC000405C0000101
      4C000304E4000204DC000204DC0002027D00FEFEFEFF5F5F5FFF494949FF4949
      49FF7D7D7DFFFCFCFCFFFEFEFEFFFEFEFEFF555555FF494949FF9B9B9BFF6262
      62FF494949FFB0B0B0FFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE00DDDD
      E200F6F6F6003333EC000000FE000000FE000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE00010138000304E4000304E4000204
      DC00040490000000000001010C000204DC000304E4000304E4000304C5000101
      4C000304E4000304E4000204DC0002027D00FEFEFEFF7F7F7FFF494949FF8D8D
      8DFFD5D5D5FFFEFEFEFFFEFEFEFFDCDCDCFF494949FF494949FF616161FFDCDC
      DCFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000A0AEA00EDED
      ED00F6F6F600A4A4DC006060DD001818F5000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE003D3D49003D3D62003D3D62003D3D
      62003D3D56003D3D3E003D3D41003D3D62003D3D62003D3D69003D3D5F003D3D
      49003D3D69003D3D69003D3D69003D3D5F00FEFEFEFFFEFEFEFFFBFBFBFFBEBE
      BEFF747474FF4A4A4AFFFEFEFEFF4A4A4AFF494949FFEFEFEFFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE001717E800EDED
      ED00EDEDED00D1D1E700B9B9DC002929ED000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFACACACFF494949FF6D6D6DFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE001D1DE700EDED
      ED00E9E9E900A6A6D800D6D6DC000101F9000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFF494949FF494949FFFEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000101F9009292
      D700E9E9E9009E9ED100AAAAE0000000FE000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FE000000FE000000FE000000
      FE001D1DE7003535EA002F2FF3000000FE000000FE000000FE000000FE000000
      FE000000FE000000FE000000FE000000FE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFE
      FEFFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000847C5BFF2A2100FF2A2100FF2A21
      00FF2A2100FF2A2100FF2A2100FF2A2100FF2A2100FF2A2100FF2A2100FF2A21
      00FF2A2100FF2A2100FF251D01FFEBEAE5FF847C5BFF2A2100FF2A2100FF2A21
      00FF2A2100FF2A2100FF2A2100FF2A2100FF2A2100FF2A2100FF2A2100FF2A21
      00FF2A2100FF2A2100FF251D01FFEBEAE5FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000280020002800200028002000280
      0200028002000280020002800200028002000280020022892200138113000280
      020002800200028002000280020002800200856C07FF836900FF836900FF8369
      00FF836900FF836900FF836900FF836900FF836900FF836900FF836900FF8369
      00FF836900FF836900FF826800FF342901FF856C07FF836900FF836900FF8369
      00FF836900FF836900FF836900FF836900FF836900FF836900FF836900FF8369
      00FF836900FF836900FF826800FF342901FF0000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000280020002800200028002000280
      0200028002000280020002800200028002005FA25F00EDEDED00EDEDED0072A7
      7200028002000280020002800200028002008A7211FF836900FF836900FF8369
      01FF836900FF836900FF836900FF836901FF836900FF836900FF836900FF8369
      01FF836900FF836900FF836900FF433500FF8A7211FF836900FF836900FF8369
      01FF836900FF836900FF836900FF836901FF836900FF836900FF836900FF8369
      01FF836900FF836900FF836900FF433500FF0000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF00000000000000000000000000000000000280020002800200028002000280
      02000280020002800200047E04008CB58C00F8F8F800F8F8F800F8F8F80095B6
      95008CB58C000280020002800200028002008A7211FF836900FF836900FF8369
      01FF836900FF836900FF836900FF836901FF836900FF836900FF836900FF8369
      01FF836900FF836900FF836900FF433500FF8A7211FF836900FF826801FF8369
      01FF836900FF836900FF836900FF836901FF836900FF836900FF836900FF7D64
      0BFF806606FF836900FF836900FF433500FF00000000000000000000FF000000
      FF000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF000000000000000000000000000280020002800200028002000280
      020002800200047E040099BC9900F8F8F800F8F8F800F8F8F800A5C1A500D2DC
      D2005FA25F000280020002800200028002008A7211FF836901FF836900FF8369
      01FF836901FF836901FF826901FFEEEEE1FFC2B886FF836901FF826901FFA093
      44FFC1BA87FF836901FF836900FF433500FF8A7211FF836901FF594751FF3A2F
      8CFF836901FF836901FF826901FFEEEEE1FFC2B886FF836901FF7F6608FF2522
      D5FFC1BA87FF836901FF836900FF433500FF000000000000FF000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000280020002800200028002000280
      02000280020073AA7300F8F8F800F8F8F8008CBA8C00B8CCB800C4D4C4007DB1
      7D00028002000280020002800200028002008A7211FF836900FF836900FF8369
      00FF836900FF846B04FFFAF9F5FFFFFFFFFFC2B885FF836900FFC1BA86FF9A8A
      36FFF5F5EDFF826901FF836900FF433500FF8A7211FF836900FF836900FF624E
      40FF3027A0FF846B04FFFAF9F5FFFFFFFFFFC2B885FF816704FF2726EEFF9A8A
      36FFF5F5EDFF826901FF836900FF433500FF000000000000FF00000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      00000000FF000000FF0000000000000000000280020002800200028002000280
      020022892200F8F8F800F8F8F80092BB9200047E04005FA25F0092BB92000280
      0200028002000280020002800200028002008A7211FF836900FFDEDCC0FFEBEB
      DCFFEBEBDCFFFEFEFDFFFFFFFFFFFFFFFFFFC2B885FFF0F0E3FF836901FFFDFD
      FCFF9E903FFFA3964AFF836900FF433500FF8A7211FF836900FFDEDCC0FFEBEB
      DCFFC5C5F1FF4646FEFFFFFFFFFFFFFFFFFFC1B787FF2525FCFF826901FFFDFD
      FCFF9E903FFFA3964AFF836900FF433500FF0000FF000000FF00000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000FF000000FF00000000000280020002800200028002000280
      020099BC9900F8F8F800EDEDED00228922000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836900FFF4F5EDFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC2B885FF9C8E3CFFA6984DFFF3F2
      E8FF846C05FFCCCA9FFF836900FF433500FF8A7211FF836900FFF4F5EDFFFFFF
      FFFFFFFFFFFFD9D9FFFF3636FFFFFEFEFFFF1210E9FF9C8E3DFFA6984DFFF3F2
      E8FF846C05FFCCCA9FFF836900FF433500FF0000FF000000FF00000000000000
      0000000000000000FF000000FF000000FF000000000000000000000000000000
      0000000000000000FF000000FF00000000000280020002800200028002001881
      1800EDEDED00F8F8F8009CBF9C00028002000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836901FFF4F5EDFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC2B885FF917C21FFB6AA6DFFE3E3
      CCFF836A02FFD4D1AEFF836900FF433500FF8A7211FF836901FFF4F5EDFFFFFF
      FFFFFFFFFFFFFFFFFFFFEBEBFFFF0000FFFFC2B885FF917C21FFB6AA6DFFE3E3
      CCFF836A02FFD4D1AEFF836900FF433500FF0000FF000000FF00000000000000
      000000000000000000000000FF000000FF000000FF0000000000000000000000
      0000000000000000FF000000FF000000000002800200028002000280020068A6
      6800F8F8F800EDEDED002D8E2D00028002000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836900FFF4F5EDFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC2B885FFD0CAA3FF897311FFFCFC
      FAFF8A7615FFBBB279FF836900FF433500FF8A7211FF836900FFF4F5EDFFFFFF
      FFFFFFFFFFFFFFFFFFFF2323FFFFF1F1FFFF0C09E7FFD0CAA3FF897311FFFCFC
      FAFF8A7615FFBBB279FF836900FF433500FF0000FF000000FF00000000000000
      00000000000000000000000000000000FF000000FF000000FF00000000000000
      0000000000000000FF000000FF0000000000028002000280020002800200AAC6
      AA00F8F8F800A5C1A50002800200028002000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836900FF846D06FF8570
      0AFF85700AFFBFB782FFFFFFFFFFFFFFFFFFC2B885FF938329FF8D7A1BFFCECA
      A2FFCECAA2FF87720EFF836900FF433500FF8A7211FF836900FF846D06FF8570
      0AFF85700AFF201FEAFFFAFAFFFFFFFFFFFFBEB48FFF0F0FF8FF8D7A1BFFCECA
      A2FFCECAA2FF87720EFF836900FF433500FF0000FF000000FF00000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      0000000000000000FF000000FF00000000000280020002800200047E0400DEE0
      DE00EDEDED003690360002800200028002000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836900FF836900FF8369
      01FF836900FF836900FFA39549FFFFFFFFFFC2B885FF836900FFA69B51FF8369
      01FFF4F3EAFF836900FF836900FF433500FF8A7211FF836900FF836900FF8369
      01FF1A15CAFF7F6508FFA39549FFFFFFFFFFC2B885FF806705FF0A0AFCFF8269
      01FFF4F3EAFF836900FF836900FF433500FF000000000000FF000000FF000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF00000000000000FF00000000000000000002800200028002000C7B0C00EDED
      ED00F8F8F800A5C1A50060A260001A881A000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836901FF836900FF8369
      01FF836901FF836901FF836900FF8C7919FFA6994FFF836901FF836900FFA79A
      51FF836B03FF836901FF836900FF433500FF8A7211FF836901FF836900FF211B
      BDFF7D640BFF836901FF836900FF8C7919FFA6994FFF836901FF836900FF0201
      FAFF826B05FF836901FF836900FF433500FF000000000000FF000000FF000000
      FF000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF000000FF000000000000000000028002000280020018811800EDED
      ED00EDEDED00D2DCD200B9CAB9002A8B2A000280020002800200028002000280
      0200028002000280020002800200028002008A7211FF836900FF836900FF8369
      00FF836900FF836900FF836900FF836900FF836900FF836900FF836900FF8369
      00FF836900FF836900FF836900FF433500FF8A7211FF836900FF816803FF7961
      13FF836900FF836900FF836900FF836900FF836900FF836900FF836900FF8369
      00FF241CB9FF836900FF836900FF433500FF00000000000000000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      FF000000FF00000000000000000000000000028002000280020018811800EDED
      ED00E9E9E900A6BFA600D2DCD200047E04000280020002800200028002000280
      0200028002000280020002800200028002008C7414FF836900FF836900FF8369
      01FF836900FF836900FF836900FF836901FF836900FF836900FF836900FF8369
      01FF836900FF836900FF836900FF433600FF8C7414FF836900FF836900FF8369
      01FF836900FF836900FF836900FF836901FF836900FF836900FF836900FF8369
      01FF836900FF836900FF836900FF433600FF0000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000000000000000000000000000000002800200028002000C7B0C0095B6
      9500E9E9E9009FB79F00AAC6AA00028002000280020002800200028002000280
      020002800200028002000280020002800200BAAB71FF927B1FFF917A1EFF917A
      1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A
      1EFF917A1EFF917A1EFF917B1FFF938345FFBAAB71FF927B1FFF917A1EFF917A
      1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A1EFF917A
      1EFF917A1EFF917A1EFF917B1FFF938345FF0000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF00000000000000
      000000000000000000000000000000000000028002000280020002800200047E
      04001F831F003690360036903600028002000280020002800200028002000280
      02000280020002800200028002000280020000FC01FF00F902FF00F902FF00F9
      02FF00F902FF00F902FF00F902FF00F902FF00F902FF00F902FF00FD00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00E91DFF00E91DFF00E91DFF00E9
      1DFF00E91DFF00E91DFF00E91DFF00E91DFF00E91DFF00E91DFF00E91DFF00E9
      1DFF00E91DFF00E91DFF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF36DB44FF3C3C3CFF3C3C3CFF3C3C
      3CFF3C3C3CFF3C3C3CFF3C3C3CFF3C3C3CFF3C3C3CFF3C3C3CFF35D039FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF03E820FF3C3C3CFF1A1A1AFF1A1A
      1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A
      1AFF1A1A1AFF1E1E1EFF5EE16EFF00E91DFF3C3CF5FF3D3C3CFF3D3C3CFF3D3C
      3CFF3D3C3CFF3D3C3CFF3D3C3CFF3D3C3CFF3D3C3CFF3D3C3CFF5252EDFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF0303FEFF3C3C3CFF1A1A1AFF1A1A
      1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A1AFF1A1A
      1AFF1A1A1AFF1E1E1EFF5E5EEEFF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF739177FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF737393FF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF444444FF38E74EFF84C68CFF000000FF000000FF0000
      00FF000000FF000000FF749177FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF444444FF3838F7FF8484CCFF000000FF000000FF0000
      00FF000000FF000000FF747494FF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF525252FF00E91DFF5FD46EFF000000FF000000FF0000
      00FF000000FF000000FF739177FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF525252FF0000FFFF5F5FDFFF000000FF000000FF0000
      00FF000000FF000000FF737393FF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF797C79FF00E91DFF64DC73FF000000FF000000FF0000
      00FF000000FF000000FF749177FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF79797DFF0000FFFF6464E8FF000000FF000000FF0000
      00FF000000FF000000FF747494FF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF5CDF6CFF00E91DFF0AE826FF010101FF000000FF0000
      00FF000000FF000000FF749178FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF5C5CEBFF0000FFFF0A0AFDFF010101FF000000FF0000
      00FF000000FF000000FF747494FF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF00FA02FF00F902FF00FF00FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF000000FF494949FF0D0D0DFF000000FF000000FF0000
      00FF000000FF000000FF739177FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF000000FF494949FF0D0D0DFF000000FF000000FF0000
      00FF000000FF000000FF737393FF0000FFFF36DB43FF010101FF010101FF0101
      01FF010101FF010101FF010101FF010101FF010101FF010101FF2BC730FF00FF
      00FF00FF00FF2B402DFF0C0B0CFF01F305FF1BE735FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF759278FF00E91DFF3B3BF5FF010000FF010000FF0100
      00FF010000FF010000FF010000FF010000FF010000FF010000FF5050EAFF0707
      FEFF0707FEFF373636FF0D0C0CFF0707FEFF1B1BFAFF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF757594FF0000FFFF03F507FF12EA1BFF12EA1BFF12EA
      1BFF12EA1BFF12EA1BFF16E521FF292828FF353434FF14E61FFF03F607FF00FF
      00FF00FF00FF233825FF161515FF01F305FF00E91DFF7A7A7AFF010101FF0000
      00FF303030FF525252FF525252FF525252FF525252FF525252FF515151FF0000
      00FF000000FF585858FF46E65AFF00E91DFF0D0DFDFF2222FAFF2222FAFF2222
      FAFF2222FAFF2222FAFF2222FAFF100F0FFF363535FF2222FAFF0A0AFDFF0707
      FEFF0707FEFF2B2A2AFF151414FF0707FEFF0000FFFF7A7A7AFF010101FF0000
      00FF303030FF525252FF525252FF525252FF525252FF525252FF515151FF0000
      00FF000000FF585858FF4646F5FF0000FFFF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF2F382FFF121111FF00F902FF00FF00FF00FF
      00FF00FF00FF1F261FFF353535FF01F305FF00E91DFF00E91DFF050505FF0000
      00FF4F8A57FF00E91DFF00E91DFF00E91DFF00E91DFF00E91DFF37E64DFF0000
      00FF000000FF54E666FF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF272626FF141313FF0707FEFF0707FEFF0707
      FEFF0707FEFF0D0C0CFF343333FF0707FEFF0000FFFF0000FFFF050505FF0000
      00FF4F4F8FFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF3737F6FF0000
      00FF000000FF5454F4FF0000FFFF0000FFFF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF406B45FF010101FF15ED1CFF00FF00FF00FF
      00FF00FF00FF070606FF6A776BFF00FF00FF00E91DFF00E91DFF121212FF0000
      00FF4F4F4FFF00E91DFF00E91DFF00E91DFF00E91DFF00E91DFF91CF99FF0000
      00FF000000FF55E667FF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF58576EFF010000FF0707FEFF0707FEFF0707
      FEFF0707FEFF010000FF717179FF0707FEFF0000FFFF0000FFFF121212FF0000
      00FF4F4F4FFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF9191D5FF0000
      00FF000000FF5555F4FF0000FFFF0000FFFF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF65D76CFF010101FF519C58FF00FF00FF00FF
      00FF56BB5CFF010101FF3AB947FF00FF00FF00E91DFF00E91DFF84A288FF0000
      00FF000000FF87BA8DFF00E91DFF00E91DFF00E91DFF58E369FF050505FF0000
      00FF242424FF00E91DFF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF6C6CE4FF010000FF6D6CC5FF0707FEFF0707
      FEFF6A6ACEFF010000FF5151E8FF0707FEFF0000FFFF0000FFFF8484A4FF0000
      00FF000000FF8787BFFF0000FFFF0000FFFF0000FFFF5858F0FF050505FF0000
      00FF242424FF0000FFFF0000FFFF0000FFFF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00F703FF272827FF010101FF5B6A5DFF5D72
      5FFF010101FF121212FF08EC11FF00FF00FF00E91DFF00E91DFF07E823FF3C3C
      3CFF000000FF000000FF040404FF343434FF131313FF000000FF000000FF0404
      04FF3FE654FF00E91DFF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF111011FF010000FF646376FF6261
      78FF010000FF0B0A0AFF0707FEFF0707FEFF0000FFFF0000FFFF0707FEFF3C3C
      3CFF000000FF000000FF040404FF343434FF131313FF000000FF000000FF0404
      04FF3F3FF6FF0000FFFF0000FFFF0000FFFF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF22E52CFF222422FF010101FF0101
      01FF191818FF30D23EFF00FF00FF00FF00FF00E91DFF00E91DFF00E91DFF00E9
      1DFF99A79BFF040404FF000000FF000000FF000000FF000000FF616161FF0EE8
      29FF00E91DFF00E91DFF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF2828F9FF0D0C0DFF010000FF0100
      00FF090808FF3232F7FF0707FEFF0707FEFF0000FFFF0000FFFF0000FFFF0000
      FFFF9999A9FF040404FF000000FF000000FF000000FF000000FF616161FF0E0E
      FDFF0000FFFF0000FFFF0000FFFF0000FFFF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00F404FF38DC45FF1BDE
      29FF01ED08FF00FF00FF00FF00FF00FF00FF00E91DFF00E91DFF00E91DFF00E9
      1DFF00E91DFF00E91DFF1CE835FF1CE835FF1CE835FF00E91DFF00E91DFF00E9
      1DFF00E91DFF00E91DFF00E91DFF00E91DFF0707FEFF0707FEFF0707FEFF0707
      FEFF0707FEFF0707FEFF0707FEFF0707FEFF0707FEFF0707FEFF3D3DF7FF2222
      FAFF0707FEFF0707FEFF0707FEFF0707FEFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF1C1CFBFF1C1CFBFF1C1CFBFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF191919FF191919FF191919FF1919
      19FF191919FF191919FF191919FF191919FF191919FF191919FF191919FF1919
      19FF191919FF191919FF191919FF090909FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF191919FF00000000CCC8C800B0ACAC00ACA8
      A800000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008787CCFF121261FF1F1F1FFF1F1F
      1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F
      1FFF1F1F1FFF1F1F1FFF1E1E27FF070797FF8787DAFF121270FF1F1F1FFF1F1F
      1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F
      1FFF1F1F1FFF1F1F1FFF1E1E28FF0707B3FF4C4C4CFF4C4C4CFF963414FF8938
      1DFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF5349
      46FFAC2D03FF61443CFF4C4C4CFF191919FF00000000C0BCBC00BCBCB800ACAC
      AC00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008383CBFF6D6DBEFF8B8BC6FF0101
      8CFF01018CFF01018CFF01018CFF01018CFF01018CFF01018CFF01018CFF0101
      8CFF01018CFF01018CFF020285FF171720FF8383D9FF6D6DCEFF8B8BD1FF0101
      A7FF0101A7FF0101A7FF0101A7FF0101A7FF0101A7FF0101A7FF0101A7FF0101
      A7FF0101A7FF0101A7FF02029FFF171722FF4C4C4CFF4C4C4CFFB22C00FFB22C
      00FF933516FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF534946FFB22C
      00FFB22C00FFAC2D03FF4C4C4CFF191919FF00000000BCB8B800A6A2A0006464
      5C00B8B8B4000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008383CBFF7373C4FFA0A0FAFF1F1F
      F5FF1414EEFF0000E1FF0000E1FF0000E1FF0000E1FF0000E1FF0000D3FF0000
      94FF000094FF000094FF01018CFF191919FF8383D9FF7373D4FFA0A0FBFF1F1F
      F7FF1F1FF7FF1717F7FF0606F7FF0606F7FF0606F7FF0606F7FF0505EAFF0000
      B1FF0000B1FF0000B1FF0101A7FF191919FF4C4C4CFF4C4C4CFF88381EFFB22C
      00FFB22C00FF933516FF4C4C4CFF4C4C4CFF4C4C4CFF534946FFB22C00FFB22C
      00FFB22C00FF534946FF4C4C4CFF191919FF00000000BCB8B400D6D4D200C0C0
      BC007874700060605C0078787400CCCCC8000000000000000000000000000000
      0000000000000000000000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF2121FEFF1414F5FF0000E9FF3D3DEEFFE0E0FCFFB0B0F8FF0000E7FF0000
      D3FF000094FF000094FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2121FEFF1818FEFF0707FEFF0707FEFF0707FEFF0505F0FF0000
      B1FF0000B1FF0000B1FF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF8838
      1EFFB22C00FFB22C00FF933516FF4C4C4CFF534946FFB22C00FFB22C00FFB22C
      00FF534946FF4C4C4CFF4C4C4CFF191919FF00000000C8C4C400C0C0C000CCCC
      C80000000000E8E8E800C8C8C40084848000B2B2B20000000000000000000000
      0000000000000000000000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF2323FFFF2121FDFF1414F6FF4545EFFFFFFFFFFFC8C8FAFF0000E9FF0000
      E7FF0000D3FF000094FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF1A1AFEFF0707FEFF0707FEFF0707FEFF0606FBFF0505
      F2FF0505EAFF0000B1FF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF88381EFFB22C00FFB22C00FF933516FFB22C00FFB22C00FFB22C00FF5349
      46FF4C4C4CFF4C4C4CFF4C4C4CFF191919FF000000000000000000000000DAD8
      D800B8B8B40098989400CCCCC800C4C0C000C4C4C00000000000000000000000
      0000000000000000000000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2121FDFF5A5AFCFFFFFFFFFFC8C8FAFF0000E9FF0000
      E9FF0000E7FF0000D3FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2121FEFF1717FEFF0707FEFF0707FEFF0707FEFF0707
      FEFF0606FCFF0505EAFF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF88381EFFB22C00FFB22C00FFB22C00FFB22C00FF534946FF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF191919FF0000000000000000000000007878
      7400706C68008C8C84006060580084807C00D0D0D00000000000000000000000
      0000000000000000000000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF6262FFFFD0D0FFFFD0D0FFFFDDDDFFFFFFFFFFFFF3F3FEFFC8C8FAFFC8C8
      FAFFB0B0F8FF0000E1FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF6262FFFFD0D0FFFFD0D0FFFFCECEFEFFCACAFEFFCACAFEFFCACAFEFFCACA
      FEFFB2B2FEFF0606F6FF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF534946FFB22C00FFB22C00FFB22C00FF933516FF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF191919FF00000000C8C8C8008C8C88008C8C
      880088848000807C78007874700074706C006868640084848400B8B8B800C8C8
      C800000000000000000000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF7272FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFE0E0FCFF0000E1FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF7272FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFE0E0FEFF0606F6FF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF534946FFB22C00FFB22C00FFB22C00FFB22C00FFB22C00FF933516FF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF191919FF00000000ECEAEA0094909000C4C4
      C000D4D2D000D0D0CC00BCB8B8009C989800807C7800CCC8C800807C7800C0C0
      BC00A8A4A4000000000000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF3838FFFF5F5FFFFF5F5FFFFF8A8AFFFFFFFFFFFFDDDDFFFF5A5AFCFF4545
      EFFF3D3DEEFF0000E1FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF3838FFFF5F5FFFFF5F5FFFFF5F5FFFFF5F5FFFFF5A5AFEFF4A4AFEFF4A4A
      FEFF4242FEFF0606F6FF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF5349
      46FFB22C00FFB22C00FFB22C00FF534946FF88381EFFB22C00FFB22C00FF9335
      16FF4C4C4CFF4C4C4CFF4C4C4CFF191919FF00000000DAD8D600DAD8D600D6D4
      D200B4B4B400908C8C008C888800A0A0A000D2D2CE0030342800545444009C9C
      980088848400BCBCBC0000000000000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF5F5FFFFFFFFFFFFFD0D0FFFF2121FDFF1414
      F6FF0000E9FF0000E1FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2121FEFF1A1AFEFF1717
      FEFF0707FEFF0606F6FF0101A7FF191919FF4C4C4CFF4C4C4CFF534946FFB22C
      00FFB22C00FFB22C00FF534946FF4C4C4CFF4C4C4CFF88381EFFB22C00FFB22C
      00FF933516FF4C4C4CFF4C4C4CFF191919FF00000000D8D4D400D6D4D200D8D4
      D400D6D4D200D6D4D200D8D8D400D8D4D400989494001C201C0024282000706C
      68007C787400908C8C00B2B2B200000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF5F5FFFFFFFFFFFFFD0D0FFFF2323FFFF2121
      FDFF1414F5FF0000E1FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF1E1E
      FEFF0707FEFF0606F6FF0101A7FF191919FF4C4C4CFF4C4C4CFFAC2D03FFB22C
      00FFB22C00FF534946FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF88381EFFB22C
      00FFB22C00FF684236FF4C4C4CFF191919FF00000000DCD8D800D6D4D200D6D4
      D200D6D4D200D8D4D400D6D4D200D8D4D000D4D2D0004C4C4C0000040000686C
      64003C3C340074746C008C8C8800000000008383CBFF7373C4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF3838FFFF7272FFFF6262FFFF2323FFFF2323
      FFFF2121FEFF1414EDFF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2121
      FEFF1616FEFF0606F6FF0101A7FF191919FF4C4C4CFF4C4C4CFF833A22FFAC2D
      03FF534946FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF8539
      20FFAC2D03FF504A48FF4C4C4CFF191919FF000000000000000000000000E0DC
      DC00D8D8D800D6D4D200D6D4D200D6D4D200D4D0D000D4D2D000585850002428
      1C00242820003034240044443000606050008383CBFF7373C4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323
      FFFF2323FFFF1F1FF5FF01018CFF191919FF8383D9FF7373D4FFA1A1FFFF2323
      FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323FFFF2323
      FFFF2121FEFF1515F7FF0101A7FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF191919FF0000000000000000000000000000
      00000000000000000000E6E4E400DAD8D600D4D0D000D2D0D000D2D0D0003E3C
      3400383C24003C3C24003C4020005C5E52008383CBFF7373C4FFD7D7FFFFA1A1
      FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1
      FFFFA1A1FFFFA0A0FAFF8B8BC6FF191919FF8383D9FF7373D4FFD7D7FFFFA1A1
      FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1FFFFA1A1
      FFFFA1A1FFFFA0A0FBFF8B8BD1FF191919FF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C4CFF4C4C
      4CFF4C4C4CFF4C4C4CFF4C4C4CFF191919FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000DCDAD800D0D0
      CC005C5E500054544C006A686000000000008383CBFF3434AAFF7373C4FF7373
      C4FF7373C4FF7373C4FF7373C4FF7373C4FF7373C4FF7373C4FF7373C4FF7373
      C4FF7373C4FF7373C4FF6D6DBEFF0B0B5CFF8383D9FF3434C1FF7373D4FF7373
      D4FF7373D4FF7373D4FF7373D4FF7373D4FF7373D4FF7373D4FF7373D4FF7373
      D4FF7373D4FF7373D4FF6D6DCEFF0B0B6BFFF7F7F700F7EFEF00F7EFEF00F7EF
      EF00F7EFEF00F7EFEF00F7EFEF00F7EFEF00F7F7F700FFF7F700FFF7F700FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F3F2F2FFD2CFCFFF000000000000
      000000000000000000000000000000000000EFD6D600FFFFF700FFF7F700FFF7
      F700FFF7F700FFF7F700FFFFF700FFF7F700FFFFF700FFFFFF00FFFFF700FFFF
      FF00EFDEDE00EFDEDE00F7E7DE00CE9C9C000000000000000000429C4200429C
      4200429C4200429C4200429C4200429C4200429C4200429C4200429C4200429C
      4200429C4200429C4200000000000000000084634A0084634A0084634A008463
      4A0084634A0084634A0084634A0084634A0084634A0084634A0084634A008463
      4A0084634A000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009F8A8AFFA87676FF895555FFC8B0
      B0FFFBFBFBFF000000000000000000000000D6B5B500F7E7E700FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00F7EFEF00F7EF
      EF00FFFFFF00FFFFFF00B57373000000000000000000429C4200F7FFF700EFF7
      EF00EFF7EF00E7F7E700E7F7E700DEEFDE00DEEFDE00D6EFD600D6EFD600CEE7
      CE00CEE7CE00CEE7CE00429C420000000000A58C7B00FFFFFF00BDA59400BDA5
      9400BDA59400BDA59400BDA59400BDA59400BDA59400BDA59400BDA59400BDA5
      940084634A0084634A0000000000000000000000000000000000000000000000
      0000000000008F8F8FFF686968FF767776FF7B6363FFAA7878FFA06D6DFF9F6C
      6CFF925F5FFF9D7575FFE7E5E5FF0000000000000000C6949400C68C8C00DEBD
      B500E7CECE00DEBDBD00E7C6BD00D6ADAD00D6ADAD00E7BDB500D6ADAD00DEBD
      BD00D6A5A500BD737300DEDEDE000000000000000000429C4200F7FFF7004AA5
      4A0042A5420042A5420039A53900399C3900319C3100319C3100299C2900299C
      2900299C2900CEE7CE00429C420000000000A58C7B00FFFFFF00FFFFFF00FFFF
      FF00FFF7F700FFEFE700F7E7DE00F7DECE00F7D6C60021395A00EFCEAD00BDA5
      940084634A0084634A0084634A00000000000000000000000000000000000000
      000000000000909090FF706C6FFF3AB15BFF728564FFAD7C7CFFA37070FFA370
      70FFA26F6FFFA16E6EFF785050FF00000000D6D6D600BDB5B500BDB5B500D6AD
      AD00BD848400B56B6B00E7BDB500E7ADA500E7A59C00E7A59C00B5636300BD84
      8400D6ADAD00BDB5B500BDB5B500D6CECE0000000000429C4200FFFFFF004AAD
      4A004AA54A0042A54200DEF7DE00ADDEAD00319C3100319C3100319C3100299C
      2900299C2900CEE7CE00429C420000000000A58C7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFF7F700FFEFE700F7E7DE00F7DECE0042AD4A00EFCEB500BDA5
      9400A58C7B00A57B630084634A00000000000000000000000000000000000000
      0000ECEFECFF949494FF736F72FF199B35FF587C4BFFB0807FFFA67373FFA673
      73FFA57272FFA47171FF7C5454FF00000000C6848400FFF7EF00FFEFEF00FFEF
      E700FFF7EF00FFEFE700FFE7E700FFE7DE00FFDED600FFDED600FFD6CE00FFCE
      C600FFDECE00FFD6CE00FFD6CE00AD63630000000000429C4200FFFFFF0052AD
      52004AAD4A004AA54A00DEF7DE00FFFFFF00ADDEAD00399C3900319C3100319C
      3100299C2900D6EFD600429C420000000000A58C7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFF7F700FFEFE700F7E7DE00F7DECE00F7D6C600EFCE
      B500A58C7B00BD94730084634A00000000000000000000000000000000000000
      000024A542FFA5AEA5FF757175FF0E851EFF5A7446FFB48282FFAA7777FFA271
      71FFA77575FFA77474FF7F5858FF00000000BD848400F7DEDE00FFEFC600FFEF
      BD00FFEFA500FFE79400FFDE7B00FFDE6B00FFD65A00FFCE5200FFC64A00FFBD
      4200FFAD3900FFA53100FFD6BD00AD63630000000000429C4200FFFFFF005AAD
      5A0052AD52004AAD4A00DEF7DE00FFFFFF00FFFFFF00ADDEAD00399C3900319C
      3100319C3100D6EFD600429C420000000000A58C7B00A58C7B00A58C7B00A58C
      7B00A58C7B00A58C7B00A58C7B00A58C7B00A58C7B00A58C7B0084634A008463
      4A00A58C7B00C69C840084634A00000000006F986FFF218F2FFF22942FFF1F97
      2CFF44DC75FF2AAC47FF8A908AFF036B06FF5D6C40FFB68686FF9F8E8EFF937D
      7DFFA77676FFAA7777FF855C5CFF00000000BD848400F7E7E700FFEFAD00FFE7
      A500FFE79400FFDE8400FFDE7300FFDE6300FFD66300FFCE5200FFC65200FFB5
      4A00FFAD4200FFA53100FFD6BD00AD63630000000000429C4200FFFFFF005AB5
      5A005AB55A0052AD5200DEF7DE00FFFFFF00FFFFFF00FFFFFF00ADDEAD00399C
      3900319C3100DEEFDE00429C420000000000A58C7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFF7F700FFEFE700F7E7DE00F7DE
      CE00A58C7B00D6AD940084634A0000000000658E65FF3CD56FFF42DB75FF47E0
      7AFF4CE57FFF4FE983FF2BAF47FFB1FAF0FFABAEAEFFB98888FFE1E2E2FFBBAF
      AFFFAE7B7BFFAD7A7AFF896161FF00000000C6848400F7DEE700FFE79400FFE7
      8C00FFDE8400FFDE7300FFDE6B00FFD66300FFCE5A00FFC65200FFBD4A00FFB5
      4200FFAD3900FFA53100FFD6BD00AD63630000000000429C4200FFFFFF006BB5
      6B0063B563005AB55A00DEF7DE00FFFFFF00FFFFFF00FFFFFF00ADDEAD0039A5
      3900399C3900DEF7DE00429C420000000000D6ADAD00A58C7B00A58C7B00A58C
      7B00A58C7B00A58C7B00A58C7B00A58C7B00A58C7B00A58C7B00A58C7B00A58C
      7B00DEB59C009484730084634A0000000000618B61FF48DA79FF46DF79FF4CE5
      7FFF51EA84FF56EF89FF59EF8CFF80D189FFC2ADADFFBE8E8EFFB48080FFB380
      80FFB17E7EFFB07D7DFF8E6565FF00000000C6848400EFDEE700FFDE7B00FFDE
      7300FFDE7300FFDE6B00FFD66300FFCE5A00FFCE5200FFC65200FFB54A00FFAD
      4200FFA53900FF9C3100FFD6C600AD6B630000000000429C4200FFFFFF0073BD
      73006BBD6B0063B56300DEF7DE00FFFFFF00FFFFFF00ADDEAD0042A5420042A5
      420039A53900E7F7E700429C42000000000000000000D6ADAD00D6ADAD00F7F7
      EF00FFFFFF00FFFFFF00FFFFF700F7F7F700F7F7EF00F7EFEF00F7EFE7008463
      4A00AD948400DEB59C0084634A0000000000638E63FF76E69BFF7FEBA4FF86F0
      AAFF86F3ABFF5DF691FF59A95BFFFFFAF6FFCFAEAEFFC19393FFB78484FFB683
      83FFB48181FFB27F7FFF906969FF00000000C6848400EFDEDE00FFDE6B00FFD6
      6300FFD66300FFD66300FFCE5A00FFCE5A00FFC65200FFBD4A00FFB54200FFAD
      3900FFA53900FF9C2900FFDECE00AD6B630000000000429C4200FFFFFF007BC6
      7B007BC67B0073BD7300DEF7DE00FFFFFF00ADDEAD004AAD4A004AA54A0042A5
      420042A54200E7F7E700429C4200000000000000000000000000D6ADAD00D6AD
      AD00FFFFFF00D6BDAD00D6BDAD00D6BDAD00D6BDAD00D6BDAD00F7EFEF00F7D6
      C60084634A0084634A0084634A00000000000000000000000000000000000000
      000060F290FF67B969FF747576FFFFF1E4FFD4AFAAFFC49595FFBA8787FFB986
      86FFB78484FFB58282FF956D6DFF00000000C6848400EFDEDE00FFD66300FFCE
      5A00FFCE5A00FFCE5A00FFC65200FFBD5200FFBD4A00FFB54200FFAD4200FFA5
      3900FF9C3100FF942900FFDECE00AD6B6B0000000000429C4200FFFFFF008CCE
      8C0084C684007BC67B00DEF7DE00ADDEAD005AB55A0052AD52004AAD4A004AA5
      4A0042A54200EFF7EF00429C420000000000000000000000000000000000D6AD
      AD00F7F7EF00FFFFFF00FFFFFF00FFFFFF00FFFFF700F7F7F700F7F7EF00F7E7
      DE0084634A000000000000000000000000000000000000000000000000000000
      000073D074FFAAAAAAFF767778FFFFE8D3FFD6ADA5FFC79999FFF5DADAFFF8D6
      D6FFE1B5B5FFCB9999FF987070FF00000000C68C8C00EFDEDE00FFC65A00FFC6
      5200FFC65200FFC65200FFBD4A00FFBD4A00FFB54200FFAD4200FFAD3900FFA5
      3100FF9C2900FF942100FFDECE00B56B6B0000000000429C4200FFFFFF0094CE
      94008CCE8C0084C6840073BD73006BBD6B0063B563005AAD5A0052AD52004AAD
      4A004AAD4A00EFFFEF00429C420000000000000000000000000000000000D6AD
      AD00D6ADAD00F7F7EF00D6BDAD00D6BDAD00D6BDAD00D6BDAD00D6BDAD00F7F7
      EF00F7D6C60084634A0000000000000000000000000000000000000000000000
      000000000000ADADADFF797B7CFFFFDFC1FFD9ADA3FFCA9D9DFFF1DFDFFFFFE9
      E9FFFFE0E0FFF4C9C9FF9B7575FF00000000C68C8C00EFDEDE00FFBD5200FFBD
      4A00FFBD4A00FFBD4A00FFB54200FFB54200FFAD3900FFA53900FFA53100FF9C
      3100FF942900FF8C2100FFDECE00B56B6B0000000000429C4200FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00F7FFF700F7FFF700429C4200000000000000000000000000000000000000
      0000D6ADAD00D6ADAD00F7F7EF00FFFFFF00FFFFFF00FFFFFF00FFFFF700F7F7
      F700F7E7DE0084634A0000000000000000000000000000000000000000000000
      000000000000B0B0B0FF7A7C7DFFFFD8B0FFDCADA1FFCCA0A0FFBF8B8BFFBC88
      88FFCA9D9DFFD1A3A3FF9F7777FF00000000C68C8C00EFD6DE00FFB54200FFB5
      4200FFB54200FFB53900FFAD3900FFA53100FFA53100FF9C2900FF9C2900FF94
      2100FF8C1800FF841000FFDECE00B56B6B000000000000000000429C4200429C
      4200429C4200429C4200429C4200429C4200429C4200429C4200429C4200429C
      4200429C4200429C420000000000000000000000000000000000000000000000
      000000000000D6ADAD00D6ADAD00D6ADAD00D6ADAD00D6ADAD00D6ADAD00D6AD
      AD00D6ADAD00D6ADAD0000000000000000000000000000000000000000000000
      000000000000B4B4B4FF929292FF8E8F90FFB39596FFDFBDBDFFD8AFAFFFCEA0
      A0FFC99898FFC49292FFA37C7CFF00000000C6848400FFFFFF00FFFFFF00FFF7
      FF00FFF7F700FFF7F700FFF7F700FFF7F700FFEFEF00FFEFEF00FFEFEF00FFEF
      EF00FFEFEF00FFEFE700FFEFE700AD6B63000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000B4B4B4FFBCBCBCFFBCBCBCFFB8B8B8FFAFAFAFFFA8A8A8FF9FA0
      A0FF989999FF8F9191FF8A8B8BFF00000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B0000000000FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B0000000000000000000000000084CE8400317318006B4A31006B4A
      31006B4A31006B4A31006B4A31006B4A31006B4A31006B4A31006B4A31006B4A
      31006B4A31006B4A31006352310000940000000000007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF007B7B7B0000000000000000000000000000000000000000000000
      000000000000000000007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B000000000000000000000000000000000000000000000000007B7B
      7B007B7B7B0000000000FFFFFF000000000000000000000000007B7B7B007B7B
      7B000000000000000000000000000000000084CE84006BBD6B0094BD8C000073
      000000730000007B0000007B00000084000000840000008C0000008C0000008C
      00000094000000940000088C0000634A29007B7B7B00FFFFFF0000000000FFFF
      FF0000000000FFFFFF007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B000000000000000000FFFFFF00000000007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B0000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF007B7B7B00FFFFFF00FFFFFF00FFFFFF007B7B7B00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0084CE840073C67300ADE7B50031BD
      520031B5420029AD390021AD310018AD290010A5180008A51000089C0800009C
      0000009C0000009C0000009400006B4231007B7B7B00FFFFFF007B7B7B000000
      00007B7B7B0000000000000000007B7B7B007B7B7B007B7B7B0000000000FFFF
      FF0000000000000000007B7B7B007B7B7B00000000007B7B7B000000FF007B7B
      7B0000FF00007B7B7B007B7B7B00000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B00FFFFFF0084CE840073C67300B5E7BD0042C6
      630039BD520031BD4A0029B5420021AD310018AD290010A5210008A51000089C
      0800009C0000009C0000009400006B4231007B7B7B00FFFFFF00000000000000
      00000000000000000000000000000000000000000000000000007B7B7B00FFFF
      FF00FFFFFF007B7B7B00000000007B7B7B00000000007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B00BDBDBD00BDBDBD00000000000000
      00000000000000000000BDBDBD00000000007B7B7B00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000007B7B
      7B0000000000000000007B7B7B00FFFFFF0084CE840073C67300B5EFC6004ACE
      6B0042C6630039BD520031B5420029AD390021AD310018A5290010A51800089C
      1000089C080000940000008C00006B4231007B7B7B00FFFFFF0000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000007B7B7B007B7B
      7B007B7B7B00FFFFFF00000000007B7B7B00000000007B7B7B00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD007B7B7B00BDBDBD00BDBDBD00000000000000
      0000000000007B7B7B007B7B7B00000000007B7B7B00FFFFFF00000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300B5EFCE0052CE
      7B004AC66B0039B5520029A5420021A53100219C2900189C2100109418001094
      10000894100000940800008C00006B4231007B7B7B00FFFFFF007B7B7B007B7B
      7B007B7B7B007B7B7B00000000000000000000000000000000007B7B7B00FFFF
      FF007B7B7B00FFFFFF00000000007B7B7B00000000007B7B7B00000000000000
      00000000000000000000BDBDBD007B7B7B00BDBDBD00BDBDBD00000000007B7B
      7B00000000007B7B7B00BDBDBD00000000007B7B7B00FFFFFF00000000007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE0052CE
      7B0084DE9C00D6EFDE00D6EFD600D6EFD600CEEFD600CEEFD600CEEFCE00CEE7
      CE00B5DEB50008941000008400006B4231007B7B7B00FFFFFF00000000000000
      00000000000000000000000000000000000000000000000000007B7B7B00FFFF
      FF007B7B7B00FFFFFF00000000007B7B7B00000000007B7B7B00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD007B7B7B00BDBDBD00BDBDBD0000000000BDBD
      BD0000000000BDBDBD00BDBDBD00000000007B7B7B00FFFFFF00000000007B7B
      7B00FFFFFF000000000000000000000000000000000000000000000000007B7B
      7B00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE0052CE
      7B0094E7AD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00E7F7E700109C1800008400006B4231007B7B7B00FFFFFF00000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF0000000000000000007B7B7B007B7B
      7B007B7B7B0000000000FFFFFF007B7B7B00000000007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B00BDBDBD00BDBDBD00000000000000
      000000000000BDBDBD00BDBDBD00000000007B7B7B00FFFFFF00000000007B7B
      7B00FFFFFF000000000000000000000000000000000000000000000000007B7B
      7B00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE0052CE
      7B006BD68C0084DEA50084DE9C007BDE9C007BD6940073D68C006BCE84006BCE
      7B005AC66B0018A52100008400006B4231007B7B7B0000000000FFFFFF00FFFF
      FF007B7B7B007B7B7B007B7B7B00FFFFFF00FFFFFF00FFFFFF007B7B7B000000
      0000000000007B7B7B00000000007B7B7B0000000000BDBDBD00BDBDBD00BDBD
      BD00000000000000000000000000BDBDBD00BDBDBD00BDBDBD00000000000000
      00000000000000000000BDBDBD00000000007B7B7B00FFFFFF00000000007B7B
      7B00FFFFFF000000000000000000000000000000000000000000000000007B7B
      7B00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE005AD6
      840052CE7B0052CE7B0052CE7B0052CE7B004ACE730042C6630039BD5A0031BD
      520031B5420021AD3100007B00006B423100000000007B7B7B007B7B7B007B7B
      7B007B7B7B00000000007B7B7B007B7B7B007B7B7B007B7B7B00000000000000
      000000000000000000007B7B7B007B7B7B000000000000000000000000000000
      000000000000BDBDBD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B00FFFFFF00000000007B7B
      7B00FFFFFF000000000000000000000000000000000000000000000000007B7B
      7B00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE005AD6
      84005AD684005AD684005AD6840052CE7B0052CE7B004ACE730042C66B0042C6
      5A0039BD520029B54200007B00006B4231000000000000000000FFFFFF007B7B
      7B00000000007B7B7B0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BDBDBD000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B00FFFFFF00000000007B7B
      7B00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF007B7B
      7B00FFFFFF00000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE005AD6
      84005AD684005AD684005AD684005AD6840052CE7B0052CE7B004ACE730042C6
      6B0042C65A0031B54A00007300006B423100000000007B7B7B007B7B7B000000
      00007B7B7B000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDBD
      BD00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B00FFFFFF00000000007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B0000000000000000007B7B7B00FFFFFF0084CE840073C67300BDEFCE005AD6
      84005AD684005AD684005AD684005AD684005AD6840052CE7B0052CE7B004ACE
      730042C66B0039BD5200007300006B4231007B7B7B0000000000FFFFFF007B7B
      7B00FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000BDBDBD00BDBDBD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007B7B7B00FFFFFF0084CE840073C67300E7F7EF00BDEF
      CE00BDEFCE00BDEFCE00BDEFCE00BDEFCE00BDEFCE00BDEFCE00B5EFCE00B5EF
      C600B5E7C600ADE7BD0094BD8C006B423100000000007B7B7B00000000007B7B
      7B00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDBDBD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF007B7B7B00FFFFFF0084CE840031A5310073C6730073C6
      730073C6730073C6730073C6730073C6730073C6730073C6730073C6730073C6
      730073C6730073C673006BBD6B00296B100000000000000000007B7B7B000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B7B007B7B
      7B007B7B7B007B7B7B007B7B7B00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000087CA87FF36731DFF6D4C37FF6D4C
      37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C37FF6D4C
      37FF6D4C37FF6D4C37FF675034FF079307FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000083CA83FF6FBE6EFF90BC8CFF0673
      02FF067702FF067A02FF067E02FF068202FF068402FF068502FF068A02FF068F
      02FF069302FF069302FF0B8E05FF624B2EFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000083CA83FF73C373FFABE1B6FF37B8
      50FF30B345FF29AF3BFF22AB31FF1AA427FF129A1BFF0B9110FF07930AFF0296
      03FF009800FF009800FF069302FF694731FF0000000000000000000000000000
      000000000000FFFFFF00F7E7DE00D6A59400D6AD9400F7E7DE00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E7EFE700ADC6A500FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E7E7E700A5A5A500ADADAD00EFEFEF00000000000000
      00000000000000000000000000000000000083CA83FF73C373FFB0E6BEFF43C3
      62FF3CBE57FF34B84BFF2CB33FFF248C66FF2131E3FF1C44B6FF0B9110FF0899
      0CFF029903FF009800FF069302FF694731FF0000000000000000000000000000
      0000FFFFFF00D6A58C00B5631800B5631000B5631000B5631800D6AD9C00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000E7EFE70039944200109429008CB58400FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF009C9C9C0010101000000000000000000018181800ADADAD000000
      00000000000000000000000000000000000083C983FF73C373FFB4E8C3FF4BC8
      6DFF43C261FF39BA54FF30B246FF228171FF0C0CFFFF0D28CDFF0F9116FF0D9A
      13FF08990CFF029603FF068F02FF694731FF0000000000000000000000000000
      0000EFDED600BD6B2100C6732100C67B2100C67B2100C6732100BD732100F7E7
      DE00000000000000000000000000000000000000000000000000000000000000
      0000E7EFE700319C4200009C2100009C2100009C21008CBD8C00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D6D6D600080808000000000000000000000000000000000010101000E7E7
      E7000000000000000000000000000000000083C983FF73C373FFB7EAC8FF52CC
      78FF48C369FF3AB555FF2DA742FF1E776EFF0909FFFF0B24CEFF118D19FF0F91
      16FF0B9110FF07930AFF068A02FF694731FF0000000000000000000000000000
      0000CE9C7B00CE843100D68C3100D68C3900D68C3900D68C3100CE843100DEBD
      A50000000000000000000000000000000000000000000000000000000000E7EF
      E70039A54A0000AD310000AD310000AD310000AD310000A529008CBD8C00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000848484000000000000000000000000000000000000000000000000009494
      94000000000000000000000000000000000083C983FF73C273FFB8EBC9FF56CE
      7DFF41979EFF1B35DAFF102AD6FF0B1EE0FF0101FFFF0308F4FF0721CEFF0722
      CDFF1139B6FF0B9110FF068502FF694731FF0000000000000000000000000000
      0000D6A58400DE9C4A00E79C4A00E7A54A00E7A54A00E7A54A00DE9C5200E7C6
      AD00000000000000000000000000000000000000000000000000FFFFFF0052AD
      630018BD520010BD4A0031BD63008CCE940010BD4A0000B5390008AD390094BD
      8C00FFFFFF000000000000000000000000000000000000000000000000000000
      0000737373000000000000000000000000000000000000000000000000008484
      84000000000000000000000000000000000083C983FF73C273FFB8EBC9FF57CF
      7FFF408CACFF1313FFFF0707FFFF0303FFFF0000FFFF0101FFFF0404FFFF0505
      FFFF1323E3FF129A1BFF068202FF694731FF0000000000000000000000000000
      0000EFDECE00EFBD7300F7BD7B00F7C67B00F7C67B00F7C67B00EFBD7300F7E7
      DE0000000000000000000000000000000000000000000000000000000000CEE7
      CE0052D6840063D68C00F7F7F700FFFFFF009CD6A5005AD68C0052CE7B0052C6
      73009CC69400FFFFFF0000000000000000000000000000000000000000000000
      0000B5B5B500000000000000000000000000000000000000000000000000C6C6
      C6000000000000000000000000000000000083C983FF73C273FFB8EBC9FF57CF
      7FFF51BD8BFF449BA0FF3F969EFF2D6DB4FF0B0BFFFF0F22E0FF1F7771FF2381
      75FF238A69FF1AA427FF068002FF694731FF0000000000000000000000000000
      0000FFFFFF00EFCEA500FFD69C00FFDE9C00FFDE9C00FFDE9C00EFCEAD00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000DEEFDE00F7FFF7000000000000000000FFFFFF00A5D6AD008CE7AD008CDE
      AD0094D69C000000000000000000000000000000000000000000000000000000
      0000FFFFFF004A4A4A000000000000000000000000000000000063636300FFFF
      FF000000000000000000000000000000000083C983FF73C273FFB8EBC9FF58D0
      80FF57CF7FFF57CF7FFF56CD7DFF40979DFF0B0BFFFF122CD7FF30A946FF34B5
      4BFF30B545FF24AC35FF067C02FF694731FF0000000000000000000000000000
      000000000000FFFFFF00F7E7D600EFCEAD00E7CEAD00FFEFE700FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00A5DEB500A5DE
      B500FFFFFF000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF009C9C9C00424242004A4A4A00A5A5A500FFFFFF000000
      00000000000000000000000000000000000083C983FF73C273FFB8EBC9FF58D0
      80FF58D080FF58D080FF57CF7FFF439AA0FF1111FFFF1A34DBFF3DB759FF3DBD
      59FF38BB51FF2CB240FF067902FF694731FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000083C983FF73C273FFB8EBC9FF58D0
      80FF58D080FF58D080FF57CF7FFF50BD8BFF3E8BACFF41969FFF4BC66EFF46C4
      67FF40C05DFF33B64BFF067502FF694731FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000083C983FF73C273FFB8EBC9FF58D0
      80FF58D080FF58D080FF58D080FF57CF7FFF57CF7FFF56CE7EFF54CD7BFF4FCA
      73FF47C568FF3ABA55FF067102FF694731FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000083C983FF73C273FFE0F6E8FFB8EB
      C9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB8EBC9FFB7EAC8FFB5E9
      C5FFB2E7C1FFADE2B9FF90BB8CFF694731FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000083C983FF34A634FF73C273FF73C2
      73FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C273FF73C2
      73FF73C373FF73C373FF6FBE6EFF2F6E16FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000296B940000639400006394000063
      9400006394000063940000639400006394000063940000639400006394000063
      9400B5BDC6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084A5AD004AADCE0039BDE70039BD
      E70031BDE70031BDE70031B5E70029B5E70029B5E70021B5E70021ADE70010A5
      DE004A9CBD000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084CEDE007BADBD005AD6F70052D6
      F70052CEF7004ACEF7004ACEF70042CEEF0039C6EF0039C6EF0031BDEF0031BD
      EF001894C600C6DEE70000000000000000000000000000000000000000000000
      000000000000FFFFFF00CEDEC60084B5840084B57B00C6DEC600FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00A5CEDE0063ADDE0063ADDE009CCEDE00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00CECEEF008484D6007B7BD600C6C6EF00FFFFFF000000
      00000000000000000000000000000000000084D6E70084C6D60063C6DE005AD6
      F70052D6F70052D6F7004ACEF7004ACEF70042CEF70042C6EF0039C6EF0039C6
      EF0021B5E700428CAD00F7F7F700000000000000000000000000000000000000
      0000FFFFFF0084BD8400089C290000942100009421000894210073B57300FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF005AA5DE001894FF001894FF00188CFF00108CFF005AA5DE00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF008484D6000808BD000000C6000000C6000808B5007373CE00FFFF
      FF000000000000000000000000000000000084D6E70084E7F7007BA5AD0063D6
      EF005AD6F7005AD6F70052D6F7004ACEF7004ACEF7004ACEF70042C6EF0039C6
      EF0039C6EF00109CCE00BDCED600000000000000000000000000000000000000
      0000CEDEC60000A5290000A5290000A5310000A5290000A52900009C2100BDD6
      BD00000000000000000000000000000000000000000000000000000000000000
      00009CC6DE00189CFF0021A5FF00219CFF00189CFF001894FF00188CFF009CC6
      DE00000000000000000000000000000000000000000000000000000000000000
      0000D6D6EF000000CE000000D6000000D6000000D6000000CE000000C600BDBD
      E700000000000000000000000000000000008CD6E70084EFF70084CEDE0073BD
      CE0063DEF7005AD6F7005AD6F70052D6F7004ACEF7004ACEF7004ACEF70042C6
      EF0039C6EF0031BDEF004294BD00000000000000000000000000000000000000
      00007BBD840000B5390000B5390000BD420000BD420000B5390000AD31006BB5
      7300000000000000000000000000000000000000000000000000000000000000
      00005AADE70021ADFF0021B5FF0021ADFF0021ADFF0021A5FF00189CFF0052A5
      E700000000000000000000000000000000000000000000000000000000000000
      00007373DE000000DE000000E7000000E7000000E7000000E7000000DE006363
      CE00000000000000000000000000000000008CDEE7008CEFFF0084EFFF007BB5
      C60063DEF70063DEF7005AD6F7005AD6F70052D6F70052CEF7004ACEF7004ACE
      F70042C6EF0039C6EF001894C6009CC6D6000000000000000000000000000000
      00007BC68C0010C6520000CE520000CE520000CE520000C64A0010C652006BBD
      7B00000000000000000000000000000000000000000000000000000000000000
      00006BBDE70042C6FF0031C6FF0029BDFF0029BDFF0029B5FF0042B5FF0063B5
      E700000000000000000000000000000000000000000000000000000000000000
      00007B7BDE001818EF000808F7000000F7000000F7000000EF001818EF006363
      D600000000000000000000000000000000008CDEE7008CEFFF008CEFFF007BCE
      DE007BB5C60063D6F70063D6F70063D6F7005AD6EF005ACEEF0052CEEF0052CE
      EF004AC6EF004AC6EF0029B5E700317BA5000000000000000000000000000000
      0000D6EFDE0031DE7B0031E77B0031E7840031E77B0029DE730031D67300CEE7
      CE00000000000000000000000000000000000000000000000000000000000000
      0000B5DEEF0073DEFF0073DEFF006BDEFF006BD6FF006BD6FF006BCEFF00B5DE
      EF00000000000000000000000000000000000000000000000000000000000000
      0000D6D6F7004A4AFF004242FF004242FF004242FF004242FF004A4AFF00C6C6
      EF00000000000000000000000000000000008CDEE7008CEFFF008CEFFF008CEF
      F70084CED60084C6D60084C6D60084C6D60084C6D6007BC6D6007BC6D6007BC6
      D6007BBDD60039739400B5B5B500B5B5B5000000000000000000000000000000
      0000FFFFFF0094E7AD007BF7AD008CF7B5007BEFAD005AEF9C008CE7A500FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF008CD6EF008CEFFF0084EFFF0084E7FF0084E7FF008CCEEF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF009494EF007373FF007373FF007373FF007373FF008C8CEF00FFFF
      FF00000000000000000000000000000000008CDEE7008CF7FF008CEFFF008CEF
      FF008CEFFF0084E7F70084D6E70084D6E70084D6E7007BD6E7007BD6E7007BD6
      E7007BCEE700296B8C0000000000000000000000000000000000000000000000
      000000000000FFFFFF00DEF7E700A5DEB5009CDEAD00CEEFD600FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00C6E7F7009CE7EF009CDEEF00BDE7F700FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00CECEF7008C8CEF008C8CEF00CECEF700FFFFFF000000
      00000000000000000000000000000000000094DEE70094F7FF008CF7FF008CEF
      FF008CEFF7007BB5C600C6C6CE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008CBDC6008CD6DE008CD6DE008CD6
      DE007BB5C600BDC6C60000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7E7E700E7E7E700E7E7E700E7E7
      E700E7E7E700FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001818180018181800181818001818
      1800181818001818180018181800181818001818180018181800181818001818
      1800181818001818180018181800080808001818180018181800181818001818
      1800181818001818180018181800181818001818180018181800181818001818
      1800181818001818180018181800080808001818180018181800181818001818
      1800181818001818180018181800181818001818180018181800181818001818
      1800181818001818180018181800080808000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A94AD000073A5000073A5000073
      A5000073A5000073A5000073A5000073A5000073A5000073A5000073A5000073
      A5000073A5000073A5000073A500006394004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818008CD6DE0063D6EF0063D6EF005AD6
      EF005AD6EF0052CEEF0052CEEF0052CEEF004AC6EF0042C6EF0042C6EF0039C6
      EF0039C6EF0039C6EF000894CE00006394004A4A4A004A4A4A00317B310000FF
      000010CE10004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A00425A420000FF
      000000FF00004A4A4A004A4A4A00181818004A4A4A004A4A4A00317B7B0000FF
      FF0010CECE004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A00425A5A0000FF
      FF0000FFFF004A4A4A004A4A4A00181818004A4A4A004A4A4A0031317B000000
      FF001010CE004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A0042425A000000
      FF000000FF004A4A4A004A4A4A00181818008CD6DE008CF7F70084EFF70084EF
      F7007BE7F70073E7F70073E7F7006BDEF70063DEF70063DEF7005AD6F70052D6
      F70052D6F70052D6F7000894CE00006394004A4A4A004A4A4A002994290000FF
      000000FF000010CE10004A4A4A004A4A4A004A4A4A00425A420000FF000000FF
      000000FF00004A4A4A004A4A4A00181818004A4A4A004A4A4A002994940000FF
      FF0000FFFF0010CECE004A4A4A004A4A4A004A4A4A00425A5A0000FFFF0000FF
      FF0000FFFF004A4A4A004A4A4A00181818004A4A4A004A4A4A00292994000000
      FF000000FF001010CE004A4A4A004A4A4A004A4A4A0042425A000000FF000000
      FF000000FF004A4A4A004A4A4A00181818008CD6DE008CF7F7008CF7F70084EF
      F70084EFF7007BE7F70073E7F70073E7F7006BDEF70063DEF70063DEF7005AD6
      F70052D6F70052D6F7000894CE00006394004A4A4A004A4A4A004A4A4A0018B5
      180000FF000000FF000010CE10004A4A4A00425A420000FF000000FF000000FF
      0000425A42004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A0018B5
      B50000FFFF0000FFFF0010CECE004A4A4A00425A5A0000FFFF0000FFFF0000FF
      FF00425A5A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A001818
      B5000000FF000000FF001010CE004A4A4A0042425A000000FF000000FF000000
      FF0042425A004A4A4A004A4A4A00181818008CD6DE0094F7FF008CF7F7008CF7
      F70084EFF70084EFF7007BE7F70073E7F70073E7F7006BDEF70063DEF70063DE
      F7005AD6F70052D6F7000894CE00006394004A4A4A004A4A4A004A4A4A004A4A
      4A0018B5180000FF000000FF000010CE100000FF000000FF000000FF0000425A
      42004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A0018B5B50000FFFF0000FFFF0010CECE0000FFFF0000FFFF0000FFFF00425A
      5A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A001818B5000000FF000000FF001010CE000000FF000000FF000000FF004242
      5A004A4A4A004A4A4A004A4A4A00181818008CD6DE0094F7FF0094F7FF0094F7
      FF008CF7F70084EFF70084EFF7007BEFF70073E7F70073E7F7006BDEF7006BDE
      F70063DEF7005AD6F7000894CE00006394004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A0018B5180000FF000000FF000000FF000000FF0000425A42004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A0018B5B50000FFFF0000FFFF0000FFFF0000FFFF00425A5A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A001818B5000000FF000000FF000000FF000000FF0042425A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818008CD6DE0094F7FF0094F7FF0094F7
      FF0094F7FF008CF7F70084EFF70084EFF7007BEFF7007BE7F70073E7F7006BE7
      F7006BDEF70063DEF7000894CE00006394004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A00425A420000FF000000FF000000FF000010CE10004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A00425A5A0000FFFF0000FFFF0000FFFF0010CECE004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A0042425A000000FF000000FF000000FF001010CE004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818008CD6DE0094F7FF0094F7FF0094F7
      FF0094F7FF0094F7FF008CF7FF0084EFF70084EFF7007BEFF7007BE7F70073E7
      F7006BE7F7006BDEF7000894CE00006394004A4A4A004A4A4A004A4A4A004A4A
      4A00425A420000FF000000FF000000FF000000FF000000FF000010CE10004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A00425A5A0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0010CECE004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A0042425A000000FF000000FF000000FF000000FF000000FF001010CE004A4A
      4A004A4A4A004A4A4A004A4A4A00181818008CD6DE0094F7FF0094F7FF0094F7
      FF0094F7FF0094F7FF0094F7FF008CF7F70084EFF70084EFF7007BEFF7007BE7
      F70073E7F7006BE7F7000894CE00006394004A4A4A004A4A4A004A4A4A00425A
      420000FF000000FF000000FF0000425A420018B5180000FF000000FF000010CE
      10004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A00425A
      5A0000FFFF0000FFFF0000FFFF00425A5A0018B5B50000FFFF0000FFFF0010CE
      CE004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004242
      5A000000FF000000FF000000FF0042425A001818B5000000FF000000FF001010
      CE004A4A4A004A4A4A004A4A4A00181818008CD6DE0094F7FF0094F7FF0094F7
      FF0094F7FF0094F7FF0094F7FF0094F7FF008CF7F70084EFF70084EFF7007BEF
      F7007BE7F70073E7F7000894CE00006394004A4A4A004A4A4A004A524A0000FF
      000000FF000000FF0000425A42004A4A4A004A4A4A0018B5180000FF000000FF
      000010CE10004A4A4A004A4A4A00181818004A4A4A004A4A4A004A52520000FF
      FF0000FFFF0000FFFF00425A5A004A4A4A004A4A4A0018B5B50000FFFF0000FF
      FF0010CECE004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A52000000
      FF000000FF000000FF0042425A004A4A4A004A4A4A001818B5000000FF000000
      FF001010CE004A4A4A004A4A4A00181818008CCED60094E7EF0094E7EF0094E7
      EF0094E7EF0094E7EF0094E7EF0094E7EF0094E7EF008CE7EF008CE7EF0084E7
      EF007BDEEF0073DEEF0073DEEF0021739C004A4A4A004A4A4A0018BD180000FF
      000000FF0000425A42004A4A4A004A4A4A004A4A4A004A4A4A0018B5180000FF
      000000FF00004A4A4A004A4A4A00181818004A4A4A004A4A4A0018BDBD0000FF
      FF0000FFFF00425A5A004A4A4A004A4A4A004A4A4A004A4A4A0018B5B50000FF
      FF0000FFFF004A4A4A004A4A4A00181818004A4A4A004A4A4A001818BD000000
      FF000000FF0042425A004A4A4A004A4A4A004A4A4A004A4A4A001818B5000000
      FF000000FF004A4A4A004A4A4A00181818008CB5BD008CC6CE008CC6CE008CC6
      CE008CC6CE0084B5C60084949C00A5ADB500A5A5A500A5A5A500A5A5A500A5A5
      A500A5A5A500A5A5A500A5A5A500E7E7E7004A4A4A004A4A4A004A4A4A0018BD
      18004A524A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A002994
      2900317B31004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A0018BD
      BD004A5252004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A002994
      9400317B7B004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A001818
      BD004A4A52004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A002929
      940031317B004A4A4A004A4A4A001818180084C6D60094F7FF0094F7FF008CF7
      FF008CEFF70084B5BD00CECED600FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800A5ADAD008C9494008C9494008C94
      94008C949400B5BDBD00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000394A0000394A0000394A000039
      4A0000394A0000394A0000394A0000394A0000394A0000394A0000394A000039
      4A0000394A0000394A0000394A0000394A0000004A0000004A0000004A000000
      4A0000004A0000004A0000004A0000004A0000004A0000004A0000004A000000
      4A0000004A0000004A0000004A0000004A008400000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000084000000840000001818180018181800181818001818
      1800181818001818180018181800181818001818180018181800181818001818
      1800181818001818180018181800080808000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B50000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000394A00000084000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000004A00B5290000FF000000FF000000FF00
      0000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF00
      0000FF000000FF000000FF000000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000084B5000084B5000084B5000084
      B5000084B5000084B5000084B5000084B5000084B5000084B5000084B5000084
      B5000084B5000084B5000084B50000394A000000840000008400000084000000
      8400000084000000840000008400000084000000840000008400000084000000
      840000008400000084000000840000004A00B5290000B5290000B5290000B529
      0000B5290000B5290000B5290000B5290000B5290000B5290000B5290000B529
      0000B5290000B5290000B5290000840000004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A00181818000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004242420042424200424242004242
      4200424242004242420042424200424242004242420042424200424242004242
      4200424242004242420042424200181818004242420042424200424242004242
      4200424242004242420042424200424242004242420042424200424242004242
      420042424200424242004242420018181800004A2100004A2100004A2100004A
      2100004A2100004A2100004A2100004A2100004A2100004A2100004A2100004A
      2100004A2100004A2100004A2100004A21000000000000000000FFFFFF00F7F7
      F700EFEFEF00E7E7E700DEDEDE00DEDEDE00DEDEDE00DEDEDE00E7E7E700F7F7
      F700FFFFFF00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A2100FFFFFF00D6D6D6006B6B6B007373
      7300848484008C8C8C009494940094949400949494008C8C8C00848484007B7B
      7B006B6B6B00D6D6D600F7F7F70000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A2100FFFFFF00DEDEDE00525252007373
      730094949400BDBDBD00DEDEDE00F7F7F700DEDEDE00BDBDBD009C9C9C007373
      730052525200FFFFFF00FFFFFF0000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00B5B5B500BDBDBD00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000636363008C8C
      8C00A5A5A500BDBDBD00E7E7E700F7F7F700DEDEDE00C6C6C600ADADAD008C8C
      8C006B6B6B00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE000000000029292900CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000636363008C8C
      8C00A5A5A500BDBDBD00EFEFEF00F7F7F700DEDEDE00C6C6C600ADADAD008C8C
      8C006B6B6B00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE002929290052525200CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000525252007B7B
      7B009C9C9C00B5B5B500C6C6C600CECECE00C6C6C600B5B5B5009C9C9C007B7B
      7B005A5A5A00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00292929004A4A4A00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000525252007B7B
      7B009C9C9C00BDBDBD00E7E7E700FFFFFF00E7E7E700C6C6C600A5A5A5007B7B
      7B005A5A5A00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE000000000000000000CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000636363009494
      9400ADADAD00C6C6C600EFEFEF00FFFFFF00E7E7E700CECECE00B5B5B5009494
      94006B6B6B00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00313131000000000000000000C6C6C600CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000636363009494
      9400ADADAD00C6C6C600F7F7F700FFFFFF00E7E7E700CECECE00B5B5B5009494
      94006B6B6B00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE005A5A5A000000000000000000CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000525252007B7B
      7B0094949400ADADAD00C6C6C600CECECE00C6C6C600ADADAD009C9C9C007B7B
      7B005A5A5A00000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00ADADAD008C8C8C00B5B5B500CECECE00CECECE0029292900000000009C9C
      9C00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000636363009494
      9400B5B5B500D6D6D600F7F7F700FFFFFF00F7F7F700D6D6D600B5B5B5008C8C
      8C0063636300000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00848484000000000008080800C6C6C600C6C6C6000808080000000000B5B5
      B500CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A210000000000000000007B7B7B00ADAD
      AD00CECECE00E7E7E700F7F7F700FFFFFF00F7F7F700DEDEDE00C6C6C600A5A5
      A50073737300000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00212121000000000000000000000000000000000052525200CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A2100000000000000000084848400B5B5
      B500CECECE00E7E7E700FFFFFF00FFFFFF00F7F7F700DEDEDE00C6C6C600ADAD
      AD0084848400000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00ADADAD007373730073737300C6C6C600CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000C6C6C600DEDE
      DE00EFEFEF00F7F7F700FFFFFF00FFFFFF00FFFFFF00F7F7F700E7E7E700D6D6
      D600C6C6C600000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000004A21000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE0042424200CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00424242000084000000840000008400000084
      0000008400000084000000840000008400000084000000840000008400000084
      0000008400000084000000840000004A21000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6844200D6945A00D6AD8400DEBD9C00DEBD9C00D6AD8C00CE945A00BD73
      29009C6300000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00F7F7
      F700F7F7F700FFFFFF00000000000000000029A5290052945200215210002152
      1000215210002152100021521000215210002152100021521000215210002152
      10002152100021521000315A1800000000000000000000000000ADAD5200D69C
      5A00E7C6A500EFE7E700EFE7DE00DECEC600DECEBD00E7D6CE00EFEFE700E7CE
      B500C68C5200BD63180000000000000000000000000000000000000000000000
      0000000000000000000000000000F7F7FF00ADADE700DEDEF700FFFFFF00EFEF
      FF009C9CDE00EFEFFF000000000000000000FFFFFF00F7F7F700EFEFEF00E7E7
      E700DEDEDE00DEDEDE00DEDEDE00DEDEDE00E7E7E700F7F7F7004A6B4200087B
      1000087B100000000000000000000000000029A52900ADE7BD0039BD5A0031BD
      520031B5420029B5390021AD310018AD290010A5210008A51000089C0800009C
      0000009C0000009C000039521800000000000000000000000000D69C6300EFDE
      CE00EFE7DE00C69C7B00BD7B4200BD733100B56B2900B56B3100BD845200DECE
      BD00EFE7DE00CE945A00B55A100000000000000000000000000000000000FFFF
      FF00F7F7F700EFEFEF00EFEFEF009C9CD6000000C6001010AD00CECEEF004242
      BD000000C6006363C600F7F7FF00000000006B6B6B0073737300848484008C8C
      8C009494940094949400949494008C8C8C00848484007B7B7B00295229000084
      10000084100000000000000000000000000029A52900ADE7BD0042C6630039BD
      5A0031BD520029AD390021A5310021AD310018AD290010A5210008A51000089C
      0800009C0000009C0000395218000000000000000000D69C5A00EFD6C600E7DE
      CE00BD845A00BD7B3100C67B3100FFFFFF00FFFFFF00BD6B2100B5631000B56B
      2900D6B59C00EFE7DE00C6844200AD52000000000000FFFFFF00E7E7E700DEDE
      DE00ADADAD00D6D6D600F7F7F7006B6BD6001010D6000000D6000000C6000000
      D6000000D6000000CE00FFFFFF0000000000525252007373730094949400BDBD
      BD00DEDEDE00F7F7F700DEDEDE00BDBDBD004A6B4200395A3100186318000094
      2100009C210063735A0063735A00C6D6BD0029A52900B5EFC6004ACE6B0042C6
      630052C66B00FFFFFF003994420021A5310021AD310018AD290010A5210008A5
      1000089C0800009C00003952180000000000D6946B00E7BD9400F7EFE700C694
      6300C6844200CE844200CE844200EFD6B500EFCEB500C6732900BD6B2100B563
      1800B56B3100DECEBD00E7C6AD00BD6B180000000000E7E7E700B5B5B500FFFF
      FF00FFFFFF00F7F7F700F7F7F700F7F7F7007373DE000000E7000000E7000000
      E7000808E700F7F7FF000000000000000000636363008C8C8C00A5A5A500BDBD
      BD00E7E7E700F7F7F700DEDEDE00BDBDBD0000A5290000A5290000AD310000AD
      310000A5310000A52900009C2100317B390029A52900B5EFC60052CE7B0052BD
      6B00FFFFFF00FFFFFF00FFFFFF00217B210021A5310021B5310018AD290018A5
      210010A51800089C10003952180000000000D69C6300EFDECE00D6BDA500C684
      4A00CE8C4A00D68C4A00D68C4A00E7C6A500E7BD9C00CE7B3100CE7B2900BD6B
      2100B5631800BD845200EFEFE700C6844200FFFFFF00CECECE00F7F7F700E7E7
      E700D6D6D600E7E7DE00E7E7E700D6D6E7007373D6004A42F7000000F7000000
      F7001010D600DEDEF700FFFFFF0000000000636363008C8C8C00A5A5A500BDBD
      BD00EFEFEF00F7F7F700DEDEDE00BDBDBD0039CE6B0031C6630018C6520010C6
      4A0010BD4A0021C65A0031BD5A0052945A0029A52900B5EFC60052C67300F7FF
      F700FFFFFF00FFFFFF00FFFFFF00F7F7F7002984290021A5310021B5310018AD
      290018A5210010A518003952180000000000DEAD7B00F7EFE700CE9C7300CE94
      5200D6945A00DE945A00DE945200FFFFFF00FFFFFF00CE844200CE843100C673
      2900BD6B1800B56B3100E7DED600CE9C630000000000EFEFEF00CECECE00BDBD
      BD00D6D6CE00DEDEDE00DEDEDE007373D6005A5AFF005A5AFF006363FF000808
      FF000000FF001010D600F7F7FF0000000000525252007B7B7B009C9C9C00B5B5
      B500C6C6C600CECECE00C6C6C600B5B5B500949C94007B7B7B004A84520052DE
      8C0063E79400F7F7F700F7F7F700FFFFFF0029A52900B5EFC600C6EFD600FFFF
      FF00EFF7EF004ABD6300E7F7E700FFFFFF00FFFFFF003994420021A5310021B5
      310018AD290018A521003952180000000000DEAD8400F7F7F700C68C6300D69C
      6300DE9C6300DE9C5A00DE9C5A00F7EFDE00FFFFFF00F7E7DE00DEAD7B00C67B
      3100BD732100B56B2100DECEBD00D6AD8400EFEFEF00E7E7E700948C8C00ADAD
      AD00C6C6C600847B7B00847B7B007373B5007373FF008484FF009494A5008C8C
      F7005252FF001818F700FFFFFF0000000000525252007B7B7B009C9C9C00BDBD
      BD00E7E7E700FFFFFF00E7E7E700C6C6C600A5A5A5007B7B7B004A8452007BEF
      AD0084F7BD0000000000000000000000000029A52900B5EFC6005AD68400CEF7
      D6004AC66B0052CE7B004ACE7300FFFFFF00FFFFFF00FFFFFF00006B000021A5
      310021B5310018AD29003952180000000000DEB58400FFF7F700C6946300DEA5
      6B00DEA56B00DEA56300DE9C5A00DE9C5A00E7B58400FFF7F700FFFFFF00DEAD
      8400C6732900B56B2100DECEBD00D6A57B00DEDEDE00CECECE008C8484009C9C
      9C00848484008C8C84009494940094948C007B7BBD008C8C94009C9C9C007B7B
      7B008C8CF700F7F7FF0000000000000000006363630094949400ADADAD00C6C6
      C600EFEFEF00FFFFFF00E7E7E700CECECE00B5B5B50094949400527B52009CF7
      C6009CFFC60000000000000000000000000029A52900B5EFC6005AD684005AD6
      84005AD684005AD6840052CE7B005ACE7B00EFFFEF00FFFFFF00FFFFFF00398C
      390021A5310021B539003952180000000000E7B58400F7F7EF00CE9C7B00DEA5
      7300DEA57300DEA56B00DE9C5A00DE9C5A00DE9C5A00EFD6BD00FFFFFF00F7E7
      DE00BD732900B5733100EFDED600CE9C6300D6D6D600C6C6C6007B7373008C8C
      8C008C8C8C00A5A5A500B5B5B500B5B5AD00A59C9C008C8C8C008C8C8400736B
      6B00D6D6D600F7F7FF0000000000000000006363630094949400ADADAD00C6C6
      C600F7F7F700FFFFFF00E7E7E700CECECE00B5B5B500949494006B6B6B000000
      00000000000000000000000000000000000029A52900B5EFC6005AD684005AD6
      84005AD684005AD684005AD6840052CE7B004ACE7300E7F7EF00FFFFFF00FFFF
      FF00318C390029B542003952180000000000DE9C6300F7E7CE00DEC6AD00D69C
      6B00DEAD7300E7BD8C00E7C6AD00D69C6300D69C6300F7EFDE00FFFFFF00F7EF
      DE00BD732900BD8C5A00F7EFEF00CE844200DEDEDE00CECECE00636363007B7B
      7B0094949400CECECE00DEDEDE00DEDEDE00C6BDBD008C8484007B737300847B
      7B00CECECE00FFFFFF000000000000000000525252007B7B7B0094949400ADAD
      AD00C6C6C600CECECE00C6C6C600ADADAD009C9C9C007B7B7B005A5A5A000000
      00000000000000000000000000000000000029A52900B5EFC6005AD684005AD6
      84005AD684005AD684005AD6840052CE7B0052CE7B005ACE7B00FFFFFF00FFFF
      FF0042B55A0031BD4A003952180000000000DE9C5A00E7C69C00F7F7EF00CE9C
      7B00DEA57300E7BD9400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00DEAD
      8400BD7B3900E7CEC600E7C6A500C6732900FFFFFF00C6BDBD00ADA5A5006363
      6300737373008C8C8C00CEC6C600BDBDBD007B7B7B0073737300635A5A00C6BD
      BD00BDBDBD000000000000000000000000006363630094949400B5B5B500D6D6
      D600F7F7F700FFFFFF00F7F7F700D6D6D600B5B5B5008C8C8C00636363000000
      00000000000000000000000000000000000029A52900B5EFC6005AD684005AD6
      84005AD684005AD684005AD684005AD684005AD6840052CE7B0052CE730063CE
      7B0042C6630039BD5200395218000000000000000000DE9C6300F7DEC600EFDE
      D600CE9C7300D6A57300E7BD9400EFD6B500EFD6C600E7CEAD00D6A56B00BD7B
      4200D6BDA500F7EFDE00CE844200FF7B000000000000C6C6C600BDBDBD00A5A5
      A500636363006B6363006B6B6B006B6B6B00636363006B6B6B00B5B5B500C6BD
      BD00EFEFEF000000000000000000000000007B7B7B00ADADAD00CECECE00E7E7
      E700F7F7F700FFFFFF00F7F7F700DEDEDE00C6C6C600A5A5A500737373000000
      00000000000000000000000000000000000029A52900B5EFC6005AD684005AD6
      84005AD684005AD684005AD684005AD684005AD684005AD6840052CE7B0052CE
      73004AC66B0042C6630039522100000000000000000000000000E7AD7300F7E7
      CE00F7EFE700CEAD8C00C6946300CE8C5A00C68C5200C6845200C68C6300E7D6
      C600F7EFE700CE945200CE7B3100000000000000000000000000BDBDBD00C6BD
      BD00B5B5B500ADA5A5009C9494009C9C9C00ADADAD00B5B5B500CECECE00DEDE
      DE000000000000000000000000000000000084848400B5B5B500CECECE00E7E7
      E700FFFFFF00FFFFFF00F7F7F700DEDEDE00C6C6C600ADADAD00848484000000
      00000000000000000000000000000000000029A52900EFFFF700D6F7DE00D6F7
      DE00D6F7DE00D6F7DE00D6F7DE00D6F7DE00D6F7DE00D6F7DE00D6F7DE00D6F7
      DE00D6F7DE00D6F7DE005A845200000000000000000000000000FFFF0000DEA5
      6B00EFCEAD00F7F7EF00F7EFE700E7D6CE00E7D6C600EFDED600F7F7EF00EFCE
      B500D6945200CE7B31000000000000000000000000000000000000000000E7E7
      DE00BDBDBD00D6D6D600DEDEDE00DEDEDE00EFEFEF00DEDEDE00F7F7F7000000
      000000000000000000000000000000000000C6C6C600DEDEDE00EFEFEF00F7F7
      F700FFFFFF00FFFFFF00FFFFFF00F7F7F700E7E7E700D6D6D600C6C6C6000000
      0000000000000000000000000000000000007BC67B005ABD5A005ABD5A005ABD
      5A005ABD5A005ABD5A005ABD5A005ABD5A005ABD5A005ABD5A005ABD5A005ABD
      5A005ABD5A005ABD5A005ABD5A00000000000000000000000000000000000000
      0000E79C5A00DEAD7300E7B58C00E7C69C00E7C69C00E7B58400DE9C6300CE84
      4200AD5200000000000000000000000000000000000000000000000000000000
      000000000000BDBDBD00CECECE00E7E7E700CECECE0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000D00000000100010000000000800600000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FFFF00000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FFFF000000000000F83F0000
      00000000E00F000000000000CFC700000000000087E3000000000000A3F30000
      0000000031F900000000000038F90000000000003C790000000000003E390000
      000000003F190000000000009F8B0000000000008FC3000000000000C7E70000
      00000000E00F000000000000F83F000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF0000000000008FFF00000000
      00008FFF00000000000087FF00000000000080FF000000000000887F00000000
      0000E07F000000000000E07F000000000000800F000000000000800700000000
      0000800300000000000080010000000000008001000000000000E00000000000
      0000FC00000000000000FFC1000000000001FFFFFFFFFF3F0000C0030007FF07
      000180010003F801800180010001F801000080010001F001000080010001F001
      0000800100010001000080010001000100008001000100010000800180010001
      00008001C001F00100008001E007F00100008001E003F80100008001F003F801
      0000C003F803F8010000FFFFFFFFF8010000C005FC07C007000082038003E5CF
      00002806000780000000162C003C000000003FC200183FEC000021C200003004
      000003C20000200400003FC2000027E4000038C4000027E40000401A001827E4
      0000843C803C27E40000CBFFE3FF2004000097FF87FF200C000047FF0FFF3FFC
      0000AFFF8FFF00000000DFFFDFFF0001FFFFFFFFFFFF0000FFFFFFFFFFFF0000
      FFFFFFFFFFFF0000FFFFFFFFFFFF0000F81FFC7FFC3F0000F00FF83FF01F0000
      F00FF01FF00F0000F00FE00FF00F0000F00FC007F00F0000F00FE003F00F0000
      F00FF307F00F0000F81FFF87F81F0000FFFFFFEFFFFF0000FFFFFFFFFFFF0000
      FFFFFFFFFFFF0000FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      0007FFFFFFFFFFFF0007FFFFFFFFFFFF0003F81FF81FF81F0001F00FF00FF00F
      0001F00FF00FF00F0001F00FF00FF00F0000F00FF00FF00F0000F00FF00FF00F
      0000F00FF00FF00F0003F81FF81FF81F0003FFFFFFFFFFFF03FFFFFFFFFFFFFF
      03FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFF0000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000FF
      00000000000001FF000000000000FFFF00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFF000000000000C007000000000000
      00010000000000000001000000000000C007000000000000C007000000000000
      C007000000000000C007000000000000C007000000000000C007000000000000
      C007000000000000C007000000000000C007000000000000C007000000000000
      C007000000000000FFFF000000000000FFFFF007FF37FFC30001C003FE030007
      0001C001E0010007000180008001000000010000800300000001000000010000
      000100008001000000010000000100070001000000030007000100000003001F
      000100000003001F000100000007001F000180008007001F0001C001C00F001F
      0001C003E01F001F0001F007F87FFFFF00000000000000000000000000000000
      000000000000}
  end
  object PopupMenu1: TPopupMenu
    Images = ImageList1
    OnPopup = PopupMenu1Popup
    Left = 8
    Top = 72
    object N6: TMenuItem
      Caption = #1056#1072#1079#1074#1077#1088#1085#1091#1090#1100' '#1076#1077#1088#1077#1074#1086' '#1086#1073#1098#1077#1082#1090#1086#1074
      OnClick = N6Click
    end
    object N21: TMenuItem
      Caption = #1057#1074#1077#1088#1085#1091#1090#1100' '#1076#1077#1088#1077#1074#1086' '#1086#1073#1098#1077#1082#1090#1086#1074
      OnClick = N21Click
    end
    object Control_pdi: TMenuItem
      Caption = #1050#1086#1085#1090#1088#1086#1083#1100
      OnClick = Control_pdiClick
    end
    object N11: TMenuItem
      Caption = '-'
    end
    object OnOff_pdi: TMenuItem
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100'/'#1042#1099#1082#1083#1102#1095#1080#1090#1100
      OnClick = OnOff_pdiClick
    end
    object Off_pdi: TMenuItem
      Caption = #1047#1072#1082#1088#1099#1090#1100
      OnClick = Off_pdiClick
    end
    object N8: TMenuItem
      Caption = '-'
    end
    object Dk_pdi: TMenuItem
      Caption = #1044#1050
      OnClick = Dk_pdiClick
    end
    object N9: TMenuItem
      Caption = '-'
    end
    object Pult_pdi: TMenuItem
      Caption = #1056#1072#1073#1086#1090#1072' '#1089' '#1087#1091#1083#1100#1090#1086#1084
      OnClick = Pult_pdiClick
    end
    object N15: TMenuItem
      Caption = '-'
    end
    object OnOffAll_pdi: TMenuItem
      Caption = #1042#1099#1082#1083#1102#1095#1080#1090#1100' '#1074#1089#1077
      OnClick = OnOffAll_pdiClick
    end
    object N24: TMenuItem
      Caption = '-'
    end
    object PultOff_pdi: TMenuItem
      Caption = #1047#1072#1074#1077#1088#1096#1077#1085#1080#1077' '#1088#1072#1073#1086#1090#1099' '#1089' '#1087#1091#1083#1100#1090#1086#1084
      OnClick = PultOff_pdiClick
    end
    object Metka_pdi: TMenuItem
      Caption = #1054#1090#1084#1077#1090#1082#1072' '#1095#1072#1089#1086#1074#1086#1075#1086
      OnClick = Metka_pdiClick
    end
    object ConnectBlock_pdi: TMenuItem
      Caption = 'ConnectBlock_pdi'
      OnClick = ConnectBlock_pdiClick
    end
    object OnOff2_pdi: TMenuItem
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100'/'#1042#1099#1082#1083#1102#1095#1080#1090#1100
      OnClick = OnOff2_pdiClick
    end
    object ChangeStatus_pdi: TMenuItem
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1089#1086#1089#1090#1086#1103#1085#1080#1077
      object Norm_pdi: TMenuItem
        Caption = #1053#1086#1088#1084#1072
        ImageIndex = 7
        OnClick = Norm_pdiClick
      end
      object As_pdi: TMenuItem
        Caption = #1058#1088#1077#1074#1086#1075#1072' ('#1089#1088#1072#1073#1086#1090#1082#1072')'
        ImageIndex = 9
        OnClick = As_pdiClick
      end
      object N_pdi: TMenuItem
        Caption = #1053#1077#1090' '#1089#1074#1103#1079#1080
        ImageIndex = 8
        OnClick = N_pdiClick
      end
    end
  end
  object Table1: TTable
    OnCalcFields = Table1CalcFields
    Left = 856
    Top = 8
    object Table1Cnt: TAutoIncField
      FieldName = 'Cnt'
      ReadOnly = True
    end
    object Table1Dt: TDateTimeField
      DisplayWidth = 18
      FieldName = 'Dt'
      DisplayFormat = 'dd.mm.yyyy   hh:nn:ss'
    end
    object Table1Type: TIntegerField
      FieldName = 'Type'
    end
    object Table1Name: TStringField
      FieldName = 'Name'
      Size = 25
    end
    object Table1Flag: TBooleanField
      FieldName = 'Flag'
    end
    object Table1Dtype: TIntegerField
      FieldName = 'Dtype'
    end
    object Table1Dnum1: TIntegerField
      FieldName = 'Dnum1'
    end
    object Table1Dnum2: TIntegerField
      FieldName = 'Dnum2'
    end
    object Table1Dnum3: TIntegerField
      FieldName = 'Dnum3'
    end
    object Table1Comment: TStringField
      FieldName = 'Comment'
      Size = 25
    end
    object Table1Comment2: TStringField
      FieldName = 'Comment2'
      Size = 25
    end
    object Table1OpFn: TStringField
      FieldName = 'OpFn'
      Size = 15
    end
    object Table1OpN1: TStringField
      FieldName = 'OpN1'
      Size = 15
    end
    object Table1OpN2: TStringField
      FieldName = 'OpN2'
      Size = 15
    end
    object Table1ClFn: TStringField
      FieldName = 'ClFn'
      Size = 15
    end
    object Table1ClN1: TStringField
      FieldName = 'ClN1'
      Size = 15
    end
    object Table1ClN2: TStringField
      FieldName = 'ClN2'
      Size = 15
    end
    object Table1Type2Str: TStringField
      FieldKind = fkCalculated
      FieldName = 'Type2Str'
      Size = 30
      Calculated = True
    end
    object Table1OpFio: TStringField
      FieldKind = fkCalculated
      FieldName = 'OpFio'
      Size = 50
      Calculated = True
    end
    object Table1ClFio: TStringField
      FieldKind = fkCalculated
      FieldName = 'ClFio'
      Size = 50
      Calculated = True
    end
    object Table1OutType: TIntegerField
      FieldName = 'OutType'
    end
  end
  object DataSource1: TDataSource
    DataSet = Table1
    Left = 824
    Top = 8
  end
  object ImageList2: TImageList
    Left = 856
    Top = 40
    Bitmap = {
      494C010109000E00040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000394CFF00394CFF00394CFF0039
      4CFF00394CFF00394CFF00394CFF00394CFF00394CFF00394CFF00394CFF0039
      4CFF00394CFF00394CFF00394CFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FF
      FFFF00FFFFFF00FFFFFF00FFFFFF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000085B2FF0085B2FF0085B2FF0085
      B2FF0085B2FF0085B2FF0085B2FF0085B2FF0085B2FF0085B2FF0085B2FF0085
      B2FF0085B2FF0085B2FF0085B2FF00394CFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000009C0000009C0000009C000000
      9C0000009C0000009C0000009C0000009C0000009C0000009C0000009C000000
      9C0000009C0000009C0000009C0000007B001818180018181800181818001818
      1800181818001818180018181800181818001818180018181800181818001818
      180018181800181818001818180008080800004C26FF004C26FF004C26FF004C
      26FF004C26FF004C26FF004C26FF004C26FF004C26FF004C26FF004C26FF004C
      26FF004C26FF004C26FF004C26FF004C26FF00004CFF00004CFF00004CFF0000
      4CFF00004CFF00004CFF00004CFF00004CFF00004CFF00004CFF00004CFF0000
      4CFF00004CFF00004CFF00004CFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF0000002900000052000000FF000000100000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000290000000000000000000000080000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF0000005A00000000000000000000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000D6000000000000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000007B0000000000000052000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF00FF
      00FF00FF00FF00FF00FF00FF00FF004C26FF000080FF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF00004CFF0000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF0000009C004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A4A004A4A
      4A004A4A4A004A4A4A004A4A4A0018181800008000FF008000FF008000FF0080
      00FF008000FF008000FF008000FF008000FF008000FF008000FF008000FF0080
      00FF008000FF008000FF008000FF004C26FF000080FF000080FF000080FF0000
      80FF000080FF000080FF000080FF000080FF000080FF000080FF000080FF0000
      80FF000080FF000080FF000080FF00004CFF4242420042424200424242004242
      4200424242004242420042424200424242004242420042424200424242004242
      420042424200424242004242420018181800009C1800009C1800009C1800009C
      1800009C1800009C1800009C1800009C1800009C1800009C1800009C1800009C
      1800009C1800009C1800009C1800007B1800009C1800009C1800009C1800009C
      1800009C1800009C1800009C1800009C1800009C1800009C1800009C1800009C
      1800009C1800009C1800009C1800007B1800009CDE00009CDE00009CDE00009C
      DE00009CDE00009CDE00009CDE00009CDE00009CDE00009CDE00009CDE00009C
      DE00009CDE00009CDE00009CDE000073BD00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000FF00000021420000084A0000084A0000104A0000F7000000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00B5B5B500BDBDBD00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000084A0000084A0000084A0000084A0000084A0000084A0000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE000000000029292900CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000CE100000084A0000084A0000FF000000FF000000084A0000084A00008C
      210000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE002929290052525200CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      00000052310000084A0000104A0000FF000000FF0000005A310000084A000010
      4A0000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00292929004A4A4A00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000104A0000084A000042390000FF000000FF0000008C210000084A000008
      4A0000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE000000000000000000CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000084A0000084A00004A390000FF000000FF0000009C180000084A000008
      4A0000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00313131000000000000000000C6C6C600CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000084A0000084A00004A390000FF000000FF0000009C180000084A000008
      4A0000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE005A5A5A000000000000000000CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000084A0000084A000042390000FF000000FF00000094210000084A000008
      4A0000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF00000029420000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000EFF7000039730000FFFF0000D6E70000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00ADADAD008C8C8C00B5B5B500CECECE00CECECE0029292900000000009C9C
      9C00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      0000004A310000084A0000104A0000FF000000FF00000063310000084A000008
      4A0000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000084A0000084A00009C180000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000EFF70000004A0000004A00009CB50000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00848484000000000008080800C6C6C600C6C6C6000808080000000000B5B5
      B500CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000CE100000084A0000084A0000FF000000FF000000084A0000084A00007B
      290000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000AD180000084A0000084A0000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF00008CAD0000004A0000004A0000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00212121000000000000000000000000000000000052525200CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000084A0000084A0000084A0000084A0000084A0000084A0000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000104A0000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000004A0000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00ADADAD007373730073737300C6C6C600CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000FF000000104A0000084A0000084A0000084A0000E7000000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000084A0000084A0000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000F7FF0000004A0000004A0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE004242420000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000009C180000FF000000FF000000FF000000FF
      000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF
      000000FF000000FF000000FF0000009C180000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FF
      FF0000FFFF0000FFFF0000FFFF00009CDE00424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000}
  end
  object SoundTimer: TTimer
    Enabled = False
    OnTimer = SoundTimerTimer
    Left = 552
    Top = 80
  end
  object PopupMenu2: TPopupMenu
    Images = ImageList1
    OnPopup = PopupMenu2Popup
    Left = 416
    Top = 80
    object AddPrichina_pdi: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      ImageIndex = 23
      OnClick = AddPrichina_pdiClick
    end
    object N10: TMenuItem
      Caption = '-'
    end
    object DelPrichina_pdi: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      ImageIndex = 24
      OnClick = DelPrichina_pdiClick
    end
  end
  object PopupMenu3: TPopupMenu
    Images = ImageList1
    OnPopup = PopupMenu3Popup
    Left = 416
    Top = 112
    object AddMera_pdi: TMenuItem
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      ImageIndex = 23
      OnClick = AddMera_pdiClick
    end
    object N14: TMenuItem
      Caption = '-'
    end
    object DelMera_pdi: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      ImageIndex = 24
      OnClick = DelMera_pdiClick
    end
  end
  object TvTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TvTimerTimer
    Left = 584
    Top = 80
  end
  object ApplicationEvents1: TApplicationEvents
    OnMessage = ApplicationEvents1Message
    Left = 496
    Top = 16
  end
  object OprosGobiTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = OprosGobiTimerTimer
    Left = 616
    Top = 80
  end
  object SolidTimer: TTimer
    Enabled = False
    Interval = 250
    OnTimer = SolidTimerTimer
    Left = 520
    Top = 80
  end
  object Adam4068Timer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Adam4068TimerTimer
    Left = 488
    Top = 80
  end
  object Server2: TServerSocket
    Active = False
    Port = 1972
    ServerType = stNonBlocking
    OnClientConnect = Server2ClientConnect
    OnClientDisconnect = Server2ClientDisconnect
    OnClientRead = Server2ClientRead
    OnClientError = Server2ClientError
    Left = 648
    Top = 48
  end
  object GobiCamTimer: TTimer
    Enabled = False
    OnTimer = GobiCamTimerTimer
    Left = 456
    Top = 80
  end
  object GobiDkTimer: TTimer
    Enabled = False
    Interval = 1500
    OnTimer = GobiDkTimerTimer
    Left = 648
    Top = 80
  end
  object iServer: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = iServerClientConnect
    OnClientDisconnect = iServerClientDisconnect
    OnClientRead = iServerClientRead
    OnClientError = iServerClientError
    Left = 680
    Top = 48
  end
  object KeepAliveTimer: TTimer
    Enabled = False
    OnTimer = KeepAliveTimerTimer
    Left = 680
    Top = 80
  end
  object frxReport1: TfrxReport
    Version = '4.14'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbNavigator]
    PreviewOptions.Zoom = 1
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41565.3635839699
    ReportOptions.LastChange = 41565.4188067708
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    Left = 792
    Top = 40
    Datasets = <
      item
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
      end>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000
      Width = 1000
    end
    object Page1: TfrxReportPage
      Orientation = poLandscape
      PaperWidth = 297
      PaperHeight = 210
      PaperSize = 9
      LeftMargin = 30
      RightMargin = 15
      TopMargin = 15
      BottomMargin = 15
      Columns = 1
      ColumnWidth = 252
      ColumnPositions.Strings = (
        '0')
      object PageHeader1: TfrxPageHeader
        Height = 21.73222
        Top = 68.03154
        Width = 952.44156
        object Memo5: TfrxMemoView
          Left = 49.13386559
          Top = 3.73222
          Width = 124.72440945
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#8221#1056#176#1057#8218#1056#176', '#1056#8217#1057#1026#1056#181#1056#1112#1057#1039)
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 755.90557283
          Top = 3.73222
          Width = 196.53543795
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#1119#1057#1026#1056#1105#1057#1039#1056#1029#1057#8218#1057#8249#1056#181' '#1056#1112#1056#181#1057#1026#1057#8249)
          ParentFont = False
        end
        object Memo11: TfrxMemoView
          Left = 558.89765
          Top = 3.73222
          Width = 196.53543307
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#1119#1057#1026#1056#1105#1057#8225#1056#1105#1056#1029#1056#176)
          ParentFont = False
        end
        object Memo9: TfrxMemoView
          Left = 389.29136299
          Top = 3.73222
          Width = 170.07874016
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#1115#1056#177#1057#1033#1056#181#1056#1108#1057#8218)
          ParentFont = False
        end
        object Memo7: TfrxMemoView
          Left = 173.85827504
          Top = 3.73222
          Width = 215.43308795
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#1038#1056#1109#1056#177#1057#8249#1057#8218#1056#1105#1056#181)
          ParentFont = False
        end
        object Memo3: TfrxMemoView
          Top = 3.73222
          Width = 49.13386559
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = [ftLeft, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            #1074#8222#8211)
          ParentFont = False
        end
      end
      object MasterData1: TfrxMasterData
        Height = 18.89765
        Top = 151.1812
        Width = 952.44156
        DataSet = frxDBDataset1
        DataSetName = 'frxDBDataset1'
        RowCount = 0
        object frxDBDataset1Dt: TfrxMemoView
          Left = 49.13386559
          Width = 124.72441677
          Height = 18.89765
          ShowHint = False
          DataField = 'Dt'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8 = (
            '[frxDBDataset1."Dt"]')
          ParentFont = False
        end
        object frxDBDataset1Type2Str: TfrxMemoView
          Left = 173.85827504
          Width = 215.43308795
          Height = 18.89765
          ShowHint = False
          DataField = 'Type2Str'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8 = (
            '[frxDBDataset1."Type2Str"]')
          ParentFont = False
        end
        object frxDBDataset1Name: TfrxMemoView
          Left = 389.29136299
          Width = 170.07885
          Height = 18.89765
          ShowHint = False
          DataField = 'Name'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8 = (
            '[frxDBDataset1."Name"]')
          ParentFont = False
        end
        object frxDBDataset1Comment: TfrxMemoView
          Left = 559.37044
          Width = 196.53556
          Height = 18.89765
          ShowHint = False
          DataField = 'Comment'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8 = (
            '[frxDBDataset1."Comment"]')
          ParentFont = False
        end
        object frxDBDataset1Comment2: TfrxMemoView
          Left = 755.906
          Width = 196.53545016
          Height = 18.89765
          ShowHint = False
          DataField = 'Comment2'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          Memo.UTF8 = (
            '[frxDBDataset1."Comment2"]')
          ParentFont = False
        end
        object frxDBDataset1Cnt: TfrxMemoView
          Width = 49.13386559
          Height = 18.89765
          ShowHint = False
          DataField = 'Cnt'
          DataSet = frxDBDataset1
          DataSetName = 'frxDBDataset1'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
          HAlign = haCenter
          Memo.UTF8 = (
            '[frxDBDataset1."Cnt"]')
          ParentFont = False
        end
      end
      object ReportTitle1: TfrxReportTitle
        Height = 28
        Top = 18.89765
        Width = 952.44156
        object Memo19: TfrxMemoView
          Width = 952.44156
          Height = 22.67718
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#8211#1057#1107#1057#1026#1056#1029#1056#176#1056#187' '#1057#1027#1056#1109#1056#177#1057#8249#1057#8218#1056#1105#1056#8470)
          ParentFont = False
        end
      end
      object PageFooter1: TfrxPageFooter
        Height = 28
        Top = 370.39394
        Width = 952.44156
        object Page: TfrxMemoView
          Left = 873.07143
          Width = 79.37013
          Height = 18.89765
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          HAlign = haCenter
          Memo.UTF8 = (
            '[Page#]')
          ParentFont = False
        end
      end
      object ReportSummary1: TfrxReportSummary
        Height = 116
        Top = 230.55133
        Width = 952.44156
        object Line1: TfrxLineView
          Left = 491.33858268
          Top = 35.46444
          Width = 185.196850393701
          ShowHint = False
          Frame.Typ = [ftTop]
          Frame.Width = 2
        end
        object Memo15: TfrxMemoView
          Left = 491.33858268
          Top = 35.46444
          Width = 188.97637795
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#1111#1056#1109#1056#1169#1056#1111#1056#1105#1057#1027#1057#1034)
          ParentFont = False
        end
        object Line2: TfrxLineView
          Left = 680.88188
          Top = 35.46444
          Width = 264.56692913
          ShowHint = False
          Frame.Typ = [ftTop]
          Frame.Width = 2
        end
        object Memo16: TfrxMemoView
          Left = 680.88188
          Top = 35.46444
          Width = 264.566929133858
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#164'.'#1056#152'.'#1056#1115'.')
          ParentFont = False
        end
        object Line3: TfrxLineView
          Left = 491.33858268
          Top = 90.58256
          Width = 188.97637795
          ShowHint = False
          Frame.Typ = [ftTop]
          Frame.Width = 2
        end
        object Memo17: TfrxMemoView
          Left = 491.33858268
          Top = 90.58256
          Width = 188.97637795
          Height = 18
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          HAlign = haCenter
          Memo.UTF8 = (
            #1056#1169#1056#176#1057#8218#1056#176', '#1056#1030#1057#1026#1056#181#1056#1112#1057#1039' '#1057#1027#1056#1109#1056#183#1056#1169#1056#176#1056#1029#1056#1105#1057#1039' '#1056#1109#1057#8218#1057#8225#1056#181#1057#8218#1056#176)
          ParentFont = False
        end
        object Date1: TfrxMemoView
          Left = 491.33858268
          Top = 68.03154
          Width = 94.48825
          Height = 18.89765
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          HAlign = haCenter
          Memo.UTF8 = (
            '[Date]')
          ParentFont = False
        end
        object Time: TfrxMemoView
          Left = 585.82715
          Top = 68.03154
          Width = 94.48825
          Height = 18.89765
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          HAlign = haCenter
          Memo.UTF8 = (
            '[Time]')
          ParentFont = False
        end
        object Memo2: TfrxMemoView
          Top = 113.44867
          Width = 900
          Height = 20
          ShowHint = False
          StretchMode = smMaxHeight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsItalic]
          ParentFont = False
        end
      end
    end
    object Page2: TfrxReportPage
      PaperWidth = 210
      PaperHeight = 297
      PaperSize = 9
      LeftMargin = 10
      RightMargin = 10
      TopMargin = 10
      BottomMargin = 10
    end
  end
  object frxDBDataset1: TfrxDBDataset
    UserName = 'frxDBDataset1'
    CloseDataSource = False
    DataSet = Table1
    BCDToCurrency = False
    Left = 824
    Top = 40
  end
  object TabloTimer: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TabloTimerTimer
    Left = 712
    Top = 80
  end
  object AsoosdClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = AsoosdClientSocketConnect
    OnError = AsoosdClientSocketError
    Left = 712
    Top = 48
  end
  object ILivedTimer: TTimer
    Enabled = False
    Interval = 60000
    OnTimer = ILivedTimerTimer
    Left = 744
    Top = 80
  end
  object CfgTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = CfgTimerTimer
    Left = 776
    Top = 80
  end
end
