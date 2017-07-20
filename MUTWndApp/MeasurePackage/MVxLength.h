

#pragma once


#include "MeasureObject.h"
/************************************************************************/
/* 连接线长度                                                                     */
/************************************************************************/
class MEASUREPACKAGE_API CMVxLength : public CMeasureObject  
{
private:
	CArray<CPoint,CPoint> m_pointArray;
	CPoint		m_pointMove;
public:
	CMVxLength(const CComputeMethod &);
	virtual ~CMVxLength();
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual CMeasureObject *Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);;

};
