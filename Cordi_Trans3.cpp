#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

 xyz Cordi_Trans3(xyz P, double theta) //y²‰ñ‚è‚É‰ñ“]‚³‚¹‚éÀ•W•ÏŠ·iEQL‚ªz²ã‚É‚È‚é‚æ‚¤‚Éj
{
	xyz a;
	a.x = P.x*cos(theta) - P.z*sin(theta);
	a.y = P.y;
	a.z = P.x*sin(theta) + P.z*cos(theta);

	return a;

}

/*int i=0;
	int m = 0;
	cordi_trans3 ct3[25000];

	for( i=0; i<=total_n-1; i=i+1){

		ct3[i].d = atan2((trans2+i)->XEQL, (trans2+i)->ZEQL); //XEQL‚ªí‚É‚O

		ct3[i].XEQL = 0;
		ct3[i].YEQL = 0;
		ct3[i].ZEQL = (trans2+i)->XEQL * sin(ct3[i].d) + (trans2+i)->ZEQL * cos(ct3[i].d);

		ct3[i].XEARTH = (trans2+i)->XEARTH * cos(ct3[i].d) - (trans2+i)->ZEARTH * sin(ct3[i].d);
		ct3[i].YEARTH = (trans2+i)->YEARTH;
		ct3[i].ZEARTH = (trans2+i)->XEARTH * sin(ct3[i].d) + (trans2+i)->ZEARTH * cos(ct3[i].d);

		ct3[i].XSUN = (trans2+i)->XSUN * cos(ct3[i].d) - (trans2+i)->ZSUN * sin(ct3[i].d);
		ct3[i].YSUN = (trans2+i)->YSUN;
		ct3[i].ZSUN = (trans2+i)->XSUN * sin(ct3[i].d) + (trans2+i)->ZSUN * cos(ct3[i].d);

		for (m = 0; m <= total_n2; m = m + 1) {
			ct3[i].star[m].xstar = (trans2+i)-> star[m].xstar * cos(ct3[i].d) - (trans2+i)-> star[m].zstar * sin(ct3[i].d);
			ct3[i].star[m].ystar = (trans2+i)-> star[m].ystar;
			ct3[i].star[m].zstar = (trans2+i)-> star[m].xstar * sin(ct3[i].d) + (trans2+i)-> star[m].zstar * cos(ct3[i].d);
		}
		
	}
    trans3 = &ct3[0];*/