
/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartEjbBkll.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartEjbBkll
file ext:	h
author:		li

purpose:	二尖瓣瓣口流量
*********************************************************************/

//输出结果待改进

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartEjbBkll:public CHeartSBTime
{
public:
	CHeartEjbBkll(const CComputeMethod &computer);
	~CHeartEjbBkll();
protected:
	virtual CMeasureObject *Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int GetResultCount();
	virtual bool GetResultArray(vector<double> &lstResult) const;
};