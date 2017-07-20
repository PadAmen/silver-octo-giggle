// DIB.cpp
//
#include "stdafx.h"
#include "MUTGlobal.h"
#include "MUTDibFunc.h"
#include "Table.h"


#pragma warning (disable : 4244) // conversion from 'double' to 'unsigned char', possible loss of data

/////////////////////////////////////////////////////////////////////////////
// CDib
CMUTDibFunc::CMUTDibFunc()
{
	::ZeroMemory(&m_Head, sizeof(DIBINFO));
	m_pDib = NULL;
	m_ppLine = NULL;
	m_hBitmap = NULL;

	m_bModify = FALSE;

	m_bCheckColor = FALSE;
	m_nPseudoMode = PSEUDO_COMPRESS;
	m_nPseudoColor = PSEUDO_COLOR_0;
	m_nPos = 0;
	m_nPalRange = 255;
}

CMUTDibFunc::CMUTDibFunc(const CMUTDibFunc& Dib)
{
	::ZeroMemory(&m_Head, sizeof(DIBINFO));
	m_pDib = NULL;
	m_ppLine = NULL;
	m_hBitmap = NULL;

	m_bModify = FALSE;

	m_bCheckColor = FALSE;
	m_nPseudoMode = PSEUDO_COMPRESS;
	m_nPseudoColor = PSEUDO_COLOR_0;
	m_nPos = 0;
	m_nPalRange = 255;

	*this = Dib;
}

CMUTDibFunc::CMUTDibFunc(int nWidth, int nHeight, COLORREF rgb, int nPseudoColor, BOOL bCheckColor)
{
	::ZeroMemory(&m_Head, sizeof(DIBINFO));
	m_pDib = NULL;
	m_ppLine = NULL;
	m_hBitmap = NULL;

	m_bModify = FALSE;

	m_bCheckColor = bCheckColor;
	m_nPseudoMode = PSEUDO_COMPRESS;
	m_nPseudoColor = PSEUDO_COLOR_0;
	m_nPos = 0;
	m_nPalRange = 255;

	this->Create(nWidth, nHeight, rgb, nPseudoColor, bCheckColor);
}

CMUTDibFunc::~CMUTDibFunc()
{
	Empty();
}

void CMUTDibFunc::Empty()
{
	if (this != NULL)
	{
		CSingleLock lock(&m_cs, TRUE);
		if (m_ppLine != NULL) delete[] m_ppLine;
		if (m_hBitmap != NULL) ::DeleteObject(m_hBitmap);
		m_pDib = NULL;
		m_ppLine = NULL;
		m_hBitmap = NULL;
		::ZeroMemory(&m_Head, sizeof(DIBINFO));

		m_bCheckColor = FALSE;
		m_nPseudoMode = PSEUDO_COMPRESS;
		m_nPseudoColor = PSEUDO_COLOR_0;
		m_nPos = 0;
		m_nPalRange = 255;
		m_bModify = FALSE;
	}
}

CMUTDibFunc& CMUTDibFunc::operator=(const CMUTDibFunc & dib)
{
	if (this != &dib)
	{
		this->CopyDib(dib);
	}
	return *this;
}

// 该函数通过比较两个类的位图来判定它们是否具有相同的图像。
// 注：如果两个类都是空的(即都没有图像)，则该函数将视它们是不相同
BOOL CMUTDibFunc::operator==(CMUTDibFunc& Dib) const
{
	LONG len;

	// 如果两个类都是空的(即都没有图像)，则该函数将视它们是不相同
	if (Dib.IsEmpty() || this->IsEmpty())
		return FALSE;

	// 如果是与自身比较，则直接返回TRUE
	if (this == &Dib)
		return TRUE;

	// 伪彩色设置比较
	if (Dib.GetPseudoColor() != m_nPseudoColor)
		return FALSE;

	// 位图头比较
	len = sizeof(DIBINFO);
	LPBYTE pData1 = (LPBYTE)this->GetHead();
	LPBYTE pData2 = (LPBYTE)Dib.GetHead();
	while (len--)
	{ if (*pData1++ != *pData2++) return FALSE; }

	// 位图数据比较
	len = this->GetHead()->biSizeImage / 4;
	LPDWORD pBits1 = (LPDWORD)this->GetBits();
	LPDWORD pBits2 = (LPDWORD)Dib.GetBits();
	while (len--)
	{ if (*pBits1++ != *pBits2++) return FALSE; }

	return TRUE;
}

