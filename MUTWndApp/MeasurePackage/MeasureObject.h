/********************************************************************
	created:	2010/02/10
	created:	10:2:2010   14:42
	filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MeasureObject.h
	file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
	file base:	MeasureObject
	file ext:	h
	author:		jiang
	
	purpose:	//测量功能基类,定义各测量模式的基本接口,并实现了一些子类共用的方法
*********************************************************************/
// MeasureObject.h: interface for the CMeasureObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEASUREOBJECT_H__E0778C08_960D_4F96_806A_0934B54891E7__INCLUDED_)
#define AFX_MEASUREOBJECT_H__E0778C08_960D_4F96_806A_0934B54891E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "ComputeMethod.h"
#include <vector>
using namespace std;

class MEASUREPACKAGE_API CMeasureObject  
{	
public:
	CMeasureObject(const CComputeMethod &);
	virtual ~CMeasureObject();

public:	
	virtual void SetMDTextColor(COLORREF color){};
	virtual void DrawObject(CDC *dc,int nIndex);			//绘制测量界面
	virtual bool HasEnded();								//是否结束测量过程
	virtual void SetEnded(){};								//强制结束
	virtual CMeasureObject *Clone();						//创建并返回一个新的对象	
	virtual void DrawResult(CDC *dc,int &x,int &y);			//计算测量结果
	virtual void DrawResult(CDC *dc){};
	virtual void DrawResult(CDC *dc,CString strResult){};
	virtual bool HasStarted();								//是否已经开始测量过程,确定了第一点
	virtual	void Restart();	//重新开始测量	
	virtual int  GetResultCount();//最终测量结果值的个数
	virtual bool GetResultArray(vector<double> &lstResult)const;//将结果放到指定的数组里

public:
	virtual BOOL procMouse(const MSG * pMsg);//处理鼠标消息
protected:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);//鼠标左键操作
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);  //鼠标移动操作
protected:	
	void	DrawNumber(CDC *dc,const int nIndex,const CPoint &point);//在某点绘制测量序号
	void	DrawResultText(CDC *dc,CString strResult,CPoint &point);//float result
	void    DrawCrossFlag(CDC *dc, int x, int y);			//画十字
protected:
	int		m_nStep;//当前步骤序号 
	const    CComputeMethod &m_computer;
};

#endif // !defined(AFX_MEASUREOBJECT_H__E0778C08_960D_4F96_806A_0934B54891E7__INCLUDED_)
