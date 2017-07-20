
#pragma once

#include "MeasureObject.h"
#include "MDistance.h"
/*
L,W ��ʾ����ֱ�ߵĳ��ȣ����͸�
*/
class MEASUREPACKAGE_API CMTwoDistance : public CMeasureObject  
{
public:
	CMTwoDistance(const CComputeMethod &computer);
	virtual ~CMTwoDistance();
private:
	CMDistance	m_Distance1;
	CMDistance	m_Distance2;
	CString		strPercent;	
public :
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual CMeasureObject *Clone();
	virtual void DrawObject(CDC *dc,int nIndex);
	virtual bool HasEnded();
	virtual void Restart();
	virtual bool HasStarted();

	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int   GetResultCount();//���ղ������ֵ�ĸ���
	virtual bool GetResultArray(vector<double> &lstResult)const;
protected:

};