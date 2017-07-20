#include "stdafx.h"
#include "MUTDAOManagerFunc.h"
#include "MUTAdoFunc.h"
//#include "logfile.h"


CMUTDAOManagerFunc::CMUTDAOManagerFunc()
{
	m_patients_list = new CArray<CMUTPatientInfoFunc>();
	m_doctors_list = new CArray<CMUTDoctorInfoFunc>();
	m_study_list = new CArray<CMUTStudyInfoFunc>();
}


CMUTDAOManagerFunc::~CMUTDAOManagerFunc()
{
	//CLogout("clear DAOManager memory\r\n");
	delete m_patients_list;
	delete m_doctors_list;
	delete m_study_list;    //add
}

CMUTDAOManagerFunc* CMUTDAOManagerFunc::GetDAOManager()
{
	static CMUTDAOManagerFunc m_DAOManager;//is it a single object?
	return &m_DAOManager;
}
CArray<CMUTPatientInfoFunc> *CMUTDAOManagerFunc::getpatients()
{
	m_patients_list->RemoveAll();
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  
		_bstr_t sql_DDL = "select * from patient order by ID asc";           //desc
		sql.m_pReset->Open(sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��
		
		while (!sql.m_pReset->adoEOF)                                           //��¼��������ĩβʱִ��ѭ��
		{
			CString patientid;
			_variant_t vID;
			vID = sql.m_pReset->GetCollect("ID");
// 			int id = vID.iVal;
// 			printf("get id is %d \r\n", id);
// 			if (id == 1) //ignore first row, it is default.
// 			{
// 				sql.m_pReset->MoveNext();
// 			}

			vID = sql.m_pReset->GetCollect("ID");
			patientid.Format(_T("%d"),vID.iVal);
			

			CString userid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("userid");
			CString username = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("username");
			CString sex = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("usersex");
			CString birthday = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("userbirthday");
			CString history = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("history");
			//CString age = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("age");
			//CString idcard = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("idcard");
			//CString address = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("address");
			//CString description = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("description");
			//CString birthday = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("birthday");
			//FIXME , these colume are null now.
			//CString other = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("other");
			//CString doctorid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("doctorid");

			CMUTPatientInfoFunc patient;
			patient.m_patient_id = patientid;
			patient.m_patient_userid = userid;
			patient.m_patient_username = username;
			patient.m_patient_sex = sex;
			patient.m_patient_birthday = birthday;
			patient.m_history = history;
			//patient.m_patient_age = _tstoi(age);
			//patient.m_patient_age = age;
			//patient.m_patient_idcard = idcard; 
			//patient.m_patient_description = description;
			//patient.m_patient_birthday = birthday;
			//patient.m_others = other;
			//patient.m_doctorid = doctorid;

			m_patients_list->Add(patient);

		
			sql.m_pReset->MoveNext();                                                         //��¼��ָ�����һλ
		}
		/*
		if (sql.m_pReset->GetRecordCount() == 0)	 //�ж�sql������ü�¼���Ƿ��м�¼
		{
			printf("get user count is %d\n", sql.m_pReset->GetRecordCount());
			sql.CloseConn();
			return m_patients_list;
		}
		*/
		sql.CloseConn();
	}
	catch (_com_error e)
	{
		//CLogout("catch error %s \r\n",e.ErrorMessage());
		
	}

	return m_patients_list;
	
}
CString CMUTDAOManagerFunc::getPatientId(CString patientname)
{
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from patient where username = '%s'"),patientname);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��

		_variant_t vID;
		vID = sql.m_pReset->GetCollect("ID");
		int id = vID.iVal;
		sql.CloseConn();
		CString tempReturn;
		tempReturn.Format(_T("%d"),id);
		return tempReturn;
		
	}
	catch (_com_error e)	
	{
		AfxMessageBox(_T("ɾ�����ݿ���ʧ��"));
		return _T("");
	}

	return _T("");
}
CArray<CMUTDoctorInfoFunc> *CMUTDAOManagerFunc::getdoctors()
{
	m_doctors_list->RemoveAll();
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  
		_bstr_t sql_DDL = "select * from doctor order by ID asc";           //desc ����
		sql.m_pReset->Open(sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��



		while (!sql.m_pReset->adoEOF)                                           //��¼��������ĩβʱִ��ѭ��
		{
			_variant_t varTemp;
			CString doctorid;
			CString doctorname;
			_variant_t vID;

			vID = sql.m_pReset->GetCollect("ID");
			int id = vID.iVal;
	
			vID = sql.m_pReset->GetCollect("ID");
			doctorid.Format(_T("%d"),vID.iVal);
			varTemp = sql.m_pReset->GetCollect("name");

			if (varTemp.vt == VT_NULL)
			{
				continue;
			}
			else
			{
				doctorname = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("name");
			}
			
			//CString description = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("description");


			CMUTDoctorInfoFunc doctor;
			doctor.m_doctor_id = doctorid;
			doctor.m_doctor_username = doctorname;
			//doctor.m_doctor_description = description;

			m_doctors_list->Add(doctor);


			sql.m_pReset->MoveNext();                                                         //��¼��ָ�����һλ
		}
		/*
		if (sql.m_pReset->GetRecordCount() == 0)	 //�ж�sql������ü�¼���Ƿ��м�¼
		{
		printf("get user count is %d\n", sql.m_pReset->GetRecordCount());
		sql.CloseConn();
		return m_patients_list;
		}
		*/
		sql.CloseConn();
	}
	catch (_com_error e)
	{
		//CLogout("catch error %s \r\n", e.ErrorMessage());
		AfxMessageBox(_T("��ȡҽ����Ϣʧ��"));
	}

	return m_doctors_list;

}

