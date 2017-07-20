// MTwoDistance.cpp: implementation of the CMDiamPercent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "MTwoDistance.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMTwoDistance::CMTwoDistance(const CComputeMethod &computer):CMeasureObject(computer),
m_Distance1(computer),m_Distance2(computer)
{
	m_nStep = 0;	
}

CMTwoDistance::~CMTwoDistance()
{

}
CMeasureObject *CMTwoDistance::Clone()
{
	return new CMDiamPercent(m_computer);
}
void CMTwoDistance::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance2.DrawObject(dc,nIndex);	
}
void CMTwoDistance::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	//画线
	float  d1 = m_Distance1.GetDistance();
	float  d2 = m_Distance2.GetDistance();
	CString str;
	str.Format(_T("L:%8.2f cm"), d1);
	dc->TextOut(x, y,str);	
	y += szLine.cy;;
	str.Format(_T("W:%8.2f cm"), d2);
	dc->TextOut(x, y,str);	
	y += szLine.cy;;
	//计算并绘制最终结果	
	dc->TextOut(x,y, strPercent);
	y += szLine.cy;

}
bool CMTwoDistance::HasEnded()
{
	return m_nStep==2;
}
bool CMTwoDistance::HasStarted()
{
	return m_Distance1.HasStarted();
}
BOOL CMTwoDistance::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CMTwoDistance::OnMouseMove(UINT nFlags, CPoint point)
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

int CMTwoDistance::GetResultCount()
{
	return 2;
}

bool CMTwoDistance::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_Distance1.GetDistance() );		//长
	lstResult.push_back( m_Distance2.GetDistance() );		//宽
	return true;
}

void CMTwoDistance::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	strPercent = _T("");
}