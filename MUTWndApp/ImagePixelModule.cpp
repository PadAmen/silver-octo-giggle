#include "StdAfx.h"
#include "ImagePixelModule.h"

ImagePixelModule::ImagePixelModule(DcmDataset *pDataset):DcmModuleBase(pDataset)
{
	DcmRLEDecoderRegistration::registerCodecs(OFFalse /*pCreateSOPInstanceUID*/,  OFTrue );
	if(pDataset != NULL)
		m_pdcmimage = new DicomImage(pDataset, pDataset->getOriginalXfer());
	else 
		m_pdcmimage = NULL;
}

ImagePixelModule::~ImagePixelModule(void)
{
	delete m_pdcmimage;
	DcmRLEDecoderRegistration::cleanup();
}


bool ImagePixelModule::SetImageData(const void *pData, unsigned long nSizeInByte)
{
	if(pDataset == NULL || pData==NULL || nSizeInByte <=0) return false;	//
	pDataset->putAndInsertUint8Array(DCM_PixelData, (unsigned char*) pData, nSizeInByte);
	return true;
}

bool ImagePixelModule::GetImageColorType(string &strType)
{
	if(pDataset == NULL) return false;
	OFString strColorType;
	if(!pDataset->findAndGetOFString(DCM_PhotometricInterpretation,strColorType).good())
		return false;
	strType = strColorType.c_str();
	return true;
}

bool ImagePixelModule::GetPattleTable(vector<tagRGBQUAD> &pal)
{
	if(pDataset == NULL) return false;
	unsigned short palcount;
	palcount = 256;
	unsigned long count;
	const unsigned short *pRedPal = NULL;
	const unsigned short *pGreenPal = NULL;
	const unsigned short *pBluePal = NULL;
	while(1)
	{
		if(!pDataset->findAndGetUint16Array(DCM_RedPaletteColorLookupTableData,pRedPal, &count).good()) break;	
		if(count <= 0) break;
		if(!pDataset->findAndGetUint16Array(DCM_GreenPaletteColorLookupTableData,pGreenPal, &count).good()) break;
		if(count <= 0) break;
		if(!pDataset->findAndGetUint16Array(DCM_BluePaletteColorLookupTableData,pBluePal, &count).good()) break;
		if(count <= 0) break;
		break;
	}

	pal.resize(count);
	for(unsigned long i=0; i<count; i++)
	{
		pal[i].rgbBlue  = pBluePal[i]>>8;
		pal[i].rgbGreen = pGreenPal[i]>>8;
		pal[i].rgbRed   = pRedPal[i]>>8;
		pal[i].rgbReserved = 0;
	}						
	return true;
}
/*
Enumerated Values:
0 = The sample values for the first pixel are followed by the sample values for the second pixel, etc.
For RGB images, this means the order of the pixel values sent shall be R1, G1, B1, R2, G2, B2, ..., etc.
1 = Each color plane shall be sent contiguously. For RGB images, 
this means the order of the pixel values sent is R1, R2, R3, ..., G1, G2, G3, ..., B1, B2, B3, etc. 
*/
bool ImagePixelModule::GetPlanarConfiguration(WORD &val)
{
	if(pDataset == NULL) return false;
	return pDataset->findAndGetUint16(DCM_PlanarConfiguration,val).good();
}

// bool ImagePixelModule::SetPlanarConfiguration(WORD val)
// {
// 	if(pDataset == NULL) return false;
// 	return pDataset->findAndGetUint16(DCM_PlanarConfiguration,val).good();
// }

/*

bool ImagePixelModule::SetImageInfo(unsigned int width, unsigned int height, BYTE depth, BYTE channel)
{
	if(pDataset == NULL) return false;
	if(channel != 1 && channel!=3) return false;
	pDataset->putAndInsertString(DCM_PhotometricInterpretation, channel > 1 ? "RGB" : "PALETTE COLOR");	
	if(channel > 1){
		pDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);//默认使用rgb,rgb,..
	}
	pDataset->putAndInsertUint16(DCM_SamplesPerPixel, channel);
	pDataset->putAndInsertUint16(DCM_BitsAllocated, depth);
	pDataset->putAndInsertUint16(DCM_BitsStored, depth);
	pDataset->putAndInsertUint16(DCM_HighBit, depth-1);
	pDataset->putAndInsertUint16(DCM_PixelRepresentation,0);//是否为有符号数
	pDataset->putAndInsertUint16(DCM_Rows,	height);
	pDataset->putAndInsertUint16(DCM_Columns, width);
	return true;
}*/

