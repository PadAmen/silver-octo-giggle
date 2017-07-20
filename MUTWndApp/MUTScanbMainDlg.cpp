// ScanBWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTScanbMainDlg.h"
#include "MUTWndApp.h"


// CScanBWnd 对话框

IMPLEMENT_DYNAMIC(CMUTScanbMainDlg, CDialog)

CMUTScanbMainDlg::CMUTScanbMainDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMUTScanbMainDlg::IDD, pParent)
,m_bIsRun(TRUE)
,m_bIsFlipImage(FALSE)
,m_bIsFreeze(FALSE)
,m_uIndex(0)
,m_iGain(GAIN_INIT_VALUE)
,m_fFps(0)
,m_fFreq(0)
,m_SaveIndex(0)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();

	//m_pImgProc = new CMUTImgProcFunc();
	m_pImgProc = CMUTImgProcFunc::GetImgProc();
	m_AdoManger = CMUTDAOManagerFunc::GetDAOManager();

}

CMUTScanbMainDlg::~CMUTScanbMainDlg()		
{
	m_ImgRgn.DeleteObject();
}

void CMUTScanbMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DOCTOR_BTN, m_Doctor);
	DDX_Control(pDX, IDC_PATIENT_BTN, m_Patient);
	DDX_Control(pDX, IDC_CLOSE_BTN, m_CloseBtn);
	DDX_Control(pDX, IDC_STATE_BTN, m_StateBtn);
	DDX_Control(pDX, IDC_SAVE_BTN, m_SaveBtn);
	DDX_Control(pDX, IDC_MODE_BTN, m_ModeBtn);
	DDX_Control(pDX, IDC_SCANB_MENU, m_ScanbMenu);
	DDX_Control(pDX, IDC_LIST_BTN, m_ListBtn);
	DDX_Control(pDX, IDC_FREQ_SET, m_SetFreq);
	DDX_Control(pDX, IDC_FPS_SET, m_SetFps);
	DDX_Control(pDX, IDC_DEPTH_SET, m_SetDepth);
	DDX_Control(pDX, IDC_ADD_BTN, m_AddBtn);
	DDX_Control(pDX, IDC_CUT_BTN, m_CutBtn);
	DDX_Control(pDX, IDC_LEFT_BTN, m_ProbePosBtn);
	DDX_Control(pDX, IDC_GRAY_BMP, m_GrayBtn);
	DDX_Control(pDX, IDC_MAC_STATIC, m_MacStatic);
	DDX_Control(pDX, IDC_NET_BTN, m_NetBtn);
	DDX_Control(pDX, IDC_EVALUE_BTN, m_EvalBtn);
	DDX_Control(pDX, IDC_THUMB_LIST, m_ListImg);
}


BEGIN_MESSAGE_MAP(CMUTScanbMainDlg, CDialog)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &CMUTScanbMainDlg::OnBnClickedCloseBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_DOCTOR_BTN, &CMUTScanbMainDlg::OnBnClickedDoctorBtn)
	ON_BN_CLICKED(IDC_PATIENT_BTN, &CMUTScanbMainDlg::OnBnClickedPatientBtn)
	ON_BN_CLICKED(IDC_STATE_BTN, &CMUTScanbMainDlg::OnBnClickedStateBtn)
	ON_BN_CLICKED(IDC_LEFT_BTN, &CMUTScanbMainDlg::OnBnClickedLeftBtn)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMUTScanbMainDlg::OnBnClickedAddBtn)
	ON_BN_CLICKED(IDC_CUT_BTN, &CMUTScanbMainDlg::OnBnClickedDecBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CMUTScanbMainDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_LIST_BTN, &CMUTScanbMainDlg::OnBnClickedListBtn)
	ON_MESSAGE(WM_ADD_DOCTOR,&CMUTScanbMainDlg::OnAddDoctor)
	ON_MESSAGE(WM_ADD_PATIENT,&CMUTScanbMainDlg::OnAddPatient)
	ON_MESSAGE(WM_DISP_IMAGE,&CMUTScanbMainDlg::OnDisplayDcm)
	ON_MESSAGE(WM_UPDATE_IMAGE,&CMUTScanbMainDlg::OnUpdateRgn)
	ON_MESSAGE(WM_SAVE_IMAGE,&CMUTScanbMainDlg::OnSaveDcm)
	ON_MESSAGE(WM_INPUT_STR,&CMUTScanbMainDlg::OnInputStr)
	ON_MESSAGE(WM_CLEAR_VECTOR,&CMUTScanbMainDlg::OnClearVector)
	ON_COMMAND(ID_X_32784, &CMUTScanbMainDlg::OnClickAbout)
	ON_COMMAND(ID_X_32778, &CMUTScanbMainDlg::OnClickReport)
	ON_WM_PAINT()
	//ON_WM_TIMER()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

