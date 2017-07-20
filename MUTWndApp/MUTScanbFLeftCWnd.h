#pragma once
#include "atltypes.h"
#include "btnst.h"
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"
#include "MUTMeasureFunc.h"
#include "MUTScanbTextOWnd.h"


// CRunWnd 对话框

class CMUTScanbFLeftCWnd : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTScanbFLeftCWnd)

public:
	CMUTScanbFLeftCWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanbFLeftCWnd();

// 对话框数据
	enum { IDD = IDD_SWND_FRZE_LEFT };

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
	CButtonST m_MeaLenBtn;
	CButtonST m_MeaAreaBtn;
	CButtonST m_MeaArrBtn;
	CButtonST m_MeaAngBtn;
	CButtonST m_MeaCirBtn;
	CButtonST m_MeaTextBtn;
	CButtonST m_MeaUndoBtn;
	CButtonST m_MeaNDoallBtn;

	CRect m_rcParent;
	INT		m_MeaIndex;
	//BOOL	m_bMeaSelected;
public:
	CMUTScanbTextOWnd		m_TextWnd;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnLen();
	CMUTMeasureFunc	*m_pMeaFun;
	afx_msg void OnBnClickedBtnLast();
	afx_msg void OnBnClickedBtnAll();
	BOOL GetBtnClickState();
	afx_msg void OnBnClickedBtnArea();
	DWORD GetBtnObject(INT index=0);
	afx_msg void OnBnClickedBtnArrw();
	afx_msg void OnBnClickedBtnAngle();
	afx_msg void OnBnClickedBtnCir();
	afx_msg void OnBnClickedBtnText();
	void	ResumeInitState();
};
