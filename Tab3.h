#pragma once


// CTab3 �Ի���

class CTab3 : public CDialog
{
	DECLARE_DYNAMIC(CTab3)

public:
	CTab3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTab3();

// �Ի�������
	enum { IDD = IDD_TAB3 };
	int m_iMaxPotentialSkill;//�������ֵ;
	BOOL m_BSkillBeforeName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
