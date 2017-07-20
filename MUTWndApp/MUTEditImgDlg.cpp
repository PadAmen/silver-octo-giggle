// MUTEditImgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MUTWndApp.h"
#include "MUTEditImgDlg.h"


// CMUTEditImgDlg �Ի���

IMPLEMENT_DYNAMIC(CMUTEditImgDlg, CDialog)

CMUTEditImgDlg::CMUTEditImgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTEditImgDlg::IDD, pParent)
	,m_bIsClickFromScanb(FALSE)
	,m_bIsClickFromReportInfo(FALSE)
	,m_bIsClickFromScanOver(FALSE)
{
	CMUTDlgBaseFunc::InitComRect();
	CMUTDlgBaseFunc::InitComStyle();
	newFont1.CreatePointFont(APP_FONT_POINT3,APP_FONT_FACENAME3,NULL);//����һ���µ�����
}

CMUTEditImgDlg::~CMUTEditImgDlg()
{
}

void CMUTEditImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPORT_BTN, m_ExportBtn);
	DDX_Control(pDX, IDC_DELETE_BTN, m_DeleteBtn);
	DDX_Control(pDX, IDC_SEND_BTN, m_SendBtn);
}


BEGIN_MESSAGE_MAP(CMUTEditImgDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_EXPORT_BTN, &CMUTEditImgDlg::OnBnClickedExportBtn)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DELETE_BTN, &CMUTEditImgDlg::OnBnClickedDeleteBtn)
END_MESSAGE_MAP()


// CMUTEditImgDlg ��Ϣ�������
BOOL CMUTEditImgDlg::OnInitDialog()
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

