// musicfiles.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LeaderGenerator.h"
#include "musicfiles.h"
 

#define FACTORCOL 50
#define MAXFACTORS 6

IMPLEMENT_DYNAMIC(CMusicFiles, CDialog)

CMusicFiles::CMusicFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicFiles::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAINFRAME);
}

CMusicFiles::~CMusicFiles()
{
}

void CMusicFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    
}

BEGIN_MESSAGE_MAP(CMusicFiles, CDialog)
    ON_BN_CLICKED(IDC_MFILE_BTN1, &CMusicFiles::OnBnClickedSave)
    ON_BN_CLICKED(IDC_MFILE_BTN2, &CMusicFiles::OnBnClickedCancel)
    ON_COMMAND(IDM_MFILE_CUT, &CMusicFiles::OnCut)
    ON_COMMAND(IDM_MFILE_COPY, &CMusicFiles::OnCopy)
    ON_COMMAND(IDM_MFILE_PASTE, &CMusicFiles::OnPaste)
    ON_COMMAND(IDM_MFILE_INSERT, &CMusicFiles::OnInsert)
    ON_EN_SETFOCUS(IDC_MFILE_EDIT1, &CMusicFiles::OnSetfocusEdit1)
    ON_BN_CLICKED(IDC_MFILE_BTN3, &CMusicFiles::OnSaveToControl)
    ON_NOTIFY(TVN_SELCHANGED, IDC_MFILE_TREE1, &CMusicFiles::OnTvnSelChanged)
    ON_NOTIFY(NM_RCLICK, IDC_MFILE_TREE1, &CMusicFiles::OnNMRClickTree1)
END_MESSAGE_MAP()

BOOL CMusicFiles::OnInitDialog()
{//�ڴ�֮ǰ��ִ��Import����;	
    CDialog::OnInitDialog();
    this->SetIcon(m_hIcon,FALSE);
    this->SetIcon(m_hIcon,TRUE);

    CString strload;
    int retload = 0;

    strload = _T("����Ҫ����");
    ((CStatic*)GetDlgItem(IDC_MFILE_NOTES))->SetWindowTextW(strload.GetBuffer());

    strload = _T("���ڴ�����factor�ڵĴ���");
    ((CEdit*)GetDlgItem(IDC_MFILE_EDIT1))->SetWindowTextW(strload.GetBuffer());

    CTreeCtrl* pTree = ((CTreeCtrl*)GetDlgItem(IDC_MFILE_TREE1));
    pTree->ModifyStyle(NULL,TVS_HASBUTTONS);
    strload =_T("����mp3�ļ�");
    HTREEITEM hRoot = pTree->InsertItem(strload.GetBuffer(),TVI_ROOT,TVI_LAST);
    
    for (int i = 0 ;i < m_filenames.GetCount(); i++)
    {
        CString tmp = m_filenames.GetAt(i); 

        //add to tree;
        HTREEITEM hSong = pTree->InsertItem(tmp.GetBuffer(),hRoot,TVI_LAST);
        pTree->SetItem(hSong,TVIF_CHILDREN | TVIF_STATE |TVIF_PARAM ,tmp.GetBuffer(),0,0,TVIS_EXPANDPARTIAL,TVIS_SELECTED,(LPARAM) one);

        tmp = _T("��������");
        TVITEM TVItemModifier;
        TVItemModifier.mask = TVIF_TEXT;
        TVItemModifier.pszText =  tmp.GetBuffer();

        TVINSERTSTRUCT InsertItem;
        InsertItem.hParent = hSong;
        InsertItem.hInsertAfter = TVI_LAST;
        InsertItem.item = TVItemModifier;
        
        HTREEITEM hModifier = pTree->InsertItem(&InsertItem);


    }
    pTree->Expand(hRoot,TVE_EXPAND);//�����з������οؼ���չ��;
    return TRUE;
}

int CMusicFiles::ImportFileNames(const CStringArray& filenames )
{//��ʱ�Ի�����δ����;
    m_filenames.RemoveAll();

    CString strload;
    for (int i = 0 ;i < filenames.GetCount(); i++)
    {//�����ַ���;
        strload = filenames.GetAt(i);
        int index = strload.ReverseFind(_T('\\'));
        int size = strload.GetLength();
        CString tmp = strload.Right(size - index - 1);
        m_filenames.Add(tmp);
    }
    return 0;
}


afx_msg void CMusicFiles::OnBnClickedSave()
{
    CStdioFile songfile;
    CString filename;
    int ret = 0;
    errno_t err = 0;
    CString strload;
    int retload = 0;

    strload = _T("f");
    filename = m_path + _T("song.txt");

    if ( FALSE == songfile.Open(filename.GetBuffer(),CFile::modeWrite | CFile::modeCreate | CFile::typeText))
    {
        strload = _T("error!");//д���ļ�����;
        AfxMessageBox(strload.GetBuffer(),MB_ICONEXCLAMATION);
        return;
    }

    CString sline;
    for (int i = 0;i < m_filenames.GetCount(); i++ )
    {//write file;
        sline = _T("song = {\r\n");
        songfile.WriteString(sline.GetBuffer());
        CString tmp;
        tmp = m_filenames.GetAt(i);
        //�ļ���;
        sline.Format(_T("\t\tname = \"%s\"\r\n"),tmp.GetBuffer());
        songfile.WriteString(sline.GetBuffer());
        //����;
        sline.Format(_T("\r\n"));
        songfile.WriteString(sline.GetBuffer());
        //chance;
        sline.Format(_T("\t\tchance = {\r\n"));
        songfile.WriteString(sline.GetBuffer());
        sline.Format(_T("\t\t\tmodifier = {\r\n"));
        songfile.WriteString(sline.GetBuffer());
        //factor;
        sline = _T("");
        songfile.WriteString(sline.GetBuffer());
        songfile.WriteString(sline.GetBuffer());
        //end chance;
        sline.Format(_T("\t\t\t}\r\n"));
        songfile.WriteString(sline);
        //end name;
        sline.Format(_T("\t\t}\r\n"));
        songfile.WriteString(sline);
        //end song;
        sline.Format(_T("}\r\n"));
        songfile.WriteString(sline);
    }
    

    songfile.Close();
    this->OnOK();
}

