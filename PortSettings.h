#pragma once
#include "hoi3data.h"

// CExport

class CSETTINGS : public CDialog
{
	DECLARE_DYNAMIC(CSETTINGS)

public:
	CSETTINGS();
	virtual ~CSETTINGS();
	enum{IDD = IDD_SETTINGS};

    int m_portways;//关联到hoi3::settings;

protected:
	HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持;
	virtual BOOL OnInitDialog();
public:

    int PortSettings(const int& portway = hoi3::ExportSet);

    afx_msg void OnBnClickedIMPORT();
    afx_msg void OnBnClickedEXPORT();
    afx_msg void OnBnClickedRETURN();
    afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
};
