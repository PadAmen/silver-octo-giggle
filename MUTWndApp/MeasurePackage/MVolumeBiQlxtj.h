
#pragma once


#include "MeasureObject.h"
#include "MVolumeBi.h"
#include "MDistance.h"
/*
三条直线求体积 v = pi/6 *a*b*m (m为第3轴长度) (前列腺体积)
*/
class MEASUREPACKAGE_API CMVolumeBiQlxtj : public CMVolumeBi  
{
public:
	CMVolumeBiQlxtj(const CComputeMethod &computer);
	virtual ~CMVolumeBiQlxtj();
public:
	virtual CMeasureObject*Clone();
	virtual void DrawResult(CDC *dc,int &x,int &y);
	virtual int  GetResultCount(){return 5;};//最终测量结果值的个数
	virtual bool GetResultArray(vector<double> &lstResult)const;
};