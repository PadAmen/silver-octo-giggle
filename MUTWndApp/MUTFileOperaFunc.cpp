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
	//错误提示消息
	CString strMsg, strHint;
	CString strPre, strNxt;
	//源文件目的文件路径信息
	CString strTem1;
	strTem1 = directoryname;


	//由于fileOpStruct.pFrom的特殊要求，其必须以null结尾，否则不会成功
	//故这里需要在尾部加上null字符
	directoryname += '\0';

	fileOpStruct.pFrom = directoryname;

	//准备提示信息
	strPre = "将目录";
	strNxt = "全部删除!";
	strPre = strPre + strTem1 + strNxt;
	strHint = "删除被取消";
	strMsg = "删除出错，其代码为:";
	//填充结构的成员
	fileOpStruct.lpszProgressTitle = strPre;
	fileOpStruct.wFunc = FO_DELETE;

	//填充结构成员
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
		//提示中断信息
		AfxMessageBox(strHint);
		return false;
	}
	else
	{
		//如果操作出错
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




