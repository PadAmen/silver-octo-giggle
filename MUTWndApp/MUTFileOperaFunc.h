#pragma once
#include "stdafx.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dcdatset.h"


class CMUTFileOperaFunc
{
public:
	CMUTFileOperaFunc(void);
	~CMUTFileOperaFunc(void);
	static BOOL DeleteDirectoryAndFiles(SHFILEOPSTRUCT fileOpStruct, CString directoryname , int flag);
	static char* CMUTFileOperaFunc::encode(const wchar_t* wstr, unsigned int codePage);
	static wchar_t* decode(const char* encodedStr, unsigned int codePage);
	static void SaveBitmapToDirectFile(CDC* pDC, CRect BitmapSize, int BitCount, CString strFilePath);

};