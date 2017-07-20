#pragma once
#include "atltypes.h"
#include "btnst.h"
#include "afxwin.h"
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"


// CRunWnd 对话框
class CMUTScanbRLeftCWnd : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTScanbRLeftCWnd)

public:
	CMUTScanbRLeftCWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanbRLeftCWnd();

// 对话框数据
	enum { IDD = IDD_SWND_RUN_LEFT};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	BOOL GetParentSize(CRect rct);
	BOOL InitWindow(void);
	BOOL InitComStyle(void);
	BOOL InitComRect(void);
private:
	CRect m_rcParent;
	CButtonST m_AddBtn;
	CButtonST m_CutBtn;
	CStatic m_SetDepth;
	CStatic m_DepthStatic;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL SetTextDepth(UINT uDepth=0);
	INT  GetDepth(){return m_iDepth;};
	LONG GetDistance(){return (LONG)(m_iDepth*PIXEL_PER_CM);};
private:
	INT m_iDepth;
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDec();
	void SetParameterForMIAndTI();
	void ResumeInitState();
};