// CScanBWnd 消息处理程序
BOOL CMUTScanbMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//CDC *pDC = GetDC();
	CRect rct;
	m_StateBtn.GetWindowRect(&rct);			//传递主窗口控件尺寸
	m_RunLeftWnd.GetParentSize(rct);		
	m_FreezeLeftWnd.GetParentSize(rct);
	m_SaveWnd.GetParentHwnd(m_hWnd);


	m_RunBtmWnd.Create(IDD_SWND_RUN_BTM,this);
	m_RunLeftWnd.Create(IDD_SWND_RUN_LEFT,this);
	m_FreezeBtmWnd.Create(IDD_SWND_FRZE_BTM,this);
	m_FreezeLeftWnd.Create(IDD_SWND_FRZE_LEFT,this);
	m_SaveWnd.Create(IDD_SAVE_WND,this);

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("Apply Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}
	// 	if(TRUE != this->InitThread())
	// 	{
	// 		MessageBox(_T("Apply Dialog InitThread Err!"));
	// 		goto NORMAL_EXIT;
	// 	}

	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}
BOOL CMUTScanbMainDlg::PreTranslateMessage(MSG* pMsg)
{

		// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN) 
	{

		if (pMsg->wParam == VK_ESCAPE ||

			pMsg->wParam == VK_RETURN)

			return TRUE;
	}

	::ScreenToClient(m_hWnd,&pMsg->pt);	
	if(IsRun())	goto RETURN;

	if(m_ImgRgn.PtInRegion(pMsg->pt)&&m_FreezeLeftWnd.GetBtnClickState())//GetImageRect().PtInRect(pMsg->pt)
	{
		m_FreezeLeftWnd.m_pMeaFun->ProMouse(pMsg);
		if(pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_MOUSEMOVE)
		{
			CDC *pDC = GetDC();
			pDC->SelectClipRgn(&m_ImgRgn);
			m_FreezeLeftWnd.m_pMeaFun->DrawObject(pDC);		
			if(m_FreezeLeftWnd.m_pMeaFun->CurTempHasEnd())
			{
				//::SendMessage(m_hWnd,WM_UPDATE_IMAGE,0,NULL);		//???最后一次更新
				m_FreezeLeftWnd.m_pMeaFun->MeasureRstartProc();
			}				

			if(m_FreezeLeftWnd.m_pMeaFun->IsCurMeaText()&&m_FreezeLeftWnd.m_pMeaFun->CurTempHasStarted())
				m_FreezeLeftWnd.m_TextWnd.ShowWindow(TRUE);

			ReleaseDC(pDC);
		}
	}


RETURN:		
	return CDialog::PreTranslateMessage(pMsg);
}
// BOOL CMUTScanbMainDlg::InitThread(void)
// {
// 	hProcessThread=CreateThread(NULL,0,ProcessThread,this,CREATE_SUSPENDED,NULL);
// 	SetThreadPriority(hProcessThread,THREAD_PRIORITY_HIGHEST);
// 	ResumeThread(hProcessThread);
// 
// 	return TRUE;
// }
BOOL CMUTScanbMainDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()|| TRUE != this->InitComStyle())
		return FALSE;

	m_FreezeBtmWnd.GetParentRunPtr(&m_bIsRun);
	ShowStateWnd(state_default_index);

	return TRUE;
}
BOOL CMUTScanbMainDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);
	//////////////////////////////////////////////////////////////////////////
	/*左侧控件尺寸*/

	/*以顶边为基准*/
	m_rcLeftRgn.left = SCANB_BORDER_WIDTH;
	m_rcLeftRgn.top = SCANB_BORDER_HEIGHT;

	CStatic *pFreqStatic = (CStatic *)GetDlgItem(IDC_FREQ_STATIC);
	pFreqStatic->GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = SCANB_BORDER_HEIGHT;
	nowRect.bottom = nowRect.top + rct.Height();
	pFreqStatic->MoveWindow(&nowRect);

	m_SetFreq.GetWindowRect(&rct);
	nowRect.top += (SCANB_HEIGHT_SAPCE+nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_SetFreq.MoveWindow(&nowRect);

	m_StateBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_StateBtn.MoveWindow(&nowRect);

	m_SaveBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_SaveBtn.MoveWindow(&nowRect);

	m_ProbePosBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_ProbePosBtn.MoveWindow(&nowRect);

	m_AddBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_AddBtn.MoveWindow(&nowRect);

	CStatic *pDepthStatic = (CStatic *)GetDlgItem(IDC_DEPTH_STATIC);
	pDepthStatic->GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());	//???
	nowRect.bottom = nowRect.top + rct.Height();
	pDepthStatic->MoveWindow(&nowRect);

	m_SetDepth.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());	//???
	nowRect.bottom = nowRect.top + rct.Height();
	m_SetDepth.MoveWindow(&nowRect);

	m_CutBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_CutBtn.MoveWindow(&nowRect);
	/*状态窗口显示尺寸*/
	//m_RunLeftWnd.GetWindowRect(&rct);
	nowRect.left = SCANB_LEFTWND_LEFT;
	nowRect.right = nowRect.left + nowRect.Width()+SCANB_BORDER_WIDTH;
	nowRect.top += (SCANB_HEIGHT_SAPCE + nowRect.Height());
	nowRect.bottom = nowRect.top + SCANB_LEFTWND_HEIGHT;//rct.Height()
	m_RunLeftWnd.MoveWindow(&nowRect);	
	m_FreezeLeftWnd.MoveWindow(&nowRect);

	/*以底边为基准*/
	m_ScanbMenu.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = APP_SCREEN_HEIGHT-SCANB_BORDER_WIDTH-rct.Height();
	nowRect.bottom = nowRect.top + rct.Height();
	m_ScanbMenu.MoveWindow(&nowRect);

	m_ModeBtn.GetWindowRect(&rct);
	nowRect.left = SCANB_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top -= (SCANB_BORDER_WIDTH+rct.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_ModeBtn.MoveWindow(&nowRect);

	m_rcLeftRgn.right = m_rcLeftRgn.left + rct.Width();
	m_rcLeftRgn.bottom = nowRect.bottom;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/*中间控件尺寸*/
	// 	m_rcTopRgn.left = m_rcLeftRgn.right + 1;
	// 	m_rcTopRgn.top = m_rcLeftRgn.top;

	m_Doctor.GetWindowRect(&rct);
	nowRect.left = SCANB_DOCTOR_LEFT;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = SCANB_DOCTOR_TOP;
	nowRect.bottom = nowRect.top + rct.Height();
	m_Doctor.MoveWindow(&nowRect);

	//m_Patient.GetWindowRect(&rct);
	nowRect.left +=  (rct.Width()+ SCANB_WIDTH_TOPSPACE);
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = SCANB_DOCTOR_TOP;
	nowRect.bottom = nowRect.top + rct.Height();
	m_Patient.MoveWindow(&nowRect);

	// 	m_rcTopRgn.bottom = m_rcTopRgn.top + rct.Height();
	// 	m_rcTopRgn.right = m_rcTopRgn.left + SCANB_IMAGE_WIDTH;
	/*图像显示区域*/
	m_rcImageRgn.left = m_rcLeftRgn.right + SCANB_IMAGE_SPACE;
	m_rcImageRgn.right = m_rcImageRgn.left + SCANB_IMAGE_WIDTH;
	m_rcImageRgn.top = rct.Height()+ SCANB_IMAGE_SPACE1;
	m_rcImageRgn.bottom = m_rcImageRgn.top + SCANB_IMAGE_HEIGHT;
	m_ImgRgn.CreateRectRgnIndirect(&m_rcImageRgn);

	m_RunBtmWnd.GetWindowRect(&rct);
	nowRect.left = SCANB_DOCTOR_LEFT;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top =APP_SCREEN_HEIGHT -rct.Height();
	nowRect.bottom = nowRect.top + rct.Height();
	m_RunBtmWnd.MoveWindow(&nowRect);
	m_FreezeBtmWnd.MoveWindow(&nowRect);

	m_ListImg.GetWindowRect(&rct);												//缩略图显示控件
	nowRect.left = m_rcImageRgn.right+SCANB_IMAGE_SPACE1;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = m_rcImageRgn.top;
	nowRect.bottom = nowRect.top + SCANB_LIST_HEIGHT;
	m_ListImg.MoveWindow(&nowRect);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	/*右侧控件尺寸*/

	CStatic *pFpsStatic = (CStatic *)GetDlgItem(IDC_FPS_STATIC);
	pFpsStatic->GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH-SCANB_BORDER_WIDTH-rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = SCANB_BORDER_HEIGHT;
	nowRect.bottom = nowRect.top + rct.Height();
	pFpsStatic->MoveWindow(&nowRect);

	m_SetFps.GetWindowRect(&rct);
	nowRect.top += (SCANB_HEIGHT_SAPCE+rct.Height());
	nowRect.bottom = nowRect.top + rct.Height();
	m_SetFps.MoveWindow(&nowRect);


	m_MacStatic.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH-SCANB_BORDER_WIDTH-rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = nowRect.bottom + SCANB_HEIGHT_SAPCE1;
	nowRect.bottom = nowRect.top + rct.Height();
	m_MacStatic.MoveWindow(&nowRect);

	m_GrayBtn.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH-SCANB_BORDER_WIDTH-rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (APP_SCREEN_HEIGHT - rct.Height())/3;
	nowRect.bottom = nowRect.top + rct.Height();
	m_GrayBtn.MoveWindow(&nowRect);

	m_ListBtn.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH-SCANB_BORDER_WIDTH-rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (APP_SCREEN_HEIGHT - rct.Height())*2/3;
	nowRect.bottom = nowRect.top + rct.Height();
	m_ListBtn.MoveWindow(&nowRect);

	m_NetBtn.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH-SCANB_BORDER_WIDTH-rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = nowRect.bottom + SCANB_HEIGHT_SAPCE1;
	nowRect.bottom = nowRect.top + rct.Height();
	m_NetBtn.MoveWindow(&nowRect);

	m_EvalBtn.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH-SCANB_BORDER_WIDTH-rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = nowRect.bottom + SCANB_HEIGHT_SAPCE;
	nowRect.bottom = nowRect.top + rct.Height();
	m_EvalBtn.MoveWindow(&nowRect);

	m_CloseBtn.GetWindowRect(&rct);
	nowRect.left = APP_SCREEN_WIDTH - rct.Width()-APPLY_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = APP_SCREEN_HEIGHT - rct.Height()-APPLY_BORDER_WIDTH;
	nowRect.bottom = nowRect.top + rct.Height();
	m_CloseBtn.MoveWindow(&nowRect);


	//////////////////////////////////////////////////////////////////////////

	/*CRect rct;*/
	HWND hScrHwnd = ::GetDesktopWindow();
	CRect hScrRct;
	::GetWindowRect(hScrHwnd,&hScrRct);
	m_SaveWnd.GetWindowRect(&rct);
	nowRect.left = (hScrRct.Width() - APP_SCREEN_WIDTH)/2; //得到APP相对应屏幕座标
	nowRect.left += (APP_SCREEN_WIDTH - rct.Width())/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = (hScrRct.Height() - APP_SCREEN_HEIGHT)/2;
	nowRect.top += (APP_SCREEN_HEIGHT - rct.Height())/2;
	nowRect.bottom = nowRect.top + rct.Height();
	m_SaveWnd.MoveWindow(&nowRect);
	m_SaveWnd.ShowWindow(FALSE);

	return TRUE;
}

