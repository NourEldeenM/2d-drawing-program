#include <windows.h>
#include <algorithm>
#include <cmath>
using namespace std;

void DrawLineMidPointDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1, dy = y2 - y1;
    int yStep = (dy < 0) ? -1 : 1;
    dy = abs(dy);
    dx = abs(dx);
    int d = 2 * dy - dx;

    int x = x1, y = y1;
    SetPixel(hdc, x, y, color);

    if (dx >= dy) {
        while (x < x2) {
            x++;
            if (d > 0) {
                y += yStep;
                d -= 2 * dx;
            }
            d += 2 * dy;
            SetPixel(hdc, x, y, color);
        }
    } 
    else {
        d = 2 * dx - dy;
        while ((yStep > 0 && y < y2) || (yStep < 0 && y > y2)) {
            y += yStep;
            if (d > 0) {
                x++;
                d -= 2 * dy;
            }
            d += 2 * dx;
            SetPixel(hdc, x, y, color);
        }
    }
}

void DrawParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c1, COLORREF c2){
    int r1 = GetRValue(c1), g1 = GetGValue(c1), b1 = GetBValue(c1);
    int r2 = GetRValue(c2), g2 = GetGValue(c2), b2 = GetBValue(c2);
    int alpha1 = x2 - x1, alpha2 = y2 - y1,alphaRed = r2 - r1, alphaGreen = g2 - g1, alphaBlue = b2 - b1;
    SetPixel(hdc, x1, y1, c1);
    double step = 1.0 / max(abs(alpha1), abs(alpha2));
    for (double t = 0; t <= 1; t += step)
        SetPixel(hdc, round(x1 + t * alpha1), round(y1 + t * alpha2), RGB(round(r1 + t * alphaRed), round(g1 + t * alphaGreen), round(b1 + t * alphaBlue)));
    
}