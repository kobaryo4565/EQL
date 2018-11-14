#include "kobayashi.h"

// ウィンドウ中に目盛軸を描く関数
BOOL disp_axes2( HDC hdc, RECT rect )
{
	int i, x, y;	// forで使う変数iと、縦横のグリッド線を引くときのx座標とy座標
	
	HPEN hPen_a = CreatePen( PS_DOT, 0, RGB(0,0,0));		// 黒色、破線のペンを作る(注：白と黒の破線になる)
	SelectObject( hdc, hPen_a );							// hdcで上記のペンを使うために選ぶ
	double hdiv = (double)(rect.right - rect.left)/10.0;
	double vdiv = (double)(rect.bottom - rect.top)/10.0;

	for ( i=0; i<=10; i++ ) {	// 縦線を描く
		if (i == 5) {
			x = (int)(hdiv * (double)i + 0.5);
			MoveToEx(hdc, x, rect.top, NULL);	//ペンを移動する
			LineTo(hdc, x, rect.bottom);	//線を引く
		}

		if ( i == 4 ){
			x = (int)(hdiv * (double)i + 0.5);
			MoveToEx(hdc, x, rect.bottom*3/10, NULL);	//ペンを移動する
			LineTo(hdc, x, rect.bottom/2);	//線を引く
		}
		
		if (i == 6) {
			x = (int)(hdiv * (double)i + 0.5);
			MoveToEx(hdc, x, rect.bottom * 3/10, NULL);	//ペンを移動する
			LineTo(hdc, x, rect.bottom /2);	//線を引く
		}
	}


	for ( i=0; i<=10; i++ ) {		// 横線を描く
		
		if ( i == 3 ){
			y = (int)(vdiv * (double)i + 0.5);
			MoveToEx(hdc, rect.right*2/5, y, NULL);
			LineTo(hdc, rect.right*3/5, y);
		}
		
		if ( i == 5 ){
		y = (int)( vdiv * (double)i + 0.5 );
		MoveToEx(hdc, rect.left, y, NULL);
		LineTo	(hdc, rect.right, y);
		}

		}

	

	DeleteObject( hPen_a );	// ペンを破棄する

	return TRUE;
}