BOOL CMUTScanbMainDlg::InitComStyle(void)
{

	m_StateBtn.DrawBorder(FALSE);
	m_StateBtn.DrawTransparent(TRUE);
	m_StateBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_StateBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	//m_StateBtn.SetBitmaps(IDB_BMP_FREZE);
	m_StateBtn.SetPngMaps(APP_FREEZE_IMAGE);

	m_SaveBtn.DrawBorder(FALSE);
	m_SaveBtn.DrawTransparent(TRUE);
	m_SaveBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SaveBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_SaveBtn.SetPngMaps(APP_SAVE_IMAGE);
	//m_SaveBtn.SetPngMaps(IDB_PNG_SAVE);
	//m_SaveBtn.SetBitmaps(IDB_BMP_SAVE);

	m_ProbePosBtn.DrawBorder(FALSE);
	m_ProbePosBtn.DrawTransparent(TRUE);
	m_ProbePosBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_ProbePosBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_ProbePosBtn.SetPngMaps(APP_MIRROR_OFF_IMAGE);
	//m_ProbePosBtn.SetBitmaps(IDB_BMP_RIGHT);

	m_AddBtn.DrawBorder(FALSE);
	/*m_AddBtn.DrawTransparent(TRUE);*/
	m_AddBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_AddBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_AddBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_AddBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_AddBtn.SetPngMaps(APP_ADD_IMAGE);

	m_CutBtn.DrawBorder(FALSE);
	/*m_CutBtn.DrawTransparent(TRUE);*/
	m_CutBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_CutBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_CutBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_CutBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_CutBtn.SetPngMaps(APP_REDUCE_IMAGE);

	m_ScanbMenu.DrawBorder(FALSE);
	m_ScanbMenu.DrawTransparent(TRUE);
	// 	m_ScanbMenu.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	// 	m_ScanbMenu.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_ScanbMenu.SetPngMaps(APP_MORE_IMAGE);
	m_ScanbMenu.SetMenu(IDR_SCANB_MENU,m_hWnd,FALSE);

	m_ModeBtn.DrawBorder(FALSE);
	m_ModeBtn.DrawTransparent(TRUE);
	m_ModeBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_ModeBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_ModeBtn.SetPngMaps(APP_CMODE_OFF_IAMGE);

	m_Doctor.DrawBorder(TRUE);
	m_Doctor.SetRounded(TRUE);
	m_Doctor.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_Doctor.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_Doctor.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_Doctor.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_Patient.DrawBorder(TRUE);
	m_Patient.SetRounded(TRUE);
	m_Patient.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_Patient.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_Patient.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_Patient.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_GrayBtn.DrawBorder(FALSE);
	m_GrayBtn.DrawTransparent(TRUE);
	m_GrayBtn.SetPngMaps(APP_GRAY_IMAGE);

	m_ListBtn.DrawBorder(TRUE);
	m_ListBtn.DrawTransparent(TRUE);
	m_ListBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	m_ListBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_ListBtn.SetColor(BTNST_COLOR_FG_IN,SCANB_COLOR_SECELT);
	m_ListBtn.SetColor(BTNST_COLOR_FG_OUT,SCANB_COLOR_SECELT);

	m_ListImg.SetBkColor(APP_BK_COLOR1);					//缩略图
	m_ListImg.CreateColumn();
	//m_ListImg.ModifyStyle(0,WS_OVERLAPPEDWINDOW);
	m_ListImg.ShowWindow(SW_HIDE);

	m_NetBtn.DrawBorder(FALSE);
	m_NetBtn.DrawTransparent(TRUE);
	m_NetBtn.SetPngMaps(APP_DISCONNET_IMAGE);

	m_EvalBtn.DrawBorder(FALSE);
	m_EvalBtn.DrawTransparent(TRUE);
	m_EvalBtn.SetPngMaps(APP_EVALUE_IMAGE);

	m_CloseBtn.DrawBorder(FALSE);
	m_CloseBtn.DrawTransparent(TRUE);
	// 	m_CloseBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_OUT);
	// 	m_CloseBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_CloseBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_CloseBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);
	m_CloseBtn.SetPngMaps(APP_CLOSE_IMAGE);

	SetTextFreq(11.2);
	m_pFpsStatic = (CStatic*)GetDlgItem(IDC_FPS_STATIC);
	m_pFpsStatic->ShowWindow(TRUE);
	SetTextGain(m_iGain);
	CString	str;
	str.Format(_T("MUT\r\n\n\nTI\r\n%.1f\r\n\n\nMI\r\n%.1f\r\n"),0.9,0.2);
	m_MacStatic.SetWindowText(str);

	return TRUE;
}
LRESULT CMUTScanbMainDlg::OnAddDoctor(WPARAM wParam,LPARAM lParam)
{
	CString *pStr = (CString *)lParam;
	TCHAR pBuf[256];
	memset(pBuf,0,sizeof(pBuf));
	int id;
	//CString doctorname;
	swscanf(pStr->GetBuffer(),_T("%d%s"),&id,&pBuf);
	m_DoctorName.Format(_T("%s"),pBuf);
	m_Doctor.SetWindowText(_T("扫描医生:\r\n")+m_DoctorName);
	m_CurDoctorId.Format(_T("%d"),id);

	return 1;
}
LRESULT CMUTScanbMainDlg::OnAddPatient(WPARAM wParam,LPARAM lParam)
{
	CString *pStr = (CString *)lParam;
	TCHAR pBuf[256];
	memset(pBuf,0,sizeof(pBuf));
	int id;
	swscanf(pStr->GetBuffer(),_T("%d%s%s%s"),&id,&pBuf[0],&pBuf[32],&pBuf[64]);
	m_PatientName.Format(_T("%s"),pBuf);
	m_Patient.SetWindowText(_T("患者:\r\n")+m_PatientName);
	m_CurPatientId.Format(_T("%d"),id);
	//m_Doctor.SetWindowText(right);
	return 1;
}
LRESULT CMUTScanbMainDlg::OnDisplayDcm(WPARAM wParam,LPARAM lParam)
{
	//CMUTScanbSaveOWnd *pSaveWnd = (CMUTScanbSaveOWnd*)lParam;
	CString *pFilename = (CString *)lParam;

	CDC *pDC = this->GetDC();
	CRect img = GetImageRect();
	m_FreezeLeftWnd.m_pMeaFun->DeleteAllResult();			//显示Dcm图像之前将先前测量信息删除
	m_pImgProc->SetDcmOn();
	m_pImgProc->OpenDcmImage(*pFilename);
	m_pImgProc->DrawImage(pDC,img,m_bIsFlipImage);			//???
	ReleaseDC(pDC);
	return 1;
}
LRESULT CMUTScanbMainDlg::OnInputStr(WPARAM wParam,LPARAM lParam)
{
	CString *str = (CString *)lParam;

	::SendMessage(m_hWnd,WM_UPDATE_IMAGE,0,NULL);
	m_FreezeLeftWnd.m_pMeaFun->TransStrText(*str);
	m_FreezeLeftWnd.m_pMeaFun->SetCurTempEnded();
	//m_FreezeLeftWnd.pMeaFun->MeasureRstartProc();

	return 1;
}
BOOL  CMUTScanbMainDlg::AddInfoToAccess()
{
	//////////////////////////////////////////////////////////////////////////
	//是否选中医生、病人
	if (m_CurDoctorId.IsEmpty()||m_CurPatientId.IsEmpty())
	{
		return FALSE;
	}

	if (m_AdoManger->QueryUserId(m_CurPatientId, QUERY_TYPE_USERID))
	{
		return FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	//查找同一个病人中studyid号最大值
	CMUTStudyInfoFunc medicalinfo;
	int maxtemp = 0; 
	CArray<CMUTStudyInfoFunc> *pStudyidInfo = m_AdoManger->getStudyidInfo(m_CurPatientId);

	if(pStudyidInfo->IsEmpty())
	{
		medicalinfo.m_studyid.Format(_T("0"));
	}
	else
	{
		int last = pStudyidInfo->GetSize() -1;
		CMUTStudyInfoFunc	lastStudy = pStudyidInfo->GetAt(last);
		maxtemp = _wtoi(lastStudy.m_studyid);
	}
	//////////////////////////////////////////////////////////////////////////
	//扫描结束时添加MedicalInfo信息将studyid加1
	int studyid = maxtemp + 1;
	medicalinfo.m_studyid.Format(_T("%d"),studyid);
	medicalinfo.m_doctorid = m_CurDoctorId;
	medicalinfo.m_patientid = m_CurPatientId;

	//////////////////////////////////////////////////////////////////////////
	//次数study及dcm文件写入相应表格
	extern CMUTWndAppApp theApp;
	CString strFilePath = theApp.GetDcmDirtory();
	if (m_AdoManger->addStudyInfo(medicalinfo))
	{
		static int dcmid = 0;
		for(int i=0;i<m_DcmSavedArray.GetSize();i++)
		{
			CMUTDicomFileFunc dicomfile;
			dicomfile.m_filename = m_DcmSavedArray.GetAt(i);
			dicomfile.m_dicomfileid.Format(_T("%d"),++ dcmid);	//need ini record max dcm file cout
			dicomfile.m_patientid = m_CurPatientId;
			dicomfile.m_studyid.Format(_T("%d"),studyid);
			dicomfile.m_directory = strFilePath;
			if (!m_AdoManger->addDicomFile(dicomfile))
			{		
				//printf("something go wrong \r\n");
				return FALSE;
			}
		}

	}

	return TRUE;
}
LRESULT CMUTScanbMainDlg::OnSaveDcm(WPARAM wParam,LPARAM lParam)
{
	//CMUTScanbSaveOWnd *pSaveWnd = (CMUTScanbSaveOWnd*)lParam;	
	extern CMUTWndAppApp theApp;
	CString strFilePath = theApp.GetDcmDirtory();
	COleDateTime datetime = COleDateTime::GetCurrentTime();
	CString filename,dcmfilename,imgfilename;

	dcmfilename  = datetime.Format(_T("%Y%m%d_%H%M%S")) + _T(".dcm");
	filename = strFilePath +  _T("\\") + dcmfilename;

	CDC *pDC = this->GetDC();
	if(m_pImgProc->SaveDcmImage(pDC,GetImageRect(),filename))
	{
		m_DcmSavedArray.Add(dcmfilename);			//保存文件名
	}
	strFilePath = theApp.GetThumbnailImageDirectory();
	imgfilename  = datetime.Format(_T("%Y%m%d_%H%M%S")) + _T(".bmp");
	filename = strFilePath +  _T("\\") + imgfilename;

	if(m_pImgProc->SaveSnapShotFile(pDC,GetImageRect(),filename))
	{
		m_imageSavedArray.Add(imgfilename);			//保存文件名
		m_ListImg.m_strImageDir = strFilePath;
		m_ListImg.m_VectorImageNames.push_back(imgfilename);		
		m_ListImg.Load();
	}
	ReleaseDC(pDC);

	CString str;
	str.Format(_T("%d"),m_ListImg.GetItemCount());
	m_ListBtn.SetWindowText(str);

	return 1;
}
LRESULT CMUTScanbMainDlg::OnClearVector(WPARAM wParam,LPARAM lParam)
{
	m_DcmSavedArray.RemoveAll();
	m_imageSavedArray.RemoveAll();
	m_ListImg.Clear();					//清除listimg缓存
	//m_ListImg.Load();					//不需要重新加载

	return 1;
}
LRESULT CMUTScanbMainDlg::OnUpdateRgn(WPARAM wParam,LPARAM lParam)
{
	CDC *pDC = GetDC();	
	CRect img;
	img.CopyRect(&GetImageRect());
	m_pImgProc->DrawImage(pDC,img,m_bIsFlipImage);			//???
	pDC->SelectClipRgn(&m_ImgRgn);
	m_FreezeLeftWnd.m_pMeaFun->DrawObjectArray(pDC);		
	ReleaseDC(pDC);
	return TRUE;
}
BOOL CMUTScanbMainDlg::SetTextFreq(DOUBLE fFreq)
{
	if(fFreq < 0) return FALSE;

	m_fFreq = fFreq;
	CString str;
	str.Format(_T("%.1f MHz"),m_fFreq);
	m_SetFreq.SetWindowText(str);

	return TRUE;
}
BOOL CMUTScanbMainDlg::SetTextFps(DOUBLE fFps)
{	
	if(fFps < 0) return FALSE;

	m_fFps = fFps;

	CString str;
	str.Format(_T("%.1f"),m_fFps);
	m_SetFps.SetWindowText(str);

	return TRUE;
}
BOOL CMUTScanbMainDlg::SetTextGain(UINT uGain)
{
	m_iGain = uGain;

	CString str;
	str.Format(_T("%d"),m_iGain);
	m_SetDepth.SetWindowText(str);

	return TRUE;
}

void CMUTScanbMainDlg::OnBnClickedCloseBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	m_FreezeLeftWnd.m_pMeaFun->DeleteAllResult();

	if(!m_DcmSavedArray.IsEmpty())												//有图像保存	进入结束编辑界面
	{
		SelectPageIndex(type_scanover_index);
		::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uIndex,(LPARAM)this);
	}
	else																		//当前没有图像保存 直接进入应用主界面
	{
		SelectPageIndex(type_apply_index);
		::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uIndex,(LPARAM)this);
	}

}

