// MVxLength.cpp: implementation of the CMVxLength class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MVxLength.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMVxLength::CMVxLength(const CComputeMethod &computer):CMeasureObject(computer)
{
	m_nStep=0;
}

CMVxLength::~CMVxLength()
{
	
}
/*void CMVxLength::DeepCopy(CMVxLength &rt)
{
	rt.m_nStep = this->m_nStep;
	m_pointMove = this->m_pointMove;
	for(UINT i=0;i<m_pointArray.GetSize();i++)
		rt.m_pointArray.GetAt(i) = this->m_pointArray.GetAt(i);

}*/
BOOL CMVxLength::OnLButtonDown(UINT nFlags, CPoint point)
{	
	if(m_nStep == 0)
	{
		m_nStep = 1;
		m_pointArray.Add(point);
		return TRUE;
	}
	else if(m_nStep == 1)
	{//���ͬһ�����2��,��������
		CPoint pointlast = (m_pointArray.GetAt(m_pointArray.GetSize()-1));//���һ��
		float dis = this->m_computer.GetDistanceInPixes(point, pointlast);
		if(dis < 10.0f)	
		{
			m_nStep = 2;
		}
		else
		{			
			m_pointArray.Add(point);
		}	
		return TRUE;
	}
	return FALSE;
}
BOOL CMVxLength::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_nStep < 2)
	{
		m_pointMove = point;
		return TRUE;
	}
	return FALSE;
}

void CMVxLength::DrawObject(CDC *dc,int nIndex)
{
	if(m_nStep<1) return;
	CPoint ptStart = m_pointArray.GetAt(0);
	DrawNumber(dc, nIndex, ptStart);

	CPen pen(PS_SOLID,1, 0xffffff), *oldpen;
	oldpen = dc->SelectObject(&pen);
	for(int i=0; i<m_pointArray.GetSize(); i++)
	{
		//��ԲȦ��ʹ�ÿջ�ˢ
		HBRUSH nullBr = (HBRUSH)::GetStockObject(NULL_BRUSH);
		void *oldbr = dc->SelectObject(nullBr);
	
		CPoint ptTemp = m_pointArray.GetAt(i);
		//�ڽڵ��ϻ�һ��СԲȦ
		dc->Ellipse(ptTemp.x-4, ptTemp.y-4, ptTemp.x+4, ptTemp.y+4);
		if(i)
		{
			dc->LineTo(ptTemp);			
		}
		else 
		{
			dc->MoveTo(ptTemp);
		}

	}
	//���һ��������ͷ��ľ���
	CPoint ptlast = m_pointArray.GetAt(m_pointArray.GetSize()-1);
	float fdis_LastPoint_mouse =  this->m_computer.GetDistanceInPixes(ptlast, m_pointMove);
	//����һ���б�־
	if(!HasEnded())
	{
		dc->MoveTo(ptlast.x - 10, ptlast.y);
		dc->LineTo(ptlast.x + 10, ptlast.y);
		dc->MoveTo(ptlast.x, ptlast.y - 10);
		dc->LineTo(ptlast.x, ptlast.y + 10);
		dc->Ellipse(ptlast.x - 8, ptlast.y-8, ptlast.x+8, ptlast.y+8);
	}
	//�������һ��������λ�õ�֮�����
	if(m_nStep==1 && fdis_LastPoint_mouse >= 10.0)	
	{
		dc->MoveTo(ptlast);
		dc->LineTo(m_pointMove);
	}
	dc->SelectObject(oldpen);
}
CMeasureObject* CMVxLength::Clone()
{
	CMVxLength *pMVxlen = new CMVxLength(m_computer);
	pMVxlen->m_nStep = this->m_nStep;
	pMVxlen->m_pointMove = this->m_pointMove;
	pMVxlen->m_pointArray.Copy(this->m_pointArray);

	return pMVxlen;
}
bool CMVxLength::HasEnded()
{
	return m_nStep>1;
}
void CMVxLength::DrawResult(CDC *dc,int &x,int &y)
{
	const CSize szLine = dc->GetTextExtent(_T("Test"));
	CString strResult;
	//�ı�����
	strResult.Format(_T("L: %8.2f cm"), m_computer.GetCanveDistance(m_pointArray, false));

	//�����ı�
	dc->TextOut(x, y, strResult);
	y += szLine.cy;

}

void CMVxLength::Restart()
{
	m_pointArray.RemoveAll();
	m_pointMove.SetPoint(0,0);
	m_nStep = 0;
}