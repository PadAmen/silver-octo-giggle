
/********************************************************************
created:	2010/07/17
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\HeartLHWeight.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MHeartLHWeight
file ext:	h
author:		li

purpose:	���������ļ�����
*********************************************************************/

//�������Ľ�

#pragma once

#include "MeasureObject.h"
#include "MeasurePackage.h"

class MEASUREPACKAGE_API CHeartLHWeight:public CMeasureObject
{
public:
	CHeartLHWeight(const CComputeMethod &computer);
	virtual ~CHeartLHWeight();
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
	double GetLVMW()const;					//�ļ�����	
	double GetLVMWI()const;					//����ָ��
protected:
	CMDistance m_Distance1;
	CMDistance m_Distance2;
	CMDistance m_Distance3;
};
