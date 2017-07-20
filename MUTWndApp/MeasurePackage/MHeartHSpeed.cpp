// MHeartHSpeed.cpp: implementation of the CHeartHSpeed class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartHSpeed.h"
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

CHeartHSpeed::CHeartHSpeed(const CComputeMethod &computer):CHeartSBTime(computer)
{
	m_nStep = 0;
}

CHeartHSpeed::~CHeartHSpeed()
{

}


void CHeartHSpeed::DrawResult(CDC *dc,int &x,int &y)
{
	CString str;
	double speed = m_computer.GetHeartRate(m_pointStart,m_pointEnd);
	str.Format(_T("%8.2f bpm"), speed);
	dc->TextOut(x, y,str);	
}

bool CHeartHSpeed::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( m_computer.GetHeartRate(m_pointStart,m_pointEnd) );
	return true;
}