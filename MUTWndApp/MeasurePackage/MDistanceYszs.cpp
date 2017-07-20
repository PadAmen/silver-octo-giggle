// MDistanceYszs.cpp: implementation of the CMVolumeBi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MDistanceYszs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMDistanceYszs::CMDistanceYszs(const CComputeMethod &computer):CMeasureObject(computer),
m_Distance1(computer),m_Distance2(computer),m_Distance3(computer),m_Distance4(computer)
{
	m_nStep = 0;
}

CMDistanceYszs::~CMDistanceYszs()
{

}
CMeasureObject *CMDistanceYszs::Clone()
{
	return new CMDistanceYszs(m_computer);
}
void CMDistanceYszs::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance2.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance3.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance4.DrawObject(dc,nIndex);
}
bool CMDistanceYszs::HasEnded()
{
	return m_nStep==4;
}
bool CMDistanceYszs::HasStarted()
{
	return m_Distance1.HasStarted();
}
BOOL CMDistanceYszs::OnLButtonDown(UINT nFlags, CPoint point)
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
	case 2:
		{
			m_Distance3.OnLButtonDown(nFlags, point);
			if(m_Distance3.HasEnded())//结束
			{
				m_nStep=3;
			}
			return TRUE;
			break;
		}
	case 3:
		{
			m_Distance4.OnLButtonDown(nFlags, point);
			if(m_Distance4.HasEnded())//结束
			{
				m_nStep=4;
			}
			return TRUE;
			break;
		}
	}	
	return FALSE;
}
BOOL CMDistanceYszs::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		return	m_Distance1.OnMouseMove(nFlags, point);
	}
	else if(m_nStep==1)
	{
		return m_Distance2.OnMouseMove(nFlags, point);		
	}
	else if (m_nStep==2)
	{
		return m_Distance3.OnMouseMove(nFlags, point);
	} 
	else if(m_nStep==3)
	{
		m_Distance4.OnMouseMove(nFlags, point);
		return TRUE;
	}
	return FALSE;
}

void CMDistanceYszs::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strText;
	
	strText.Format(_T("Q1:  %8.2f cm"), m_Distance1.GetDistance() );
	
	dc->TextOut(x,y, strText);
	y += szLine.cy;

	CString strText1;
	
	strText1.Format(_T("Q2:  %8.2f cm"), m_Distance2.GetDistance() );
	
	dc->TextOut(x,y, strText1);
	y += szLine.cy;

	CString strText2;
	
	strText2.Format(_T("Q3:  %8.2f cm"), m_Distance3.GetDistance() );
	
	dc->TextOut(x,y, strText2);
	y += szLine.cy;

	CString strText3;
	
	strText3.Format(_T("Q4:  %8.2f cm"), m_Distance4.GetDistance() );
	
	dc->TextOut(x,y, strText3);
	y += szLine.cy;
	float num = 0.0;
	if ( m_nStep>=3 && m_Distance4.HasStarted() )
	{
		num = m_Distance1.GetDistance() + m_Distance2.GetDistance() +
			m_Distance3.GetDistance() + m_Distance4.GetDistance();
	}
	CString strText4;
	
	strText4.Format(_T("AFI:  %8.2f cm"), num );
	
	dc->TextOut(x,y, strText4);
}

bool CMDistanceYszs::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back(m_Distance1.GetDistance());		//保存第一条直线的长度，计算平均孕周和预产期
	lstResult.push_back( (m_Distance1.GetDistance() + m_Distance2.GetDistance() +
						  m_Distance3.GetDistance() + m_Distance4.GetDistance()) );
	return true;
}

void CMDistanceYszs::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_Distance3.Restart();
	m_Distance4.Restart();
	m_nStep = 0;
	m_result.clear();
}