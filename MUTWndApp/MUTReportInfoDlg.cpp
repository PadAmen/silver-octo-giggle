// MUTReportInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTReportInfoDlg.h"


// CMUTReportInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMUTReportInfoDlg, CDialog)

CMUTReportInfoDlg::CMUTReportInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTReportInfoDlg::IDD, pParent)
	,m_bEdit(FALSE)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	m_AdoManger = CMUTDAOManagerFunc::GetDAOManager();

}

CMUTReportInfoDlg::~CMUTReportInfoDlg()
{
}

void CMUTReportInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SELECTD_BTN1, m_SelectBtn);
	DDX_Control(pDX, IDC_CANCEL_BTN1, m_CancelBtn);
	DDX_Control(pDX, IDC_SEARCH_BTN1, m_SarchBtn);
	DDX_Control(pDX, IDC_EXPORT_BTN1, m_ExportBtn);
	DDX_Control(pDX, IDC_COMPARE_BTN1, m_CompareBtn);
	DDX_Control(pDX, IDC_LIST1, m_DcmList);
	DDX_Control(pDX, IDC_EXIT_BTN1, m_ExitBtn);
	DDX_Control(pDX, IDC_DELETE_BTN1, m_DeleteBtn);
	DDX_Control(pDX, IDC_MODIFY_BTN1, m_ModifyBtn);
	DDX_Control(pDX, IDC_INPUT_EDIT1, m_InputEdit);
}


BEGIN_MESSAGE_MAP(CMUTReportInfoDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_MODIFY_BTN1, &CMUTReportInfoDlg::OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_EXIT_BTN1, &CMUTReportInfoDlg::OnBnClickedExitBtn)
	ON_BN_CLICKED(IDC_SEARCH_BTN1, &CMUTReportInfoDlg::OnBnClickedSearchBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SELECTD_BTN1, &CMUTReportInfoDlg::OnBnClickedSelectdBtn1)
	ON_BN_CLICKED(IDC_DELETE_BTN1, &CMUTReportInfoDlg::OnBnClickedDeleteBtn1)
	ON_BN_CLICKED(IDC_CANCEL_BTN1, &CMUTReportInfoDlg::OnBnClickedCancelBtn1)
	ON_BN_CLICKED(IDC_EXPORT_BTN1, &CMUTReportInfoDlg::OnBnClickedExportBtn1)
END_MESSAGE_MAP()


// CMUTReportInfoDlg 消息处理程序
// CMUTEditImgDlg 消息处理程序
BOOL CMUTReportInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(TRUE != this->InitWindow())
	{
		MessageBox(_T("About Dialog InitWindow Err!"));
		goto NORMAL_EXIT;
	}
	ControlShow(show_edit_index,TRUE);
	ControlShow(show_search_index,FALSE);
	return TRUE;

NORMAL_EXIT:
	::SendMessage(m_hWnd,WM_CLOSE,0,NULL);
	return FALSE;
}

BOOL CMUTReportInfoDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTReportInfoDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

