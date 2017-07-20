
#pragma once

#include "MeasureObject.h"

//距离测量
class  MEASUREPACKAGE_API CMPWHeartRatio : public CMeasureObject  
{
public:
	CMPWHeartRatio(const CComputeMethod &computer);
	virtual ~CMPWHeartRatio();
public:			//给继承类使用
	float GetDistance() const;//返回测量长度
	float ReturnGetDistanceInPixes();
public:
	double GetSlope()const;			//(M)得到斜率
	double GetLine()const;			//心率直线长
	double GetPWHeartRate(CPoint ptStart, CPoint ptEnd)const;
public:
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void Restart();
	virtual int  GetResultCount();//最终测量结果值的个数

public:	//产科
	virtual bool SetResultValue(vector<CString> strResult);
	virtual bool GetResultValue(vector<CString> &strResult)const;
protected:
	CPoint m_pointStart;//开始点
	CPoint m_pointEnd;	//结束点
private:
	vector<CString> m_result;		//存放产科的测量结果
};
