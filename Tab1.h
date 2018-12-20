#pragma once
#include "resource.h"
// CTab1 对话框;

class CTab1 : public CDialog
{
	DECLARE_DYNAMIC(CTab1)
public:
	CTab1(CWnd* pParent = NULL);   // 标准构造函数;
	virtual ~CTab1();

// 对话框数据;
	enum { IDD = IDD_TAB1 };

	int  m_namestyle;
	int  m_NameFormat;
	BOOL m_BHanzi;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持;
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int UpdataToMainWindow( BOOL BWriteToMainWindow = TRUE);
	afx_msg void OnLbnSelchangeTab1List();
	afx_msg void OnBnClickedTab1Check1();
	afx_msg void OnBnClickedTab1Check2();
	virtual void OnCancel();
	virtual void OnOK();
};
