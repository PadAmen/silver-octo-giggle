// MUTCaseReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTPatientReportDlg.h"

#define ICON_UP_INDEX	0
#define ICON_DOWN_INDEX 1
// CMUTCaseReportDlg 对话框

IMPLEMENT_DYNAMIC(CMUTPatientReportDlg, CDialog)

CMUTPatientReportDlg::CMUTPatientReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTPatientReportDlg::IDD, pParent)
	,m_bEdit(FALSE)
	,m_bIsDownNow(FALSE)
	,m_bIsDcmUpdate(TRUE)
/*	,m_bCheckAcessNow(TRUE)*/
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	m_AdoManger = CMUTDAOManagerFunc::GetDAOManager();
	StaticFont.CreatePointFont(APP_FONT_POINT,APP_FONT_FACENAME,NULL);//创建一个新的字体
	//newFont1.CreatePointFont(APP_FONT_POINT2,APP_FONT_FACENAME2,NULL);//创建一个新的字体
}

CMUTPatientReportDlg::~CMUTPatientReportDlg()
{
	StaticFont.DeleteObject();
}

void CMUTPatientReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXIT_BTN, m_ExitBtn);
	DDX_Control(pDX, IDC_DELETE_BTN, m_DeleteBtn);
	DDX_Control(pDX, IDC_MODIFY_BTN, m_ModifyBtn);
	DDX_Control(pDX, IDC_SELECTD_BTN, m_SelectBtn);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_CancelBtn);
	DDX_Control(pDX, IDC_DELETE_BTN1, m_DeleteBtn1);
	DDX_Control(pDX, IDC_EXPORT_BTN, m_ExportBtn);
	DDX_Control(pDX, IDC_COMPARE_BTN, m_CompareBtn);
	DDX_Control(pDX, IDC_INPUT_EDIT, m_InputEdit);
	DDX_Control(pDX, IDC_REPORT_STATIC, m_TextStatic);
	DDX_Control(pDX, IDC_LIST1, m_ReportList);
	//DDX_Control(pDX, IDC_LIST2, m_dcmlist);
}


BEGIN_MESSAGE_MAP(CMUTPatientReportDlg, CDialog)
	ON_WM_CTLCOLOR()
	//ON_MESSAGE(WM_DISP_LIST,&CMUTPatientReportDlg::OnDispList)
	ON_BN_CLICKED(IDC_DELETE_BTN, &CMUTPatientReportDlg::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_EXIT_BTN, &CMUTPatientReportDlg::OnBnClickedExitBtn)
	ON_BN_CLICKED(IDC_MODIFY_BTN, &CMUTPatientReportDlg::OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_SELECTD_BTN, &CMUTPatientReportDlg::OnBnClickedSelectBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &CMUTPatientReportDlg::OnBnClickedCancelBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN1,&CMUTPatientReportDlg::OnBnClickedDelete1Btn)
	ON_BN_CLICKED(IDC_EXPORT_BTN,&CMUTPatientReportDlg::OnBnClickedExportBtn)
	//ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMUTCaseReportDlg 消息处理程序
BOOL CMUTPatientReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("Apply Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}
	ControlShow(show_search_index,FALSE);
	ControlShow(show_edit_index,FALSE);
	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}
