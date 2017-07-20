
// FlatUltDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTWndAppDlg.h"
#include <queue>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define		STR_CONFIG_PROCCED	  _T("配置中")
#define		STR_CONFIG_SUCCESS	  _T("配置成功")
#define		STR_CONFIG_ERR		  _T("配置失败")
#define		STR_CONFIG_ARROW	  _T(">")
#define		STR_CONFIG_CNT		  3
#define		DIALOG_VECTOR_CNT		  3
// CFlatUltDemoDlg 对话框


CMUTWndAppDlg::CMUTWndAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTWndAppDlg::IDD, pParent)
	,m_bInitDevEnd(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_BUTTER);

}

void CMUTWndAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_PROGRESS, m_ProcessCtrl);
}

BEGIN_MESSAGE_MAP(CMUTWndAppDlg, CDialog)

	ON_MESSAGE(WM_CHANGE_WND,&CMUTWndAppDlg::OnChangeWndMsg)
	ON_MESSAGE(WM_RTLAST_WND,&CMUTWndAppDlg::OnRtlastWndMsg)
	ON_MESSAGE(WM_WARNING_MSG,&CMUTWndAppDlg::OnWarningMsg)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()

END_MESSAGE_MAP()


// CFlatUltDemoDlg 消息处理程序
BOOL CMUTWndAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon


	m_ApplyDlg.SetHMainWnd(m_hWnd);
	m_ScanBDlg.SetHMainWnd(m_hWnd);
	m_AboutDlg.SetHMainWnd(m_hWnd);
	//m_DoctorDlg.SetHMainWnd(m_hWnd);
	//m_PatientDlg.SetHMainWnd(m_hWnd);

	CreatWindow();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("MUTWndAppDlg Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}

	TransParam();

	m_pShortKeyFunc = new CMUTShortKeyFunc(m_hWnd);	
	m_pThreadOpreation = CMUTThreadOperaFunc::GetThreadOperation();

	m_pThreadOpreation->Create(TYPE_SYSTEM_INIT,this);
	m_pThreadOpreation->Create(TYPE_READDATA_FORMUSB,&m_ScanBDlg);
	m_pThreadOpreation->Create(TYPE_GETDATA_FORMBUFFER,&m_ScanBDlg);

	m_pShortKeyFunc->SetStart();
	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}

void CMUTWndAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	CStatic	 *pText = (CStatic *)GetDlgItem(IDC_PROGRESS_TEXT);
	static int cnt=0;
	static int timecnt = 0;

	if(!IsConfigEnded())
	{
		static CString strConfig = STR_CONFIG_PROCCED;
		CString strArrow = STR_CONFIG_ARROW;

		if(cnt ++ < STR_CONFIG_CNT)
		{
			strConfig += strArrow;
		}
		else
		{
			cnt = 0;
			strConfig = STR_CONFIG_PROCCED;
		}
		pText->SetWindowText(strConfig);

		if(m_ProcessCtrl.GetPos() >= APP_PROGRESS_MAX)
		{
			pText->SetWindowText(STR_CONFIG_ERR);
			if(timecnt ++ >= 3)
			{
				timecnt = 0;
				cnt = 0;
				this->KillTimer(1);
				pText->ShowWindow(FALSE);
				m_ProcessCtrl.ShowWindow(FALSE);
				m_pThreadOpreation->DoActive(TYPE_GETDATA_AND_PROCESS);
				::SendMessage(m_hWnd,WM_CHANGE_WND,(WPARAM)type_sanb_index,(LPARAM)this);
			}
		}
		else
		{
			m_ProcessCtrl.StepIt();
		}

	}
	else
	{	
		cnt = 0;
		timecnt = 0;
		m_ProcessCtrl.SetPos(APP_PROGRESS_MAX);
		pText->SetWindowText(STR_CONFIG_SUCCESS);
		this->KillTimer(1);	
		pText->ShowWindow(FALSE);
		m_ProcessCtrl.ShowWindow(FALSE);
		m_pThreadOpreation->DoActive(TYPE_GETDATA_AND_PROCESS);
		::SendMessage(m_hWnd,WM_CHANGE_WND,(WPARAM)type_sanb_index,(LPARAM)this);
	}
}
void CMUTWndAppDlg::CreatWindow(void)
{
	m_ApplyDlg.Create(IDD_APPLY_DLG,this);
	m_ScanBDlg.Create(IDD_SCANB_DLG,this);
	m_AboutDlg.Create(IDD_ABOUT_DLG,this);
	m_DoctorDlg.Create(IDD_DOCTOR_DLG,this);
	m_PatientDlg.Create(IDD_PATIENT_DLG,this);
	m_ReportDlg.Create(IDD_REPORT_DLG,this);
	m_DoctorInfoDlg.Create(IDD_DCINFO_DLG,this);
	m_PatientInfoDlg.Create(IDD_PTINFO_DLG,this);
	m_EditImgDlg.Create(IDD_EDITIMG_DLG,this);
	m_ScanOverDlg.Create(IDD_SCANOVER_DLG,this);
	m_ReportInfoDlg.Create(IDD_REPORTINFO_DLG,this);
}
void CMUTWndAppDlg::TransParam(void)
{
	m_DoctorDlg.GetScanbPtr((DWORD)&m_ScanBDlg);
	//m_DoctorDlg.GetScanOverPtr((DWORD)&m_ScanOverDlg);
	m_PatientDlg.GetScanbPtr((DWORD)&m_ScanBDlg);
	//m_PatientDlg.GetScanOverPtr((DWORD)&m_ScanOverDlg);
	m_ScanOverDlg.GetScanbPtr((DWORD)&m_ScanBDlg);
	m_ScanOverDlg.GetAddDoctorPtr((DWORD)&m_DoctorDlg);
	m_ScanOverDlg.GetAddPatientPtr((DWORD)&m_PatientDlg);
	m_ReportInfoDlg.GetReportPtr((DWORD)&m_ReportDlg);
	m_EditImgDlg.GetReportInfoPtr((DWORD)&m_ReportInfoDlg);
	m_EditImgDlg.GetScanbMainPtr((DWORD)&m_ScanBDlg);
	m_EditImgDlg.GetScanOverPtr((DWORD)&m_ScanOverDlg);
}
void CMUTWndAppDlg::InitParam(void)
{
	m_ApplyDlg.ResumeInitState();
	m_ScanBDlg.ResumeInitState();
	SetConfigEnd(FALSE);						//重新计时
	//m_ScanBDlg.m_FreezeLeftWnd.ResumeAllState();

}
BOOL CMUTWndAppDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTWndAppDlg::InitComRect(void)
{
	CMUTDlgBaseFunc::InitComRect();

	CRect nowRect;
	CRect rct;
	GetAppWndRect(&rct);
	::SetWindowPos(this->GetSafeHwnd(), HWND_TOP,rct.left,rct.top
		,rct.Width(),rct.Height(), WS_EX_TOPMOST);
	
	CStatic *pTextStatic = (CStatic *)GetDlgItem(IDC_PROGRESS_TEXT);
	pTextStatic->GetWindowRect(&rct);
	nowRect.left = (APP_SCREEN_WIDTH -rct.Width())/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top  = (APP_SCREEN_HEIGHT - rct.Height())/2;
	nowRect.bottom = nowRect.top + rct.Height();
	pTextStatic->MoveWindow(&nowRect);

	m_ProcessCtrl.GetWindowRect(&rct);
	//nowRect.left = (APP_SCREEN_WIDTH -rct.Width())/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top  += APP_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + rct.Height();
	m_ProcessCtrl.MoveWindow(&nowRect);

	//m_ScanOverDlg.SetHScanbWnd(m_ScanBDlg.m_hWnd);
	

	return TRUE;
}
BOOL CMUTWndAppDlg::InitComStyle(void)
{
	CMUTDlgBaseFunc::InitComStyle();

	m_ApplyDlg.ShowWindow(TRUE);
	m_ScanBDlg.ShowWindow(FALSE);
	m_AboutDlg.ShowWindow(FALSE);
	m_DoctorDlg.ShowWindow(FALSE);
	m_PatientDlg.ShowWindow(FALSE);
	m_ReportDlg.ShowWindow(FALSE);
	m_DoctorInfoDlg.ShowWindow(FALSE);
	m_PatientInfoDlg.ShowWindow(FALSE);
	m_EditImgDlg.ShowWindow(FALSE);
	m_ScanOverDlg.ShowWindow(FALSE);
	m_ReportInfoDlg.ShowWindow(FALSE);

// 	m_DialogList.push_back(&m_ApplyDlg);
// 	m_DialogList.push_back(&m_ScanBDlg);
// 	m_DialogList.push_back(&m_AboutDlg);
// 	m_DialogList.push_back(&m_DoctorDlg);
// 	m_DialogList.push_back(&m_PatientDlg);
// 	m_DialogList.push_back(&m_ReportDlg);
// 	m_DialogList.push_back(&m_DoctorInfoDlg);
// 	m_DialogList.push_back(&m_PatientInfoDlg);
// 	m_DialogList.push_back(&m_EditImgDlg);
// 	m_DialogList.push_back(&m_ScanOverDlg);
// 	m_DialogList.push_back(&m_ReportInfoDlg);

	m_DialogChangeList.push_back(&m_ApplyDlg);			//应用初始窗口保存
	//m_pOldDialog=&m_ApplyDlg;

	CStatic *pTextStatic = (CStatic *)GetDlgItem(IDC_PROGRESS_TEXT);
	newFont.CreatePointFont(APP_FONT_POINT2,APP_FONT_FACENAME2,NULL);//创建一个新的字体
	pTextStatic->SetFont(&newFont);

	m_ProcessCtrl.SetRange(APP_PROGRESS_MIN,APP_PROGRESS_MAX);
	m_ProcessCtrl.SetPos(APP_PROGRESS_MIN);
	m_ProcessCtrl.SetStep(APP_STEP_VAL);
	m_ProcessCtrl.ShowWindow(FALSE);

	this->ShowWindow(FALSE);			//???
	return TRUE;
}

