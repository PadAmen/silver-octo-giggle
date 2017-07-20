// MTrArea.h: interface for the CMTrArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTRAREA_H__443FD9A7_4550_422D_9326_EC5559E7E058__INCLUDED_)
#define AFX_MTRAREA_H__443FD9A7_4550_422D_9326_EC5559E7E058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MeasureObject.h"
/************************************************************************/
/* 描线面积                                                    */
/************************************************************************/
class  MEASUREPACKAGE_API CMTrArea : public CMeasureObject  
{
public:
	CMTrArea(const CComputeMethod &computer);
	virtual void BackUpObj(CMTrArea &rt);
	virtual ~CMTrArea();
private:
	CArray<CPoint, CPoint> m_ArrPoint;	//点数组
public:
	float GetArea();
	float GetPerimeter();
public :
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();	
	virtual void Restart();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int GetResultCount();
	virtual CMeasureObject *Clone();
	virtual bool GetResultArray(vector<double> &lstResult)const;
};

#endif // !defined(AFX_MTRAREA_H__443FD9A7_4550_422D_9326_EC5559E7E058__INCLUDED_)
