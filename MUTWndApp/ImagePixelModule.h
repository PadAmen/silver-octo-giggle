#pragma once
#include "DcmModuleBase.h"
//#include "../Image/dcmtk-3.5.4-win32-i386/include/dcmtk/dcmimgle/dcmimage.h"
class _declspec(dllexport) ImagePixelModule: public DcmModuleBase
{
public:
	/*!
	@brief ��rgb��ʽ����ɫ����ת����bgrģʽ
	@param pDst nSizeDst
	@param pSrc nSizeSrc
	@return nWidth
	@remark
	*/
	//static bool rgb2bgr(BYTE *pDst, int nSizeDst, const BYTE *pSrc, int nSizeSrc, int nWidth);
	/*!
	@brief ��r1,r2,r3..rn,g1,g2..b1,b2..��ʽ������ת����r1,g1,b1,r2,g2,b2...��ʽ
	@param pDst Ŀ����������С
	@param pSrc Դ��������С
	@return nSize  ���ݴ�С,������3��������
	@remark nSize ������3��������
	*/
	static bool r1r2r3_2_r1g1b1(BYTE *pDst, const BYTE *pSrc, int nSize );
	/*!
	@brief ��24λhbitmap��ʽ������ת����24λdcm��ʽ��ͼ������,\
	������Ϊhbitmapͼ�����ݵ�ÿ����32λ�����,��dicomͼ���в�����,����Ҫ������ת��
	@param pDataHbmp 24λhbitmap��ͼ������,���ݳ��ȱ����� (nWidth*3+3)/4*4)*height
	@param pDataDcm  24λdicomͼ�������,���õĳ��� nwidth*3*height
	@param nWidth  ͼ���� 
	@param nHeight ͼ��߶�
	@remark �˺���ֻ������24λͼ������,ʹ��ǰ��ر�֤pDataHbmp����Ϊ:(nWidth*3+3)/4*4)*height,
	pDataDcm ����Ϊnwidth*3*height
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
	bool GetImageDataOriginal(void *pdata, unsigned long  nBytesMax);//!<��ȡ��ԭʼ��ͼ������,δ���κδ���
	/*!
	@brief ��ȡһ֡ͼ��,���ص�hbitmap������Ҫ�������ֶ��ͷ�
	@param nFramePos ������ļ��Ƕ��ͼ��,nFramePosָ����Ӱ��nλ��(��0��ʼ)
	@return ����ɹ����ؾ��,���򷵻�NULL
	@remark ����ֶ��ͷŷ��ص�HBITMAP ��� 
	*/
	HBITMAP GetHBITMAP(int nFramePos=0);
	//single frame
	bool  Get24BitBGRData(BYTE *pdata, unsigned long nBytesMax, int nFramePos = 0);
	//multiframe
	bool GetNumberOfFrames(int &count);//֡��
	bool GetFrameIncrementPointer(DWORD &nAdd);//ÿ֡����ָ���ַ����
	bool GetFrameTime();//֡���ʱ��//Normal time per frame in millisecond
	bool GetRecommendedDisplayFrameRate(int n);//in frames per second
public:
	//========================set ===========================
	bool SetWidth(unsigned short width);//!< ����ͼ����
	bool SetHeight(unsigned short nwith);//!< ����ͼ��߶�
	bool SetChannel(unsigned short nchannel);//!< ����ͼ��ͨ����
	bool SetDepth(unsigned short nDepth);//!< ����ͼ�����
	/*!
	@brief ����ͼ��ĵ�ɫ��,�˺�������8λͼʱ��Ч
	@param pPal  ��ɫ��ָ��
	@param count ��ɫ���tagRGBQUAD����
	*/
	bool SetPalette(const tagRGBQUAD* pPal, int count);
	/*!
	@brief ֻ����ͼ������,
	@param pdata ͼ������ָ��
	@param nbytes ͼ�����ݵĳ���
	@return ���óɹ�����true, ���򷵻�false
	*/
	bool SetImageData(const void *pdata, unsigned long nbytes);
	/*!
	@brief s����ͼ��ĳ���,���,λ�����������,����������
	@param hbmp ͼ����,����֧��8λ,24λrgbλͼ
	@reutrn  return true if successed
	*/ 
	bool SetHBITMAP(HBITMAP hbmp);//!<����ͼ��,��֧��16λλͼ
	/*!
	@brief ����ͼ��ĳ���,���,λ�����������,����������
	@param nwidth  ͼ����
	@param nheight  ͼ��߶�
	@param pData   ����ָ��
	@param nFrameCount ͼ��֡��
	@return ���óɹ�����true, ���򷵻�false
	@remark ���뱣֤pdata�ĳ���lenthΪ(nwidth*3+3)/4*4)*nheight,��Ȳ���Ҫ4�ֽڶ���
	*/
	bool SetImage24Bit(int nwidth, int nheight, const void *pData, int nFrameCount=1);//pdata'lenth = (nwidth*3+3)/4*4)*nheight
	//multframe
	bool SetNumberOfFrames(int nCount);//!< ���õ�Ӱ֡��
	bool SetFrameIncrementPointer(unsigned int nAdd);//
	bool SetFrameTime(float fFrameTime);//!< ����֡��
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
