#pragma once
#include "MUTDlgBaseFunc.h"
#include "MUTAdoFunc.h"
#include "MUTDAOManagerFunc.h"
#include "afxwin.h"
#include "btnst.h"
#include "editst.h"

// CMUTDoctorInfoDlg 对话框

class CMUTDoctorInfoDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTDoctorInfoDlg)

public:
	CMUTDoctorInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTDoctorInfoDlg();
	virtual BOOL OnInitDialog();
	
// 对话框数据
	enum { IDD = IDD_DCINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
private:
	CMUTDAOManagerFunc		*m_pAdoManager;
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);
	afx_msg HBRUSH CMUTDoctorInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
private:
	CFont	newFont;
	CStatic m_TextStatic;
	CStatic m_ModifyStatic;
	CButtonST m_AddBtn;
	CEditST m_NameEdit;
	CEditST m_PhoneEdit;
	CEditST m_EmailEdit;
	CEditST m_CompanyEdit;
	CEditST m_DutiesEdit;
	CEditST m_OthersEdit;
	CRect	m_EditStart;
	
public:
	afx_msg void OnBnClickedAddBtn();
	void ClearControl();
	virtual void OnOK( );
};