bool CMUTDAOManagerFunc::QueryUserId(CString name, QUERY_TYPE type)
{
	try           //���������ļ��
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();
		sql.initRecordset();
		CString sql_DDL_ensure;


		if (type == QUERY_TYPE_USERID)
		{
			sql_DDL_ensure.Format(_T("select * from patient where userid='%s'"), name);

		}
		else if (type == QUERY_TYPE_USERNAME)
		{
			sql_DDL_ensure.Format(_T("select * from patient where username='%s'"), name);
		}
		else
		{
			AfxMessageBox(_T("wrong parameter"));
			sql.CloseConn();
			return true;
		}

		//��֤sql���,����޸ĺ��������������ֹ�޸�
		sql.m_pReset->Open((_bstr_t)sql_DDL_ensure, sql.m_pConn.GetInterfacePtr(), \
			adOpenStatic, adLockOptimistic, adCmdText);//����֤sql����ҵ��ļ�¼��,ע�������Ǿ�̬��,
													   //���������������ado����ڿͻ���ʹ�õ�ǰ��ֻ���α꣬
													   //���޷����ؽ������������ֻ�ܷ��أ�1
		if (sql.m_pReset->GetRecordCount() != 0)	 //�ж�sql������ü�¼���Ƿ��м�¼
		{
			if (type == QUERY_TYPE_USERID) {
				//AfxMessageBox(_T("userid�Ѵ���"));
			}
			if (type == QUERY_TYPE_USERNAME) {
				AfxMessageBox(_T("username�Ѵ���"));
			}
			sql.CloseConn();
			return true;
		}
	}
	catch (...)
	{
		if (type == QUERY_TYPE_USERID) {
			//AfxMessageBox(_T("userid�Ѵ���"));
		}
		if (type == QUERY_TYPE_USERNAME) {
			AfxMessageBox(_T("username�Ѵ���"));
		}
		return true;
	}
	return false;
}


bool CMUTDAOManagerFunc::QueryDoctorByType(CString name, QUERY_TYPE type)
{
	try           //���������ļ��
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();
		sql.initRecordset();
		CString sql_DDL_ensure;
		if (type == QUERY_TYPE_USERID)
		{
			sql_DDL_ensure.Format(_T("select * from doctor where ID='%s'"), name);
			

		}
		else if (type == QUERY_TYPE_USERNAME)
		{
			sql_DDL_ensure.Format(_T("select * from doctor where name='%s'"), name);
		}
		else
		{
			AfxMessageBox(_T("wrong parameter"));
			sql.CloseConn();
			return true;
		}
		//��֤sql���,����޸ĺ��������������ֹ�޸�
		sql.m_pReset->Open((_bstr_t)sql_DDL_ensure, sql.m_pConn.GetInterfacePtr(), \
			adOpenStatic, adLockOptimistic, adCmdText);//����֤sql����ҵ��ļ�¼��,ע�������Ǿ�̬��,
													   //���������������ado����ڿͻ���ʹ�õ�ǰ��ֻ���α꣬
													   //���޷����ؽ������������ֻ�ܷ��أ�1
		if (sql.m_pReset->GetRecordCount() != 0)	 //�ж�sql������ü�¼���Ƿ��м�¼
		{
			if (type == QUERY_TYPE_USERID) {
				AfxMessageBox(_T("doctor id �Ѵ���"));
			}
			if (type == QUERY_TYPE_USERNAME) {
				AfxMessageBox(_T("doctor name �Ѵ���"));
			}
			sql.CloseConn();
			return true;
		}
	}
	catch (_com_error e)
	{

		//CLogout("catch error %s \r\n", e.ErrorMessage());
		if (type == QUERY_TYPE_USERID) {
			AfxMessageBox(_T("doctor id�Ѵ���"));
		}
		if (type == QUERY_TYPE_USERNAME) {
			AfxMessageBox(_T("doctor name �Ѵ���"));
		}
		return true;
	}

	return false;
}



