#include "stdafx.h"
#include "ListImageCtrl.h"
#include "MUTGlobal.h"

#define THUMBNAIL_WIDTH  80
#define THUMBNAIL_HEIGHT 60
#define IDS_TITLE _T("title")
#define IDS_DIR_ERROR _T("dir error")
void DoEvents(void);
/////////////////////////////////////////////////////////////////////////////

// CListImageCtrl
CListImageCtrl::CListImageCtrl()
{
	m_strImageDir = _T("");
	m_bHorz = FALSE;
}

CListImageCtrl::~CListImageCtrl()
{

}

BEGIN_MESSAGE_MAP(CListImageCtrl, CListCtrl)

	//{{AFX_MSG_MAP(CListImageCtrl)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	ON_WM_NCCALCSIZE()
	ON_NOTIFY_REFLECT(NM_CLICK, &CListImageCtrl::OnNMClick)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////

// CListImageCtrl message handlers
// This funtion is used to load the Window dropped files into the listview

void CListImageCtrl::OnDropFiles(HDROP hDropInfo)
{

	WORD wNumFilesDropped = DragQueryFile(hDropInfo, -1, NULL, 0);
	CString firstFile(_T(""));

	int kk = 0;
	int tTot = (int)wNumFilesDropped;
	// show hour glass cursor

	BeginWaitCursor();
	for (WORD x = 0; x < wNumFilesDropped; x++)

	{
		kk++;

		// Get the number of bytes required by the file's full pathname

		WORD wPathnameSize = DragQueryFile(hDropInfo, x, NULL, 0);

		TRACE1("wPathnameSize=%d,\n", wPathnameSize);

		// Allocate memory to contain full pathname & zero byte

		wPathnameSize += 1;

		TCHAR * npszFile = (TCHAR *)LocalAlloc(LPTR, sizeof(TCHAR)*wPathnameSize);  //ע�������ڴ��С
																		// If not enough memory, skip this one
		if (npszFile == NULL) continue;
		DragQueryFile(hDropInfo, x, npszFile, wPathnameSize);
		if (firstFile == "")

			firstFile = npszFile;

		CString strExt;
		CString nFileText;
		CString pItemText = npszFile;

		TRACE1("%s\n", pItemText);

		int i = pItemText.ReverseFind('\\');

		nFileText = pItemText.Mid(i + 1);

		m_strImageDir = pItemText.Left(i + 1);

		strExt = pItemText.Right(3);

		TRACE1("strExt=%s\n", strExt);

		if ((strExt.CompareNoCase(TEXT("bmp")) == 0) ||
			(strExt.CompareNoCase(TEXT("jpg")) == 0) ||
			(strExt.CompareNoCase(TEXT("gif")) == 0) ||
			(strExt.CompareNoCase(TEXT("tif")) == 0) ||
			(strExt.CompareNoCase(TEXT("png")) == 0))

		{
			// save the image file name, not the path
			m_VectorImageNames.push_back(nFileText);
		}

		// clean up
		LocalFree(npszFile);

	}

	// Free the memory block containing the dropped-file information

	DragFinish(hDropInfo);

	if (!m_VectorImageNames.empty())

		DrawThumbnails();

	SetFocus();

	SetItemState(0, LVIS_SELECTED | LVS_ICON | LVS_AUTOARRANGE, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);

	EndWaitCursor();
	CListCtrl::OnDropFiles(hDropInfo);

}
void CListImageCtrl::CreateColumn()

{

	InsertColumn(0, _T("Filename"), LVCFMT_LEFT, 125, -1);

	InsertColumn(1, _T("Path"), LVCFMT_LEFT, 125, -1);

	InsertColumn(2, _T("Size"), LVCFMT_LEFT, 75, -1);


	HIMAGELIST hScreens = ImageList_Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR32 /*| ILC_MASK*/, 0, 1);

	m_ImageListThumb.Attach(hScreens);

	m_nSelectedItem = 0;

	// load the starting bitmap ("Loading..." and "Corrupt file")

	//  CBitmap dummy;

	//  dummy.LoadBitmap(IDB_BITMAP1);

	//  m_ImageListThumb.Add(&dummy, RGB(0, 0, 0));


	SetImageList(&m_ImageListThumb, LVSIL_NORMAL);

	SetImageList(&m_ImageListThumb, LVSIL_SMALL);


}

// this function is used to enable the system messages

// this is mainly used to display the multiple images dropped on the list control




void DoEvents(void)

{

	MSG Symsg;



	while (PeekMessage(&Symsg, NULL, 0, 0, PM_REMOVE))

	{

		TranslateMessage(&Symsg);

		DispatchMessage(&Symsg);

	}

}


void	CListImageCtrl::DeletSelectedItem()
{
	m_VectorImageNames.erase(m_VectorImageNames.begin()+m_nSelectedItem);
	DeleteItem(m_nSelectedItem);
};
CString CListImageCtrl::GetItemFileName()
{
	if(m_VectorImageNames.empty()) 
		return _T("");

	//std::vector<CString>::iterator  iter;
	for (uint i=0; i < m_VectorImageNames.size(); i++)
	{
		CString temp = m_VectorImageNames.at(i);
		if(i == m_nSelectedItem)
		{
			return temp;
		}
	}

	return _T("");
}
BOOL  CListImageCtrl::GetImageFileNames()

