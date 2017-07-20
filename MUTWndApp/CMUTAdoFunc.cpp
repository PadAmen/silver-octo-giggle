#include "stdafx.h"
#include "MUTAdoFunc.h"



CMUTAdoFunc::CMUTAdoFunc(void)
{
	m_pConn = NULL;
	m_pReset = NULL;
}

CMUTAdoFunc::~CMUTAdoFunc(void)
{
}

BOOL CMUTAdoFunc::OnInitADOConn()			//������ʱ�����޸������ִ�
{
	::CoInitialize(NULL);   //  ��ʼ��COM ����
	try
	{
		m_pConn.CreateInstance(_T("ADODB.Connection"));    //�������Ӷ���ʵ��
		_bstr_t strConn = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=mut.mdb;Jet OLEDB:DataBase;");//..\\Debug\\�����ַ���
		m_pConn->Open(strConn, "", "", adModeUnknown);      //�������ݿ�
		return TRUE;
	}
	catch (_com_error e)      //��ʱ��������Ĵ��Ȳ���e....�뱨�������������e.Description()��e.ErrorMessage();
	{
		CString err = _T("");
		err.Format(_T("���ݿ����ӳ���!"));
		return false;
	}
}

void CMUTAdoFunc::initRecordset()   //�����ݼ�
{
	try
	{
		m_pReset.CreateInstance(_T("ADODB.Recordset"));  //������¼��ʵ��
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("�򿪼�¼��ʧ��!"));
		return;
	}
}

void CMUTAdoFunc::CloseRecordset()
{
	try
	{
		if (m_pReset->GetState() == adStateOpen)     //�жϼ�¼����״̬�Ƿ�Ϊ��
		{
			m_pReset->Close();                       //�رռ�¼��
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("�رռ�¼������!"));
	}
}

void CMUTAdoFunc::CloseConn()
{
	if (m_pConn->GetState() == adStateOpen)        //�ж����ݿ������Ƿ�Ϊ��
	{
		m_pConn->Close();						   //�Ͽ����ݿ����� 
	}
	::CoUninitialize();          //�ͷ�COM����
}
