//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MsgFormUnit.h"
#include "MainUnit_.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMsgForm *MsgForm;
//---------------------------------------------------------------------------
__fastcall TMsgForm::TMsgForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMsgForm::Button1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

