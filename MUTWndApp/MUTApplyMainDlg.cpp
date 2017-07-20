// ApplyWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTApplyMainDlg.h"
#include "MUTProcessDlg.h"
#include "MUTThreadOperaFunc.h"
#include "DevMemDC.h"

// CApplyWnd 对话框
#define  PERCENT_WIDTH		21/50

IMPLEMENT_DYNAMIC(CMUTApplyMainDlg, CDialog)

CMUTApplyMainDlg::CMUTApplyMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTApplyMainDlg::IDD, pParent)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
}

CMUTApplyMainDlg::~CMUTApplyMainDlg()
{
	
}

void CMUTApplyMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MENU_BTN, m_LeftBtn);
	DDX_Control(pDX, IDC_START_BTN, m_StartBtn);
	DDX_Control(pDX, IDC_UPDATE_BTN, m_UpdateBtn);
	DDX_Control(pDX, IDC_BTN_LINE, m_LineBtn);
	DDX_Control(pDX, IDC_BTN_CARVE, m_CurveBtn);
	DDX_Control(pDX, IDC_RADIO_LINE,m_RadioLineBtn);
	DDX_Control(pDX, IDC_RADIO_CURVE,m_RadioCurveBtn);
/*	DDX_Control(pDX, IDC_PROGRESS1, m_ProcessCtrl);*/
}


BEGIN_MESSAGE_MAP(CMUTApplyMainDlg, CDialog)
	//ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MENU_BTN, &CMUTApplyMainDlg::OnBnClickedMenuBtn)
	ON_BN_CLICKED(IDC_START_BTN, &CMUTApplyMainDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_UPDATE_BTN, &CMUTApplyMainDlg::OnBnClickedUpdateBtn)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RADIO_LINE, &CMUTApplyMainDlg::OnBnClickedRadioLine)
	ON_BN_CLICKED(IDC_RADIO_CURVE, &CMUTApplyMainDlg::OnBnClickedRadioCurve)
END_MESSAGE_MAP()
BOOL CMUTApplyMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("Apply Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}
	UpdateWindow();
	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}
BOOL CMUTApplyMainDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;
	m_AppMenu.GetHMainWnd(m_hMainWnd);
	return TRUE;
}
BOOL CMUTApplyMainDlg::InitComRect(void)
{
	CRect rct;
	CRect nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

	m_LeftBtn.GetWindowRect(&rct);
	CRect rcLeftBtn;
	rcLeftBtn.CopyRect(&rct);
	//szRightBtn.cx = rct.Width();
	//szRightBtn.cy = rct.Height();
	nowRect.CopyRect(&rct);
	nowRect.left = 0;
	nowRect.top = APP_SCREEN_HEIGHT - rcLeftBtn.Height();//szRightBtn.cy;
	nowRect.right = nowRect.left + rcLeftBtn.Width();//szRightBtn.cx;
	nowRect.bottom = nowRect.top + rcLeftBtn.Height();//szRightBtn.cy;
	m_LeftBtn.MoveWindow(nowRect);

	m_StartBtn.GetWindowRect(&rct);
	nowRect.left  = (APP_SCREEN_WIDTH - rct.Width())/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (APP_SCREEN_HEIGHT - rct.Height())/3;
	nowRect.bottom = nowRect.top + rct.Height();
	m_StartBtn.MoveWindow(nowRect);

	CWnd *pWnd = GetDlgItem(IDC_RADIO_LINE);
	pWnd->GetWindowRect(&rct);
	CRect temp;
	m_LineBtn.GetWindowRect(&temp);
	nowRect.left  = (APP_SCREEN_WIDTH - rct.Width())*PERCENT_WIDTH + (temp.Width()-rct.Width())/10;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = nowRect.bottom + APPLY_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + rct.Height();
	pWnd->MoveWindow(nowRect);

	pWnd = GetDlgItem(IDC_RADIO_CURVE);
	pWnd->GetWindowRect(&rct);
	nowRect.left  = (APP_SCREEN_WIDTH - rct.Width())*PERCENT_WIDTH + temp.Width() + APPLY_WIDTH_SPACE;
	nowRect.left += (temp.Width()-rct.Width())/10;
	nowRect.right = nowRect.left + rct.Width();
	//nowRect.top = nowRect.bottom + APPLY_HEIGHT_SPACE;
	//nowRect.bottom = nowRect.top + rct.Height();
	pWnd->MoveWindow(nowRect);

	m_LineBtn.GetWindowRect(&rct);
	nowRect.left  = (APP_SCREEN_WIDTH - rct.Width())*PERCENT_WIDTH ;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = nowRect.bottom + APPLY_GROUP_SPACE;
	nowRect.bottom = nowRect.top + rct.Height();
	m_LineBtn.MoveWindow(nowRect);

	m_CurveBtn.GetWindowRect(&rct);
	nowRect.left  += (rct.Width()+ APPLY_WIDTH_SPACE);
	nowRect.right = nowRect.left + rct.Width();
	//nowRect.top = nowRect.bottom + APPLY_HEIGHT_SPACE;
	//nowRect.bottom = nowRect.top + rct.Height();
	m_CurveBtn.MoveWindow(nowRect);

	m_UpdateBtn.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH - rct.Width() -APP_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = APP_SCREEN_HEIGHT - rct.Height();
	nowRect.bottom = nowRect.top + rct.Height();
	m_UpdateBtn.MoveWindow(nowRect);
	m_UpdatRect.CopyRect(&nowRect);

	m_AppMenu.GetParentSize(rcLeftBtn);
	m_AppMenu.Create(IDD_APPLY_MENU,this);
	m_AppMenu.GetWindowRect(&rct);
	nowRect.CopyRect(&rct);
	nowRect.left = rcLeftBtn.Width();
	nowRect.top = APP_SCREEN_HEIGHT - rcLeftBtn.Height();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	m_AppMenu.MoveWindow(nowRect);
	m_AppMenu.ShowWindow(FALSE);

	return TRUE;
}

