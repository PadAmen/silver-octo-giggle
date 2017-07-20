#include "StdAfx.h"
#include "MUTImgProcFunc.h"
#include "MUTWndApp.h"
#include "ScreenShot.h"

CMUTImgProcFunc::CMUTImgProcFunc(void)
:m_bOpenDicom(FALSE)
,m_nCurrentFrame(0)
,m_IsFullFrame(FALSE)
,m_fps(0)
{
	setRun(TRUE);
	dwOldTime = ::GetTickCount();
}

CMUTImgProcFunc::~CMUTImgProcFunc(void)
{
}
CMUTImgProcFunc* CMUTImgProcFunc::GetImgProc()
{
	static CMUTImgProcFunc m_ImgProc;//is it a single object?
	return &m_ImgProc;
}
void CMUTImgProcFunc::ReverseMatrix(PBYTE pdata, int nwidth, int nheight)
{
	if (pdata == NULL) return;
	BYTE *pTemp = new BYTE[nwidth];
	for (int i = 0, j = nheight - 1; i<j; i++, j--)
	{
		::CopyMemory(pTemp, pdata + i*nwidth, nwidth);
		::CopyMemory(pdata + i*nwidth, pdata + j*nwidth, nwidth);
		::CopyMemory(pdata + j*nwidth, pTemp, nwidth);
	}
	delete[]pTemp;
}

void CMUTImgProcFunc::OpenDcmImage(LPCTSTR lpszPathName)
{
	DcmFile file;
	file.Load(lpszPathName);
	ImagePixelModule *m_pImgPixel = new ImagePixelModule(file.GetDcmDataset());
	m_hBitmap = m_pImgPixel->GetHBITMAP(0);
	delete m_pImgPixel;

	//return hbmp;

}
BOOL CMUTImgProcFunc::SaveDcmImage(CDC *pDC,CRect rect,CString filename)
{
	//获取文件路径	
	//CString strFilePath.Format(_T("%s"),theApp.GetDcmDirtory());	
	//获取屏幕图像
	CScreenShot scrShot;
	//CRect rect;
	//this->GetClientRect(&rect);
	//rect.right  -= 140;
	theApp.m_pMainWnd->ClientToScreen(&rect);
	HBITMAP hbmpForSave = scrShot.GetScrRectBmp(rect.left, rect.top, rect.right, rect.bottom);
	// 保存图像	
	//CString strExt=_T(".dcm");
	//保存成功标志
	bool bSave = false;	
	do{
		DcmFile file;
		if(!file.Create()) break;
		ImagePixelModule im(file.GetDcmDataset());		
		if(hbmpForSave == NULL) break;
		if(!im.SetHBITMAP(hbmpForSave)) break;
		im.SetPixelAspectRatio(_T("1\\1"));
		//SetDcmInfo(file);//设置dcm文件的其他信息
		if(!file.Save(filename)) break;
		bSave = true;
	}while(false);

	::DeleteObject(hbmpForSave);
	return bSave;
}
void CMUTImgProcFunc::SaveBitmapToDirectFile(CDC* pDC, CRect BitmapSize, int BitCount, CString strFilePath)
{
	CBitmap bmp, *pOldBmp;
	CDC dcMem;
	BITMAP                  bm;
	BITMAPINFOHEADER        bi;
	LPBITMAPINFOHEADER      lpbi;
	DWORD                   dwLen;
	HANDLE                  handle;
	HANDLE                  hDIB;
	HPALETTE                hPal = NULL;


	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, BitmapSize.Width(), BitmapSize.Height());
	pOldBmp = (CBitmap*)dcMem.SelectObject(&bmp);
	dcMem.BitBlt(0, 0, BitmapSize.Width(), BitmapSize.Height(), pDC, BitmapSize.left, BitmapSize.top, SRCCOPY);
	dcMem.SelectObject(pOldBmp);

	if (strFilePath == "")
		return;
	if (hPal == NULL)
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
	GetObject(HBITMAP(bmp), sizeof(BITMAP), &bm);

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = bm.bmWidth * bm.bmHeight * 3;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	int nColors = (1 << bi.biBitCount);
	if (nColors > 256)
		nColors = 0;
	dwLen = bi.biSize + nColors * sizeof(RGBQUAD);
	hPal = SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);
	RealizePalette(pDC->GetSafeHdc());

	hDIB = GlobalAlloc(GMEM_FIXED, dwLen);
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	*lpbi = bi;
	GetDIBits(pDC->GetSafeHdc(),
		HBITMAP(bmp),
		0,
		(DWORD)bi.biHeight,
		(LPBYTE)NULL,
		(LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);
	bi = *lpbi;
	if (bi.biSizeImage == 0)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;
	}
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	GetDIBits(pDC->GetSafeHdc(),
		HBITMAP(bmp),
		0,
		(DWORD)bi.biHeight,
		(LPBYTE)lpbi + (bi.biSize + nColors * sizeof(RGBQUAD)),
		(LPBITMAPINFO)lpbi,
		(DWORD)DIB_RGB_COLORS);


	BITMAPFILEHEADER      hdr;
	hdr.bfType = ((WORD)('M' << 8) | 'B');
	hdr.bfSize = GlobalSize(hDIB) + sizeof(hdr);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + nColors * sizeof(RGBQUAD));
	char* pBmpBuf;
	DWORD FileSize;
	FileSize = sizeof(hdr) + GlobalSize(hDIB);
	pBmpBuf = new char[FileSize];
	memcpy(pBmpBuf, &hdr, sizeof(hdr));
	memcpy(pBmpBuf + sizeof(hdr), lpbi, GlobalSize(hDIB));

	CFile file;
	file.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	file.Write(pBmpBuf, FileSize);
	file.Close();

	delete[] pBmpBuf;

	if (hDIB)
	{
		GlobalFree(hDIB);
	}
	SelectPalette(pDC->GetSafeHdc(), hPal, FALSE);


}
void CMUTImgProcFunc::saveBmpFile(CDC *pDC,CRect rect,CString strFilePath)
{
	this->SaveBitmapToDirectFile(pDC, rect, 32, strFilePath);
}
BOOL CMUTImgProcFunc::SaveSnapShotFile(CDC *pDC,CRect rect,CString filename)
{
	if(NULL == pDC || filename.IsEmpty()) return FALSE;

	saveBmpFile(pDC,rect,filename);


	return TRUE;
}
BOOL CMUTImgProcFunc::GetUsbData(PWORD pData,int &iRows,int &iColums,unsigned long &dwFrame)
{
	if(iRows <= 0 ||iColums <= 0)	return FALSE;
	//pData = new WORD[MAX_FRAM_VALUE];
	pData = getImageData(iRows, iColums, dwFrame);
	//memcpy(pData,pDest,MAX_FRAM_VALUE);

	return TRUE;
}
void CMUTImgProcFunc::CountFPS()
{
	static int count = 0;

	count++;			
	if (count > 10) 
	{
		m_fps = count*1000.0f / (::GetTickCount() - dwOldTime);
		dwOldTime = ::GetTickCount();
		count = 0;
	}
}

