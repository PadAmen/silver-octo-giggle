
#pragma once

#include "MeasureObject.h"
#include "MDistance.h"
/*
L,W 显示两条直线的长度，测宽和高
*/
class MEASUREPACKAGE_API CMTwoDistance : public CMeasureObject  
{
public:
	CMTwoDistance(const CComputeMethod &computer);
	virtual ~CMTwoDistance();
private:
	CMDistance	m_Distance1;
	CMDistance	m_Distance2;
	CString		strPercent;	
public :
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();

	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount();//最终测量结果值的个数
	virtual bool GetResultArray(vector<double> &lstResult)const;
protected:

};