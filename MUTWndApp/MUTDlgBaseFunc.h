#pragma once
#include "MUTGlobal.h"
class CMUTDlgBaseFunc
{
public:
	CMUTDlgBaseFunc(void);
	~CMUTDlgBaseFunc(void);

	virtual BOOL	InitComRect();
	virtual BOOL	InitComStyle();
	//virtual CRect	GetImageRect()=0;

private:
	CRect m_AppWndRect;
	COLORREF m_bkColor;
	COLORREF m_textColor;
	HBRUSH	m_hbrush;
public:
	BOOL GetAppWndRect(LPRECT lprct);
	virtual void SetWndColor(COLORREF bkColor = RGB(0,0,0),COLORREF textColor=RGB(250,250,250));
	HBRUSH GetWndBkHBrush(){ return m_hbrush;};
	COLORREF GetWndTextColor(){return m_textColor;};
	COLORREF GetWndBkColor(){return m_bkColor;};

};
