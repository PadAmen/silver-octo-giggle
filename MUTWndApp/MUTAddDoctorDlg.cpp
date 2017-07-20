// DoctorWnd.cpp : 实现文件
//

#include "stdafx.h"
/*#include "FlatUltDemo.h"*/
#include "MUTAddDoctorDlg.h"


// CDoctorWnd 对话框

IMPLEMENT_DYNAMIC(CMUTAddDoctorDlg, CDialog)

CMUTAddDoctorDlg::CMUTAddDoctorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTAddDoctorDlg::IDD, pParent)
	,m_bCheckAcessNow(TRUE)
	,m_bIsOverDlgSend(FALSE)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	m_AdoManger = CMUTDAOManagerFunc::GetDAOManager();
	newFont.CreatePointFont(APP_FONT_POINT1,APP_FONT_FACENAME1,NULL);//创建一个新的字体
}

CMUTAddDoctorDlg::~CMUTAddDoctorDlg()
{
}

void CMUTAddDoctorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_BTN, m_SearchBtn);
	DDX_Control(pDX, IDC_ADD_BTN, m_AddBtn);
	DDX_Control(pDX, IDC_SELECT_BTN, m_SelectBtn);
	DDX_Control(pDX, IDC_EXIT_BTN, m_ExitBtn);
	DDX_Control(pDX, IDC_INPUT_EDIT, m_InputEdit);
	DDX_Control(pDX, IDC_LIST1, m_DoctorList);
}


BEGIN_MESSAGE_MAP(CMUTAddDoctorDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ADD_BTN, &CMUTAddDoctorDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN, &CMUTAddDoctorDlg::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_EXIT_BTN, &CMUTAddDoctorDlg::OnBnClickedExitBtn)
	ON_BN_CLICKED(IDC_SELECT_BTN, &CMUTAddDoctorDlg::OnBnClickedSelectBtn)
	ON_MESSAGE(WM_LAST_WND,&CMUTAddDoctorDlg::OnRecvLastWnd)
END_MESSAGE_MAP()


// CDoctorWnd 消息处理程序
BOOL CMUTAddDoctorDlg::OnInitDialog()
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
BOOL CMUTAddDoctorDlg::InitWindow(void)
{
	
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;
	
	m_ExitBtn.ShowWindow(FALSE);
	m_InputEdit.ShowWindow(FALSE);

	return TRUE;
}
BOOL  CMUTAddDoctorDlg::InitComRect(void)
{
	CRect rct;
	CRect nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

	//m_SearchBtn.GetWindowRect(&rct);
	nowRect.left = (APP_SCREEN_WIDTH  - 2*DOCTOR_BORDER_SPACE 
	-DOCTOR_SEARCH_WIDTH - DOCTOR_EDIT_WIDTH - DOCTOR_EXIT_WIDTH)/2;
	nowRect.right = nowRect.left + DOCTOR_EXIT_WIDTH;
	nowRect.top = DOCTOR_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + DOCTOR_EXIT_HEIGHT;
	m_ExitBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + DOCTOR_BORDER_SPACE;
	nowRect.right = nowRect.left + DOCTOR_EDIT_WIDTH;
	nowRect.top = DOCTOR_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + DOCTOR_EDIT_HEIGHT;
	m_InputEdit.MoveWindow(&nowRect);

	nowRect.left = APP_SCREEN_WIDTH - DOCTOR_BORDER_SPACE - DOCTOR_SEARCH_WIDTH;
	nowRect.right = nowRect.left + DOCTOR_SEARCH_WIDTH;
	nowRect.top = DOCTOR_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + DOCTOR_SEARCH_HEIGHT;
	m_SearchBtn.MoveWindow(&nowRect);

	int width = APP_SCREEN_WIDTH - 2*DOCTOR_BORDER_SPACE;
	int height = APP_SCREEN_HEIGHT - 2*DOCTOR_BORDER_SPACE - 2*DOCTOR_SEARCH_HEIGHT;
	nowRect.left = DOCTOR_BORDER_SPACE;
	nowRect.right = nowRect.left + width;
	nowRect.top = nowRect.bottom + DOCTOR_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_DoctorList.MoveWindow(&nowRect);

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
BOOL CMUTAddDoctorDlg::InitComStyle(void)
{
	m_ExitBtn.DrawBorder(FALSE);	
	m_ExitBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_ExitBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_ExitBtn.SetPngMaps(APP_BACK_IMAGE,FALSE);
	
	m_SearchBtn.DrawBorder(FALSE);	
	m_SearchBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_SearchBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_SearchBtn.SetPngMaps(APP_SEARCH_IMAGE,FALSE);

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

	//m_DoctorList.AddString(_T("NI HO!"));
	m_DoctorList.SetFont(&newFont);
	m_SelectBtn.SetWindowText(_T("选定"));
	m_AddBtn.SetWindowText(_T("增加"));
	return TRUE;
}
HBRUSH CMUTAddDoctorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_LISTBOX)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_TEXT_COLOR1);
	}
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		m_InputEdit.CtlColor(pDC,nCtlColor);
	}

	return GetWndBkHBrush();
}
LRESULT CMUTAddDoctorDlg::OnRecvLastWnd(WPARAM wParam,LPARAM lParam)
{
// 	DWORD lastusr = (DWORD)lParam;
// 	if(lastusr != (DWORD)m_pScanbWnd)
// 	m_bIsOverDlgSend = TRUE;
	return 1;
}
void CMUTAddDoctorDlg::OnBnClickedAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	SetCheckAccess();
	this->ShowWindow(FALSE);
	::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_dcinfo_index,(LPARAM)this);
}

