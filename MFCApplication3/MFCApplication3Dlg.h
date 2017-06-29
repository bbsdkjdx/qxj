
// MFCApplication3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "CmdEdit.h"
#include "afxdtctl.h"

const int WM_QuitForUpgrade = 44444;

class CMFCApplication3Dlg : public CDialogEx
{
public:
	CMFCApplication3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION3_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LRESULT TrayFunction(WPARAM wp, LPARAM lp); 
public:
	NOTIFYICONDATA m_tnid;
public:
	virtual BOOL DestroyWindow();
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnNcPaint();
public:
	bool m_can_show;
	afx_msg LRESULT OnTaskbarrestart(WPARAM wParam, LPARAM lParam);
//	void SetCurrentDir();
	void Quit();
protected:
//	CString m_code;
//	CString m_result;
//	CCmdEdit m_code_edit;
	HWND m_nextClipboardViewer;
	bool m_isListenClipboard;
public:
//	afx_msg void OnSetfocusEdit1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ListenClipboard(bool enable);
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDrawClipboard();
	bool SetTrayIcon(WCHAR* fn);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	bool m_block_msg;
	afx_msg void OnLogIn();
protected:
	CButton m_btn_login;
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CListCtrl m_history;
	afx_msg void OnRefresh();
	afx_msg void OnCustomdrawHistory(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	bool SvrLogIn(wchar_t* un, wchar_t* pw);
public:
	afx_msg void OnEnChangeEdit5();
protected:
	void ShowDetail();
public:
	CEdit m_proposer;
	CEdit m_approver;
	CDateTimeCtrl m_date_start;
	CDateTimeCtrl m_time_start;
	CComboBox m_type;
	CEdit m_reason;
	CComboBox m_allow;
	CEdit m_comment;
	CButton m_btn_submit;
//	CButton m_btn_propose;
	afx_msg void OnSubmit();
	afx_msg void OnDoBack();
protected:
	CButton m_btn_back;
public:
	afx_msg void OnPropose();
	CString m_name;
	afx_msg void OnChangePassWd();
protected:
	CWinThread *m_notify_thd;
public:
	bool m_need_notify;

//	int SelectHistory(int idx);
	CComboBox m_hours;
	void SetCtrlTime(WCHAR* s_time);
	CString GetCtrlTime();
	afx_msg void OnBtnDelete();
protected:
	CButton m_btn_delete;
public:
	afx_msg void OnBnClickedButton8();
	CButton m_btn_propose;
	void ShowBubble(CString info);
protected:
	afx_msg LRESULT OnQuitforupgrade(WPARAM wParam, LPARAM lParam);
};