BOOL CMUTDibFunc::operator!=(CMUTDibFunc& Dib) const
{
	return (*this == Dib) ? FALSE : TRUE;
}

BOOL CMUTDibFunc::CopyDib(const CMUTDibFunc & dib)
{
	if (dib.IsEmpty())
	{
		this->Empty();
		return TRUE;
	}
	CSingleLock lock(&m_cs, TRUE);
	if (this->Create(dib.GetWidth(), dib.GetHeight(), 0, dib.m_nPseudoColor, dib.m_bCheckColor))
	{
		::CopyMemory(GetBits(), dib.GetBits(), dib.GetPitch() * dib.GetHeight());		
		return TRUE;
	}

	return FALSE;
}

// 交换位图
void CMUTDibFunc::Swap(CMUTDibFunc & dib)
{
	CMUTDibFunc tmp = *this;
	this->CopyDib(dib);
	dib.CopyDib(tmp);
}

// 建立DIB位图(pPal!=NULL,则复制伪彩信息到新建的dib中)
BOOL CMUTDibFunc::Create(int nWidth, int nHeight, COLORREF rgb, int nPseudoColor, BOOL bCheckColor)
{
	this->Empty();

	::ZeroMemory(&m_Head, sizeof(DIBINFO));
	m_Head.bih.biSize			= sizeof(BITMAPINFOHEADER);
	m_Head.bih.biWidth			= nWidth;
	m_Head.bih.biHeight			= nHeight;
	m_Head.bih.biPlanes			= 1;
	m_Head.bih.biBitCount		= 8;
	m_Head.bih.biCompression	= BI_RGB;
	if (nPseudoColor < PSEUDO_COLOR_0) nPseudoColor = PSEUDO_COLOR_0;
	if (nPseudoColor > PSEUDO_COLOR_44) nPseudoColor = PSEUDO_COLOR_44;
	if (nPseudoColor != PSEUDO_COLOR_44)
	{
		LPBYTE pPal = m_Head.pPal;
		for (int i=0; i<256; i++)
		{
			*pPal++ = MyPseudoColorsTable[nPseudoColor][i][2];
			*pPal++ = MyPseudoColorsTable[nPseudoColor][i][1];
			*pPal++ = MyPseudoColorsTable[nPseudoColor][i][0] * (bCheckColor ? 0.96 : 1);
			*pPal++ = MyPseudoColorsTable[nPseudoColor][i][3];
		}
	}
	else
	{
		// 实现灰度到彩色变换(类似PhotoShop)
		register BYTE R, G, B;
		LPBYTE pPal = m_Head.pPal;
		for (register int i=0; i<256; i++)
		{
			if (i <= 64)
			{
				R = 0;
				G = min(255, i << 2);
				B = 255;
			}
			else if (i>64 && i<=128)
			{
				R = 0;
				G = 255;
				B = (128 - i) << 2;
			}
			else if (i>128 && i<=192)
			{
				R = min(255, (i - 128)<<2);
				G = 255;
				B = 0;
			}
			else if (i>192 && i<=255)
			{
				R = 255;
				G = (255 - i) << 2;
				B = 0;
			}

			*pPal++ = B;
			*pPal++ = G;
			*pPal++ = R;
			*pPal++ = 0;
		}
	}
	m_bCheckColor = bCheckColor;
	m_nPseudoColor = nPseudoColor;
	CSingleLock lock(&m_cs, TRUE);
	m_hBitmap = ::CreateDIBSection(NULL, (LPBITMAPINFO)&m_Head, DIB_RGB_COLORS, (VOID**)&m_pDib, NULL, 0);
	if ((m_hBitmap == NULL) || (m_pDib == NULL))
	{
		this->Empty();
		return FALSE;
	}

	DIBSECTION ds;
	::GetObject(m_hBitmap, sizeof(DIBSECTION), &ds);
	CopyMemory(&m_Head.bih, &ds.dsBmih, sizeof(BITMAPINFOHEADER));

	m_ppLine = (LPBYTE*) new BYTE[sizeof(LPBYTE) * nHeight];
	for (int y=0; y<nHeight; y++)
	{
		m_ppLine[nHeight - 1 - y] = m_pDib + this->GetPitch() * y;
	}

	if (rgb)
	{
		::FillMemory(m_pDib, ds.dsBmih.biSizeImage, this->GetGrayscale(rgb));
	}

	return TRUE;
}

