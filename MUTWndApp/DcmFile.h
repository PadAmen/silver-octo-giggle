#pragma once
//#include "../Image/dcmtk-3.5.4-win32-i386/include/dcmtk/dcmdata/dcdatset.h"
//#include "../Image/dcmtk-3.5.4-win32-i386/include/dcmtk/dcmdata/dcfilefo.h"
class DcmDataset;
class DcmFileFormat;
class _declspec(dllexport) DcmFile
{
public:
	//DcmFile(LPCTSTR lpszPath);
	DcmFile();
	~DcmFile(void);
	
	bool Load(LPCTSTR lpszPath);	
	bool Save(LPCTSTR lpszPath);
	bool Create();

	bool SetDcmOtherInfo();
	bool SetImageInfo(WORD width, WORD height, WORD channel, WORD depth);

	DcmDataset *GetDcmDataset();
protected:
	DcmFileFormat *m_pfileformat;
};