void CMUTAddDoctorDlg::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_bIsSearch = TRUE;
	m_InputEdit.SetSel(0, -1);
	m_InputEdit.Clear();

	m_SearchBtn.SetPngMaps(APP_CLOSE_IMAGE,FALSE);
	m_ExitBtn.ShowWindow(TRUE);
	m_InputEdit.ShowWindow(TRUE);
	
}

void CMUTAddDoctorDlg::OnBnClickedExitBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_bIsSearch = FALSE;
	m_SearchBtn.SetPngMaps(APP_SEARCH_IMAGE,FALSE);
	m_ExitBtn.ShowWindow(FALSE);
	m_InputEdit.ShowWindow(FALSE);
}

void CMUTAddDoctorDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	if(!m_bCheckAcessNow)  return;

	m_bCheckAcessNow = FALSE;
	CArray <CMUTDoctorInfoFunc> * pDoctor_list = m_AdoManger->getdoctors();
	m_DoctorList.ResetContent();
	for (int i = 0; i < pDoctor_list->GetSize(); i++)
	{
		CMUTDoctorInfoFunc tmpdoctor = pDoctor_list->GetAt(i);
		m_DoctorList.AddString(tmpdoctor.m_doctor_id+_T("    ")+tmpdoctor.m_doctor_username);
	}
	
}

void CMUTAddDoctorDlg::OnBnClickedSelectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	int select = m_DoctorList.GetCurSel();
	if(LB_ERR == select) return;

	m_DoctorList.GetText(select,m_SelectDoctor);
	this->ShowWindow(FALSE);
// 	if(!m_bIsOverDlgSend)
// 	{
		::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_sanb_index,(LPARAM)this);
		::SendMessage(m_pScanbWnd->GetSafeHwnd(),WM_ADD_DOCTOR,0,(LPARAM)&m_SelectDoctor);
// 	}
// 	else
// 	{
// 		m_bIsOverDlgSend = FALSE;
// 		::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_scanover_index,(LPARAM)this);
// 		//::SendMessage(m_pScanOverWnd->GetSafeHwnd(),WM_ADD_DOCTOR,0,(LPARAM)&m_SelectDoctor);
// 	}
}