bool CMUTDAOManagerFunc::AddPatient(CMUTPatientInfoFunc patient)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		_bstr_t sql_DDL = "select * from patient";							//sql���
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //��patient���ݼ�
		
		sql2.m_pReset->AddNew();                                           //���ݿ������
		sql2.m_pReset->PutCollect("userid", (_bstr_t)patient.m_patient_userid);      //
		sql2.m_pReset->PutCollect("username", (_bstr_t)patient.m_patient_username);       //
		sql2.m_pReset->PutCollect("usersex", (_bstr_t)patient.m_patient_sex);       //
		//sql2.m_pReset->PutCollect("age", (_bstr_t)patient.m_patient_age);       //
		//sql2.m_pReset->PutCollect("idcard", (_bstr_t)patient.m_patient_idcard);     //
		//sql2.m_pReset->PutCollect("address", (_bstr_t)patient.m_patient_address);
		sql2.m_pReset->PutCollect("userbirthday", (_bstr_t)patient.m_patient_birthday);//
		sql2.m_pReset->PutCollect("history", (_bstr_t)patient.m_history);

		sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("���Ӳ��˴���"));
		return false;
	}
	return true;
}

bool CMUTDAOManagerFunc::AddDoctor(CMUTDoctorInfoFunc doctor)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		_bstr_t sql_DDL = "select * from doctor";							//sql���
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //��doctor���ݼ�

		sql2.m_pReset->AddNew();                                           //���ݿ������
		//sql2.m_pReset->PutCollect("doctorid", (_bstr_t)doctor.m_doctor_userid);      //
		sql2.m_pReset->PutCollect("name", (_bstr_t)doctor.m_doctor_username);       //
		sql2.m_pReset->PutCollect("sex", (_bstr_t)doctor.m_doctor_sex);       //
		sql2.m_pReset->PutCollect("cellphone", (_bstr_t)doctor.m_doctor_cellphone);       //
		sql2.m_pReset->PutCollect("email", (_bstr_t)doctor.m_doctor_email);       //
		sql2.m_pReset->PutCollect("company", (_bstr_t)doctor.m_doctor_company);       //
		sql2.m_pReset->PutCollect("duties", (_bstr_t)doctor.m_doctor_duties);       //
		sql2.m_pReset->PutCollect("others", (_bstr_t)doctor.m_others);       //

		sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("����ҽ������"));
		return false;
	}
	return true;
}


bool CMUTDAOManagerFunc::deletePatientByname(CString patientname)
{
	CMUTAdoFunc sql;
	sql.OnInitADOConn();                      //��ʼ�����ݿ�����
	sql.initRecordset();                      //�������ݼ�ʵ��
	_bstr_t sql_DDL_DELETE = "select * from patient";    //Ҫִ�е�sql���
	sql.m_pReset->Open(sql_DDL_DELETE, sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic, adLockOptimistic, adCmdText);             //��patient��¼��
	CString Target_Name;                        //���ѭ������patient name
	CString Delete_Name = patientname;                    //���ѡ�еĽ�Ҫɾ���ĺ�����
	try
	{
		while (!sql.m_pReset->adoEOF)                                   //������¼��ָ�벻����ĩβ��ִ��ѭ��
		{
			Target_Name = (CString)sql.m_pReset->GetCollect("username");    //����ѭ�����õĺ�����
			//int lx = patientname.GetLength();
			//int len = Target_Name.GetLength();

			if (Delete_Name == Target_Name)									//�ж�ѭ�����ú������Ƿ�ͽ�Ҫɾ���ĺ��������
			{
				sql.m_pReset->Delete(adAffectCurrent);                  //ɾ����ǰ��
				sql.m_pReset->Update();                                 //�������ݿ�
				sql.CloseConn();                                        //�ر�����
				return true;											//Ϊ������,�ǵ�break;��ֹ����ѭ��
			}
			sql.m_pReset->MoveNext();                                   //��¼��ָ�����һλ
		}
		sql.CloseConn(); 

		CString msg = _T("δ�ҵ�") + patientname;
		AfxMessageBox(msg);
		return false;
	}
	catch (...)
	{
		CString msg = _T("ɾ��") + patientname + _T("����");
		AfxMessageBox(msg);
		
		return false;
	}
	return true;
}

