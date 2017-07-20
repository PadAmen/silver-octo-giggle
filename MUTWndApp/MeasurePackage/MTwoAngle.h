/********************************************************************
created:	2010/07/16
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MTwoAngle.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MTwoAngle
file ext:	h
author:		li

purpose:	测量双角度
*********************************************************************/

#pragma once

#include "MeasureObject.h"
#include "MTwoAngle.h"

class MEASUREPACKAGE_API CMTwoAngle : public CMAngle
{
public:
	CMTwoAngle(const CComputeMethod &computer);
	virtual ~CMTwoAngle();
protected:
	CPoint m_pointEndEnd;		//第四个点
	CPoint last_point;
	float m_angle1;
	float m_angle2;
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount(){return 2;};
};
