#pragma once
#include "MUTDlgBaseFunc.h"
#include "MUTDAOManagerFunc.h"
#include "afxwin.h"
#include "btnst.h"
#include "editst.h"


// CMUTPatientInfoDlg 对话框
// #define  DCINFO_INPUT_NUM		7
class CMUTPatientInfoDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTPatientInfoDlg)

public:
	CMUTPatientInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTPatientInfoDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_PTINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
	//afx_msg void OnBnClickedButton1();
private:
	CStatic m_TextStatic;
	CButtonST m_AddBtn;
	CButtonST m_PhotoBtn;
	CEditST m_IdEdit;
	CEditST m_NameEdit;
	CEditST m_BirthdayEdit;
	CEditST m_HistoryEdit;
	CRect	m_EditStart;
	CMUTDAOManagerFunc *m_pAdoManager;
public:
	afx_msg void OnBnClickedAddBtn();
	void ClearControl();
	virtual void OnOK( );

};
