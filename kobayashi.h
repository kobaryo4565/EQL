/************************************************************/
/*	�F�����J���[LeCroy�I�V����csv�ŕۑ������f�[�^�t�@�C����	*/
/*  �\�����A�f�[�^�������炵�ĕۑ�����v���O����			*/
/*�@�@�@						2009.08.31 <by Yanagisawa>	*/
/************************************************************/

#include  <stdio.h>
//#include  <string.h>
//#include  <stdlib.h>
#include  <windows.h>
#include  <windowsx.h>		// Button_SetCheck(hCHECK_SATURATION, BST_UNCHECKED)�Ȃǂ��g�����߂ɕK�v
#include  "resource.h"
#include <time.h>
#define ID_MYTIMER 1

typedef struct {
	double x,y,z;
}xyz; //���W������\����

BOOL CALLBACK MyDlgProc( HWND, UINT, WPARAM, LPARAM );		// �_�C�A���O�E�B���h�E�̃R�[���o�b�N�֐�
LRESULT CALLBACK WndProc_bitmap( HWND, UINT, WPARAM, LPARAM );
ATOM InitApp_bitmap( HINSTANCE );
BOOL InitInstance_bitmap( HINSTANCE, int );
char* filename();					// �t�@�C����I�����A���̃p�X���𓾂�֐�
BOOL read_data( HWND, FILE*, int );	// �P�`�����l�����̃f�[�^��ǂݍ��݁A�w�b�_�[�f�[�^���G�f�B�b�g�{�b�N�X�ɏ����o���֐�
BOOL disp_axes2( HDC, RECT );
xyz Cordi_Trans1(xyz, xyz);//���_�����ɕϊ�����֐�
xyz Cordi_Trans2(xyz, double);//Z�����ɉ�]������֐�
xyz Cordi_Trans3(xyz, double);//Y'�����ɉ�]������֐�
BOOL read_star(HWND, FILE*, int);
BOOL disp_star_xy(HDC, RECT, HWND);
int et(int, int, int, int, int, int); //�N���������b����j2000����̕b�����v�Z����֐�
int now(); //J2000���猻�݂܂ł̕b�����v�Z����֐�

extern char szBuf[256];	
extern HWND hWnd;						// �摜�p�E�B���h�E�̃n���h��
extern HWND hWnd_bitmap;
extern HWND hDlg;						// �_�C�A���O�{�b�N�X�̃n���h��
extern SHORT xs, xe;					// �͈͂��w�肷�鎞�̍��E�̓_�ɑΉ�����}�E�X�ʒu
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

	


