//---------------------------------------------------------------------
#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop

#include "RestoreDlgUnit.h"
#include "MainUnit_.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TRestoreDlg *RestoreDlg;
//---------------------------------------------------------------------
__fastcall TRestoreDlg::TRestoreDlg(TComponent* AOwner)
	: TForm(AOwner)
{
   OpenDialog1->InitialDir = ExtractFilePath(Application->ExeName);

   try
   {
      AnsiString str;
      if( FileExists(ExtractFilePath(Application->ExeName)+"rifx.ini") )
      {
         TMemIniFile *ini;
         ini = new TMemIniFile( ExtractFilePath(Application->ExeName)+"rifx.ini" );
         str = ini->ReadString( "BACKUP", "Path", "" );
         delete ini;

         if( str == "" ) str = ExtractFilePath(Application->ExeName) + "_BACKUP\\";
         else str = str + "\\";
      }
      if( DirectoryExists( str ) ) OpenDialog1->InitialDir = str;
   }
   catch(...)
   {
      ;
   }
}
//---------------------------------------------------------------------
void __fastcall TRestoreDlg::Button1Click(TObject *Sender)
{
   if( OpenDialog1->Execute() )
   {
      if( FileExists(OpenDialog1->FileName) )
      {
         Edit1->Text = OpenDialog1->FileName;
         OKBtn->Enabled = true;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TRestoreDlg::OKBtnClick(TObject *Sender)
{
   if( FileExists(Edit1->Text) ) MainForm->RestoreFileName = Edit1->Text;
}
//---------------------------------------------------------------------------

