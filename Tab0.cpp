// Tab0.cpp : 实现文件
//

#include "stdafx.h"
#include "LeaderGenerator.h"
#include "Tab0.h"


// CTab0 对话框

IMPLEMENT_DYNAMIC(CTab0, CDialog)

CTab0::CTab0(CWnd* pParent /*=NULL*/)
	: CDialog(CTab0::IDD, pParent)
{

}

CTab0::~CTab0()
{
}

void CTab0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab0, CDialog)
END_MESSAGE_MAP()

BOOL CTab0::OnInitDialog()
{
	return TRUE;
}


void CTab0::OnCancel()
{
	return;
}


void CTab0::OnOK()
{
	return;
}
