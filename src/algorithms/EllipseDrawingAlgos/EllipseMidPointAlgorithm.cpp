#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class EllipseMidPointAlgorithm : public DrawingAlgorithm {
public:
    EllipseMidPointAlgorithm() {
        setName((char*)"Ellipse Mid Point");
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
        int dx = (bSq << 1) * x, dy = (aSq << 1) * y;
        Color color = drawingColors.empty() ? BLACK : drawingColors.back();
        DrawEllipsePoints(center, {x, y}, color, result);
        while(dx < dy){
            double d = (x + 1.0) * (x + 1.0) / aSq + (y - 0.5) * (y - 0.5) / bSq - 1;
            if (d > 0)
                --y,
                dy -= (aSq << 1);
            dx += (bSq << 1);
            ++x;
            DrawEllipsePoints(center, {x, y}, color, result);
        }
        while(y >= 0){
            double d = (x + 0.5) * (x + 0.5) / aSq + (y - 1.0) * (y - 1.0) / bSq - 1;
            if (d < 0)
                ++x,
                dx += (bSq << 1);
            dy -= (aSq << 1);
            --y;
            DrawEllipsePoints(center, {x, y}, color, result);
        }
        return result;
    }
};
