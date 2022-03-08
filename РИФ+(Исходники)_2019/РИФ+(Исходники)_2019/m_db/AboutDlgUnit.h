//----------------------------------------------------------------------------
#ifndef AboutDlgUnitH
#define AboutDlgUnitH
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
//----------------------------------------------------------------------------
class TAboutDlg : public TForm
{
__published:        
	TButton *OKBtn;
	TBevel *Bevel1;
   TStaticText *StaticText1;
   TStaticText *StaticText2;
   void __fastcall FormCreate(TObject *Sender);
private:
public:
	virtual __fastcall TAboutDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutDlg *AboutDlg;
//----------------------------------------------------------------------------
#endif    
