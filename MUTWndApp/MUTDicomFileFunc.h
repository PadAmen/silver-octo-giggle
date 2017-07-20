#pragma once
class CMUTDicomFileFunc
{
public:
	CMUTDicomFileFunc();
	~CMUTDicomFileFunc();
public:
	CString m_dicomfileid;
	CString m_studyid;
	CString m_patientid;
	CString m_directory;
	CString m_filename;

};

