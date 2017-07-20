// MHeartEjbCACE.cpp: implementation of the CHeartEjbCACE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartEjbCACE.h"
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

CHeartEjbCACE::CHeartEjbCACE(const CComputeMethod &computer):CHeartZdmLADAOD(computer)
{
	m_nStep = 0;
}

CHeartEjbCACE::~CHeartEjbCACE()
{

}

CMeasureObject *CHeartEjbCACE::Clone()
{
	return new CHeartEjbCACE(m_computer);
}

void CHeartEjbCACE::DrawResult(CDC *dc, int &x, int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	float slope1 =(float)m_Distance1.GetSlope();
	float slope2 =(float)m_Distance2.GetSlope();
	CString str;
	str.Format(_T("CA:   %8.2f cm"), slope1);
	dc->TextOut(x,y,str);
	y += szLine.cy;

	str.Format(_T("CE:   %8.2f cm"), slope2);
	dc->TextOut(x,y,str);
	y += szLine.cy;

	str.Format(_T("CA/CE:   %8.2f"), slope1/slope2);
	dc->TextOut(x,y,str);
	y += szLine.cy;
}

bool CHeartEjbCACE::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_Distance1.GetSlope()/m_Distance2.GetSlope() );
	return true;
}