//----------------------------------------------------------------------------
#ifndef OperatorsDlgUnitH
#define OperatorsDlgUnitH
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
#include <Mask.hpp>
//----------------------------------------------------------------------------
class TOperatorsDlg : public TForm
{
__published:        
	TButton *OKBtn;
	TBevel *Bevel1;
   TLabel *Label1;
   TComboBox *ComboBox1;
   TLabel *Label2;
   TMaskEdit *MaskEdit1;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
	virtual __fastcall TOperatorsDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOperatorsDlg *OperatorsDlg;
//----------------------------------------------------------------------------
#endif    
