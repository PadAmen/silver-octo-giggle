#pragma once
//////////////////////////////////////////////////////////////////////////
/*整体界面公共参数*/

#define		APP_SCREEN_WIDTH			1000 
#define		APP_SCREEN_HEIGHT			800

#define		APP_IMAGE_WIDTH				48
#define		APP_IMAGE_HEIGHT			50

#define		APP_HEIGHT_SPACE			40
#define		APP_WIDTH_SAPCE				20

#define		APP_BORDER_WIDTH			10

#define		APP_PROGRESS_MIN			0
#define		APP_MAX_SEC					20
#define		APP_STEP_VAL				4
#define		APP_PROGRESS_MAX			APP_MAX_SEC*APP_STEP_VAL


//

#define		APP_FONT_POINT				320
#define		APP_FONT_FACENAME			_T("华文行楷")

#define		APP_FONT_POINT1				240
#define		APP_FONT_FACENAME1			_T("宋体")

#define		APP_FONT_POINT2				180
#define		APP_FONT_FACENAME2			_T("宋体")

#define		APP_FONT_POINT3				120
#define		APP_FONT_FACENAME3			_T("宋体")

#define		APP_BK_COLOR				RGB(0,0,0)
#define		APP_BK_COLOR1				RGB(22, 42, 67)		//蓝色
#define		APP_POPUP_COLOR				RGB(80,80,80)
#define		APP_BMPBK_COLOR				RGB(255,255,255)
#define		APP_TEXT_COLOR				RGB(125,0,0)
#define		APP_TEXT_COLOR1				RGB(250,250,250)
#define		APP_MEATEXT_COLOR			RGB(78,238,148)		//绿色

#define		COLOR_BK_IN					RGB(50,50,50)
#define		COLOR_BK_OUT				APP_BK_COLOR1
#define		COLOR_BK_INOUT				RGB(238,201,0)		//金黄色 开始检查
#define		COLOR_FG_IN					RGB(250,250,250)
#define		COLOR_FG_OUT				RGB(250,250,250)
#define		COLOR_START_OUT				RGB(125,0,0)

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/*应用主界面参数*/

#define		APPLY_BORDER_WIDTH			10
#define		APPLY_HEIGHT_SPACE			80
#define		APPLY_GROUP_SPACE			10
#define		APPLY_WIDTH_SPACE			60

#define		APPLY_MENU_SPACE			10
#define		APPLY_MENU_LEFT				20

#define		APPLY_MENU_WIDTH			160
#define		APPLY_MENU_HEIGHT			50

#define		APPLY_IMAGE_WIDTH			250
#define		APPLY_IMAGE_HEIGHT			220

//////////////////////////////////////////////////////////////////////////
/*扫描B模式界面参数*/
#define		SCANB_IMAGE_WIDTH			500
#define		SCANB_IMAGE_HEIGHT			40*10		//深度40cm
#define		SCANB_MAX_HEIGHT			60*10

#define		SCANB_IMAGE_SPACE			150
#define		SCANB_IMAGE_SPACE1			50

#define		SCANB_BORDER_WIDTH			10
#define		SCANB_BORDER_HEIGHT			20

#define		SCANB_COLOR_SECELT			RGB(250,0,0)

#define		SCANB_DOCTOR_LEFT			APP_SCREEN_WIDTH/3
#define		SCANB_DOCTOR_TOP			SCANB_BORDER_HEIGHT
#define		SCANB_WIDTH_TOPSPACE		60

#define		SCANB_LEFTWND_LEFT			0
#define		SCANB_LEFTWND_TOP			0
#define		SCANB_LEFTWND_HEIGHT		(APP_SCREEN_HEIGHT*40/100)

#define		SCANB_BTMWND_LEFT			0	
#define		SCANB_BTMWND_BTM			APP_SCREEN_HEIGHT - SCANB_BORDER_WIDTH
#define		SCANB_BTMWND_SPACE			10
/*#define		SCANB_BTMWND_TOP			0*/

#define		SCANB_HEIGHT_SAPCE			5
#define		SCANB_HEIGHT_SAPCE1			20
#define		SCANB_EXTERN_WIDTH			10
#define		SCANB_EXTERN_HEIGHT			10

#define		SCANB_LIST_HEIGHT			600

#define		SCANB_SAVE_MAX				1000

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/*升级界面参数*/

#define		ABOUT_ICON_WIDTH				80
#define		ABOUT_ICON_HEIGHT				80

#define		ABOUT_WIDTH_SPACE				20
#define		ABOUT_HEIGHT_SPACE				20

#define		ABOUT_STATIC_LENGTH1			80
#define		ABOUT_STATIC_LENGTH2			100
#define		ABOUT_STATIC_LENGTH3			120

