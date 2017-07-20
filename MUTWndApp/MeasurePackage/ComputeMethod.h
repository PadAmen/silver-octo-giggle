#pragma once

typedef struct tagCUBE_TEICHHOLZT
{
	// ����
	double et;
	double lvidd;
	double lvids;
	double rate;

	// ���
	double bas;
	double edv;
	double esv;
	double sv;
	double svi;
	double co;
	double coi;
	double ef;
	double fs;
	double mvcf;
}CUBE_TEICHHOLZT, *PCUBE_TEICHHOLZT;

struct tagMSPARARM{
	double	dbHeight;				//���
	double	dbWeight;				//����
	float   fPixesPerMM_x;
	float   fPixesPerMM_y;//ÿcm��������
	int		nHeartMethod;
	int		nMSpeed;				// M���ٶ�
	double	dbFrameTime;			// һ֡�ɼ�ʱ��	
};

class MEASUREPACKAGE_API CComputeMethod
{
public:
	CComputeMethod(void);
	~CComputeMethod(void);
	void  SetPixelsPerMM(float pixesPerMM_x,float pixesPerMM_y);
	void  SetMspeed(int speed){m_nMSpeed = speed;};
	void  SetFrameTime(double time){ m_dbFrameTime = time;};
	void  SetPatientWH(double height, double weight){m_dbWeight = weight; m_dbHeight = height;}
	void  SetHeartMethod(int heartMethod) { m_nHeartMethod = heartMethod;};
	int   GetHeartMethod()const{return m_nHeartMethod;};	
public:
	virtual float GetDistance(float fPixels)const;//�������س��ȼ���ʵ�ʳ���(��λCM)
	virtual float GetDistance(const CPoint &ptStart, const CPoint &ptEnd)const;//ֱ�߳���(cm)
	virtual float GetDistanceInPixes(const CPoint &ptStart,const CPoint &ptEnd)const;//���س���(cm)
	/*!
	@brief �������ߵĵ�����������߳���(���ȵ�λ:cm)
	@param  ptArray         �����ϵĵ�����
	@param  bAddHeadTailDis �Ƿ����ͷβ֮��ĳ���
	@return �������߳���,��λ(cm)
	*/
	virtual float GetCanveDistance(const CArray<CPoint,CPoint> &ptArray,bool bAddHeadTailDis = false)const;
	/*!
	@brief �������ߵĵ���������������(���ȵ�λ:cm^2)
	@param  ptArray         �����ϵĵ�����
	@return �������߳���,��λ(cm^2)
	*/
	virtual float GetCanveArea(const CArray<CPoint,CPoint> &ptArray)const;
	/*!
	@brief �������ߵĵ���������������(���ȵ�λ:cm^2)
	@param  ptArray         �����ϵĵ�����
	@return �������߳���,��λ(cm^2)
	*/
	virtual float GetCanveArea(const CPtrArray &ptArray)const;
	/*!
	@brief ���ݳ������ĳ��ȼ�����Բ�ܳ�
	@param nharfShortR ����᳤(���س���)
	@param nHarfLongR �볤�᳤(���س���)
	@return ������Բ���ܳ�
	*/
	virtual float GetEllipsePerimeterFromPixel(float nharfShortR_pixel,float nHarfLongR_pixel)const;
	/*!
	@brief ���ݳ������ĳ��ȼ�����Բ���
	@param nharfShortR ����᳤(���س���)
	@param nHarfLongR �볤�᳤(���س���)
	@return ������Բ�����(��λ cm^2)
	*/
	virtual float GetEllipseAreaFromPixel(float nA_pixel,float nB_pixel)const;
	/*!
	@brief ��Բ�������
	@param a a���߳���(���س���)
	@param b b���߳���(���س���)
	@return �������(��λ cm^3)
	*/
	virtual float GetVolumeEl(float a_pixel, float b_pixel) const ;
	/*!
	@brief ��ֱ�߼������(��λ:cm^3)
	@param a a�߳���(���س���)
	@param b b�߳���(���س���)
	@param m m�߳���(���س���)
	@return �������(��λ cm^3)
	*/
	virtual float GetVolumeBiInPixel(float a_pixel, float b_pixel, float m_pixel) const ;
	/*!
	@brief ��ֱ�߼������(��λ:cm^3)
	@param a a�߳���(��λcm)
	@param b b�߳���(��λcm)
	@param m m�߳���(��λcm)
	@return �������(��λ cm^3)
	*/
	virtual float GetVolumeBi(float a, float b, float c) const ;
	/*!
	@brief ��������͸߶ȼ������
	@param fArea �����(��λcm)
	@param h     �߶�(��λcm)
	@return  �������(��λcm^3)
	*/
	float GetVolumeTr(float fArea, float b) const;
	/*!
	@brief  2ֱ�߼���Ƕ�,���ؽǶ�ֵ(��λ:��) 
	@param ptStart �Ƕȵĵ�һ�������
	@param ptMiddle �Ƕȵļ��λ�����겻
	@param ptEnd �Ƕȵĵ�2�������
	*/
	virtual float Get1Angle(CPoint &ptStart,CPoint &ptMiddle,CPoint &ptEnd) const;

public:
	//! ��������
	double GetHeartRate(CPoint ptStart,CPoint ptEnd)const;
	/* ����mͼ���������ʱ��*/
	virtual double GetM_Time(CPoint ptStart, CPoint ptEnd)const;
	/** ����ֱ�ߵ�б��*/
	virtual double GetSlope(const CPoint &ptStart, const CPoint &ptEnd)const;	//(M)�õ�б��
	virtual double GetBodyArea()const;		//������
protected:
	int		m_nMSpeed;				// M���ٶ�
	double	m_dbFrameTime;			// һ֡�ɼ�ʱ��	
	double	m_dbHeight;				//���
	double	m_dbWeight;				//����
	float   fPixesPerMM_x,fPixesPerMM_y;//ÿcm��������
	int		m_nHeartMethod;
};
