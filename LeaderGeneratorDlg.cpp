// LeaderGeneratorDlg.cpp : ʵ���ļ�;
//
#include "stdafx.h"
#include "LeaderGenerator.h"
#include "LeaderGeneratorDlg.h"
#include "resource.h"
#include "aboutdlg.h"
#include "xmlparse.h"

#include "hoi3data.h"

#include "PortSettings.h"
#include "musicfiles.h"
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDMIN 590000
#define IDMAX 999999
#define MAXSKILL 10
#define MAXTABINDEX 5

//MAXPATH �Ѷ���;
#define MAXFILECOUNT 300
#define MAXFILEBUFFER (MAXFILECOUNT * (MAX_PATH + 1) + 1)

CLeaderGeneratorDlg::CLeaderGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLeaderGeneratorDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAINFRAME);
}

void CLeaderGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_MAIN, m_output);
	DDX_Text(pDX, IDC_EDIT_LAND, m_land);
	DDX_Text(pDX, IDC_EDIT_AIR, m_air);
	DDX_Text(pDX, IDC_EDIT_NAVY, m_navy);

	DDX_Check(pDX, IDC_CHECK_M1, m_BM1);
	DDX_Check(pDX, IDC_CHECK_M2, m_BM2);

	DDX_Control(pDX, IDC_TAB, mc_tab);
}

BEGIN_MESSAGE_MAP(CLeaderGeneratorDlg, CDialog)
//	ON_WM_SYSCOMMAND()
//	ON_WM_PAINT()
// 	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON_GEN, &CLeaderGeneratorDlg::OnBnClickedButtonGen)
	ON_BN_CLICKED(IDOK, &CLeaderGeneratorDlg::SetDefaultData)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CLeaderGeneratorDlg::OnBnClickedButtonPreview)

	ON_BN_CLICKED(IDC_CHECK_M1, &CLeaderGeneratorDlg::OnBnClickedCheckM1)
	ON_BN_CLICKED(IDC_CHECK_M2, &CLeaderGeneratorDlg::OnBnClickedCheckM2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CLeaderGeneratorDlg::OnTcnSelchangeTab)
	ON_COMMAND(IDM_FILE_EXIT, &CLeaderGeneratorDlg::OnMenuQuit)
	ON_COMMAND(IDM_ABOUT, &CLeaderGeneratorDlg::OnMenuAbout)
	ON_COMMAND(IDM_TOOLS_IMPORT, &CLeaderGeneratorDlg::OnImport)
	ON_COMMAND(IDM_TOOLS_EXPORT, &CLeaderGeneratorDlg::OnExport)
    ON_COMMAND(IDM_FILE_NEW, &CLeaderGeneratorDlg::OnFileNew)
    ON_COMMAND(IDM_FILE_OPEN, &CLeaderGeneratorDlg::OnFileOpen)
    ON_COMMAND(IDM_TOOLS_MUSIC, &CLeaderGeneratorDlg::OnToolsMusic)
END_MESSAGE_MAP()


// CLeaderGeneratorDlg ��Ϣ�������;

BOOL CLeaderGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���;
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��;
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��;

	// TODO: �ڴ���Ӷ���ĳ�ʼ������;
	AfxGetApp()->LoadIcon(IDI_ICON_MAINFRAME);
	CString strload;
	strload.Empty();
	int retload = 0;


//tab control;
	for ( int k = IDS_TAB0 ; k <= IDS_TAB5; k++ )
	{
		retload = strload.LoadStringW((UINT) k );
		mc_tab.InsertItem(k - IDS_TAB0,strload);
	}
	mc_tab0.Create(IDD_TAB0,GetDlgItem(IDC_TAB));
	mc_tab1.Create(IDD_TAB1,GetDlgItem(IDC_TAB));
	mc_tab2.Create(IDD_TAB2,GetDlgItem(IDC_TAB));
	mc_tab3.Create(IDD_TAB3,GetDlgItem(IDC_TAB));
	mc_tab4.Create(IDD_TAB4,GetDlgItem(IDC_TAB));
	mc_tab5.Create(IDD_TAB5,GetDlgItem(IDC_TAB));
	CRect rect; 
	mc_tab.GetClientRect(&rect); 
	rect.top+=23; 
	rect.bottom-=4; 
	rect.left+=3; 
	rect.right-=4; 
	mc_tab0.MoveWindow(&rect); 
	mc_tab1.MoveWindow(&rect); 
	mc_tab2.MoveWindow(&rect); 
	mc_tab3.MoveWindow(&rect); 
	mc_tab4.MoveWindow(&rect); 
	mc_tab5.MoveWindow(&rect); 
	mc_tab0.ShowWindow(TRUE); 
	mc_tab.SetCurSel(0); 
	mc_tab0.ShowWindow(SW_SHOW);
