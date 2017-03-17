// CmdEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "CmdEdit.h"


// CCmdEdit

IMPLEMENT_DYNAMIC(CCmdEdit, CEdit)

CCmdEdit::CCmdEdit()
{

}

CCmdEdit::~CCmdEdit()
{
}


BEGIN_MESSAGE_MAP(CCmdEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CCmdEdit 消息处理程序




void CCmdEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 13){}//enter. treat in PreTranslateMessage.

	if (nChar==8)//backspace.
	{
		return;
	}

	if (nChar==9)//tab.replace tab to 4 spaces.
	{
		int nPos = LOWORD(CharFromPos(GetCaretPos()));
		SetSel(nPos, nPos);
		ReplaceSel(_T("    "), TRUE);
		return;
	}

	//int pos = CharFromPos(GetCaretPos());
	//CString str;
	//str.Format(_T("%d"),nChar);
	//GetForegroundWindow()->SetWindowTextW(str);

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CCmdEdit::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message)
	{
		WCHAR line[1000] = { 0 };
		int nPos = (CharFromPos(GetCaretPos()));
		int ln_cur = nPos >> 16;
		//ln_cur = ln_cur > 0 ? ln_cur - 1 : ln_cur;
		int nl = GetLine(ln_cur, line, 1000 - 1);

		if (VK_RETURN == pMsg->wParam)
		{
			if (nl == 0)//run code when press enter at a blank line.
			{
				GetParent()->SendMessage(WM_COMMAND, IDOK, 0);
				CString tmp;
				GetWindowText(tmp);
				SetSel(0, -1);
				return true;
			}

			//auto indent.
			WCHAR buf[1000] = _T("\r\n");
			int nidnt = GetNewIndent(line);
			for (int x = 0; x < nidnt;++x)
			{
				buf[x + 2] = 32;
			}
			buf[nidnt + 2] = 0;
			ReplaceSel(buf, TRUE);
			return true;

			//CString str;
			//str.Format(_T("%d"),GetNewIndent(line));
			//GetForegroundWindow()->SetWindowTextW(str);
			//return CEdit::PreTranslateMessage(pMsg);
		}

		if (VK_BACK==pMsg->wParam)
		{
			CString str;
			GetWindowText(str);
			int nPos = LOWORD(CharFromPos(GetCaretPos()));
			if (str.GetLength()>3 && str.Mid(nPos-4,4)==_T("    "))
			{
				SetSel(nPos - 4, nPos);
				ReplaceSel(_T(""), TRUE);
				return true;
			}
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}


int CCmdEdit::GetNewIndent(WCHAR* lastline)
{
	bool all_space = true;
	for (int x = 0; lastline[x] != 0;++x)
	{
		if (lastline[x]!=32)
		{
			all_space = false;
			break;
		}
	}
	if (all_space)
	{
		return 0;
	}
	int nsp = 0;
	WCHAR lastchar = 0;
	for (; lastline[nsp] == 32; ++nsp);
	if (lastline[wcslen(lastline)-1]==':')
	{
		nsp += 4;
	}
	return nsp;
}
