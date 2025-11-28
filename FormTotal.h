//---------------------------------------------------------------------------

#ifndef FormTotalH
#define FormTotalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IniFiles.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Menus.hpp>
#include "AdvSmoothButton.hpp"
#include <Graphics.hpp>
#include "AdvSmoothPanel.hpp"
#include <System.Win.ScktComp.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <queue>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include "define.h"
#include "FormMeasureInfo.h"
#include "FormRemeasure.h"

#define HV_ETX						"\n"

const int NoCell = 1;
const int BadIr = 2;
const int CellError = 3;
const int Line = 4;
const int IrCheck = 5;
const int OcvCheck = 6;
const int BothCheck = 7;
const int MeasureFail = 8;
const int BadOcv = 9;

using namespace std;


typedef struct{
	AnsiString cmd;
	AnsiString param;
	int tx_mode;
	int time_out;
	int re_send;
}SEND_DATA;

typedef struct ExtInput
{
	uint8_t OUT2_9: 1;			// 2-09
	uint8_t OUT2_10: 1;			// 2-10
	uint8_t OUT2_11: 1;			// 2-11
	uint8_t OUT2_12: 1;				// 2-12
	uint8_t OUT2_13: 1;			// 2-13
	uint8_t OUT2_14: 1;			// 2-14
	uint8_t OUT2_15: 1;		// 2-15
	uint8_t Finish: 1;				// 2-16
		
	uint8_t oProbeUpDn: 1;		    // 2-O1
	uint8_t oProbeDnUp: 1;  			// 2-O2
	uint8_t oCenteringUp: 1;			// 2-O3
	uint8_t OUT2_4: 1;				// 2-O4
	uint8_t oTrayForward: 1;			// 2-O5
	uint8_t OUT2_6: 1;			// 2-O6
	uint8_t OUT2_7: 1;			// 2-O7
	uint8_t Standby: 1;				// 2-O8

	// board2
	uint8_t IN2_17: 1;						// 2-I17
	uint8_t IN2_18: 1;		  				// 2-I18
	uint8_t IN2_19: 1;				// 2-I19
	uint8_t IN2_20: 1;				// 2-I20
	uint8_t IN2_21: 1;						// 2-I21
	uint8_t IN2_22: 1;						// 2-I22
	uint8_t OP_EMSSw: 1; 						// 2-I23
	uint8_t IN2_24: 1;						// 2-I24

	uint8_t _TraySensing: 1;				// 2-I09
	uint8_t Interface_InOK: 1;						// 2-I10
	uint8_t _SafetySensing_1: 1;  					// 2-I11
	uint8_t _Air: 1;						// 2-I12
	uint8_t CenteringUp: 1;						// 2-I13
	uint8_t CenteringDn: 1;      				// 2-I14
	uint8_t IN2_15: 1;						// 2-I15
	uint8_t IN2_16: 1;						// 2-I16

	uint8_t ProbeUpUp: 1;				// 2-I1
	uint8_t ProbeUpDn: 1;				// 2-I2
	uint8_t ProbeDnUp: 1;				// 2-I3
	uint8_t ProbeDnDn: 1;				// 2-I4
	uint8_t IN2_5: 1; 		// 2-I5
	uint8_t IN2_6: 1;					// 2-I6
	uint8_t TrayForward: 1;				// 2-I7
	uint8_t TrayBackward: 1;				// 2-I8
} TExtInput;

class TTotalForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GrpMain;
	TImage *StatusImage;
	TGroupBox *GrpError;
	TLabel *error1;
	TLabel *error3;
	TLabel *error4;
	TLabel *ErrorTime;
	TImage *Image2;
	TAdvSmoothButton *AlarmConfirmBtn;
	TGroupBox *GrpLocal;
	TImage *Image5;
	TAdvSmoothButton *localTest;
	TAdvSmoothPanel *pback;
	TLabel *lblTitle;
	TAdvSmoothButton *btnAuto;
	TAdvSmoothButton *btnManual;
	TAdvSmoothPanel *pmain;
	TTimer *Timer_AutoInspection;
	TPanel *pnormal1;
	TPanel *pnormal2;
	TGroupBox *GrpAlarm;
	TLabel *modAlarm2;
	TImage *Image3;
	TLabel *modAlarm1;
	TLabel *modAlarm3;
	TLabel *modAlarm4;
	TLabel *AlarmTime;
	TGroupBox *grbChInfo;
	TPanel *pBase;
	TPanel *flowChart;
	TLabel *lblProcess;
	TPanel *pReady;
	TPanel *pTrayIn;
	TPanel *pBarcode;
	TPanel *pCharge;
	TPanel *pFinish;
	TPanel *pProbeOpen;
	TPanel *pTrayOut;
	TPanel *pProbeDown;
	TPanel *Panel3;
	TPanel *pnlTrayId;
	TPanel *pTrayid;
	TEdit *editTrayId;
	TLabel *lblTrayInfo;
	TPanel *Panel_State;
	TPanel *pnlEqStatus;
	TCheckBox *chkCycle;
	TCheckBox *chkBypass;
	TLabel *lblRemeasureAlarmCheck;
	TPanel *Panel10;
	TLabel *lblChargingProcess;
	TAdvSmoothPanel *pnlConfig;
	TLabel *lblConfiguration;
	TGroupBox *gbPreCharger;
	TEdit *editPRECHARGERIPAddress;
	TPanel *Panel23;
	TPanel *Panel24;
	TEdit *editPRECHARGERPort;
	TAdvSmoothButton *btnConnectPRECHARGER;
	TAdvSmoothButton *btnConfig;
	TAdvSmoothButton *btnCloseConnConfig;
	TAdvSmoothButton *btnSaveConnConfig;
	TPanel *p0;
	TPanel *Panel16;
	TPanel *pstep;
	TPanel *Panel17;
	TPanel *testTime;
	TAdvSmoothPanel *pnlTrayIn;
	TAdvSmoothPanel *pnlTrayOut;
	TAdvSmoothPanel *pnlProbeClose;
	TAdvSmoothPanel *pnlProbeOpen;
	TPanel *Panel8;
	TEdit *editChargeVolt;
	TPanel *Panel18;
	TEdit *editChargeCurrent;
	TPanel *Panel25;
	TEdit *editChargeTime;
	TClientSocket *Client;
	TPanel *pConInfo;
	TTimer *ReContactTimer;
	TPanel *Panel26;
	TPanel *clrConInfo;
	TTimer *rxTimer;
	TTimer *StatusTimer;
	TPanel *Panel33;
	TPanel *cl_line;
	TPanel *cl_charge;
	TPanel *cl_end;
	TPanel *cl_error;
	TPanel *cl_outflow;
	TPanel *cl_no;
	TGroupBox *gbEtc;
	TGroupBox *GroupBox6;
	TPanel *Panel11;
	TEdit *editMaxChargeVolt;
	TPanel *Panel12;
	TEdit *editMaxChargeCurrent;
	TPanel *Panel13;
	TEdit *editMaxChargeTime;
	TPanel *Panel28;
	TEdit *editNGAlarmCount;
	TGroupBox *gbPlcConnection;
	TEdit *editPLCIPAddress;
	TPanel *Panel2;
	TAdvSmoothButton *btnConnectPLC;
	TAdvSmoothButton *btnDisConnectPLC;
	TPanel *Panel4;
	TPanel *pnlportplc;
	TEdit *editPLCPortPC;
	TEdit *editPLCPortPLC;
	TTimer *Timer_PLCConnect;
	TPanel *Panel15;
	TEdit *editRemeasureAlarmCount;
	TTimer *Timer_ManualInspection;
	TTimer *Timer_FinishCharging;
	TTimer *Timer_Reset;
	TTimer *Timer_Reboot;
	TLabel *lblSet1;
	TPanel *pnlStatus;
	TPanel *pnlResetMsg;
	TAdvSmoothButton *btnDisconnPRECHARGER;
	TGroupBox *GroupBox1;
	TEdit *editModelName;
	TCheckBox *chkCellIdBypass;
	TAdvSmoothButton *btnInit;
	TAdvSmoothButton *btnNgInfo;
	TAdvSmoothButton *btnMeasureInfo;
	TAdvSmoothButton *btnTrayOut;
	TAdvSmoothButton *ConfigBtn1;
	TAdvSmoothPanel *AdvSmoothPanel2;
	TLabel *Label5;
	TAdvSmoothButton *AdvSmoothButton9;
	TPanel *Panel30;
	TPanel *Panel32;
	TEdit *Edit6;
	TEdit *Edit7;
	TPanel *Panel9;
	TPanel *pPos;
	TPanel *Panel20;
	TPanel *pStatus;
	TPanel *Panel31;
	TPanel *pIrValue;
	TPanel *Panel63;
	TPanel *pOcvValue;
	TGroupBox *GroupBox2;
	TPanel *Panel1;
	TEdit *editCurrentMin;
	TPanel *pnlCurrMin;
	TEdit *editCurrMin;
	TAdvSmoothButton *btnSaveConfig;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnSaveConfigClick(TObject *Sender);
	void __fastcall BitmapBtn5Click(TObject *Sender);
	void __fastcall btnAutoClick(TObject *Sender);
	void __fastcall btnTrayOutClick(TObject *Sender);
	void __fastcall editTrayIdKeyDown(TObject *Sender, WORD &Key,
		  TShiftState Shift);
	void __fastcall MainBtnClick(TObject *Sender);
	void __fastcall chkBypassMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
	void __fastcall btnManualClick(TObject *Sender);
	void __fastcall btnMeasureInfoClick(TObject *Sender);
	void __fastcall btnNgInfoClick(TObject *Sender);
	void __fastcall Timer_AutoInspectionTimer(TObject *Sender);
	void __fastcall btnInitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnConfigClick(TObject *Sender);
	void __fastcall btnConnectPLCClick(TObject *Sender);
	void __fastcall btnCloseConnConfigClick(TObject *Sender);
	void __fastcall btnDisConnectPLCClick(TObject *Sender);
	void __fastcall lblChargingProcessDblClick(TObject *Sender);
	void __fastcall ConfigBtn1Click(TObject *Sender);
	void __fastcall ClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ReContactTimerTimer(TObject *Sender);
	void __fastcall ClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall rxTimerTimer(TObject *Sender);
	void __fastcall ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
	void __fastcall ClientConnecting(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall StatusTimerTimer(TObject *Sender);
	void __fastcall Timer_PLCConnectTimer(TObject *Sender);
	void __fastcall btnConnectPRECHARGERClick(TObject *Sender);
	void __fastcall Timer_ManualInspectionTimer(TObject *Sender);
	void __fastcall Timer_FinishChargingTimer(TObject *Sender);
	void __fastcall Timer_ResetTimer(TObject *Sender);
	void __fastcall Timer_RebootTimer(TObject *Sender);
	void __fastcall btnDisconnPRECHARGERClick(TObject *Sender);
	void __fastcall lblTitleDblClick(TObject *Sender);
	void __fastcall localTestClick(TObject *Sender);
    void __fastcall ChInfoMouseEnter(TObject *Sender);
	void __fastcall ChInfoMouseLeave(TObject *Sender);
private:	// User declarations
//---------------------------------------------------------------------------
// Controller 데이터 처리
	TCustomWinSocket *sock;
	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(COMM_RECEIVE, TMessage, OnReceiveStage)
	END_MESSAGE_MAP(TForm)

    int cmd_mode;
	queue<string> q_cmd;
	queue<string> q_param;
	queue<int> q_txMode;
    queue<string> rxq;		// 수신 큐
   	int sock_len;
    int rxCount;
	vector<unsigned char> TxVector;		// 전송 데이터 만들기
    vector<unsigned char> dataBuffer;

    //* controller 의 마지막 응답
    AnsiString LASTRESPONSE;
    AnsiString LASTCMD;
    int nResponseCount;

   	void __fastcall MakeData(int tx_mode, AnsiString cmd, AnsiString param);
   	void __fastcall SendData(AnsiString Cmd, AnsiString Param = "");

	void __fastcall OnReceiveStage(TMessage& Msg);		// 데이터 수신시 발생
	int __fastcall DataCheck(AnsiString msg, AnsiString &param);
	void __fastcall ProcessMON(AnsiString param, int stageno);
    void __fastcall SET_MONDATA(AnsiString runcount, AnsiString runtime,
	AnsiString status, AnsiString current, AnsiString voltage, AnsiString capacity, int stageno);
	void __fastcall ProcessSEN(AnsiString param, int stageno);
    void __fastcall SET_SENDATA(AnsiString eqstatus, AnsiString runcount, AnsiString connection,
    AnsiString servostatus, vector<AnsiString> btset1, vector<AnsiString> btset2, int stageno);
	void __fastcall ProcessRPY(AnsiString param, int stageno);
    void __fastcall SetRunCount(AnsiString strRuncount);
    void __fastcall SetStatus(AnsiString strStatus);
    void __fastcall SetVoltage(AnsiString strVoltage);
    void __fastcall SetCurrent(AnsiString strCurrent);
    void __fastcall SetCapacity(AnsiString strCapacity);
    void __fastcall SetFinalResult(AnsiString strResult);
    void __fastcall SetFinalData();
    void __fastcall SetEquipStatus(AnsiString eqStatus, int stageno);

//---------------------------------------------------------------------------
// MON 데이터 처리
	void __fastcall ChannelStatus();
    void __fastcall DisplayChannelInfo();
    void __fastcall WriteMonData();
    void __fastcall WriteResultFile();
    void __fastcall WriteTrayInfo();
    void __fastcall BadInfomation();
	void __fastcall WriteVoltCurrValue();
    void __fastcall WriteVoltCurrValue(int initValue);
	void __fastcall SetResultList();
    void __fastcall SetResultList_Org();

//------------ 폼 관련 -------------------//
	TGroupBox *CurrentGrp;
	TGroupBox *OldGrp;
	void __fastcall VisibleBox(TGroupBox *grp);
	bool bconfig;
	void __fastcall MakePanel(AnsiString type);
    void __fastcall SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index);
	bool __fastcall ErrorCheck();
	void __fastcall DisplayProcess(int status, AnsiString Status_Step, AnsiString msg, bool bError = false);
    void __fastcall DisplayError(AnsiString msg, bool bError = false);
    void __fastcall DisplayTrayInfo();

