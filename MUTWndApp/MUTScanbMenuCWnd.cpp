// ScanBMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanbMenuCWnd.h"


// CScanBMenu 对话框

IMPLEMENT_DYNAMIC(CMUTScanbMenuCWnd, CDialog)

CMUTScanbMenuCWnd::CMUTScanbMenuCWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbMenuCWnd::IDD, pParent)
{

}

CMUTScanbMenuCWnd::~CMUTScanbMenuCWnd()
{
}

void CMUTScanbMenuCWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCANB_FILE, m_FileBtn);
	DDX_Control(pDX, IDC_SCANB_OPERA, m_OperaBtn);
	DDX_Control(pDX, IDC_SCANB_TEACH, m_TeachBtn);
	DDX_Control(pDX, IDC_SCANB_PUNC, m_PuncBtn);
	DDX_Control(pDX, IDC_SCANB_SPEICAL, m_SpecialBtn);
	DDX_Control(pDX, IDC_SCANB_SET, m_SetBtn);
	DDX_Control(pDX, IDC_SCANB_ABOUT, m_AboutBtn);
}


BEGIN_MESSAGE_MAP(CMUTScanbMenuCWnd, CDialog)
END_MESSAGE_MAP()


// CScanBMenu 消息处理程序
