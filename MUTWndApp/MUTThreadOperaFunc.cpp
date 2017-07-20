#include "StdAfx.h"
#include "MUTThreadOperaFunc.h"
#include "MUTScanbMainDlg.h"
#include "MUTWndAppDlg.h"

#define WAIT_OBJECT_TIME		1000


CMUTThreadOperaFunc::CMUTThreadOperaFunc()
:m_bRead(FALSE)
,m_bProcess(FALSE)
,m_hReceiveThread(NULL)
{
	m_hStartEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	//SetEvent(m_hStartEvent);
}
CMUTThreadOperaFunc::~CMUTThreadOperaFunc(void)
{
	//DeActive();
	if(!m_queue.empty())
	{
		INT cnt = m_queue.size();
		for(int i=0;i<cnt;i++)
		{
			PTAGIMAGEINFO pInfo = m_queue.front();
			m_queue.pop();
			delete pInfo;
		}
		int xd = 0;
	}
}
CMUTThreadOperaFunc * CMUTThreadOperaFunc::GetThreadOperation()
{
	static CMUTThreadOperaFunc m_ThreadOpera;

	return &m_ThreadOpera;
}
void  CMUTThreadOperaFunc::DoActive(INT type)
{
	switch(type)
	{
		case TYPE_SYSTEM_INIT:
				ResumeThread(m_hInitThread);
				SetEvent(m_hStartEvent);			//add 8.16
				break;
		case TYPE_READDATA_FORMUSB:
				ResumeThread(m_hReceiveThread);
				break;
		case TYPE_GETDATA_FORMBUFFER:
				ResumeThread(m_hProcThread);
				break;
		case TYPE_GETDATA_AND_PROCESS:
				ResumeThread(m_hReceiveThread);
				ResumeThread(m_hProcThread);
				break;

		default: break;
		
	}
}
void CMUTThreadOperaFunc::PauseThread(INT type)
{
	switch(type)
	{
	case TYPE_SYSTEM_INIT:
		SuspendThread(m_hInitThread);
		ResetEvent(m_hStartEvent);			//add 8.16
		break;
	case TYPE_READDATA_FORMUSB:
		SuspendThread(m_hReceiveThread);
		break;
	case TYPE_GETDATA_FORMBUFFER:
		SuspendThread(m_hProcThread);
		break;
	case TYPE_GETDATA_AND_PROCESS:
		SuspendThread(m_hReceiveThread);
		SuspendThread(m_hProcThread);
		break;

	default: break;

	}
}
void CMUTThreadOperaFunc::AppendFrame(PWORD pData,int &iRows,int &iCoums,unsigned long &dwFrame)
{
	if(pData == NULL) 
		return;

	CSingleLock singleLock(&m_CritSection);
	singleLock.Lock();
	INT count = m_queue.size(); 
	if(count >= QUEUE_MAX_VALUE)
	{
		PTAGIMAGEINFO pInfo = m_queue.front();
		m_queue.pop();
		delete pInfo;
	}
	PTAGIMAGEINFO pInfo=new TAGIMAGEINFO;
	pInfo->iRows = iRows;
	pInfo->iColums = iCoums;
	pInfo->dwFrame = dwFrame;
	memcpy(pInfo->pBuffer,pData,MAX_FRAM_VALUE);
	m_queue.push(pInfo);
	//singleLock.Unlock();
}

