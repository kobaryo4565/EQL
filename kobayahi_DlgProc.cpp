#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>
//#define ID_MYTIMER 1




//様々な作業の中心となるダイアログ
BOOL CALLBACK MyDlgProc( HWND hDlg, UINT msg, WPARAM wp, LPARAM lp )
{
	char	*fname;		// ファイル名
	static FILE *fp;	// FILEへのポインタ
	static FILE *fp1;

	int year, month, day, hour, min, sec;	//ETを秒で求めたい年, 月, 日, 時, 分, 秒(UTC)
	
	int i;
	double Time;
	double Time_now;
	double dt;
	double theta;
	double RA, DEC; //赤経、赤
	double koukei, koui; //黄経、黄緯

	switch(msg){
		case WM_INITDIALOG:

			//2019年12月26日12時0分0秒(UTC)に初期設定する。
			SetDlgItemInt(hDlg, IDC_EDIT_Y, 2019, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_M, 12, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_D, 26, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_H, 12, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_MIN, 0, FALSE);
			SetDlgItemInt(hDlg, IDC_EDIT_S, 0, FALSE);

			CheckDlgButton( hDlg, IDC_CHECK_DISPLAY1, BST_UNCHECKED);
	
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wp)){
				case IDC_BUTTON_OPEN1:	// CH1のファイルを開く処理
					if( fname = filename() ){
						if ( fp ) fclose ( fp );
						fopen_s ( &fp, fname, "r" );
						//read_data(hDlg, fp, 1);
					//	MessageBox(NULL ,"座標ファイル読み込み成功", "CH1", MB_OK);// ファイルをテキスト読み込みモードで開く

						
						
						if (fname = filename()) {
							if (fp1) fclose(fp1);
							fopen_s(&fp1, fname, "r");
							read_star(hDlg, fp1, 1);
							//MessageBox(NULL, "星のデータ読み込み成功", "CH1", MB_OK);
							fclose(fp1);
						}
					
						if (read_data(hDlg, fp, 1)) 			// CH1で読み込む
							CheckDlgButton(hDlg, IDC_CHECK_DISPLAY1, BST_CHECKED);// チェックボタンを「表示」とする
						
						fclose( fp );
						InvalidateRect(hWnd, NULL, TRUE);
			        }
					
						
					return TRUE;

				case ID_OK://OKボタンが押された
					//MessageBox(NULL ,"座標ファイル読み込み成功", "CH1", MB_OK);
					//Time =  et(year, month, day, hour, min, sec)/*GetDlgItemInt(hDlg, IDC_EDIT_ET, NULL, FALSE)*/;
					
					year = GetDlgItemInt(hDlg, IDC_EDIT_Y, NULL, FALSE);	//エディットボックスから年を読み込む
					month = GetDlgItemInt(hDlg, IDC_EDIT_M, NULL, FALSE);	//以下同様
					day = GetDlgItemInt(hDlg, IDC_EDIT_D, NULL, FALSE);
					hour = GetDlgItemInt(hDlg, IDC_EDIT_H, NULL, FALSE);
					min = GetDlgItemInt(hDlg, IDC_EDIT_MIN, NULL, FALSE);
					sec = GetDlgItemInt(hDlg, IDC_EDIT_S, NULL, FALSE);

					//関数etに上記を引数として渡すと、秒で表されたElapsed Timeが戻される。
					Time =  et(year, month, day, hour, min, sec);

					for(i=0; i<=total_n; i++){
						if(rh[i].ET > Time){
							g = i-1;
							dt = Time - rh[g].ET;
							//sprintf_s(szBuf, 256, "%d", g);
					        //MessageBox(NULL, szBuf, "超える直前のデータの番号", MB_OK);
							break;
						}
						
					}

					//sprintf_s(szBuf, 256, "%d %lf",g , dt);
					//MessageBox(NULL, szBuf, "データ", MB_OK);

					//sprintf_s(szBuf, 256, "%lf", haET);
					//MessageBox(NULL, szBuf, "元データ", MB_OK);



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
	
		            //t = 360*3474/(2*M_PI*EQL_MOON);//視直径を計算
		            s = (3474.0*0.00005) / EQL_MOON; //月の相対的な大きさを計算

					//sprintf_s(szBuf, 256, "%lf %lf", EQL_MOON, s);
					//MessageBox(NULL, szBuf, "EQL_MOON, s", MB_OK);

					for(i=0; i<=total_n2; i++){
					 RA = 2*M_PI*(h[i].RA_h + h[i].RA_m/60 + h[i].RA_s/3600)/24; //単位を時で統一
		             DEC = 2*M_PI*(h[i].Dec_d + h[i].Dec_m/60 + h[i].Dec_s/3600)/360; //単位を度で統一
		               if (h[i].Dec_sig == FALSE) {
			              DEC = -DEC;
		               }
		             koukei = atan2(sin(M_PI*23.43 / 180)*sin(DEC)+cos(M_PI*23.43 / 180)*cos(DEC)*sin(RA),cos(DEC)*cos(RA)); //単位はrad
		               if (koukei < 0) {
			              koukei = koukei + 2 * M_PI; //単位はrad
		               }
		             koui = asin(cos(M_PI*23.43 / 180)*sin(DEC) - sin(M_PI*23.43 / 180)*cos(DEC)*sin(RA));

		             star[i].x = cos(koui)*cos(koukei);
		             star[i].y = cos(koui)*sin(koukei);
		             star[i].z = sin(koui);
					}

					

		
					//座標変換１
					eql = Cordi_Trans1(eql, moon);
					moon = Cordi_Trans1(moon, moon);
					sun = Cordi_Trans1(sun, moon);
					earth = Cordi_Trans1(earth, moon);
					
				
					//座標変換２
					theta = atan2(eql.y, eql.x);
					eql = Cordi_Trans2(eql, theta);
					sun = Cordi_Trans2(sun, theta);
					earth = Cordi_Trans2(eql, theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
					}
					
					//座標変換３
					theta = atan2(eql.x, eql.z);
					eql = Cordi_Trans3(eql,theta);
					sun = Cordi_Trans3(sun,theta);
					earth = Cordi_Trans3(earth,theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans3(star[i], theta);
					}
					

					//座標変換４
					theta = atan2(-sun.x, sun.y);
					eql = Cordi_Trans2(eql,theta);
					sun = Cordi_Trans2(sun,theta);
					earth = Cordi_Trans2(earth,theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
						if(star[i].z < 0){
							star[i].x = star[i].x * (-50 / star[i].z);
					        star[i].y = star[i].y * (-50 / star[i].z);

					       starx[i] =  /*(988.5*star[i].x)/20*/(star[i].x) / 2 * (988.5 / 10);
					       stary[i] = /*(741*star[i].y)/20*/(star[i].y) / 2 * (741 / 10);

						  
				       }
					}

					if(sun.y > 0){
					  theta = atan2(-sun.x, sun.y) + M_PI;
					  eql = Cordi_Trans2(eql,theta);
					  sun = Cordi_Trans2(sun,theta);
					  earth = Cordi_Trans2(earth,theta);
					 for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
						if(star[i].z < 0){
							star[i].x = star[i].x * (-50 / star[i].z);
					        star[i].y = star[i].y * (-50 / star[i].z);

					       starx[i] =  /*(988.5*star[i].x)/20*/(star[i].x) / 2 * (988.5 / 10);
					       stary[i] = /*(741*star[i].y)/20*/(star[i].y) / 2 * (741 / 10);
				       }

					}
					}


					sprintf_s(szBuf, 256, "%lf %lf %lf %lf", starx[10], stary[10], star[10].x, star[10].y);
					MessageBox(NULL, szBuf, "変換後データ", MB_OK);


					//g = GetDlgItemInt( hDlg, IDC_EDIT_header2, &number, FALSE );
					InvalidateRect(hWnd_bitmap, NULL, TRUE);
					return TRUE;
                
				case ID_Anime:
					year = GetDlgItemInt(hDlg, IDC_EDIT_Y, NULL, FALSE);	//エディットボックスから年を読み込む
					month = GetDlgItemInt(hDlg, IDC_EDIT_M, NULL, FALSE);	//以下同様
					day = GetDlgItemInt(hDlg, IDC_EDIT_D, NULL, FALSE);
					hour = GetDlgItemInt(hDlg, IDC_EDIT_H, NULL, FALSE);
					min = GetDlgItemInt(hDlg, IDC_EDIT_MIN, NULL, FALSE);
					sec = GetDlgItemInt(hDlg, IDC_EDIT_S, NULL, FALSE);

					//関数etに上記を引数として渡すと、秒で表されたElapsed Timeが戻される。
					Time =  et(year, month, day, hour, min, sec);
					
					for(i=0; i<=total_n; i++){
						if(rh[i].ET > Time){
							g = i-1;
							//dt = Time - rh[g].ET;
							//sprintf_s(szBuf, 256, "%d", g);
					        //MessageBox(NULL, szBuf, "超える直前のデータの番号", MB_OK);
							break;
						}
						
					}
					SetTimer(hWnd_bitmap, ID_MYTIMER, 5, NULL);

					return TRUE;

				case ID_STOP:
					KillTimer(hWnd_bitmap, 1);
					return TRUE;

				case ID_NOW:
					Time_now = now()/*GetDlgItemInt(hDlg, IDC_EDIT_NOW, NULL, FALSE)*/;
					
					for(i=0; i<=total_n; i++){
						if(rh[i].ET > Time_now){
							g = i-1;
							dt = Time_now - rh[g].ET;
							//sprintf_s(szBuf, 256, "%d", g);
					        //MessageBox(NULL, szBuf, "超える直前のデータの番号", MB_OK);
							break;
						}
						
					}

					//sprintf_s(szBuf, 256, "%d %lf",g , dt);
					//MessageBox(NULL, szBuf, "データ", MB_OK);

					//sprintf_s(szBuf, 256, "%lf", haET);
					//MessageBox(NULL, szBuf, "元データ", MB_OK);



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
	
		            //t = 360*3474/(2*M_PI*EQL_MOON);//視直径を計算
		            s = (3474.0*0.00005) / EQL_MOON; //月の相対的な大きさを計算

					//sprintf_s(szBuf, 256, "%lf %lf", EQL_MOON, s);
					//MessageBox(NULL, szBuf, "EQL_MOON, s", MB_OK);

					for(i=0; i<=total_n2; i++){
					 RA = 2*M_PI*(h[i].RA_h + h[i].RA_m/60 + h[i].RA_s/3600)/24; //単位を時で統一
		             DEC = 2*M_PI*(h[i].Dec_d + h[i].Dec_m/60 + h[i].Dec_s/3600)/360; //単位を度で統一
		               if (h[i].Dec_sig == FALSE) {
			              DEC = -DEC;
		               }
		             koukei = atan2(sin(M_PI*23.43 / 180)*sin(DEC)+cos(M_PI*23.43 / 180)*cos(DEC)*sin(RA),cos(DEC)*cos(RA)); //単位はrad
		               if (koukei < 0) {
			              koukei = koukei + 2 * M_PI; //単位はrad
		               }
		             koui = asin(cos(M_PI*23.43 / 180)*sin(DEC) - sin(M_PI*23.43 / 180)*cos(DEC)*sin(RA));

		             star[i].x = cos(koui)*cos(koukei);
		             star[i].y = cos(koui)*sin(koukei);
		             star[i].z = sin(koui);
					}

		
					//座標変換１
					eql = Cordi_Trans1(eql, moon);
					moon = Cordi_Trans1(moon, moon);
					sun = Cordi_Trans1(sun, moon);
					earth = Cordi_Trans1(earth, moon);
					
				
					//座標変換２
					theta = atan2(eql.y, eql.x);
					eql = Cordi_Trans2(eql, theta);
					sun = Cordi_Trans2(sun, theta);
					earth = Cordi_Trans2(eql, theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
					}

					//座標変換３
					theta = atan2(eql.x, eql.z);
					eql = Cordi_Trans3(eql,theta);
					sun = Cordi_Trans3(sun,theta);
					earth = Cordi_Trans3(earth,theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans3(star[i], theta);
					}

					//座標変換４
					theta = atan2(-sun.x, sun.y);
					eql = Cordi_Trans2(eql,theta);
					sun = Cordi_Trans2(sun,theta);
					earth = Cordi_Trans2(earth,theta);
					for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
						if(star[i].z < 0){
							star[i].x = star[i].x * (-50 / star[i].z);
					        star[i].y = star[i].y * (-50 / star[i].z);

					       //star[i].x = (star[i].x) / 2 * (988.5 / 10);
					      // star[i].y = (star[i].y) / 2 * (741 / 10);
				       }
					}

					if(sun.y > 0){
					  theta = atan2(-sun.x, sun.y) + M_PI;
					  eql = Cordi_Trans2(eql,theta);
					  sun = Cordi_Trans2(sun,theta);
					  earth = Cordi_Trans2(earth,theta);
					 for(i=0; i<=total_n2; i++){
						star[i] = Cordi_Trans2(star[i], theta);
						if(star[i].z < 0){
							star[i].x = star[i].x * (-50 / star[i].z);
					        star[i].y = star[i].y * (-50 / star[i].z);

					       //star[i].x = (star[i].x) / 2 * (988.5 / 10);
					       //star[i].y = (star[i].y) / 2 * (741 / 10);
				       }
					}
					}


					//sprintf_s(szBuf, 256, "%lf %lf", star[5].x, star[5].y);
					//MessageBox(NULL, szBuf, "変換後データ", MB_OK);


					//g = GetDlgItemInt( hDlg, IDC_EDIT_header2, &number, FALSE );
					InvalidateRect(hWnd_bitmap, NULL, TRUE);
					return TRUE;


				case IDCANCEL:				//右上の×クリックで終了
					PostQuitMessage(0);
					DestroyWindow (hWnd);
					
					DestroyWindow (hDlg);
					return TRUE;

						}
			return TRUE;

	}
	return FALSE;
}
