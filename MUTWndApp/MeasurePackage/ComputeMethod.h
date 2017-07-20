#pragma once

typedef struct tagCUBE_TEICHHOLZT
{
	// 输入
	double et;
	double lvidd;
	double lvids;
	double rate;

	// 输出
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
	double	dbHeight;				//身高
	double	dbWeight;				//重量
	float   fPixesPerMM_x;
	float   fPixesPerMM_y;//每cm多少像素
	int		nHeartMethod;
	int		nMSpeed;				// M超速度
	double	dbFrameTime;			// 一帧采集时间	
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
	virtual float GetDistance(float fPixels)const;//根据像素长度计算实际长度(单位CM)
	virtual float GetDistance(const CPoint &ptStart, const CPoint &ptEnd)const;//直线长度(cm)
	virtual float GetDistanceInPixes(const CPoint &ptStart,const CPoint &ptEnd)const;//像素长度(cm)
	/*!
	@brief 根据描线的点数组计算描线长度(长度单位:cm)
	@param  ptArray         描线上的点数组
	@param  bAddHeadTailDis 是否加上头尾之间的长度
	@return 返回描线长度,单位(cm)
	*/
	virtual float GetCanveDistance(const CArray<CPoint,CPoint> &ptArray,bool bAddHeadTailDis = false)const;
	/*!
	@brief 根据描线的点数组计算描线面积(长度单位:cm^2)
	@param  ptArray         描线上的点数组
	@return 返回描线长度,单位(cm^2)
	*/
	virtual float GetCanveArea(const CArray<CPoint,CPoint> &ptArray)const;
	/*!
	@brief 根据描线的点数组计算描线面积(长度单位:cm^2)
	@param  ptArray         描线上的点数组
	@return 返回描线长度,单位(cm^2)
	*/
	virtual float GetCanveArea(const CPtrArray &ptArray)const;
	/*!
	@brief 根据长轴短轴的长度计算椭圆周长
	@param nharfShortR 半短轴长(像素长度)
	@param nHarfLongR 半长轴长(像素长度)
	@return 返回椭圆的周长
	*/
	virtual float GetEllipsePerimeterFromPixel(float nharfShortR_pixel,float nHarfLongR_pixel)const;
	/*!
	@brief 根据长轴短轴的长度计算椭圆面积
	@param nharfShortR 半短轴长(像素长度)
	@param nHarfLongR 半长轴长(像素长度)
	@return 返回椭圆的面积(单位 cm^2)
	*/
	virtual float GetEllipseAreaFromPixel(float nA_pixel,float nB_pixel)const;
	/*!
	@brief 椭圆计算体积
	@param a a轴线长度(像素长度)
	@param b b轴线长度(像素长度)
	@return 返回体积(单位 cm^3)
	*/
	virtual float GetVolumeEl(float a_pixel, float b_pixel) const ;
	/*!
	@brief 三直线计算体积(单位:cm^3)
	@param a a线长度(像素长度)
	@param b b线长度(像素长度)
	@param m m线长度(像素长度)
	@return 返回体积(单位 cm^3)
	*/
	virtual float GetVolumeBiInPixel(float a_pixel, float b_pixel, float m_pixel) const ;
	/*!
	@brief 三直线计算体积(单位:cm^3)
	@param a a线长度(单位cm)
	@param b b线长度(单位cm)
	@param m m线长度(单位cm)
	@return 返回体积(单位 cm^3)
	*/
	virtual float GetVolumeBi(float a, float b, float c) const ;
	/*!
	@brief 描线面积和高度计算体积
	@param fArea 底面积(单位cm)
	@param h     高度(单位cm)
	@return  返回体积(单位cm^3)
	*/
	float GetVolumeTr(float fArea, float b) const;
	/*!
	@brief  2直线计算角度,返回角度值(单位:度) 
	@param ptStart 角度的第一条边起点
	@param ptMiddle 角度的尖点位置坐标不
	@param ptEnd 角度的第2条边起点
	*/
	virtual float Get1Angle(CPoint &ptStart,CPoint &ptMiddle,CPoint &ptEnd) const;

public:
	//! 计算心率
	double GetHeartRate(CPoint ptStart,CPoint ptEnd)const;
	/* 计算m图像上两点的时间*/
	virtual double GetM_Time(CPoint ptStart, CPoint ptEnd)const;
	/** 计算直线的斜率*/
	virtual double GetSlope(const CPoint &ptStart, const CPoint &ptEnd)const;	//(M)得到斜率
	virtual double GetBodyArea()const;		//体表面积
protected:
	int		m_nMSpeed;				// M超速度
	double	m_dbFrameTime;			// 一帧采集时间	
	double	m_dbHeight;				//身高
	double	m_dbWeight;				//重量
	float   fPixesPerMM_x,fPixesPerMM_y;//每cm多少像素
	int		m_nHeartMethod;
};
