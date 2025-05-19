#include <windows.h>
#include <cmath>
#include <vector>
#include "Matrix.cpp"
using namespace std;

vector<vector<int>> BezierMatrix = {
    {-1, 3, -3, 1},
    {3, -6, 3, 0},
    {-3, 3, 0, 0},
    {1, 0, 0, 0}
};

void cubicBezierCurve(
    HDC hdc,
    vector<int> x,
    vector<int> y,
    int numOfPoints,
    COLORREF color
) {
    double step = 1.0 / numOfPoints;
    x = multiplyMatrixByVector(BezierMatrix, x);
    y = multiplyMatrixByVector(BezierMatrix, y);
    for (double t = 0; t <= 1; t += step) {
        int px = round(x[0] * t * t * t + x[1] * t * t + x[2] * t + x[3]);
        int py = round(y[0] * t * t * t + y[1] * t * t + y[2] * t + y[3]);
        SetPixel(hdc, px, py, color);
    }
}

void cubicBezierCurveWithInterpolatedColors(
    HDC hdc,
    vector<int> x,
    vector<int> y,
    int numOfPoints,
    vector<COLORREF> colors
) {
    double step = 1.0 / numOfPoints;
    vector<int> reds(colors.size()), greens(colors.size()), blues(colors.size());
    for (int i = 0; i < colors.size(); i++) {
        reds[i] = GetRValue(colors[i]);
        greens[i] = GetGValue(colors[i]);
        blues[i] = GetBValue(colors[i]);
    }
    x = multiplyMatrixByVector(BezierMatrix, x);
    y = multiplyMatrixByVector(BezierMatrix, y);
    reds = multiplyMatrixByVector(BezierMatrix, reds);
    greens = multiplyMatrixByVector(BezierMatrix, greens);
    blues = multiplyMatrixByVector(BezierMatrix, blues);
    for (double t = 0; t <= 1; t += step) {
        int px = round(x[0] * t * t * t + x[1] * t * t + x[2] * t + x[3]);
        int py = round(y[0] * t * t * t + y[1] * t * t + y[2] * t + y[3]);
        COLORREF color = RGB(
            round(reds[0] * t * t * t + reds[1] * t * t + reds[2] * t + reds[3]),
            round(greens[0] * t * t * t + greens[1] * t * t + greens[2] * t + greens[3]),
            round(blues[0] * t * t * t + blues[1] * t * t + blues[2] * t + blues[3])
        );
        SetPixel(hdc, px, py, color);
    }
}
