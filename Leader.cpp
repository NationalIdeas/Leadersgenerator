#include "stdafx.h"
#include "Leader.h"
#include "hoi3data.h"

mdate::mdate(void)
{
	m_Year  = 1930;
	m_Month = 1;
	m_Day   = 1;	
}

int mdate::setDate( int iYear,int iMonth,int iDay)
{
	this->m_Year  = iYear;
	this->m_Month = iMonth;
	this->m_Day   = iDay;
	return 0;
}

int mdate::get_year()
{
	return m_Year;
}

int mdate::get_month()
{
	return m_Month;
}

int mdate::get_day()
{
	return m_Day;
}
int mdate::check()
{
	return 0;
}

mdate::~mdate()
{
}


mdate& mdate::operator= ( const mdate& source)
{
	this->m_Day   = source.m_Day;
	this->m_Month = source.m_Month;
	this->m_Year  = source.m_Year;
	return *this;
}

history::history(void)
{
	m_StartDate.setDate();
	m_nDates = 1;
}

int history::add( mdate datex)
{//unimplemented;

	m_nDates ++;
	return 0;
}

int history::remove( int sn )
{//unimplemented;
	return 0;
}

int history::setStartDate()
{
	m_StartDate.setDate();
	return 0;
}

int history::getDates()
{//unimplemented;
	return 0;
}

history::~history()
{
}

history& history::operator=( const history& source )
{
	this->m_nDates = source.m_nDates;
	this->m_StartDate = source.m_StartDate;
	return *this;
}	

Leader::Leader(void)
{
	m_name = "Leader's Name";
	m_country = "REB";
	m_type = _T("land");
	m_skill = 3;
	m_maxskill = 3;
	m_loyalty = 1.00;
	m_picture = 60000;
	m_traits.RemoveAll();
	m_history.setStartDate();
	
}

Leader& Leader::operator= ( const Leader& source )
{
	this->m_name     = source.m_name;
	this->m_country  = source.m_country;
	this->m_type     = source.m_type; 
	this->m_skill    = source.m_skill;
	this->m_maxskill = source.m_maxskill;
	this->m_loyalty  = source.m_loyalty;
	this->m_picture  = source.m_picture;
	(this->m_traits).Copy( source.m_traits ) ;
	this->m_history  = source.m_history;
	return *this;
}

Leader::~Leader()
{
}



