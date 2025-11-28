//---------------------------------------------------------------------------

#ifndef FormPLCInterfaceH
#define FormPLCInterfaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "AdvSmoothButton.hpp"
#include "AdvSmoothPanel.hpp"
//---------------------------------------------------------------------------
class TForm_PLCInterface : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox2;
	TListView *ListView_PC;
	TListView *ListView_PLC;
	TTimer *Timer_Update;
	TAdvSmoothPanel *Panel1;
	TAdvSmoothButton *AdvSmoothButton9;
	TPanel *Panel30;
	TPanel *Panel32;
	TEdit *Edit6;
	TEdit *Edit7;
	TLabel *Label1;
	TGroupBox *GroupBox4;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *cbAddress;
	TEdit *editValue;
	TButton *btnWriteValue;
	TButton *Button1;
	TGroupBox *GroupBox1;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *editVoltage;
	TEdit *editCurrent;
	TButton *btnWriteIrOcvValue;
	TGroupBox *GroupBox3;
	TEdit *editIrOcvNg;
	TButton *btnWriteNgValue;
	TListView *ListView_PC2;
	TListView *ListView_PLC2;
	TLabel *Label4;
	TComboBox *cbStageNo;
	void __fastcall Timer_UpdateTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall GroupBox2Click(TObject *Sender);
	void __fastcall btnWriteValueClick(TObject *Sender);
	void __fastcall btnWriteNgValueClick(TObject *Sender);
	void __fastcall btnWriteIrOcvValueClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	void __fastcall SetListViewPLC(int nTag);
	void __fastcall SetListViewPC(int nTag);
	void __fastcall SetListViewPLC2();
	void __fastcall SetListViewPC2();

	void __fastcall AddListView(TListView *list, AnsiString address, AnsiString name);
	double auto_manual_plc[CONTCOUNT], auto_manual_plc_old[CONTCOUNT];

    TListItem *tempListItem;
public:		// User declarations
	__fastcall TForm_PLCInterface(TComponent* Owner);
	TListView *nListView_PLC[CONTCOUNT];
	TListView *nListView_PC[CONTCOUNT];
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_PLCInterface *Form_PLCInterface;
//---------------------------------------------------------------------------
#endif
