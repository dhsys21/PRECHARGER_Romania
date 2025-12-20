//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "RVMO_main.h"
#include "FormMeasureInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothButton"
#pragma link "AdvSmoothPanel"
#pragma resource "*.dfm"
TBaseForm *BaseForm;
//---------------------------------------------------------------------------
__fastcall TBaseForm::TBaseForm(TComponent* Owner)
	: TForm(Owner)
{
	FormCnt = CONTCOUNT;
	DeleteDay = 180;
	DeleteIndex = 0;
	this->Left = 960;
	this->Top = 0;
	this->Width = 960;

	statusImage[0] = Image1;
	statusImage[1] = Image2;
	statusImage[2] = Image3;
	statusImage[3] = Image4;
	statusImage[4] = Image5;
	statusImage[5] = Image6;
	statusImage[6] = Image7;
	statusImage[7] = Image8;
	statusImage[8] = Image9;
	statusImage[9] = Image10;
	statusImage[10] = Image11;

    pnlBT[0] = pnlBT1;
    pnlBT[1] = pnlBT2;
    pnlBT[2] = pnlBT21;
    pnlBT[3] = pnlBT22;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::FormCreate(TObject *Sender)
{
	if(!DirectoryExists((AnsiString)APP_PATH))MkDir((AnsiString)APP_PATH);
	if(!DirectoryExists((AnsiString)BIN_PATH))MkDir((AnsiString)BIN_PATH);
	if(!DirectoryExists((AnsiString)DATA_PATH))MkDir((AnsiString)DATA_PATH);
	if(!DirectoryExists((AnsiString)LOG_PATH))MkDir((AnsiString)LOG_PATH);
	if(!DirectoryExists((AnsiString)TRAY_PATH))MkDir((AnsiString)TRAY_PATH);

	ReadSystemInfo();
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::FormShow(TObject *Sender)
{
	this->Left = 0;
	MakePanel();
	this->HorzScrollBar->Position = 0;

	Form_Error->Parent = this;
	Form_Error->Position = poDesigned;

    Form_Language->LanguageChange(0);

    ReadSystemInfo();
    //Timer_PLCConnect->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::MakePanel()
{
	int nx, ny;
	nx = 5;
	ny = 85;

	for(int i=0; i<FormCnt;){
		nForm[i] = new TTotalForm(Owner);
		nForm[i]->Parent = this;
		nForm[i]->Left = nx;
		nForm[i]->Top = ny;
		nForm[i]->Position = poDesigned;
		nForm[i]->Tag = i;
		nForm[i]->Visible = true; 		// WM_SHOW 이벤트 발생

		i += 1;
		nx += (nForm[i-1]->Width + 1);
	}
}

void __fastcall TBaseForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	for(int i=0; i<FormCnt ;++i){
		nForm[i]->Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (MessageDlg("Close the form?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel,1) == mrOk){
		pPassword->Visible = !pPassword->Visible;
        pPassword->BringToFront();
	}
	CanClose = false;
}

//---------------------------------------------------------------------------
//--------------------- 버튼 색상표시 (연결정보)  ---------------------------
//---------------------------------------------------------------------------
void __fastcall TBaseForm::ClockTimerTimer(TObject *Sender)
{

	if(Mod_PLC->ClientSocket_PC->Active && Mod_PLC->ClientSocket_PLC->Active)
	{
        nPlcDisconCnt = 0;
		AdvSmoothPanel_PLC->Fill->Color = pon->Color;
		AdvSmoothPanel_PLC->Fill->ColorMirror = pon->Color;
		AdvSmoothPanel_PLC->Fill->ColorMirrorTo = pon->Color;
		AdvSmoothPanel_PLC->Fill->ColorTo = pon->Color;
	}else{
        nPlcDisconCnt++;
        if(nPlcDisconCnt > 3){
            AdvSmoothPanel_PLC->Fill->Color = poff->Color;
            AdvSmoothPanel_PLC->Fill->ColorMirror = poff->Color;
            AdvSmoothPanel_PLC->Fill->ColorMirrorTo = poff->Color;
            AdvSmoothPanel_PLC->Fill->ColorTo = poff->Color;
        }
	}

    if(nForm[0]->Client->Active == true)
        SetColorPanel(pnlCONT, true);
    else
        SetColorPanel(pnlCONT, false);

    if(nForm[1]->Client->Active == true)
        SetColorPanel(pnlCONT2, true);
    else
        SetColorPanel(pnlCONT2, false);

	if(Now().FormatString("hhnn") == "0700") {
		DeleteDay = 90;	// 12시가 되면 DeleteDay를 90으로 초기화
	}
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::SetColorPanel(TAdvSmoothPanel* pnl, bool bOn)
{
    if(bOn == true)
	{
		pnl->Fill->Color = pon->Color;
		pnl->Fill->ColorMirror = pon->Color;
		pnl->Fill->ColorMirrorTo = pon->Color;
		pnl->Fill->ColorTo = pon->Color;
	}else{
		pnl->Fill->Color = poff->Color;
		pnl->Fill->ColorMirror = poff->Color;
		pnl->Fill->ColorMirrorTo = poff->Color;
		pnl->Fill->ColorTo = poff->Color;
	}
}
void __fastcall TBaseForm::IncErrorCount()
{
	ErrorCount += 1;
	if(ErrorCount == 1){
		AnsiString path;
		path = AnsiString(BIN_PATH)+"Alarm.wav";
		PlaySound((TCHAR *)path.c_str(), NULL, SND_ASYNC|SND_LOOP);
	}
}
void __fastcall TBaseForm::DecErrorCount()
{
	ErrorCount = 0;
	PlaySound(NULL, NULL, 0);
}


//---------------------------------------------------------------------------
//--------------------- 파일 삭제  ------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TBaseForm::DeleteLogFile(AnsiString FileName)
{
	if(FileExists(FileName))
	{
		DeleteFile(FileName);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TBaseForm::DeleteLogFolder(UnicodeString FolderName)
{
	if(DirectoryExists(FolderName)) {
		SHFILEOPSTRUCT FileOp;

		FileOp.hwnd = this->WindowHandle;
		FileOp.wFunc = FO_DELETE;
		FileOp.pFrom = (TCHAR *)FolderName.c_str();
		FileOp.pTo = NULL;
		FileOp.fFlags = FOF_NOCONFIRMATION |FOF_NOERRORUI;
		FileOp.fAnyOperationsAborted = FALSE;
		SHFileOperationW(&FileOp);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::FileDeleteTimerTimer(TObject *Sender)
{
	TDateTime  dt;

	// 1시간에 파일 하나씩 삭제
	dt = Now() - DeleteDay;
	switch(DeleteIndex){
	case 0:

		DeleteLogFolder((AnsiString)LOG_PATH + dt.FormatString("yyyymmdd"));
		DeleteDay += 1;
		break;
	}
}
//---------------------------------------------------------------------------
//--------------------- 파일 삭제  ------------------------------------------
//---------------------------------------------------------------------------


void __fastcall TBaseForm::advGraphShowClick(TObject *Sender)
{
	Form_PLCInterface->Visible = false;

	Form_Graph->Position = poDesigned;
	Form_Graph->Left = 5;
	Form_Graph->Top = 85;
    Form_Graph->BringToFront();
	Form_Graph->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::ptimeClick(TObject *Sender)
{
	advPLCInterfaceShow->Visible = !advPLCInterfaceShow->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::Label1DblClick(TObject *Sender)
{
    Memo1->Visible = !Memo1->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::Memo1Change(TObject *Sender)
{
	if(Memo1->Lines->Count > 500) Memo1->Clear();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//--------------------- PLC  ------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TBaseForm::advPLCInterfaceShowClick(TObject *Sender)
{
	Form_Graph->Visible = false;

	Form_PLCInterface->Position = poDesigned;
	Form_PLCInterface->Left = 5;
	Form_PLCInterface->Top = 85;
	Form_PLCInterface->Visible = true;

    Form_PLCInterface->WindowState = wsNormal;
    Form_PLCInterface->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::AdvSmoothPanel_PLCClick(TObject *Sender)
{
	gbPLCConnection->Visible = !gbPLCConnection->Visible;
	gbPLCConnection->BringToFront();
    Memo1->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnConnectPLCClick(TObject *Sender)
{
	WriteSystemInfo();
    ReadSystemInfo();
	Mod_PLC->Connect(PLC_IPADDRESS, PLC_PLCPORT, PLC_PCPORT);
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::btnDisConnectPLCClick(TObject *Sender)
{
    Mod_PLC->DisConnect();
}

//---------------------------------------------------------------------------
//--------------------- 함수 정리  ------------------------------------------
//---------------------------------------------------------------------------
//double __fastcall TBaseForm::HexToDouble(UnicodeString str, int def)
//{
//    double dVal;
//
//}bool TBaseForm::WaitForMilliSeconds(int milliseconds)
{
    // 1. 필요한 메시지 큐만 감시 (QS_ALLINPUT)
    // 2. 메시지가 도착하거나 타임아웃이 발생할 때까지 대기
    // 3. 타임아웃 시간은 '0'으로 설정하여 큐만 확인하거나, '1'로 설정하여 1ms 대기

    // Windows API의 MsgWaitForMultipleObjects를 사용하여 메시지가 도착할 때까지 대기합니다.
    DWORD StartTick = GetTickCount();
    DWORD Timeout = (DWORD)milliseconds;

    // 최종 종료 시간 계산
    DWORD EndTick = StartTick + Timeout;

    // 루프 실행
    while (true)
    {
        // 남은 시간 계산
        DWORD RemainingTime = EndTick - GetTickCount();

        // 시간이 다 되었거나, GetTickCount() 오버플로우를 감안하여 루프 종료
        if (GetTickCount() >= EndTick)
        {
            break;
        }

        // MsgWaitForMultipleObjects를 사용하여 대기합니다.
        // 1. dwCount: 0 (감시할 핸들 없음)
        // 2. pHandles: NULL
        // 3. bWaitAll: FALSE
        // 4. dwMilliseconds: 남은 시간
        // 5. dwWakeMask: 모든 입력 메시지 (마우스, 키보드, 타이머 등)를 감시
        DWORD Result = MsgWaitForMultipleObjects(
            0,            // 감시할 핸들 수 (없음)
            NULL,         // 감시할 핸들 목록
            FALSE,        // 모든 핸들을 기다릴 필요 없음
            RemainingTime, // 남은 시간만큼 대기 (최대)
            QS_ALLINPUT   // 모든 종류의 메시지 큐를 감시
        );

        // 결과 확인
        if (Result == WAIT_OBJECT_0 + 0)
        {
            // 메시지 큐에 입력 메시지가 도착했을 경우 (WAIT_OBJECT_0는 0이므로 +0)
            // Application->ProcessMessages()를 한 번만 호출하여 메시지를 처리하고 즉시 복귀합니다.
            Application->ProcessMessages();
        }
        else if (Result == WAIT_TIMEOUT)
        {
            // 시간이 다 되어 타임아웃이 발생한 경우 (루프 종료 조건에 따라 종료)
            break;
        }
        // 그 외의 경우 (WAIT_FAILED 등)에도 일단 루프를 계속합니다.
    }

    return true;
}
int __fastcall TBaseForm::StringToInt(UnicodeString str, int def)
{
	int iVal;
	if(TryStrToInt(str, iVal) == true) return iVal;
	else return def;
}
//---------------------------------------------------------------------------
double __fastcall TBaseForm::StringToDouble(UnicodeString str, double def)
{
	double dVal;
	if(TryStrToFloat(str, dVal) == true) return dVal;
	else return def;
}
//---------------------------------------------------------------------------
vector<int> __fastcall TBaseForm::StringToVector(UnicodeString str)
{
	vector<int> numbers;

	int start = 1, end = 0;
	while((end = str.Pos(",")) > 0)
	{
		UnicodeString temp = str.SubString(start, end - start);
		numbers.push_back(temp.ToIntDef(0));
		str.Delete(start, end);
	}
	numbers.push_back(str.SubString(start, str.Length() - start + 1).ToIntDef(0));

    return numbers;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TBaseForm::HexToAscii(AnsiString hex)
{
	AnsiString result = "";
    if(hex.Length() % 2 == 1) hex += "00";

    for(int i = 1; i < hex.Length(); i += 2){
        String hexByte = hex.SubString(i, 2);
        char asciiChar = (char)StrToInt("$" + hexByte);
        result += asciiChar;
    }
    return result;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TBaseForm::HexToAscii(AnsiString hex, int length)
{
	AnsiString result = "";

    for(int i = 1; i < length; i += 2){
        String hexByte = hex.SubString(i, 2);
        char asciiChar = (char)StrToInt("$" + hexByte);
        result += asciiChar;
    }
    return result;
}
//--------------------------------------------------------------------------- '
//---------------------------------------------------------------------------
vector<AnsiString> __fastcall TBaseForm::SplitString(AnsiString str, AnsiString delimiter)
{
	vector<AnsiString> result;

    int pos = 0;
    while((pos = str.Pos(delimiter)) > 0){
        result.push_back(str.SubString(1, pos - 1));
        str = str.SubString(pos + 1, str.Length() - pos);
    }
    result.push_back(str);

    return result;
}
//---------------------------------------------------------------------------
bool __fastcall TBaseForm::ReadSystemInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "config.inf";

	ini = new TIniFile(file);

    editPLCIPAddress->Text = ini->ReadString("PRE_PLC_CONNECTION", "IP", "17.91.71.221");
	editPLCPortPC->Text = ini->ReadString("PRE_PLC_CONNECTION", "PORT1", "6007");
	editPLCPortPLC->Text = ini->ReadString("PRE_PLC_CONNECTION", "PORT2", "6008");

    PLC_IPADDRESS = editPLCIPAddress->Text;
	PLC_PCPORT = editPLCPortPC->Text.ToIntDef(6007);
	PLC_PLCPORT = editPLCPortPLC->Text.ToIntDef(6008);

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::WriteSystemInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "config.inf";
	ini = new TIniFile(file);

	ini->WriteString("PRE_PLC_CONNECTION", "IP", editPLCIPAddress->Text);
	ini->WriteString("PRE_PLC_CONNECTION", "PORT1", editPLCPortPC->Text);
	ini->WriteString("PRE_PLC_CONNECTION", "PORT2", editPLCPortPLC->Text);

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::OpenFolder(UnicodeString path)
{
	 ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------
//--------------------- 함수 정리  ------------------------------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//--------------------- 프로그램 종료시 패스워드 입력 ------------------------
//---------------------------------------------------------------------------
void __fastcall TBaseForm::PasswordBtnClick(TObject *Sender)
{
	if(PassEdit->Text == "0000"){
        for(int i=0; i<FormCnt ;++i){
            nForm[i]->Close();
        }
		Application->Terminate();
	}
	else{
		MessageBox(Handle, L"Are you sure you’re spelling your password correctly?", L"ERROR", MB_OK|MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::cancelBtn2Click(TObject *Sender)
{
    pPassword->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::PassEditKeyPress(TObject *Sender, System::WideChar &Key)
{
    if(Key == VK_RETURN){
		PasswordBtnClick(Sender);
	}
}
//---------------------------------------------------------------------------
//--------------------- 프로그램 종료시 패스워드 입력 ------------------------
//---------------------------------------------------------------------------
void __fastcall TBaseForm::btnViewLogClick(TObject *Sender)
{
    OpenFolder(LOG_PATH);
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnViewDataClick(TObject *Sender)
{
    OpenFolder(DATA_PATH);
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::rbKoreanClick(TObject *Sender)
{
    TRadioButton *rbt = (TRadioButton *)Sender;
	if(rbt->Checked)
	{
		Form_Language->LanguageChange(rbt->Tag);
	}
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::btnNgCountErrClick(TObject *Sender)
{
    Form_Error->DisplayErrorMessage(this->Tag, nNgErr);
    Form_Error->Tag = this->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnInitClick(TObject *Sender)
{
    nForm[0]->Initialization();
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::Button1Click(TObject *Sender)
{
//    if(WaitForMilliSeconds(1000) == true)
//        Form_Error->DisplayErrorMessage(0, nNgErr);
	if(Form_ErrorReset->Visible == false)
        Form_ErrorReset->DisplayErrorMessage(0);
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::Button5Click(TObject *Sender)
{
//    if(Form_ErrorSet->Visible == false)
//	    Form_ErrorSet->DisplayErrorMessage(1);
    nForm[1]->DisplayErrorMessage("SET", "Do you want to set PRECHARGER?");
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::lblTitleDblClick(TObject *Sender)
{
    GroupBox2->Visible = !GroupBox2->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::Timer_PLCConnectTimer(TObject *Sender)
{
    if(Mod_PLC->ClientSocket_PC->Active == false && Mod_PLC->ClientSocket_PLC->Active == false)
		Mod_PLC->Connect(PLC_IPADDRESS, PLC_PLCPORT, PLC_PCPORT);
	Timer_PLCConnect->Enabled = false;
}
//---------------------------------------------------------------------------


