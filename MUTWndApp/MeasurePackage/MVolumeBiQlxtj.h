
#pragma once


#include "MeasureObject.h"
#include "MVolumeBi.h"
#include "MDistance.h"
/*
����ֱ������� v = pi/6 *a*b*m (mΪ��3�᳤��) (ǰ�������)
*/
class MEASUREPACKAGE_API CMVolumeBiQlxtj : public CMVolumeBi  
{
public:
	CMVolumeBiQlxtj(const CComputeMethod &computer);
	virtual ~CMVolumeBiQlxtj();
public:
	virtual CMeasureObject*Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 5;};//���ղ������ֵ�ĸ���
	virtual bool GetResultArray(vector<double> &lstResult)const;
};