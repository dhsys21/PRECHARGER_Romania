//---------------------------------------------------------------------------

#ifndef ModPLCH
#define ModPLCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <System.Win.ScktComp.hpp>
#include "Define.h"

#include <deque>

//---------------------------------------------------------------------------
//	디바이스 코드
//---------------------------------------------------------------------------
const int DEVCODE_M			=	0x90;		//	내부 릴레이
const int DEVCODE_L			=	0x92;	  	//	래치 릴레이
const int DEVCODE_D			=	0xA8;		//	데이터 레지스터
const int DEVCODE_W			=	0xB4;		//	링크 레지스터
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	Index 구분
//---------------------------------------------------------------------------
const int PLC_INDEX_INTERFACE[2]				=	{ 1, 2 };
const int PC_INDEX_INTERFACE					=	11;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	시작 번지(통합)
//---------------------------------------------------------------------------
const int PLC_D_INTERFACE_START_DEV_NUM[2] 			=	{20000, 20500};
const int PLC_D_INTERFACE_LEN	 					= 	480;
//----------------------------------------------------------------------------
//const int PLC_D_CELL_SERIAL_NUM                     =	{90000};
//const int PLC_D_CELL_SERIAL_LEN                     =   4100; //* 총 4100 word. 820 * 5번 읽어야 함
//const int PLC_D_CELL_SERIAL_READLEN                 =   820;

const int PC_D_INTERFACE_START_DEV_NUM[2]			=	{21000, 22700};
const int PC_D_INTERFACE_LEN  						= 	45;

const int PC_D_INTERFACE_VOLTAGE[2]					=	{21050, 22750};
const int PC_D_INTERFACE_VOLTAGE_LEN				= 	800;

const int PC_D_INTERFACE_CURRENT[2]					=	{21850, 23550};
const int PC_D_INTERFACE_CURRENT_LEN				= 	800;
//----------------------------------------------------------------------------


//---------------------------------------------------------------------------
//	PLC - PC Interface
//---------------------------------------------------------------------------
const int PLC_D_HEART_BEAT				   			=	0;
const int PLC_D_AUTO_MANUAL			   				=	1;
const int PLC_D_PRE_ERROR		   	  				=	2;

const int PLC_D_PRE_TRAY_IN	    	  		        =   3;
const int PLC_D_PRE_PROB_OPEN   	  		        =   4;
const int PLC_D_PRE_PROB_CLOSE 		   	  	        =   5;
const int PLC_D_PRE_BCR_EVENT                       =   6;

const int PLC_D_PRE_TRAY_ID    	  			        =   10;

//CELL SERIAL  - Write Start, Write Complete
const int PLC_D_PRE_CELL_SERIAL_START              	=   20;
const int PLC_D_PRE_CELL_SERIAL_COMP               	=   21;
const int PLC_D_PRE_CELL_SERIAL_COUNT               =   22;

// TRAY INFO
const int PLC_D_PRE_TRAY_CELL_DATA				   	=	30;

// CELL SERIAL TRAY ID   - 90000 번지
const int PLC_D_PRE_CELL_SERIAL_TRAYID              =   0;
const int PLC_D_PRE_CELL_SERIAL                    	=   10;
//---------------------------------------------------------------------------
//	PC - PLC Interface
//---------------------------------------------------------------------------
const int PC_D_HEART_BEAT			  				=	0;
const int PC_D_PRE_STAGE_AUTO_READY     	        =   1;
const int PC_D_PRE_ERROR						   	=	2;

const int PC_D_PRE_TRAY_OUT    	  		        	=   3;
const int PC_D_PRE_PROB_OPEN   	  		        	=   4;
const int PC_D_PRE_PROB_CLOSE    	  	        	=   5;
const int PC_D_PRE_CHARGING                      	=   6;
const int PC_D_PRE_NG_COUNT                      	=   7;
const int PC_D_PRE_NG_ALARM                         =   17;

const int PC_D_PRE_CURRENT_MIN                      =   8;
const int PC_D_PRE_CHARGE_VOLTAGE                   =   10;
const int PC_D_PRE_CHARGE_CURRENT                   =   12;
const int PC_D_PRE_CHARGE_TIME                      =   14;

// CELL SERIAL - Read Start, Read Complete
const int PC_D_PRE_CELL_SERIAL_START                =   120;
const int PC_D_PRE_CELL_SERIAL_COMP                 =   121;
const int PC_D_PRE_CELLID_BYPASS                    =   122;