#define		ABOUT_STATIC_HEIGHT1			40
#define		ABOUT_STATIC_HEIGHT2			60
#define		ABOUT_STATIC_HEIGHT3			80
//////////////////////////////////////////////////////////////////////////
/*医生、病人增加选定界面参数*/

#define		DOCTOR_BORDER_SPACE			10
#define		DOCTOR_WIDTH_SPACE			10
#define		DOCTOR_HEIGHT_SPACE			10

#define		DOCTOR_SEARCH_WIDTH			120
#define		DOCTOR_SEARCH_HEIGHT		50

#define		DOCTOR_EDIT_WIDTH			320
#define		DOCTOR_EDIT_HEIGHT			50

#define		DOCTOR_EXIT_WIDTH			80
#define		DOCTOR_EXIT_HEIGHT			50

#define		PATIENT_TEXT_WIDTH			320
#define		PATIENT_TEXT_HEIGHT			50
//////////////////////////////////////////////////////////////////////////
/*医生、病人修改资料界面参数*/
#define		DCINFO_INPUT_NUM			7
#define		PTINFO_INPUT_NUM			5

#define		DCINFO_MOTEXT_WIDTH			320
#define		DCINFO_MOTEXT_HEIGHT		50

#define		DCINFO_TEXT_WIDTH			120
#define		DCINFO_TEXT_HEIGHT			270

#define		DCINFO_RADIO_SPACE			200

#define		DCINFO_HEIGHT_SPACE			5
#define		DCINFO_HEIGHT_SPACE1		10
#define		DCINFO_BORDER_SPACE			10

#define		PTINFO_TEXT_WIDTH			120
#define		PTINFO_TEXT_HEIGHT			190

#define		PTINFO_IDEDIT_WIDTH			320		

#define		PTINFO_HEIGHT_SPACE			10
#define		PTINFO_WIDTH_SPACE			40
#define		PTINFO_BORDER_SPACE			10


//////////////////////////////////////////////////////////////////////////
/*病例档案界面参数*/
#define		REPORT_BORDER_SPACE			10
#define		REPORT_WIDTH_SPACE			5
#define		REPORT_HEIGHT_SPACE			10
#define		REPORT_HEIGHT_SPACE1		50

#define		REPORT_SEARCH_WIDTH			80
#define		REPORT_SEARCH_HEIGHT		50

#define		REPORT_MODIFY_WIDTH			80
#define		REPORT_MODIFY_HEIGHT		50

#define		REPORT_EDIT_WIDTH			320
#define		REPORT_EDIT_HEIGHT			50
#define		REPORT_EDIT_BORDER			4

#define		REPORT_EXIT_WIDTH			80
#define		REPORT_EXIT_HEIGHT			50

#define		REPORT_TEXT_WIDTH			320
#define		REPORT_TEXT_HEIGHT			40

#define		REPORT_LOWERBTN_WIDTH		80
#define		REPORT_LOWERBTN_HEIGHT		50
//////////////////////////////////////////////////////////////////////////
/*扫描结束编辑界面*/
#define  SCANOVER_BORDER_WIDTH			20
#define  SCANOVER_SPACE_WIDTH			40
#define  SCANOVER_SPACE_HEIGHT			10




