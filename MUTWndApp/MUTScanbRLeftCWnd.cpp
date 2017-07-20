// RunWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanbRLeftCWnd.h"


// CRunWnd 对话框

IMPLEMENT_DYNAMIC(CMUTScanbRLeftCWnd, CDialog)

CMUTScanbRLeftCWnd::CMUTScanbRLeftCWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbRLeftCWnd::IDD, pParent)
	, m_iDepth(DEPTH_INIT_VALUE)
{
	CMUTDlgBaseFunc::InitComStyle();
}

CMUTScanbRLeftCWnd::~CMUTScanbRLeftCWnd()
{
}

void CMUTScanbRLeftCWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ADD, m_AddBtn);
	DDX_Control(pDX, IDC_BTN_DEC, m_CutBtn);
	DDX_Control(pDX, IDC_SET_DEPTH, m_SetDepth);
	DDX_Control(pDX, IDC_DEPTH_STATIC, m_DepthStatic);
}

BEGIN_MESSAGE_MAP(CMUTScanbRLeftCWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_ADD, &CMUTScanbRLeftCWnd::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEC, &CMUTScanbRLeftCWnd::OnBnClickedBtnDec)
END_MESSAGE_MAP()


// CRunWnd 消息处理程序


BOOL CMUTScanbRLeftCWnd::GetParentSize(CRect rct)
{
	m_rcParent.CopyRect(&rct);

	return TRUE;
}
BOOL CMUTScanbRLeftCWnd::OnInitDialog()
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
BOOL CMUTScanbRLeftCWnd::InitWindow(void)
{
	if(TRUE != this->InitComRect()|| TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTScanbRLeftCWnd::InitComRect(void)
{
	CRect rct,nowRect;

	//m_AddBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + m_rcParent.Width();
	nowRect.top = SCANB_LEFTWND_TOP;
	nowRect.bottom = nowRect.top + m_rcParent.Height();
	m_AddBtn.MoveWindow(&nowRect);

	m_DepthStatic.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + m_rcParent.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE+nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_DepthStatic.MoveWindow(&nowRect);

	m_SetDepth.GetWindowRect(&rct);
	//nowRect.left = SCANB_LEFTWND_LEFT;
	//nowRect.right = nowRect.left + m_rcParent.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE+nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_SetDepth.MoveWindow(&nowRect);

	//nowRect.left = SCANB_LEFTWND_LEFT;
	//nowRect.right = nowRect.left + m_rcParent.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE+nowRect.Height());
	nowRect.bottom = nowRect.top + m_rcParent.Height();
	m_CutBtn.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTScanbRLeftCWnd::InitComStyle(void)
{
	m_AddBtn.DrawBorder(FALSE);
	m_AddBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_AddBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_AddBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_AddBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_AddBtn.SetPngMaps(APP_ADD_IMAGE);

	m_CutBtn.DrawBorder(FALSE);
	m_CutBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_CutBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_CutBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_CutBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_CutBtn.SetPngMaps(APP_REDUCE_IMAGE);

	SetTextDepth(DEPTH_INIT_VALUE);
	return TRUE;
}
HBRUSH CMUTScanbRLeftCWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(250,250,250));
		//return ::CreateSolidBrush(APP_BK_COLOR);
	}

	return GetWndBkHBrush();
}
void  CMUTScanbRLeftCWnd::ResumeInitState()
{
	SetTextDepth(DEPTH_INIT_VALUE);
	SetParameterForMIAndTI();
}
BOOL CMUTScanbRLeftCWnd::SetTextDepth(UINT uDepth)
{
	int index = uDepth/10 - 3;//线阵：0－30mm，1－40mm，2－50mm，3－60mm；凸阵：0－140mm，1－160mm，2－180mm

	setRun(FALSE);
	switch(index)
	{
		case 0:
			setFreq(2);
			break;
		case 1:
			setFreq(2);
			break;
		case 2:
			setFreq(1);
			break;
		case 3:
			setFreq(0);

		default: break;
	
	}
	setDepth(index);
	setRun(TRUE);

	CString str;
	str.Format(_T("%d mm"),uDepth);
	m_SetDepth.SetWindowText(str);
	return TRUE;
}

