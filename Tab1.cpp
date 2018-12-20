// Tab1.cpp : ʵ���ļ�;
//

#include "stdafx.h"
#include "Tab1.h"
#include "hoi3data.h"

// CTab1 �����Ի���;

IMPLEMENT_DYNAMIC(CTab1, CDialog)

CTab1::CTab1(CWnd* pParent /*=NULL*/)
	: CDialog(CTab1::IDD, pParent)
{

}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab1, CDialog)
	ON_LBN_SELCHANGE(IDC_TAB1_LIST, &CTab1::OnLbnSelchangeTab1List)
	ON_BN_CLICKED(IDC_TAB1_CHECK1, &CTab1::OnBnClickedTab1Check1)
	ON_BN_CLICKED(IDC_TAB1_CHECK2, &CTab1::OnBnClickedTab1Check2)
END_MESSAGE_MAP()

BOOL CTab1::OnInitDialog()
{
	CString strload;
	strload.Empty();
	int retload = 0 ;

	m_namestyle = 0;
	m_BHanzi = FALSE;
	m_NameFormat = 0;

	for ( int i = IDS_NAME_STYLE + 1;i < IDS_NAME_STYLE_END; i++)
	{
		retload = strload.LoadStringW( (UINT) i );
		((CListBox*)GetDlgItem(IDC_TAB1_LIST))->InsertString(i - IDS_NAME_STYLE - 1,strload);
	}
	((CListBox*)GetDlgItem(IDC_TAB1_LIST))->SetCurSel(0);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetCheck(BST_CHECKED);
	retload = strload.LoadStringW(IDS_STRING411);//��;
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->EnableWindow(TRUE);
	retload = strload.LoadStringW(IDS_STRING412);//��;
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->EnableWindow(TRUE);
	retload = strload.LoadStringW(IDS_STRING413);//ʹ�ú���;
	((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->EnableWindow(FALSE);
	return TRUE;
}

void CTab1::OnLbnSelchangeTab1List()
{
	int CurSel = 0;
	CurSel = ((CListBox*)GetDlgItem(IDC_TAB1_LIST))->GetCurSel();
	((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->EnableWindow(FALSE);
	if ( hoi3::Nordic == CurSel )
	{//nordic names only have fname;
		((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	if ( hoi3::Ukrainian == CurSel )
	{//ukrianian names only have fname;
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	if ( hoi3::Chinese == CurSel )
	{//chinese name only Hanzi;
//���޸�;
		((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_TAB1_CHECK3))->EnableWindow(FALSE);
	UpdateData(FALSE);
}

int CTab1::UpdataToMainWindow( BOOL BWriteToMainWindow )
{
	m_namestyle = ((CListBox*)GetDlgItem(IDC_TAB1_LIST))->GetCurSel();
	//���޸�;
	int m = 0;
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->GetCheck()) m+=1;
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->GetCheck()) m+= 10;
	switch(m)
	{//switch start;
	case 0:
		//����;
		break;
	case 1:
		m_NameFormat = hoi3::onlyfamilyname;
		break;
	case 10:
		m_NameFormat = hoi3::onlygivenname;
		break;
	case 11:
		m_NameFormat = hoi3::fullname;
		break;
	default:
		//����;
		break;
	}//switch end;
	m_BHanzi = ((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->GetCheck();
	return 0;
}

void CTab1::OnBnClickedTab1Check1()
{//��;
    if ( hoi3::Nordic == m_namestyle || hoi3::Ukrainian == m_namestyle) return;

	if ( BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->GetCheck() )
	((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->SetCheck(BST_CHECKED);
}

void CTab1::OnBnClickedTab1Check2()
{//��;
    if ( hoi3::Nordic == m_namestyle || hoi3::Ukrainian == m_namestyle) return;

    if ( BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_TAB1_CHECK1))->GetCheck() )
    ((CButton*)GetDlgItem(IDC_TAB1_CHECK2))->SetCheck(BST_CHECKED);
}


void CTab1::OnCancel()
{
	return;
}


void CTab1::OnOK()
{
	return;
}