
// MFCApplication3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"
#include "python_support.h"
#include "DlgLogin.h"
#include "DlgChangePwd.h"
#include "DlgHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCApplication3Dlg *g_p_main_dlg = nullptr;

void show_window(int para)
{
	if (g_p_main_dlg)
	{
		g_p_main_dlg->m_can_show = true;
		g_p_main_dlg->ShowWindow(para);
	}
}

HWND get_main_hwnd(void)
{
	return g_p_main_dlg ? g_p_main_dlg->m_hWnd : 0;
}

void quit_app(void)
{
	if (g_p_main_dlg)
	{
		g_p_main_dlg->Quit();
	}
}

void set_timer(int id,int sec, bool reg)
{
	if (!g_p_main_dlg)return;
	if (reg)
	{
		g_p_main_dlg->SetTimer(id, sec * 1000, 0);
	}
	else
	{
		g_p_main_dlg->KillTimer(id);
	}
}

void listen_clipboard(bool enable)
{
	if (!g_p_main_dlg)return;
	g_p_main_dlg->ListenClipboard(enable);
}

bool set_tray_icon(WCHAR *fn)
{
	if (!g_p_main_dlg)return false;
	return g_p_main_dlg->SetTrayIcon(fn);
}

void block_message(bool blk)
{
	if (g_p_main_dlg)
	{
		g_p_main_dlg->m_block_msg = blk;
	
		//AfxMessageBox(_T("set blk2"));
	}
}

void append_actives(int n,WCHAR *un1, WCHAR *un2, WCHAR *leave, WCHAR *status, WCHAR *id)
{
	if (!g_p_main_dlg)return;
	g_p_main_dlg->m_history.InsertItem(n,un1);
	g_p_main_dlg->m_history.SetItemText(n, 1, un2);
	g_p_main_dlg->m_history.SetItemText(n, 2, leave);
	g_p_main_dlg->m_history.SetItemText(n, 3, status);
	g_p_main_dlg->m_history.SetItemText(n, 4, id);

	CString sta(_T("待您审批"));
	if (g_p_main_dlg && sta==status)
	{
		g_p_main_dlg->m_need_notify = 1;
	}
}



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication3Dlg::IDD, pParent)
	, m_can_show(false)
	, m_nextClipboardViewer(0)
	, m_isListenClipboard(false)
	, m_block_msg(false)
	, m_name(_T(""))
	, m_need_notify(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_p_main_dlg = this;
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_code);
	//  DDX_Text(pDX, IDC_EDIT2, m_result);
	//  DDX_Control(pDX, IDC_EDIT1, m_code_edit);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_login);
	DDX_Control(pDX, IDC_LIST1, m_history);
	DDX_Control(pDX, IDC_EDIT3, m_proposer);
	DDX_Control(pDX, IDC_EDIT4, m_approver);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_time_start);
	DDX_Control(pDX, IDC_COMBO2, m_type);
	DDX_Control(pDX, IDC_EDIT5, m_reason);
	DDX_Control(pDX, IDC_COMBO1, m_allow);
	DDX_Control(pDX, IDC_EDIT6, m_comment);
	DDX_Control(pDX, IDC_BUTTON3, m_btn_submit);
	DDX_Control(pDX, IDC_BUTTON4, m_btn_back);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Control(pDX, IDC_COMBO5, m_hours);
	DDX_Control(pDX, IDC_BUTTON7, m_btn_delete);
	//  DDX_Control(pDX, IDC_BUTTON5, m_btn_propose);
	DDX_Control(pDX, IDC_BUTTON5, m_btn_propose);
}

const UINT WM_TaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));
const int IDM_TRAY = 2000;

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_MESSAGE(IDM_TRAY, TrayFunction)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
	ON_WM_NCPAINT()
	ON_REGISTERED_MESSAGE(WM_TaskbarRestart, &CMFCApplication3Dlg::OnTaskbarrestart)
