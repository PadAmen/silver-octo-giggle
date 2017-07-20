#include "stdafx.h"

#include "MVolumeTD.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVolumeTD::CMVolumeTD(const CComputeMethod &computer):CMeasureObject(computer),
m_Distance1(m_computer),m_Distance2(computer),m_Distance3(m_computer)
{
	m_nStep = 0;
}

CMVolumeTD::~CMVolumeTD()
{

}
CMeasureObject *CMVolumeTD::Clone()
{
	CMVolumeTD *pVolumeTD = new CMVolumeTD(m_computer);
	pVolumeTD->m_nStep = this->m_nStep;
	
	this->m_Distance1.BackUpObj(pVolumeTD->m_Distance1);
	this->m_Distance2.BackUpObj(pVolumeTD->m_Distance2);
	this->m_Distance3.BackUpObj(pVolumeTD->m_Distance3);

	return pVolumeTD;
}
void CMVolumeTD::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance2.DrawObject(dc,nIndex);
	nIndex += 1;
	m_Distance3.DrawObject(dc,nIndex);
	nIndex += 1;

}
bool CMVolumeTD::HasEnded()
{
	return m_nStep==3;
}
bool CMVolumeTD::HasStarted()
{
	return m_Distance1.HasStarted();
}
BOOL CMVolumeTD::OnLButtonDown(UINT nFlags, CPoint point)
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
BOOL CMVolumeTD::OnMouseMove(UINT nFlags, CPoint point)
{
	CMDistance *pDis[3]={&m_Distance1, &m_Distance2, &m_Distance3};
	if(m_nStep<3)
	{
		return pDis[m_nStep]->OnMouseMove(nFlags, point);
	}
	return FALSE;
}

void CMVolumeTD::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strV;
	
	strV.Format(_T("V:  %8.2f ml"), m_computer.GetVolumeBi(m_Distance1.GetDistance(),
		m_Distance2.GetDistance(),
		m_Distance3.GetDistance()) );
	
	dc->TextOut(x,y, strV);
	y += szLine.cy;

}

bool CMVolumeTD::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetVolumeBi(m_Distance1.GetDistance(),
												m_Distance2.GetDistance(),
												m_Distance3.GetDistance()) );
	return true;
}

void CMVolumeTD::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_Distance3.Restart();
	m_nStep = 0;
}
