/********************************************************************
	created:	2010/03/11
	created:	11:3:2010   15:00
	filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MVxArea.h
	file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
	file base:	MVxArea
	file ext:	h
	author:		jiang
	
	purpose:	�����������,����ȷ��һ���λ��,����Щ����ֱ��������,������������ܳ�
*********************************************************************/

// MVxArea.h: interface for the CMVxArea class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


#include "MeasureObject.h"

/************************************************************************/
/* ���������                                                                     */
/************************************************************************/
class MEASUREPACKAGE_API CMVxArea : public CMeasureObject  
{
public:
	CMVxArea(const CComputeMethod &computer);
	virtual ~CMVxArea();
private:
	CPtrArray	m_pointArray;//��ȷ���ĵ�
	CPoint m_pointMove;//��ǰ���λ��
	float  m_PInPix;//�ܳ�
	float  m_AInPix;//���
protected:
	float AreaCalculate(CPtrArray &arrPoint);//����������Χ��������������
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual CMeasureObject *Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);;
	virtual int   GetResultCount();//���ղ������ֵ�ĸ���
};