// 画线
void CMUTDibFunc::Line(POINT pt1, POINT pt2, COLORREF rgb, double step, LPRECT lpRectRegion) 
{
	this->Line(pt1.x, pt1.y, pt2.x, pt2.y, rgb, step, lpRectRegion);
}
void CMUTDibFunc::Line(int x1, int y1, int x2, int y2, COLORREF rgb, double step, LPRECT lpRectRegion) 
{
	if (this->IsEmpty()) return;
	CSingleLock lock(&m_cs, TRUE);
	CRect region;
	if (lpRectRegion == NULL)
		region = CRect(0, 0, m_Head.bih.biWidth, m_Head.bih.biHeight);
	else
	{
		region = CRect(lpRectRegion->left, lpRectRegion->top, lpRectRegion->right, lpRectRegion->bottom);
		region.IntersectRect(&region, CRect(0, 0, m_Head.bih.biWidth, m_Head.bih.biHeight));
	}

	BYTE color = this->GetGrayscale(rgb);

	if (y1 == y2)
	{
		if (x1 < region.left) x1 = region.left;
		if (x2 < region.left) x2 = region.left;
		if (x1 >= region.right) x1 = region.right - 1;
		if (x2 >= region.right) x2 = region.right - 1;

		if (y1 < 0) y1 = region.top;
		if (y1 >= region.bottom) y1 = region.bottom - 1;

		if (x1 < x2)
		{
			PBYTE pLine = this->GetLine(y1);
			for (double x=x1; x<=x2; x+=step)
			{
				pLine[(int)x] = color;
			}
		}
		else
		{
			PBYTE pLine = this->GetLine(y1);
			for (double x=x1; x>=x2; x-=step)
			{
				pLine[(int)x] = color;
			}
		}
	}
	else if (x1 == x2)
	{
		if (x1 < region.left) x1 = region.left;
		if (x1 >= region.right) x1 = region.right - 1;

		if (y1 < region.top) y1 = region.top;
		if (y2 < region.top) y2 = region.top;
		if (y1 >= region.bottom) y1 = region.bottom - 1;
		if (y2 >= region.bottom) y2 = region.bottom - 1;

		if (y1 < y2)
		{
			for (double y=y1; y<=y2; y+=step)
			{
				*(m_ppLine[(int)y] + x1) = color;
			}
		}
		else
		{
			double dy = y2;
			for (double y=y2; y<=y1; y+=step)
			{
				*(m_ppLine[(int)y] + x1) = color;
			}
		}
	}
	else
	{
		int dx = x2 - x1;
		int dy = y2 - y1;
		int stepx, stepy, change;

		// 从右向左画线
		if (dx < 0)
		{
			dx = -dx;
			stepx = -1;
		}
		// 从左向右画线
		else
		{
			stepx = 1;
		}

		// 从下向上画线
		if (dy < 0)
		{
			dy = -dy;
			stepy = -1;
		}
		// 从上向下画线
		else
		{
			stepy = 1;
		}

		// x改变得比y快
		if (dx > dy)
		{
			int dxy = step;

			change = dx >> 1;
			while (x1 != x2)
			{
				if (dxy >= step && x1 >= region.left && y1 >= region.top && x1 < region.right && y1 < region.bottom)
				{
					dxy = 0;
					*(m_ppLine[y1] + x1) = color;
				}

				x1 += stepx;
				change += dy;
				if (change > dx)
				{
					y1 += stepy;
					change -= dx;
				}

				dxy++;
			}
		}
		// y改变得比x快
		else
		{
			int dxy = step;

			change = dy >> 1;
			while (y1 != y2)
			{
				if (dxy >= step && x1 >= region.left && y1 >= region.top && x1 < region.right && y1 < region.bottom)
				{
					dxy = 0;
					*(m_ppLine[y1] + x1) = color;
				}

				y1 += stepy;
				change += dx;
				if (change > dy)
				{
					x1 += stepx;
					change -= dy;
				}

				dxy++;
			}
		}
		if (x2 >= region.left && y2 >= region.top && x2 < region.right && y2 < region.bottom)
		{
			*(m_ppLine[y2] + x2) = color;
		}
	}
}

