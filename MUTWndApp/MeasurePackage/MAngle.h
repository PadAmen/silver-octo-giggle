
/********************************************************************
created:	2010/07/16
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MAngle.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MAngle
file ext:	h
author:		li

purpose:	测量两直线之间的夹角
*********************************************************************/

#pragma once

#include "MeasureObject.h"
#include "MDistance.h"

/*
*	测量直线角度,
*/


class MEASUREPACKAGE_API CMAngle : public CMeasureObject 
{
public:
	CMAngle(const CComputeMethod &computer);
	virtual ~CMAngle();
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual	void DrawResult(CDC *dc);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void Restart();
public:
	COLORREF	m_TextColor;
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
	float GetAngle();			//得到角度(非弧度,0~180)
	//得到直线和点的变化率 用于控制圆弧的角度范围
	void GetLineAndPointRatio(CPoint m_pointBtwStartToMid,CPoint &c_p,CPoint m_pointMiddle,//m_pointBtwStartToMid在起始两个点的直线上截距为fDisBtwLine的点,m_pointMiddle鼠标压下的第二个点
							  float fDisStarToMid,float fDisBtwLine,int ddx_MidToStart,// fDisStarToMid在第一条直线的截距,fDisBtwLine在第二条直线上的截距,ddx_MidToStart,ddy_MidToStart第一条直线的x,y的变化率
							  int ddy_MidToStart,CPoint m_pointVec);	//m_pointVec在与第一条直线垂直的垂线上的点
	//获取圆弧的画法
	void GetDrawCircle(int ddx_MidToStart,int ddy_MidToStart,
					   int ddx_MidToEnd,int ddy_MidToEnd,
					   float cos_an,int &draw_flag);
	//画角度
	void DrawAngle(CDC *dc,int nIndex,CPoint &m_pointStart,CPoint &m_pointMiddle,
				   CPoint &m_pointEnd,float fDisBtwLine,float &m_angle);
protected:
	CPoint m_pointStart;
	CPoint m_pointMiddle;
	CPoint m_pointEnd;
	CPoint m_pointLast;			
	float m_angle;

};
