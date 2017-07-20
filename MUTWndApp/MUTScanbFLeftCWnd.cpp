// RunWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanbFLeftCWnd.h"


// CRunWnd 对话框

IMPLEMENT_DYNAMIC(CMUTScanbFLeftCWnd, CDialog)

CMUTScanbFLeftCWnd::CMUTScanbFLeftCWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbFLeftCWnd::IDD, pParent)
	,m_MeaIndex(0)
{
	CMUTDlgBaseFunc::InitComStyle();
	m_pMeaFun = new CMUTMeasureFunc;
}

CMUTScanbFLeftCWnd::~CMUTScanbFLeftCWnd()
{
	if(m_pMeaFun) delete m_pMeaFun;
}

void CMUTScanbFLeftCWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_LEN, m_MeaLenBtn);
	DDX_Control(pDX, IDC_BTN_AREA, m_MeaAreaBtn);
	DDX_Control(pDX, IDC_BTN_ARRW, m_MeaArrBtn);
	DDX_Control(pDX, IDC_BTN_ANGLE, m_MeaAngBtn);
	DDX_Control(pDX, IDC_BTN_CIR, m_MeaCirBtn);
	DDX_Control(pDX, IDC_BTN_TEXT, m_MeaTextBtn);
	DDX_Control(pDX, IDC_BTN_LAST, m_MeaUndoBtn);
	DDX_Control(pDX, IDC_BTN_ALL, m_MeaNDoallBtn);
}


BEGIN_MESSAGE_MAP(CMUTScanbFLeftCWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_LEN, &CMUTScanbFLeftCWnd::OnBnClickedBtnLen)
	ON_BN_CLICKED(IDC_BTN_LAST, &CMUTScanbFLeftCWnd::OnBnClickedBtnLast)
	ON_BN_CLICKED(IDC_BTN_ALL, &CMUTScanbFLeftCWnd::OnBnClickedBtnAll)
	ON_BN_CLICKED(IDC_BTN_AREA, &CMUTScanbFLeftCWnd::OnBnClickedBtnArea)
	ON_BN_CLICKED(IDC_BTN_ARRW, &CMUTScanbFLeftCWnd::OnBnClickedBtnArrw)
	ON_BN_CLICKED(IDC_BTN_ANGLE, &CMUTScanbFLeftCWnd::OnBnClickedBtnAngle)
	ON_BN_CLICKED(IDC_BTN_CIR, &CMUTScanbFLeftCWnd::OnBnClickedBtnCir)
	ON_BN_CLICKED(IDC_BTN_TEXT, &CMUTScanbFLeftCWnd::OnBnClickedBtnText)
END_MESSAGE_MAP()


// CRunWnd 消息处理程序

