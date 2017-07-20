#include "stdafx.h"

#include "MUTFileOperaFunc.h"


CMUTFileOperaFunc::CMUTFileOperaFunc(void)
{

}

CMUTFileOperaFunc::~CMUTFileOperaFunc(void)
{
}

BOOL CMUTFileOperaFunc::DeleteDirectoryAndFiles(SHFILEOPSTRUCT fileOpStruct, CString directoryname, int flag)
{
	DWORD  errorCode;
	//������ʾ��Ϣ
	CString strMsg, strHint;
	CString strPre, strNxt;
	//Դ�ļ�Ŀ���ļ�·����Ϣ
	CString strTem1;
	strTem1 = directoryname;


	//����fileOpStruct.pFrom������Ҫ���������null��β�����򲻻�ɹ�
	//��������Ҫ��β������null�ַ�
	directoryname += '\0';

	fileOpStruct.pFrom = directoryname;

	//׼����ʾ��Ϣ
	strPre = "��Ŀ¼";
	strNxt = "ȫ��ɾ��!";
	strPre = strPre + strTem1 + strNxt;
	strHint = "ɾ����ȡ��";
	strMsg = "ɾ�����������Ϊ:";
	//���ṹ�ĳ�Ա
	fileOpStruct.lpszProgressTitle = strPre;
	fileOpStruct.wFunc = FO_DELETE;

	//���ṹ��Ա
	if (flag == 0)//don't need prompt
	{
		fileOpStruct.fFlags = FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION;
	}
	else
	{
		fileOpStruct.fFlags = FOF_SIMPLEPROGRESS;
	}
	
	int  res = SHFileOperation(&fileOpStruct);
	errorCode = GetLastError();

	if (fileOpStruct.fAnyOperationsAborted == TRUE)
	{
		//��ʾ�ж���Ϣ
		AfxMessageBox(strHint);
		return false;
	}
	else
	{
		//�����������
		if (res != 0)
		{

			AfxMessageBox(strMsg);
			return false;
		}
	}
	return true;
}

char* CMUTFileOperaFunc::encode(const wchar_t* wstr, unsigned int codePage)
{
	int sizeNeeded = WideCharToMultiByte(codePage, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* encodedStr = new char[sizeNeeded];
	WideCharToMultiByte(codePage, 0, wstr, -1, encodedStr, sizeNeeded, NULL, NULL);
	return encodedStr;
}

wchar_t* CMUTFileOperaFunc::decode(const char* encodedStr, unsigned int codePage)
{
	int sizeNeeded = MultiByteToWideChar(codePage, 0, encodedStr, -1, NULL, 0);
	wchar_t* decodedStr = new wchar_t[sizeNeeded];
	MultiByteToWideChar(codePage, 0, encodedStr, -1, decodedStr, sizeNeeded);
	return decodedStr;
}