BOOL CMUTEditImgDlg::InitWindow(void)
{
	if(TRUE != this->InitComRect()||TRUE != this->InitComStyle())
		return FALSE;

	return TRUE;
}
BOOL CMUTEditImgDlg::InitComRect(void)
{
	CRect	rct;
	CRect	nowRect;

	GetAppWndRect(&rct);
	nowRect.left = 0;
	nowRect.top  = 0;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.bottom = nowRect.top + rct.Height();
	this->MoveWindow(&nowRect);

	CStatic *pPatientStatic = (CStatic *)GetDlgItem(IDC_PATIENT_STATIC);
	pPatientStatic->GetWindowRect(&rct);
	nowRect.left = (APP_SCREEN_WIDTH - 2*rct.Width() -APP_WIDTH_SAPCE - APP_BORDER_WIDTH)/2;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top = APP_BORDER_WIDTH;	//???
	nowRect.bottom = nowRect.top + rct.Height();
	pPatientStatic->MoveWindow(&nowRect);

	CStatic *pScanStatic = (CStatic *)GetDlgItem(IDC_SCAN_STATIC);
	nowRect.left = APP_SCREEN_WIDTH - SCANB_IMAGE_SPACE1 -rct.Width();
	nowRect.right = nowRect.left + rct.Width();
	pScanStatic->MoveWindow(&nowRect);

	m_rcImageRgn.left = SCANB_IMAGE_SPACE1;
	m_rcImageRgn.right = m_rcImageRgn.left + SCANB_IMAGE_WIDTH;
	m_rcImageRgn.top = rct.Height()+ SCANB_IMAGE_SPACE1;
	m_rcImageRgn.bottom = m_rcImageRgn.top + SCANB_MAX_HEIGHT;
	m_ImgRgn.CreateRectRgnIndirect(&m_rcImageRgn);

	m_DeleteBtn.GetWindowRect(&rct);
	nowRect.left = APP_BORDER_WIDTH;
	nowRect.right = nowRect.left + rct.Width();
	nowRect.top  = APP_SCREEN_HEIGHT - rct.Height() - APP_BORDER_WIDTH;
	nowRect.bottom = nowRect.top + rct.Height();
	m_DeleteBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + APP_WIDTH_SAPCE;
	nowRect.right = nowRect.left + rct.Width();
	m_ExportBtn.MoveWindow(&nowRect);

	nowRect.left = nowRect.right + APP_WIDTH_SAPCE;
	nowRect.right = nowRect.left + rct.Width();
	m_SendBtn.MoveWindow(&nowRect);

	return TRUE;
}
BOOL CMUTEditImgDlg::InitComStyle(void)
{
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

	m_SendBtn.DrawBorder(FALSE);	
	m_SendBtn.SetColor(BTNST_COLOR_BK_IN,COLOR_BK_IN);
	m_SendBtn.SetColor(BTNST_COLOR_BK_OUT,APP_BK_COLOR);
	m_SendBtn.SetColor(BTNST_COLOR_FG_IN,COLOR_FG_IN);
	m_SendBtn.SetColor(BTNST_COLOR_FG_OUT,COLOR_FG_OUT);

	CStatic *pPatientStatic = (CStatic *)GetDlgItem(IDC_PATIENT_STATIC);
	pPatientStatic->SetFont(&newFont1);
	pPatientStatic->SetWindowText(_T(""));
	CStatic *pScanStatic = (CStatic *)GetDlgItem(IDC_SCAN_STATIC);
	pScanStatic->SetFont(&newFont1);
	pScanStatic->SetWindowText(_T("ɨ�������"));

	return TRUE;
}
HBRUSH CMUTEditImgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(APP_MEATEXT_COLOR);

	}

	return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CMUTEditImgDlg::OpenImageFile(CDC *pDC,CString bmpName)
{
	//��������洢ͼƬ��Ϣ
	BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�

	//��ֻ���ķ�ʽ���ļ� ��ȡbmpͼƬ������ bmp�ļ�ͷ ��Ϣ ����
	if(!bmpFile.Open(bmpName, CFile::modeRead|CFile::typeBinary)) 
		return;
	if (bmpFile.Read(&bmpHeader,sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo,sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//Ϊͼ����������ռ�
	memcpy(pBmpInfo,&bmpInfo,sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData,dataBytes);
	bmpFile.Close();

	//��ʾͼ��
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(),m_rcImageRgn.left,m_rcImageRgn.top,m_rcImageRgn.Width(),m_rcImageRgn.Height()
		,0,0,bmpInfo.biWidth,bmpInfo.biHeight,pBmpData,pBmpInfo,DIB_RGB_COLORS,SRCCOPY);

	delete []pBmpData;
	delete pBmpInfo;

}
void CMUTEditImgDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� __super::OnPaint()
	CString dcmdir = APP_NULL_STR;
	m_clickname = pReportInfoDlg->m_DcmList.GetClickItemFileName();		//���������а���Ӱ��༭���� needs modify
	if(m_clickname.IsEmpty())
	{
		m_clickname = pScanbMainDlg->m_ListImg.GetItemFileName();
		if(m_clickname.IsEmpty())
			return;
		m_bIsClickFromScanb = TRUE;
		dcmdir = pScanbMainDlg->m_ListImg.m_strImageDir + _T("\\");
		dcmdir += m_clickname;
	}
	else
	{
		m_bIsClickFromReportInfo = TRUE;
		dcmdir = pReportInfoDlg->m_DcmList.m_strImageDir + _T("\\");
		dcmdir += m_clickname;		
	}
	
	OpenImageFile(&dc,dcmdir);
}
void CMUTEditImgDlg::OnBnClickedDeleteBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString clickname = m_clickname;
	CString strBmpDir = theApp.GetThumbnailImageDirectory();
	strBmpDir += _T("\\");
	strBmpDir += clickname;
	DeleteFile(strBmpDir);
	CString strDcmDir = theApp.GetDcmDirtory();
	strDcmDir += _T("\\");
	clickname.Replace(_T(".bmp"),_T(".dcm"));
	strDcmDir += clickname;
	DeleteFile(strDcmDir);
	if(m_bIsClickFromScanb)
	{
		m_bIsClickFromScanb = FALSE;
		pScanbMainDlg->m_ListImg.DeletSelectedItem();
		pScanbMainDlg->m_ListImg.Load();
	}
	if(m_bIsClickFromReportInfo)
	{
		m_bIsClickFromReportInfo = FALSE;
		pReportInfoDlg->m_DcmList.DeletSelectedItem();
	}
	//if(m_bIsClickFromReportInfo)
	//pScanbMainDlg->m_ListImg.DeleteItem()
}
void CMUTEditImgDlg::OnBnClickedExportBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString clickname = m_clickname;
	CString strDcmDir = theApp.GetDcmDirtory();
	strDcmDir += _T("\\");
	clickname.Replace(_T(".bmp"),_T(".dcm"));
	strDcmDir += clickname;
	CString strExport = theApp.GetExportDirectory();
		strExport + _T("\\");
	//strExport += filename;
	
}

void CMUTEditImgDlg::OnOK()   //����OnOK do nothing
{
	//CDialog::OnOK(); 
}