// DIB.h
//////////////////////////////////////////////////////////////////
//					**	图象基础封装类	**						//
//		  所有图像特效只对8位图像有效,如果不是,则先转换			//
//////////////////////////////////////////////////////////////////
#ifndef __DIB_H__
#define __DIB_H__

//#include <afxtempl.h>
#include "afxmt.h"

//=============================================================================
//	合并方式
//=============================================================================
#define		UNION_MOV	0x00000001
#define		UNION_AND	0x00000002
#define		UNION_OR	0x00000004
#define		UNION_XOR	0x00000008
#define		UNION_ADD	0x00000010
#define		UNION_SUB	0x00000020
#define		UNION_MUL	0x00000040
#define		UNION_DIV	0x00000080
#define		UNION_TRP	0x00000100

//=============================================================================
//	伪彩着色方式(中断方式、压缩方式)
//=============================================================================
enum
{
	PSEUDO_BREAK = 0,
	PSEUDO_COMPRESS = 1
};

//////////////////////////////////////////////////////////////////
//					**	图象基础封装类	**						//
//		  所有图像特效只对8位图像有效,如果不是,则先转换			//
//////////////////////////////////////////////////////////////////

typedef struct tagDIBINFO
{
	BITMAPINFOHEADER bih;
	BYTE pPal[1024];
}DIBINFO, *PDIBINFO;

class __declspec(dllexport) CMUTDibFunc
{
public:
	CMUTDibFunc();
	CMUTDibFunc(const CMUTDibFunc& Dib);
	CMUTDibFunc(int nWidth, int nHeight, COLORREF rgb = 0, int nPseudoColor = 0, BOOL bCheckColor = FALSE);

	~CMUTDibFunc();

public:
				// 位图是否修改
	BOOL		GetModify() const;
				// 设置修改标志
	void		SetModify(BOOL bModify);

				// 位图赋值与交换
	CMUTDibFunc&		operator=(const CMUTDibFunc& Dib);
	BOOL		operator==(CMUTDibFunc& Dib) const;
	BOOL		operator!=(CMUTDibFunc& Dib) const;
	void		Swap(CMUTDibFunc & dib);

				// 建立DIB位图
	BOOL		Create(int nWidth, int nHeight, COLORREF rgb = 0, int nPseudoColor = 0, BOOL bCheckColor = FALSE);

// 位图属性
public:
				// 位图是否为空
	BOOL		IsEmpty() const;
				// 清空位图
	void		Empty();

				// 获取图像宽度
	int			GetWidth() const;
				// 获取图像高度
	int			GetHeight() const;
				// 获取图像扫描行长度(32位补齐)
	DWORD		GetPitch() const;

				// 获取象素真实的颜色值
	COLORREF	GetPixel(int x, int y) const;
				// 设置象素的颜色值
	void		SetPixel(int x, int y, COLORREF rgb) ;
				// 画线
	void		Line(POINT pt1, POINT pt2, COLORREF rgb, double step = 1.0, LPRECT lpRectRegion = NULL) ;
	void		Line(int x1, int y1, int x2, int y2, COLORREF rgb, double step = 1.0, LPRECT lpRectRegion = NULL) ;

				// 获取位图头
	PBITMAPINFOHEADER GetHead() const;
	const DIBINFO * GetDibInfo();
				// 获取调色板数据
	unsigned char *	GetPal();
	void		GetPalette(tagRGBQUAD pPal[256])const;
	void		SetPalette(tagRGBQUAD *pPal, unsigned short count);
				// 获取图像数据
	LPBYTE		GetBits() const;
				// 获取某一行数据指针
	LPBYTE		GetLine(int nLine = 0) const;
				// 获取从y行，x列开始的数据指针
	LPBYTE		GetLine(int x, int y) const;
				// 获取位图句柄(不能删除)
	HBITMAP		GetBitmap() const;

