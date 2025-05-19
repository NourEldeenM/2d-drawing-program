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