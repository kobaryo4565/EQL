#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

xyz Cordi_Trans1(xyz P1, xyz P2) //Œ´“_‚ğŒ‚É•½sˆÚ“®‚·‚éÀ•W•ÏŠ·
{
	xyz a;
		
		a.x = P1.x -  P2.x;
		a.y = P1.y -  P2.y;
		a.z = P1.z -  P2.z;
	
	return a;

}


