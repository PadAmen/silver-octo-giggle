#pragma once
//头文件ListImageCtrl.h  
#include <vector>
//note:need GDI+
using namespace std;
// ListImageCtrl.h : header file
typedef struct tgItemFileNameInfo
{
	int nItem;
	CString filename;
}ITEMNAMEINFO,*PITEMNAMEINFO;

class CListImageCtrl_H : public CListCtrl
{

	// Construction

public:

	CListImageCtrl_H();
// Attributes

public:

	void CreateColumn();
	//
	BOOL  GetImageFileNames();// gather the image file names
	void  DrawThumbnails(int dcmcnt=0);// draw the thumbnails in list control
	void  Load(int dcmcnt);         //start load files
	void Clear();   //clear list
// Operations

public:

	CString m_strImageDir;

	CImageList m_ImageListThumb;// image list holding the thumbnails

	std::vector<CString> m_VectorImageNames;// vector holding the image names  
	std::vector<ITEMNAMEINFO> m_ItemNameInfo;// add 8.10 why not use m_VectorImageNames 
										    //because it will be update
	int m_nSelectedItem;

	BOOL  m_bHorz;
private:
	CString m_strCloum0;
	CString m_strCloum1;
	CString m_clickItem;
// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CListImageCtrl)
//}}AFX_VIRTUAL

// Implementation

public:

	virtual ~CListImageCtrl_H();
// Generated message map functions
protected:
	//{{AFX_MSG(CListImageCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	BOOL	m_IsLocalSave;		//是否本地保存
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString GetClickItemFileName();
	vector<CString> *  DeleteSelectItemAndFile(CString strDcmDir,CString strBmpDir,vector<int> arrayindex);
	vector<CString> *  GetSelectImageFileName(vector<int> arrayindex);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	void SetHeaderText(CString strCloum0=_T(""),CString strCloum1=_T(""));
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	void	DeletSelectedItem(){DeleteItem(m_nSelectedItem);};
};
