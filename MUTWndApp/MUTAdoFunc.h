#pragma once
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") 
class CMUTAdoFunc
{
public:
	CMUTAdoFunc(void);
	~CMUTAdoFunc(void);
	_RecordsetPtr m_pReset;     //������¼��ָ��
	_ConnectionPtr m_pConn;     //��������ָ��

	BOOL OnInitADOConn();       //������ʼ�����Ӻ���
	void initRecordset();       //����������¼��ʵ������
	void CloseRecordset();      //�����رռ�¼��ʵ������
	void CloseConn();           //�����ر����Ӻ���
};


