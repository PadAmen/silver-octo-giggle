// MUTPatientInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTPatientInfoDlg.h"


// CMUTPatientInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMUTPatientInfoDlg, CDialog)

CMUTPatientInfoDlg::CMUTPatientInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTPatientInfoDlg::IDD, pParent)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	m_pAdoManager = CMUTDAOManagerFunc::GetDAOManager();
}

CMUTPatientInfoDlg::~CMUTPatientInfoDlg()
{
}

void CMUTPatientInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_STATIC, m_TextStatic);
	DDX_Control(pDX, IDC_ADD_BTN, m_AddBtn);
	DDX_Control(pDX, IDC_PHOTO_BTN, m_PhotoBtn);
	DDX_Control(pDX, IDC_ID_EDIT, m_IdEdit);
	DDX_Control(pDX, IDC_NAME_EDIT, m_NameEdit);
	DDX_Control(pDX, IDC_BIRTHDAY_EDIT, m_BirthdayEdit);
	DDX_Control(pDX, IDC_HISTORY_EDIT, m_HistoryEdit);
}


BEGIN_MESSAGE_MAP(CMUTPatientInfoDlg, CDialog)
	ON_WM_CTLCOLOR()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMUTPatientInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMUTPatientInfoDlg::OnBnClickedAddBtn)
END_MESSAGE_MAP()


// CMUTPatientInfoDlg 消息处理程序
BOOL CMUTPatientInfoDlg::OnInitDialog()
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

BOOL CMUTPatientInfoDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTPatientInfoDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

// 	nowRect.left = (APP_SCREEN_WIDTH - DCINFO_MOTEXT_WIDTH)/2;
// 	nowRect.right = nowRect.left + DCINFO_MOTEXT_WIDTH;
// 	nowRect.top  = DCINFO_BORDER_SPACE;
// 	nowRect.bottom = nowRect.top + DCINFO_MOTEXT_HEIGHT;
// 	m_ModifyStatic.MoveWindow(&nowRect);

	int width = (APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE)/3;
	nowRect.left = DCINFO_BORDER_SPACE;
	nowRect.right = nowRect.left + width;
	nowRect.top  = DCINFO_HEIGHT_SPACE1;
	nowRect.bottom = nowRect.top + DCINFO_TEXT_HEIGHT;
	m_TextStatic.MoveWindow(&nowRect);

	width = (APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE)*2/3;
	int height = (DCINFO_TEXT_HEIGHT - (DCINFO_INPUT_NUM-1)*DCINFO_HEIGHT_SPACE)/PTINFO_INPUT_NUM;
	nowRect.left = nowRect.right;
	nowRect.right = nowRect.left + PTINFO_IDEDIT_WIDTH;
	//nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_IdEdit.MoveWindow(&nowRect);

// 	nowRect.left = nowRect.right;
 	nowRect.right = nowRect.left + width;
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_NameEdit.MoveWindow(&nowRect);
	 
	int editleft = DCINFO_BORDER_SPACE+(APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE)/3;
	//nowRect.left = nowRect.right;
	//nowRect.right = nowRect.left + width;
	GetDlgItem(IDC_MAN_RADIO)->GetWindowRect(&rct);
	nowRect.left = editleft;
	nowRect.right = nowRect.left+rct.Width();
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	GetDlgItem(IDC_MAN_RADIO)->MoveWindow(&nowRect);
	m_EditStart.CopyRect(&nowRect);

	nowRect.left +=  DCINFO_RADIO_SPACE;
	nowRect.right = nowRect.left + rct.Width();				//接上一个Radio
	GetDlgItem(IDC_WOMAN_RADIO)->MoveWindow(&nowRect);

	nowRect.CopyRect(&m_EditStart);
	//nowRect.left = nowRect.right;
	nowRect.right = nowRect.left + width;
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_BirthdayEdit.MoveWindow(&nowRect);

	//nowRect.left = nowRect.right;
	nowRect.right = nowRect.left + width;
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_HistoryEdit.MoveWindow(&nowRect);

	nowRect.left = DCINFO_BORDER_SPACE;
	nowRect.right = nowRect.left + (APP_SCREEN_WIDTH - 2*DCINFO_BORDER_SPACE);
	nowRect.top  = nowRect.bottom + DCINFO_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_AddBtn.MoveWindow(&nowRect);

	m_PhotoBtn.GetWindowRect(&rct);
	nowRect.left = editleft+ PTINFO_IDEDIT_WIDTH + PTINFO_WIDTH_SPACE;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top  = DCINFO_HEIGHT_SPACE1;
	nowRect.bottom = nowRect.top + rct.Height();
	m_PhotoBtn.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTPatientInfoDlg::InitComStyle(void)
{

	m_PhotoBtn.DrawBorder(FALSE);	
	m_PhotoBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_PhotoBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_PhotoBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_PhotoBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_PhotoBtn.SetPngMaps(APP_CAMERA_IMAGE,FALSE);

	m_AddBtn.DrawBorder(FALSE);	
	m_AddBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_AddBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_AddBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_AddBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_AddBtn.SetWindowText(_T("增加"));
	CButton  *pManBtn = (CButton *)GetDlgItem(IDC_MAN_RADIO);
	CButton  *pWoManBtn = (CButton *)GetDlgItem(IDC_WOMAN_RADIO);
	pManBtn->SetWindowText(_T("男"));
	pWoManBtn->SetWindowText(_T("女"));
	pManBtn->SetCheck(TRUE);
	pWoManBtn->SetCheck(FALSE);
	CString str;
	str.Format(_T("ID\r\n\n\n\n姓名\r\n\n\n\n性别\r\n\n\n\n生日\r\n\n\n\n病史"));
	m_TextStatic.SetWindowText(str);

	return TRUE;
}