//---------------------------------------------------------------------------
// 로그 파일 관련 생성
	void __fastcall WriteSystemInfo();
	bool __fastcall ReadSystemInfo();
	bool __fastcall ReadCellInfo();
	void __fastcall ErrorLog();
    void __fastcall ErrorMsg(int err);
    void __fastcall WriteCommLog(AnsiString Type, AnsiString Msg);

	void __fastcall StageClearAlarm();
	void __fastcall StageReady();

	void __fastcall SensorInputProcess(AnsiString param);
	int __fastcall SensorState(AnsiString cmd);
	void __fastcall EquipStatus(int cmd);
	void __fastcall InitEquipStatus(int cmd);

	TColor clNoCell;
	TColor clBadIr;
	TColor clCellError;
	TColor clLine;
	TColor clSelect;
	TColor clIrCheck;
	TColor clOcvCheck;
	TColor clBothCheck;
	TColor clMeasureFail;
	TColor clNo;
	TColor clYes;

	TPanel *pProcess[8];
	bool bStatus;
	int NgCount;
    int NgAlarmCount;

    //* CELL SERIAL
    int nReadCellCountTime;
    int nReadCellSerialCount;
    AnsiString m_sTrayID, m_sCell_Serial[MAXCHANNEL];
    bool m_bReadCellSerial;
    int nCellSerialStep;
    void __fastcall InitCellSerial();
    void __fastcall ReadCellSerial2();
