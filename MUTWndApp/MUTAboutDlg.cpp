// AboutWnd.cpp : 实现文件
//

#include "stdafx.h"
/*#include "MUT.h"*/
#include "MUTAboutDlg.h"


// CAboutWnd 对话框

IMPLEMENT_DYNAMIC(CMUTAboutDlg, CDialog)

CMUTAboutDlg::CMUTAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTAboutDlg::IDD, pParent)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
}

CMUTAboutDlg::~CMUTAboutDlg()
{
}

void CMUTAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABOUT_UBTN, m_UpdateBtn);
	DDX_Control(pDX, IDC_ICON_BTN, m_IconBtn);
	DDX_Control(pDX, IDC_STATIC_HARWARE, m_HardStatic);
	DDX_Control(pDX, IDC_STATIC_SOFTWARE, m_SoftStatic);
}


BEGIN_MESSAGE_MAP(CMUTAboutDlg, CDialog)
	//ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ABOUT_UBTN, &CMUTAboutDlg::OnBnClickedAboutUbtn)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CAboutWnd 消息处理程序
BOOL CMUTAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("About Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}

	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}
BOOL CMUTAboutDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTAboutDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

	//m_IconBtn.GetWindowRect()
	nowRect.left = (APP_SCREEN_WIDTH - ABOUT_ICON_WIDTH)/2;
	nowRect.right = nowRect.left + ABOUT_ICON_WIDTH;
	nowRect.top = ABOUT_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + ABOUT_ICON_HEIGHT;
	m_IconBtn.MoveWindow(&nowRect);

	m_UpdateBtn.GetWindowRect(&rct);
	nowRect.left = (APP_SCREEN_WIDTH - ABOUT_STATIC_LENGTH1 - rct.Width())/2;
	nowRect.right = nowRect.left + ABOUT_STATIC_LENGTH1;
	nowRect.top = nowRect.bottom + ABOUT_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + ABOUT_STATIC_HEIGHT1;
	m_SoftStatic.MoveWindow(&nowRect);
	
	nowRect.left = nowRect.right + ABOUT_WIDTH_SPACE;
	nowRect.right = nowRect.left + rct.Width();
	//nowRect.top = (SCANB_HEIGHT_SAPCE + rct.Height());
	//nowRect.bottom = nowRect.top + rct.Height();
	m_UpdateBtn.MoveWindow(&nowRect);

	nowRect.left = (APP_SCREEN_WIDTH - ABOUT_STATIC_LENGTH3)/2;
	nowRect.right = nowRect.left + ABOUT_STATIC_LENGTH3;
	nowRect.top = nowRect.bottom + ABOUT_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + ABOUT_STATIC_HEIGHT3;
	m_HardStatic.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTAboutDlg::InitComStyle(void)
{
	
	
	m_UpdateBtn.DrawBorder(FALSE);
	m_UpdateBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_UpdateBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_UpdateBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_UpdateBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_IconBtn.LoadStdImage(IDB_ICON_PNG2, _T("PNG"));
	m_IconBtn.SetImage(CGdipButton::STD_TYPE);


	m_UpdateBtn.SetWindowText(_T("检查更新"));
	m_SoftStatic.SetWindowText(_T("平板超声"));
	m_HardStatic.SetWindowText(_T("序列号:"));

	return TRUE;
}
HBRUSH CMUTAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return GetWndBkHBrush();
}


void CMUTAboutDlg::OnBnClickedAboutUbtn()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CMUTAboutDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rct;
	this->GetClientRect(&rct);
	pDC->FillSolidRect(rct,APP_BK_COLOR1);

	return TRUE;
}
