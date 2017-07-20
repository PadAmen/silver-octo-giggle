#ifndef _STRING_CONVERT_
#define _STRING_CONVERT_

#include <vector>
#include <tchar.h>
#include <Windows.h>

using namespace std;

/*!
@brief �����ֽ��ַ���ת���ɿ��ֽ��ַ���,ת�������н������Ӧ��С���ڴ�ռ�
@param szWideChar ��Ҫת���Ŀ��ֽ��ַ���ָ��
@param pszMulitChar ת����Ķ��ֽ��ַ������ݴ洢λ��ָ���ַ
@return ת���ɹ�,����true
@remark ����ֶ��ͷű�����ִ�к�,*pszMulitChar ָ����ڴ�
*/
static bool UnicodeToAnsi(const WCHAR*  szWideChar, char **pszMulitChar) 
{
	//�����Unicodeת����Ansi����Ҫ���ֽ���//����ANSI code pageת��//ת��������ȱʡ�ַ�����
	int nMinLen = ::WideCharToMultiByte( CP_ACP,WC_COMPOSITECHECK | WC_DEFAULTCHAR, (LPCWSTR)szWideChar, -1, NULL, 0, NULL,FALSE);
	*pszMulitChar = new char[nMinLen];
	//ת��Unicode��Ansi //ת������������ //�����ֽ�
	::WideCharToMultiByte(CP_ACP,	WC_COMPOSITECHECK | WC_DEFAULTCHAR,	(LPCWSTR)szWideChar, -1, *pszMulitChar,	nMinLen,	NULL, FALSE	);
	return true;
}
/*!
@brief �����ֽ��ַ���ת���ɿ��ֽ��ַ���,ת�������н������Ӧ��С���ڴ�ռ�
@param szMultiChar ��Ҫת���Ķ��ֽ��ַ���ָ��
@param pszWideChar ת����Ŀ��ַ����ݴ洢λ��ָ���ַ
@return ת���ɹ�,����true
@remark ����ֶ��ͷű�����ִ�к�,*pszWideChar ָ����ڴ�
*/
static bool AnsiToUnicode(const char*  szMultiChar, WCHAR**pszWideChar) 
{
	//�����Ansiת����Unicode����Ҫ���ֽ���//Ҫת����Ansi�ַ���//�Զ����㳤��
	int nMinLen = ::MultiByteToWideChar( CP_ACP,MB_COMPOSITE,(LPCSTR)szMultiChar, -1, NULL,	0);
	*pszWideChar = new WCHAR[nMinLen];
	//Ϊת���󱣴�Unicode�ַ��������ڴ�//��Ansiת����Unicode�ַ� //ת����tmpstr//���ת��widecharlen��Unicode�ַ�
	::MultiByteToWideChar( CP_ACP,	MB_COMPOSITE,(LPCSTR)szMultiChar,	-1,	 *pszWideChar, nMinLen );	
	return true;
}
/*!
@brief			  ���ַ�������
@param strSrc     �ָ���Դ�ַ���
@param arrStrings �ַ����ָ���������ַ�������
@param chSep      �ָ���
@return �ɹ�����true, ���򷵻�false
@remark  
*/
static bool splitString(const char *szSrc, vector<string> &arrStrings, char chSep='.')
{
	if(!szSrc) return false;
	unsigned int nEnd=0,nStart= 0;
	while(true){
		if((szSrc[nEnd]==chSep) || szSrc[nEnd]=='\0'){
			char temp[100];
			memcpy(temp, &szSrc[nStart], nEnd-nStart);
			temp[nEnd-nStart] = '\0';
			arrStrings.push_back(temp);
			if(szSrc[nEnd]=='\0') break;
			nStart = nEnd+1;
			nEnd = nStart;
		}else{
			nEnd++;
		}
	}
	return true;
}
/*!
@brief			  ���ݵ�ǰ�������ַ���ת���ɶ��ֽ��ַ���
@param strSrc     Դ�ַ���
@param arrStrings ת������ַ�������
@return �ɹ�����true, ���򷵻�false
@remark  
*/
static bool TcharToAnsi(const TCHAR *szSrc, string &strDst)
{
	char *szPathAnsi = NULL;
#ifdef _UNICODE	
	if(!UnicodeToAnsi(szSrc, &szPathAnsi))
		return false;
	strDst = szPathAnsi;
	delete []szPathAnsi;
#else
	strDst = szSrc;
#endif
	return true;
}

static bool AnsiToTchar(const char *szSrc, TCHAR * szDst, unsigned int nCountOfTchar)
{
	if(!szSrc || !szDst || nCountOfTchar < 1) return false;
	bool bSucc = false;
#ifdef _UNICODE
	WCHAR *pStrTemp = NULL;
	if(AnsiToUnicode(szSrc, &pStrTemp))
	{
		_tcscpy_s(szDst, nCountOfTchar, pStrTemp);
		bSucc = true;
	}
	delete []pStrTemp;
#else
	strcpy_s(szDst, nCountOfTchar, szSrc);
	bSucc = true;
#endif
	return bSucc;
}
// char* encode(const wchar_t* wstr, unsigned int codePage)       //TCHAR ת CHAR
// {
// 	int sizeNeeded = WideCharToMultiByte(codePage, 0, wstr, -1, NULL, 0, NULL, NULL);
// 	char* encodedStr = new char[sizeNeeded];
// 	WideCharToMultiByte(codePage, 0, wstr, -1, encodedStr, sizeNeeded, NULL, NULL);
// 	return encodedStr;
// }
// 
// wchar_t* decode(const char* encodedStr, unsigned int codePage) //CHAR ת TCHAR
// {
// 	int sizeNeeded = MultiByteToWideChar(codePage, 0, encodedStr, -1, NULL, 0);
// 	wchar_t* decodedStr = new wchar_t[sizeNeeded];
// 	MultiByteToWideChar(codePage, 0, encodedStr, -1, decodedStr, sizeNeeded);
// 	return decodedStr;
// }
#endif