//	ON_EN_SETFOCUS(IDC_EDIT1, &CMFCApplication3Dlg::OnSetfocusEdit1)
ON_WM_TIMER()
ON_WM_CHANGECBCHAIN()
ON_WM_DRAWCLIPBOARD()
ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3Dlg::OnLogIn)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication3Dlg::OnLvnItemchangedList1)
ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication3Dlg::OnRefresh)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, &CMFCApplication3Dlg::OnCustomdrawHistory)
ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication3Dlg::OnEnChangeEdit5)
ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication3Dlg::OnSubmit)
ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication3Dlg::OnDoBack)
ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication3Dlg::OnPropose)
ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication3Dlg::OnChangePassWd)
ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication3Dlg::OnBtnDelete)
ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication3Dlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CMFCApplication3Dlg 消息处理程序

UINT __cdecl NotifyFunction(LPVOID pParam)
{
	CMFCApplication3Dlg *pdlg = (CMFCApplication3Dlg*)pParam;
	for (;;)
	{
		if (pdlg->m_need_notify)
		{
			pdlg->m_tnid.hIcon = 0;
			Shell_NotifyIcon(NIM_MODIFY, &pdlg->m_tnid);
			Sleep(300);
			pdlg->m_tnid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
			Shell_NotifyIcon(NIM_MODIFY, &pdlg->m_tnid);
			Sleep(300);
		}
		else
		{
			Sleep(100);
		}
	}
	return 0;
}

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// add sys tray.
	CString s_title = GetVersionStr(_T("国土环翠分局请销假客户端"));
	SetWindowText(s_title);
	m_tnid.cbSize = sizeof(NOTIFYICONDATA);
	m_tnid.hWnd = m_hWnd;
	m_tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_tnid.uCallbackMessage = IDM_TRAY;
	wcscpy_s(m_tnid.szTip, s_title);
	m_tnid.uID = IDR_MAINFRAME;
	m_tnid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Shell_NotifyIcon(NIM_ADD, &m_tnid);
	//reg functions being used by python.
	REG_EXE_FUN(show_window, "#l","void(int show)");
	REG_EXE_FUN(get_main_hwnd, "u","uint()");
	REG_EXE_FUN(quit_app, "#","void()");
	REG_EXE_FUN(set_timer, "#lll", "void(int id,int sec,bool reg)");
	REG_EXE_FUN(listen_clipboard, "#l", "void(bool enable)");
	REG_EXE_FUN(set_tray_icon, "lS", "bool(wchar* fn_ico)");
	REG_EXE_FUN(block_message, "#l", "block_message(bool blk)");
	REG_EXE_FUN(append_actives, "#lSSSSS", "append_actives(int n,WCHAR *un1, WCHAR *un2, WCHAR *leave, WCHAR *status,WCHAR* id)");

	//list control set
	RECT rct;
	m_history.GetWindowRect(&rct);
	int len = rct.right - rct.left;
	DWORD dwStyle = m_history.GetExtendedStyle();    //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT;                //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES;                    //网格线（report风格时）
	m_history.SetExtendedStyle(dwStyle);            //设置扩展风格
	m_history.InsertColumn(0, _T("请假人"), 0, len/4-10);
	m_history.InsertColumn(1, _T("批假人"), 0, len/4-10);
	m_history.InsertColumn(2, _T("离岗时间"), 0, len/4);
	m_history.InsertColumn(4, _T("状态"), 0, len / 4);
	m_history.InsertColumn(5, _T(""), 0, 0);

	PySendMsg("on_init_dialog", 0, 0);

	//auto login.
	CString un, pw;
	PySendMsg("get_log_info", 0, 0);
	un = PyGetStr(0);
	pw = PyGetStr(1);
	if (un!=_T("") && SvrLogIn(un.GetBuffer(), pw.GetBuffer()))
	{
		OnRefresh();
	}
	SetTimer(10, 10000, 0);
	SetTimer(600, 600000, 0);
	m_notify_thd = AfxBeginThread(NotifyFunction, (LPVOID)this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication3Dlg::OnPaint()
{
	if (!m_can_show)
	{
		ShowWindow(0);
		return;
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMFCApplication3Dlg::TrayFunction(WPARAM wp, LPARAM lp)
{
	switch (lp)
	{
	case  WM_RBUTTONDBLCLK:
		PySendMsg("on_tray_rdbclk", wp, lp);
		break;
	case  WM_LBUTTONDBLCLK:
		PySendMsg("on_tray_ldbclk", wp, lp);
		break;
	case WM_RBUTTONUP:
		PySendMsg("on_tray_rbtnup", wp, lp);
		break;
	default:
		break;
	}
	return 0;
}

BOOL CMFCApplication3Dlg::DestroyWindow()
{
	// TODO:  在此添加专用代码和/或调用基类
	Shell_NotifyIcon(NIM_DELETE, &m_tnid);
	ListenClipboard(false);
	PySendMsg("on_destroy_window", 0, 0);
	return CDialogEx::DestroyWindow();
}

void CMFCApplication3Dlg::OnOK()
{
	//UpdateData();
	//PyEvalOrExecW(m_code.GetBuffer());
	//m_result = PyGetStr();

	////CString str;
	////str.Format(_T("%f"),PyGetDouble());
	////m_result = str;

	//UpdateData(FALSE);
	////m_code_edit.SetSel(0, -1);
}

void CMFCApplication3Dlg::OnCancel()
{

	ShowWindow(0);
}

void CMFCApplication3Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	PySendMsg("on_hot_key", nKey1, nKey2);
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CMFCApplication3Dlg::OnNcPaint()
{
	if (!m_can_show)
	{
		ShowWindow(0);
		return;
	}
	CDialogEx::OnNcPaint();
}


afx_msg LRESULT CMFCApplication3Dlg::OnTaskbarrestart(WPARAM wParam, LPARAM lParam)
{
	Shell_NotifyIcon(NIM_ADD, &m_tnid);
	return 0;
}


void CMFCApplication3Dlg::Quit()
{
	CDialogEx::OnOK();
}



void CMFCApplication3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_block_msg)return;
	PySendMsg("on_timer", nIDEvent, 0);

	if (nIDEvent==10 && !IsWindowVisible())//!m_history.GetFirstSelectedItemPosition())
	{
		OnRefresh();
	}

	if (nIDEvent==600)
	{
		char buf[100];
		sprintf_s(buf, "agent.exe -c \"import upgrade\" %d", GetCurrentProcessId());
		WinExec(buf, 0);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication3Dlg::ListenClipboard(bool enable)
{
	if (enable)
	{
		m_nextClipboardViewer = SetClipboardViewer();
		m_isListenClipboard = true;
	}
	else
	{
		if (m_isListenClipboard)
		{
			ChangeClipboardChain(m_nextClipboardViewer);
		}
		m_isListenClipboard = false;
	}

}


void CMFCApplication3Dlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter)
{
	CDialogEx::OnChangeCbChain(hWndRemove, hWndAfter);
	if (hWndRemove==m_nextClipboardViewer)
	{
		m_nextClipboardViewer = hWndAfter;
		return;
	}
	if (m_nextClipboardViewer!=NULL)
	{
		::SendMessage(m_nextClipboardViewer, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter);
	}
	// TODO:  在此处添加消息处理程序代码
}


void CMFCApplication3Dlg::OnDrawClipboard()
{
	CDialogEx::OnDrawClipboard();

	PySendMsg("on_clipboard_change",0,0);
	::SendMessage(m_nextClipboardViewer, WM_DRAWCLIPBOARD, 0, 0);
}


bool CMFCApplication3Dlg::SetTrayIcon(WCHAR* fn)
{
	HICON icon = (HICON)LoadImage(
		NULL,
		fn,//name or identifier of image
		IMAGE_ICON,//type of image-can also be IMAGE_CURSOR or MAGE_ICON
		0, 0,//desired width and height
		LR_LOADFROMFILE);//load flags

	if (!icon)
	{
		return false;
	}
	m_tnid.hIcon = icon;
	Shell_NotifyIcon(NIM_MODIFY, &m_tnid);
	return true;
}


void CMFCApplication3Dlg::OnLogIn()
{
	CDlgLogin cdl;
	CString un, pw;
	PySendMsg("get_log_info", 0, 0);
	un = PyGetStr(0);
	pw = PyGetStr(1);


	if (cdl.ShowLogin(un, pw) )
	{
		SvrLogIn(un.GetBuffer(), pw.GetBuffer());
		OnRefresh();
	}
}


void CMFCApplication3Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	ShowDetail();
	*pResult = 0;
}


void CMFCApplication3Dlg::OnRefresh()
{
	m_history.DeleteAllItems();
	if (m_name == _T(""))
	{
		//AfxMessageBox(_T("请先登录！"));
		return;
	}
	m_need_notify = 0;
	PySendMsg("refresh_actives", 0, 0);
	
	CString ofln(_T("offline"));
	if (ofln==PyGetStr(0))
	{
		m_history.InsertItem(0, _T("系统离线！"));
		m_history.InsertItem(1, _T("请联系技术人员！"));
	}
}


void CMFCApplication3Dlg::OnCustomdrawHistory(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = CDRF_DODEFAULT;
	NMLVCUSTOMDRAW * lplvdr = (NMLVCUSTOMDRAW*)pNMHDR;
	NMCUSTOMDRAW &nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)//判断状态
	{
	case CDDS_PREPAINT:
	{
						  *pResult = CDRF_NOTIFYITEMDRAW;
						  return;
	}
	case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变
	{
						CString strText;
						strText = m_history.GetItemText((int)nmcd.dwItemSpec, 3);
						// AfxMessageBox(strText);
						if (strText.Find(_T("已销假")) != -1)
						{
							//lplvdr->clrText = 0x00ff00;//ItemColor;
							*pResult = CDRF_DODEFAULT;
							return;
						}
						if (strText.Find(_T("已批准")) != -1)
						{
							lplvdr->clrText = 0x00ff00;//ItemColor;
							*pResult = CDRF_DODEFAULT;
							return;
						}
						if (strText.Find(_T("未批准")) != -1)
						{
							lplvdr->clrText = 0x0000ff;//ItemColor;
							*pResult = CDRF_DODEFAULT;
							return;
						}
						if (strText.Find(_T("待审批")) != -1)
						{
							lplvdr->clrTextBk = RGB(227,176,0);//ItemColor;
							*pResult = CDRF_DODEFAULT;
							return;
						}
						if (strText.Find(_T("待您审批")) != -1)
						{
							lplvdr->clrTextBk = RGB(254,188,193);//ItemColor;
							*pResult = CDRF_DODEFAULT;
							return;
						}
	}
		break;
	}

}


