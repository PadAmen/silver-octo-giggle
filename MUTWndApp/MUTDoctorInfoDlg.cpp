// MUTDoctorInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <ctype.h> 
#include "StringConvert.h"
#include "MUTWndApp.h"
#include "MUTDoctorInfoDlg.h"



// CMUTDoctorInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMUTDoctorInfoDlg, CDialog)

CMUTDoctorInfoDlg::CMUTDoctorInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTDoctorInfoDlg::IDD, pParent)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	newFont.CreatePointFont(APP_FONT_POINT,APP_FONT_FACENAME,NULL);//创建一个新的字体
	m_pAdoManager = CMUTDAOManagerFunc::GetDAOManager();
}

CMUTDoctorInfoDlg::~CMUTDoctorInfoDlg()
{
	newFont.DeleteObject();
}

void CMUTDoctorInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_STATIC, m_TextStatic);
	DDX_Control(pDX, IDC_MOTEXT_STATIC, m_ModifyStatic);
	DDX_Control(pDX, IDC_ADD_BTN, m_AddBtn);
	DDX_Control(pDX, IDC_NAME_EDIT, m_NameEdit);
	DDX_Control(pDX, IDC_PHONE_EDIT, m_PhoneEdit);
	DDX_Control(pDX, IDC_EMAIL_EDIT, m_EmailEdit);
	DDX_Control(pDX, IDC_COMPANY_EDIT, m_CompanyEdit);
	DDX_Control(pDX, IDC_DUTIES_EDIT, m_DutiesEdit);
	DDX_Control(pDX, IDC_OTHERS_EDIT, m_OthersEdit);
}

BEGIN_MESSAGE_MAP(CMUTDoctorInfoDlg, CDialog)
	ON_WM_CTLCOLOR()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMUTDoctorInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMUTDoctorInfoDlg::OnBnClickedAddBtn)
END_MESSAGE_MAP()


// CMUTDoctorInfoDlg 消息处理程序
BOOL CMUTDoctorInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("About Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}

	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}

BOOL CMUTDoctorInfoDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTDoctorInfoDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);
	
	nowRect.left = (APP_SCREEN_WIDTH - DCINFO_MOTEXT_WIDTH)/2;
	nowRect.right = nowRect.left + DCINFO_MOTEXT_WIDTH;
	nowRect.top  = DCINFO_BORDER_SPACE;
	nowRect.bottom = nowRect.top + DCINFO_MOTEXT_HEIGHT;
	m_ModifyStatic.MoveWindow(&nowRect);
 
	int width = (APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE)/3;
	nowRect.left = DCINFO_BORDER_SPACE;
	nowRect.right = nowRect.left + width;
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE1;
	nowRect.bottom = nowRect.top + DCINFO_TEXT_HEIGHT;
	m_TextStatic.MoveWindow(&nowRect);

	width = (APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE)*2/3;
	int height = (DCINFO_TEXT_HEIGHT - (DCINFO_INPUT_NUM-1)*DCINFO_HEIGHT_SPACE)/DCINFO_INPUT_NUM;
	nowRect.left = nowRect.right;
	nowRect.right = nowRect.left + width;
	//nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_NameEdit.MoveWindow(&nowRect);
	
	//nowRect.left = nowRect.right;
	//nowRect.right = nowRect.left + width;
	((CButton*)GetDlgItem(IDC_MAN_RADIO))->GetWindowRect(&rct);
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	((CButton*)GetDlgItem(IDC_MAN_RADIO))->MoveWindow(&nowRect);
	m_EditStart.CopyRect(&nowRect);

	nowRect.left +=  DCINFO_RADIO_SPACE;
	nowRect.right = nowRect.left + rct.Width();				//接上一个Radio
	//nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	((CButton*)GetDlgItem(IDC_WOMAN_RADIO))->MoveWindow(&nowRect);
 
	nowRect.CopyRect(&m_EditStart);
	nowRect.right = nowRect.left + width;
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_PhoneEdit.MoveWindow(&nowRect);

	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_EmailEdit.MoveWindow(&nowRect);

	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_CompanyEdit.MoveWindow(&nowRect);

	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_DutiesEdit.MoveWindow(&nowRect);

	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_OthersEdit.MoveWindow(&nowRect);

	nowRect.left = DCINFO_BORDER_SPACE;
	nowRect.right = nowRect.left + (APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE);
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_AddBtn.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTDoctorInfoDlg::InitComStyle(void)
{
	m_AddBtn.DrawBorder(FALSE);	
	m_AddBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_AddBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_AddBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_AddBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_ModifyStatic.SetFont(&newFont);
	m_ModifyStatic.SetWindowText(_T("修改资料"));
	m_AddBtn.SetWindowText(_T("增加"));

	CButton *pManBtn = (CButton *)GetDlgItem(IDC_MAN_RADIO);
	CButton *pWomanBtn = (CButton *)GetDlgItem(IDC_WOMAN_RADIO);

	pManBtn->SetWindowText(_T("男"));
	pWomanBtn->SetWindowText(_T("女"));
	pManBtn->SetCheck(TRUE);
	pWomanBtn->SetCheck(FALSE);
// 	pManBtn->ShowWindow(TRUE);
// 	pWomanBtn->ShowWindow(TRUE);
	CString str;
	str.Format(_T("姓名\r\n\n\n性别\r\n\n\n手机号\r\n\n\n邮箱\r\n\n\n单位\r\n\n\n职务\r\n\n\n备注"));
	m_TextStatic.SetWindowText(str);

	return TRUE;
}

