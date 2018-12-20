#pragma once


// CTab3 对话框

class CTab3 : public CDialog
{
	DECLARE_DYNAMIC(CTab3)

public:
	CTab3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTab3();

// 对话框数据
	enum { IDD = IDD_TAB3 };
	int m_iMaxPotentialSkill;//资质最大值;
	BOOL m_BSkillBeforeName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	int m_slider;// value of slider;
	int m_edit;//value of edit;

public:
	int UpdataToMainWindow(BOOL BWriteToMainWindow = TRUE); 
	
	afx_msg void OnSliderChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditChange();
	virtual void OnCancel();
	virtual void OnOK();
};
