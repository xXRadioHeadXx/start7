//---------------------------------------------------------------------------
#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "GridsEh.hpp"
#include "ToolCtrlsEh.hpp"
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include <ScktComp.hpp>
#include "TNetClientUnit.h"
#include "TGobiSysUnit.h"
#include "TRifSysUnit.h"
//---------------------------------------------------------------------------
#define RifxComplexType 0           
#define SsoiComplexType 1           
#define Rastr_M_SsoiComplexType 2   
//---------------------------------------------------------------------------
#define IpBlIdx 100
//---------------------------------------------------------------------------
#define GroupType 0
#define SdType 3
#define IuType 4
#define SsoiMSdType 33
#define SsoiMIuType 43
#define RastrType 51
#define Stn485Type 42
#define RastrOldType 5
#define RifType 1
#define RifRlmSType 111
#define SdConcType 2
#define TorosType 8
#define NastType 9
#define RadarType 91
#define RazrivBoType 21
#define TochkaType 10
#define Adam4068Type 7
#define SolidType 6
#define SsoiType 41
#define SdIpBlType 11
#define IuIpBlType 12
#define TabloType 71
#define StrazhIpType 24
#define OnvifTvType 25
#define TochkaMBoIdx 26
#define TochkaMUchIdx 27
#define TochkaMDdIdx 28
#define SotaMBoIdx 29
#define SotaMUchIdx 30
#define SotaMDdIdx 31
#define DevLineIdx 32
#define DevLineIdx 32
#define NetDevIdx 200
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TMainMenu *MainMenu1;
   TMenuItem *FileItems;
   TStatusBar *StatusBar1;
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TDBGridEh *DBGridEh1;
   TTable *Table2;
   TDataSource *DataSource1;
   TMenuItem *ExitItem;
   TMenuItem *N1;
   TMenuItem *MySQLConnectItem;
   TLabel *Label1;
   TComboBox *ComboBox1;
   TButton *Button1;
   TDateTimePicker *DateTimePicker1;
   TLabel *Label2;
   TLabel *Label3;
   TComboBox *ComboBox2;
   TComboBox *ComboBox3;
   TSpeedButton *SpeedButton1;
   TSpeedButton *SpeedButton2;
   TSpeedButton *SpeedButton3;
   TSpeedButton *SpeedButton4;
   TBevel *Bevel1;
   TBevel *Bevel2;
   TPopupMenu *PopupMenu1;
   TMenuItem *N2;
   TPopupMenu *PopupMenu2;
   TMenuItem *N3;
   TButton *Button2;
   TfrxReport *frxReport1;
   TfrxDBDataset *frxDBDataset1;
   TButton *Button3;
   TDateTimePicker *DateTimePicker2;
   TLabel *Label4;
   TLabel *Label5;
   TComboBox *ComboBox4;
   TLabel *Label6;
   TLabel *Label7;
   TComboBox *ComboBox5;
   TIntegerField *Table2Ecnt;
   TStringField *Table2Edt;
   TIntegerField *Table2Etype;
   TStringField *Table2Ename;
   TBooleanField *Table2Eflag;
   TIntegerField *Table2Dtype;
   TIntegerField *Table2Dnum1;
   TIntegerField *Table2Dnum2;
   TIntegerField *Table2Dnum3;
   TStringField *Table2Dname;
   TStringField *Table2Comment;
   TStringField *Table2Comment2;
   TStringField *Table2OpFio;
   TStringField *Table2ClFio;
   TLabel *Label8;
   TComboBox *ComboBox6;
   TLabel *Label9;
   TComboBox *ComboBox7;
   TComboBox *ComboBox8;
   TLabel *Label10;
   TIntegerField *Table2OutType;
   TLabel *Label11;
   TComboBox *ComboBox9;
   TServerSocket *iServer;
   TTimer *KeepAliveTimer;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall ExitItemClick(TObject *Sender);
   void __fastcall MySQLConnectItemClick(TObject *Sender);
   void __fastcall DBGridEh1DblClick(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall ComboBox1Change(TObject *Sender);
   void __fastcall SpeedButton1Click(TObject *Sender);
   void __fastcall SpeedButton2Click(TObject *Sender);
   void __fastcall SpeedButton3Click(TObject *Sender);
   void __fastcall SpeedButton4Click(TObject *Sender);
   void __fastcall N2Click(TObject *Sender);
   void __fastcall N3Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Button3Click(TObject *Sender);
   void __fastcall ComboBox4Click(TObject *Sender);
   void __fastcall ComboBox4KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall DBGridEh1DrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumnEh *Column,
          TGridDrawState State);
   void __fastcall KeepAliveTimerTimer(TObject *Sender);
   void __fastcall iServerClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall iServerClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall iServerClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
   void __fastcall iServerClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);

   int ComplexVersion;

   AnsiString VersionInfoStr;

   AnsiString AppDataPath;

   bool SetTbl1();
   bool CreateTbl1();

   bool LoadLocalConfig(AnsiString fp);
   bool SaveLocalConfig(AnsiString fp);

   AnsiString MySQL_host, MySQL_login, MySQL_password, MySQL_dbname;
   int MySQL_port;
   bool LoadGlobalConfig(AnsiString fp);

   bool ConnectDb();
   bool ReadDb();

   TStringList *CommentList, *CommentList2;

   bool TMainForm::LoadLangConfig( AnsiString fp );
   AnsiString InfoStr1, InfoStr2, InfoStr3, InfoStr4, InfoStr5, InfoStr6,
              InfoStr7, InfoStr8, InfoStr9, InfoStr10, InfoStr11,
              InfoStr12, InfoStr13, InfoStr14, InfoStr15, InfoStr16,
              InfoStr17, InfoStr18, InfoStr19, InfoStr20, InfoStr21,
              InfoStr22,  InfoStr23, InfoStr24, InfoStr25, InfoStr26,
              InfoStr27, InfoStr28, InfoStr29, 
              ErrorMsg, WarningMsg,
              MsgStr1, MsgStr3, MsgStr4, MsgStr12, MsgStr19, MsgStr20, MsgStr23,
              MsgStr27, MsgStr28, MsgStr29, MsgStr30, MsgStr32,
              pfrm_Caption, pfrm_Label1_Caption,
              Table1Str5, Table1Str6, Table1Str7, Table1Str8, Table1Str9, 
              DkItemCaption, Bazalt_pdiCaption, PupStr1;

   void SelectMyObject();

   bool iServerUse;
   int iServerPort;
   int iKeepAlive;

   TStringList *EventsAndStates;
   TiNetSys *iNetSys;
   AnsiString iServerHost;

   TRifSys *RifSys;
   TGobiSys *GobiSys;
   TGobiSys2 *GobiSys2;

   bool Connect;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