HBRUSH CMUTScanbMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_STATIC
		||nCtlColor == CTLCOLOR_SCROLLBAR 
		||nCtlColor == CTLCOLOR_LISTBOX)
	{
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetTextColor(RGB(250,250,250));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	return GetWndBkHBrush();
}

void CMUTScanbMainDlg::OnBnClickedDoctorBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	SelectPageIndex(type_doctor_index);
	::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uIndex,(LPARAM)this);
}

void CMUTScanbMainDlg::OnBnClickedPatientBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);
	SelectPageIndex(type_patient_index);
	::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uIndex,(LPARAM)this);
}
void CMUTScanbMainDlg::ResumeInitState()
{
	m_FreezeBtmWnd.ResumeInitState();
	m_RunLeftWnd.ResumeInitState();
	m_RunBtmWnd.ResumeInitState();	
	m_ListBtn.SetClickState(FALSE);
	m_ListBtn.ShowWindow(FALSE);
	m_ListBtn.SetWindowText(APP_NULL_STR);
	m_Patient.SetWindowText(_T("请选择一位病人！"));
	SetRunWndParam();
}
void CMUTScanbMainDlg::SetRunWndParam()
{
	SetRun(TRUE);
	m_bIsFreeze = FALSE;
	m_pImgProc->SetDcmOn(FALSE);
	m_FreezeLeftWnd.ResumeInitState();				
	m_pFpsStatic->ShowWindow(TRUE);
	m_SetFps.ShowWindow(TRUE);	
	m_StateBtn.SetPngMaps(APP_FREEZE_IMAGE);	
	ShowStateWnd(state_run_index);
	
}
void CMUTScanbMainDlg::SetFreezeWndParam()
{
	SetTextFps(0);
	SetRun(FALSE);

	m_bIsFreeze = TRUE;							//冻结图像
	m_pFpsStatic->ShowWindow(FALSE);
	m_SetFps.ShowWindow(FALSE);
	m_StateBtn.SetPngMaps(APP_RESUME_IMAGE);
	ShowStateWnd(state_fre_index);
}
void CMUTScanbMainDlg::OnBnClickedStateBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//static BOOL bRet = FALSE;
	IsRun()? SetFreezeWndParam():SetRunWndParam();

}