bool CMUTDAOManagerFunc::deleteDoctorByname(CString doctorname)
{
	CMUTAdoFunc sql;
	sql.OnInitADOConn();                      //��ʼ�����ݿ�����
	sql.initRecordset();                      //�������ݼ�ʵ��
	_bstr_t sql_DDL_DELETE = "select * from doctor";    //Ҫִ�е�sql���
	sql.m_pReset->Open(sql_DDL_DELETE, sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic, adLockOptimistic, adCmdText);             //��patient��¼��
	CString Target_Name;                        //���ѭ������patient name
	CString Delete_Name = doctorname;                    //���ѡ�еĽ�Ҫɾ���ĺ�����
	try
	{
		while (!sql.m_pReset->adoEOF)                                   //������¼��ָ�벻����ĩβ��ִ��ѭ��
		{
			Target_Name = (CString)sql.m_pReset->GetCollect("doctorname");    //����ѭ�����õ�doctor name
			if (Delete_Name == Target_Name)                             //�ж�ѭ�����ú������Ƿ�ͽ�Ҫɾ���ĺ��������
			{
				sql.m_pReset->Delete(adAffectCurrent);                  //ɾ����ǰ��
				sql.m_pReset->Update();                                 //�������ݿ�
				sql.CloseConn();                                        //�ر�����
				break;                                                  //Ϊ������,�ǵ�break;��ֹ����ѭ��
			}
			sql.m_pReset->MoveNext();                                   //��¼��ָ�����һλ
		}
		sql.CloseConn();                                                //�ر����ݿ�����
	}
	catch (...)
	{
		CString msg = _T("ɾ��") + doctorname + _T("����");
		AfxMessageBox(msg);

		return false;
	}
	return true;
}


bool CMUTDAOManagerFunc::addStudyInfo(CMUTStudyInfoFunc studyinfo)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		_bstr_t sql_DDL = "select * from study";							//sql���
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //��medical���ݼ�

		sql2.m_pReset->AddNew();                                           //���ݿ������
		sql2.m_pReset->PutCollect("studyid", (_bstr_t)studyinfo.m_studyid);      //
		sql2.m_pReset->PutCollect("patientid", (_bstr_t)studyinfo.m_patientid);       //
		sql2.m_pReset->PutCollect("doctorid", (_bstr_t)studyinfo.m_doctorid);       //


		sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("����studyinfo����"));
		return false;
	}
	return true;
}

bool CMUTDAOManagerFunc::deleteStudyInfo(CString patientid,DELETE_STUDY_TYPE type)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		CString sql_DDL;
		if(type == DELETE_TYPE_PATIENTID)
		sql_DDL.Format(_T("delete from study where patientid = '%s'"),patientid);		//sql���
		else if(type == DELETE_TYPE_STUDYID)
			 sql_DDL.Format(_T("delete form study where studyid = '%s'"),patientid);

		sql2.m_pReset->Open((_bstr_t)sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);				   //��medical���ݼ�

		//sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("ɾ��studyinfo����"));
		return false;
	}
	return true;
}
bool CMUTDAOManagerFunc::deleteDcmInfo(CString patientid)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		CString sql_DDL;
		sql_DDL.Format(_T("delete from dicomfile where patientid = '%s'"),patientid);							//sql���
		sql2.m_pReset->Open((_bstr_t)sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);				   //��medical���ݼ�

		//sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("ɾ��Dcminfo����"));
		return false;
	}
	return true;
}
bool CMUTDAOManagerFunc::deleteDcmFile(CString filename)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		CString sql_DDL;
		sql_DDL.Format(_T("delete from dicomfile where filename = '%s'"),filename);							//sql���
		sql2.m_pReset->Open((_bstr_t)sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);				   //��medical���ݼ�

		//sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("ɾ��dicomfile����"));
		return false;
	}
	return true;
}
bool CMUTDAOManagerFunc::addDicomFile(CMUTDicomFileFunc dicomfile)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		_bstr_t sql_DDL = "select * from dicomfile";							//sql���
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //��dicomfile���ݼ�

		sql2.m_pReset->AddNew();                                           //���ݿ������
		sql2.m_pReset->PutCollect("dicomfileid", (_bstr_t)dicomfile.m_dicomfileid);      //
		sql2.m_pReset->PutCollect("studyid", (_bstr_t)dicomfile.m_studyid);       //
		sql2.m_pReset->PutCollect("patientid", (_bstr_t)dicomfile.m_patientid);       //
		sql2.m_pReset->PutCollect("directory", (_bstr_t)dicomfile.m_directory);       //
		sql2.m_pReset->PutCollect("filename", (_bstr_t)dicomfile.m_filename);       //

		sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch (...)
	{
		AfxMessageBox(_T("����DicomFile����"));
		return false;
	}
	return true;
}


