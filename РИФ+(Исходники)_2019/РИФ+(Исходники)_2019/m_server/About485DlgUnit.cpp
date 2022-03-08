//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About485DlgUnit.h"
#include "MainUnit_.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAbout485Dlg *About485Dlg;
//---------------------------------------------------------------------
__fastcall TAbout485Dlg::TAbout485Dlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAbout485Dlg::FormCreate(TObject *Sender)
{
      Label1->Caption = "–»‘+";
}
//---------------------------------------------------------------------------