/*
bool ImagePixelModule::GetImageInfo(unsigned short &width, unsigned short &height)
{
	if(pDataset == NULL) return false;
	do 
	{
		if(!pDataset->findAndGetUint16(DCM_Rows,height).good()) break;
		if(!pDataset->findAndGetUint16(DCM_Columns,width).good()) break;
	} while (false);
	return true;
}*/

bool ImagePixelModule::GetDepth(unsigned short &depth){
	if(pDataset == NULL) return false;
	return pDataset->findAndGetUint16(DCM_BitsAllocated, depth).good();

}
bool ImagePixelModule::GetChannel(unsigned short &channel)
{	
	if(pDataset == NULL) return false;
	return pDataset->findAndGetUint16(DCM_SamplesPerPixel, channel).good();	
}
bool ImagePixelModule::GetWidth(unsigned short &width)
{
	if(pDataset == NULL) return false;
	return pDataset->findAndGetUint16(DCM_Columns, width).good();	
}
bool ImagePixelModule::GetHeight(unsigned short &height)
{
	if(pDataset == NULL) return false;
	return pDataset->findAndGetUint16(DCM_Rows, height).good();	
}


bool ImagePixelModule::SetPalette(const tagRGBQUAD *pPalette, int count){
	
	if(pDataset == NULL) return false;
	//16位或者8位位图需要调色板
	//put color lookup table
	unsigned short pal[3]={256, 0, 16};
	pDataset->putAndInsertUint16Array(DCM_RedPaletteColorLookupTableDescriptor,pal,3);
	pDataset->putAndInsertUint16Array(DCM_GreenPaletteColorLookupTableDescriptor,pal,3);
	pDataset->putAndInsertUint16Array(DCM_BluePaletteColorLookupTableDescriptor,pal,3);

	vector<unsigned short> pRedPal(count),pGreenPal(count),pBluePal(count);
	for(int i=0; i<count; i++)
	{
		pRedPal[i]	= pPalette[i].rgbRed<<8;
		pGreenPal[i]= pPalette[i].rgbGreen<<8;
		pBluePal[i]	= pPalette[i].rgbBlue<<8;
	}
	pDataset->putAndInsertUint16Array(DCM_RedPaletteColorLookupTableData,   &pRedPal[0],   count);
	pDataset->putAndInsertUint16Array(DCM_GreenPaletteColorLookupTableData, &pGreenPal[0], count);
	pDataset->putAndInsertUint16Array(DCM_BluePaletteColorLookupTableData,  &pBluePal[0],  count);
	return true;
}

bool ImagePixelModule::SetPixelAspectRatio(LPCTSTR lpszRatio)
{
	return SetDcmString(DCM_PixelAspectRatio, lpszRatio);
}

bool ImagePixelModule::SetNumberOfFrames(int nCount)
{
	if(pDataset == NULL) return false;
	char szTemp[30];
	sprintf_s(szTemp,  30, "%d", nCount);
	return pDataset->putAndInsertString(DCM_NumberOfFrames, szTemp).good();
}
bool ImagePixelModule::SetFrameIncrementPointer(unsigned int nAdd)
{
	if(pDataset == NULL) return false;
	return pDataset->putAndInsertUint32(DCM_FrameIncrementPointer, nAdd).good();
}
bool ImagePixelModule::GetNumberOfFrames(int &count)//帧数
{
	if(pDataset == NULL) return false;
	const char *szTemp = NULL;
	if(pDataset->findAndGetString(DCM_NumberOfFrames, szTemp).good())
	{
		count = atoi(szTemp);
		return true;
	}
	return false;
}
bool ImagePixelModule::GetFrameIncrementPointer(DWORD &nAdd)//每帧数据指针地址增量
{
	if(pDataset == NULL) return false;
	if(pDataset->findAndGetUint32(DCM_FrameIncrementPointer, (Uint32)nAdd).good())
	{
		return true;
	}
	return false;
}

