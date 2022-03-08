//---------------------------------------------------------------------------
#ifndef WriteFormUnitH
#define WriteFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TReadForm : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
private:	// User declarations
public:		// User declarations
   __fastcall TReadForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReadForm *ReadForm;
//---------------------------------------------------------------------------
#endif
