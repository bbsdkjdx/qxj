
// stdafx.cpp : 只包括标准包含文件的源文件
// MFCApplication3.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include"python_support.h"

CString GetVersionStr(WCHAR *s)
{// 
	HRSRC hsrc = FindResource(0, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	HGLOBAL hgbl = LoadResource(0, hsrc);
	BYTE *pBt = (BYTE *)LockResource(hgbl);
	VS_FIXEDFILEINFO* pFinfo = (VS_FIXEDFILEINFO*)(pBt + 40);
	CString valStr;
	valStr.Format(_T("%s V%d.%d.%d.%d"),
		s,
		(pFinfo->dwFileVersionMS >> 16) & 0xFF,
		(pFinfo->dwFileVersionMS) & 0xFF,
		(pFinfo->dwFileVersionLS >> 16) & 0xFF,
		(pFinfo->dwFileVersionLS) & 0xFF);
	return valStr;
}
//
//bool do_upgrade(void)
//{
//	if (!PyEvalW(_T("upgrade.do_upgrade()")))
//	{
//		return false;
//		MessageBox(0, PyGetStr(), _T("upgrade.do_upgrade()"), 0);
//	}
//	if (PyGetInt()==1)
//	{
//		wchar_t szExeFilePathFileName[MAX_PATH];
//		GetModuleFileName(NULL, szExeFilePathFileName, MAX_PATH);
//		CString str = szExeFilePathFileName;
//		int pos = str.ReverseFind(_T('\\'));
//		str = str.Mid(pos + 1, str.GetLength() - pos - 1);
//		char _cmd[MAX_PATH];
//		_cmd[0] = 'u'; _cmd[1] = 'p'; _cmd[2] = 'g'; _cmd[3] = '.';
//		_cmd[4] = 'e'; _cmd[5] = 'x'; _cmd[6] = 'e'; _cmd[7] = ' ';
//		WideCharToMultiByte(CP_ACP, 0, str.GetBuffer(), -1, _cmd + 8, MAX_PATH - 8, NULL, NULL);
//		//MessageBoxA(0, _cmd, "", 0);
//		WinExec(_cmd, 0);
//		return true;
//	}
//	return false;
//}