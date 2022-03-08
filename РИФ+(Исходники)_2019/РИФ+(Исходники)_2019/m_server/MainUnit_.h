//---------------------------------------------------------------------------
#ifndef MainUnit_H
#define MainUnit_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ScktComp.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
#include "TOhrObjUnit.h"
#include "TRifSysUnit.h"
#include "TRifSys2Unit.h"
#include "TGobiSysUnit.h"
#include "TRastrSysUnit.h"
#include "TNetClientSysUnit.h"
#include "TNetClientUnit.h"
#include "CSerialUnit.h"
#include "TSolidSysUnit.h"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <Buttons.hpp>
#include <AppEvnts.hpp>
#include <ActnList.hpp>
#include <ActnMan.hpp>
#include "TAdam4068SysUnit.h"
#include "CGAUGES.h"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "AdvGrid.hpp"
#include "BaseGrid.hpp"
#include "OperatorsDlgUnit.h"
#include "OperatorListUnit.h"
#include "TTabloSysUnit.h"
#include "CSPIN.h"
#include "TRifOprosThreadUnit.h"
//---------------------------------------------------------------------------
#define GroupType 0
#define RifType 1
#define SdConcType 2
#define RazrivBoType 21
#define SdType 3
#define SsoiMSdType 33
#define IuType 4
#define SsoiType 41
#define Stn485Type 42
#define SsoiMIuType 43
#define RastrType 51
#define RastrOldType 5
#define SolidType 6
#define Adam4068Type 7
#define TabloType 71
#define TorosType 8
#define NastType 9
#define RadarType 91
#define TochkaType 10
#define RifRlmSType 111
#define SdIpBlType 11
#define IuIpBlType 12
#define StrazhIpType 24
#define OnvifTvType 25
#define TochkaMBoIdx 26
#define TochkaMUchIdx 27
#define TochkaMDdIdx 28
#define SotaMBoIdx 29
#define SotaMUchIdx 30
#define SotaMDdIdx 31
#define DevLineIdx 32
#define NetDevIdx 200
//---------------------------------------------------------------------------
#define MaxMySQLRecCnt 5
//---------------------------------------------------------------------------
#define TochkaMux 2.2
//---------------------------------------------------------------------------
#define IpBlIdx 100
//---------------------------------------------------------------------------
#define RifxComplexType 0           
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TMainMenu *MainMenu1;
   TImageList *ImageList1;
   TMenuItem *ZhurnalItems;
   TMenuItem *ZhurnalToDbItem;
   TMenuItem *N1;
   TMenuItem *ExitItem;
   TStatusBar *StatusBar1;
   TMenuItem *AlarmItems;
   TMenuItem *SoundResetItem;
   TMenuItem *N2;
   TMenuItem *AlarmResetItem;
   TMenuItem *ControlItems;
   TMenuItem *ControlItem;
   TMenuItem *N3;
   TMenuItem *RifsDkItem;
   TMenuItem *GobiDkItem;
   TMenuItem *DbItem;
   TMenuItem *N4;
   TToolBar *ToolBar1;
   TToolButton *ToolButton1;
   TToolButton *ToolButton2;
   TPanel *Panel1;
   TPanel *Panel2;
   TSplitter *Splitter1;
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox3;
   TTreeView *ObjTree;
   TPopupMenu *PopupMenu1;
   TStaticText *StaticText1;
   TMenuItem *OnOff_pdi;
   TMenuItem *N8;
   TMenuItem *Dk_pdi;
   TMenuItem *N9;
   TMenuItem *Pult_pdi;
   TMenuItem *N11;
   TMenuItem *Control_pdi;
   TDBGrid *DBGrid1;
   TTable *Table1;
   TDataSource *DataSource1;
   TImageList *ImageList2;
   TGroupBox *GroupBox2;
   TComboBox *ComboBox1;
   TComboBox *ComboBox2;
   TLabel *Label11;
   TLabel *Label12;
   TBitBtn *BitBtn2;
   TBitBtn *BitBtn1;
   TTimer *SoundTimer;
   TGroupBox *GroupBox6;
   TComboBox *ComboBox3;
   TLabel *Label10;
   TLabel *Label13;
   TComboBox *ComboBox4;
   TPopupMenu *PopupMenu2;
   TMenuItem *AddPrichina_pdi;
   TMenuItem *DelPrichina_pdi;
   TMenuItem *N10;
   TPopupMenu *PopupMenu3;
   TMenuItem *AddMera_pdi;
   TMenuItem *N14;
   TMenuItem *DelMera_pdi;
   TGroupBox *GroupBox7;
   TTreeView *RastrTree;
   TTimer *TvTimer;
   TStaticText *StaticText15;
   TGroupBox *GroupBox8;
   TSpeedButton *SpeedButton1;
   TSpeedButton *SpeedButton2;
   TSpeedButton *SpeedButton3;
   TSpeedButton *SpeedButton4;
   TSpeedButton *SpeedButton5;
   TSpeedButton *SpeedButton6;
   TSpeedButton *SpeedButton7;
   TSpeedButton *SpeedButton8;
   TApplicationEvents *ApplicationEvents1;
   TSpeedButton *SpeedButton9;
   TSpeedButton *SpeedButton11;
   TSpeedButton *SpeedButton12;
   TTimer *OprosGobiTimer;
   TMenuItem *ZhurnalPrintItem;
   TMenuItem *N12;
   TMenuItem *ZhurnalPrintViewItem;
   TTimer *SolidTimer;
   TMenuItem *OnOffAll_pdi;
   TMenuItem *N15;
   TGroupBox *GroupBox4;
   TLabel *Label1;
   TImage *Image1;
   TLabel *Label2;
   TImage *Image2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TImage *Image3;
   TImage *Image4;
   TImage *Image5;
   TImage *Image6;
   TImage *Image7;
   TImage *Image8;
   TStaticText *StaticText2;
   TStaticText *StaticText3;
   TStaticText *StaticText4;
   TStaticText *StaticText5;
   TStaticText *StaticText6;
   TStaticText *StaticText7;
   TStaticText *StaticText8;
   TStaticText *StaticText9;
   TStaticText *StaticText10;
   TMenuItem *N16;
   TMenuItem *ConcDkItem;
   TImage *Image13;
   TLabel *Label51;
   TImage *Image51;
   TStaticText *StaticText51;
   TLabel *Label52;
   TImage *Image52;
   TStaticText *StaticText52;
   TLabel *Label53;
   TImage *Image53;
   TStaticText *StaticText53;
   TLabel *Label54;
   TImage *Image54;
   TStaticText *StaticText54;
   TLabel *Label55;
   TImage *Image55;
   TStaticText *StaticText55;
   TLabel *Label56;
   TImage *Image56;
   TStaticText *StaticText56;
   TLabel *Label57;
   TImage *Image57;
   TStaticText *StaticText57;
   TLabel *Label58;
   TImage *Image58;
   TStaticText *StaticText58;
   TLabel *Label59;
   TImage *Image59;
   TStaticText *StaticText59;
   TLabel *Label60;
   TImage *Image60;
   TStaticText *StaticText60;
   TLabel *Label61;
   TImage *Image61;
   TStaticText *StaticText61;
   TLabel *Label62;
   TImage *Image62;
   TStaticText *StaticText62;
   TTimer *Adam4068Timer;
   TLabel *Label14;
   TComboBox *ComboBox5;
   TLabel *Label69;
   TImage *Image69;
   TStaticText *StaticText69;
   TLabel *Label70;
   TImage *Image70;
   TStaticText *StaticText70;
   TLabel *Label71;
   TImage *Image71;
   TStaticText *StaticText71;
   TLabel *Label72;
   TImage *Image72;
   TStaticText *StaticText72;
   TMenuItem *TorosDkItem;
   TMenuItem *NastDkItem;
   TLabel *Label15;
   TComboBox *ComboBox6;
   TLabel *Label16;
   TComboBox *ComboBox7;
   TMenuItem *N24;
   TMenuItem *PultOff_pdi;
   TMenuItem *DiagItem;
   TMenuItem *N26;
   TMenuItem *SetupItem;
   TSpeedButton *SpeedButton10;
   TMenuItem *DkItem;
   TMenuItem *DkRifItem;
   TMenuItem *DkRifAllItem;
   TMenuItem *N7;
   TGroupBox *GroupBox5;
   TCGauge *CGauge1;
   TMenuItem *SpoolerClearItem;
   TMenuItem *N13;
   TMenuItem *Off_pdi;
   TMenuItem *N17;
   TMenuItem *N18;
   TMenuItem *N19;
   TMenuItem *N20;
   TMenuItem *HelpItems;
   TMenuItem *AboutItem;
   TServerSocket *Server2;
   TMenuItem *GobiDkKan1Item;
   TMenuItem *GobiDkKan2Item;
   TMenuItem *GobiDkKan3Item;
   TMenuItem *GobiDkKan4Item;
   TMenuItem *Metka_pdi;
   TGroupBox *GroupBox9;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TComboBox *ComboBox8;
   TLabel *Label20;
   TComboBox *ComboBox9;
   TLabel *Label21;
   TLabel *Label22;
   TComboBox *ComboBox11;
   TLabel *Label23;
   TLabel *Label24;
   TLabel *Label25;
   TComboBox *ComboBox10;
   TComboBox *ComboBox14;
   TLabel *Label26;
   TComboBox *ComboBox15;
   TLabel *Label27;
   TButton *Button1;
   TLabel *Label28;
   TComboBox *ComboBox12;
   TLabel *Label29;
   TComboBox *ComboBox13;
   TLabel *Label30;
   TLabel *Label31;
   TComboBox *ComboBox16;
   TLabel *Label32;
   TComboBox *ComboBox17;
   TLabel *Label33;
   TTimer *GobiCamTimer;
   TMenuItem *GobiDkKanalsItem;
   TTimer *GobiDkTimer;
   TMenuItem *RadarDkItem;
   TLabel *Label34;
   TStaticText *StaticText11;
   TLabel *Label35;
   TImage *Image75;
   TStaticText *StaticText75;
   TLabel *Label36;
   TImage *Image76;
   TStaticText *StaticText76;
   TLabel *Label77;
   TImage *Image77;
   TStaticText *StaticText77;
   TLabel *Label95;
   TStaticText *StaticText95;
   TLabel *Label85;
   TLabel *Label86;
   TLabel *Label87;
   TLabel *Label88;
   TLabel *Label89;
   TLabel *Label90;
   TLabel *Label91;
   TLabel *Label92;
   TLabel *Label78;
   TLabel *Label79;
   TLabel *Label80;
   TLabel *Label81;
   TLabel *Label82;
   TLabel *Label83;
   TLabel *Label84;
   TLabel *Label96;
   TLabel *Label97;
   TLabel *Label98;
   TLabel *Label99;
   TLabel *Label100;
   TLabel *Label101;
   TLabel *Label102;
   TImage *Image78;
   TImage *Image79;
   TImage *Image80;
   TImage *Image81;
   TImage *Image82;
   TImage *Image83;
   TImage *Image84;
   TStaticText *StaticText78;
   TStaticText *StaticText79;
   TStaticText *StaticText80;
   TStaticText *StaticText81;
   TStaticText *StaticText82;
   TStaticText *StaticText83;
   TStaticText *StaticText84;
   TStaticText *StaticText96;
   TStaticText *StaticText97;
   TStaticText *StaticText98;
   TStaticText *StaticText99;
   TStaticText *StaticText100;
   TStaticText *StaticText101;
   TStaticText *StaticText102;
   TScrollBox *ScrollBox1;
   TLabel *Label292;
   TLabel *Label293;
   TImage *Image293;
   TStaticText *StaticText293;
   TImage *Image294;
   TStaticText *StaticText294;
   TStaticText *StaticText295;
   TLabel *Label294;
   TLabel *Label295;
   TLabel *Label296;
   TLabel *Label297;
   TLabel *Label298;
   TLabel *Label299;
   TImage *Image297;
   TImage *Image298;
   TStaticText *StaticText297;
   TStaticText *StaticText298;
   TStaticText *StaticText299;
   TLabel *Label300;
   TLabel *Label301;
   TLabel *Label302;
   TLabel *Label303;
   TImage *Image301;
   TImage *Image302;
   TStaticText *StaticText301;
   TStaticText *StaticText302;
   TStaticText *StaticText303;
   TLabel *Label304;
   TLabel *Label305;
   TLabel *Label306;
   TLabel *Label307;
   TImage *Image305;
   TImage *Image306;
   TStaticText *StaticText305;
   TStaticText *StaticText306;
   TStaticText *StaticText307;
   TCheckBox *CheckBox1;
   TLabel *Label37;
   TLabel *Label38;
   TCheckBox *CheckBox2;
   TLabel *Label39;
   TCheckBox *CheckBox3;
   TComboBox *ComboBox18;
   TLabel *Label40;
   TLabel *Label41;
   TComboBox *ComboBox19;
   TLabel *Label42;
   TComboBox *ComboBox20;
   TBevel *Bevel1;
   TLabel *Label43;
   TLabel *Label44;
   TStaticText *StaticText12;
   TLabel *Label45;
   TStaticText *StaticText13;
   TLabel *Label46;
   TStaticText *StaticText14;
   TBevel *Bevel2;
   TLabel *Label47;
   TLabel *Label48;
   TLabel *Label49;
   TLabel *Label50;
   TLabel *Label63;
   TLabel *Label64;
   TStaticText *StaticText17;
   TStaticText *StaticText18;
   TStaticText *StaticText19;
   TBevel *Bevel3;
   TLabel *Label65;
   TLabel *Label66;
   TLabel *Label67;
   TLabel *Label103;
   TStaticText *StaticText103;
   TLabel *Label68;
   TLabel *Label73;
   TLabel *Label74;
   TStaticText *StaticText20;
   TStaticText *StaticText21;
   TStaticText *StaticText22;
   TBevel *Bevel4;
   TStaticText *StaticText23;
   TStaticText *StaticText24;
   TStaticText *StaticText25;
   TStaticText *StaticText26;
   TStaticText *StaticText27;
   TStaticText *StaticText28;
   TServerSocket *iServer;
   TTimer *KeepAliveTimer;
   TfrxReport *frxReport1;
   TfrxDBDataset *frxDBDataset1;
   TGroupBox *GroupBox10;
   TAdvStringGrid *AdvStringGrid1;
   TStaticText *StaticText29;
   TAutoIncField *Table1Cnt;
   TDateTimeField *Table1Dt;
   TIntegerField *Table1Type;
   TStringField *Table1Name;
   TBooleanField *Table1Flag;
   TIntegerField *Table1Dtype;
   TIntegerField *Table1Dnum1;
   TIntegerField *Table1Dnum2;
   TIntegerField *Table1Dnum3;
   TStringField *Table1Comment;
   TStringField *Table1Comment2;
   TStringField *Table1OpFn;
   TStringField *Table1OpN1;
   TStringField *Table1OpN2;
   TStringField *Table1ClFn;
   TStringField *Table1ClN1;
   TStringField *Table1ClN2;
   TStringField *Table1Type2Str;
   TStringField *Table1OpFio;
   TStringField *Table1ClFio;
   TMenuItem *ConnectBlock_pdi;
   TMenuItem *SoundSetItem;
   TToolButton *ToolButton3;
   TMenuItem *OnOff2_pdi;
   TMenuItem *TabloResetItem;
   TMenuItem *N5;
   TStaticText *StaticText16;
   TStaticText *StaticText30;
   TStaticText *StaticText31;
   TStaticText *StaticText32;
   TStaticText *StaticText33;
   TStaticText *StaticText34;
   TStaticText *StaticText35;
   TStaticText *StaticText36;
   TStaticText *StaticText37;
   TToolButton *ToolButton4;
   TTimer *TabloTimer;
   TIntegerField *Table1OutType;
   TLabel *Label75;
   TLabel *Label76;
   TStaticText *StaticText38;
   TStaticText *StaticText39;
   TClientSocket *AsoosdClientSocket;
   TCSpinEdit *CSpinEdit1;
   TCSpinEdit *CSpinEdit2;
   TCSpinEdit *CSpinEdit3;
   TTimer *ILivedTimer;
   TCSpinEdit *CSpinEdit4;
   TCSpinEdit *CSpinEdit5;
   TComboBox *ComboBox21;
   TLabel *Label93;
   TLabel *Label94;
   TComboBox *ComboBox22;
   TLabel *Label104;
   TLabel *Label105;
   TComboBox *ComboBox23;
   TComboBox *ComboBox24;
   TCSpinEdit *CSpinEdit6;
   TCSpinEdit *CSpinEdit7;
   TLabel *Label106;
   TLabel *Label107;
   TLabel *Label108;
   TLabel *Label109;
   TComboBox *ComboBox25;
   TComboBox *ComboBox26;
   TLabel *Label110;
   TLabel *Label111;
   TCSpinEdit *CSpinEdit8;
   TCSpinEdit *CSpinEdit9;
   TLabel *Label112;
   TLabel *Label113;
   TComboBox *ComboBox27;
   TComboBox *ComboBox28;
   TLabel *Label114;
   TLabel *Label115;
   TComboBox *ComboBox29;
   TComboBox *ComboBox30;
   TLabel *Label116;
   TLabel *Label117;
   TCSpinEdit *CSpinEdit10;
   TCSpinEdit *CSpinEdit11;
   TMenuItem *N6;
   TScrollBox *ScrollBox2;
   TComboBox *ComboBox31;
   TLabel *Label118;
   TLabel *Label119;
   TComboBox *ComboBox32;
   TTimer *CfgTimer;
   TMenuItem *N21;
   TMenuItem *ChangeStatus_pdi;
   TMenuItem *Norm_pdi;
   TMenuItem *As_pdi;
   TMenuItem *N_pdi;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall ObjTreeClick(TObject *Sender);
   void __fastcall ObjTreeKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall PopupMenu1Popup(TObject *Sender);
   void __fastcall OnOff_pdiClick(TObject *Sender);
   void __fastcall Pult_pdiClick(TObject *Sender);
   void __fastcall Dk_pdiClick(TObject *Sender);
   void __fastcall Setup_pdiClick(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall ControlItemClick(TObject *Sender);
   void __fastcall RifsDkItemClick(TObject *Sender);
   void __fastcall SoundResetItemClick(TObject *Sender);
   void __fastcall SoundTimerTimer(TObject *Sender);
   void __fastcall Control_pdiClick(TObject *Sender);
   void __fastcall DBGrid1DrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
   void __fastcall AlarmResetItemClick(TObject *Sender);
   void __fastcall ZhurnalToDbItemClick(TObject *Sender);
   void __fastcall ExitItemClick(TObject *Sender);
   void __fastcall PopupMenu2Popup(TObject *Sender);
   void __fastcall PopupMenu3Popup(TObject *Sender);
   void __fastcall AddPrichina_pdiClick(TObject *Sender);
   void __fastcall DelPrichina_pdiClick(TObject *Sender);
   void __fastcall AddMera_pdiClick(TObject *Sender);
   void __fastcall DelMera_pdiClick(TObject *Sender);
   void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
   void __fastcall TvTimerTimer(TObject *Sender);
   void __fastcall RastrTreeClick(TObject *Sender);
   void __fastcall RastrTreeKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall SpeedButton1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton3MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton3MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton4MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton4MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton5MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton5MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton6MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton6MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton7MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton7MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton8MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton8MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
   void __fastcall SpeedButton9Click(TObject *Sender);
   void __fastcall SpeedButton10Click(TObject *Sender);
   void __fastcall SpeedButton11Click(TObject *Sender);
   void __fastcall SpeedButton12Click(TObject *Sender);
   void __fastcall OprosGobiTimerTimer(TObject *Sender);
   void __fastcall ZhurnalPrintItemClick(TObject *Sender);
   void __fastcall ZhurnalPrintViewItemClick(TObject *Sender);
   void __fastcall DbItemClick(TObject *Sender);
   void __fastcall OnOffAll_pdiClick(TObject *Sender);
   void __fastcall SolidTimerTimer(TObject *Sender);
   void __fastcall ConcDkItemClick(TObject *Sender);
   void __fastcall Adam4068TimerTimer(TObject *Sender);
   void __fastcall TorosDkItemClick(TObject *Sender);
   void __fastcall NastDkItemClick(TObject *Sender);
   void __fastcall PultOff_pdiClick(TObject *Sender);
   void __fastcall DiagItemClick(TObject *Sender);
   void __fastcall SetupItemClick(TObject *Sender);
   void __fastcall ToolButton1Click(TObject *Sender);
   void __fastcall ToolButton2Click(TObject *Sender);
   void __fastcall DkRifAllItemClick(TObject *Sender);
   void __fastcall SpoolerClearItemClick(TObject *Sender);
   void __fastcall Off_pdiClick(TObject *Sender);
   void __fastcall DBGrid1KeyPress(TObject *Sender, char &Key);
   void __fastcall N18Click(TObject *Sender);
   void __fastcall N19Click(TObject *Sender);
   void __fastcall AboutItemClick(TObject *Sender);
   void __fastcall Server2ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
   void __fastcall GobiDkKan1ItemClick(TObject *Sender);
   void __fastcall GobiDkKan2ItemClick(TObject *Sender);
   void __fastcall GobiDkKan3ItemClick(TObject *Sender);
   void __fastcall GobiDkKan4ItemClick(TObject *Sender);
   void __fastcall Metka_pdiClick(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall GobiCamTimerTimer(TObject *Sender);
   void __fastcall GobiDkKanalsItemClick(TObject *Sender);
   void __fastcall GobiDkTimerTimer(TObject *Sender);
   void __fastcall RadarDkItemClick(TObject *Sender);
   void __fastcall Server2ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall ComboBox1Change(TObject *Sender);
   void __fastcall iServerClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall iServerClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall iServerClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
   void __fastcall KeepAliveTimerTimer(TObject *Sender);
   void __fastcall iServerClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall Server2ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall Server2ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall AdvStringGrid1GetAlignment(TObject *Sender, int ARow,
          int ACol, TAlignment &HAlign, TVAlignment &VAlign);
   void __fastcall AdvStringGrid1GetCellColor(TObject *Sender, int ARow,
          int ACol, TGridDrawState AState, TBrush *ABrush, TFont *AFont);
   void __fastcall FormResize(TObject *Sender);
   void __fastcall Table1CalcFields(TDataSet *DataSet);
   void __fastcall ConnectBlock_pdiClick(TObject *Sender);
   void __fastcall SoundSetItemClick(TObject *Sender);
   void __fastcall OnOff2_pdiClick(TObject *Sender);
   void __fastcall TabloResetItemClick(TObject *Sender);
   void __fastcall TabloTimerTimer(TObject *Sender);
   void __fastcall ToolBar1Resize(TObject *Sender);
   void __fastcall AsoosdClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall AsoosdClientSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
   void __fastcall ILivedTimerTimer(TObject *Sender);
   void __fastcall N6Click(TObject *Sender);
   void __fastcall CfgTimerTimer(TObject *Sender);
   void __fastcall DBGrid1DblClick(TObject *Sender);
   void __fastcall N21Click(TObject *Sender);
   void __fastcall As_pdiClick(TObject *Sender);
   void __fastcall Norm_pdiClick(TObject *Sender);
   void __fastcall N_pdiClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
   AnsiString AppDataPath;
   int PlanType;
   AnsiString BackupPath;
   unsigned int MaxBdStringCnt;
   void BackupAll();
   AnsiString VersionInfoStr;
   int ComplexVersion;
   AnsiString PlanPath;
   AnsiString Icon1Path;
   AnsiString Icon2Path;
   AnsiString Icon3Path;
   AnsiString Icon4Path;
   AnsiString Icon5Path;
   AnsiString Icon6Path;
   AnsiString Icon7Path;
   AnsiString Icon8Path;
   int RifPortNum[RifKanCnt], RifPortSpeed[RifKanCnt], RifTimerInterval[RifKanCnt], TochkaDirectionInterval, TochkaPauseInterval;
   int SsoiM_PortNum[KanCnt], GobiPortSpeed, SsoiVersion, SsoiM_PortSpeed;
   int Ssoi2MaxCnt[KanCnt], Ssoi2Cnt[KanCnt], Ssoi2Buf[KanCnt][10000], Ssoi2BufCnt[KanCnt], SsoiM_MaxErrCnt[KanCnt];
   int RastrPortNum, RastrPortSpeed;
   int SolidPortNum, SolidPortSpeed, SolidAutoTime;
   int Adam4068PortNum, Adam4068PortSpeed, Adam4068Interval;
   int TabloPortNum, TabloPortSpeed;
   bool TabloBlinking;
   int TabloBlinkingNum;
   bool Server2Use;
   AnsiString Server2Name;
   int Server2Port;
   TiNetSys *r485NetSys;
   int r485KeepAlive;
   bool iServerUse;
   AnsiString iServerHost;
   int iServerPort;
   int iKeepAlive;
   TiNetSys *iNetSys;
   TStringList *TreeAndStates;
   TStringList *EventsAndStates;
   bool LoadGlobalConfig( AnsiString fp );
   bool SaveGlobalConfig( AnsiString fp );
   bool LoadLangConfig( AnsiString fp );
   bool SaveLangConfig( AnsiString fp );
   void ShowGlobalConfig();
   bool LoadLocalConfig( AnsiString fp );
   bool SaveLocalConfig( AnsiString fp );
   TRifSys *RifSys;
   TRif2Sys *Rif2Sys;
   TGobiSys *GobiSys;
   TGobiSys2 *GobiSys2;
   TRastrSys *RastrSys;
   TSolidSys *SolidSys;
   TAdam4068Sys *A4068Sys;
   TTabloSys *TabloSys;
   HANDLE hMapOpros;
   LPVOID lpMapOpros;
   HANDLE hMapCfg;
   LPVOID lpMapCfg;
   HANDLE hMapPlan;
   LPVOID lpMapPlan;
   int ActiveOprosChannels;
   bool SsoiAutoDkUse;
   CSerial SsoiSerial;
   int SsoiScnt;
   CSerial SsoiMSerial[KanCnt];
   void _fastcall SsoiMOpros(TObject* Sender);
   TTimer **SsoiMTimer;
   int SsoiMScnt[KanCnt];
   int SsoiMIdx[KanCnt];
   CSerial RifSerial[RifKanCnt];
   int RifScnt[RifKanCnt];
   int RifIdx[RifKanCnt];
   int RifMaxErrCnt[RifKanCnt];
   void _fastcall RifOpros(TObject* Sender);
   TTimer **RifTimer;
   int RifBazaltCnt[RifKanCnt];
   TRifOprosThread **RifOprosThread;
   CSerial Serial3, Serial4, Serial5, Serial6;
   int S3cnt, S4cnt, S7cnt;
   bool AlarmFlag;
   void ShowNewRkStatus( int flag, int adr, int pn, bool vs, bool tin[MaxIpBlSdCnt], int packet[1000] );
   void ShowNewGobiStatus();
   void ShowNewA4068Status();
   void ShowNewSsoi2Status( int kan, int adr, bool tin[SdCnt], bool vin );
   bool SetTbl1();
   bool CreateTbl1();
   void SetSob( int stype, int otype, int onum1, int onum2, int onum3, AnsiString name, AnsiString ofn, AnsiString on1, AnsiString on2, AnsiString cfn, AnsiString cn1, AnsiString cn2, bool Msg, int outtype );
   void SetSob1( int stype, int otype, int onum1, int onum2, int onum3, AnsiString name, AnsiString ofn, AnsiString on1, AnsiString on2, AnsiString cfn, AnsiString cn1, AnsiString cn2, bool Msg, int outtype, TDateTime dt );
   AnsiString SetSob2( int stype, int otype, int onum1, int onum2, int onum3, AnsiString name, AnsiString ofn, AnsiString on1, AnsiString on2, AnsiString cfn, AnsiString cn1, AnsiString cn2, bool Msg, int outtype );
   AnsiString SetSob22( int stype, int otype, int onum1, int onum2, int onum3, AnsiString udpadress, int udpport,  AnsiString name, AnsiString ofn, AnsiString on1, AnsiString on2, AnsiString cfn, AnsiString cn1, AnsiString cn2, bool Msg, int outtype );
   void SetSob3( int stype, int otype, int onum1, int onum2, int onum3, AnsiString name, AnsiString ofn, AnsiString on1, AnsiString on2, AnsiString cfn, AnsiString cn1, AnsiString cn2, bool Msg, int outtype);
   void SetSob4( int stype, int otype, int onum1, int onum2, int onum3, AnsiString name, AnsiString ofn, AnsiString on1, AnsiString on2, AnsiString cfn, AnsiString cn1, AnsiString cn2, bool Msg, int outtype );
   TDiagRif *DiagRif;
   void ShowDiagRifInfo( int type, int status, int sb, double u, double u2, int d1, int d2 );
   void ShowDiagRifInfoNew( int type, int status, int sb, double u, double u2, int d1, int d2 );
   void ShowDiagRifInfo2( int type, int status, int sb, double u, double u2, double u3, int d1, int d2, int sb2 );
   TDiagKonc *DiagKonc;
   void ShowDiagKoncInfo( int status, int d1, int d2, int d3 );
   void ShowDiagKoncInfo2( int status, int d1, int d2, int d3 );
   void ShowDiagTochkaInfoNew( int packet[1000], int tF[4][3], int ch );
   void ShowDiagSsoi2Info( int packet[30] );
   void ShowDiagSsoi2InfoNew(int status, bool t, bool tv, bool vin, bool dk, bool dk_in, bool tin[8], bool ts[8], bool iu[3], bool vk[3]);
   void ShowDiagIpBlInfo( int packet[1000] );
   void ResetTochkaMDiagInfo( int type, int num2 );
   void ShowDiagTochkaMInfo( int kn, int adr, int packet[1000] );
   bool ShowDiagTochkaMInfo2( int type, int num2, int num3, int packet[1000], int adress, int ddnum );
   int DiagInfoType;
   void Diagnostics_show( int type, int ch, int adr, int sd );
   Graphics::TBitmap *I1Img;
   Graphics::TBitmap *I2Img;
   Graphics::TBitmap *I3Img;
   Graphics::TBitmap *I4Img;
   Graphics::TBitmap *I5Img;
   Graphics::TBitmap *I6Img;
   Graphics::TBitmap *I7Img;
   Graphics::TBitmap *I8Img;
   Graphics::TBitmap *I9Img;
   Graphics::TBitmap *WImg;
   Graphics::TBitmap *AImg;
   Graphics::TBitmap *NImg;
   Graphics::TBitmap *PImg;
   Graphics::TBitmap *HImg;
   Graphics::TBitmap *OImg;
   int Porogi, Rezhim, Takt, Porogi1, Porogi2, Porogi3;
   TTime DkDtOn;
   void ShowSetupInfo( int type );
   int SoundFlag;
   TStringList *CommentList, *CommentList2;
   bool Audit();
   TDateTime CurrentDtRif[RifKanCnt], CurrentDt2;
   int CurMon;
   int TvAutoNum[MonCnt], TvAutoCnt[MonCnt];
   int Monitor, Camera;
   bool TvHand;
   int Adr4068;
   void ResetDiagInfo( int type );
   void ResetDiagInfo2(int type, int ch );
   int MainFormLeft;
   int MainFormTop;
   int MainFormWidth;
   int MainFormHeight;
   int SoundType;
   bool SoundStop;
   AnsiString SoundFilePath, SoundFilePath2, SoundFilePath3;
   AnsiString  pfrm_Label1_Caption, pfrm_Caption,
               RestoreDlg_Caption, RestoreDlg_Label1_Caption, RestoreDlg_Button1_Caption,
               RestoreDlg_OKBtn_Caption, RestoreDlg_CancelBtn_Caption,
               MsgStr1, MsgStr2, ErrorMsg, MsgStr3, MsgStr4, MsgStr5, MsgStr6, MsgStr7,
               MsgStr8, MsgStr9, MsgStr10, MsgStr11, WarningMsg, MsgStr12, MsgStr38,
               Table1Str1, Table1Str2, Table1Str3, Table1Str4, Table1Str5, Table1Str6,
               Table1Str7, Table1Str8, Table1Str9, Table1Str10, Table1Str11, Table1Str12,
               Table1Str13, Table1Str14, Table1Str15, Table1Str16, Table1Str17, Table1Str18,
               Table1Str19, Table1Str20, Table1Str21, Table1Str22, Table1Str23, Table1Str24,
               Table1Str25, Table1Str26, Table1Str27, Table1Str28, Table1Str29, Table1Str30,
               Table1Str32, Table1Str33,
               SetSobStr01, SetSobStr02, SetSobStr03, SetSobStr04, SetSobStr05, SetSobStr06,
               MsgStr13, MsgStr14, MsgStr15, MsgStr16, MsgStr17, MsgStr18, MsgStr19, MsgStr20,
               MsgStr21, MsgStr22, MsgStr23, MsgStr24, MsgStr25, MsgStr26, MsgStr27, MsgStr28,
               MsgStr29, MsgStr30, MsgStr31, MsgStr32, MsgStr33, MsgStr34, MsgStr35, MsgStr36,
               MsgStr37,
               InfoStr2, InfoStr3, InfoStr4, InfoStr6, InfoStr34, InfoStr35, InfoStr36, InfoStr37,
               PupStr1, PupStr2, PupStr3, PupStr4, PupStr5, PupStr6, PupStr7, PupStr8,
               PupStr9, PupStr10,
               AboutDlgStr1, AboutDlgStr2, AboutDlgStr3,
               OperatorsDlgCaption, OperatorsDlgLabel1Caption, OperatorsDlgLabel2Caption;
   bool STN1;
   int cam1[4];
   int cam2[4];
   TDate OprosDate;
   bool GobiTv;
   TGobiCam HandCam;
   AnsiString handCamstr;
   int HandCamCnt;
   int GobiDkCnt;
   int GobiFixNewWarning;
   bool Stn485Tv;
   int cam485[18];
   AnsiString cam485_sn[6];
   AnsiString cam485str;
   void ShowTochkaSettings();
   void ShowTochkaSettings2(int ch);
   int MySQL_use, MySQL_port;
   AnsiString MySQL_host, MySQL_login, MySQL_password, MySQL_dbname;
   unsigned int events_num;
   int SsoiM1_devnum, SsoiM1_speed, SsoiM1_timeout, SsoiM1_BazaltCnt;
   AnsiString SsoiM1_sernum;
   int SsoiM1_adr[KanCnt];
   void _fastcall SsoiM1Opros(TObject* Sender);
   TTimer **SsoiM1Timer;
   int GroupCmdCnt[KanCnt];
   int ShowSsoiM1Status( int kan, int bl, int flag, unsigned char tbuf[2], int tag );
   void ResetSsoiM1Info();
   TSysOperatorList *OpList;
   AnsiString OpFn, OpN1, OpN2;
   AnsiString ClFn, ClN1, ClN2;
   long int DebugCnt;
   bool P1, P2, P12, P123;
   void ShowPrCnt();
   int MainFormY;
   int ILivedCnt;
   int GoodCloseOpen( AnsiString fn, int &year, int &month, int &day, int &hour, int &min, int &sec );
   void GoodCloseSave( AnsiString fn );
   bool UseAsoosd;
   AnsiString Asoosd_str[100];
   AnsiString DevLineFilePath;
   bool ShowDevLineCam[200];
   SHELLEXECUTEINFO se1[200];
   int AutoStart;
   AnsiString oldName;
   void AlarmsReset( bool netuser );
   void DbStart( bool netuser, bool autostart );
   void Dk_Rif( bool netuser );
   void Dk_Rif_Kan( bool netuser, int kan );
   void Dk_Ssoi( bool netuser );
   void Dk_Ssoi_Kan( bool netuser, int kan );
   void Dk_Dev( bool netuser );
   void Control_Dev( bool netuser );
   bool AutoDbStart;
   int AutoDbStartHour, AutoDbStartMinute;
   TDateTime AutoDbStartDt;
   TStringList *UdpAdress;
   void SaveStringToMySQL(AnsiString sob_str);
   bool DemoMode;
   void AutoChildsOn( int ch, int adr, int sd );
   int ReadStn485Channel( AnsiString fp, AnsiString dev_num );
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
