// MTrArea.cpp: implementation of the CMTrArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MTrArea.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMTrArea::CMTrArea(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;	
}

CMTrArea::~CMTrArea()
{
}
void CMTrArea::BackUpObj(CMTrArea &rt)
{
	rt.m_nStep = this->m_nStep;
	rt.m_ArrPoint.Copy(this->m_ArrPoint);
}
CMeasureObject *CMTrArea::Clone()
{
	CMTrArea *pMTrArea = new CMTrArea(m_computer);
	pMTrArea->m_nStep = this->m_nStep;
	pMTrArea->m_ArrPoint.Copy(this->m_ArrPoint);
	return pMTrArea;
}

float CMTrArea::GetArea()
{
	return this->m_computer.GetCanveArea(m_ArrPoint);
}

float CMTrArea::GetPerimeter()
{
	return this->m_computer.GetCanveDistance(m_ArrPoint);
}

void CMTrArea::DrawObject(CDC *dc,int nIndex)
{
	if(m_nStep<1) return;	
	CPen penLine(PS_DOT, 1, 0xFFFFFF);
	CPen *oldPen = dc->SelectObject(&penLine);	
	//将所有点连起来
	for(int i=0; i<m_ArrPoint.GetSize(); i++)
	{
		CPoint p = m_ArrPoint.GetAt(i);
		if(i != 0)	dc->LineTo(p.x, p.y);
		dc->MoveTo(p.x, p.y);
	}
	
	//
	CPoint pStart  = m_ArrPoint.GetAt(0);
	//绘制序号
	DrawNumber(dc,nIndex,pStart);
	//将首尾连起来
	if(m_ArrPoint.GetSize()>2 && m_nStep==2)
	{		
		dc->LineTo(pStart.x, pStart.y);
	}
	dc->SelectObject(oldPen);
	//在起点画个圈
	if(m_nStep < 2)
	{	
		HBRUSH nullbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		CPen RingPen(PS_SOLID, 1, 0xffffff);
		void *oldbr = dc->SelectObject(nullbr);
		CPen *oldPen = dc->SelectObject(&RingPen);
		dc->Ellipse(pStart.x-4, pStart.y-4, pStart.x+4, pStart.y+4);
		dc->SelectObject(oldbr);
		dc->SelectObject(oldPen);
	}
}

void CMTrArea::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strA;	
	//文本内容	
	strA.Format(_T("A: %8.2f cm^2"), m_computer.GetCanveArea(m_ArrPoint));	
	//strP.Format(_T("P: %8.2f cm"), m_computer.GetCanveDistance(m_ArrPoint, true));
	//绘制文本
	dc->TextOut(x, y, strA);
	y += szLine.cy;
}
BOOL CMTrArea::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		m_ArrPoint.Add(point);
		m_nStep = 1;
		return TRUE;
	}
	else if(m_nStep==1)
	{	
		m_nStep = 2;
		m_ArrPoint.Add(point);		
		return TRUE;
	}	
	return FALSE;
}

BOOL CMTrArea::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==1)
	{	
		CPoint ptLast = m_ArrPoint.GetAt(m_ArrPoint.GetSize()-1);
		float dis = this->m_computer.GetDistanceInPixes(ptLast, point);
		if(dis > 10)
		{			
			m_ArrPoint.Add(point);		//距离够长才添加			
			return TRUE;
		}		
	}
	return FALSE;	
}
bool CMTrArea::HasEnded()
{
	return m_nStep > 1;
}

int CMTrArea::GetResultCount()
{
	return 1;
}

bool CMTrArea::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetCanveArea(m_ArrPoint) );
	return true;
}

void CMTrArea::Restart()
{
	m_ArrPoint.RemoveAll();
	m_nStep = 0;
}