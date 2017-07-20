#pragma once
#include "btnst.h"


// CScanBMenu 对话框

class CMUTScanbMenuCWnd : public CDialog
{
	DECLARE_DYNAMIC(CMUTScanbMenuCWnd)

public:
	CMUTScanbMenuCWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanbMenuCWnd();

// 对话框数据
	enum { IDD = IDD_SCANB_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	private:
	CButtonST m_FileBtn;
	CButtonST m_OperaBtn;
	CButtonST m_TeachBtn;
	CButtonST m_PuncBtn;
	CButtonST m_SpecialBtn;
	CButtonST m_SetBtn;
	CButtonST m_AboutBtn;

};
