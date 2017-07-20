#include "stdafx.h"
#include "MutBitmap.h"


CMutBitmap::CMutBitmap()
{
	m_pPalette = NULL;
}

CMutBitmap::~CMutBitmap()
{
	if (m_pPalette)
	{
		delete m_pPalette;
	}
}

void CMutBitmap::LoadBitmapEx(UINT nID, BOOL bTransparent)
{
	// can only load once
	ASSERT(!m_pPalette);

	CDC dcScreen;
	dcScreen.Attach(::GetDC(NULL));

	// find and lock bitmap resource
	HRSRC hRsrc = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nID), RT_BITMAP);
	HGLOBAL hglb = LoadResource(AfxGetResourceHandle(), hRsrc);
	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);

	// get pointers into bitmap structures (header, color table and picture bits)
	LPBITMAPINFO pBitmapInfo = (LPBITMAPINFO)lpBitmap;
	LPBITMAPINFOHEADER pBitmapInfoHeader = (LPBITMAPINFOHEADER)lpBitmap;
	// if the picture data uses more then 8 bits per pixel, there's
	// no color table to turn into a palette
	int nNumberOfColors = 0;
	if (lpBitmap->biClrUsed)
		nNumberOfColors = lpBitmap->biClrUsed;
	else if (pBitmapInfoHeader->biBitCount <= 8)
		nNumberOfColors = (1 << pBitmapInfoHeader->biBitCount);
	LPBYTE pBitmapPictureData = (LPBYTE)lpBitmap + lpBitmap->biSize +
		(nNumberOfColors*sizeof(RGBQUAD));

	// get width and height
	m_Width = lpBitmap->biWidth;
	m_Height = lpBitmap->biHeight;

	// create a logical palette from the color table in this bitmap 
	if (nNumberOfColors)
	{
		LOGPALETTE *pLogPal = (LOGPALETTE *)new BYTE[
			sizeof(LOGPALETTE) + (nNumberOfColors * sizeof(PALETTEENTRY))];
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = nNumberOfColors;

		for (int i = 0; i < nNumberOfColors; i++)
		{
			// if flag set, replace grey color with window's background color
			if (bTransparent &&
				pBitmapInfo->bmiColors[i].rgbRed == 192 &&
				pBitmapInfo->bmiColors[i].rgbGreen == 192 &&
				pBitmapInfo->bmiColors[i].rgbBlue == 192)
			{
				pBitmapInfo->bmiColors[i].rgbRed = GetRValue(::GetSysColor(COLOR_BTNFACE));
				pBitmapInfo->bmiColors[i].rgbGreen = GetGValue(::GetSysColor(COLOR_BTNFACE));
				pBitmapInfo->bmiColors[i].rgbBlue = GetBValue(::GetSysColor(COLOR_BTNFACE));
			}
			pLogPal->palPalEntry[i].peRed = pBitmapInfo->bmiColors[i].rgbRed;
			pLogPal->palPalEntry[i].peGreen = pBitmapInfo->bmiColors[i].rgbGreen;
			pLogPal->palPalEntry[i].peBlue = pBitmapInfo->bmiColors[i].rgbBlue;
			pLogPal->palPalEntry[i].peFlags = 0;
		}
		m_pPalette = new CPalette;
		m_pPalette->CreatePalette(pLogPal);
		delete[]pLogPal;
		dcScreen.SelectPalette(m_pPalette, TRUE);
		dcScreen.RealizePalette();
	}

	// create device dependant bitmap
	HBITMAP bitmap = ::CreateDIBitmap(dcScreen.m_hDC, pBitmapInfoHeader, CBM_INIT, pBitmapPictureData,
		pBitmapInfo, DIB_RGB_COLORS);

	// attach this new bitmap object to our CBitmap class
	Attach(bitmap);

	// release dc
	::ReleaseDC(NULL, dcScreen.Detach());
}

