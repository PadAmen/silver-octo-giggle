// MHeartLHWeight.cpp: implementation of the CHeartLHWeight class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartLHWeight.h"
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

CHeartLHWeight::CHeartLHWeight(const CComputeMethod &computer):CMeasureObject(computer)
								,m_Distance1(computer),m_Distance2(computer),m_Distance3(computer)
{
	m_nStep = 0;
}

CHeartLHWeight::~CHeartLHWeight()
{

}

BOOL CHeartLHWeight::OnLButtonDown(UINT nFlags, CPoint point)
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
	case 2:
		{
			m_Distance3.OnLButtonDown(nFlags, point);
			if(m_Distance3.HasEnded())//½áÊø
			{
				m_nStep=3;
			}
			return TRUE;
			break;
		}
	}	
	return FALSE;
}

BOOL CHeartLHWeight::OnMouseMove(UINT nFlags, CPoint point)
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
	else if(m_nStep==2)
	{
		m_Distance3.OnMouseMove(nFlags, point);	
		return TRUE;
	}
	return FALSE;
}

CMeasureObject *CHeartLHWeight::Clone()
{
	return new CHeartLHWeight(m_computer);
}

void CHeartLHWeight::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance2.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance3.DrawObject(dc,nIndex);
}

void CHeartLHWeight::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	float  d1 = (float)m_Distance1.GetSlope();
	float  d2 = (float)m_Distance2.GetSlope();
	float  d3 = (float)m_Distance3.GetSlope();	
	float  d4 = (float)GetLVMW();
	float  d5 = (float)GetLVMWI();

	CString str;
	str.Format(_T("LVPWd:%8.2f cm"), d1);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	str.Format(_T("IVSTd:%8.2f cm"), d2);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	str.Format(_T("LVIDd:%8.2f cm"), d3);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	str.Format(_T("LVMW:%8.2f g"), d4);
	dc->TextOut(x, y,str);	
	y += szLine.cy;

	str.Format(_T("LVMWI:%8.2f "), d5);
	dc->TextOut(x, y,str);	

}


bool CHeartLHWeight::HasEnded()
{
	return m_nStep==3;
}

int CHeartLHWeight::GetResultCount()
{
	return 5;
}

double CHeartLHWeight::GetLVMW()const
{
	float LVSTd = (float)m_Distance1.GetLine();
	float LVPWd = (float)m_Distance2.GetLine();
	float LVIDd = (float)m_Distance3.GetLine();

	if ((LVSTd == 0) || (LVPWd == 0) || (LVIDd == 0)) return 0.0;
	double a = (LVSTd + LVPWd + LVIDd);
	double b = LVIDd;
	return 1.05 * (a*a*a - b*b*b);
}



double CHeartLHWeight::GetLVMWI()const
{
	return GetLVMW() / m_computer.GetBodyArea();
}

bool CHeartLHWeight::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_Distance1.GetSlope() );
	lstResult.push_back( m_Distance2.GetSlope() );
	lstResult.push_back( m_Distance3.GetSlope() );
	lstResult.push_back( GetLVMW() );
	lstResult.push_back( GetLVMWI() );
	return true;
}

void CHeartLHWeight::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_Distance3.Restart();
	m_nStep = 0;
}