void CMUTScanbRLeftCWnd::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iDepth += DEPTH_OFFSET_VALUE;

	if(m_iDepth >= DEPTH_MAX_VALUE)
		m_iDepth = DEPTH_MAX_VALUE;
	SetTextDepth(m_iDepth);
	SetParameterForMIAndTI();
}

void CMUTScanbRLeftCWnd::OnBnClickedBtnDec()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iDepth -= DEPTH_OFFSET_VALUE;

	if(m_iDepth <= DEPTH_MIN_VALUE)
		m_iDepth = DEPTH_MIN_VALUE;
	SetTextDepth(m_iDepth);
	SetParameterForMIAndTI();
}
void CMUTScanbRLeftCWnd::SetParameterForMIAndTI()
{
	CString str;
	CStatic * pMacStatic = (CStatic *)GetParent()->GetDlgItem(IDC_MAC_STATIC);
	// 	if (m_current_pin == LINEEAR_PINTYPE)
	// 	{
	switch (m_iDepth)
	{
	case 40:
	case 1:	
		str.Format(_T("MUT\r\n\n\nTI\r\n%.1f\r\n\n\nMI\r\n%.1f\r\n"),0.9,0.2);
		pMacStatic->SetWindowText(str);
		break;
	case 50:
	case 2:
		str.Format(_T("MUT\r\n\n\nTI\r\n%.1f\r\n\n\nMI\r\n%.1f\r\n"),0.8,0.2);
		pMacStatic->SetWindowText(str);
		break;
	case 60:
	case 3:
		str.Format(_T("MUT\r\n\n\nTI\r\n%.1f\r\n\n\nMI\r\n%.1f\r\n"),0.7,0.2);
		pMacStatic->SetWindowText(str);
		break;
	default:
		//FIXME 30 is not set
		str.Format(_T("MUT\r\n\n\nTI\r\n%.1f\r\n\n\nMI\r\n%.1f\r\n"),0.8,0.2);
		pMacStatic->SetWindowText(str);
		break;

	}
	//	}
	// 	else
	// 	{
	// 		switch (m_organ_type)
	// 		{
	// 		case ORGAN_TYPE_4://腹部
	// 			printf("getdepth() bug ? %d\r\n", getDepth());
	// 			//switch (getDepth())
	// 			switch(m_depth)
	// 				////线阵：0－30mm，1－40mm，2－50mm，3－60mm；凸阵：0－140mm，1－160mm，2－180mm；
	// 			{
	// 			case 140:
	// 			case 0:
	// 				str.Format(_T("%.1f"), 1.0);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.2);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			case 160:
	// 			case 1:
	// 				str.Format(_T("%.1f"), 0.9);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.2);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			case 180:
	// 			case 2:
	// 				str.Format(_T("%.1f"), 0.8);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.1);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			default:
	// 				str.Format(_T("%.1f"), 1.0);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.2);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			}
	// 
	// 			break;
	// 		case ORGAN_TYPE_5://产妇
	// 			//switch (getDepth())
	// 			switch (m_depth)
	// 			{
	// 			case 140:
	// 			case 0:
	// 				str.Format(_T("%.1f"), 1.1);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.1);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			case 160:
	// 			case 1:
	// 				str.Format(_T("%.1f"), 1.0);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.1);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			case 180:
	// 			case 2:
	// 				str.Format(_T("%.1f"), 0.9);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.1);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			default:
	// 				str.Format(_T("%.1f"), 1.1);
	// 				m_static_mi.SetWindowTextW(str);
	// 				str.Format(_T("%.1f"), 0.);
	// 				m_static_ti.SetWindowTextW(str);
	// 				break;
	// 			}
	// 			break;
	// 		}
	// 	}
}