// MHeartEjbACXjsd.cpp: implementation of the CHeartEjbACXjsd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartEjbACXjsdAndEF.h"
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

CHeartEjbACxjsd::CHeartEjbACxjsd(const CComputeMethod &computer):CHeartSBTime(computer)
{
	m_nStep = 0;
}

CHeartEjbACxjsd::~CHeartEjbACxjsd()
{

}

CMeasureObject *CHeartEjbACxjsd::Clone()
{
	return new CHeartEjbACxjsd(m_computer);
}

void  CHeartEjbACxjsd::DrawResult(CDC *dc,int &x,int &y)
{
	CString str;
	str.Format(_T("%8.2f cm/s"), m_computer.GetSlope(m_pointStart,m_pointEnd));
	dc->TextOut(x,y,str);

}

bool CHeartEjbACxjsd::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetSlope(m_pointStart,m_pointEnd) );
	return true;
}