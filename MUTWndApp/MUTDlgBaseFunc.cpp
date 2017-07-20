#include "StdAfx.h"
#include "MUTDlgBaseFunc.h"

CMUTDlgBaseFunc::CMUTDlgBaseFunc(void)
{
	
}

CMUTDlgBaseFunc::~CMUTDlgBaseFunc(void)
{
	::DeleteObject(m_hbrush);
}

BOOL CMUTDlgBaseFunc::InitComRect()
{
	m_AppWndRect.left = (GetSystemMetrics(SM_CXSCREEN) - APP_SCREEN_WIDTH)/2;
	m_AppWndRect.top = (GetSystemMetrics(SM_CYSCREEN) - APP_SCREEN_HEIGHT)/2;
	m_AppWndRect.right = m_AppWndRect.left + APP_SCREEN_WIDTH;
	m_AppWndRect.bottom = m_AppWndRect.top + APP_SCREEN_HEIGHT;
	//MoveWindow(&m_WndRect);
	return TRUE;
}
void CMUTDlgBaseFunc::SetWndColor(COLORREF bkColor,COLORREF textColor)
{
	m_bkColor = bkColor;
	m_textColor = textColor;
	m_hbrush = ::CreateSolidBrush(m_bkColor);
}
BOOL CMUTDlgBaseFunc::InitComStyle()
{
	SetWndColor(APP_BK_COLOR1);
	return TRUE;
}
BOOL CMUTDlgBaseFunc::GetAppWndRect(LPRECT lprct)
{
	if(NULL == lprct) return FALSE;

	* lprct = m_AppWndRect;

	return TRUE;
}