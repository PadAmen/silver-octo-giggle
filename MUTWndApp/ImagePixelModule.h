#pragma once
#include "DcmModuleBase.h"
//#include "../Image/dcmtk-3.5.4-win32-i386/include/dcmtk/dcmimgle/dcmimage.h"
class _declspec(dllexport) ImagePixelModule: public DcmModuleBase
{
public:
	/*!
	@brief 将rgb格式的颜色数据转换成bgr模式
	@param pDst nSizeDst
	@param pSrc nSizeSrc
	@return nWidth
	@remark
	*/
	//static bool rgb2bgr(BYTE *pDst, int nSizeDst, const BYTE *pSrc, int nSizeSrc, int nWidth);
	/*!
	@brief 将r1,r2,r3..rn,g1,g2..b1,b2..格式的数据转换成r1,g1,b1,r2,g2,b2...格式
	@param pDst 目标数据区大小
	@param pSrc 源数据区大小
	@return nSize  数据大小,必须是3的整数倍
	@remark nSize 必须是3的整数倍
	*/
	static bool r1r2r3_2_r1g1b1(BYTE *pDst, const BYTE *pSrc, int nSize );
	/*!
	@brief 将24位hbitmap格式的数据转换成24位dcm格式的图像数据,\
	这是因为hbitmap图像数据的每行是32位对齐的,而dicom图像中不对齐,故需要作特列转换
	@param pDataHbmp 24位hbitmap的图像数据,数据长度必须是 (nWidth*3+3)/4*4)*height
	@param pDataDcm  24位dicom图像的数据,可用的长度 nwidth*3*height
	@param nWidth  图像宽度 
	@param nHeight 图像高度
	@remark 此函数只适用于24位图像数据,使用前务必保证pDataHbmp长度为:(nWidth*3+3)/4*4)*height,
	pDataDcm 长度为nwidth*3*height
	*/
	static void hbmp24bgr_2_dcm24rgb( BYTE *pDataDcm, const BYTE *pDataHbmp, int nWidth, int nHeight);
public:
	ImagePixelModule(DcmDataset *pDataset);
	virtual ~ImagePixelModule(void);
protected:
	ImagePixelModule(const ImagePixelModule&);
	ImagePixelModule&operator=(const ImagePixelModule&);
public:
	//========================Get ===========================
	bool GetImageData(BYTE *pdata, unsigned long nBytesMax);
	bool GetPlanarConfiguration(WORD &val);
	bool GetDepth(unsigned short &depth);
	bool GetChannel(unsigned short &channel);
	bool GetWidth(unsigned short &width);
	bool GetHeight(unsigned short &height);

	bool GetImageColorType(string &strType);
	bool GetPattleTable(vector<tagRGBQUAD> &pal);
	bool GetImageDataOriginal(void *pdata, unsigned long  nBytesMax);//!<获取最原始的图像数据,未作任何处理
	/*!
	@brief 获取一帧图像,返回的hbitmap对象需要调用者手动释放
	@param nFramePos 如果此文件是多幅图像,nFramePos指代电影的n位置(从0开始)
	@return 如果成功返回句柄,否则返回NULL
	@remark 务必手动释放返回的HBITMAP 句柄 
	*/
	HBITMAP GetHBITMAP(int nFramePos=0);
	//single frame
	bool  Get24BitBGRData(BYTE *pdata, unsigned long nBytesMax, int nFramePos = 0);
	//multiframe
	bool GetNumberOfFrames(int &count);//帧数
	bool GetFrameIncrementPointer(DWORD &nAdd);//每帧数据指针地址增量
	bool GetFrameTime();//帧间隔时间//Normal time per frame in millisecond
	bool GetRecommendedDisplayFrameRate(int n);//in frames per second
public:
	//========================set ===========================
	bool SetWidth(unsigned short width);//!< 设置图像宽度
	bool SetHeight(unsigned short nwith);//!< 设置图像高度
	bool SetChannel(unsigned short nchannel);//!< 设置图像通道数
	bool SetDepth(unsigned short nDepth);//!< 设置图像深度
	/*!
	@brief 设置图像的调色板,此函数仅当8位图时有效
	@param pPal  调色板指针
	@param count 调色板的tagRGBQUAD个数
	*/
	bool SetPalette(const tagRGBQUAD* pPal, int count);
	/*!
	@brief 只设置图像数据,
	@param pdata 图像数据指针
	@param nbytes 图像数据的长度
	@return 设置成功返回true, 否则返回false
	*/
	bool SetImageData(const void *pdata, unsigned long nbytes);
	/*!
	@brief s设置图像的长度,宽度,位数等相关属性,并设置数据
	@param hbmp 图像句柄,仅可支持8位,24位rgb位图
	@reutrn  return true if successed
	*/ 
	bool SetHBITMAP(HBITMAP hbmp);//!<设置图像,不支持16位位图
	/*!
	@brief 设置图像的长度,宽度,位数等相关属性,并设置数据
	@param nwidth  图像宽度
	@param nheight  图像高度
	@param pData   数据指针
	@param nFrameCount 图像帧数
	@return 设置成功返回true, 否则返回false
	@remark 必须保证pdata的长度lenth为(nwidth*3+3)/4*4)*nheight,宽度不需要4字节对齐
	*/
	bool SetImage24Bit(int nwidth, int nheight, const void *pData, int nFrameCount=1);//pdata'lenth = (nwidth*3+3)/4*4)*nheight
	//multframe
	bool SetNumberOfFrames(int nCount);//!< 设置电影帧数
	bool SetFrameIncrementPointer(unsigned int nAdd);//
	bool SetFrameTime(float fFrameTime);//!< 设置帧率
	/*!
	@brief Pixel Aspect Ratio = Vertical Size \ Horizontal Size = 0.30 mm \0.25 mm. 
	      Thus the Pixel Aspect Ratio could be represented as the multivalued integer string "6\5", "60\50",
		  or any equivalent integer ratio.
	*/
	bool SetPixelAspectRatio(LPCTSTR lpszRatio);
protected:
	bool GetHBITMAPData(HBITMAP hbmp, BITMAPINFOHEADER *pInfoHeader, vector<tagRGBQUAD> &pal, vector<BYTE> &buffer);
protected:
	DicomImage *m_pdcmimage;
};
