#include "StdAfx.h"
#include "GeneralSeriesModule.h"

GeneralSeriesModule::GeneralSeriesModule(DcmDataset *pDataset):DcmModuleBase(pDataset)
{
}

GeneralSeriesModule::~GeneralSeriesModule(void)
{
}

//general series module
bool GeneralSeriesModule::SetModality(LPCTSTR szVal){
	return this->SetDcmString(DCM_Modality, szVal);
}
bool GeneralSeriesModule::SetSeriesInstanceUID(LPCTSTR szVal){
	return this->SetDcmString(DCM_SeriesInstanceUID, szVal);

}
bool GeneralSeriesModule::SetSeriesNumber(LPCTSTR szVal){

	return this->SetDcmString(DCM_SeriesNumber, szVal);
}
bool GeneralSeriesModule::SetSeriesDate(LPCTSTR szVal){

	return this->SetDcmString(DCM_SeriesDate, szVal);
}
bool GeneralSeriesModule::SetSeriesTime(LPCTSTR szVal){

	return this->SetDcmString(DCM_SeriesTime, szVal);
}

bool GeneralSeriesModule::GetModality(TCHAR *szName, UINT nCount){
	return this->GetDcmString(DCM_Modality, szName, nCount);
}

bool GeneralSeriesModule::GetSeriesInstanceUID(TCHAR *szName, UINT nCount){
	return this->GetDcmString(DCM_SeriesInstanceUID, szName, nCount);
}

bool GeneralSeriesModule::GetSeriesNumber(TCHAR *szName, UINT nCount){
	return this->GetDcmString(DCM_SeriesNumber, szName, nCount);
}

bool GeneralSeriesModule::GetSeriesDate(TCHAR *szName, UINT nCount){
	return this->GetDcmString(DCM_SeriesDate, szName, nCount);
}

bool GeneralSeriesModule::GetSeriesTime(TCHAR *szName, UINT nCount){

	return this->GetDcmString(DCM_SeriesTime, szName, nCount);
}
