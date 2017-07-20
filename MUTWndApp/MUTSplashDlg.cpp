// MUTSplashDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTSplashDlg.h"


// CMUTSplashDlg 对话框

IMPLEMENT_DYNAMIC(CMUTSplashDlg, CDialog)

CMUTSplashDlg::CMUTSplashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTSplashDlg::IDD, pParent)
{

}

CMUTSplashDlg::~CMUTSplashDlg()
{
}

void CMUTSplashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMUTSplashDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMUTSplashDlg 消息处理程序

void CMUTSplashDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// get bitmap colors
	CPalette *pOldPal = dc.SelectPalette(m_bitmap.GetPalette(), FALSE);
	dc.RealizePalette();

	// get device context to select bitmap into
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);

	// draw bitmap
	dc.BitBlt(0, 0, m_bitmap.m_Width, m_bitmap.m_Height, &dcComp, 0, 0, SRCCOPY);

	// reselect old palette
	dc.SelectPalette(pOldPal, FALSE);
}

void CMUTSplashDlg::Create(UINT nID)
{
	m_bitmap.LoadBitmapEx(nID, TRUE);

	int x = (::GetSystemMetrics(SM_CXSCREEN) - m_bitmap.m_Width) / 2;
	int y = (::GetSystemMetrics(SM_CYSCREEN) - m_bitmap.m_Height) / 2;
	CRect rect(x, y, x + m_bitmap.m_Width, y + m_bitmap.m_Height);
	//CreateEx 使用多字节字符集编译通过
	CreateEx(0, AfxRegisterWndClass(0), _T(""), WS_POPUP | WS_VISIBLE | WS_BORDER, rect, NULL, 0);
}