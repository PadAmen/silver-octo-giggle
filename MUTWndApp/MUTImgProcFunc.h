#pragma once
#include "inc/UT-SDK.h"
#include "MUTMeDCFunc.h"
#include "MUTGlobal.h"
#include "MUTDibFunc.h"



#define IMG_DIS_WIDTH		256
#define IMG_DIS_HEIGHT		512

#define IMG_RULER_H			0 //����̶ȳ�
#define IMG_RULER_W			1 //����̶ȳ� 

#define IMG_HRULER_RGN		40 //����̶ȳ�������
#define IMG_WRULER_RGN		10 //����̶ȳ�����߶� 

class CMUTImgProcFunc
{
public:
	CMUTImgProcFunc(void);
	~CMUTImgProcFunc(void);
	static CMUTImgProcFunc* GetImgProc();
private:
	CMUTDibFunc m_dib;				//λͼ�������
	//CMUTDibFunc m_olddib;			//����ǰһ֡
	//CMUTDibFunc m_movie[MOV_MAX_FRAME];		//Ӱ������

 	DOUBLE m_fps;
 	DWORD dwOldTime;

	int		m_nCurrentFrame;
	int		m_nStartFrame;
	bool	m_IsFullFrame;
	bool	m_IsPlayMovie;
	CRect	m_cRulerImg;
	CRect	m_cImage;

	HBITMAP	m_hBitmap;
	BOOL	m_bOpenDicom;	//�Ƿ��DCMͼ��
	//CString m_newdcmdirectory;
	//bool m_needcreatenewdcmdirectory;		

public:
	void	ReverseMatrix(PBYTE pdata, int nwidth, int nheight);
	BOOL	GetUsbData(PWORD pData,int &iRows,int &iColums,unsigned long &dwFrame);	//��ȡ�ײ�����
	void	CountFPS();																//֡Ƶ����
	void	ProcessGetData(CMUTDibFunc &curdib,PBYTE pData,CRect dstRect);									//����DSCת��
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
