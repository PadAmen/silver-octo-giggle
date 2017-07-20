#pragma once
#include "MUTGlobal.h"
#include "MUTWndApp.h"
#include "MUTDlgBaseFunc.h"
#include "btnst.h"
#include "GdipButton.h"
#include "afxwin.h"

// CAboutWnd 对话框

class CMUTAboutDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTAboutDlg)

public:
	CMUTAboutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

private:
	CButtonST		m_UpdateBtn;	
	CGdipButton		m_IconBtn;
	CStatic m_HardStatic;
	CStatic m_SoftStatic;

	HWND			m_hMainWnd;
	UINT			m_uIndex;
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);

	void SetHMainWnd(HWND hMainWnd){m_hMainWnd = hMainWnd;};
	void SelectPageIndex(UINT uIndex){m_uIndex = uIndex;};

	DECLARE_MESSAGE_MAP()

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedAboutUbtn();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
