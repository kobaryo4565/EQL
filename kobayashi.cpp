#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>


char szClassName[] = "image";	// �S�̕\���p�E�B���h�E�N���X�̖�
char szClassName6[] = "image_bitmap";
HWND hWnd;						// �S�̕\���p�E�B���h�E�̃n���h��
HWND hWnd_bitmap;
HWND hDlg;						// ���[�h���X�_�C�A���O�{�b�N�X�̃n���h
char szBuf[256];
SHORT xs, xe;					// �͈͂��w�肷�鎞�̍��E�̓_�ɑΉ�����}�E�X�ʒu
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

// �_�C�A���O�{�b�N�X�̍쐬
	hDlg = CreateDialog(hCurInst, "MYDLG", HWND_DESKTOP, (DLGPROC)MyDlgProc);
	ShowWindow(hDlg, nCmdShow);
	UpdateWindow(hDlg);

// �v���b�g�p�E�B���h�E�N���X��o�^���쐬����
	
	if (!InitApp_bitmap(hCurInst))
		return FALSE;
	if (!InitInstance_bitmap(hCurInst, nCmdShow))
		return FALSE;

// xs, xe�̏����l�Ƃ��ăE�B���h�E�̗��[����͂���
	GetClientRect( hWnd, &rect );	// �E�B���h�E�̕`��̈�𓾂�
	xs = (int)rect.left;			// �}�E�X�ݒ�͉�ʂ̍��[��
	xe = (int)rect.right;			// �E�[�������l�Ƃ���B


	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			MessageBox(NULL, "GetMeseeage�G���[", "Error", MB_OK);
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
	WNDCLASSEX  wc;						//�V�������摜�p�E�C���h�E�N���X
	wc.cbSize		= sizeof(WNDCLASSEX);
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= WndProc_bitmap;				//���̃N���X�̎��E�C���h�v���V�[�W��
	wc.cbClsExtra	= 0;
	wc.cbWndExtra	= 0;
	wc.hInstance	= hInst_bitmap;
	wc.hIcon		= (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor		= (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName	= NULL;
	wc.lpszClassName= (LPCSTR)szClassName6;	//���̃N���X�̖��O
	wc.hIconSm		= (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

	return (RegisterClassEx(&wc));	
}



BOOL InitInstance_bitmap(HINSTANCE hInst_bitmap, int nCmdShow)
{

	// �v���b�g�p�E�B���h�E�̍쐬
	hWnd_bitmap = CreateWindowEx(WS_EX_COMPOSITED,szClassName6,	// �N���X�̖��O
			"DELPHINUS��5�{�̎���",		// �^�C�g���o�[�ɕ\�������
			WS_OVERLAPPEDWINDOW,		// �E�B���h�E�̎��
			CW_USEDEFAULT,	//x���W
			CW_USEDEFAULT,	//y���W
			988.5,	//��
			741,	//����
			NULL,	// �e�E�B���h�E�̃n���h���A�e�����Ƃ���NULL 
			NULL,	// ���j���[�n���h���A�N���X���j���[�����Ƃ���NULL
			hInst_bitmap,	// �C���X�^���X�n���h��
			NULL );
	if(!hWnd_bitmap)
		return FALSE;
	ShowWindow(hWnd_bitmap, nCmdShow);
	UpdateWindow(hWnd_bitmap);
	return TRUE;


	
	
}
