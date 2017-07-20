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
	WORD wbitsCount;//位图中每个像素所占字节数。
	DWORD dwpalettelsize=0;//调色板大小
	DWORD dwbmdibitsize,dwdibsize,dwwritten;
	BITMAP bitmap;//定义了位图的各种的信息。
	BITMAPFILEHEADER bmfhdr;//定义了大小、类型等BMP文件的信息。
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh,fdib;
	::GetObject(hBitmap,sizeof(BITMAP),(void *)&bitmap);//得到BITMAP结构。
	//以下代码是用BITMAP的信息填充BITMAPINFOHEADER结构
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
	//以下代码是获取调色板的长度，调色板现在的用处很少，因为256色的位图已经不多了。
	if(wbitsCount<=8)
	{
		dwpalettelsize = ((DWORD)(1<<wbitsCount)*sizeof(RGBQUAD));
	}
	//计算位图的大小，并分配相应的内存空间，注意的是没有分配BITMAPFILEHEADER。
	dwbmdibitsize=((bitmap.bmWidth*wbitsCount+31)/8)*bitmap.bmHeight;
	fdib = ::GlobalAlloc(GHND,dwbmdibitsize+dwpalettelsize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(fdib);
	*lpbi=bi;//将bi中的数据写入分配的内存中。
	HDC hdc=::GetDC(NULL);
	::GetDIBits(hdc,hBitmap,0,(UINT)bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwpalettelsize,(BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	::ReleaseDC(NULL, hdc);
	/*GetDIBits是最重要的函数，真正获得位图数据的工作就由它完成，它第一个参数为HDC,第二个参数为位图句柄，
	第三个参数为扫描行的开始行，一般为0，第四个为结束行，一般就是高度，第四个参数最重要，它表示接收数据的起始地址，
	这个地址一般是在调色板之后。第五个参数指的是接收BITMAPINFO结构的地址，
	这个结构上面没有写，它其实就是BITMAPINFO结构加上调色板信息。最后一个参数是格式。一般是DIB_RGB_COLORS*/
	//创建文件以及文件信息头
	fh = ::CreateFile(lpszPath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(fh==INVALID_HANDLE_VALUE)
		return FALSE;
	bmfhdr.bfType=0x4d42;//BMP类型，一定要这样写
	dwdibsize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwbmdibitsize+dwpalettelsize;//文件总长，由几个部分组成
	bmfhdr.bfSize=dwdibsize;
	bmfhdr.bfReserved1=0;
	bmfhdr.bfReserved2=0;
	bmfhdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwpalettelsize;//位图数据相对于文件头的偏移量
	//将文件信息头写入文件
	::WriteFile(fh,(LPSTR)&bmfhdr,sizeof(BITMAPFILEHEADER),&dwwritten,NULL);
	//将数据写入文件，包含BITMAPINFO结构、调色板、数据
	::WriteFile(fh,(LPSTR)lpbi,dwdibsize,&dwwritten,NULL);
	//关闭相关句柄
	::GlobalUnlock(fdib);
	::GlobalFree(fdib);
	::CloseHandle(fh);
	return TRUE;
}

// 需要注意调用deleteobject来释放返回的HBITMAP句柄
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