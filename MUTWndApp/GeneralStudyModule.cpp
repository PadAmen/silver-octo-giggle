#include "StdAfx.h"
#include "GeneralStudyModule.h"

GeneralStudyModule::GeneralStudyModule(DcmDataset *pDataset):DcmModuleBase(pDataset)
{
}

GeneralStudyModule::~GeneralStudyModule(void)
{
}

//GeneralStudy module
bool GeneralStudyModule::SetStudyInstanceUID(LPCTSTR lpszval)
{
	return this->SetDcmString(DCM_StudyInstanceUID, lpszval);
}
bool GeneralStudyModule::SetStudyDate(LPCTSTR lpszval)//yyyymmdd
{
	return this->SetDcmString(DCM_StudyDate, lpszval);
}
bool GeneralStudyModule::SetStudyTime(LPCTSTR lpszval)//HHMMSS
{
	return this->SetDcmString(DCM_StudyTime, lpszval);
}
bool GeneralStudyModule::SetReferringPhyName(LPCTSTR lpszval)
{
	return this->SetDcmString(DCM_ReferringPhysiciansName, lpszval);
}
bool GeneralStudyModule::SetStudyID(LPCTSTR lpszval)
{
	return this->SetDcmString(DCM_StudyID, lpszval);
}
bool GeneralStudyModule::SetStudyDescription(LPCTSTR lpszval)
{
	return this->SetDcmString(DCM_StudyDescription, lpszval);
}
bool GeneralStudyModule::SetNameOfPhy(LPCTSTR lpszval)
{
	return this->SetDcmString(DCM_NameOfPhysiciansReadingStudy, lpszval);
}

bool GeneralStudyModule::GetStudyInstanceUID(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_StudyInstanceUID, szDst, nCount);
}
bool GeneralStudyModule::GetStudyDate(TCHAR *szDst, UINT nCount)//yyyymmdd
{
	return this->GetDcmString(DCM_StudyDate, szDst, nCount);
}
bool GeneralStudyModule::GetStudyTime(TCHAR *szDst, UINT nCount)//HHMMSS
{
	return this->GetDcmString(DCM_StudyTime, szDst, nCount);
}
bool GeneralStudyModule::GetReferringPhyName(TCHAR *szDst, UINT nCount)

{
	return this->GetDcmString(DCM_ReferringPhysiciansName, szDst, nCount);
}
bool GeneralStudyModule::GetStudyID(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_StudyID, szDst, nCount);
}
bool GeneralStudyModule::GetStudyDescription(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_StudyDescription, szDst, nCount);
}
bool GeneralStudyModule::GetNameOfPhy(TCHAR *szDst, UINT nCount)
{
	return this->GetDcmString(DCM_NameOfPhysiciansReadingStudy, szDst, nCount);
}