void CMUTScanbMainDlg::OnBnClickedLeftBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//static BOOL bRet = FALSE;
	if(!m_bIsFlipImage)
	{
		m_bIsFlipImage = TRUE;
		m_ProbePosBtn.SetPngMaps(APP_MIRROR_ON_IAMGE);
	}
	else
	{
		m_bIsFlipImage = FALSE;
		//m_ProbePosBtn.SetBitmaps(IDB_BMP_LEFT,0);
		m_ProbePosBtn.SetPngMaps(APP_MIRROR_OFF_IMAGE);
	}
}


void CMUTScanbMainDlg::OnBnClickedAddBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iGain += GAIN_OFFSET_VALUE;
	setGain(m_iGain);
	SetTextGain((m_iGain  >= GAIN_MAX_VALUE)?GAIN_MAX_VALUE:m_iGain);
}

void CMUTScanbMainDlg::OnBnClickedDecBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iGain -= GAIN_OFFSET_VALUE;
	setGain(m_iGain);
	SetTextGain((m_iGain  <= GAIN_MIN_VALUE)?GAIN_MIN_VALUE:m_iGain);
}

void CMUTScanbMainDlg::OnBnClickedSaveBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//static BOOL bCnt = FALSE;

	if(!IsFreeze())
	{
		m_ListBtn.ShowWindow(TRUE);
		CString str;
		if(m_SaveIndex >= SCANB_SAVE_MAX)
			m_SaveIndex = SCANB_SAVE_MAX;
		str.Format(_T("%d"),m_ListImg.GetItemCount()+1);
		m_ListBtn.SetWindowText(str);
		this->SendMessage(WM_SAVE_IMAGE,0,NULL);
	}
	else
	{
		m_SaveWnd.ShowWindow(TRUE);
	}
	SetFocus();
}

