#include "StdAfx.h"
#include "MUTMeasureFunc.h"
#include "MArrow.h"

CMUTMeasureFunc::CMUTMeasureFunc()
://m_iFunClickCnt(0)
m_MenuStr(0)
,m_iRunIndex(0)
,m_pCurTemp(NULL)
,m_IsCurTempEnd(FALSE)
{
	/*m_pMainWnd = (CMainWindow*)userdata;*/
	//m_pCurTemp = new CMeasureObject(m_Compute);
}

CMUTMeasureFunc::~CMUTMeasureFunc(void)
{
	if(m_StrText)
		m_StrText.Empty();
	if(m_pCurTemp)
	{
		delete m_pCurTemp;
		m_pCurTemp = NULL;
	}
	INT len = m_pMeaObj.size();
	for(unsigned int i=0;i<len;i++)
	{
		CMeasureObject *pObj = m_pMeaObj.at(i);
		delete pObj;
	}
	m_pMeaObj.clear();
	//m_iSubIndex.clear();
}
CMeasureObject *CMUTMeasureFunc::GetMeaObjSpointer(UINT index)
{
	if(index == 0) return NULL;

	switch(index)
	{
		case mea_length_index:										//长度
			return new CMDistance(m_Compute);		
			break;
		case mea_area_index:										//面积
			return new CMElArea(m_Compute,fun_area_index);		
			break;
		case mea_arrow_index:										//箭头
			return new CMArrow(m_Compute);		
			break;		
		case mea_angle_index:										//角度
			return new CMAngle(m_Compute);
			break;
		case mea_circum_index:										//周长
			return new CMElArea(m_Compute,fun_circum_index);	
			break;
		case mea_text_index:										//文字     
			return new CMText(m_Compute);
			break;
	// 	case 7:										//体积（长宽高）
	// 		return new CMVolumeTD(m_Compute);
	// 		break;
	// 	case 8:										//体积（椭圆）
	// 		return new CMVolumeEl(m_Compute);
	// 		break;
	// 	case 9:										//体积（描底+高）
	// 		return new CMVolumeTr(m_Compute);
	// 		break;
	// 	case 10:									//角度
	// 		return new CMAngle(m_Compute);
	// 		break;
	// 	case 11:									//wu
	// 		return new CMTrArea(m_Compute);
	// 		break;
	// 	case 12:									//断面图
	// 		return new CMTrArea(m_Compute);
	// 		break;	
	// 	case 13:									//髋关节角度
	// 		return new CMTwoAngle(m_Compute);
	// 		break;
	// 	case 14:									//PW心率测量
	// 		return new CMPWHeartRatio(m_Compute);
	// 		break;
		default:
			return new CMeasureObject(m_Compute);
			break;
	}

}
// BOOL CMeasureFunction::IsMeaText()
// {
// 	return m_iRunIndex == mea_text_index;
// }
BOOL CMUTMeasureFunc::DeleteLastResult()
{
	m_cs.Lock();

	if(m_pCurTemp)  
	{
		delete m_pCurTemp;
		m_pCurTemp = NULL;
	}
	if(m_pMeaObj.empty())
	{
		m_cs.Unlock();
		return FALSE;
	}
	unsigned int lstcnt = m_pMeaObj.size();
	delete m_pMeaObj.at(lstcnt-1);
	m_pMeaObj.pop_back();
	m_MenuStr.pop_back();

	//m_iFunClickCnt -= 1;
	m_cs.Unlock();

	return TRUE;
}
BOOL CMUTMeasureFunc::DeleteAllResult()
{
	m_cs.Lock();

	if(!m_pMeaObj.empty())
	{
		for(unsigned int ix=0;ix < m_pMeaObj.size();ix ++)
		{
			delete m_pMeaObj.at(ix);
		}
		m_pMeaObj.clear();
	}
	if(!m_MenuStr.empty())
		m_MenuStr.clear();

	m_cs.Unlock();

	return TRUE;
}
BOOL CMUTMeasureFunc::ProMouse(MSG* pMsg)
{
	m_cs.Lock();
	if(NULL == m_pCurTemp)  
		return FALSE;

	m_pCurTemp->procMouse(pMsg);
// 	if(m_pCurTemp->HasEnded()&&!m_IsCurTempEnd) 		
// 	{
// 		MeasureEndProc();
// 		m_IsCurTempEnd = TRUE;
// 		//InvalidateRgn(pMsg->hwnd,)	
// 	}
	m_cs.Unlock();

	return TRUE;
}
void CMUTMeasureFunc::DrawObject(CDC *dc,int nIndex)
{
	m_cs.Lock();

	if(NULL == m_pCurTemp) 
	{
		m_cs.Unlock();
		return;
	}

	//m_pCurTemp->SetMDTextColor(APP_MEATEXT_COLOR);
	m_pCurTemp->DrawObject(dc,nIndex);
	if(m_pCurTemp->HasEnded()&&!m_IsCurTempEnd)
	{
		m_IsCurTempEnd = TRUE;
		if(!IsCurMeaText())
		{
			m_pCurTemp->DrawResult(dc);
		}
		else
		{
			m_pCurTemp->DrawResult(dc,m_StrText);
			//m_StrTextArray.Add(m_StrText);
		}
		MeasureEndProc();
	}

	m_cs.Unlock();
}
BOOL CMUTMeasureFunc::DrawObjectArray(CDC *dc)
{
	m_cs.Lock();

	if(m_pMeaObj.empty())
	{
		m_cs.Unlock();
		return FALSE;
	}
	for(int ix=0;ix<m_pMeaObj.size();ix++)
	{
		if(!m_pMeaObj.at(ix)->HasEnded()) 
		{
			//AfxMessageBox(_T("err!Measure is not done!"));
			continue;
		}
		m_pMeaObj.at(ix)->SetMDTextColor(APP_MEATEXT_COLOR);
		
		if(mea_text_index == m_MenuStr.at(ix).index)
		{
			m_pMeaObj.at(ix)->DrawResult(dc,m_MenuStr.at(ix).str);
		}
		else
		{
			m_pMeaObj.at(ix)->DrawObject(dc,0);
			m_pMeaObj.at(ix)->DrawResult(dc);
		}
	}

	m_cs.Unlock();

	return TRUE;
}
BOOL CMUTMeasureFunc::MeasureRstartProc()
{

	if(m_IsCurTempEnd)
	{
		MeasureStartProc(m_iRunIndex);

	}
	return TRUE;
}
BOOL CMUTMeasureFunc::MeasureStartProc(INT index)
{
	if(index <= 0 )  return FALSE;
	m_iRunIndex = index;
		
	if(m_pCurTemp)					//删除当前对象 清除图像上未完成部分？？
	{
		delete m_pCurTemp;
		m_pCurTemp = NULL;
	}
	if(IsMeaCntToMax(index)) 
		return FALSE;

	m_cs.Lock();
	m_IsCurTempEnd = FALSE;	
	m_pCurTemp = GetMeaObjSpointer(index);
	m_pCurTemp->SetMDTextColor(APP_MEATEXT_COLOR);
	m_pCurTemp->Restart();
	m_cs.Unlock();

	return TRUE;
}
BOOL CMUTMeasureFunc::MeasureEndProc()
{
	m_cs.Lock();

	if(!m_pCurTemp->HasEnded()) return FALSE;
				
	m_pMeaObj.push_back(m_pCurTemp->Clone());

	MEASURESTR menustr;
	menustr.index = m_iRunIndex;
	if(IsCurMeaText())
	menustr.str = m_StrText;
	else
	menustr.str = APP_NULL_STR;

	m_MenuStr.push_back(menustr);
	delete m_pCurTemp;
	m_pCurTemp = NULL;

	m_cs.Unlock();

	return TRUE;
}
UINT CMUTMeasureFunc::ReturnIndexMax(INT index)
{
	switch(index)
	{
		case mea_length_index:
			return DISTANCE_MAX_CNT;
			break;
		case mea_area_index:
			return AREA_MAX_CNT;
			break;
		case mea_arrow_index:
			return ARROW_MAX_CNT;
			break;
		case mea_angle_index:
			return ANGLE_MAX_CNT;
			break;
		case mea_circum_index:
			return CIRCUM_MAX_CNT;
			break;
		case mea_text_index:
			return TEXT_MAX_CNT;
			break;
		default:
			break;
	}
	return	0;			
}
BOOL CMUTMeasureFunc::IsMeaCntToMax(INT index)
{
	m_cs.Lock();	
	if(m_MenuStr.empty())
	{
		m_cs.Unlock();
		return FALSE;
	}

	for(int ix=0;ix<m_MenuStr.size();ix++)
	{
		INT curId = m_MenuStr.at(ix).index;
		static int cnt = 0;
		if(curId == index)
		{		
			UINT max = ReturnIndexMax(index);
			if(++cnt >= max)
			{
				cnt = 0;
				return TRUE;
			}
		}

	}
	
	m_cs.Unlock();

	return FALSE;
}
