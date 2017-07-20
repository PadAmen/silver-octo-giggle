// ApplyMenuWnd.cpp : 实现文件
//

#include "stdafx.h"
/*#include "FlatUltDemo.h"*/
#include "MUTApplyMenuCWnd.h"


// CApplyMenuWnd 对话框

IMPLEMENT_DYNAMIC(CMUTApplyMenuCWnd, CDialog)

CMUTApplyMenuCWnd::CMUTApplyMenuCWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTApplyMenuCWnd::IDD, pParent)
{
	InitComStyle();
}

CMUTApplyMenuCWnd::~CMUTApplyMenuCWnd()
{
}

void CMUTApplyMenuCWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_BTN, m_FileBtn);
	DDX_Control(pDX, IDC_SET_BTN, m_SetBtn);
	DDX_Control(pDX, IDC_TEACH_BTN, m_TeachBtn);
	DDX_Control(pDX, IDC_OPERATE_BTN, m_OperaBtn);
}


BEGIN_MESSAGE_MAP(CMUTApplyMenuCWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_TEACH_BTN, &CMUTApplyMenuCWnd::OnBnClickedTeachBtn)
	ON_BN_CLICKED(IDC_FILE_BTN, &CMUTApplyMenuCWnd::OnBnClickedFileBtn)
END_MESSAGE_MAP()
BOOL CMUTApplyMenuCWnd::OnInitDialog()
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
BOOL CMUTApplyMenuCWnd::GetParentSize(CRect rct)
{

	m_rcLeftBtn.CopyRect(&rct);

	return TRUE;
}
// CApplyMenuWnd 消息处理程序
BOOL CMUTApplyMenuCWnd::InitWindow(void)
{
	CRect rcWnd;
	CRect nowRct;

	this->GetWindowRect(&rcWnd);
	nowRct.left = 0;
	nowRct.top = 0;
	nowRct.right = rcWnd.Width();
	nowRct.bottom = m_rcLeftBtn.Height();
	MoveWindow(&nowRct);
	rcWnd.CopyRect(&nowRct);

	CRect rcBtn;
	m_FileBtn.GetWindowRect(&rcBtn);
	//nowRct.CopyRect(&rcBtn);
	nowRct.left = APPLY_MENU_LEFT;
	nowRct.right = nowRct.left + rcBtn.Width();
	nowRct.top = (rcWnd.Height()-rcBtn.Height())/2;
	nowRct.bottom = nowRct.top + rcBtn.Height();
	m_FileBtn.MoveWindow(&nowRct);

	m_FileBtn.DrawBorder(TRUE);
	m_FileBtn.SetRounded(TRUE);
	m_FileBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_FileBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_FileBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_FileBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	//m_SetBtn.GetWindowRect(&rcBtn);
	//nowRct.CopyRect(&rcBtn);
	nowRct.left = APPLY_MENU_LEFT+rcBtn.Width()+APPLY_MENU_SPACE;
	nowRct.right = nowRct.left + rcBtn.Width();
	nowRct.top = (rcWnd.Height()-rcBtn.Height())/2;
	nowRct.bottom = nowRct.top + rcBtn.Height();
	m_SetBtn.MoveWindow(&nowRct);

	m_SetBtn.DrawBorder(TRUE);
	m_SetBtn.SetRounded(TRUE);
	m_SetBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_SetBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_SetBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SetBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	//m_TeachBtn.GetWindowRect(&rcBtn);
	//nowRct.CopyRect(&rcBtn);
	nowRct.left = APPLY_MENU_LEFT+2*(rcBtn.Width()+APPLY_MENU_SPACE);
	nowRct.right = nowRct.left + rcBtn.Width();
	nowRct.top = (rcWnd.Height()-rcBtn.Height())/2;
	nowRct.bottom = nowRct.top + rcBtn.Height();
	m_TeachBtn.MoveWindow(&nowRct);

	m_TeachBtn.DrawBorder(TRUE);
	m_TeachBtn.SetRounded(TRUE);
	m_TeachBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_TeachBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_TeachBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_TeachBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	//m_OperaBtn.GetWindowRect(&rcBtn);
	//nowRct.CopyRect(&rcBtn);
	nowRct.left = APPLY_MENU_LEFT+3*(rcBtn.Width()+APPLY_MENU_SPACE);
	nowRct.right = nowRct.left + rcBtn.Width();
	nowRct.top = (rcWnd.Height()-rcBtn.Height())/2;
	nowRct.bottom = nowRct.top + rcBtn.Height();
	m_OperaBtn.MoveWindow(&nowRct);

	m_OperaBtn.DrawBorder(TRUE);
	m_OperaBtn.SetRounded(TRUE);
	m_OperaBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_OperaBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_OperaBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_OperaBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	return TRUE;
}



HBRUSH CMUTApplyMenuCWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	return GetWndBkHBrush();
}

void CMUTApplyMenuCWnd::OnBnClickedTeachBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(GetParent()->GetSafeHwnd(), _T("open"), _T("http://www.baidu.com"), NULL, NULL, SW_SHOWMAXIMIZED);
	//SHELLEXECUTEINFO	csSEI;

// 	memset(&csSEI, 0, sizeof(csSEI));
// 	csSEI.cbSize = sizeof(SHELLEXECUTEINFO);
// 	csSEI.fMask = SEE_MASK_FLAG_NO_UI;
// 	csSEI.lpVerb = _T("open");
// 	csSEI.lpFile = m_szURL;
// 	csSEI.nShow = SW_SHOWMAXIMIZED;
// 	::ShellExecuteEx(&csSEI);
}

void CMUTApplyMenuCWnd::OnBnClickedFileBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//GetParent()->ShowWindow(FALSE);
	//::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)type_report_index,(LPARAM)GetParent());
}
