
#pragma once

#include "MeasureObject.h"
/*
���߳���
*/
class MEASUREPACKAGE_API CMTrLength : public CMeasureObject  
{
public:
	CMTrLength(const CComputeMethod &computer);
	virtual ~CMTrLength();
private:
	CArray<CPoint,CPoint>	m_ArrPoint;//������
	float		m_fTrLengthInPix;//����
 
public :
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual void Restart();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual CMeasureObject *Clone();
};
