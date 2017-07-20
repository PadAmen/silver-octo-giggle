// MARatio.cpp: implementation of the CMTrRatio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MTrRatio.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMTrRatio::CMTrRatio(const CComputeMethod &computer):CMeasureObject(computer),
	m_TrArea1(m_computer),m_TrArea2(m_computer)
{
	m_nStep = 0;
	m_Ratio = 0.0f;
}

CMTrRatio::~CMTrRatio()
{

}
CMeasureObject* CMTrRatio::Clone()
{
	return new CMTrRatio(m_computer);
}
void CMTrRatio::DrawObject(CDC *dc,int nIndex)
{
	m_TrArea1.DrawObject(dc, nIndex);
	nIndex += 1;
	m_TrArea2.DrawObject(dc, nIndex);
}
void CMTrRatio::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strA1, strA2, strRatio;	
	CString strP1, strP2, strPerimeter;
	float a1 = m_TrArea1.GetArea();
	float a2 = m_TrArea2.GetArea();
	float p1 = m_TrArea1.GetPerimeter();
	float p2 = m_TrArea2.GetPerimeter();
	//面积一的内容

	strA1.Format(_T("A1: %8.2f cm^2"), a1);	
	strP1.Format(_T("P1: %8.2f cm")	 , p1);
	//面积2的内容
	if(a2 < 0.00001f)
	{
		strA2.Format(_T("A2:  --------"));
		strP2.Format(_T("P2:  --------"));
		strRatio	= _T("%%(A1/A2): --------");
		strPerimeter= _T("%%(P1/P2): --------");
	}
	else 
	{
		strA2.Format(_T("A2: %8.2f cm^2"), a2);
		strP2.Format(_T("P2: %8.2f cm")	 , p2);
		strRatio.Format(_T("%%(A1/A2): %8.2f %%"), a1*100/a2);
		strPerimeter.Format(_T("%%(P1/P2): %8.2f %%"), p1*100/p2);
	}	
	//面积一
	dc->TextOut(x, y, strA1);	y += szLine.cy;
	dc->TextOut(x, y, strP1);	y += szLine.cy;
	//面积二
	dc->TextOut(x, y, strA2);	y += szLine.cy;
	dc->TextOut(x, y, strP2);	y += szLine.cy;
	//多出面积比	
	dc->TextOut(x, y, strRatio);		y += szLine.cy;	
	dc->TextOut(x, y, strPerimeter);	y += szLine.cy;
}
BOOL CMTrRatio::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		m_TrArea1.OnLButtonDown(nFlags,point);
		if(m_TrArea1.HasEnded()) 	m_nStep=1;
		return TRUE;
	}
	else if(m_nStep==1)
	{
		m_TrArea2.OnLButtonDown(nFlags,point);
		if(m_TrArea2.HasEnded()) m_nStep=2;
		return TRUE;
	}
	return FALSE;
}
BOOL CMTrRatio::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		return m_TrArea1.OnMouseMove(nFlags, point);
	}
	else if(m_nStep==1)
	{
		return m_TrArea2.OnMouseMove(nFlags, point);
	}
	return FALSE;
	
}
bool CMTrRatio::HasEnded()
{
	return m_nStep==2;
}
bool CMTrRatio::HasStarted()
{
	return m_TrArea1.HasStarted();
}

int CMTrRatio::GetResultCount()
{
	return 6;
}

void CMTrRatio::Restart()
{
	m_TrArea1.Restart();
	m_TrArea2.Restart();
	m_nStep = 0;
	m_Ratio = 0;
}