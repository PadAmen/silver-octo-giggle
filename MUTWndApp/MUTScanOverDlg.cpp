// MUTScanOverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanOverDlg.h"
#include "MUTFileOperaFunc.h"
#include "MUTWndApp.h"


// CMUTScanOverDlg 对话框

IMPLEMENT_DYNAMIC(CMUTScanOverDlg, CDialog)

CMUTScanOverDlg::CMUTScanOverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanOverDlg::IDD, pParent)
	,m_bIsUpdate(FALSE)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	m_pThread = CMUTThreadOperaFunc::GetThreadOperation();
}

CMUTScanOverDlg::~CMUTScanOverDlg()
{
}

void CMUTScanOverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAVE_BTN, m_SaveBtn);
	DDX_Control(pDX, IDC_GIVEUP_BTN, m_GiveupBtn);
	DDX_Control(pDX, IDC_EXPORT_BTN, m_ExportBtn);
	DDX_Control(pDX, IDC_SEND_BTN, m_SendBtn);
	DDX_Control(pDX, IDC_LIST1, m_ReportList1);
	DDX_Control(pDX, IDC_DOCTOR_SELECT_BTN, m_SelectDoctorBtn);
	DDX_Control(pDX, IDC_PATIENT_SELECT_BTN, m_SelectPatientBtn);
}


BEGIN_MESSAGE_MAP(CMUTScanOverDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SAVE_BTN, &CMUTScanOverDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_GIVEUP_BTN, &CMUTScanOverDlg::OnBnClickedGiveupBtn)
	ON_MESSAGE(WM_ADD_DOCTOR,&CMUTScanOverDlg::OnAddDoctor)
	ON_MESSAGE(WM_ADD_PATIENT,&CMUTScanOverDlg::OnAddPatient)
	ON_BN_CLICKED(IDC_DOCTOR_SELECT_BTN, &CMUTScanOverDlg::OnBnClickedDoctorSelectBtn)
	ON_BN_CLICKED(IDC_PATIENT_SELECT_BTN, &CMUTScanOverDlg::OnBnClickedPatientSelectBtn)
END_MESSAGE_MAP()


// CMUTScanOverDlg 消息处理程序
BOOL CMUTScanOverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("CMUTScanOverDlg InitWindow Err!"));
		goto NORMAL_EXIT;
	}

	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}

BOOL CMUTScanOverDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTScanOverDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.CopyRect(&nowRect);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

	m_SaveBtn.GetWindowRect(&rct);
	nowRect.left = SCANOVER_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = APP_SCREEN_HEIGHT - rct.Height() - SCANOVER_BORDER_WIDTH;
	nowRect.bottom = nowRect.top +rct.Height();
	m_SaveBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + SCANOVER_SPACE_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	m_ExportBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + SCANOVER_SPACE_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	m_SendBtn.MoveWindow(&nowRect);

	m_GiveupBtn.GetWindowRect(&rct);
	nowRect.left =nowRect.right + SCANOVER_SPACE_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	m_GiveupBtn.MoveWindow(&nowRect);

	nowRect.left = SCANOVER_BORDER_WIDTH;
	nowRect.right = APP_SCREEN_WIDTH - SCANOVER_BORDER_WIDTH;
	nowRect.top = SCANOVER_BORDER_WIDTH;
	nowRect.bottom = APP_SCREEN_HEIGHT/2;
	m_ReportList1.MoveWindow(&nowRect);

	int height = (APP_SCREEN_HEIGHT - rct.Height() - nowRect.Height() 
		- 8*SCANOVER_SPACE_HEIGHT -SCANOVER_BORDER_WIDTH)/2;
	nowRect.left = SCANOVER_BORDER_WIDTH;
	nowRect.right = (APP_SCREEN_WIDTH - SCANOVER_BORDER_WIDTH)/2;
	nowRect.top = nowRect.bottom + SCANOVER_SPACE_HEIGHT;
	nowRect.bottom = nowRect.top + height;
	m_SelectDoctorBtn.MoveWindow(&nowRect);

	nowRect.top = nowRect.bottom + SCANOVER_SPACE_HEIGHT;
	nowRect.bottom = nowRect.top + height;
	m_SelectPatientBtn.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTScanOverDlg::InitComStyle(void)
{
	m_SaveBtn.DrawBorder(TRUE);
	m_SaveBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_SaveBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_SaveBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SaveBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_ExportBtn.DrawBorder(TRUE);
	m_ExportBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_ExportBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_ExportBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_ExportBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_SendBtn.DrawBorder(TRUE);
	m_SendBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_SendBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_SendBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SendBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_GiveupBtn.DrawBorder(TRUE);
	m_GiveupBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_GiveupBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_GiveupBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_GiveupBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_SelectDoctorBtn.DrawBorder(TRUE);
	m_SelectDoctorBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_SelectDoctorBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_SelectDoctorBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SelectDoctorBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_SelectPatientBtn.DrawBorder(TRUE);
	m_SelectPatientBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_SelectPatientBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_SelectPatientBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SelectPatientBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_ReportList1.SetBkColor(APP_BK_COLOR1);
	m_ReportList1.CreateColumn();

	return TRUE;
}
HBRUSH CMUTScanOverDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何属性

