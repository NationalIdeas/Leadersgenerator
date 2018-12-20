#pragma once


// CTab4 对话框

class CTab4 : public CDialog
{
	DECLARE_DYNAMIC(CTab4)

public:
	CTab4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTab4();

// 对话框数据
	enum { IDD = IDD_TAB4 };
	BOOL m_BNoOldGuard;//没有保守派;
	BOOL m_BFTMCompatible;//兼容FTM;
	BOOL m_BCustomTraits;//自定义特技组;
	int m_MaxTraits;//将领最多特技个数;
	int m_TraitsDist;//将领特技分布函数;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	int m_edit;
public:
	int UpdataToMainWindow(BOOL BWriteToMainWindow = TRUE); 
	
	afx_msg void OnSliderChange(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnCancel();
	virtual void OnOK();
};