BOOL CMUTApplyMainDlg::InitComStyle(void)
{

	m_LeftBtn.DrawBorder(FALSE);
	m_LeftBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_LeftBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_LeftBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_LeftBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_LeftBtn.SetPngMaps(APP_LEFT_IMAGE);

// 	m_StartBtn.DrawBorder(TRUE);
// 	m_StartBtn.SetWindowText(_T("开始检查"));
// 	m_StartBtn.SetAlign(ST_ALIGN_VERT);
// 	m_StartBtn.SetRounded(TRUE,FALSE);
// 	m_StartBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_INOUT);
// 	m_StartBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_INOUT);
//  m_StartBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
//  m_StartBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_StartBtn.SetShade(SHS_HARDBUMP,2,20,50,COLOR_BK_INOUT);
	m_StartBtn.DrawBorder(FALSE);

	m_LineBtn.LoadStdImage(IDB_LINE_PNG,_T("PNG"));
	m_CurveBtn.LoadStdImage(IDB_CURVE_PNG,_T("PNG"));
	//CButton * pLineRadio = (CButton *)GetDlgItem(IDC_RADIO_LINE);
	m_RadioLineBtn.LoadStdImage(IDB_SRADIO_PNG,_T("PNG"));
	m_RadioLineBtn.LoadAltImage(IDB_URADIO_PNG,_T("PNG"));
	m_RadioCurveBtn.LoadStdImage(IDB_URADIO_PNG,_T("PNG"));
	m_RadioCurveBtn.LoadAltImage(IDB_SRADIO_PNG,_T("PNG"));
	//m_RadioLineBtn.SetCheck(TRUE);
	
// 	m_UpdateBtn.DrawBorder(FALSE);	
// 	m_UpdateBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
// 	m_UpdateBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
// 	m_UpdateBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
// 	m_UpdateBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
// 	m_UpdateBtn.SetPngMaps(APP_ICON1_IMAGE,FALSE);
	BOOL bok = m_UpdateBtn.LoadStdImage(IDB_ICON_PNG2, _T("PNG"));
	m_UpdateBtn.SetImage(CGdipButton::STD_TYPE);

	return TRUE;
}
// CApplyWnd 消息处理程序
void CMUTApplyMainDlg::ResumeInitState()
{
	m_AppMenu.ShowWindow(FALSE);
}
HBRUSH CMUTApplyMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//pDC->SetTextColor(APP_TEXT_COLOR);

	return GetWndBkHBrush();
}

void CMUTApplyMainDlg::OnBnClickedMenuBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	/*m_AppMenu.ShowWindow(TRUE);*/
	if(!m_AppMenu.IsWindowVisible())
	{	
		//m_LeftBtn.SetWindowText(_T("<"));
		m_LeftBtn.SetPngMaps(APP_RIGHT_IMAGE);
		m_AppMenu.ShowWindow(TRUE);
	}
	else
	{	
		//m_LeftBtn.SetWindowText(_T(">"));
		m_LeftBtn.SetPngMaps(APP_LEFT_IMAGE);
		m_AppMenu.ShowWindow(FALSE);
	}
}
void CMUTApplyMainDlg::ShowProgress()
{
	CProgressCtrl *pProgress = (CProgressCtrl *)GetParent()->GetDlgItem(IDC_MAIN_PROGRESS);
	if(!pProgress->IsWindowVisible()) 
		pProgress->ShowWindow(TRUE);
}
void CMUTApplyMainDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	ShowProgress();	
	GetParent()->SetTimer(1,1000,NULL);	
	CMUTThreadOperaFunc *pThread = CMUTThreadOperaFunc::GetThreadOperation();
	pThread->DoActive(TYPE_SYSTEM_INIT);
}

void CMUTApplyMainDlg::OnBnClickedUpdateBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	SelectPageIndex(type_update_index);
	::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uSelectedIndex,(LPARAM)this);
}

BOOL CMUTApplyMainDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rct;
	this->GetClientRect(&rct);
	pDC->FillSolidRect(rct,APP_BK_COLOR1);
	return TRUE;
	//return __super::OnEraseBkgnd(pDC);
}

void CMUTApplyMainDlg::OnBnClickedRadioLine()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RadioLineBtn.SetImage(CGdipButton::STD_TYPE);
	m_RadioCurveBtn.SetImage(CGdipButton::STD_TYPE);
}

void CMUTApplyMainDlg::OnBnClickedRadioCurve()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RadioLineBtn.SetImage(CGdipButton::ALT_TYPE);
	m_RadioCurveBtn.SetImage(CGdipButton::ALT_TYPE);
}
