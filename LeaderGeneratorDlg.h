// LeaderGeneratorDlg.h : 头文件;
//
#pragma once
#include "Leader.h"

#include "Tab0.h"
#include "Tab1.h"
#include "Tab2.h"
#include "Tab3.h"
#include "Tab4.h"
#include "Tab5.h"


// CLeaderGeneratorDlg 对话框;
class CLeaderGeneratorDlg : public CDialog
{
// 构造;
public:
	CLeaderGeneratorDlg(CWnd* pParent = NULL);	// 标准构造函数;

// 对话框数据;
	enum { IDD = IDD_LEADERGENERATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持;


// 实现;
protected:
	HICON m_hIcon;

	// 生成的消息映射函数;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	//Extrated Method;
	int CheckValidData();
	int Random(UINT &n);
	int GenerateLeader(Leader* leaderx , int id , int type);
	int SaveDataToMainWindow();
	int showtab(int tab = 0);

public:
	CString m_output;
	
	CTabCtrl mc_tab;
	CTab0 mc_tab0;
	CTab1 mc_tab1;//Namestyle;
	CTab2 mc_tab2;//Country Name;
	CTab3 mc_tab3;
	CTab4 mc_tab4;
	CTab5 mc_tab5;

//tab1;
	int m_namestyle;
	int m_NameFormat;//关联到hoi3::NameFormat;
	BOOL m_BHanzi;
//tab2;
	CString m_country;
	BOOL m_BCCCompatible;//Custom Country Compatible;
//tab3;
	int m_iGMaxPotentialSkill;//资质最大值;
	BOOL m_BSkillBeforeName;
//tab4;
	BOOL m_BNoOldGuard;
	BOOL m_BFTMCompatible;
	BOOL m_BCustomTraits;//自定义特技组;
	int m_MaxTraits;//将领最多特技个数;
	int m_TraitsDist;//将领特技分布函数;//关联到hoi3::TraitsDist;
//tab5;
	int m_GenMethod;//hoi3::PictureSet;
	int m_usetag;
	int m_PicBeginID;
	BOOL m_BSamePic;
//;
	int m_IDstart;
	int m_IDend;
	int m_type;
	
	int m_land;
	int m_air;
	int m_navy;
//;
	BOOL m_BM1;
	BOOL m_BM2;

	afx_msg void OnBnClickedButtonGen();
	afx_msg void SetDefaultData();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedCheckM1();
	afx_msg void OnBnClickedCheckM2();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnMenuQuit();
	afx_msg void OnMenuAbout();
	afx_msg void OnImport();
	afx_msg void OnExport();
    afx_msg void OnFileNew();
    afx_msg void OnFileOpen();
    afx_msg void OnToolsMusic();
};