void CMUTDibFunc::SetPseudoColor(BYTE nMode, BYTE nPseudoColor, BYTE nPos, BYTE nPalRange)
{
	CMUTDibFunc Old;
	Old = *this;

	if (this->Create(Old.GetWidth(), Old.GetHeight(), 0, nPseudoColor, Old.m_bCheckColor))
	{
		::CopyMemory(m_pDib, Old.GetBits(), m_Head.bih.biSizeImage);
	}
}

// 统计使用的颜色数
DWORD CMUTDibFunc::GetColorsCount() const
{
	if (this->IsEmpty())
		return FALSE;

	DWORD nCount = 0;
	BYTE pMap[257];
	FillMemory(pMap, 257, 0);

	LPBYTE pData;
	register int y = 0;
	register int nWidth = this->GetWidth();
	DWORD dwLen = this->GetPitch() * this->GetHeight();
	for (register DWORD l=0; l<dwLen; l++, pData++)
	{
		if (!(l % nWidth))
			pData = this->GetLine(y++);

		if (!*(pMap + *pData))
		{
			*(pMap + *pData) = 1;
			nCount++;
		}
	}
	return nCount;
}

// 得到一个不在图像中出现的颜色，作透明色
BOOL CMUTDibFunc::GetKeyColor(COLORREF &col)
{
	if (this->IsEmpty())
		return FALSE;

	DWORD nCount = 0;
	BYTE pMap[257];
	FillMemory(pMap, 257, 0);

	LPBYTE pData;
	register int y = 0;
	register int nWidth = this->GetWidth();
	DWORD dwLen = this->GetPitch() * this->GetHeight();
	for (register DWORD l=0; l<dwLen; l++, pData++)
	{
		if (!(l % nWidth))
			pData = this->GetLine(y++);

		if (!*(pMap + *pData))
		{
			*(pMap + *pData) = 1;
			nCount++;
		}
	}

	for (int c=0; c<256; c++)
	{
		if (!(pMap + c))
		{
			col = RGB(c, c, c);
			return TRUE;
		}
	}
	return FALSE;
}

// 得到灰度直方图数组，返回FALSE表示图像不是灰度
BOOL CMUTDibFunc::GetIntensity(DWORD dwIntensity[256], DWORD &dwMax, DWORD &dwCount)
{
	if (this->IsEmpty())
		return FALSE;

	FillMemory(dwIntensity, 256 * sizeof(LONG), 0);
	DWORD dwLen = this->GetPitch() * this->GetHeight();

	if ((DWORD)this->GetWidth() == this->GetPitch())
	{
		LPBYTE pData = this->GetBits();
		while (dwLen--)
			dwIntensity[*pData++]++;
	}
	else
	{
		LPBYTE pData;
		register DWORD y = 0, l;
		register DWORD dwPitch = this->GetPitch();
		for (l=0; l<dwLen; l++)
		{
			if (!(l % dwPitch))
				pData = this->GetLine(y++);
			dwIntensity[*pData++]++;
		}
	}

	dwMax = 0;
	dwCount = 0;
	for (register int i=0; i<256; i++)
	{
		dwMax = (dwMax >= dwIntensity[i]) ? dwMax : dwIntensity[i];
		dwCount += dwIntensity[i];
	}

	return TRUE;
}

