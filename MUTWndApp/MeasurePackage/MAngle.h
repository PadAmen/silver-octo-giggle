
/********************************************************************
created:	2010/07/16
created:	4:3:2010   10:38
filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MAngle.h
file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
file base:	MAngle
file ext:	h
author:		li

purpose:	������ֱ��֮��ļн�
*********************************************************************/

#pragma once

#include "MeasureObject.h"
#include "MDistance.h"

/*
*	����ֱ�߽Ƕ�,
*/


class MEASUREPACKAGE_API CMAngle : public CMeasureObject 
{
public:
	CMAngle(const CComputeMethod &computer);
	virtual ~CMAngle();
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual	void DrawResult(CDC *dc);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void Restart();
public:
	COLORREF	m_TextColor;
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
	float GetAngle();			//�õ��Ƕ�(�ǻ���,0~180)
	//�õ�ֱ�ߺ͵�ı仯�� ���ڿ���Բ���ĽǶȷ�Χ
	void GetLineAndPointRatio(CPoint m_pointBtwStartToMid,CPoint &c_p,CPoint m_pointMiddle,//m_pointBtwStartToMid����ʼ�������ֱ���Ͻؾ�ΪfDisBtwLine�ĵ�,m_pointMiddle���ѹ�µĵڶ�����
							  float fDisStarToMid,float fDisBtwLine,int ddx_MidToStart,// fDisStarToMid�ڵ�һ��ֱ�ߵĽؾ�,fDisBtwLine�ڵڶ���ֱ���ϵĽؾ�,ddx_MidToStart,ddy_MidToStart��һ��ֱ�ߵ�x,y�ı仯��
							  int ddy_MidToStart,CPoint m_pointVec);	//m_pointVec�����һ��ֱ�ߴ�ֱ�Ĵ����ϵĵ�
	//��ȡԲ���Ļ���
	void GetDrawCircle(int ddx_MidToStart,int ddy_MidToStart,
					   int ddx_MidToEnd,int ddy_MidToEnd,
					   float cos_an,int &draw_flag);
	//���Ƕ�
	void DrawAngle(CDC *dc,int nIndex,CPoint &m_pointStart,CPoint &m_pointMiddle,
				   CPoint &m_pointEnd,float fDisBtwLine,float &m_angle);
protected:
	CPoint m_pointStart;
	CPoint m_pointMiddle;
	CPoint m_pointEnd;
	CPoint m_pointLast;			
	float m_angle;

};