//    bool __fastcall CheckTrayInfo(AnsiString trayID);
    bool __fastcall LoadTrayInfo(AnsiString trayID);
    void __fastcall SaveTrayInfo(AnsiString trayID);
    void __fastcall DeleteTrayInfo(AnsiString trayID);
    void __fastcall WriteTrayLog(AnsiString msg);
public:		// User declarations
	void __fastcall InitMeasureForm();
	void __fastcall InitTrayStruct();
    void __fastcall Initialization();
    void __fastcall WriteMINMAX();
	void __fastcall PLCInitialization();
	void __fastcall DisplayStatus(int status);

	void __fastcall AutoInspection_Wait();
	void __fastcall AutoInspection_Measure();
	void __fastcall AutoInspection_Finish();

    bool __fastcall CheckTrayInfo(AnsiString trayID);

	void __fastcall CmdTrayOut();
	void __fastcall CmdTrayOut_Original();
	void __fastcall CmdForceStop();
	void __fastcall CmdForceStop_Original();
	void __fastcall CmdManualMod(bool Set);
    void __fastcall AutoTestFinish();
	void __fastcall ReadchannelMapping();

    //* CELL SERIAL STEP
    void __fastcall ChangeCellSerialStep(int nstep);

//---------------------------------------------------------------------------
// Controller 명령어
	void __fastcall CmdAutoTest();
    void __fastcall CmdAutoStop();
    void __fastcall CmdReset();
    void __fastcall CmdReboot();
    void __fastcall CmdResetTimer();
    void __fastcall CmdRebootTimer();
    void __fastcall CmdDST();
    void __fastcall CmdEna();
	void __fastcall CmdStop();
    void __fastcall CmdSetStep();
    void __fastcall CmdDischargeSetStep();
    bool __fastcall CmdCheckSet();
    void __fastcall CmdReport();
    void __fastcall CmdCAL();
    void __fastcall CmdSTC();
    void __fastcall CmdCLS();
    void __fastcall CmdBID();

	AnsiString __fastcall GetCodeColor(TPanel *pnl, int index);
	AnsiString __fastcall GetCodeColor2(TPanel *pnl, int index);