BOOL CMUTScanbMainDlg::ShowStateWnd(INT iIndex)
{
	switch(iIndex)
	{
	case -1:
		m_RunLeftWnd.ShowWindow(TRUE);
		m_RunBtmWnd.ShowWindow(TRUE);
		m_FreezeLeftWnd.ShowWindow(FALSE);		
		m_FreezeBtmWnd.ShowWindow(FALSE);
		break;
	case 0:
		m_RunLeftWnd.ShowWindow(TRUE);
		m_RunBtmWnd.ShowWindow(TRUE);
		m_FreezeLeftWnd.ShowWindow(FALSE);		
		m_FreezeBtmWnd.ShowWindow(FALSE);
		break;
	case 1:
		m_RunLeftWnd.ShowWindow(FALSE);
		m_RunBtmWnd.ShowWindow(FALSE);
		m_FreezeLeftWnd.ShowWindow(TRUE);		
		m_FreezeBtmWnd.ShowWindow(TRUE);
		break;		
	default:
		return FALSE;
		break;

	}
	return TRUE;
}

// CRect CMUTScanbMainDlg::GetImageRect()
// {
// 	return m_rcImageRgn;
// }

void CMUTScanbMainDlg::OnBnClickedListBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_ListImg.IsWindowVisible())
		m_ListImg.ShowWindow(TRUE);
	else
		m_ListImg.ShowWindow(FALSE);
}

