#pragma once
#include "MUTGlobal.h"
#include "MUTWndApp.h"
#include "winxpbuttonst.h"
#include "MUTDlgBaseFunc.h"


// CApplyMenuWnd 对话框

class CMUTApplyMenuCWnd : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTApplyMenuCWnd)

public:
	CMUTApplyMenuCWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTApplyMenuCWnd();

// 对话框数据
	enum { IDD = IDD_APPLY_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CWinXPButtonST m_FileBtn;
	CWinXPButtonST m_SetBtn;
	CWinXPButtonST m_TeachBtn;
	CWinXPButtonST m_OperaBtn;

	HWND	m_hMainWnd;
	CRect	m_rcLeftBtn;
public:
	BOOL InitWindow(void);
	BOOL GetParentSize(CRect rct);
	void GetHMainWnd(HWND hMainWnd){m_hMainWnd = hMainWnd;};
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedTeachBtn();
	afx_msg void OnBnClickedFileBtn();
};
