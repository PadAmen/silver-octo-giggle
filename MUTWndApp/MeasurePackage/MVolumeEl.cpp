// MVolumeEl.cpp: implementation of the CMVolumeEl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MVolumeEl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVolumeEl::CMVolumeEl(const CComputeMethod &computer):CMeasureObject(computer),
		m_ElArea(m_computer)
{

}

CMVolumeEl::~CMVolumeEl()
{

}
CMeasureObject *CMVolumeEl::Clone()
{
	CMVolumeEl *pVolumeEl = new CMVolumeEl(m_computer);
	pVolumeEl->m_nStep = this->m_nStep;
	this->m_ElArea.BackUpObj(pVolumeEl->m_ElArea);

	return pVolumeEl;
}
bool CMVolumeEl::HasEnded()
{
	return m_ElArea.HasEnded();
}
bool CMVolumeEl::HasStarted()
{
	return m_ElArea.HasStarted();
}
BOOL CMVolumeEl::OnLButtonDown(UINT nFlags, CPoint point)
{
	return	m_ElArea.OnLButtonDown(nFlags,point);	
}
BOOL CMVolumeEl::OnMouseMove(UINT nFlags, CPoint point)
{	
	return	m_ElArea.OnMouseMove(nFlags, point);
	
}
void CMVolumeEl::DrawObject(CDC *dc,int nIndex)
{
	m_ElArea.DrawObject(dc,nIndex);
}

void CMVolumeEl::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));	
	m_ElArea.DrawResult(dc, x, y);		//y += m_ElArea.GetResultCount()* szLine.cy;
	CString strVol;
	strVol.Format(_T("VOL:  %8.2f ml"), m_computer.GetVolumeEl(m_ElArea.GetLongRInPixel(), m_ElArea.GetShortRInPixel()));
	dc->TextOut(x, y, strVol);	y += szLine.cy;
}

int  CMVolumeEl::GetResultCount()
{
	return m_ElArea.GetResultCount()+1;
}

void CMVolumeEl::Restart()
{
	m_ElArea.Restart();
	m_nStep = 0;
}
