#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

//星のデータを読み込み、構造体配列に書き込む
BOOL read_star(HWND hDlg, FILE *hm, int channel)
{
	//hipdata h[5000];        //星のデータを入れる構造体配列を宣言
	char cbuf[500];			// １行分のデータを読み込む文字列
	char *p, *context;		// strtok_sを使うために必要
	int i = 0;

	while (fgets(cbuf, 501, hm) != NULL) {		// データを最後まで読み込む

		p = strtok_s(cbuf, ",", &context);
		sscanf_s(p, "%d", &h[i].HIP);

		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].RA_h);
		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].RA_m);
		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].RA_s);


		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%d", &h[i].Dec_sig);
		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].Dec_d);
		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].Dec_m);
		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].Dec_s);


		p = strtok_s(NULL, ",", &context);
		sscanf_s(p, "%lf", &h[i].Mag);

		i++;

	}
	total_n2 = i;
	TCHAR msg[8];
	
	return TRUE;	// 戻り値TRUEを返す

}