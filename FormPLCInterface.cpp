#pragma link "AdvSmoothPanel"
#pragma link "AdvSmoothButton"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_PLCInterface *Form_PLCInterface;
//---------------------------------------------------------------------------
__fastcall TForm_PLCInterface::TForm_PLCInterface(TComponent* Owner)
	: TForm(Owner)
{
	nListView_PLC[0] = ListView_PLC;
	nListView_PC[0] = ListView_PC;
    nListView_PLC[1] = ListView_PLC2;
	nListView_PC[1] = ListView_PC2;

	for(int i = 0; i < CONTCOUNT; i++){
		SetListViewPLC(i);
		SetListViewPC(i);
	}

	for(int nIndex = 0; nIndex < CONTCOUNT; nIndex++){
		auto_manual_plc[nIndex] = 0;
		auto_manual_plc_old[nIndex] = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::SetListViewPLC(int nTag)
{
	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_HEART_BEAT), "PLC HEART BEAT #" + IntToStr(nTag + 1));
	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_AUTO_MANUAL), "PLC MANUAL/AUTO #" + IntToStr(nTag + 1));
	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_ERROR), "PLC ERROR #" + IntToStr(nTag + 1));

	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_TRAY_IN), "TRAY IN #" + IntToStr(nTag + 1));
	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_PROB_OPEN), "PROB OPEN #" + IntToStr(nTag + 1));
	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_PROB_CLOSE), "PROB CLOSE #" + IntToStr(nTag + 1));
    AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_BCR_EVENT), "BCR EVENT #" + IntToStr(nTag + 1));

	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_TRAY_ID), "TRAY ID #" + IntToStr(nTag + 1));

    //* Cell Serial Data
//    AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_CELL_SERIAL_START), "CELL SERIAL WRITE START");
//	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_CELL_SERIAL_COMP), "CELL SERIAL WRITE COMPLETE");
//	AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_CELL_SERIAL_COUNT), "CELL SERIAL COUNT");

	// CELL INFO => 1 : YES, 0 : NO
	for(int i = 0; i < MAXCHANNEL; i++)
	{
		AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_INTERFACE_START_DEV_NUM[nTag] + PLC_D_PRE_TRAY_CELL_DATA + i), "TRAY CELL DATA #" + IntToStr(i + 1));
	}

    //* CELL SERIAL DATA
//    for(int i = 0; i < 20; i++)
//       AddListView(nListView_PLC[nTag], "D" + IntToStr(PLC_D_CELL_SERIAL_NUM + PLC_D_PRE_CELL_SERIAL + (i * 10 * 20)), "CELL SERIAL #" + IntToStr(i * 20 + 1));
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::SetListViewPC(int nTag)
{
    // PC - PRE CHARGER
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_HEART_BEAT), "PC HEART BEAT #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_STAGE_AUTO_READY), "STAGE AUTO READY #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_ERROR), "PC ERROR #" + IntToStr(nTag + 1));

	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_TRAY_OUT), "TRAY OUT #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_PROB_OPEN), "PROB OPEN #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_PROB_CLOSE), "PROB CLOSE #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CHARGING), "CHARGING #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_NG_COUNT), "NG COUNT #" + IntToStr(nTag + 1));
    AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_NG_ALARM), "NG ALARM #" + IntToStr(nTag + 1));

	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CURRENT_MIN), "CURRENT MIN. VALUE #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CHARGE_VOLTAGE), "CHARGE VOLTAGE #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CHARGE_CURRENT), "CHARGE CURRENT #" + IntToStr(nTag + 1));
	AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CHARGE_TIME), "CHARGE TIME #" + IntToStr(nTag + 1));

    // CELL SERIAL
//    AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CELL_SERIAL_START), "CELL SERIAL READ START");
//    AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CELL_SERIAL_COMP), "CELL SERIAL READ COMPLETE");
//    AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_CELLID_BYPASS), "CELL ID BYPASS");

	// PRECHARGE RESULT OK/NG => 1 : NG, 0 : OK or NO CELL
	for(int i = 0; i < 25; i++)
		AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_START_DEV_NUM[nTag] + PC_D_PRE_MEASURE_OK_NG + i), "PRECHARGE OK/NG #" + IntToStr(i + 1));

    for(int i = 0; i < 20; i++)
		AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_VOLTAGE[nTag] + PC_D_PRE_VOLTAGE_VALUE + (i * 2 * 20)), "PRECHARGE VOLTAGE #" + IntToStr(i * 20 + 1));

	for(int i = 0; i < 20; i++)
		AddListView(nListView_PC[nTag], "D" + IntToStr(PC_D_INTERFACE_CURRENT[nTag] + PC_D_PRE_CURRENT_VALUE + (i * 2 * 20)), "PRECHARGE CURRENT #" + IntToStr(i * 20 + 1));
}//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::AddListView(TListView *list, AnsiString address, AnsiString name)
{
	tempListItem = list->Items->Add();
	tempListItem->Caption = address;
	tempListItem->SubItems->Add(name);
	tempListItem->SubItems->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::FormShow(TObject *Sender)
{
	Timer_Update->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer_Update->Enabled = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::Timer_UpdateTimer(TObject *Sender)
{
	int index;
	if(Mod_PLC->ClientSocket_PLC->Active)	//	PLC 상태
	{
		for(int nTag = 0; nTag < BaseForm->FormCnt; nTag++){
			index = 0;
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_HEART_BEAT);
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_AUTO_MANUAL);
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_ERROR);

			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_TRAY_IN);
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_PROB_OPEN);
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_PROB_CLOSE);
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_BCR_EVENT);
			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetString(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_TRAY_ID, 10);

            //* CELL SERIAL
