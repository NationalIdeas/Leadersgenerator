
#pragma once

#include "stdafx.h"


class C2TAB : public CDialog
{
	DECLARE_DYNAMIC(C2TAB)

public:
	C2TAB(CWnd* pParent = NULL);   // ��׼���캯��;
	virtual ~C2TAB();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��;
	virtual BOOL OnInitDialog();
	
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};

BOOL C2TAB::PreTranslateMessage(MSG* pMsg)
{

	//��������ʱ�Ļس�������;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd *wnd = GetFocus();
		if (wnd != NULL){
			char chKey[256];
			CString ClassName = _T("Button");
			GetClassName(wnd->m_hWnd, chKey, 256);
			//��ť��Button)��ִ�н�����ת;
			//����һ��WM_COMMAND��Ϣ���͸������ó�����Ϊ��������˸ð�ť;
			if (ClassName == chKey){
				UINT i = wnd->GetDlgCtrlID();
				SendMessage(WM_COMMAND, i, (LPARAM)wnd->m_hWnd);
				return TRUE;
			}
		}
		//�ǰ�ť����������ؼ�;
		CWnd *mwnd = GetNextDlgTabItem(wnd);
		if (mwnd){
			mwnd->SetFocus();
			return TRUE;
		}
	}
	//����ESC��;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}