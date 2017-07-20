/********************************************************************
	created:	2010/03/11
	created:	11:3:2010   15:00
	filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MVxArea.h
	file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
	file base:	MVxArea
	file ext:	h
	author:		jiang
	
	purpose:	面积测量功能,连续确定一起点位置,将这些点用直线连起来,求它的面积和周长
*********************************************************************/

// MVxArea.h: interface for the CMVxArea class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


#include "MeasureObject.h"

/************************************************************************/
/* 连接线面积                                                                     */
/************************************************************************/
class MEASUREPACKAGE_API CMVxArea : public CMeasureObject  
{
public:
	CMVxArea(const CComputeMethod &computer);
	virtual ~CMVxArea();
private:
	CPtrArray	m_pointArray;//已确定的点
	CPoint m_pointMove;//当前鼠标位置
	float  m_PInPix;//周长
	float  m_AInPix;//面积
protected:
	float AreaCalculate(CPtrArray &arrPoint);//计算坐标点包围起来的区域的面积
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual CMeasureObject *Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);;
	virtual int   GetResultCount();//最终测量结果值的个数
};

