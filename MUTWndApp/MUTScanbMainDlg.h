#pragma once
#include "MUTGlobal.h"
#include "btnst.h"
#include "WinXPButtonST.h"
#include "ListImageCtrl.h"
#include "MUTDlgBaseFunc.h"
#include "afxwin.h"
#include "MUTScanbRLeftCWnd.h"
#include "MUTScanbRBtmCWnd.h"
#include "MUTScanbFLeftCWnd.h"
#include "MUTScanbFBtmCWnd.h"
#include "MUTScanbSaveOWnd.h"
#include "MUTMeDCFunc.h"
#include "MUTImgProcFunc.h"
#include "MUTDAOManagerFunc.h"




// CScanBWnd 对话框

class CMUTScanbMainDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTScanbMainDlg)

public:
	CMUTScanbMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanbMainDlg();

// 对话框数据
	enum { IDD = IDD_SCANB_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//virtual BOOL DestroyWindow( );
	DECLARE_MESSAGE_MAP()
private:
	CRect		m_rcImageRgn;
	CRect		m_rcLeftRgn;
	HWND		m_hMainWnd;
	UINT		m_uIndex;
public:
	void SetHMainWnd(HWND hMainWnd){m_hMainWnd = hMainWnd;};
	void SelectPageIndex(UINT uIndex){m_uIndex = uIndex;};
	afx_msg void OnBnClickedCloseBtn();
	BOOL InitWindow(void);
	BOOL InitThread(void);
	BOOL InitComStyle(void);
	BOOL InitComRect(void);
	BOOL SetTextFreq(DOUBLE fFreq = 0);
	BOOL SetTextFps(DOUBLE fFps = 0);
	BOOL SetTextGain(UINT uGain=0);
private:
	DOUBLE		m_fFreq;
	DOUBLE		m_fFps;
	INT			m_iGain;
	UINT		m_SaveIndex;

	BOOL		m_bIsFreeze;		//是否冻结图像	
	BOOL		m_bIsFlipImage;		//是否翻转图像
	volatile BOOL		m_bIsRun;
private:	
	CWinXPButtonST m_Doctor;
	CWinXPButtonST m_Patient;
	CWinXPButtonST m_CloseBtn;
	CButtonST	m_StateBtn;
	CButtonST	m_SaveBtn;
	CButtonST	m_ProbePosBtn;
	CButtonST	m_AddBtn;
	CButtonST	m_CutBtn;
	CButtonST	m_ModeBtn;
	CButtonST	m_ScanbMenu;
	CButtonST	m_ListBtn;
	CButtonST	m_GrayBtn;
	CStatic		m_SetDepth;
	CStatic		m_SetFreq;
	CStatic		*m_pFpsStatic;
	CStatic		m_SetFps;

	CStatic		m_MacStatic;
	CButtonST m_NetBtn;
	CButtonST m_EvalBtn;

public:	
	CMUTScanbFLeftCWnd	m_FreezeLeftWnd;
	CMUTScanbFBtmCWnd	m_FreezeBtmWnd;
	CMUTScanbRLeftCWnd		m_RunLeftWnd;
	CMUTScanbRBtmCWnd		m_RunBtmWnd;
	CMUTScanbSaveOWnd		m_SaveWnd;		//重叠窗口

	CMUTImgProcFunc			*m_pImgProc;
	CMUTDAOManagerFunc		*m_AdoManger;	
private:
	CString					m_DoctorName;
	CString					m_PatientName;
	CString					m_CurDoctorId;
	CString					m_CurPatientId;
	//CString					m_DcmFileName;

public:
	CListImageCtrl			m_ListImg;
	CRgn					m_ImgRgn;	
	CStringArray			m_DcmSavedArray;
	CStringArray			m_imageSavedArray;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedDoctorBtn();
	afx_msg void OnBnClickedPatientBtn();
	afx_msg void OnBnClickedStateBtn();
	afx_msg void OnBnClickedLeftBtn();	
	afx_msg void OnBnClickedAddBtn();
	afx_msg void OnBnClickedDecBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnBnClickedListBtn();

	BOOL  AddInfoToAccess();
	LRESULT OnAddDoctor(WPARAM wParam,LPARAM lParam);
	LRESULT OnAddPatient(WPARAM wParam,LPARAM lParam);
	LRESULT OnDisplayDcm(WPARAM wParam,LPARAM lParam);
	LRESULT OnSaveDcm(WPARAM wParam,LPARAM lParam);
	LRESULT OnUpdateRgn(WPARAM wParam,LPARAM lParam);
	LRESULT OnInputStr(WPARAM wParam,LPARAM lParam);
	LRESULT OnClearVector(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClickAbout();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnClickReport();

	void	SetImageRect(CRect rect){m_rcImageRgn.CopyRect(&rect);};
	virtual CRect GetImageRect(){return m_rcImageRgn;};
	BOOL	IsFreeze(){return m_bIsFreeze;};
	BOOL	IsRun(){return m_bIsRun;};
	BOOL	ShowStateWnd(INT iIndex);
	void	SetRun(bool bRun,bool bMask=FALSE){m_bIsRun = bRun;	if(bMask) return;setRun(bRun);};  //add 7.18	
	BOOL	GetFlipImage(){return m_bIsFlipImage;};
	CString GetCurSelectDoctor(){return m_DoctorName;};
	CString GetCurSelectPatient(){return m_PatientName;};
	void SetRunWndParam();
	void SetFreezeWndParam();
	void ResumeInitState();
	
};
