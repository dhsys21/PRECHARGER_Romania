object Form_PLCInterface: TForm_PLCInterface
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'PLC Interface'
  ClientHeight = 951
  ClientWidth = 1264
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 4
    Top = 8
    Width = 1250
    Height = 935
    Caption = 'PreCharger 1 (PLC - PC INTERFACE)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = GroupBox2Click
    object ListView_PC: TListView
      Left = 631
      Top = 47
      Width = 615
      Height = 434
      Columns = <
        item
          Caption = 'PC_Address'
          Width = 150
        end
        item
          Caption = 'PC_Name'
          Width = 200
        end
        item
          Caption = 'PC_Value'
          Width = 240
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 0
      ViewStyle = vsReport
    end
    object ListView_PLC: TListView
      Left = 15
      Top = 47
      Width = 610
      Height = 434
      Columns = <
        item
          Caption = 'PLC_Address'
          Width = 150
        end
        item
          Caption = 'PLC_Name'
          Width = 200
        end
        item
          Caption = 'PLC_Value'
          Width = 240
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 1
      ViewStyle = vsReport
    end
    object ListView_PC2: TListView
      Left = 631
      Top = 489
      Width = 615
      Height = 434
      Columns = <
        item
          Caption = 'PC_Address'
          Width = 150
        end
        item
          Caption = 'PC_Name'
          Width = 200
        end
        item
          Caption = 'PC_Value'
          Width = 240
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 2
      ViewStyle = vsReport
    end
    object ListView_PLC2: TListView
      Left = 15
      Top = 487
      Width = 610
      Height = 434
      Columns = <
        item
          Caption = 'PLC_Address'
          Width = 150
        end
        item
          Caption = 'PLC_Name'
          Width = 200
        end
        item
          Caption = 'PLC_Value'
          Width = 240
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 3
      ViewStyle = vsReport
    end
  end
  object Panel1: TAdvSmoothPanel
    Left = 411
    Top = 136
    Width = 457
    Height = 289
    Cursor = crDefault
    CanMove = True
    Caption.Location = plCenterCenter
    Caption.HTMLFont.Charset = DEFAULT_CHARSET
    Caption.HTMLFont.Color = clWindowText
    Caption.HTMLFont.Height = -11
    Caption.HTMLFont.Name = 'Tahoma'
    Caption.HTMLFont.Style = []
    Caption.HTMLURLColor = clBlack
    Caption.Font.Charset = DEFAULT_CHARSET
    Caption.Font.Color = clWindowText
    Caption.Font.Height = -24
    Caption.Font.Name = 'Tahoma'
    Caption.Font.Style = [fsBold]
    Caption.ColorStart = clWhite
    Caption.ColorEnd = clWhite
    Caption.LineColor = clBlack
    Caption.Line = False
    Caption.TextAlignment = taCenter
    Fill.Color = clWhite
    Fill.ColorTo = clWhite
    Fill.ColorMirror = clWhite
    Fill.ColorMirrorTo = clWhite
    Fill.GradientType = gtVertical
    Fill.GradientMirrorType = gtVertical
    Fill.BorderColor = 14922381
    Fill.Rounding = 5
    Fill.ShadowOffset = 0
    Fill.Glow = gmNone
    Version = '1.5.2.1'
    Visible = False
    TabOrder = 1
    TMSStyle = 0
    object Label1: TLabel
      Left = 179
      Top = 6
      Width = 70
      Height = 19
      Caption = 'PLC TEST'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 255
      Top = 30
      Width = 64
      Height = 16
      Caption = 'STAGE NO.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object AdvSmoothButton9: TAdvSmoothButton
      Left = 323
      Top = 404
      Width = 80
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -17
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Save '
      Color = clWhite
      ParentFont = False
      TabOrder = 0
      Visible = False
      Version = '2.1.1.5'
      TMSStyle = 8
    end
    object Panel30: TPanel
      Left = 13
      Top = 396
      Width = 184
      Height = 24
      Margins.Top = 5
      Margins.Bottom = 5
      BevelKind = bkFlat
      BevelOuter = bvNone
      Caption = 'NG ALARM COUNT'
      Color = 15658734
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      Padding.Top = 5
      ParentBackground = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 1
    end
    object Panel32: TPanel
      Left = 13
      Top = 430
      Width = 184
      Height = 24
      Margins.Top = 5
      Margins.Bottom = 5
      BevelKind = bkFlat
      BevelOuter = bvNone
      Caption = 'PreCharging NG - Min. (mA)'
      Color = 15658734
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      Padding.Top = 5
      ParentBackground = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 2
      Visible = False
    end
    object Edit6: TEdit
      Left = 199
      Top = 430
      Width = 108
      Height = 24
      Margins.Bottom = 0
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Text = '50'
      Visible = False
    end
    object Edit7: TEdit
      Left = 199
      Top = 396
      Width = 108
      Height = 24
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ImeName = 'Microsoft Office IME 2007'
      NumbersOnly = True
      ParentFont = False
      TabOrder = 4
      Text = '2'
    end
    object GroupBox4: TGroupBox
      Left = 5
      Top = 31
      Width = 244
      Height = 135
      Caption = 'Write Value'
      TabOrder = 5
      object Label2: TLabel
        Left = 16
        Top = 22
        Width = 55
        Height = 16
        Caption = 'ADDRESS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 16
        Top = 75
        Width = 37
        Height = 16
        Caption = 'VALUE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object cbAddress: TComboBox
        Left = 16
        Top = 44
        Width = 129
        Height = 21
        TabOrder = 0
        Text = '41000'
        Items.Strings = (
          '41000'
          '41001'
          '41002'
          '41003'
          '41004'
          '41005'
          '41006'
          '41007'
          '41008'
          '41009'
          '41010'
          '41020'
          '41021')
      end
      object editValue: TEdit
        Left = 16
        Top = 98
        Width = 129
        Height = 21
        TabOrder = 1
        Text = '1'
      end
      object btnWriteValue: TButton
        Left = 159
        Top = 40
        Width = 66
        Height = 36
        Caption = 'Write Value'
        TabOrder = 2
        OnClick = btnWriteValueClick
      end
      object Button1: TButton
        Left = 159
        Top = 82
        Width = 66
        Height = 36
        Caption = 'Write Curr'
        TabOrder = 3
        OnClick = Button1Click
      end
    end
    object GroupBox1: TGroupBox
      Left = 255
      Top = 106
      Width = 194
      Height = 178
      Caption = 'Volt/Curr Value'
      TabOrder = 6
      object Label5: TLabel
        Left = 104
        Top = 25
        Width = 79
        Height = 16
        Caption = 'Voltage Value'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 101
        Top = 82
        Width = 79
        Height = 16
        Caption = 'Current Value'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object editVoltage: TEdit
        Left = 6
        Top = 47
        Width = 178
        Height = 21
        TabOrder = 0
        Text = '3100'
      end
      object editCurrent: TEdit
        Left = 6
        Top = 104
        Width = 178
        Height = 21
        TabOrder = 1
        Text = '1000'
      end
      object btnWriteIrOcvValue: TButton
        Left = 96
        Top = 134
        Width = 88
        Height = 32
        Caption = 'Write Value'
        TabOrder = 2
        OnClick = btnWriteIrOcvValueClick
      end
    end
    object GroupBox3: TGroupBox
      Left = 5
      Top = 172
      Width = 244
      Height = 112
      Caption = 'IROCV NG Value'
      TabOrder = 7
      object editIrOcvNg: TEdit
        Left = 16
        Top = 30
        Width = 209
        Height = 21
        TabOrder = 0
        Text = 
          '1,22,43,64,85,106,127,148,169,190,211,232,253,274,295,316,337,35' +
          '8,379,400'
      end
      object btnWriteNgValue: TButton
        Left = 144
        Top = 57
        Width = 81
        Height = 32
        Caption = 'Write NG Value'
        TabOrder = 1
        OnClick = btnWriteNgValueClick
      end
    end
    object cbStageNo: TComboBox
      Left = 255
      Top = 52
      Width = 129
      Height = 21
      TabOrder = 8
      Text = '1'
      Items.Strings = (
        '1'
        '2')
    end
  end
  object Timer_Update: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer_UpdateTimer
    Left = 390
    Top = 8
  end
end
