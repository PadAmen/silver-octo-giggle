#pragma once
#include "MUTGlobal.h"
#include "BCMenu.h"
#include "BtnST.h"
#include "MUTApplyMenuCWnd.h"
#include "CISBitmap.h"
#include "ShadeButtonST.h"
#include "MUTScanbMainDlg.h"
#include "MUTDlgBaseFunc.h"
#include "afxcmn.h"
#include "GdipButton.h"
//#include "MUTScanbMainDlg.h"
/*#include "CxImage/CxImage/ximage.h"*/

// CApplyWnd 对话框


class CMUTApplyMainDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTApplyMainDlg)

public:
	CMUTApplyMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTApplyMainDlg();

// 对话框数据
	enum { IDD = IDD_APPLY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

private:
/*	CxImage			m_PngImage;*/
 	CButtonST		m_LeftBtn;
	//CWinXPButtonST	m_StartBtn;
	//CGdipButton		m_StartBtn;
	CShadeButtonST		m_StartBtn;
	//CButtonST		m_UpdateBtn;
	CGdipButton		m_UpdateBtn;
	CGdipButton		m_LineBtn;
	CGdipButton		m_CurveBtn;

	CMUTApplyMenuCWnd	m_AppMenu;
	//CMUTScanbMainDlg	m_ScanbDlg;

	CRect			m_UpdatRect;
	HWND			m_hMainWnd;
	//UINT			m_uCurIndex;		//当前页面索引
	UINT			m_uSelectedIndex;	//切换页面索引
	//BOOL			m_bIsMenuExpan;
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMenuBtn();

	void SetHMainWnd(HWND hMainWnd){m_hMainWnd = hMainWnd;};
	void SelectPageIndex(UINT uIndex){m_uSelectedIndex = uIndex;};
		
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedUpdateBtn();
	void	ShowProgress();
	//void	SetThreadHandle(HANDLE InitThread=NULL){m_InitThread = InitThread;};

	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	CGdipButton m_RadioCurveBtn;
	CGdipButton m_RadioLineBtn;
public:
	afx_msg void OnBnClickedRadioLine();
	afx_msg void OnBnClickedRadioCurve();
	void ResumeInitState();
};

