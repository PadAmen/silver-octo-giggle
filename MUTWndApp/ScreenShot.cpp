#include "stdafx.h"
#include "ScreenShot.h"
#include <assert.h>
CScreenShot::CScreenShot(void)
{
}

CScreenShot::~CScreenShot(void)
{
}


BOOL CScreenShot::Save32BitBmp(HBITMAP hBitmap,LPCTSTR lpszPath)
{
	assert(hBitmap != NULL && lpszPath != NULL);
	WORD wbitsCount;//λͼ��ÿ��������ռ�ֽ�����
	DWORD dwpalettelsize=0;//��ɫ���С
	DWORD dwbmdibitsize,dwdibsize,dwwritten;
	BITMAP bitmap;//������λͼ�ĸ��ֵ���Ϣ��
	BITMAPFILEHEADER bmfhdr;//�����˴�С�����͵�BMP�ļ�����Ϣ��
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh,fdib;
	::GetObject(hBitmap,sizeof(BITMAP),(void *)&bitmap);//�õ�BITMAP�ṹ��
	//���´�������BITMAP����Ϣ���BITMAPINFOHEADER�ṹ
	wbitsCount=bitmap.bmBitsPixel;
	bi.biSize=sizeof(BITMAPINFOHEADER);
	bi.biWidth=bitmap.bmWidth;
	bi.biHeight=bitmap.bmHeight;
	bi.biPlanes=1;
	bi.biBitCount= bitmap.bmBitsPixel ;
	bi.biClrImportant=0;
	bi.biClrUsed=0;
	bi.biCompression=BI_RGB;
	bi.biSizeImage=0;
	bi.biYPelsPerMeter=0;
	bi.biXPelsPerMeter=0;
	//���´����ǻ�ȡ��ɫ��ĳ��ȣ���ɫ�����ڵ��ô����٣���Ϊ256ɫ��λͼ�Ѿ������ˡ�
	if(wbitsCount<=8)
	{
		dwpalettelsize = ((DWORD)(1<<wbitsCount)*sizeof(RGBQUAD));
	}
	//����λͼ�Ĵ�С����������Ӧ���ڴ�ռ䣬ע�����û�з���BITMAPFILEHEADER��
	dwbmdibitsize=((bitmap.bmWidth*wbitsCount+31)/8)*bitmap.bmHeight;
	fdib = ::GlobalAlloc(GHND,dwbmdibitsize+dwpalettelsize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(fdib);
	*lpbi=bi;//��bi�е�����д�������ڴ��С�
	HDC hdc=::GetDC(NULL);
	::GetDIBits(hdc,hBitmap,0,(UINT)bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwpalettelsize,(BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	::ReleaseDC(NULL, hdc);
	/*GetDIBits������Ҫ�ĺ������������λͼ���ݵĹ�����������ɣ�����һ������ΪHDC,�ڶ�������Ϊλͼ�����
	����������Ϊɨ���еĿ�ʼ�У�һ��Ϊ0�����ĸ�Ϊ�����У�һ����Ǹ߶ȣ����ĸ���������Ҫ������ʾ�������ݵ���ʼ��ַ��
	�����ַһ�����ڵ�ɫ��֮�󡣵��������ָ���ǽ���BITMAPINFO�ṹ�ĵ�ַ��
	����ṹ����û��д������ʵ����BITMAPINFO�ṹ���ϵ�ɫ����Ϣ�����һ�������Ǹ�ʽ��һ����DIB_RGB_COLORS*/
	//�����ļ��Լ��ļ���Ϣͷ
	fh = ::CreateFile(lpszPath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(fh==INVALID_HANDLE_VALUE)
		return FALSE;
	bmfhdr.bfType=0x4d42;//BMP���ͣ�һ��Ҫ����д
	dwdibsize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwbmdibitsize+dwpalettelsize;//�ļ��ܳ����ɼ����������
	bmfhdr.bfSize=dwdibsize;
	bmfhdr.bfReserved1=0;
	bmfhdr.bfReserved2=0;
	bmfhdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwpalettelsize;//λͼ����������ļ�ͷ��ƫ����
	//���ļ���Ϣͷд���ļ�
	::WriteFile(fh,(LPSTR)&bmfhdr,sizeof(BITMAPFILEHEADER),&dwwritten,NULL);
	//������д���ļ�������BITMAPINFO�ṹ����ɫ�塢����
	::WriteFile(fh,(LPSTR)lpbi,dwdibsize,&dwwritten,NULL);
	//�ر���ؾ��
	::GlobalUnlock(fdib);
	::GlobalFree(fdib);
	::CloseHandle(fh);
	return TRUE;
}

// ��Ҫע�����deleteobject���ͷŷ��ص�HBITMAP���
HBITMAP CScreenShot::GetScrRectBmp(int l, int t, int r, int b)
{
	assert(r>l);
	assert(b>t);
	RECT rcCopy = {l, t, r,b};
	HDC hdcScr = ::GetWindowDC(NULL);

	int cx = rcCopy.right-rcCopy.left;
	int cy = rcCopy.bottom-rcCopy.top;
	HBITMAP hbmp=::CreateCompatibleBitmap(hdcScr, cx, cy);
	HDC memdc = ::CreateCompatibleDC(hdcScr);
	::SelectObject(memdc, hbmp);
	::BitBlt(memdc, 0, 0, cx, cy, hdcScr, rcCopy.left, rcCopy.top, SRCCOPY);	
	::DeleteDC(memdc);
	return hbmp;
}