// 	nowRect.left = (APP_SCREEN_WIDTH  - 3*REPORT_BORDER_SPACE 
// 		-REPORT_SEARCH_WIDTH - REPORT_EDIT_WIDTH 
// 		- REPORT_MODIFY_WIDTH - REPORT_EXIT_WIDTH)/2;
// 	nowRect.right = nowRect.left + REPORT_EXIT_WIDTH;
// 	nowRect.top = REPORT_HEIGHT_SPACE;
// 	nowRect.bottom = nowRect.top + REPORT_EXIT_HEIGHT;
// 	m_ExitBtn.MoveWindow(&nowRect);
// 
// 	nowRect.left = nowRect.right + REPORT_BORDER_SPACE;
// 	nowRect.right = nowRect.left + REPORT_EDIT_WIDTH;
// 	//nowRect.top = REPORT_HEIGHT_SPACE;
// 	//nowRect.bottom = nowRect.top + REPORT_EDIT_HEIGHT;
// 	m_InputEdit.MoveWindow(&nowRect);
// // 	m_EditRect.CopyRect(&nowRect);
// // 
// // 	nowRect.right = nowRect.left+REPORT_TEXT_WIDTH;
// // 	m_TextStatic.MoveWindow(&nowRect);
// 
// 	nowRect.left += REPORT_EDIT_WIDTH + 2*REPORT_BORDER_SPACE;
// 	nowRect.right = nowRect.left + REPORT_SEARCH_WIDTH;
// 	//nowRect.top = REPORT_HEIGHT_SPACE;
// 	//nowRect.bottom = nowRect.top + REPORT_SEARCH_HEIGHT;
// 	m_SarchBtn.MoveWindow(&nowRect);
// 
// 	nowRect.left = APP_SCREEN_WIDTH - REPORT_BORDER_SPACE - REPORT_MODIFY_WIDTH;
// 	nowRect.right = nowRect.left + REPORT_MODIFY_WIDTH;
// 	//nowRect.top = REPORT_HEIGHT_SPACE;
// 	//nowRect.bottom = nowRect.top + REPORT_SEARCH_HEIGHT;
// 	m_ModifyBtn.MoveWindow(&nowRect);

	int width = APP_SCREEN_WIDTH - 2*REPORT_BORDER_SPACE;
	int height = APP_SCREEN_HEIGHT - 2*REPORT_BORDER_SPACE - 2*REPORT_SEARCH_HEIGHT - 2*REPORT_HEIGHT_SPACE;
	nowRect.left = REPORT_BORDER_SPACE;
	nowRect.right = nowRect.left + width;
	nowRect.top = REPORT_HEIGHT_SPACE1;
	nowRect.bottom = nowRect.top + height;
	m_DcmList.MoveWindow(&nowRect);

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
	m_DeleteBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_WIDTH_SPACE;
	nowRect.right = nowRect.left+width;
	m_ExportBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + REPORT_WIDTH_SPACE;
	nowRect.right = nowRect.left+width;
	m_CompareBtn.MoveWindow(&nowRect);
	return TRUE;
}
BOOL CMUTReportInfoDlg::InitComStyle(void)
{
// 	m_ExitBtn.DrawBorder(FALSE);	
// 	m_ExitBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
// 	m_ExitBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
// 	m_ExitBtn.SetPngMaps(APP_BACK_IMAGE,FALSE);
// 
// 	m_SarchBtn.DrawBorder(FALSE);	
// 	m_SarchBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
// 	m_SarchBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
// 	m_SarchBtn.SetPngMaps(APP_SEARCH_IMAGE,FALSE);
// 
// 
// 	m_ModifyBtn.DrawBorder(FALSE);	
// 	m_ModifyBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
// 	m_ModifyBtn.SetColor(BTNST_COLOR_BK_OUT,COLOR_BK_OUT);
// 	m_ModifyBtn.SetPngMaps(APP_EDIT_IMAGE,FALSE);

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

	m_DeleteBtn.DrawBorder(FALSE);	
	m_DeleteBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_DeleteBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_DeleteBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_DeleteBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

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

	m_DcmList.SetBkColor(APP_BK_COLOR1);
	m_DcmList.SetTextBkColor(APP_BK_COLOR1);
	m_DcmList.SetTextColor(APP_TEXT_COLOR1);
	m_DcmList.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);//LVS_EX_GRIDLINES|
	m_DcmList.CreateColumn();

	//m_TextStatic.SetWindowText(_T("病例档案"));
	m_SelectBtn.SetWindowText(_T("全选"));
	m_CancelBtn.SetWindowText(_T("取消"));
	m_DeleteBtn.SetWindowText(_T("删除"));
	m_ExportBtn.SetWindowText(_T("导出"));
	m_CompareBtn.SetWindowText(_T("比较"));

	return TRUE;
}
void CMUTReportInfoDlg::ControlShow(UINT index,BOOL bShow)
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
			m_DeleteBtn.ShowWindow(TRUE);
			m_ExportBtn.ShowWindow(TRUE);
			m_CompareBtn.ShowWindow(TRUE);
		}
		else
		{
			m_SelectBtn.ShowWindow(FALSE);
			m_CancelBtn.ShowWindow(FALSE);
			m_DeleteBtn.ShowWindow(FALSE);
			m_ExportBtn.ShowWindow(FALSE);
			m_CompareBtn.ShowWindow(FALSE);
		}
		break;
		default: break;
	}
}
HBRUSH CMUTReportInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何属性
	if(nCtlColor == CTLCOLOR_EDIT)
	{	
		m_InputEdit.CtlColor(pDC,nCtlColor);
	}
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}
void CMUTReportInfoDlg::OnBnClickedModifyBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bEdit)
	{
		m_bEdit = TRUE;
		ControlShow(show_edit_index,TRUE);
	}
	else
	{
		m_bEdit = FALSE;
		ControlShow(show_edit_index,FALSE);
		//this->Invalidate();
	}
}

