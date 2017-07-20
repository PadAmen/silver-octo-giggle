// MArea.cpp: implementation of the CMArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MArea.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMArea::CMArea(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
}

CMArea::~CMArea()
{
	CPoint *p ;
	for(int i=0;i<m_ArrPoint.GetSize();i++)
	{
		p = (CPoint*)m_ArrPoint.GetAt(i);
		delete p;
		p=NULL;
	}
}
BOOL CMArea::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		m_ArrPoint.Add(new CPoint(point));
		m_nStep = 1;
		return TRUE;
	}
	else 
	{
		m_nStep = 2;
		return TRUE;
	}
	return FALSE;

}
BOOL CMArea::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==1)
	{		
		CPoint *pLast = (CPoint*)m_ArrPoint.GetAt(m_ArrPoint.GetSize()-1);
		double dis = this->m_computer.GetDistanceInPixes(*pLast, point);
		if(dis > 15)
		{
			m_ArrPoint.Add(new CPoint(point));//距离够长才添加
			return TRUE;
		}
		//}		else m_ArrPoint.Add(new CPoint(point));	
	}
	return FALSE;
}
void CMArea::DrawObject(CDC *dc,int nIndex)
{
	if(m_nStep<1) return;
	//使用虚线
	CPen pen(PS_DOT,1,0xff00ff),*oldPen;
	oldPen = dc->SelectObject(&pen);
	
	CPoint *p;
	//将所有点连起来
	for(int i = 0;i<m_ArrPoint.GetSize();i++)
	{
		p=(CPoint*)m_ArrPoint.GetAt(i);
		if(i != 0)	dc->LineTo(p->x,p->y);
		dc->MoveTo(p->x,p->y);
	}
	CPoint *pStart  = (CPoint*)m_ArrPoint.GetAt(0);
	DrawNumber(dc,nIndex,*pStart);
	//将首尾连起来
	if(m_ArrPoint.GetSize()>2 && m_nStep==2)
	{
	
		dc->LineTo(pStart->x,pStart->y);
	}
	//选回绘图设备
	dc->SelectObject(&oldPen);
	
	if(m_nStep<2)
	{
		HBRUSH nullbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		CPen RingPen(PS_SOLID,1,0x00ffff);
		void *oldbr = dc->SelectObject(nullbr);
		oldPen = dc->SelectObject(&RingPen);
		dc->Ellipse(pStart->x-4,pStart->y-4,pStart->x+4,pStart->y+4);
		dc->SelectObject(oldbr);
		dc->SelectObject(&oldPen);
	}
	return ;
}
void CMArea::DrawResult(CDC *dc,int x,int y)
{
	if(HasStarted())
	{
		CString str;
		str.Format(_T(" A: %8.2f"), this->m_computer.GetCanveArea(m_ArrPoint));
		dc->TextOut(x, y,  str);
	}
	else
	{
		CString str;
		str.Format(_T(" A: --------"));
		dc->TextOut(x, y,"A: %8.2f mm^2");
	}
}
bool CMArea::HasEnded()
{
	return m_nStep>1;
}

CMeasureObject *CMArea::Clone()
{
	return new CMArea(m_computer);
}

int  CMArea::GetResultCount()//最终测量结果值的个数
{
	return 2;
}