/*

bool ImagePixelModule::rgb2bgr(BYTE *pDst, int nSizeDst, const BYTE *pSrc, int nSizeSrc, int nWidth)
{
	if(pDst == NULL || pSrc == NULL) return false;
	int nDstWidthBytes = (nWidth*3+3)/4*4;
	int nSrcWidthBytes = nWidth*3;
	if(nSizeDst % nDstWidthBytes != 0) return false;
	if(nSizeSrc % nSrcWidthBytes != 0) return false;
	if(nSizeDst < nSizeSrc)  return false;
	const int nheight = nSizeSrc/nSrcWidthBytes;
	for(int y=0; y<nheight; y++)
	{
		BYTE *pDstLine = pDst+y*nDstWidthBytes;
		const BYTE *pSrcLine = pSrc+y*nSrcWidthBytes;
		for(int x=0; x<nWidth; x++)
		{
			pDstLine[x*3+0] = pSrcLine[x*3+2];
			pDstLine[x*3+1] = pSrcLine[x*3+1]; 
			pDstLine[x*3+2] = pSrcLine[x*3+0]; 
		}
	}
	return true;
}*/

bool ImagePixelModule::r1r2r3_2_r1g1b1(BYTE *pDst, const BYTE *pSrc, int nSize )
{
	if(pSrc == NULL || pDst == NULL) return false;
	if(nSize % 3 != 0 || nSize <= 0) return false;
	const int nLineCount = nSize/3;
	for(long i=0; i<nLineCount; i++)
	{
		pDst[i*3+0] = pSrc[i];
		pDst[i*3+1] = pSrc[i+nLineCount*1];
		pDst[i*3+2] = pSrc[i+nLineCount*2];
	}
	return true;
}

/*
@brief 将24位hbitmap格式的bgr数据转换成24位dcm格式的rgb图像数据,\
	这是因为hbitmap图像数据的每行是32位对齐的,而dicom图像中不对齐,故需要作特列转换
@param pDataHbmp 24位hbitmap的图像数据,数据长度必须是 (nWidth*3+3)/4*4)*height
@param pDataDcm  24位dicom图像的数据,可用的长度 nwidth*3*height
@param nWidth  图像宽度 
@param nHeight 图像高度
@remark 此函数只适用于24位图像数据,使用前务必保证pDataHbmp长度为:(nWidth*3+3)/4*4)*height,
	    pDataDcm 长度为nwidth*3*height
*/
void ImagePixelModule::hbmp24bgr_2_dcm24rgb( BYTE *pDataDcm, const BYTE *pDataHbmp, int nWidth, int nHeight)
{
	int nWidthStepHbmp = (nWidth*3+3)/4*4;
	int nWidthStepDcm = nWidth*3;
	const BYTE *pLineHbmp = NULL;
	BYTE *pLineDcm = NULL;
	for(int y=0; y<nHeight; y++)
	{
		pLineHbmp = pDataHbmp+y*nWidthStepHbmp;
		pLineDcm  = pDataDcm +y*nWidthStepDcm;
		for(int x=0; x<nWidth; x++)
		{
			pLineDcm[x*3+2] = pLineHbmp[x*3+0];
			pLineDcm[x*3+1] = pLineHbmp[x*3+1];
			pLineDcm[x*3+0] = pLineHbmp[x*3+2];
		}
	}
}

bool ImagePixelModule::GetImageDataOriginal(void *pdata, unsigned long nBytesMax)
{
	if(pdata == NULL ) return false;
	unsigned long nImageSize = 0;
	const unsigned char *pImageData = NULL;
	if(pDataset->findAndGetUint8Array(DCM_PixelData, pImageData, &nImageSize).good())
	{
		if(nBytesMax < nImageSize) return false;
		::CopyMemory(pdata, pImageData, nImageSize);
		return true;
	}
	return false;
}

bool  ImagePixelModule::Get24BitBGRData(BYTE *pImageData, unsigned long nBytesMax, int nFramePos)
{
	if(pImageData == NULL) return false;
	if(nFramePos < 0 || nFramePos > (int)(m_pdcmimage->getFrameCount())) return false;
	if( m_pdcmimage->createWindowsDIB((void*&)pImageData, nBytesMax, nFramePos ) <= 0 )
		return false;
	return true;
}

