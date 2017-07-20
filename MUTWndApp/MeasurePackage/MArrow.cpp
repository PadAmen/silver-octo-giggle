#include "stdafx.h"
#include <math.h>
#include "MArrow.h"

#define	 ARROW_LENGTH	80			//固定箭头长度
#define  PI				3.1416

CMArrow::CMArrow(const CComputeMethod &computer)
:CMeasureObject(computer)
{
	m_nStep = 0;
}

CMArrow::~CMArrow(void)
{

}
CMeasureObject *CMArrow::Clone()
{
	CMArrow *pArr = new CMArrow(m_computer);
	pArr->m_nStep = this->m_nStep;
	pArr->m_pointStart = this->m_pointStart;
	pArr->m_pointEnd = this->m_pointEnd;

	return pArr;
}
BOOL CMArrow::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(0 == m_nStep)
	{
		m_nStep = 1;
		m_pointStart = point;
		m_pointMove = point;
		CPoint temp(-ARROW_LENGTH/2,ARROW_LENGTH/2);		//初始45度夹角
		m_pointEnd = m_pointStart + temp;
		//m_pointEnd = point;
		return TRUE;
	}
	else if(1 == m_nStep)
	{
		m_nStep = 2;
		m_pointMove = point;
		return TRUE;
	}
	else if(2 == m_nStep)
	{
		m_nStep = 3;
	}
	return FALSE;
}
BOOL CMArrow::OnMouseMove(UINT nFlags, CPoint point)
{
	if(2 == m_nStep)
	{
		//m_pointMove = point;
// 		CPoint offset = point - m_pointStart;
// 		if((offset.x>0&&offset.y>0)||(offset.x < 0&&offset.y>0))		//逆时针旋转
// 		{
// 			//CPoint temp(ARROW_LENGTH*cos(fd),-ARROW_LENGTH*sin(fd));
// 			m_pointStart.x = m_pointStart.x*cos(fd) - m_pointStart.y*sin(fd);
// 			m_pointStart.y = m_pointStart.x*sin(fd) + m_pointStart.y*cos(fd);
// 			//m_pointStart.x = ARROW_LENGTH*cos(fd+45);
// 			//m_pointStart.y = ARROW_LENGTH*sin(fd+45); 
// 		}
// 		else if((offset.x<=0&&offset.y<=0)||(offset.x>=0&&offset.y<=0))  //顺时针旋转
// 		{
// 			m_pointStart.x = m_pointStart.x*cos(fd) + m_pointStart.y*sin(fd);
// 			m_pointStart.y = -m_pointStart.x*sin(fd) + m_pointStart.y*cos(fd);
// 		}

		return TRUE;
	}
	return FALSE;
}

