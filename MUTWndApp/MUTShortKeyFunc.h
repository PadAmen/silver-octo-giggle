#pragma once
#include "MUTGlobal.h"
class CMUTShortKeyFunc
{
public:
	CMUTShortKeyFunc(HWND mhwnd);
	~CMUTShortKeyFunc(void);
	void SetStart();

};
LRESULT CALLBACK KeyboardProc(int code,WPARAM wParam,LPARAM lParam);
