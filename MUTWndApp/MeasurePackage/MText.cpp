#include "stdafx.h"
#include "MText.h"

CMText::CMText(const CComputeMethod &computer)
:CMeasureObject(computer)
{
	m_uWidth = 40;
	m_uHeight = 40;
	m_nStep = 0;
}

CMText::~CMText(void)
{
}
CMeasureObject *CMText::Clone()
{
	CMText *pText = new CMText(m_computer);
	pText->m_nStep = this->m_nStep;
	pText->m_pointStart = this->m_pointStart;

	return pText;
}
void CMText::DrawObject(CDC *dc,int nIndex)
{
	//if(m_nStep<1) return;

	if(1 == m_nStep)
	{
		dc->SetBkMode(TRANSPARENT);
		COLORREF cr = RGB(255,193,37);//»ÆÉ«
		dc->Draw3dRect(m_pointStart.x,m_pointStart.y,m_uWidth,m_uHeight,cr,cr);
	}
}
BOOL CMText::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(0 == m_nStep )
	{
		m_nStep = 1;
		m_pointStart = point;
	}
	return TRUE;
}
void CMText::Restart()
{
	m_nStep = 0;
	m_pointStart.SetPoint(0, 0);
}
bool CMText::HasEnded()
{	
	return m_nStep==2;
}
void CMText::DrawResult(CDC *dc,CString strResult)
{
	dc->SetTextColor(m_TextColor);
	dc->SetBkMode(TRANSPARENT);
	CFont font;
	font.CreatePointFont(200, _T("Arial"), dc);
	CFont *oldfont = dc->SelectObject(&font);
	dc->TextOut(m_pointStart.x+1,m_pointStart.y,strResult);
	dc->SelectObject(oldfont);
	font.DeleteObject();
}
BOOL CMText::OnMouseMove(UINT nFlags, CPoint point)
{
	
	return TRUE;
}