void CMUTImgProcFunc::ProcessGetData(CMUTDibFunc &curdib,PBYTE pData,CRect dstRect)
{
	if(NULL == pData && getHardwareExist())  return;

	CMUTDibFunc dib(IMG_DIS_WIDTH, IMG_DIS_HEIGHT);			//nDstWidth nDstHeight已发生变化

	int nDstWidth = dstRect.Width();
	int nDstHeight = dstRect.Height();

	CMUTDibFunc dibDst(nDstWidth, nDstHeight);
	Process(dibDst.GetBits(), dibDst.GetPitch(), dibDst.GetHeight(), (unsigned short*)pData, dib.GetPitch(), dib.GetHeight());
	m_dib = dibDst;
	ReverseMatrix(m_dib.GetBits(), m_dib.GetPitch(), m_dib.GetHeight());
	curdib = m_dib;
}
// void CMUTImgProcFunc::GetImage(CRect rect)
// {
// 	static int count = 0;
// 	int nSrcWidth = IMG_DIS_WIDTH;
// 	int nSrcHeight = IMG_DIS_HEIGHT;
// 	unsigned long dwFrame;
// 	unsigned short *pdata = getImageData(nSrcWidth, nSrcHeight, dwFrame);
// 	if (pdata != NULL) 
// 	{
// 		if (!m_olddib.IsEmpty()) 
// 		{
// 			m_movie[m_nCurrentFrame] = m_olddib;
// 			if (m_nCurrentFrame == MOV_MAX_FRAME) 
// 			{
// 				m_IsFullFrame = true;
// 			}
// 			m_nCurrentFrame = (m_nCurrentFrame + 1) % MOV_MAX_FRAME;
// 
// 			if (m_IsFullFrame) 
// 			{
// 				m_nStartFrame = m_nCurrentFrame;
// 			}
// 		}
// 		count++;			//帧频计算
// 		if (count > 10) 
// 		{
// 			m_fps = count*1000.0f / (::GetTickCount() - dwOldTime);
// 			dwOldTime = ::GetTickCount();
// 			count = 0;
// 		}
// 	}
// 	else if (pdata == NULL && getHardwareExist()) {				//不能有虚拟数据
// 		if (!m_IsPlayMovie) {		//???
// 			m_fps = 0;
// 			m_dib = m_olddib;
// 		}
// 		else {
// 			m_dib = m_movie[m_nStartFrame];
// 			//m_nStartFrame = (m_nStartFrame + 1) % MOV_MAX_FRAME;
// 			if(++ m_nStartFrame >= MOV_MAX_FRAME)
// 			{
// 				m_nStartFrame = 0;
// 				m_IsPlayMovie = FALSE;
// 			}
// 		}
// 		return;
// 	}
// 
// 	CMUTDibFunc dib(IMG_DIS_WIDTH, IMG_DIS_HEIGHT);			//nDstWidth nDstHeight已发生变化
// 
// 	int nDstWidth = rect.Width();
// 	int nDstHeight = rect.Height();
// 
// 	CMUTDibFunc dibDst(nDstWidth, nDstHeight);
// 	Process(dibDst.GetBits(), dibDst.GetPitch(), dibDst.GetHeight(), pdata, dib.GetPitch(), dib.GetHeight());
// 	m_dib = dibDst;
// 	ReverseMatrix(m_dib.GetBits(), m_dib.GetPitch(), m_dib.GetHeight());
// 	m_olddib = m_dib;
// 
// 	//this->OnPaint();
// }
void CMUTImgProcFunc::DrawImage(CDC *dc,CRect rect,BOOL bFlipImage)
{
	//CFont font;
	//font.CreatePointFont(98, _T("宋体"));
	//CFont *poldfont = dc->SelectObject(&font);
	CMUTMeDCFunc memdc(dc, rect,-1);

	memdc.FillSolidRect(&rect, RGB(0, 0, 0));
	memdc.SetTextColor(APP_TEXT_COLOR1);
	memdc.SetBkMode(TRANSPARENT);
	//memdc.SelectObject(&font);

	this->DrawRuler(dc, rect,IMG_RULER_H);
	this->DrawRuler(dc, rect,IMG_RULER_W);

	if (m_dib.IsEmpty()) 
	{
		this->DrawAngle(&memdc, rect,bFlipImage);
		memdc.ExeDC();
		DeleteSpareImage(dc,rect);
		return;
	}

	if (m_bOpenDicom)
	{
		CBitmap memBmp;
		memBmp.CreateCompatibleBitmap(dc, rect.Width(), rect.Height());
		memdc.SelectObject(m_hBitmap);
		//dc->BitBlt(rect.left,rect.top, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
		memBmp.DeleteObject();
	}
	else
	{
		m_dib.BitBlt(memdc.m_hDC, 0, 0,SRCCOPY, FALSE, bFlipImage);
	}

	this->DrawAngle(&memdc, rect,bFlipImage);
	memdc.ExeDC();
	DeleteSpareImage(dc,rect);

}
void CMUTImgProcFunc::drawVideo(CDC *dc,CRect rect)
{
	//CPaintDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(dc);

	dc->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);


}
void CMUTImgProcFunc::DrawAngle(CMUTMeDCFunc *dc,CRect rect,BOOL bIsFlipImage)		//以memdc作为原始dc
{
	
	CPen pen(PS_SOLID, 1, APP_TEXT_COLOR1);
	CPen *pOldPen = dc->SelectObject(&pen);
	int iTriWidth = 6;
	int iTriHeight = 6;

	if(bIsFlipImage)
	{
		int iTriStartCx = rect.Width()-iTriWidth-10;			//
		int iTriStartCy = 0+2;//rect.top

		CPoint point[3]={CPoint(iTriStartCx,iTriStartCy)
			,CPoint(iTriStartCx,iTriStartCy+iTriHeight)
			,CPoint(iTriStartCx+iTriWidth,iTriStartCy+iTriHeight/2)};
		if(!dc->Polygon(point,3))
			int xi = 0;
	}
	else
	{
		int iTriStartCx = 0+10;//rect.left
		int iTriStartCy = 0+2;//rect.top

		CPoint point[3]={CPoint(iTriStartCx+iTriWidth,iTriStartCy)
			,CPoint(iTriStartCx+iTriWidth,iTriStartCy+iTriHeight)
			,CPoint(iTriStartCx,iTriStartCy+iTriHeight/2)};

		dc->Polygon(point,3);
	}

	//rect.DeflateRect(40,40);
	//dc.RoundRect(&rect,CPoint(8,8));
	

	dc->SelectObject(pOldPen);
/*	pDC->SelectObject(oldpen);*/
}

