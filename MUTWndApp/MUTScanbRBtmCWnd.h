#pragma once
#include "btnst.h"
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"
// CRunBtmWnd �Ի���

class CMUTScanbRBtmCWnd : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNCREATE(CMUTScanbRBtmCWnd)

public:
	CMUTScanbRBtmCWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMUTScanbRBtmCWnd();

// �Ի�������
	enum { IDD = IDD_SWND_RUN_BTM};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	CButtonST m_NormalBtn;
	CButtonST m_BloodBtn;
	CButtonST m_OrganBtn;
	CButtonST m_MuslBtn;

	INT		  m_OrganIndex;
public:
	BOOL InitWindow(void);
	BOOL InitComStyle(void);
	BOOL InitComRect(void);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnNormal();
	afx_msg void OnBnClickedBtnBlood();
	afx_msg void OnBnClickedBtnOrgan();
	afx_msg void OnBnClickedBtnMus();
	DWORD GetBtnObject(INT index);
	void  ResetDeviceGain();
	void  ResumeInitState();	
};
