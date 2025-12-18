//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_MessageBox *Form_MessageBox;
//---------------------------------------------------------------------------
__fastcall TForm_MessageBox::TForm_MessageBox(TComponent* Owner)
	: TForm(Owner)
{
    stage = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm_MessageBox::DisplayErrorMessage(int nStage, AnsiString title, AnsiString msg)
{
    stage = nStage;
    title = title + " - STAGE #" + IntToStr(nStage + 1);
    lblTitle->Caption = title;
    lblMsg->Caption = msg;
	if(!this->Visible)
	{
		Timer_BringToFront->Enabled = true;

		this->Position = poMainFormCenter;
		this->BringToFront();
		this->Show();
	}
	else this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_MessageBox::Timer_BringToFrontTimer(TObject *Sender)
{
    this->BringToFront();
}
//---------------------------------------------------------------------------
