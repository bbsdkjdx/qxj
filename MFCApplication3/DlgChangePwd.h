#pragma once

#include "resource.h"
// CDlgChangePwd �Ի���

class CDlgChangePwd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChangePwd)

public:
	CDlgChangePwd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChangePwd();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	int GetPasswords(CString& name, CString& oldpass, CString& newpass);
	virtual BOOL OnInitDialog();
	CString m_name;
	CString m_oldpass;
	CString m_newpass;
	CString m_newpass2;
	afx_msg void OnBnClickedOk();
	CString ChangePasswd(CString name);
};
