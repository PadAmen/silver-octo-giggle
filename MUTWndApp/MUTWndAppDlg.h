//

#pragma once
#include "afxcmn.h"
#include "MUTGlobal.h"
#include "MUTApplyMainDlg.h"
#include "MUTScanbMainDlg.h"
#include "MUTDlgBaseFunc.h"
#include "MUTAboutDlg.h"
#include "MUTAddDoctorDlg.h"
#include "MUTAddPatientDlg.h"
#include "MUTPatientReportDlg.h"
#include "MUTShortKeyFunc.h"
#include "MUTDoctorInfoDlg.h"
#include "MUTPatientInfoDlg.h"
#include "MUTThreadOperaFunc.h"
#include "MUTEditImgDlg.h"
#include "MUTScanOverDlg.h"
#include "MUTReportInfoDlg.h"


//#define DLG_MAX_VALUE			6
class CMUTWndAppDlg : public CDialog,public CMUTDlgBaseFunc
{
// 构造
public:
	CMUTWndAppDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FLATULT_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	LRESULT OnChangeWndMsg(WPARAM wParam,LPARAM lParam);
	LRESULT OnRtlastWndMsg(WPARAM wParam,LPARAM lParam);
	LRESULT OnWarningMsg(WPARAM wParam,LPARAM lParam);
	virtual BOOL DestroyWindow( );
private:
	CMUTApplyMainDlg		m_ApplyDlg;
	CMUTScanbMainDlg		m_ScanBDlg;
	CMUTAboutDlg			m_AboutDlg;
	CMUTAddDoctorDlg		m_DoctorDlg;
	CMUTAddPatientDlg		m_PatientDlg;
	CMUTPatientReportDlg	m_ReportDlg;
	CMUTDoctorInfoDlg		m_DoctorInfoDlg;
	CMUTPatientInfoDlg		m_PatientInfoDlg;
	CMUTEditImgDlg			m_EditImgDlg;
	CMUTScanOverDlg			m_ScanOverDlg;
	CMUTReportInfoDlg		m_ReportInfoDlg;

	//CMUTDAOManagerFunc		*m_AdoManger;

	CDialog					*m_pLastDialog;
	CDialog					*m_pCurDialog;
	CDialog					*m_pOldDialog;



	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	void CreatWindow(void);
	BOOL InitWindow(void);
	void InitParam(void);
	void TransParam(void);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void	SetConfigEnd(BOOL bInitDevEnd=TRUE){m_bInitDevEnd = bInitDevEnd;};
	BOOL	IsConfigEnded(){return m_bInitDevEnd;};
	CMUTShortKeyFunc		*m_pShortKeyFunc;
	CMUTThreadOperaFunc		*m_pThreadOpreation;

private:
	CProgressCtrl m_ProcessCtrl;
	CFont		  newFont;
	BOOL		  m_bInitDevEnd;
	vector<CDialog*>  m_DialogList;
	vector<CDialog*>  m_DialogChangeList;
};