BOOL CMUTDibFunc::GetSubBlock(CMUTDibFunc & SubDib, const RECT &rcBlock) const
{
	if (this->IsEmpty())
		return FALSE;

	RECT now = { 0, 0, this->GetWidth(), this->GetHeight() }, rcDest;
	if ((::IntersectRect(&rcDest, &now, &rcBlock)==0) || (&SubDib==this))
		return FALSE; // 没有相交区域或不满足条件

	int	nRectW = rcDest.right - rcDest.left,
		nRectH = rcDest.bottom - rcDest.top;
	if (!SubDib.Create(nRectW, nRectH, 0, this->m_nPseudoColor, this->m_bCheckColor))
		return FALSE;

	DWORD dwPitch = this->GetPitch();
	LPBYTE pSrc = this->GetLine(rcDest.left, rcDest.top);
	for (register int i=0; i<nRectH; i++, pSrc-=dwPitch)
		CopyMemory(SubDib.GetLine(i), pSrc, nRectW);

	return TRUE;
}

// 用一种颜色填充图像
BOOL CMUTDibFunc::Fill(LPRECT lpRect/* = NULL*/, COLORREF rgb/* = 0*/) 
{
	if (this->IsEmpty())
		return FALSE;
	CSingleLock lock(&m_cs, TRUE);
	if (lpRect == NULL)
		FillMemory(this->GetBits(), this->GetPitch() * this->GetHeight(), this->GetGrayscale(rgb));
	else
	{
		int l = (lpRect->left < 0) ? 0 : lpRect->left;
		int t = (lpRect->top < 0) ? 0 : lpRect->top;
		int r = (lpRect->right > this->GetWidth()) ? this->GetWidth() : lpRect->right;
		int b = (lpRect->bottom > this->GetHeight()) ? this->GetHeight() : lpRect->bottom;

		for (register int y=t; y<b; y++)
			FillMemory(this->GetLine(y) + l, r - l, this->GetGrayscale(rgb));
	}

	return TRUE;
}

#ifdef USE_MMX_IN_WIN32_XP
// 位图缩放bType == TRUE为宽高成比例缩放
BOOL CMUTDibFunc::Stretch32MMX(int nWidth, int nHeight, BOOL bType)
{
	CSingleLock lock(&m_cs, TRUE);
	if (this->IsEmpty() || nWidth<=0 || nHeight<=0)
		return FALSE;

	if (this->GetWidth()==nWidth && this->GetHeight()==nHeight)
		return TRUE;

	if (bType) // 成比例缩放
	{
		double duScale = min(nWidth / (double)this->GetWidth(), nHeight / (double)this->GetHeight());
		nWidth = (int)(duScale * this->GetWidth());
		nHeight = (int)(duScale * this->GetHeight());
	}
	int nWidthOld = this->GetWidth();
	int nHeightOld = this->GetHeight();

	DWORD *pOld = (DWORD*)SafeAlloc(nWidthOld * nHeightOld * sizeof(DWORD));
	if (pOld == NULL)
		return FALSE;

	LPBYTE ppOld = (LPBYTE)pOld;
	for (register int y=0; y<this->GetHeight(); y++)
	{
		LPBYTE pData = this->GetLine(y);
		for (register int x=0; x<this->GetWidth(); x++, pData++)
		{
			*ppOld++ = *pData;
			*ppOld++ = *pData;
			*ppOld++ = *pData;
			*ppOld++ = 0;
		}
	}

	if (!Create(nWidth, nHeight, 0, this->m_nPseudoColor, this->m_bCheckColor))
		return FALSE;
	else
	{
		DWORD *pNew = (DWORD*)SafeAlloc(nWidth * nHeight * sizeof(DWORD));
		if (pNew == NULL)
		{
			SafeFree(pOld);
			return FALSE;
		}

		// 调用内部MMX函数进行缩放
		CBaseObject::__MMX_InitAlphaTable();
		DWORD dU = (nWidthOld << 16) / nWidth;
		DWORD dV = (nHeightOld << 16) / nHeight;
		DWORD V1 = 0;
		for (register int i=0; i<nHeight-1; i++)
		{
			int y= (V1>>16);

			DWORD *ppNew = pNew + (nWidth * i);
			DWORD *ppOld = pOld + (nWidthOld * y);

			CBaseObject::__MMX_DrawScanLine(ppNew, ppOld, nWidth, dU);
			y++;

			CBaseObject::__MMX_DrawScanLineAlpha(ppNew, ppOld, nWidth, dU, (V1>>9)&0x7f);
			V1 += dV;
		}

		LPBYTE pp = (LPBYTE)pNew;
		for (register int y=0; y<this->GetHeight(); y++)
		{
			LPBYTE pData = this->GetLine(y);
			for (register int x=0; x<this->GetWidth(); x++, pp+=4)
			{
				*pData++ = *pp;
			}
		}

		SafeFree(pNew);
	}

	SafeFree(pOld);
	return TRUE;
}
#endif

