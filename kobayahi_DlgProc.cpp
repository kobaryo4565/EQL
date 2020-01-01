#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>
//#define ID_MYTIMER 1

int nAddress = 0;
int id = 0;
BOOL flag_open = false;

//�l�X�ȍ�Ƃ̒��S�ƂȂ�_�C�A���O
BOOL CALLBACK MyDlgProc( HWND hDlg, UINT msg, WPARAM wp, LPARAM lp )
{
	char	*fname;		// �t�@�C����
	static FILE *fp;	// FILE�ւ̃|�C���^
	static FILE *fp1;

	int year, month, day, hour, min, sec;	//ET��b�ŋ��߂����N, ��, ��, ��, ��, �b(UTC)
	
	int i;
	int n;
	static HWND hCombo1;
	TCHAR szCombo[3][16] = { TEXT("6 �b/����"), TEXT("0.6 �b/����"), TEXT("0.06 �b/����")};
	TCHAR szText[3][64];
	static HWND hMain;
	int oi;
	SYSTEMTIME st;
	

	
	switch(msg){
		case WM_INITDIALOG:
			//2019�N12��26��12��0��0�b(UTC)�ɏ����ݒ肷��B
			GetSystemTime(&st);
			SetDlgItemInt(hDlg, IDC_EDIT_Y, st.wYear, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_M,  st.wMonth, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_D,  st.wDay, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_H,  st.wHour, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_MIN,  st.wMinute, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_S,  st.wSecond, FALSE);

			CheckDlgButton( hDlg, IDC_CHECK_DISPLAY1, BST_UNCHECKED);

			hMain = GetParent(hDlg);
			//�R���g���[���̃n���h�����擾
			hCombo1 = GetDlgItem(hDlg, IDC_COMBO1);
			//�R���{�{�b�N�X�ɕ������������
			for(n = 0; n < 3; n++){
				ComboBox_AddString(hCombo1, szCombo[n]);
			}
		    //MessageBox(NULL, szCombo[4], "�������\��", MB_OK);
			
			//�R���{�{�b�N�X�̏����l
			ComboBox_SetCurSel(hCombo1, nAddress);
	
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wp)){
				case IDC_BUTTON_OPEN1:	// CH1�̃t�@�C�����J������
					if(flag_open == true){
						MessageBox(NULL ,"���Ƀt�@�C�����J���Ă��܂�", "�G���[", MB_OK);
					    break;
					}
					if( fname = filename() ){
						if ( fp ) fclose ( fp );
						fopen_s ( &fp, fname, "r" );
						//read_data(hDlg, fp, 1);
					//	MessageBox(NULL ,"���W�t�@�C���ǂݍ��ݐ���", "CH1", MB_OK);// �t�@�C�����e�L�X�g�ǂݍ��݃��[�h�ŊJ��

						
						
						if (fname = filename()) {
							if (fp1) fclose(fp1);
							fopen_s(&fp1, fname, "r");
							read_star(hDlg, fp1, 1);
							//MessageBox(NULL, "���̃f�[�^�ǂݍ��ݐ���", "CH1", MB_OK);
							fclose(fp1);
						}
					
						if (read_data(hDlg, fp, 1)) 			// CH1�œǂݍ���
							CheckDlgButton(hDlg, IDC_CHECK_DISPLAY1, BST_CHECKED);// �`�F�b�N�{�^�����u�\���v�Ƃ���
						
						fclose( fp );
						InvalidateRect(hWnd, NULL, TRUE);
			        }
					
					flag_open = !flag_open;	
					return TRUE;

				case ID_OK://OK�{�^���������ꂽ
					if(flag_open == false){
						MessageBox(NULL ,"�t�@�C�����I������Ă��܂���", "�G���[", MB_OK);
					    break;
					}
					KillTimer(hWnd_bitmap, 1);
					KillTimer(hWnd_bitmap, 2);
					year = GetDlgItemInt(hDlg, IDC_EDIT_Y, NULL, FALSE);	//�G�f�B�b�g�{�b�N�X����N��ǂݍ���
					month = GetDlgItemInt(hDlg, IDC_EDIT_M, NULL, FALSE);	//�ȉ����l
					day = GetDlgItemInt(hDlg, IDC_EDIT_D, NULL, FALSE);
					hour = GetDlgItemInt(hDlg, IDC_EDIT_H, NULL, FALSE);
					min = GetDlgItemInt(hDlg, IDC_EDIT_MIN, NULL, FALSE);
					sec = GetDlgItemInt(hDlg, IDC_EDIT_S, NULL, FALSE);

					//�֐�et�ɏ�L�������Ƃ��ēn���ƁA�b�ŕ\���ꂽElapsed Time���߂����B
					Time =  et(year, month, day, hour, min, sec);

					//sprintf_s(szBuf, 256, "%lf %lf %lf", Time, rh[0].ET, rh[total_n-1].ET);
					//MessageBox(NULL, szBuf, "time", MB_OK);

					for(i=0; i<=total_n; i++){
						if(Time < rh[0].ET || rh[total_n-1].ET < Time){
							MessageBox(NULL ,"�~�b�V�������ԊO�ł�", "�G���[", MB_OK);
							return FALSE;
					    }
						  else if(rh[i].ET > Time){
							g = i-1;
							dt = Time - rh[g].ET;
							break;
						  }

					}


					eql.x = rh[g].VXEQL * dt + rh[g].XEQL;
					eql.y = rh[g].VYEQL * dt + rh[g].YEQL;
					eql.z = rh[g].VZEQL * dt + rh[g].ZEQL;

					moon.x = rh[g].VXMOON * dt + rh[g].XMOON;
					moon.y = rh[g].VYMOON * dt + rh[g].YMOON;
					moon.z = rh[g].VZMOON * dt + rh[g].ZMOON;

					sun.x = rh[g].VXSUN * dt + rh[g].XSUN;
					sun.y = rh[g].VYSUN * dt + rh[g].YSUN;
					sun.z = rh[g].VZSUN * dt + rh[g].ZSUN;

					earth.x = 0;
					earth.y = 0;
					earth.z = 0;

					//sprintf_s(szBuf, 256, "%lf %lf %lf %lf %lf %lf", eql.x , eql.y, eql.z, moon.x, moon.y, moon.z);
					//MessageBox(NULL, szBuf, "eql.x, moon.x", MB_OK);

					EQL_MOON = sqrtf((moon.x - eql.x)*(moon.x - eql.x) + (moon.y - eql.y)*(moon.y - eql.y) + (moon.z - eql.z)*(moon.z - eql.z));
		            SUN_MOON = sqrtf(sun.x * sun.x + sun.y * sun.y + sun.z * sun.z);
		            EARTH_MOON = sqrtf(moon.x * moon.x + moon.y * moon.y + moon.z * moon.z);
	
		            //t = 360*3474/(2*M_PI*EQL_MOON);//�����a���v�Z
		            s = (3474.0*0.00005) / EQL_MOON; //���̑��ΓI�ȑ傫�����v�Z

					//sprintf_s(szBuf, 256, "%lf %lf", EQL_MOON, s);
					//MessageBox(NULL, szBuf, "EQL_MOON, s", MB_OK);

					for(i=0; i<=total_n2; i++){
					 RA = 2*M_PI*(h[i].RA_h + h[i].RA_m/60 + h[i].RA_s/3600)/24; //�P�ʂ����œ���
		             DEC = 2*M_PI*(h[i].Dec_d + h[i].Dec_m/60 + h[i].Dec_s/3600)/360; //�P�ʂ�x�œ���
		               if (h[i].Dec_sig == FALSE) {
			              DEC = -DEC;
		               }
		             koukei = atan2(sin(M_PI*23.43 / 180)*sin(DEC)+cos(M_PI*23.43 / 180)*cos(DEC)*sin(RA),cos(DEC)*cos(RA)); //�P�ʂ�rad
		               if (koukei < 0) {
			              koukei = koukei + 2 * M_PI; //�P�ʂ�rad
		               }
		             koui = asin(cos(M_PI*23.43 / 180)*sin(DEC) - sin(M_PI*23.43 / 180)*cos(DEC)*sin(RA));

		             star[i].x = cos(koui)*cos(koukei);
		             star[i].y = cos(koui)*sin(koukei);
		             star[i].z = sin(koui);
					}

					
					//sprintf_s(szBuf, 256, "%lf %lf %lf", star[0].x, star[0].y, star[0].z);
					//MessageBox(NULL, szBuf, "���f�[�^1", MB_OK);
		
					//���W�ϊ��P
					eql = Cordi_Trans1(eql, moon);
					moon = Cordi_Trans1(moon, moon);
					sun = Cordi_Trans1(sun, moon);
					earth = Cordi_Trans1(earth, moon);

					
				
					//���W�ϊ��Q
					theta = atan2(eql.y, eql.x);
					//sprintf_s(szBuf, 256, "%lf", theta);
					//MessageBox(NULL, szBuf, "�p�x1", MB_OK);
					eql = Cordi_Trans2(eql, theta);
					sun = Cordi_Trans2(sun, theta);
					earth = Cordi_Trans2(eql, theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
					}

					//sprintf_s(szBuf, 256, "%lf %lf %lf", star[0].x, star[0].y, star[0].z);
					//MessageBox(NULL, szBuf, "���f�[�^2", MB_OK);
					
					//���W�ϊ��R
					theta = atan2(eql.x, eql.z);
					//sprintf_s(szBuf, 256, "%lf", theta);
					//MessageBox(NULL, szBuf, "�p�x2", MB_OK);
					eql = Cordi_Trans3(eql,theta);
					sun = Cordi_Trans3(sun,theta);
					earth = Cordi_Trans3(earth,theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans3(star[i], theta);
					}

					//sprintf_s(szBuf, 256, "%lf %lf %lf", star[0].x, star[0].y, star[0].z);
					//MessageBox(NULL, szBuf, "���f�[�^3", MB_OK);
					

					//���W�ϊ��S
					theta = atan2(-sun.x, sun.y);
					//sprintf_s(szBuf, 256, "%lf", theta);
					//MessageBox(NULL, szBuf, "�p�x3", MB_OK);
					eql2 = Cordi_Trans2(eql,theta);
					sun2 = Cordi_Trans2(sun,theta);
					earth2 = Cordi_Trans2(earth,theta);
					for(i=0; i<=total_n2; i++){
						star_mm[i] = Cordi_Trans2(star[i], theta);
						if(star_mm[i].z < 0){
							star_mm[i].x = star_mm[i].x * (-50 / star_mm[i].z);
					        star_mm[i].y = star_mm[i].y * (-50 / star_mm[i].z);

					       starx_pix[i] =  /*(988.5*star[i].x)/20*/(star_mm[i].x) / 2 * (988.5 / 10);
					       stary_pix[i] = /*(741*star[i].y)/20*/(star_mm[i].y) / 2 * (741 / 10);

						  
				       }
					}

					//sprintf_s(szBuf, 256, "%lf %lf %lf %lf %lf", star[0].x, star[0].y, star[0].z, starx_pix[0],stary_pix[0]);
					//MessageBox(NULL, szBuf, "���f�[�^4", MB_OK);

					if(sun2.y > 0){
					  theta = atan2(-sun.x, sun.y) + M_PI;
					  //sprintf_s(szBuf, 256, "%lf", theta);
					  //MessageBox(NULL, szBuf, "�p�x4", MB_OK);
					  eql2 = Cordi_Trans2(eql,theta);
					  sun2 = Cordi_Trans2(sun,theta);
					  earth2 = Cordi_Trans2(earth,theta);
					 for(i=0; i<=total_n2; i++){
						star_mm[i] = Cordi_Trans2(star[i], theta);
						if(star_mm[i].z < 0){
							star_mm[i].x = star_mm[i].x * (-50 / star_mm[i].z);
					        star_mm[i].y = star_mm[i].y * (-50 / star_mm[i].z);

					       starx_pix[i] =  /*(988.5*star[i].x)/20*/(star_mm[i].x) / 2 * (988.5 / 10);
					       stary_pix[i] = /*(741*star[i].y)/20*/(star_mm[i].y) / 2 * (741 / 10);
				       }

					}
					}
					asdf(Time);
					InvalidateRect(hWnd_bitmap, NULL, FALSE);
					return TRUE;
                
				case ID_Anime:
					if(flag_open == false){
						MessageBox(NULL ,"�t�@�C�����I������Ă��܂���", "�G���[", MB_OK);
					    break;
					}
					KillTimer(hWnd_bitmap, 2);
					switch(nAddress){
					case 0:
						SetTimer(hWnd_bitmap, ID_MYTIMER, 1000, NULL);
						break;

					case 1:
						SetTimer(hWnd_bitmap, ID_MYTIMER, 100, NULL);
						break;

					case 2:
						SetTimer(hWnd_bitmap, ID_MYTIMER, 10, NULL);
						break;

					}

					return TRUE;


				case IDC_COMBO1:
					id = ComboBox_GetCurSel(hCombo1);
					nAddress = id;
					return TRUE;

				case ID_STOP:
					KillTimer(hWnd_bitmap, 1);
					KillTimer(hWnd_bitmap, 2);
					asdf(rh[g].ET);
					return TRUE;

				case ID_NOW:
					if(flag_open == false){
						MessageBox(NULL ,"�t�@�C�����I������Ă��܂���", "�G���[", MB_OK);
					    break;
					}
					KillTimer(hWnd_bitmap, 1);
					SetTimer(hWnd_bitmap, ID_MYTIMER_now, 1000, NULL);
					return TRUE;
					


				case IDCANCEL:				//�E��́~�N���b�N�ŏI��
					PostQuitMessage(0);
					DestroyWindow (hWnd);
					
					DestroyWindow (hDlg);
					return TRUE;

						}
			return TRUE;

	}
	return FALSE;
}
