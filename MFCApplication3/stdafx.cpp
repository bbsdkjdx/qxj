
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// MFCApplication3.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

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