//tab control end;

//Menu Setup;
CMenu* pMainMenu = new CMenu;//���˵�;
pMainMenu->LoadMenuW(IDR_MENU1);

//Menu End;
//;
	GetDlgItem(IDC_CHECK_M2)->EnableWindow(FALSE);
	//���ý������ķ�Χ;
	((CProgressCtrl*) GetDlgItem( IDC_PROGRESS ) )->SetRange( (short)(IDMIN),(short)(IDMAX));
	((CProgressCtrl*) GetDlgItem(IDC_PROGRESS))->ShowWindow(SW_HIDE);
#ifndef DEBUG
	//�����������ݰ�ť;
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
#endif
	m_PicBeginID = IDMIN;
	m_IDstart = IDMIN;
	m_IDend = IDMIN;
	m_BSamePic = FALSE;
	m_BM1 = TRUE;
	m_BM2 = FALSE;
	m_land = 0;
	m_air = 0;
	m_navy = 0;

	UpdateData(FALSE);//���update;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE;
}

// �����Ի��������С����ť������Ҫ����Ĵ���;
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLeaderGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������;

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���;
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CLeaderGeneratorDlg::OnBnClickedButtonGen()
{//���ɰ�ť;

	m_IDstart = IDMIN;
	CString strload;
	int retload;
//Check Valid Data;
	if ( 0 != CheckValidData() )
	{
		retload = strload.LoadStringW(IDS_STRING501);
		m_output = strload;
		return ;
	}
	UpdateData(TRUE);

	m_country.Trim(_T("!@#$%^&*()_+=- "));
	m_output.Empty();
	
	CString temp;
//;
	CStdioFile leaderfile;
	if ( !leaderfile.Open(_T("Leaders.txt"),CFile::modeCreate | CFile::modeReadWrite | CFile::typeText))
	{
		retload = strload.LoadStringW(IDS_STRING502);
		UpdateData(FALSE);
		AfxMessageBox(strload,MB_ICONEXCLAMATION);
		return;
	}
//��������;
	if ( TRUE == mc_tab1.m_BHanzi )
	{
		temp = ::setlocale(LC_ALL,("CHS"));
	}
	if ( FALSE == mc_tab1.m_BHanzi )
	{
		temp = ::setlocale(LC_ALL,("uk"));
	}
	leaderfile.SeekToBegin();
	

	for ( int BattleType = 1; BattleType <= 3 ; BattleType ++ )
	{//for ����;
	
	switch ( BattleType )
		{//switch leader's type;
		case 1://land;
			m_IDend = m_IDstart + m_land - 1;
			m_output.Format(_T("��������½������..."));
			break;
		case 2://air;
			m_IDstart = m_IDend + 1;
			m_IDend = m_IDstart + m_air - 1;
			m_output.Format(_T("�������ɿվ�����..."));
			break;
		case 3://navy;
			m_IDstart = m_IDend + 1;
			m_IDend = m_IDstart + m_navy - 1;
			m_output.Format(_T("�������ɺ�½������..."));
			break;
		}//switch leader's type;
	( (CProgressCtrl*) GetDlgItem( IDC_PROGRESS) )->ShowWindow(SW_SHOW);//׼���������ؼ�;
	( (CProgressCtrl*) GetDlgItem( IDC_PROGRESS) )->SetRedraw(TRUE);
	( (CStatic*) GetDlgItem( IDC_STATIC_MAIN ) )->SetRedraw(TRUE);

	if (  m_IDstart >= m_IDend  ) continue;
	for (int id = m_IDstart;id < (m_IDend + 1 ) ; id++)
	{//for each type generate leaders;
		CString sline;
		sline.Empty();
	//generate leader;
		Leader* leaderx = new Leader;
		GenerateLeader(leaderx , id , BattleType);
	//write to file;
		sline.Format(_T("%d = {\r\n"),leaderx->m_id );
		leaderfile.WriteString(sline);
		sline.Format(_T("\tname = \"%s\"\r\n"),leaderx->m_name.GetBuffer());
		leaderfile.WriteString(sline);
		sline.Format(_T("\tcountry = %s\r\n"),leaderx->m_country.MakeUpper().GetBuffer());
		leaderfile.WriteString(sline);
		sline.Format(_T("\ttype = %s\r\n"),leaderx->m_type.GetBuffer());
		leaderfile.WriteString(sline);
		sline.Format(_T("\tskill = %d\r\n"),leaderx->m_skill);
		leaderfile.WriteString(sline);
		sline.Format(_T("\tmax_skill = %d\r\n"),leaderx->m_maxskill);
		leaderfile.WriteString(sline);
		sline.Format(_T("\tloyalty = %.2f\r\n"),leaderx->m_loyalty);
		leaderfile.WriteString(sline);
		sline.Format(_T("\tpicture = L%d\r\n"),leaderx->m_picture);
		leaderfile.WriteString(sline);
	for ( int itrait = 0; itrait < ( (leaderx->m_traits).GetCount() ) ; itrait ++ )
	{//traits;
		temp = (leaderx->m_traits).GetAt(itrait);
		sline.Format(_T("\tadd_trait = %s\r\n"), temp.GetBuffer());
		leaderfile.WriteString(sline);
	}
		sline.Format(_T("\thistory = {\r\n"));
		leaderfile.WriteString(sline);
		sline.Format(_T("\t\t 1936.1.1 = { rank = 1 }\r\n"));
		leaderfile.WriteString(sline);
		sline.Empty();
		sline.Format(_T("\t}\r\n"));
		leaderfile.WriteString(sline);
		sline.Empty();
		sline.Format(_T("}\r\n"));
		leaderfile.WriteString(sline);
		//;
		sline.Empty();
		temp.Empty();
		//;
		delete leaderx;
		( (CProgressCtrl*) GetDlgItem( IDC_PROGRESS) )->SetRange(m_IDstart,m_IDend);
		( (CProgressCtrl*) GetDlgItem( IDC_PROGRESS) )->SetPos(id);
		}//for each type generate leaders;
	( (CProgressCtrl*) GetDlgItem( IDC_PROGRESS ) )->ShowWindow(SW_HIDE);
	}//for ����;	

	m_output.Format(_T("�ļ����ɳɹ���"));
	leaderfile.Close();
	UpdateData(FALSE);
	
}


