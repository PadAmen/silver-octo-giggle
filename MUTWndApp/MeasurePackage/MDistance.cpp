// MDistance.cpp: implementation of the CMDistance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MDistance.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define POINTNULL (CPoint(-1,-1))

#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMDistance::CMDistance(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep = 0;
	m_pointStart.SetPoint(0, 0);
	m_pointEnd.SetPoint(0, 0);
}
void CMDistance::BackUpObj(CMDistance &rt)
{
	rt.m_nStep = this->m_nStep;
	rt.m_pointStart = this->m_pointStart;
	rt.m_pointEnd = this->m_pointEnd;
	for(unsigned int i=0;i<m_result.size();i++)
		rt.m_result.at(i) = this->m_result.at(i);
}
CMDistance::~CMDistance()
{
	m_result.clear();
}

float CMDistance::GetDistance() const
{
	return m_computer.GetDistance(m_pointStart, m_pointEnd);
}


float CMDistance::ReturnGetDistanceInPixes()
{	
	return m_computer.GetDistanceInPixes(m_pointEnd, m_pointStart);
}

void CMDistance::DrawObject(CDC *dc,int nIndex)
{
	if(m_nStep<1) return;
	//dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(m_TextColor);
	//DrawNumber(dc,nIndex,CPoint(m_pointStart.x,m_pointStart.y));	
	float dx=0,dy=0;
	int nPointCount=0;
	float dotDis = 10.0f;
	// 水平线
	if(m_pointStart.y == m_pointEnd.y) 
	{
		//区分正负值
		dx = (m_pointEnd.x>m_pointStart.x) ? dotDis : -dotDis;
		dy = 0.0; 		
	}
	//  垂直线
	else if(m_pointStart.x == m_pointEnd.x)
	{
		dx = 0.0;
		//区分正负值
		dy = (m_pointEnd.y>m_pointStart.y) ? dotDis : -dotDis;	
	}
	//其他角度线
	else
	{	
		float angle;
		angle = (float)atan(float(m_pointEnd.y-m_pointStart.y)/(m_pointEnd.x-m_pointStart.x));
		if(m_pointStart.x > m_pointEnd.x) 	angle = 3.1415926f + angle;
		dx = (float)(dotDis*cos(angle));
		dy = (float)(dotDis*sin(angle));			
	}
	//计算该画的点数
	nPointCount = (int)(this->m_computer.GetDistanceInPixes(m_pointEnd,m_pointStart)/dotDis);
	CPen pen(PS_SOLID, 1, m_TextColor);
	CPen *oldpen = dc->SelectObject(&pen);
// 	//起末点图标
// 	HICON hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_MD_DOT));
	if(m_nStep > 0)
	{
		DrawCrossFlag(dc, m_pointStart.x, m_pointStart.y);
	}
		//DrawIconEx(dc->m_hDC, m_pointStart.x-7, m_pointStart.y-7, hIcon, 32, 32, 0, NULL, DI_NORMAL);
 	if(m_nStep == 2)
	{
		DrawCrossFlag(dc, m_pointEnd.x, m_pointEnd.y);
		//DrawIconEx(dc->m_hDC, m_pointEnd.x-7, m_pointEnd.y-7, hIcon, 32, 32, 0, NULL, DI_NORMAL);
	}
	//描点
	int px, py;
	COLORREF crDot = m_TextColor;
	for(int j=1; j<=nPointCount; j++)
	{	
		px = (int)(dx*j+0.5);
		py = (int)(dy*j+0.5);
		//描点,中心点,上,下,左,右5个点
		dc->SetPixel(m_pointStart.x+px,	 m_pointStart.y+py,   crDot);
		dc->SetPixel(m_pointStart.x+px,	 m_pointStart.y+py+1, crDot);
		dc->SetPixel(m_pointStart.x+px,	 m_pointStart.y+py-1, crDot);
		dc->SetPixel(m_pointStart.x+px+1,m_pointStart.y+py,   crDot);
		dc->SetPixel(m_pointStart.x+px-1,m_pointStart.y+py,   crDot);
	}

	dc->SelectObject(oldpen);
}


BOOL CMDistance::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_nStep == 0)//点第一下,确定开始点
	{
		m_pointStart = point;
		m_pointEnd = point;
		m_nStep=1;	
		return TRUE;
	}
	else if(m_nStep==1)//点第二下,确定结束点
	{
		//计算两点间距离				
		m_pointEnd = point;
		m_nStep = 2;
		return TRUE;
	}
	
	return FALSE;
}
BOOL CMDistance::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep ==1)
	{
		//m_pointEnd = point;		
		return TRUE;
	}
	return FALSE;
}
bool CMDistance::HasEnded()
{	
	return m_nStep==2;
}

CMeasureObject *CMDistance::Clone()
{
	CMDistance *pDis = new CMDistance(m_computer);
	pDis->m_nStep = this->m_nStep;
	pDis->m_pointStart = this->m_pointStart;
	pDis->m_pointEnd = this->m_pointEnd;
	for(unsigned int i=0;i<m_result.size();i++)
		pDis->m_result.at(i)=this->m_result.at(i);

	return pDis;
}

double CMDistance::GetSlope()const
{
	return m_computer.GetSlope(m_pointStart, m_pointEnd);
}


double CMDistance::GetLine()const
{
	if ((POINTNULL == m_pointStart) || (POINTNULL == m_pointEnd)) return 0;
	double cx = abs(m_pointStart.x - m_pointEnd.x);
	double cy = abs(m_pointStart.y - m_pointEnd.y);
	double d = _hypot(cx, cy);//计算3角形第3边长
	return m_computer.GetDistance(float(d));//返回cm
}

void CMDistance::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));	
	CString strResult;
	//float disInpixel = m_computer.GetDistanceInPixes(m_pointEnd, m_pointStart);
	if( m_nStep < 1)
		strResult.Format(_T("D: - - - - - - - -"));
	else
		strResult.Format(_T("D: %8.2f cm"),m_computer.GetDistance(m_pointStart, m_pointEnd));	
	dc->TextOut(x,y,strResult);
	y += szLine.cy;
}
void CMDistance::DrawResult(CDC *dc)
{
	CString strResult;
	strResult.Format(_T("%8.2f mm"),m_computer.GetDistance(m_pointStart, m_pointEnd)*10);//MM
	DrawResultText(dc,strResult,CPoint(m_pointStart.x,m_pointStart.y));
}
bool CMDistance::GetResultArray(vector<double> &lstResult)const
{
	lstResult.clear();
	lstResult.push_back(m_computer.GetDistance(m_pointStart, m_pointEnd));
	return true;
}

bool CMDistance::SetResultValue(vector<CString> strResult)
{
	if( strResult.empty() )return false;
	if ( !m_result.empty() )m_result.clear();
	for (int i=0; i<strResult.size(); i++)
	{
		m_result.push_back(strResult.at(i));
	}
	return true;
}

bool CMDistance::GetResultValue(vector<CString> &strResult)const
{
	if( !strResult.empty() )strResult.clear();
	if ( m_result.empty() )return false;
	for (int i=0; i<m_result.size(); i++)
	{
		strResult.push_back(m_result.at(i));
	}
	return true;
}

void CMDistance::Restart()
{
	m_pointStart.SetPoint(0,0);
	m_pointEnd.SetPoint(0,0);
	m_nStep = 0;
	m_result.clear();
}