// MVolumeBiQlxtj.cpp: implementation of the CMVolumeBi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MVolumeBiQlxtj.h"
#define PI 3.1415926535898
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVolumeBiQlxtj::CMVolumeBiQlxtj(const CComputeMethod &computer):CMVolumeBi(computer)
{
	m_nStep = 0;
}

CMVolumeBiQlxtj::~CMVolumeBiQlxtj()
{
	
}

CMeasureObject *CMVolumeBiQlxtj::Clone()
{
	return new CMVolumeBiQlxtj(m_computer);
}


void CMVolumeBiQlxtj::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strText;
	strText.Format(_T("L : %8.2f cm"), GetDistance1());
	dc->TextOut(x, y, strText);
	y += szLine.cy;
	strText.Format(_T("W : %8.2f cm"), GetDistance2());
	dc->TextOut(x, y, strText);
	y += szLine.cy;
	strText.Format(_T("H : %8.2f cm"), GetDistance3());
	dc->TextOut(x, y, strText);
	y += szLine.cy;
	CString strV;
	
	strV.Format(_T("V : %8.2f ml"), m_computer.GetVolumeBi(GetDistance1(),
		GetDistance2(),GetDistance3()));
	
	dc->TextOut(x,y, strV);
	y += szLine.cy;
	CString strAge;
	
	strAge.Format(_T("P.PSA:%8.2f ng/ml"), GetAge() );
	
	dc->TextOut(x,y, strAge);
	y += szLine.cy;
}

bool CMVolumeBiQlxtj::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( GetDistance1() );		//长
	lstResult.push_back( GetDistance2() );		//宽
	lstResult.push_back( GetDistance3() );		//高
	lstResult.push_back( m_computer.GetVolumeBi(GetDistance1(),		//体积
												GetDistance2(),
												GetDistance3()));
	lstResult.push_back( GetAge() );			//P.PSA
	return true;
}