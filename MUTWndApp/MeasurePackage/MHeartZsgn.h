/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MHeartZsgn.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartZsgn
file ext:	h
author:		li

purpose:	左室功能,
*********************************************************************/

//输出结果待改进

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"


class MEASUREPACKAGE_API CHeartZsgn:public CMeasureObject
{
public:
	CHeartZsgn(const CComputeMethod &computer);
	virtual ~CHeartZsgn();
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
	void GetTeichholz(CUBE_TEICHHOLZT& ct);
protected:
	CMDistance m_Distance1;
	CMDistance m_Distance2;
	CUBE_TEICHHOLZT ct;
};