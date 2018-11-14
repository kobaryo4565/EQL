#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

//データを読み込み、グローバル配列に書き込む
BOOL read_data( HWND hDlg, FILE *hm, int channel )
{
  
	char cbuf[500];			// １行分のデータを読み込む文字列
	char *p, *context;		// strtok_sを使うために必要
	//static bool flag = TRUE;// 最初のデータの読み込み時はTRUE、後はFAULTにす
	int i = 0;
	//read_halo rh[30000];
	
	while ( fgets( cbuf, 501, hm ) != NULL ){		// データを最後まで読み込む
		
		p = strtok_s( cbuf, ",", &context ); //1回目の第一引数は、cbufで、２回目以降はNULLにするhttp://shuzo-kino.hateblo.jp/entry/2013/10/17/184936参照
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
	
	return TRUE;	// 戻り値TRUEを返す
}