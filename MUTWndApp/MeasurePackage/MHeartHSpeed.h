

/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartHSpeed.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartHSpeed
file ext:	h
author:		li

purpose:	测量心率
*********************************************************************/

//结果待改进

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartHSpeed:public CHeartSBTime
{
public:
	CHeartHSpeed(const CComputeMethod &computer);
	virtual ~CHeartHSpeed();
public:
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual bool GetResultArray(vector<double> &lstResult)const;
protected:
	double GetHeartRate(const CPoint m_pointStart,const CPoint m_pointEnd)const;
};
