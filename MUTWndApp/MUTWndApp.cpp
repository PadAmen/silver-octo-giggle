
// FlatUltDemo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTWndAppDlg.h"
#include "MUTSplashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFlatUltDemoApp
TCHAR g_ExePath[256];
BEGIN_MESSAGE_MAP(CMUTWndAppApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFlatUltDemoApp ����
/*TCHAR g_ExePath[256];*/
CMUTWndAppApp::CMUTWndAppApp()
/*:m_bCreateDcmDirctory(TRUE)*/
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFlatUltDemoApp ����

CMUTWndAppApp theApp;

// CFlatUltDemoApp ��ʼ��

BOOL CMUTWndAppApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CMUTSplashDlg WndSplash;
	WndSplash.Create(IDB_START_BITMAP);
	WndSplash.UpdateWindow();
	InitializeMut();
	AfxEnableControlContainer();
// 	// ���� shell ���������Է��Ի������
// 	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
//	CShellManager *pShellManager = new CShellManager;
	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	WndSplash.DestroyWindow();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	if(GetModuleFileName(NULL,   g_ExePath,   256) == 0)
	{   
		return FALSE;   
	}
	(_tcsrchr(g_ExePath, _T('\\')))[1] = 0; //ɾ���ļ�����ע��·�������/����
	m_ExeDirtory.Format(_T("%s"),g_ExePath);
	
	LoadCursor(MAKEINTRESOURCE(IDC_NO));
	CMUTWndAppDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

// 	if(pShellManager)
// 	{
// 		delete pShellManager;
// 		pShellManager = NULL;
// 	}
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
int CMUTWndAppApp::ExitInstance()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	return CWinApp::ExitInstance();
}
// CString CMUTWndAppApp::GetDcmDirtory()
// {
// 	CString newdcmdirectory=_T("dicomfile");
// 	//CString strFilePath;
// 	//newdcmdirectory = datetime.Format(_T("dicomfile"));//fixme,replace it use patient id.
// 	CString strFilePath = m_ExeDirtory + _T("\\") + newdcmdirectory;
// 	if(!PathFileExists(strFilePath))
// 	{
// 		if (!CreateDirectory(strFilePath, NULL))
// 		{
// 			if (GetLastError() == ERROR_ALREADY_EXISTS)
// 			{
// 
// 			}	
// 			return APP_NULL_STR;
// 		}
// 	}
// // 		m_bCreateDcmDirctory = FALSE;
// // 	}
// 
// 	return strFilePath;
// }
bool CMUTWndAppApp::CreateThumbnailDirectory()
{

	CString strFilePath;
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, strFilePath.GetBuffer(MAX_PATH));
	strFilePath.ReleaseBuffer();

	int pos = strFilePath.ReverseFind('\\');
	strFilePath = strFilePath.Left(pos);

	strFilePath += _T("\\");
	strFilePath += _T("thumbnail");

	if (!CreateDirectory(strFilePath, NULL)) 
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_thumbnailImageDirectory = strFilePath;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		m_thumbnailImageDirectory = strFilePath;
		return true;
	}

}