HBITMAP ImagePixelModule::GetHBITMAP(int nFramePos)//读取dcm图像,返回一个HBITMAP对象
{
	if(pDataset == NULL) return NULL;
	if(nFramePos < 0 ) return NULL;
	if(m_pdcmimage == NULL) return NULL;
	if(m_pdcmimage->getStatus() != EIS_Normal) return NULL;
	bool  bReadRes = false;	
	HDC hdc = ::GetDC(NULL);
	HBITMAP hbmp = NULL;
	do
	{
		unsigned short nwidth, nheight,nChannel, nDepth;
		nwidth = (unsigned short)m_pdcmimage->getWidth();
		nheight = (unsigned short)m_pdcmimage->getHeight();
		nDepth = 8;
		nChannel = 3;
		BITMAPINFOHEADER infoheader;
		BITMAPINFOHEADER *bih = (BITMAPINFOHEADER*)&infoheader;
		::ZeroMemory(bih, sizeof(BITMAPINFOHEADER));
		bih->biSize			= sizeof(BITMAPINFOHEADER);
		bih->biWidth		= nwidth;
		bih->biHeight		= -nheight;
		bih->biPlanes		= 1;
		bih->biBitCount		= nChannel * 8;
		bih->biCompression	= BI_RGB;
		bih->biBitCount     = nChannel * 8;
		bih->biSizeImage    = ((nwidth*3+3)/4*4)*nheight;		
		BYTE *pImageData=NULL;
		hbmp = ::CreateDIBSection(NULL, (LPBITMAPINFO)&infoheader, DIB_RGB_COLORS, (VOID**)&pImageData, NULL, 0);
		if(!hbmp) break;
		if( m_pdcmimage->createWindowsDIB((void*&)pImageData, infoheader.biSizeImage, nFramePos ) <= 0 ) break;
		bReadRes = true;
		break;
	}while(false);
	::ReleaseDC(NULL, hdc);
	//读取失败, 释放对象
	if(!bReadRes) {
		::DeleteObject(hbmp);
		hbmp = NULL;
	}
	return hbmp;
}

bool ImagePixelModule::GetHBITMAPData(HBITMAP hbmp, BITMAPINFOHEADER *pInfoHeader, vector<tagRGBQUAD> &pal, vector<BYTE> &buffer)
{
	if(hbmp == NULL || pInfoHeader == NULL) return false;
	bool bGet = false;
	HDC hdc = ::GetDC(NULL);
	do{		
		BITMAP bmp;
		DWORD dwPaletteSize = 0;
		::GetObject(hbmp, sizeof(bmp), &bmp);
		if (bmp.bmBitsPixel <= 8){
			dwPaletteSize = ((DWORD)(1<<bmp.bmBitsPixel))*sizeof(tagRGBQUAD);
		} 
		vector<BYTE> headinfo(sizeof(BITMAPINFOHEADER) + dwPaletteSize);
		BITMAPINFOHEADER *pbih = (BITMAPINFOHEADER*)&headinfo[0];
		pbih->biSize = sizeof(BITMAPINFOHEADER);
		if(0==::GetDIBits(hdc, hbmp, 0, 1, NULL, (LPBITMAPINFO) pbih, DIB_RGB_COLORS)) break;
		pbih->biCompression = BI_RGB;	
		buffer.resize(pbih->biSizeImage);
		if(0==::GetDIBits(hdc, hbmp, 0, pbih->biHeight, &buffer[0],(LPBITMAPINFO) pbih, DIB_RGB_COLORS)) break;		
		//上下翻转图像
		unsigned int nWidthStep = pbih->biSizeImage/pbih->biHeight;
		vector<BYTE> temp(nWidthStep);
		for(int i=0, j=pbih->biHeight-1; i<j; i++,j--){
			::CopyMemory(&temp[0],              &buffer[i*nWidthStep], nWidthStep);
			::CopyMemory(&buffer[i*nWidthStep], &buffer[j*nWidthStep], nWidthStep);
			::CopyMemory(&buffer[j*nWidthStep], &temp[0],              nWidthStep);
		}
		//复制内容
		::CopyMemory(pInfoHeader, &headinfo[0], sizeof(BITMAPINFOHEADER));
		if(dwPaletteSize > 0) {
			pal.resize(dwPaletteSize/sizeof(tagRGBQUAD));
			::CopyMemory(&pal[0], &headinfo[sizeof(BITMAPINFOHEADER)], dwPaletteSize);
		}
		bGet = true;
	}while(false);
	::ReleaseDC(NULL, hdc);
	return bGet;

}

//将4通道图像数据转换成3通道数据,并且将bgr转换成rgb
void bgr2rgb(vector<BYTE> &dataDst, vector<BYTE> &dataSrc, int nWidthBytes, int nWidth, int nChannel)
{
	assert(dataSrc.size() > 0 && dataSrc.size()%nWidthBytes == 0);
	assert(nWidthBytes >= nWidth*nChannel);
	int nheight = (int)(dataSrc.size()/nWidthBytes);
	int nWidthBytesDst = (nWidth*3);//DICOM图像数据不需要宽度是4的整数倍
	dataDst.resize(nWidthBytesDst*nheight);
	for(int y=0; y<nheight; y++)
	{
		BYTE *pLineSrc = &dataSrc[y*nWidthBytes];
		BYTE *pLineDst = &dataDst[y*nWidthBytesDst];
		for(int x=0; x<nWidth; x++)
		{
			pLineDst[x*3+2] = pLineSrc[x*nChannel+0];
			pLineDst[x*3+1] = pLineSrc[x*nChannel+1];
			pLineDst[x*3+0] = pLineSrc[x*nChannel+2];
		}
	}
}

