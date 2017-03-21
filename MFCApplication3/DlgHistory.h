#pragma once


// CDlgHistory 对话框
#include "resource.h"
#include "afxcmn.h"
class CDlgHistory : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistory)

public:
	CDlgHistory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHistory();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowHistory(CString name);
protected:
	CString m_s_name;
	CListCtrl m_list1;
	CListCtrl m_list2;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
