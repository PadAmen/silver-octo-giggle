// MeasureObject.cpp: implementation of the CMeasureObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MeasureObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeasureObject::CMeasureObject(const CComputeMethod &computerobj):m_computer(computerobj)
{

}

CMeasureObject::~CMeasureObject()
{

}
CMeasureObject * CMeasureObject::Clone()
{
	return NULL;
}
void CMeasureObject::DrawObject(CDC *dc,int nIndex)
{
	return;
}
bool CMeasureObject::HasEnded()
{
	return TRUE;
}
BOOL CMeasureObject::OnLButtonDown(UINT nFlags, CPoint point)
{
	return TRUE;
}
void CMeasureObject::DrawResult(CDC *dc,int &x,int &y)
{
	return;
}
BOOL CMeasureObject::OnMouseMove(UINT nFlags, CPoint point)
{
	return TRUE;
}
void CMeasureObject::DrawNumber(CDC *dc,const int nIndex,const CPoint &point)
{
	if(!dc)			return;
	if(nIndex < 0 ) return;

	CString str;					//ÄÚÈÝ
	str.Format(_T("[%d]"),nIndex);	
	dc->SetBkMode(TRANSPARENT);	
	dc->TextOut(point.x+5,point.y+5,str);//Î»ÖÃ	

}
void CMeasureObject::DrawResultText(CDC *dc,CString strResult,CPoint &point)
{
	if(!dc)		return;
	//CString str;
	//str.Format(_T("%8.2f mm"),result*10);
	dc->SetBkMode(TRANSPARENT);
	dc->TextOut(point.x+2,point.y+2,strResult);//Î»ÖÃ
}
void CMeasureObject::DrawCrossFlag(CDC *dc, int x, int y)
{
	dc->MoveTo(x-4,y);
	dc->LineTo(x+5,y);
	dc->MoveTo(x,  y-4);
	dc->LineTo(x,  y+5);
}

bool CMeasureObject::HasStarted()
{
	return m_nStep>0;
}

void CMeasureObject::Restart()
{
	m_nStep = 0;
}

BOOL CMeasureObject::procMouse(const MSG * pMsg)
{
	if(pMsg->message==WM_LBUTTONDOWN)
	{
		return this->OnLButtonDown(0, pMsg->pt);
	}
	if(pMsg->message==WM_MOUSEMOVE)
	{
		return this->OnMouseMove(0, pMsg->pt);
	}
	return FALSE;
}


int CMeasureObject::GetResultCount()
{
	return 1;
}

bool CMeasureObject::GetResultArray(vector<double> &lstResult)const
{
	return false;
}

