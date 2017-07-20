#include "stdafx.h"
#include "ComputeMethod.h"
#include "math.h"

#define  PI  3.14159f



CComputeMethod::CComputeMethod(void)
{
	fPixesPerMM_x = 1.0f;
	fPixesPerMM_y = 1.0f;
	m_nMSpeed = 1;						// M���ٶ�
	m_dbFrameTime = 40.28;				// һ֡�ɼ�ʱ��
	m_dbHeight = 170;					// ���
	m_dbWeight = 60;					// ����
	m_nHeartMethod = 0;				// ���������ʽ(���ҹ���)
}

CComputeMethod::~CComputeMethod(void)
{
}



float CComputeMethod::GetDistanceInPixes(const CPoint &ptStart, const CPoint &ptEnd)const
{
	float lengthInPixes =   sqrt(float((ptEnd.x-ptStart.x)*(ptEnd.x-ptStart.x)+(ptEnd.y-ptStart.y)*(ptEnd.y-ptStart.y)));
	return lengthInPixes;
}

float CComputeMethod::GetDistance(float fPixels)const
{
	return fPixels/fPixesPerMM_y/10;
}

float CComputeMethod::GetDistance(const CPoint &ptStart,const CPoint &ptEnd)const
{	
	//ֱ�߳���
	return this->GetDistance(this->GetDistanceInPixes(ptStart, ptEnd));
}

float CComputeMethod::GetCanveDistance(const CArray<CPoint,CPoint> &ptArray, bool bAddHeadTailDis/*=false*/)const
{
	if(ptArray.GetSize()<2) return 0.0f;
	float dis  = 0.0f;
	for(int i=0; i<ptArray.GetSize()-2; i++)
	{
		dis += GetDistanceInPixes(ptArray.GetAt(i), ptArray.GetAt(i+1));
	}
	//�Ƿ����ͷ�����β���ĳ�
	if(bAddHeadTailDis)
	{
		dis += GetDistanceInPixes(ptArray.GetAt(ptArray.GetSize()-1),ptArray.GetAt(0));
	}
	return this->GetDistance(dis);
}

float CComputeMethod::GetCanveArea(const CArray<CPoint,CPoint> &ptArray)const
{
	if(ptArray.GetCount() <= 2) return 0.0;
	CPoint a, b;
	float lfArea2 = 0;
	float lfArea1 = 0;
	int count = ptArray.GetSize();
	for(int i=0; i<count-1; i++)
	{
		a=(CPoint)ptArray.GetAt(i);
		b=(CPoint)ptArray.GetAt(i+1);

		if(b.x >= a.x)
			lfArea1 += ((b.y)+(a.y))*((b.x)-(a.x))/2;
		else 
			lfArea2 += ((b.y)+(a.y))*((a.x)-(b.x))/2;		
	}
	//������β���ߵ����
	a = ptArray.GetAt(count-1);
	b = ptArray.GetAt(0);	
	if(b.x >= a.x)
		lfArea1 += ((b.y)+(a.y))*((b.x)-(a.x))/2;
	else 
		lfArea2 += ((b.y)+(a.y))*((a.x)-(b.x))/2;		

	float fAreaInPixes = (lfArea2>lfArea1)?(lfArea2-lfArea1):(lfArea1-lfArea2);	
	return fAreaInPixes /(fPixesPerMM_x*10*fPixesPerMM_y*10);
}

float CComputeMethod::GetCanveArea(const CPtrArray &ptArray)const
{
	if(ptArray.GetCount() <= 2) return 0.0;
	CPoint a, b;
	float lfArea2 = 0;
	float lfArea1 = 0;
	int count = ptArray.GetSize();
	for(int i=0; i<count-1; i++)
	{
		a=*(CPoint*)ptArray.GetAt(i);
		b=*(CPoint*)ptArray.GetAt(i+1);

		if(b.x >= a.x)
			lfArea1 += ((b.y)+(a.y))*((b.x)-(a.x))/2;
		else 
			lfArea2 += ((b.y)+(a.y))*((a.x)-(b.x))/2;		
	}
	//������β���ߵ����
	a =*(CPoint*)ptArray.GetAt(count-1);
	b =*(CPoint*) ptArray.GetAt(0);	
	if(b.x >= a.x)
		lfArea1 += ((b.y)+(a.y))*((b.x)-(a.x))/2;
	else 
		lfArea2 += ((b.y)+(a.y))*((a.x)-(b.x))/2;		

	float fAreaInPixes =  (lfArea2>lfArea1)?(lfArea2-lfArea1):(lfArea1-lfArea2);	
	return fAreaInPixes /(fPixesPerMM_x*10*fPixesPerMM_y*10);
}

