#pragma once
#include "DcmModuleBase.h"
class  _declspec(dllexport) GeneralStudyModule: public DcmModuleBase
{
public:
	GeneralStudyModule(DcmDataset *pDataset);
	~GeneralStudyModule(void);
protected:
	GeneralStudyModule(const GeneralStudyModule&);
	GeneralStudyModule &operator=(const GeneralStudyModule&);
public:
	//GeneralStudy module
	bool SetStudyInstanceUID(LPCTSTR lpszval);
	bool SetStudyDate(LPCTSTR lpszval);//yyyymmdd
	bool SetStudyTime(LPCTSTR lpszval);//HHMMSS
	bool SetReferringPhyName(LPCTSTR lpszval);
	bool SetStudyID(LPCTSTR lpszval);
	bool SetStudyDescription(LPCTSTR lpszval);
	bool SetNameOfPhy(LPCTSTR lpszval);

	bool GetStudyInstanceUID(TCHAR *szDst, UINT nCount);
	bool GetStudyDate(TCHAR *szDst, UINT nCount);//yyyymmdd
	bool GetStudyTime(TCHAR *szDst, UINT nCount);//HHMMSS
	bool GetReferringPhyName(TCHAR *szDst, UINT nCount);
	bool GetStudyID(TCHAR *szDst, UINT nCount);
	bool GetStudyDescription(TCHAR *szDst, UINT nCount);
	bool GetNameOfPhy(TCHAR *szDst, UINT nCount);
};

