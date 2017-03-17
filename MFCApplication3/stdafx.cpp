
// stdafx.cpp : 只包括标准包含文件的源文件
// MFCApplication3.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"



CTime CtimeFromStr(WCHAR *s)
{
	int y, m, d;
	swscanf_s(s, _T("%d.%d.%d"), &y, &m, &d);
	return CTime(y, m, d, 0, 0, 0);
}

CString CtimeToStr(CTime time)
{
	return time.Format(_T("%Y.%m.%d"));
}