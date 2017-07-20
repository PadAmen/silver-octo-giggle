#include "StdAfx.h"
#include "EditST.h"

CEditST::CEditST(void)
:m_uHeight(4)
{
	m_bSetFont = TRUE;
	EditFont.CreatePointFont(APP_FONT_POINT1,APP_FONT_FACENAME1,NULL);//创建一个新的字体
	//this->SetFont(&EditFont);
}

CEditST::~CEditST(void)
{
	EditFont.DeleteObject();
}
BEGIN_MESSAGE_MAP(CEditST, CEdit)
	//ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

LRESULT CEditST::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

	return CEdit::DefWindowProc(message, wParam, lParam);
} // End of DefWindowProc
LRESULT CEditST::OnSetStyle(WPARAM wParam,LPARAM lParam)
{
	return DefWindowProc(EM_SETEDITSTYLE,wParam, lParam);
}

void CEditST::CtlColor(CDC* pDC, UINT nCtlColor)
{
	if(m_bSetFont)
	{
		m_bSetFont = FALSE;
		this->SetFont(&EditFont);
	}

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(APP_TEXT_COLOR1);

	CRect rct;
	this->GetRect(&rct);
	//CRect now;
	//this->GetWindowRect(&rct);
	//int  height = 4;
	CPen pen(PS_SOLID,m_uHeight,APP_BK_COLOR);
	CPen *oldpen = pDC->SelectObject(&pen);

	pDC->MoveTo(rct.left,rct.bottom+m_uHeight/2);
	pDC->LineTo(rct.left+REPORT_TEXT_WIDTH,rct.bottom+m_uHeight/2);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	
	//return (HBRUSH)::GetStockObject(NULL_BRUSH); 
}


