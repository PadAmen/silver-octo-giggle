// MTrLength.cpp: implementation of the CMTrLength class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MTrLength.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMTrLength::CMTrLength(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
	m_fTrLengthInPix = 0;
}

CMTrLength::~CMTrLength()
{	
}
CMeasureObject *CMTrLength::Clone()
{
	CMTrLength *pTrLength = new CMTrLength(m_computer);
	pTrLength->m_nStep = this->m_nStep;
	pTrLength->m_ArrPoint.Copy(this->m_ArrPoint);
	pTrLength->m_fTrLengthInPix = this->m_fTrLengthInPix;
	return pTrLength;
}
void CMTrLength::DrawObject(CDC *dc,int nIndex)
{
	if(m_nStep<1) return;	
	CPen pen, *oldPen;
	//dc->SetBkMode(TRANSPARENT);
	//绘制中/绘制完毕使用不同颜色的线条
	pen.CreatePen(PS_DOT, 1, m_nStep<2 ? 0xffffff : 0xaaaaaa);
	oldPen = dc->SelectObject(&pen);	
	CPoint p;
	//将所有点连起来
	for(int i=0; i<m_ArrPoint.GetSize(); i++)
	{
		p = m_ArrPoint.GetAt(i);
		if(i != 0)	dc->LineTo(p.x, p.y);
		dc->MoveTo(p.x, p.y);
	}

	//选回绘图设备
	dc->SelectObject(&oldPen);
	CPoint pStart  = m_ArrPoint.GetAt(0);
	DrawNumber(dc,nIndex,pStart);
	//在起点画个圈
	if(m_nStep < 2)
	{		
		//HBRUSH nullbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		//CPen RingPen(PS_SOLID, 1, 0x00ffff);
		//void *oldbr = dc->SelectObject(nullbr);
		//oldPen = dc->SelectObject(&RingPen);
		dc->Ellipse(pStart.x-4, pStart.y-4, pStart.x+4, pStart.y+4);
		//dc->SelectObject(oldbr);
		//dc->SelectObject(&oldPen);
	}

}
BOOL CMTrLength::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		m_ArrPoint.Add(point);
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
BOOL CMTrLength::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==1)
	{	
		CPoint pLast = m_ArrPoint.GetAt(m_ArrPoint.GetSize()-1);
		double dis = this->m_computer.GetDistanceInPixes(pLast, point);
		if(dis > 15)	
		{
			m_ArrPoint.Add( point );//距离够长才添加
			m_fTrLengthInPix += float(dis);
		}
		return TRUE;
	}
	return FALSE;	
}
bool CMTrLength::HasEnded()
{
	return m_nStep > 1;
}

void CMTrLength::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strResult;	
	strResult.Format(_T("L: %8.2f cm"),  m_computer.GetCanveDistance(m_ArrPoint, false));	
	//绘制文本
	dc->TextOut(x, y, strResult);
	y += szLine.cy;

}

void CMTrLength::Restart()
{
	m_ArrPoint.RemoveAll();
	m_nStep = 0;
	m_fTrLengthInPix = 0;
}

