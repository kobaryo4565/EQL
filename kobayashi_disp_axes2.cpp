#include "kobayashi.h"

// �E�B���h�E���ɖڐ�����`���֐�
BOOL disp_axes2( HDC hdc, RECT rect )
{
	int i, x, y;	// for�Ŏg���ϐ�i�ƁA�c���̃O���b�h���������Ƃ���x���W��y���W
	
	HPEN hPen_a = CreatePen( PS_DOT, 0, RGB(0,0,0));		// ���F�A�j���̃y�������(���F���ƍ��̔j���ɂȂ�)
	SelectObject( hdc, hPen_a );							// hdc�ŏ�L�̃y�����g�����߂ɑI��
	double hdiv = (double)(rect.right - rect.left)/10.0;
	double vdiv = (double)(rect.bottom - rect.top)/10.0;

	for ( i=0; i<=10; i++ ) {	// �c����`��
		if (i == 5) {
			x = (int)(hdiv * (double)i + 0.5);
			MoveToEx(hdc, x, rect.top, NULL);	//�y�����ړ�����
			LineTo(hdc, x, rect.bottom);	//��������
		}

		if ( i == 4 ){
			x = (int)(hdiv * (double)i + 0.5);
			MoveToEx(hdc, x, rect.bottom*3/10, NULL);	//�y�����ړ�����
			LineTo(hdc, x, rect.bottom/2);	//��������
		}
		
		if (i == 6) {
			x = (int)(hdiv * (double)i + 0.5);
			MoveToEx(hdc, x, rect.bottom * 3/10, NULL);	//�y�����ړ�����
			LineTo(hdc, x, rect.bottom /2);	//��������
		}
	}


	for ( i=0; i<=10; i++ ) {		// ������`��
		
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

	

	DeleteObject( hPen_a );	// �y����j������

	return TRUE;
}
