/************************************************************************/
/* 绘制羊水指数                                                      */
/************************************************************************/


#pragma once


#include "MeasureObject.h"
//显示第一条测量长度
class MEASUREPACKAGE_API CMDistanceYszs : public CMeasureObject  
{
public:
	CMDistanceYszs(const CComputeMethod &computer);
	virtual ~CMDistanceYszs();
private:	
	CMDistance m_Distance1;//4个测量距离的对象
	CMDistance m_Distance2;//4个测量距离的对象
	CMDistance m_Distance3;//4个测量距离的对象
	CMDistance m_Distance4;//4个测量距离的对象
public:
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual void Restart();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 5;};//最终测量结果值的个数
	virtual bool GetResultArray(vector<double> &lstResult)const;
private:
	vector<CString> m_result;
};