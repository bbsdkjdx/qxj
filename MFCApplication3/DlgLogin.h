#pragma once


// CDlgLogin 对话框
#include"resource.h"
class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool ShowLogin(CString & username, CString & password);
protected:
	CString m_username;
	CString m_password;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
