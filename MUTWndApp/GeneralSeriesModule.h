#pragma once
#include "DcmModuleBase.h"
class _declspec(dllexport) GeneralSeriesModule: public DcmModuleBase
{
public:
	GeneralSeriesModule(DcmDataset *pDataset);
	~GeneralSeriesModule(void);
protected:
	GeneralSeriesModule(const GeneralSeriesModule&);
	GeneralSeriesModule &operator=(const GeneralSeriesModule&);
public:
	//general series module
	bool SetModality(LPCTSTR );
	bool SetSeriesInstanceUID(LPCTSTR);
	bool SetSeriesNumber(LPCTSTR);
	bool SetSeriesDate(LPCTSTR);
	bool SetSeriesTime(LPCTSTR);

	bool GetModality(TCHAR *szName, UINT nCount);
	bool GetSeriesInstanceUID(TCHAR *szName, UINT nCount);
	bool GetSeriesNumber(TCHAR *szName, UINT nCount);
	bool GetSeriesDate(TCHAR *szName, UINT nCount);
	bool GetSeriesTime(TCHAR *szName, UINT nCount);
};
