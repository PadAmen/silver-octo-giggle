#pragma once
#include "StringConvert.h"
//#include "../Image/dcmtk-3.5.4-win32-i386/include/dcmtk/dcmdata/dcdatset.h"
//class DcmDataset;
class _declspec(dllexport) DcmModuleBase
{
public:
	DcmModuleBase(DcmDataset *);
	virtual ~DcmModuleBase(void);
	bool SetDcmString(const DcmTag &tag,LPCTSTR lpszName);
	bool GetDcmString(const DcmTag &tag, TCHAR *szDst, UINT nCount);
protected:
	DcmModuleBase(const DcmModuleBase&);
	DcmModuleBase& operator=(const DcmModuleBase&);
protected:
	DcmDataset *pDataset;
};
