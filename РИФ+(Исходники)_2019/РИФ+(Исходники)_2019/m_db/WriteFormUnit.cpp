//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "WriteFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TReadForm *ReadForm;
//---------------------------------------------------------------------------
__fastcall TReadForm::TReadForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
