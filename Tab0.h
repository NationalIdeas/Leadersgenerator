#pragma once


// CTab0 �Ի���

class CTab0 : public CDialog
{
	DECLARE_DYNAMIC(CTab0)

public:
	CTab0(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTab0();

// �Ի�������
	enum { IDD = IDD_TAB0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
};
