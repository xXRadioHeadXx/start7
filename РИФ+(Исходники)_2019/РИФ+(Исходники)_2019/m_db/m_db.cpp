//---------------------------------------------------------------------------
#include <vcl.h>
#include <IniFiles.hpp>
#include "MyApiUnit.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainUnit.cpp", MainForm);
USEFORM("MySQLDlgUnit.cpp", MySQLDlg);
USEFORM("WriteFormUnit.cpp", ReadForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   TMemIniFile *ini;
   ini = new TMemIniFile( ExtractFilePath(Application->ExeName)+"lang1.ini" );

   AnsiString str1 = ini->ReadString( "APP", "MsgStr1", "Программа уже запущена!" );
   AnsiString wrnstr = ini->ReadString( "MSGSTRING", "WarningMsg", "Предупреждение" );

   delete ini;

   if ( WeAreAlone ("RIFx_MDB_by_Start7") )
   {
       try
       {
           Application->Initialize();
           Application->CreateForm(__classid(TMainForm), &MainForm);
       Application->Run();
       }
       catch (Exception &exception)
       {
           Application->ShowException(&exception);
       }
       catch (...)
       {
           try
           {
              throw Exception("");
           }
           catch (Exception &exception)
           {
              Application->ShowException(&exception);
           }
       }
   }
   else MessageBox( NULL, str1.c_str(), wrnstr.c_str(), MB_OK|MB_ICONWARNING );

   return 0;
}
//---------------------------------------------------------------------------
