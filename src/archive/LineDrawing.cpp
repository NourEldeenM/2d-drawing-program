#include <windows.h>
#include <algorithm>
#include <cmath>
using namespace std;
int Round(double x)
{
	return (int)(x + 0.5);
}

void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
	int dx = x2 - x1, dy = y2 - y1;
	SetPixel(hdc, x1, y1, c);

	if (abs(dx) >= abs(dy)) {
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
			dx = x2 - x1; dy = y2 - y1;
		}

		double m = (dx == 0) ? 0 : (double)dy / dx;
		int x = x1;
		double y = y1;
		while (x <= x2) {
			x++;
			y += m;
			SetPixel(hdc, x, Round(y), c);
		}
	}
	else {
		if (y1 > y2) {
			swap(x1, x2);
			swap(y1, y2);
			dx = x2 - x1; dy = y2 - y1;
		}

		double mi = (dy == 0) ? 0 : (double)dx / dy;
		int y = y1;
		double x = x1;
		while (y <= y2) {
			y++;
			x += mi;
			SetPixel(hdc, Round(x), y, c);
		}
	}
}

void DrawLineBres(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
	int x = x1, y = y1;
	int dx, dy, d, d1, d2;
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	SetPixel(hdc, x, y, c);
	int xinc = (x1 < x2) ? 1 : -1;
	int yinc = (y1 < y2) ? 1 : -1;
	if (dy <= dx) { //slope <= 1 || slope >= -1
		d = dx - 2 * dy;
		d1 = -2 * dy; //d>0
		d2 = 2 * (dx - dy); //d>0
		while (x != x2) {
			if (d > 0) {
				d += d1;
			}
			else {
				d += d2;
				y += yinc;
			}
			x += xinc;
			SetPixel(hdc, x, y, c);
		}
	}
	else { //slope > 1 || slope < -1
		d = 2 * dx - dy;
		d1 = 2 * dx;
		d2 = 2 * (dx - dy);
		while (y != y2) {
			if (d > 0) {
				d += d2;
				x += xinc;
			}
			else {
				d += d1;
			}
			y += yinc;
			SetPixel(hdc, x, y, c);
		}
	}
}

void DrawParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c1, COLORREF c2) {
	int r1 = GetRValue(c1), g1 = GetGValue(c1), b1 = GetBValue(c1);
	int r2 = GetRValue(c2), g2 = GetGValue(c2), b2 = GetBValue(c2);
	int alpha1 = x2 - x1, alpha2 = y2 - y1, alphaRed = r2 - r1, alphaGreen = g2 - g1, alphaBlue = b2 - b1;
	SetPixel(hdc, x1, y1, c1);
	double step = 1.0 / max(abs(alpha1), abs(alpha2));
	for (double t = 0; t <= 1; t += step)
		SetPixel(hdc, round(x1 + t * alpha1), round(y1 + t * alpha2), RGB(round(r1 + t * alphaRed), round(g1 + t * alphaGreen), round(b1 + t * alphaBlue)));

}
