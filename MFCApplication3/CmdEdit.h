#pragma once


// CCmdEdit

class CCmdEdit : public CEdit
{
	DECLARE_DYNAMIC(CCmdEdit)

public:
	CCmdEdit();
	virtual ~CCmdEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	int GetNewIndent(WCHAR* lastline);
};