BOOL CMUTScanbFLeftCWnd::GetParentSize(CRect rct)
{

	m_rcParent.CopyRect(&rct);

	return TRUE;
}
BOOL CMUTScanbFLeftCWnd::OnInitDialog()
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
BOOL CMUTScanbFLeftCWnd::InitWindow(void)
{
	m_TextWnd.GetHMainWnd(GetParent()->GetSafeHwnd());
	m_TextWnd.Create(IDD_TEXT_DLG,this);
	if(TRUE != this->InitComRect()|| TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}

BOOL CMUTScanbFLeftCWnd::InitComRect(void)
{

	CRect rct,nowRect;
	CRect rcMainWnd;
	this->GetWindowRect(&rcMainWnd);

	m_MeaLenBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = SCANB_LEFTWND_TOP;
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaLenBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaAreaBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaArrBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaAngBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaCirBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaTextBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaUndoBtn.MoveWindow(&nowRect);

	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_MeaNDoallBtn.MoveWindow(&nowRect);

	HWND hScrHwnd = ::GetDesktopWindow();
	CRect hScrRct;
	::GetWindowRect(hScrHwnd,&hScrRct);
	m_TextWnd.GetWindowRect(&rct);
	nowRect.left = (hScrRct.Width() - APP_SCREEN_WIDTH)/2; //得到APP相对应屏幕座标
	nowRect.left += (APP_SCREEN_WIDTH - rct.Width())/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (hScrRct.Height() - APP_SCREEN_HEIGHT)/2;
	nowRect.top += (APP_SCREEN_HEIGHT - rct.Height())/2;
	nowRect.bottom = nowRect.top + rct.Height();
	m_TextWnd.MoveWindow(&nowRect);
	m_TextWnd.ShowWindow(FALSE);

	return TRUE;
}

BOOL CMUTScanbFLeftCWnd::InitComStyle(void)
{
	m_MeaLenBtn.DrawBorder(TRUE);
	m_MeaLenBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaLenBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaLenBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaLenBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MeaAreaBtn.DrawBorder(TRUE);
	m_MeaAreaBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaAreaBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaAreaBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaAreaBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MeaArrBtn.DrawBorder(TRUE);
	m_MeaArrBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaArrBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaArrBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaArrBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MeaAngBtn.DrawBorder(TRUE);
	m_MeaAngBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaAngBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaAngBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaAngBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MeaCirBtn.DrawBorder(TRUE);
	m_MeaCirBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaCirBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaCirBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaCirBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MeaTextBtn.DrawBorder(TRUE);
	m_MeaTextBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaTextBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaTextBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaTextBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_MeaUndoBtn.DrawBorder(FALSE);
	m_MeaUndoBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaUndoBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaUndoBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaUndoBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_MeaUndoBtn.SetPngMaps(APP_UNDO_IMAGE);

	m_MeaNDoallBtn.DrawBorder(FALSE);
	m_MeaNDoallBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_MeaNDoallBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_MeaNDoallBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_MeaNDoallBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_MeaNDoallBtn.SetPngMaps(APP_DELETE_IMAGE);
	return TRUE;
}
HBRUSH CMUTScanbFLeftCWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	return GetWndBkHBrush();
}
DWORD CMUTScanbFLeftCWnd::GetBtnObject(INT index)
{
	//if(index <= 0) return NULL;
// 	INT oldIndex=0;
// 	static INT cnt=0;
// 	if(oldIndex == index || 0 == oldIndex)
// 	{
// 		if(1 == ++ cnt)
// 		{
// 			oldIndex = index;
// 			return NULL;
// 		}
// 		if(cnt >= 2) cnt = 0;
// 	}
// 	
// 	oldIndex = index;
	switch(index)
	{
		case mea_length_index:
			return (DWORD)(&m_MeaLenBtn);
			break;
		case mea_area_index:
			return (DWORD)(&m_MeaAreaBtn);
			break;
		case mea_arrow_index:
			return (DWORD)(&m_MeaArrBtn);
			break;
		case mea_angle_index:
			return (DWORD)(&m_MeaAngBtn);
			break;
		case mea_circum_index:
			return (DWORD)(&m_MeaCirBtn);
			break;
		case mea_text_index:
			return (DWORD)(&m_MeaTextBtn);
			break;
		default:
			return NULL;
		break;

	}
	//old = index;				
	
	return NULL;
}
BOOL CMUTScanbFLeftCWnd::GetBtnClickState()
{
	switch(m_MeaIndex)
	{
		case mea_length_index:
			return m_MeaLenBtn.GetClickState();
			break;
		case mea_area_index:
			return m_MeaAreaBtn.GetClickState();
			break;
		case mea_arrow_index:
			return m_MeaArrBtn.GetClickState();
			break;
		case mea_angle_index:
			return m_MeaAngBtn.GetClickState();
			break;
		case mea_circum_index:
			return m_MeaCirBtn.GetClickState();
			break;
		case mea_text_index:
			return m_MeaTextBtn.GetClickState();
			break;
		default:
			return FALSE;
			break;

	}
	return FALSE;
}
void CMUTScanbFLeftCWnd::OnBnClickedBtnLen()
{
	// TODO: 在此添加控件通知处理程序代码
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	CButtonST *pCurBtn = &m_MeaLenBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	if(pCurBtn->GetClickState())
	m_pMeaFun->MeasureStartProc(mea_length_index);

	m_MeaIndex = mea_length_index;
}

