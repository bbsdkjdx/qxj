// DlgHistory.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgHistory.h"
#include "afxdialogex.h"
#include "python_support.h"


// CDlgHistory �Ի���

IMPLEMENT_DYNAMIC(CDlgHistory, CDialog)

CDlgHistory::CDlgHistory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistory::IDD, pParent)
	, m_s_name(_T(""))
{

}

CDlgHistory::~CDlgHistory()
{
}

void CDlgHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
}


BEGIN_MESSAGE_MAP(CDlgHistory, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgHistory::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDlgHistory::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CDlgHistory ��Ϣ�������


void CDlgHistory::ShowHistory(CString name)
{
	m_s_name = name;
	DoModal();
}

CListCtrl *pli1=nullptr, *pli2=nullptr;

void clear_list(int n)
{
	if (n==0)
	{
		pli1->DeleteAllItems();
	}
	else
	{
		pli2->DeleteAllItems();
	}
}

void insert_list1(int n,WCHAR *s1, WCHAR *s2, WCHAR *s3, WCHAR *s4)
{
	pli1->InsertItem(n, s1);
	pli1->SetItemText(n, 1, s2);
	pli1->SetItemText(n, 2, s3);
	pli1->SetItemText(n, 3, s4);
}
void insert_list2(int n, WCHAR *s1, WCHAR *s2, WCHAR *s3, WCHAR *s4, WCHAR *s5, WCHAR *s6, WCHAR *s7, WCHAR *s8, WCHAR *s9)
{
	pli2->InsertItem(n, s1);
	pli2->SetItemText(n, 1, s2);
	pli2->SetItemText(n, 2, s3);
	pli2->SetItemText(n, 3, s4);
	pli2->SetItemText(n, 4, s5);
	pli2->SetItemText(n, 5, s6);
	pli2->SetItemText(n,6, s7);
	pli2->SetItemText(n, 7, s8);
	pli2->SetItemText(n, 8, s9);
}


BOOL CDlgHistory::OnInitDialog()
{
	CDialog::OnInitDialog();

	REG_EXE_FUN(clear_list, "#l", "");
	REG_EXE_FUN(insert_list1, "#lSSSS", "");
	REG_EXE_FUN(insert_list2, "#lSSSSSSSSS", "");

	pli1 = &m_list1;
	pli2 = &m_list2;
	DWORD dwStyle = m_list1.GetExtendedStyle();    //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT;                //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES;                    //�����ߣ�report���ʱ��
	m_list1.SetExtendedStyle(dwStyle);            //������չ���
	m_list2.SetExtendedStyle(dwStyle);            //������չ���

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list1.InsertColumn(0, _T("�����"), 0, 50);
	m_list1.InsertColumn(1, _T("�¼ٺϼ�"), 0, 150);
	m_list1.InsertColumn(2, _T("����ϼ�"), 0, 150);
	m_list1.InsertColumn(3, _T("�ܼ�"), 0, 150);

	m_list2.InsertColumn(0, _T("�����"),0,50);
	m_list2.InsertColumn(1, _T("������"), 0, 50);
	m_list2.InsertColumn(2, _T("���ʱ��"), 0, 110);
	m_list2.InsertColumn(3, _T("ʱ��(h)"), 0, 50);
	m_list2.InsertColumn(4, _T("���"), 0, 50);
	m_list2.InsertColumn(5, _T("����"), 0, 120);
	m_list2.InsertColumn(7, _T("׼��"), 0, 50);
	m_list2.InsertColumn(8, _T("��ʾ"), 0, 120);
	m_list2.InsertColumn(9, _T("����ʱ��"), 0, 110);

	PySendMsg("get_history", 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgHistory::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void CDlgHistory::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CString name;
	POSITION pos = m_list1.GetFirstSelectedItemPosition();
	if (pos)
	{
		name = m_list1.GetItemText(m_list1.GetNextSelectedItem(pos), 0);
	}

	PySendMsg("show_history_detail", unsigned(name.GetBuffer()), 0);

	*pResult = 0;
}
