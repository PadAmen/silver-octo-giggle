#pragma once
#include "MUTGlobal.h"
#include "MUTMoiveOperaFunc.h"
#include <queue>
using namespace std;
typedef struct tgImageInfo
{
	INT			iRows;			//行数
	INT			iColums;		//列数
	ULONG		dwFrame;		//帧数

	BYTE		pBuffer[MAX_FRAM_VALUE];//缓冲区
}TAGIMAGEINFO,*PTAGIMAGEINFO;

class CMUTThreadOperaFunc
{
public:
	CMUTThreadOperaFunc();
	~CMUTThreadOperaFunc(void);
	static CMUTThreadOperaFunc * GetThreadOperation();
	
	static DWORD WINAPI InitializingThread(LPVOID pParam);
	static DWORD WINAPI ReadDataFromUSB(LPVOID pParam);
	static DWORD WINAPI GetDataFromBuffer(LPVOID pParam);
private:
	HANDLE	m_hInitThread;
	HANDLE	m_hReceiveThread;
	HANDLE	m_hProcThread;
	volatile BOOL	m_bInit;
	volatile BOOL	m_bRead;			//是否读取USB
	volatile BOOL	m_bProcess;				//是否从buffer中获取数据
	HANDLE			m_hStartEvent;

	queue<PTAGIMAGEINFO>	m_queue;	//缓冲队列
	//CEvent	event;
public:
	CCriticalSection		m_CritSection;
	CMUTMoiveOperaFunc		m_cMoive;
	void	Create(INT type,LPVOID pVoid); 
	BOOL	IsInit()   {return m_bInit;};
	BOOL	IsReading(){return m_bRead;};
	BOOL	IsProcing(){return m_bProcess;};
	void	SetInitState(BOOL bInit=TRUE){m_bInit = bInit;};
	void	SetReadState(BOOL bRead=TRUE){m_bRead = bRead;};
	void	SetProcessState(BOOL bProcess=TRUE){m_bProcess = bProcess;};

	void	DoActive(INT type);
	void	PauseThread(INT type);
	BOOL	DeActive();
	void	AppendFrame(PWORD pData,int &iRows,int &iCoums,unsigned long &dwFrame);
	PBYTE	GetFrameData();
	void	SetStartEvent(){SetEvent(m_hStartEvent);};
	void	ResetStartEvent(){ResetEvent(m_hStartEvent);};
};
