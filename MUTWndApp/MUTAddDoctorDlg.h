#pragma once
#include "afxwin.h"
#include "btnst.h"
#include "EditST.h"
#include "MUTGlobal.h"
#include "MUTWndApp.h"
#include "MUTDlgBaseFunc.h"
#include "MUTDoctorInfoDlg.h"
#include "MUTDAOManagerFunc.h"
#include "MUTScanbMainDlg.h"
//#include "MUTScanOverDlg.h"



// CDoctorWnd 对话框

class CMUTAddDoctorDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTAddDoctorDlg)

public:
	CMUTAddDoctorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTAddDoctorDlg();

// 对话框数据
	enum { IDD = IDD_DOCTOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual	BOOL OnInitDialog();
private:
	CButtonST m_SearchBtn;	
	CButtonST m_AddBtn;
	CButtonST m_SelectBtn;
	CButtonST m_ExitBtn;
	CEditST m_InputEdit;
	CListBox m_DoctorList;


	HWND			m_hMainWnd;
	//HWND			m_hScanbWnd;
	UINT			m_uIndex;
	CFont			newFont;
	CString			m_SelectDoctor;
	BOOL			m_bCheckAcessNow;
	BOOL			m_bIsOverDlgSend;

	CMUTDAOManagerFunc	*m_AdoManger;
	CMUTScanbMainDlg	*m_pScanbWnd;
	//CMUTScanOverDlg		*m_pScanOverWnd;
public:

	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);

	//void SetHMainWnd(HWND hMainWnd){m_hMainWnd = hMainWnd;};
	void GetScanbPtr(DWORD usr){m_pScanbWnd = (CMUTScanbMainDlg *)usr;};
	//void GetScanOverPtr(DWORD usr){m_pScanOverWnd = (CMUTScanOverDlg *)usr;};
	void SelectPageIndex(UINT uIndex){m_uIndex = uIndex;};
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedSearchBtn();
	afx_msg void OnBnClickedExitBtn();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedSelectBtn();
	void  SetCheckAccess(){m_bCheckAcessNow = TRUE;};
	LRESULT OnRecvLastWnd(WPARAM wParam,LPARAM lParam);
};
