#pragma once
#include "inc/UT-SDK.h"
#include "MUTMeDCFunc.h"
#include "MUTGlobal.h"
#include "MUTDibFunc.h"



#define IMG_DIS_WIDTH		256
#define IMG_DIS_HEIGHT		512

#define IMG_RULER_H			0 //纵向刻度尺
#define IMG_RULER_W			1 //横向刻度尺 

#define IMG_HRULER_RGN		40 //纵向刻度尺区域宽度
#define IMG_WRULER_RGN		10 //横向刻度尺区域高度 

class CMUTImgProcFunc
{
public:
	CMUTImgProcFunc(void);
	~CMUTImgProcFunc(void);
	static CMUTImgProcFunc* GetImgProc();
private:
	CMUTDibFunc m_dib;				//位图处理对像
	//CMUTDibFunc m_olddib;			//冻结前一帧
	//CMUTDibFunc m_movie[MOV_MAX_FRAME];		//影像数组

 	DOUBLE m_fps;
 	DWORD dwOldTime;

	int		m_nCurrentFrame;
	int		m_nStartFrame;
	bool	m_IsFullFrame;
	bool	m_IsPlayMovie;
	CRect	m_cRulerImg;
	CRect	m_cImage;

	HBITMAP	m_hBitmap;
	BOOL	m_bOpenDicom;	//是否打开DCM图像
	//CString m_newdcmdirectory;
	//bool m_needcreatenewdcmdirectory;		

public:
	void	ReverseMatrix(PBYTE pdata, int nwidth, int nheight);
	BOOL	GetUsbData(PWORD pData,int &iRows,int &iColums,unsigned long &dwFrame);	//获取底层数据
	void	CountFPS();																//帧频计算
	void	ProcessGetData(CMUTDibFunc &curdib,PBYTE pData,CRect dstRect);									//数据DSC转换
	void	OpenDcmImage(LPCTSTR lpszPathName);
	void	SaveBitmapToDirectFile(CDC* pDC, CRect BitmapSize, int BitCount, CString strFilePath);
	void	saveBmpFile(CDC *pDC,CRect rect,CString strFilePath);
	BOOL	SaveDcmImage(CDC *pDC,CRect rect,CString filename);
	BOOL	SaveSnapShotFile(CDC *pDC,CRect rect,CString filename);
	void	drawVideo(CDC *dc,CRect rect);
	void	DrawImage(CDC *dc,CRect rect,BOOL bFlipImage);
	void	DrawRuler(CDC *dc, CRect &rect,UINT uType);
	void	DrawAngle(CMUTMeDCFunc *dc,CRect rect,BOOL bIsFlipImage=FALSE);
	void	DeleteSpareImage(CDC * dc, CRect rect);
	BOOL    IsDcmOn(){return m_bOpenDicom;};
	void	SetDcmOn(BOOL bOn=TRUE){m_bOpenDicom = bOn;};
	DOUBLE	GetFpsValue(){return m_fps;};
	void	SetFPS(DOUBLE fps=0){m_fps = fps;};
	void	TransDib(CMUTDibFunc dib){m_dib = dib;};
	void	TransRect(CRect rct){m_cImage.CopyRect(rct);};
	//void	SetPlayMove(bool bIsPlayMovie){m_IsPlayMovie = bIsPlayMovie;};
};