bool CMFCApplication3Dlg::SvrLogIn(wchar_t* un, wchar_t* pw)
{
		PySendMsg("login", (unsigned)un, (unsigned)pw);
		switch (PyGetInt())
		{
		case 1:
			AfxMessageBox(PyGetStr(0));
			m_name = _T("");
			UpdateData(FALSE);
			GetDlgItem(IDC_EDIT1)->SetWindowTextW(_T(""));
			GetDlgItem(IDC_EDIT7)->SetWindowTextW(_T(""));
			break;
		case 3:
			m_name=PyGetStr(0);
			UpdateData(FALSE);
			GetDlgItem(IDC_EDIT1)->SetWindowTextW(PyGetStr(1));
			GetDlgItem(IDC_EDIT7)->SetWindowTextW(PyGetStr(2));
			return true;
			break;
		default:
			AfxMessageBox(_T("网络连接失败！"));
			break;
		}
		return false;
}


void CMFCApplication3Dlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication3Dlg::ShowDetail()
{
	POSITION pos = m_history.GetFirstSelectedItemPosition();
	int nItem = pos ? m_history.GetNextSelectedItem(pos) : -1;

	CString s_proposer;
	CString s_approver;
	CString s_time=_T("2017.1.1 0:0");
	CString s_hours;
	CString s_type;
	CString s_reason;
	CString s_allow;
	CString s_comment;
	CString s_backed;// = PyGetStr(8);
	if (nItem>-1)
	{
		PySendMsg("get_actives_detail", nItem, 0);
		s_proposer = PyGetStr(0);
		s_approver = PyGetStr(1);
		s_time = PyGetStr(2);
		s_hours = PyGetStr(3);
		s_type = PyGetStr(4);
		s_reason = PyGetStr(5);
		s_allow = PyGetStr(6);
		s_comment = PyGetStr(7);
		s_backed = PyGetStr(8);
	}
	m_proposer.SetWindowTextW(s_proposer);//proposer
	m_approver.SetWindowTextW(s_approver);//approver
	SetCtrlTime(s_time.GetBuffer());
	m_hours.SetCurSel(m_hours.FindString(-1, s_hours));//hours
	m_type.SetCurSel(m_type.FindString(-1,s_type));//type
	m_reason.SetWindowTextW(s_reason);//reason
	m_allow.SetCurSel(m_allow.FindString(-1, s_allow));//allow
	m_comment.SetWindowTextW(s_comment);//


	bool can_propose = (m_name == s_proposer && s_allow==_T(""));
	bool can_approve = (m_name == s_approver && s_allow == _T(""));

	m_date_start.EnableWindow(can_propose);
	m_time_start.EnableWindow(can_propose);
	m_hours.EnableWindow(can_propose);
	m_type.EnableWindow(can_propose);
	m_reason.EnableWindow(can_propose);
	m_allow.EnableWindow(can_approve);
	m_comment.EnableWindow(can_approve);
	m_btn_submit.EnableWindow(can_approve||can_propose);
	m_btn_propose.EnableWindow(!(can_approve || can_propose));
	m_btn_back.EnableWindow(s_allow==_T("是") && m_name==s_proposer && s_backed==_T(""));
	m_btn_delete.EnableWindow(can_propose || (s_allow == _T("否") && m_name==s_proposer));

}


