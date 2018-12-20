#pragma once
#include "stdafx.h"
#include "aboutdlg.h"

#pragma comment(lib,"version.lib")

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_sVersion(_T(""))
, m_sCopyright(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAINFRAME);

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ABOUT_ICON, m_StaticIcon);
	DDX_Text(pDX, IDC_STATIC_ABOUT_VERSION, m_sVersion);
	DDX_Text(pDX, IDC_STATIC_ABOUT_COPYRIGHT, m_sCopyright);
	DDX_Control(pDX, IDC_STATIC_ABOUT_SYSLINK1, m_Link);
}
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->SetIcon(m_hIcon,FALSE);
	this->SetIcon(m_hIcon,TRUE);
//;
	m_StaticIcon.SetIcon(m_hIcon);
//version;
	int retload = 0;
	CString temp;
	temp.Empty();

	
	LPTSTR lpszFilePath = _T("LeaderGenerator.exe");

	DWORD dwDummy;
	DWORD dwFVISize = GetFileVersionInfoSize(lpszFilePath, &dwDummy);

	LPBYTE lpVersionInfo = new BYTE[dwFVISize];

	GetFileVersionInfo(lpszFilePath, 0, dwFVISize, lpVersionInfo);

	UINT uLen;
	VS_FIXEDFILEINFO *lpFfi;

	VerQueryValue(lpVersionInfo, _T("\\"), (LPVOID *)&lpFfi, &uLen);

	DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
	DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;

	delete[] lpVersionInfo;

	DWORD major = HIWORD(dwFileVersionMS);
	DWORD minor = LOWORD(dwFileVersionMS);
	DWORD revision = HIWORD(dwFileVersionLS);
	DWORD build = LOWORD(dwFileVersionLS);

	CString szVersion;
	szVersion.Format(_T("%d.%d.%d.%d"), major, minor, revision, build);

	m_sVersion.Append(szVersion);


//copyright;
	temp.Empty();
	retload = temp.LoadString(IDS_COPYRIGHT_AUTHOR);
	m_sCopyright.Append(temp);
	m_sCopyright +=" ";
	retload = temp.LoadString(IDS_COPYRIGHT_UNIVERSITY);
	m_sCopyright.Append(temp);
	m_sCopyright +=" ";
	retload = temp.LoadString(IDS_COPYRIGHT_YEAR);
	m_sCopyright.Append(temp);
//MailTo;
	retload = temp.LoadString(IDS_COPYRIGHT_EMAIL);
	m_Link.SetWindowTextW(_T("<a>rubost@outlook.com</a>"));
	



	UpdateData(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_STATIC_ABOUT_SYSLINK1, &CAboutDlg::OnNMClickStaticAboutSyslink1)
END_MESSAGE_MAP()

void CAboutDlg::OnNMClickStaticAboutSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	ShellExecute(NULL,_T("open"),_T("mailto:rubost@outlook.com"),NULL,NULL,SW_NORMAL);
	return;
}
