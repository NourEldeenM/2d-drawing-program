#include <windows.h>
#include <cmath>
#include <algorithm>

void DrawPoints(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
	int dx[] = { x, -x, x, -x };
	int dy[] = { y, y, -y, -y };
	for (int i = 0; i < 4; i++)
		SetPixel(hdc, xc + dx[i], yc + dy[i], color);
}

void DrawEllipseCartesian(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
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