//            nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetPlcValue(nTag, PLC_D_PRE_CELL_SERIAL_START);
//			nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetPlcValue(nTag, PLC_D_PRE_CELL_SERIAL_COMP);
//            nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetPlcValue(nTag, PLC_D_PRE_CELL_SERIAL_COUNT);

			for(int i = 0; i < MAXCHANNEL; i++)
			{
				nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetDouble(Mod_PLC->plc_Interface_Data[nTag], PLC_D_PRE_TRAY_CELL_DATA + i);
			}

			//* CELL SERIAL
//			int serialIndex = 0;
//            nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetCellSrialTrayId(nTag, PLC_D_PRE_CELL_SERIAL_TRAYID, 10);
//			for(int i = 0; i < 20; i++){
//				serialIndex = i * 20;
//				nListView_PLC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetCellSrial(nTag, PLC_D_PRE_CELL_SERIAL, serialIndex, 10);
//			}
		}
	}

	if(Mod_PLC->ClientSocket_PC->Active)	//	PC 상태
	{
		for(int nTag =0; nTag < CONTCOUNT; nTag++)
		{
			index = 0;
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_HEART_BEAT);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_STAGE_AUTO_READY);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_ERROR);

			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_TRAY_OUT);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_PROB_OPEN);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_PROB_CLOSE);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CHARGING);
            nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_NG_COUNT);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_NG_ALARM);

			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CURRENT_MIN);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CHARGE_VOLTAGE);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CHARGE_CURRENT);
			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CHARGE_TIME);

            //* CELL SERIAL
//			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CELL_SERIAL_START);
//			nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CELL_SERIAL_COMP);
//            nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetValue(nTag, PC_D_PRE_CELLID_BYPASS);

			// PRECHARGE RESULT OK/NG
			AnsiString okng_bin;
			for(int i = 0; i < 25; i++)
			{
				okng_bin = "";
				for(int j = 0; j < 16; j++)
				{
					okng_bin += Mod_PLC->GetData(Mod_PLC->pc_Interface_Data[nTag], PC_D_PRE_MEASURE_OK_NG + i, j);
				}
				nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = okng_bin;
			}

			// PRECHARGE RESULT VOLTAGE VALUE
            for(int i = 0; i < 20; i++)
                nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetVoltValue(nTag, PC_D_PRE_VOLTAGE_VALUE, i * 20);

			// PRECHARGE RESULT CURRENT VALUE
            for(int i = 0; i < 20; i++)
                nListView_PC[nTag]->Items->Item[index++]->SubItems->Strings[1] = Mod_PLC->GetCurrValue(nTag, PC_D_PRE_CURRENT_VALUE, i * 20);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::GroupBox2Click(TObject *Sender)
{
    Panel1->Visible = !Panel1->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnWriteValueClick(TObject *Sender)
{
	int address = cbAddress->Text.ToIntDef(21000); //* 21000, 22700
	int value = editValue->Text.ToIntDef(1);
    int nTag = cbStageNo->Text.ToIntDef(1) - 1;
    if(nTag == 0) Mod_PLC->SetValue(nTag, address - 21000, value);
    else if(nTag == 1) Mod_PLC->SetValue(nTag, address - 22700, value);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::Button1Click(TObject *Sender)
{
    int address = cbAddress->Text.ToIntDef(21850); //* 21850, 23550
	int value = editValue->Text.ToIntDef(1);
    int nTag = cbStageNo->Text.ToIntDef(1) - 1;
    if(nTag == 0) Mod_PLC->SetCurrValue(nTag, address - 21850, 0, value);
    else if(nTag == 1) Mod_PLC->SetCurrValue(nTag, address - 23550, 0, value);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnWriteNgValueClick(TObject *Sender)
{
    AnsiString strIrocvNg = editIrOcvNg->Text;
	vector<int> ngchannels = BaseForm->StringToVector(strIrocvNg);
    int nTag = cbStageNo->Text.ToIntDef(1) - 1;
    int ngCount = 0;
	for(int i = 0; i < 25; ++i){
		for(int j = 0; j < 16; j++)
		{
			int nChannel = i * 16 + j + 1;
			if(find(ngchannels.begin(), ngchannels.end(), nChannel) != ngchannels.end())
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data[nTag], PC_D_PRE_MEASURE_OK_NG + i, j, true);
				ngCount++;
			}
			else
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data[nTag], PC_D_PRE_MEASURE_OK_NG + i, j, false);
			}
		}
	}

    Mod_PLC->SetValue(nTag, PC_D_PRE_NG_COUNT, ngCount);
}
//---------------------------------------------------------------------------
void __fastcall TForm_PLCInterface::btnWriteIrOcvValueClick(TObject *Sender)
{
    int nTag = cbStageNo->Text.ToIntDef(1) - 1;
    Mod_PLC->PLC_Write_Result = true;
	double voltage_base = BaseForm->StringToDouble(editVoltage->Text, 1);
	double current_base = BaseForm->StringToDouble(editCurrent->Text, 1);

	// ir value 2 Word
	// 2 Word :  value / (65536 / 2) => 윗 주소에 쓰기, value % (65536 /2 ) => 아래 주소에 쓰기 // herald 2017 11 30
	for(int i = 0; i < MAXCHANNEL; i++)
	{
		int32_t voltage_int = static_cast<int32_t>(voltage_base * 10.0) + i;  // signed 32-bit int
        Mod_PLC->SetVoltValue(nTag, PC_D_PRE_VOLTAGE_VALUE, i, voltage_int);
	}

	for(int i = 0; i < MAXCHANNEL; i++)
	{
		double current = static_cast<int32_t>(current_base * 10.0) + i;
		Mod_PLC->SetCurrValue(nTag, PC_D_PRE_CURRENT_VALUE, i, current);
	}
}
//---------------------------------------------------------------------------