void CMArrow::Restart()
{
	m_pointStart.SetPoint(0,0);
	m_pointEnd.SetPoint(0,0);
	m_nStep = 0;

}
bool CMArrow::HasEnded()
{	
	return m_nStep==3;
}
void CMArrow::DrawObject(CDC *dc, int nIndex)
{
	COLORREF cr;	
	cr = (HasEnded())?m_TextColor:RGB(255,193,37);

	if(m_nStep < 1) return;
	CPen pen(PS_SOLID,1,cr);//橙色
	//CPen *old = dc->SelectObject(&pen);
	//DrawArrow(dc,m_pointStart,m_pointEnd);
	DrawRArrow(dc,m_pointStart,m_pointEnd,45.0,ARROW_LENGTH);
	if(m_nStep < 2) return;
// 	float cos_angle = m_computer.Get1Angle(m_pointStart,m_pointEnd,m_pointMove);
// 	float fd = (acos(cos_angle) * 180);//0~180度范围
// 	//m_angle =  fd / PI;			//返回角度
// 	double Px,Py,P1x,P1y,P2x,P2y;
// 	//以P2为原点得到向量P2P1（P）
// 	Px=m_pointStart.x-m_pointEnd.x;
// 	Py=m_pointStart.y-m_pointEnd.y;
// 	//向量P旋转theta角得到向量P1
// 	CPoint offset = m_pointMove - m_pointEnd;
// 	CPoint start = m_pointStart - m_pointEnd;
// 	CPoint temp = offset -start;
// 	if((temp.x >= 0&&temp.y >= 0)||(temp.x <= 0&&temp.y >= 0))
// 	{
// 		P1x=Px*cos(fd)-Py*sin(fd);
// 		P1y=Px*sin(fd)+Py*cos(fd);
// 	}
// 	else if((temp.x <0&&temp.y<0)||(temp.x > 0&&temp.y < 0))
// 	{
// 		P1x=Px*cos(-fd)-Py*sin(-fd);
// 		P1y=Px*sin(-fd)+Py*cos(-fd);
// 	}
// 
// 	//伸缩向量至制定长度
// 	double x1;
// 	x1=sqrt(P1x*P1x+P1y*P1y);
// 	P1x=P1x*ARROW_LENGTH/x1;
// 	P1y=P1y*ARROW_LENGTH/x1;
// 
// 	P1x=P1x+m_pointEnd.x;
// 	P1y=P1y+m_pointEnd.y;
// 
// 	P1x += 0.5;
// 	P1y += 0.5;
// 	m_pointStart.SetPoint(P1x,P1y);
// 	int lstart = sqrt(start.x*start.x + start.y*start.y);
 	//CPoint temp = m_pointMove - m_pointEnd;
	double tx = 0,ty = 0;
	tx = m_pointMove.x - m_pointEnd.x;
	ty = m_pointMove.y - m_pointEnd.y;

	double lofset = sqrt(tx*tx + ty*ty);
	double p1x,p1y;
	p1x = m_pointMove.x*ARROW_LENGTH/lofset;
	p1y = m_pointMove.y*ARROW_LENGTH/lofset;

// 	p1x=p1x+m_pointEnd.x;
// 	p1y=p1y+m_pointEnd.y;

	p1x += 0.5;
	p1y += 0.5;

	m_pointStart.SetPoint(p1x,p1y);

	pen.DeleteObject();
}
void CMArrow::DrawArrow(CDC *dc,POINT startPoint, POINT endPoint)
{
	if(m_nStep < 1) return;

	dc->MoveTo(startPoint);
	dc->LineTo(endPoint);

	//double PI = 3.1415926;
	double t=PI/4; //箭头与直线夹角
	double l=0.3; //箭头边长度占直线长度的百分比

	POINT arrowPoint;
	

	arrowPoint.x = (int)(l*((startPoint.x-endPoint.x)*cos(t)-(startPoint.y-endPoint.y)*sin(t)+0.5)+endPoint.x);
	arrowPoint.y = (int)(l*((startPoint.x-endPoint.x)*sin(t)+(startPoint.y-endPoint.y)*cos(t)+0.5)+endPoint.y);
	dc->MoveTo(endPoint);
	dc->LineTo(arrowPoint);

	arrowPoint.x = (int)(l*((startPoint.x-endPoint.x)*cos(-t)-(startPoint.y-endPoint.y)*sin(-t)+0.5)+endPoint.x);
	arrowPoint.y = (int)(l*((startPoint.x-endPoint.x)*sin(-t)+(startPoint.y-endPoint.y)*cos(-t)+0.5)+endPoint.y);
	dc->MoveTo(endPoint);
	dc->LineTo(arrowPoint);	

}
void CMArrow::DrawRArrow(CDC *dc,CPoint p1,CPoint p2,double theta,int length)
{
	theta=3.1415926*theta/180;//转换为弧度
	double ratio=0.3; //箭头边长度占直线长度的百分比
	double len = ratio*length; //箭头边长度

	double Px,Py,P1x,P1y,P2x,P2y;
	//以P2为原点得到向量P2P1（P）
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//向量P旋转theta角得到向量P1
	P1x=Px*cos(theta)-Py*sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//伸缩向量至制定长度
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*len/x1;
	P1y=P1y*len/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*len/x2;
	P2y=P2y*len/x2;
	//平移变量到直线的末端
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;

	P1x += 0.5;
	P1y += 0.5;
	P2x += 0.5;
	P2y += 0.5;
	//Graphics g(hdc);
	//GraphicsPath hPath;
	//Pen pen(Color(255,0,0,0),4);
	//hPath.AddLine(Point(p2.x,p2.y),Point(P1x,P1y));
	//hPath.AddLine(Point(P1x,P1y),Point(P2x,P2y));
	//hPath.AddLine(Point(P2x,P2y),Point(p2.x,p2.y));
	//CustomLineCap myCap(&hPath，NULL);
	//pen.SetCustomStartCap(&myCap);
	//pen.SetCustomEndCap(&myCap);
	//g.DrawLine(&pen,100,100,500,100);

	//CClientDC dc(this);//获取客户窗口DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 125, 0));
	pen1.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldpen=dc->SelectObject(&pen);
	dc->MoveTo(p1.x,p1.y);
	dc->LineTo(p2.x,p2.y);
	dc->SelectObject(&pen1);
	dc->MoveTo(p2.x,p2.y);
	dc->LineTo(P1x,P1y);
	dc->MoveTo(p2.x,p2.y);
	dc->LineTo(P2x,P2y);
// 	dc->MoveTo(P1x,P1y);
// 	dc->LineTo(P2x,P2y);
	dc->SelectObject(oldpen);
}
