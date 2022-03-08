//---------------------------------------------------------------------------
#include <vcl.h>
#include <IniFiles.hpp>
#include "MyApiUnit.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("WriteFormUnit.cpp", ReadForm);
USEFORM("MainUnit_.cpp", MainForm);
USEFORM("OperatorsDlgUnit.cpp", OperatorsDlg);
USEFORM("..\..\M_db\Src\AboutDlgUnit.cpp", AboutDlg);
USEFORM("MsgFormUnit.cpp", MsgForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   TMemIniFile *ini;
   ini = new TMemIniFile( ExtractFilePath(Application->ExeName)+"lang1.ini" );

   AnsiString str1 = ini->ReadString( "APP", "MsgStr1", "Программа уже запущена!" );
   AnsiString str2 = ini->ReadString( "APP", "MsgStr2", "Для работы программы необходимо завершить работу модуля \"Клиент\"!" );
   AnsiString str3 = ini->ReadString( "APP", "MsgStr3", "Для работы программы необходимо завершить работу модуля \"Сервер\"!" );
   AnsiString str4 = ini->ReadString( "APP", "MsgStr4", "Для работы программы необходимо завершить работу модуля \"Настройка\"!" );
   AnsiString str5 = ini->ReadString( "APP", "MsgStr5", "Для работы программы необходимо завершить работу модуля \"Настройка изделий\"!" );
   AnsiString wrnstr = ini->ReadString( "MSGSTRING", "WarningMsg", "Предупреждение" );

   delete ini;

   if( WeAreAlone ("RIFx_Mserver_by_Start7") )
   {
      if( WeAreAlone1("RIFx_Mcfg_by_Start7") )
      {
         if( WeAreAlone1("RIFx_Tmprog_by_Start7") )
         {
              try
              {
                  Application->Initialize();
                  Application->Title = "Server";
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
         else Application->MessageBoxA(str5.c_str(), wrnstr.c_str(), 0);
      }
      else Application->MessageBoxA(str4.c_str(), wrnstr.c_str(), 0);
   }
   else MessageBox( NULL, str1.c_str(), wrnstr.c_str(), MB_OK|MB_ICONWARNING );

   return 0;
}
//---------------------------------------------------------------------------
