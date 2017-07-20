#pragma once
#include "measureobject.h"

class MEASUREPACKAGE_API CMArrow :public CMeasureObject
{
public:
	CMArrow(const CComputeMethod &computer);
	~CMArrow(void);
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
	//virtual	void DrawResult(CDC *dc);
	//virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void Restart();
	
private:
	COLORREF	m_TextColor;
	CPoint m_pointStart;
	CPoint m_pointEnd;
	CPoint m_pointMove;
	float m_angle;
	//CPoint m_pointMove;
public:
	void DrawArrow(CDC *dc,POINT startPoint, POINT endPoint);
	void DrawRArrow(CDC *dc,CPoint p1,CPoint p2,double theta,int length);
	
};
