#pragma once
#include "afxwin.h"
class CMutBitmap : public CBitmap
{
public:
	// Constructors
	CMutBitmap();

	void LoadBitmapEx(UINT nID, BOOL bIconBkgrd);
	CPalette *GetPalette() { return m_pPalette; };

	// Implementation
public:
	virtual ~CMutBitmap();

	// Attributes
	int	m_Width;
	int m_Height;
	// Operations

private:
	CPalette *m_pPalette;
};

