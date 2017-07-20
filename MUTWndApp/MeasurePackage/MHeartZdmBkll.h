
/********************************************************************
created:	2010/07/18
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartZdmBkll.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartZdmBkll
file ext:	h
author:		li

purpose:	测量主动脉瓣口流量
*********************************************************************/

//参数待改进

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartZdmBkll:public CHeartLHWeight
{
public:
	CHeartZdmBkll(const CComputeMethod &computer);
	~CHeartZdmBkll();
public:
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual CMeasureObject* Clone();
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual int GetResultCount();
};