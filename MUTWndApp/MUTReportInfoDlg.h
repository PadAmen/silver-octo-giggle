#pragma once
#include "MUTDlgBaseFunc.h"
#include "btnst.h"
#include "listimagectrl_h.h"
#include "editst.h"
#include "MUTGlobal.h"
#include "MUTPatientReportDlg.h"

// CMUTReportInfoDlg 对话框

class CMUTReportInfoDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTReportInfoDlg)

public:
	CMUTReportInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTReportInfoDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_REPORTINFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void ControlShow(UINT index,BOOL bShow);
private:
	CButtonST m_ExitBtn;
	CButtonST m_SarchBtn;
	CButtonST m_ModifyBtn;

	CButtonST m_SelectBtn;
	CButtonST m_CancelBtn;
	CButtonST m_DeleteBtn;
	CButtonST m_ExportBtn;
	CButtonST m_CompareBtn;
	CEditST m_InputEdit;
	TGPATIENT m_clickpatient;

	BOOL  m_bEdit;

public:
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedExitBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnPaint();
private:
	//BOOL m_bIsDcmUpdate;
	CMUTDAOManagerFunc	*m_AdoManger;
	CMUTPatientReportDlg *m_ReportDlg;
public:
	CListImageCtrl_H m_DcmList;
	void	GetReportPtr(DWORD usr){m_ReportDlg = (CMUTPatientReportDlg *)usr;};
	afx_msg void OnBnClickedSelectdBtn1();
	afx_msg void OnBnClickedDeleteBtn1();
	afx_msg void OnBnClickedCancelBtn1();
	afx_msg void OnBnClickedExportBtn1();
};
