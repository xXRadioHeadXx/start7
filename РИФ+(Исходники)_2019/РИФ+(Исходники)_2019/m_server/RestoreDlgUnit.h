//----------------------------------------------------------------------------
#ifndef RestoreDlgUnitH
#define RestoreDlgUnitH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Dialogs.hpp>
//----------------------------------------------------------------------------
class TRestoreDlg : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
   TEdit *Edit1;
   TLabel *Label1;
   TButton *Button1;
   TOpenDialog *OpenDialog1;
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall OKBtnClick(TObject *Sender);
private:
public:
	virtual __fastcall TRestoreDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TRestoreDlg *RestoreDlg;
//----------------------------------------------------------------------------
#endif    
