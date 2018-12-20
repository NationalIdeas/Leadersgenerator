#pragma once


// CTab0 对话框

class CTab0 : public CDialog
{
	DECLARE_DYNAMIC(CTab0)

public:
	CTab0(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTab0();

// 对话框数据
	enum { IDD = IDD_TAB0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
};
