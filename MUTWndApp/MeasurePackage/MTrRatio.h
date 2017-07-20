// MARatio.h: interface for the CMTrRatio class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


#include "MeasureObject.h"
#include "MTrArea.h"
/*
���������
*/
class MEASUREPACKAGE_API CMTrRatio : public CMeasureObject  
{
public:
	CMTrRatio(const CComputeMethod &computer);
	virtual ~CMTrRatio();
private:
	CMTrArea m_TrArea1;//������1
	CMTrArea m_TrArea2;//������2
	float	 m_Ratio;
public :
	virtual void	DrawObject(CDC *dc,int nIndex);
	virtual BOOL	OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL	OnMouseMove(UINT nFlags, CPoint point);
	virtual bool	HasEnded();
	virtual void	Restart();
	virtual bool	HasStarted();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int    GetResultCount();//���ղ������ֵ�ĸ���
	virtual CMeasureObject *Clone();
protected:
	void DrawArrayPoint(CDC *dc,CPtrArray &m_Arrpoint, bool bJoinTips);//�Ƿ�������β
};
