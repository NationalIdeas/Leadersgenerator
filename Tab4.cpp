// Tab4.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "LeaderGenerator.h"
#include "Tab4.h"
#include "hoi3data.h"

// CTab4 特质对话框;

//最少特质数量;
#define MINTRAITS 1
//最多特质数量;
#define MAXTRAITS 6
//推荐特质数量;
#define RECTRAITS 3

IMPLEMENT_DYNAMIC(CTab4, CDialog)

CTab4::CTab4(CWnd* pParent /*=NULL*/)
	: CDialog(CTab4::IDD, pParent)
{

}

CTab4::~CTab4()
{
}

void CTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_TAB4_EDIT1,m_edit);
}


BEGIN_MESSAGE_MAP(CTab4, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TAB4_SLIDER1, &CTab4::OnSliderChange)
	
END_MESSAGE_MAP()


BOOL CTab4::OnInitDialog()
{
	m_BNoOldGuard = TRUE;
	m_BFTMCompatible = TRUE;
	CString strload;
	int retload = strload.LoadStringW(IDS_STRING441);//没有保守派;
	((CButton*)GetDlgItem(IDC_TAB4_CHECK1))->SetWindowTextW(strload);
	retload = strload.LoadStringW(IDS_STRING442);//兼容FTM;
	((CButton*)GetDlgItem(IDC_TAB4_CHECK2))->SetWindowTextW(strload);
	retload = strload.LoadStringW(IDS_STRING443);//自定义将领特技组;
	((CButton*)GetDlgItem(IDC_TAB4_CHECK3))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB4_CHECK3))->EnableWindow(FALSE);
	retload = strload.LoadStringW(IDS_STRING444);//将领最大特技数;
	((CStatic*)GetDlgItem(IDC_TAB4_STATIC))->SetWindowTextW(strload);

	((CSliderCtrl*)GetDlgItem(IDC_TAB4_SLIDER1))->SetRange(MINTRAITS,MAXTRAITS);
	((CSliderCtrl*)GetDlgItem(IDC_TAB4_SLIDER1))->SetPos(RECTRAITS);

	retload = strload.LoadStringW(IDS_STRING445);//将领最大特技数服从;
	((CStatic*)GetDlgItem(IDC_TAB4_STATIC2))->SetWindowTextW(strload);
	retload = strload.LoadStringW(IDS_STRING446);//平均分布;
	((CButton*)GetDlgItem(IDC_TAB4_RADIO1))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB4_RADIO1))->SetCheck(BST_CHECKED);//默认;
	retload = strload.LoadStringW(IDS_STRING447);//正态分布;
	((CButton*)GetDlgItem(IDC_TAB4_RADIO2))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB4_RADIO2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_TAB4_RADIO2))->EnableWindow(TRUE);//启用正态分布;
	retload = strload.LoadStringW(IDS_STRING448);//没有分布;
	((CButton*)GetDlgItem(IDC_TAB4_RADIO3))->SetWindowTextW(strload);
	((CButton*)GetDlgItem(IDC_TAB4_RADIO3))->SetCheck(BST_UNCHECKED);




	((CEdit*)GetDlgItem(IDC_TAB4_EDIT1))->EnableWindow(FALSE);
	return TRUE;
}

int CTab4::UpdataToMainWindow( BOOL BWriteToMainWindow /*= TRUE*/ )
{
	m_BNoOldGuard = ((CButton*)GetDlgItem(IDC_TAB4_CHECK1))->GetCheck();
	m_BFTMCompatible = ((CButton*)GetDlgItem(IDC_TAB4_CHECK2))->GetCheck();
	m_BCustomTraits = ((CButton*)GetDlgItem(IDC_TAB4_CHECK3))->GetCheck();
	m_MaxTraits =  ((CSliderCtrl*)GetDlgItem(IDC_TAB4_SLIDER1))->GetPos();
	if ( BST_CHECKED == ((CButton*)GetDlgItem(IDC_TAB4_RADIO1))->GetCheck()) 
		m_TraitsDist = hoi3::dist_avg;
	if ( BST_CHECKED == ((CButton*)GetDlgItem(IDC_TAB4_RADIO2))->GetCheck()) 
		m_TraitsDist = hoi3::dist_normal;
	if ( BST_CHECKED == ((CButton*)GetDlgItem(IDC_TAB4_RADIO3))->GetCheck()) 
		m_TraitsDist = hoi3::dist_none;
	return 0;
}


void CTab4::OnSliderChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_edit = ((CSliderCtrl*)GetDlgItem(IDC_TAB4_SLIDER1))->GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}


void CTab4::OnCancel()
{
	return;
}


void CTab4::OnOK()
{
	return;
}