bool CMUTWndAppApp::CreateDCMDirectory()
{

	CString strFilePath;
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, strFilePath.GetBuffer(MAX_PATH));
	strFilePath.ReleaseBuffer();

	int pos = strFilePath.ReverseFind('\\');
	strFilePath = strFilePath.Left(pos);

	strFilePath += _T("\\");
	strFilePath += _T("dcm");

	if (!CreateDirectory(strFilePath, NULL)) 
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_dcmDirectory = strFilePath;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		m_dcmDirectory = strFilePath;
		return true;
	}

}
bool CMUTWndAppApp::CreateExportDirectory(CString patientname)
{
	CString strFilePath;
	SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, strFilePath.GetBuffer(MAX_PATH));
	strFilePath.ReleaseBuffer();

	//int pos = strFilePath.ReverseFind('\\');
	//strFilePath = strFilePath.Left(pos);

	strFilePath += _T("\\");
	strFilePath += _T("export");

	m_patientname = patientname;
	if(!patientname.IsEmpty())
	{
		strFilePath += _T("\\");
		strFilePath += patientname;
	}

	if (!CreateDirectory(strFilePath, NULL)) 
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_exportDirectory = strFilePath;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		m_exportDirectory = strFilePath;
		return true;
	}
}
CString CMUTWndAppApp::GetDcmDirtory()
{
	if(!PathFileExists(m_dcmDirectory))
		CreateDCMDirectory();

	return m_dcmDirectory;

}
CString CMUTWndAppApp::GetExportDirectory()
{
	if(!PathFileExists(m_exportDirectory))
		CreateExportDirectory(m_patientname);

	return m_exportDirectory;
}
CString CMUTWndAppApp::GetThumbnailImageDirectory()
{
	if(!PathFileExists(m_thumbnailImageDirectory))
		CreateThumbnailDirectory();

	return m_thumbnailImageDirectory;

}
CString CMUTWndAppApp::GetImageDirtory()
{
	CString newimagedirectory =_T("ui-pic");
	newimagedirectory += +_T("\\");

	CString strImagePath  = m_ExeDirtory + newimagedirectory;

	return strImagePath;
}

CString CMUTWndAppApp::GetAccessDirtory()
{
	CString strAccessDirtory = m_ExeDirtory;

	return strAccessDirtory;
}
CString CMUTWndAppApp::GetBinDirtory()
{
	CString strBinPath = m_ExeDirtory + _T("bin");
	strBinPath += +_T("\\");
	
	return strBinPath;
}

