
#pragma once

#include "MeasureObject.h"
/*
描线长度
*/
class MEASUREPACKAGE_API CMTrLength : public CMeasureObject  
{
public:
	CMTrLength(const CComputeMethod &computer);
	virtual ~CMTrLength();
private:
	CArray<CPoint,CPoint>	m_ArrPoint;//点数组
	float		m_fTrLengthInPix;//长度
 
public :
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual void Restart();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual CMeasureObject *Clone();
};
