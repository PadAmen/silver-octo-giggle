// MSlope.cpp: implementation of the CMSlope class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MSlope.h"
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

CMSlope::CMSlope(const CComputeMethod &computer):CMDistance(computer)
{
	m_nStep = 0;
}

CMSlope::~CMSlope()
{

}

CMeasureObject *CMSlope::Clone()
{
	return new CMSlope(m_computer);
}
int CMSlope::GetResultCount()
{
	return 1;
}

void CMSlope::DrawResult(CDC *dc,int &x,int &y)
{
	CString str;
	str.Format(_T("%8.2f cm"), GetSlope());
	dc->TextOut(x,y,str);

}