// 对图像进行逻辑操作
BOOL CMUTDibFunc::Union(const CMUTDibFunc& Dib, DWORD dwRop, int x, int y, BYTE clrTransparent)
{
	if (this->IsEmpty() || Dib.IsEmpty())
		return FALSE;
	CSingleLock lock(&m_cs, TRUE);
	int		nNum;
	RECT	dib1 = { 0, 0, this->GetWidth(), this->GetHeight() },
			dib2 = { x, y, x + Dib.GetWidth(), y + Dib.GetHeight() },
			rcDest;
	if ((::IntersectRect(&rcDest, &dib1, &dib2) != 0))
	{
		LPBYTE pDst, pSrc;
		register int cx, cy;
		for (cy=rcDest.top; cy<rcDest.bottom; cy++)
		{
			pSrc = Dib.GetLine(rcDest.left - x, cy - y);
			pDst = this->GetLine(rcDest.left, cy);

			switch (dwRop)
			{
			case UNION_MOV:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
					*pDst = *pSrc;
				break;
			case UNION_AND:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
					*pDst &= *pSrc;
				break;
			case UNION_OR:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
					*pDst |= *pSrc;
				break;
			case UNION_XOR:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
					*pDst ^= *pSrc;
				break;
			case UNION_ADD:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
				{
					// 不用VC++的max和min宏定义,速度奇慢
					nNum = *pSrc + *pDst;
					if (nNum < 0) nNum = 0;
					else if (nNum > 0xFF) nNum = 0xFF;
					*pDst = nNum;
				}
				break;
			case UNION_SUB:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
				{
					// 不用VC++的max和min宏定义,速度奇慢
					nNum = *pSrc - *pDst;
					if (nNum < 0) nNum = 0;
					else if (nNum > 0xFF) nNum = 0xFF;
					*pDst = nNum;
				}
				break;
			case UNION_MUL:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
				{
					// 不用VC++的max和min宏定义,速度奇慢
					nNum = *pSrc * *pDst;
					if (nNum < 0) nNum = 0;
					else if (nNum > 0xFF) nNum = 0xFF;
					*pDst = nNum;
				}
				break;
			case UNION_TRP:
				for (cx=rcDest.left; cx<rcDest.right; cx++, pDst++, pSrc++)
				{
					if (*pSrc != clrTransparent)
					{
						*pDst = *pSrc;
					}
				}
				break;
			}
		}
	}

	return TRUE;
}

// 替换颜色
BOOL CMUTDibFunc::Replace(COLORREF src, COLORREF dst) 
{
	if (this->IsEmpty()) return FALSE;
	CSingleLock lock(&m_cs, TRUE);
	BYTE clrSrc = this->GetGrayscale(src);
	BYTE clrDst = this->GetGrayscale(dst);

	long w = this->GetWidth();
	long h = this->GetHeight();
	for (long y=0; y<h; y++)
	{
		PBYTE pLine = this->GetLine(y);
		for (long x=0; x<w; x++, pLine++)
		{
			if (*pLine == clrSrc) *pLine = clrDst;
		}
	}

	return TRUE;
}

