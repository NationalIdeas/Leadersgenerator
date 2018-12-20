#pragma once
#include "stdafx.h"

class mdate
{ 
public://members;
	int m_Year;
	int m_Month;
	int	m_Day;
public:
	mdate(void);
	~mdate();
	
	int setDate(int year = 1936,int month = 1,int day = 1);
	int get_year();
	int get_month();
	int get_day();
	int check();
	mdate& operator= (const mdate& source);
};

class history
{
private://members;
	int m_nDates;//count of date;
	mdate m_StartDate;
//	time end;
public:
	history(void);
	~history();	
	int setStartDate();
	int getDates();
	int add(mdate);
	int remove(int sn);
	history& operator= (const history& source);
};

class Leader
{
public://members;
	int m_id;
	CString m_name;
	CString m_country;//hoi3::countrytag;
	CString m_type;//Leader type;
	int m_skill;
	int m_maxskill;
	double m_loyalty;//2 fixed number after zero;
	int m_picture;//five digit number,start from 6xxyy;
	CStringArray m_traits;//0-;
	history m_history;

public:
	Leader(void);
	~Leader();

	Leader& operator= (const Leader& source);
	
};