void CMUTScanbMainDlg::OnClickAbout()
{
	// TODO: 在此添加命令处理程序代码
	this->ShowWindow(FALSE);
	SelectPageIndex(type_update_index);
	::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uIndex,(LPARAM)this);
}

void CMUTScanbMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	if(IsRun())		return;

	m_pImgProc->DrawImage(&dc,GetImageRect(),m_bIsFlipImage);			//needs modify

}

// BOOL CMUTScanbMainDlg::DestroyWindow(void)
// {
// 	if(!IsExit())
// 	{
// 		SetExit();
// 		SetRun(FALSE);	
// 		WaitForSingleObject(hProcessThread,500);
// 		CloseHandle(hProcessThread);
// 		hProcessThread=NULL;
// 	}
// 
// 	return CDialog::DestroyWindow();
// }


LRESULT CMUTScanbMainDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	m_SetFps.GetWindowRect(&rect);
	ScreenToClient(&point);	//把屏幕坐标转换为当前窗体坐标
	if(rect.PtInRect(point))
	{	
		return HTCAPTION;
	}
	else
	{
		return CDialog::OnNcHitTest(point);
	}

}

void CMUTScanbMainDlg::OnClickReport()
{
	// TODO: 在此添加命令处理程序代码
	//this->ShowWindow(FALSE);          //子窗口一起关闭
	//SelectPageIndex(type_report_index);
	//::SendMessage(m_hMainWnd,WM_CHANGE_WND,(WPARAM)m_uIndex,(LPARAM)this);
}

// BOOL CMUTScanbMainDlg::InitDeviceParam(void)
// {
// 
// 	m_RunLeftWnd.SetTextDepth(DEPTH_INIT_VAL);
// 
// 	return TRUE;
// }