void CMFCApplication3Dlg::OnSubmit()
{
	int nItem = -1;
	POSITION pos = m_history.GetFirstSelectedItemPosition();
	if (pos)nItem = m_history.GetNextSelectedItem(pos);

	CString tmp,approver;
	PySetStr(m_name.GetBuffer(), 0);//token
	m_proposer.GetWindowTextW(tmp);
	PySetStr(tmp.GetBuffer(), 1);//proposer
	m_approver.GetWindowTextW(approver);
	PySetStr(approver.GetBuffer(), 2);//approver
	PySetStr(GetCtrlTime().GetBuffer(), 3);//start time
	int cur = m_hours.GetCurSel();
	if (cur == -1)
	{
		AfxMessageBox(_T("请选择请假时长！"));
		return;
	}
	m_hours.GetLBText(cur, tmp);
	PySetStr(tmp.GetBuffer(), 4);//propose hours.
	cur = m_type.GetCurSel();
	if (cur==-1)
	{
		AfxMessageBox(_T("请选择假期类型！"));
		return;
	}
	m_type.GetLBText(cur, tmp);
	PySetStr(tmp.GetBuffer(), 5);//type
	m_reason.GetWindowTextW(tmp);
	PySetStr(tmp.GetBuffer(), 6);//reason
	cur = m_allow.GetCurSel();
	if (cur>-1)
	{
		m_allow.GetLBText(cur, tmp);
	}
	else
	{
		tmp = _T("");
	}
	PySetStr(tmp.GetBuffer(), 7);//allow
	if (tmp==_T("") && m_name==approver)
	{
		AfxMessageBox(_T("请选择是否准假！"));
		return;
	}
	m_comment.GetWindowTextW(tmp);
	PySetStr(tmp.GetBuffer(), 8);//comment
	PySetStr(_T(""), 9);//back time
	PySetStr(nItem>=0?m_history.GetItemText(nItem,4).GetBuffer():_T(""), 10);
	//AfxMessageBox(m_history.GetItemText(nItem, 4));
	PySendMsg("submit", 0, 0);
	OnRefresh();
	ShowDetail();
}


