#pragma once


// CDlgLogin �Ի���
#include"resource.h"
class CDlgLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLogin();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
