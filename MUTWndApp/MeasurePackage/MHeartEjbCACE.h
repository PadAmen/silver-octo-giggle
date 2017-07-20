/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartEjbCACE.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartEjbCACE
file ext:	h
author:		li

purpose:	�����CA/CE
*********************************************************************/

//���������Ľ�


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