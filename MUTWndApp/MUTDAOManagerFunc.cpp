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
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  
		_bstr_t sql_DDL = "select * from patient order by ID asc";           //desc
		sql.m_pReset->Open(sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集
		
		while (!sql.m_pReset->adoEOF)                                           //记录集不超出末尾时执行循环
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

		
			sql.m_pReset->MoveNext();                                                         //记录集指针后移一位
		}
		/*
		if (sql.m_pReset->GetRecordCount() == 0)	 //判断sql语句所得记录集是否有记录
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
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from patient where username = '%s'"),patientname);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集

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
		AfxMessageBox(_T("删除数据库表格失败"));
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
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  
		_bstr_t sql_DDL = "select * from doctor order by ID asc";           //desc 倒序
		sql.m_pReset->Open(sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集



		while (!sql.m_pReset->adoEOF)                                           //记录集不超出末尾时执行循环
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


			sql.m_pReset->MoveNext();                                                         //记录集指针后移一位
		}
		/*
		if (sql.m_pReset->GetRecordCount() == 0)	 //判断sql语句所得记录集是否有记录
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
		AfxMessageBox(_T("获取医生信息失败"));
	}

	return m_doctors_list;

}

bool CMUTDAOManagerFunc::QueryUserId(CString name, QUERY_TYPE type)
{
	try           //不能重名的检测
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

		//验证sql语句,如果修改后有重名情况则终止修改
		sql.m_pReset->Open((_bstr_t)sql_DDL_ensure, sql.m_pConn.GetInterfacePtr(), \
			adOpenStatic, adLockOptimistic, adCmdText);//打开验证sql语句找到的记录集,注意这里是静态打开,
													   //见第三个参数如果ado组件在客户端使用的前向只读游标，
													   //就无法返回结果集的条数，只能返回－1
		if (sql.m_pReset->GetRecordCount() != 0)	 //判断sql语句所得记录集是否有记录
		{
			if (type == QUERY_TYPE_USERID) {
				//AfxMessageBox(_T("userid已存在"));
			}
			if (type == QUERY_TYPE_USERNAME) {
				AfxMessageBox(_T("username已存在"));
			}
			sql.CloseConn();
			return true;
		}
	}
	catch (...)
	{
		if (type == QUERY_TYPE_USERID) {
			//AfxMessageBox(_T("userid已存在"));
		}
		if (type == QUERY_TYPE_USERNAME) {
			AfxMessageBox(_T("username已存在"));
		}
		return true;
	}
	return false;
}


bool CMUTDAOManagerFunc::QueryDoctorByType(CString name, QUERY_TYPE type)
{
	try           //不能重名的检测
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
		//验证sql语句,如果修改后有重名情况则终止修改
		sql.m_pReset->Open((_bstr_t)sql_DDL_ensure, sql.m_pConn.GetInterfacePtr(), \
			adOpenStatic, adLockOptimistic, adCmdText);//打开验证sql语句找到的记录集,注意这里是静态打开,
													   //见第三个参数如果ado组件在客户端使用的前向只读游标，
													   //就无法返回结果集的条数，只能返回－1
		if (sql.m_pReset->GetRecordCount() != 0)	 //判断sql语句所得记录集是否有记录
		{
			if (type == QUERY_TYPE_USERID) {
				AfxMessageBox(_T("doctor id 已存在"));
			}
			if (type == QUERY_TYPE_USERNAME) {
				AfxMessageBox(_T("doctor name 已存在"));
			}
			sql.CloseConn();
			return true;
		}
	}
	catch (_com_error e)
	{

		//CLogout("catch error %s \r\n", e.ErrorMessage());
		if (type == QUERY_TYPE_USERID) {
			AfxMessageBox(_T("doctor id已存在"));
		}
		if (type == QUERY_TYPE_USERNAME) {
			AfxMessageBox(_T("doctor name 已存在"));
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
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		_bstr_t sql_DDL = "select * from patient";							//sql语句
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //打开patient数据集
		
		sql2.m_pReset->AddNew();                                           //数据库添加行
		sql2.m_pReset->PutCollect("userid", (_bstr_t)patient.m_patient_userid);      //
		sql2.m_pReset->PutCollect("username", (_bstr_t)patient.m_patient_username);       //
		sql2.m_pReset->PutCollect("usersex", (_bstr_t)patient.m_patient_sex);       //
		//sql2.m_pReset->PutCollect("age", (_bstr_t)patient.m_patient_age);       //
		//sql2.m_pReset->PutCollect("idcard", (_bstr_t)patient.m_patient_idcard);     //
		//sql2.m_pReset->PutCollect("address", (_bstr_t)patient.m_patient_address);
		sql2.m_pReset->PutCollect("userbirthday", (_bstr_t)patient.m_patient_birthday);//
		sql2.m_pReset->PutCollect("history", (_bstr_t)patient.m_history);

		sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("增加病人错误"));
		return false;
	}
	return true;
}

bool CMUTDAOManagerFunc::AddDoctor(CMUTDoctorInfoFunc doctor)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		_bstr_t sql_DDL = "select * from doctor";							//sql语句
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //打开doctor数据集

		sql2.m_pReset->AddNew();                                           //数据库添加行
		//sql2.m_pReset->PutCollect("doctorid", (_bstr_t)doctor.m_doctor_userid);      //
		sql2.m_pReset->PutCollect("name", (_bstr_t)doctor.m_doctor_username);       //
		sql2.m_pReset->PutCollect("sex", (_bstr_t)doctor.m_doctor_sex);       //
		sql2.m_pReset->PutCollect("cellphone", (_bstr_t)doctor.m_doctor_cellphone);       //
		sql2.m_pReset->PutCollect("email", (_bstr_t)doctor.m_doctor_email);       //
		sql2.m_pReset->PutCollect("company", (_bstr_t)doctor.m_doctor_company);       //
		sql2.m_pReset->PutCollect("duties", (_bstr_t)doctor.m_doctor_duties);       //
		sql2.m_pReset->PutCollect("others", (_bstr_t)doctor.m_others);       //

		sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("增加医生错误"));
		return false;
	}
	return true;
}


bool CMUTDAOManagerFunc::deletePatientByname(CString patientname)
{
	CMUTAdoFunc sql;
	sql.OnInitADOConn();                      //初始化数据库连接
	sql.initRecordset();                      //创建数据集实例
	_bstr_t sql_DDL_DELETE = "select * from patient";    //要执行的sql语句
	sql.m_pReset->Open(sql_DDL_DELETE, sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic, adLockOptimistic, adCmdText);             //打开patient记录集
	CString Target_Name;                        //存放循环所得patient name
	CString Delete_Name = patientname;                    //存放选中的将要删除的好友名
	try
	{
		while (!sql.m_pReset->adoEOF)                                   //若不记录集指针不超出末尾则执行循环
		{
			Target_Name = (CString)sql.m_pReset->GetCollect("username");    //保存循环所得的好友名
			//int lx = patientname.GetLength();
			//int len = Target_Name.GetLength();

			if (Delete_Name == Target_Name)									//判断循环所得好友名是否和将要删除的好友名相等
			{
				sql.m_pReset->Delete(adAffectCurrent);                  //删除当前项
				sql.m_pReset->Update();                                 //更新数据库
				sql.CloseConn();                                        //关闭连接
				return true;											//为了性能,记得break;防止继续循环
			}
			sql.m_pReset->MoveNext();                                   //记录集指针后移一位
		}
		sql.CloseConn(); 

		CString msg = _T("未找到") + patientname;
		AfxMessageBox(msg);
		return false;
	}
	catch (...)
	{
		CString msg = _T("删除") + patientname + _T("错误");
		AfxMessageBox(msg);
		
		return false;
	}
	return true;
}

bool CMUTDAOManagerFunc::deleteDoctorByname(CString doctorname)
{
	CMUTAdoFunc sql;
	sql.OnInitADOConn();                      //初始化数据库连接
	sql.initRecordset();                      //创建数据集实例
	_bstr_t sql_DDL_DELETE = "select * from doctor";    //要执行的sql语句
	sql.m_pReset->Open(sql_DDL_DELETE, sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic, adLockOptimistic, adCmdText);             //打开patient记录集
	CString Target_Name;                        //存放循环所得patient name
	CString Delete_Name = doctorname;                    //存放选中的将要删除的好友名
	try
	{
		while (!sql.m_pReset->adoEOF)                                   //若不记录集指针不超出末尾则执行循环
		{
			Target_Name = (CString)sql.m_pReset->GetCollect("doctorname");    //保存循环所得的doctor name
			if (Delete_Name == Target_Name)                             //判断循环所得好友名是否和将要删除的好友名相等
			{
				sql.m_pReset->Delete(adAffectCurrent);                  //删除当前项
				sql.m_pReset->Update();                                 //更新数据库
				sql.CloseConn();                                        //关闭连接
				break;                                                  //为了性能,记得break;防止继续循环
			}
			sql.m_pReset->MoveNext();                                   //记录集指针后移一位
		}
		sql.CloseConn();                                                //关闭数据库连接
	}
	catch (...)
	{
		CString msg = _T("删除") + doctorname + _T("错误");
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
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		_bstr_t sql_DDL = "select * from study";							//sql语句
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //打开medical数据集

		sql2.m_pReset->AddNew();                                           //数据库添加行
		sql2.m_pReset->PutCollect("studyid", (_bstr_t)studyinfo.m_studyid);      //
		sql2.m_pReset->PutCollect("patientid", (_bstr_t)studyinfo.m_patientid);       //
		sql2.m_pReset->PutCollect("doctorid", (_bstr_t)studyinfo.m_doctorid);       //


		sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("增加studyinfo错误"));
		return false;
	}
	return true;
}

bool CMUTDAOManagerFunc::deleteStudyInfo(CString patientid,DELETE_STUDY_TYPE type)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		CString sql_DDL;
		if(type == DELETE_TYPE_PATIENTID)
		sql_DDL.Format(_T("delete from study where patientid = '%s'"),patientid);		//sql语句
		else if(type == DELETE_TYPE_STUDYID)
			 sql_DDL.Format(_T("delete form study where studyid = '%s'"),patientid);

		sql2.m_pReset->Open((_bstr_t)sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);				   //打开medical数据集

		//sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("删除studyinfo错误"));
		return false;
	}
	return true;
}
bool CMUTDAOManagerFunc::deleteDcmInfo(CString patientid)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		CString sql_DDL;
		sql_DDL.Format(_T("delete from dicomfile where patientid = '%s'"),patientid);							//sql语句
		sql2.m_pReset->Open((_bstr_t)sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);				   //打开medical数据集

		//sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("删除Dcminfo错误"));
		return false;
	}
	return true;
}
bool CMUTDAOManagerFunc::deleteDcmFile(CString filename)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		CString sql_DDL;
		sql_DDL.Format(_T("delete from dicomfile where filename = '%s'"),filename);							//sql语句
		sql2.m_pReset->Open((_bstr_t)sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);				   //打开medical数据集

		//sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("删除dicomfile错误"));
		return false;
	}
	return true;
}
bool CMUTDAOManagerFunc::addDicomFile(CMUTDicomFileFunc dicomfile)
{
	try
	{
		CMUTAdoFunc sql2;
		sql2.OnInitADOConn();               //初始化数据库连接
		sql2.initRecordset();               //创建记录集实例
		_bstr_t sql_DDL = "select * from dicomfile";							//sql语句
		sql2.m_pReset->Open(sql_DDL, sql2.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);     //打开dicomfile数据集

		sql2.m_pReset->AddNew();                                           //数据库添加行
		sql2.m_pReset->PutCollect("dicomfileid", (_bstr_t)dicomfile.m_dicomfileid);      //
		sql2.m_pReset->PutCollect("studyid", (_bstr_t)dicomfile.m_studyid);       //
		sql2.m_pReset->PutCollect("patientid", (_bstr_t)dicomfile.m_patientid);       //
		sql2.m_pReset->PutCollect("directory", (_bstr_t)dicomfile.m_directory);       //
		sql2.m_pReset->PutCollect("filename", (_bstr_t)dicomfile.m_filename);       //

		sql2.m_pReset->Update();                                           //更新数据表
		sql2.CloseConn();												  //关闭连接
	}
	catch (...)
	{
		AfxMessageBox(_T("增加DicomFile错误"));
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
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from study where patientid='%s'"), patientid);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集


		while (!sql.m_pReset->adoEOF)                                           //记录集不超出末尾时执行循环
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

			sql.m_pReset->MoveNext();                                                         //记录集指针后移一位
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
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from dicomfile where patientid='%s'"), ptid);
		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集

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
		AfxMessageBox(_T("删除DicomFile错误"));
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
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  

		CString sql_DDL;
		sql_DDL.Format(_T("select * from dicomfile  where studyid='%s'and patientid='%s'"), studyid,ptid);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集



		while (!sql.m_pReset->adoEOF)                                           //记录集不超出末尾时执行循环
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


			sql.m_pReset->MoveNext();                                                         //记录集指针后移一位
		}

		sql.CloseConn();
	}
	catch (_com_error e)
	{
		//CLogout("catch dicomfile info error %s \r\n", e.ErrorMessage());
		AfxMessageBox(_T("获取DicomFile错误"));

	}

	return dicomfile_list;
}
bool CMUTDAOManagerFunc:: deleteTableData(CString tbName)
{
	try
	{
		CMUTAdoFunc sql;
		sql.OnInitADOConn();                             //初始化数据库链接
		sql.initRecordset();                             //创建记录集对象指针实例  

		CString sql_DDL;
		sql_DDL.Format(_T("delete from %s"),tbName);

		sql.m_pReset->Open((_bstr_t)sql_DDL, sql.m_pConn.GetInterfacePtr(), \
			adOpenDynamic, adLockOptimistic, adCmdText);   //打开记录集
		sql.CloseConn();
	}
	catch (_com_error e)	
	{
		AfxMessageBox(_T("删除数据库表格失败"));
		return FALSE;
	}

	return TRUE;
}
