#ifndef _MEASUREPACKAGE_
#define _MEASUREPACKAGE_
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MEASUREPACKAGE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MEASUREPACKAGE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MEASUREPACKAGE_EXPORTS
#define MEASUREPACKAGE_API __declspec(dllexport)
#else
#define MEASUREPACKAGE_API __declspec(dllimport)
#endif
//////////////////////////////////////////////////////////////////////////
//add 6.30
#include "MText.h"
/*#include "MArrow.h"*/
//////////////////////////////////////////////////////////////////////////
#include "ComputeMethod.h"
#include "MDistance.h"
#include "MDistanceYszs.h"
#include "MDRatio.h"
#include "MDiamPercent.h"
#include "MTrArea.h" 
#include "MTrLength.h"
#include "MTrArea.h"
#include "MTrPercent.h"
#include "MTrRatio.h"
#include "MVxLength.h"
#include "MVxArea.h"
#include "MElArea.h"
#include "MElPercent.h"
#include "MElRatio.h"
#include "MVolumeEl.h"
#include "MVolumeBiQlxtj.h"
#include "MVolumeTr.h"
#include "MVolumeBi.h"
#include "MAngle.h"
#include "MTwoAngle.h"
#include "MD3ToD1.h"
#include "MTWoDistance.h"
#include "MVolumeTD.h"

#include "MHeartLHWeight.h"
#include "MHeartSBTime.h"
#include "MHeartHSpeed.h"
#include "MHeartZdmBkll.h"
#include "MHeartZdmLADAOD.h"
#include "MHeartEjbBkll.h"
#include "MHeartEjbCACE.h"
#include "MHeartEjbACXjsdAndEF.h"
#include "MHeartZsgn.h"
#include "MSlope.h"
#include "MPWHeartRatio.h"



// This class is exported from the MeasurePackage.dll
class MEASUREPACKAGE_API CMeasurePackage {
public:
	CMeasurePackage(void);
	// TODO: add your methods here.
};




extern MEASUREPACKAGE_API int nMeasurePackage;

MEASUREPACKAGE_API int fnMeasurePackage(void);

#endif