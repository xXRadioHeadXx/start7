//---------------------------------------------------------------------------
#include <vcl.h>
#include <mysql.h>
#include <errmsg.h>
#include <memory>
#pragma hdrstop

#include "MainUnit.h"
#include "MyApiUnit.h"
#include "MySQLDlgUnit.h"
#include "WriteFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "msimg32.lib"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "GridsEh"
#pragma link "ToolCtrlsEh"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
#pragma warn -aus
//---------------------------------------------------------------------------
MYSQL *Con;
MYSQL_RES *Result;
MYSQL_ROW row;
//---------------------------------------------------------------------------
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   VersionInfoStr = "release 04.11.2019";

   MainMenu1->OwnerDraw=true;
   Screen->MenuFont->Name="Microsoft Sans Serif";
   Screen->MenuFont->Charset=DEFAULT_CHARSET;

   ComplexVersion = RifxComplexType;

   iServer->Active = false;

   AnsiString str = ExtractFileName(Application->ExeName);
   if( str.Pos("ssoi") != 0 ) ComplexVersion = SsoiComplexType;

   if( FileExists(ExtractFilePath(Application->ExeName)+"ssoi.ver") )
      ComplexVersion = SsoiComplexType;

   str = ExtractFileName(Application->ExeName);
   if( str.Pos("rastrmssoi") != 0 ) ComplexVersion = Rastr_M_SsoiComplexType;

   if( FileExists(ExtractFilePath(Application->ExeName)+"rastrmssoi.ver") )
      ComplexVersion = Rastr_M_SsoiComplexType;

   AnsiString err_str;

   LoadLangConfig(ExtractFilePath(Application->ExeName)+"lang1.ini");

   RifSys = new TRifSys;
   GobiSys = new TGobiSys;
   GobiSys2 = new TGobiSys2;

   iNetSys = new TiNetSys;

   if( !FileExists(ExtractFilePath(Application->ExeName)+"rifx.ini") ||
       !LoadGlobalConfig(ExtractFilePath(Application->ExeName)+"rifx.ini") )
   {
      MessageBox (NULL, MsgStr1.c_str(), ErrorMsg.c_str(), MB_OK|MB_ICONERROR);
   }

   LoadLocalConfig(ExtractFilePath(Application->ExeName)+"m_db.ini");

   AppDataPath = ExtractFilePath(Application->ExeName) + "AppData\\";
   if( !SetCatalog(AppDataPath) )
   {
      err_str = MsgStr3;
      ShowMessage(err_str);
      Application->Terminate();
   }

   SelectMyObject();

   try
   {
      Table2->DisableControls();
      Table2->Active = false;
      if( SetTbl1() ) Table2->Active = true;
      else
      {
         err_str = MsgStr4;
         ShowMessage(err_str);
         Application->Terminate();
      }
      Table2->EnableControls();
   }
   catch(...)
   {
         err_str = MsgStr4;
         ShowMessage(err_str);
         Application->Terminate();
   }

   if( iServerUse )
   {
     WORD wVersionRequested;
     WSADATA WSAData;
     wVersionRequested = MAKEWORD(1,1);

     try
     {
        if( WSAStartup(wVersionRequested, &WSAData) )
        {
           iServerUse = false;
           MessageBox (NULL,"Ошибка определения сетевых параметров. Запуск модуля БД невозможен!",ErrorMsg.c_str(),MB_OK|MB_ICONERROR);
        }
        else
        {
           hostent *P;
           char s[128];
           in_addr in;
           char *P2;
           gethostname(s,128);
           P=gethostbyname(s);
           iServerHost = P->h_name;
           in.S_un.S_un_b.s_b1 = P->h_addr_list[0][0];
           in.S_un.S_un_b.s_b2 = P->h_addr_list[0][1];
           in.S_un.S_un_b.s_b3 = P->h_addr_list[0][2];
           in.S_un.S_un_b.s_b4 = P->h_addr_list[0][3];
           P2 = inet_ntoa(in);

           iServer->Port = iServerPort;
           if( iServerUse )
           {
              iServer->Active = true;
              EventsAndStates = new TStringList();
              KeepAliveTimer->Enabled = true;
           }
        }

        WSACleanup();
     }
     catch(...)
     {
        iServerUse = false;
        MessageBox (NULL,"Ошибка определения сетевых параметров. Запуск модуля БД невозможен!",ErrorMsg.c_str(),MB_OK|MB_ICONERROR);
     }
   }

   Con = mysql_init(NULL);
   if( ConnectDb() ) ReadDb();
   else
   {
      Application->Terminate();
   }

   DateTimePicker1->Enabled = false;
   DateTimePicker1->Visible = false;
   DateTimePicker2->Enabled = false;
   DateTimePicker2->Visible = false;
   Label4->Visible = false;
   Label5->Visible = false;
   Label6->Visible = false;
   ComboBox4->Visible = false;
   Label7->Visible = false;
   ComboBox5->Visible = false;

   CommentList = new TStringList;
   try
   {
      CommentList->LoadFromFile(ExtractFilePath(Application->ExeName)+"comment.lst");
      CommentList->Sort();
      ComboBox2->Items->Clear();
      for( int i = 0; i < CommentList->Count; i++ )
         ComboBox2->Items->Add(CommentList->Strings[i]);
   }
   catch(...)
   {
      ;
   }

   CommentList2 = new TStringList;
   try
   {
      CommentList2->LoadFromFile(ExtractFilePath(Application->ExeName)+"comment2.lst");
      CommentList2->Sort();
      ComboBox3->Items->Clear();
      for( int i = 0; i < CommentList2->Count; i++ )
         ComboBox3->Items->Add(CommentList2->Strings[i]);
   }
   catch(...)
   {
      ;
   }

   Caption = Caption + " - " + VersionInfoStr;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
   if( Application->MessageBox( MsgStr12.c_str(), WarningMsg.c_str(), MB_YESNO ) != IDYES )
      Action = caNone;
   else
   {
      SaveLocalConfig(ExtractFilePath(Application->ExeName)+"m_db.ini");

      if( Table2->Exists )
      {
         Table2->Active = false;
         Table2->DeleteTable();
      }

      mysql_close(Con);

      try
      {
         CommentList->SaveToFile(ExtractFilePath(Application->ExeName)+"comment.lst");
         CommentList2->SaveToFile(ExtractFilePath(Application->ExeName)+"comment2.lst");
      }
      catch(...)
      {
         ;
      }
      
      delete CommentList;
      delete CommentList2;
   }
}
//---------------------------------------------------------------------------
bool TMainForm::SetTbl1()
{
   bool flag = false;

   Table2->Active = false;
   Table2->DatabaseName = AppDataPath;
   Table2->TableType = ttParadox;
   Table2->TableName = "DbTemp.Db";

   if( Table2->Exists )
   {
      Table2->DeleteTable();
   }

   if( CreateTbl1() ) flag = true;
   else flag = true;

   return flag;
}
//---------------------------------------------------------------------------
bool TMainForm::CreateTbl1()
{
   bool flag = false;

   try
   {
      Table2->Active = false;

      Table2->FieldDefs->Clear();
      Table2->FieldDefs->Add( "Ecnt", ftInteger, 0, false );  
      Table2->FieldDefs->Add( "Edt", ftString, 25, false );   
      Table2->FieldDefs->Add( "Etype", ftInteger, 0, false ); 
      Table2->FieldDefs->Add( "Ename", ftString, 30, false ); 
      Table2->FieldDefs->Add( "Eflag", ftBoolean, 0, false ); 
      Table2->FieldDefs->Add( "Dtype", ftInteger, 0, false ); 
      Table2->FieldDefs->Add( "Dnum1", ftInteger, 0, false );
      Table2->FieldDefs->Add( "Dnum2", ftInteger, 0, false );
      Table2->FieldDefs->Add( "Dnum3", ftInteger, 0, false );
      Table2->FieldDefs->Add( "Dname", ftString, 25, false );
      Table2->FieldDefs->Add( "Comment", ftString, 25, false ); 
      Table2->FieldDefs->Add( "Comment2", ftString, 25, false );
      Table2->FieldDefs->Add( "OpFio", ftString, 50, false );  
      Table2->FieldDefs->Add( "ClFio", ftString, 50, false ); 
      Table2->FieldDefs->Add( "OutType", ftInteger, 0, false ); 

      Table2->IndexDefs->Clear();
      Table2->IndexDefs->Add("","Ecnt", TIndexOptions()<<ixPrimary<< ixUnique);
      Table2->IndexDefs->Add("PosIdx","Ecnt", TIndexOptions()<< ixCaseInsensitive);

      Table2->CreateTable();

      flag = true;
   }
   catch(...)
   {
      flag = false;
   }

   return flag;
}
//---------------------------------------------------------------------------
bool TMainForm::LoadLocalConfig(AnsiString fp)
{
   TMemIniFile *ini;
   ini = new TMemIniFile( fp );

   bool mf_maximized = ini->ReadBool( "MAINFORM", "MainFormMaximixed", false );
   if( mf_maximized ) MainForm->WindowState = wsMaximized;
   else
   {
      MainForm->Left = ini->ReadInteger( "MAINFORM", "MainFormLeft", 10 );
      MainForm->Top = ini->ReadInteger( "MAINFORM", "MainFormTop", 10 );
      MainForm->Width = ini->ReadInteger( "MAINFORM", "MainFormWidth", 640 );
      MainForm->Height = ini->ReadInteger( "MAINFORM", "MainFormHeight", 480 );
   }

   DBGridEh1->Font->Size = ini->ReadInteger( "DBGRIDEH1", "Font", 8 );
   DBGridEh1->Columns->Items[0]->Width = ini->ReadInteger( "DBGRIDEH1", "C1_Width", 70 );
   DBGridEh1->Columns->Items[1]->Width = ini->ReadInteger( "DBGRIDEH1", "C2_Width", 100 );
   DBGridEh1->Columns->Items[2]->Width = ini->ReadInteger( "DBGRIDEH1", "C3_Width", 170 );
   DBGridEh1->Columns->Items[3]->Width = ini->ReadInteger( "DBGRIDEH1", "C4_Width", 170 );
   DBGridEh1->Columns->Items[4]->Width = ini->ReadInteger( "DBGRIDEH1", "C5_Width", 150 );
   DBGridEh1->Columns->Items[5]->Width = ini->ReadInteger( "DBGRIDEH1", "C6_Width", 150 );
   DBGridEh1->Columns->Items[6]->Width = ini->ReadInteger( "DBGRIDEH1", "C7_Width", 150 );
   DBGridEh1->Columns->Items[7]->Width = ini->ReadInteger( "DBGRIDEH1", "C8_Width", 150 );
   DBGridEh1->Columns->Items[7]->Visible = false;

   delete ini;

   return true;
}
//---------------------------------------------------------------------------
bool TMainForm::SaveLocalConfig(AnsiString fp)
{
   TMemIniFile *ini;
   ini = new TMemIniFile( fp );

   if( MainForm->WindowState == wsMaximized ) ini->WriteInteger( "MAINFORM", "MainFormMaximixed", true );
   else ini->WriteInteger( "MAINFORM", "MainFormMaximixed", false );

   ini->WriteInteger( "MAINFORM", "MainFormLeft", MainForm->Left );
   ini->WriteInteger( "MAINFORM", "MainFormTop", MainForm->Top );
   ini->WriteInteger( "MAINFORM", "MainFormWidth", MainForm->Width );
   ini->WriteInteger( "MAINFORM", "MainFormHeight", MainForm->Height );

   ini->WriteInteger( "DBGRIDEH1", "Font", DBGridEh1->Font->Size );
   ini->WriteInteger( "DBGRIDEH1", "C1_Width", DBGridEh1->Columns->Items[0]->Width);
   ini->WriteInteger( "DBGRIDEH1", "C2_Width", DBGridEh1->Columns->Items[1]->Width );
   ini->WriteInteger( "DBGRIDEH1", "C3_Width", DBGridEh1->Columns->Items[2]->Width );
   ini->WriteInteger( "DBGRIDEH1", "C4_Width", DBGridEh1->Columns->Items[3]->Width );
   ini->WriteInteger( "DBGRIDEH1", "C5_Width", DBGridEh1->Columns->Items[4]->Width );
   ini->WriteInteger( "DBGRIDEH1", "C6_Width", DBGridEh1->Columns->Items[5]->Width );
   ini->WriteInteger( "DBGRIDEH1", "C7_Width", DBGridEh1->Columns->Items[6]->Width );
   ini->WriteInteger( "DBGRIDEH1", "C8_Width", DBGridEh1->Columns->Items[7]->Width );

   ini->UpdateFile();
   delete ini;

   return true;
}
//---------------------------------------------------------------------------
bool TMainForm::LoadLangConfig( AnsiString fp )
{
   TMemIniFile *ini;
   ini = new TMemIniFile( fp );

   MainForm->Caption = ini->ReadString( "DB", "MainCaption", "База данных" );
   GroupBox2->Caption = MainForm->Caption;
   FileItems->Caption = ini->ReadString( "DB", "FileItemsCaption", "Файл" );
   MySQLConnectItem->Caption = ini->ReadString( "DB", "MySQLConnectItemCaption", "Подключение к БД" );
   ExitItem->Caption = ini->ReadString( "DB", "ExitItemCaption", "Выход" );

   GroupBox1->Caption = ini->ReadString( "DB", "GroupBox1Caption", "Выбор данных" );
   Label1->Caption = ini->ReadString( "DB", "Label1Caption", "Тип данных" );
   InfoStr7 = ini->ReadString( "DB", "InfoStr7", "Все смены" );
   InfoStr8 = ini->ReadString( "DB", "InfoStr8", "По параметрам" );
   ComboBox1->Items->Clear();
   ComboBox1->Items->Add(InfoStr7);
   ComboBox1->Items->Add(InfoStr8);
   ComboBox1->ItemIndex = 0;
   Label4->Caption = ini->ReadString( "DB", "Label4Caption", "Период с" );
   Label5->Caption = ini->ReadString( "DB", "Label5Caption", "по" );
   Label6->Caption = ini->ReadString( "DB", "Label6Caption", "Объект" );
   InfoStr9 = ini->ReadString( "DB", "InfoStr9", "Все" );
   InfoStr10 = ini->ReadString( "DB", "InfoStr10", "СД" );
   InfoStr11 = ini->ReadString( "DB", "InfoStr11", "ИУ" );
   InfoStr12 = ini->ReadString( "DB", "InfoStr12", "РИФ-РЛМ(КРЛ), Трасса" );
   InfoStr13 = ini->ReadString( "DB", "InfoStr13", "СД концентратора" );
   InfoStr14 = ini->ReadString( "DB", "InfoStr14", "Торос" );
   InfoStr15 = ini->ReadString( "DB", "InfoStr15", "Наст" );
   InfoStr16 = ini->ReadString( "DB", "InfoStr16", "Радар" );
   InfoStr17 = ini->ReadString( "DB", "InfoStr17", "Разрыв БО" );
   InfoStr18 = ini->ReadString( "DB", "InfoStr18", "Точка/Гарда" );
   InfoStr19 = ini->ReadString( "DB", "InfoStr19", "Адам-406x/4168" );
   InfoStr20= ini->ReadString( "DB", "InfoStr20", "СД БЛ-IP" );
   InfoStr21= ini->ReadString( "DB", "InfoStr21", "ИУ БЛ-IP" );
   ComboBox4->Items->Clear();
   ComboBox4->Items->Add(InfoStr9);
   ComboBox4->Items->Add(InfoStr10);
   ComboBox4->Items->Add(InfoStr11);
   if( ComplexVersion == RifxComplexType )
   {
      ComboBox4->Items->Add(InfoStr12);
      ComboBox4->Items->Add(InfoStr13);
      ComboBox4->Items->Add(InfoStr14);
      ComboBox4->Items->Add(InfoStr15);
      ComboBox4->Items->Add(InfoStr16);
      ComboBox4->Items->Add(InfoStr17);
      ComboBox4->Items->Add(InfoStr18);
      ComboBox4->Items->Add(InfoStr19);
      ComboBox4->Items->Add(InfoStr20);
      ComboBox4->Items->Add(InfoStr21);
      ComboBox4->Items->Add("РИФ-РЛМ-С");
      ComboBox4->Items->Add("БОД Точка-М/Гарда-М");
      ComboBox4->Items->Add("ДД Точка-М/Гарда-М");
      ComboBox4->Items->Add("БО Сота/Сота-М");
      ComboBox4->Items->Add("ДД Сота/Сота-М");
   }
   ComboBox4->ItemIndex = 0;
   Label7->Caption = ini->ReadString( "DB", "Label7Caption", "Событие" );
   InfoStr22= ini->ReadString( "DB", "InfoStr22", "Тревоги" );
   InfoStr23= ini->ReadString( "DB", "InfoStr23", "Неисправности" );
   InfoStr24= ini->ReadString( "DB", "InfoStr24", "Команды" );
   ComboBox5->Items->Clear();
   ComboBox5->Items->Add(InfoStr9);
   ComboBox5->Items->Add(InfoStr22);
   ComboBox5->Items->Add(InfoStr23);
   ComboBox5->Items->Add(InfoStr24);
   ComboBox5->ItemIndex = 0;
   Button1->Caption = ini->ReadString( "DB", "Button1Caption", "Выбрать" );
   Button2->Caption = ini->ReadString( "DB", "Button2Caption", "Предварительный просмотр" );
   Button3->Caption = ini->ReadString( "DB", "Button3Caption", "Печать" );
   Label2->Caption = ini->ReadString( "DB", "Label2Caption", "Причины" );
   Label3->Caption = ini->ReadString( "DB", "Label3Caption", "Принятые меры" );

   InfoStr1 = ini->ReadString( "DB", "InfoStr1", "Соединение с сервером баз данных MySQL успешно!" );
   InfoStr2 = ini->ReadString( "DB", "InfoStr2", "Ошибка соединения с сервером баз данных MySQL!" );
   InfoStr3 = ini->ReadString( "DB", "InfoStr3", "Код ошибки" );
   InfoStr4 = ini->ReadString( "DB", "InfoStr4", "Cообщение" );
   InfoStr5 = "Данные с заданными параметрами сортировки. Измените параметры сортировки";
   InfoStr6 = ini->ReadString( "DB", "InfoStr6", "Ошибка записи в таблицу EVENTS!" );
   InfoStr25 = ini->ReadString( "DB", "InfoStr25", "Сервер БД" );
   InfoStr26 = ini->ReadString( "DB", "InfoStr26", "Порт" );
   InfoStr27 = ini->ReadString( "DB", "InfoStr27", "База данных" );
   InfoStr28 = ini->ReadString( "DB", "InfoStr28", "Логин" );
   InfoStr29 = ini->ReadString( "DB", "InfoStr29", "Пароль" );

   ErrorMsg = ini->ReadString( "MSGSTRING", "ErrorMsg", "Ошибка" );
   WarningMsg = ini->ReadString( "MSGSTRING", "WarningMsg", "Предупреждение" );

   MsgStr1 = ini->ReadString( "MSGSTRING", "MsgStr1", "Ошибка загрузки конфигурации!" );
   MsgStr3 = ini->ReadString( "MSGSTRING", "MsgStr3", "Отсутствует рабочий каталог программы!" );
   MsgStr4 = ini->ReadString( "MSGSTRING", "MsgStr4", "Ошибка создания баз данных!" );
   MsgStr12 = ini->ReadString( "MSGSTRING", "MsgStr12", "Завершить работу и выйти из программы?" );
   MsgStr19 = ini->ReadString( "MSGSTRING", "MsgStr19", "Причина не задана!" );
   MsgStr20 = ini->ReadString( "MSGSTRING", "MsgStr20", "Принятые меры не заданы!" );
   MsgStr27 = ini->ReadString( "MSGSTRING", "MsgStr27", "Канал" );
   MsgStr28 = ini->ReadString( "MSGSTRING", "MsgStr28", "БЛ" );
   MsgStr29 = ini->ReadString( "MSGSTRING", "MsgStr29", "СД" );
   MsgStr30 = ini->ReadString( "MSGSTRING", "MsgStr30", "ИУ" );
   MsgStr32 = ini->ReadString( "MSGSTRING", "MsgStr32", "Вскрытие" );

   DBGridEh1->Columns->Items[1]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns1TitleCaption", "Дата, время" );
   DBGridEh1->Columns->Items[2]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns2TitleCaption", "Событие" );
   DBGridEh1->Columns->Items[3]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns3TitleCaption", "Объект" );
   DBGridEh1->Columns->Items[4]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns4TitleCaption", "Причина" );
   DBGridEh1->Columns->Items[5]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns5TitleCaption", "Принятые меры" );
   DBGridEh1->Columns->Items[6]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns6TitleCaption", "Оператор" );
   DBGridEh1->Columns->Items[7]->Title->Caption = ini->ReadString( "MAINFORM", "DBGrid1Columns7TitleCaption", "Клиент" );

   pfrm_Caption = ini->ReadString( "OWINDOWS", "pfrm_Caption", "Подождите" );
   pfrm_Label1_Caption = ini->ReadString( "OWINDOWS", "pfrm_Label1_Caption", "Загрузка данных..." );

   Table1Str5 = ini->ReadString( "TABLE1STRINGS", "Table1Str5", "Нет связи" );
   Table1Str6 = ini->ReadString( "TABLE1STRINGS", "Table1Str6", "Ком. ДК не выполнена" );
   Table1Str7 = ini->ReadString( "TABLE1STRINGS", "Table1Str7", "Ком. упр. не выполнена" );
   Table1Str8 = ini->ReadString( "TABLE1STRINGS", "Table1Str8", "Тревога - СРАБОТКА" );
   Table1Str9 = ini->ReadString( "TABLE1STRINGS", "Table1Str9", "Тревога - ВСКРЫТИЕ" );
   PupStr1 = ini->ReadString( "POPUPMENU1", "PupStr1", "Включить/Выключить" );
   MsgStr23 = ini->ReadString( "MSGSTRING", "MsgStr23", "Оператор" );
   DkItemCaption = ini->ReadString( "MAINFORM", "DkItemCaption", "ДК" );
   Bazalt_pdiCaption = ini->ReadString( "MCFG", "Bazalt_pdiCaption", "УЗ Монолит" );

   TfrxMemoView * Memo19 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo19"));
   Memo19->Text = ini->ReadString( "DB", "InfoStr30", "Отчет" );
   TfrxMemoView * Memo5 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo5"));
   Memo5->Text = DBGridEh1->Columns->Items[1]->Title->Caption;
   TfrxMemoView * Memo7 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo7"));
   Memo7->Text = DBGridEh1->Columns->Items[2]->Title->Caption;
   TfrxMemoView * Memo9 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo9"));
   Memo9->Text = DBGridEh1->Columns->Items[3]->Title->Caption;
   TfrxMemoView * Memo11 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo11"));
   Memo11->Text = DBGridEh1->Columns->Items[4]->Title->Caption;
   TfrxMemoView * Memo13 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo13"));
   Memo13->Text = DBGridEh1->Columns->Items[5]->Title->Caption;
   TfrxMemoView * Memo1 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo1"));
   Memo1->Text = DBGridEh1->Columns->Items[6]->Title->Caption;
   TfrxMemoView * Memo15 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo15"));
   Memo15->Text = ini->ReadString( "DB", "InfoStr31", "подпись" );
   TfrxMemoView * Memo16 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo16"));
   Memo16->Text = ini->ReadString( "DB", "InfoStr32", "ФИО" );
   TfrxMemoView * Memo17 = dynamic_cast <TfrxMemoView *> (frxReport1->FindObject("Memo17"));
   Memo17->Text = ini->ReadString( "DB", "InfoStr33", "дата, время создания" );

   delete ini;

   return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ExitItemClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::MySQLConnectItemClick(TObject *Sender)
{
   Connect = false;

   MySQLDlg = new TMySQLDlg(this);
   MySQLDlg->ShowModal();
   delete MySQLDlg;

   if( Connect )
   {
      mysql_close(Con);

      Con = mysql_init(NULL);

      if( ConnectDb() ) ReadDb();
   }
}
//---------------------------------------------------------------------------
bool TMainForm::LoadGlobalConfig( AnsiString fp )
{
   TMemIniFile *ini;
   ini = new TMemIniFile( fp );

   MySQL_host = ini->ReadString( "MYSQL", "Host", "" );
   MySQL_port = ini->ReadInteger( "MYSQL", "Port", 3306 );
   MySQL_login = ini->ReadString( "MYSQL", "Login", "" );
   MySQL_password = ini->ReadString( "MYSQL", "Password", "" );
   MySQL_password = XOR_Crypt(MySQL_password,"start7");
   MySQL_dbname = ini->ReadString( "MYSQL", "DbName", "" );

   iServerUse = ini->ReadBool( "INTEGRATION", "Use", false );
   iServerPort = ini->ReadInteger( "INTEGRATION", "Port2", 1976 );
   iKeepAlive = ini->ReadInteger( "INTEGRATION", "KeepAliveInterval", 10 );

   int Cnt = ini->ReadInteger( "TREE", "Count", 0 );
   if( Cnt > 0 )
   {
      AnsiString str, name, description;
      int type, num1, num2, num3, level, idx;
      double lan, lon;

      for( int i = 1; i <= Cnt; i++ )
      {
         str.sprintf("Obj_%d", i);
         type = ini->ReadInteger( str.c_str(), "Type", 0 );
         num1 = ini->ReadInteger( str.c_str(), "Num1", 0 );
         num2 = ini->ReadInteger( str.c_str(), "Num2", 0 );
         num3 = ini->ReadInteger( str.c_str(), "Num3", 0 );
         level = ini->ReadInteger( str.c_str(), "Level", 0 );
         name = ini->ReadString( str.c_str(), "Name", "" );
         idx = i;
         description = ini->ReadString( str.c_str(), "Description", "" );
         lan = ini->ReadFloat( str.c_str(), "lan", 0.0 );
         lon = ini->ReadFloat( str.c_str(), "lon", 0.0 );

         if( type == RifType || type == RifRlmSType )
         {
            RifSys->Rk[num3-1][num1-1].Use = true;
            if( type == RifType ) RifSys->Rk[num3-1][num1-1].Type = 0;
            else if( type == RifRlmSType ) RifSys->Rk[num3-1][num1-1].Type = RifRlmSType;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[0] = idx;
            RifSys->Rk[num3-1][num1-1].Level[0] = level;
            RifSys->Rk[num3-1][num1-1].Name[0] = name;
            RifSys->Rk[num3-1][num1-1].description[0] = description;
            RifSys->Rk[num3-1][num1-1].lan[0] = lan;
            RifSys->Rk[num3-1][num1-1].lon[0] = lon;
         }
         else if( type == SdConcType )
         {
            RifSys->Rk[num3-1][num1-1].Type = 1;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[num2-1] = idx;
            RifSys->Rk[num3-1][num1-1].Level[num2-1] = level;
            RifSys->Rk[num3-1][num1-1].Name[num2-1] = name;
            RifSys->Rk[num3-1][num1-1].description[num2-1] = description;
            RifSys->Rk[num3-1][num1-1].lan[num2-1] = lan;
            RifSys->Rk[num3-1][num1-1].lon[num2-1] = lon;
         }
         else if( type == RazrivBoType )
         {
            RifSys->Rk[num3-1][num1-1].Type = 6;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[num2-1] = idx;
            RifSys->Rk[num3-1][num1-1].Level[num2-1] = level;
            RifSys->Rk[num3-1][num1-1].Name[num2-1] = name;
            RifSys->Rk[num3-1][num1-1].description[num2-1] = description;
            RifSys->Rk[num3-1][num1-1].lan[num2-1] = lan;
            RifSys->Rk[num3-1][num1-1].lon[num2-1] = lon;
         }
         else if( type == TorosType )
         {
            RifSys->Rk[num3-1][num1-1].Type = 2;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[0] = idx;
            RifSys->Rk[num3-1][num1-1].Level[0] = level;
            RifSys->Rk[num3-1][num1-1].Name[0] = name;
            RifSys->Rk[num3-1][num1-1].description[0] = description;
            RifSys->Rk[num3-1][num1-1].lan[0] = lan;
            RifSys->Rk[num3-1][num1-1].lon[0] = lon;
         }
         else if( type == NastType )
         {
            RifSys->Rk[num3-1][num1-1].Type = 3;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[0] = idx;
            RifSys->Rk[num3-1][num1-1].Level[0] = level;
            RifSys->Rk[num3-1][num1-1].Name[0] = name;
            RifSys->Rk[num3-1][num1-1].description[0] = description;
            RifSys->Rk[num3-1][num1-1].lan[0] = lan;
            RifSys->Rk[num3-1][num1-1].lon[0] = lon;
         }
         else if( type == RadarType )
         {
            RifSys->Rk[num3-1][num1-1].Type = 5;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[0] = idx;
            RifSys->Rk[num3-1][num1-1].Level[0] = level;
            RifSys->Rk[num3-1][num1-1].Name[0] = name;
            RifSys->Rk[num3-1][num1-1].lon[0] = lon;
            RifSys->Rk[num3-1][num1-1].lan[0] = lan;
            RifSys->Rk[num3-1][num1-1].Name[0] = name;
            RifSys->Rk[num3-1][num1-1].description[0] = description;
            RifSys->Rk[num3-1][num1-1].lan[0] = lan;
            RifSys->Rk[num3-1][num1-1].lon[0] = lon;
         }
         else if( type == TochkaType )
         {
            RifSys->Rk[num3-1][num1-1].Type = 7;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[num2-1] = idx;
            RifSys->Rk[num3-1][num1-1].Level[num2-1] = level;
            RifSys->Rk[num3-1][num1-1].Name[num2-1] = name;
            RifSys->Rk[num3-1][num1-1].description[num2-1] = description;
            RifSys->Rk[num3-1][num1-1].lan[num2-1] = lan;
            RifSys->Rk[num3-1][num1-1].lon[num2-1] = lon;
         }
         else if( type == SdType )
         {
            GobiSys->Kanal[num1-1].Bl[num2-1].Sd[num3-1].TreeIdx = idx;
            GobiSys->Kanal[num1-1].Bl[num2-1].Sd[num3-1].Level = level;
            GobiSys->Kanal[num1-1].Bl[num2-1].Sd[num3-1].Name = name;
            GobiSys->Kanal[num1-1].Bl[num2-1].Sd[num3-1].description = description;
            GobiSys->Kanal[num1-1].Bl[num2-1].Sd[num3-1].lan = lan;
            GobiSys->Kanal[num1-1].Bl[num2-1].Sd[num3-1].lon = lon;
         }
         else if( type == SsoiMSdType )
         {
            GobiSys2->Bl[num1-1][num2-1].Sd[num3-1].TreeIdx = idx;
            GobiSys2->Bl[num1-1][num2-1].Sd[num3-1].Level = level;
            GobiSys2->Bl[num1-1][num2-1].Sd[num3-1].Name = name;
            GobiSys2->Bl[num1-1][num2-1].Sd[num3-1].description = description;
            GobiSys2->Bl[num1-1][num2-1].Sd[num3-1].lan = lan;
            GobiSys2->Bl[num1-1][num2-1].Sd[num3-1].lon = lon;
         }
         else if( type == IuType )
         {
            GobiSys->Kanal[num1-1].Bl[num2-1].Iu[num3-1].TreeIdx = idx;
            GobiSys->Kanal[num1-1].Bl[num2-1].Iu[num3-1].Level = level;
            GobiSys->Kanal[num1-1].Bl[num2-1].Iu[num3-1].Name = name;
         }
         else if( type == SsoiMIuType )
         {
            if( num3 < 4 )
            {
               GobiSys2->Bl[num1-1][num2-1].Iu[num3-1].TreeIdx = idx;
               GobiSys2->Bl[num1-1][num2-1].Iu[num3-1].TreeIdx = level;
               GobiSys2->Bl[num1-1][num2-1].Iu[num3-1].Name = name;
            }
            else
            {
               GobiSys2->Bl[num1-1][num2-1].Vk[num3-4].TreeIdx = idx;
               GobiSys2->Bl[num1-1][num2-1].Vk[num3-4].TreeIdx = level;
               GobiSys2->Bl[num1-1][num2-1].Vk[num3-4].Name = name;
            }
         }
         else if( type == SdIpBlType )
         {
            RifSys->Rk[num3-1][IpBlIdx].Type = SdIpBlType;
            RifSys->Rk[num3-1][IpBlIdx].Port = num3;
            RifSys->Rk[num3-1][IpBlIdx].TreeIdx[num2-1] = idx;
            RifSys->Rk[num3-1][IpBlIdx].Level[num2-1] = level;
            RifSys->Rk[num3-1][IpBlIdx].Name[num2-1] = name;
            RifSys->Rk[num3-1][IpBlIdx].description[num2-1] = description;
            RifSys->Rk[num3-1][IpBlIdx].lan[num2-1] = lan;
            RifSys->Rk[num3-1][IpBlIdx].lon[num2-1] = lon;
         }
         else if( type == IuIpBlType )
         {
            RifSys->Rk[num3-1][IpBlIdx].Type = SdIpBlType;
            RifSys->Rk[num3-1][IpBlIdx].Port = num3;
            RifSys->Rk[num3-1][IpBlIdx].TreeIdx[num2-1+MaxIpBlSdCnt] = idx;
            RifSys->Rk[num3-1][IpBlIdx].Level[num2-1+MaxIpBlSdCnt] = level;
            RifSys->Rk[num3-1][IpBlIdx].Name[num2-1+MaxIpBlSdCnt] = name;
            RifSys->Rk[num3-1][IpBlIdx].description[num2-1+MaxIpBlSdCnt] = description;
            RifSys->Rk[num3-1][IpBlIdx].lan[num2-1+MaxIpBlSdCnt] = lan;
            RifSys->Rk[num3-1][IpBlIdx].lon[num2-1+MaxIpBlSdCnt] = lon;
         }
         else if( type == TochkaMBoIdx || type == SotaMBoIdx )
         {
            if( type == TochkaMBoIdx ) RifSys->Rk[num3-1][num1-1].Type = TochkaMBoIdx;
            else RifSys->Rk[num3-1][num1-1].Type = SotaMBoIdx;
            RifSys->Rk[num3-1][num1-1].Port = num3;
            RifSys->Rk[num3-1][num1-1].TreeIdx[0] = idx;
            RifSys->Rk[num3-1][num1-1].Level[0] = level;
            RifSys->Rk[num3-1][num1-1].Name[0] = name;
            RifSys->Rk[num3-1][num1-1].description[0] = description;
            RifSys->Rk[num3-1][num1-1].lan[0] = lan;
            RifSys->Rk[num3-1][num1-1].lon[0] = lon;

            RifSys->Rk[num3-1][num1-1].Uch = new TDd[MaxTochkaMUchCnt];
            RifSys->Rk[num3-1][num1-1].Dd = new TDd[MaxTochkaMDdCnt];
            for( int uch = 0; uch < MaxTochkaMUchCnt; uch++ ) RifSys->Rk[num3-1][num1-1].Uch[uch].Reset();
            for( int dd = 0; dd < MaxTochkaMDdCnt; dd++ ) RifSys->Rk[num3-1][num1-1].Dd[dd].Reset();
         }
         else if( type == TochkaMUchIdx || type == SotaMUchIdx )
         {
            int flang = num2/100-1;
            RifSys->Rk[num3-1][num1-1].Uch[flang].TreeIdx = idx;
            RifSys->Rk[num3-1][num1-1].Uch[flang].Level = level;
            RifSys->Rk[num3-1][num1-1].Uch[flang].Name = name;
            RifSys->Rk[num3-1][num1-1].Uch[flang].description = description;
            RifSys->Rk[num3-1][num1-1].Uch[flang].lan = lan;
            RifSys->Rk[num3-1][num1-1].Uch[flang].lon = lon;
         }
         else if( type == TochkaMDdIdx || type == SotaMDdIdx )
         {
            int flang = num2/100;
            int dd = num2%100;

            if( flang >= 3 )
            {
               if( type == TochkaMDdIdx ) dd += 26;
               else dd += 100;
            }

            RifSys->Rk[num3-1][num1-1].Dd[dd].TreeIdx = idx;
            RifSys->Rk[num3-1][num1-1].Dd[dd].Level = level;
            RifSys->Rk[num3-1][num1-1].Dd[dd].Name = name;
            RifSys->Rk[num3-1][num1-1].Dd[dd].description = description;
            RifSys->Rk[num3-1][num1-1].Dd[dd].lan = lan;
            RifSys->Rk[num3-1][num1-1].Dd[dd].lon = lon;
         }
      }
   }

   delete ini;

   return true;
}
//---------------------------------------------------------------------------
bool TMainForm::ConnectDb()
{
   AnsiString err_str;
   mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
   int errcode = mysql_errno(Con);
   if( errcode != 0 && errcode != CR_ALREADY_CONNECTED )
   {
      err_str.sprintf("%s %s: %d. %s: %s", InfoStr2, InfoStr3, errcode, InfoStr4, mysql_error(Con));
      ShowMessage(err_str);
      return false;
   }
   else
   {
      err_str = InfoStr1;
      ShowMessage(err_str);
   }

   return true;
}
//---------------------------------------------------------------------------
bool TMainForm::ReadDb()
{
   std::auto_ptr<TReadForm> pfrm(new TReadForm(this));
   pfrm->Caption = pfrm_Caption;
   pfrm->Label1->Caption = pfrm_Label1_Caption;
   pfrm->Update();

   AnsiString query, err_str;
   AnsiString start_str, finish_str;

   if( Table2->Active ) Table2->Active = false;
   Table2->EmptyTable();
   Table2->Active = true;

   if( ComboBox1->ItemIndex == 0 )
   {
      query.sprintf("SELECT * FROM %s.events WHERE event_code=902", MySQL_dbname);
   }
   else
   {
      TDate dt1 = DateTimePicker1->Date;
      DateTimeToString(start_str, "yyyy-mm-dd", dt1);
      start_str = start_str + " 00:00:00";

      TDate dt2 = DateTimePicker2->Date;
      DateTimeToString(finish_str, "yyyy-mm-dd", dt2);
      finish_str = finish_str + " 23:59:59";

      query.sprintf("SELECT * FROM %s.events WHERE event_dt>=\"%s\" AND event_dt<=\"%s\"", MySQL_dbname, start_str, finish_str);

      if( ComboBox4->ItemIndex > 0 )
      {
         switch( ComboBox4->ItemIndex )
         {
            case 1: query = query + " AND (dev_type=3 OR dev_type=33)";  /* СД */
                    if( ComboBox6->ItemIndex > 0 ) query = query + " AND dev_num1=" + IntToStr(ComboBox6->ItemIndex);
                    if( ComboBox7->ItemIndex > 0 ) query = query + " AND dev_num2=" + IntToStr(ComboBox7->ItemIndex);
                    if( ComboBox8->ItemIndex > 0 ) query = query + " AND dev_num3=" + IntToStr(ComboBox8->ItemIndex);
                    break;
            case 2: query = query + " AND (dev_type=4 OR dev_type=43)";  /* ИУ */
                    if( ComboBox6->ItemIndex > 0 ) query = query + " AND dev_num1=" + IntToStr(ComboBox6->ItemIndex);
                    if( ComboBox7->ItemIndex > 0 ) query = query + " AND dev_num2=" + IntToStr(ComboBox7->ItemIndex);
                    if( ComboBox8->ItemIndex > 0 ) query = query + " AND dev_num3=" + IntToStr(ComboBox8->ItemIndex);
                    break;
            case 3: query = query + " AND dev_type=1"; break;   
            case 4: query = query + " AND dev_type=2"; break;   
            case 5: query = query + " AND dev_type=8"; break;   
            case 6: query = query + " AND dev_type=9"; break;   
            case 7: query = query + " AND dev_type=91"; break;  
            case 8: query = query + " AND dev_type=21"; break;  
            case 9: query = query + " AND dev_type=10"; break;  
            case 10: query = query + " AND dev_type=7"; break;  
            case 11: query = query + " AND dev_type=11"; break; 
            case 12: query = query + " AND dev_type=12"; break; 
//            case 13: query = query + " AND dev_type=14"; break;
//            case 14: query = query + " AND dev_type=17"; break;
            case 13: query = query + " AND dev_type=111"; break; 
            case 14: query = query + " AND dev_type=26"; break;  
            case 15: query = query + " AND dev_type=28"; break;  
            case 16: query = query + " AND dev_type=29"; break;  
            case 17: query = query + " AND dev_type=31"; break;  
         }
      }

      if( ComboBox4->Text == InfoStr10 )
      {
          if( ComboBox5->ItemIndex == 1 )
          {
             query = query + " AND (event_code >= 20 AND event_code < 30)";
          }
          else if( ComboBox5->ItemIndex == 2 )
          {
             query = query + "  AND event_code=20";
          }
          else if( ComboBox5->ItemIndex == 3 )
          {
             query = query + "  AND (event_code=21 OR event_code=25)";
          }
          else if( ComboBox5->ItemIndex == 4 )
          {
             query = query + "  AND ((event_code >= 10 AND event_code < 20) OR event_code=200)";
          }
          else if( ComboBox5->ItemIndex == 5 )
          {
             query = query + "  AND (event_code=10 OR event_code=200)";
          }
          else if( ComboBox5->ItemIndex == 6 )
          {
             query = query + "  AND (event_code=11 OR event_code=133 OR event_code=1002 OR event_code=3)";
          }
          else if( ComboBox5->ItemIndex == 7 )
          {
             query = query + " AND ((event_code >= 0 AND event_code < 10) OR (event_code >= 30 AND event_code < 200) OR event_code >= 200)";
          }
          else if( ComboBox5->ItemIndex == 8 )
          {
             query = query + "  AND (event_code=11 OR event_code=133 OR event_code=1002 OR event_code=3)";
          }
          else if( ComboBox5->ItemIndex == 9 )
          {
             query = query + "  AND ((event_code >= 110 AND event_code < 114) OR event_code=150 OR event_code=151 OR event_code=1003 OR event_code=1004 OR event_code=13)";
          }
          else if( ComboBox5->ItemIndex == 10 )
          {
             query = query + "  AND (event_code >= 900 OR event_code=135 OR event_code=136 OR event_code=137)";
          }

          if( ComboBox9->ItemIndex > 0 )
          {
             query = query + "  AND (out_dev_type =" + IntToStr(ComboBox9->ItemIndex) +")";
          }
      }
      else if( ComboBox4->Text == InfoStr11 )
      {
          if( ComboBox5->ItemIndex == 1 )
          {
             query = query + "  AND (event_code=10 OR event_code=11 OR event_code=200)";
          }
          else if( ComboBox5->ItemIndex == 2 )
          {
            query = query + "  AND (event_code=10 OR event_code=200)";
          }
          else if( ComboBox5->ItemIndex == 3 )
          {
            query = query + "  AND event_code=13";
          }
          else if( ComboBox5->ItemIndex == 4 )
          {
            query = query + "  AND event_code=13 OR event_code=100 OR event_code=111\
                               OR event_code=112 OR event_code=113 OR event_code=130\
                               OR event_code=131 OR event_code=140 OR event_code=141\
                               OR event_code=1000 OR event_code=1001";
          }
      }
      else
      {
          if( ComboBox5->ItemIndex == 1 )
          {
             query = query + " AND (event_code >= 20 AND event_code < 30)";
          }
          else if( ComboBox5->ItemIndex == 2 )
          {
             query = query + "  AND ((event_code >= 10 AND event_code < 20) OR event_code=200)";
          }
          else if( ComboBox5->ItemIndex == 3 )
          {
             query = query + " AND ((event_code >= 2 AND event_code < 5) OR event_code=15 OR event_code=30 OR event_code=31\
                               OR (event_code >= 100 AND event_code < 200) OR event_code >= 900)";
          }
      }
   }

   mysql_real_query(Con,query.c_str(),query.Length());
   int err_code = mysql_errno(Con);
   if( err_code != 0 )
   {
      mysql_close(Con);

      Con = mysql_init(NULL);
      mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
      err_code = mysql_errno(Con);
      if( err_code != 0 && err_code != CR_ALREADY_CONNECTED )
      {
         err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
         ShowMessage(err_str);
      }
      else
      {
         mysql_real_query(Con,query.c_str(),query.Length());
         err_code = mysql_errno(Con);
         if( err_code != 0 )
         {
            err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
            ShowMessage(err_str);
         }
      }
   }

   unsigned int num_rows = 0;

   if( err_code == 0 )
   {
       Result = mysql_store_result(Con);

       AnsiString str, fio;

       num_rows = mysql_num_rows(Result);
       if( num_rows != 0 )
       {
          for( unsigned int i = 0; i < num_rows; i++)
          {
             row = mysql_fetch_row(Result);

             Table2->Insert();
             Table2Ecnt->AsInteger = AnsiString(row[0]).ToInt();
             Table2Edt->AsString = AnsiString(row[1]);
             Table2Etype->AsInteger = AnsiString(row[2]).ToInt();
             Table2Ename->AsString = AnsiString(row[3]);
             Table2Eflag->AsBoolean = false;
             Table2Dtype->AsInteger = AnsiString(row[4]).ToInt();
             Table2Dnum1->AsInteger = AnsiString(row[5]).ToInt();
             Table2Dnum2->AsInteger = AnsiString(row[6]).ToInt();
             Table2Dnum3->AsInteger = AnsiString(row[7]).ToInt();
             Table2Dname->AsString = AnsiString(row[8]);
             Table2Comment->AsString = AnsiString(row[9]);
             Table2Comment2->AsString = AnsiString(row[10]);

             str = "";
             fio = "";
             str = AnsiString(row[11]);
             if( str != "(null)" ) fio = str;
             str = AnsiString(row[12]);
             if( str != "(null)" ) fio = fio + " " + str;
             str = AnsiString(row[13]);
             if( str != "(null)" ) fio = fio + " " + str;
             Table2OpFio->AsString = fio;

             str = "";
             fio = "";
             str = AnsiString(row[14]);
             if( str != "(null)" ) fio = str;
             str = AnsiString(row[15]);
             if( str != "(null)" ) fio = fio + " " + str;
             str = AnsiString(row[16]);
             if( str != "(null)" ) fio = fio + " " + str;
             Table2ClFio->AsString = fio;

             Table2OutType->AsInteger = AnsiString(row[17]).ToInt();

             Table2->Post();
          }
          Table2->FlushBuffers();
       }
   }

   pfrm->Close();

   if( err_code == 0 )
   {
      if( num_rows == 0 ) MessageBox (NULL, InfoStr5.c_str(), WarningMsg.c_str() ,MB_OK|MB_ICONINFORMATION);

      mysql_free_result(Result);
   }

   return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DBGridEh1DblClick(TObject *Sender)
{
   if( iServerUse )
   {
      int otype = Table2Dtype->AsInteger;
      int onum1 = Table2Dnum1->AsInteger;
      int onum2 = Table2Dnum2->AsInteger;
      int onum3 = Table2Dnum3->AsInteger;

      int id = 0;
      int level = 0;

      double lan = 0.0;
      double lon = 0.0;
      AnsiString description;

      int flangnum = 0;
      int uchnum = 0;
      int dvnum = 0;
      int num21 = 0;

      switch( otype )
      {
         case 0: 
                 break;
         case 1: 
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
         case 111: 
                 otype = 99;
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
         case 2: 
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[onum2];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[onum2];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[onum2];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[onum2];
                 description = RifSys->Rk[onum3-1][onum1-1].description[onum2];
                 break;
         case 3: 
                 id = GobiSys->Kanal[onum1-1].Bl[onum2-1].Sd[onum3-1].TreeIdx;
                 level = GobiSys->Kanal[onum1-1].Bl[onum2-1].Sd[onum3-1].Level;
                 lan = GobiSys->Kanal[onum1-1].Bl[onum2-1].Sd[onum3-1].lan;
                 lon = GobiSys->Kanal[onum1-1].Bl[onum2-1].Sd[onum3-1].lon;
                 description = GobiSys->Kanal[onum1-1].Bl[onum2-1].Sd[onum3-1].description;
                 break;
         case 33:
                 id = GobiSys2->Bl[onum1-1][onum2-1].Sd[onum3-1].TreeIdx;
                 level = GobiSys2->Bl[onum1-1][onum2-1].Sd[onum3-1].Level;
                 lan = GobiSys2->Bl[onum1-1][onum2-1].Sd[onum3-1].lan;
                 lon = GobiSys2->Bl[onum1-1][onum2-1].Sd[onum3-1].lon;
                 description = GobiSys2->Bl[onum1-1][onum2-1].Sd[onum3-1].description;
                 break;
         case 4: 
                 id = GobiSys->Kanal[onum1-1].Bl[onum2-1].Iu[onum3-1].TreeIdx;
                 level = GobiSys->Kanal[onum1-1].Bl[onum2-1].Iu[onum3-1].Level;
                 break;
         case 43:
                 id = GobiSys2->Bl[onum1-1][onum2-1].Iu[onum3-1].TreeIdx;
                 level = GobiSys2->Bl[onum1-1][onum2-1].Iu[onum3-1].Level;
                 break;
         case 5: 
                 break;
         case 6: 
                 break;
         case 7: 
                 break;
         case 8: 
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
         case 9: 
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
         case 10:
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[onum2-1];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[onum2-1];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[onum2-1];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[onum2-1];
                 description = RifSys->Rk[onum3-1][onum1-1].description[onum2-1];
                 break;
         case 11:
                 id = RifSys->Rk[onum3-1][IpBlIdx].TreeIdx[onum2-1];
                 level = RifSys->Rk[onum3-1][IpBlIdx].Level[onum2-1];
                 lan = RifSys->Rk[onum3-1][IpBlIdx].lan[onum2-1];
                 lon = RifSys->Rk[onum3-1][IpBlIdx].lon[onum2-1];
                 description = RifSys->Rk[onum3-1][IpBlIdx].description[onum2-1];
                 break;
         case 12:
                 id = RifSys->Rk[onum3-1][IpBlIdx].TreeIdx[onum2-1+MaxIpBlSdCnt];
                 level = RifSys->Rk[onum3-1][IpBlIdx].Level[onum2-1+MaxIpBlSdCnt];
                 break;
         case 26:
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
         case 27:
                 num21 = onum2/100-1;
                 id = RifSys->Rk[onum3-1][onum1-1].Uch[num21].TreeIdx;
                 level = RifSys->Rk[onum3-1][onum1-1].Uch[num21].Level;
                 lan = RifSys->Rk[onum3-1][onum1-1].Uch[num21].lan;
                 lon = RifSys->Rk[onum3-1][onum1-1].Uch[num21].lon;
                 description = RifSys->Rk[onum3-1][onum1-1].Uch[num21].description;
                 break;
         case 28:
                 num21 = onum2%100;
                 if( onum2 >= 300 ) num21 += 26;
                 id = RifSys->Rk[onum3-1][onum1-1].Dd[num21].TreeIdx;
                 level = RifSys->Rk[onum3-1][onum1-1].Dd[num21].Level;
                 lan = RifSys->Rk[onum3-1][onum1-1].Dd[num21].lan;
                 lon = RifSys->Rk[onum3-1][onum1-1].Dd[num21].lon;
                 description = RifSys->Rk[onum3-1][onum1-1].Dd[num21].description;
                 break;
         case 29:
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
         case 30:
                 num21 = onum2/100-1;
                 id = RifSys->Rk[onum3-1][onum1-1].Uch[num21].TreeIdx;
                 level = RifSys->Rk[onum3-1][onum1-1].Uch[num21].Level;
                 lan = RifSys->Rk[onum3-1][onum1-1].Uch[num21].lan;
                 lon = RifSys->Rk[onum3-1][onum1-1].Uch[num21].lon;
                 description = RifSys->Rk[onum3-1][onum1-1].Uch[num21].description;
                 break;
         case 31:
                 num21 = onum2%100;
                 if( onum2 >= 300 ) num21 += 26;
                 id = RifSys->Rk[onum3-1][onum1-1].Dd[num21].TreeIdx;
                 level = RifSys->Rk[onum3-1][onum1-1].Dd[num21].Level;
                 lan = RifSys->Rk[onum3-1][onum1-1].Dd[num21].lan;
                 lon = RifSys->Rk[onum3-1][onum1-1].Dd[num21].lon;
                 description = RifSys->Rk[onum3-1][onum1-1].Dd[num21].description;
                 break;
         case 21:
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[onum2];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[onum2];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[onum2];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[onum2];
                 description = RifSys->Rk[onum3-1][onum1-1].description[onum2];
                 break;
         case 41:
                 break;
         case 42:
                 break;
         case 51:
                 break;
         case 91:
                 id = RifSys->Rk[onum3-1][onum1-1].TreeIdx[0];
                 level = RifSys->Rk[onum3-1][onum1-1].Level[0];
                 lan = RifSys->Rk[onum3-1][onum1-1].lan[0];
                 lon = RifSys->Rk[onum3-1][onum1-1].lon[0];
                 description = RifSys->Rk[onum3-1][onum1-1].description[0];
                 break;
      }

      AnsiString str;
      str = "<RIFPlusPacket type=\"EventBook\">";
      EventsAndStates->Add(str);
      str = "<devices>";
      EventsAndStates->Add(str);

      str.sprintf("<device id=\"%d\" level=\"%d\" type=\"%d\" num1=\"%d\" num2=\"%d\" num3=\"%d\" name=\"%s\" lat=\"%10.8f\" lon=\"%10.8f\" description=\"%s\">",
                  id, level, otype, onum1, onum2, onum3, Table2Dname->AsString, lan, lon, description );
      EventsAndStates->Add(str);
      str.sprintf("<states>");
      EventsAndStates->Add(str);

      AnsiString dt_str = Table2Edt->AsString;
      str.sprintf("<state id=\"%d\" datetime=\"%s\" name=\"%s\"/>",
                  Table2Etype->AsInteger, dt_str, Table2Ename->AsString );
      EventsAndStates->Add(str);

      str.sprintf("</states>");
      EventsAndStates->Add(str);

      str.sprintf("</device>");
      EventsAndStates->Add(str);

      str = "</devices>";
      EventsAndStates->Add(str);

      str = "</RIFPlusPacket>";
      EventsAndStates->Add(str);
   }

   if( Table2Etype->AsInteger == 902 )
   {
      std::auto_ptr<TReadForm> pfrm(new TReadForm(this));
      pfrm->Update();

      int start = Table2Ecnt->AsInteger;

      AnsiString query, err_str, str, fio;
      query.sprintf("SELECT * FROM %s.events WHERE event_code=902 AND event_num>%d LIMIT 1", MySQL_dbname, start);

      mysql_real_query(Con,query.c_str(),query.Length());
      int err_code = mysql_errno(Con);
      if( err_code != 0 )
      {
          mysql_close(Con);

          Con = mysql_init(NULL);
          mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
          err_code = mysql_errno(Con);
          if( err_code != 0 && err_code != CR_ALREADY_CONNECTED )
          {
             err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
             ShowMessage(err_str);
          }
          else
          {
             mysql_real_query(Con,query.c_str(),query.Length());
             err_code = mysql_errno(Con);
             if( err_code != 0 )
             {
                err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                ShowMessage(err_str);
             }
          }
      }

      if( err_code == 0 )
      {
         Result = mysql_store_result(Con);

         if( Result != NULL )
         {
            row = mysql_fetch_row(Result);

            if( row == NULL )
               query.sprintf("SELECT * FROM %s.events WHERE event_num>%d", MySQL_dbname, start);
            else
            {
                int finish = AnsiString(row[0]).ToInt();
                query.sprintf("SELECT * FROM %s.events WHERE event_num>=%d AND event_num<%d", MySQL_dbname, start, finish);
            }
            mysql_free_result(Result);
            mysql_real_query(Con,query.c_str(),query.Length());
            Result = mysql_store_result(Con);

            if( Result != NULL )
            {
//            if( row != NULL )
               {
                   unsigned int num_rows;
                   num_rows = mysql_num_rows(Result);
                   if( num_rows != 0 )
                   {
                      if( Table2->Active ) Table2->Active = false;

                      Table2->EmptyTable();

                      Table2->Active = true;

                      for( unsigned int i = 0; i < num_rows; i++)
                      {
                         row = mysql_fetch_row(Result);

                         Table2->Insert();
                         Table2Ecnt->AsInteger = AnsiString(row[0]).ToInt();
                         Table2Edt->AsString = AnsiString(row[1]);
                         Table2Etype->AsInteger = AnsiString(row[2]).ToInt();
                         Table2Ename->AsString = AnsiString(row[3]);
                         Table2Eflag->AsBoolean = false;
                         Table2Dtype->AsInteger = AnsiString(row[4]).ToInt();
                         Table2Dnum1->AsInteger = AnsiString(row[5]).ToInt();
                         Table2Dnum2->AsInteger = AnsiString(row[6]).ToInt();
                         Table2Dnum3->AsInteger = AnsiString(row[7]).ToInt();
                         Table2Dname->AsString = AnsiString(row[8]);
                         Table2Comment->AsString = AnsiString(row[9]);
                         Table2Comment2->AsString = AnsiString(row[10]);

                         str = "";
                         fio = "";
                         str = AnsiString(row[11]);
                         if( str != "(null)" ) fio = str;
                         str = AnsiString(row[12]);
                         if( str != "(null)" ) fio = fio + " " + str;
                         str = AnsiString(row[13]);
                         if( str != "(null)" ) fio = fio + " " + str;
                         Table2OpFio->AsString = fio;

                         str = "";
                         fio = "";
                         str = AnsiString(row[14]);
                         if( str != "(null)" ) fio = str;
                         str = AnsiString(row[15]);
                         if( str != "(null)" ) fio = fio + " " + str;
                         str = AnsiString(row[16]);
                         if( str != "(null)" ) fio = fio + " " + str;
                         Table2ClFio->AsString = fio;

                         Table2->Post();
                      }
                      Table2->FlushBuffers();
                   }
               }
            }
         }

         mysql_free_result(Result);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   ReadDb();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ComboBox1Change(TObject *Sender)
{
   if( ComboBox1->ItemIndex == 0 )
   {
      DateTimePicker1->Enabled = false;
      DateTimePicker1->Visible = false;
      DateTimePicker2->Enabled = false;
      DateTimePicker2->Visible = false;
      Label4->Visible = false;
      Label5->Visible = false;
      Label6->Visible = false;
      ComboBox4->Visible = false;
      Label7->Visible = false;
      ComboBox5->Visible = false;
      Label8->Visible = false;
      Label9->Visible = false;
      Label10->Visible = false;
      Label11->Visible = false;
      ComboBox6->Visible = false;
      ComboBox7->Visible = false;
      ComboBox8->Visible = false;
      ComboBox9->Visible = false;
   }
   else
   {
      DateTimePicker1->DateTime = Now();
      DateTimePicker1->Enabled = true;
      DateTimePicker1->Visible = true;
      DateTimePicker2->DateTime = Now();
      DateTimePicker2->Enabled = true;
      DateTimePicker2->Visible = true;
      Label4->Visible = true;
      Label5->Visible = true;
      Label6->Visible = true;
      ComboBox4->Visible = true;
      Label7->Visible = true;
      ComboBox5->Visible = true;
      Label8->Visible = false;
      Label9->Visible = false;
      Label10->Visible = false;
      Label11->Visible = false;
      ComboBox6->Visible = false;
      ComboBox7->Visible = false;
      ComboBox8->Visible = false;
      ComboBox9->Visible = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{
   if( ComboBox2->Text == "" )
      MessageBox (NULL, MsgStr19.c_str(), ErrorMsg.c_str(),MB_OK|MB_ICONERROR);
   else
   {
      if( !Table2->IsEmpty() && DBGridEh1->SelectedRows->Count > 0 )
      {
         TDataSet *pDS = DBGridEh1->DataSource->DataSet;
         for( int i=0; i < DBGridEh1->SelectedRows->Count; i++)
         {
            pDS->GotoBookmark((void *)DBGridEh1->SelectedRows->Items[i].c_str());

            AnsiString str;
            str = pDS->Fields->Fields[10]->AsString;
            if( str.Length() == 0 )
            {
               Table2->Edit();
               pDS->Fields->Fields[10]->AsString = ComboBox2->Text;
               Table2->Post();
            }
            Table2->FlushBuffers();


            AnsiString query, err_str;
            int event_num = StrToInt(pDS->Fields->Fields[0]->AsString);
            query.sprintf("UPDATE %s.events SET comment1=\'%s\' WHERE comment1=\'\' AND event_num=%d",
                           MySQL_dbname,
                           pDS->Fields->Fields[10]->AsString,
                           event_num);

             mysql_real_query(Con,query.c_str(),query.Length());
             int err_code = mysql_errno(Con);
             if( err_code != 0 )
             {
                  mysql_close(Con);

                  Con = mysql_init(NULL);
                  mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
                  err_code = mysql_errno(Con);
                  if( err_code != 0 && err_code != CR_ALREADY_CONNECTED )
                  {
                     err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                     ShowMessage(err_str);
                  }
                  else
                  {
                     mysql_real_query(Con,query.c_str(),query.Length());
                     err_code = mysql_errno(Con);
                     if( err_code != 0 )
                     {
                        err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                        ShowMessage(err_str);
                     }
                  }
             }
         }
      }

      if( CommentList->IndexOf(ComboBox2->Text) == -1 )
      {
         CommentList->Add(ComboBox2->Text);
         CommentList->Sort();

         ComboBox2->Items->Clear();
         for( int i = 0; i < CommentList->Count; i++ )
            ComboBox2->Items->Add(CommentList->Strings[i]);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButton2Click(TObject *Sender)
{
   {
      if( !Table2->IsEmpty() && DBGridEh1->SelectedRows->Count > 0 )
      {
         TDataSet *pDS = DBGridEh1->DataSource->DataSet;
         for( int i=0; i < DBGridEh1->SelectedRows->Count; i++)
         {
            pDS->GotoBookmark((void *)DBGridEh1->SelectedRows->Items[i].c_str());
            Table2->Edit();
            pDS->Fields->Fields[10]->AsString = "";
            Table2->Post();
            Table2->FlushBuffers();

            AnsiString query, err_str;
            int event_num = StrToInt(pDS->Fields->Fields[0]->AsString);
            query.sprintf("UPDATE %s.events SET comment1=\'%s\' WHERE event_num=%d",
                           MySQL_dbname,
                           "",
                           event_num);

             mysql_real_query(Con,query.c_str(),query.Length());
             int err_code = mysql_errno(Con);
             if( err_code != 0 )
             {
                  mysql_close(Con);

                  Con = mysql_init(NULL);
                  mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
                  err_code = mysql_errno(Con);
                  if( err_code != 0 && err_code != CR_ALREADY_CONNECTED )
                  {
                     err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                     ShowMessage(err_str);
                  }
                  else
                  {
                     mysql_real_query(Con,query.c_str(),query.Length());
                     err_code = mysql_errno(Con);
                     if( err_code != 0 )
                     {
                        err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                        ShowMessage(err_str);
                     }
                  }
             }
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButton3Click(TObject *Sender)
{
   if( ComboBox3->Text == "" )
      MessageBox (NULL, MsgStr20.c_str(), ErrorMsg.c_str(), MB_OK|MB_ICONERROR);
   else
   {
      if( !Table2->IsEmpty() && DBGridEh1->SelectedRows->Count > 0 )
      {
         TDataSet *pDS = DBGridEh1->DataSource->DataSet;
         for( int i=0; i < DBGridEh1->SelectedRows->Count; i++)
         {
            pDS->GotoBookmark((void *)DBGridEh1->SelectedRows->Items[i].c_str());

            AnsiString str;
            str = pDS->Fields->Fields[11]->AsString;
            if( str.Length() == 0 )
            {
               Table2->Edit();
               pDS->Fields->Fields[11]->AsString = ComboBox3->Text;
               Table2->Post();
            }
            Table2->FlushBuffers();

            AnsiString query, err_str;
            int event_num = StrToInt(pDS->Fields->Fields[0]->AsString);
            query.sprintf("UPDATE %s.events SET comment2=\'%s\' WHERE comment2=\'\' AND event_num=%d",
                           MySQL_dbname,
                           pDS->Fields->Fields[11]->AsString,
                           event_num);   

             mysql_real_query(Con,query.c_str(),query.Length());
             int err_code = mysql_errno(Con);
             if( err_code != 0 )
             {
                  mysql_close(Con);

                  Con = mysql_init(NULL);
                  mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
                  err_code = mysql_errno(Con);
                  if( err_code != 0 && err_code != CR_ALREADY_CONNECTED )
                  {
                     err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                     ShowMessage(err_str);
                  }
                  else
                  {
                     mysql_real_query(Con,query.c_str(),query.Length());
                     err_code = mysql_errno(Con);
                     if( err_code != 0 )
                     {
                        err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                        ShowMessage(err_str);
                     }
                  }
             }
         }
      }

      if( CommentList2->IndexOf(ComboBox3->Text) == -1 )
      {
         CommentList2->Add(ComboBox3->Text);
         CommentList2->Sort();

         ComboBox3->Items->Clear();
         for( int i = 0; i < CommentList2->Count; i++ )
            ComboBox3->Items->Add(CommentList2->Strings[i]);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SpeedButton4Click(TObject *Sender)
{
   {
      if( !Table2->IsEmpty() && DBGridEh1->SelectedRows->Count > 0 )
      {
         TDataSet *pDS = DBGridEh1->DataSource->DataSet;
         for( int i=0; i < DBGridEh1->SelectedRows->Count; i++)
         {
            pDS->GotoBookmark((void *)DBGridEh1->SelectedRows->Items[i].c_str());
            Table2->Edit();
            pDS->Fields->Fields[11]->AsString = "";
            Table2->Post();
            Table2->FlushBuffers();

            AnsiString query, err_str;
            int event_num = StrToInt(pDS->Fields->Fields[0]->AsString);
            query.sprintf("UPDATE %s.events SET comment2=\'%s\' WHERE event_num=%d",
                           MySQL_dbname,
                           "",
                           event_num);   

             mysql_real_query(Con,query.c_str(),query.Length());
             int err_code = mysql_errno(Con);
             if( err_code != 0 )
             {
                  mysql_close(Con);

                  Con = mysql_init(NULL);
                  mysql_real_connect(Con,MySQL_host.c_str(),MySQL_login.c_str(),MySQL_password.c_str(),MySQL_dbname.c_str(),MySQL_port,NULL,0);
                  err_code = mysql_errno(Con);
                  if( err_code != 0 && err_code != CR_ALREADY_CONNECTED )
                  {
                     err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                     ShowMessage(err_str);
                  }
                  else
                  {
                     mysql_real_query(Con,query.c_str(),query.Length());
                     err_code = mysql_errno(Con);
                     if( err_code != 0 )
                     {
                        err_str.sprintf("%s EVENTS!\n %s:%d\n %s:%s", InfoStr6, InfoStr3, err_code, InfoStr4, mysql_error(Con));
                        ShowMessage(err_str);
                     }
                  }
             }
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N2Click(TObject *Sender)
{
   CommentList->Clear();
   ComboBox2->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N3Click(TObject *Sender)
{
   CommentList2->Clear();
   ComboBox3->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   Table2->DisableControls();
   frxReport1->ShowReport();
   Table2->EnableControls();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
   Table2->DisableControls();
   if( frxReport1->PrepareReport() ) frxReport1->Print();
   Table2->EnableControls();
}
//---------------------------------------------------------------------------
void TMainForm::SelectMyObject()
{
   Label8->Visible = false;
   Label9->Visible = false;
   Label10->Visible = false;

   ComboBox6->Visible = false;
   ComboBox7->Visible = false;
   ComboBox8->Visible = false;

   AnsiString str;

   ComboBox5->Items->Clear();
   ComboBox5->Items->Add(InfoStr9);
   ComboBox5->Items->Add(InfoStr22);
   ComboBox5->Items->Add(InfoStr23);
   ComboBox5->Items->Add(InfoStr24);
   ComboBox5->ItemIndex = 0;

   Label11->Visible = false;
   ComboBox9->ItemIndex = 0;
   ComboBox9->Visible = false;

   if( ComboBox4->Text == InfoStr10 )
   {
      Label8->Caption = MsgStr27;
      Label8->Visible = true;
      ComboBox6->Items->Clear();
      ComboBox6->Items->Add(InfoStr9);
      for( int ch = 0; ch < 4; ch++ )
      {
         str.sprintf("%d", ch+1);
         ComboBox6->Items->Add(str);
      }
      ComboBox6->ItemIndex = 0;
      ComboBox6->Visible = true;

      Label9->Caption = MsgStr28;
      Label9->Visible = true;
      ComboBox7->Items->Clear();
      ComboBox7->Items->Add(InfoStr9);
      for( int bl = 0; bl < 15; bl++ )
      {
         str.sprintf("%02d", bl+1);
         ComboBox7->Items->Add(str);
      }
      ComboBox7->ItemIndex = 0;
      ComboBox7->Visible = true;

      Label10->Caption = MsgStr29;
      Label10->Visible = true;
      ComboBox8->Items->Clear();
      ComboBox8->Items->Add(InfoStr9);
      for( int sd = 0; sd < 8; sd++ )
      {
         str.sprintf("%d", sd+1);
         ComboBox8->Items->Add(str);
      }
      ComboBox8->Items->Add(MsgStr32);
      ComboBox8->ItemIndex = 0;
      ComboBox8->Visible = true;

      Label11->Visible = true;
      ComboBox9->ItemIndex = 0;
      ComboBox9->Visible = true;

      ComboBox5->Items->Clear();
      ComboBox5->Items->Add(InfoStr9);    
      ComboBox5->Items->Add(InfoStr22);   
      str = "- " + Table1Str8;
      ComboBox5->Items->Add(str);         
      str = "- " + Table1Str9;
      ComboBox5->Items->Add(str);         
      ComboBox5->Items->Add(InfoStr23);   
      str = "- " + Table1Str5;
      ComboBox5->Items->Add(str);         
      str = "- " + Table1Str6;
      ComboBox5->Items->Add(str);         
      ComboBox5->Items->Add(InfoStr24);   
      str = "- " + DkItemCaption;
      ComboBox5->Items->Add(str);         
      str = "- " + Bazalt_pdiCaption;
      ComboBox5->Items->Add(str);         
      str = "- " + MsgStr23;
      ComboBox5->Items->Add(str);         
      ComboBox5->ItemIndex = 0;
   }
   else if( ComboBox4->Text == InfoStr11 )
   {
      Label8->Caption = MsgStr27;
      Label8->Visible = true;
      ComboBox6->Items->Clear();
      ComboBox6->Items->Add(InfoStr9);
      for( int ch = 0; ch < 4; ch++ )
      {
         str.sprintf("%d", ch+1);
         ComboBox6->Items->Add(str);
      }
      ComboBox6->ItemIndex = 0;
      ComboBox6->Visible = true;

      Label9->Caption = MsgStr28;
      Label9->Visible = true;
      ComboBox7->Items->Clear();
      ComboBox7->Items->Add(InfoStr9);
      for( int bl = 0; bl < 15; bl++ )
      {
         str.sprintf("%02d", bl+1);
         ComboBox7->Items->Add(str);
      }
      ComboBox7->ItemIndex = 0;
      ComboBox7->Visible = true;

      Label10->Caption = MsgStr30;
      Label10->Visible = true;
      ComboBox8->Items->Clear();
      ComboBox8->Items->Add(InfoStr9);
      for( int iu = 0; iu < 3; iu++ )
      {
         str.sprintf("%d", iu+1);
         ComboBox8->Items->Add(str);
      }
      ComboBox8->ItemIndex = 0;
      ComboBox8->Visible = true;

      ComboBox5->Items->Clear();
      ComboBox5->Items->Add(InfoStr9);   
      ComboBox5->Items->Add(InfoStr23);  
      str = "- " + Table1Str5;
      ComboBox5->Items->Add(str);        
      str = "- " + Table1Str7;
      ComboBox5->Items->Add(str);        
      ComboBox5->Items->Add(InfoStr24);  
      ComboBox5->ItemIndex = 0;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ComboBox4Click(TObject *Sender)
{
   SelectMyObject();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ComboBox4KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   ComboBox4Click(this);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DBGridEh1DrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
   if( State.Contains(gdSelected) || DBGridEh1->SelectedRows->CurrentRowSelected )
   {
      DBGridEh1->Canvas->Brush->Color=clSkyBlue;
      DBGridEh1->Canvas->Font->Color=clWindowText;
      DBGridEh1->Canvas->FillRect(Rect);
      DBGridEh1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
   }

   if( Table2Etype->AsInteger >= 20 && Table2Etype->AsInteger < 30 || Table2Etype->AsInteger == 145 )
   {
      DBGridEh1->Canvas->Font->Color=clRed;
      DBGridEh1->Canvas->FillRect(Rect);
      DBGridEh1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
   }
   else if( Table2Etype->AsInteger > 200 && Table2Etype->AsInteger < 300 )
   {
      DBGridEh1->Canvas->Font->Color=clRed;
      DBGridEh1->Canvas->FillRect(Rect);
      DBGridEh1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
   }
   else if( Table2Etype->AsInteger == 5 ||
            Table2Etype->AsInteger == 3 ||
            Table2Etype->AsInteger == 4 ||
            Table2Etype->AsInteger == 130 ||
            Table2Etype->AsInteger == 131 ||
            Table2Etype->AsInteger == 133 ||
            Table2Etype->AsInteger == 134 ||
            Table2Etype->AsInteger == 135 ||
            Table2Etype->AsInteger == 136 ||
            Table2Etype->AsInteger == 137 ||
            Table2Etype->AsInteger == 138 ||
            Table2Etype->AsInteger == 140 ||
            Table2Etype->AsInteger == 141 ||
            Table2Etype->AsInteger == 142 ||
            Table2Etype->AsInteger == 143 ||
            Table2Etype->AsInteger == 144 ||
            Table2Etype->AsInteger == 150 ||
            Table2Etype->AsInteger == 151 ||
            Table2Etype->AsInteger == 160 ||
            Table2Etype->AsInteger == 161 ||
            Table2Etype->AsInteger == 170 ||
            Table2Etype->AsInteger == 171 ||
            Table2Etype->AsInteger == 172 ||
            Table2Etype->AsInteger == 173 ||
            Table2Etype->AsInteger == 174 ||
            Table2Etype->AsInteger == 175 ||
            Table2Etype->AsInteger == 900 ||
            Table2Etype->AsInteger == 901 ||
            Table2Etype->AsInteger == 903 ||
            Table2Etype->AsInteger == 1000 ||
            Table2Etype->AsInteger == 1001 ||
            Table2Etype->AsInteger == 1002 )
   {
      DBGridEh1->Canvas->Font->Color=clGreen;
      DBGridEh1->Canvas->FillRect(Rect);
      DBGridEh1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
   }
   else if( (Table2Etype->AsInteger == 11 && Table2Dtype->AsInteger != 14 && Table2Dtype->AsInteger != 17) ||
             Table2Etype->AsInteger == 12 ||
             Table2Etype->AsInteger == 13 ||
             Table2Etype->AsInteger == 15 ||
             Table2Etype->AsInteger == 16 ||
             Table2Etype->AsInteger == 18 ||
             Table2Etype->AsInteger == 30 ||
             Table2Etype->AsInteger == 31 ||
             Table2Etype->AsInteger == 201 ||
             Table2Etype->AsInteger == 202 ||
             Table2Etype->AsInteger == 203 ||
             Table2Etype->AsInteger == 204 ||
             Table2Etype->AsInteger == 211 ||
             Table2Etype->AsInteger == 212 ||
             Table2Etype->AsInteger == 213 ||
             Table2Etype->AsInteger == 214 ||
             Table2Etype->AsInteger == 221 ||
             Table2Etype->AsInteger == 222 ||
             Table2Etype->AsInteger == 223 ||
             Table2Etype->AsInteger == 224 ||
             Table2Etype->AsInteger == 231 ||
             Table2Etype->AsInteger == 232 ||
             Table2Etype->AsInteger == 241 ||
             Table2Etype->AsInteger == 242 ||
             Table2Etype->AsInteger == 251 ||
             Table2Etype->AsInteger == 252 )
   {
      DBGridEh1->Canvas->Font->Color=clBlue;
      DBGridEh1->Canvas->FillRect(Rect);
      DBGridEh1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
   }
   else if( Table2Etype->AsInteger == 10 || Table2Etype->AsInteger == 200 )
   {
      DBGridEh1->Canvas->Font->Color=(TColor)RGB(255,93,0);
      DBGridEh1->Canvas->FillRect(Rect);
      DBGridEh1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::KeepAliveTimerTimer(TObject *Sender)
{
   AnsiString str;
   if( iServerUse )
   {
       if( iServer->Active )
       {
          for( int i = 0; i < iServer->Socket->ActiveConnections; i++ )
          for( int j = 0; j < NetClientMaxCnt; j++ )
          {
             if( iNetSys->iNetClient[j].IsExist(iServer->Socket->Connections[i]->SocketHandle) )
             {
                if( iNetSys->iNetClient[j].KeepAliveCnt < (iKeepAlive-1) )
                {
                   iNetSys->iNetClient[j].KeepAliveCnt += 1;

                   if( iNetSys->iNetClient[j].EventsAndStates )
                   {
                      if( EventsAndStates->Count > 0 )
                      {
                         if( EventsAndStates->Strings[0] != "<RIFPlusPacket type=\"EventBook\">" )
                         {
                             if( EventsAndStates->Strings[0] != "<RIFPlusPacket type=\"EventsAndStates\">" )
                             {
                                EventsAndStates->Insert(0, "<RIFPlusPacket type=\"EventsAndStates\">");
                                EventsAndStates->Insert(1, "<devices>");
                             }
                             if( EventsAndStates->Strings[EventsAndStates->Count-2] != "</devices>" )
                             {
                                EventsAndStates->Add("</devices>");
                                EventsAndStates->Add("</RIFPlusPacket>");
                             }
                         }

                         iServer->Socket->Connections[i]->SendBuf(EventsAndStates->Text.c_str(),EventsAndStates->Text.Length());
                      }
                   }
                }
                else
                {
                   iServer->Socket->Connections[i]->Close();
                   iNetSys->iNetClient[j].Reset();
                }

                break;
             }
          }

          EventsAndStates->Clear();


          str = "iServer: " + iServerHost + ":" + IntToStr(iServerPort) +  " Клиентов: " + iServer->Socket->ActiveConnections;
          StatusBar1->Panels->Items[0]->Text = str;
       }
       else
       {
          str = "iServer: -";
          if( StatusBar1->Panels->Items[0]->Text != str ) StatusBar1->Panels->Items[0]->Text = str;

          iNetSys->Reset();

          iServer->Socket->Close();
          iServer->Active = false;
          iServer->Active = true;
       }
   }
   else
   {
      str = "iServer: -";
      if( StatusBar1->Panels->Items[0]->Text != str ) StatusBar1->Panels->Items[0]->Text = str;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::iServerClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   for( int i = 0; i < NetClientMaxCnt; i++ )
   {
      if( iNetSys->iNetClient[i].IsEmpty() )
      {
         iNetSys->iNetClient[i].Set(Socket->SocketHandle);
         iNetSys->iNetClient[i].KeepAliveCnt = 0;
         iNetSys->iNetClient[i].EventsAndStates = true;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::iServerClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   for( int j = 0; j < NetClientMaxCnt; j++ )
   {
      if( iNetSys->iNetClient[j].IsExist(Socket->SocketHandle) )
      {
         iNetSys->iNetClient[j].Reset();
         iNetSys->iNetClient[j].KeepAliveCnt = 0;
         iNetSys->iNetClient[j].EventsAndStates = false;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::iServerClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
   try
   {
      ErrorCode = 0;
      iServer->Socket->Close();
      iServer->Active = false;
   }
   catch(...)
   {
      ;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::iServerClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
   int length = Socket->ReceiveLength();

   char *Buf;
   Buf = new char [length];
   memset(Buf,0,length);

   length = Socket->ReceiveBuf(Buf,length);

   for( int i = 0; i < length-8; i++ )
   {
      if( toupper(Buf[i]) == toupper('k') &&
          toupper(Buf[i+1]) == toupper('e') &&
          toupper(Buf[i+2]) == toupper('e') &&
          toupper(Buf[i+3]) == toupper('p') &&
          toupper(Buf[i+4]) == toupper('a') &&
          toupper(Buf[i+5]) == toupper('l') &&
          toupper(Buf[i+6]) == toupper('i') &&
          toupper(Buf[i+7]) == toupper('v') &&
          toupper(Buf[i+8]) == toupper('e') )
      {
         for( int j = 0; j < NetClientMaxCnt; j++ )
         {
            if( iNetSys->iNetClient[j].IsExist(Socket->SocketHandle) )
            {
               iNetSys->iNetClient[j].KeepAliveCnt = 0;
               break;
            }
         }
      }
   }
}
//---------------------------------------------------------------------------

