// DIB.h
//////////////////////////////////////////////////////////////////
//					**	ͼ�������װ��	**						//
//		  ����ͼ����Чֻ��8λͼ����Ч,�������,����ת��			//
//////////////////////////////////////////////////////////////////
#ifndef __DIB_H__
#define __DIB_H__

//#include <afxtempl.h>
#include "afxmt.h"

//=============================================================================
//	�ϲ���ʽ
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
//	α����ɫ��ʽ(�жϷ�ʽ��ѹ����ʽ)
//=============================================================================
enum
{
	PSEUDO_BREAK = 0,
	PSEUDO_COMPRESS = 1
};

//////////////////////////////////////////////////////////////////
//					**	ͼ�������װ��	**						//
//		  ����ͼ����Чֻ��8λͼ����Ч,�������,����ת��			//
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
				// λͼ�Ƿ��޸�
	BOOL		GetModify() const;
				// �����޸ı�־
	void		SetModify(BOOL bModify);

				// λͼ��ֵ�뽻��
	CMUTDibFunc&		operator=(const CMUTDibFunc& Dib);
	BOOL		operator==(CMUTDibFunc& Dib) const;
	BOOL		operator!=(CMUTDibFunc& Dib) const;
	void		Swap(CMUTDibFunc & dib);

				// ����DIBλͼ
	BOOL		Create(int nWidth, int nHeight, COLORREF rgb = 0, int nPseudoColor = 0, BOOL bCheckColor = FALSE);

// λͼ����
public:
				// λͼ�Ƿ�Ϊ��
	BOOL		IsEmpty() const;
				// ���λͼ
	void		Empty();

				// ��ȡͼ����
	int			GetWidth() const;
				// ��ȡͼ��߶�
	int			GetHeight() const;
				// ��ȡͼ��ɨ���г���(32λ����)
	DWORD		GetPitch() const;

				// ��ȡ������ʵ����ɫֵ
	COLORREF	GetPixel(int x, int y) const;
				// �������ص���ɫֵ
	void		SetPixel(int x, int y, COLORREF rgb) ;
				// ����
	void		Line(POINT pt1, POINT pt2, COLORREF rgb, double step = 1.0, LPRECT lpRectRegion = NULL) ;
	void		Line(int x1, int y1, int x2, int y2, COLORREF rgb, double step = 1.0, LPRECT lpRectRegion = NULL) ;

				// ��ȡλͼͷ
	PBITMAPINFOHEADER GetHead() const;
	const DIBINFO * GetDibInfo();
				// ��ȡ��ɫ������
	unsigned char *	GetPal();
	void		GetPalette(tagRGBQUAD pPal[256])const;
	void		SetPalette(tagRGBQUAD *pPal, unsigned short count);
				// ��ȡͼ������
	LPBYTE		GetBits() const;
				// ��ȡĳһ������ָ��
	LPBYTE		GetLine(int nLine = 0) const;
				// ��ȡ��y�У�x�п�ʼ������ָ��
	LPBYTE		GetLine(int x, int y) const;
				// ��ȡλͼ���(����ɾ��)
	HBITMAP		GetBitmap() const;

				// ��ȡ��ǰͼ���α�ʱ��
	int			GetPseudoColor() const;
	void		GetPseudoColor(BYTE &nMode, BYTE &nType, BYTE &nPos, BYTE &nPalRange) const;
				// ���õ�ǰͼ���α�ʱ��
				// ע��: �˺������ؽ�λͼ,������Ҫ���ٶ�ʱ,��ֱ����Createʱ����α�ʲ���
	void		SetPseudoColor(BYTE nPseudoColor);
	void		SetPseudoColor(BYTE nMode, BYTE nPseudoColor, BYTE nPos, BYTE nPalRange);

				// �Ƿ�У����ɫ
	BOOL		GetCheckColor() const;
				// ͳ��ʹ�õ���ɫ��
	DWORD		GetColorsCount() const;
				// �õ�һ������ͼ���г��ֵ���ɫ����͸��ɫ
	BOOL		GetKeyColor(COLORREF &col);
				// �õ��Ҷ�ֱ��ͼ���飬����FALSE��ʾͼ���ǻҶ�
	BOOL		GetIntensity(DWORD dwIntensity[256], DWORD &dwMax, DWORD &dwCount);

