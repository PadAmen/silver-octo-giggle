// MERatio.cpp: implementation of the CMElRatio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MElRatio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMElRatio::CMElRatio(const CComputeMethod&computer):CMeasureObject(computer),
	m_AxArea1(computer),m_AxArea2(computer)
{
	m_nStep = 0;
}

CMElRatio::~CMElRatio()
{

}
CMeasureObject *CMElRatio::Clone()
{

	return new CMElRatio(m_computer);
}
void CMElRatio::DrawObject(CDC *dc,int nIndex)
{
	m_AxArea1.DrawObject(dc, nIndex);
	nIndex += 1;
	m_AxArea2.DrawObject(dc, nIndex);
}
bool CMElRatio::HasEnded()
{
	return m_nStep==2;
}
bool CMElRatio::HasStarted()
{
	return m_AxArea1.HasStarted();
}
BOOL CMElRatio::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		m_AxArea1.OnLButtonDown(nFlags, point);
		if(m_AxArea1.HasEnded()) m_nStep = 1;
		return TRUE;
	}
	else if(m_nStep==1)
	{
		m_AxArea2.OnLButtonDown(nFlags, point);
		if(m_AxArea2.HasEnded()) m_nStep = 2;
		return TRUE;
	}
	return FALSE;
}
BOOL CMElRatio::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		return m_AxArea1.OnMouseMove(nFlags, point);
	}
	else if(m_nStep==1)
	{
		return m_AxArea2.OnMouseMove(nFlags, point);
	}
	return FALSE;
}
void CMElRatio::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	this->m_AxArea1.DrawResult(dc,x, y);
	y += szLine.cy * m_AxArea1.GetResultCount();
	this->m_AxArea2.DrawResult(dc,x, y);
	y += szLine.cy * m_AxArea2.GetResultCount();
	CString strRatio;
	CString strPercent;
	CString strPermiter;
	float a1 = m_AxArea1.GetArea();
	float a2 = m_AxArea2.GetArea();
	float p1 = m_AxArea1.GetPerimeter();
	float p2 = m_AxArea2.GetPerimeter();
	if(a2 < 0.00001f)	strPercent  = _T("%%(A1/A2): --------");
	else				strPercent.Format(_T("%%(A1/A2): %8.2f"), 100*a1/a2);
	
	if (p2 < 0.00001f)	strPermiter = _T("%%(P1/P2): --------");
	else			    strPermiter.Format(_T("%%(P1/P2): %8.2f"), 100*p1/p2);

	dc->TextOut(x, y,  strPercent);
	y += szLine.cy ;
	dc->TextOut(x, y, strPermiter);

}

int CMElRatio::GetResultCount()
{
	return 6;
}

void CMElRatio::Restart()
{
	m_AxArea1.Restart();
	m_AxArea2.Restart();
	m_nStep = 0;
}