#include "kobayashi.h"

#include <iostream>

//�N���������b����AJ2000.0����̕b�����v�Z����֐�
int et(int year, int month, int day, int hour, int min, int sec)
{
	tm epoch0;	//tm��time.h���Œ�`����Ă���\���́Aepoch0��Elapsed Time�̊�ƂȂ�J2000.0
	epoch0.tm_year = 2000 - 1900;	//1900�N���琔����
	epoch0.tm_mon = 0;				//1����0�A12����11
	epoch0.tm_mday = 1;				//���ʂ�1�����̓�
	epoch0.tm_hour = 12;			//���ʂɎ�
	epoch0.tm_min = 0;				//���ʂɕ�
	epoch0.tm_sec = 0;				//���ʂɕb

	tm epoch1;
	epoch1.tm_year = year - 1900;
	epoch1.tm_mon = month - 1;
	epoch1.tm_mday = day;
	epoch1.tm_hour = hour;
	epoch1.tm_min = min;
	epoch1.tm_sec = sec;

	time_t time0 = mktime(&epoch0);	//time_t�^�Ƃ������̂�����
	time_t time1 = mktime(&epoch1);	//mktime��1970/1/1 0:00:00����̌o�ߕb�����v�Z����(�ȉ����Q��)
									//https://qiita.com/edo_m18/items/364ffc6713b81c4d1c87
									//http://hitorilife.com/time.php

	return (int)difftime(time1, time0);	//difftime����L���Q��
}

//J2000.0���猻�݂܂ł̕b�����v�Z����֐�
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

	time_t time1 = time(NULL);	//time��PC�̌��ݎ����𓾂āAtime_t�^�̕ϐ��Ɋi�[����

	

	return (int)(difftime(time1, time0) - 32400.);	//time�œ����鎞���͓��{���ԂȂ̂�UT�ɂ��邽��9����(32400�b)�����B
}

//J2000.0����̌o�ߕb����N���������b�ɒ����֐�
using namespace std;

void asdf(time_t x){
	time_t foo = 946728000 + x;
	tm *bar = gmtime(&foo);
	char buf[80];
	strftime(buf,sizeof(buf), "%Y-%m-%d %H:%M:%S",bar);
	cout << buf << endl;
	sprintf_s(szBuf, 256, "%s", buf);
	MessageBox(NULL, szBuf, "�N���������b", MB_OK);
}