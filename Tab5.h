#pragma once

// CTab5 �Ի���

class CTab5 : public CDialog
{
	DECLARE_DYNAMIC(CTab5)

public:
	CTab5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTab5();

// �Ի�������
	enum { IDD = IDD_TAB5 };
	int m_GenMethod;//hoi3::PictureSet;
	int m_countrytag;
	int m_pic;//;
	BOOL m_BSamepic;//ʹ��ͬ����ͷ��;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	int UpdataToMainWindow(BOOL BWriteToMainWindow = TRUE); 
	afx_msg void OnBnClickedCheck1();
	afx_msg void ChangeList1();
	
	afx_msg void OnBnClickedTab5Radio1();
	afx_msg void OnBnClickedTab5Radio2();
	virtual void OnCancel();
	virtual void OnOK();
};
