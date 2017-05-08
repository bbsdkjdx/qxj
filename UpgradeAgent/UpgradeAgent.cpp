#include "stdafx.h"
#include "python_support.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	MSG msg;
	SetTimer(0, 1, 1000, 0);
	//MessageBoxA(0,"","",0);
	if (!PyExecW(_T("import sys;sys.path.insert(0,'msvcp134.dll')")))
	{
		MessageBox(0, PyGetStr(), _T("import sys;sys.path.insert(0,'msvcp134.dll')"), 0);
		return 0;
	}
	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		PyExecW(_T("import upgrade"));
		break;
	}

	return 0;
}
