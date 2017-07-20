
#pragma once


#include "MeasureObject.h"
#include "MDistance.h"
#include "MTrArea.h"
/*
用一个描线面积和一条直线求体积
*/
class MEASUREPACKAGE_API CMVolumeTr : public CMeasureObject  
{
public:
	CMVolumeTr(const CComputeMethod &computer);
	virtual ~CMVolumeTr();
private:
	CMTrArea m_TrArea;
	CMDistance m_Distance;

public:
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 3;};
};

