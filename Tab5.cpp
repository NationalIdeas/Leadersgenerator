// Tab5.cpp : 实现文件
//

#include "stdafx.h"
#include "LeaderGenerator.h"
#include "Tab5.h"
#include "hoi3data.h"

// CTab5 头像对话框;

IMPLEMENT_DYNAMIC(CTab5, CDialog)

CTab5::CTab5(CWnd* pParent /*=NULL*/)
	: CDialog(CTab5::IDD, pParent)
	, m_pic(0)
	, m_BSamepic(FALSE)
{

}

CTab5::~CTab5()
{
}

void CTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TAB5_EDIT1, m_pic);
	DDX_Check(pDX, IDC_TAB5_CHECK1, m_BSamepic);
}


BEGIN_MESSAGE_MAP(CTab5, CDialog)
	ON_BN_CLICKED(IDC_TAB5_CHECK1, &CTab5::OnBnClickedCheck1)
	ON_LBN_SELCHANGE(IDC_TAB5_LIST1, &CTab5::ChangeList1)
	ON_BN_CLICKED(IDC_TAB5_RADIO1, &CTab5::OnBnClickedTab5Radio1)
	ON_BN_CLICKED(IDC_TAB5_RADIO2, &CTab5::OnBnClickedTab5Radio2)
END_MESSAGE_MAP()

BOOL CTab5::OnInitDialog()
{
	int retload = 0;
	CString strload;
	strload.Empty();
	
	retload = strload.LoadStringW(IDS_STRING451);//顺序生成;
	((CStatic*)GetDlgItem(IDC_TAB5_GROUP1))->SetWindowTextW(strload);
	retload = strload.LoadStringW(IDS_STRING452);//使用现有将领头像;
	((CStatic*)GetDlgItem(IDC_TAB5_GROUP2))->SetWindowTextW(strload);
	retload = strload.LoadStringW(IDS_STRING453);//头像ID号;
	((CStatic*)GetDlgItem(IDC_TAB5_STATIC))->SetWindowTextW(strload);

	retload = strload.LoadStringW(IDS_STRING454);//使用同一个头像;
	((CButton*)GetDlgItem(IDC_TAB5_CHECK1))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB5_CHECK1))->SetCheck(BST_UNCHECKED);
	((CEdit*)GetDlgItem(IDC_TAB5_EDIT1))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_TAB5_EDIT1))->SetWindowText(_T("590000"));

	retload = strload.LoadStringW(IDS_STRING455);//生成;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO1))->SetWindowTextW(strload);
	
	//Radio1 and Radio2 are MUTUALLY EXCLUSIVE!!!;
	//Radio1 for Generate;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO1))->SetCheck(BST_CHECKED);
	//Radio2 for UsePack;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO2))->SetCheck(BST_UNCHECKED);

	retload = strload.LoadStringW(IDS_STRING456);//使用现有;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO2))->SetWindowTextW(strload);

	retload = strload.LoadStringW(IDS_STRING457);//空;
	((CStatic*)GetDlgItem(IDC_TAB5_STATIC2))->SetWindowTextW(strload);
	for (int i = 0;i < 5;i++)
	{
		retload = strload.LoadStringW(IDS_TAG1 + (UINT) i);//待修改;
		((CListBox*)GetDlgItem(IDC_TAB5_LIST1))->InsertString(i,strload);	
	}
	//listbox;
	((CListBox*)GetDlgItem(IDC_TAB5_LIST1))->EnableWindow(TRUE);
	((CListBox*)GetDlgItem(IDC_TAB5_LIST1))->SetCurSel(0);

	return TRUE;
}

int CTab5::UpdataToMainWindow( BOOL BWriteToMainWindow /*= TRUE*/ )
{
	UpdateData(TRUE);
	//radio button;
	int radio1 = ((CButton*)GetDlgItem(IDC_TAB5_RADIO1))->GetCheck();
	int radio2 = ((CButton*)GetDlgItem(IDC_TAB5_RADIO2))->GetCheck();
	int checkx = ((CButton*)GetDlgItem(IDC_TAB5_CHECK1))->GetCheck();

	if ( BST_UNCHECKED == radio1 && BST_UNCHECKED == radio2) return 1;
	if ( BST_CHECKED == checkx)
	{
		m_BSamepic = TRUE;
	}else
	{
		m_BSamepic = FALSE;
	}
	if ( BST_CHECKED == radio1)
	{//顺序生成;
		m_GenMethod = hoi3::PGM_GeneratePortraitID;
		m_countrytag = 0;
	}
	if ( BST_CHECKED == radio2)
	{//使用头像包;
		m_GenMethod = hoi3::PGM_UsePortraitPack;
		m_countrytag = ((CListBox*)GetDlgItem(IDC_TAB5_LIST1))->GetCurSel()+1;
	}
	

	return 0;
}

void CTab5::OnBnClickedCheck1()
{
	if ( BST_CHECKED == ((CButton*)GetDlgItem(IDC_TAB5_CHECK1))->GetCheck() )
	{
		((CEdit*)GetDlgItem(IDC_TAB5_EDIT1))->EnableWindow(TRUE);
		return;
	}
	((CEdit*)GetDlgItem(IDC_TAB5_EDIT1))->EnableWindow(FALSE);


}

void CTab5::ChangeList1()
{
	UpdateData(TRUE);
	m_countrytag = ((CListBox*)GetDlgItem(IDC_TAB5_LIST1))->GetCurSel();	

	//Radio1 and Radio2 are MUTUALLY EXCLUSIVE!!!;
	//Radio1 for Generate;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO1))->SetCheck(BST_UNCHECKED);
	//Radio2 for UsePack;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO2))->SetCheck(BST_CHECKED);
}


void CTab5::OnBnClickedTab5Radio1()
{
	//Radio1 and Radio2 are MUTUALLY EXCLUSIVE!!!;
	//Radio1 for Generate;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO1))->SetCheck(BST_CHECKED);
	//Radio2 for UsePack;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO2))->SetCheck(BST_UNCHECKED);
}


void CTab5::OnBnClickedTab5Radio2()
{
	//Radio1 and Radio2 are MUTUALLY EXCLUSIVE!!!;
	//Radio1 for Generate;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO1))->SetCheck(BST_UNCHECKED);
	//Radio2 for UsePack;
	((CButton*)GetDlgItem(IDC_TAB5_RADIO2))->SetCheck(BST_CHECKED);
}

void CTab5::OnCancel()
{
	return ;
}


void CTab5::OnOK()
{
	return;
}