BOOL CMUTPatientReportDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;
	return TRUE;
}
BOOL CMUTPatientReportDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

	nowRect.left = (APP_SCREEN_WIDTH  - 3*REPORT_BORDER_SPACE 
		-REPORT_SEARCH_WIDTH - REPORT_EDIT_WIDTH 
		- REPORT_MODIFY_WIDTH - REPORT_EXIT_WIDTH)/2;
	nowRect.right = nowRect.left + REPORT_EXIT_WIDTH;
	nowRect.top = REPORT_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + REPORT_EXIT_HEIGHT;
	m_ExitBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_BORDER_SPACE;
	nowRect.right = nowRect.left + REPORT_EDIT_WIDTH;
	//nowRect.top = REPORT_HEIGHT_SPACE;
	//nowRect.bottom = nowRect.top + REPORT_EDIT_HEIGHT;
	m_InputEdit.MoveWindow(&nowRect);
	m_EditRect.CopyRect(&nowRect);

	nowRect.right = nowRect.left+REPORT_TEXT_WIDTH;
	m_TextStatic.MoveWindow(&nowRect);

	nowRect.left += REPORT_EDIT_WIDTH + 2*REPORT_BORDER_SPACE;
	nowRect.right = nowRect.left + REPORT_SEARCH_WIDTH;
	//nowRect.top = REPORT_HEIGHT_SPACE;
	//nowRect.bottom = nowRect.top + REPORT_SEARCH_HEIGHT;
	m_DeleteBtn.MoveWindow(&nowRect);

	nowRect.left = APP_SCREEN_WIDTH - REPORT_BORDER_SPACE - REPORT_MODIFY_WIDTH;
	nowRect.right = nowRect.left + REPORT_MODIFY_WIDTH;
	//nowRect.top = REPORT_HEIGHT_SPACE;
	//nowRect.bottom = nowRect.top + REPORT_SEARCH_HEIGHT;
	m_ModifyBtn.MoveWindow(&nowRect);
	
	int width = APP_SCREEN_WIDTH - 2*REPORT_BORDER_SPACE;
	int height = APP_SCREEN_HEIGHT - 2*REPORT_BORDER_SPACE - 2*REPORT_SEARCH_HEIGHT - 2*REPORT_HEIGHT_SPACE;
	nowRect.left = REPORT_BORDER_SPACE;
	nowRect.right = nowRect.left + width;
	nowRect.top = nowRect.bottom + REPORT_HEIGHT_SPACE;
	nowRect.bottom = nowRect.top + height;
	m_ReportList.MoveWindow(&nowRect);
	m_ListBoxRect.CopyRect(&nowRect);


	width = (APP_SCREEN_WIDTH - 2*REPORT_BORDER_SPACE 
		- 4*REPORT_WIDTH_SPACE)/5; 
	nowRect.left = REPORT_BORDER_SPACE;
	nowRect.right = nowRect.left+width;
	nowRect.top = APP_SCREEN_HEIGHT - REPORT_BORDER_SPACE - REPORT_LOWERBTN_HEIGHT;
	nowRect.bottom = nowRect.top + REPORT_LOWERBTN_HEIGHT;
	m_SelectBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_WIDTH_SPACE;
	nowRect.right = nowRect.left+width;
	m_CancelBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_WIDTH_SPACE;
	nowRect.right = nowRect.left+width;
	m_DeleteBtn1.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_WIDTH_SPACE;
	nowRect.right = nowRect.left+width;
	m_ExportBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_WIDTH_SPACE;
	nowRect.right = nowRect.left+width;
	m_CompareBtn.MoveWindow(&nowRect);
	return TRUE;
}
BOOL CMUTPatientReportDlg::InitComStyle(void)
{
	m_ExitBtn.DrawBorder(FALSE);	
	m_ExitBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_ExitBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_ExitBtn.SetPngMaps(APP_BACK_IMAGE,FALSE);

	m_DeleteBtn.DrawBorder(FALSE);	
	m_DeleteBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_DeleteBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_DeleteBtn.SetPngMaps(APP_SEARCH_IMAGE,FALSE);


	m_ModifyBtn.DrawBorder(FALSE);	
	m_ModifyBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_ModifyBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
	m_ModifyBtn.SetPngMaps(APP_EDIT_IMAGE,FALSE);

	m_SelectBtn.DrawBorder(FALSE);	
	m_SelectBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_SelectBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_SelectBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SelectBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_CancelBtn.DrawBorder(FALSE);	
	m_CancelBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_CancelBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_CancelBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_CancelBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_DeleteBtn1.DrawBorder(FALSE);	
	m_DeleteBtn1.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_DeleteBtn1.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_DeleteBtn1.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_DeleteBtn1.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_ExportBtn.DrawBorder(FALSE);	
	m_ExportBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_ExportBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_ExportBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_ExportBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_CompareBtn.DrawBorder(FALSE);	
	m_CompareBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_CompareBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_CompareBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_CompareBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	m_TextStatic.SetFont(&StaticFont);
	//m_ReportList.SetFont(&newFont1);
//	m_ReportList.SetBkColor(APP_BK_COLOR1);					//缩略图
//	m_ReportList.CreateColumn();
// 	m_ReportList.InsertColumn(0,_T("编号"),LVCFMT_LEFT,100);
// 	m_ReportList.InsertColumn(1,_T("编号"),LVCFMT_LEFT,100);
// 	m_ReportList.SetItemText(0,0,_T("RR!"));
	CreateImageList();
	m_ReportList.SetImageList(&m_ImageList);
	m_ReportList.SetCheckBtnOk(FALSE);

// 	m_dcmlist.SetBkColor(APP_BK_COLOR1);
// 	m_dcmlist.CreateColumn();
// 	m_dcmlist.ShowWindow(FALSE);

	m_TextStatic.SetWindowText(_T("病例档案"));
	m_SelectBtn.SetWindowText(_T("全选"));
	m_CancelBtn.SetWindowText(_T("取消"));
	m_DeleteBtn1.SetWindowText(_T("删除"));
	m_ExportBtn.SetWindowText(_T("导出"));
	m_CompareBtn.SetWindowText(_T("比较"));

	return TRUE;
}
HBRUSH CMUTPatientReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_TEXT_COLOR1);

	}
	if(nCtlColor == CTLCOLOR_EDIT)
	{	
		m_InputEdit.CtlColor(pDC,nCtlColor);
	}

	return GetWndBkHBrush();
}
TGPATIENT CMUTPatientReportDlg::GetClickPatient()
{
 	CString strItem;
// 	DWORD pos = GetMessagePos();
// 	CPoint pt(LOWORD(pos), HIWORD(pos));
// 	ScreenToClient(&pt);
// 	CRect rect;
// 	m_ReportList.GetItemRect(m_ReportList.GetCurSel(),&rect);
// 	if(rect.PtInRect(pt))
// 	{
	int index = m_ReportList.GetCurSel();
	m_ReportList.GetText(index, strItem); 
	int pos = strItem.Find(_T("ID:"));
	CString patientname = strItem.Left(pos);
	patientname.Replace(_T("姓名:"),_T(""));
	patientname.Trim(_T("\n"));
	CString idstr = m_AdoManger->getPatientId(patientname);
	TGPATIENT tgPatinet;
	tgPatinet.ptid = idstr;
	tgPatinet.ptname = patientname;


	return tgPatinet;
	//}
	//return APP_NULL_STR;
}
void CMUTPatientReportDlg::ControlShow(UINT index,BOOL bShow)
{
	switch (index)
	{
		case show_search_index:
			if(bShow)
			{
				m_ExitBtn.ShowWindow(TRUE);
				m_InputEdit.ShowWindow(TRUE);
			}
			else
			{
				m_ExitBtn.ShowWindow(FALSE);
				m_InputEdit.ShowWindow(FALSE);
			}
			break;
		case show_edit_index:
			if(bShow)
			{
				m_SelectBtn.ShowWindow(TRUE);
				m_CancelBtn.ShowWindow(TRUE);
				m_DeleteBtn1.ShowWindow(TRUE);
				m_ExportBtn.ShowWindow(TRUE);
				m_CompareBtn.ShowWindow(TRUE);
			}
			else
			{
				m_SelectBtn.ShowWindow(FALSE);
				m_CancelBtn.ShowWindow(FALSE);
				m_DeleteBtn1.ShowWindow(FALSE);
				m_ExportBtn.ShowWindow(FALSE);
				m_CompareBtn.ShowWindow(FALSE);
			}
			break;
		default: break;
	}
}
void CMUTPatientReportDlg::OnBnClickedDeleteBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TextStatic.ShowWindow(FALSE);
	ControlShow(show_search_index,TRUE);
}
void CMUTPatientReportDlg::OnBnClickedDelete1Btn()
{

	//m_AdoManger->deleteTableData(_T("study"));
	int nCount = m_ReportList.GetSelCount();
	if(nCount <=0 ) 
	{
		AfxMessageBox(_T("选择为空"));
		return;
	}

	CArray<int,int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);
	m_ReportList.GetSelItems(nCount, aryListBoxSel.GetData());		
	CString str;
	for (int i=0; i<nCount; i++)
	{
		m_ReportList.GetText(aryListBoxSel[i]-i, str); 
		int pos = str.Find(_T("ID:"));
		CString patientname = str.Left(pos);
		patientname.Replace(_T("姓名:"),_T(""));
		patientname.Trim(_T("\n"));

		//if(!m_AdoManger->deletePatientByname(patientname))			//不删除病人信息 只删除对应dcm文件
			//return;
	
		CString idstr = m_AdoManger->getPatientId(patientname);			
		CStringArray *pDcmArray = m_AdoManger->getDicomFiles(idstr);	//删除路径下dcm及bmp文件
		if(pDcmArray == NULL) return;
		for(int ik=0;ik<pDcmArray->GetSize();ik++)
		{
			CString filename = pDcmArray->GetAt(ik);
			if(!PathFileExists(filename)) 
				continue;						//判断文件是否存在 用户点击鼠标过快造成数据库中存储相同文件
			if(!DeleteFile(filename))
			{
				AfxMessageBox(_T("deletefile err"));
				return;
			}
			int pos = filename.ReverseFind(_T('\\'));
			filename = filename.Right(pos);
			filename.TrimLeft(_T("\\dcm"));
			filename.Replace(_T(".dcm"),_T(".bmp"));
			filename = _T("\\") +filename;
			CString thumbnaildir = theApp.GetThumbnailImageDirectory();
			thumbnaildir += filename;
			if(!PathFileExists(thumbnaildir)) 
				continue;						//判断文件是否存在
			if(!DeleteFile(thumbnaildir))
			{
				AfxMessageBox(_T("deletefile err"));
				return;
			}

		}
		delete pDcmArray;												//释放内存
		m_AdoManger->deleteStudyInfo(idstr);							//删除数据库内容
		m_AdoManger->deleteDcmInfo(idstr);

		m_ReportList.DeleteString(aryListBoxSel[i]-i);
	}
	AfxMessageBox(_T("删除成功"));

}
void CMUTPatientReportDlg::OnBnClickedExportBtn()
{
	int nCount = m_ReportList.GetSelCount();
	if(nCount <=0 ) 
	{
		AfxMessageBox(_T("选择为空"));
		return;
	}
	CArray<int,int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);
	m_ReportList.GetSelItems(nCount, aryListBoxSel.GetData());

	
	CString strDcmfile = theApp.GetDcmDirtory();
	CString str;
	for (int i=0; i<nCount; i++)
	{
		m_ReportList.GetText(aryListBoxSel[i]-i, str); 
		int pos = str.Find(_T("ID:"));
		CString patientname = str.Left(pos);
		patientname.Replace(_T("姓名:"),_T(""));
		patientname.Trim(_T("\n"));

		theApp.CreateExportDirectory(patientname);
		CString strExport = theApp.GetExportDirectory();

		CString idstr = m_AdoManger->getPatientId(patientname);			
		CStringArray *pDcmArray = m_AdoManger->getDicomFiles(idstr);
		if(pDcmArray == NULL) return;
		for(int ik=0;ik<pDcmArray->GetSize();ik++)						//获取导出文件信息
		{
			CString filename = pDcmArray->GetAt(ik);
			CString oldname = filename;
			int pos = filename.ReverseFind(_T('\\'));
			filename = filename.Right(pos);
			filename.TrimLeft(_T("\\dcm"));
			CString newname = strExport + _T("\\");
			newname += filename;
			if(theApp.IsExportFileExist(newname))
				continue;
			if(!CopyFile(oldname,newname,FALSE))						//未添加病人名字
			{
				AfxMessageBox(_T("copyfile err"));
				return;
			}
		}
		delete pDcmArray;	
	}
	AfxMessageBox(_T("文件导出完成"));
}
void CMUTPatientReportDlg::OnBnClickedExitBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TextStatic.ShowWindow(TRUE);
	ControlShow(show_search_index,FALSE);
}

