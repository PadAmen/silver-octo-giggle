
#pragma once


#include "MeasureObject.h"
#include "MElArea.h"
/*
��һ����Բ����� v = pi/6*A*B*B (AΪ��Բ����,bΪ��Բ����)
*/
class  MEASUREPACKAGE_API CMVolumeEl : public CMeasureObject  
{
public:
	CMVolumeEl(const CComputeMethod &computer);
	virtual ~CMVolumeEl();
private:
	CMElArea m_ElArea;
public :
	virtual CMeasureObject*Clone();
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual void Restart();
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount();
};