void CMUTImgProcFunc::DrawRuler(CDC *dc, CRect &rect,UINT uType)
{
	CRect nowRect;
	if(uType == IMG_RULER_H)
	{
		nowRect.CopyRect(&rect);
		nowRect.left = nowRect.right;
		nowRect.right = nowRect.left + IMG_HRULER_RGN;
	}
	else if(uType == IMG_RULER_W)
	{
		nowRect.CopyRect(&rect);
		nowRect.top = nowRect.bottom;
		nowRect.bottom = nowRect.top + IMG_WRULER_RGN;
	}

	CMUTMeDCFunc  memdc(dc,nowRect,APP_BK_COLOR1);	
	//刻度尺 单位
	const float m_fPixelPerMM = (float)1.0;
	if (m_fPixelPerMM < 0) return;
	const UINT	PixerPerCM = (UINT)(m_fPixelPerMM * 10.0);		 //每厘米步进多少个像素点	
	const UINT fstep =  PixerPerCM*2;
	const UINT nSpace = 5;
	UINT  xcm = 0; 
	int yPos = 0;//rect.Height()+10;
	int xPos = 0;//rect.Width() / 2;
	int count = 0;
	CPen pen(PS_SOLID, 1, APP_TEXT_COLOR1);
	CPen *pOldPen = memdc.SelectObject(&pen);

	if(uType == IMG_RULER_H)						//======绘制纵向标尺
	{
		for (float fy = 0; fy<rect.Height(); fy += fstep)
		{
			int y = (int)(yPos+fy+0.5f);
			memdc.MoveTo(xPos, y); memdc.LineTo(xPos+3, y);
			if (count % nSpace == 0)
			{
				memdc.MoveTo(xPos, y - 1); memdc.LineTo(xPos+5, y - 1);
				memdc.MoveTo(xPos, y);   memdc.LineTo(xPos+5, y);
				memdc.MoveTo(xPos, y + 1); memdc.LineTo(xPos+5, y + 1);
				memdc.SetTextColor(APP_TEXT_COLOR1);
				CString str;
				str.Format(_T("%dcm"),xcm++);
				memdc.TextOut(xPos,y+2,str);
			}
			count++;
		}
	}
	else if(uType == IMG_RULER_W)					//=====绘制横向标尺
	{
		count = 0;
		xPos = 2;
		yPos = 0;
		for (float fx = 0; fx<rect.Width(); fx += fstep)
		{
			int x = int(fx + 0.5f);
			memdc.MoveTo(xPos + x, yPos); memdc.LineTo(xPos + x, yPos + 3);
			//memdc.MoveTo(xPos - x, yPos); memdc.LineTo(xPos - x, yPos + 3);

			if (count % nSpace == 0)
			{
				memdc.MoveTo(xPos + x - 1, yPos); memdc.LineTo(xPos + x - 1, yPos + 5);
				memdc.MoveTo(xPos + x, yPos); memdc.LineTo(xPos + x, yPos + 5);
				memdc.MoveTo(xPos + x + 1, yPos); memdc.LineTo(xPos + x + 1, yPos + 5);
			}
			count++;
		}
	}
	
	memdc.SelectObject(pOldPen);  //selectobject 产生临时对象
	pen.DeleteObject();
	memdc.ExeDC();
}

void CMUTImgProcFunc::DeleteSpareImage(CDC *dc, CRect rect)
{
	CRect curRect;
	static CRect oldRect;
	curRect.CopyRect(&rect);
	curRect.DeflateRect(&oldRect);
	if(curRect.bottom < 0)
	{
		CBrush brush;
		brush.CreateSolidBrush(APP_BK_COLOR1);
		CRect temp(oldRect.left,rect.bottom,oldRect.right+IMG_HRULER_RGN,oldRect.bottom+IMG_WRULER_RGN);
		dc->FillRect(temp,&brush);
		brush.DeleteObject();
	}
	oldRect.CopyRect(&rect);
}