void CLeaderGeneratorDlg::SetDefaultData()
{//��������;//TBE;
	m_namestyle = 2; 
	m_NameFormat = 0;
	mc_tab2.m_country = _T("usa");
	mc_tab2.m_BCCCompatible = TRUE;//�����Խ���;
	m_iGMaxPotentialSkill = 3;
	m_BNoOldGuard = TRUE;
	m_BSkillBeforeName = TRUE;//������ʾ������ǰ;
	m_BFTMCompatible = TRUE;//����FTM;
	m_BM1 = TRUE;
	m_BM2 = FALSE;
	m_land = 4000;
	m_air = 6000;
	m_navy = 7000;
	mc_tab2.UpdataToMainWindow(FALSE);
	UpdateData(FALSE);
	UpdateData(TRUE);
}

void CLeaderGeneratorDlg::OnBnClickedButtonPreview()
{//preview data;
	CString strload;
	CString tmp;
	tmp.Empty();
	int retload;
	if ( 0 != CheckValidData() )
	{
		retload = strload.LoadStringW(IDS_STRING501);
		m_output = strload;
		return;
	}
	
	Leader* leaderx = new Leader;

	GenerateLeader( leaderx , 0 , 1);
	m_output.Empty();
	m_output.AppendFormat(_T("%d = {\r\n"),leaderx->m_id);
	m_output.AppendFormat(_T("\tname = \"%s\"\r\n"),leaderx->m_name.GetBuffer());
	m_output.AppendFormat(_T("\tcountry = %s\r\n"),leaderx->m_country.MakeUpper().GetBuffer());
	m_output.AppendFormat(_T("\ttype = %s\r\n"),leaderx->m_type.GetBuffer());
	m_output.AppendFormat(_T("\tskill = %d\r\n"),leaderx->m_skill);
	m_output.AppendFormat(_T("\tmax_skill = %d\r\n"),leaderx->m_maxskill);
	m_output.AppendFormat(_T("\tloyalty = %.2f\r\n"),leaderx->m_loyalty);
	m_output.AppendFormat(_T("\tpicture = L%d\r\n"),leaderx->m_picture);
	for ( int itrait = 0 ; itrait < ( (leaderx->m_traits).GetCount() ) ; itrait ++ )
	{
		tmp = (leaderx->m_traits).GetAt(itrait);
		m_output.AppendFormat(_T("\tadd_trait = %s\r\n"),tmp.GetBuffer() );
	}
	
	m_output.AppendFormat(_T("\thistory = {\r\n"));
	m_output.AppendFormat(_T("\t\t1936.1.1 = { rank = 1 }\r\n"));
	m_output.AppendFormat(_T("\t}\r\n"));
	UpdateData(FALSE);
	UpdateData(TRUE);
}

