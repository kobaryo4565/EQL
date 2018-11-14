/************************************************************/
/*	宇宙研カラーLeCroyオシロのcsvで保存したデータファイルを	*/
/*  表示し、データ数を減らして保存するプログラム			*/
/*　　　						2009.08.31 <by Yanagisawa>	*/
/************************************************************/

#include  <stdio.h>
//#include  <string.h>
//#include  <stdlib.h>
#include  <windows.h>
#include  <windowsx.h>		// Button_SetCheck(hCHECK_SATURATION, BST_UNCHECKED)などを使うために必要
#include  "resource.h"
#include <time.h>
#define ID_MYTIMER 1

typedef struct {
	double x,y,z;
}xyz; //座標を入れる構造体

BOOL CALLBACK MyDlgProc( HWND, UINT, WPARAM, LPARAM );		// ダイアログウィンドウのコールバック関数
LRESULT CALLBACK WndProc_bitmap( HWND, UINT, WPARAM, LPARAM );
ATOM InitApp_bitmap( HINSTANCE );
BOOL InitInstance_bitmap( HINSTANCE, int );
char* filename();					// ファイルを選択し、そのパス名を得る関数
BOOL read_data( HWND, FILE*, int );	// １チャンネル分のデータを読み込み、ヘッダーデータをエディットボックスに書き出す関数
BOOL disp_axes2( HDC, RECT );
xyz Cordi_Trans1(xyz, xyz);//原点を月に変換する関数
xyz Cordi_Trans2(xyz, double);//Z軸回りに回転させる関数
xyz Cordi_Trans3(xyz, double);//Y'軸回りに回転させる関数
BOOL read_star(HWND, FILE*, int);
BOOL disp_star_xy(HDC, RECT, HWND);
int et(int, int, int, int, int, int); //年月日時分秒からj2000からの秒数を計算する関数
int now(); //J2000から現在までの秒数を計算する関数

extern char szBuf[256];	
extern HWND hWnd;						// 画像用ウィンドウのハンドル
extern HWND hWnd_bitmap;
extern HWND hDlg;						// ダイアログボックスのハンドル
extern SHORT xs, xe;					// 範囲を指定する時の左右の点に対応するマウス位置
extern int total_n;
extern int total_n2;
extern xyz eql, moon, sun, earth, star[5000];
extern int g;
extern double EQL_MOON, SUN_MOON, EARTH_MOON;
extern double s;
extern double starx[5000], stary[5000];
extern double starx2[5000], stary2[5000];





typedef struct {
	double ET;
	double XEQL, YEQL, ZEQL;
	double VXEQL, VYEQL, VZEQL;
	double XSUN, YSUN, ZSUN;
	double VXSUN, VYSUN, VZSUN;
	double XMOON, YMOON, ZMOON;
	double VXMOON, VYMOON, VZMOON;
} read_halo;

extern read_halo rh[30000];

typedef struct {
	int HIP;
	double RA_h;
	double RA_m;
	double RA_s;
	int Dec_sig;
	double Dec_d;
	double Dec_m;
	double Dec_s;
	double Mag;
} hipdata;

extern hipdata h[5000]; 

	


