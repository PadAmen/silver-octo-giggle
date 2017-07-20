// MHeartZsgn.cpp: implementation of the CMHeartZsgn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MHeartZsgn.h"
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

CHeartZsgn::CHeartZsgn(const CComputeMethod &computer):CMeasureObject(computer)
,m_Distance1(computer),m_Distance2(computer)
{
	m_nStep = 0;
}

CHeartZsgn::~CHeartZsgn()
{

}

BOOL CHeartZsgn::OnLButtonDown(UINT nFlags, CPoint point)
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

BOOL CHeartZsgn::OnMouseMove(UINT nFlags, CPoint point)
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

CMeasureObject *CHeartZsgn::Clone()
{
	return new CHeartZsgn(m_computer);
}

void CHeartZsgn::DrawObject(CDC *dc,int nIndex)
{
	m_Distance1.DrawObject(dc,nIndex);
	nIndex+=1;
	m_Distance2.DrawObject(dc,nIndex);
}

void CHeartZsgn::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	// 输入
	ct.lvidd = m_Distance1.GetSlope();
	ct.lvids = m_Distance2.GetSlope();
	GetTeichholz(ct);

	CString str;
	str.Format(_T("LVIDd:%8.2f cm"), ct.lvidd);	dc->TextOut(x, y,str);		y += szLine.cy;
	str.Format(_T("LVIDs:%8.2f cm"), ct.lvids);	dc->TextOut(x, y,str);		y += szLine.cy;
	str.Format(_T("EDC:   %8.2f ml"), ct.edv);	dc->TextOut(x, y,str);		y += szLine.cy;
	str.Format(_T("ESV:   %8.2f ml"), ct.esv);	dc->TextOut(x, y,str);		y += szLine.cy;
	str.Format(_T("SV:   %8.2f ml"), ct.sv);	dc->TextOut(x, y,str);		y += szLine.cy;
	str.Format(_T("FS:   %8.2f%%"), ct.fs);		dc->TextOut(x, y,str);		y += szLine.cy;
	str.Format(_T("EF:   %8.2f%%"), ct.ef);		dc->TextOut(x, y,str);		y += szLine.cy;
}

bool CHeartZsgn::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back( ct.lvidd );		//左室内径
	lstResult.push_back( ct.lvids );		//左室收缩末内径
	lstResult.push_back( ct.fs );			//缩短分数
	lstResult.push_back( ct.sv );			//每搏量										
	lstResult.push_back( ct.ef);			//射血分数
	//心搏指数未知
	return true;
}


bool CHeartZsgn::HasEnded()
{
	return m_nStep==2;
}

int CHeartZsgn::GetResultCount()
{
	return 7;
}


void CHeartZsgn::GetTeichholz(CUBE_TEICHHOLZT& ct)
{
	ct.bas = m_computer.GetBodyArea();
	switch (m_computer.GetHeartMethod())
	{
	case 0:
		ct.edv = ct.lvidd * ct.lvidd * ct.lvidd;
		ct.esv = ct.lvids * ct.lvids * ct.lvids;
		break;
	case 1:
		ct.edv = 7.0 * ct.lvidd * ct.lvidd * ct.lvidd / (2.4 + ct.lvidd);
		ct.esv = 7.0 * ct.lvids * ct.lvids * ct.lvids / (2.4 + ct.lvids);
		break;
	case 2:
		ct.edv = PI / 6.0 * ct.lvidd * ct.lvidd * (5.90 + ct.lvidd * 0.98);
		ct.esv = PI / 6.0 * ct.lvids * ct.lvids * (4.18 + ct.lvids * 1.14);
		break;
	}
	if ((ct.edv > 0) && (ct.esv > 0))
	{
		ct.sv  = ct.edv - ct.esv;
		ct.svi = (ct.bas > 0) ? (ct.sv / ct.bas) : 0;
		ct.co  = ct.sv * ct.rate / 1000;
		ct.coi = (ct.bas > 0) ? (ct.co / ct.bas) : 0;
		ct.ef  = (ct.edv > 0) ? (ct.sv / ct.edv * 100) : 0;
		ct.fs  = (ct.lvidd - ct.lvids) / ct.lvidd * 100;
		ct.mvcf = (ct.et > 0) ? ((ct.lvidd - ct.lvids) / (ct.lvidd * ct.et) * 100) : 0;
	}
	else
	{
		ct.sv  = 0;
		ct.svi = 0;
		ct.co  = 0;
		ct.coi = 0;
		ct.ef  = 0;
		ct.fs  = 0;
		ct.mvcf = 0;
	}
}

void CHeartZsgn::Restart()
{
	m_Distance1.Restart();
	m_Distance2.Restart();
	m_nStep = 0;
}