void CMFCApplication3Dlg::OnDoBack()
{
	int nItem = -1;
	POSITION pos = m_history.GetFirstSelectedItemPosition();
	if (pos)
	{
		nItem = m_history.GetNextSelectedItem(pos);
		PySetStr(m_history.GetItemText(nItem, 4).GetBuffer(),0);
		PySendMsg("do_back", 0, 0);
		m_btn_back.EnableWindow(0);
		OnRefresh();
	}
}


void CMFCApplication3Dlg::OnPropose()
{
	CString leader;
	GetDlgItem(IDC_EDIT7)->GetWindowTextW(leader);
	if (m_name==_T(""))
	{
		AfxMessageBox(_T("请先登录！"));
		return;
	}
	POSITION pos = m_history.GetFirstSelectedItemPosition();
	if (pos)
	{
		int nItem = m_history.GetNextSelectedItem(pos);
		m_history.SetItemState(nItem, 0, -1);
	}

	
	m_proposer.SetWindowTextW(m_name);
	m_approver.SetWindowTextW(leader);
	CTime t = CTime::GetCurrentTime();
	m_date_start.SetTime(&t);
	m_time_start.SetTime(&t);
	m_type.SetCurSel(-1);
	m_reason.SetWindowTextW(_T(""));
	m_allow.SetCurSel(-1);
	m_comment.SetWindowTextW(_T(""));

	m_date_start.EnableWindow(1);
	m_time_start.EnableWindow(1);
	m_hours.EnableWindow(1);
	m_type.EnableWindow(1);
	m_reason.EnableWindow(1);
	m_allow.EnableWindow(0);
	m_comment.EnableWindow(0);
	m_btn_submit.EnableWindow(1);
	m_btn_propose.EnableWindow(0);
	m_btn_back.EnableWindow(0);

}


