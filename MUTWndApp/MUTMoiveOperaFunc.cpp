#include "StdAfx.h"
#include "MUTMoiveOperaFunc.h"

CMUTMoiveOperaFunc::CMUTMoiveOperaFunc(void)
:m_bPlay(FALSE)
,m_bIsFullFrame(FALSE)
,m_nCurrentFrame(0)
,m_nStartFrame(0)
{
}

CMUTMoiveOperaFunc::~CMUTMoiveOperaFunc(void)
{
}
void CMUTMoiveOperaFunc::InsertFrame(CMUTDibFunc dib)		//Insert与Get在同一时刻不会出现不用加锁
{
	if(dib.IsEmpty())	return;
//	vector<CMUTDibFunc>:: iterator itor;
//	itor = m_Moive.begin();
//	m_Moive.push_back(dib);
// 	if(m_Moive.size() >= MOIVE_MAX_FRAME-1)
// 	{
// 		m_bIsFullFrame = TRUE;
// 		vector<CMUTDibFunc>:: iterator itor;
// 		itor = m_Moive.begin();
// 		m_Moive.erase(itor);	
// 	}
	m_Moive[m_nCurrentFrame] = dib;
	if (m_nCurrentFrame == MOIVE_MAX_FRAME-1) 
	{
		m_bIsFullFrame = true;
	}
	m_nCurrentFrame = (m_nCurrentFrame + 1) % MOIVE_MAX_FRAME;

	if (m_bIsFullFrame) 
	{
		m_nStartFrame = m_nCurrentFrame;
	}
	else
	{
		m_nEndFrame = m_nCurrentFrame;
// 		else
// 		m_nEndFrame = MOIVE_MAX_FRAME-1;
	}
	
}

void CMUTMoiveOperaFunc::GetFrame(CMUTDibFunc &dib)
{
// 	if(m_Moive.empty()) return;
// 
// 	dib = m_Moive.at(m_nCurrentFrame);
// 
// 	m_nCurrentFrame = (m_nCurrentFrame + 1) % (m_Moive.size()+1);
	dib = m_Moive[m_nStartFrame];

	if(m_bIsFullFrame)
	m_nStartFrame = (m_nStartFrame + 1) % MOIVE_MAX_FRAME;
	else
	m_nStartFrame = (m_nStartFrame + 1) % m_nEndFrame; 

}
void CMUTMoiveOperaFunc::GetFrameFromIndex(CMUTDibFunc &dib,UINT index)
{
	if(index < 0 || index >= MOIVE_MAX_FRAME)
		return;

	dib = m_Moive[index];
}
void CMUTMoiveOperaFunc::SetPlay(BOOL bPlay)
{
	m_bPlay = bPlay;
	m_nStartFrame = 0;
	//m_nEndFrame = 0;
	m_nCurrentFrame = 0;
	//m_bIsFullFrame = FALSE;
}

void CMUTMoiveOperaFunc::Clear()
{
	m_nEndFrame = 0;
	m_bIsFullFrame = FALSE;
}