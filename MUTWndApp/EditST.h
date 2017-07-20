#pragma once
#include "afxwin.h"
#include "MUTGlobal.h"

class CEditST :
	public CEdit
{
public:
	CEditST(void);
	~CEditST(void);
private:
	CFont	EditFont;
	COLORREF  m_OutColor;
	COLORREF  m_SelectColor;
	BOOL	m_bSetFont;
	UINT	m_uHeight;
public:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//LRESULT OnCrateEdit(WPARAM wParam,LPARAM lParam);
	LRESULT OnSetStyle(WPARAM wParam,LPARAM lParam);
	afx_msg void CtlColor(CDC* pDC, UINT nCtlColor);
	void	SetBorder(UINT height=4){ m_uHeight = height;};
	void	SetColor(COLORREF colorOut = RGB(0,0,0),COLORREF colorSel=RGB(125,0,0))
	{
		m_OutColor = colorOut;
		m_SelectColor = colorSel;
	};
	DECLARE_MESSAGE_MAP()

};