HBRUSH CMUTPatientInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	if(nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_TEXT_COLOR1);

	}

	return GetWndBkHBrush();
}
void CMUTPatientInfoDlg::ClearControl()
{
	m_IdEdit.SetSel(0,-1);
	m_IdEdit.Clear();
	m_NameEdit.SetSel(0,-1);
	m_NameEdit.Clear();
	m_BirthdayEdit.SetSel(0,-1);
	m_BirthdayEdit.Clear();
	m_HistoryEdit.SetSel(0,-1);
	m_HistoryEdit.Clear();
}
void CMUTPatientInfoDlg::OnBnClickedAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	CMUTPatientInfoFunc patientInfo;
	CString	str;
	m_IdEdit.GetWindowText(str);
	patientInfo.m_patient_userid = str;
	if (patientInfo.m_patient_userid.IsEmpty())
	{
		AfxMessageBox(_T("patient userid不能为空"));
		return;
	}
	int lenNumber = patientInfo.m_patient_userid.GetLength();	
	TCHAR pTBuf[256];
	memset(pTBuf,0,sizeof(pTBuf));
	wcscpy(pTBuf,patientInfo.m_patient_userid.GetBuffer());
	do 
	{
		if(pTBuf[lenNumber-1] >= 0xa0)	
		{
			AfxMessageBox(_T("patient userid中有汉字"));
			m_IdEdit.SetFocus();
			return;
		}
		if(!isdigit(pTBuf[lenNumber-1]))
		{	
			AfxMessageBox(_T("patient userid中有字符"));
			m_IdEdit.SetFocus();
			return;
		}

	} while (--lenNumber != 0);

	if (m_pAdoManager->QueryUserId(patientInfo.m_patient_userid, QUERY_TYPE_USERID))
	{
		AfxMessageBox(_T("当前病人已存在"));
		m_IdEdit.SetFocus();
		return;
	}

	m_NameEdit.GetWindowText(str);
	patientInfo.m_patient_username = str;

	if (patientInfo.m_patient_username.IsEmpty())
	{
		AfxMessageBox(_T("patient username不能为空"));
		return;
	}

// 	if (m_pAdoManager->QueryUserId(patientInfo.m_patient_username, QUERY_TYPE_USERNAME))
// 	{
// 		return;
// 	}

	CButton *pManBtn = (CButton *)GetDlgItem(IDC_MAN_RADIO);
	CButton *pWomanBtn = (CButton *)GetDlgItem(IDC_WOMAN_RADIO);

	if(pManBtn->GetCheck())
		patientInfo.m_patient_sex = _T("男");
	else if(pWomanBtn->GetCheck())
		patientInfo.m_patient_sex = _T("女");


	m_BirthdayEdit.GetWindowText(str);
	patientInfo.m_patient_birthday = str;
	if (patientInfo.m_patient_birthday.IsEmpty())
	{
		AfxMessageBox(_T("m_patient birthday不能为空"));
		return;
	}
	lenNumber = patientInfo.m_patient_birthday.GetLength();	
	memset(pTBuf,0,sizeof(pTBuf));
	wcscpy(pTBuf,patientInfo.m_patient_birthday.GetBuffer());
	do 
	{
		if(pTBuf[lenNumber-1] >= 0xa0)	
		{
			AfxMessageBox(_T("patient birthday中有汉字"));
			m_BirthdayEdit.SetFocus();
			return;
		}
		if(!isdigit(pTBuf[lenNumber-1]))
		{	
			AfxMessageBox(_T("patient birthday中有字符"));
			m_BirthdayEdit.SetFocus();
			return;
		}

	} while (--lenNumber != 0);

	m_HistoryEdit.GetWindowText(str);
	patientInfo.m_history = str;

	if (!m_pAdoManager->AddPatient(patientInfo))
	{
		//OnOK();
		return ;
	}

	ClearControl();
	this->ShowWindow(FALSE);
	::SendMessage(GetParent()->GetSafeHwnd(),WM_CHANGE_WND,(WPARAM)type_patient_index,(LPARAM)this);
}

void CMUTPatientInfoDlg::OnOK()   //重载OnOK do nothing
{
	 //CDialog::OnOK(); 
}
