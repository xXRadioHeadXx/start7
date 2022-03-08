//----------------------------------------------------------------------------
#ifndef About485DlgUnitH
#define About485DlgUnitH
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
#include <jpeg.hpp>
#include <Menus.hpp>
//----------------------------------------------------------------------------
class TAbout485Dlg : public TForm
{
__published:
   TLabel *Label1;
   TLabel *Label2;
   void __fastcall FormCreate(TObject *Sender);
private:
public:
	virtual __fastcall TAbout485Dlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAbout485Dlg *About485Dlg;
//----------------------------------------------------------------------------
#endif    
