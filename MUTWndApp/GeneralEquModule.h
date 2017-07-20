#pragma once
#include "DcmModuleBase.h"
//general equipment module
class _declspec(dllexport) GeneralEquModule : public DcmModuleBase
{
public:
	GeneralEquModule(DcmDataset *pDataset);
	~GeneralEquModule(void);
protected:
	GeneralEquModule(const GeneralEquModule&);
	GeneralEquModule &operator=(const GeneralEquModule&);
public:
	//General Equipment Module
	bool SetManufacturer(LPCTSTR);//生产商
	bool SetInstitutionName(LPCTSTR);//医院或研究所单位名称
	bool SetManufacturersModelName(LPCTSTR);//产品型号
	bool SetSoftwareVersion(LPCTSTR);//软件版本

	bool GetSoftwareVersion(TCHAR *szDst, UINT nCount);
	bool GetManufacturersModelName(TCHAR *szDst, UINT nCount);
	bool GetInstitutionName(TCHAR *szDst, UINT nCount);
	bool GetManufacturer(TCHAR *szDst, UINT nCount);

};
