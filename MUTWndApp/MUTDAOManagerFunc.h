#pragma once
#include "MUTPatientInfoFunc.h"
#include "MUTDoctorInfoFunc.h"
#include "MUTStudyInfoFunc.h"
#include "MUTDicomFileFunc.h"

enum QUERY_TYPE
{
	QUERY_TYPE_USERID,
	QUERY_TYPE_USERNAME
};
enum DELETE_STUDY_TYPE
{
	DELETE_TYPE_STUDYID,
	DELETE_TYPE_PATIENTID
};
class CMUTDAOManagerFunc
{
public:
	static CMUTDAOManagerFunc * GetDAOManager();
	CArray <CMUTPatientInfoFunc> * getpatients();
	CArray <CMUTDoctorInfoFunc> * getdoctors();
	CArray<CMUTStudyInfoFunc>* getStudyidInfo(CString patientid);
	CStringArray *CMUTDAOManagerFunc::getDicomFiles(CString ptid);
	CArray<CMUTDicomFileFunc>* getDicomFiles(CString studyid,CString ptid);
protected:
	CMUTDAOManagerFunc();
	~CMUTDAOManagerFunc();

	
private:
	CArray <CMUTPatientInfoFunc>  *m_patients_list;
	CArray <CMUTDoctorInfoFunc>  *m_doctors_list;
	CArray <CMUTStudyInfoFunc> *m_study_list;
public:
	bool QueryUserId(CString userid, QUERY_TYPE type);
	bool QueryDoctorByType(CString name, QUERY_TYPE type);
	bool AddPatient(CMUTPatientInfoFunc patient);
	CString getPatientId(CString patientname);
	bool deletePatientByname(CString patientname);
	bool AddDoctor(CMUTDoctorInfoFunc doctor);
	bool deleteDoctorByname(CString doctorname);
	bool addStudyInfo(CMUTStudyInfoFunc medicalinfo);
	bool deleteStudyInfo(CString patientid,DELETE_STUDY_TYPE type=DELETE_TYPE_PATIENTID);
	bool deleteDcmInfo(CString patientid);
	bool deleteDcmFile(CString filename);
	bool addDicomFile(CMUTDicomFileFunc dicomfile);
	bool deleteTableData(CString tbName);
	
};