float CComputeMethod::GetEllipsePerimeterFromPixel(float nharfShortR,float nHarfLongR)const
{	
	float nB = (nHarfLongR < nharfShortR)? nharfShortR : nHarfLongR;
	float nA = (nHarfLongR < nharfShortR)? nHarfLongR : nharfShortR;	
	//���ܳ�
	return GetDistance(2 * PI * nA + 4 * ( nB - nA ));	
};

float CComputeMethod::GetEllipseAreaFromPixel(float nA,float nB) const 
{	
	nA = nA/fPixesPerMM_x/10;
	nB = nB/fPixesPerMM_y/10;
	return  PI * nA * nB;			//�����;
}

void CComputeMethod::SetPixelsPerMM(float pixesPerMMX, float pixesPerMMY)
{
	ASSERT(pixesPerMMX> 0.0f && pixesPerMMY > 0.0f);
	fPixesPerMM_x = pixesPerMMX;
	fPixesPerMM_y = pixesPerMMY;
}



float CComputeMethod::GetVolumeEl(float a, float b) const
{
	//assert(fPixesPerMM_x)
	a = a/(fPixesPerMM_x*10);
	b = b/(fPixesPerMM_y*10);
	if(a>b)	return PI /6 * a * b * b;
	else	return PI /6 * b * a * a;
}

float CComputeMethod::GetVolumeBi(float a, float b, float m) const
{
	return PI / 6 * a * b * m;
}
float CComputeMethod::GetVolumeTr(float fArea, float b) const
{
	return PI /6 * fArea * b;
}
float CComputeMethod::GetVolumeBiInPixel(float a, float b, float m) const
{
	a = a/(fPixesPerMM_x*10);
	b = b/(fPixesPerMM_y*10);
	m = m/(fPixesPerMM_x*10);
	return GetVolumeBi(a, b, m);
}

float CComputeMethod::Get1Angle(CPoint &ptStart,CPoint &ptMiddle,CPoint &ptEnd) const
{
	float cos_angle;
	float oneLen,twoLen,threeLen;	//�ֱ�Ϊ��һ����������ֱ�߳���
	oneLen = GetDistanceInPixes(ptStart,ptMiddle);
	twoLen = GetDistanceInPixes(ptMiddle,ptEnd);
	threeLen = GetDistanceInPixes(ptStart,ptEnd);
	if ( oneLen==0 || twoLen==0 )		//�õ��Ƕ�
	{
		return 0.0;
	} 
	else
	{
		cos_angle = (oneLen * oneLen + twoLen * twoLen - threeLen * threeLen)
					/(2 * oneLen * twoLen);
		return cos_angle;
	}
}

double CComputeMethod::GetM_Time(CPoint ptStart, CPoint ptEnd) const
{
	if (m_nMSpeed > 0)
	{
		double x = abs(ptStart.x - ptEnd.x) / (double)m_nMSpeed;
		if (x > 0)
		{
			// ������ʱ��(s)
			double dbTime = x * m_dbFrameTime / 1000.0;	// ��
			// б��
			if (dbTime > 0)
			{
				return dbTime;
			}
		}
	}
	return 0.0;
}

// (M)����
double CComputeMethod::GetHeartRate(CPoint ptStart, CPoint ptEnd)const
{
	if (m_nMSpeed > 0)
	{
		double x = abs(ptStart.x - ptEnd.x) / (double)m_nMSpeed;	// ֻ��x����
		double dbHeart = x * m_dbFrameTime / 1000.0;
		TRACE("\n %d %d",ptStart.x, ptEnd.x);
		if (dbHeart > 0.0)
		{
			dbHeart = 60.0 / dbHeart;	// 1��������������
		}
		return dbHeart;
	}
	return 0.0;
}

double CComputeMethod::GetSlope(const CPoint &ptStart, const CPoint &ptEnd) const
{
	if (m_nMSpeed > 0)
	{
		double x = abs(ptStart.x - ptEnd.x) / (double)m_nMSpeed;
		double y = abs(ptStart.y - ptEnd.y);
		if ((x > 0) && (y > 0))
		{
			// б��ֻ��M������,X����ֻ�Ǽ���,��������
			// ���������(cm)
			double dbA = y / fPixesPerMM_y / 10.0;
			// ������ʱ��(s)
			double dbTime = x * m_dbFrameTime / 1000.0;	// ��
			// б��
			if (dbTime > 0)
			{
				return (dbA / dbTime);
			}
		}
	}
	return 0.0;
}

/**
��������,��߼���������
*/
double CComputeMethod::GetBodyArea()const
{	
	if (m_dbHeight <= 0 || m_dbWeight <= 0) return 0.0;
	return (0.0061*m_dbHeight + 0.0128*m_dbWeight - 0.1529);
}