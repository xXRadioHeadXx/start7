//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OperatorsDlgUnit.h"
#include "MainUnit_.h"
#include "MyApiUnit.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TOperatorsDlg *OperatorsDlg;
//---------------------------------------------------------------------
__fastcall TOperatorsDlg::TOperatorsDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TOperatorsDlg::FormCreate(TObject *Sender)
{
   Caption = MainForm->OperatorsDlgCaption;
   Label1->Caption = MainForm->OperatorsDlgLabel1Caption;
   Label2->Caption = MainForm->OperatorsDlgLabel2Caption;

   ComboBox1->Items->Clear();

   AnsiString str;

   MainForm->OpList->Sort();
   for( int i = 0; i < MainForm->OpList->OpCnt; i++ )
   {
      str.sprintf("%s", MainForm->OpList->Op[i].FamilyName );
      if( MainForm->OpList->Op[i].FirstName != "(null)" )
         str = str + " " + MainForm->OpList->Op[i].FirstName;
      if( MainForm->OpList->Op[i].SecondName != "(null)" )
         str = str + " " + MainForm->OpList->Op[i].SecondName;

      ComboBox1->Items->Add(str);
   }
   ComboBox1->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TOperatorsDlg::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   if( MainForm->OpList->Op[ComboBox1->ItemIndex].Password == XOR_Crypt(MaskEdit1->Text,"start7") )
   {
      MainForm->OpFn = MainForm->OpList->Op[ComboBox1->ItemIndex].FamilyName;
      MainForm->OpN1 = MainForm->OpList->Op[ComboBox1->ItemIndex].FirstName;
      MainForm->OpN2 = MainForm->OpList->Op[ComboBox1->ItemIndex].SecondName;
   }
   else
   {
      MainForm->OpFn = "";
   }
}
//---------------------------------------------------------------------------


