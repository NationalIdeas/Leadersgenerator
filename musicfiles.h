#pragma once
#include "resource.h"

// CMUSICFILES 对话框

class CMusicFiles : public CDialog
{
	DECLARE_DYNAMIC(CMusicFiles)

public:
	CMusicFiles(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMusicFiles();

// 对话框数据
	enum { IDD = IDD_MUSICFILES };
    enum Factors{
        one = 1,
        two     ,
        three   ,
        four    ,
        five    ,
        six     
    };

protected:
    HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
    CString m_path;
    CStringArray m_filenames;

    int SetEdit1();

public:
    int ImportFileNames(const CStringArray& filenames);
    int ImportWorkPath(const CString& path);
    afx_msg void OnBnClickedSave();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnCut();
    afx_msg void OnCopy();
    afx_msg void OnPaste();
    afx_msg void OnInsert();
    afx_msg void OnSetfocusEdit1();
    afx_msg void OnSaveToControl();
    afx_msg void OnTvnSelChanged(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
