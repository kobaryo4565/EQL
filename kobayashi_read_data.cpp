#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

//�f�[�^��ǂݍ��݁A�O���[�o���z��ɏ�������
BOOL read_data( HWND hDlg, FILE *hm, int channel )
{
  
	char cbuf[500];			// �P�s���̃f�[�^��ǂݍ��ޕ�����
	char *p, *context;		// strtok_s���g�����߂ɕK�v
	//static bool flag = TRUE;// �ŏ��̃f�[�^�̓ǂݍ��ݎ���TRUE�A���FAULT�ɂ�
	int i = 0;
	//read_halo rh[30000];
	
	while ( fgets( cbuf, 501, hm ) != NULL ){		// �f�[�^���Ō�܂œǂݍ���
		
		p = strtok_s( cbuf, ",", &context ); //1��ڂ̑������́Acbuf�ŁA�Q��ڈȍ~��NULL�ɂ���http://shuzo-kino.hateblo.jp/entry/2013/10/17/184936�Q��
		    sscanf_s( p, "%lf", &rh[i].ET );
			
		p = strtok_s( NULL, ",", &context );
	     sscanf_s( p, "%lf", &rh[i].XEQL);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].YEQL);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].ZEQL);
		
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VXEQL);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VYEQL);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VZEQL);


		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].XMOON);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].YMOON);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].ZMOON);

		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VXMOON);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VYMOON);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VZMOON);
		

		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].XSUN);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].YSUN);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].ZSUN);

		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VXSUN);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VYSUN);
		p = strtok_s( NULL, ",", &context );
		 sscanf_s( p, "%lf", &rh[i].VZSUN);

	  i++;	
	}

	 total_n = i;
	
	return TRUE;	// �߂�lTRUE��Ԃ�
}