#include <windows.h>
#include <algorithm>
#include <cmath>
#include <Point.cpp>

void drawQuadCurve(
    HDC hdc, 
    Point p1,
    Point p2,
    Point p3,
    int numOfPoints,
    COLORREF color
){
    int alpha1 = (p1.x << 1) - (p2.x << 2) + (p3.x << 1), alpha2 = (p1.y << 1) - (p2.y << 2) + (p3.y << 1);
    int beta1 = -3*p1.x + (p2.x << 2) - p3.x, beta2 = -3*p1.y + (p2.y << 2) - p3.y;
    SetPixel(hdc, p1.x, p1.y, color);
    double step = 1.0 / numOfPoints;
    for (double t = 0; t <= 1; t += step)
        SetPixel(
            hdc,
            round(alpha1*t*t + beta1 * t + p1.x), 
            round(alpha2*t*t + beta2 * t + p1.y),
            color
        );
    
}

void drawQuadCurveInterpolatedColors(
    HDC hdc, 
    Point p1,
    Point p2,
    Point p3,
    int numOfPoints,
    COLORREF c1, COLORREF c2
){
    int r1 = GetRValue(c1), g1 = GetGValue(c1), b1 = GetBValue(c1);
    int r2 = GetRValue(c2), g2 = GetGValue(c2), b2 = GetBValue(c2);
    int alpha1 = (p1.x << 1) - (p2.x << 2) + (p3.x << 1), alpha2 = (p1.y << 1) - (p2.y << 2) + (p3.y << 1);
    int beta1 = -3*p1.x + (p2.x << 2) - p3.x, beta2 = -3*p1.y + (p2.y << 2) - p3.y;
    int alphaRed = r2 - r1, alphaGreen = g2 - g1, alphaBlue = b2 - b1;
    SetPixel(hdc, p1.x, p1.y, c1);
    double step = 1.0 / numOfPoints;
    for (double t = 0; t <= 1; t += step)
        SetPixel(
            hdc,
            round(alpha1*t*t + beta1 * t + p1.x), 
            round(alpha2*t*t + beta2 * t + p1.y),
            RGB(
                round(r1 + t * alphaRed), 
                round(g1 + t * alphaGreen), 
                round(b1 + t * alphaBlue)
            )
        );
    
}