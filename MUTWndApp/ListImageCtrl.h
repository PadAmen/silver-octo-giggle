#pragma once
//Í·ÎÄ¼þListImageCtrl.h  
#include <vector>
//note:need GDI+
// ListImageCtrl.h : header file




class CListImageCtrl : public CListCtrl
{

	// Construction

public:

	CListImageCtrl();
// Attributes

public:

	void CreateColumn();
	//
	BOOL  GetImageFileNames();// gather the image file names
	void  DrawThumbnails();// draw the thumbnails in list control
	void  Load();         //start load files
	void Clear();   //clear list
// Operations

public:

	CString m_strImageDir;

	CImageList m_ImageListThumb;// image list holding the thumbnails

	std::vector<CString> m_VectorImageNames;// vector holding the image names

	int m_nSelectedItem;

	BOOL  m_bHorz;
// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CListImageCtrl)
//}}AFX_VIRTUAL

// Implementation

public:

	virtual ~CListImageCtrl();
// Generated message map functions
protected:
	//{{AFX_MSG(CListImageCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	CString GetItemFileName();
	void	DeletSelectedItem();
};
