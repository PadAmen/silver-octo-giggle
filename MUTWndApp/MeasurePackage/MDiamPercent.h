
#pragma once

#include "MeasureObject.h"
#include "MDistance.h"
/*
abs(d1-d2)/d1
*/
class MEASUREPACKAGE_API CMDiamPercent : public CMeasureObject  
{
public:
	CMDiamPercent(const CComputeMethod &computer);
	virtual ~CMDiamPercent();
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
	virtual bool HasStarted();
	virtual void Restart();

	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount();//最终测量结果值的个数
protected:

};


