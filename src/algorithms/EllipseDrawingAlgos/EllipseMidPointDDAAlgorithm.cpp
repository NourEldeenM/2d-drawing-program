#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class EllipseMidPointDDAAlgorithm : public DrawingAlgorithm {
public:
    EllipseMidPointDDAAlgorithm() {
        setName((char*)"Ellipse Mid Point DDA");
        setRequiredPoints(3);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3) return result;
        Point center = pts[0];
        Point p1 = pts[1], p2 = pts[2];
        int a = abs(p1.x - center.x);
        int b = abs(p2.y - center.y);
        int x = 0, y = b;
        int aSq = a * a, bSq = b * b;
        double d = bSq - aSq * b + 0.25 * aSq;
        int dx = (bSq << 1) * x, dy = (aSq << 1) * y;
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        DrawEllipsePoints(center, {x, y}, color, result);
        while(dx < dy){
            double d = (x + 1.0) * (x + 1.0) / aSq + (y - 0.5) * (y - 0.5) / bSq - 1;
            if (d > 0)
                --y,
                dy -= (aSq << 1),
                d -= dy;
            dx += (bSq << 1);
            d += dx + bSq;
            ++x;
            DrawEllipsePoints(center, {x, y}, color, result);
        }
        d = (bSq * (x + 0.5) * (x + 0.5) + aSq * (y - 1) * (y - 1) - aSq * bSq);
        while(y >= 0){
            double d = (x + 0.5) * (x + 0.5) / aSq + (y - 1.0) * (y - 1.0) / bSq - 1;
            if (d < 0)
                ++x,
                dx += (bSq << 1),
                d += dx;
            dy -= (aSq << 1);
            d += aSq - dy;
            --y;
            DrawEllipsePoints(center, {x, y}, color, result);
        }
        return result;
    }
};
