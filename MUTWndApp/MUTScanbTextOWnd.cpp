// MtextWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanbTextOWnd.h"


// CMtextWnd 对话框

IMPLEMENT_DYNAMIC(CMUTScanbTextOWnd, CDialog)

CMUTScanbTextOWnd::CMUTScanbTextOWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbTextOWnd::IDD, pParent)
{
	m_brush.CreateSolidBrush(APP_POPUP_COLOR);
}

CMUTScanbTextOWnd::~CMUTScanbTextOWnd()
{
}

void CMUTScanbTextOWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_TextBtn);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_TextEdit);
}


BEGIN_MESSAGE_MAP(CMUTScanbTextOWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CMUTScanbTextOWnd::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMtextWnd 消息处理程序

HBRUSH CMUTScanbTextOWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return m_brush;
}

void CMUTScanbTextOWnd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	m_TextEdit.GetWindowText(m_StrText);
	m_TextEdit.SetWindowText(APP_NULL_STR);
	::SendMessage(m_hMainWnd,WM_INPUT_STR,0,(LPARAM)&m_StrText);
	
}
