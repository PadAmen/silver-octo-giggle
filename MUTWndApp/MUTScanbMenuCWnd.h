#pragma once
#include "btnst.h"


// CScanBMenu �Ի���

class CMUTScanbMenuCWnd : public CDialog
{
	DECLARE_DYNAMIC(CMUTScanbMenuCWnd)

public:
	CMUTScanbMenuCWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMUTScanbMenuCWnd();

// �Ի�������
	enum { IDD = IDD_SCANB_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
