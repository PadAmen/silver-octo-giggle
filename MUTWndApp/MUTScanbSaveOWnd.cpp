// SaveWnd.cpp : 实现文件
//

#include "stdafx.h"
//包含Dcmtk开源库的头文件
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmjpeg/djdecode.h"
#include "dcmtk/dcmdata/dcvrfd.h"
#include "StringConvert.h"
//包含自定义的头文件
#include "MUTWndApp.h"
#include "MUTScanbSaveOWnd.h"
//包含系统头文件
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Shlwapi.h"
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <cstring>



// CSaveWnd 对话框

IMPLEMENT_DYNAMIC(CMUTScanbSaveOWnd, CDialog)

CMUTScanbSaveOWnd::CMUTScanbSaveOWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CMUTScanbSaveOWnd::IDD, pParent)
	//,m_pDcm(NULL)
	,pDicomDibits(NULL)
	,m_lpBMIH(NULL)
	//,m_pDicomFile(NULL)
	,m_needcreatenewdcmdirectory(TRUE)
{
	m_brush.CreateSolidBrush(APP_POPUP_COLOR);
	//m_hParentWnd = pParent->GetSafeHwnd();

}

CMUTScanbSaveOWnd::~CMUTScanbSaveOWnd()
{
	m_brush.DeleteObject();
}

void CMUTScanbSaveOWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMUTScanbSaveOWnd, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_TEST, &CMUTScanbSaveOWnd::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_LOCAL, &CMUTScanbSaveOWnd::OnBnClickedBtnLocal)
END_MESSAGE_MAP()


// CSaveWnd 消息处理程序

HBRUSH CMUTScanbSaveOWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
// 	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
// 
// 	// TODO:  在此更改 DC 的任何属性
// 
// 	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
// 	return hbr;
	return m_brush;

}

void CMUTScanbSaveOWnd::OnBnClickedBtnTest()
{
	// TODO: 在此添加控件通知处理程序代码	
	this->ShowWindow(FALSE);

	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = _T("DCM File (*.dcm)");
	dlg.m_ofn.lpstrTitle = _T("Open DCM File");
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName();
		//printf("filename:");
		//OpenDCMFile(filename);
		::SendMessage(m_hParentWnd,WM_DISP_IMAGE,0,(LPARAM)&filename);
	}
	//::SendMessage(m_hParentWnd,WM_DISP_IMAGE,0,NULL);
}

void CMUTScanbSaveOWnd::OnBnClickedBtnLocal()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(FALSE);

	::SendMessage(m_hParentWnd,WM_SAVE_IMAGE,0,(LPARAM)this);
	//SaveDcmFile(datetime);
}


