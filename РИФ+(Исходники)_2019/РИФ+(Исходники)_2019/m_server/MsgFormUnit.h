//---------------------------------------------------------------------------

#ifndef MsgFormUnitH
#define MsgFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TMsgForm : public TForm
{
__published:	// IDE-managed Components
   TButton *Button1;
   TStaticText *StaticText1;
   TStaticText *StaticText2;
   void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMsgForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMsgForm *MsgForm;
//---------------------------------------------------------------------------
#endif
