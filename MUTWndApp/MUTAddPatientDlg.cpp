// PatientWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTAddPatientDlg.h"


// CPatientWnd 对话框

IMPLEMENT_DYNAMIC(CMUTAddPatientDlg, CDialog)

CMUTAddPatientDlg::CMUTAddPatientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTAddPatientDlg::IDD, pParent)
	,m_bIsCheckAccessNow(TRUE)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	m_AdoManger = CMUTDAOManagerFunc::GetDAOManager();
	newFont.CreatePointFont(APP_FONT_POINT,APP_FONT_FACENAME,NULL);//创建一个新的字体
	newFont1.CreatePointFont(APP_FONT_POINT1,APP_FONT_FACENAME1,NULL);
}

CMUTAddPatientDlg::~CMUTAddPatientDlg()
{
	newFont.DeleteObject();
}

void CMUTAddPatientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECT_BTN, m_SelectBtn);
	DDX_Control(pDX, IDC_ADD_BTN, m_AddBtn);
	DDX_Control(pDX, IDC_TEXT_BTN, m_TextBtn);
	DDX_Control(pDX, IDC_LIST1, m_PatientList);
}


BEGIN_MESSAGE_MAP(CMUTAddPatientDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CMUTAddPatientDlg::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMUTAddPatientDlg::OnBnClickedAddBtn)
	ON_MESSAGE(WM_LAST_WND,&CMUTAddPatientDlg::OnRecvLastWnd)
	ON_BN_CLICKED(IDC_SELECT_BTN, &CMUTAddPatientDlg::OnBnClickedSelectBtn)
END_MESSAGE_MAP()

// CPatientWnd 消息处理程序
BOOL CMUTAddPatientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("Apply Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}

	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}
BOOL CMUTAddPatientDlg::InitWindow(void)
{

	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;
	return TRUE;
}

BOOL CMUTAddPatientDlg::InitComRect(void)
{
	CRect rct;
	CRect nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

// 	nowRect.left = APP_SCREEN_WIDTH - DOCTOR_WIDTH_SPACE - DOCTOR_SEARCH_WIDTH;
// 	nowRect.right = nowRect.left + DOCTOR_SEARCH_WIDTH;
// 	nowRect.top = DOCTOR_HEIGHT_SPACE;
// 	nowRect.bottom = nowRect.top + DOCTOR_SEARCH_HEIGHT;
// 	m_SearchBtn.MoveWindow(&nowRect);

	int width = APP_SCREEN_WIDTH - 2*DOCTOR_BORDER_SPACE;
	int height = APP_SCREEN_HEIGHT - 2*DOCTOR_BORDER_SPACE - 2*DOCTOR_SEARCH_HEIGHT - 2*DOCTOR_HEIGHT_SPACE;
	nowRect.left = DOCTOR_BORDER_SPACE;
	nowRect.right = nowRect.left + width;
	nowRect.top =DOCTOR_BORDER_SPACE + DOCTOR_HEIGHT_SPACE + DOCTOR_SEARCH_HEIGHT;
	nowRect.bottom = nowRect.top + height;
	m_PatientList.MoveWindow(&nowRect);

	nowRect.left = (APP_SCREEN_WIDTH - PATIENT_TEXT_WIDTH)/2;
	nowRect.right = nowRect.left + PATIENT_TEXT_WIDTH;
	nowRect.top = DOCTOR_BORDER_SPACE;
	nowRect.bottom = nowRect.top + PATIENT_TEXT_HEIGHT;
	m_TextBtn.MoveWindow(&nowRect);

	width = (APP_SCREEN_WIDTH - 2*DOCTOR_BORDER_SPACE - DOCTOR_WIDTH_SPACE)/2; 
	nowRect.left = DOCTOR_BORDER_SPACE;
	nowRect.right = nowRect.left+width;
	nowRect.top = APP_SCREEN_HEIGHT - DOCTOR_BORDER_SPACE - DOCTOR_SEARCH_HEIGHT;
	nowRect.bottom = nowRect.top + DOCTOR_SEARCH_HEIGHT;
	m_SelectBtn.MoveWindow(&nowRect);

	nowRect.left = APP_SCREEN_WIDTH - DOCTOR_BORDER_SPACE - width;
	nowRect.right = nowRect.left+width;
	nowRect.top = APP_SCREEN_HEIGHT - DOCTOR_BORDER_SPACE - DOCTOR_SEARCH_HEIGHT;
	nowRect.bottom = nowRect.top + DOCTOR_SEARCH_HEIGHT;
	m_AddBtn.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTAddPatientDlg::InitComStyle(void)
{
	m_TextBtn.DrawBorder(FALSE);
	m_TextBtn.DrawTransparent(TRUE);
	m_TextBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_TextBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	
	m_SelectBtn.DrawBorder(FALSE);	
	m_SelectBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_SelectBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_SelectBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SelectBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_AddBtn.DrawBorder(FALSE);	
	m_AddBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_AddBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_AddBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_AddBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_PatientList.SetFont(&newFont1);
	m_TextBtn.SetFont(&newFont);
	m_TextBtn.SetWindowText(_T("病人信息列表"));
	m_SelectBtn.SetWindowText(_T("选定"));
	m_AddBtn.SetWindowText(_T("增加"));
	return TRUE;
}
LRESULT CMUTAddPatientDlg::OnRecvLastWnd(WPARAM wParam,LPARAM lParam)
{
// 	DWORD lastusr = (DWORD)lParam;
// 	if(lastusr != (DWORD)m_pScanbWnd)
// 		m_bIsOverDlgSend = TRUE;
	return 1;
}
HBRUSH CMUTAddPatientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_LISTBOX)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_TEXT_COLOR1);
	}

	return GetWndBkHBrush();
}

void CMUTAddPatientDlg::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMUTAddPatientDlg::OnBnClickedAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	SetCheckAccess();
	this->ShowWindow(FALSE);
	::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_ptinfo_index,(LPARAM)this);
}

void CMUTAddPatientDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	if(!m_bIsCheckAccessNow) return;
	m_bIsCheckAccessNow = FALSE;
	CArray <CMUTPatientInfoFunc> * pPatient_list = m_AdoManger->getpatients();
	m_PatientList.ResetContent();
	for (int i = 0; i < pPatient_list->GetSize(); i++)
	{
		CMUTPatientInfoFunc tmppatient = pPatient_list->GetAt(i);
		m_PatientList.InsertString(-1,tmppatient.m_patient_id+_T("    ")
			+tmppatient.m_patient_username+_T("    ")
			+tmppatient.m_patient_sex +_T("    ")
			+tmppatient.m_patient_birthday);
	}
}

void CMUTAddPatientDlg::OnBnClickedSelectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	int select = m_PatientList.GetCurSel();
	if(LB_ERR == select) return;
	m_PatientList.GetText(select,m_SelectPatient);
	this->ShowWindow(FALSE);
// 	if(!m_bIsOverDlgSend)
// 	{
		::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_sanb_index,(LPARAM)this);
		::SendMessage(m_pScanbWnd->GetSafeHwnd(),WM_ADD_PATIENT,0,(LPARAM)&m_SelectPatient);
// 	}
// 	else
// 	{
// 		::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_scanover_index,(LPARAM)this);
// 		//::SendMessage(m_pScanOverWnd->GetSafeHwnd(),WM_ADD_PATIENT,0,(LPARAM)&m_SelectPatient);
// 	}
}