int CLeaderGeneratorDlg::CheckValidData()
{
	int ret;
	int retload = 0;
	CString temp;
	CString strload;
	ret = SaveDataToMainWindow();
	UpdateData(TRUE);
//check ID range;
	m_IDend = m_IDstart + m_land + m_air + m_navy;
	if ( m_IDstart > m_IDend)
	{
		retload = strload.LoadStringW(IDS_STRING503);
		m_output = strload;
		UpdateData(FALSE);
//		AfxMessageBox(strload,MB_ICONEXCLAMATION);//����ʾ������ʾ��;
		return EXIT_FAILURE;
	}
//check ID MAX;
	if ( m_IDend > IDMAX)
	{
		retload = strload.LoadStringW(IDS_STRING510);
		m_output = strload;
		UpdateData(FALSE);
		return EXIT_FAILURE;
	}
//check country TAG;
	if ( true == m_country.IsEmpty() )
	{
		retload = strload.LoadStringW(IDS_STRING504);
		m_output = strload;
		UpdateData(FALSE);
		showtab(2);//TAB2;
		AfxMessageBox(strload,MB_ICONEXCLAMATION);
		return EXIT_FAILURE;
	}
	if ( FALSE == m_BCCCompatible)
	{//�������Խ���ʱ;
		for(int i = 0 ; i<= hoi3::countrycount ; i++ )
		{
			retload = temp.LoadStringW((UINT)(i + IDS_TAG0));
			ret = m_country.CompareNoCase(temp);
			if (0 == ret) break;
		}
		if ( 0 != ret)
		{
			retload = strload.LoadStringW(IDS_STRING505);
			m_output = strload;
			UpdateData(FALSE);
			showtab(2);//TAB2;
			AfxMessageBox(strload,MB_ICONEXCLAMATION);
			return EXIT_FAILURE;
		}
	}
	if ( (FALSE == m_BM1 && FALSE == m_BM2) || (TRUE == m_BM1 && TRUE == m_BM2) )
	{
		ret = strload.LoadStringW(IDS_STRING509);
		m_output = strload;
		UpdateData(FALSE);
	}
	if ( TRUE == m_BM2 )
	{//ʹ�õڶ��ַ���;
		retload = strload.LoadStringW(IDS_STRING506);
		m_output = strload;
		UpdateData(FALSE);
		AfxMessageBox(strload,MB_ICONEXCLAMATION);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int CLeaderGeneratorDlg::Random( UINT &n )
{
	errno_t err = rand_s( &n );
	CString strload;
	int retload = strload.LoadStringW(IDS_STRING507);
	if (err != 0)
	{
		m_output = strload;
		UpdateData(FALSE);
		AfxMessageBox(strload,MB_ICONEXCLAMATION);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int CLeaderGeneratorDlg::GenerateLeader( Leader* leaderx ,int id ,int type)
{
	int res;
//for load string;
	int retload = 0;
	CString strload;
	strload.Empty();

	unsigned int n;//random function parameter;
	CString temp;
	CString fname = _T("King");
	leaderx->m_id = id;
	leaderx->m_skill = 1;
	leaderx->m_maxskill = MAXSKILL;
//use same portrait;
	int iMinPicID = IDMIN;
	int iMaxPicID = IDMAX;
	switch (m_usetag)
	{
	case hoi3::GER:
		iMinPicID = 1;
		iMaxPicID = 997;
		break;
	case hoi3::SOV:
		iMinPicID = 9800;
		iMaxPicID = 10522;
		break;
	case hoi3::USA:
		iMinPicID = 60000;
		iMaxPicID = 60586;
		break;
	case hoi3::ENG:
		iMinPicID = 1000;
		iMaxPicID = 1517;
		break;
	case hoi3::JAP:
		iMinPicID = 101000;
		iMaxPicID = 101362;
		break;
	default:
		iMinPicID = 1;
		iMaxPicID = 10000;
		break;
	}
	Random(n);
	int iPicID = iMinPicID + 1 + (int) ((double) n / ( UINT_MAX + 1.0 ) * ((double) (iMaxPicID - 1.0 - iMinPicID)));
	if ( m_GenMethod == hoi3::PGM_UsePortraitPack)
	{
		leaderx->m_picture = iPicID;
	}
	if ( m_GenMethod == hoi3::PGM_GeneratePortraitID)
	{
		iPicID = 1000;
		leaderx->m_picture = (m_BSamePic == TRUE ? iPicID : 1);
	}
	
//History;
	leaderx->m_history.setStartDate();
	temp.Empty();
//Name;
	
	CString gname;//given name;
	int max_gname = 0, max_fname = 0, min_gname = 0, min_fname = 0;
	switch( m_namestyle )
	{//switch start;
		case hoi3::Britain :
			min_gname = (int) IDS_ENG_ENG_GNAME;
			max_gname = (int) IDS_ENG_ENG_GNAME_END ;
			min_fname = (int) IDS_ENG_ENG_FNAME ;
			max_fname = (int) IDS_ENG_ENG_FNAME_END ;
			break;
		case hoi3::Germanic :
			min_gname = (int) IDS_DEU_GER_GNAME;
			max_gname = (int) IDS_DEU_GER_GNAME_END ;
			min_fname = (int) IDS_DEU_GER_FNAME ;
			max_fname = (int) IDS_DEU_GER_FNAME_END ;
			break;
		case hoi3::French :
			min_gname = (int) IDS_LAT_FRA_GNAME;
			max_gname = (int) IDS_LAT_FRA_GNAME_END ;
			min_fname = (int) IDS_LAT_FRA_FNAME ;
			max_fname = (int) IDS_LAT_FRA_FNAME_END ;
			break;
		case hoi3::Russian :
			min_gname = (int) IDS_SLA_RUS_GNAME;
			max_gname = (int) IDS_SLA_RUS_GNAME_END ;
			min_fname = (int) IDS_SLA_RUS_FNAME ;
			max_fname = (int) IDS_SLA_RUS_FNAME_END ;
			break;
		case hoi3::Nordic :
			min_gname = (int) IDS_NDC_SWE_FNAME;
			max_gname = (int) IDS_NDC_SWE_FNAME_END ;
			min_fname = (int) IDS_NDC_SWE_FNAME ;//NO GIVEN NAME;
			max_fname = (int) IDS_NDC_SWE_FNAME_END ;//NO GIVEN NAME;
			break;
		case hoi3::Ukrainian :
			min_gname = (int) IDS_SLA_UKR_FNAME;
			max_gname = (int) IDS_SLA_UKR_FNAME_END ;
			min_fname = (int) IDS_SLA_UKR_FNAME ;//NO GIVEN NAME;
			max_fname = (int) IDS_SLA_UKR_FNAME_END ;//NO GIVEN NAME;
			break;
		case hoi3::Chinese ://���޸�ֻ�к��ְ�;
			min_gname = (int) IDS_HANZI_CJK_CHS_GNAME;
			max_gname = (int) IDS_HANZI_CJK_CHS_GNAME_END ;
			min_fname = (int) IDS_HANZI_CJK_CHS_FNAME ;
			max_fname = (int) IDS_HANZI_CJK_CHS_FNAME_END ;
			break;
	}//switch end;
//given name;
	Random( n );
	res = min_gname + 1 + (int) ( (double) n / ( UINT_MAX + 1.0 ) * ((double) (max_gname - 1.0 - min_gname)));
	retload = gname.LoadStringW((UINT) res);
//family name;
	Random( n );
	res = min_fname + 1 + (int) ((double) n / ( UINT_MAX + 1.0 ) * ((double) (max_fname - 1.0 - min_fname)));
	retload = fname.LoadStringW((UINT) res);
//;
	switch(m_NameFormat)
	{
		case hoi3::fullname:
			leaderx->m_name.Format(_T("%s %s"),gname.GetBuffer(),fname.GetBuffer());
			if (m_namestyle == hoi3::Chinese)
			leaderx->m_name.Format(_T("%s %s"),fname.GetBuffer(),gname.GetBuffer());
			break;
		case hoi3::onlyfamilyname:
			leaderx->m_name.Format(_T("%s"),fname.GetBuffer());
			break;
		case hoi3::onlygivenname:
			leaderx->m_name.Format(_T("%s"),gname.GetBuffer());
			break;
		default:
			break;
	}
//Country;
	leaderx->m_country = m_country;
//BattleType;
	retload = temp.LoadStringW((UINT) type - 1 + IDS_TYPE_LAND);
	leaderx->m_type.Format(_T("%s"), temp.GetBuffer() );
//Skill;
	Random( n );
	res = (int) ((double) n / ( UINT_MAX + 1.0 ) * ((double) m_iGMaxPotentialSkill ));
	leaderx->m_skill = res ;
//maxskill;
	Random( n );
	res = (int) ((double) n / ( UINT_MAX + 1.0 ) * ((double) m_iGMaxPotentialSkill + 1.0));
	if (res < leaderx->m_skill )
	{
		res = leaderx->m_skill ;
	}
	leaderx->m_maxskill = res;

//add MAXPotentialSkill number before name;
	if ( TRUE == m_BSkillBeforeName )
	{
		CString maxskill;
		maxskill.Format(_T("%d"),leaderx->m_maxskill);
		//add string before name;
		temp.Format(_T("%s%s"),maxskill.GetBuffer(),leaderx->m_name.GetBuffer());
		leaderx->m_name.Format(_T("%s"),temp.GetBuffer());
	}
	if ( TRUE == 0)
	{
		CString szPrefix;
		CString szSurffix;
		szPrefix.LoadStringW(123);
		szSurffix.LoadStringW(13);
		temp.Format(_T("%s%s%s"),szPrefix.GetBuffer(),leaderx->m_name.GetBuffer(),szSurffix.GetBuffer());
		leaderx->m_name.Format(_T(""), temp.GetBuffer());
	}
//Trait; 		
	( leaderx->m_traits ).RemoveAll();
	int iTraits = 0;
	
	UINT uStratID = 0;
	switch ( type )
	{//swtich start;
		case hoi3::land:
			iTraits = 10;//land trait;
			if ( m_BFTMCompatible == FALSE )	iTraits = 17;
			uStratID = IDS_TRAIT_LAND + 1;
			break;
		case hoi3::air:
			iTraits = 7;//air trait;
			uStratID = IDS_TRAIT_AIR + 1;
			break;
		case hoi3::navy:
			iTraits = 5;//navy trait;
			uStratID = IDS_TRAIT_NAVY + 1;
			break;
		default:
			retload = strload.LoadStringW(IDS_STRING508);
			m_output = strload;
			UpdateData(FALSE);
			AfxMessageBox(strload,MB_ICONEXCLAMATION);
			break;
	}//swtich end;
	if ( TRUE == m_BNoOldGuard ) 
	{
		iTraits--;
		uStratID++;
	}
	CStringArray sTraits;
	sTraits.RemoveAll();
	for ( int nload = 0; nload < iTraits ; nload++ )
	{
		retload = temp.LoadStringW( uStratID + (UINT) nload );
		sTraits.Add(temp);
	}
	Random(n);
	//ƥ��ֲ�����;
	const int iNumOfTraits = m_MaxTraits;
	int itNumOfTratis = m_MaxTraits;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::normal_distribution<double> NormalDistribution(iNumOfTraits/2,iNumOfTraits/2);

	//Write Data to <Leaderx> Classes;
	if (m_TraitsDist == hoi3::dist_avg)
	{	
		itNumOfTratis =  (int) std::abs(NormalDistribution(rd));
		for ( int iwrite = 0; iwrite < itNumOfTratis; iwrite++ )
	{
		if ( 0 == iTraits ) break;
		res = (int) ((double)n / ( UINT_MAX + 1.0  ) * ((double) iTraits));
		iTraits--;
		temp = sTraits.GetAt(res);
		(leaderx->m_traits).Add(temp);
		sTraits.RemoveAt(res);
	}
	}
	if (m_TraitsDist == hoi3::dist_normal)
	{	
		itNumOfTratis =  (int) ((double)n / ( UINT_MAX + 1.0  ) * ((double) iNumOfTraits));
		for ( int iwrite = 0; iwrite < itNumOfTratis; iwrite++ )
		{
			if ( 0 == iTraits ) break;
			res = (int) std::abs(NormalDistribution(rd));
			if ( res >= m_MaxTraits || res < 0) break;
			iTraits--;
			temp = sTraits.GetAt(res);
			(leaderx->m_traits).Add(temp);
			sTraits.RemoveAt(res);
		}
	}

	return EXIT_SUCCESS;
}

void CLeaderGeneratorDlg::OnBnClickedCheckM1()
	{
	UpdateData(TRUE);
	if ( TRUE == m_BM1)
	{
		m_BM2 = FALSE;

	}
	if ( FALSE == m_BM1)
	{
		m_BM2 = TRUE;
	}
	UpdateData(FALSE);
	}

void CLeaderGeneratorDlg::OnBnClickedCheckM2()
	{
	UpdateData(TRUE);
	if ( TRUE == m_BM2)
		{
		m_BM1 = FALSE;
		}
	if ( FALSE == m_BM2)
	{
		m_BM1 = TRUE;
		}
		UpdateData(FALSE);
	}

void CLeaderGeneratorDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{//change tab page;
	SaveDataToMainWindow();
	int TabSel;
	TabSel = mc_tab.GetCurSel();
	showtab(TabSel);
	*pResult = 0;
}


int CLeaderGeneratorDlg::SaveDataToMainWindow()
{//save tab data to main window;
	//mc_tab0.savedata();
	CString strload;
	strload.Empty();
	int ret = 0;
	ret = mc_tab1.UpdataToMainWindow(TRUE);
	switch (ret)
	{
	case 1:
		break;
	default:
		break;
	}
	m_namestyle = mc_tab1.m_namestyle;
	m_NameFormat = mc_tab1.m_NameFormat;
	
	ret = mc_tab2.UpdataToMainWindow(TRUE);
	switch (ret)
	{
	case 1:
		break;
	default:
		break;
	}
	m_country = mc_tab2.m_country;
	m_BCCCompatible = mc_tab2.m_BCCCompatible;

	ret = mc_tab3.UpdataToMainWindow(TRUE);
	switch (ret)
	{
	case 1:
		break;
	default:
		break;
	}
	m_iGMaxPotentialSkill = mc_tab3.m_iMaxPotentialSkill;
	m_BSkillBeforeName = mc_tab3.m_BSkillBeforeName;

	ret = mc_tab4.UpdataToMainWindow(TRUE);
	switch (ret)
	{
	case 1:
		strload.Format(_T("TAB4����1!"));
		m_output = strload;
		UpdateData(TRUE);
		return 41;
		break;
	default:
		break;
	}
	m_BNoOldGuard = mc_tab4.m_BNoOldGuard;
	m_BFTMCompatible = mc_tab4.m_BFTMCompatible;
	m_BCustomTraits = mc_tab4.m_BCustomTraits;
	m_MaxTraits = mc_tab4.m_MaxTraits;
	m_TraitsDist = mc_tab4.m_TraitsDist;
//tab5;
	ret = mc_tab5.UpdataToMainWindow(TRUE);
	switch (ret)
	{
	case 1:
		strload.Format(_T("TAB5����1!"));
		m_output = strload;
		UpdateData(TRUE);
		return 51;
		break;
	default:
		break;
	}
	m_GenMethod = mc_tab5.m_GenMethod;
	m_usetag = mc_tab5.m_countrytag;
	m_BSamePic = mc_tab5.m_BSamepic;
	if ( TRUE == m_BSamePic)
	{
		m_PicBeginID = mc_tab5.m_pic;
	}

	return 0;
}

int CLeaderGeneratorDlg::showtab( int tab /*= 0*/ )
{
	if ( MAXTABINDEX < tab) return -1;
	switch(tab)
	{
	case 0:
		mc_tab0.ShowWindow(TRUE);
		mc_tab1.ShowWindow(FALSE);
		mc_tab2.ShowWindow(FALSE);
		mc_tab3.ShowWindow(FALSE);
		mc_tab4.ShowWindow(FALSE);
		mc_tab5.ShowWindow(FALSE);
		break;
	case 1:
		mc_tab0.ShowWindow(FALSE);
		mc_tab1.ShowWindow(TRUE);
		mc_tab2.ShowWindow(FALSE);
		mc_tab3.ShowWindow(FALSE);
		mc_tab4.ShowWindow(FALSE);
		mc_tab5.ShowWindow(FALSE);
		break;
	case 2:
		mc_tab0.ShowWindow(FALSE);
		mc_tab1.ShowWindow(FALSE);
		mc_tab2.ShowWindow(TRUE);
		mc_tab3.ShowWindow(FALSE);
		mc_tab4.ShowWindow(FALSE);
		mc_tab5.ShowWindow(FALSE);
		break;
	case 3:
		mc_tab0.ShowWindow(FALSE);
		mc_tab1.ShowWindow(FALSE);
		mc_tab2.ShowWindow(FALSE);
		mc_tab3.ShowWindow(TRUE);
		mc_tab4.ShowWindow(FALSE);
		mc_tab5.ShowWindow(FALSE);
		break;
	case 4:
		mc_tab0.ShowWindow(FALSE);
		mc_tab1.ShowWindow(FALSE);
		mc_tab2.ShowWindow(FALSE);
		mc_tab3.ShowWindow(FALSE);
		mc_tab4.ShowWindow(TRUE);
		mc_tab5.ShowWindow(FALSE);
		break;
	case 5:
		mc_tab0.ShowWindow(FALSE);
		mc_tab1.ShowWindow(FALSE);
		mc_tab2.ShowWindow(FALSE);
		mc_tab3.ShowWindow(FALSE);
		mc_tab4.ShowWindow(FALSE);
		mc_tab5.ShowWindow(TRUE);
		break;
	default:
		break;
	}
	SaveDataToMainWindow();
	mc_tab.SetCurSel(tab);
	UpdateData(FALSE);
	return 0;
}

void CLeaderGeneratorDlg::OnMenuQuit()
{//�˳�;
	this->OnCancel();
}

void CLeaderGeneratorDlg::OnMenuAbout()
{//����;
	CAboutDlg* CAboutDlgEx = new CAboutDlg;
	CAboutDlgEx->DoModal();
}

void CLeaderGeneratorDlg::OnImport()
{//��������;
    CSETTINGS* CImportEx = new CSETTINGS;
    CImportEx->PortSettings(hoi3::ImportSet);
    CImportEx->DoModal();
}

void CLeaderGeneratorDlg::OnExport()
{//��������;
	CSETTINGS* CExportEx = new CSETTINGS;
    CExportEx->PortSettings(hoi3::ExportSet);
	CExportEx->DoModal();
}

void CLeaderGeneratorDlg::OnFileNew()
{//�½�;
    HOI3XML::writeXML(_T("nihao"));
    HOI3XML::readXML(_T("nihao"));
}

void CLeaderGeneratorDlg::OnFileOpen()
{//��;
    return;
}

void CLeaderGeneratorDlg::OnToolsMusic()
{
   CString strload,fileext,filefilter;
   CString sTitle;
   CString tmp;
   CString path;//�����ļ���·��;
   CString workpath;//����·��;
   int retload = 0;
   INT_PTR ret = 0;//return value;
   CStringArray filenames;

   fileext = _T("mp3");
   strload = _T("HOI3�����ļ�");
   filefilter.Format(_T("%s (*.%s)|*.mp3||"),strload.GetBuffer(),fileext.GetBuffer());
   sTitle = _T("��ѡ�������ļ�");

   
   int buffersize = MAX_PATH + 1;
   GetModuleFileName(NULL,workpath.GetBuffer(buffersize + 1),buffersize);
   workpath.ReleaseBuffer();

   
   int r_index = workpath.ReverseFind('\\');
   tmp = workpath.Left(r_index + 1);//��'\';
   workpath = tmp;
   path = workpath;

   tmp = _T("Hearts of Iron");
   if ( 0 > path.Find(tmp))
   {//��ȡע���;
       HKEY hKEY;
       HKEY hKeyRoot = HKEY_LOCAL_MACHINE;
       tmp = _T("SOFTWARE\\Paradox Interactive\\Hearts of Iron III");
       LONG retReg;
       retReg = RegOpenKeyEx(hKeyRoot,tmp,NULL,KEY_READ,&hKEY);

       tmp = _T("CD");
       path.Empty();
       DWORD keyType = REG_SZ;
       DWORD DataLen = MAX_PATH;
       retReg = RegQueryValueEx(hKEY,tmp,NULL,&keyType,(LPBYTE)(LPCTSTR)path.GetBuffer(MAX_PATH),&DataLen);
       path.ReleaseBuffer();//�����ͷŻ���;

       tmp.Empty();
       tmp = _T("\\music");
       path += tmp;
   }
   CString sMaxfile;
   CFileDialog CFileDialogEx(TRUE,0,0,4|2|OFN_ALLOWMULTISELECT,filefilter,this->GetSafeOwner(),0,1);
   OPENFILENAME& ofn = CFileDialogEx.GetOFN();
   ofn.lpstrTitle = sTitle;
   ofn.lpstrFile = sMaxfile.GetBuffer(MAXFILEBUFFER);
   ofn.nMaxFile = MAXFILEBUFFER;
   ofn.lpstrInitialDir = path;//���ó�ʼ�ļ���;
   sMaxfile.ReleaseBuffer();//������;
   
   ret = CFileDialogEx.DoModal();
   if (ret == IDCANCEL) 
   {
       strload = _T("δѡȡ�ļ�!");
       m_output = strload;
       UpdateData(FALSE);
       return;
   }
//Deal with Selected Files;
   POSITION pos = CFileDialogEx.GetStartPosition();//start position;
   filenames.RemoveAll();
   while(pos != NULL)
   {
       filenames.Add(CFileDialogEx.GetNextPathName(pos));
   }
   CMusicFiles musicfiles;
   musicfiles.ImportFileNames(filenames);
   musicfiles.ImportWorkPath(workpath);//��"\";
   ret = musicfiles.DoModal();
   if (ret == IDCANCEL)
   {
       strload = _T("ȡ�����������ļ�����!");
       m_output = strload;
       UpdateData(FALSE);
       return;
   }
   
       
   UpdateData(FALSE);
}
