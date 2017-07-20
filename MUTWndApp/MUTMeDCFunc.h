
#pragma once

class CMUTMeDCFunc : public CDC  
{
public:
    CMUTMeDCFunc(CDC* pDC, const CRect& Rect, COLORREF clBack = -1);
    virtual ~CMUTMeDCFunc();

	void Discard();

	void FromDC();

	void ExeDC();

	CBitmap& GetBitmap();

protected:
	CDC* m_pDC;
	CRect m_Rect;
	CBitmap m_Bitmap;
	HBITMAP m_hOldBitmap;
	BOOL m_bValid;
};

