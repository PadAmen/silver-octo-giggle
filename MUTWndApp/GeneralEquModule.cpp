#include "StdAfx.h"
#include "GeneralEquModule.h"

GeneralEquModule::GeneralEquModule(DcmDataset *pDataset):DcmModuleBase(pDataset)
{
}

GeneralEquModule::~GeneralEquModule(void)
{
}

bool  GeneralEquModule::SetManufacturer(LPCTSTR lpszVal)
{
	return this->SetDcmString(DCM_Manufacturer, lpszVal);
}
bool  GeneralEquModule::SetInstitutionName(LPCTSTR lpszVal )//ҽԺ���о�����λ����
{
	return this->SetDcmString(DCM_InstitutionName, lpszVal);
}
bool  GeneralEquModule::SetManufacturersModelName(LPCTSTR lpszVal)//��Ʒ�ͺ�
{
	return this->SetDcmString(DCM_ManufacturersModelName, lpszVal);

}
bool  GeneralEquModule::SetSoftwareVersion(LPCTSTR lpszVal)//����汾
{
	return this->SetDcmString(DCM_SoftwareVersions, lpszVal);
}


bool  GeneralEquModule::GetSoftwareVersion(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_SoftwareVersions, szDst, nCount);
}
bool  GeneralEquModule::GetManufacturersModelName(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_ManufacturersModelName,  szDst, nCount);

}
bool  GeneralEquModule::GetInstitutionName(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_InstitutionName,  szDst, nCount);
}
bool  GeneralEquModule::GetManufacturer(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_Manufacturer, szDst, nCount);
}