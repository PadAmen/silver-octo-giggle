#ifndef _STRING_CONVERT_
#define _STRING_CONVERT_

#include <vector>
#include <tchar.h>
#include <Windows.h>

using namespace std;

/*!
@brief 将多字节字符串转换成宽字节字符串,转换过程中将申请对应大小的内存空间
@param szWideChar 需要转换的宽字节字符串指针
@param pszMulitChar 转换后的多字节字符串数据存储位置指针地址
@return 转换成功,返回true
@remark 务必手动释放本函数执行后,*pszMulitChar 指向的内存
*/
static bool UnicodeToAnsi(const WCHAR*  szWideChar, char **pszMulitChar) 
{
	//计算从Unicode转换到Ansi后需要的字节数//根据ANSI code page转换//转换出错用缺省字符代替
	int nMinLen = ::WideCharToMultiByte( CP_ACP,WC_COMPOSITECHECK | WC_DEFAULTCHAR, (LPCWSTR)szWideChar, -1, NULL, 0, NULL,FALSE);
	*pszMulitChar = new char[nMinLen];
	//转换Unicode到Ansi //转换到缓冲区中 //最多个字节
	::WideCharToMultiByte(CP_ACP,	WC_COMPOSITECHECK | WC_DEFAULTCHAR,	(LPCWSTR)szWideChar, -1, *pszMulitChar,	nMinLen,	NULL, FALSE	);
	return true;
}
/*!
@brief 将多字节字符串转换成宽字节字符串,转换过程中将申请对应大小的内存空间
@param szMultiChar 需要转换的多字节字符串指针
@param pszWideChar 转换后的宽字符数据存储位置指针地址
@return 转换成功,返回true
@remark 务必手动释放本函数执行后,*pszWideChar 指向的内存
*/
static bool AnsiToUnicode(const char*  szMultiChar, WCHAR**pszWideChar) 
{
	//计算从Ansi转换到Unicode后需要的字节数//要转换的Ansi字符串//自动计算长度
	int nMinLen = ::MultiByteToWideChar( CP_ACP,MB_COMPOSITE,(LPCSTR)szMultiChar, -1, NULL,	0);
	*pszWideChar = new WCHAR[nMinLen];
	//为转换后保存Unicode字符串分配内存//从Ansi转换到Unicode字符 //转换到tmpstr//最多转换widecharlen个Unicode字符
	::MultiByteToWideChar( CP_ACP,	MB_COMPOSITE,(LPCSTR)szMultiChar,	-1,	 *pszWideChar, nMinLen );	
	return true;
}
/*!
@brief			  将字符串根据
@param strSrc     分隔的源字符串
@param arrStrings 字符串分隔后产生的字符串数组
@param chSep      分隔符
@return 成功返回true, 否则返回false
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
@brief			  根据当前环境将字符串转换成多字节字符串
@param strSrc     源字符串
@param arrStrings 转换后的字符串对象
@return 成功返回true, 否则返回false
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
// char* encode(const wchar_t* wstr, unsigned int codePage)       //TCHAR 转 CHAR
// {
// 	int sizeNeeded = WideCharToMultiByte(codePage, 0, wstr, -1, NULL, 0, NULL, NULL);
// 	char* encodedStr = new char[sizeNeeded];
// 	WideCharToMultiByte(codePage, 0, wstr, -1, encodedStr, sizeNeeded, NULL, NULL);
// 	return encodedStr;
// }
// 
// wchar_t* decode(const char* encodedStr, unsigned int codePage) //CHAR 转 TCHAR
// {
// 	int sizeNeeded = MultiByteToWideChar(codePage, 0, encodedStr, -1, NULL, 0);
// 	wchar_t* decodedStr = new wchar_t[sizeNeeded];
// 	MultiByteToWideChar(codePage, 0, encodedStr, -1, decodedStr, sizeNeeded);
// 	return decodedStr;
// }
#endif


