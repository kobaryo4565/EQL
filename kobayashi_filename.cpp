#include  "kobayashi.h"

//�t�@�C����I�����A���̃p�X���𓾂�֐�
char* filename()
{
	OPENFILENAME	fname;
	static char		fn[256];
	static char		filefilter[] = "���ׂẴt�@�C��(*.*)\0*.*\0\0";
	/*"�e�L�X�g�t�@�C��(*.txt)\0*.txt\0";*/

	memset( &fname, 0, sizeof(OPENFILENAME) );
	fname.lStructSize    = sizeof(OPENFILENAME);
	fname.lpstrFilter    = filefilter;
	fname.nFilterIndex   = 1;
	fname.lpstrFile      = fn;
	fname.nMaxFile       = sizeof(fn);
	fname.Flags          = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if( !GetOpenFileName( &fname ) )  return NULL;

	return fn;
}
