#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>

//���̃f�[�^��ǂݍ��݁A�\���̔z��ɏ�������
BOOL read_star(HWND hDlg, FILE *hm, int channel)
{
	//hipdata h[5000];        //���̃f�[�^������\���̔z���錾
	char cbuf[500];			// �P�s���̃f�[�^��ǂݍ��ޕ�����
	char *p, *context;		// strtok_s���g�����߂ɕK�v
	int i = 0;

	while (fgets(cbuf, 501, hm) != NULL) {		// �f�[�^���Ō�܂œǂݍ���

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
	
	return TRUE;	// �߂�lTRUE��Ԃ�

}