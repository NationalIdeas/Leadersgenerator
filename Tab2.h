#pragma once


// CTab2 对话框

class CTab2 : public CDialog
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTab2();

// 对话框数据
	enum { IDD = IDD_TAB2 };
	CString m_country;
	BOOL m_BCCCompatible;//Custom Country TAG Compatible;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int UpdataToMainWindow(BOOL BWriteToMainWindow = TRUE);
	virtual void OnCancel();
	virtual void OnOK();
};
