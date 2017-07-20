#pragma once
#include "MUTGlobal.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmimgle/dcmimage.h"
/*#include "TDcmFileFormat.h"*/
#include "MUTDcmTag.h"

// CSaveWnd 对话框

class CMUTScanbSaveOWnd : public CDialog
{
	DECLARE_DYNAMIC(CMUTScanbSaveOWnd)

public:
	CMUTScanbSaveOWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMUTScanbSaveOWnd();

// 对话框数据
	enum { IDD = IDD_SAVE_WND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CBrush		m_brush;
	HWND		m_hParentWnd;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnLocal();
	virtual BOOL DestroyWindow( );
private:
	DcmFileFormat *m_pDicomFile;
	DicomImage *m_pDcm;
	DcmDataset *m_pDataset;
	void *pDicomDibits;
	int size;

	double m_curWC;
	double m_curWW;
	int m_destWidth;
	int m_destHeight;
// 	int m_destX;
// 	int m_destY;

	//CRect m_rect;

	LPBITMAPINFOHEADER m_lpBMIH;
	CString m_newdcmdirectory;
	bool m_needcreatenewdcmdirectory;
public:
	//void SetImageRct(CRect rct){m_rect = rct;};
	void GetParentHwnd(HWND hParentWnd){m_hParentWnd = hParentWnd;};
// 	void OpenDCMFile(LPCTSTR lpszPathName);
// 	BOOL DrawDcmFile(CDC *pDC,CRect rect);
// 	BYTE* CaptureScreen(CDC *pDC,CRect rect,int* size);
	void SaveDcmFile(CDC *pDC,CRect rect,COleDateTime datetime);

};
