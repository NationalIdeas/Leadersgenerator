#pragma once


// CTab4 �Ի���

class CTab4 : public CDialog
{
	DECLARE_DYNAMIC(CTab4)

public:
	CTab4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTab4();

// �Ի�������
	enum { IDD = IDD_TAB4 };
	BOOL m_BNoOldGuard;//û�б�����;
	BOOL m_BFTMCompatible;//����FTM;
	BOOL m_BCustomTraits;//�Զ����ؼ���;
	int m_MaxTraits;//��������ؼ�����;
	int m_TraitsDist;//�����ؼ��ֲ�����;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��;
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
