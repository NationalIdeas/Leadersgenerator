#pragma once
#include "stdafx.h"

namespace hoi3
{
	enum Trait_type
	{
		land = 1,
		air,
		navy
	};
	enum NameStyle
	{//tab1;
		Britain = 0,
		Germanic	,
		French		,
		Russian		,
		Nordic		,
		Ukrainian	,
		Chinese

	};
	enum Name_Format
	{//name format;
		fullname	 = 0,
		onlygivenname	,
		onlyfamilyname	,
	};
	enum TraitsDist
	{//tab4;
		dist_avg = 0 ,//平均分布;
		dist_normal	 ,//正态分布;
		dist_none	  //没有分布;
	};
	enum PortraitGenerateMethod
	{//tab5;
		PGM_GeneratePortraitID	= 0,
		PGM_UsePortraitPack 
	};
	enum settings
	{
		NonSet = 0 ,
		ImportSet      ,//导入设置;
		ExportSet      ,//导出设置;
	};
	// 	enum Trait_Land 
/*	 	{
	 		old_guard				= 1,
	 		trickster				,
	 		commando				,
	 		engineer				,
	 		defensive_doctorine		,
	 		offensive_doctorine		,
	 		fortress_buster			,
	 		logistics_wizard		,
	 		panzer_leader			,
	 		winter_specialist		,
	 		desert_fox				= 11,
	 		hill_fighter			,
	 		jungle_rat				,
	 		mountaineer				,
	 		piercing				,
	 		ranger					,
	 		swamp_fox				,
	 		urban_assault_specialist,
	 		leader_land_size		
	 	};
	 	enum Trait_Air 
	 	{
	 		carpet_bomber			= 2,
	 		fleet_destroyer			,
	 		night_flyer				,
	 		superior_air_tactician	,
	 		tank_buster				,
	 		leader_air_size			
	 	};
	 	enum Trait_Navy
	 	{
	 		blockade_runner			= 2,
	 		seawolf					,
	 		superior_tactician		,
	 		spotter					,
	 		leader_navy_size		
	 	};
*/
	enum country_tag
	{
		REB = 0,//Partisans;
		GER,    //Germany;
		ENG,    //United Kingdom;
		SOV,    //Soviet Union;
		USA,    //USA;
		JAP,    //Japan;
		FRA,    //France;
		ITA,    //Italy;
		DEN,    //Denmark;
		ICL,    //Iceland;
		EST,    //Estonia;
		FIN,    //Finland;
		LAT,    //Latvia;
		LIT,    //Lithuania;
		NOR,    //Norway;
		SCA,    //Scandinavia;
		SWE,    //Sweden;
		BEL,    //Belgium;
		FLA,    //Flanders;
		HOL,    //Netherlands;
		IRE,    //Ireland;
		LUX,    //Luxembourg;
		SCO,    //Scotland;
		VIC,    //Vichy France;
		WLL,    //Wallonia;
		AUS,    //Austria;
		CZE,    //Czechoslovakia;
		CRO,    //Croatia;
		DDR,    //DDR;
		DFR,    //FRG;
		HUN,    //Hungary;
		POL,    //Poland;
		ROM,    //Romania;
		SLO,    //Slovakia;
		SLV,    //Slovenia;
		SCH,    //Switzerland;
		EUS,    //Euskadi;
		POR,    //Portugal;
		RSI,    //Italian Social Republic;
		SPA,    //Nationalist Spain;
		SPR,    //Republican Spain;
		ALB,    //Albania;
		BOS,    //Bosnia;
		BUL,    //Bulgaria;
		GRE,    //Greece;
		MTN,    //Montenegro;
		SER,    //Serbia;
		YUG,    //Yugoslavia;
		BLR,    //Byelorussia;
		PRI,    //Primorsk;
		RUS,    //Russia;
		SIB,    //Siberia;
		TAN,    //Tannu Tuva;
		TRA,    //Transural Republic;
		UKR,    //Ukraine;
		AFG,    //Afghanistan;
		ARA,    //Arab Federation;
		ARM,    //Armenia;
		AZB,    //Azerbaijan;
		CYP,    //Cyprus;
		GEO,    //Georgia;
		IRQ,    //Iraq;
		ISR,    //Israel;
		JOR,    //Jordan;
		LEB,    //Lebanon;
		OMN,    //Oman;
		OTT,    //Ottoman Empire;
		PAL,    //Palestine;
		PER,    //Persia;
		SAU,    //Saudi Arabia;
		SYR,    //Syria;
		TUR,    //Turkey;
		YEM,    //Yemen;
		KAZ,    //Kazakhstan;
		KUR,    //Kurdistan;
		KYG,    //Kyrgyzstan;
		TAJ,    //Tajikistan;
		TRK,    //Turkmenistan;
		UZB,    //Uzbekistan;
		BHU,    //Bhutan;
		IND,    //India;
		NEP,    //Nepal;
		PAK,    //Pakistan;
		CGX,    //Guangxi Clique;
		CHC,    //Communist China;
		CHI,    //Nationalist China;
		CSX,    //Shanxi;
		CXB,    //Xibei San Ma;
		CYN,    //Yunnan;
		KOR,    //Korea;
		MAN,    //Manchukuo;
		MEN,    //Mengkukuo;
		MON,    //Mongolia;
		PRK,    //People's Republic of Korea;
		SIK,    //Sinkiang;
		TIB,    //Tibet;
		BRU,    //Brunei;
		BUR,    //Burma;
		CMB,    //Cambodia;
		IDC,    //Indochina;
		INO,    //Indonesia;
		LAO,    //Laos;
		MLY,    //Malaysia;
		PHI,    //Philippines;
		SAR,    //Sarawak;
		SIA,    //Siam;
		VIE,    //Vietnam;
		ALG,    //Algeria;
		EGY,    //Egypt;
		LBY,    //Libya;
		MOR,    //Morocco;
		SUD,    //Sudan;
		TUN,    //Tunisia;
		BEN,    //Benin-Sahel;
		GLD,    //Gold Coast;
		GUI,    //Guinea;
		LIB,    //Liberia;
		MAL,    //Union of Mali;
		NIG,    //Nigeria;
		SIE,    //Sierra Leone;
		KON,    //Congo;
		EAF,    //East African Union;
		ETH,    //Ethiopia;
		GAB,    //Gabon;
		CAM,    //Cameroon;
		SOM,    //Somalia;
		ANG,    //Angola;
		EQA,    //Equatorial Africa;
		MAD,    //Madagascar;
		MOZ,    //Mozambique;
		NAM,    //Namibia;
		RHO,    //Rhodesia;
		SAF,    //South Africa;
		AST,    //Australia;
		NZL,    //New Zealand;
		CAL,    //California;
		CAN,    //Canada;
		CSA,    //Confederate States;
		QUE,    //Quebec;
		CUB,    //Cuba;
		COS,    //Costa Rica;
		DOM,    //Dominican Republic;
		GUA,    //Guatemala;
		HAI,    //Haiti;
		HON,    //Honduras;
		NIC,    //Nicaragua;
		PAN,    //Panama;
		SAL,    //El Salvador;
		ARG,    //Argentina;
		BOL,    //Bolivia;
		BRA,    //Brazil;
		CHL,    //Chile;
		COL,    //Colombia;
		ECU,    //Ecuador;
		GUY,    //Guyana;
		MEX,    //Mexico;
		PAR,    //Paraguay;
		PRU,    //Peru;
		TEX,    //Texas;
		URU,    //Uruguay;
		VEN,    //Venezuela;
		countrycount	//size;
	};
	

}

namespace names
{

}