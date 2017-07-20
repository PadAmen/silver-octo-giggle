// MVolumeTr.cpp: implementation of the CMVolumeTr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MVolumeTr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVolumeTr::CMVolumeTr(const CComputeMethod &computer):CMeasureObject(computer),
					m_Distance(computer),m_TrArea(computer)
{
	m_nStep = 0;
}

CMVolumeTr::~CMVolumeTr()
{

}
bool CMVolumeTr::HasEnded()
{
	return m_nStep==2;
}
bool CMVolumeTr::HasStarted()
{
	return m_TrArea.HasStarted();
}
CMeasureObject*CMVolumeTr::Clone()
{
	CMVolumeTr *pVolumeTr =  new CMVolumeTr(m_computer);
	pVolumeTr->m_nStep = this->m_nStep;
	this->m_Distance.BackUpObj(pVolumeTr->m_Distance);
	this->m_TrArea.BackUpObj(pVolumeTr->m_TrArea);
	return pVolumeTr;
}
void CMVolumeTr::DrawObject(CDC *dc,int nIndex)
{
	m_TrArea.DrawObject(dc, nIndex);
	nIndex ++;
	m_Distance.DrawObject(dc,nIndex);
}
BOOL CMVolumeTr::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_nStep==0)
	{
		m_TrArea.OnLButtonDown(nFlags, point);
		if (m_TrArea.HasEnded())
		{
			m_nStep = 1;
		}
		return TRUE;
	}
	else if (m_nStep==1)
	{
		m_Distance.OnLButtonDown(nFlags, point);
		if(m_Distance.HasEnded())	
			m_nStep=2;
		return TRUE;
	}
	return FALSE;
}
BOOL CMVolumeTr::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nStep==0)
	{
		return	m_TrArea.OnMouseMove(nFlags, point);
	
	}
	else if (m_nStep==1)
	{
		return m_Distance.OnMouseMove(nFlags, point);	
	}
	return FALSE;
}
void CMVolumeTr::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strA, strD, strVOL;
	m_TrArea.DrawResult(dc, x, y);		//y += szLine.cy;
	m_Distance.DrawResult(dc,  x, y);	//y += szLine.cy;
	if(m_Distance.HasStarted())
		strVOL.Format(_T("VOL: %8.2f cm^3"), m_computer.GetVolumeTr(m_TrArea.GetArea(), m_Distance.GetDistance()) );
	else 
		strVOL = (_T("VOL: --------"));	
	dc->TextOut(x, y, strVOL);	y += szLine.cy;
}

void CMVolumeTr::Restart()
{
	m_TrArea.Restart();
	m_Distance.Restart();
	m_nStep = 0;
}