/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartEjbCACE.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartEjbCACE
file ext:	h
author:		li

purpose:	二尖瓣CA/CE
*********************************************************************/

//输出结果待改进


#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartEjbCACE:public CHeartZdmLADAOD
{
public:
	CHeartEjbCACE(const CComputeMethod &computer);
	~CHeartEjbCACE();
protected:
	virtual CMeasureObject* Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual bool GetResultArray(vector<double> &lstResult)const;
};