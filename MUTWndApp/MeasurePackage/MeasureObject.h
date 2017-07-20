/********************************************************************
	created:	2010/02/10
	created:	10:2:2010   14:42
	filename: 	C:\Program Files\Microsoft Visual Studio\MyProjects\mem\MeasureObject.h
	file path:	C:\Program Files\Microsoft Visual Studio\MyProjects\mem
	file base:	MeasureObject
	file ext:	h
	author:		jiang
	
	purpose:	//�������ܻ���,���������ģʽ�Ļ����ӿ�,��ʵ����һЩ���๲�õķ���
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
	virtual void DrawObject(CDC *dc,int nIndex);			//���Ʋ�������
	virtual bool HasEnded();								//�Ƿ������������
	virtual void SetEnded(){};								//ǿ�ƽ���
	virtual CMeasureObject *Clone();						//����������һ���µĶ���	
	virtual void DrawResult(CDC *dc,int &x,int &y);			//����������
	virtual void DrawResult(CDC *dc){};
	virtual void DrawResult(CDC *dc,CString strResult){};
	virtual bool HasStarted();								//�Ƿ��Ѿ���ʼ��������,ȷ���˵�һ��
	virtual	void Restart();	//���¿�ʼ����	
	virtual int  GetResultCount();//���ղ������ֵ�ĸ���
	virtual bool GetResultArray(vector<double> &lstResult)const;//������ŵ�ָ����������

public:
	virtual BOOL procMouse(const MSG * pMsg);//���������Ϣ
protected:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);//����������
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);  //����ƶ�����
protected:	
	void	DrawNumber(CDC *dc,const int nIndex,const CPoint &point);//��ĳ����Ʋ������
	void	DrawResultText(CDC *dc,CString strResult,CPoint &point);//float result
	void    DrawCrossFlag(CDC *dc, int x, int y);			//��ʮ��
protected:
	int		m_nStep;//��ǰ������� 
	const    CComputeMethod &m_computer;
};

#endif // !defined(AFX_MEASUREOBJECT_H__E0778C08_960D_4F96_806A_0934B54891E7__INCLUDED_)