// 	if(nCtlColor == CTLCOLOR_BTN)
// 	{
// 		pDC->SetBkColor(TRANSPARENT);
// 		pDC->SetTextColor(RGB(250,250,250));
// 		return (HBRUSH)GetStockObject(NULL_BRUSH);
// 	}

	return GetWndBkHBrush();
}
bool CMUTScanOverDlg::DeleteDirectoryAndFiles(CString directoryname)
{
	CMUTFileOperaFunc::DeleteDirectoryAndFiles(m_fileOpStruct, directoryname, 0);
	return true;
}
void CMUTScanOverDlg::OnBnClickedSaveBtn()								
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	if(!m_pScanbDlg->AddInfoToAccess())								//存入数据库
	{
		AfxMessageBox(_T("Add Info To Access Fail!"));
	}		
	::SendMessage(m_pScanbDlg->GetSafeHwnd(),WM_CLEAR_VECTOR,0,NULL);
	::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,type_apply_index,NULL);
	//m_pThread->PauseThread(TYPE_GETDATA_AND_PROCESS);
	setRun(FALSE);
}
// void CMUTScanOverDlg::deleteFilesAll()
// {
// 	CString imageFilePath = theApp.GetThumbnailImageDirectory();
// 	imageFilePath += _T("//") + imagedirectory + _T("//") + imageSavedArray.ElementAt(m_selected_image_index);
// 
// 	DeleteFile(imageFilePath);
// 
// 	CString dcmFilePath = theApp.getDcmDirectory();
// 	CString filename = imageSavedArray.ElementAt(m_selected_image_index);
// 	filename.Replace(_T("bmp"), _T("dcm"));
// 	dcmFilePath += _T("//") + imagedirectory + _T("//") + filename;
// 	DeleteFile(dcmFilePath);
// }
void CMUTScanOverDlg::OnBnClickedGiveupBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	CString dcmdir = theApp.GetDcmDirtory();
	dcmdir += _T("\\");
	//DeleteDirectoryAndFiles(theApp.GetThumbnailImageDirectory());	//删除路径及文件
	for(int ik=0;ik<m_pScanbDlg->m_DcmSavedArray.GetSize();ik++)
	{
		CString filename = m_pScanbDlg->m_DcmSavedArray.GetAt(ik);	
		filename = dcmdir + filename;
		if(!PathFileExists(dcmdir))		
			continue;		
		DeleteFile(filename);										//删除当前保存文件
	}
	CString imgagedir = theApp.GetThumbnailImageDirectory();
	imgagedir += _T("\\");
	for(int im =0;im<m_pScanbDlg->m_imageSavedArray.GetSize();im++)
	{
		CString filename = m_pScanbDlg->m_imageSavedArray.GetAt(im);
		//CString imagedir = dir + filename;
		filename = imgagedir +filename;
		if(!PathFileExists(dcmdir))
			continue;
		DeleteFile(filename);											//删除当前保存文件
	}
	::SendMessage(m_pScanbDlg->GetSafeHwnd(),WM_CLEAR_VECTOR,0,NULL);
	::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,type_apply_index,NULL);

	//m_pThread->PauseThread(TYPE_GETDATA_AND_PROCESS);
	setRun(FALSE);
}

void CMUTScanOverDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
// 	if(!m_bIsUpdate) return;
// 	m_bIsUpdate = TRUE;
	m_ReportList1.Clear();
	CString imagedir = theApp.GetThumbnailImageDirectory() ;
	m_ReportList1.m_strImageDir = imagedir;
	imagedir += _T("\\");
	for(int im =0;im<m_pScanbDlg->m_imageSavedArray.GetSize();im++)
	{
		CString filename = m_pScanbDlg->m_imageSavedArray.GetAt(im);
		CString imagefiledir  = imagedir + filename;
		if(!PathFileExists(imagefiledir))
			continue;
		m_ReportList1.m_VectorImageNames.push_back(filename);
	}
	m_ReportList1.Load();
	CString doctor = m_pScanbDlg->GetCurSelectDoctor();
	CString patient = m_pScanbDlg->GetCurSelectPatient();

	if(doctor.IsEmpty())
	m_SelectDoctorBtn.SetWindowText(_T("请选择一名医生!"));
	else
	m_SelectDoctorBtn.SetWindowText(_T("扫描医生:")+doctor);
	if(patient.IsEmpty())
	m_SelectPatientBtn.SetWindowText(_T("请选择一名患者!"));
	else
	m_SelectPatientBtn.SetWindowText(_T("患者:")+patient);
}
LRESULT CMUTScanOverDlg::OnAddDoctor(WPARAM wParam,LPARAM lParam)
{
	CString *pStr = (CString *)lParam;
	TCHAR pBuf[256];
	memset(pBuf,0,sizeof(pBuf));
	int id;
	CString doctorname;
	swscanf(pStr->GetBuffer(),_T("%d%s"),&id,&pBuf);
	doctorname.Format(_T("%s"),pBuf);
	m_SelectDoctorBtn.SetWindowText(_T("扫描医生:")+doctorname);

	return 1;
}
LRESULT CMUTScanOverDlg::OnAddPatient(WPARAM wParam,LPARAM lParam)
{
	CString *pStr = (CString *)lParam;
	TCHAR pBuf[256];
	memset(pBuf,0,sizeof(pBuf));
	int id;
	swscanf(pStr->GetBuffer(),_T("%d%s%s%s"),&id,&pBuf[0],&pBuf[32],&pBuf[64]);
	CString patientname;
	patientname.Format(_T("%s"),pBuf);
	m_SelectPatientBtn.SetWindowText(_T("患者:")+patientname);
	return 1;
}
void CMUTScanOverDlg::OnBnClickedDoctorSelectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	GetParent()->SendMessage(WM_CHANGE_WND,type_doctor_index,(LPARAM)this);
	::SendMessage(m_pAddDoctorDlg->GetSafeHwnd(),WM_LAST_WND,0,(LPARAM)this);
}

void CMUTScanOverDlg::OnBnClickedPatientSelectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	GetParent()->SendMessage(WM_CHANGE_WND,type_patient_index,(LPARAM)this);
	::SendMessage(m_pAddPatientDlg->GetSafeHwnd(),WM_LAST_WND,0,(LPARAM)this);
}
