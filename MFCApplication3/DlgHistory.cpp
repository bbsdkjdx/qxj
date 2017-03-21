// DlgHistory.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgHistory.h"
#include "afxdialogex.h"
#include "python_support.h"


// CDlgHistory 对话框

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


// CDlgHistory 消息处理程序


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
	DWORD dwStyle = m_list1.GetExtendedStyle();    //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT;                //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES;                    //网格线（report风格时）
	m_list1.SetExtendedStyle(dwStyle);            //设置扩展风格
	m_list2.SetExtendedStyle(dwStyle);            //设置扩展风格

	// TODO:  在此添加额外的初始化
	m_list1.InsertColumn(0, _T("请假人"), 0, 50);
	m_list1.InsertColumn(1, _T("事假合计"), 0, 150);
	m_list1.InsertColumn(2, _T("公差合计"), 0, 150);
	m_list1.InsertColumn(3, _T("总计"), 0, 150);

	m_list2.InsertColumn(0, _T("请假人"),0,50);
	m_list2.InsertColumn(1, _T("批假人"), 0, 50);
	m_list2.InsertColumn(2, _T("请假时间"), 0, 110);
	m_list2.InsertColumn(3, _T("时长(h)"), 0, 50);
	m_list2.InsertColumn(4, _T("类别"), 0, 50);
	m_list2.InsertColumn(5, _T("事由"), 0, 120);
	m_list2.InsertColumn(7, _T("准假"), 0, 50);
	m_list2.InsertColumn(8, _T("批示"), 0, 120);
	m_list2.InsertColumn(9, _T("销假时间"), 0, 110);

	PySendMsg("get_history", 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgHistory::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
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
