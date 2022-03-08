//----------------------------------------------------------------------------
#ifndef MySQLDlgUnitH
#define MySQLDlgUnitH
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
#include "CSPIN.h"
//----------------------------------------------------------------------------
class TMySQLDlg : public TForm
{
__published:
	TButton *CancelBtn;
	TBevel *Bevel1;
   TLabel *Label1;
   TEdit *Edit1;
   TLabel *Label2;
   TCSpinEdit *CSpinEdit1;
   TLabel *Label3;
   TEdit *Edit2;
   TLabel *Label4;
   TEdit *Edit3;
   TLabel *Label5;
   TEdit *Edit4;
   TButton *Button1;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
private:
public:
	virtual __fastcall TMySQLDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TMySQLDlg *MySQLDlg;
//----------------------------------------------------------------------------
#endif    