void CMusicFiles::OnBnClickedCancel()
{
    this->OnCancel();
}

int CMusicFiles::ImportWorkPath( const CString& path )
{//��"\";
    m_path = path;
    return 0;
}

void CMusicFiles::OnCut()
{//δʹ��;

    CMenu* mainmenu = new CMenu;
    mainmenu->LoadMenuW(IDR_MENU3);

}

void CMusicFiles::OnCopy()
{//δʹ��;
    // TODO: �ڴ���������������
}

void CMusicFiles::OnPaste()
{//δʹ��;
    // TODO: �ڴ���������������
}

void CMusicFiles::OnInsert()
{//δʹ��;
    int WidthCol1 = FACTORCOL;
    CString strload = _T("factor");
    
 
}

void CMusicFiles::OnSetfocusEdit1()
{
    CString strload;
    int retload = 0;
    strload = _T("");
    ((CEdit*)GetDlgItem(IDC_MFILE_EDIT1))->SetWindowTextW(strload.GetBuffer());
}

void CMusicFiles::OnSaveToControl()
{
    CString strload;
    int retload = 0;

    CTreeCtrl* pTree = ((CTreeCtrl*)GetDlgItem(IDC_MFILE_TREE1));
    HTREEITEM hSelItem = pTree->GetSelectedItem();
    HTREEITEM hSubItem = pTree->GetNextItem(hSelItem,TVGN_CHILD);
    DWORD_PTR pFactors = pTree->GetItemData(hSelItem);

    ((CEdit*)GetDlgItem(IDC_MFILE_EDIT1))->GetWindowTextW(strload);
    

}

int CMusicFiles::SetEdit1()
{
    CString strload;
    int retload = 0;
    strload = _T("���ڴ�����factor\r\n�ڵĴ���");
    CEdit* pEdit = ((CEdit*)GetDlgItem(IDC_MFILE_EDIT1));
    pEdit->EnableWindow(TRUE);
    pEdit->SetWindowTextW(strload.GetBuffer());
    return 0;
}

void CMusicFiles::OnTvnSelChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
    CTreeCtrl* pTree = ((CTreeCtrl*)GetDlgItem(IDC_MFILE_TREE1));
    CString strload;
    int retload = 0;

    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    TVITEM newItem = pNMTreeView->itemNew;
    HTREEITEM hThisItem = pTree->GetNextItem(newItem.hItem,TVGN_CARET);
    
    HTREEITEM hChildItem = pTree->GetNextItem(hThisItem,TVGN_CHILD);
    DWORD_PTR pFactors = pTree->GetItemData(hThisItem);

    if ( NULL == hChildItem )
    {
        SetEdit1();
        return;
    }

    if ( 0 == pFactors )
    {
        strload = _T("�뵥��ÿ��mp3�ļ��������");
        CEdit* pEdit = ((CEdit*)GetDlgItem(IDC_MFILE_EDIT1));
        pEdit->SetWindowTextW(strload.GetBuffer());
        pEdit->EnableWindow(FALSE);
        UpdateData(FALSE);
        return;
    }

    strload.Format(_T("�˽ڵ���%d����\r\n��˫��mp3�ļ��༭\r\n��������"),(int) pFactors);
    CEdit* pEdit = ((CEdit*)GetDlgItem(IDC_MFILE_EDIT1));
    pEdit->SetWindowTextW(strload.GetBuffer());
    pEdit->EnableWindow(FALSE);
    UpdateData(FALSE);
    *pResult = 0;
}

void CMusicFiles::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CTreeCtrl* pTree = ((CTreeCtrl*)GetDlgItem(IDC_MFILE_TREE1));
    TVITEM newItem = pNMTreeView->itemNew;
    HTREEITEM hThisItem = pTree->GetNextItem(newItem.hItem,TVGN_CARET);

    CString strload;
    int retload = 0;

    HTREEITEM hSelItem = pTree->GetSelectedItem();
    HTREEITEM hSubItem = pTree->GetNextItem(hSelItem,TVGN_CHILD);
    TVITEM Item;
    retload = pTree->GetItem(&Item);
    int pFactors = (int) Item.lParam;
    if ( NULL != hSubItem && MAXFACTORS > pFactors && 0 < pFactors )
    {
        CPoint pt;
        ::GetCursorPos(&pt);//get Mouse Position;
        CMenu* pMainMenu = new CMenu;
        pMainMenu->LoadMenuW(IDR_MENU3);
        CMenu* pMenu = new CMenu;
        pMenu->GetSubMenu(0);
        pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
    }

    *pResult = 0;
}
