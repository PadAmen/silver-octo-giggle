// MTwoAngle.cpp: implementation of the CMDistance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MTwoAngle.h"
#define  PI  3.14159f
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "math.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMTwoAngle::CMTwoAngle(const CComputeMethod &computer):CMAngle(computer)
{
	m_nStep = 0;
	m_angle2 = 0.0;
}

CMTwoAngle::~CMTwoAngle()
{

}

CMeasureObject *CMTwoAngle::Clone()
{
	CMTwoAngle *pTwoAngle = new CMTwoAngle(m_computer);
	pTwoAngle->m_nStep = this->m_nStep;
	pTwoAngle->m_angle1 = this->m_angle1;
	pTwoAngle->m_angle2 = this->m_angle2;
	pTwoAngle->m_angle = this->m_angle;
	pTwoAngle->m_pointMiddle = this->m_pointMiddle;
	pTwoAngle->m_pointEnd = this->m_pointEnd;
	pTwoAngle->m_pointEndEnd = this->m_pointEndEnd;
	pTwoAngle->m_pointStart = this->m_pointStart;
	pTwoAngle->last_point = this->last_point;

	return pTwoAngle;
}

void CMTwoAngle::DrawObject(CDC *dc, int nIndex)
{
	DrawNumber(dc,nIndex,CPoint(m_pointStart.x,m_pointStart.y));
	CPen pen(PS_SOLID, 1, 0xffffff);
	CPen *oldpen = dc->SelectObject(&pen);
	DrawCrossFlag(dc, m_pointStart.x, m_pointStart.y);

	dc->MoveTo(m_pointStart);
	dc->LineTo(m_pointMiddle);
	if ( m_nStep>=2 )
	{
		last_point.x = 2 * m_pointMiddle.x - m_pointStart.x;
		last_point.y = 2 * m_pointMiddle.y - m_pointStart.y;
		dc->MoveTo(m_pointMiddle);
		dc->LineTo(last_point);
		DrawAngle(dc,nIndex,m_pointStart,m_pointMiddle,m_pointEnd,15.0,m_angle1);		//画圆弧
		dc->TextOut(m_pointEnd.x, m_pointEnd.y, _T("α"));
	}
	dc->MoveTo(m_pointMiddle);
	dc->LineTo(m_pointEnd);
	if ( m_nStep >=3 )
	{
		dc->MoveTo(m_pointMiddle);
		dc->LineTo(m_pointEndEnd);
		DrawAngle(dc,nIndex,m_pointStart,m_pointMiddle,m_pointEndEnd,25.0,m_angle2);
		dc->TextOut(m_pointEndEnd.x, m_pointEndEnd.y, _T("β"));
	} 
}


BOOL CMTwoAngle::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep == 0)//点第一下,确定开始点
	{
		m_pointStart = point;
		m_pointMiddle = point;
		m_pointEnd = point;
		m_pointEndEnd = point;
		m_nStep=1;	
		return TRUE;
	}
	else if(m_nStep==1)//点第二下,确定结束点
	{
		//计算两点间距离				
		m_pointMiddle = point;
		m_pointEnd = point;
		m_pointEndEnd = point;
		m_nStep = 2;
		return TRUE;
	}
	else if (m_nStep==2)
	{
		//第三点
		m_pointEnd = point;
		m_pointEndEnd = point;
		m_nStep = 3;
		return TRUE;
	}
	else if ( m_nStep==3)
	{
		m_pointEndEnd = point;
		m_nStep = 4;
	}
	return FALSE;

}

BOOL CMTwoAngle::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep ==1)
	{
		m_pointMiddle = point;		
		return TRUE;
	}
	if (m_nStep==2)
	{
		m_pointEnd = point;
		return TRUE;
	}
	if (m_nStep==3)
	{
		m_pointEndEnd = point;
		return TRUE;
	} 
	return FALSE;
}
bool CMTwoAngle::HasEnded()
{	
	return m_nStep==4;
}

void CMTwoAngle::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strResult;
	float disInpixel = m_computer.GetDistanceInPixes(m_pointEnd, m_pointStart);
	if(disInpixel < 5)	strResult.Format(_T("∠α: -------- "));
	else				strResult.Format(_T("∠α: %8.2f°"),m_angle1);		
	
	CString strResult1;
	if(disInpixel < 5)		strResult1.Format(_T("∠β: --------"));
	else					strResult1.Format(_T("∠β: %8.2f°"),m_angle2);	

	dc->TextOut(x,y,strResult); 	y += szLine.cy;
	dc->TextOut(x,y,strResult1);	y += szLine.cy;
}

void CMTwoAngle::Restart()
{
	m_pointEndEnd.SetPoint(0,0);
	last_point.SetPoint(0,0);
	//m_pointStart.SetPoint(0,0);
	//m_pointEnd.SetPoint(0,0);
	m_nStep = 0;
	m_angle1 = 0;
	m_angle2 = 0;
}