void CMUTPatientReportDlg::OnBnClickedModifyBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bEdit)
	{
		m_bEdit = TRUE;
		ControlShow(show_edit_index,TRUE);
		m_ReportList.SetCheckBtnOk();
	}
	else
	{
		m_bEdit = FALSE;
		ControlShow(show_edit_index,FALSE);
		m_ReportList.SetCheckBtnOk(FALSE);
	}

}
void CMUTPatientReportDlg::OnBnClickedSelectBtn()
{
	int index = m_ReportList.GetCount();
	for(int i=0;i<index;i++)
	{
		m_ReportList.SetSel(i);
	}
}
void CMUTPatientReportDlg::OnBnClickedCancelBtn()
{
	ControlShow(show_edit_index,FALSE);
	m_ReportList.SetCheckBtnOk(FALSE);
}
// void	CMUTPatientReportDlg::DcmListLoad(CRect rcItem)
// {
// 	CRect listRect;
// 	listRect.CopyRect(&rcItem);
// 	listRect.top = rcItem.bottom + m_ListBoxRect.top;
// 	listRect.bottom = listRect.top + m_ListBoxRect.Height() - rcItem.Height();
// 	m_dcmlist.MoveWindow(&listRect);
// 
// 	CString strFilePath = theApp.GetThumbnailImageDirectory();
// 	m_dcmlist.m_strImageDir = strFilePath;
// 	m_dcmlist.Load();
// 
// }
// LRESULT CMUTPatientReportDlg::OnDispList(WPARAM wParam,LPARAM lParam)
// {
// 	CListBoxST  *pListBox = (CListBoxST *)lParam; 
// 
// 	CString		itemStr;
// 	int index = m_ReportList.GetCurSel();
// 	m_ReportList.GetText(index,itemStr);
// 	if(!m_bIsDownNow)
// 	{
// 		m_ReportList.ReplaceString(index,itemStr,ICON_UP_INDEX);
// 		CRect rct;
// 		pListBox->GetItemRect(index,&rct);
// 		DcmListLoad(rct);
// 		m_dcmlist.ShowWindow(TRUE);
// 	}
// 	else
// 	{
// 		m_ReportList.ReplaceString(index,itemStr,ICON_DOWN_INDEX);
// 		m_dcmlist.ShowWindow(FALSE);
// 	}
// 
// 	m_ReportList.SetCurSel(-1);
// 
// 	m_bIsDownNow = !m_bIsDownNow;
// 
// 	return 1;
// }
CImage CMUTPatientReportDlg::ConvertPngToBmp(CString strImg)
{
	CImage tempImage;
	CString strDir;
	extern CMUTWndAppApp theApp;
	strDir = theApp.GetImageDirtory();
	//strDir += (_T("\\ui-pic\\") + strIn);
	strDir += strImg;
	tempImage.Destroy();
	tempImage.Load(strDir);
	//if(tempImage.IsNull()) 
		//return BTNST_INVALIDINDEX;

	if(32 == tempImage.GetBPP())
	{
		for(int i = 0; i < tempImage.GetWidth(); i++)  
		{  
			for(int j = 0; j < tempImage.GetHeight(); j++)  
			{  
				unsigned char* pucColor = reinterpret_cast<unsigned char *>(tempImage.GetPixelAddress(i , j));  
				pucColor[0] = (pucColor[0] * pucColor[3]+127) / 255;  
				pucColor[1] = (pucColor[1] * pucColor[3]+127)/ 255;  
				pucColor[2] = (pucColor[2] * pucColor[3]+127) / 255;  
			}  
		}  
	}
	return tempImage;
}
void CMUTPatientReportDlg::CreateImageList()
{
	BOOL	bRetValue = FALSE;
	HICON	hIcon = NULL;

	// Create image list
	bRetValue = m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 5, 1);
	ASSERT(bRetValue == TRUE);
	hIcon = AfxGetApp()->LoadIcon(IDI_UP_ICO);
	m_ImageList.Add(hIcon);
	hIcon = AfxGetApp()->LoadIcon(IDI_DOWN_ICO);
	m_ImageList.Add(hIcon);
	//CImage temp = ConvertPngToBmp(APP_ADD9_IMAGE);
} // End of CreateImageList
void CMUTPatientReportDlg::AcessInfoToDisplay()
{
	m_ReportList.ResetContent();
	//DWORD oldtime = ::GetTickCount();
	CArray <CMUTPatientInfoFunc>*pPatien_list = m_AdoManger->getpatients();
	//DWORD nowtime = ::GetTickCount() - oldtime;

	for(int i=0;i<pPatien_list->GetSize();i++)
	{
		//////////////////////////////////////////////////////////////////////////
		//依据doctorid获取病人信息
		CMUTPatientInfoFunc temppatient = pPatien_list->GetAt(i);
		CArray <CMUTStudyInfoFunc>* pStudy_list = m_AdoManger->getStudyidInfo(temppatient.m_patient_id);
		if(pStudy_list->IsEmpty()) continue;
		CString  patientname = temppatient.m_patient_username;
		CString	 patientbirthday = temppatient.m_patient_birthday;
		CString	 patientsex = temppatient.m_patient_sex;
		CString	 patienthistory = temppatient.m_history;
		CString  patientid = temppatient.m_patient_userid;
		CString  strPatinetInfo = _T("姓名:")+patientname + _T("\n")
			_T("ID:")+ patientid + _T("\n") 
			_T("生日:")+ patientbirthday + _T("\n")
			_T("性别:")+ patientsex + _T("\n") 
			_T("病史:")+ patienthistory;

		m_ReportList.AddString(strPatinetInfo,ICON_DOWN_INDEX);
// 		for(int j=0;j<pStudy_list->GetSize();j++)
// 		{
// 			CMUTStudyInfoFunc	tempstudy = pStudy_list->GetAt(j);
// 			CString studyid = tempstudy.m_studyid;
// 			CString ptid = tempstudy.m_patientid;
// 			//strStudyInfo = studyid;
// 			//////////////////////////////////////////////////////////////////////////
// 			//获取检查次数相关信息doctorid scantype 
// 			CString doctorname = APP_NULL_STR;
// 			CArray <CMUTDoctorInfoFunc>*pDoctor_list = m_AdoManger->getdoctors();
// 			for(int k = 0;k < pDoctor_list->GetSize();k++)
// 			{
// 				CMUTDoctorInfoFunc tempdoctor = pDoctor_list->GetAt(k);
// 				//if(k >= pDoctor_list->GetSize()-1) break;
// 				//CMUTDoctorInfoFunc tempdoctorNext = pDoctor_list->GetAt(k+1);
// 				if(!tempdoctor.m_doctor_id.Compare(tempstudy.m_doctorid))
// 				{
// 					doctorname = tempdoctor.m_doctor_username;
// 				}
// 			}
// 			//strStudyInfo += doctorname;
// 			//////////////////////////////////////////////////////////////////////////
// 			//获取dicom信息
// 
//  		CArray <CMUTDicomFileFunc> * pDcmFile_list = m_AdoManger->getDicomFiles(studyid,ptid);//获取当前病人第n次检查dcm文件
// 			int dcmcnt = pDcmFile_list->GetSize();
// 			for (int h = 0; h < dcmcnt; h++)
// 			{
// 				CMUTDicomFileFunc tmpdcmfile = pDcmFile_list->GetAt(h);
// 				CString dcminfo = studyid + _T("    ")+doctorname +_T("    ")+ tmpdcmfile.m_filename;
// 				m_ReportList.InsertString(-1,dcminfo);
// 			}
// 			delete pDcmFile_list;
//		}
	}
}

void CMUTPatientReportDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	if(m_bCheckAcessNow)
	{
		m_bCheckAcessNow = FALSE;
		AcessInfoToDisplay();
	}

}
void CMUTPatientReportDlg::OnOK()   //重载OnOK do nothing
{
	//CDialog::OnOK(); 
}
