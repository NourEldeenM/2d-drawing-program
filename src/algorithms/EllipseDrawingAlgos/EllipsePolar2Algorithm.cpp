#include "../DrawingAlgorithm.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class EllipsePolar2Algorithm : public DrawingAlgorithm {
public:
    EllipsePolar2Algorithm() {
        setName((char*)"Ellipse Polar Iterative");
        setRequiredPoints(3);
    }
    vector<pair<Point, Color>> draw(vector<Point>& pts, vector<Color> drawingColors = {BLACK}) override {
        vector<pair<Point, Color>> result;
        if (pts.size() < 3) return result;
        Point center = pts[0];
        Point p1 = pts[1], p2 = pts[2];
        int a = abs(p1.x - center.x);
        int b = abs(p2.y - center.y);
        double thetaInc = 1.0 / max(a, b);
        double sinTheta = sin(thetaInc), cosTheta = cos(thetaInc);
        double x = a, y = 0;
        Color color = drawingColors.empty() ? BLACK : drawingColors[0];
        DrawEllipsePoints(center, {static_cast<int>(x), static_cast<int>(y)}, color, result);
        while (x > 0) {
            double temp = x * cosTheta - (y / b) * a * sinTheta;
            y = (x / a) * b * sinTheta + y * cosTheta;
            x = temp;
            DrawEllipsePoints(center, {static_cast<int>(round(x)), static_cast<int>(round(y))}, color, result);
        }
        return result;
    }
};
