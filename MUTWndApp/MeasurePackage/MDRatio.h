
#pragma once


#include "MeasureObject.h"
#include "MDistance.h"
/*
�󳤶ȱ�d1/d2*100%
*/
class  MEASUREPACKAGE_API CMDRatio : public CMeasureObject  
{
public:
	CMDRatio(const CComputeMethod &computer);
	virtual ~CMDRatio();
private:
	CMDistance m_Distance1;
	CMDistance m_Distance2;
	float	m_fRatio;
	CString strRatio;		//�ٷֱ�d1/d2*100%
public :
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual int GetResultCount();

	virtual void DrawResult(CDC *dc,int &x,int &y);
protected:
	void DrawLine(CDC *dc,const CPoint &m_pointStart,const CPoint &m_pointEnd);

};
