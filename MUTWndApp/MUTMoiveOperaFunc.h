#pragma once
#include "MUTGlobal.h"
#include "MUTDibFunc.h"
#include <vector>
using namespace std;

class CMUTMoiveOperaFunc
{
public:
	CMUTMoiveOperaFunc(void);
	~CMUTMoiveOperaFunc(void);
private:
	CMUTDibFunc					m_Moive[MOIVE_MAX_FRAME];
	//vector<CMUTDibFunc>		m_Moive;
	//vector<int>				m_test;
	CCriticalSection		m_CritSection;
	volatile BOOL			m_bPlay;
	BOOL					m_bIsFullFrame;
	UINT					m_nCurrentFrame;
	UINT					m_nStartFrame;
	volatile UINT			m_nEndFrame;
public:
	void SetPlay(BOOL bPlay=TRUE);
	void Clear();
	BOOL IsPlay(){return m_bPlay;};
	void InsertFrame(CMUTDibFunc dib);
	void GetFrame(CMUTDibFunc &dib);
	void GetFrameFromIndex(CMUTDibFunc &dib,UINT index);
	UINT GetCurrentIndex(){return m_nCurrentFrame;};
	UINT GetEndIndex(){return m_nEndFrame;};
	UINT GetStartIndex(){return m_nStartFrame;};
};
