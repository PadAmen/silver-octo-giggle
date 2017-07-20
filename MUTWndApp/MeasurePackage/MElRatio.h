
/********************************************************************
	created:	2010/03/04
	created:	4:3:2010   10:38
	filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MERatio.h
	file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
	file base:	MERatio
	file ext:	h
	author:		jiang
	
	purpose:	��������Բ�����xx����
*********************************************************************/


// MERatio.h: interface for the CMElRatio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERATIO_H__A49630B2_68C7_45B5_919E_C6B266E4A06E__INCLUDED_)
#define AFX_MERATIO_H__A49630B2_68C7_45B5_919E_C6B266E4A06E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MeasureObject.h"
#include "MElArea.h"
/*
δע��Բ�����a1/a2
*/

class MEASUREPACKAGE_API CMElRatio : public CMeasureObject  
{
public:
	CMElRatio(const CComputeMethod &computer);
	virtual ~CMElRatio();
private:
	CMElArea m_AxArea1;//���һ
	CMElArea m_AxArea2;//�����
public:	
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);	
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual CMeasureObject *Clone();
	virtual int   GetResultCount();//���ղ������ֵ�ĸ���

};

#endif // !defined(AFX_MERATIO_H__A49630B2_68C7_45B5_919E_C6B266E4A06E__INCLUDED_)
