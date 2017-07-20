
#pragma once


#include "MeasureObject.h"
/************************************************************************/
/*   ��Բ�������                                                                   */
/************************************************************************/
class MEASUREPACKAGE_API CMElArea : public CMeasureObject  
{
public:
	CMElArea(const CComputeMethod &computer);
	CMElArea(const CComputeMethod &computer,UINT index);
	virtual void BackUpObj(CMElArea &rt);
	virtual ~CMElArea();
private:
	CPoint m_pointFirst;
	CPoint m_pointSecond;
	CPoint m_pointThird;
	float	    m_nAInPix, m_nBInPix;//�볤�����
	COLORREF cr,dr;	
public:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual	void DrawResult(CDC *dc);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual bool GetResultArray(vector<double> &lstResult)const;
	virtual bool HasEnded();
	virtual void Restart();
	virtual CMeasureObject *Clone();
	virtual int   GetResultCount();//���ղ������ֵ�ĸ���
	float  GetArea()		{return m_computer.GetEllipseAreaFromPixel(m_nAInPix, m_nBInPix);}
	float  GetPerimeter()	{return m_computer.GetEllipsePerimeterFromPixel(m_nAInPix, m_nBInPix);}
	float  GetLongRInPixel()		{ return m_nAInPix > m_nBInPix ? m_nAInPix : m_nBInPix;};
	float  GetShortRInPixel()		{ return m_nAInPix < m_nBInPix ? m_nAInPix : m_nBInPix;};	
public:		//���̳���ʹ��
	float ReturnGetEllipseAreaFromPixel();
	float ReturnGetEllipsePerimeterFromPixel();
public:		//����
	virtual bool SetResultValue(vector<CString> strResult);
	virtual bool GetResultValue(vector<CString> &strResult)const;
protected:
	//����ƫ��,�Ƕȱ任��ĵ�
	void CirPot( CDC*dc,const double x,const double y,const double beta,const CPoint& pointCenter);
	//���������Բ
	//void DrawAreaEllipse(CDC *dc,int nStep,CPoint &pFirst,CPoint &pSecond,CPoint &pThird);
private:
	vector<CString> m_result;		//��Ų��ƵĲ������
public:
	COLORREF	m_TextColor;
	UINT		m_uIndex;			//����ܳ�����
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
	void CountBInPix(const double beta,const CPoint& pointCenter);
};