				// 获取当前图像的伪彩编号
	int			GetPseudoColor() const;
	void		GetPseudoColor(BYTE &nMode, BYTE &nType, BYTE &nPos, BYTE &nPalRange) const;
				// 设置当前图像的伪彩编号
				// 注意: 此函数将重建位图,所以在要求速度时,请直接在Create时传递伪彩参数
	void		SetPseudoColor(BYTE nPseudoColor);
	void		SetPseudoColor(BYTE nMode, BYTE nPseudoColor, BYTE nPos, BYTE nPalRange);

				// 是否校验颜色
	BOOL		GetCheckColor() const;
				// 统计使用的颜色数
	DWORD		GetColorsCount() const;
				// 得到一个不在图像中出现的颜色，作透明色
	BOOL		GetKeyColor(COLORREF &col);
				// 得到灰度直方图数组，返回FALSE表示图像不是灰度
	BOOL		GetIntensity(DWORD dwIntensity[256], DWORD &dwMax, DWORD &dwCount);

// 位图基本操作
public:
	enum FILTERTYPE
	{
		STOCK_FILTER_BELL = 0,
		STOCK_FILTER_BOX,
		STOCK_FILTER_CATMULLROM,
		STOCK_FILTER_COSINE,
		STOCK_FILTER_CUBICCONVOLUTION,
		STOCK_FILTER_CUBICSPLINE,
		STOCK_FILTER_HERMITE,
		STOCK_FILTER_LANCZOS3,
		STOCK_FILTER_LANCZOS8,
		STOCK_FILTER_MITCHELL,
		STOCK_FILTER_QUADRATIC,
		STOCK_FILTER_QUADRATICBSPLINE,
		STOCK_FILTER_TRIANGLE,
		STOCK_FILTERS
	};

#ifdef USE_MMX_IN_WIN32_XP
				// 32位MMX位图缩放bType == TRUE 为宽高成比例缩放
	BOOL		Stretch32MMX(int nWidth, int nHeight, BOOL bType = TRUE);
#endif

				// 用一种颜色填充图像
	BOOL		Fill(LPRECT lpRect = NULL, COLORREF rgb = 0) ;
				// 从Dib中获取子块Dib, pSubDib不能为this
	BOOL		GetSubBlock(CMUTDibFunc & SubDib, const RECT &rcBlock) const;
				// 图像合并
	BOOL		Union(const CMUTDibFunc& Dib, DWORD dwRop = UNION_MOV, int x = 0, int y = 0, BYTE clrTransparent = 0);

				// 替换颜色
	BOOL		Replace(COLORREF src, COLORREF dst) ;

				// 拷贝位图
	BOOL		CopyDib(const CMUTDibFunc & dib);

				// 在图像上写文本(lpRect不能超过图像大小)
	BOOL		DrawText(LPCTSTR lpszStr,
						 LPCRECT lpRect,
						 UINT nFormat,
						 COLORREF color,
						 CFont* pFont);
	BOOL		TextOut(int x, int y, LPCTSTR lpszStr, COLORREF color, CFont* pFont);

// 位图的缩放显示
public:
	void		BitBlt(HDC hDC,
					   int x = 0, int y = 0,	// 画图位置
					   DWORD dwRop = SRCCOPY,	// 与背景方式
					   BOOL bPrint = FALSE,
					   BOOL bRevert = FALSE);	// 是否是在打印

	void		BitBlt(HDC hDC,
					   LPCRECT lpRcDst = NULL,	// 画图矩形
					   DWORD dwRop = SRCCOPY,	// 与背景方式
					   BOOL bPrint = FALSE,
					   BOOL bRevert = FALSE);	// 是否是在打印
	

public:
					// 复制位图到新内存,处理时保存旧图像
	static LPBYTE	CopyBitsEx(CMUTDibFunc & dib);
					// 用完后一定要记得FreeBitsEx删除
	static void		FreeBitsEx(LPBYTE pCopyBits);
	

public:
	static BYTE		GetGrayscale(const DWORD rgb);
	static BYTE		GetGrayscale(const RGBQUAD rgb);
	static BYTE		GetGrayscale(const RGBTRIPLE rgb);
	static BYTE		GetGrayscale(const BYTE r, const BYTE g, const BYTE b);

private:
	DIBINFO			m_Head;			// BMP位图头+调色板
	BYTE*			m_pDib;			// 图像内存
	BYTE**			m_ppLine;		// ppLine自上而下存放
	HBITMAP			m_hBitmap;		// 位图句柄

//	用于图像缩放及显示
private:
	BOOL			m_bModify;		// 图像是否修改标志