//////////////////////////////////////////////////////////////////////////
//自定义窗口消息
#define		WM_CHANGE_WND		WM_USER + 0x00000011
#define		WM_DISP_IMAGE		WM_USER + 0x00000012
#define		WM_UPDATE_IMAGE		WM_USER + 0x00000013
#define		WM_SAVE_IMAGE		WM_USER + 0x00000014
#define		WM_INPUT_STR		WM_USER + 0x00000015
#define		WM_RTLAST_WND		WM_USER + 0x00000016	
#define		WM_ADD_DOCTOR		WM_USER + 0x00000017
#define		WM_ADD_PATIENT		WM_USER + 0x00000018
#define		WM_WARNING_MSG		WM_USER + 0x00000019
#define		WM_CLEAR_VECTOR		WM_USER + 0x00000020
#define		WM_LAST_WND			WM_USER + 0x00000021
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define		DEPTH_INIT_VAL		40
//////////////////////////////////////////////////////////////////////////
//功能对话框ID
typedef enum
{
	type_apply_index=1,
	type_sanb_index,
	type_update_index,
	type_doctor_index,
	type_patient_index,
	type_report_index,
	type_dcinfo_index,
	type_ptinfo_index,
	type_editimg_index,
	type_scanover_index,
	type_reportinfo_index


}TYPEPAGEINDEX;
//运行状态ID
typedef enum
{
	state_default_index=-1,
	state_run_index,
	state_fre_index,
	state_sus_index,
	state_stop_index

}STATEINDEX;
//测量菜单ID
typedef enum
{
	mea_length_index=1,
	mea_area_index,
	mea_arrow_index,
	mea_angle_index,
	mea_circum_index,
	mea_text_index

}MEASUREINDEX;
//面积周长选择功能ID
typedef enum
{
	fun_area_index,
	fun_circum_index

}MEASUREFUNINDEX;
//器官选择
typedef enum
{
	ogran_little_index,
	organ_muscle_index,
	organ_blood_index,
	organ_superface_index
	
}ORGANINDEX;
typedef enum
{
	show_search_index = 1,
	show_edit_index
}REPORTSHOWINDEX;
typedef struct tgPatient
{
	CString ptid;
	CString ptname;

}TGPATIENT,*PTGXPATIENT;
//////////////////////////////////////////////////////////////////////////
#define APP_NULL_STR			_T("")
#define APP_ADD9_IMAGE			_T("add.9.png")
#define APP_REDUCE9_IMAGE		_T("reduce.9.png")
#define APP_CAMERA_IMAGE		_T("camera.png")
#define APP_BACK_IMAGE			_T("back.png")
#define APP_SHUTTER_IMAGE		_T("shutter.png")
#define APP_LINE_IMAGE			_T("line.png")
#define APP_CURVE_IMAGE			_T("curve.png")
#define APP_OPEN_IMAGE			_T("open.png")
#define APP_FREEZE_IMAGE		_T("freeze.png")
#define APP_ICON_IMAGE			_T("ic_launcher.png")
#define APP_ICON1_IMAGE			_T("icon.png")
#define APP_LEFT_IMAGE			_T("left.png")
#define APP_RIGHT_IMAGE			_T("right.png")
#define APP_SAVE_IMAGE			_T("save.png")
#define APP_MIRROR_ON_IAMGE		_T("mirror_on.png")	
#define APP_MIRROR_OFF_IMAGE	_T("mirror_off.png")
#define APP_MORE_IMAGE			_T("more.png")
#define APP_ADD_IMAGE			_T("add.png")
#define APP_REDUCE_IMAGE		_T("reduce.png")
#define APP_DONE_IMAGE			_T("done.png")
#define APP_CLOSE_IMAGE			_T("close.png")
#define APP_CMODE_OFF_IAMGE		_T("cmode_off.png")
#define APP_CMODE_ON_IMAGE		_T("cmode_on.png")
#define APP_RESUME_IMAGE		_T("resume.png")
#define APP_SEARCH_IMAGE		_T("search.png")
#define APP_EDIT_IMAGE			_T("edit.png")
#define APP_GRAY_IMAGE			_T("gray.png")
#define APP_REDO_IMAGE			_T("redo.png")
#define APP_UNDO_IMAGE			_T("undo.png")
#define APP_DELETE_IMAGE		_T("delete.png")
#define APP_SINGLE_MODE_IMAGE	_T("single_mode.png")
#define APP_MULTI_MODE_IMAGE	_T("multi_mode.png")
#define APP_DISCONNET_IMAGE		_T("disconnect.png")
#define APP_CONNECT_IMAGE		_T("connect.png")
#define APP_EVALUE_IMAGE		_T("stat_sys_battery_0.png")

// #define SafeAlloc(len) ::VirtualAlloc(NULL, len + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE)
// #define SafeFree(pData){ if (pData != NULL){ ::VirtualFree(pData, 0, MEM_RELEASE); pData = NULL; }}
#define APP_BIN_NEWNAME			_T("MUT_40M.bin")
#define APP_BIN_OLDNAME			_T("PANDA_40M.bin")
//////////////////////////////////////////////////////////////////////////
//增益及深度相关参数
#define PIXEL_PER_CM				10.0f
#define GAIN_OFFSET_VALUE			5
#define	GAIN_MAX_VALUE				100
#define GAIN_MIN_VALUE				0
#define GAIN_INIT_VALUE				70
#define DEPTH_OFFSET_VALUE			10
#define	DEPTH_MAX_VALUE				60
#define DEPTH_MIN_VALUE				40
#define DEPTH_INIT_VALUE			DEPTH_MIN_VALUE

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//线程操作宏定义

#define		MAX_FRAM_VALUE				256*512*2
#define		QUEUE_MAX_VALUE				10

#define		TYPE_SYSTEM_INIT			0x00000001
#define		TYPE_READDATA_FORMUSB		0x00000002
#define		TYPE_GETDATA_FORMBUFFER		0x00000003
#define		TYPE_GETDATA_AND_PROCESS	0x00000004

//////////////////////////////////////////////////////////////////////////
#define MOIVE_MAX_FRAME			1024
#define SLIDER_RANGE_MIN		0
#define SLIDER_RANGE_MAX		MOIVE_MAX_FRAME



