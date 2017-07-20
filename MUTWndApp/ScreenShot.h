#pragma once

class _declspec(dllexport) CScreenShot
{
public:
	CScreenShot(void);
	~CScreenShot(void);

	/*!
	@brief 截取指定位置矩形(l,t, r, b)的矩形图像
	@param left   左边界
	@param top    上边界
	@param right  右边界
	@param bottom 底边界
	@return  需注意释放HBITMAP对象
	*/
	HBITMAP GetScrRectBmp(int l, int t, int r, int b);
	/*!
	@brief 将bmp保存成32位彩色bmp文件
	*/
	BOOL Save32BitBmp(HBITMAP hBitmap,LPCTSTR lpszPath);

};
