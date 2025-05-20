#include <windows.h>
#include <queue>
#include <stack>
#include "Point.cpp"

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void FloodFillRecursive(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor) {
    COLORREF currentColor = GetPixel(hdc, x, y);
    if (currentColor == fillColor || currentColor == borderColor)
        return;

    SetPixel(hdc, x, y, fillColor);

    for (int i = 0; i < 4; ++i)
        FloodFillRecursive(hdc, x + dx[i], y + dy[i], borderColor, fillColor);
}

void FloodFillSimulatedRecursive(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor) {
    stack<Point> st;
    st.push(Point(x, y));

    while (!st.empty()) {
        Point p = st.top();
        st.pop();

        COLORREF currentColor = GetPixel(hdc, p.x, p.y);
        if (currentColor == fillColor || currentColor == borderColor)
            continue;

        SetPixel(hdc, p.x, p.y, fillColor);

        for (int i = 0; i < 4; ++i)
            st.push(Point(p.x + dx[i], p.y + dy[i]));
        
    }
}

void FloodFill(HDC hdc, int x, int y, COLORREF borderColor, COLORREF fillColor) {
    queue<Point> q;
    q.push(Point(x, y));

    while (!q.empty()) {
        Point p = q.front();
        q.pop();

        COLORREF currentColor = GetPixel(hdc, p.x, p.y);
        if (currentColor == fillColor || currentColor == borderColor)
            continue;

        SetPixel(hdc, p.x, p.y, fillColor);

        for (int i = 0; i < 4; ++i)
            q.push(Point(p.x + dx[i], p.y + dy[i]));
        
    }
}