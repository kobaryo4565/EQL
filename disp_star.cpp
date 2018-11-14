#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>



// ���̍��W�f�[�^���P�`�����l�����E�B���h�E�ɕ\������֐�
BOOL disp_star_xy(HDC hdc, RECT rect, HWND hDlg) //�������Axy���ʂɕ`�悷��֐�
{   
	COLORREF color;
	HPEN hPen_xy;
	int i;
	
    color = RGB(0,0, 0);/*RGB(255,241,0)*/	// �`�����l���P�͉��F
	hPen_xy = CreatePen(PS_SOLID, 9, color);
	SelectObject(hdc, hPen_xy);					// hdc�ŏ�L�̃y�����g�����߂ɑI��
	HBRUSH hBrush_xy, h01dBrush_xy;
	hBrush_xy = CreateSolidBrush(color);
	h01dBrush_xy = (HBRUSH)SelectObject(hdc, hBrush_xy);
	//int nop = rect.right - rect.left + 1; //�������̃s�N�Z���������߂�?
	//double ppd = (rect.bottom - rect.top) / 10.0;		// �c����1div�����艽�s�N�Z����

          for(i=0; i<=total_n2; i++){
			//star[i].x = (988.5*star[i].x)/20;
	        //star[i].y = (741*star[i].y)/20;  
			//star[i].x = star[i].x - (rect.right-rect.left)/2;
			star[i].y = (rect.bottom - rect.top) / 2 - star[i].y;

			star[i].x -= (rect.right - rect.left) / 2;
            //star[i].y += (rect.bottom - rect.top) / 2;
			
			int m;
			if(h[i].Mag < 0.0){
				
				for (m = 0; m <= 8; m += 1) {
					SetPixel(hdc, star[i].x - m, star[i].y, RGB(228, 0, 127)/*RGB(255, 255, 255)*/);
					SetPixel(hdc, star[i].x, star[i].y - m, RGB(228, 0, 127)/*RGB(255, 255, 255)*/);
					SetPixel(hdc, star[i].x, star[i].y, /*RGB(255, 255, 255)*/RGB(228, 0, 127));
					SetPixel(hdc, star[i].x + m, star[i].y, RGB(228, 0, 127)/* RGB(255, 255, 255)*/);
					SetPixel(hdc, star[i].x, star[i].y + m, RGB(228, 0, 127)/*RGB(255, 255, 255)*/);
				}
			}

			else if(h[i].Mag < 2.0){
				for (m = 0; m <= 6; m += 1) {
					SetPixel(hdc, star[i].x - m, star[i].y, RGB(255, 255, 255));
					SetPixel(hdc, star[i].x, star[i].y - m, RGB(255, 255, 255));
					SetPixel(hdc, star[i].x, star[i].y, RGB(255, 255, 255)/*RGB(173, 255, 47)*/);
					SetPixel(hdc, star[i].x + m, star[i].y, RGB(255, 255, 255));
					SetPixel(hdc, star[i].x, star[i].y + m, RGB(255, 255, 255));
				}
			}

			else if (h[i].Mag < 4.0) {
				for (m = 0; m <= 4; m += 1) {
					SetPixel(hdc, star[i].x - m, star[i].y, RGB(255, 255, 255));
					SetPixel(hdc, star[i].x, star[i].y - m, RGB(255, 255, 255));
					SetPixel(hdc, star[i].x, star[i].y, RGB(255, 255, 255)/*RGB(173, 255, 47)*/);
					SetPixel(hdc, star[i].x + m, star[i].y, RGB(255, 255, 255));
					SetPixel(hdc, star[i].x, star[i].y + m, RGB(255, 255, 255));
				}
			}

			else {
				SetPixel(hdc, star[i].x - 2, star[i].y, RGB(255, 255, 255));
				SetPixel(hdc, star[i].x, star[i].y - 2, RGB(255, 255, 255));
				SetPixel(hdc, star[i].x, star[i].y, RGB(255, 255, 255)/*RGB(173, 255, 47)*/);
				SetPixel(hdc, star[i].x + 2, star[i].y, RGB(255, 255, 255));
				SetPixel(hdc, star[i].x, star[i].y + 2, RGB(255, 255,255));
			}
			
		}

		   //�ǋL�F�����`��
    //for (int i = 0; i <  rect.right - rect.left; i++)
        //SetPixel(hdc, i, rect.bottom / 2, RGB(255, 0, 0));

	

	DeleteObject(hPen_xy);	// �y����j������
	DeleteObject(hBrush_xy);
	DeleteObject(h01dBrush_xy);
	
	



	return TRUE;	// �߂�lTRUE��Ԃ�
}
