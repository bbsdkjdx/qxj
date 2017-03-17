// DlgChangePwd.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgChangePwd.h"
#include "afxdialogex.h"
#include "python_support.h"


// CDlgChangePwd 对话框

IMPLEMENT_DYNAMIC(CDlgChangePwd, CDialogEx)

CDlgChangePwd::CDlgChangePwd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChangePwd::IDD, pParent)
	, m_name(_T(""))
	, m_oldpass(_T(""))
	, m_newpass(_T(""))
	, m_newpass2(_T(""))
{

}

CDlgChangePwd::~CDlgChangePwd()
{
}

void CDlgChangePwd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_oldpass);
	DDX_Text(pDX, IDC_EDIT8, m_newpass);
	DDX_Text(pDX, IDC_EDIT9, m_newpass2);
}


BEGIN_MESSAGE_MAP(CDlgChangePwd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgChangePwd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgChangePwd 消息处理程序




BOOL CDlgChangePwd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_EDIT2)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgChangePwd::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (m_newpass!=m_newpass2)
	{
		AfxMessageBox(_T("两个新密码不一致，请重新输入！"));
		return;
	}

	PySetStr(m_name.GetBuffer(),0);
	PySetStr(m_oldpass.GetBuffer(),1);
	PySetStr(m_newpass.GetBuffer(),2);
	PySendMsg("change_pwd", 0, 0);
	CString ret = PyGetStr(0);
	if (ret==_T("ok"))
	{
		AfxMessageBox(_T("密码已修改！"));
	}
	else
	{
		AfxMessageBox(ret==_T("")?_T("无法连接服务器！"):ret);
		return;
	}
	UpdateData();
	CDialogEx::OnOK();
}


CString CDlgChangePwd::ChangePasswd(CString name)
{
	m_name = name;
	DoModal();
	return m_newpass;
}
