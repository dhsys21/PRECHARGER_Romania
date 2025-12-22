#include "FormTotal.h"
#include "RVMO_main.h"
//---------------------------------------------------------------------------
void __fastcall TTotalForm::MakeData(int tx_mode, AnsiString cmd, AnsiString param)
{
	q_txMode.push(tx_mode);
	q_cmd.push(cmd.c_str());
	q_param.push(param.c_str());
}
void __fastcall TTotalForm::SendData(AnsiString Cmd, AnsiString Param)
{
	bool sock_con;
	if(sock != NULL) sock_con = true;
	else sock_con = false;

	if(sock_con)
	{
        AnsiString msg = "@" + Cmd + ";";
        sock->SendText(msg);
        WriteCommLog("TX", msg);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdForceStop_Original()
{
    CmdStop();
	tray.amf = true;

	PLCStatus = "run AMF. probe open.";
	if(PLCStatus != OldPLCStatus){
		WritePLCLog("CmdForceStop_Original", PLCStatus);
        OldPLCStatus = PLCStatus;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdForceStop_Cycle()
{
	// 자동검사 7. 검사종료	- Probe 오픈
	DisplayStatus(nEND);
	Panel_State->Caption = " PreCharger Complete ... ";

    Mod_PLC->SetValue(this->Tag, PC_D_PRE_PROB_OPEN, 1);
	WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , PC_INTERFACE_PROB_OPEN = 1");

    //* BadInfomation
    int ngCount = 0;
	NgCount = 0;

	AnsiString strIrocvNg = Form_PLCInterface->editIrOcvNg->Text;
	vector<int> ngchannels = BaseForm->StringToVector(strIrocvNg);
    int nTag = Form_PLCInterface->cbStageNo->Text.ToIntDef(1) - 1;
    int32_t voltage_int, current_int;

	for(int i = 0; i < 25; ++i){
		for(int j = 0; j < 16; j++)
		{
			int nChannel = i * 16 + j + 1;
			if(find(ngchannels.begin(), ngchannels.end(), nChannel) != ngchannels.end())
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data[nTag], PC_D_PRE_MEASURE_OK_NG + i, j, true);
                acc_remeasure[nChannel - 1] += 1;   // 셀이 있고 에러일 때 count 증가
				ngCount++;
                voltage_int = 100;
                current_int = 0;
			}
			else
			{
				Mod_PLC->SetData(Mod_PLC->pc_Interface_Data[nTag], PC_D_PRE_MEASURE_OK_NG + i, j, false);

				real_data.final_volt[nChannel - 1] = BaseForm->StringToDouble(Form_PLCInterface->editVoltage->Text, 0) + (double)((nChannel - 1) * 0.1);
				voltage_int = static_cast<int32_t>(std::floor(BaseForm->StringToDouble(real_data.final_volt[nChannel -1 ], 0) * 10.0 + 0.5));

				real_data.final_curr[nChannel - 1] = BaseForm->StringToDouble(Form_PLCInterface->editCurrent->Text, 0) + (double)((nChannel - 1) * 0.1);
				current_int = static_cast<int32_t>(std::floor(BaseForm->StringToDouble(real_data.final_curr[nChannel - 1], 0) * 10.0 + 0.5));
			}

			Mod_PLC->SetVoltValue(this->Tag, PC_D_PRE_VOLTAGE_VALUE, nChannel - 1, voltage_int);
			Mod_PLC->SetCurrValue(this->Tag, PC_D_PRE_CURRENT_VALUE, nChannel - 1, current_int);
        }
	}

	Mod_PLC->SetValue(nTag, PC_D_PRE_NG_COUNT, ngCount);
	WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , Write BadInfomation");
    WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , Write Voltage, Current Value");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdForceStop()
{
	// 자동검사 7. 검사종료	- Probe 오픈
	DisplayStatus(nEND);
	Panel_State->Caption = " PreCharger Complete ... ";

    Mod_PLC->SetValue(this->Tag, PC_D_PRE_PROB_OPEN, 1);
	WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , PC_INTERFACE_PROB_OPEN = 1");

    BadInfomation();
    WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , Write BadInfomation");
    ReadCellInfo();

    Sleep(100);
    WriteVoltCurrValue();
    WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , Write Voltage, Current Value");
    //* Load Cell Serial
    LoadTrayInfo(tray.trayid);
    //* Write Result File
    WriteResultFile();
	//	Mod_PLC->SetValue(this->Tag, PC_D_PRE_COMPLETE, 1);
    //	WritePLCLog("AutoInspection_Measure", "CmdForceStop ... , PC_D_PRE_COMPLETE = 1");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdTrayOut()
{
	// 자동검사 9(끝). 트레이 방출
	if(NgCount == tray.cell_count || NgCount > editNGAlarmCount->Text.ToIntDef(10)){
        Form_Error->DisplayErrorMessage(this->Tag, nNgErr);
		Form_Error->Tag = this->Tag;
        DisplayStatus(nEND);
	}
	else{
        //if(BaseForm->chkTest->Checked == false)
        Mod_PLC->SetValue(this->Tag, PC_D_PRE_TRAY_OUT, 1);
        WritePLCLog("AutoInspection_Measure", "CmdTrayOut ... , PC_D_PRE_TRAY_OUT = 1");
		DisplayStatus(nFinish);
		Panel_State->Caption = " PreCharger Tray Out ... ";
	}
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdTrayOut_Original()
{
	BadInfomation();
	WriteVoltCurrValue();

}
//--------------------------------------------------------------------------
void __fastcall TTotalForm::CmdManualMod(bool Set)
{
	this->InitTrayStruct();

	if(Set){ //* Manual
        Mod_PLC->SetValue(this->Tag, PC_D_PRE_STAGE_AUTO_READY, 0);
		DisplayStatus(nManual);
        nSection = STEP_WAIT;
		nStep = 0;
		if(Timer_AutoInspection->Enabled == true)
            Timer_AutoInspection->Enabled = false;
	} else{ //* Auto
        Mod_PLC->SetValue(this->Tag, PC_D_PRE_STAGE_AUTO_READY, 1);
		DisplayStatus(nVacancy);
        nSection = STEP_WAIT;
		nStep = 0;
        if(Timer_AutoInspection->Enabled == false)
            Timer_AutoInspection->Enabled = true;
    }

}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::AutoTestFinish()
{
	SetResultList();
	if(MeasureInfoForm->n_bManualStart == true)
	{
        // CmdForseStop() 에서 동일코드가 있음. 중복
		//WriteResultFile();
		MeasureInfoForm->n_bManualStart = false;
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// 컨트롤러 명령어
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdAutoTest()
{
    tray.ams = true;
//    BaseForm->WaitForMilliSeconds(10000);
//    Sleep(100);
    WriteCommLog("CmdAutoTest()", "START CHARGING");
    dt1StartTime = StrToDateTime(Now());

    SendData("ASB");
    LASTCMD = "ASB";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdAutoStop()
{
    Sleep(100);
//    BaseForm->WaitForMilliSeconds(100);
    tray.amf = true;
    tray.ams = false;

    //* 마지막 종료 색상 표시
    DisplayChannelInfo();
    //* final data 저장.
    AutoTestFinish();

    if(chkCycle->Checked == false)
    	CmdForceStop();
    else
        CmdForceStop_Cycle();

    //* 위 버전으로 테스트 필요. 아래 코드는 시간이 3-4초 이상 걸림.
    //* GetReport, AutoTestFinish
//	if(Timer_FinishCharging->Enabled == false){
//        tray.amf = true;
//        tray.ams[this->Tag] = false;
//
//        nFinishStep = 0;
//        Timer_FinishCharging->Enabled = true;
//    }
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdStop()
{
    SendData("STP");
    LASTCMD = "STP";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdResetTimer()
{
    nRStep = 0;
    Timer_Reset->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdRebootTimer()
{
    nRStep = 0;
    Timer_Reboot->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdReset()
{
    SendData("RST");
    LASTCMD = "RST";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdReboot()
{
    SendData("RBT");
    LASTCMD = "RBT";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdDST()
{
    SendData("DST");
    LASTCMD = "DST";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdEna()
{
    SendData("ENA");
    LASTCMD = "ENA";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdCAL()
{
    SendData("CAL");
    LASTCMD = "CAL";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdSTC()
{
    SendData("STC");
    LASTCMD = "STC";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdCLS()
{
    SendData("CLS");
    LASTCMD = "CLS";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdBID()
{
    SendData("BID");
    LASTCMD = "BID";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdReport()
{
    AnsiString CMD = "STAT:CELL:REP? (@1001:1032,2001:2032,3001:3032,4001:4032,5001:5032,6001:6032,7001:7016)";
    CMD = "TRB" + CMD + "\n";
    SendData(CMD);
    LASTCMD = "REP";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdSetStep()
{
    AnsiString CMD = "";
    AnsiString cTime, cCurr, cVolt, cPrechargeTime, cPreCurr;

    //* settle time : precharge2 시작할 때 충전전류를 흘리기 전 검사시간 약 7초
    //* charge 명령은 약 15초 정도 걸림
    /// config.time = 30s, cTime = config.time + SETTLETIME = 37s
    /// SETTLETIME = 7s
    /// PRECHARGETIME = 10s
    cPrechargeTime = IntToStr(PRECHARGETIME);
    cTime = config.time + SETTLETIME;
	cCurr = convertCondition2(config.curr);
	cVolt = convertCondition2(config.volt);

    if(config.curr > 1000) cPreCurr = "1.0";
	else cPreCurr = cCurr;
/* 조건 예시
    // "SEQ:TEST:DEF 1,2,2,VOLT_LE,0.1,BEFORE,90,FAIL";  // 100mV
    // "SEQ:TEST:DEF 1,2,1,CURR_LE,0.01,BEFORE,60,FAIL"; // 10mA
    // "SEQ:TEST:DEF 1,1,1,VOLT_GE,2.0,BEFORE,20,NEX";
*/
    CMD = "SEQ:STEP:DEF 1,1,PRECHARGE," + cPrechargeTime + ",1.0,2.0\n";
    CMD += "SEQ:TEST:DEF 1,1,1,VOLT_GE,1.2,BEFORE,20,NEXT\n";
    CMD += "SEQ:STEP:DEF 1,2,PRECHARGE2," + cTime + "," + cCurr + "," + cVolt + "\n";
    CMD += "SEQ:TEST:DEF 1,2,1,CURR_LE,0.01,BEFORE,40,FAIL\n";
    CMD += "SEQ:TEST:DEF 1,2,2,VOLT_LE,0.1,BEFORE,40,FAIL\n";
    CMD += "SYST:ERR?";
    CMD = "TRB" + CMD + "\n";
    SendData(CMD);
    LASTCMD = "SET";
}
//---------------------------------------------------------------------------
bool __fastcall TTotalForm::CmdCheckSet()
{
    /// charge[0].time = charge[1].time = 30s
    /// SETTLETIME = 7s
    /// config.time = 30s
    int time1 = BaseForm->StringToInt(charge[0].time, 0);
    int time2 = BaseForm->StringToInt(charge[1].time, 0);
    double curr1 = charge[0].curr * 1000;
    double curr2 = charge[1].curr * 1000;
    double volt1 = charge[0].volt * 1000;
    double volt2 = charge[1].volt * 1000;
    if(config.time ==  time1 && config.time == time2
        && config.curr == curr1 && config.curr == curr2
        && config.volt == volt1 && config.volt == volt2)
		return true;
    return false;
}

//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdDischargeSetStep()
{
    AnsiString CMD = "";
	AnsiString precharge_time = "20", precharge_curr = "1.0", precharge_volt = "2.0";
    AnsiString cTime, cCurr, cVolt;

    cTime = config.time + SETTLETIME;
	cCurr = convertCondition2(config.curr);
	cVolt = convertCondition2(config.volt);

    CMD = "SEQ:STEP:DEF 1,1,PRECHARGE," + precharge_time + "," + precharge_curr + "," + precharge_volt + "\n";
    CMD += "SEQ:STEP:DEF 1,2,DISCHARGE," + cTime + "," + cCurr + "," + cVolt + "\n";
    CMD += "SYST:ERR?";
    CMD = "TRB" + CMD + "\n";
    SendData(CMD);
    LASTCMD = "DEF";
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdCheckStep(int step)
{
	AnsiString CMD = "SEQ:STEP:DEF? 1," + IntToStr(step);
	CMD = "TRB" + CMD + "\n";
	SendData(CMD);
	LASTCMD = "STEP";
}
//---------------------------------------------------------------------------
// 컨트롤러 명령어
//---------------------------------------------------------------------------