void CMUTReportInfoDlg::OnBnClickedExitBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ControlShow(show_search_index,FALSE);
}

void CMUTReportInfoDlg::OnBnClickedSearchBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	ControlShow(show_search_index,TRUE);	

}

void CMUTReportInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 __super::OnPaint()
	if(!m_ReportDlg->m_ReportList.IsDcmlistUpdate()) return;
	m_ReportDlg->m_ReportList.SetDcmlistUpdate(FALSE);

	m_DcmList.Clear();
	int dcmcnt = 0;
	CString strFilePath = theApp.GetThumbnailImageDirectory();				//从数据库中读取dcm及bmp文件并显示
	m_DcmList.m_strImageDir = strFilePath;
	m_clickpatient = m_ReportDlg->GetClickPatient();						//从ReportDlg中获取当前点击病人信息
	CString idstr = m_clickpatient.ptid;
	CArray<CMUTDoctorInfoFunc> *pDoctorList = m_AdoManger->getdoctors();
	CArray<CMUTStudyInfoFunc> *pStudyidInfo = m_AdoManger->getStudyidInfo(idstr);

	if(pDoctorList->IsEmpty()||pStudyidInfo->IsEmpty()) 
		return;
	for(int i=0;i<pStudyidInfo->GetSize();i++)
	{
		CMUTStudyInfoFunc study = pStudyidInfo->GetAt(i);
		CArray<CMUTDicomFileFunc> *pDcmFile = m_AdoManger->getDicomFiles(study.m_studyid,idstr);
		CString studytime;			//检查开始第一次保存图片时间
		int studydcmcnt = pDcmFile->GetSize();
		for(int ik=0;ik<studydcmcnt;ik++)
		{
			CMUTDicomFileFunc dicomfile = pDcmFile->GetAt(ik);
			CString  filename = dicomfile.m_filename;
			if(0 == ik) 
			{
				int pos = filename.Find(_T("."));
				studytime = filename.Left(pos);
			}
			filename.Replace(_T(".dcm"),_T(".bmp"));
			m_DcmList.m_VectorImageNames.push_back(filename);	
		}
		CString doctorname;
		for(int di =0;di < pDoctorList->GetSize();di ++)
		{
			CMUTDoctorInfoFunc doctor = pDoctorList->GetAt(di);
			if(study.m_doctorid == doctor.m_doctor_id)
			{
				doctorname = doctor.m_doctor_username;
				break;
			}
		}
		CString strCloum0,strCloum1;
		strCloum0 += study.m_studyid;
		strCloum0 += _T("\n");
		strCloum0 += studytime;
		strCloum1 += study.m_scantype;
		strCloum1 += _T("\n");
		strCloum1 += doctorname;
		m_DcmList.SetHeaderText(strCloum0,strCloum1);
		m_DcmList.Load(dcmcnt);
		dcmcnt += studydcmcnt;
		delete pDcmFile;
		m_DcmList.m_VectorImageNames.clear();
	}

}

