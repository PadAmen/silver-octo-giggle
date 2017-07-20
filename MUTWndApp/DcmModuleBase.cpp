#include "StdAfx.h"
#include "DcmModuleBase.h"

DcmModuleBase::DcmModuleBase(DcmDataset *pdataset)
{
	this->pDataset = (pdataset);
}

DcmModuleBase::~DcmModuleBase(void)
{
}


bool DcmModuleBase::SetDcmString(const DcmTag &tag,LPCTSTR lpszName)
{
	if(pDataset == NULL) return false;
	string str;
	if(!TcharToAnsi(lpszName, str)) return false;
	return pDataset->putAndInsertString(tag, str.c_str()).good();
}

bool DcmModuleBase::GetDcmString(const DcmTag &tag, TCHAR *szDst, UINT nCount)
{
	if(pDataset == NULL) return false;
	const char *szTemp = NULL;
	if(pDataset->findAndGetString(tag, szTemp).good())
	{
		return AnsiToTchar(szTemp, szDst, nCount);
	}
	return false;
}