HBRUSH CMUTDoctorInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_STATIC||nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_TEXT_COLOR1);

	}
// 	if(nCtlColor == CTLCOLOR_EDIT)
// 	{
// 		m_NameEdit.CtlColor(pDC,nCtlColor);
// 		//m_NameEdit.CtlColor(pDC,nCtlColor);
// 		//m_NameEdit.CtlColor(pDC,nCtlColor);
// 		//m_NameEdit.CtlColor(pDC,nCtlColor);
// 		
// 	}
	return GetWndBkHBrush();
}
void CMUTDoctorInfoDlg::ClearControl()
{
	m_NameEdit.SetSel(0, -1);
	m_NameEdit.Clear();
	m_PhoneEdit.SetSel(0, -1);
	m_PhoneEdit.Clear();
	m_EmailEdit.SetSel(0, -1);
	m_EmailEdit.Clear();
	m_CompanyEdit.SetSel(0, -1);
	m_CompanyEdit.Clear();
	m_DutiesEdit.SetSel(0, -1);
	m_DutiesEdit.Clear();
	m_OthersEdit.SetSel(0, -1);
	m_OthersEdit.Clear();
}

void CMUTDoctorInfoDlg::OnBnClickedAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CMUTDoctorInfoFunc doctorInfo;
	CString	str;
	m_NameEdit.GetWindowText(str);
	doctorInfo.m_doctor_username = str;
	if (doctorInfo.m_doctor_username.IsEmpty())
	{
		AfxMessageBox(_T("doctor username不能为空"));
		return;
	}

	if (m_pAdoManager->QueryDoctorByType(doctorInfo.m_doctor_username, QUERY_TYPE_USERNAME))
	{
		return;
	}
	CButton *pManBtn = (CButton *)GetDlgItem(IDC_MAN_RADIO);
	CButton *pWomanBtn = (CButton *)GetDlgItem(IDC_WOMAN_RADIO);

	if(pManBtn->GetCheck())
		doctorInfo.m_doctor_sex = _T("男");
	else if(pWomanBtn->GetCheck())
		 doctorInfo.m_doctor_sex = _T("女");

	m_PhoneEdit.GetWindowText(str);
	//str.Format(_T("%s"),pbuf);
	doctorInfo.m_doctor_cellphone = str;
	if (doctorInfo.m_doctor_cellphone.IsEmpty())
	{
		AfxMessageBox(_T("doctor cellphone不能为空"));
		return;
	}
	int lenNumber = doctorInfo.m_doctor_cellphone.GetLength();	
	if( lenNumber != 11)
	{
		AfxMessageBox(_T("doctor cellphone格式不正确"));
		return;
	}
	TCHAR pTBuf[256];
	//CHAR  pBuf[256];
	memset(pTBuf,0,sizeof(pTBuf));
	wcscpy(pTBuf,doctorInfo.m_doctor_cellphone.GetBuffer());
	
	do 
	{
		//int i = isdigit('5');//????
		if(!isdigit(pTBuf[lenNumber-1]))
		{	
			AfxMessageBox(_T("doctor cellphone中有字符"));
			return;
		}
		
	} while (--lenNumber != 0);

	m_EmailEdit.GetWindowText(str);
	doctorInfo.m_doctor_email = str;
	m_CompanyEdit.GetWindowText(str);
	doctorInfo.m_doctor_company = str;
	m_DutiesEdit.GetWindowText(str);
	doctorInfo.m_doctor_duties = str;
	m_OthersEdit.GetWindowText(str);
	doctorInfo.m_others = str;
	
	if (m_pAdoManager->AddDoctor(doctorInfo))
	{
		//OnOK();
	}
	ClearControl();
	this->ShowWindow(FALSE);
	::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_doctor_index,(LPARAM)this);
}
void CMUTDoctorInfoDlg::OnOK()   //重载OnOK do nothing
{
	//CDialog::OnOK(); 
}
