#pragma once
#include "stdafx.h"
#include "resource.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// �Ի�������;
	enum { IDD = IDD_ABOUTBOX };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��;
	virtual BOOL OnInitDialog();
	int GetFileVersion();

	// ʵ��;
	DECLARE_MESSAGE_MAP()

public:
	// AboutICON;
	CStatic m_StaticIcon;
	HICON m_hIcon;
	CString m_sVersion;
	CString m_sCopyright;
	CLinkCtrl m_Link;
	afx_msg void OnNMClickStaticAboutSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};