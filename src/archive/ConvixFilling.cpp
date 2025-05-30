#include <windows.h>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    Point() : x(0), y(0) {}
};


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


void EdgeToTable(Point p1, Point p2, vector<pair<int,int>>& table){
    if (p1.y == p2.y)
        return;
    if (p1.y > p2.y)
        swap(p1, p2);
    
    double x = p1.x,mi = (double)(p2.x - p1.x) / (p2.y - p1.y);
    for (int y = p1.y; y < p2.y; y++){
        if (x < table[y].first)
            table[y].first = ceil(x);
        if (x > table[y].second)
            table[y].second = floor(x);
        x += mi;
    }
}

void PolygonToTable(vector<Point>& points, vector<pair<int,int>>& table){
    int n = points.size();
    for (int i = 0; i < n - 1; i++)
        EdgeToTable(points[i], points[(i + 1) % n], table);
    EdgeToTable(points[n - 1], points[0], table);
}

void TableToScreen(HDC hdc, vector<pair<int,int>>& table, COLORREF color){
    for (int i = 0; i < table.size(); i++)
        if (table[i].first < table[i].second)
            DrawLineMidPointDDA(hdc, table[i].first, i, table[i].second, i, color);
}

void ConvexFill(HDC hdc, vector<Point>& points, COLORREF color) {
    vector<pair<int,int>> table(800, {INT_MAX, INT_MIN});
    PolygonToTable(points, table);
    TableToScreen(hdc, table, color);
}