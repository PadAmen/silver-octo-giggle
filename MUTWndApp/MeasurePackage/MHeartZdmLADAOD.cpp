// MHeartZdmLADAOD.cpp: implementation of the CMHeartZdmLADAOD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartZdmLADAOD.h"
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

CHeartZdmLADAOD::CHeartZdmLADAOD(const CComputeMethod &computer):CMeasureObject(computer)
,m_Distance1(computer),m_Distance2(computer)
{
	m_nStep = 0;
}

CHeartZdmLADAOD::~CHeartZdmLADAOD()
{

}

BOOL CHeartZdmLADAOD::OnLButtonDown(UINT nFlags, CPoint point)
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
			if(m_Distance2.HasEnded())
			{
				m_nStep=2;
			}
			return TRUE;
			break;
		}
	}	
	return FALSE;
}

BOOL CHeartZdmLADAOD::OnMouseMove(UINT nFlags, CPoint point)
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

CMeasureObject *CHeartZdmLADAOD::Clone()
{
	return new CHeartZdmLADAOD(m_computer);
}

void CHeartZdmLADAOD::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance2.DrawObject(dc,nIndex);
}

void CHeartZdmLADAOD::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	float  d1 = (float)m_Distance1.GetSlope();
	float  d2 = (float)m_Distance2.GetSlope();

	CString str;
	str.Format(_T("LAD:%8.2f cm"), d1);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	str.Format(_T("AOD:%8.2f cm"), d2);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	if ( d2>0 )
	{
		str.Format(_T("LAD/AOD:%8.2f"), d1/d2);
		dc->TextOut(x, y,str);	
		y += szLine.cy;
	}
	else
	{
		str.Format(_T("LAD/AOD:0.0"));
		dc->TextOut(x, y,str);	
		y += szLine.cy;
	}
}


bool CHeartZdmLADAOD::HasEnded()
{
	return m_nStep==2;
}

int CHeartZdmLADAOD::GetResultCount()
{
	return 3;
}

bool CHeartZdmLADAOD::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_Distance1.GetSlope());
	lstResult.push_back( m_Distance2.GetSlope());
	lstResult.push_back( m_Distance1.GetSlope()/m_Distance2.GetSlope() );
	return true;
}

void CHeartZdmLADAOD::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_nStep = 0;
}