LRESULT CMUTWndAppDlg::OnRtlastWndMsg(WPARAM wParam,LPARAM lParam)
{
		int listcnt = m_DialogChangeList.size();
		if(listcnt < 2)      
			return 1;
		CDialog *pDialog = m_DialogChangeList.at(listcnt-1);
		if(pDialog == (CDialog*)&m_ScanBDlg				//当进入scanb scanover apply窗口后不能退回
			||pDialog == (CDialog*)&m_ScanOverDlg
			||pDialog == (CDialog *)&m_ApplyDlg
			)	
			return 1;
		pDialog->ShowWindow(FALSE);						//vector中最后一两个
		pDialog = m_DialogChangeList.at(listcnt-2);
		pDialog->ShowWindow(TRUE);	
		//pDialog->UpdateWindow();
		m_DialogChangeList.pop_back();
// 		if(m_DialogChangeList.size()>=DIALOG_VECTOR_CNT)		
// 		{
// 			m_DialogChangeList.back()->ShowWindow(FALSE);
// 			m_DialogChangeList.at(1)->ShowWindow(TRUE);
// 			m_DialogChangeList.erase(m_DialogChangeList.begin());
// 		}
// 		else
// 		{
		//	m_pLastDialog->ShowWindow(TRUE);
		//	m_pCurDialog->ShowWindow(FALSE);
		//}
//	}

	return TRUE;
}
LRESULT CMUTWndAppDlg::OnChangeWndMsg(WPARAM wParam,LPARAM lParam)
{
	m_pLastDialog = (CDialog *)lParam;
	switch(wParam)
	{
		case type_apply_index:
			m_ApplyDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_ApplyDlg;
			break;
		case type_sanb_index:
			m_ScanBDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_ScanBDlg;
			break;
		case type_update_index:
			m_AboutDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_AboutDlg;
			break;
		case type_doctor_index:
			m_DoctorDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_DoctorDlg;
			break;
		case type_patient_index:
			m_PatientDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_PatientDlg;
			break;
		case type_report_index:
			m_ReportDlg.ShowWindow(TRUE);
			m_ReportDlg.SetAcessCheck();
			m_pCurDialog = &m_ReportDlg;
			break;
		case type_dcinfo_index:
			m_DoctorInfoDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_DoctorInfoDlg;
			break;
		case type_ptinfo_index:
			m_PatientInfoDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_PatientInfoDlg;
			break;
		case type_editimg_index:
			m_EditImgDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_EditImgDlg;
			break;
		case type_scanover_index:
			m_ScanOverDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_ScanOverDlg;
			break;
		case type_reportinfo_index:
			m_ReportInfoDlg.ShowWindow(TRUE);
			m_pCurDialog = &m_ReportInfoDlg;
			break;		
		default:
			return FALSE;
			break;
	}

	//if(m_pOldDialog!=m_pCurDialog)							//保存不同窗口
	//{
		m_DialogChangeList.push_back(m_pCurDialog);				
// 		if(m_DialogChangeList.size() >= DIALOG_VECTOR_CNT)
// 		{
// 			m_DialogChangeList.erase(m_DialogChangeList.begin());
// 		}
//	}

//	m_pOldDialog = m_pCurDialog;

	return TRUE;
}
LRESULT CMUTWndAppDlg::OnWarningMsg(WPARAM wParam,LPARAM lParam)
{
	CString *pStr = (CString *)lParam;
	
	this->MessageBox(*pStr,_T("Error"), MB_ICONERROR);

	return TRUE;
}
BOOL CMUTWndAppDlg::DestroyWindow(void)
{
	m_pThreadOpreation->DeActive();
	if(m_pShortKeyFunc)
	{
		delete m_pShortKeyFunc;
		m_pShortKeyFunc = NULL;
	}

	return CDialog::DestroyWindow();
}
HBRUSH CMUTWndAppDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_MEATEXT_COLOR);

	}

	return GetWndBkHBrush();
}

LRESULT CMUTWndAppDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return CDialog::OnNcHitTest(point);
}