	BOOL			m_bCheckColor;	// 是否校验颜色
	BYTE			m_nPseudoMode;	// 伪彩着色(中断方式/压缩方式)
	BYTE			m_nPseudoColor;	// 伪彩编号
	BYTE			m_nPos;			// 伪彩起点
	BYTE			m_nPalRange;	// 伪彩范围
	CCriticalSection m_cs;	// 图像数据的写锁,在任何改变图像数据的地方都要加锁
public:
	HBITMAP GetInvertedBitmap(HBITMAP hBitmap, BOOL bLateral);
};

inline BOOL CMUTDibFunc::GetModify() const		 { return m_bModify;   }
inline void CMUTDibFunc::SetModify(BOOL bModify){	m_bModify = bModify;}
inline BOOL CMUTDibFunc::IsEmpty() const {
	return ((m_hBitmap == NULL) || (m_pDib == NULL) || (m_Head.bih.biWidth == 0) || (m_Head.bih.biHeight == 0));
}
inline int CMUTDibFunc::GetWidth() const {	return m_Head.bih.biWidth;}
inline int CMUTDibFunc::GetHeight() const {return m_Head.bih.biHeight;}
inline DWORD CMUTDibFunc::GetPitch() const { return ((m_Head.bih.biWidth * 8) + 31) / 32 * 4;}
inline COLORREF CMUTDibFunc::GetPixel(int x, int y) const {
	ASSERT(y >= 0 && y < m_Head.bih.biHeight);
	BYTE rgb = *GetLine(x, y);
	return RGB(rgb, rgb, rgb);
}
inline HBITMAP CMUTDibFunc::GetBitmap() const {	return m_hBitmap;}
inline void CMUTDibFunc::SetPixel(int x, int y, COLORREF rgb) {
	CSingleLock lock(&m_cs, TRUE);
	ASSERT(y >= 0 && y < m_Head.bih.biHeight);
	*GetLine(x, y) = this->GetGrayscale(rgb);
}
inline PBITMAPINFOHEADER CMUTDibFunc::GetHead() const {
	return (PBITMAPINFOHEADER)&m_Head.bih;
}
inline const DIBINFO *CMUTDibFunc::GetDibInfo() {
	return &m_Head;
}
inline LPBYTE CMUTDibFunc::GetBits() const {
	return m_pDib;
}
inline LPBYTE CMUTDibFunc::GetLine(int nLine) const {
	ASSERT(nLine >= 0 && nLine < m_Head.bih.biHeight);
	return m_ppLine[nLine];
}
inline LPBYTE CMUTDibFunc::GetLine(int x, int y) const {
	ASSERT(y >= 0 && y < m_Head.bih.biHeight);
	return (m_ppLine[y] + x);
}
inline unsigned char * CMUTDibFunc::GetPal() {
	return m_Head.pPal;
}

inline BOOL CMUTDibFunc::GetCheckColor() const {
	return m_bCheckColor;
}
inline int CMUTDibFunc::GetPseudoColor() const {
	return m_nPseudoColor;
}
inline void CMUTDibFunc::GetPseudoColor(BYTE &nMode, BYTE &nType, BYTE &nPos, BYTE &nPalRange) const {
	nMode = m_nPseudoMode;
	nType = m_nPseudoColor;
	nPos = m_nPos;
	nPalRange = m_nPalRange;
}
inline void CMUTDibFunc::SetPseudoColor(BYTE nPseudoColor) {
	if(m_nPseudoColor != nPseudoColor) 
	{
		this->SetPseudoColor(PSEUDO_COMPRESS, nPseudoColor, 0, 255);
	}
}

#endif
