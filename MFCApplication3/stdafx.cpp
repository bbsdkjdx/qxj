
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// MFCApplication3.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

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