
#pragma once


#include "MeasureObject.h"
#include "MDistance.h"
/*
三条直线求体积 v = pi/6 *a*b*m (m为第3轴长度)，结果只显示体积
*/
class MEASUREPACKAGE_API CMVolumeTD : public CMeasureObject  
{
public:
	CMVolumeTD(const CComputeMethod &computer);
	virtual ~CMVolumeTD();
private:	
	CMDistance m_Distance1;//3个测量距离的对象
	CMDistance m_Distance2;//3个测量距离的对象
	CMDistance m_Distance3;//3个测量距离的对象
public:
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount(){return 1;};//最终测量结果值的个数
	virtual bool GetResultArray(vector<double> &lstResult)const;

};