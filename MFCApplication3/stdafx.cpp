
// stdafx.cpp : 只包括标准包含文件的源文件
// MFCApplication3.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


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