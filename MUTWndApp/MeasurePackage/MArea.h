/********************************************************************
	created:	2010/02/10
	created:	10:2:2010   14:43
	filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MArea.h
	file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
	file base:	MArea
	file ext:	h
	author:		姜
	
	purpose:	//画点线测量面积
*********************************************************************/


// MArea.h: interface for the CMArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAREA_H__AE7A77E1_0E00_492D_8617_09E40E9CB3AA__INCLUDED_)
#define AFX_MAREA_H__AE7A77E1_0E00_492D_8617_09E40E9CB3AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MeasureObject.h"


class MEASUREPACKAGE_API CMArea : public CMeasureObject  
{
public:
	CMArea(const CComputeMethod &computer);
	virtual ~CMArea();
private:
	CPtrArray m_ArrPoint;//点数组
	bool bDraw;//是否显示图像 
public :
	virtual void DrawObject(CDC *dc,int nIndex);

	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual CMeasureObject *Clone();
	virtual void DrawResult(CDC *dc,int x,int y);
	int  GetResultCount();//最终测量结果值的个数
};

#endif // !defined(AFX_MAREA_H__AE7A77E1_0E00_492D_8617_09E40E9CB3AA__INCLUDED_)