{

	CString strExt;
	CString strName;
	CString strPattern;
	BOOL bRC = TRUE;




	HANDLE hFind = NULL;

	WIN32_FIND_DATA FindFileData;

	std::vector<CString>VectorImageNames;
	if (m_strImageDir[m_strImageDir.GetLength() - 1] == TCHAR('\\'))

		strPattern.Format(TEXT("%s*.*"), m_strImageDir);

	else

		strPattern.Format(TEXT("%s\\*.*"), m_strImageDir);


	hFind = ::FindFirstFile(strPattern, &FindFileData);// strat search

	if (hFind == INVALID_HANDLE_VALUE)

	{

		LPVOID  msg;

		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,

			NULL,

			GetLastError(),

			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),

			(LPTSTR)&msg,

			0,

			NULL);

		MessageBox((LPTSTR)msg, CString((LPCSTR)IDS_TITLE), MB_OK | MB_ICONSTOP);

		::LocalFree(msg);

		return FALSE;

	}




	// filter off the system files and directories

	if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&

		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&

		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&

		!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))

	{

		// test file extension

		strName = FindFileData.cFileName;

		strExt = strName.Right(3);




		if ((strExt.CompareNoCase(TEXT("bmp")) == 0) ||

			(strExt.CompareNoCase(TEXT("jpg")) == 0) ||

			(strExt.CompareNoCase(TEXT("gif")) == 0) ||

			(strExt.CompareNoCase(TEXT("tif")) == 0) ||

			(strExt.CompareNoCase(TEXT("png")) == 0))

		{

			// save the image file name

			VectorImageNames.push_back(strName);

		}

	}




	// loop through to add all of them to our vector

	while (bRC)

	{

		bRC = ::FindNextFile(hFind, &FindFileData);

		if (bRC)

		{

			// filter off the system files and directories

			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&

				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&

				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) &&

				!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))

			{

				// test file extension

				strName = FindFileData.cFileName;

				strExt = strName.Right(3);




				if ((strExt.CompareNoCase(TEXT("bmp")) == 0) ||

					(strExt.CompareNoCase(TEXT("jpg")) == 0) ||

					(strExt.CompareNoCase(TEXT("gif")) == 0) ||

					(strExt.CompareNoCase(TEXT("tif")) == 0) ||

					(strExt.CompareNoCase(TEXT("png")) == 0))

				{

					// save the image file name

					VectorImageNames.push_back(strName);

				}

			}

		}

		else

		{

			DWORD err = ::GetLastError();

			if (err != ERROR_NO_MORE_FILES)

			{

				LPVOID msg;

				::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,

					NULL, err,

					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),

					(LPTSTR)&msg, 0, NULL);

				MessageBox((LPTSTR)msg, CString((LPCSTR)IDS_TITLE), MB_OK | MB_ICONSTOP);

				::LocalFree(msg);

				::FindClose(hFind);

				return FALSE;

			}

		}

	} // end of while loop




	  // close the search handle

	::FindClose(hFind);




	// update the names, if any

	if (!VectorImageNames.empty())

	{

		// reset the image name vector

		m_VectorImageNames.clear();

		m_VectorImageNames = VectorImageNames;

		return TRUE;

	}




	return FALSE;

}




void  CListImageCtrl::DrawThumbnails()

