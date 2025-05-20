#include "Point.cpp"
#include <windows.h>
#include <algorithm>
#include <cmath>

int getOutCode(Point p, int xLeft, int xRight, int yBottom, int yTop){
    int code = 0;
    if (p.x < xLeft)
        code |= 1 << 0;
    if (p.x > xRight)
        code |= 1 << 1;
    if (p.y < yBottom)
        code |= 1 << 2;
    if (p.y > yTop)
        code |= 1 << 3;
    return code;
}

Point getVerticalIntersect(Point p1, Point p2, int xEdge){
    return Point(xEdge, round(p1.y + (double)(xEdge - p1.x) * (p2.y - p1.y) / (p2.x - p1.x)));
}

Point getHorizontalIntersect(Point p1, Point p2, int yEdge){
    return Point(round(p1.x + (double)(yEdge - p1.y) * (p2.x - p1.x) / (p2.y - p1.y)), yEdge);
}

bool canClipAndModifyIfCan(Point& p1, Point& p2, int xLeft, int xRight, int yBottom, int yTop){
    int code1 = getOutCode(p1, xLeft, xRight, yBottom, yTop);
    int code2 = getOutCode(p2, xLeft, xRight, yBottom, yTop);
    Point newP1 = p1, newP2 = p2;
    while (true){
        if (!(code1 | code2)){
            p1 = newP1;
            p2 = newP2;
            return true;
        }
        if (code1 & code2)
            return false;
        int codeOut = code1 ? code1 : code2;
        Point intersect;
        if (codeOut & (1 << 3))
            intersect = getHorizontalIntersect(p1, p2, yTop);
        else if (codeOut & (1 << 2))
            intersect = getHorizontalIntersect(p1, p2, yBottom);
        else if (codeOut & (1 << 1))
            intersect = getVerticalIntersect(p1, p2, xRight);
        else if (codeOut & (1 << 0))
            intersect = getVerticalIntersect(p1, p2, xLeft);

        if (codeOut == code1){
            newP1 = intersect;
            code1 = getOutCode(newP1, xLeft, xRight, yBottom, yTop);
        }
        else{
            newP2 = intersect;
            code2 = getOutCode(newP2, xLeft, xRight, yBottom, yTop);
        }
    }
}