#pragma once
#include "MutBitmap.h"

// CMUTSplashDlg 对话框

class CMUTSplashDlg : public CDialog
{
	DECLARE_DYNAMIC(CMUTSplashDlg)

public:
	CMUTSplashDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTSplashDlg();

// 对话框数据
	enum { IDD = IDD_START_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
private:
	CMutBitmap m_bitmap;
public:
	afx_msg void OnPaint();
	void Create(UINT nID);
};
