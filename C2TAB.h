
#pragma once

#include "stdafx.h"


class C2TAB : public CDialog
{
	DECLARE_DYNAMIC(C2TAB)

public:
	C2TAB(CWnd* pParent = NULL);   // 标准构造函数;
	virtual ~C2TAB();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持;
	virtual BOOL OnInitDialog();
	
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};

BOOL C2TAB::PreTranslateMessage(MSG* pMsg)
{

	//按键按下时的回车键处理;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd *wnd = GetFocus();
		if (wnd != NULL){
			char chKey[256];
			CString ClassName = _T("Button");
			GetClassName(wnd->m_hWnd, chKey, 256);
			//按钮（Button)不执行焦点跳转;
			//构造一条WM_COMMAND消息发送给程序，让程序以为是鼠标点击了该按钮;
			if (ClassName == chKey){
				UINT i = wnd->GetDlgCtrlID();
				SendMessage(WM_COMMAND, i, (LPARAM)wnd->m_hWnd);
				return TRUE;
			}
		}
		//非按钮，即可输入控件;
		CWnd *mwnd = GetNextDlgTabItem(wnd);
		if (mwnd){
			mwnd->SetFocus();
			return TRUE;
		}
	}
	//按下ESC键;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}