
#pragma once

#include "MeasureObject.h"

//�������
class  MEASUREPACKAGE_API CMDistance : public CMeasureObject  
{
public:
	CMDistance(const CComputeMethod &computer);
	virtual void BackUpObj(CMDistance &rt);
	virtual ~CMDistance();
public:			//���̳���ʹ��
	float GetDistance() const;//���ز�������
	float ReturnGetDistanceInPixes();
public:
	double GetSlope()const;			//(M)�õ�б��
	double GetLine()const;			//����ֱ�߳�
public:
	virtual CMeasureObject*Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual bool HasEnded();
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual void DrawResult(CDC *dc);
	virtual void Restart();

public:	//����
	virtual bool SetResultValue(vector<CString> strResult);
	virtual bool GetResultValue(vector<CString> &strResult)const;
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
protected:
	CPoint m_pointStart;//��ʼ��
	CPoint m_pointEnd;	//������
private:
	vector<CString> m_result;		//��Ų��ƵĲ������
	COLORREF	m_TextColor;
};
