#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

xyz Cordi_Trans2(xyz P, double theta) //‚š²‰ñ‚è‚É‰ñ“]‚³‚¹‚éÀ•W•ÏŠ·iEQL‚ªxz–Ê“à‚É‚¢‚é‚æ‚¤‚Éj
{
	xyz a;

	a.x =   P.x*cos(theta) + P.y*sin(theta);
	a.y = - P.x*sin(theta) + P.y*cos(theta) ;
	a.z =   P.z;
	
	return a;

}

/*int i=0;
	int m = 0;
	cordi_trans2 ct2[25000];

	for( i=0; i<=total_n-1; i=i+1){

		ct2[i].theta = atan2((trans1+i)->YEQL, (trans1+i)->XEQL);  //YEQL‚ªí‚É‚O

		ct2[i].XEQL = (trans1+i)->XEQL * cos(ct2[i].theta) + (trans1+i)->YEQL * sin(ct2[i].theta);
		ct2[i].YEQL = 0;
		ct2[i].ZEQL = (trans1+i)->ZEQL;

		ct2[i].XEARTH = (trans1+i)->XEARTH * cos(ct2[i].theta) + (trans1+i)->YEARTH * sin(ct2[i].theta);
		ct2[i].YEARTH = (trans1+i)->YEARTH * cos(ct2[i].theta) - (trans1+i)->XEARTH * sin(ct2[i].theta);
		ct2[i].ZEARTH = (trans1+i)->ZEARTH;

		ct2[i].XSUN = (trans1+i)->XSUN * cos(ct2[i].theta) + (trans1+i)->YSUN * sin(ct2[i].theta);
		ct2[i].YSUN = (trans1+i)->YSUN * cos(ct2[i].theta) - (trans1+i)->XSUN * sin(ct2[i].theta);
		ct2[i].ZSUN = (trans1+i)->ZSUN;

		for (m = 0; m < total_n2; m++) {
			ct2[i].star[m].xstar = (hip+m)->xstar * cos(ct2[i].theta) + (hip+m)->ystar * sin(ct2[i].theta);
			ct2[i].star[m].ystar = (hip+m)->ystar * cos(ct2[i].theta) - (hip+m)->xstar * sin(ct2[i].theta);
			ct2[i].star[m].zstar = (hip+m)->zstar;
		}

		trans2 = &ct2[0];
	}*/