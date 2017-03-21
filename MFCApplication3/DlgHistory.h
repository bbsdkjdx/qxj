#pragma once


// CDlgHistory �Ի���
#include "resource.h"
#include "afxcmn.h"
class CDlgHistory : public CDialog
{
	DECLARE_DYNAMIC(CDlgHistory)

public:
	CDlgHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistory();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
