#include <windows.h>
#include <cmath>

void DrawPoints(HDC hdc, int xc, int yc, int x, int y, COLORREF color){
	int dx[] = { x, -x, x, -x, y, -y, y, -y };
	int dy[] = { y, y, -y, -y, x, x, -x, -x };
	for (int i = 0; i < 8; i++)
		SetPixel(hdc, xc + dx[i], yc + dy[i], color);
}

void DrawCircleCartesian(HDC hdc, int xc, int yc, int radius, COLORREF color){
	int x = 0, y = radius;
	DrawPoints(hdc, xc, yc, x, y, color);
	while (x < y){
		++x;
		y = round(sqrt(radius * radius - x * x));
		DrawPoints(hdc, xc, yc, x, y, color);
	}
}

void DrawCirclePolar(HDC hdc, int xc, int yc, int radius, COLORREF color){
    double theta = 0, piOver4 = 3.14159 / 4, thetaInc = 1.0 / radius;
    while (theta < piOver4){
        int x = round(radius * cos(theta));
        int y = round(radius * sin(theta));
        DrawPoints(hdc, xc, yc, x, y, color);
        theta += thetaInc;
    }
}

void DrawCirclePolarIterative(HDC hdc, int xc, int yc, int radius, COLORREF color){
    double thetaInc = 1.0 / radius;
    double sinTheta = sin(thetaInc), cosTheta = cos(thetaInc);
    double x = radius, y = 0;
    DrawPoints(hdc, xc, yc, x, y, color);
    while (x > y){
        double temp = x * cosTheta - y * sinTheta;
        y = x * sinTheta + y * cosTheta;
        x = temp;
        DrawPoints(hdc, xc, yc, round(x), round(y), color);
    }
}

void DrawCircleMidPoint(HDC hdc, int xc, int yc, int radius, COLORREF color){
    int x = 0, y = radius;
    DrawPoints(hdc, xc, yc, x, y, color);
    while (x < y){
        double d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - radius * radius;
        x++;
        if (d > 0)
            y--;
        DrawPoints(hdc, xc, yc, x, y, color);
    }
}

void DrawCircleMidPointDDA(HDC hdc, int xc, int yc, int radius, COLORREF color){
    int x = 0, y = radius;
    int d = 1 - radius;
    DrawPoints(hdc, xc, yc, x, y, color);
    while (x < y){
        if (d < 0)
            d += (x << 1) + 3;
        else
            d += ((x - y) << 1) + 5,
            --y;
        ++x;
        DrawPoints(hdc, xc, yc, x, y, color);
    }
}

void DrawCircleMidPointDDAModified(HDC hdc, int xc, int yc, int radius, COLORREF color){
    int x = 0, y = radius, d = 1 - radius;
    int d1 = 3, d2 = ((x - y) << 1) + 5;
    DrawPoints(hdc, xc, yc, x, y, color);
    while (x < y){
        if (d < 0)
            d += d1,
            d2 += 2;
        else
            --y,
            d += d2,
            d2 += 4;
        ++x;
        d1 += 2;
        DrawPoints(hdc, xc, yc, x, y, color);
    }
}
