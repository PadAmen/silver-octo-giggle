#pragma once
#include "afxcmn.h"


// CMUTProcessDlg �Ի���

class CMUTProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(CMUTProcessDlg)

public:
	CMUTProcessDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMUTProcessDlg();

// �Ի�������
	enum { IDD = IDD_PROCESS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_ProcessBar;
};
