#include <windows.h>
#include <algorithm>
#include <cmath>
#include <Point.cpp>
#include <vector>
#include <utility>
#include "LineDrawing.cpp"
using namespace std;

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