// OK/NG - D41030
const int PC_D_PRE_MEASURE_OK_NG			   		=	20;
// {21050, 22750}
const int PC_D_PRE_VOLTAGE_VALUE                    =   0;
// {21850, 23550}
const int PC_D_PRE_CURRENT_VALUE                    =   0;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	PLC
//---------------------------------------------------------------------------
typedef struct
{
	unsigned char SubHeader[2];			//	서브 헤더
	unsigned char NetNum;		 		//	네트워크 번호
	unsigned char PlcNum;	   			//	PLC 번호
	unsigned char ReqIONum[2];			//	IO 번호
	unsigned char ReqOfficeNum;	  		//	국 번호
	unsigned char ReqDataLen[2];		//  요구 데이터 길이(CPU 감시 타이머 ~ 디바이스 길이)
	unsigned char CpuTime[2];			//	CPU 감시 타이머
	unsigned char Command[2];			//	커맨드
	unsigned char SubCommand[2];		//	서브 커맨드 (0 = 비트-16단위, 워드-1단위 / 1 = 비트-1단위)
	unsigned char StartDevNum[3];		//	선두 디바이스
	unsigned char DevCode;  			//	디바이스 코드
	unsigned char DevLen[2];			//	디바이스 길이
} PLC_DATA;
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//	PC
//---------------------------------------------------------------------------
typedef struct
{
	unsigned char SubHeader[2];					//	서브 헤더
	unsigned char NetNum;						//	네트워크 번호
	unsigned char PlcNum;	    				//	PLC 번호
	unsigned char ReqIONum[2];					//	IO 번호
	unsigned char ReqOfficeNum;	  				//	국 번호
	unsigned char ReqDataLen[2];				//  요구 데이터 길이(CPU 감시 타이머 ~ 디바이스 길이)
	unsigned char CpuTime[2];					//	CPU 감시 타이머
	unsigned char Command[2];					//	커맨드
	unsigned char SubCommand[2];				//	서브 커맨드
	unsigned char StartDevNum[3];				//	선두 디바이스
	unsigned char DevCode;  					//	디바이스 코드
	unsigned char DevLen[2];					//	디바이스 길이
} PC_DATA;
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
class TMod_PLC : public TDataModule
{
__published:	// IDE-managed Components
	TTimer *Timer_Read;
	TClientSocket *ClientSocket_PC;
	TClientSocket *ClientSocket_PLC;
	TTimer *Timer_PC_AutoConnect;
	TTimer *Timer_PC_WriteMsg;
	TTimer *Timer_PLC_WriteMsg;
	TTimer *Timer_PLC_AutoConnect;
	void __fastcall ClientSocket_PCConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PCDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ClientSocket_PCRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Timer_PC_WriteMsgTimer(TObject *Sender);
	void __fastcall Timer_PC_AutoConnectTimer(TObject *Sender);
	void __fastcall ClientSocket_PLCConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ClientSocket_PLCRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Timer_PLC_WriteMsgTimer(TObject *Sender);
	void __fastcall Timer_PLC_AutoConnectTimer(TObject *Sender);

private:	// User declarations
	bool bClose;

//---------------------------------------------------------------------------
//	PLC
//---------------------------------------------------------------------------
	void __fastcall PLC_Initialization();
	void __fastcall PLC_DataChange(int subCommand, int address, int devCode, int devLen);
	void __fastcall PLC_Recv_Interface(int nTag);
    void __fastcall PLC_Recv_Interface_CellSerial(int index, int wordsToRead);

	PLC_DATA plc_Data;
	AnsiString plc_Read, plc_Read_Temp;
	bool plc_ReadFlag;
	int plc_ReadCount, plc_index;
	AnsiString plc_Interface;

//---------------------------------------------------------------------------
//	PC
//---------------------------------------------------------------------------
	void __fastcall PC_Initialization();
	void __fastcall PC_DataChange(int subCommand, int address, int devCode, int devLen);

	PC_DATA pc_Data;
	AnsiString pc_Read, pc_Read_Temp;
	bool pc_ReadFlag;
	int pc_ReadCount, pc_index;

//---------------------------------------------------------------------------
//	Tray Info
//---------------------------------------------------------------------------
	void __fastcall SaveTrayInfo(AnsiString trayID);
    AnsiString m_trayID;
	int m_slotNum, m_slotNumTemp;
public:		// User declarations
	__fastcall TMod_PLC(TComponent* Owner);

	void __fastcall Connect(AnsiString ip, int port1, int port2);
	void __fastcall DisConnect();

	void __fastcall SetData(unsigned char (*data)[2], int column, int num, bool flag);
	void __fastcall SetDouble(unsigned char (*data)[2], int column, double value);
	void __fastcall SetString(unsigned char (*data)[2], int column, AnsiString msg);

	int __fastcall GetData(unsigned char (*data)[2], int column, int num);
	double __fastcall GetDouble(unsigned char (*data)[2], int column);
	AnsiString __fastcall GetString(unsigned char (*data)[2], int column, int count);
//---------------------------------------------------------------------------
//  실제호출함수
	AnsiString __fastcall GetCellSrial(int stageno, int plc_address, int index, int size);
    AnsiString __fastcall GetCellSrialTrayId(int stageno, int plc_address, int size);
    double __fastcall GetCellSrialValue(int stageno, int plc_address);

    AnsiString __fastcall GetPlcString(int stageno, int plc_address, int size);
    double __fastcall GetPlcValue(int stageno, int plc_address);
    int __fastcall GetPlcData(int stageno, int plc_address, int bit_num);
    void __fastcall SetValue(int stageno, int pc_address, int value);
    double __fastcall GetValue(int stageno, int pc_address);
    void __fastcall SetSpecValue(int stageno, int pc_address, int value);
    void __fastcall SetVoltValue(int stageno, int pc_address, int index, int value);
    void __fastcall SetCurrValue(int stageno, int pc_address, int index, int value);
    int __fastcall GetVoltValue(int stageno, int pc_address, int index);
    int __fastcall GetCurrValue(int stageno, int pc_address, int index);

	bool PLC_Write_Result; //voltage, current 값은 필요 시에만 쓰기를 한다.
    //* PLC Data
    int currentPlcIndex;
    int currentReadTask;
    int CellSerialIndex;
	unsigned char plc_Interface_Data[2][PLC_D_INTERFACE_LEN][2];
    //unsigned char plc_Interface_Cell_Serial[PLC_D_CELL_SERIAL_LEN][2];
    //* PC Data
    int currentPcIndex;
    int currentWriteTask[2];
	unsigned char pc_Interface_Data[2][PC_D_INTERFACE_LEN][2];
    unsigned char pc_Interface_Volt_Data[2][PC_D_INTERFACE_VOLTAGE_LEN][2];
	unsigned char pc_Interface_Curr_Data[2][PC_D_INTERFACE_CURRENT_LEN][2];
};
//---------------------------------------------------------------------------
extern PACKAGE TMod_PLC *Mod_PLC;
//---------------------------------------------------------------------------
#endif
