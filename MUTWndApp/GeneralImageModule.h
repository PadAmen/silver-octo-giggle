#pragma once
#include "DcmModuleBase.h"
class _declspec(dllexport) GeneralImageModule: public DcmModuleBase
{
public:
	GeneralImageModule(DcmDataset *pDataset);
	~GeneralImageModule(void);
protected:
	GeneralImageModule(const GeneralImageModule&);
	GeneralImageModule &operator=(const GeneralImageModule&);
public:
	//generalImage Module
	bool SetInstanceNumber(LPCTSTR lpszVal);
	bool SetImageDate(LPCTSTR lpszVal);
	bool SetImageTime(LPCTSTR lpszVal);//
	bool SetImageType(LPCTSTR lpszVal);//ORIGINAL\SECONDARY
	bool SetImageComments(LPCTSTR lpszVal);//contain clip, frame, or view name
	bool SetLossyImageCompression(LPCTSTR lpszVal);//00-No lossy compresssion -01-Lossy comp
	bool SetLossyImageCompressionRatio(LPCTSTR lpszVal );//

	bool GetInstanceNumber(TCHAR *szDst, int nCount);
	bool GetImageDate(TCHAR *szDst, int nCount);
	bool GetImageTime(TCHAR *szDst, int nCount);//
	bool GetImageType(TCHAR *szDst, int nCount);//ORIGINAL\SECONDARY
	bool GetImageComments(TCHAR *szDst, int nCount);//contain clip, frame, or view name
	bool GetLossyImageCompression(TCHAR *szDst, int nCount);//00-No lossy compresssion -01-Lossy comp
	bool GetLossyImageCompressionRatio(TCHAR *szDst, int nCount );//
};
