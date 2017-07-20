/************************************************************************/
/* ������ˮָ��                                                      */
/************************************************************************/


#pragma once


#include "MeasureObject.h"
//��ʾ��һ����������
class MEASUREPACKAGE_API CMDistanceYszs : public CMeasureObject  
{
public:
	CMDistanceYszs(const CComputeMethod &computer);
	virtual ~CMDistanceYszs();
private:	
	CMDistance m_Distance1;//4����������Ķ���
	CMDistance m_Distance2;//4����������Ķ���
	CMDistance m_Distance3;//4����������Ķ���
	CMDistance m_Distance4;//4����������Ķ���
public:
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual void Restart();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 5;};//���ղ������ֵ�ĸ���
	virtual bool GetResultArray(vector<double> &lstResult)const;
private:
	vector<CString> m_result;
};