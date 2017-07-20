// MARatio.h: interface for the CMTrRatio class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


#include "MeasureObject.h"
#include "MTrArea.h"
/*
描线面积比
*/
class MEASUREPACKAGE_API CMTrRatio : public CMeasureObject  
{
public:
	CMTrRatio(const CComputeMethod &computer);
	virtual ~CMTrRatio();
private:
	CMTrArea m_TrArea1;//点数组1
	CMTrArea m_TrArea2;//点数组2
	float	 m_Ratio;
public :
	virtual void	DrawObject(CDC *dc,int nIndex);
	virtual BOOL	OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL	OnMouseMove(UINT nFlags, CPoint point);
	virtual bool	HasEnded();
	virtual void	Restart();
	virtual bool	HasStarted();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int    GetResultCount();//最终测量结果值的个数
	virtual CMeasureObject *Clone();
protected:
	void DrawArrayPoint(CDC *dc,CPtrArray &m_Arrpoint, bool bJoinTips);//是否连接首尾
};