// λͼ��������
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
				// 32λMMXλͼ����bType == TRUE Ϊ��߳ɱ�������
	BOOL		Stretch32MMX(int nWidth, int nHeight, BOOL bType = TRUE);
#endif

				// ��һ����ɫ���ͼ��
	BOOL		Fill(LPRECT lpRect = NULL, COLORREF rgb = 0) ;
				// ��Dib�л�ȡ�ӿ�Dib, pSubDib����Ϊthis
	BOOL		GetSubBlock(CMUTDibFunc & SubDib, const RECT &rcBlock) const;
				// ͼ��ϲ�
	BOOL		Union(const CMUTDibFunc& Dib, DWORD dwRop = UNION_MOV, int x = 0, int y = 0, BYTE clrTransparent = 0);

				// �滻��ɫ
	BOOL		Replace(COLORREF src, COLORREF dst) ;

				// ����λͼ
	BOOL		CopyDib(const CMUTDibFunc & dib);

				// ��ͼ����д�ı�(lpRect���ܳ���ͼ���С)
	BOOL		DrawText(LPCTSTR lpszStr,
						 LPCRECT lpRect,
						 UINT nFormat,
						 COLORREF color,
						 CFont* pFont);
	BOOL		TextOut(int x, int y, LPCTSTR lpszStr, COLORREF color, CFont* pFont);

// λͼ��������ʾ
public:
	void		BitBlt(HDC hDC,
					   int x = 0, int y = 0,	// ��ͼλ��
					   DWORD dwRop = SRCCOPY,	// �뱳����ʽ
					   BOOL bPrint = FALSE,
					   BOOL bRevert = FALSE);	// �Ƿ����ڴ�ӡ

	void		BitBlt(HDC hDC,
					   LPCRECT lpRcDst = NULL,	// ��ͼ����
					   DWORD dwRop = SRCCOPY,	// �뱳����ʽ
					   BOOL bPrint = FALSE,
					   BOOL bRevert = FALSE);	// �Ƿ����ڴ�ӡ
	

public:
					// ����λͼ�����ڴ�,����ʱ�����ͼ��
	static LPBYTE	CopyBitsEx(CMUTDibFunc & dib);
					// �����һ��Ҫ�ǵ�FreeBitsExɾ��
	static void		FreeBitsEx(LPBYTE pCopyBits);
	

public:
	static BYTE		GetGrayscale(const DWORD rgb);
	static BYTE		GetGrayscale(const RGBQUAD rgb);
	static BYTE		GetGrayscale(const RGBTRIPLE rgb);
	static BYTE		GetGrayscale(const BYTE r, const BYTE g, const BYTE b);

private:
	DIBINFO			m_Head;			// BMPλͼͷ+��ɫ��
	BYTE*			m_pDib;			// ͼ���ڴ�
	BYTE**			m_ppLine;		// ppLine���϶��´��
	HBITMAP			m_hBitmap;		// λͼ���

//	����ͼ�����ż���ʾ
private:
	BOOL			m_bModify;		// ͼ���Ƿ��޸ı�־

	BOOL			m_bCheckColor;	// �Ƿ�У����ɫ
	BYTE			m_nPseudoMode;	// α����ɫ(�жϷ�ʽ/ѹ����ʽ)
	BYTE			m_nPseudoColor;	// α�ʱ��
	BYTE			m_nPos;			// α�����
	BYTE			m_nPalRange;	// α�ʷ�Χ
	CCriticalSection m_cs;	// ͼ�����ݵ�д��,���κθı�ͼ�����ݵĵط���Ҫ����
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
