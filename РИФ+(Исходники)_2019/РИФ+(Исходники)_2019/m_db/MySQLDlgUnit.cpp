//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MySQLDlgUnit.h"
#include "MainUnit.h"
//---------------------------------------------------------------------
#pragma link "CSPIN"
#pragma resource "*.dfm"
TMySQLDlg *MySQLDlg;
//---------------------------------------------------------------------
__fastcall TMySQLDlg::TMySQLDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TMySQLDlg::FormCreate(TObject *Sender)
{
   Caption = MainForm->MySQLConnectItem->Caption;
   Label1->Caption = MainForm->InfoStr25;
   Label2->Caption = MainForm->InfoStr26;
   Label3->Caption = MainForm->InfoStr27;
   Label4->Caption = MainForm->InfoStr28;
   Label5->Caption = MainForm->InfoStr29;

   Edit1->Text = MainForm->MySQL_host;
   CSpinEdit1->Value = MainForm->MySQL_port;
   Edit2->Text = MainForm->MySQL_dbname;
   Edit3->Text = MainForm->MySQL_login;
   Edit4->Text = MainForm->MySQL_password;
}
//---------------------------------------------------------------------------
void __fastcall TMySQLDlg::Button1Click(TObject *Sender)
{
   MainForm->MySQL_host = Edit1->Text;
   MainForm->MySQL_port = CSpinEdit1->Value;
   MainForm->MySQL_dbname = Edit2->Text;
   MainForm->MySQL_login = Edit3->Text;
   MainForm->MySQL_password = Edit4->Text;

   MainForm->Connect = true;
}
//---------------------------------------------------------------------------

