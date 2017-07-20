#pragma once
#include "btnst.h"
#include "afxwin.h"
#include "EditST.h"
#include "ListBoxST.h"
#include "ListImageCtrl.h"
#include "MUTDlgBaseFunc.h"
#include "MUTPatientReportDlg.h"
#include "MUTDAOManagerFunc.h"
// #include "resource.h"
// CMUTCaseReportDlg 对话框
class CMUTPatientReportDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTPatientReportDlg)

public:
	CMUTPatientReportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTPatientReportDlg();

// 对话框数据
	enum { IDD = IDD_REPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	
private:
	CButtonST m_ExitBtn;
	CButtonST m_DeleteBtn;
	CButtonST m_ModifyBtn;

	CButtonST m_SelectBtn;
	CButtonST m_CancelBtn;
	CButtonST m_DeleteBtn1;
	CButtonST m_ExportBtn;
	CButtonST m_CompareBtn;
	CEditST m_InputEdit;
	CStatic m_TextStatic;
	BOOL	m_bEdit;

	CFont	StaticFont;  //Font对象必须为成员变量 不能是局部变量，否则无法改变大小
	//CFont	newFont1;
	CRect	m_EditRect;
	CMUTDAOManagerFunc	*m_AdoManger;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);
	
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedExitBtn();
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedSelectBtn();
	afx_msg void OnBnClickedCancelBtn();
	afx_msg void OnBnClickedDelete1Btn();
	afx_msg void OnBnClickedExportBtn();
	void ControlShow(UINT index,BOOL bShow);
	CRect GetEditRect(){return m_EditRect;};
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	CImageList m_ImageList;
	CRect			m_ListBoxRect;
	BOOL			m_bCheckAcessNow;
	BOOL			m_bIsDownNow;
	BOOL			m_bIsDcmUpdate;

public:
	CListBoxST m_ReportList;
	afx_msg void OnPaint();
	void CreateImageList();
	CImage ConvertPngToBmp(CString strImg);
	void AcessInfoToDisplay();
	void SetAcessCheck(){m_bCheckAcessNow = TRUE;};
	TGPATIENT GetClickPatient();
	virtual void OnOK( );
	DECLARE_MESSAGE_MAP()
};
