#include  "kobayashi.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

typedef struct{
	HINSTANCE hInst_bitmap;
	HWND hWnd_bitmap;	
	BYTE *lpBmpData;
	BITMAPINFO bmi;
	//BITMAPINFOHEADER bmiHeader;
	char *fname;
	int fsize;
} IMG;



LRESULT CALLBACK WndProc_bitmap( HWND hWnd_bitmap, UINT msg, WPARAM wp, LPARAM lp )
{
	IMG g_img;

	g_img.lpBmpData = NULL;

	PAINTSTRUCT ps;
	HDC hdc, hdc_mem;
	HBITMAP hBmp;
	HBITMAP hBmp2;
	double x,y,z,r;
	int a, b, ab;
	double lam1,lam2,lam3;
	int i;
	
	

	switch (msg) {

	case WM_CREATE: //ウインドウが生成されたときに1度だけ通過
		//時間割り込みの発生タイミングを設定
		//free(g_img.lpBmpData);
	    asdf(now());
		break;
   
	case WM_TIMER:

		switch(wp)
		{
		case ID_MYTIMER:
		//if (wp != ID_MYTIMER)
		//return (DefWindowProc(hWnd_bitmap, msg, wp, lp));
					g = g++;
		           
					eql.x = rh[g].XEQL;
					eql.y = rh[g].YEQL;
					eql.z = rh[g].ZEQL;

					moon.x = rh[g].XMOON;
					moon.y = rh[g].YMOON;
					moon.z = rh[g].ZMOON;

					sun.x = rh[g].XSUN;
					sun.y = rh[g].YSUN;
					sun.z = rh[g].ZSUN;

					earth.x = 0;
					earth.y = 0;
					earth.z = 0;

					EQL_MOON = sqrtf((moon.x - eql.x)*(moon.x - eql.x) + (moon.y - eql.y)*(moon.y - eql.y) + (moon.z - eql.z)*(moon.z - eql.z));
		            SUN_MOON = sqrtf(sun.x * sun.x + sun.y * sun.y + sun.z * sun.z);
		            EARTH_MOON = sqrtf(moon.x * moon.x + moon.y * moon.y + moon.z * moon.z);
	
		            s = (3474.0*0.00005) / EQL_MOON; //月の相対的な大きさを計算

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
					eql2 = Cordi_Trans2(eql,theta);
					sun2 = Cordi_Trans2(sun,theta);
					earth2 = Cordi_Trans2(earth,theta);
					for(i=0; i<=total_n2; i++){
						star_mm[i] = Cordi_Trans2(star[i], theta);
						if(star_mm[i].z < 0){
							star_mm[i].x = star_mm[i].x * (-50 / star_mm[i].z);
					        star_mm[i].y = star_mm[i].y * (-50 / star_mm[i].z);

					       starx_pix[i] = (star_mm[i].x) / 2 * (988.5 / 10);
					       stary_pix[i] = (star_mm[i].y) / 2 * (741 / 10);
				       }
					}

					if(sun2.y > 0){
					  theta = atan2(-sun.x, sun.y) + M_PI;
					  eql2 = Cordi_Trans2(eql,theta);
					  sun2 = Cordi_Trans2(sun,theta);
					  earth2 = Cordi_Trans2(earth,theta);
					 for(i=0; i<=total_n2; i++){
						star_mm[i] = Cordi_Trans2(star[i], theta);
						if(star_mm[i].z < 0){
							star_mm[i].x = star_mm[i].x * (-50 / star_mm[i].z);
					        star_mm[i].y = star_mm[i].y * (-50 / star_mm[i].z);

					       starx_pix[i] = (star_mm[i].x) / 2 * (988.5 / 10);
					       stary_pix[i] = (star_mm[i].y) / 2 * (741 / 10);
				       }
					}
					}
					//InvalidateRect(hWnd_bitmap, NULL, TRUE);
					//free(g_img.lpBmpData);
					asdf(rh[g].ET);
					break;

		case ID_MYTIMER_now:
					//if (wp != ID_MYTIMER_now)
		            //return (DefWindowProc(hWnd_bitmap, msg, wp, lp));
					Time_now = now();
					
					for(i=0; i<=total_n; i++){
						if(rh[i].ET > Time_now){
							g = i-1;
							dt = Time_now - rh[g].ET;
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


					EQL_MOON = sqrtf((moon.x - eql.x)*(moon.x - eql.x) + (moon.y - eql.y)*(moon.y - eql.y) + (moon.z - eql.z)*(moon.z - eql.z));
		            SUN_MOON = sqrtf(sun.x * sun.x + sun.y * sun.y + sun.z * sun.z);
		            EARTH_MOON = sqrtf(moon.x * moon.x + moon.y * moon.y + moon.z * moon.z);
	
		            //t = 360*3474/(2*M_PI*EQL_MOON);//視直径を計算
		            s = (3474.0*0.00005) / EQL_MOON; //月の相対的な大きさを計算

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
					eql2 = Cordi_Trans2(eql,theta);
					sun2 = Cordi_Trans2(sun,theta);
					earth2 = Cordi_Trans2(earth,theta);
					for(i=0; i<=total_n2; i++){
						star_mm[i] = Cordi_Trans2(star[i], theta);
						if(star_mm[i].z < 0){
							star_mm[i].x = star_mm[i].x * (-50 / star_mm[i].z);
					        star_mm[i].y = star_mm[i].y * (-50 / star_mm[i].z);

					       starx_pix[i] = (star_mm[i].x) / 2 * (988.5 / 10);
					       stary_pix[i] = (star_mm[i].y) / 2 * (741 / 10);
				       }
					}

					if(sun2.y > 0){
					  theta = atan2(-sun.x, sun.y) + M_PI;
					  eql2 = Cordi_Trans2(eql,theta);
					  sun2 = Cordi_Trans2(sun,theta);
					  earth2 = Cordi_Trans2(earth,theta);
					 for(i=0; i<=total_n2; i++){
						star_mm[i] = Cordi_Trans2(star[i], theta);
						if(star_mm[i].z < 0){
							star_mm[i].x = star_mm[i].x * (-50 / star_mm[i].z);
					        star_mm[i].y = star_mm[i].y * (-50 / star_mm[i].z);

					       starx_pix[i] = (star_mm[i].x) / 2 * (988.5 / 10);
					       stary_pix[i] = (star_mm[i].y) / 2 * (741 / 10);
				       }
					}
					}

					//InvalidateRect(hWnd_bitmap, NULL, TRUE);
					//free(g_img.lpBmpData);
					asdf(Time_now);
					break;
					
			}
					InvalidateRect(hWnd_bitmap, NULL, FALSE);
					free(g_img.lpBmpData);
					return TRUE;


	case WM_PAINT:
		
		g_img.bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		g_img.bmi.bmiHeader.biWidth = 988/*659*/;
		g_img.bmi.bmiHeader.biHeight = -741/*494*/;
		g_img.bmi.bmiHeader.biPlanes = 1;
		g_img.bmi.bmiHeader.biBitCount = 32;
		g_img.bmi.bmiHeader.biCompression = BI_RGB;
		g_img.bmi.bmiHeader.biSizeImage = 988*741/*659* 494*/ * 4;
		g_img.bmi.bmiHeader.biXPelsPerMeter = 3704;
		g_img.bmi.bmiHeader.biYPelsPerMeter = 3704;
		g_img.bmi.bmiHeader.biClrUsed = 0;
		g_img.bmi.bmiHeader.biClrImportant = 0;

		g_img.lpBmpData = (BYTE *)malloc(988 * 741 * 4);

		RECT rect;

		hdc = BeginPaint(hWnd_bitmap, &ps);
		GetClientRect(hWnd_bitmap, &rect);
		hdc_mem = CreateCompatibleDC(hdc);
		
			for (a = 0; a < 741; a++) {
				for (b = 0; b < 988; b++) {
					
					ab = a*(988 * 4) + b * 4; //始めの項が行数、次の項が左から何ビット目かを表す。（blueの位置を決めている）

					if ((b - (rect.right - rect.left )/2)*(b -( rect.right - rect.left) / 2) + ((rect.bottom - rect.top)/2 - a)*((rect.bottom - rect.top)/2 - a) <= (s / 4 * 1000000 * (rect.right - rect.left) / 10 + 0.5)*(s / 4 * 1000000 * (rect.right - rect.left) / 10 + 0.5)) {

						x = b - (rect.right - rect.left) / 2;
						y = (rect.bottom - rect.top)/2 - a;
						z = sqrtf(-(x*x) - (y*y) + (s / 4 * 1000000 * (rect.right - rect.left) / 10 + 0.5)*(s / 4 * 1000000 * (rect.right - rect.left) / 10 + 0.5));
						r = sqrtf(x*x + y*y + z*z);

						lam1 = (x*sun2.x + y*sun2.y + z*sun2.z) / (r*SUN_MOON); //太陽の方向との内積
						lam2 = (x*earth2.x + y*earth2.y + z*earth2.z) / (r*EARTH_MOON); //地球の方向との内積
						lam3 = (x*eql2.x + y*eql2.y + z*eql2.z) / (r*EQL_MOON); //EQLの方向との内積

						if (lam2 > 0) {
							g_img.lpBmpData[ab] = 224;
							g_img.lpBmpData[ab + 1] = 204;
							g_img.lpBmpData[ab + 2] = 157;
							g_img.lpBmpData[ab + 3] = 0;
						}

					   if (lam1 > 0) {
							g_img.lpBmpData[ab] = 0;
							g_img.lpBmpData[ab + 1] = 100;
							g_img.lpBmpData[ab + 2] = 100;
							g_img.lpBmpData[ab + 3] = 0;
						}

						if (!(lam1 >= 0 || lam2 >= 0)) {
							g_img.lpBmpData[ab] = 179;
							g_img.lpBmpData[ab + 1] = 179;
							g_img.lpBmpData[ab + 2] = 179;
							g_img.lpBmpData[ab + 3] = 0;					
						}

					}

					
					if ((b - (rect.right - rect.left)/2)*(b - (rect.right - rect.left) / 2) + ((rect.bottom - rect.top)/2 - a)*((rect.bottom - rect.top)/2 - a) > (s / 4 * 1000000 * (rect.right - rect.left) / 10 + 0.5)*(s / 4 * 1000000 * (rect.right - rect.left) / 10 + 0.5)) {
						g_img.lpBmpData[ab] = 0;
						g_img.lpBmpData[ab + 1] = 0;
						g_img.lpBmpData[ab + 2] = 0;
						g_img.lpBmpData[ab + 3] = 0;	

					}
				}
			}

			hBmp = CreateDIBitmap(hdc, &(g_img.bmi.bmiHeader), CBM_INIT, g_img.lpBmpData, &(g_img.bmi), DIB_RGB_COLORS);
			free(g_img.lpBmpData);	
			SelectObject(hdc_mem, hBmp);
			SetStretchBltMode(hdc, COLORONCOLOR);
			StretchBlt(hdc, 0, 0, 988, 741, hdc_mem, 0, 0, 988, 741, SRCCOPY);
			disp_axes2(hdc, rect);
			disp_star_xy(hdc, rect, hDlg);
			//asdf(rh[g].ET);
			//asdf(now());
			//TextOut(hdc, 10,10, buf, sizeof(buf)/sizeof(TCHAR));
			DrawText(hdc, buf, -1, &rect, DT_WORDBREAK);
			DeleteDC(hdc);
			DeleteDC(hdc_mem);
			DeleteObject(hBmp);
			EndPaint(hWnd_bitmap, &ps);
			ReleaseDC(hWnd_bitmap, hdc);

		break;
	
	case WM_DESTROY: 
		if (++g = NULL) 
			KillTimer(hWnd_bitmap, ID_MYTIMER);
		KillTimer(hWnd_bitmap, ID_MYTIMER_now);
		PostQuitMessage(0);
		free(g_img.lpBmpData);
	
		break;
		
	
	default:
		return (DefWindowProc(hWnd_bitmap, msg, wp, lp));

	

	}
	return 0;

}