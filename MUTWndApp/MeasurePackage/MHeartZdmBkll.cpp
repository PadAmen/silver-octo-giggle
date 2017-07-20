// MHeartZdmBkll.cpp: implementation of the CHeartZdmBkll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartZdmBkll.h"
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

CHeartZdmBkll::CHeartZdmBkll(const CComputeMethod &computer):CHeartLHWeight(computer)
{
	m_nStep = 0;
}

CHeartZdmBkll::~CHeartZdmBkll()
{

}

CMeasureObject *CHeartZdmBkll::Clone()
{
	return new CHeartZdmBkll(m_computer);
}

int CHeartZdmBkll::GetResultCount()
{
	return 4;
}

void CHeartZdmBkll::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString str;
	str.Format(_T("MOVO1:   %8.2f cm"), m_Distance1.GetSlope());
	dc->TextOut(x, y, str);
	y += szLine.cy;

	str.Format(_T("MOVO2:   %8.2f cm"), m_Distance2.GetSlope());
	dc->TextOut(x, y, str);
	y += szLine.cy;

	str.Format(_T("AA:   %8.2f cm"), m_Distance3.GetSlope());
	dc->TextOut(x, y, str);
	y += szLine.cy;

	str.Format(_T("vol:   %8.2f ml"), m_computer.GetVolumeBi(
								(float)m_Distance1.GetLine(), 
								(float)m_Distance2.GetLine(),
								(float)m_Distance3.GetLine()));
	dc->TextOut(x, y, str);
}

bool CHeartZdmBkll::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetVolumeBi( (float)m_Distance1.GetLine(), 
												 (float)m_Distance2.GetLine(),
												 (float)m_Distance3.GetLine()));
	lstResult.push_back( m_Distance3.GetSlope());
	return true;
}