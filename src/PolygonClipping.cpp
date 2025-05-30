#include <windows.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    Point() : x(0), y(0) {}
};

Point getVerticalIntersect(Point p1, Point p2, int xEdge){
    if (p2.x == p1.x) return Point(xEdge, p1.y); // Avoid division by zero
    return Point(xEdge, round(p1.y + (double)(xEdge - p1.x) * (p2.y - p1.y) / (p2.x - p1.x)));
}

Point getHorizontalIntersect(Point p1, Point p2, int yEdge){
    if (p2.y == p1.y) return Point(p1.x, yEdge); // Avoid division by zero
    return Point(round(p1.x + (double)(yEdge - p1.y) * (p2.x - p1.x) / (p2.y - p1.y)), yEdge);
}

vector<Point> clipLeft(vector<Point>& points,int xLeft){
    vector<Point> clipped;
    for (size_t i = 0; i < points.size(); i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % points.size()];

        if (p1.x >= xLeft && p2.x >= xLeft) 
            clipped.push_back(p2);
        else if (p1.x < xLeft && p2.x >= xLeft) {
            clipped.push_back(getVerticalIntersect(p1, p2, xLeft));
            clipped.push_back(p2);
        } 
        else if (p1.x >= xLeft && p2.x < xLeft) 
            clipped.push_back(getVerticalIntersect(p1, p2, xLeft));
    }
    return clipped;
}

vector<Point> clipRight(vector<Point>& points,int xRight){
    vector<Point> clipped;
    for (size_t i = 0; i < points.size(); i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % points.size()];

        if (p1.x <= xRight && p2.x <= xRight) 
            clipped.push_back(p2);
        else if (p1.x > xRight && p2.x <= xRight) {
            clipped.push_back(getVerticalIntersect(p1, p2, xRight));
            clipped.push_back(p2);
        } 
        else if (p1.x <= xRight && p2.x > xRight) 
            clipped.push_back(getVerticalIntersect(p1, p2, xRight));
    }
    return clipped;

}

vector<Point> clipTop(vector<Point>& points, int yTop){
    vector<Point> clipped;
    for (size_t i = 0; i < points.size(); i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % points.size()];

        if (p1.y <= yTop && p2.y <= yTop) 
            clipped.push_back(p2);
        else if (p1.y > yTop && p2.y <= yTop) {
            clipped.push_back(getHorizontalIntersect(p1, p2, yTop));
            clipped.push_back(p2);
        } 
        else if (p1.y <= yTop && p2.y > yTop) 
            clipped.push_back(getHorizontalIntersect(p1, p2, yTop));
    }
    return clipped;

}

vector<Point> clipBottom(vector<Point>& points, int yBottom){
    vector<Point> clipped;
    for (size_t i = 0; i < points.size(); i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % points.size()];

        if (p1.y >= yBottom && p2.y >= yBottom) 
            clipped.push_back(p2);
        else if (p1.y < yBottom && p2.y >= yBottom) {
            clipped.push_back(getHorizontalIntersect(p1, p2, yBottom));
            clipped.push_back(p2);
        } 
        else if (p1.y >= yBottom && p2.y < yBottom) 
            clipped.push_back(getHorizontalIntersect(p1, p2, yBottom));
    }
    return clipped;

}

void PolygonClip(vector<Point>& points, int xLeft, int xRight, int yBottom, int yTop) {
    points = clipLeft(points, xLeft);
    points = clipRight(points, xRight);
    points = clipTop(points, yTop);
    points = clipBottom(points, yBottom);
}