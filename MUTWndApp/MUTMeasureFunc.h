#pragma once
#include "MUTGlobal.h"
#include "MeasurePackage.h"
#include "MUTMeDCFunc.h"

#define DISTANCE_MAX_CNT	4
#define AREA_MAX_CNT		2
#define ARROW_MAX_CNT		6
#define ANGLE_MAX_CNT		3
#define CIRCUM_MAX_CNT		2
#define TEXT_MAX_CNT		6

typedef struct
{
	UINT index;
	CString str;
}MEASURESTR,*PMEASURESTR;

class CMUTMeasureFunc
{
public:
	CMUTMeasureFunc();
	~CMUTMeasureFunc(void);
	
public:
	//BOOL DrawMeasureMap(HDC hMemDC,CPoint ptStart,PMENUMSGINFO pMenuMsgInfo);
	//CPoint DrawResult(CDC *pDC,CMeasureObject *pTemp,int subIndex,int inObj,INT x,INT y,CSize ftSize);
	BOOL DeleteLastResult();
	BOOL DeleteAllResult();	
	CMeasureObject *GetMeaObjSpointer(UINT index = 1);
	virtual BOOL ProMouse(MSG* pMsg);
	virtual void DrawObject(CDC *dc,int nIndex = 0);
	virtual BOOL DrawObjectArray(CDC *dc);
	BOOL MeasureStartProc(INT index=0);
	BOOL MeasureEndProc();
private:
	CComputeMethod		m_Compute;
	CMeasureObject			*m_pCurTemp;
	vector<CMeasureObject*>	m_pMeaObj;
	//CStringArray			m_StrTextArray;
	vector<MEASURESTR>		m_MenuStr;		//菜单索引号 从上到下（1~n）
	INT					m_iRunIndex;
	//INT					m_iFunIndex;
	//UINT				m_iFunClickCnt;		//功能点击次数
	BOOL				m_IsCurTempEnd;
	CString				m_StrText;
public:
	CCriticalSection		m_cs;

	CMeasureObject * GetTempObj(){return m_pCurTemp;};
	BOOL	IsMeaArrayEmpty(){return m_pMeaObj.empty();};
	BOOL	MeasureRstartProc();
	BOOL	CurTempHasStarted(){if(NULL == m_pCurTemp) return FALSE;return m_pCurTemp->HasStarted();};
	BOOL	CurTempHasEnd(){return m_IsCurTempEnd;};
	BOOL	IsCurMeaText(){return m_iRunIndex == mea_text_index;};
	void	TransStrText(CString str){ m_StrText = str;};
	void	SetCurTempEnded(){m_pCurTemp->SetEnded();};
	UINT	ReturnIndexMax(INT index);
	BOOL	IsMeaCntToMax(INT index);
	

};