void CMFCApplication3Dlg::OnChangePassWd()
{
	CDlgChangePwd ccp;
	m_name,ccp.ChangePasswd(m_name);
}


void CMFCApplication3Dlg::SetCtrlTime(WCHAR* s_time)
{
		int y, mon, d,h,minute;
		swscanf_s(s_time, _T("%d.%d.%d %d:%d"), &y, &mon, &d,&h,&minute);
		CTime time(y, mon, d, h, minute, 0);
		m_date_start.SetTime(&time);
		m_time_start.SetTime(&time);
}


CString CMFCApplication3Dlg::GetCtrlTime()
{
	CTime date,time;
	m_date_start.GetTime(date);
	m_time_start.GetTime(time);
	CString ret;
	ret.Format(_T("%d.%d.%d %d:%d"), date.GetYear(), date.GetMonth(), date.GetDay(), time.GetHour(), time.GetMinute());
	return ret;
}


void CMFCApplication3Dlg::OnBtnDelete()
{
	int nItem = -1;
	POSITION pos = m_history.GetFirstSelectedItemPosition();
	if (pos)
	{
		nItem = m_history.GetNextSelectedItem(pos);
		PySetStr(m_history.GetItemText(nItem, 4).GetBuffer(), 0);
		PySendMsg("do_delete", 0, 0);
		m_btn_delete.EnableWindow(0);
		OnRefresh();
	}
}


void CMFCApplication3Dlg::OnBnClickedButton8()
{
	CDlgHistory cdh;
	cdh.ShowHistory(m_name);
}