{

	CString strPath;

	int i;




	// no images

	if (m_VectorImageNames.empty())

		return;




	// set the length of the space between thumbnails

	// you can also calculate and set it based on the length of your list control

	int nGap = 30;




	// hold the window update to avoid flicking

	SetRedraw(FALSE);




	// reset our image list

	for (i = 0; i < m_ImageListThumb.GetImageCount(); i++)

		m_ImageListThumb.Remove(i);




	// remove all items from list view

	if (this->GetItemCount() != 0)

		this->DeleteAllItems();




	// set the size of the image list

	m_ImageListThumb.SetImageCount(m_VectorImageNames.size());

	i = 0;




	// draw the thumbnails

	std::vector<CString>::iterator  iter;

	for (iter = m_VectorImageNames.begin(); iter != m_VectorImageNames.end(); iter++)

	{

		HBITMAP hbmReturn = NULL;

		Bitmap  *bmPhoto = NULL;

		CBitmap Bmp1;




		// load the bitmap

		strPath.Format(TEXT("%s\\%s"), m_strImageDir, *iter);




		Bitmap img(strPath.AllocSysString());




		int sourceWidth = img.GetWidth();

		int sourceHeight = img.GetHeight();




		int destX, destY, destWidth, destHeight;

		const float fRatio = (float)THUMBNAIL_HEIGHT / THUMBNAIL_WIDTH;

		const float fImgRatio = (float)sourceHeight / sourceWidth;




		if (fImgRatio > fRatio)

		{

			destWidth = (THUMBNAIL_HEIGHT / fImgRatio);

			destX = (THUMBNAIL_WIDTH - destWidth) / 2;

			destY = 0;

			destHeight = THUMBNAIL_HEIGHT;

		}

		else

		{

			destX = 0;

			destWidth = THUMBNAIL_WIDTH;

			destHeight = (THUMBNAIL_WIDTH*fImgRatio);

			destY = (THUMBNAIL_HEIGHT - destHeight) / 2;

		}




		//check out very small image

		if ((sourceHeight < THUMBNAIL_HEIGHT) && (sourceWidth < THUMBNAIL_WIDTH))

		{

			destWidth = sourceWidth;

			destHeight = sourceHeight;

			destX = (THUMBNAIL_WIDTH - destWidth) / 2;

			destY = (THUMBNAIL_HEIGHT - destHeight) / 2;

		}



		bmPhoto = new Bitmap(THUMBNAIL_WIDTH, THUMBNAIL_WIDTH, PixelFormat32bppRGB);			//80,80����ͼ

		bmPhoto->SetResolution(img.GetHorizontalResolution(), img.GetVerticalResolution());




		//destX += 80;

		Graphics *grPhoto = Graphics::FromImage(bmPhoto);

		Color colorW(255, 255, 255, 255);

		Gdiplus::Pen pen(Color(200, 192, 192, 192));

		grPhoto->Clear(colorW);

		grPhoto->SetInterpolationMode(InterpolationModeHighQualityBilinear);

		grPhoto->DrawImage(&img, Rect(destX, destY, destWidth, destHeight));

		grPhoto->DrawRectangle(&pen, Gdiplus::Rect(0, 0, THUMBNAIL_WIDTH - 1, THUMBNAIL_HEIGHT - 1));  //draw border




		bmPhoto->GetHBITMAP(colorW, &hbmReturn);




		Bmp1.Attach(hbmReturn);

		m_ImageListThumb.Replace(i, &Bmp1, NULL);

		//int imgP=m_ImageListThumb.Add(&Bmp1,RGB(0,0,0));




		//InsertItem(i, m_VectorImageNames[i], i);  //Link to the added listview item 
		InsertItem(i,_T(""), i);//remove file name.



		delete grPhoto;

		delete bmPhoto;

		Bmp1.Detach();

		DeleteObject(hbmReturn);

		i++;




	}




	// let's show the new thumbnails

	SetRedraw();

}




void CListImageCtrl::Load()

{

	// TODO: Add your control notification handler code here

	UpdateData(TRUE);




	// validate image directory

	if (m_strImageDir.IsEmpty())

	{

		MessageBox(CString((LPCSTR)IDS_DIR_ERROR), CString((LPCSTR)IDS_TITLE), MB_OK | MB_ICONSTOP);

		return;

	}




	// show hour glass cursor

	BeginWaitCursor();




	// get the names of bitmap files

	if (m_VectorImageNames.empty())       //!GetImageFileNames() modify 8.10

	{

		EndWaitCursor();

		return;

	}




	// draw thumbnail images in list control

	DrawThumbnails();




	// draw the selected image in its full size

	//DrawSelectedImage();




	// if this was a shortcut, we need to expand it to the target path

	SetItemState(0, LVIS_SELECTED | LVS_ICON | LVS_AUTOARRANGE,LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);

	SetFocus();




	RedrawWindow(NULL, NULL);




	EndWaitCursor();




}




void CListImageCtrl::Clear()

{

	// hold the window update to avoid flicking

	SetRedraw(FALSE);




	// reset our image list

	for (int i = 0; i < m_ImageListThumb.GetImageCount(); i++)

		m_ImageListThumb.Remove(i);




	// remove all items from list view

	if (this->GetItemCount() != 0)

		this->DeleteAllItems();




	m_strImageDir = _T("");




	m_VectorImageNames.clear();




	SetRedraw();




}




void CListImageCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ModifyStyle(WS_HSCROLL , 0,0);
	CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CListImageCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// Get the current mouse location and convert it to client
	// coordinates.
	DWORD pos = GetMessagePos();
	CPoint pt(LOWORD(pos), HIWORD(pos));
	ScreenToClient(&pt);

	// Get indexes of the first and last visible items in listview
	// control.
	int index = GetTopIndex();
	int last_visible_index = index + GetCountPerPage();
	if (last_visible_index > GetItemCount())
		last_visible_index = GetItemCount();

	// Loop until number visible items has been reached.
	while (index <= last_visible_index)
	{
		// Get the bounding rectangle of an item. If the mouse
		// location is within the bounding rectangle of the item,
		// you know you have found the item that was being clicked.
		CRect r;
		GetItemRect(index, &r, LVIR_BOUNDS);
		if (r.PtInRect(pt))
		{
			UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
			SetItemState(index, flag, flag);
			this->GetParent()->ShowWindow(FALSE);
			this->GetParent()->GetParent()->SendMessage(WM_CHANGE_WND,(WPARAM)type_editimg_index,(LPARAM)this->GetParent());
			break;
		}

		// Get the next item in listview control.
		index++;
	}
	m_nSelectedItem = GetHotItem();								//add 8.11

	*pResult = 0;
}