void CMUTDibFunc::BitBlt(HDC hDC,
				int x, int y,		// 画图矩形
				DWORD dwRop,		// 与背景方式
				BOOL bPrint,
				BOOL bRevert)		// 是否是在打印(打印时要用StretchDIBits函数作图)
{
	if (m_hBitmap == NULL) return;
	CRect rect(x, y, x + m_Head.bih.biWidth, y + m_Head.bih.biHeight);
	this->BitBlt(hDC, &rect, dwRop, bPrint,bRevert);
}



void CMUTDibFunc::BitBlt(HDC hDC,
				LPCRECT lpRcDst,	// 画图矩形
				DWORD dwRop,		// 与背景方式
				BOOL bPrint,// 是否是在打印(打印时要用StretchDIBits函数作图)
				BOOL bRevert)		
{
	if (m_hBitmap == NULL) return;

	int width = m_Head.bih.biWidth;
	int height = m_Head.bih.biHeight;

	CRect Rect;
	if (lpRcDst == NULL)
		SetRect(&Rect, 0, 0, width, height);
	else
		Rect = lpRcDst;

	if (!bPrint)
	{
		HDC hMemDC = ::CreateCompatibleDC(hDC);
		//here flip?
		HGDIOBJ hOld;
		if (bRevert)
		{
			HBITMAP tmpBitmap = GetInvertedBitmap(m_hBitmap, true);
			 hOld = ::SelectObject(hMemDC, tmpBitmap);
		}
		else
		{
			 hOld = ::SelectObject(hMemDC, m_hBitmap);
		}

		::BitBlt(hDC, Rect.left, Rect.top, Rect.Width(), Rect.Height(), hMemDC, 0, 0, dwRop);

		::SelectObject(hMemDC, hOld);
		::DeleteDC(hMemDC);
	}
	else
	{
		::StretchDIBits(hDC,
						Rect.left, Rect.top, Rect.Width(), Rect.Height(),
						0, 0, Rect.Width(), Rect.Height(),
						m_pDib,
						(BITMAPINFO*)&m_Head,
						DIB_RGB_COLORS, dwRop);
	}
}

// 在图像上写文本(lpRect不能超过图像大小)
BOOL CMUTDibFunc::DrawText(LPCTSTR lpszStr, LPCRECT lpRect, UINT nFormat, COLORREF color, CFont* pFont)
{
	if (this->IsEmpty() || this->IsEmpty())
		return FALSE;
	CSingleLock lock(&m_cs, TRUE);
	CRect rect;
	if (lpRect == NULL)
	{
		rect.SetRect(0, 0, this->GetWidth(), this->GetHeight());
	}
	else
	{
		rect = lpRect;
	}

	HDC hDC = ::CreateCompatibleDC(NULL);
	HGDIOBJ hOldBmp = ::SelectObject(hDC, this->GetBitmap());
	HGDIOBJ hOldFont = ::SelectObject(hDC, pFont->GetSafeHandle());

	::SetBkMode(hDC, TRANSPARENT);
	::SetTextColor(hDC, color);
	::DrawText(hDC, lpszStr, lstrlen(lpszStr), &rect, nFormat);

	::SelectObject(hDC, hOldFont);
	::SelectObject(hDC, hOldBmp);
	::DeleteDC(hDC);

	return TRUE;
}

BOOL CMUTDibFunc::TextOut(int x, int y, LPCTSTR lpszStr, COLORREF color, CFont* pFont)
{
	if (this->IsEmpty() || this->IsEmpty())
		return FALSE;
	CSingleLock lock(&m_cs, TRUE);
	HDC hDC = ::CreateCompatibleDC(NULL);
	HGDIOBJ hOldBmp = ::SelectObject(hDC, this->GetBitmap());
	HGDIOBJ hOldFont = ::SelectObject(hDC, pFont->GetSafeHandle());

	::SetBkMode(hDC, TRANSPARENT);
	::SetTextColor(hDC, color);
	::TextOut(hDC, x, y, lpszStr, lstrlen(lpszStr));

	::SelectObject(hDC, hOldFont);
	::SelectObject(hDC, hOldBmp);
	::DeleteDC(hDC);

	return TRUE;
}

