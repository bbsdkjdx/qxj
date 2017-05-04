#include "stdafx.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	//MessageBoxW(0, lpCmdLine, _T("1"), 0);
	//return 0;

	MSG msg;
	SetTimer(0, 1, 1000, 0);
	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		MoveFile(_T("main"), lpCmdLine);

		char szTarget[255];
		WideCharToMultiByte(CP_ACP, 0, lpCmdLine, -1, szTarget, 255, NULL, NULL);
		WinExec(szTarget, 1);
		break;
	}

	return 0;
}
