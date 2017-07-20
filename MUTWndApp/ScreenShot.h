#pragma once

class _declspec(dllexport) CScreenShot
{
public:
	CScreenShot(void);
	~CScreenShot(void);

	/*!
	@brief ��ȡָ��λ�þ���(l,t, r, b)�ľ���ͼ��
	@param left   ��߽�
	@param top    �ϱ߽�
	@param right  �ұ߽�
	@param bottom �ױ߽�
	@return  ��ע���ͷ�HBITMAP����
	*/
	HBITMAP GetScrRectBmp(int l, int t, int r, int b);
	/*!
	@brief ��bmp�����32λ��ɫbmp�ļ�
	*/
	BOOL Save32BitBmp(HBITMAP hBitmap,LPCTSTR lpszPath);

};