//---------------------------------------------------------------------------
// 충전 셋팅
	AnsiString __fastcall convertCondition(AnsiString condition);
	AnsiString __fastcall convertCondition2(int iCondition);

	PRECHARGE_CONFIG precharge;
	CHARGE_CONFIG charge[2]; //* BT 설비 2개를 다루기 위한 배열 2개
	int nQueryIndex;
	int nCount;

//---------------------------------------------------------------------------
// CONSTROLLER Socket Start
	bool m_bConnect;

	void __fastcall SendCommand(AnsiString cmd, int mode = -1);
    void __fastcall StartCharge();
    void _fastcall PreChargeSet(int stageno);
    void __fastcall SetSystemInfo();

//---------------------------------------------------------------------------
// PLC
	AnsiString PLC_IPADDRESS;
	int PLC_PCPORT;
	int PLC_PLCPORT;

// Define.h structure 데이터
	REAL_TIME real_data;
	STAGE_INFO stage;
	CONFIG config;
	MAX_CONFIG max_config;					// 환경 설정
	TRAY_INFO tray;

	TPanel *panel[MAXCHANNEL];
	int stageno;
	int nSection, nStep, nStep_Count, nManualStep, nFinishStep, nRStep;
    int nSetStepCount, nRStepCount;

	int testtime;
    bool n_bMeasureStart;

	AnsiString OldPLCStatus, PLCStatus, OldErrorCheckStatus, ErrorCheckStatus, OldPreChargerStatus, PreChargerStatus;

	void __fastcall ProcessError(AnsiString err1, AnsiString err2,AnsiString err3,AnsiString err4);
	void __fastcall ShowAlarm(AnsiString err1, AnsiString err2, AnsiString err3 , AnsiString err4);
	void __fastcall SetTrayID(AnsiString str_id);
	AnsiString __fastcall GetStatus(AnsiString status);
    void __fastcall ShowPLCSignal(TAdvSmoothPanel *advPanel, bool bOn);

	int cnt;
	int acc_remeasure[MAXCHANNEL];
	int acc_cnt;
	AnsiString acc_init;
	int chMap[MAXCHANNEL + 1];
	int chReverseMap[MAXCHANNEL + 1];

	double curr_min;
	TDateTime dt1StartTime, dt1FinishTime, dt1CurrentTime, diff, dt2ChargingTime;

	int no_file_error_count;
	int mon_count;

    void __fastcall StageStatus();
	void __fastcall ReadRemeasureInfo();
	void __fastcall WriteRemeasureInfo();
	void __fastcall RemeasureAlarm(int remeasure_alarm_count);
    void __fastcall WritePLCLog(AnsiString Type, AnsiString Msg);

	TDateTime m_dateTime;
	AnsiString m_date, m_time;

	AnsiString m_sTempVlot[MAXCHANNEL], m_sTempCurr[MAXCHANNEL];
	AnsiString m_sTempVlot_Value[MAXCHANNEL], m_sTempCurr_Value[MAXCHANNEL];
	AnsiString LimitVolt[MAXCHANNEL], LimitCurr[MAXCHANNEL];

	int currMin;
    void __fastcall displayprocesstest();

	__fastcall TTotalForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTotalForm *TotalForm;
//---------------------------------------------------------------------------
#endif
