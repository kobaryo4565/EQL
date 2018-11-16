#include "kobayashi.h"

#include <iostream>

//年月日時分秒から、J2000.0からの秒数を計算する関数
int et(int year, int month, int day, int hour, int min, int sec)
{
	tm epoch0;	//tmはtime.h内で定義されている構造体、epoch0はElapsed Timeの基準となるJ2000.0
	epoch0.tm_year = 2000 - 1900;	//1900年から数える
	epoch0.tm_mon = 0;				//1月は0、12月は11
	epoch0.tm_mday = 1;				//普通に1月内の日
	epoch0.tm_hour = 12;			//普通に時
	epoch0.tm_min = 0;				//普通に分
	epoch0.tm_sec = 0;				//普通に秒

	tm epoch1;
	epoch1.tm_year = year - 1900;
	epoch1.tm_mon = month - 1;
	epoch1.tm_mday = day;
	epoch1.tm_hour = hour;
	epoch1.tm_min = min;
	epoch1.tm_sec = sec;

	time_t time0 = mktime(&epoch0);	//time_t型というものがある
	time_t time1 = mktime(&epoch1);	//mktimeは1970/1/1 0:00:00からの経過秒数を計算する(以下を参照)
									//https://qiita.com/edo_m18/items/364ffc6713b81c4d1c87
									//http://hitorilife.com/time.php

	return (int)difftime(time1, time0);	//difftimeも上記を参照
}

//J2000.0から現在までの秒数を計算する関数
int now()
{
	tm epoch0;
	epoch0.tm_year = 2000 - 1900;
	epoch0.tm_mon = 0;
	epoch0.tm_mday = 1;
	epoch0.tm_hour = 12;
	epoch0.tm_min = 0;
	epoch0.tm_sec = 0;

	time_t time0 = mktime(&epoch0);

	time_t time1 = time(NULL);	//timeはPCの現在時刻を得て、time_t型の変数に格納する

	

	return (int)(difftime(time1, time0) - 32400.);	//timeで得られる時刻は日本時間なのでUTにするため9時間(32400秒)引く。
}

//J2000.0からの経過秒数を年月日時分秒に直す関数
using namespace std;

void asdf(time_t x){
	time_t foo = 946728000 + x;
	tm *bar = gmtime(&foo);
	char buf[80];
	strftime(buf,sizeof(buf), "%Y-%m-%d %H:%M:%S",bar);
	cout << buf << endl;
	sprintf_s(szBuf, 256, "%s", buf);
	MessageBox(NULL, szBuf, "年月日時分秒", MB_OK);
}