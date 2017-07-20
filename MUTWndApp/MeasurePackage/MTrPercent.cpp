// MAPercent.cpp: implementation of the CMTrPercent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MTrPercent.h"
#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMTrPercent::CMTrPercent(const CComputeMethod &computer):CMeasureObject(computer),
	m_TrArea1(m_computer),m_TrArea2(m_computer)
{
	m_nStep=0;
}

CMTrPercent::~CMTrPercent()
{

}
CMeasureObject *CMTrPercent::Clone()
{
	return new CMTrPercent(m_computer);
}
void CMTrPercent::DrawObject(CDC *dc,int nIndex)
{
	m_TrArea1.DrawObject(dc, nIndex);
	nIndex += 1;
	m_TrArea2.DrawObject(dc, nIndex);
}
void CMTrPercent::DrawResult(CDC *dc,int &x,int &y)
{	
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strA1, strA2, strPercent;
	CString strP1, strP2, strPerimeter;
	float a1 = m_TrArea1.GetArea();
	float a2 = m_TrArea2.GetArea();
	float p1 = m_TrArea1.GetPerimeter();
	float p2 = m_TrArea2.GetPerimeter();

	strA1.Format(_T("A1: %8.2f cm^2"),   a1);	
	strP1.Format(_T("P1: %8.2f cm")	,	p1);
	if(a1 > 0.00005f)
	{
		strA2.Format(_T("A2: %8.2f cm^2"),  a2);
		strP2.Format(_T("P2: %8.2f cm")	 ,	p2);
		strPercent.Format(_T("△A/A1: %8.2f%%"), fabs(a1-a2)*100/a1);
		strPerimeter.Format(_T("△P/P1: %8.2f%%"), fabs(p1-p2)*100/p1);
	}
	else 
	{
		strA2		=(_T("A2: --------"));
		strP2		=(_T("P2: --------"));
		strPercent	=(_T("%%A: --------"));
		strPerimeter=(_T("%%P: --------"));
	}
	dc->TextOut(x, y, strA1);		y += szLine.cy;	
	dc->TextOut(x, y, strP1);		y += szLine.cy;
	dc->TextOut(x, y, strA2);		y += szLine.cy;	
	dc->TextOut(x, y, strP2);		y += szLine.cy;		
	dc->TextOut(x, y, strPercent);	y += szLine.cy;	
	dc->TextOut(x, y, strPerimeter);y += szLine.cy;
}
BOOL CMTrPercent::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep==0)//画第一个
	{
		m_TrArea1.OnLButtonDown(nFlags,point);
		if(m_TrArea1.HasEnded()) 	m_nStep=1;
		return TRUE;
	}
	else if(m_nStep==1)//画第二个
	{
		m_TrArea2.OnLButtonDown(nFlags,point);
		if(m_TrArea2.HasEnded()) m_nStep=2;
		return TRUE;
	}
	return FALSE;
}
BOOL CMTrPercent::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep == 0)
	{
		return m_TrArea1.OnMouseMove(nFlags, point);//画第一个
	}
	else if(m_nStep == 1)
	{
		return m_TrArea2.OnMouseMove(nFlags, point);//画第二个
	}
	return FALSE;
}
bool CMTrPercent::HasEnded()
{
	return m_nStep==2;
}
bool CMTrPercent::HasStarted()
{
	return m_TrArea1.HasStarted();
}

int CMTrPercent::GetResultCount()
{
	return 6;
}

void CMTrPercent::Restart()
{
	m_TrArea1.Restart();
	m_TrArea2.Restart();
	m_nStep = 0;
}