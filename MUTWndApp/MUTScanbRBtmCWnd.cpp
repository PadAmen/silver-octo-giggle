// RunBtmWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanbRBtmCWnd.h"

#define  INIT_GAIN_VALUE	70
// CRunBtmWnd 对话框

IMPLEMENT_DYNCREATE(CMUTScanbRBtmCWnd, CDialog)

CMUTScanbRBtmCWnd::CMUTScanbRBtmCWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbRBtmCWnd::IDD,pParent)
	,m_OrganIndex(ogran_little_index)
{
	CMUTDlgBaseFunc::InitComStyle();
}

CMUTScanbRBtmCWnd::~CMUTScanbRBtmCWnd()
{
}

void CMUTScanbRBtmCWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_NORMAL, m_NormalBtn);
	DDX_Control(pDX, IDC_BTN_BLOOD, m_BloodBtn);
	DDX_Control(pDX, IDC_BTN_ORGAN, m_OrganBtn);
	DDX_Control(pDX, IDC_BTN_MUS, m_MuslBtn);
}

BEGIN_MESSAGE_MAP(CMUTScanbRBtmCWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_NORMAL, &CMUTScanbRBtmCWnd::OnBnClickedBtnNormal)
	ON_BN_CLICKED(IDC_BTN_BLOOD, &CMUTScanbRBtmCWnd::OnBnClickedBtnBlood)
	ON_BN_CLICKED(IDC_BTN_ORGAN, &CMUTScanbRBtmCWnd::OnBnClickedBtnOrgan)
	ON_BN_CLICKED(IDC_BTN_MUS, &CMUTScanbRBtmCWnd::OnBnClickedBtnMus)
END_MESSAGE_MAP()

BOOL CMUTScanbRBtmCWnd::OnInitDialog()
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
BOOL CMUTScanbRBtmCWnd::InitWindow(void)
{
	if(TRUE != this->InitComRect()|| TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}

BOOL CMUTScanbRBtmCWnd::InitComRect(void)
{
	CRect rct,nowRect;
	CRect rcMainWnd;
	this->GetWindowRect(&rcMainWnd);
	m_NormalBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BTMWND_LEFT;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (rcMainWnd.Height() -  rct.Height())/2;
	nowRect.bottom = nowRect.top + rct.Height();
	m_NormalBtn.MoveWindow(&nowRect);

	m_BloodBtn.GetWindowRect(&rct);
	nowRect.left += (SCANB_BTMWND_SPACE + rct.Width());
	nowRect.right = nowRect.left + rct.Width();
// 	nowRect.top = SCANB_BTMWND_BTM -  rct.Height();
// 	nowRect.bottom = nowRect.top + rct.Height();
	m_BloodBtn.MoveWindow(&nowRect);

	m_OrganBtn.GetWindowRect(&rct);
	nowRect.left += (SCANB_BTMWND_SPACE + rct.Width());
	nowRect.right = nowRect.left + rct.Width();
// 	nowRect.top = SCANB_BTMWND_BTM -  rct.Height();
// 	nowRect.bottom = nowRect.top + rct.Height();
	m_OrganBtn.MoveWindow(&nowRect);

	m_MuslBtn.GetWindowRect(&rct);
	nowRect.left += (SCANB_BTMWND_SPACE + rct.Width());
	nowRect.right = nowRect.left + rct.Width();
// 	nowRect.top = SCANB_BTMWND_BTM -  rct.Height();
// 	nowRect.bottom = nowRect.top + rct.Height();
	m_MuslBtn.MoveWindow(&nowRect);

	return TRUE;
}

BOOL CMUTScanbRBtmCWnd::InitComStyle(void)
{
	m_NormalBtn.DrawBorder(TRUE);
	m_NormalBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_NormalBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_NormalBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_NormalBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	
	m_BloodBtn.DrawBorder(TRUE);
	m_BloodBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_BloodBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_BloodBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_BloodBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_OrganBtn.DrawBorder(TRUE);
	m_OrganBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_OrganBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_OrganBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_OrganBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MuslBtn.DrawBorder(TRUE);
	m_MuslBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MuslBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MuslBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MuslBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	return TRUE;
}

HBRUSH CMUTScanbRBtmCWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return GetWndBkHBrush();
}
DWORD CMUTScanbRBtmCWnd::GetBtnObject(INT index)
{
	switch(index)
	{
	case ogran_little_index:
		return (DWORD)(&m_NormalBtn);
		break;
	case organ_muscle_index:
		return (DWORD)(&m_BloodBtn);
		break;
	case organ_blood_index:
		return (DWORD)(&m_OrganBtn);
		break;
	case organ_superface_index:
		return (DWORD)(&m_MuslBtn);
		break;
	default:
		return NULL;
		break;

	}
	//old = index;				

	return NULL;
}
void  CMUTScanbRBtmCWnd::ResumeInitState()
{
	setGain(INIT_GAIN_VALUE);
	for(int i=ogran_little_index;i<organ_superface_index;i++)			//选择状态清除
	{
		CButtonST *pBtn = (CButtonST *)GetBtnObject(i);
		pBtn->SetClickState(FALSE);
	}
	m_NormalBtn.SetClickState(TRUE);
}
void CMUTScanbRBtmCWnd::ResetDeviceGain()
{
	CStatic *pGainSet = (CStatic *)(GetParent()->GetDlgItem(IDC_DEPTH_SET));
	CString strGain;

	pGainSet->GetWindowText(strGain);
	if(strGain == APP_NULL_STR)
		MessageBox(_T("ScanbRbtm GetText Err!"));

	int gain = _wtoi(strGain);
	setGain(gain);

}
void CMUTScanbRBtmCWnd::OnBnClickedBtnNormal()
{
	// TODO: 在此添加控件通知处理程序代码
	setSolution(ogran_little_index);

	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_OrganIndex);
	CButtonST *pCurBtn = &m_NormalBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	m_OrganIndex = ogran_little_index;

	ResetDeviceGain();

}

void CMUTScanbRBtmCWnd::OnBnClickedBtnBlood()
{
	// TODO: 在此添加控件通知处理程序代码
	setSolution(organ_muscle_index);
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_OrganIndex);
	CButtonST *pCurBtn = &m_BloodBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	m_OrganIndex = organ_muscle_index;
	ResetDeviceGain();
}

void CMUTScanbRBtmCWnd::OnBnClickedBtnOrgan()
{
	// TODO: 在此添加控件通知处理程序代码
	setSolution(organ_blood_index);
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_OrganIndex);
	CButtonST *pCurBtn = &m_OrganBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	m_OrganIndex = organ_blood_index;
	ResetDeviceGain();
}

void CMUTScanbRBtmCWnd::OnBnClickedBtnMus()
{
	// TODO: 在此添加控件通知处理程序代码
	setSolution(organ_superface_index);
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_OrganIndex);
	CButtonST *pCurBtn = &m_MuslBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	m_OrganIndex = organ_blood_index;			//organ_superface_index ???
	ResetDeviceGain();
}
