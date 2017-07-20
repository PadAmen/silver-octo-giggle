#pragma once
#include "afxcmn.h"


// CMUTProcessDlg 对话框

class CMUTProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(CMUTProcessDlg)

public:
	CMUTProcessDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTProcessDlg();

// 对话框数据
	enum { IDD = IDD_PROCESS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl m_ProcessBar;
};
