// Export.cpp : 实现文件
//
#include "stdafx.h"
#include "LeaderGenerator.h"
#include "PortSettings.h"


IMPLEMENT_DYNAMIC(CSETTINGS, CDialog)

CSETTINGS::CSETTINGS():CDialog(CSETTINGS::IDD)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAINFRAME);
}

CSETTINGS::~CSETTINGS()
{
}
void CSETTINGS::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSETTINGS, CDialog)
    ON_BN_CLICKED(IDC_SET_BUTTON2, &CSETTINGS::OnBnClickedIMPORT)
    ON_BN_CLICKED(IDC_SET_BUTTON1, &CSETTINGS::OnBnClickedEXPORT)
    ON_BN_CLICKED(IDC_SET_BUTTON3, &CSETTINGS::OnBnClickedRETURN)
    ON_NOTIFY(TVN_SELCHANGED, IDC_SET_TREE, &CSETTINGS::OnTvnSelchangedTree)
END_MESSAGE_MAP()

BOOL CSETTINGS::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->SetIcon(m_hIcon,FALSE);
	this->SetIcon(m_hIcon,TRUE);

    m_portways = hoi3::NonSet;

    CString strload;
    int retload = 0;

    CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_SET_TREE);
    pTree->ModifyStyle(NULL,TVS_CHECKBOXES | TVS_HASBUTTONS | TVS_HASLINES | TVS_INFOTIP |TVS_LINESATROOT | TVS_NOHSCROLL);

    retload = strload.LoadStringW(IDS_TREE_SETI);
    HTREEITEM hRoot = pTree->InsertItem(strload.GetBuffer(),TVI_ROOT,TVI_LAST);
    for (int i = 0;i < 4 ; i++ )
    {
        retload = strload.LoadStringW(IDS_TREE_SETI + 1 + i);
        HTREEITEM hItem = pTree->InsertItem(strload.GetBuffer(),hRoot,TVI_LAST);
//         if ( 0 == i || 1 == i )
//         {
//             for (int j = 0; j < (IDS_NAME_STYLE_END - IDS_NAME_STYLE) ; j++)
//             {
//                 retload = strload.LoadStringW(IDS_NAME_STYLE + 1 + j);
//                 HTREEITEM hStyle = pTree->InsertItem(strload.GetBuffer(),hItem,TVI_LAST);
//             }
//        }
    }
    
    retload = strload.LoadStringW(IDS_STRING411);
    HTREEITEM h2 = pTree->InsertItem(_T("root2"),TVI_ROOT,TVI_LAST);

    pTree->Expand(hRoot,TVE_EXPAND);//必须有否则树形控件不展开;
	return TRUE;
}




void CSETTINGS::OnBnClickedIMPORT()
{
    if ( hoi3::ExportSet == m_portways) return;
    ((CStatic*)GetDlgItem(IDC_SET_OUT))->SetWindowText(_T("导入成功!"));
}

void CSETTINGS::OnBnClickedEXPORT()
{
    if ( hoi3::ImportSet == m_portways) return;
    ((CStatic*)GetDlgItem(IDC_SET_OUT))->SetWindowText(_T("导出成功!"));
}

void CSETTINGS::OnBnClickedRETURN()
{
    this->OnCancel();
}

int CSETTINGS::PortSettings( const int& portway /*= hoi3::ExportSet*/ )
{
    switch(portway)
    {
    case hoi3::ImportSet:
        m_portways = hoi3::ImportSet;
        break;
    case hoi3::ExportSet:
        m_portways = hoi3::ExportSet;
        break;
    case hoi3::NonSet:
        m_portways = hoi3::NonSet;
        break;
    default:
        m_portways = hoi3::NonSet;
        break;
    }
    return 0;
}

void CSETTINGS::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_SET_TREE);
    TVITEM TVItemNew = pNMTreeView->itemNew;
    HTREEITEM hItem = TVItemNew.hItem;
    pTree->SelectItem(hItem);

    *pResult = 0;
}
