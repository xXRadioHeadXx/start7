//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AboutDlgUnit.h"
#include "MainUnit_.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutDlg *AboutDlg;
//---------------------------------------------------------------------
__fastcall TAboutDlg::TAboutDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutDlg::FormCreate(TObject *Sender)
{
   Caption = MainForm->AboutItem->Caption;

   if( MainForm->ComplexVersion == SsoiComplexType )
      StaticText1->Caption = MainForm->AboutDlgStr1;
   else if( MainForm->ComplexVersion == Rastr_M_SsoiComplexType )
      StaticText1->Caption = MainForm->AboutDlgStr2;
   else
      StaticText1->Caption = MainForm->AboutDlgStr3;

   StaticText2->Caption = MainForm->VersionInfoStr;
}
//---------------------------------------------------------------------------