// 复制位图到新内存,用完后一定要记得FreeBitsEx删除,处理时保存旧图像
LPBYTE CMUTDibFunc::CopyBitsEx(CMUTDibFunc & dib)
{
	if (dib.IsEmpty())
		return NULL;

	DWORD dwLen = dib.GetPitch() * dib.GetHeight();
	LPBYTE pOldDib = (LPBYTE)SafeAlloc(dwLen);
	if (pOldDib == NULL)
		return NULL;
	CopyMemory(pOldDib, dib.GetBits(), dwLen);
	return pOldDib;
}
void CMUTDibFunc::FreeBitsEx(LPBYTE pCopyBits)
{
	SafeFree(pCopyBits);
}
void CMUTDibFunc::SetPalette(tagRGBQUAD *pPal, unsigned short count)
{
	if(count<= 256 )
	{
		memcpy(m_Head.pPal, pPal, count*sizeof(tagRGBQUAD));
	}
}

void CMUTDibFunc::GetPalette(tagRGBQUAD *pal) const
{
	if(pal != NULL)
	{
		memcpy(pal, m_Head.pPal, 256*sizeof(tagRGBQUAD));
	}
}

BYTE CMUTDibFunc::GetGrayscale(const DWORD rgb)
{
	register UINT32	tol = 299*(rgb&0xff) + 587*((rgb>>8)&0xff) + 114*((rgb>>16)&0xff) + 500;
	return (tol / 1000);
}

BYTE CMUTDibFunc::GetGrayscale(const RGBQUAD rgb)
{
	register UINT32	tol = 299*rgb.rgbRed + 587*rgb.rgbGreen + 114*rgb.rgbBlue + 500;
	return (tol / 1000);
}

BYTE CMUTDibFunc::GetGrayscale(const RGBTRIPLE rgb)
{
	register UINT32	tol = 299*rgb.rgbtRed + 587*rgb.rgbtGreen + 114*rgb.rgbtBlue + 500;
	return (tol / 1000);
}

BYTE CMUTDibFunc::GetGrayscale(const BYTE r, const BYTE g, const BYTE b)
{
	register UINT32	tol = 299 * r + 587 * g + 114 * b + 500;
	return (tol / 1000);
}



// GetInvertedBitmap - Creates a new bitmap with the inverted image
// Returns - Handle to a new bitmap with inverted image
// hBitmap - Bitmap to invert
// bLateral - Flag to indicate whether to invert laterally or vertically
HBITMAP CMUTDibFunc::GetInvertedBitmap(HBITMAP hBitmap, BOOL bLateral)
{
	// Create a memory DC compatible with the display 
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC(NULL);
	destDC.CreateCompatibleDC(NULL);

	// Get logical coordinates 
	BITMAP bm;
	::GetObject(hBitmap, sizeof(bm), &bm);

	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), bm.bmWidth, bm.bmHeight);

	// Select bitmaps into the DCs
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject(sourceDC.m_hDC, hBitmap);
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject(destDC.m_hDC, hbmResult);
	if (bLateral)
		destDC.StretchBlt(0, 0, bm.bmWidth, bm.bmHeight, &sourceDC,
			bm.bmWidth - 1, 0, -bm.bmWidth, bm.bmHeight, SRCCOPY);
	else
		destDC.StretchBlt(0, 0, bm.bmWidth, bm.bmHeight, &sourceDC,
			0, bm.bmHeight - 1, bm.bmWidth, -bm.bmHeight, SRCCOPY);

	// Reselect the old bitmaps 
	::SelectObject(sourceDC.m_hDC, hbmOldSource);
	::SelectObject(destDC.m_hDC, hbmOldDest);
	//sourceDC.Detach();
	//destDC.Detach();
	//DeleteObject(hbmResult);
	DeleteObject(hbmOldSource);
	DeleteObject(hbmOldDest);
	return hbmResult;
}
