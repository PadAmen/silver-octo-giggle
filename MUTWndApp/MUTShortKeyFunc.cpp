#include "StdAfx.h"
#include "MUTShortKeyFunc.h"

HHOOK	g_hKeyboard;
HWND	g_hWnd;
CMUTShortKeyFunc::CMUTShortKeyFunc(HWND mhwnd)
{
	g_hWnd = mhwnd;
}

CMUTShortKeyFunc::~CMUTShortKeyFunc(void)
{
	UnhookWindowsHookEx(g_hKeyboard);
}
void CMUTShortKeyFunc::SetStart()
{
	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,NULL,GetCurrentThreadId());
}
LRESULT CALLBACK KeyboardProc(
							  int code,       // hook code
							  WPARAM wParam,  // virtual-key code
							  LPARAM lParam   // keystroke-message information
							  )
{
	switch (wParam)
	{
		case VK_ESCAPE:
// 			if(GetKeyState(VK_ESCAPE)&0x80)
// 			::SendMessage(g_hWnd,WM_RTLAST_WND,0,NULL);
			break;
		case VK_F2:
			UnhookWindowsHookEx(g_hKeyboard);
			break;
		case VK_SPACE:
			break;
		case 'M':	
			if(GetKeyState(VK_CONTROL)&0x80&&GetKeyState('M')&0x80)
			{
				::SendMessage(g_hWnd,WM_RTLAST_WND,0,NULL);
			}
			break;
		case 'N':
			break;
		case 'X':
			if(GetKeyState(VK_CONTROL)&0x80&&GetKeyState('X')&0x80)
			{
				UnhookWindowsHookEx(g_hKeyboard);
				::SendMessage(g_hWnd,WM_CLOSE,0,NULL);
			}
			break;
		default:
			break;
	}

	return CallNextHookEx(g_hKeyboard,code,wParam,lParam);
}
