#pragma once
#include "btnst.h"
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"
#include "MUTScanbMainDlg.h"
#include "MUTAddDoctorDlg.h"
#include "MUTAddPatientDlg.h"
#include "MUTThreadOperaFunc.h"
#include "afxcmn.h"


// CMUTScanOverDlg 对话框

class CMUTScanOverDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTScanOverDlg)

public:
	CMUTScanOverDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanOverDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_SCANOVER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CButtonST m_SaveBtn;
	CButtonST m_GiveupBtn;
	CButtonST m_ExportBtn;
	CButtonST m_SendBtn;
	CListImageCtrl m_ReportList1;

	BOOL m_bIsUpdate;

	SHFILEOPSTRUCT	m_fileOpStruct;
	CMUTScanbMainDlg *m_pScanbDlg;
 	CMUTAddDoctorDlg *m_pAddDoctorDlg;
 	CMUTAddPatientDlg *m_pAddPatientDlg;
	CMUTThreadOperaFunc *m_pThread;
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedGiveupBtn();
	//void deleteFilesAll();
	bool DeleteDirectoryAndFiles(CString directoryname);
	void GetScanbPtr(DWORD usr){m_pScanbDlg = (CMUTScanbMainDlg *)usr;};
 	void GetAddDoctorPtr(DWORD usr){m_pAddDoctorDlg = (CMUTAddDoctorDlg *)usr;};
 	void GetAddPatientPtr(DWORD usr){m_pAddPatientDlg = (CMUTAddPatientDlg *)usr;};
	afx_msg void OnPaint();
private:
	CButtonST m_SelectDoctorBtn;
	CButtonST m_SelectPatientBtn;
public:
	LRESULT OnAddDoctor(WPARAM wParam,LPARAM lParam);
	LRESULT OnAddPatient(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedDoctorSelectBtn();
	afx_msg void OnBnClickedPatientSelectBtn();
};
