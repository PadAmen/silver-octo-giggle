/************************************************************************/
/* 绘制息肉和结石                                                       */
/************************************************************************/


#pragma once


#include "MeasureObject.h"
//显示第一条测量长度
class MEASUREPACKAGE_API CMD3ToD1 : public CMeasureObject  
{
public:
	CMD3ToD1(const CComputeMethod &computer);
	virtual ~CMD3ToD1();
private:	
	CMDistance m_Distance1;//3个测量距离的对象
	CMDistance m_Distance2;//3个测量距离的对象
	CMDistance m_Distance3;//3个测量距离的对象
public:
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount(){return 1;};//最终测量结果值的个数	只需第一条直线
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void Restart();
};