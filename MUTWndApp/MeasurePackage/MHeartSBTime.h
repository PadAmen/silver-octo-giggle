
/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartSBTime.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartSBTime
file ext:	h
author:		li

purpose:	测量射血时间
*********************************************************************/

//输出结果待改进

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartSBTime:public CMeasureObject
{
public:
	CHeartSBTime(const CComputeMethod &computer);
	~CHeartSBTime();
protected:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int GetResultCount();
	virtual bool GetResultArray(vector<double> &lstResult)const;
protected:
	float GetTime()const;
protected:
	CPoint m_pointStart;
	CPoint m_pointEnd;
};