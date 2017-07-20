// FreezeBtmWnd.cpp : 实现文件
//

#include "stdafx.h"
/*#include "FlatUltDemo.h"*/
#include "MUTScanbFBtmCWnd.h"
#include "MUTImgProcFunc.h"
#include "MUTThreadOperaFunc.h"


// CFreezeBtmWnd 对话框

IMPLEMENT_DYNAMIC(CMUTScanbFBtmCWnd, CDialog)

CMUTScanbFBtmCWnd::CMUTScanbFBtmCWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbFBtmCWnd::IDD, pParent)
	,m_bIsMoiveRun(FALSE)
	, m_bIsList(FALSE)
{
	CMUTDlgBaseFunc::InitComStyle();
}

CMUTScanbFBtmCWnd::~CMUTScanbFBtmCWnd()
{
}

void CMUTScanbFBtmCWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_PLAY, m_PlayBtn);
	DDX_Control(pDX, IDC_BTN_MLIST, m_MListBtn);
	DDX_Control(pDX, IDC_SLIDER_MOIVE, m_MovSlider);
}


BEGIN_MESSAGE_MAP(CMUTScanbFBtmCWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CMUTScanbFBtmCWnd::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_MLIST, &CMUTScanbFBtmCWnd::OnBnClickedBtnMlist)
END_MESSAGE_MAP()


// CFreezeBtmWnd 消息处理程序
BOOL CMUTScanbFBtmCWnd::OnInitDialog()
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
BOOL CMUTScanbFBtmCWnd::InitWindow(void)
{
	if(TRUE != this->InitComRect()|| TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}

BOOL CMUTScanbFBtmCWnd::InitComRect(void)
{
	CRect rct,nowRect;
	CRect rcMainWnd;
	this->GetWindowRect(&rcMainWnd);

	m_MovSlider.GetWindowRect(&rct);
	nowRect.left = (rcMainWnd.Width() - rct.Width())/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (rcMainWnd.Height() - rct.Height())/4;
	nowRect.bottom = nowRect.top + rct.Height();
	m_MovSlider.MoveWindow(&nowRect);
	
	m_MListBtn.GetWindowRect(&rct);
	nowRect.left += (nowRect.Width() - rct.Width())/3;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MListBtn.MoveWindow(&nowRect);

	m_PlayBtn.GetWindowRect(&rct);
	nowRect.left += (SCANB_BTMWND_SPACE + nowRect.Width());
	nowRect.right = nowRect.left + rct.Width();
// 	nowRect.top = SCANB_LEFTWND_TOP;
// 	nowRect.bottom = nowRect.top + rct.Height();
	m_PlayBtn.MoveWindow(&nowRect);


	return TRUE;
}

BOOL CMUTScanbFBtmCWnd::InitComStyle(void)
{
	m_PlayBtn.DrawBorder(FALSE);
	m_PlayBtn.DrawTransparent(TRUE);
	m_PlayBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_PlayBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_PlayBtn.SetPngMaps(APP_OPEN_IMAGE);
	//m_PlayBtn.SetBitmaps(IDB_BMP_START);

	m_MListBtn.DrawBorder(TRUE);
	m_MListBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MListBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MListBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MListBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_MListBtn.SetPngMaps(APP_SINGLE_MODE_IMAGE);

	m_MovSlider.SetRange(SLIDER_RANGE_MIN,SLIDER_RANGE_MAX);
	m_MovSlider.SetPos(SLIDER_RANGE_MIN);

	return TRUE;
}
HBRUSH CMUTScanbFBtmCWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return GetWndBkHBrush();
}
void  CMUTScanbFBtmCWnd::ResumeInitState()
{
	m_PlayBtn.SetPngMaps(APP_OPEN_IMAGE);
	m_MListBtn.SetPngMaps(APP_SINGLE_MODE_IMAGE);
	m_MovSlider.SetRange(SLIDER_RANGE_MIN,SLIDER_RANGE_MAX);
	m_MovSlider.SetPos(SLIDER_RANGE_MIN);

}
void CMUTScanbFBtmCWnd::OnBnClickedBtnPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CMUTImgProcFunc *pImgPorc = CMUTImgProcFunc::GetImgProc();
	CMUTThreadOperaFunc *pThread = CMUTThreadOperaFunc::GetThreadOperation();
	if(!m_bIsMoiveRun)
	{
		m_bIsMoiveRun = TRUE;
		//pImgPorc->SetPlayMove(TRUE);
		pThread->m_cMoive.SetPlay();
		//this->SetRun(TRUE);
		m_PlayBtn.SetPngMaps(APP_FREEZE_IMAGE);
	}
	else
	{
		m_bIsMoiveRun = FALSE;
		pThread->m_cMoive.SetPlay(FALSE);
		//this->SetRun(FALSE);
		m_PlayBtn.SetPngMaps(APP_OPEN_IMAGE);
	}
}

void CMUTScanbFBtmCWnd::OnBnClickedBtnMlist()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bIsList)
	{
		m_bIsList = TRUE;
		m_MListBtn.SetPngMaps(APP_MULTI_MODE_IMAGE);
	}
	else
	{
		m_bIsList = FALSE;
		m_MListBtn.SetPngMaps(APP_SINGLE_MODE_IMAGE);
	}
}
