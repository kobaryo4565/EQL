#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

xyz Cordi_Trans1(xyz P1, xyz P2) //���_�����ɕ��s�ړ�������W�ϊ�
{
	xyz a;
		
		a.x = P1.x -  P2.x;
		a.y = P1.y -  P2.y;
		a.z = P1.z -  P2.z;
	
	return a;

}


