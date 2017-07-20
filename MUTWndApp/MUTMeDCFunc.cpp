// MemDC.cpp
//

#include "stdafx.h"
#include "MUTMeDCFunc.h"

CMUTMeDCFunc::CMUTMeDCFunc(CDC* pDC, const CRect& Rect, COLORREF clBack)
{
	ASSERT(pDC != NULL);
	m_pDC = pDC;

	if (Rect.IsRectEmpty())
		m_pDC->GetClipBox(&m_Rect);
	else
		m_Rect.CopyRect(&Rect);

	if (CreateCompatibleDC(m_pDC))
	{
#ifndef _WIN32_WCE
		SetMapMode(m_pDC->GetMapMode());
#endif
		m_Bitmap.CreateCompatibleBitmap(m_pDC, m_Rect.Width(), m_Rect.Height());
		m_hOldBitmap = (HBITMAP)SelectObject(&m_Bitmap)->GetSafeHandle();

		if (clBack != -1)
		{
			CRect Rc(m_Rect);
			Rc.left = 0;
			Rc.right -= m_Rect.left;
			Rc.top = 0;
			Rc.bottom -= m_Rect.top;
			FillSolidRect(Rc, clBack);
		}

		m_bValid = TRUE;

		HRGN hRgn = ::CreateRectRgnIndirect(&m_Rect);
		::SelectClipRgn(m_pDC->m_hDC, hRgn);
		DeleteObject(hRgn);
	}
	else
	{
		m_bValid = FALSE;
		m_hOldBitmap = NULL;
	}
}

CMUTMeDCFunc::~CMUTMeDCFunc()
{
// 	if (m_bValid)
// 	{
// 		m_bValid = FALSE;
// 		m_pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), this, 0, 0, SRCCOPY);
// 		::SelectClipRgn(m_pDC->m_hDC, NULL);
// 	}

	if (m_hOldBitmap != NULL)
	{
		SelectObject(m_hOldBitmap);
		m_Bitmap.DeleteObject();
	}

	DeleteDC();
}

CBitmap& CMUTMeDCFunc::GetBitmap()
{
	return m_Bitmap;
}

void CMUTMeDCFunc::Discard()
{
	m_bValid = FALSE;
}

void CMUTMeDCFunc::FromDC()
{
	BitBlt(0, 0, m_Rect.Width(), m_Rect.Height(), m_pDC, m_Rect.left, m_Rect.top, SRCCOPY);            
}
void CMUTMeDCFunc::ExeDC()
{
	if (m_bValid)
	{
		m_bValid = FALSE;
		m_pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), this, 0, 0, SRCCOPY);
		::SelectClipRgn(m_pDC->m_hDC, NULL);
	}
}
