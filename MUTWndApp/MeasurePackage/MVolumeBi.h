
#pragma once


#include "MeasureObject.h"
#include "MDistance.h"
/*
����ֱ������� v = pi/6 *a*b*m (mΪ��3�᳤��)
*/
class MEASUREPACKAGE_API CMVolumeBi : public CMeasureObject  
{
public:
	CMVolumeBi(const CComputeMethod &computer);
	virtual ~CMVolumeBi();
public:
	virtual bool HasEnded();
	virtual bool HasStarted();
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 4;};//���ղ������ֵ�ĸ���
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void Restart();
protected:
	float GetDistance1()const;	//�õ�3��ֱ�ߵĳ���
	float GetDistance2()const;
	float GetDistance3()const;
	float GetAge()const;			//����ϵ�� P.PSA 0.125
private:	
	CMDistance m_Distance1;//3����������Ķ���
	CMDistance m_Distance2;//3����������Ķ���
	CMDistance m_Distance3;//3����������Ķ���


};