CArray<CMUTStudyInfoFunc>* CMUTDAOManagerFunc::getStudyidInfo(CString patientid)
{
	m_study_list->RemoveAll();
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from study where patientid='%s'"), patientid);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��


		while (!sql.m_pReset->adoEOF)                                           //��¼��������ĩβʱִ��ѭ��
		{
			CString studyid;
			studyid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("studyid");
			CString patientid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("patientid");
			CString doctorid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("doctorid");

			CMUTStudyInfoFunc StudyInfo;
			StudyInfo.m_studyid = studyid;
			StudyInfo.m_patientid = patientid;
			StudyInfo.m_doctorid = doctorid;


			m_study_list->Add(StudyInfo);

			sql.m_pReset->MoveNext();                                                         //��¼��ָ�����һλ
		}

		sql.CloseConn();
	}
	catch (_com_error e)
	{
		//CLogout("catch medical info error %s \r\n", e.ErrorMessage());

	}

	return m_study_list;
}
CStringArray *CMUTDAOManagerFunc::getDicomFiles(CString ptid)
{
	CStringArray *pDcmFile = new CStringArray;
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from dicomfile where patientid='%s'"), ptid);
		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��

		while (!sql.m_pReset->adoEOF)
		{
			CString directory = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect(_T("directory"));
			CString filename = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect(_T("filename"));
			directory += _T("\\");
			filename = directory + filename;
			pDcmFile->Add(filename);
			sql.m_pReset->MoveNext(); 
		}	

		sql.CloseConn();
		return pDcmFile;
	}
	catch(_com_error ex)
	{
		AfxMessageBox(_T("ɾ��DicomFile����"));
		delete pDcmFile;
	}
	return NULL;

}
CArray<CMUTDicomFileFunc>* CMUTDAOManagerFunc::getDicomFiles(CString studyid,CString ptid)
{
	CArray<CMUTDicomFileFunc> *dicomfile_list = new CArray<CMUTDicomFileFunc>();

	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from dicomfile  where studyid='%s'and patientid='%s'"), studyid,ptid);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��



		while (!sql.m_pReset->adoEOF)                                           //��¼��������ĩβʱִ��ѭ��
		{
			CString medical_id;
			medical_id = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("studyid");
			CString patientid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("patientid");
			CString directory = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("directory");
			CString dicomfileid = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("dicomfileid");
			CString filename = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("filename");
			CMUTDicomFileFunc dicomfile;

			dicomfile.m_studyid = medical_id;
			dicomfile.m_patientid = patientid;
			dicomfile.m_directory = directory;
			dicomfile.m_dicomfileid = dicomfileid;
			dicomfile.m_filename = filename;



			dicomfile_list->Add(dicomfile);


			sql.m_pReset->MoveNext();                                                         //��¼��ָ�����һλ
		}

		sql.CloseConn();
	}
	catch (_com_error e)
	{
		//CLogout("catch dicomfile info error %s \r\n", e.ErrorMessage());
		AfxMessageBox(_T("��ȡDicomFile����"));

	}

	return dicomfile_list;
}
bool CMUTDAOManagerFunc:: deleteTableData(CString tbName)
{
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //��ʼ�����ݿ�����
		sql.initRecordset();                             //������¼������ָ��ʵ��  

		CString sql_DDL;
		sql_DDL.Format(_T("delete from %s"),tbName);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //�򿪼�¼��
		sql.CloseConn();
	}
	catch (_com_error e)	
	{
		AfxMessageBox(_T("ɾ�����ݿ���ʧ��"));
		return FALSE;
	}

	return TRUE;
}
