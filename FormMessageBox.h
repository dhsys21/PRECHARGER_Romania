//---------------------------------------------------------------------------

#ifndef FormMessageBoxH
#define FormMessageBoxH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_MessageBox : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel26;
	TLabel *lblMsg;
	TButton *btnNo;
	TButton *btnYes;
	TLabel *lblTitle;
	TTimer *Timer_BringToFront;
	TPanel *Panel1;
	void __fastcall Timer_BringToFrontTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_MessageBox(TComponent* Owner);
    int stage;
    void __fastcall DisplayErrorMessage(int nStage, AnsiString title, AnsiString msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_MessageBox *Form_MessageBox;
//---------------------------------------------------------------------------
#endif
