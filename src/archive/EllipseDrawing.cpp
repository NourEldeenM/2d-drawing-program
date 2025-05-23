#include <windows.h>
#include <cmath>
#include <algorithm>
using namespace std;

void DrawPoints(HDC hdc, int xc, int yc, int x, int y, COLORREF color){
	int dx[] = { x, -x, x, -x };
	int dy[] = { y, y, -y, -y };
	for (int i = 0; i < 4; i++)
		SetPixel(hdc, xc + dx[i], yc + dy[i], color);
}

void DrawEllipseCartesian(HDC hdc, int xc, int yc, int a, int b, COLORREF color){
	int x = 0, y = b;
	DrawPoints(hdc, xc, yc, x, y, color);
	while (x < a){
		++x;
		y = round(sqrt((1.0 - (double)(x * x) / (a * a))) * b);
		DrawPoints(hdc, xc, yc, x, y, color);
	}
	x = a, y = 0;
	while (y < b){
		++y;
		x = round(sqrt((1.0 - (double)(y * y) / (b * b))) * a);
		DrawPoints(hdc, xc, yc, x, y, color);
	}
	
}

void DrawEllipsePolar(HDC hdc, int xc, int yc, int a, int b, COLORREF color){
	for (double theta = 0; theta <  M_PI / 2; theta += 0.001){
		int x = round(a * cos(theta));
		int y = round(b * sin(theta));
		DrawPoints(hdc, xc , yc , x, y, color);
	}
}

void DrawEllipsePolar2(HDC hdc, int xc, int yc, int a, int b, COLORREF color){
	double thetaInc = 1.0 / max(a, b);
    double sinTheta = sin(thetaInc), cosTheta = cos(thetaInc);
    double x = a, y = 0;
    DrawPoints(hdc, xc, yc, x, y, color);
    while (x > 0)
    {
        double temp = x * cosTheta - (y / b) * a * sinTheta;
        y = (x / a) * b * sinTheta + y * cosTheta;
        x = temp;
        DrawPoints(hdc, xc, yc, round(x), round(y), color);
    }
}

void DrawEllipseMidPoint(HDC hdc, int xc, int yc, int a, int b, COLORREF color){
	int x = 0, y = b;
	int aSq = a * a, bSq = b * b;
	DrawPoints(hdc, xc, yc, x, y, color);
	int dx = (bSq << 1) * x, dy = (aSq << 1) * y;
	while(dx < dy){
		double d = (x + 1.0) * (x + 1.0) / aSq + (y - 0.5) * (y - 0.5) / bSq - 1;
		if (d > 0)
			--y,
			dy -= (aSq << 1);
		dx += (bSq << 1);
		++x;
		DrawPoints(hdc, xc, yc, x, y, color);
	}
	while(y >= 0){
		double d = (x + 0.5) * (x + 0.5) / aSq + (y - 1.0) * (y - 1.0) / bSq - 1;
		if (d < 0)
			++x,
			dx += (bSq << 1);
		dy -= (aSq << 1);
		--y;
		DrawPoints(hdc, xc, yc, x, y, color);
	}
}

void DrawEllipseMidPointDDA(HDC hdc, int xc, int yc, int a, int b, COLORREF color){
	int x = 0, y = b;
	int aSq = a * a, bSq = b * b;
	double d = bSq - aSq * b + 0.25 * aSq;
	DrawPoints(hdc, xc, yc, x, y, color);
	int dx = (bSq << 1) * x, dy = (aSq << 1) * y;
	while(dx < dy){
		double d = (x + 1.0) * (x + 1.0) / aSq + (y - 0.5) * (y - 0.5) / bSq - 1;
		if (d > 0)
			--y,
			dy -= (aSq << 1),
			d -= dy;
		dx += (bSq << 1);
		d += dx + bSq;
		++x;
		DrawPoints(hdc, xc, yc, x, y, color);
	}
	d = (bSq * (x + 0.5) * (x + 0.5) + aSq * (y - 1) * (y - 1) - aSq * bSq);
	while(y >= 0){
		double d = (x + 0.5) * (x + 0.5) / aSq + (y - 1.0) * (y - 1.0) / bSq - 1;
		if (d < 0)
			++x,
			dx += (bSq << 1),
			d += dx;
		dy -= (aSq << 1);
		d += aSq - dy;
		--y;
		DrawPoints(hdc, xc, yc, x, y, color);
	}
}