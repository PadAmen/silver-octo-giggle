#pragma once
#include "MUTGlobal.h"
#include "MUTDlgBaseFunc.h"
#include "btnst.h"
#include "MUTReportInfoDlg.h"
#include "MUTScanbMainDlg.h"
#include "MUTScanOverDlg.h"


// CMUTEditImgDlg 对话框

class CMUTEditImgDlg : public CDialog,public CMUTDlgBaseFunc
{
	DECLARE_DYNAMIC(CMUTEditImgDlg)

public:
	CMUTEditImgDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTEditImgDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_EDITIMG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL InitComRect(void);
	BOOL InitComStyle(void);
	BOOL InitWindow(void);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CMUTReportInfoDlg *pReportInfoDlg;
	CMUTScanbMainDlg  *pScanbMainDlg;
	CMUTScanOverDlg   *pScanOverDlg;
	CButtonST m_ExportBtn;
	CButtonST m_DeleteBtn;
	CButtonST m_SendBtn;

	CRect		m_rcImageRgn;
	CRgn		m_ImgRgn;
	CFont		newFont1;			//add 8.10
	CString		m_clickname;

	BOOL		m_bIsClickFromScanb;
	BOOL		m_bIsClickFromReportInfo;
	BOOL		m_bIsClickFromScanOver;
public:
	afx_msg void OnBnClickedExportBtn();
	afx_msg void OnPaint();
	void    GetReportInfoPtr(DWORD usr){pReportInfoDlg = (CMUTReportInfoDlg*)usr;};
	void	GetScanbMainPtr(DWORD usr){pScanbMainDlg = (CMUTScanbMainDlg *)usr;};
	void	GetScanOverPtr(DWORD usr){pScanOverDlg = (CMUTScanOverDlg *)usr;};

	void	OpenImageFile(CDC *pDC,CString bmpName);
	afx_msg void OnBnClickedDeleteBtn();
	virtual void OnOK( );
};
