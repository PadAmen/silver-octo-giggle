/************************************************************************/
/* ����Ϣ��ͽ�ʯ                                                       */
/************************************************************************/


#pragma once


#include "MeasureObject.h"
//��ʾ��һ����������
class MEASUREPACKAGE_API CMD3ToD1 : public CMeasureObject  
{
public:
	CMD3ToD1(const CComputeMethod &computer);
	virtual ~CMD3ToD1();
private:	
	CMDistance m_Distance1;//3����������Ķ���
	CMDistance m_Distance2;//3����������Ķ���
	CMDistance m_Distance3;//3����������Ķ���
public:
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount(){return 1;};//���ղ������ֵ�ĸ���	ֻ���һ��ֱ��
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void Restart();
};