void CMUTReportInfoDlg::OnBnClickedSelectdBtn1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0;i<m_DcmList.GetItemCount();i++)
	{
		ListView_SetCheckState(m_DcmList.GetSafeHwnd(),i,TRUE);
	}

}

void CMUTReportInfoDlg::OnBnClickedDeleteBtn1()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<int> selectindex;
	int itemcount = m_DcmList.GetItemCount();
	for(int i=0;i<itemcount;i++)
	{
		BOOL bCheck = ListView_GetCheckState(m_DcmList.GetSafeHwnd(),i);
		if(bCheck)
		selectindex.push_back(i);
	}
	if(selectindex.empty()) 
	{
		AfxMessageBox(_T("选择为空"));
			return ;
	}
	CString strBmpDir = theApp.GetThumbnailImageDirectory();
	CString strDcmDir = theApp.GetDcmDirtory();
	vector<CString> *pSelectItemStr = m_DcmList.DeleteSelectItemAndFile(strDcmDir,strBmpDir,selectindex);		//删除路径下bmp文件及dcm文件
	if(NULL == pSelectItemStr) 
	{
		delete pSelectItemStr;
		return;
	}
	//CString 
	for(uint k=0;k<pSelectItemStr->size();k++)				//删除数据库dicomfile记录
	{
		CString filename = pSelectItemStr->at(k);
		m_AdoManger->deleteDcmFile(filename);
	}	
	
	if(itemcount == selectindex.size())		//删除整个病人dcm文件时 删除数据库中study表记录
	{
		//TGPATIENT patient = m_ReportDlg->GetClickPatient();
		CString idstr = m_clickpatient.ptid;
		m_AdoManger->deleteStudyInfo(idstr);
	}
	delete pSelectItemStr;
	m_ReportDlg->m_ReportList.SetDcmlistUpdate();			//刷新reportinfo窗口ctrllist
	Invalidate();
	m_ReportDlg->SetAcessCheck();							//刷新report窗口listbox
}

void CMUTReportInfoDlg::OnBnClickedCancelBtn1()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0;i<m_DcmList.GetItemCount();i++)
	{
		ListView_SetCheckState(m_DcmList.GetSafeHwnd(),i,FALSE);
	}
}

void CMUTReportInfoDlg::OnBnClickedExportBtn1()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<int> selectindex;
	int itemcount = m_DcmList.GetItemCount();
	for(int i=0;i<itemcount;i++)
	{
		BOOL bCheck = ListView_GetCheckState(m_DcmList.GetSafeHwnd(),i);
		if(bCheck)
			selectindex.push_back(i);
	}
	if(selectindex.empty()) 
	{
		AfxMessageBox(_T("选择为空"));
		return ;
	}
	CString patientname = m_clickpatient.ptname;						//检查Export中是否存在该patient文件夹
	theApp.CreateExportDirectory(patientname);							
	CString strExport = theApp.GetExportDirectory();
	vector <CString> *pItemStr = m_DcmList.GetSelectImageFileName(selectindex);
	CString strdcmdir = theApp.GetDcmDirtory();
	for(uint i=0;i<pItemStr->size();i++)
	{
		CString filename = pItemStr->at(i);
		filename.Replace(_T(".bmp"),_T(".dcm"));
		CString oldname = strdcmdir + _T("\\");
		oldname += filename;
		CString newname = strExport + _T("\\");
		newname += filename;
		if(theApp.IsExportFileExist(newname))
			continue;
		if(!CopyFile(oldname,newname,FALSE))							//未添加病人名字
		{
			AfxMessageBox(_T("copyfile err"));
			delete pItemStr;
			return;
		}
	}
	delete pItemStr;
	AfxMessageBox(_T("文件导出完成"));
}
