/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartEjbCACXjsd.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartEjbCACXjsd
file ext:	h
author:		li

purpose:	�����AC�½��ٶ�
*********************************************************************/

//���������Ľ�

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartEjbACxjsd:public CHeartSBTime
{
public:
	CHeartEjbACxjsd(const CComputeMethod &computer);
	virtual ~CHeartEjbACxjsd();
public:
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual CMeasureObject *Clone();
};