bool ImagePixelModule::SetImage24Bit(int nWidth, int nHeight, const void *pData, int nFrameCount/*=1*/)
{
	if(NULL == pData) return false;
	bool bRes = false;
	do{	
		if(nFrameCount < 1) break;
		if(nHeight <= 0)    break;
		if(nWidth <=0)      break;		
		int nChannel = 3;
		int nDepth   = 8;
		int nWidthBytes = (nFrameCount > 1) ? nWidth*3 : (nWidth*3+3)/4*4;		
		if(!this->SetImageData(pData, nWidthBytes*nHeight*nFrameCount)) break;		
		//设置图像信息
		pDataset->putAndInsertString(DCM_PhotometricInterpretation, "RGB");	
		pDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);//默认使用rgb,rgb,..		
		pDataset->putAndInsertUint16(DCM_SamplesPerPixel, nChannel);
		pDataset->putAndInsertUint16(DCM_BitsAllocated, nDepth);
		pDataset->putAndInsertUint16(DCM_BitsStored, nDepth);
		pDataset->putAndInsertUint16(DCM_HighBit, nDepth-1);
		pDataset->putAndInsertUint16(DCM_PixelRepresentation,0);//是否为有符号数
		pDataset->putAndInsertUint16(DCM_Rows,	  (unsigned short)nHeight);
		pDataset->putAndInsertUint16(DCM_Columns, (unsigned short)nWidth);
		if(nFrameCount > 1)
		{
			this->SetNumberOfFrames(nFrameCount);
		}
		bRes = true;
	}while(false);
	return bRes;
}

bool ImagePixelModule::SetHBITMAP(HBITMAP hbmp)
{
	if(hbmp == NULL) return false;
	if(pDataset == NULL) return false;
	bool bRes = false;
	do{
		BITMAPINFOHEADER infoheader;
		vector<tagRGBQUAD> pal;
		vector<BYTE> imagedata;
		//读取图像信息及数据		
		if( !GetHBITMAPData(hbmp, &infoheader, pal, imagedata) ) break;
		if(infoheader.biHeight <= 0) break;
		if(infoheader.biWidth <=0) break;
		if(infoheader.biBitCount % 8 != 0) break;
		int nChannel = infoheader.biBitCount/8;
		int nDepth = infoheader.biBitCount < 24 ? infoheader.biBitCount : 8;
		int nWidthBytes = infoheader.biSizeImage/infoheader.biHeight;		
		if(nChannel >= 3)	{
			//需要将abrg,bgr数据转换成rgb数据
			vector<BYTE> imageRGB;
			bgr2rgb(imageRGB, imagedata, nWidthBytes, infoheader.biWidth, nChannel);
			if(!this->SetImageData(&imageRGB[0],(unsigned long)(imageRGB.size()) )) break;
			if(nChannel==4){ nChannel = 3;	}
		}else{
			if(!this->SetImageData(&imagedata[0], (unsigned long) imagedata.size())) break;
		}
		//设置图像信息
		pDataset->putAndInsertString(DCM_PhotometricInterpretation, nChannel > 1 ? "RGB" : "PALETTE COLOR");	
		if(nChannel > 1)	{
			pDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);//默认使用rgb,rgb,..
		}else if(nChannel == 1){
			if(!this->SetPalette(&pal[0], (int)(pal.size()))) break;//设置调色板
		}	
		pDataset->putAndInsertUint16(DCM_SamplesPerPixel, nChannel);
		pDataset->putAndInsertUint16(DCM_BitsAllocated, nDepth);
		pDataset->putAndInsertUint16(DCM_BitsStored, nDepth);
		pDataset->putAndInsertUint16(DCM_HighBit, nDepth-1);
		pDataset->putAndInsertUint16(DCM_PixelRepresentation,0);//是否为有符号数
		pDataset->putAndInsertUint16(DCM_Rows,	  (unsigned short)infoheader.biHeight);
		pDataset->putAndInsertUint16(DCM_Columns, (unsigned short)infoheader.biWidth);		
		bRes = true;
	}while(false);
	return bRes;
}