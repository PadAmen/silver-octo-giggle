// MVolumeBi.cpp: implementation of the CMVolumeBi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MVolumeBi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVolumeBi::CMVolumeBi(const CComputeMethod &computer):CMeasureObject(computer),
	m_Distance1(m_computer),m_Distance2(computer),m_Distance3(m_computer)
{
	m_nStep = 0;
}

CMVolumeBi::~CMVolumeBi()
{

}
CMeasureObject *CMVolumeBi::Clone()
{
	return new CMVolumeBi(m_computer);
}

float CMVolumeBi::GetAge()const
{
	return ( (float)(0.125 * m_computer.GetVolumeBi(m_Distance1.GetDistance(),
		m_Distance2.GetDistance(),
		m_Distance3.GetDistance())) );
}

float CMVolumeBi::GetDistance1()const
{
	return m_Distance1.GetDistance();
}

float CMVolumeBi::GetDistance2()const
{
	return m_Distance2.GetDistance();
}

float CMVolumeBi::GetDistance3()const
{
	return m_Distance3.GetDistance();
}

void CMVolumeBi::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance2.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance3.DrawObject(dc,nIndex);
	nIndex += 1;
}
bool CMVolumeBi::HasEnded()
{
	return m_nStep==3;
}
bool CMVolumeBi::HasStarted()
{
	return m_Distance1.HasStarted();
}
BOOL CMVolumeBi::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMDistance *pDis[3]={&m_Distance1, &m_Distance2, &m_Distance3};
	if(m_nStep < 3)
	{
		pDis[m_nStep]->OnLButtonDown(nFlags, point);
		if(pDis[m_nStep]->HasEnded())
		{
			m_nStep++;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMVolumeBi::OnMouseMove(UINT nFlags, CPoint point)
{
	CMDistance *pDis[3]={&m_Distance1, &m_Distance2, &m_Distance3};
	if(m_nStep<3)
	{
		return pDis[m_nStep]->OnMouseMove(nFlags, point);
	}
	return FALSE;
}

void CMVolumeBi::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strText;
	float d1 = m_Distance1.GetDistance();
	float d2 = m_Distance2.GetDistance();
	float d3 = m_Distance3.GetDistance();
	strText.Format(_T("L: %8.2f cm"), d1);
	dc->TextOut(x, y, strText);
	y += szLine.cy;

	strText.Format(_T("W: %8.2f cm"), d2);
	dc->TextOut(x, y, strText);
	y += szLine.cy;

	strText.Format(_T("H: %8.2f cm"), d3);
	dc->TextOut(x, y, strText);
	y += szLine.cy;

	CString strV;
	strV.Format(_T("V: %8.2f ml"), m_computer.GetVolumeBi(d1,d2, d3) );
	dc->TextOut(x,y, strV);
}

bool CMVolumeBi::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_Distance1.GetDistance() );			//长
	lstResult.push_back( m_Distance2.GetDistance() );			//宽
	lstResult.push_back( m_Distance3.GetDistance() );			//高
	lstResult.push_back( m_computer.GetVolumeBi(m_Distance1.GetDistance(),		//体积
												m_Distance2.GetDistance(),
												m_Distance3.GetDistance()) );
	return true;
}

void CMVolumeBi::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_Distance3.Restart();
	m_nStep = 0;
}