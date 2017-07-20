// MDiamPercent.cpp: implementation of the CMDiamPercent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "MDiamPercent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMDiamPercent::CMDiamPercent(const CComputeMethod &computer):CMeasureObject(computer),
	m_Distance1(computer),m_Distance2(computer)
{
	m_nStep = 0;	
}

CMDiamPercent::~CMDiamPercent()
{

}
CMeasureObject *CMDiamPercent::Clone()
{
	return new CMDiamPercent(m_computer);
}
void CMDiamPercent::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance2.DrawObject(dc,nIndex);	
}
void CMDiamPercent::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	//画线
	float  d1 = m_Distance1.GetDistance();
	float  d2 = m_Distance2.GetDistance();
	CString str;
	str.Format(_T("D1:%8.2f cm"), d1);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	str.Format(_T("D2:%8.2f cm"), d2);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	//计算并绘制最终结果
	if(d1 < 0.0001f) 
	{
		strPercent=("% D: --------");			
	}
	else
	{		
		strPercent.Format(_T("△D/D1: %8.2f%%"), (fabs(d1-d2)*100/d1));		
	}	
	dc->TextOut(x,y, strPercent);	
}
bool CMDiamPercent::HasEnded()
{
	return m_nStep==2;
}
bool CMDiamPercent::HasStarted()
{
	return m_Distance1.HasStarted();
}
BOOL CMDiamPercent::OnLButtonDown(UINT nFlags, CPoint point)
{
	switch(m_nStep)
	{
	case 0:
		{
			m_Distance1.OnLButtonDown(nFlags,point);
			if(m_Distance1.HasEnded()) m_nStep=1;
			return TRUE;
			break;
		}
	case 1:
		{
			m_Distance2.OnLButtonDown(nFlags, point);
			if(m_Distance2.HasEnded())//结束
			{
				m_nStep=2;
			}
			return TRUE;
			break;
		}
	}	
	return FALSE;
}
BOOL CMDiamPercent::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		return	m_Distance1.OnMouseMove(nFlags, point);
	}
	else if(m_nStep==1)
	{
		m_Distance2.OnMouseMove(nFlags, point);		
		return TRUE;
	}
	return FALSE;
}

int CMDiamPercent::GetResultCount()
{
	return 3;
}

void CMDiamPercent::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_nStep = 0;
	strPercent = _T("");
}