#pragma once
#include "MutBitmap.h"

// CMUTSplashDlg �Ի���

class CMUTSplashDlg : public CDialog
{
	DECLARE_DYNAMIC(CMUTSplashDlg)

public:
	CMUTSplashDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMUTSplashDlg();

// �Ի�������
	enum { IDD = IDD_START_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
private:
	CMutBitmap m_bitmap;
public:
	afx_msg void OnPaint();
	void Create(UINT nID);
};
