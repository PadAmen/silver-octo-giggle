#pragma once
#include "MUTGlobal.h"
#include "btnst.h"
#include "EditST.h"
#include "afxwin.h"

// CMtextWnd 对话框

class CMUTScanbTextOWnd : public CDialog
{
	DECLARE_DYNAMIC(CMUTScanbTextOWnd)

public:
	CMUTScanbTextOWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanbTextOWnd();

// 对话框数据
	enum { IDD = IDD_TEXT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CBrush m_brush;
	CEditST m_TextEdit;
	CString m_StrText;
	HWND	m_hMainWnd;
public:
	CButtonST m_TextBtn;
	afx_msg void OnBnClickedButton1();	
	void	GetHMainWnd(HWND hwnd){m_hMainWnd = hwnd;};
	//BOOL	GetStrText(CString str){ m_StrText = str;};
};
