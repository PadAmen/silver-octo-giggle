// MHeartSBTime.cpp: implementation of the CHeartSBTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartSBTime.h"
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

CHeartSBTime::CHeartSBTime(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
}

CHeartSBTime::~CHeartSBTime()
{

}

bool CHeartSBTime::HasEnded()
{
	return m_nStep==2;
}

BOOL CHeartSBTime::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep == 0)//点第一下,确定开始点
	{
		m_pointStart = point;
		m_pointEnd = point;
		m_nStep=1;	
		return TRUE;
	}
	else if(m_nStep==1)//点第二下,确定结束点
	{
		//计算两点间距离				
		m_pointEnd = point;
		m_nStep = 2;
		return TRUE;
	}
	return FALSE;
}

BOOL CHeartSBTime::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep == 0){
		m_pointStart = point;
		m_pointEnd = point;	
		return TRUE;
	}else if(m_nStep == 1){
		m_pointEnd = point;		
		return TRUE;
	}
	return FALSE;
}

CMeasureObject *CHeartSBTime::Clone()
{
	return new CHeartSBTime(m_computer);
}

void CHeartSBTime::DrawObject(CDC *dc,int nIndex)
{	
	CPen pen(PS_SOLID,1,0xffffff);
	CPen *oldpen = dc->SelectObject(&pen);
	dc->MoveTo(m_pointStart.x,0);
	dc->LineTo(m_pointStart.x,430);

	dc->MoveTo(m_pointEnd.x,0);
	dc->LineTo(m_pointEnd.x,430);
	dc->SelectObject(oldpen);	
}

void CHeartSBTime::DrawResult(CDC *dc,int &x,int &y)
{
	CString str;
	str.Format(_T("射血时间:%8.2f s"), m_computer.GetM_Time(m_pointStart, m_pointEnd));
	dc->TextOut(x, y,str);	
}

int CHeartSBTime::GetResultCount()
{
	return 1;
}

bool CHeartSBTime::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetM_Time(m_pointStart, m_pointEnd));
	return true;
}

void CHeartSBTime::Restart()
{
	m_nStep = 0;
	m_pointStart.SetPoint(0,0);
	m_pointEnd.SetPoint(0,0);
}