// void CMUTScanbSaveOWnd::OpenDCMFile(LPCTSTR lpszPathName)
// {
// #if 1
// 	char *str = NULL;
// 	wchar_t *wstr = NULL;
// 
// 	//GetDlgItem(IDC_BUTTON1)->ShowWindow(FALSE);
// 	//GetDlgItem(IDC_BUTTON2)->ShowWindow(FALSE);
// 	DJDecoderRegistration::registerCodecs();//register JPEG codecs
// 
// 	if (m_pDicomFile != NULL)
// 	{
// 		delete m_pDicomFile;
// 		m_pDicomFile = NULL;
// 	}
// 	if (m_pDcm != NULL)
// 	{
// 		delete m_pDcm;
// 		m_pDcm = NULL;
// 	}
// 
// 	m_pDicomFile = new DcmFileFormat();
// 
// 	//CHAR *str = NULL;
// 	str = encode(lpszPathName, CP_OEMCP);//support 中文目录和中文文件
// 	OFCondition stat = m_pDicomFile->loadFile(str);
// 	if(!stat.good())
// 	{
// 		MessageBox(_T("ERR!"));
// 		exit(0);
// 	}
// 
// 	delete str;
// 	str = NULL;
// 
// 	m_pDataset = m_pDicomFile->getDataset();
// 
// 	E_TransferSyntax xfer = m_pDataset->getOriginalXfer();
// 
// 	OFString patientid;
// 	m_pDataset->findAndGetOFString(DCM_PatientID, patientid);
// 
// 	m_pDcm = new DicomImage(m_pDataset, xfer);
// 
// 	EI_Status status = m_pDcm->getStatus();
// 
// 	if (m_pDcm->getStatus() != EIS_Normal)
// 	{
// 		//AfxMessageBox(DicomImage::getString(dcm->getStatus()));
// 
// 		wstr = decode(DicomImage::getString(m_pDcm->getStatus()), CP_UTF8);
// 
// 		MessageBox(wstr);
// 		delete wstr;
// 		wstr = NULL;
// 		exit(0);
// 	}
// 
// 	if (pDicomDibits != NULL)
// 		delete[]pDicomDibits;
// 	// 	double cc,cw;
// 	// 	dcm->getWindow(cc,cw);
// 	// 	dcm->setWindow(cc,cw);
// 	size = m_pDcm->createWindowsDIB(pDicomDibits, 0, 0, 24, 1, 1);
// 
// 
// 	if (size == 0)
// 	{
// 		//AfxMessageBox("Create DIB failed!");
// 		AfxMessageBox(_T("Create DIB failed!"));
// 
// 		return;
// 	}
// 	if (m_lpBMIH != NULL)
// 	{
// 		delete m_lpBMIH;
// 		m_lpBMIH = NULL;
// 	}
// 
// 	//m_lpBMIH include BITMAPINFOHEADER adn palette.
// 	m_lpBMIH = (LPBITMAPINFOHEADER) new char[sizeof(BITMAPINFOHEADER)
// 		+ sizeof(RGBQUAD) * 256];
// 
// 	m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
// 	m_lpBMIH->biWidth = m_pDcm->getWidth();
// 	m_lpBMIH->biHeight = m_pDcm->getHeight();
// 	m_lpBMIH->biPlanes = 1;
// 	m_lpBMIH->biBitCount = 24;
// 	m_lpBMIH->biCompression = BI_RGB;
// 	m_lpBMIH->biSizeImage = 0;
// 	m_lpBMIH->biXPelsPerMeter = 0;
// 	m_lpBMIH->biYPelsPerMeter = 0;
// 
// 	OFString wc, ww;
// 	if (m_pDataset->findAndGetOFString(DCM_WC, wc).good() &&
// 		m_pDataset->findAndGetOFString(DCM_WW, ww).good())
// 	{
// 		m_curWC = atof(wc.c_str());
// 		m_curWW = atof(ww.c_str());
// 		m_pDcm->setWindow(m_curWC, m_curWW);
// 	}
// 
// 	OFString sample, bitsstored, bitsallocated;
// 	m_pDataset->findAndGetOFString(DCM_SAMPLESPERPIXEL, sample);
// 	m_pDataset->findAndGetOFString(DCM_BITSSTORED, bitsstored);
// 	m_pDataset->findAndGetOFString(DCM_BITSALLOCATED, bitsallocated);
// 
// 
// #endif
// }
// BOOL CMUTScanbSaveOWnd::DrawDcmFile(CDC *pDC,CRect rect)
// {
// 	if (m_pDcm != NULL)
// 	{
// 
// 		m_destHeight = rect.Height();
// 		LONG width = m_lpBMIH->biWidth;
// 		LONG height = m_lpBMIH->biHeight;
// 		m_destWidth = m_lpBMIH->biWidth*m_destHeight / m_lpBMIH->biHeight;
// 
// 		CRect rect1;
// 		SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);//修复图片失真的问题
// 
// 		StretchDIBits(pDC->m_hDC, rect.left, rect.top, rect.Width(),
// 			rect.Height(), 0, 0, m_lpBMIH->biWidth,
// 			m_lpBMIH->biHeight, pDicomDibits,
// 			(LPBITMAPINFO)m_lpBMIH, DIB_RGB_COLORS, SRCCOPY);
// 
// 	}
// 	return TRUE;
// }
// BYTE* CMUTScanbSaveOWnd::CaptureScreen(CDC *pDC,CRect rect,int* size)
// {
// 
// 
// 	CBitmap bitmap;
// 	CDC memDC;
// 
// 	BITMAP bInfo;
// 
// 	//CClientDC dc(this);
// 	//CMeDC memDC(&dc, &m_rect, RGB(0, 0, 0));
// 	//CDC 
// 
// 	memDC.CreateCompatibleDC(pDC);
// 
// 	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
// 	memDC.SelectObject(&bitmap);
// 	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rect.left, rect.top, SRCCOPY);
// 
// 	bitmap.GetBitmap(&bInfo);
// 
// 
// 	//计算调色板大小 
// 	int panelsize = 0;
// 	if (bInfo.bmBitsPixel<24) //非真彩色 
// 	{
// 		panelsize = pow((double)2, bInfo.bmBitsPixel)*sizeof(RGBQUAD);
// 	}
// 
// 	//定义位图信息 
// 	BITMAPINFO* bMapInfo = (BITMAPINFO*)LocalAlloc(LPTR, sizeof(BITMAPINFO) + panelsize);
// 	bMapInfo->bmiHeader.biBitCount = bInfo.bmBitsPixel;
// 	//bMapInfo->bmiHeader.biBitCount = 32;
// 	bMapInfo->bmiHeader.biClrImportant = 0;
// 	bMapInfo->bmiHeader.biCompression = BI_RGB;
// 	bMapInfo->bmiHeader.biHeight = -bInfo.bmHeight; //fix picture up and down
// 	bMapInfo->bmiHeader.biPlanes = bInfo.bmPlanes;
// 	bMapInfo->bmiHeader.biSize = sizeof(BITMAPINFO);
// 	bMapInfo->bmiHeader.biSizeImage = bInfo.bmHeight*bInfo.bmWidthBytes;
// 	bMapInfo->bmiHeader.biWidth = bInfo.bmWidth;
// 	bMapInfo->bmiHeader.biXPelsPerMeter = 0;
// 	bMapInfo->bmiHeader.biYPelsPerMeter = 0;
// 
// 
// 
// 	char* pData = new char[bMapInfo->bmiHeader.biSizeImage];
// 	int len = GetDIBits(memDC.m_hDC, bitmap, 0, bInfo.bmHeight, pData, bMapInfo, DIB_RGB_COLORS);
// 	//*size = bMapInfo->bmiHeader.biSizeImage;
// 
// 	int nbyte = bInfo.bmBitsPixel / 8;
// 	BYTE * modata = new BYTE[bInfo.bmWidth * bInfo.bmHeight];
// /*	BYTE * rgbdata = new BYTE[bInfo.bmWidth * bInfo.bmHeight * 3];*/
// 
// 	/*
// 	int k = 0;
// 	for (int i = 0; i < bInfo.bmWidth; ++i)
// 	{
// 	for (int j = 0; j < bInfo.bmHeight; ++j)
// 	{
// 	BYTE r = pData[i * nbyte + j * bInfo.bmWidthBytes + 2];
// 	BYTE g = pData[i * nbyte + j * bInfo.bmWidthBytes + 1];
// 	BYTE b = pData[i * nbyte + j * bInfo.bmWidthBytes + 0];
// 	rgbdata[k] = r;
// 	rgbdata[k + 1] = g;
// 	rgbdata[k + 2] = b;
// 	k = k + 3;
// 	}
// 	}
// 	*size = k;
// 	*/
// 	//it is ok, but picture is up and down.
// 
// // 	int j = 0;
// // 	//swap B & R, remove alpha.
// // 	for (int i = 0; i< bInfo.bmWidth * bInfo.bmHeight * nbyte; i += 4)
// // 	{
// // 
// // 		byte temp = pData[i];
// // 		rgbdata[j] = pData[i + 2];
// // 		rgbdata[j + 1] = pData[i + 1];
// // 		rgbdata[j + 2] = temp;
// // 
// // 		j = j + 3;
// // 
// // 	}
// // 	*size = j;
// 
// 	int j=0;
// 	for (int i = 0; i< bInfo.bmWidth * bInfo.bmHeight * nbyte; i += nbyte)
// 	{
// 		modata[j] = pData[i];
// 		j = j + 1;
// 	}
// 	*size = j;
// 	/*
// 	//it worked ,but let and right
// 	int j = 0;
// 	//swap B & R, remove alpha.
// 	for (int i = bInfo.bmWidth * bInfo.bmHeight * nbyte -1 ; i > 0; i -= 4)
// 	{
// 
// 
// 	rgbdata[j] = pData[i - 1 ];
// 	rgbdata[j + 1] = pData[i - 2];
// 	rgbdata[j + 2] = pData[i - 3];
// 
// 	j = j + 3;
// 
// 	}
// 	*size = j;
// 	*/
// 	LocalFree(bMapInfo);
// 	bitmap.DeleteObject();
// 	memDC.DeleteDC();
// 	delete pData;
// 
// 	return modata;
// 
// }
// void CMUTScanbSaveOWnd::SaveDcmFile(CDC *pDC,CRect rect,COleDateTime datetime)
// {
// 
// 	DJDecoderRegistration::registerCodecs();//register JPEG codecs
// 	DcmFileFormat newfileFormat;
// 
// 	DcmDataset *newDataset = newfileFormat.getDataset();
// 	char uid[100];
// 	newDataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
// 	newDataset->putAndInsertString(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);
// 	//type 1 attributes.
// 	newDataset->putAndInsertString(DCM_StudyInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_STUDY_UID_ROOT));
// 	newDataset->putAndInsertString(DCM_SeriesInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_SERIES_UID_ROOT));
// 	//type 2 attributes
// 	newDataset->putAndInsertString(DCM_PatientID, "12345");
// 
// 	newDataset->putAndInsertString(DCM_PatientName, "ly");
// 	//newDataset->putAndInsertString(DCM_PatientBirthDate, "00000000");
// 	newDataset->putAndInsertString(DCM_PatientSex, "M");
// 
// 	CT2A asciitime(CTime::GetCurrentTime().Format("%H:%M"));
// 
// 	newDataset->putAndInsertString(DCM_StudyDate, asciitime);
// 	newDataset->putAndInsertString(DCM_StudyTime, asciitime);
// 
// 	newDataset->putAndInsertString(DCM_AccessionNumber, "");
// 	//newDataset->putAndInsertString(DCM_ReferringPhysicianName,"");
// 	newDataset->putAndInsertString(DCM_StudyID, "1");
// 	newDataset->putAndInsertString(DCM_SeriesNumber, "1");
// 
// 	newDataset->putAndInsertString(DCM_ModalitiesInStudy, "CR");
// 	newDataset->putAndInsertString(DCM_Modality,"CR");
// 
// 	newDataset->putAndInsertString(DCM_NumberOfStudyRelatedInstances, "1");
// 	newDataset->putAndInsertString(DCM_NumberOfStudyRelatedSeries, "1");
// 	newDataset->putAndInsertString(DCM_NumberOfSeriesRelatedInstances, "1");
// 	newDataset->putAndInsertString(DCM_PatientOrientation, "F/A");
// 	newDataset->putAndInsertString(DCM_ImageLaterality, "U");
// 	//rgb is ok.
// 	/*
// 	newDataset->putAndInsertString(DCM_PhotometricInterpretation, "RGB");
// 	newDataset->putAndInsertUint16(DCM_Rows, m_lpBMIH->biHeight);
// 	newDataset->putAndInsertUint16(DCM_Columns, m_lpBMIH->biWidth);
// 	newDataset->putAndInsertUint16(DCM_BitsStored, 8);
// 	newDataset->putAndInsertUint16(DCM_BitsAllocated, 8);
// 	newDataset->putAndInsertUint16(DCM_SamplesPerPixel, 3);
// 	newDataset->putAndInsertUint16(DCM_HighBit, 7);
// 	newDataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
// 	newDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);
// 
// 
// 	DcmElement* element = NULL;
// 	pDataset->findAndGetElement(DCM_PixelData, element);
// 	unsigned char* pImage = NULL;
// 	element->getUint8Array(pImage);
// 	Uint32 length = element->getLength();
// 	length = m_lpBMIH->biWidth * m_lpBMIH->biHeight * 3; //same
// 
// 
// 
// 	newDataset->putAndInsertUint8Array(DCM_PixelData,pImage, length);
// 	*/
// 	//gray is ok 
// 	/*
// 	newDataset->putAndInsertString(DCM_PhotometricInterpretation, "Monochrome2");
// 	newDataset->putAndInsertUint16(DCM_Rows, m_lpBMIH->biHeight);
// 	newDataset->putAndInsertUint16(DCM_Columns, m_lpBMIH->biWidth);
// 	newDataset->putAndInsertUint16(DCM_BitsStored, 8);
// 	newDataset->putAndInsertUint16(DCM_BitsAllocated, 8);
// 	newDataset->putAndInsertUint16(DCM_SamplesPerPixel, 1);
// 	newDataset->putAndInsertUint16(DCM_HighBit, 7);
// 	newDataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
// 	newDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);
// 
// 
// 	DcmElement* element = NULL;
// 	pDataset->findAndGetElement(DCM_PixelData, element);
// 	unsigned char* pImage = NULL;
// 	element->getUint8Array(pImage);
// 	Uint32 length = element->getLength();
// 	length = m_lpBMIH->biWidth * m_lpBMIH->biHeight ; //same
// 	newDataset->putAndInsertUint8Array(DCM_PixelData, pImage, length);
// 	*/
// 
// 	//capture dc is not ok
// // 
// // 	newDataset->putAndInsertString(DCM_PhotometricInterpretation, _T("RGB"));
// // 	newDataset->putAndInsertUint16(DCM_Rows, m_rect.Height());
// // 	newDataset->putAndInsertUint16(DCM_Columns, m_rect.Width());
// // 	newDataset->putAndInsertUint16(DCM_BitsStored, 8);
// // 	newDataset->putAndInsertUint16(DCM_BitsAllocated, 8);
// // 	newDataset->putAndInsertUint16(DCM_SamplesPerPixel, 3);
// // 	newDataset->putAndInsertUint16(DCM_HighBit, 7);
// // 	newDataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
// // 	newDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);
// 
// 	newDataset->putAndInsertString(DCM_PhotometricInterpretation, "Monochrome2");
// 	newDataset->putAndInsertUint16(DCM_Rows, rect.Height());
// 	newDataset->putAndInsertUint16(DCM_Columns, rect.Width());
// 	newDataset->putAndInsertUint16(DCM_BitsStored, 8);
// 	newDataset->putAndInsertUint16(DCM_BitsAllocated, 8);
// 	newDataset->putAndInsertUint16(DCM_SamplesPerPixel, 1);
// 	newDataset->putAndInsertUint16(DCM_HighBit, 7);
// 	newDataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
// 	newDataset->putAndInsertUint16(DCM_PlanarConfiguration, 0);
// 
// // 	DcmElement* element = NULL;
// // 	m_pDataset->findAndGetElement(DCM_PixelData, element);
// // 	unsigned char* pImage = NULL;
// // 	element->getUint8Array(pImage);
// // 	Uint32 length = element->getLength();
// // 	length = m_lpBMIH->biWidth * m_lpBMIH->biHeight ; //same
// // 	newDataset->putAndInsertUint8Array(DCM_PixelData, pImage, length);
// 
//  	int dc_size = 0;	//彩色RGB
//  	BYTE* newbmpdata = CaptureScreen(pDC,rect,&dc_size); 
//  	newDataset->putAndInsertUint8Array(DCM_PixelData, (unsigned char*)newbmpdata, dc_size);
//  	delete newbmpdata;
// 
// 	extern CMUTWndAppApp theApp;
// 	CString strFilePath;
// 	strFilePath.Format(_T("%s"),theApp.GetExeDirtory());
// 	if (m_needcreatenewdcmdirectory)
// 	{
// 		m_newdcmdirectory = datetime.Format(_T("%Y%m%d_%H%M%S"));//fixme,replace it use patient id.
// 		CString directory = strFilePath + _T("\\") + m_newdcmdirectory;
// 
// 		if (!CreateDirectory(directory, NULL))
// 		{
// 			if (GetLastError() == ERROR_ALREADY_EXISTS)
// 			{
// 
// 			}	
// 			m_needcreatenewdcmdirectory = false;
// 		}
// 		strFilePath += _T("\\") + m_newdcmdirectory;
// 		CString filename = strFilePath +  _T("\\") + datetime.Format(_T("%Y%m%d_%H%M%S")) + _T(".dcm");
// 
// 		char *savedfilepath = encode(filename.GetBuffer(),CP_OEMCP);
// 		filename.ReleaseBuffer();
// 		OFCondition status = newfileFormat.saveFile(savedfilepath, EXS_LittleEndianImplicit);
// 	}
//  
//  }

BOOL CMUTScanbSaveOWnd::DestroyWindow()
{
// 	if(m_pDicomFile)
// 	{
// 		delete m_pDicomFile;
// 	}

	if(m_lpBMIH)
	{
		delete m_lpBMIH;
	}

	if(pDicomDibits)
	{
		delete pDicomDibits;
	}
// 	if(m_pDataset)
// 	{
// 		delete m_pDataset;
// 	}
	return TRUE;
}