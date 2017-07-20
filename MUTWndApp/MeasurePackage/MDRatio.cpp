// MDRatio.cpp: implementation of the CMDRatio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MDRatio.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMDRatio::CMDRatio(const CComputeMethod &computer):CMeasureObject(computer),
	m_Distance1(computer),m_Distance2(computer)
{
	m_nStep = 0;
}

CMDRatio::~CMDRatio()
{

}


CMeasureObject *CMDRatio::Clone()
{
	return new CMDRatio(m_computer);
}
void CMDRatio::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance2.DrawObject(dc,nIndex);
}
bool CMDRatio::HasEnded()
{
	return m_nStep==2;
}
BOOL CMDRatio::OnLButtonDown(UINT nFlags, CPoint point)
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
			if(m_Distance2.HasEnded()) m_nStep = 2;		
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CMDRatio::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep==0)
	{
		m_Distance1.OnMouseMove(nFlags, point);
		return TRUE;
	}
	else if(m_nStep==1)
	{
		m_Distance2.OnMouseMove(nFlags, point);		
		return TRUE;
	}
	return FALSE;
}


void CMDRatio::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	float  d1 = m_Distance1.GetDistance();
	float  d2 = m_Distance2.GetDistance();
	CString str;
	str.Format(_T("D1:%8.2f cm"), d1);
	dc->TextOut(x, y,str);	
	y += szLine.cy;
	str.Format(_T("D2:%8.2f cm"), d2);
	dc->TextOut(x, y,str);		
	y += szLine.cy;
	
	CString strRatio;
	CString strPercent;
	if(d2 < 0.00001)	strPercent=_T("D1/D2: --------");
	else				strPercent.Format(_T("D1/D2: %8.2f%%"), 100*d1/d2);
	dc->TextOut(x, y, strPercent);
	y += szLine.cy;
}

int CMDRatio::GetResultCount()
{
	return 3;
}

void CMDRatio::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_nStep = 0;
	m_fRatio = 0.0;
	strRatio = _T("");
}