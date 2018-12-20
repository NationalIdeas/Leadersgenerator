// Tab2.cpp : 实现文件
//

#include "stdafx.h"
#include "LeaderGenerator.h"
#include "Tab2.h"

// CTab2 国家对话框;

IMPLEMENT_DYNAMIC(CTab2, CDialog)

CTab2::CTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CTab2::IDD, pParent)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab2, CDialog)
END_MESSAGE_MAP()

int CTab2::UpdataToMainWindow( BOOL BWriteToMainWindow )
{
	if (TRUE == BWriteToMainWindow)//TAB写到主窗口;
	{
	int check = ((CButton*) GetDlgItem(IDC_TAB2_CHECK))->GetCheck();
	if ( BST_CHECKED   == check) m_BCCCompatible = TRUE;
	if ( BST_UNCHECKED == check) m_BCCCompatible = FALSE;
	((CEdit*)GetDlgItem(IDC_TAB2_EDIT))->GetWindowTextW(m_country);
	}
	if (FALSE == BWriteToMainWindow)//主窗口写回TAB;
	{
		m_country = "USA";
		((CEdit*)GetDlgItem(IDC_TAB2_EDIT))->SetWindowTextW(m_country);
		((CButton*) GetDlgItem(IDC_TAB2_CHECK))->SetCheck(BST_CHECKED);
	
	}
	return 0;
}

BOOL CTab2::OnInitDialog()
{
	m_country.Empty();
	m_BCCCompatible = FALSE;
	CString strload;
	int retload = 0;
	retload = strload.LoadStringW(IDS_STRING421);
	((CButton*)GetDlgItem(IDC_TAB2_CHECK))->SetWindowTextW(strload);
	return TRUE;
}





void CTab2::OnCancel()
{
	return;
}


void CTab2::OnOK()
{
	return;
}
