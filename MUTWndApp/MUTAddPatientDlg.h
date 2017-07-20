#pragma once
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"
#include "MUTDAOManagerFunc.h"
#include "btnst.h"
#include "afxwin.h"
//#include "MUTScanOverDlg.h"
#include "MUTScanbMainDlg.h"

// CPatientWnd 对话框

class CMUTAddPatientDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTAddPatientDlg)

public:
	CMUTAddPatientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTAddPatientDlg();

// 对话框数据
	enum { IDD = IDD_PATIENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual	BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CButtonST m_SelectBtn;
	CButtonST m_AddBtn;
	CButtonST m_TextBtn;
	CListBox m_PatientList;
	CString			m_SelectPatient;
	CFont			newFont;
	CFont			newFont1;
	UINT			m_uIndex;
	BOOL			m_bIsCheckAccessNow;
	BOOL			m_bIsOverDlgSend;
	
	CMUTDAOManagerFunc	*m_AdoManger;
	CMUTScanbMainDlg	*m_pScanbWnd;
	//CMUTScanOverDlg		*m_pScanOverWnd;
public:

	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);

	void GetScanbPtr(DWORD usr){m_pScanbWnd = (CMUTScanbMainDlg *)usr;};
	//void GetScanOverPtr(DWORD usr){m_pScanOverWnd = (CMUTScanOverDlg *)usr;};
	void SelectPageIndex(UINT uIndex){m_uIndex = uIndex;};
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearchBtn();	
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSelectBtn();
	void	SetCheckAccess(){m_bIsCheckAccessNow = TRUE;};
	LRESULT OnRecvLastWnd(WPARAM wParam,LPARAM lParam);
};
