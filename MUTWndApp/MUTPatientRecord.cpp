// MUTPatientRecord.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTPatientRecord.h"


// CMUTPatientRecord 对话框

IMPLEMENT_DYNAMIC(CMUTPatientRecord, CDialog)

CMUTPatientRecord::CMUTPatientRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTPatientRecord::IDD, pParent)
{

}

CMUTPatientRecord::~CMUTPatientRecord()
{
}

void CMUTPatientRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMUTPatientRecord, CDialog)
END_MESSAGE_MAP()


// CMUTPatientRecord 消息处理程序
