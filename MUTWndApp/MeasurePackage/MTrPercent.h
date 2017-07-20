
#pragma once


#include "MeasureObject.h"
#include "MTrArea.h"
/*
求描线面积比d1/d2
*/
class MEASUREPACKAGE_API CMTrPercent : public CMeasureObject  
{
public:
	CMTrPercent(const CComputeMethod &computer);
	virtual ~CMTrPercent();
private:
	CMTrArea m_TrArea1;
	CMTrArea m_TrArea2;
	
public :
	virtual CMeasureObject *Clone();
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount();//最终测量结果值的个数
};
