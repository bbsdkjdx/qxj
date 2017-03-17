// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLogin::IDD, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������


bool CDlgLogin::ShowLogin(CString & username, CString & password)
{
	m_username = username;
	m_password = password;
	int ret = DoModal();
	username = m_username;
	password = m_password;
	return ret==IDOK;
}


BOOL CDlgLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit *pe = (CEdit *)GetDlgItem(IDC_EDIT1);
	pe->SetFocus();
	pe->SetSel(0, -1);
	UpdateData(FALSE);
	
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgLogin::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
