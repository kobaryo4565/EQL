#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>


char szClassName[] = "image";	// 全体表示用ウィンドウクラスの名
char szClassName6[] = "image_bitmap";
HWND hWnd;						// 全体表示用ウィンドウのハンドル
HWND hWnd_bitmap;
HWND hDlg;						// モードレスダイアログボックスのハンド
char szBuf[256];
SHORT xs, xe;					// 範囲を指定する時の左右の点に対応するマウス位置
int total_n;
int total_n2;
int g = 0;


xyz eql, moon, sun, earth, star[5000];
double EQL_MOON, SUN_MOON, EARTH_MOON;
double s;
double starx[5000], stary[5000];
double starx2[5000], stary2[5000];


//read_halo *halo;
//hipdata *hip;
xyz *trans;

hipdata h[5000]; 
read_halo rh[30000];


int WINAPI WinMain( HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow )
{
	MSG msg;
	BOOL bRet;
	RECT rect;

// ダイアログボックスの作成
	hDlg = CreateDialog(hCurInst, "MYDLG", HWND_DESKTOP, (DLGPROC)MyDlgProc);
	ShowWindow(hDlg, nCmdShow);
	UpdateWindow(hDlg);

// プロット用ウィンドウクラスを登録し作成する
	
	if (!InitApp_bitmap(hCurInst))
		return FALSE;
	if (!InitInstance_bitmap(hCurInst, nCmdShow))
		return FALSE;

// xs, xeの初期値としてウィンドウの両端を入力する
	GetClientRect( hWnd, &rect );	// ウィンドウの描画領域を得る
	xs = (int)rect.left;			// マウス設定は画面の左端と
	xe = (int)rect.right;			// 右端を初期値とする。


	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			MessageBox(NULL, "GetMeseeageエラー", "Error", MB_OK);
			break;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}


ATOM InitApp_bitmap( HINSTANCE hInst_bitmap )
{
	WNDCLASSEX  wc;						//新しく作る画像用ウインドウクラス
	wc.cbSize		= sizeof(WNDCLASSEX);
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= WndProc_bitmap;				//このクラスの持つウインドプロシージャ
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInst_bitmap;
	wc.hIcon		= (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor		= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	= NULL;
	wc.lpszClassName= (LPCSTR)szClassName6;	//このクラスの名前
	wc.hIconSm		= (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));	
}



BOOL InitInstance_bitmap(HINSTANCE hInst_bitmap, int nCmdShow)
{

	// プロット用ウィンドウの作成
	hWnd_bitmap = CreateWindowEx(WS_EX_COMPOSITED,szClassName6,	// クラスの名前
			"DELPHINUSの5倍の視野",		// タイトルバーに表示される
			WS_OVERLAPPEDWINDOW,		// ウィンドウの種類
			CW_USEDEFAULT,	//x座標
			CW_USEDEFAULT,	//y座標
			988.5,	//幅
			741,	//高さ
			NULL,	// 親ウィンドウのハンドル、親を作るときはNULL 
			NULL,	// メニューハンドル、クラスメニューを作るときはNULL
			hInst_bitmap,	// インスタンスハンドル
			NULL );
	if(!hWnd_bitmap)
		return FALSE;
	ShowWindow(hWnd_bitmap, nCmdShow);
	UpdateWindow(hWnd_bitmap);
	return TRUE;


	
	
}
