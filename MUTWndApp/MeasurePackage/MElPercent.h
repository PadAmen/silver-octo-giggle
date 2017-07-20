
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MeasureObject.h"
#include "MElArea.h"
/*
未注椭圆面积比(a1-a2)/a2
*/

class MEASUREPACKAGE_API CMElPercent : public CMeasureObject  
{
public:
	CMElPercent(const CComputeMethod &computer);
	virtual ~CMElPercent();
private:
	CMElArea m_AxArea1;//面积一
	CMElArea m_AxArea2;//面积二
public:	
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);	
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual CMeasureObject *Clone();
	virtual int   GetResultCount();//最终测量结果值的个数

};
