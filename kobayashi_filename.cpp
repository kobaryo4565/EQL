#include  "kobayashi.h"

//ファイルを選択し、そのパス名を得る関数
char* filename()
{
	OPENFILENAME	fname;
	static char		fn[256];
	static char		filefilter[] = "すべてのファイル(*.*)\0*.*\0\0";
	/*"テキストファイル(*.txt)\0*.txt\0";*/

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
