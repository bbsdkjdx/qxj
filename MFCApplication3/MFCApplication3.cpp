
// MFCApplication3.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "python_support.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3App

BEGIN_MESSAGE_MAP(CMFCApplication3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplication3App ����

CMFCApplication3App::CMFCApplication3App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴����ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCApplication3App ����

CMFCApplication3App theApp;


// CMFCApplication3App ��ʼ��

BOOL CMFCApplication3App::InitInstance()
{
	char buf[100];
	sprintf_s(buf, "agent.exe -c \"import upgrade\" %d", GetCurrentProcessId());
	WinExec(buf, 0);

	SetCurrentDir();

	if (!PyExecW(_T("from autorun import *")))
	{
		AfxMessageBox(PyGetStr());
		return 0;
	}

	if (!PyEvalW(_T("can_run()")) || !PyGetInt())
	{
		return 0;
	}
	
	//WinExec("agent.exe -c \"import upgrade\" abc",0);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));


	CMFCApplication3Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{

	}
	else if (nResponse == IDCANCEL)
	{

	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



void CMFCApplication3App::SetCurrentDir()
{
	wchar_t szExeFilePathFileName[MAX_PATH];
	GetModuleFileName(NULL, szExeFilePathFileName, MAX_PATH);
	CString str = szExeFilePathFileName;
	str = str.Mid(0, str.ReverseFind(_T('\\')));
	SetCurrentDirectory(str.GetBuffer());
}