
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <afxdhtml.h>

// #ifndef _DEBUG
// #pragma comment(lib, "../release/UT-SDK.lib")
// #else
// #pragma comment(lib, "../Debug/UT-SDK.lib")
// #endif

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
#include "resource.h"
#include "inc/UT-SDK.h"
#ifndef _DEBUG
#pragma comment(lib, "./Interface/UT-SDK.lib")
#else
#pragma comment(lib, "./Interface/UT-SDK.lib")
#endif

#define SafeAlloc(len) ::VirtualAlloc(NULL, len + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE)
#define SafeFree(pData){ if (pData != NULL){ ::VirtualFree(pData, 0, MEM_RELEASE); pData = NULL; } }

// #include <vector>
// using namespace std;

#define _DICOM_SUPPORT_
#ifdef _DICOM_SUPPORT_
/* required to support color images */
#include <dcmtk/dcmimage/diregist.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmimage/diargimg.h>
#include <dcmtk/dcmdata/dctk.h>          /* for various dcmdata headers */
#include <dcmtk/dcmdata/dcdebug.h>       /* for SetDebugLevel */
#include <dcmtk/dcmdata/cmdlnarg.h>      /* for prepareCmdLineArgs */
#include <dcmtk/dcmdata/dcuid.h>         /* for dcmtk version name */
#include <dcmtk/dcmdata/dcrledrg.h>      /* for DcmRLEDecoderRegistration */

#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

#ifdef _DEBUG
#pragma comment(linker, "/NOD:msvcrt.lib")
#pragma comment(lib,"./MeasurePackage/Debug/MeasurePackaged.lib")
#endif
#ifdef _WIN64	
#pragma comment(lib,"./MeasurePackage/Release/MeasurePackaged.lib")
#pragma comment(lib, "../dcmtk-3.5.4-win32-i386/lib_x64/ofstd.lib")
#pragma comment(lib, "../dcmtk-3.5.4-win32-i386/lib_x64/dcmimage.lib")
#pragma comment(lib, "../dcmtk-3.5.4-win32-i386/lib_x64/dcmdata.lib")
#pragma comment(lib, "../dcmtk-3.5.4-win32-i386/lib_x64/dcmjpeg.lib")
#pragma comment(lib, "../dcmtk-3.5.4-win32-i386/lib_x64/dcmimgle.lib")
#pragma comment(lib, "../dcmtk-3.5.4-win32-i386/lib_x64/dcmtls.lib")
#else
#pragma comment(lib, "./Interface/dcmtk/dcmtk-3.5.4-win32-i386/lib/ofstd.lib")
#pragma comment(lib, "./Interface/dcmtk/dcmtk-3.5.4-win32-i386/lib/dcmimage.lib")
#pragma comment(lib, "./Interface/dcmtk/dcmtk-3.5.4-win32-i386/lib/dcmdata.lib")
#pragma comment(lib, "./Interface/dcmtk/dcmtk-3.5.4-win32-i386/lib/dcmjpeg.lib")
#pragma comment(lib, "./Interface/dcmtk/dcmtk-3.5.4-win32-i386/lib/dcmimgle.lib")
#pragma comment(lib, "./Interface/dcmtk/dcmtk-3.5.4-win32-i386/lib/dcmtls.lib")
#endif

#endif
#include <GdiPlus.h>
//#include <afxdlgs.h>
#include "DcmFile.h"
#include "GeneralEquModule.h"
#include "GeneralImageModule.h"
#include "GeneralSeriesModule.h"
#include "GeneralStudyModule.h"
#include "ImagePixelModule.h"
#include "ScreenShot.h"