int CMUTWndAppApp::FindUSB()
{
	HDEVINFO                         hDevInfo;
	SP_DEVICE_INTERFACE_DATA         DevIntfData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DevIntfDetailData;
	SP_DEVINFO_DATA                  DevData;

	DWORD dwSize, dwMemberIdx;//dwType,
	//HKEY hKey;
	BYTE lpData[1024];
	int ret = 0;
	// We will try to get device information set for all USB devices that have a
	// device interface and are currently present on the system (plugged in).
	hDevInfo = SetupDiGetClassDevs(
		&GUID_DEVINTERFACE_USB_DEVICE, NULL, 0, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (hDevInfo != INVALID_HANDLE_VALUE)
	{
		// Prepare to enumerate all device interfaces for the device information
		// set that we retrieved with SetupDiGetClassDevs(..)
		DevIntfData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
		dwMemberIdx = 0;

		// Next, we will keep calling this SetupDiEnumDeviceInterfaces(..) until this
		// function causes GetLastError() to return  ERROR_NO_MORE_ITEMS. With each
		// call the dwMemberIdx value needs to be incremented to retrieve the next
		// device interface information.

		SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &GUID_DEVINTERFACE_USB_DEVICE,
			dwMemberIdx, &DevIntfData);

		while (GetLastError() != ERROR_NO_MORE_ITEMS)
		{
			// As a last step we will need to get some more details for each
			// of device interface information we are able to retrieve. This
			// device interface detail gives us the information we need to identify
			// the device (VID/PID), and decide if it's useful to us. It will also
			// provide a DEVINFO_DATA structure which we can use to know the serial
			// port name for a virtual com port.

			DevData.cbSize = sizeof(DevData);

			// Get the required buffer size. Call SetupDiGetDeviceInterfaceDetail with
			// a NULL DevIntfDetailData pointer, a DevIntfDetailDataSize
			// of zero, and a valid RequiredSize variable. In response to such a call,
			// this function returns the required buffer size at dwSize.

			SetupDiGetDeviceInterfaceDetail(
				hDevInfo, &DevIntfData, NULL, 0, &dwSize, NULL);

			// Allocate memory for the DeviceInterfaceDetail struct. Don't forget to
			// deallocate it later!
			DevIntfDetailData =(PSP_DEVICE_INTERFACE_DETAIL_DATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize);
			DevIntfDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			if (SetupDiGetDeviceInterfaceDetail(hDevInfo, &DevIntfData,
				DevIntfDetailData, dwSize, &dwSize, &DevData))
			{
				// Finally we can start checking if we've found a useable device,
				// by inspecting the DevIntfDetailData->DevicePath variable.
				// The DevicePath looks something like this:
				//
				// \\?\usb#vid_04d8&pid_0033#5&19f2438f&0&2#{a5dcbf10-6530-11d2-901f-00c04fb951ed}
				//
				// The VID for Velleman Projects is always 10cf. The PID is variable
				// for each device:
				//
				//    -------------------
				//    | Device   | PID  |
				//    -------------------
				//    | K8090    | 8090 |
				//    | VMB1USB  | 0b1b |
				//    -------------------
				//
				// As you can see it contains the VID/PID for the device, so we can check
				// for the right VID/PID with string handling routines.

				if (NULL != _tcsstr((TCHAR*)DevIntfDetailData->DevicePath, BEE1_DEV_PID_VID)
					||NULL != _tcsstr((TCHAR*)DevIntfDetailData->DevicePath, PANDA_DEV_PID_VID))
				{
					// To find out the serial port for our K8090 device,
					// we'll need to check the registry:
					/*
					hKey = SetupDiOpenDevRegKey(
						hDevInfo,
						&DevData,
						DICS_FLAG_GLOBAL,
						0,
						DIREG_DEV,
						KEY_READ
						);

					dwType = REG_SZ;
					dwSize = sizeof(lpData);
					RegQueryValueEx(hKey, _T("PortName"), NULL, &dwType, lpData, &dwSize);
					RegCloseKey(hKey);
					*/
					// Eureka!
					printf("Found a device on port '%s'\n", lpData);
					ret = 1;
				}
			}

			HeapFree(GetProcessHeap(), 0, DevIntfDetailData);

			// Continue looping
			SetupDiEnumDeviceInterfaces(
				hDevInfo, NULL, &GUID_DEVINTERFACE_USB_DEVICE, ++dwMemberIdx, &DevIntfData);
		}

		SetupDiDestroyDeviceInfoList(hDevInfo);
	}

	return ret;
}
UINT  CMUTWndAppApp::InitMutThreadProc(LPVOID lpParameter)
{

	CEvent* pEvent = (CEvent*)(lpParameter);
	VERIFY(pEvent != NULL);

	// Wait for the event to be signaled
	::WaitForSingleObject(pEvent->m_hObject, INFINITE);
	// Do what you want here.
// 	if (!initParam())
// 	{
// 		AfxMessageBox(_T("��ʼ������ʧ��"));
// 	}
	Sleep(2000);
	// Terminate the thread
	::AfxEndThread(0, TRUE);

	return 0;
}

void CMUTWndAppApp::InitializeMut()
{
	CreateThumbnailDirectory();
	CreateDCMDirectory();
	GetExportDirectory();
	if (FindUSB()!=0)
	{
		m_IsUsbConnect = TRUE;//here, usb is plug in and device driver is ok.


	// Create the CEvent object that will be passed to the thread routine
		CEvent* pEvent = new CEvent(FALSE, FALSE);
		
		// Create a thread that will wait on the event
		CWinThread* pThread;

		pThread = ::AfxBeginThread(InitMutThreadProc, (LPVOID)pEvent, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
		pThread->m_bAutoDelete = FALSE;
		pThread->ResumeThread();

		// Signal the thread to do the next work item
		pEvent->SetEvent();

		// Wait for the thread to consume the event and return
		::WaitForSingleObject(pThread->m_hThread, INFINITE);
		delete pThread;
		delete pEvent;
	}
	else
	{
		//fake
		//AfxMessageBox(_T("�����豸ʧ��"));
		Sleep(2000);
	}

#if 1
	if (!initParam())
	{
		AfxMessageBox(_T("��ʼ������ʧ��"));
	}
#endif
}
