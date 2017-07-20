
#pragma once


#include "MeasureObject.h"
#include "MDistance.h"
/*
����ֱ������� v = pi/6 *a*b*m (mΪ��3�᳤��)�����ֻ��ʾ���
*/
class MEASUREPACKAGE_API CMVolumeTD : public CMeasureObject  
{
public:
	CMVolumeTD(const CComputeMethod &computer);
	virtual ~CMVolumeTD();
private:	
	CMDistance m_Distance1;//3����������Ķ���
	CMDistance m_Distance2;//3����������Ķ���
	CMDistance m_Distance3;//3����������Ķ���
public:
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount(){return 1;};//���ղ������ֵ�ĸ���
	virtual bool GetResultArray(vector<double> &lstResult)const;

};