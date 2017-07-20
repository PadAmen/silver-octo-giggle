#pragma once
#include "btnst.h"
#include "mySliderControl.h"
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"
#include "MUTWndApp.h"

// CFreezeBtmWnd �Ի���

class CMUTScanbFBtmCWnd : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTScanbFBtmCWnd)

public:
	CMUTScanbFBtmCWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMUTScanbFBtmCWnd();

// �Ի�������
	enum { IDD = IDD_SWND_FRZE_BTM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

public:
	/*BOOL GetParentSize(CRect rct);*/
	BOOL InitWindow(void);
	BOOL InitComStyle(void);
	BOOL InitComRect(void);

private:
	CmySliderControl m_MovSlider;
	CButtonST m_PlayBtn;
	CButtonST m_MListBtn;

	BOOL	m_bIsMoiveRun;
	volatile BOOL	*m_pRun;

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnMlist();
	void	GetParentRunPtr(volatile BOOL *bRun){m_pRun = bRun;};
	void	SetRun(bool bRun){*m_pRun = bRun;};
	void	ResumeInitState();
private:
	BOOL m_bIsList;
};
