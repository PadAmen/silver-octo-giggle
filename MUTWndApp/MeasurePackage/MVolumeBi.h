
#pragma once


#include "MeasureObject.h"
#include "MDistance.h"
/*
三条直线求体积 v = pi/6 *a*b*m (m为第3轴长度)
*/
class MEASUREPACKAGE_API CMVolumeBi : public CMeasureObject  
{
public:
	CMVolumeBi(const CComputeMethod &computer);
	virtual ~CMVolumeBi();
public:
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 4;};//最终测量结果值的个数
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void Restart();
protected:
	float GetDistance1()const;	//得到3条直线的长度
	float GetDistance2()const;
	float GetDistance3()const;
	float GetAge()const;			//比例系数 P.PSA 0.125
private:	
	CMDistance m_Distance1;//3个测量距离的对象
	CMDistance m_Distance2;//3个测量距离的对象
	CMDistance m_Distance3;//3个测量距离的对象


};

