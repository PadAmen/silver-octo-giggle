
// FlatUltDemo.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <initguid.h>
#include <setupapi.h>
#include "MUTGlobal.h"


// CFlatUltDemoApp:
// 有关此类的实现，请参阅 FlatUltDemo.cpp
//
DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE,
			0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);

#define PANDA_DEV_PID_VID	_T("vid_04b4&pid_8613")			//old dev
#define BEE1_DEV_PID_VID	_T("vid_04b4&pid_1004")			//new dev

class CMUTWndAppApp : public CWinAppEx
{
public:
	CMUTWndAppApp();

// 重写
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
private:
	CString m_ExeDirtory;
	CString m_dcmDirectory;
	CString m_exportDirectory;
	CString m_thumbnailImageDirectory;
	BOOL    m_IsUsbConnect;
	CString m_patientname;
	ULONG_PTR m_gdiplusToken;  //用于在关闭时，传递给GdiplusShutdown

	//BOOL	m_bCreateDcmDirctory;
public:
	CString GetExeDirtory(){return m_ExeDirtory;};
	CString GetDcmDirtory();
	CString GetThumbnailImageDirectory();
	CString GetAccessDirtory();
	CString GetImageDirtory();
	CString GetBinDirtory();
	CString GetExportDirectory();
	bool IsExportFileExist(CString strName){ return PathFileExists(strName)?TRUE:FALSE;};

public:
	int FindUSB();
	void InitializeMut();
	static UINT InitMutThreadProc(LPVOID lpParameter);
	bool CreateThumbnailDirectory();
	bool CreateDCMDirectory();
	bool CreateExportDirectory(CString patientname=APP_NULL_STR);
};

extern CMUTWndAppApp theApp;
extern TCHAR g_ExePath[256];