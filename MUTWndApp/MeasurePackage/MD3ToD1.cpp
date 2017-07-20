// MD3ToD1.cpp: implementation of the CMVolumeBi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MD3ToD1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMD3ToD1::CMD3ToD1(const CComputeMethod &computer):CMeasureObject(computer),
													m_Distance1(m_computer),
													m_Distance2(computer),
													m_Distance3(m_computer)
{
	m_nStep = 0;
}

CMD3ToD1::~CMD3ToD1()
{

}
CMeasureObject *CMD3ToD1::Clone()
{
	return new CMD3ToD1(m_computer);
}
void CMD3ToD1::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance2.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance3.DrawObject(dc,nIndex);
	nIndex += 1;

}

bool CMD3ToD1::HasEnded()
{
	return m_nStep==3;
}
bool CMD3ToD1::HasStarted()
{
	return m_Distance1.HasStarted();
}
BOOL CMD3ToD1::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMDistance *pDis[3]={&m_Distance1, &m_Distance2, &m_Distance3};
	if(m_nStep<3)
	{
		pDis[m_nStep]->OnLButtonDown(nFlags, point);
		if(pDis[m_nStep]->HasEnded())
			m_nStep++;
		return TRUE;
	}
	return FALSE;
}
BOOL CMD3ToD1::OnMouseMove(UINT nFlags, CPoint point)
{
	CMDistance *pDis[3]={&m_Distance1, &m_Distance2, &m_Distance3};
	if(m_nStep<3)
	{
		return pDis[m_nStep]->OnMouseMove(nFlags, point);
	}
	return FALSE;
}

void CMD3ToD1::DrawResult(CDC *dc,int &x,int &y)
{
	CString strText;
	
	strText.Format(_T("D:  %8.2f cm"), m_Distance1.GetDistance() );
	
	dc->TextOut(x,y, strText);
}

bool CMD3ToD1::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back(m_Distance1.GetDistance());
	lstResult.push_back(m_Distance2.GetDistance());
	lstResult.push_back(m_Distance3.GetDistance());
	lstResult.push_back(m_computer.GetVolumeBi(m_Distance1.GetDistance(),
											   m_Distance2.GetDistance(),
											   m_Distance3.GetDistance()));
	return TRUE;
}

void CMD3ToD1::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_Distance3.Restart();
	m_nStep = 0;
}