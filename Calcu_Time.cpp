#include "kobayashi.h"

#include <iostream>

//”NŒ“ú•ª•b‚©‚çAJ2000.0‚©‚ç‚Ì•b”‚ğŒvZ‚·‚éŠÖ”
int et(int year, int month, int day, int hour, int min, int sec)
{
	tm epoch0;	//tm‚Ítime.h“à‚Å’è‹`‚³‚ê‚Ä‚¢‚é\‘¢‘ÌAepoch0‚ÍElapsed Time‚ÌŠî€‚Æ‚È‚éJ2000.0
	epoch0.tm_year = 2000 - 1900;	//1900”N‚©‚ç”‚¦‚é
	epoch0.tm_mon = 0;				//1Œ‚Í0A12Œ‚Í11
	epoch0.tm_mday = 1;				//•’Ê‚É1Œ“à‚Ì“ú
	epoch0.tm_hour = 12;			//•’Ê‚É
	epoch0.tm_min = 0;				//•’Ê‚É•ª
	epoch0.tm_sec = 0;				//•’Ê‚É•b

	tm epoch1;
	epoch1.tm_year = year - 1900;
	epoch1.tm_mon = month - 1;
	epoch1.tm_mday = day;
	epoch1.tm_hour = hour;
	epoch1.tm_min = min;
	epoch1.tm_sec = sec;

	time_t time0 = mktime(&epoch0);	//time_tŒ^‚Æ‚¢‚¤‚à‚Ì‚ª‚ ‚é
	time_t time1 = mktime(&epoch1);	//mktime‚Í1970/1/1 0:00:00‚©‚ç‚ÌŒo‰ß•b”‚ğŒvZ‚·‚é(ˆÈ‰º‚ğQÆ)
									//https://qiita.com/edo_m18/items/364ffc6713b81c4d1c87
									//http://hitorilife.com/time.php

	return (int)difftime(time1, time0);	//difftime‚àã‹L‚ğQÆ
}

//J2000.0‚©‚çŒ»İ‚Ü‚Å‚Ì•b”‚ğŒvZ‚·‚éŠÖ”
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

	time_t time1 = time(NULL);	//time‚ÍPC‚ÌŒ»İ‚ğ“¾‚ÄAtime_tŒ^‚Ì•Ï”‚ÉŠi”[‚·‚é

	return (int)(difftime(time1, time0) - 32400.);	//time‚Å“¾‚ç‚ê‚é‚Í“ú–{ŠÔ‚È‚Ì‚ÅUT‚É‚·‚é‚½‚ß9ŠÔ(32400•b)ˆø‚­B
}


//J2000.0‚©‚ç‚ÌŒo‰ß•b”‚ğ”NŒ“ú•ª•b‚É’¼‚·ŠÖ”
using namespace std;
void asdf(time_t x){
	time_t foo = 946728000 + x;
	tm *bar = gmtime(&foo);
	_tcsftime(buf, sizeof(buf)/sizeof(TCHAR), _T("‹¦’è¢ŠE(UTC)\n%Y-%m-%d %H:%M:%S"), bar);
	cout << buf << endl;
}


