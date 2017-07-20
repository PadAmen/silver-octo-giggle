// MHeartEjbBkll.cpp: implementation of the CHeartEjbBkll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartEjbBkll.h"
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

CHeartEjbBkll::CHeartEjbBkll(const CComputeMethod &computer):CHeartSBTime(computer)
{
	m_nStep = 0;
}

CHeartEjbBkll::~CHeartEjbBkll()
{

}

CMeasureObject *CHeartEjbBkll::Clone()
{
	return new CHeartEjbBkll(m_computer);
}

int CHeartEjbBkll::GetResultCount()
{
	return 1;
}

void CHeartEjbBkll::DrawResult(CDC *dc, int &x, int &y)
{
	CString str;
	str.Format(_T("%8.2f ml"), m_computer.GetSlope(m_pointStart, m_pointEnd));
	dc->TextOut(x,y,str);
}

bool CHeartEjbBkll::GetResultArray(vector<double> &lstResult) const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetSlope(m_pointStart, m_pointEnd) );
	return true;
}