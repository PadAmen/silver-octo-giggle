#pragma once
#include "measureobject.h"

class MEASUREPACKAGE_API CMText :public CMeasureObject
{
public:
	CMText(const CComputeMethod &computer);
	~CMText(void);
public:
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	//virtual bool GetResultArray(vector<double> &lstResult)const;
	//virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void DrawResult(CDC *dc,CString strResult);
	virtual void Restart();
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
private:
	COLORREF	m_TextColor;
	CPoint		m_pointStart;
	UINT		m_uWidth;
	UINT		m_uHeight;
	//CString		m_StrText;
public:
	virtual void SetEnded(){m_nStep = 2;};
};
