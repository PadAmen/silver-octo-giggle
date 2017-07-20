#include "StdAfx.h"
#include "GeneralImageModule.h"

GeneralImageModule::GeneralImageModule(DcmDataset *pDataset):DcmModuleBase(pDataset)
{
}

GeneralImageModule::~GeneralImageModule(void)
{
}

bool GeneralImageModule::SetInstanceNumber(LPCTSTR lpszVal)
{
	return this->SetDcmString(DCM_InstanceNumber, lpszVal);
}
bool GeneralImageModule::SetImageDate(LPCTSTR lpszVal)
{
	return this->SetDcmString(DCM_ContentDate, lpszVal);
}
bool GeneralImageModule::SetImageTime(LPCTSTR lpszVal)//
{
	return this->SetDcmString(DCM_ContentTime, lpszVal);
}
bool GeneralImageModule::SetImageType(LPCTSTR lpszVal)//ORIGINAL\SECONDARY
{
	return this->SetDcmString(DCM_ImageType, lpszVal);
}
bool GeneralImageModule::SetImageComments(LPCTSTR lpszVal)//contain clip, frame, or view name
{
	return this->SetDcmString(DCM_ImageComments, lpszVal);
}
bool GeneralImageModule::SetLossyImageCompression(LPCTSTR lpszVal)//00-No lossy compresssion -01-Lossy comp
{
	return this->SetDcmString(DCM_LossyImageCompression, lpszVal);
}
bool GeneralImageModule::SetLossyImageCompressionRatio(LPCTSTR lpszVal )//
{
	return this->SetDcmString(DCM_LossyImageCompressionRatio, lpszVal);
}

bool GeneralImageModule::GetInstanceNumber(TCHAR *szDst, int nCount)
{
	return this->GetDcmString(DCM_InstanceNumber, szDst, nCount);
}
bool GeneralImageModule::GetImageDate(TCHAR *szDst, int nCount)
{
	return this->GetDcmString(DCM_ContentDate, szDst, nCount);
}
bool GeneralImageModule::GetImageTime(TCHAR *szDst, int nCount)//
{
	return this->GetDcmString(DCM_ContentTime, szDst, nCount);
}
//U/S Image attribute description. Term 3 and Term 4 are left blank.
bool GeneralImageModule::GetImageType(TCHAR *szDst, int nCount)//allways ="ORIGINAL\SECONDARY\\"
{
	return this->GetDcmString(DCM_ImageType, szDst, nCount);
}
bool GeneralImageModule::GetImageComments(TCHAR *szDst, int nCount)//contain clip, frame, or view name
{
	return this->GetDcmString(DCM_ImageComments, szDst, nCount);
}
bool GeneralImageModule::GetLossyImageCompression(TCHAR *szDst, int nCount)//00-No lossy compresssion -01-Lossy comp
{
	return this->GetDcmString(DCM_LossyImageCompression, szDst, nCount);
}
bool GeneralImageModule::GetLossyImageCompressionRatio(TCHAR *szDst, int nCount )
{
	return this->GetDcmString(DCM_LossyImageCompressionRatio, szDst, nCount);
}