void CMUTScanbFLeftCWnd::OnBnClickedBtnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pMeaFun->DeleteLastResult();
	::SendMessage(GetParent()->GetSafeHwnd(),WM_UPDATE_IMAGE,0,NULL);
	CButtonST *pCurBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	if(NULL == pCurBtn)	return;
	if(pCurBtn->GetClickState())
		m_pMeaFun->MeasureStartProc(m_MeaIndex);	
}
void  CMUTScanbFLeftCWnd::ResumeInitState()
{
	m_pMeaFun->DeleteAllResult();
	::SendMessage(GetParent()->GetSafeHwnd(),WM_UPDATE_IMAGE,0,NULL);
	for(int i=mea_length_index;i <= mea_text_index;i++)
	{
		CButtonST *pBtn = (CButtonST *)GetBtnObject(i);
		if(pBtn!=NULL)
			pBtn->SetClickState(FALSE);
	}
}
void CMUTScanbFLeftCWnd::OnBnClickedBtnAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pMeaFun->DeleteAllResult();
	::SendMessage(GetParent()->GetSafeHwnd(),WM_UPDATE_IMAGE,0,NULL);
	for(int i=mea_length_index;i <= mea_text_index;i++)
	{
		CButtonST *pBtn = (CButtonST *)GetBtnObject(i);
		if(pBtn!=NULL)
			pBtn->SetClickState(FALSE);
	}
	
}

void CMUTScanbFLeftCWnd::OnBnClickedBtnArea()
{
	// TODO: 在此添加控件通知处理程序代码
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	CButtonST *pCurBtn = &m_MeaAreaBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	if(pCurBtn->GetClickState())
		m_pMeaFun->MeasureStartProc(mea_area_index);

	m_MeaIndex = mea_area_index;
}

void CMUTScanbFLeftCWnd::OnBnClickedBtnArrw()
{
	// TODO: 在此添加控件通知处理程序代码
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	CButtonST *pCurBtn = &m_MeaArrBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	if(pCurBtn->GetClickState())
		m_pMeaFun->MeasureStartProc(mea_arrow_index);

	m_MeaIndex = mea_arrow_index;
}

void CMUTScanbFLeftCWnd::OnBnClickedBtnAngle()
{
	// TODO: 在此添加控件通知处理程序代码
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	CButtonST *pCurBtn = &m_MeaAngBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	if(pCurBtn->GetClickState())
		m_pMeaFun->MeasureStartProc(mea_angle_index);

	m_MeaIndex = mea_angle_index;
}

void CMUTScanbFLeftCWnd::OnBnClickedBtnCir()
{
	// TODO: 在此添加控件通知处理程序代码
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	CButtonST *pCurBtn = &m_MeaCirBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);
 
	if(pCurBtn->GetClickState())
		m_pMeaFun->MeasureStartProc(mea_circum_index);

	m_MeaIndex = mea_circum_index;
}

void CMUTScanbFLeftCWnd::OnBnClickedBtnText()
{
	// TODO: 在此添加控件通知处理程序代码
	CButtonST *pOldBtn = (CButtonST *)GetBtnObject(m_MeaIndex);
	CButtonST *pCurBtn = &m_MeaTextBtn;

	if(pOldBtn && pCurBtn!=pOldBtn)			
		pOldBtn->SetClickState(FALSE);

	if(pCurBtn->GetClickState())
	{
		m_pMeaFun->MeasureStartProc(mea_text_index);
		//m_TextWnd.ShowWindow(TRUE);
	}
	m_MeaIndex = mea_text_index;
	
}
