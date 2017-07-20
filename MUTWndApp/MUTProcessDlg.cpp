// MUTProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTProcessDlg.h"


// CMUTProcessDlg 对话框

IMPLEMENT_DYNAMIC(CMUTProcessDlg, CDialog)

CMUTProcessDlg::CMUTProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTProcessDlg::IDD, pParent)
{

}

CMUTProcessDlg::~CMUTProcessDlg()
{
}

void CMUTProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProcessBar);
}


BEGIN_MESSAGE_MAP(CMUTProcessDlg, CDialog)

END_MESSAGE_MAP()


// CMUTProcessDlg 消息处理程序
