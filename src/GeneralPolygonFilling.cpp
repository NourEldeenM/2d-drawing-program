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

struct Node {
    double x,mi;
    int y;
    Node(double x, double mi, int y) : x(x), mi(mi), y(y) {}
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


void EdgeToTable(Point p1, Point p2, vector<vector<Node>>& table){
    if (p1.y == p2.y)
        return;
    if (p1.y > p2.y)
        swap(p1, p2);
    table[p1.y].push_back(Node(p1.x, (double) (p2.x - p1.x) / (p2.y - p1.y), p2.y));
}

void PolygonToTable(vector<Point>& points, vector<vector<Node>>& table){
    int n = points.size();
    for (int i = 0; i < n - 1; i++)
        EdgeToTable(points[i], points[(i + 1) % n], table);
    EdgeToTable(points[n - 1], points[0], table);
}

void TableToScreen(HDC hdc, vector<vector<Node>>& table, COLORREF color){
    int y = 0;
    while(table[y].empty())
        y++;
    auto active = table[y];
    while(!active.empty()){
        sort(active.begin(), active.end(), [](const Node& a,const Node& b) { return a.x < b.x; });
        for (int i = 0; i < active.size(); i += 2)
            DrawLineMidPointDDA(hdc, active[i].x, y, active[i + 1].x, y, color);
        
        y++;
        vector<Node> newActive;
        for (auto& node : active) {
            node.x += node.mi;
            if (node.y != y)
                newActive.push_back(node);
        }
        active = newActive;
        if (y < table.size())
            for (auto& node : table[y])
                active.push_back(node);
    }
}

void PolygonFill(HDC hdc, vector<Point>& points, COLORREF color) {
    vector<vector<Node>> table(800);
    PolygonToTable(points, table);
    TableToScreen(hdc, table, color);
}