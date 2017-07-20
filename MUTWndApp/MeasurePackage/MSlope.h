
/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MSlope.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MSlope
file ext:	h
author:		li

purpose:	测量心率
*********************************************************************/

//结果待改进
#pragma once
#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CMSlope:public CMDistance
{
public:
	CMSlope(const CComputeMethod &computer);
	virtual ~CMSlope();
protected:
	virtual CMeasureObject* Clone();
	virtual int GetResultCount();
	virtual void DrawResult(CDC *dc,int &x,int &y);
};