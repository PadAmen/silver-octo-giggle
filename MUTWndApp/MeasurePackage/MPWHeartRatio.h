
#pragma once

#include "MeasureObject.h"

//�������
class  MEASUREPACKAGE_API CMPWHeartRatio : public CMeasureObject  
{
public:
	CMPWHeartRatio(const CComputeMethod &computer);
	virtual ~CMPWHeartRatio();
public:			//���̳���ʹ��
	float GetDistance() const;//���ز�������
	float ReturnGetDistanceInPixes();
public:
	double GetSlope()const;			//(M)�õ�б��
	double GetLine()const;			//����ֱ�߳�
	double GetPWHeartRate(CPoint ptStart, CPoint ptEnd)const;
public:
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void Restart();
	virtual int  GetResultCount();//���ղ������ֵ�ĸ���

public:	//����
	virtual bool SetResultValue(vector<CString> strResult);
	virtual bool GetResultValue(vector<CString> &strResult)const;
protected:
	CPoint m_pointStart;//��ʼ��
	CPoint m_pointEnd;	//������
private:
	vector<CString> m_result;		//��Ų��ƵĲ������
};
