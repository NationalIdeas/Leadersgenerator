
// LeaderGenerator.h : LeaderGenerator Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLeaderGeneratorApp:
// �йش����ʵ�֣������ LeaderGenerator.cpp
//

class CLeaderGeneratorApp : public CWinAppEx
{
public:
	CLeaderGeneratorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLeaderGeneratorApp theApp;