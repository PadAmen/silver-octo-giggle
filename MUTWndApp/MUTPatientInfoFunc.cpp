#include "stdafx.h"
#include "MUTPatientInfoFunc.h"
#include "MUTGlobal.h"

CMUTPatientInfoFunc::CMUTPatientInfoFunc()
{
	m_patient_userid = APP_NULL_STR;
	m_patient_username = APP_NULL_STR;
	m_patient_sex = APP_NULL_STR;
	m_patient_birthday = APP_NULL_STR;
	m_history = APP_NULL_STR;
	 //m_doctorid = _T("");
	 //m_doctorname = _T("");
}


CMUTPatientInfoFunc::~CMUTPatientInfoFunc()
{
}
