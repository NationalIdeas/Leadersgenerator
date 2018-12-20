// Tab3.cpp : 实现文件
//

#include "stdafx.h"
#include "LeaderGenerator.h"
#include "Tab3.h"


// CTab3 技能对话框

IMPLEMENT_DYNAMIC(CTab3, CDialog)

CTab3::CTab3(CWnd* pParent /*=NULL*/)
	: CDialog(CTab3::IDD, pParent)
	, m_slider(0)
{

}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_TAB3_SLIDER1, m_slider);
	DDX_Text(pDX,IDC_TAB3_EDIT1,m_edit);
}


BEGIN_MESSAGE_MAP(CTab3, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TAB3_SLIDER1, &CTab3::OnSliderChange)
	ON_EN_CHANGE(IDC_TAB3_EDIT1, &CTab3::OnEditChange)
END_MESSAGE_MAP()

BOOL CTab3::OnInitDialog()
{
	CString strload;
	int retload = 0;
	retload = strload.LoadStringW(IDS_STRING431);
	((CButton*)GetDlgItem(IDC_TAB3_CHECK1))->SetWindowTextW(strload);//资质显示在姓名前;
	((CButton*)GetDlgItem(IDC_TAB3_CHECK1))->SetCheck(TRUE);
	retload = strload.LoadStringW(IDS_STRING432);
	((CStatic*)GetDlgItem(IDC_TAB3_STATIC))->SetWindowTextW(strload);//Label;
	retload = strload.LoadStringW(IDS_STRING433);
	((CStatic*)GetDlgItem(IDC_TAB3_CHECK2))->SetWindowTextW(strload);//将领资质最大值随机化;
	((CButton*)GetDlgItem(IDC_TAB3_CHECK2))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_TAB3_CHECK2))->EnableWindow(FALSE);
	((CSliderCtrl*)GetDlgItem(IDC_TAB3_SLIDER1))->SetRange(0,10);
	m_iMaxPotentialSkill = 3;
	m_slider = 3;
	m_edit = 3;
	UpdateData(FALSE);
	return TRUE;
}

int CTab3::UpdataToMainWindow( BOOL BWriteToMainWindow /*= TRUE*/ )
{
	int check = ((CButton*)GetDlgItem(IDC_TAB3_CHECK1))->GetCheck();
	(BST_CHECKED == check )? m_BSkillBeforeName = TRUE : m_BSkillBeforeName = FALSE;
	CString strload;
	int retload;
	retload	= strload.LoadStringW(IDS_STRING531);//Edit控件和Slider控件出错;
	if ( m_edit != m_slider)
	{
		AfxMessageBox(strload,MB_ICONEXCLAMATION);
	}
	m_iMaxPotentialSkill = m_edit;
	return 0;
}


void CTab3::OnSliderChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	m_iMaxPotentialSkill = m_edit;
	m_edit = m_slider;
	UpdateData(FALSE);
	*pResult = 0;
}

void CTab3::OnEditChange()
{
	UpdateData(TRUE);
	m_iMaxPotentialSkill = m_edit;
	m_slider = m_edit;
	UpdateData(FALSE);
}


void CTab3::OnCancel()
{
	return;
}


void CTab3::OnOK()
{
	return;
}
