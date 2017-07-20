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
	bool SetManufacturer(LPCTSTR);//������
	bool SetInstitutionName(LPCTSTR);//ҽԺ���о�����λ����
	bool SetManufacturersModelName(LPCTSTR);//��Ʒ�ͺ�
	bool SetSoftwareVersion(LPCTSTR);//����汾

	bool GetSoftwareVersion(TCHAR *szDst, UINT nCount);
	bool GetManufacturersModelName(TCHAR *szDst, UINT nCount);
	bool GetInstitutionName(TCHAR *szDst, UINT nCount);
	bool GetManufacturer(TCHAR *szDst, UINT nCount);

};
