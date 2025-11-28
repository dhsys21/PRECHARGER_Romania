//---------------------------------------------------------------------------

#ifndef FormErrorSetH
#define FormErrorSetH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_ErrorSet : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label_Title;
	TStaticText *Label_Msg1;
	TButton *btnOK;
	TTimer *Timer_BringToFront;
	TTimer *timerErrorOff;
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall Timer_BringToFrontTimer(TObject *Sender);
	void __fastcall timerErrorOffTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_ErrorSet(TComponent* Owner);
    void __fastcall ChangeMessage(UnicodeString msg1);
    void __fastcall DisplayErrorMessage(int nStage);
    void __fastcall SaveErrorLog(int nStage, AnsiString msg1);
    int stage;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_ErrorSet *Form_ErrorSet;
//---------------------------------------------------------------------------
#endif
