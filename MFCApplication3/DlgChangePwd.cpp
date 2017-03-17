// DlgChangePwd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgChangePwd.h"
#include "afxdialogex.h"
#include "python_support.h"


// CDlgChangePwd �Ի���

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


// CDlgChangePwd ��Ϣ�������




BOOL CDlgChangePwd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_EDIT2)->SetFocus();
	UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgChangePwd::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if (m_newpass!=m_newpass2)
	{
		AfxMessageBox(_T("���������벻һ�£����������룡"));
		return;
	}

	PySetStr(m_name.GetBuffer(),0);
	PySetStr(m_oldpass.GetBuffer(),1);
	PySetStr(m_newpass.GetBuffer(),2);
	PySendMsg("change_pwd", 0, 0);
	CString ret = PyGetStr(0);
	if (ret==_T("ok"))
	{
		AfxMessageBox(_T("�������޸ģ�"));
	}
	else
	{
		AfxMessageBox(ret==_T("")?_T("�޷����ӷ�������"):ret);
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