PBYTE CMUTThreadOperaFunc::GetFrameData()
{
	CSingleLock singleLock(&m_CritSection);
	singleLock.Lock();
	if(m_queue.size() > 0)
	{
		PTAGIMAGEINFO pInfo = m_queue.back();
		return &pInfo->pBuffer[0];
	}
	//singleLock.Unlock();
	return NULL;
}
void  CMUTThreadOperaFunc::Create(INT type,LPVOID pVoid)
{
	switch(type)
	{
		case TYPE_SYSTEM_INIT:
			if(IsInit())	return;
			SetInitState();
			m_hInitThread=CreateThread(NULL,0,&CMUTThreadOperaFunc::InitializingThread,pVoid,CREATE_SUSPENDED,NULL);
			SetThreadPriority(m_hInitThread,THREAD_PRIORITY_NORMAL);
			break;
		case TYPE_READDATA_FORMUSB:	
			if(IsReading()) return;
			SetReadState();
			m_hReceiveThread=CreateThread(NULL,0,&CMUTThreadOperaFunc::ReadDataFromUSB,pVoid,CREATE_SUSPENDED,NULL);
			SetThreadPriority(m_hReceiveThread,THREAD_PRIORITY_HIGHEST);
			break;

		case TYPE_GETDATA_FORMBUFFER:
			if(IsProcing())	return;
			SetProcessState();
			m_hProcThread=CreateThread(NULL,0,&CMUTThreadOperaFunc::GetDataFromBuffer,pVoid,CREATE_SUSPENDED,NULL);
			SetThreadPriority(m_hProcThread,THREAD_PRIORITY_HIGHEST);
			break;
		default: 
			break;
	}

}
BOOL  CMUTThreadOperaFunc::DeActive()
{	
	if(IsProcing())
	{
		SetProcessState(FALSE);
		if(WAIT_OBJECT_0 != WaitForSingleObject(m_hProcThread,WAIT_OBJECT_TIME))//放在读取线程后停止处理线程程序会死锁 ？？？
		{
			DWORD dwCode=0;
			TerminateThread(m_hProcThread,dwCode);
		}			
		CloseHandle(m_hProcThread);
		m_hProcThread = NULL;
	}

	if(IsReading())
	{
		//SetExit();
		setRun(FALSE);	
		SetReadState(FALSE);	
		WaitForSingleObject(m_hReceiveThread,WAIT_OBJECT_TIME);
		CloseHandle(m_hReceiveThread);
		m_hReceiveThread=NULL;
	}	
	
	CloseHandle(m_hInitThread);

	return TRUE;
}
DWORD WINAPI CMUTThreadOperaFunc::InitializingThread(LPVOID pParam)				//未添加事件处理
{
	CMUTWndAppDlg *pDlg = (CMUTWndAppDlg *)pParam;
	CMUTThreadOperaFunc *pThread = CMUTThreadOperaFunc::GetThreadOperation();
	CString strPath = theApp.GetBinDirtory();
	CString strBinName	= APP_BIN_NEWNAME;
	strPath += strBinName;
	BOOL bFirst = FALSE,bSecond = FALSE;

	while(1)
	{

		WaitForSingleObject(pThread->m_hStartEvent,INFINITE);			//等待开始信号

		if (!bFirst)	
		{
			bFirst = TRUE;
			if(!ConfigDevice(strPath))
			pDlg->MessageBox(_T("设备配置失败"),_T("Error"), MB_ICONERROR);
			//str.Format(_T("设备配置失败"));
			//::SendMessage(m_hWnd,WM_WARNING_MSG,0,(LPARAM)&str);
			//return 1;
		}
		if (!bSecond)
		{
			bSecond = TRUE;
			if(!initSystem())
			pDlg->MessageBox(_T("初始化系统失败"),_T("Error"), MB_ICONERROR);
			//str.Format(_T("初始化系统失败"));
			//::SendMessage(m_hWnd,WM_WARNING_MSG,0,(LPARAM)&str);
			//return 1;
		}
		
		pDlg->InitParam();												//TEST				
		pDlg->SetConfigEnd();

		ResetEvent(pThread->m_hStartEvent);								//置位信号
	}

	

	return 0;
}
DWORD WINAPI CMUTThreadOperaFunc::ReadDataFromUSB(LPVOID pParam)
{
	CMUTScanbMainDlg * pDlg = (CMUTScanbMainDlg *)pParam;
	CMUTImgProcFunc *pImgProc = CMUTImgProcFunc::GetImgProc();
	CMUTThreadOperaFunc *pThread = CMUTThreadOperaFunc::GetThreadOperation();

	unsigned long dwFrame;
	while(pThread->IsReading())
	{	
		if(pDlg->IsRun())
		{
			INT iRows = IMG_DIS_WIDTH,iColums = IMG_DIS_HEIGHT;
			unsigned short* pdata = getImageData(iRows, iColums, dwFrame);
			//if(pImgProc->GetUsbData(pdata,iRows,iColums,dwFrame) != FALSE)
			if(pdata != NULL) 
				pImgProc->CountFPS();
			else
				pImgProc->SetFPS(0);

			pThread->AppendFrame(pdata,iRows,iColums,dwFrame);
		}
		Sleep(1);
	}
	return 0;
}
DWORD WINAPI CMUTThreadOperaFunc::GetDataFromBuffer(LPVOID pParam)
{
	CMUTThreadOperaFunc *pThread = CMUTThreadOperaFunc::GetThreadOperation();
	CMUTScanbMainDlg * pDlg = (CMUTScanbMainDlg *)pParam;
	CMUTDibFunc	 dib,olddib;
	CRect nowRect;
	BOOL bFirst=FALSE;
	//unsigned long dwFrame;
	CmySliderControl *pSlider = (CmySliderControl *)pDlg->m_FreezeBtmWnd.GetDlgItem(IDC_SLIDER_MOIVE);
	while(pThread->IsProcing())
	{
	
		pDlg->SetTextFreq(getFreq());
		pDlg->SetTextFps(pDlg->m_pImgProc->GetFpsValue());

		CDC *pDC = pDlg->GetDC();
		pDC->SelectClipRgn(&pDlg->m_ImgRgn);
		nowRect.CopyRect(&pDlg->GetImageRect());
		nowRect.bottom = nowRect.top + pDlg->m_RunLeftWnd.GetDistance();	
		
		if(pDlg->IsRun())	//是否冻结												//1.冻结则显示前一帧图像
		{																			//2.播放影像则从buffer中取保存影像
			bFirst = TRUE;															//3.正常则从缓冲队列中取数据并处理为图像
			//INT iRows = IMG_DIS_WIDTH,iColums = IMG_DIS_HEIGHT;
			//unsigned short* pdata = getImageData(iRows, iColums, dwFrame);
			pDlg->m_pImgProc->ProcessGetData(dib,(PBYTE)pThread->GetFrameData(),nowRect);	//
			pThread->m_cMoive.InsertFrame(dib);
			pDlg->m_pImgProc->DrawImage(pDC,nowRect,pDlg->GetFlipImage());	
			
		}
		else
		{
			if(bFirst)														//显示冻结前一帧  ???
			{
				bFirst = FALSE;
				UINT index = pThread->m_cMoive.GetEndIndex();
				pSlider->SetRange(SLIDER_RANGE_MIN,index);			
			}

			if(pThread->m_cMoive.IsPlay())									//循环播放影像
			{
				pThread->m_cMoive.GetFrame(dib);
				pDlg->m_pImgProc->TransDib(dib);							//当前图像传送给处理对象
				pSlider->SetPos(pThread->m_cMoive.GetStartIndex());
				pDlg->m_pImgProc->DrawImage(pDC,nowRect,pDlg->GetFlipImage());
			}
// 			else															//影像选择显示
// 			{
// 				INT index = pSlider->GetPos();
// 				pThread->m_cMoive.GetFrameFromIndex(dib,index);	
// 				pDlg->m_pImgProc->TransDib(dib);
// 			}
			
		}

		pDlg->SetImageRect(nowRect);										
		pDlg->m_ImgRgn.SetRectRgn(&nowRect);								
		pDlg->ReleaseDC(pDC);
		
		Sleep(100);
	}
	return 0;
}