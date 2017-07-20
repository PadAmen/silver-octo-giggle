// MVxArea.cpp: implementation of the CMVxArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MVxArea.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVxArea::CMVxArea(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
	m_AInPix = 0.0f;
	m_PInPix = 0.0f;
}

CMVxArea::~CMVxArea()
{	
	//释放路径点指针
	CPoint *p;
	int len = m_pointArray.GetSize();
	for(int i=0; i<m_pointArray.GetSize(); i++)
	{
		p = (CPoint*)m_pointArray.GetAt(i);
		delete p;	
	}
	p=NULL;
}
CMeasureObject *CMVxArea::Clone()
{
	CMVxArea *pVxArea = new CMVxArea(m_computer);
	pVxArea->m_nStep = this->m_nStep;
	//pVxArea->m_pointArray.Copy(this->m_pointArray);
	for(int i=0;i<this->m_pointArray.GetSize();i++)
	{	
		CPoint *pTemp = new CPoint;						//重新开辟内存
		CPoint *pt =(CPoint*)this->m_pointArray.GetAt(i);
		*pTemp = *pt;
		pVxArea->m_pointArray.Add(pTemp);
	}
	pVxArea->m_pointMove = this->m_pointMove;
	pVxArea->m_PInPix = this->m_PInPix;
	pVxArea->m_AInPix = this->m_AInPix;
	return pVxArea;
}
void CMVxArea::DrawObject(CDC *dc,int nIndex)
{
	if(m_nStep<1) return;
	CPoint *pStart = (CPoint*)m_pointArray.GetAt(0);
	DrawNumber(dc, nIndex, *pStart);
	CPen pen, *oldpen;
	pen.CreatePen(PS_SOLID,1,m_nStep<2 ? 0xeeeeee : 0xffffff);
	oldpen = dc->SelectObject(&pen);
	for(int i=0;i<m_pointArray.GetSize(); i++)
	{
		//画圆圈故使用空画刷
		HBRUSH nullBr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		void *oldbr = dc->SelectObject(nullBr);
		
		CPoint *pTemp = (CPoint*)m_pointArray.GetAt(i);
		//在节点上画一个小圆圈
		dc->Ellipse(pTemp->x-4,pTemp->y-4,pTemp->x+4,pTemp->y+4);
		if(i)
		{
			dc->LineTo(*pTemp);			
		}
		else  
		{
			dc->MoveTo(*pTemp);		
		}
	}
	//连接最后一个点和鼠标位置点之间的线
	if(m_nStep==1)
	{
		dc->LineTo(m_pointMove);
	}
	else if(m_nStep==2)//连到头
	{
		CPoint *pFirst = (CPoint*)m_pointArray.GetAt(0) ;
		dc->LineTo(*pFirst);
	}
	
	if(!this->HasEnded())
	{
		CPoint *ptFirst = (CPoint*)m_pointArray.GetAt(0);
		dc->MoveTo(ptFirst->x - 10, ptFirst->y);
		dc->LineTo(ptFirst->x + 10, ptFirst->y);
		dc->MoveTo(ptFirst->x, ptFirst->y - 10);
		dc->LineTo(ptFirst->x, ptFirst->y + 10);
		dc->Ellipse(ptFirst->x - 8, ptFirst->y-8, ptFirst->x+8, ptFirst->y+8);
	}
	dc->SelectObject(oldpen);
}

bool CMVxArea::HasEnded()
{
	return m_nStep>1;
}
BOOL CMVxArea::OnLButtonDown(UINT nFlags, CPoint point)
{		
	if(m_nStep==0)//开始
	{
		m_pointArray.Add(new CPoint(point));        
		m_nStep=1;
		return TRUE;
	}
	else if(m_nStep<2)
	{
		//如果与开始点距离小于某值,测量结束
		CPoint *pFirst = (CPoint*)m_pointArray.GetAt(0);
		float dis = this->m_computer.GetDistanceInPixes(*pFirst, point);
		if(dis < 8.0f && m_pointArray.GetSize()>2)//至少有2点,结束
		{	//首尾距离
			CPoint *pLast = (CPoint*)m_pointArray.GetAt(m_pointArray.GetSize()-1);
			m_PInPix += this->m_computer.GetDistance(*pFirst, point);
			m_AInPix = this->m_computer.GetCanveArea(m_pointArray);
			m_nStep = 2;
		}
		else
		{
			CPoint *pLast = (CPoint*)m_pointArray.GetAt(m_pointArray.GetSize()-1);
			dis = this->m_computer.GetDistance(point, *pLast);
			m_PInPix += dis;
			m_pointArray.Add(new CPoint(point));                
			m_AInPix = this->m_computer.GetCanveArea(m_pointArray);
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CMVxArea::OnMouseMove(UINT nFlags, CPoint point)
{
	m_pointMove = point;
	return TRUE;
}
void CMVxArea::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));	
	//dc->SetBkMode(TRANSPARENT);
	CString strP;
	CString strA;
	strA.Format(_T("A: %8.2f cm^2"),  m_AInPix);
	strP.Format(_T("P: %8.2f cm"),  m_PInPix);
	
	dc->TextOut(x,y,strA);
	y += szLine.cy;
	dc->TextOut(x,y,strP);
	y += szLine.cy;

}
float CMVxArea::AreaCalculate(CPtrArray &arrPoint)
{
	return 0.0;
	
}

int CMVxArea::GetResultCount()
{
	return 2;
}

void CMVxArea::Restart()
{
	m_pointArray.RemoveAll();
	m_pointMove.SetPoint(0,0);
	m_nStep = 0;
	m_PInPix = 0;
	m_AInPix = 0;
}