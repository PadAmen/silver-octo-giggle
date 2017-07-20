
#pragma once


#include "MeasureObject.h"
/************************************************************************/
/*   椭圆测量面积                                                                   */
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
	float	    m_nAInPix, m_nBInPix;//半长轴短轴
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
	virtual int   GetResultCount();//最终测量结果值的个数
	float  GetArea()		{return m_computer.GetEllipseAreaFromPixel(m_nAInPix, m_nBInPix);}
	float  GetPerimeter()	{return m_computer.GetEllipsePerimeterFromPixel(m_nAInPix, m_nBInPix);}
	float  GetLongRInPixel()		{ return m_nAInPix > m_nBInPix ? m_nAInPix : m_nBInPix;};
	float  GetShortRInPixel()		{ return m_nAInPix < m_nBInPix ? m_nAInPix : m_nBInPix;};	
public:		//给继承类使用
	float ReturnGetEllipseAreaFromPixel();
	float ReturnGetEllipsePerimeterFromPixel();
public:		//产科
	virtual bool SetResultValue(vector<CString> strResult);
	virtual bool GetResultValue(vector<CString> &strResult)const;
protected:
	//绘制偏移,角度变换后的点
	void CirPot( CDC*dc,const double x,const double y,const double beta,const CPoint& pointCenter);
	//三点绘制椭圆
	//void DrawAreaEllipse(CDC *dc,int nStep,CPoint &pFirst,CPoint &pSecond,CPoint &pThird);
private:
	vector<CString> m_result;		//存放产科的测量结果
public:
	COLORREF	m_TextColor;
	UINT		m_uIndex;			//面积周长索引
	virtual void SetMDTextColor(COLORREF color=RGB(255,255,255)){m_TextColor = color;};
	void CountBInPix(const double beta,const CPoint& pointCenter);
};


